import numpy as np
import operator

def TrainSet():
    fevec = np.array([[1, 101], [5, 89], [108, 5], [115, 8]])
    label = ['A', 'A', 'B', 'B']
    return fevec, label

def knn(dataSet, inX, label, k):
    n = dataSet.shape[0]
    diffMat = np.tile(inX,(n, 1))- dataSet
    sqDiffMat = pow(diffMat, 2)
    sqDistance = sqDiffMat.sum(axis=1)
    dist = pow(sqDistance, 0.5)

    sortedDistIndicies = dist.argsort()
    # print(type(sortedDistIndicies))
    classCount = {}
    for i in range(k):
        voteLabel = label[sortedDistIndicies[i]]
        classCount[voteLabel] = classCount.get(voteLabel, 0) + 1
    sortedClassCount = sorted(classCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]


