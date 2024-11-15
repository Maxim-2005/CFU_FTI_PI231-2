import pandas as pd
from genser import transform_to
from dsmltf import knn_classify, principal_components

# вывод результатов
def print_result(labeled_points_full, X, y):
    dict = {}
    for k in range(1, 7):
        y_pred_full = [knn_classify(k, labeled_points_full, x) for x in X] # метод k-ближайших соседей для k от 1 до 6
        correct_predictions = sum(pred == actual for pred, actual in zip(y_pred_full, y))
        accuracy = correct_predictions / len(y)
        dict.append(k, correct_predictions)
        print(f"{k} соседей: правильных {correct_predictions} из {len(y)}, точность: {accuracy:.2f}")
    max_v = max(dict.values)
    print(dict.get(max_v))
    print('-' * 45)

# Чтение данных
df = pd.read_csv('iris.csv', delimiter=',').values.tolist()
data = []
for row in df:
    data.append([float(row[1]), float(row[2]), float(row[3]), float(row[4]), row[5]])

# Признаки и метки
X = [[value for value in row[:-1]] for row in data]  # Признаки
y = [row[-1] for row in data]  # Метки

# Использование полного набора данных
labeled_points_full = list(zip(X, y))
print_result(labeled_points_full, X, y)

# снижение размерности методом главных компонент
X_pca = principal_components(X, 2)
labeled_points_full_pca = list(zip(X_pca, y))
print_result(labeled_points_full_pca, X_pca, y)

# снижение размерности методом обощённой сериализации
X_lnn = transform_to(X, 2)[0]
labeled_points_full_lnn = list(zip(X_lnn, y))
print_result(labeled_points_full_lnn, X_lnn, y)
