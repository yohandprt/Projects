from pathlib import Path

import numpy as np
import pandas as pd
import streamlit as st
import matplotlib.pyplot as plt
import seaborn as sns

st.set_page_config(
    page_title="Brain Tumor Dashboard",
    page_icon="🧠",
    layout="wide",
    initial_sidebar_state="expanded",
)

st.markdown("""
<style>
    [data-testid="stMetricValue"] { font-size: 2rem; font-weight: 700; }
    .section-title {
        font-size: 1.1rem; font-weight: 600; color: #4A90D9;
        border-left: 4px solid #4A90D9; padding-left: 10px;
        margin-bottom: 0.5rem; margin-top: 1.5rem;
    }
    .prediction-box {
        background: linear-gradient(135deg, #1e3a5f 0%, #0d1b2a 100%);
        border-radius: 12px; padding: 1.5rem; border: 1px solid #4A90D9;
        color: white;
    }
    .tumor-pill {
        display: inline-block; padding: 6px 18px; border-radius: 20px;
        font-weight: 700; font-size: 1rem; margin: 4px;
    }
</style>
""", unsafe_allow_html=True)

ROOT_DIR = Path(__file__).resolve().parent.parent

MRI_MIXED_TRAIN_PATH  = ROOT_DIR / "datasets/supervised/MRI/mixed_types_train.csv"
MRI_MIXED_TEST_PATH   = ROOT_DIR / "datasets/supervised/MRI/mixed_types_test.csv"
MRI_SEPARATED_TRAIN_PATH = ROOT_DIR / "datasets/supervised/MRI/separated_types_train.csv"
MRI_SEPARATED_TEST_PATH  = ROOT_DIR / "datasets/supervised/MRI/separated_types_test.csv"
YOLO_PATH             = ROOT_DIR / "datasets/supervised/Yolov/brain_tumor_dataset.csv"
STUDENT_PATH          = ROOT_DIR / "datasets/unsupervised/Student_Dataset.csv"

MRI_IMG_TRAIN_PATH    = ROOT_DIR / "BrainTumorYolov/BrainTumorYolov8/train/images/"

MRI_PATHS = {
    "mixed":     {"train": MRI_MIXED_TRAIN_PATH,     "test": MRI_MIXED_TEST_PATH},
    "separated": {"train": MRI_SEPARATED_TRAIN_PATH, "test": MRI_SEPARATED_TEST_PATH},
}

TUMOR_COLORS = {
    "glioma":     "#E74C3C",
    "meningioma": "#F39C12",
    "pituitary":  "#2ECC71",
    "no_tumor":   "#3498DB",
}

MODEL_PERF = {
    "RandomForestClassifier":          {"accuracy": 97.0, "speed": "~0.5s",  "rating": "⭐⭐⭐⭐⭐"},
    "HistGradientBoostingClassifier":  {"accuracy": 97.0, "speed": "~14s",   "rating": "⭐⭐⭐⭐"},
    "LogisticRegression":              {"accuracy": 94.0, "speed": "~30s",   "rating": "⭐⭐⭐"},
    "AdaBoostClassifier":              {"accuracy": 86.0, "speed": "~3s",    "rating": "⭐⭐⭐"},
    "MultinomialNB":                   {"accuracy": 40.0, "speed": "~0s",    "rating": "⭐"},
}


@st.cache_data(show_spinner=False)
def load_csv_file(path: Path) -> pd.DataFrame:
    if not path.exists() or path.stat().st_size == 0:
        return pd.DataFrame()
    return pd.read_csv(path)


@st.cache_data(show_spinner=False)
def load_mri_dataframe(split: str, source: str) -> pd.DataFrame:
    df = load_csv_file(MRI_PATHS[source][split])
    if df.empty:
        return df
    if source == "mixed":
        df = df.copy()
        if "type" not in df.columns:
            df.columns = ["id", "image_name", "type"]
        return df
    return df.melt(id_vars=["id"], var_name="type", value_name="image_name").dropna()


@st.cache_data(show_spinner=False)
def load_yolo_dataframe() -> pd.DataFrame:
    df = load_csv_file(YOLO_PATH)
    if df.empty:
        return df
    df = df.copy()
    coord_cols = [c for c in df.columns if c.startswith(("x", "y"))]
    df[coord_cols] = df[coord_cols].apply(pd.to_numeric, errors="coerce").fillna(0)
    x_cols = [c for c in coord_cols if c.startswith("x")]
    y_cols = [c for c in coord_cols if c.startswith("y")]
    df["active_points"]  = (df[coord_cols] > 0).sum(axis=1)
    df["center_x"]       = compute_center(df, x_cols)
    df["center_y"]       = compute_center(df, y_cols)
    return df


