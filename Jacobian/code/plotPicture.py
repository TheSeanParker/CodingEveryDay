# coding:utf-8
import matplotlib.pyplot as plt
import numpy as np
import math
x = np.arange(-5, 5, 0.033)        #从1到9，间隔1取点
plt.plot(x,[(math.pow(i,-1)*(-1)+math.pow(i,1)/(-2))for i in x],"gs-", label="x*x*x") #"r"为红色, "s"为方块, "-"为实线
plt.show()