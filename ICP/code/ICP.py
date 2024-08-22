# -*- coding: UTF-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# 定义两个3D点集，这里 Q 是 target，P 是 source
P = np.empty((0, 3))
Q = np.empty((0, 3))
for i in range(10):
    for j in range(5):
        P = np.vstack((P, [i, -j, 0]))
        Q = np.vstack((Q, [i, j, 0]))
# for i in range(10):
#     P = np.vstack((P, [i, 0, 1]))
#     Q = np.vstack((Q, [0, i, 1]))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(P[:, 0], P[:, 1], P[:, 2], c='r', marker='o', label='P')
ax.scatter(Q[:, 0], Q[:, 1], Q[:, 2], c='g', marker='^', label='Q')
ax.set_title('Align before')
ax.set_xlim(0, 10)
ax.set_ylim(0, 10)
ax.set_zlim(0, 3)
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
ax.legend()
plt.show()

# 1. 计算质心
centroid_P = np.mean(P, axis=0)
centroid_Q = np.mean(Q, axis=0)
# 2. 去质心化
P_centered = P - centroid_P
Q_centered = Q - centroid_Q
# 3. 构建协方差矩阵
H = np.dot(P_centered.T, Q_centered)

# 4. SVD 分解
U, S, VT = np.linalg.svd(H)

# 5. 计算旋转矩阵
R = np.dot(VT.T, U.T)
print("旋转矩阵 R 的行列式:")
print(np.linalg.det(R))
print(R)

if np.linalg.det(R) < 0:
    VT[2, :] *= -1 
    R = np.dot(VT.T, U.T)
# 平移部分
print(np.linalg.det(R))
print(R)
t = centroid_Q - np.dot(R, centroid_P)

# 施加旋转
P_rotated = P
for i in range(len(P)):
    P_rotated[i] = np.dot(R, P[i]) + t

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(P_rotated[:, 0], P_rotated[:, 1], P_rotated[:, 2], c='r', marker='o', label='P')
ax.scatter(Q[:, 0], Q[:, 1], Q[:, 2], c='g', marker='^', label='Q')
ax.set_title('Align after')
ax.set_xlim(0, 10)
ax.set_ylim(0, 10)
ax.set_zlim(0, 3)
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
ax.legend()
plt.show()
# 检查是否需要翻转（对于反射情况）


# 平移部分
t = centroid_Q - np.dot(R, centroid_P)

# 施加旋转
P_rotated = P
for i in range(len(P)):
    P_rotated[i] = np.dot(R, P[i]) + t