@st.cache_data(show_spinner=False)
def load_student_dataframe() -> pd.DataFrame:
    columns = ["index", "color", "trouble"]
    df = load_csv_file(STUDENT_PATH)
    if df.empty:
        return df
    df.columns = columns[: len(df.columns)]
    return df


def compute_center(df: pd.DataFrame, cols: list[str]) -> pd.Series:
    counts = (df[cols] > 0).sum(axis=1)
    sums   = df[cols].sum(axis=1)
    return (sums / counts.replace(0, 1)).where(counts > 0, 0)


def show_missing_file_warning(path: Path):
    st.warning(f"Fichier manquant ou vide : {path}")


def filter_types(df: pd.DataFrame, selected_types: list[str]) -> pd.DataFrame:
    if not selected_types:
        return df
    return df[df["type"].isin(selected_types)]


def tumor_color(t: str) -> str:
    return TUMOR_COLORS.get(str(t).lower(), "#95a5a6")


def render_distribution_bar(df: pd.DataFrame, col: str = "type", title: str = "Répartition par type"):
    st.markdown(f'<p class="section-title">{title}</p>', unsafe_allow_html=True)
    counts = df[col].value_counts()
    colors = [tumor_color(t) for t in counts.index]
    fig, ax = plt.subplots(figsize=(7, 3))
    bars = ax.barh(counts.index, counts.values, color=colors, edgecolor="none")
    ax.bar_label(bars, padding=4, fontsize=10)
    ax.set_xlabel("Nombre d'images")
    ax.spines[["top", "right", "left"]].set_visible(False)
    ax.tick_params(left=False)
    fig.tight_layout()
    st.pyplot(fig)
    plt.close(fig)


def render_pie_chart(df: pd.DataFrame, col: str = "type", title: str = "Répartition (%)"):
    st.markdown(f'<p class="section-title">{title}</p>', unsafe_allow_html=True)
    counts = df[col].value_counts()
    colors = [tumor_color(t) for t in counts.index]
    fig, ax = plt.subplots(figsize=(5, 4))
    ax.pie(counts.values, labels=counts.index, autopct="%1.1f%%", colors=colors,
           startangle=140, wedgeprops=dict(edgecolor="white", linewidth=2))
    fig.tight_layout()
    st.pyplot(fig)
    plt.close(fig)


def render_basic_metrics(df: pd.DataFrame):
    c1, c2, c3 = st.columns(3)
    c1.metric("Images",       f"{len(df):,}")
    c2.metric("Types",         df["type"].nunique())
    c3.metric("Type dominant", df["type"].mode().iloc[0] if not df.empty else "-")


def render_mri_dashboard(split: str, source: str, selected_types: list[str]):
    df = load_mri_dataframe(split, source)
    if df.empty:
        show_missing_file_warning(MRI_PATHS[source][split])
        return
    df = filter_types(df, selected_types)

    st.title("MRI Dashboard")
    render_basic_metrics(df)

    col1, col2 = st.columns(2)
    with col1:
        render_distribution_bar(df)
    with col2:
        render_pie_chart(df)

    st.markdown('<p class="section-title">Comparaison Train / Test</p>', unsafe_allow_html=True)
    train_df = load_mri_dataframe("train", source)
    test_df  = load_mri_dataframe("test",  source)
    if not train_df.empty and not test_df.empty:
        train_counts = train_df["type"].value_counts().rename("Train")
        test_counts  = test_df["type"].value_counts().rename("Test")
        comp = pd.concat([train_counts, test_counts], axis=1).fillna(0).astype(int)
        fig, ax = plt.subplots(figsize=(8, 3))
        x = np.arange(len(comp))
        w = 0.35
        ax.bar(x - w/2, comp["Train"], w, label="Train", color="#4A90D9", edgecolor="none")
        ax.bar(x + w/2, comp["Test"],  w, label="Test",  color="#E8A838", edgecolor="none")
        ax.set_xticks(x)
        ax.set_xticklabels(comp.index)
        ax.legend()
        ax.spines[["top", "right"]].set_visible(False)
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)
    else:
        st.info("Les deux splits (train/test) sont nécessaires pour cette comparaison.")

    st.markdown('<p class="section-title">Ratio Train/Test global</p>', unsafe_allow_html=True)
    if not train_df.empty and not test_df.empty:
        col_a, col_b = st.columns([1, 2])
        with col_a:
            fig, ax = plt.subplots(figsize=(4, 3))
            ax.pie([len(train_df), len(test_df)], labels=["Train", "Test"],
                   autopct="%1.1f%%", colors=["#4A90D9", "#E8A838"],
                   wedgeprops=dict(edgecolor="white", linewidth=2))
            fig.tight_layout()
            st.pyplot(fig)
            plt.close(fig)
        with col_b:
            st.dataframe(comp.assign(Total=comp.sum(axis=1)), use_container_width=True)

    st.markdown('<p class="section-title">Aperçu des données</p>', unsafe_allow_html=True)
    st.dataframe(df.head(30), use_container_width=True)


