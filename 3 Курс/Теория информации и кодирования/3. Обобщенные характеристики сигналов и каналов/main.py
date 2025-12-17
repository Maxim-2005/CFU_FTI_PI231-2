import numpy as np
import math
import pandas as pd
from typing import Dict, Any

# --- КОНСТАНТЫ (Вариант №7) ---
N = 55  # Количество символов
NUM_EXPERIMENTS = 6
EPS = 1e-12 

# --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

def log2(x: float) -> float:
    """Безопасный расчет log2(x), возвращает 0 для x=0."""
    return math.log2(x) if x > 0 else 0

def format_short_row(row: np.ndarray, precision: int = 5) -> str:
    """Форматирует строку/вектор: показывает начало и конец."""
    row = np.asarray(row)
    n = row.size
    if n <= 6:
        return " ".join(f"{x:.{precision}f}" for x in row)
    first = " ".join(f"{x:.{precision}f}" for x in row[:3])
    last = " ".join(f"{x:.{precision}f}" for x in row[-3:])
    return f"{first} ... {last}"

def format_short_vector(v: np.ndarray, precision: int = 5) -> str:
    """Аналогичен format_short_row, используется для векторов."""
    return format_short_row(v, precision)

def format_short_matrix(M: np.ndarray, precision: int = 5) -> str:
    """Форматирует матрицу: показывает фрагмент 6x6 или 3x3 (начало и конец)."""
    N_rows, N_cols = M.shape
    rows = []
    
    # Печатаем первые 3 строки
    for i in range(min(3, N_rows)):
        rows.append(format_short_row(M[i], precision))
    
    if N_rows > 6:
        rows.append("...")

    # Печатаем последние 3 строки
    for i in range(max(3, N_rows - 3), N_rows):
        rows.append(format_short_row(M[i], precision))
        
    return "\n".join(rows)

# --- ГЕНЕРАЦИЯ ДАННЫХ ---

def gen_input_probabilities(N, rng):
    """Генерация и нормировка входных вероятностей p(x)."""
    raw = rng.integers(1, 101, size=N).astype(float)
    p = raw / raw.sum()
    return p

def gen_symbol_durations(N, rng):
    """Генерация длительностей символов tau_i в (0, N] мкс."""
    durations = rng.random(size=N) * N
    durations = np.where(durations <= 0, EPS, durations)
    return durations

def gen_channel_matrix(N, q, rng):
    """Генерация матрицы P(Y|X) с помехами, q = 1/(2N)."""
    P = np.zeros((N, N), dtype=float)
    for i in range(N):
        # Генерируем N-1 ошибок в диапазоне [0, q]
        errs = rng.random(size=N - 1) * q
        sum_errs = errs.sum()
        
        # Заполнение вне диагонали
        idxs = [j for j in range(N) if j != i]
        P[i, idxs] = errs
        
        # Вероятность безошибочной передачи P(y_i|x_i)
        P[i, i] = 1.0 - sum_errs

        # Нормировка (на случай ошибок округления)
        s = P[i, :].sum()
        if s > 0:
            P[i, :] = P[i, :] / s
    return P

# --- РАСЧЕТЫ ---

def entropy(p):
    """Расчет энтропии H(X)."""
    p_safe = np.clip(p, EPS, 1.0)
    return -np.sum(p_safe * np.log2(p_safe))

def conditional_entropy_X_given_Y(p_x, P_y_given_x):
    """Расчет остаточной неопределенности H(X|Y)."""
    p_y = np.dot(p_x, P_y_given_x)
    joint = p_x.reshape(-1, 1) * P_y_given_x  # p(x_i, y_j)
    p_y_safe = np.clip(p_y, EPS, 1.0)
    
    # P(X|Y) = P(X,Y) / P(Y)
    p_x_given_y = joint / p_y_safe.reshape(1, -1)
    p_x_given_y = np.clip(p_x_given_y, EPS, 1.0)
    
    # H(X|Y)
    H = -np.sum(joint * np.log2(p_x_given_y))
    return H

# --- УПРАВЛЕНИЕ ЭКСПЕРИМЕНТАМИ ---

