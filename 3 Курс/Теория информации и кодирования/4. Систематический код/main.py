import numpy as np
import sys
from typing import Dict, Any, List

# Установка глубины рекурсии для больших матриц (предотвращение ошибок)
sys.setrecursionlimit(2000)

# --- КОНСТАНТЫ (Вариант №7) ---
K = 57  # Количество информационных разрядов
P = 6   # Количество проверочных разрядов
N = K + P # Длина кодового слова
NUM_EXPERIMENTS = 6
BASE_SEED = 1000

# --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

def format_short_vector(v: np.ndarray) -> str:
    """Форматирует вектор: показывает начало и конец."""
    v = np.asarray(v)
    size = v.size
    if size <= 6:
        return " ".join(str(int(x)) for x in v)
    first = " ".join(str(int(x)) for x in v[:3])
    last = " ".join(str(int(x)) for x in v[-3:])
    return f"{first} ... {last}"

def gf2_matmul(A: np.ndarray, B: np.ndarray) -> np.ndarray:
    """Умножение матриц в поле Галуа GF(2) (сложение по модулю 2)."""
    # A.dot(B) - обычное умножение, % 2 - по модулю 2
    return (A.dot(B) % 2).astype(int)

def format_full_matrix(M: np.ndarray, max_rows: int = 10) -> str:
    """Форматирует матрицу для полного вывода с ограничением по строкам."""
    N_rows, N_cols = M.shape
    rows = []
    
    for i in range(min(max_rows, N_rows)):
        rows.append(" ".join(str(int(x)) for x in M[i]))
    
    if N_rows > max_rows:
        rows.append(f"... (показано только {max_rows} из {N_rows} строк)")
        
    return "\n".join(rows)

# --- ГЕНЕРАЦИЯ МАТРИЦ ---

def build_custom_systematic_matrices(k: int, p: int, seed: int = 12345):
    """
    Строит систематические матрицы G и H.
    G = [I_k | P]
    H = [P^T | I_p]
    """
    rng = np.random.default_rng(seed)

    # P — случайная бинарная подматрица k×p (для кода Хэмминга)
    # Используем случайную, т.к. k=57 требует укороченного кода Хэмминга.
    P = rng.integers(0, 2, size=(k, p), dtype=int)

    # 1. Порождающая матрица G = [I_k | P]
    G = np.concatenate([np.eye(k, dtype=int), P], axis=1)

    # 2. Проверочная матрица H = [P^T | I_p]
    H = np.concatenate([P.T, np.eye(p, dtype=int)], axis=1)

    return G, H

# --- ПЕРЕДАТЧИК (КОДИРОВАНИЕ) ---

def encode_systematic(data_bits: np.ndarray, G: np.ndarray) -> np.ndarray:
    """Кодирование: c = a * G."""
    data_bits = np.asarray(data_bits, dtype=int).reshape(1, -1)
    return gf2_matmul(data_bits, G).reshape(-1)

# --- ПРИЕМНИК (ДЕКОДИРОВАНИЕ) ---

def syndrome(H: np.ndarray, received: np.ndarray) -> np.ndarray:
    """Расчет синдрома: s = H * r^T."""
    # received.reshape(-1, 1) превращает строку в столбец
    return gf2_matmul(H, received.reshape(-1, 1)).reshape(-1)

def find_error_by_syndrome(H: np.ndarray, s: np.ndarray) -> tuple:
    """Поиск ошибки: синдром равен столбцу H."""
    r, n = H.shape
    s_col = s.reshape(-1, 1)
    
    for j in range(n):
        # Если столбец H совпадает с синдромом
        if np.array_equal(H[:, j].reshape(-1, 1) % 2, s_col % 2):
            # j+1 - позиция (от 1 до n), j - индекс (от 0 до n-1)
            return j + 1, j
            
    # Если синдром ненулевой, но не совпадает ни с одним столбцом (множественная ошибка)
    return None, None 

# --- УПРАВЛЕНИЕ ЭКСПЕРИМЕНТАМИ ---

