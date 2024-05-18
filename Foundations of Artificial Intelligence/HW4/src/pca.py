import numpy as np

# Discuss with b08502041

"""
Implementation of Principal Component Analysis.
"""
class PCA:
    def __init__(self, n_components: int) -> None:
        self.n_components = n_components
        self.mean = None
        self.components = None

    def fit(self, X: np.ndarray) -> None:
        #TODO: 10%
        # Hint: Use existing method to calculate covariance matrix and its eigenvalues and eigenvectors
        
        self.mean = np.mean(X, axis = 0)
        X = X - self.mean
        cov = np.cov(X.T)

        eig_vals, eig_vecs = np.linalg.eigh(cov)
        eig_pairs = [(np.abs(eig_vals[i]), eig_vecs[:, i]) for i in range(len(eig_vals))]
        eig_pairs.sort(key = lambda x: x[0], reverse = True)
        self.components = np.array([eig_pairs[i][1] for i in range(self.n_components)])

    def transform(self, X: np.ndarray) -> np.ndarray:
        #TODO: 2%
        # Hint: Use the calculated principal components to project the data onto a lower dimensional space
        
        X = X - self.mean
        return np.dot(X, self.components.T)

    def reconstruct(self, X):
        #TODO: 2%
        # Hint: Use the calculated principal components to reconstruct the data back to its original space

        X = self.transform(X)
        return np.dot(X, self.components) + self.mean