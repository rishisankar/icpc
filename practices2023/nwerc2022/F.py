from sklearn import svm
import numpy as np
import matplotlib.pyplot as plt

n=int(input())
X = []
Y = []
for i in range(n):
    x1,y1,x2,y2=map(int,input().split())
    np.append
    X.append([x1,y2])
    Y.append(0)
    X.append([x2,y1])
    Y.append(1)

X=np.array(X)
Y=np.array(Y)

# Making dataset
# X = np.array([[1, 2], [2, 3], [3, 1], [4, 3]])
# Y = np.array([0, 0, 1, 1])

# Now lets train svm model
model = svm.SVC(kernel='linear', C=10.0)
model.fit(X, Y)

# Lets predict for new input
pred = model.predict(X)
bad=0
for i in range(2*n):
    if pred[i]!=Y[i]:
        bad+=1

print(X)
print(Y)
print(pred)
# print(bad)

print("possible" if bad==0 else "impossible")

# lets plot decision boundary for this
w = model.coef_[0]
b = model.intercept_[0]
x = np.linspace(1, 10)
y = -(w[0] / w[1]) * x - b / w[1]
plt.plot(x, y, 'k-')
# plot data points
plt.scatter(X[:, 0], X[:, 1], c=Y)
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.savefig('trash.png')
# plt.show()
