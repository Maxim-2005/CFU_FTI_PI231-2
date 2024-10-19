from time import time
from math import pi, sin, cos
from dsmltf import gradient_descent, minimize_stochastic
import matplotlib.pyplot as plt

# Шаг по оси времени для построения функции
dt = 2 * pi / 1000

# Массив значений для временной оси
x = list()

# Базовый ряд из 500 точек на основе углов (от 0 до 2π)
base = [2 * pi * (i / 500) for i in range(500)]

# Функция для аппроксимации Фурье ряда
def furie(k, a):
    global base
    # Используем заданные коэффициенты для расчета ряда
    return a[0] + a[1] * cos(base[k]) + a[2] * sin(base[k]) + a[3] * cos(2 * base[k]) + a[4] * sin(2 * base[k])

# Функция ошибки для градиентного спуска
def F(a: list) -> float:
    global x
    # Возвращаем сумму квадратов ошибок между реальными значениями и аппроксимацией
    return sum([(x[j] - furie(j, a)) ** 2 for j in range(500)])

# Функция ошибки для стохастического градиентного спуска
def f(i, a):
    global x
    # Возвращаем ошибку для конкретного элемента ряда
    return (x[i] - furie(i, a)) ** 2


# Параметр, влияющий на частоту
k = 1
# Угловая частота
omega = 1000 / k
# Длина волны, масштабирующий параметр
L = k / 100


# Инициализация ряда значений
x = [0, (-1)**k * dt]

# Вычисляем значения ряда по рекуррентной формуле
for i in range(2, 500):
    x.append(x[i-1] * (2 + dt * L * (1 - x[i-2]**2)) - 
                x[i-2] * (1 + dt**2 + dt * L * (1 - x[i-2]**2)) + 
                dt**2 * sin(omega * dt))

# Поиск коэффициентов методом градиентного спуска
s_t_0 = time()
a0 = gradient_descent(F, [0] * 5)
s_t_1 = time()

# Поиск коэффициентов методом стохастического градиентного спуска
a1 = minimize_stochastic(f, [i for i in range(500)], [0] * 500, [0] * 5)

# Вывод первых двух коэффициентов для каждого метода
print(a0[0], a0[1])
print(a1[0], a1[1])

# Вывод времени, затраченного каждым методом
print(f"{s_t_1 - s_t_0} секунд", f"{time() - s_t_1} секунд")

# Построение графиков
plt.plot(base, x, label='Исходная функция', color='red')
plt.plot(base, [furie(i, a0[0]) for i in range(500)], label='Градиентный спуск', color='green')
plt.plot(base, [furie(i, a1[0]) for i in range(500)], label='Стохастический градиентный спуск', color='blue')

# Подписи осей
plt.xlabel('x')
plt.ylabel('y')

# Легенда и сетка на графике
plt.legend()
plt.grid(True)

# Отображение графика
plt.show()
