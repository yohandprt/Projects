import streamlit as st
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import joblib
import numpy as np

## [CONFIGURATION]

st.set_page_config(
    page_title="TARDIS Dashboard",
    page_icon="🚆",
    layout="wide",
    initial_sidebar_state="expanded",
)

## [INITIALIZATION]

df = pd.read_csv("cleaned_dataset.csv")
SIDEBAR = st.sidebar
COLOR = "#83C9FF"
COLORS = ["white", "#83C9FF", "#6facdc", "#5a8cb3", "#497393", "#385971"]
delays_columns = [
    "Number of trains delayed > 15min",
    "Number of trains delayed > 30min",
    "Number of trains delayed > 60min",
    "Number of cancelled trains",
]
pcts = [
    "Pct delay due to external causes",
    "Pct delay due to infrastructure",
    "Pct delay due to traffic management",
    "Pct delay due to rolling stock",
    "Pct delay due to station management and equipment reuse",
    "Pct delay due to passenger handling (crowding, disabled persons, connections)",
]
pcts_labels = [label[17:].title() for label in pcts[:-1]]
pcts_labels.append("Passenger Handling")

## [SETUP JOURNEY]

c1, c2, c3 = st.columns(3)
with c1:
    depart_station = st.selectbox(
        "Departure station", df["Departure station"].sort_values().dropna().unique()
    )
with c2:
    arriv_station = st.selectbox(
        "Arrival station",
        df[df["Departure station"] == depart_station]["Arrival station"]
        .sort_values()
        .dropna()
        .unique(),
    )
df_journey = df[
    (df["Departure station"] == depart_station)
    & (df["Arrival station"] == arriv_station)
]
with c3:
    date = st.selectbox("Date", df_journey["Date"].sort_values().dropna().unique())
df_stations = df[
    (df["Departure station"] == depart_station)
    & (df["Arrival station"] == arriv_station)
    & (df["Date"] == date)
]


## [UTILS]


def set_colors(fig, ax):
    ax.set_facecolor("none")
    ax.tick_params(colors="white")
    fig.set_facecolor("none")
    fig.set_edgecolor("white")

    ax.title.set_color("white")
    ax.xaxis.label.set_color("white")
    ax.yaxis.label.set_color("white")

    ax.spines["top"].set_color("white")
    ax.spines["left"].set_color("white")
    ax.spines["right"].set_color("white")
    ax.spines["bottom"].set_color("white")


def pass_a_line(repeat):
    if repeat <= 0:
        return
    for i in range(repeat):
        st.markdown("<br>", unsafe_allow_html=True)


def surround(func):
    col = st.columns(1, border=True)
    with col[0]:
        func()


## [JOURNEY INFOS]


def display_infos():
    try:
        if df_stations.empty:
            st.warning("No data for this route.")
            return

        service = df_stations["Service"].dropna().iloc[0]
        col1, col2, col3 = st.columns(3)
        with col1:
            st.markdown(
                f"<h5><b>Departure :</b><br>{depart_station}</h5>",
                unsafe_allow_html=True,
            )
        with col2:
            st.markdown(
                f"<h5><b>Arrival :</b><br>{arriv_station}</h5>", unsafe_allow_html=True
            )
        with col3:
            st.markdown(f"<h5><b>Date :</b><br>{date}</h5>", unsafe_allow_html=True)

        st.markdown("---")

        col4, col5, col6 = st.columns(3)
        with col4:
            st.markdown(f"<h5><b>Service :</b> {service}</h5>", unsafe_allow_html=True)
        with col5:
            try:
                time = pd.to_datetime(
                    df_stations["Average journey time"].mean(), unit="s"
                ).time()
                journey = [item for item in str(time).split(":")]
                st.markdown(
                    f"<h5><b>Average journey time :</b><br> {journey[0]} day(s), {journey[1]} hour(s), {float(journey[2]):.0f} minute(s)</h5>",
                    unsafe_allow_html=True,
                )
            except ValueError:
                st.warning("Unable to compute average journey time.")
        with col6:
            try:
                features = joblib.load("models/features.joblib")
                model = joblib.load("models/gb_model.joblib")
                input_features = df_stations.iloc[0][features]
                input_df = pd.DataFrame([input_features])
                pred_log = model.predict(input_df)[0]
                pred_delay = np.expm1(pred_log)
                st.markdown(
                    f"<h5><b>Average arrival delay:</b><br>{pred_delay:.2f} minutes</h5>",
                    unsafe_allow_html=True,
                )
            except Exception:
                st.warning("Unable to compute predicted average arrival delay.")
    except Exception as error:
        st.error(f"Error while displaying journey information : {error}")


## [DELAY DISTRIBUTION]


