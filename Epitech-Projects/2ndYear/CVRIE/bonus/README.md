# Bonus Dashboard

Dashboard Streamlit pour explorer les datasets supervises MRI et YOLO du projet.

## Contenu

- `dashboard.py`: application Streamlit
- `requirements.txt`: dependances Python pour le dashboard

## Installation

Depuis la racine du projet:

```bash
python -m venv .venv
source .venv/bin/activate
pip install -r bonus/requirements.txt
```

## Lancement

Toujours depuis la racine du projet:

```bash
streamlit run bonus/dashboard.py
```

## Donnees attendues

Le dashboard lit directement ces fichiers:

- `datasets/supervised/MRI/mixed_types_train.csv`
- `datasets/supervised/MRI/mixed_types_test.csv`
- `datasets/supervised/MRI/separated_types_train.csv`
- `datasets/supervised/MRI/separated_types_test.csv`
- `datasets/supervised/Yolov/brain_tumor_dataset.csv`

Si un fichier est absent ou vide, un message d'alerte s'affiche.
