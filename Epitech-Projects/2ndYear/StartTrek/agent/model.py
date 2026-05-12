import torch
import torch.nn as nn


class Model(nn.Module):
    def __init__(self):
        super().__init__()
        self.m1 = nn.Linear(8, 128)
        self.m2 = nn.Linear(128, 256)
        self.m3 = nn.Linear(256, 512)
        self.m4 = nn.Linear(512, 4)

    def forward(self, x):
        x = torch.relu(self.m1(x))
        x = torch.relu(self.m2(x))
        x = torch.relu(self.m3(x))
        x = self.m4(x)
        return x
