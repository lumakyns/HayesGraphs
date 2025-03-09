import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

titles = [
    "n10",
    "n100",
    "n1000",
    "n10000",
    "s1"
]

if (__name__ == "__main__"):

    for title in titles:
        degrees = pd.read_csv(f"data/{title}_degrees.csv").to_numpy()

        fig, ax = plt.subplots(1, 3, figsize=(12, 4))
        
        # Print degree graphs
        colors      = ["red", "orange", "blue"]
        graphTitles = ["In-degree distribution", "Out-degree distribution", "Undirected-degree distribution"]
        for id in range(3):
            ax[id].set_title(graphTitles[id])
            ax[id].bar(range(degrees.shape[0]), degrees[:, id].T, color=colors[id])

        plt.tight_layout()
        plt.savefig(f"imageGraphs/{title}_graph.png")