import math
import random


N = 14
array = []
exp_count = 0
entropy_array = []
exp_entropy_array = []

for k in range(6):
    for _ in range(N):
        i = random.random()
        array.append(i)
    array = [round(i/sum(array), 3) for i in array]

    entropy = 0
    for i in array:
        exp_entropy = -math.log2(i)
        entropy += i * exp_entropy
        exp_entropy_array.append(round(exp_entropy, 3))
    entropy_array.append(round(entropy, 3))

    print(f"Эксперимент №{k}: {array}\n"
          f"Максимальная энтропия: {max(exp_entropy_array)}\n")
    array.clear()
    exp_entropy_array.clear()

print(f"Среднее количество информации: {sum(entropy_array)/len(entropy_array)}\n"
      f"Максимальная энтропия: {max(entropy_array)}")