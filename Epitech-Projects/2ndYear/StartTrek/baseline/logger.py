import os
import csv
import time

def get_end_reason(obs, reward, terminated, truncated):
    if truncated:
        return "timeout"

    x, _, _, _, _, _, _, _ = obs

    if terminated:
        if reward < 0 and (x >= 1 or x <= -1):
            return "out_of_view"
        elif reward < 0:
            return "crash"
        else:
            return "landed"

    return "in_progress"

def log(obs, policy_name, episode, length, total_reward, reward, terminated, truncated):
    reason = get_end_reason(obs, reward, terminated, truncated)

    row = {
        "name": policy_name,
        "episode": episode,
        "length": length,
        "total_reward": round(total_reward, 3),
        "reason": reason,
        "terminated": terminated,
    }

    os.makedirs(f"results/logs/{policy_name}", exist_ok=True)

    file_path = f"results/logs/{policy_name}/episodes_{int(time.time())}.csv"
    file_exists = os.path.isfile(file_path)
    file_is_empty = not file_exists or os.path.getsize(file_path) == 0

    with open(file_path, "a", newline="") as fd:
        writer = csv.DictWriter(fd, fieldnames=list(row.keys()))

        if file_is_empty:
            writer.writeheader()

        writer.writerow(row)

    generic_policy_file_path = f"results/logs/{policy_name}/all_episodes.csv"
    file_exists = os.path.isfile(generic_policy_file_path)
    file_is_empty = not file_exists or os.path.getsize(generic_policy_file_path) == 0

    with open(generic_policy_file_path, "a", newline="") as fd:
        writer = csv.DictWriter(fd, fieldnames=list(row.keys()))

        if file_is_empty:
            writer.writeheader()
        
        writer.writerow(row)

    generic_file_path = f"results/logs/all_episodes.csv"
    file_exists = os.path.isfile(generic_file_path)
    file_is_empty = not file_exists or os.path.getsize(generic_file_path) == 0

    with open(generic_file_path, "a", newline="") as fd:
        writer = csv.DictWriter(fd, fieldnames=list(row.keys()))

        if file_is_empty:
            writer.writeheader()
        
        writer.writerow(row)

    return file_path