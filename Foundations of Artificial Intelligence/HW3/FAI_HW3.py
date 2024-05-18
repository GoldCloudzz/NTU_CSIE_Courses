from collections import Counter

import numpy as np
import pandas as pd

# set random seed
np.random.seed(850802)

# Discuss with b08502041

"""
reference: 
https://www.cs.toronto.edu/~frossard/post/linear_regression/
https://towardsdatascience.com/linear-regression-with-python-and-numpy-25d0e1dd220d?gi=4153ff1e345f
https://gist.github.com/golamSaroar/1a1ce33139cf77c37cd6bd123f0fa9cb
https://anderfernandez.com/en/blog/code-decision-tree-python-from-scratch/
"""

"""
Tips for debugging:
- Use `print` to check the shape of your data. Shape mismatch is a common error.
- Use `ipdb` to debug your code
    - `ipdb.set_trace()` to set breakpoints and check the values of your variables in interactive mode
    - `python -m ipdb -c continue hw3.py` to run the entire script in debug mode. Once the script is paused, you can use `n` to step through the code line by line.
"""


# 1. Load datasets
def load_data() -> tuple[pd.DataFrame, pd.DataFrame]:
    """
    DO NOT MODIFY THIS FUNCTION.
    """
    # Load iris dataset
    iris = pd.read_csv(
        "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data",
        header=None,
    )
    iris.columns = [
        "sepal_length",
        "sepal_width",
        "petal_length",
        "petal_width",
        "class",
    ]

    # Load Boston housing dataset
    boston = pd.read_csv(
        "https://raw.githubusercontent.com/selva86/datasets/master/BostonHousing.csv"
    )

    return iris, boston


