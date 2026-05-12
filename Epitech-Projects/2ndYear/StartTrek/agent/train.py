import gymnasium as gym
from gymnasium.wrappers import RecordVideo
import torch
import torch.nn as nn
import numpy as np
import random
from collections import deque
from typing import Literal
import matplotlib.pyplot as plt
import os
import csv
import json

from model import Model


DEFAULT_LR = 0.0005
DEFAULT_GAMMA = 0.99
DEFAULT_EPSILON = 1.0
DEFAULT_EPSILON_MIN = 0.01
DEFAULT_EPSILON_TO_REMOVE = 0.98
DEFAULT_PORTION_EP_TO_RM_EPS = 0.8

class TrainModel:
    """Classe d'entraînement d'un modèle DQN pour l'environnement LunarLander-v3 de la librairie Gymnasium

    Args:
        dir_name (str): le dossier vers lequel les données d'entraînement du modèle seront enregistrée | Valeur Defaut: **\"models/model\"**
        lr (float): taux d'apprentissage | Valeur Defaut: **0.0001**
        gamma (float): importance des conséquences des choix du modèle | Valeur Defaut: **0.99**
        epsilon (float): valeur de départ de l'epsilon | Valeur Defaut: **1.0**
        epsilon_min (float): valeur minimale que l'epsilon peut atteindre | Valeur Defaut: **0.01**
        epsilon_to_remove (float): défini la vitesse de décroissence de l'epsilon | Valeur Defaut: **0.98**
        n_gen_to_rm_eps (int): decroitre l'epsilon de `epsilon` jusqu'à `epsilon_min` en `n_gen_to_rm_eps` generations. -1 si `portion_gen_to_rm_eps` | Valeur Defaut: **None**
        portion_gen_to_rm_eps (float): [*need `n_gen_to_rm_eps`*] portion du nombre de generations pour laquelle l'epsilon decroie de `epsilon` jusqu'à `epsilon_min` | Valeur Defaut: **0.8**
        render_mode (Literal['record', 'human'] | None): 'record' pour enregistrer les generations, 'human' pour voir en temps réel les generations | Valeur Defaut: **None**
        only (Literal["first", "last", "all"]): [*need `render_mode = 'record'`*] enregistrer seulement la premiere/derniere generation ou tout | Valeur Defaut: **\"all\"**
    """
    def __init__(self, dir_name: str = "models/model", lr: float = DEFAULT_LR, gamma: float = DEFAULT_GAMMA,
                 epsilon: float = DEFAULT_EPSILON, epsilon_min: float = DEFAULT_EPSILON_MIN, epsilon_to_remove: float = DEFAULT_EPSILON_TO_REMOVE, n_gen_to_rm_eps: int | None = None, portion_gen_to_rm_eps: float | None = None,
                 render_mode: Literal["record", "human"] | None = None, only: Literal["first", "last", "all"] = "all"):
        self.last_steps = deque([], maxlen=10000)
        self.nb_steps_learn = 128
        self.cpt = 0

        self.dir_name = dir_name if dir_name[-1] == '/' else dir_name + "/"
        self.name = self._get_name_with_path(self.dir_name)

        self.learning_rate = lr
        self.gamma = gamma
        self.epsilon = epsilon
        self.epsilon_start = epsilon
        self.epsilon_min = epsilon_min
        self.epsilon_to_remove = epsilon_to_remove
        self.n_gen_to_rm_eps = n_gen_to_rm_eps
        self.portion_gen_to_rm_eps = portion_gen_to_rm_eps

        self.model = Model()
        self.target_model = Model()
        self.target_model.load_state_dict(self.model.state_dict())

        self.loss_fn = nn.MSELoss()
        self.optimizer = torch.optim.Adam(self.model.parameters(), lr=self.learning_rate)

        self.render_mode = render_mode
        self.video_folder = self.dir_name + "records"
        self.only = only

        self.global_steps = 0

        # PLOTS
        self.episode_returns = deque([], maxlen=100)
        self.episode_lengths = []
        self.losses = []
        self.epsilons = []
        self.termination_reasons = []

    def _get_name_with_path(self, dir_name: str):
        dir_name = dir_name.strip()
        name = dir_name
        if ('/' in dir_name):
            idx = dir_name.rfind("/")
            if idx == len(dir_name) - 1:
                return self._get_name_with_path(dir_name[:-1])
            else:
                name = dir_name[idx + 1:]
        if (name == "" or name == "."):
            name = "model"
        return name

    def _make_env(self):
        self.env = gym.make("LunarLander-v3", render_mode=("rgb_array" if self.render_mode == "record" else ("human" if self.render_mode != None else None)))

        if (self.render_mode == "record"):
            episode_trigger = lambda e: (e == 0 if self.only == "first" else (e == self.n_gen - 1 if self.only == "last" else True))
            self.env = RecordVideo(
                self.env,
                video_folder=self.video_folder,
                episode_trigger=episode_trigger
            )

    def _choose_action(self):
        if random.random() < self.epsilon:
            self.action = random.randint(0, 3)
        else:
            with torch.no_grad():
                self.action = torch.argmax(self.model(torch.tensor(self.obs))).item()

    def _can_optimize(self):
        return len(self.last_steps) >= self.nb_steps_learn

    def _should_optimize(self):
        return self._can_optimize() and self.cpt % 4 == 0

    def _optimize(self):
        self.steps_to_learn = random.sample(self.last_steps, self.nb_steps_learn)
        all_obs, all_actions, all_rewards, all_next_obs, all_terminated = zip(*self.steps_to_learn)

        all_obs = torch.tensor(np.array(all_obs), dtype=torch.float32)
        all_actions = torch.tensor(all_actions, dtype=torch.long)
        all_rewards = torch.tensor(all_rewards, dtype=torch.float32)
        all_next_obs = torch.tensor(np.array(all_next_obs), dtype=torch.float32)
        all_terminated = torch.tensor(all_terminated, dtype=torch.float32)

        with torch.no_grad():
            future_consequences = all_rewards + self.gamma * torch.max(self.target_model(all_next_obs), dim=1).values * (1 - all_terminated)

        rate_confident = self.model(all_obs)[range(self.nb_steps_learn), all_actions]

        loss = self.loss_fn(rate_confident, future_consequences)

        self.losses.append(loss.item())

        self.optimizer.zero_grad()
        loss.backward()
        # torch.nn.utils.clip_grad_norm_(self.model.parameters(), 1.0)
        self.optimizer.step()

    def _should_rebase_target(self):
        return self.cpt % 1000 == 0

    def _rebase_target(self):
        self.target_model.load_state_dict(self.model.state_dict())

    def _decrease_epsilon(self, gen: int):
        if self.n_gen_to_rm_eps is not None or self.portion_gen_to_rm_eps is not None:
            if self.portion_gen_to_rm_eps is not None:
                self.n_gen_to_rm_eps = int(self.portion_gen_to_rm_eps * self.n_gen)
            fraction = min(gen / self.n_gen_to_rm_eps, 1.0)
            self.epsilon = self.epsilon_start - fraction * (self.epsilon_start - self.epsilon_min)
        else:
            self.epsilon = max(self.epsilon_min, self.epsilon * self.epsilon_to_remove)

    def _train_gen(self):

        self.total_reward = 0
        self.steps = 0

        finish = False
        while not finish:
            self._choose_action()

            next_obs, self.reward, self.terminated, self.truncated, _ = self.env.step(self.action)

            self.total_reward += self.reward
            self.steps += 1
            self.global_steps += 1

            finish = (self.terminated or self.truncated)

            self.last_steps.append((self.obs, self.action, self.reward, next_obs, self.terminated))
            self.cpt += 1

            self.obs = next_obs

            if self._should_optimize():
                self._optimize()
            
            if self._should_rebase_target():
                self._rebase_target()

        self.termination_reason = self._get_termination_reason()
        self.episode_returns.append(self.total_reward)
        self.episode_lengths.append(self.steps)
        self.epsilons.append(self.epsilon)

    def train(self, n_gen: int = 200, render_mode: Literal["record", "human"] | None = None, video_folder: str | None = None, only: Literal["first", "last", "all"] | None = None):
        self.n_gen = n_gen
        self.render_mode = render_mode if render_mode != None else self.render_mode
        self.video_folder = video_folder if video_folder != None else self.video_folder
        self.only = only if only != None else self.only

        self._make_env()

        for gen in range(n_gen):
            print(f"GEN: {gen}/{n_gen - 1}")
            self.episode = gen

            self.obs, _ = self.env.reset()

            self._train_gen()
            self._decrease_epsilon(gen)

            self._save_data()

        self.env.close()
    
    def _get_termination_reason(self):
        if self.truncated:
            return "timeout"

        x, _, _, _, _, _, _, _ = self.obs

        if self.terminated:
            if self.reward < 0 and (x >= 1 or x <= -1):
                return "out_of_view"
            elif self.reward < 0:
                return "crash"
            else:
                return "landed"

        return "in_progress"

    def _save_data(self):
        row = {
            "episode": self.episode,
            "total_reward": np.round(self.total_reward, 2),
            "steps": self.steps,
            "global_step": self.global_steps,
            "mean_100": np.mean(self.episode_returns).round(2),
            "termination_reason": self.termination_reason
        }

        data_path = self.dir_name + "data.csv"

        file_exists = os.path.isfile(data_path)
        file_is_empty = not file_exists or os.path.getsize(data_path) == 0

        with open(data_path, "a", newline="") as fd:
            writer = csv.DictWriter(fd, fieldnames=list(row.keys()))

            if file_is_empty:
                writer.writeheader()

            writer.writerow(row)

    def plot(self):
        plt.figure()
        plt.plot(self.episode_returns)
        plt.title("Total des recompenses obtenues par generations")
        plt.xlabel("Nombre de generations")
        plt.ylabel("Nb total des recompenses")
        plt.savefig(self.dir_name + "total_rewards.png")

        plt.figure()
        plt.plot(self.losses)
        plt.title("Ajustement du modèle au court des episodes")
        plt.xlabel("Nombre d'episodes")
        plt.ylabel("Ecart entre la \"bonne reponse\" et le choix du modèle")
        plt.savefig(self.dir_name + "losses.png")

        plt.figure()
        plt.plot(self.epsilons)
        plt.title("Epsilon au court des generations")
        plt.xlabel("Nombre de generations")
        plt.ylabel("Epsilon")
        plt.savefig(self.dir_name + "epsilons.png")
    
    def _save_hyperparams(self):
        data = {
            "learning_rate": self.learning_rate,
            "gamma": self.gamma,
            "epsilon_start": self.epsilon_start,
            "epsilon_min": self.epsilon_min,
            "epsilon_decay": self.epsilon_to_remove,
            "n_gen_to_eps_decay": self.n_gen_to_rm_eps,
            "portion_ep_to_eps_decay": self.portion_gen_to_rm_eps,
            "batch_size": self.nb_steps_learn,
            "n_gen": self.n_gen,
        }

        with open(self.dir_name + "hyperparams.json", "w") as fd:
            json.dump(data, fd, indent=4)

    def save_model(self):
        os.makedirs(self.dir_name, exist_ok=True)
        torch.save(self.model.state_dict(), self.dir_name + self.name + ".pth")
        self._save_hyperparams()




trainer = TrainModel("models/model")

trainer.train(200)
trainer.save_model()
trainer.plot()
