from policies import random_policy, heuristic_policy, official_heuristic_policy
from executions import exec_policy, record_exec_policy

def execution_type():
    return input(f"\nType of execution for {name}:\n[0]: Normal\n[1]: Record\n\n=> ")

def episodes_to_record():
    ep = input(f"Episodes to record :\n[0]: First\n[1]: Last\n[2]: All\n\n=> ")
    ep_to_record = "all"
    if ep == "0":
        ep_to_record = "first"
    elif ep == "1":
        ep_to_record = "last"

    return ep_to_record




if __name__ == '__main__':

    policies = [("random", random_policy), ("heuristic", heuristic_policy), ("official_heuristic", official_heuristic_policy)]

    for name, func in list(policies):
        t = execution_type()
        if t == "1":
            ep_to_record = episodes_to_record()
            record_exec_policy(func, name, n_episodes=20, only=ep_to_record)
        else:
            exec_policy(func, name, 200)