def render_yolo_dashboard(selected_types: list[str]):
    df = load_yolo_dataframe()
    if df.empty:
        show_missing_file_warning(YOLO_PATH)
        return
    df = filter_types(df, selected_types)

    st.title("YOLO Dashboard")

    c1, c2, c3, c4 = st.columns(4)
    c1.metric("Lignes",          f"{len(df):,}")
    c2.metric("Types",            df["type"].nunique())
    c3.metric("Images uniques",   df["image_name"].nunique())
    c4.metric("Moy. points actifs", f"{df['active_points'].mean():.1f}")

    col1, col2 = st.columns(2)
    with col1:
        render_distribution_bar(df)
    with col2:
        render_pie_chart(df)

    st.markdown('<p class="section-title">Heatmap des centres de polygones</p>', unsafe_allow_html=True)
    col_heat, col_scatter = st.columns(2)
    with col_heat:
        fig, ax = plt.subplots(figsize=(5, 4))
        h = ax.hist2d(df["center_x"], df["center_y"], bins=30, cmap="YlOrRd")
        plt.colorbar(h[3], ax=ax, label="Densité")
        ax.set_xlabel("center_x")
        ax.set_ylabel("center_y")
        ax.set_title("Densité des centres")
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)
    with col_scatter:
        fig, ax = plt.subplots(figsize=(5, 4))
        for t in df["type"].unique():
            sub = df[df["type"] == t]
            ax.scatter(sub["center_x"], sub["center_y"], label=t,
                       color=tumor_color(t), alpha=0.5, s=15)
        ax.legend(fontsize=8)
        ax.set_title("Centres par type de tumeur")
        ax.set_xlabel("center_x")
        ax.set_ylabel("center_y")
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)

    st.markdown('<p class="section-title">Points actifs par type (boxplot)</p>', unsafe_allow_html=True)
    fig, ax = plt.subplots(figsize=(8, 3))
    types_order = sorted(df["type"].unique())
    data_by_type = [df[df["type"] == t]["active_points"].values for t in types_order]
    bp = ax.boxplot(data_by_type, labels=types_order, patch_artist=True, vert=True)
    for patch, t in zip(bp["boxes"], types_order):
        patch.set_facecolor(tumor_color(t))
        patch.set_alpha(0.7)
    ax.spines[["top", "right"]].set_visible(False)
    ax.set_ylabel("Nombre de points actifs")
    fig.tight_layout()
    st.pyplot(fig)
    plt.close(fig)

    st.markdown('<p class="section-title">Statistiques par type</p>', unsafe_allow_html=True)
    stats = df.groupby("type")["active_points"].agg(
        Moyenne="mean", Min="min", Max="max", Médiane="median", Écart_type="std"
    ).round(2)
    st.dataframe(stats, use_container_width=True)

    st.markdown('<p class="section-title">Aperçu des données</p>', unsafe_allow_html=True)
    st.dataframe(df.head(30), use_container_width=True)


