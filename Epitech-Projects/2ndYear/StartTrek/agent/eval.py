import gymnasium as gym
from gymnasium.wrappers import RecordVideo
import torch
import numpy as np
from typing import Literal
import csv
import os

from model import Model

class EvalModel:
    """Classe d'evaluation d'un modèle DQN pour l'environnement LunarLander-v3 de la librairie Gymnasium

    Args:
        model_path (str): chemin vers la sauvegarde du modèle
    """
    def __init__(self, model_path: str):
        self.model_path = model_path
        self.dir_name = self._get_dir_from_path()
        self.model = Model()
        self.model.load_state_dict(torch.load(self.model_path, weights_only=True))
        self.model.eval()

        self.rewards = []
        self.global_steps = 0
    
    def _get_dir_from_path(self):
        if '/' not in self.model_path:
            return "."

        idx = self.model_path.rfind("/")
        return self.model_path[:idx + 1]

    def _make_env(self):
        self.env = gym.make("LunarLander-v3", render_mode=("rgb_array" if self.render_mode == "record" else ("human" if self.render_mode != None else None)))

        if (self.render_mode == "record"):
            episode_trigger = lambda e: (e == 0 if self.only == "first" else (e == self.n_gen - 1 if self.only == "last" else True))
            self.env = RecordVideo(
                self.env,
                video_folder=self.dir_name + "eval/records",
                episode_trigger=episode_trigger
            )
    
    def _save_data(self):
        row = {
            "episode": self.episode,
            "global_step": self.global_steps,
            "mean_100": np.mean(self.rewards).round(2),
            "total_reward": np.round(self.total_reward, 2),
            "steps": self.steps
        }

        data_path = self.dir_name + "eval/" + "data.csv"

        file_exists = os.path.isfile(data_path)
        file_is_empty = not file_exists or os.path.getsize(data_path) == 0

        with open(data_path, "a", newline="") as fd:
            writer = csv.DictWriter(fd, fieldnames=list(row.keys()))

            if file_is_empty:
                writer.writeheader()

            writer.writerow(row)

    def _eval_once(self):
        obs, _ = self.env.reset()
        finish = False

        self.total_reward = 0.0
        self.steps = 0

        while not finish:

            action = torch.argmax(self.model(torch.tensor(obs))).item()

            next_obs, reward, terminated, truncated, _ = self.env.step(action)

            self.total_reward += reward
            self.steps += 1
            self.global_steps += 1

            finish = (terminated or truncated)

            obs = next_obs
    
        self.rewards.append(self.total_reward)

        if self.log:
            print(f"EPISODE: {self.episode} | TOTAL REWARDS: {self.total_reward}")

    def eval(self, n_gen: int = 100, render_mode: Literal["record", "human"] | None = None, only: Literal["first", "last", "all"] = "all", log: bool = False):
        self.n_gen = n_gen
        self.render_mode = render_mode
        self.only = only
        self.log = log
        self._make_env()

        for episode in range(n_gen):
            self.episode = episode

            self._eval_once()

            if self.log:
                self._save_data()

    def mean(self):
        self.m = np.mean(self.rewards)
        if self.log:
            print(f"MEAN SCORE OVER {self.n_gen} GENERATIONS: {self.m}")
        return self.m




evaluator = EvalModel("models/model_best/model_best.pth")

evaluator.eval(100, render_mode="record", log=True)
evaluator.mean()
