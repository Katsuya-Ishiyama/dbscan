# -*- coding: utf-8 -*-

import pandas as pd
from sklearn.datasets.samples_generator import make_blobs

centers = [[1, 1], [-1, -1], [1, -1]]

X, labels = make_blobs(
    n_samples=750,
    centers=centers,
    cluster_std=0.4,
    random_state=0
)
sample_dataset = pd.DataFrame(X).set_index(labels)
sample_dataset.index.name = 'label'
sample_dataset.columns = ['x', 'y']
sample_dataset.reset_index(inplace=True)
sample_dataset.to_csv('~/dbscan/data/sample_dataset.csv', index=False)

