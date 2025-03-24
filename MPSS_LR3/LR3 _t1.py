import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

a = 0.082e-6  
L = 0.5     
T = 140 * 3600 
N = 100       
phi1 = 11     
phi2 = 30     

delta = L / (N - 1)
h = 3
u = np.zeros(N)
u[0] = phi1
u[-1] = phi2

def dudt(u):
    dudt = np.zeros(N)
    dudt[0] = 0
    dudt[-1] = 0
    for i in range(1, N - 1):
        dudt[i] = a * (u[i - 1] - 2 * u[i] + u[i + 1]) / (delta ** 2)
    return dudt

def runge_kutta(u, h, T):
    t = 0
    results = []
    times = []
    positions = np.linspace(0, L, N) 
    while t < T:
        k1 = dudt(u)
        k2 = dudt(u + h * k1 / 2)
        k3 = dudt(u + h * k2 / 2)
        k4 = dudt(u + h * k3)
        u = u + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6
        results.append(u.copy())
        t += h
        times.append(t)
        for i in range(N):
             print(f"Час: {t / 3600:.2f} год, Відстань: {positions[i]:.4f} м, Температура: {u[i]:.2f} °C")

    return np.array(results), np.array(times)

results, times = runge_kutta(u, h, T)

fig = plt.figure(figsize=(12, 7))
ax = fig.add_subplot(111, projection='3d')

y = np.linspace(0, L, N)
X, Y = np.meshgrid(y, times[:len(results)])
Z = np.array(results)

ax.plot_surface(X, Y / 3600, Z, cmap='viridis')
ax.set_xlabel('Відстань у стінці (м)')
ax.set_ylabel('Час (години)')
ax.set_zlabel('Температура (°C)')
ax.set_title('Розподіл температури у стінці з часом')

plt.show()

# plt.figure(figsize=(10, 6))
# for i in range(0, len(results), len(results) // 10):
#     plt.plot(results[i], label=f't = {i * h / 3600:.2f} год')
# plt.xlabel('Шари')
# plt.ylabel('Температура (°C)')
# plt.title('Зміна температури у стінці')
# plt.legend()
# plt.show()
