import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Вихідні дані
a = 0.082e-6
L = 0.5
T = 140 * 3600
N = 100
h = 30
phi1 = 11
phi2 = 30

delta = L / N

# Початкові умови
u = np.zeros(N)
u[0] = phi1
u[-1] = phi2

# Функція для обчислення похідних
def dudt(u):
    dudt = np.zeros(N)
    dudt[0] = 0
    dudt[-1] = 0
    for i in range(1, N - 1):
        value = a * (u[i - 1] - 2 * u[i] + u[i + 1]) / (delta ** 2)
        if np.isfinite(value):
            dudt[i] = value
        else:
            dudt[i] = 0
    return dudt

# Реалізація методу Рунге-Кутта
def runge_kutta(u, h, T):
    t = 0
    results = []
    while t < T:
        k1 = dudt(u)
        k2 = dudt(u + h * k1 / 2)
        k3 = dudt(u + h * k2 / 2)
        k4 = dudt(u + h * k3)
        u = u + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6
        u = np.nan_to_num(u) 
        u = np.clip(u, -1e6, 1e6)  
        results.append(u.copy())
        t += h
    return np.array(results)

# Аналітичний розв’язок
#def analytical_solution(t, y):
#    u_an = phi1 + (phi2 - phi1) * y / L
#    for n in range(1, 31): 
##        term = ((-1) ** n) / (n * np.pi) * (phi2 - phi1) * np.exp(-a * n ** 2 * np.pi ** 2 * t / L ** 2) * np.sin(n * np.pi * y / L)
#        if np.isfinite(term):
#            u_an += 2 * term
#    return u_an

def analytical_solution(t, y):
    alpha = phi1
    beta = phi2
    u_an = (beta - alpha) * y / L + alpha
    for n in range(1, 200): 
        coefficient = (beta * (-1)**n - alpha) / n
        exponent = np.exp(-((n * np.pi / L) ** 2) * a * t)
        term = (2 / np.pi) * coefficient * exponent * np.sin(n * np.pi * y / L)
        if np.isfinite(term):
            u_an += term
    return u_an


# Обчислення числового розв’язку
results = runge_kutta(u, h, T)

times = np.linspace(0, T, len(results))
y_vals = np.linspace(0, L, N)
analytical = np.array([[analytical_solution(t, y) for y in y_vals] for t in times])

#results = results[:500]

# Обчислення похибок
mae = np.max(np.abs(results - analytical))
mse = np.mean((results - analytical) ** 2)

print(f'MAE = {mae:.4f} °C')
print(f'MSE = {mse:.4f} °C^2')

# Візуалізація 3D
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')
T_mesh, Y_mesh = np.meshgrid(times / 3600, y_vals)

ax.plot_surface(T_mesh, Y_mesh, results.T, cmap='viridis', alpha=0.7)
ax.plot_surface(T_mesh, Y_mesh, analytical.T, cmap='plasma', alpha=0.5)

ax.set_xlabel('Час (год)')
ax.set_ylabel('Товщина стінки (м)')
ax.set_zlabel('Температура (°C)')
plt.title('Числовий vs Аналітичний розв\'язок')
plt.show()
