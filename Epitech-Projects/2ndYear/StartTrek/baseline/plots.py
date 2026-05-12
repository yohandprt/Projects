import pandas as pd
import matplotlib.pyplot as plt
import os

df = pd.read_csv("results/logs/all_episodes.csv")

os.makedirs("results/plots", exist_ok=True)

for name, group in df.groupby("name"):
    plt.plot(group["episode"], group["total_reward"], label=name)

plt.xlabel("Episodes")
plt.ylabel("Nombre total de récompenses")
plt.title("Comparaison des récompenses par episodes entre les policies")

plt.legend()
plt.savefig("results/plots/rewards.png")


plt.figure()

for name, group in df.groupby("name"):
    sorted_group = group.sort_values("episode")
    mean = sorted_group["total_reward"].rolling(50).mean()
    plt.plot(sorted_group["episode"], mean, label=name)

plt.xlabel("Episodes")
plt.ylabel("Nombre total de récompenses")
plt.title("Différence des courbe d'apprentissage entre les policies")
plt.legend()
plt.savefig("results/plots/leaning_curve.png")


plt.figure()
df.groupby("name")["total_reward"].mean().sort_values().plot(kind="bar")

plt.xlabel("Policy")
plt.ylabel("Récompense moyenne")
plt.title("Comparaison des récompense moyenne entre les policies")
plt.savefig("results/plots/mean_rewards.png")


plt.figure()
df.groupby("name")["length"].mean().sort_values().plot(kind="bar")

plt.xlabel("Policy")
plt.ylabel("Nombre moyen d'étape par épisode")
plt.title("Comparaison des longueur d'épisodes entre les policies")
plt.savefig("results/plots/length.png")


plt.figure()
success_rate = (df["reason"] == "sleep").groupby(df["name"]).mean().sort_values().mul(100)

success_rate.plot(kind="bar")

plt.xlabel("Policy")
plt.ylabel("Taut de succès (en %)")
plt.title("Comparaison des taux de succès entre les policies")
plt.savefig("results/plots/success_rate.png")


counts = df.groupby(["name", "reason"]).size().unstack(fill_value=0)

counts.plot(kind="bar", stacked=True)

plt.xlabel("Policy")
plt.ylabel("Nombre d'épisodes")
plt.title("Comparaison des causes de fin entre les policies")
plt.legend(title="Causes")
plt.savefig("results/plots/causes_of_end.png")