def trains_by_delays():
    try:
        times_delays = [
            "Number of trains delayed > 15min",
            "Number of trains delayed > 30min",
            "Number of trains delayed > 60min",
        ]
        labels = ["> 15min", "> 30min", "> 60min"]
        times_figure, axe = plt.subplots()
        sns.barplot(df[times_delays], ax=axe, color=COLOR)
        axe.set_xticks(range(len(labels)))
        axe.set_xticklabels(labels=labels)
        set_colors(times_figure, axe)
        st.pyplot(times_figure)
    except Exception as error:
        st.error(f"Error while displaying delays : {error}")


def avg_delays_all_stations_15min():
    try:
        delay_by_stations = (
            df.groupby("Departure station")[delays_columns].mean().sum(axis=1)
        )
        st.bar_chart(delay_by_stations)
    except Exception as error:
        st.error(f"Error while displaying delays moyens : {error}")


def delays_of_route():
    try:
        pass_a_line(1)
        fig, ax = plt.subplots()
        labels = ["National", "International"]
        delays = df.groupby("Service")[delays_columns].mean().sum(axis=1)
        ax.pie(delays, autopct="%1.1f%%", colors=["white", COLOR])
        ax.legend(
            labels, title="Cause of delay", loc="upper right", bbox_to_anchor=(0, 0.8)
        )
        set_colors(fig, ax)
        st.pyplot(fig)
    except Exception as error:
        st.error(f"Error while displaying delays par type de trajet : {error}")


def trains_by_pct():
    try:
        delay_by_pcts = df[pcts].mean()
        fig, ax = plt.subplots(figsize=(10, 10))
        ax.barh(pcts_labels, delay_by_pcts, color=COLOR)
        ax.tick_params(axis="y", labelsize=20)
        set_colors(fig, ax)
        st.pyplot(fig)
    except Exception as error:
        st.error(f"Error while displaying delay causes : {error}")


def heatmap_correlation():
    try:
        if df_journey.empty:
            st.warning("No data for this route combination.")
            return
        correlation = df_journey[pcts].corr()
        fig, ax = plt.subplots()
        sns.heatmap(correlation, ax=ax, annot=True)
        ax.set_xticklabels(pcts_labels, rotation=45, ha="right")
        ax.set_yticklabels(pcts_labels)
        set_colors(fig, ax)
        st.pyplot(fig)
    except Exception as error:
        st.error(f"Error while displaying correlation heatmap : {error}")


## [STATION-LEVEL ANALYSIS]


def info_along_the_route():
    try:
        if df_stations.empty:
            st.warning("No data for this route.")
            return
        col1, col2 = st.columns(2)
        with col1:
            nb_cancelled = df_stations["Number of cancelled trains"].sum()
            st.markdown(
                f"<h5><b>Cancellation count :</b> {nb_cancelled:.0f}</h5>",
                unsafe_allow_html=True,
            )
        with col2:
            scheduled_trains = df_stations["Number of scheduled trains"].sum()
            delayed_trains = df_stations[delays_columns].mean().sum()
            if scheduled_trains == 0:
                nb_ontime = 0
            else:
                nb_ontime = 100 * (scheduled_trains - delayed_trains) / scheduled_trains
            st.markdown(
                f"<h5><b>Punctuality rates :</b> {nb_ontime:.2f}%</h5>",
                unsafe_allow_html=True,
            )
        st.markdown("---")
        causes = df_stations[pcts]
        mean_causes = causes.mean()
        if isinstance(mean_causes, pd.Series) and not mean_causes.isnull().all():
            cause_max = mean_causes.idxmax()
            st.markdown(
                f"**<h4>Main cause of delay on this route :</h4>**<h5>{cause_max[17:].title()}</h5>",
                unsafe_allow_html=True,
            )
        else:
            st.warning(
                "Unable to determine the main cause of delay (insufficient data)."
            )
    except Exception as error:
        st.error(f"Error during route analysis : {error}")


