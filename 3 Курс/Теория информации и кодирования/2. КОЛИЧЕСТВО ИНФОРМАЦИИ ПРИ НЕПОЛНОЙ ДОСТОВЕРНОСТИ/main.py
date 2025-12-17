import numpy as np
import math
import pandas as pd
from typing import Dict, Any

# Параметры для Варианта №7
N = 55 
NUM_EXPERIMENTS = 6

def log2(x: float) -> float:
    """Безопасный расчет log2(x), возвращает 0 для x=0."""
    return math.log2(x) if x > 0 else 0

def calculate_probabilities_and_information(N: int) -> Dict[str, Any]:
    """Выполняет один численный эксперимент для заданного N."""
    
    # 1. Генерация массива входных вероятностей P(X) (p(xi))
    r_x = np.random.uniform(0.01, 1.0, N)
    P_X = r_x / np.sum(r_x)

    # 2. Генерация матрицы переходных вероятностей P(Y|X) (P(yj|xi)) (N x N)
    P_Y_X = np.zeros((N, N))
    for i in range(N):
        # Вероятность безошибочной передачи p(yi|xi) >= 0.70
        P_Y_X[i, i] = np.random.uniform(0.70, 1.0)
        R_i = 1.0 - P_Y_X[i, i]
        
        # Распределение оставшейся вероятности на ошибки
        r_error = np.random.uniform(0.0, 1.0, N - 1)
        r_error_normalized = r_error / np.sum(r_error) * R_i
        
        k = 0
        for j in range(N):
            if i != j:
                P_Y_X[i, j] = r_error_normalized[k]
                k += 1
    
    # 3. Расчет матрицы совместных вероятностей P(X,Y) (p(xi, yj))
    P_X_Y = P_X[:, np.newaxis] * P_Y_X

    # 4. Расчет массива выходных вероятностей P(Y) (p(yj))
    P_Y = np.sum(P_X_Y, axis=0)

    # 5. Расчет энтропий
    H_X = -np.sum(P_X * np.array([log2(p) for p in P_X]))
    H_Y = -np.sum(P_Y * np.array([log2(p) for p in P_Y]))
    H_X_Y = -np.sum(P_X_Y * np.array([[log2(p) for p in row] for row in P_X_Y]))

    H_Y_X = H_X_Y - H_X # Энтропия помех (Шум)
    H_X_Y_cond = H_X_Y - H_Y # Остаточная неопределенность (Потери)

    # 6. Количество информации
    I_X_Y = H_X + H_Y - H_X_Y
    
    return {
        "H(X)": H_X,
        "H(Y)": H_Y,
        "H(X,Y)": H_X_Y,
        "H(Y|X)": H_Y_X,
        "H(X|Y)": H_X_Y_cond,
        "I(X,Y)": I_X_Y,
        "P_X": P_X,
        "P_Y": P_Y,
        "P_Y_X": P_Y_X,
        "P_X_Y": P_X_Y
    }

results = []
for _ in range(NUM_EXPERIMENTS):
    results.append(calculate_probabilities_and_information(N))
    
# Сбор результатов в DataFrame для удобства вывода
results_df = pd.DataFrame([
    {
        "H(X)": res["H(X)"],
        "H(Y)": res["H(Y)"],
        "H(X,Y)": res["H(X,Y)"],
        "H(Y|X)": res["H(Y|X)"],
        "H(X|Y)": res["H(X|Y)"],
        "I(X,Y)": res["I(X,Y)"],
    } for res in results
])

# Расчет средних значений
avg_results = results_df.mean().rename("Среднее значение")
results_df = pd.concat([results_df, avg_results.to_frame().T]).round(4)
results_df.index = [f"Эксперимент №{i+1}" for i in range(NUM_EXPERIMENTS)] + ["СРЕДНЕЕ"]

# --- Вывод результатов ---
first_res = results[0]

print(f"--- РЕЗУЛЬТАТЫ ЛАБОРАТОРНОЙ РАБОТЫ №2 (Вариант №7, N={N}, 6 экспериментов) ---")
print("=======================================================================\n")

print("### 3.1. Исходные массивы вероятностей для Эксперимента №1")
print("Массив P(X) и P(Y) содержат 55 элементов. Ниже приведена вырезка для наглядности:")
print("\n**Массив входных вероятностей P(X) (Первые 10 элементов):**")
print(np.around(first_res['P_X'][:10], 8))

print("\n**Массив выходных вероятностей P(Y) (Первые 10 элементов):**")
print(np.around(first_res['P_Y'][:10], 8))

print("\n-----------------------------------------------------------------------\n")

print("### 3.2. Фрагменты расчетных матриц (6x6) для Эксперимента №1")
print("Матрицы P(Y|X) и P(X,Y) имеют размер 55x55. Для отчета достаточно представить фрагмент:")

# Фрагмент матрицы переходных вероятностей P(Y|X)
print("\n**Матрица переходных вероятностей P(Y|X) (фрагмент 6x6):**")
print(np.around(first_res['P_Y_X'][:6, :6], 5))

# Фрагмент матрицы совместных вероятностей P(X,Y)
print("\n**Матрица совместных вероятностей P(X,Y) (фрагмент 6x6):**")
print(np.around(first_res['P_X_Y'][:6, :6], 8)) 

print("\n-----------------------------------------------------------------------\n")

print("### 3.3. Результаты численных экспериментов (Сводная таблица)")
print("Таблица содержит рассчитанные значения всех необходимых энтропий и количества информации для 6 экспериментов и их средние значения:")

# Вывод таблицы результатов
print(results_df.to_markdown(floatfmt=".4f"))