def render_models_dashboard():
    st.title("Modèles IA & Prédiction")

    st.markdown('<p class="section-title">Comparaison des modèles (Apprentissage Supervisé)</p>',
                unsafe_allow_html=True)

    perf_df = pd.DataFrame(MODEL_PERF).T.reset_index().rename(columns={"index": "Modèle"})
    perf_df["accuracy"] = perf_df["accuracy"].astype(float)

    col_chart, col_table = st.columns([2, 1])
    with col_chart:
        fig, ax = plt.subplots(figsize=(8, 4))
        colors = ["#27AE60" if a >= 90 else "#F39C12" if a >= 70 else "#E74C3C"
                  for a in perf_df["accuracy"]]
        bars = ax.barh(perf_df["Modèle"], perf_df["accuracy"], color=colors, edgecolor="none")
        ax.bar_label(bars, labels=[f"{v:.0f}%" for v in perf_df["accuracy"]], padding=4)
        ax.set_xlim(0, 110)
        ax.axvline(90, color="grey", linestyle="--", linewidth=1, alpha=0.5)
        ax.set_xlabel("Précision (%)")
        ax.spines[["top", "right", "left"]].set_visible(False)
        ax.tick_params(left=False)
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)
    with col_table:
        st.dataframe(perf_df[["Modèle", "accuracy", "speed", "rating"]].rename(columns={
            "accuracy": "Précision %", "speed": "Vitesse", "rating": "Note"
        }), use_container_width=True, hide_index=True)

    st.markdown('<p class="section-title">Précision par modèle (radar)</p>', unsafe_allow_html=True)
    labels = list(MODEL_PERF.keys())
    values = [MODEL_PERF[m]["accuracy"] for m in labels]
    N = len(labels)
    angles = [n / float(N) * 2 * np.pi for n in range(N)]
    angles += angles[:1]
    values_plot = values + values[:1]
    fig, ax = plt.subplots(figsize=(5, 5), subplot_kw=dict(polar=True))
    ax.plot(angles, values_plot, "o-", linewidth=2, color="#4A90D9")
    ax.fill(angles, values_plot, alpha=0.25, color="#4A90D9")
    ax.set_thetagrids(np.degrees(angles[:-1]), [label.replace("Classifier", "\nClassifier") for label in labels], fontsize=8)
    ax.set_ylim(0, 100)
    ax.set_yticks([25, 50, 75, 100])
    ax.set_yticklabels(["25%", "50%", "75%", "100%"], fontsize=7)
    ax.set_title("Précision des modèles", pad=20)
    fig.tight_layout()
    st.pyplot(fig)
    plt.close(fig)

    st.divider()

    col_input, col_result = st.columns([1, 1])
    with col_input:
        st.markdown("**Paramètres de simulation**")
        model_choice = st.selectbox(
            "Modèle",
            list(MODEL_PERF.keys()),
            index=0,
        )
        nb_images = st.slider("Nombre d'images à classifier", 1, 50, 10)
        tumor_priors = st.multiselect(
            "Types présents dans le batch (simulation)",
            ["glioma", "meningioma", "pituitary"],
            default=["glioma", "meningioma", "pituitary"],
        )

        predict_btn = st.button("Lancer la prédiction", type="primary", use_container_width=True)

    with col_result:
        if predict_btn and tumor_priors:
            acc = MODEL_PERF[model_choice]["accuracy"] / 100
            rng = np.random.default_rng(42)

            true_labels = rng.choice(tumor_priors, size=nb_images)
            pred_labels = []
            for t in true_labels:
                if rng.random() < acc:
                    pred_labels.append(t)
                else:
                    wrong = [x for x in tumor_priors if x != t]
                    pred_labels.append(rng.choice(wrong) if wrong else t)

            pred_labels = np.array(pred_labels)
            correct = (true_labels == pred_labels).sum()
            simulated_acc = correct / nb_images * 100

            st.markdown(f"### Résultats ({model_choice})")
            mc1, mc2 = st.columns(2)
            mc1.metric("Correct", f"{correct}/{nb_images}")
            mc2.metric("Précision simulée", f"{simulated_acc:.1f}%")

            fig, ax = plt.subplots(figsize=(4, 3))
            conf = pd.crosstab(
                pd.Series(true_labels, name="Réel"),
                pd.Series(pred_labels, name="Prédit"),
                dropna=False
            ).reindex(index=tumor_priors, columns=tumor_priors, fill_value=0)
            sns.heatmap(conf, annot=True, fmt="d", cmap="Blues", ax=ax,
                        linewidths=0.5, cbar=False)
            ax.set_title("Matrice de confusion")
            fig.tight_layout()
            st.pyplot(fig)
            plt.close(fig)
        elif predict_btn:
            st.warning("Veuillez sélectionner au moins un type de tumeur.")
        else:
            st.markdown("*Configurez les paramètres à gauche puis cliquez sur **Lancer la prédiction**.*")

    st.divider()

    st.markdown('<p class="section-title">Apprentissage Non Supervisé — Clustering KMeans</p>',
                unsafe_allow_html=True)

    PALETTE = ["#FF5454","#FFB554","#FCFF54","#87FF54","#54FFF6","#5465FF","#EB54FF","#FF54AA"]
    nb_clusters = st.slider("Nombre de clusters KMeans (simulation)", 2, 12, 8)

    col_sim1, col_sim2 = st.columns(2)
    with col_sim1:
        rng2 = np.random.default_rng(7)
        centers_sim = rng2.uniform(-3, 3, (nb_clusters, 2))
        X_pts = np.vstack([c + rng2.normal(0, 0.5, (20, 2)) for c in centers_sim])
        labels_sim = np.repeat(np.arange(nb_clusters), 20)
        fig, ax = plt.subplots(figsize=(5, 4))
        for k in range(nb_clusters):
            mask = labels_sim == k
            ax.scatter(X_pts[mask, 0], X_pts[mask, 1],
                       color=PALETTE[k % len(PALETTE)], s=25, alpha=0.8, label=f"Cluster {k}")
        ax.scatter(centers_sim[:, 0], centers_sim[:, 1],
                   marker="X", s=120, color="black", zorder=5)
        ax.set_title(f"Projection 2D ({nb_clusters} clusters) — simulation")
        ax.legend(fontsize=7, ncol=2, loc="upper right")
        ax.spines[["top", "right"]].set_visible(False)
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)

    with col_sim2:
        cluster_sizes = [rng2.integers(10, 40) for _ in range(nb_clusters)]
        fig, ax = plt.subplots(figsize=(5, 4))
        ax.bar([f"C{i}" for i in range(nb_clusters)], cluster_sizes,
               color=PALETTE[:nb_clusters], edgecolor="none")
        ax.set_ylabel("Taille du cluster")
        ax.set_title("Répartition des phrases par cluster")
        ax.spines[["top", "right"]].set_visible(False)
        fig.tight_layout()
        st.pyplot(fig)
        plt.close(fig)

    st.markdown('<p class="section-title">Mots-clés simulés par cluster</p>', unsafe_allow_html=True)
    SAMPLE_WORDS = [
        ["anxiety", "stress", "nervous", "worry", "panic"],
        ["sleep", "insomnia", "fatigue", "rest", "tired"],
        ["focus", "attention", "concentration", "memory", "distracted"],
        ["social", "isolation", "loneliness", "friends", "communication"],
        ["pain", "headache", "pressure", "ache", "tension"],
        ["mood", "depression", "sad", "hopeless", "empty"],
        ["appetite", "eating", "weight", "hunger", "diet"],
        ["anger", "frustration", "irritability", "control", "aggressive"],
    ]
    selected_cluster = st.selectbox("Sélectionner un cluster", [f"Cluster {i}" for i in range(nb_clusters)])
    ci = int(selected_cluster.split(" ")[1])
    words_sample = SAMPLE_WORDS[ci % len(SAMPLE_WORDS)]
    freqs_sample = sorted(np.random.default_rng(ci).integers(30, 100, len(words_sample)), reverse=True)
    fig, ax = plt.subplots(figsize=(6, 2.5))
    ax.barh(words_sample, freqs_sample, color=PALETTE[ci % len(PALETTE)], edgecolor="none")
    ax.set_xlabel("Score TF-IDF (×100)")
    ax.set_title(f"Top mots-clés — {selected_cluster}")
    ax.spines[["top", "right", "left"]].set_visible(False)
    ax.tick_params(left=False)
    fig.tight_layout()
    st.pyplot(fig)
    plt.close(fig)

    st.divider()


