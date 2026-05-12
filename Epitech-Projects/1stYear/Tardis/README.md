# TARDIS – Train Delay Prediction

## Objective

Develop a regression model capable of predicting the **average delay** of a set of trains based on multiple factors, such as:
- the number of scheduled, canceled, or delayed trains,  
- the causes of delays (infrastructure, rolling stock, etc.)

The project is complemented by a **Streamlit interface**, allowing users to simulate and view information related to their train journey.

---

## Installation

1. Install the required libraries:
    ```bash
    pip install -r requirements.txt
    ```
2. Launch `tardis_eda.ipynb`:
    - Prepare a `dataset.csv` file with raw train data.
    - Run the `tardis_eda.ipynb` notebook in your Python environment.
    - It will export a cleaned dataset named `cleaned_dataset.csv`.

3. Launch the web app:
    ```bash
    streamlit run tardis_dashboard.py
    ```

## Expected `dataset.csv` format

The `dataset.csv` file must contain exactly the following columns (all mandatory):

- `Date`
- `Service`
- `Departure station`
- `Arrival station`
- `Average journey time`
- `Number of scheduled trains`
- `Number of cancelled trains`
- `Cancellation comments`
- `Number of trains delayed at departure`
- `Average delay of late trains at departure`
- `Average delay of all trains at departure`
- `Departure delay comments`
- `Number of trains delayed at arrival`
- `Average delay of late trains at arrival`
- `Average delay of all trains at arrival`
- `Arrival delay comments`
- `Number of trains delayed > 15min`
- `Average delay of trains > 15min (if competing with flights)`
- `Number of trains delayed > 30min`
- `Number of trains delayed > 60min`
- `Pct delay due to external causes`
- `Pct delay due to infrastructure`
- `Pct delay due to traffic management`
- `Pct delay due to rolling stock`
- `Pct delay due to station management and equipment reuse`
- `Pct delay due to passenger handling (crowding, disabled persons, connections)`

## Cleanning & Visualization

- Cleaning of outliers and missing values
- Visualizations: histograms, correlation heatmap

## Why?
This project was created as part of the Epitech curriculum to introduce to data analyse and visualization


## Author
- [@ThomasVillot](https://github.com/ThomasVillot)
- [@yohandprt](https://github.com/yohandprt)
- [@BaptisteVanBunderen](https://github.com/BaptisteVanBunderen)
