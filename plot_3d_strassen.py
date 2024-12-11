import matplotlib.pyplot as plt

# Data
t = [4, 5, 6, 7, 8, 9]
n_i = [39082, 303402, 2392618, 19006506, 151521322, 1210060842]
n_r = [0.5, 0.2, 0.1, 1.6, 1.6, 26.0]
s_i = [12870766, 90055885, 630468356, 4416439131, 30921306111, 216438210165]
s_r = [0.09, 0.09, 0.11, 0.12, 0.11, 0.17]

# Plotting n_i and s_i
plt.figure(figsize=(10, 5))
plt.plot(t, n_i, label='Instruction count for 3D', marker='o')
plt.plot(t, s_i, label='Instruction count for Strassen', marker='s')
plt.xlabel('k')
plt.ylabel('Instruction count')
plt.legend()
plt.show()

# Plotting n_r and s_r
plt.figure(figsize=(10, 5))
plt.plot(t, n_r, label='Miss rate for 3D', marker='o')
plt.plot(t, s_r, label='Miss rate for Strassen', marker='s')
plt.xlabel('k')
plt.ylabel('miss rate')
plt.legend()
plt.show()
