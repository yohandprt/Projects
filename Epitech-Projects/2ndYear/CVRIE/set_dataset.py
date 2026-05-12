import os
import pandas as pd
from random import randint



def BrainTumorYolov():
    label_path = "BrainTumorYolov/BrainTumorYolov8/train/labels/"

    filenames = os.listdir(label_path)

    NB_INFOS = 28
    EXTENSION_IMG = ".jpg"
    EXTENSION_LABEL = ".txt"
    EMPTY_VALUES = 0

    columns = ["id", "image_name", "type"]
    for i in range(1, int(NB_INFOS / 2) + 1):
        columns.append(f"x{i}")
        columns.append(f"y{i}")

    df = pd.DataFrame(columns=columns)


    def set_type(int_val):
        if str(int_val) == "0":
            return "glioma"
        elif str(int_val) == "1":
            return "meningioma"
        elif str(int_val) == "2":
            return "pituitary"
        else:
            return str(int_val)


    for i, filename in enumerate(filenames):
        f = open(label_path + filename, "r")
        content = f.read()
        values = content.split(sep=' ')
        values[0] = set_type(values[0])
        line = [i] + [filename.replace(EXTENSION_LABEL, EXTENSION_IMG)] + values
        if (len(line) < 31):
            for i in range(31 - len(line)):
                line.append(EMPTY_VALUES)
        elif (len(line) > 31):
            line = line[:31]
        df.loc[len(df)] = line


    df.to_csv("datasets/supervised/Yolov/brain_tumor_dataset.csv", index=False)


def BrainTumorMRI_SeparetedTypes():
    trainingPath = "BrainTumorMRI/Training/"
    testingPath = "BrainTumorMRI/Testing/"

    types = os.listdir(trainingPath)

    nbTrainImages = len(os.listdir(trainingPath + "/" + types[0]))
    nbTestImages = len(os.listdir(testingPath + "/" + types[0]))

    df_train = pd.DataFrame(columns=["id"] + types)
    df_test = pd.DataFrame(columns=["id"] + types)

    # [TRAIN]

    images = {}

    for type in types:
        filenames = os.listdir(trainingPath + "/" + type)
        filenames.sort()
        images[type] = filenames
    
    for i in range(nbTrainImages):
        line = [i]

        for type in types:
            line += [type + "/" + images[type][i]]
        df_train.loc[len(df_train)] = line

    # [TEST]
    
    images = {}

    for type in types:
        filenames = os.listdir(testingPath + "/" + type)
        filenames.sort()
        images[type] = filenames
    
    for i in range(nbTestImages):
        line = [i]

        for type in types:
            line += [type + "/" + images[type][i]]
        df_test.loc[len(df_test)] = line

    df_train.to_csv("datasets/supervised/MRI/separated_types_train.csv", index=False)
    df_test.to_csv("datasets/supervised/MRI/separated_types_test.csv", index=False)

def BrainTumorMRI_MixedTypes():
    trainingPath = "BrainTumorMRI/Training/"
    testingPath = "BrainTumorMRI/Testing/"

    types = os.listdir(trainingPath)

    nbTrainImages = len(os.listdir(trainingPath + "/" + types[0]))
    nbTestImages = len(os.listdir(testingPath + "/" + types[0]))

    columns = ["id", "image_name", "type"]

    df_train = pd.DataFrame(columns=columns)
    df_test = pd.DataFrame(columns=columns)

    # [TRAIN]

    files = [os.listdir(trainingPath + "/" + type) for type in types]

    for i in range(nbTrainImages * len(types)):
        r_type = randint(0, len(types) - 1)

        try:
            line = [i] + [types[r_type] + "/" + files[r_type][0]] + [types[r_type]]

            df_train.loc[len(df_train)] = line

            files[r_type].pop(0)
        except:
            continue
    
    # [TEST]

    files = [os.listdir(testingPath + "/" + type) for type in types]

    for i in range(nbTestImages * len(types)):
        r_type = randint(0, len(types) - 1)

        try:
            line = [i] + [types[r_type] + "/" + files[r_type][0]] + [types[r_type]]

            df_test.loc[len(df_test)] = line

            files[r_type].pop(0)
        except:
            continue

    df_train.to_csv("datasets/supervised/MRI/mixed_types_train.csv", index=False)
    df_test.to_csv("datasets/supervised/MRI/mixed_types_test.csv", index=False)
    



BrainTumorMRI_SeparetedTypes()
BrainTumorMRI_MixedTypes()