# 2. Preprocessing functions
def train_test_split(
    df: pd.DataFrame, target: str, test_size: float = 0.3
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    # Shuffle and split dataset into train and test sets
    df = df.sample(frac=1, random_state=42).reset_index(drop=True)
    split_idx = int(len(df) * (1 - test_size))
    train = df.iloc[:split_idx]
    test = df.iloc[split_idx:]

    # Split target and features
    X_train = train.drop(target, axis=1).values
    y_train = train[target].values
    X_test = test.drop(target, axis=1).values
    y_test = test[target].values

    return X_train, X_test, y_train, y_test


def normalize(X: np.ndarray) -> np.ndarray:
    # Normalize features to [0, 1]
    # You can try other normalization methods, e.g., z-score, etc.
    # TODO: 1%
    # Hint: Calculate the min and max values for each feature (column).
    # Then, subtract the min value and divide by the range (max - min).

    X_max = np.max(X, axis = 0)
    X_min = np.min(X, axis = 0)
    return (X - X_min) / (X_max - X_min)


def encode_labels(y: np.ndarray) -> np.ndarray:
    """
    Encode labels to integers.
    """
    # TODO: 1%
    # Hint: Create a dictionary that maps unique labels to integers.
    # Then, use a list comprehension to replace the original labels with their
    # corresponding integer values.

    labels = np.unique(y)
    label_dict = {label: idx for idx, label in enumerate(labels)}

    return np.array([label_dict[label] for label in y])


# 3. Models
class LinearModel:
    def __init__(
        self, learning_rate=0.01, iterations=1000, model_type="linear"
    ) -> None:
        self.learning_rate = learning_rate
        self.iterations = iterations
        # You can try different learning rate and iterations
        self.model_type = model_type

        assert model_type in [
            "linear",
            "logistic",
        ], "model_type must be either 'linear' or 'logistic'"

    def fit(self, X: np.ndarray, y: np.ndarray) -> None:
        self.mean = np.mean(X, axis = 0)
        self.std = np.std(X, axis = 0)
        X = (X - self.mean) / self.std

        X = np.insert(X, 0, 1, axis = 1)
        n_classes = len(np.unique(y))
        n_features = X.shape[1]
    
        # TODO: 2%
        # Hint: Initialize the weights based on the model type (logistic or linear).
        # Then, update the weights using gradient descent within a loop for the
        # specified number of iterations.

        if self.model_type == "linear":
            self.weights = np.random.rand(n_features)

            for i in range(self.iterations):
                gradient = self._compute_gradients(X, y)
                self.weights -= self.learning_rate * gradient

        elif self.model_type == "logistic":
            self.weights = np.random.rand(n_features, n_classes)
            y_onehot = np.eye(n_classes)[y]

            for i in range(self.iterations):
                gradient = self._compute_gradients(X, y_onehot)
                self.weights -= self.learning_rate * gradient

    def predict(self, X: np.ndarray) -> np.ndarray:
        X = (X - self.mean) / self.std
        X = np.insert(X, 0, 1, axis = 1)

        if self.model_type == "linear":
            # TODO: 2%
            # Hint: Perform a matrix multiplication between the input features (X)
            # and the learned weights.

            return np.matmul(X, self.weights)
        
        elif self.model_type == "logistic":
            # TODO: 2%
            # Hint: Perform a matrix multiplication between the input features (X)
            # and the learned weights, then apply the softmax function to the result.

            A = np.matmul(X, self.weights)
            return np.argmax(self._softmax(A), axis = 1)

    def _compute_gradients(self, X: np.ndarray, y: np.ndarray) -> np.ndarray:
        if self.model_type == "linear":
            # TODO: 3%
            # Hint: Calculate the gradients for linear regression by computing
            # the dot product of X transposed and the difference between the
            # predicted values and the true values, then normalize by the number of samples.

            Xt = np.transpose(X)
            y_pred = np.matmul(X, self.weights)
            diff = y_pred - y

            return np.dot(Xt, diff) / X.shape[0]

        elif self.model_type == "logistic":
            # TODO: 3%
            # Hint: Calculate the gradients for logistic regression by computing
            # the dot product of X transposed and the difference between the one-hot
            # encoded true values and the softmax of the predicted values,
            # then normalize by the number of samples.

            Xt = np.transpose(X)
            y_pred = np.matmul(X, self.weights)
            diff = self._softmax(y_pred) - y

            return np.dot(Xt, diff) / X.shape[0]

    def _softmax(self, z: np.ndarray) -> np.ndarray:
        exp = np.exp(z)
        return exp / np.sum(exp, axis=1, keepdims=True)


class DecisionTree:
    def __init__(self, max_depth: int = 5, model_type: str = "classifier"):
        self.max_depth = max_depth
        self.model_type = model_type

        assert model_type in [
            "classifier",
            "regressor",
        ], "model_type must be either 'classifier' or 'regressor'"

    def fit(self, X: np.ndarray, y: np.ndarray) -> None:
        self.tree = self._build_tree(X, y, 0)

    def predict(self, X: np.ndarray) -> np.ndarray:
        return np.array([self._traverse_tree(x, self.tree) for x in X])

    def _build_tree(self, X: np.ndarray, y: np.ndarray, depth: int) -> dict:
        if depth >= self.max_depth or self._is_pure(y):
            return self._create_leaf(y)

        feature, threshold = self._find_best_split(X, y)
        # TODO: 4%
        # Hint: Create a mask based on the best feature and threshold that
        # separates the samples into two groups. Then, recursively build
        # the left and right child nodes of the current node.

        mask = X[:, feature] <= threshold

        left_child = self._build_tree(X[mask], y[mask], (depth + 1))
        right_child = self._build_tree(X[~mask], y[~mask], (depth + 1))

        return {
            "feature": feature,
            "threshold": threshold,
            "left": left_child,
            "right": right_child,
        }

    def _is_pure(self, y: np.ndarray) -> bool:
        return len(set(y)) == 1

    def _create_leaf(self, y: np.ndarray):
        if self.model_type == "classifier":
            # TODO: 1%
            # Hint: For classification, return the most common class in the given samples.

            return Counter(y).most_common(1)[0][0]

        else:
            # TODO: 1%
            # Hint: For regression, return the mean of the given samples.

            return np.mean(y)

    def _find_best_split(self, X: np.ndarray, y: np.ndarray) -> tuple[int, float]:
        best_gini = float("inf")
        best_mse = float("inf")
        best_feature = None
        best_threshold = None

        for feature in range(X.shape[1]):
            sorted_indices = np.argsort(X[:, feature])
            for i in range(1, len(X)):
                if X[sorted_indices[i - 1], feature] != X[sorted_indices[i], feature]:
                    threshold = (
                        X[sorted_indices[i - 1], feature]
                        + X[sorted_indices[i], feature]
                    ) / 2
                    mask = X[:, feature] <= threshold
                    left_y, right_y = y[mask], y[~mask]

                    if self.model_type == "classifier":
                        gini = self._gini_index(left_y, right_y)
                        if gini < best_gini:
                            best_gini = gini
                            best_feature = feature
                            best_threshold = threshold
                    else:
                        mse = self._mse(left_y, right_y)
                        if mse < best_mse:
                            best_mse = mse
                            best_feature = feature
                            best_threshold = threshold

        return best_feature, best_threshold

    def _gini_index(self, left_y: np.ndarray, right_y: np.ndarray) -> float:
        # TODO: 4%
        # Hint: Calculate the Gini index for the left and right samples,
        # then compute the weighted average based on the number of samples in each group.

        n = len(left_y) + len(right_y)

        n_left = np.array(list(Counter(left_y).values()))
        gini_left = 1 - np.sum((n_left / len(left_y)) ** 2)

        n_right = np.array(list(Counter(right_y).values()))
        gini_right = 1 - np.sum((n_right / len(right_y)) ** 2)

        return ((len(left_y) / n) * gini_left + (len(right_y) / n) * gini_right)

    def _mse(self, left_y: np.ndarray, right_y: np.ndarray) -> float:
        # TODO: 4%
        # Hint: Calculate the mean squared error for the left and right samples,
        # then compute the weighted average based on the number of samples in each group.

        n = len(left_y) + len(right_y)
        return ((len(left_y) / n) * np.var(left_y) + (len(right_y) / n) * np.var(right_y))

    def _traverse_tree(self, x: np.ndarray, node: dict):
        if isinstance(node, dict):
            feature, threshold = node["feature"], node["threshold"]
            if x[feature] <= threshold:
                return self._traverse_tree(x, node["left"])
            else:
                return self._traverse_tree(x, node["right"])
        else:
            return node


class RandomForest:
    def __init__(
        self,
        n_estimators: int = 200,
        max_depth: int = 5,
        model_type: str = "classifier",
    ):
        # TODO: 1%
        # Hint: Initialize a list of DecisionTree instances based on the
        # specified number of estimators, max depth, and model type.

        self.trees = [DecisionTree(max_depth = max_depth, model_type = model_type) for i in range(n_estimators)]

    def fit(self, X: np.ndarray, y: np.ndarray) -> None:
        n_samples = X.shape[0]
        for tree in self.trees:
            # TODO: 2%
            # Hint: Generate bootstrap indices by random sampling with replacement,
            # then fit each tree with the corresponding samples from X and y.
            # bootstrap_indices = np.random.choice(
            
            bootstrap_indices = np.random.choice(n_samples, size = n_samples, replace = True)

            X_bootstrap = X[bootstrap_indices]
            y_bootstrap = y[bootstrap_indices]
            
            tree.fit(X_bootstrap, y_bootstrap)

    def predict(self, X: np.ndarray) -> np.ndarray:
        # TODO: 2%
        # Hint: Predict the output for each tree and combine the predictions
        # based on the model type (majority voting for classification or averaging
        # for regression).
        
        predictions = np.transpose(np.array([tree.predict(X) for tree in self.trees]))

        if self.trees[0].model_type == "classifier":
            return np.array([Counter(row).most_common(1)[0][0] for row in predictions])
        
        elif self.trees[0].model_type == "regressor":
            return np.mean(predictions, axis = 1)


# 4. Evaluation metrics
def accuracy(y_true, y_pred):
    # TODO: 1%
    # Hint: Calculate the percentage of correct predictions by comparing
    # the true and predicted labels.

    return np.sum(y_true == y_pred) / len(y_true)

def mean_squared_error(y_true, y_pred):
    # TODO: 1%
    # Hint: Calculate the mean squared error between the true and predicted values.

    return np.mean((y_true - y_pred) ** 2)

# 5. Main function
def main():
    iris, boston = load_data()

    # Iris dataset - Classification
    X_train, X_test, y_train, y_test = train_test_split(iris, "class")
    X_train, X_test = normalize(X_train), normalize(X_test)
    y_train, y_test = encode_labels(y_train), encode_labels(y_test)

    """

    logistic_regression = LinearModel(model_type="logistic")
    logistic_regression.fit(X_train, y_train)
    y_pred = logistic_regression.predict(X_test)
    print("Logistic Regression Accuracy:", accuracy(y_test, y_pred))


    decision_tree_classifier = DecisionTree(model_type="classifier")
    decision_tree_classifier.fit(X_train, y_train)
    y_pred = decision_tree_classifier.predict(X_test)
    print("Decision Tree Classifier Accuracy:", accuracy(y_test, y_pred))

    """

    random_forest_classifier = RandomForest(model_type="classifier")
    random_forest_classifier.fit(X_train, y_train)
    y_pred = random_forest_classifier.predict(X_test)
    print("Random Forest Classifier Accuracy:", accuracy(y_test, y_pred))

    # Boston dataset - Regression
    X_train, X_test, y_train, y_test = train_test_split(boston, "medv")
    X_train, X_test = normalize(X_train), normalize(X_test)

    """

    linear_regression = LinearModel(model_type="linear")
    linear_regression.fit(X_train, y_train)
    y_pred = linear_regression.predict(X_test)
    print("Linear Regression MSE:", mean_squared_error(y_test, y_pred))

    decision_tree_regressor = DecisionTree(model_type="regressor")
    decision_tree_regressor.fit(X_train, y_train)
    y_pred = decision_tree_regressor.predict(X_test)
    print("Decision Tree Regressor MSE:", mean_squared_error(y_test, y_pred))
    
    """

    random_forest_regressor = RandomForest(model_type="regressor")
    random_forest_regressor.fit(X_train, y_train)
    y_pred = random_forest_regressor.predict(X_test)
    print("Random Forest Regressor MSE:", mean_squared_error(y_test, y_pred))



if __name__ == "__main__":
    main()
