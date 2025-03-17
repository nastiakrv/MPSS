import numpy as np
import matplotlib.pyplot as plt

N = 11

# Початкові параметри
H = 1000 - N
beta = 25 - N
gamma = N

x0 = 900 - N
y0 = 90 - N
z0 = H - x0 - y0
t0 = 0
h = 0.1
T = 40
steps = int(T / h)

# Ініціалізація масивів для значень
t_values = np.linspace(t0, T, steps)
x_values = np.zeros(steps)
y_values = np.zeros(steps)
z_values = np.zeros(steps)

x_values[0] = x0
y_values[0] = y0
z_values[0] = z0

# Похідні для системи рівнянь
def x_deriv(x, y):
    return -beta / H * x * y

def y_deriv(x, y):
    return beta / H * x * y - y / gamma

def z_deriv(y):
    return y / gamma

# Метод Рунге-Кутта 4-го порядку
def runge_kutta(x0, y0, z0, steps):
    for n in range(steps - 1):
        x, y, z = x_values[n], y_values[n], z_values[n]
        
        k1_x = x_deriv(x, y)
        k1_y = y_deriv(x, y)
        k1_z = z_deriv(y)

        k2_x = x_deriv(x + h/2 * k1_x, y + h/2 * k1_y)
        k2_y = y_deriv(x + h/2 * k1_x, y + h/2 * k1_y)
        k2_z = z_deriv(y + h/2 * k1_y)

        k3_x = x_deriv(x + h/2 * k2_x, y + h/2 * k2_y)
        k3_y = y_deriv(x + h/2 * k2_x, y + h/2 * k2_y)
        k3_z = z_deriv(y + h/2 * k2_y)

        k4_x = x_deriv(x + h * k3_x, y + h * k3_y)
        k4_y = y_deriv(x + h * k3_x, y + h * k3_y)
        k4_z = z_deriv(y + h * k3_y)

        x_values[n + 1] = x + h / 6 * (k1_x + 2 * k2_x + 2 * k3_x + k4_x)
        y_values[n + 1] = y + h / 6 * (k1_y + 2 * k2_y + 2 * k3_y + k4_y)
        z_values[n + 1] = z + h / 6 * (k1_z + 2 * k2_z + 2 * k3_z + k4_z)
        
        # Вивід покрокових значень
        print(f"Крок {n + 1}: t = {t_values[n + 1]:.2f}, x = {x_values[n + 1]:.4f}, y = {y_values[n + 1]:.4f}, z = {z_values[n + 1]:.4f}")

# Запуск обчислень
runge_kutta(x0, y0, z0, steps)

# Побудова графіків
plt.figure(figsize=(12, 6))
plt.plot(t_values, x_values, label='Здорові (x)', color='#0B1D51', linewidth=2)
plt.plot(t_values, y_values, label='Хворі (y)', color='#B8006B', linewidth=2)
plt.plot(t_values, z_values, label='Одужали (z)', color='#329F5B', linewidth=2)

plt.title('Графік залежності x(t), y(t) і z(t)')
plt.xlabel('Час (дні, t)')
plt.ylabel('Кількість людей')
plt.legend()

plt.grid(True)
plt.show()
