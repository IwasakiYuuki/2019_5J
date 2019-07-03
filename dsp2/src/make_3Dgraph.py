import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(7, 7))
ax = Axes3D(fig)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('YCC-Y')

data = np.genfromtxt('./data/sample.csv', delimiter=',')

# 棒の位置
X, Y = np.mgrid[0:120, 0:120]
X, Y = X.ravel(), Y.ravel()  # 1次元配列にする必要がある。
# 棒の寸法 xy 方向の長さは1で z 方向の長さはそれぞれ異なる値を指定する。
dx, dy, dz = 1, 1, np.delete(data, -1, axis=1).T.ravel()

ax.bar3d(X, Y, 0, dx, dy, dz)
plt.savefig('./data/sample_3Dgraph_y.png')