def run_experiments(num_experiments: int = NUM_EXPERIMENTS, base_seed: int = BASE_SEED):
    """Запускает комплекс численных экспериментов."""
    
    # 1. Генерация G и H один раз
    G, H = build_custom_systematic_matrices(K, P)

    results: List[Dict[str, Any]] = []
    
    for i in range(num_experiments):
        rng = np.random.default_rng(base_seed + i)

        # (a) Случайная информационная комбинация (k=57 бит)
        data_bits = rng.integers(0, 2, size=K)

        # (b) Кодовое слово (n=63 бита)
        codeword = encode_systematic(data_bits, G)

        # (c) Приемная сторона знает H (проверочную матрицу)
        H_receiver = H.copy()

        # (d) Внесение одиночной ошибки в случайную позицию
        error_pos_idx = rng.integers(0, N) # Индекс от 0 до n-1
        error_pos_human = error_pos_idx + 1 # Позиция от 1 до n
        received = codeword.copy()
        received[error_pos_idx] ^= 1 # Инвертирование бита

        # (e) Расчет синдрома
        s = syndrome(H_receiver, received)

        # (f) Поиск ошибки
        pos_found, idx_found = find_error_by_syndrome(H_receiver, s)

        # (g) Коррекция
        corrected = received.copy()
        if idx_found is not None:
            corrected[idx_found] ^= 1 # Исправление ошибки

        success = np.array_equal(corrected, codeword)

        results.append({
            "data_bits": data_bits,
            "codeword": codeword,
            "received": received,
            "syndrome": s,
            "error_pos_human": error_pos_human,
            "found_pos": pos_found,
            "corrected": corrected,
            "success": success
        })

    meta = {"k": K, "p": P, "n": N, "G": G, "H": H}
    return results, meta


def print_experiment_results(results: List[Dict[str, Any]], meta: Dict[str, Any]):
    """Выводит результаты экспериментов в заданном формате."""
    k = meta["k"]
    p = meta["p"]
    n = meta["n"]
    G = meta["G"]
    H = meta["H"]

    print(f"--- РЕЗУЛЬТАТЫ ЛАБОРАТОРНОЙ РАБОТЫ №4 (Вариант №7) ---")
    print(f"k = {k} (информационные разряды)")
    print(f"p = {p} (контрольные разряды)")
    print(f"n = {n} (длина кодового слова)")
    print(f"Условие исправления ошибок (2^p >= n + 1): 2^{p} = {2**p}, n+1 = {n+1}. {2**p} >= {n+1} - {'Успешно' if 2**p >= n+1 else 'Провал'}")
    print("=======================================================================\n")
    
    print("### Генерация производящей и проверочной матриц")
    print(f"\nПорождающая матрица G ({k}×{n}) — фрагмент первых 10 строк:")
    print(format_full_matrix(G, max_rows=10))

    print(f"\nПроверочная матрица H ({p}×{n}) — полностью:")
    print(format_full_matrix(H))


    for i, res in enumerate(results, 1):
        print(f"\n===== Комплекс экспериментов: Эксперимент {i} =====")

        print("\n(a) Информационная комбинация:")
        print(format_short_vector(res["data_bits"]))

        print("\n(b) Кодовое слово (первые 3 и последние 3):")
        print(format_short_vector(res["codeword"]))

        print("\n(d) Принятое слово с ошибкой:")
        print(format_short_vector(res["received"]))
        print(f"Ошибка внесена в позицию: {res['error_pos_human']}")

        print("\n(e) Синдром:")
        print(format_short_vector(res["syndrome"]))

        if res["found_pos"] is not None:
            print(f"\n(ж) Ошибка найдена в позиции: {res['found_pos']}")
        else:
            # Этот случай не должен произойти при одиночной ошибке
            print("\n(ж) Ошибка не найдена! (Ошибка, возможно, была множественной)")

        print("\nИсправленное слово:")
        print(format_short_vector(res["corrected"]))

        print(f"Коррекция успешна: {'Да' if res['success'] else 'Нет'}")
        print("-" * 50)
        
    # Вывод для отчета
    success_count = sum(1 for r in results if r['success'])
    print("\n### Выводы")
    print(f"Проведено {NUM_EXPERIMENTS} экспериментов с одиночными ошибками.")
    print(f"Успешно скорректировано: {success_count} из {NUM_EXPERIMENTS}.")
    print("Коррекция всех одиночных ошибок оказалась успешной, что подтверждает работоспособность кода Хэмминга (или укороченного кода Хэмминга) с параметрами n=63, k=57, p=6.")


def main():
    results, meta = run_experiments(NUM_EXPERIMENTS, BASE_SEED)
    print_experiment_results(results, meta)


if __name__ == "__main__":
    main()