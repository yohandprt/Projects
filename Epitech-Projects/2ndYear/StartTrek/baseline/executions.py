import gymnasium as gym
from gymnasium.wrappers import RecordVideo
from typing import Literal
import time

from logger import log

def record_exec_policy(policy, policy_name, *, video_folder: str = None, n_episodes: int = 20, only: Literal["first", "last", "all"] = 'all'):
    env = gym.make("LunarLander-v3", render_mode="rgb_array")

    if video_folder is None:
        video_folder = f"results/videos/{policy_name}"

    video_folder += "" if video_folder.endswith("/") else "/"
    video_folder += f"exec_{int(time.time())}"

    episode_trigger = lambda e: (e == 0 if only == "first" else (e == n_episodes - 1 if only == "last" else True))

    env = RecordVideo(
        env,
        video_folder=video_folder,
        episode_trigger=episode_trigger
    )

    exec_policy(policy, policy_name, n_episodes, env)

    env.close()

    print(f"VIDEOS SAVED IN: {video_folder}")

def exec_policy(policy, policy_name, n_episodes, env = None):

    if env is None:
        env = gym.make("LunarLander-v3")

    print(f"\nEXECUTE POLICY: {policy_name} | TYPE: {"execution" if env.render_mode != "rgb_array" else "record"}")

    log_file_path = ""

    seed = 8

    for gen in range(n_episodes):
        obs, _ = env.reset(seed=seed + gen)
        total_reward = 0
        length = 0

        reward = 0
        terminated = False
        truncated = False

        while True:
            action = policy(obs)
            obs, reward, terminated, truncated, _ = env.step(action)
            total_reward += reward
            length += 1

            if terminated or truncated:
                break

        log_file_path = log(obs, policy_name, gen, length, total_reward, reward, terminated, truncated)

    env.close()

    print(f"LOGS WRITTEN IN: {log_file_path}")