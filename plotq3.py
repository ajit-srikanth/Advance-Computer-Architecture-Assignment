import matplotlib.pyplot as plt
import numpy as np

l1_s = [128, 128, 128, 128, 128, 256, 256, 256, 256, 256, 512, 512, 512, 512, 1024, 1024, 1024, 2048, 2048, 4096]
l2_s = [256, 512, 1024, 2048, 4096, 256, 512, 1024, 2048, 4096, 512, 1024, 2048, 4096, 1024, 2048, 4096, 2048, 4096, 4096]
r = [0.8, 0.674, 0.508, 0.508, 0.508, 0.805, 0.637, 0.42, 0.42, 0.42, 0.164, 0.164, 0.164, 0.164, 0.004, 0.004, 0.004, 0.004, 0.004, 0.004]

l1_unique = np.unique(l1_s)
l2_unique = np.unique(l2_s)
l1_grid, l2_grid = np.meshgrid(l1_unique, l2_unique)

r_grid = np.zeros_like(l1_grid, dtype=float)

for l1, l2, r_value in zip(l1_s, l2_s, r):
    l1_index = np.where(l1_unique == l1)[0][0]
    l2_index = np.where(l2_unique == l2)[0][0]
    r_grid[l2_index, l1_index] = r_value

plt.rcParams.update({'font.size': 12})

fig = plt.figure(figsize=(12, 10))
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(l1_grid, l2_grid, r_grid, cmap='viridis', edgecolor='k')

ax.set_xlabel('L1 cache size')
ax.set_ylabel('L2 cache size')
ax.set_zlabel('Miss rate')

ax.set_zlim(0, 1)

plt.show()
