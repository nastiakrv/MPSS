import numpy as np
import matplotlib.pyplot as plt

# Параметри задачі
N = 11
a11 = 0.01 * N
a12 = 0.0001 * N
a21 = 0.0001 * N
a22 = 0.04 * N

# Початкові умови
x0 = 1000 - 10 * N
y0 = 700 - 10 * N

# Часові параметри
t0 = 0
T = 150
h = 0.1
steps = int(T / h)

# Функції правих частин системи
def dxdt(x, y):
    return a11 * x - a12 * x * y

def dydt(x, y):
    return -a22 * y + a21 * x * y

# Масиви для збереження результатів
t = np.linspace(t0, T, steps)
x = np.zeros(steps)
y = np.zeros(steps)

# Початкові значення
x[0] = x0
y[0] = y0

# Метод Рунге-Кутта 4-го порядку
for n in range(steps - 1):
    k1_x = dxdt(x[n], y[n])
    k1_y = dydt(x[n], y[n])

    k2_x = dxdt(x[n] + h/2 * k1_x, y[n] + h/2 * k1_y)
    k2_y = dydt(x[n] + h/2 * k1_x, y[n] + h/2 * k1_y)

    k3_x = dxdt(x[n] + h/2 * k2_x, y[n] + h/2 * k2_y)
    k3_y = dydt(x[n] + h/2 * k2_x, y[n] + h/2 * k2_y)

    k4_x = dxdt(x[n] + h * k3_x, y[n] + h * k3_y)
    k4_y = dydt(x[n] + h * k3_x, y[n] + h * k3_y)

    x[n + 1] = x[n] + (h / 6) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x)
    y[n + 1] = y[n] + (h / 6) * (k1_y + 2 * k2_y + 2 * k3_y + k4_y)

    # Виведення результатів на кожному кроці
    print(f"t = {round(t[n + 1], 2)} -> x = {round(x[n + 1], 2)}, y = {round(y[n + 1], 2)}")

# Побудова графіків
plt.figure(figsize=(12, 5))
plt.plot(t, x, label='Зайці', color='green')
plt.plot(t, y, label='Вовки', color='red')
plt.xlabel('Час (дні)')
plt.ylabel('Кількість')
plt.legend()
plt.grid()
plt.title('Графік залежності x(t) та y(t)')
plt.show()

# Фазовий портрет
plt.figure(figsize=(6, 6))
plt.plot(x, y, color='purple')
plt.xlabel('Кількість зайців')
plt.ylabel('Кількість вовків')
plt.grid()
plt.title('Графік залежності y(x)')
plt.show()
