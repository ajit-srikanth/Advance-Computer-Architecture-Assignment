import matplotlib.pyplot as plt
import numpy as np

# Data
t = [16, 32, 64, 128, 256, 512, 1024]
l1 = [0.4, 1.6, 1.8, 1.7, 3.0, 34.9, 36.0]
l2 = [0.1, 0.1, 0.0, 0.0, 0.0, 0.6, 1.6]
total = np.array(l1) + np.array(l2)


plt.figure(figsize=(10, 5))

plt.plot(t, l1, label='l1', marker='o')
plt.plot(t, l2, label='l2', marker='s')
plt.plot(t, total, label='total', marker='^')

plt.xlabel('t')
plt.ylabel('miss rate')
plt.title('l1, l2, and total against tile size')
plt.legend()
plt.show()
