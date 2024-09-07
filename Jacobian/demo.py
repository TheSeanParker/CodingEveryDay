# coding:utf-8
import matplotlib.pyplot as plt
import numpy as np

x00=2.00
xnew=10.00
arr_xnew=[]
arr_x00=[]
for i in range(100):
     xnew=(x00/2.00+1/x00)*(-1.00)
     arr_xnew.append(xnew)
     x00=x00+xnew
     arr_x00.append(x00)
print('===arr_xnew====',arr_xnew)
print('===x00====',x00)

plt.xlabel('num'); 
plt.ylabel('arr_x00')
plt.plot(arr_x00)
plt.show()


plt.legend() 
plt.xlabel('num'); 
plt.ylabel('arr_xnew')
plt.plot(arr_xnew)
plt.show()