def comp_between_stations():
    try:
        labels = [depart_station, arriv_station]
        df_depart = df[(df["Departure station"] == depart_station)]
        df_arriv = df[(df["Arrival station"] == arriv_station)]

        delay_depar = df_depart["Number of trains delayed at departure"].sum()
        delay_arriv = df_arriv["Number of trains delayed at arrival"].sum()
        cancel_depar = df_depart["Number of cancelled trains"].sum()
        cancel_arriv = df_arriv["Number of cancelled trains"].sum()

        delayed = [delay_depar, delay_arriv]
        cancelled = [cancel_depar, cancel_arriv]

        st.markdown(
            "<center>Main cause of delay according to the station</center>",
            unsafe_allow_html=True,
        )
        col1, col2 = st.columns(2)

        with col1:
            fig, ax = plt.subplots()
            ax.bar(labels, delayed, color=COLOR)
            set_colors(fig, ax)
            ax.set_title("Number of late trains")
            ax.set_ylabel("Number of delays")
            st.pyplot(fig)
            pass_a_line(2)

            st.markdown("---")

            values = df_depart[pcts].mean()
            fig, ax = plt.subplots(figsize=(8, 6))
            ax.pie(values, autopct="%1.1f%%", colors=COLORS, textprops={"fontsize": 12})
            ax.legend(
                pcts_labels,
                title="Cause of delay",
                loc="center",
                bbox_to_anchor=(-0.4, 0.6),
            )
            ax.set_xlabel(depart_station, fontsize=15)
            set_colors(fig, ax)
            st.pyplot(fig)
        with col2:
            fig, ax = plt.subplots()
            ax.bar(labels, cancelled, color=COLOR)
            set_colors(fig, ax)
            ax.set_title("Number of cancelled trains")
            ax.set_ylabel("Number of cancelled")
            st.pyplot(fig)
            pass_a_line(2)

            st.markdown("---")

            values = df_arriv[pcts].mean()
            fig, ax = plt.subplots(figsize=(8, 6))
            ax.pie(values, autopct="%1.1f%%", colors=COLORS, textprops={"fontsize": 12})
            ax.legend(
                pcts_labels,
                title="Cause of delay",
                loc="center",
                bbox_to_anchor=(-0.4, 0.6),
            )
            ax.set_xlabel(arriv_station, fontsize=15)
            set_colors(fig, ax)
            st.pyplot(fig)
    except Exception as error:
        st.error(f"Error while comparing stations : {error}")


## [REAL-TIME PREDICTIONS]


def estimate_features_for_year(df, features, year):
    from sklearn.linear_model import LinearRegression

    feature_values = {}
    for feat in features:
        if feat == "Year":
            feature_values[feat] = year
            continue
        temp = df[["Year", feat]].dropna()
        if temp["Year"].nunique() > 1:
            reg = LinearRegression()
            reg.fit(temp[["Year"]], temp[feat])
            feature_values[feat] = reg.predict(
                pd.DataFrame([[year]], columns=["Year"])
            )[0]
        else:
            feature_values[feat] = temp[feat].mean()
    return pd.DataFrame([feature_values])[features]


def real_time_prediction():
    st.title("Real-time Prediction")
    st.markdown("Predict the average arrival delay for the selected journey.")

    model_choice = st.selectbox(
        "Choose the AI model to use:",
        [
            "RandomForest",
            "GradientBoosting",
        ],
    )

    try:
        if model_choice == "RandomForest":
            model = joblib.load("models/rfr_model.joblib")
        elif model_choice == "GradientBoosting":
            model = joblib.load("models/gb_model.joblib")
        else:
            st.error("Unknown model.")
            return
        features = joblib.load("models/features.joblib")
    except Exception as error:
        st.error(f"Error loading the model : {error}")
        return

    try:
        for future_year in [2025, 2026]:
            input_df_future = estimate_features_for_year(df, features, future_year)
            pred_log_future = model.predict(input_df_future)[0]
            pred_delay_future = np.expm1(pred_log_future)
            minutes = int(pred_delay_future)
            secondes = int((pred_delay_future - minutes) * 60)
            if secondes < 10:
                secondes = f"0{secondes}"
            st.info(
                f"Estimation du retard moyen à l'arrivée pour {future_year} : **{minutes}.{secondes} minutes**"
            )
    except ValueError:
        st.info("Nos prédictions")


## [PAGES]


def journey_info():
    st.title("Journey Informations")
    if depart_station == arriv_station or df_stations.empty:
        st.subheader("no route matches")
        return

    pass_a_line(2)
    st.subheader("Information about the selected journey")
    pass_a_line(1)

    surround(display_infos)


def delay_distribution():
    st.title("Delay Distribution")
    pass_a_line(2)
    col1, col2 = st.columns(2)

    with col1:
        st.subheader("Average number of late trains by delays")
        surround(trains_by_delays)
        pass_a_line(1)
        st.subheader("Average delays per station")
        surround(avg_delays_all_stations_15min)
        pass_a_line(1)
        st.subheader("Correlations between delay factors")
        surround(heatmap_correlation)
    with col2:
        st.subheader(
            "Number of delayed and cancelled trains by route (National/International)"
        )
        surround(delays_of_route)
        pass_a_line(1)
        st.subheader("Number of late trains by cause")
        surround(trains_by_pct)


def station_level_analysis():
    st.title("Station-Level Analysis")
    pass_a_line(2)

    st.subheader("Information on delays and cancellations along the route")
    pass_a_line(1)
    surround(info_along_the_route)
    pass_a_line(2)

    st.subheader(
        f"Comparisons of delays and cancellations between {depart_station} and {arriv_station}"
    )
    pass_a_line(1)
    comp_between_stations()


tabs = st.tabs(
    [
        "Journey information",
        "Delay distribution",
        "Station-level analysis",
        "Real-time predictions",
    ]
)

with tabs[0]:
    journey_info()
with tabs[1]:
    delay_distribution()
with tabs[2]:
    station_level_analysis()
with tabs[3]:
    real_time_prediction()