def build_sidebar() -> tuple[str, str, str, list[str]]:
    st.sidebar.header("Navigation")

    page = st.sidebar.radio(
        "Section",
        ["MRI", "YOLO", "Modèles IA"],
        index=0,
    )

    split, source, selected_types = "train", "mixed", []

    if page == "MRI":
        st.sidebar.divider()
        st.sidebar.subheader("Filtres MRI")
        split  = st.sidebar.selectbox("Split", ["train", "test"])
        source = st.sidebar.radio("Source", ["mixed", "separated"])
        preview = load_mri_dataframe(split, source)
        types = sorted(preview["type"].dropna().unique()) if not preview.empty else []
        selected_types = st.sidebar.multiselect("Types", types, default=types)

    elif page == "YOLO":
        st.sidebar.divider()
        st.sidebar.subheader("Filtres YOLO")
        preview = load_yolo_dataframe()
        types = sorted(preview["type"].dropna().unique()) if not preview.empty else []
        selected_types = st.sidebar.multiselect("Types", types, default=types)

    return page, split, source, selected_types


def main():
    page, split, source, selected_types = build_sidebar()

    if page == "MRI":
        render_mri_dashboard(split, source, selected_types)
    elif page == "YOLO":
        render_yolo_dashboard(selected_types)
    else:
        render_models_dashboard()


main()