import os
import gymnasium as gym
import csv
import numpy as np
from gymnasium.wrappers import RecordVideo
from typing import Literal
import time

"""
0: do nothing
1: fire left orientation engine
2: fire main engine
3: fire right orientation engine
"""

def random_policy(obs):
    return np.random.randint(0, 4)

def heuristic_policy(obs):
    x, y, v_x, v_y, theta, theta_dot, left_leg_contact, right_leg_contact = obs

    if left_leg_contact and right_leg_contact: # si la fusée est posée -> ne rien faire
        return 0

    if v_y > 0: # si la fusée monte -> ne rien faire
        return 0

    if y < 0.6 and v_y < -0.2: # si la fusée est proche du sol et descend trop vite -> gaz au milieu
        return 2

    if theta > 0.2: # si la fusée est trop penché vers la droite -> gaz à droite
        return 3
    elif theta < -0.2: # si la fusée est trop penché vers la gauche -> gaz à gauche
        return 1

    if x > 0.2 and not v_x < 0: # si la fusée est trop à droite des drapeaux et qu'elle ne va pas vers la gauche -> gaz à droite
        return 3
    elif x < -0.2 and not v_x > 0: # si la fusée est trop à gauche des drapeaux et qu'elle ne va pas vers la droite -> gaz à gauche
        return 1

    return 0

def official_heuristic_policy(obs):
    x, y, v_x, v_y, theta, theta_dot, left_leg_contact, right_leg_contact = obs

    angle_targ = x * 0.5 + v_x * 1.0  # angle should point towards center
    if angle_targ > 0.4:
        angle_targ = 0.4  # more than 0.4 radians (22 degrees) is bad
    if angle_targ < -0.4:
        angle_targ = -0.4
    hover_targ = 0.55 * np.abs(x)  # target y should be proportional to horizontal offset

    angle_todo = (angle_targ - theta) * 0.5 - (theta_dot) * 1.0
    hover_todo = (hover_targ - y) * 0.5 - (v_y) * 0.5

    if left_leg_contact or right_leg_contact:  # legs have contact
        angle_todo = 0
        hover_todo = (-(v_y) * 0.5)  # override to reduce fall speed, that's all we need after contact

    a = 0
    if hover_todo > np.abs(angle_todo) and hover_todo > 0.05:
        a = 2
    elif angle_todo < -0.05:
        a = 3
    elif angle_todo > +0.05:
        a = 1

    return a