def run_one_experiment(N, base_seed, exp_index):
    """Выполняет один численный эксперимент."""
    seed = (base_seed + exp_index) if base_seed is not None else None
    rng = np.random.default_rng(seed)
    
    q = 1.0 / (2.0 * N)
    
    p_x = gen_input_probabilities(N, rng)
    durations = gen_symbol_durations(N, rng)
    P_noise = gen_channel_matrix(N, q, rng)
    
    tau_bar = float(np.sum(p_x * durations))
    H_X = entropy(p_x)
    H_X_given_Y = conditional_entropy_X_given_Y(p_x, P_noise)

    # log2(N) - максимальная энтропия источника
    max_H = np.log2(N) 
    
    # Расчеты в кбит/с (бит / мкс * 10^3)
    I_no_noise_kbps = (H_X / max(tau_bar, EPS)) * 1e3
    C_no_noise_kbps = (max_H / max(tau_bar, EPS)) * 1e3
    I_with_noise_kbps = ((H_X - H_X_given_Y) / max(tau_bar, EPS)) * 1e3
    C_with_noise_kbps = ((max_H - H_X_given_Y) / max(tau_bar, EPS)) * 1e3

    return {
        "p_x": p_x,
        "durations": durations,
        "P_noise": P_noise,
        "tau_bar": tau_bar,
        "H_X": H_X,
        "H_X_given_Y": H_X_given_Y,
        "I_no_noise_kbps": I_no_noise_kbps,
        "C_no_noise_kbps": C_no_noise_kbps,
        "I_with_noise_kbps": I_with_noise_kbps,
        "C_with_noise_kbps": C_with_noise_kbps,
        "q": q
    }

def run_experiments(num_experiments=6, N=55, base_seed=777):
    """Запускает комплекс экспериментов и считает среднее."""
    results = []
    for i in range(num_experiments):
        res = run_one_experiment(N, base_seed, i)
        results.append(res)

    avg = {
        "I_no_noise_kbps": np.mean([r["I_no_noise_kbps"] for r in results]),
        "C_no_noise_kbps": np.mean([r["C_no_noise_kbps"] for r in results]),
        "I_with_noise_kbps": np.mean([r["I_with_noise_kbps"] for r in results]),
        "C_with_noise_kbps": np.mean([r["C_with_noise_kbps"] for r in results]),
    }
    return results, avg

def print_results(results, avg, N):
    """Выводит результаты экспериментов в заданном формате."""
    max_H = np.log2(N)
    
    print(f"--- РЕЗУЛЬТАТЫ ЛАБОРАТОРНОЙ РАБОТЫ №3 (Вариант №7, N={N}) ---")
    print(f"Максимальная энтропия log2(N) = {max_H:.5f} бит. Макс. вероятность ошибки q = {results[0]['q']:.5f}")
    print("=======================================================================\n")
    
    for idx, r in enumerate(results, 1):
        print(f"### Эксперимент {idx}")

        print("\np(x):")
        print(format_short_vector(r["p_x"]))

        print("\nτ_i (мкс):")
        print(format_short_vector(r["durations"]))

        print("\nМатрица условных вероятностей P(y|x) (с помехами):")
        print(format_short_matrix(r["P_noise"]))

        print(f"\nСредняя длительность τ̄ = {r['tau_bar']:.5f} мкс")
        print(f"H(X) = {r['H_X']:.5f} бит")
        print(f"H(X|Y) = {r['H_X_given_Y']:.5f} бит")
        print(f"Ī (без помех) = {r['I_no_noise_kbps']:.5f} кбит/с")
        print(f"C (без помех) = {r['C_no_noise_kbps']:.5f} кбит/с")
        print(f"Ī (с помехами) = {r['I_with_noise_kbps']:.5f} кбит/с")
        print(f"C (с помехами) = {r['C_with_noise_kbps']:.5f} кбит/с")
        print("\n" + ("-"*50) + "\n")

    print("### Сводные средние результаты")
    print(f"Средняя скорость (без помех): {avg['I_no_noise_kbps']:.5f} кбит/с")
    print(f"Средняя пропускная способность (без помех): {avg['C_no_noise_kbps']:.5f} кбит/с")
    print(f"Средняя скорость (с помехами): {avg['I_with_noise_kbps']:.5f} кбит/с")
    print(f"Средняя пропускная способность (с помехами): {avg['C_with_noise_kbps']:.5f} кбит/с")

def main():
    # Запуск
    results, avg = run_experiments(NUM_EXPERIMENTS, N, base_seed=777)
    print_results(results, avg, N)

if __name__ == "__main__":
    main()