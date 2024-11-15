import pandas as pd
from genser import transform_to
from dsmltf import knn_classify, principal_components


def print_result(data):
    for k in range(1, 7):
        counter = 0
        for d in data:
            values, actual = d
            other_d = [x for x in data if x != d]
            y_pred_full = [knn_classify(k, other_d, values)]
            if y_pred_full == actual:
                counter += 1
            print(f"{k} соседей: правильных {counter} из {len(data)}")
    print('-' * 25)


df = pd.read_csv('iris.csv', delimiter=',').values.tolist()
data = []
for row in df:
    data.append(([float(row[1]), float(row[2]), float(row[3]), float(row[4])], row[5]))
print_result(data)

pca = principal_components(data[0], 2)
print_result(pca)

lnn = transform_to(data[0], 2)[0]
print_result(lnn)
