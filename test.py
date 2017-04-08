from numpy import *

# data
def loadDataSet():
    postingList = [
        [6.00, 180, 12],
        [5.92, 190, 11],
        [5.58, 170, 12],
        [5.92, 165, 10],
        [5.00, 100, 6],
        [5.50, 150, 8],
        [5.42, 130, 7],
        [5.75, 150, 9],
    ]
    classVec = [1, 1, 1, 1, 0, 0, 0, 0]
    return postingList, classVec

# training
def trainBayes(trainMatrix, trainCategory):

    numSamples = len(trainMatrix)
    numFeatures = len(trainMatrix[0])

    pAbusive = sum(trainCategory) / float(numSamples)
    
    p0Num = ones(numFeatures); p1Num = ones(numFeatures)

    p0Denom = 2.0; p1Denom = 2.0

    for i in range(numSamples):
        if trainCategory[i] == 1:
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])
    
    p1Vect = log(p1Num / p1Denom)
    p0Vect = log(p0Num / p0Denom)
    
    return p0Vect, p1Vect, pAbusive

# classify
def classifyBayes(vec2Classify, p0Vec, p1Vec, pClass1):

    p1 = sum(vec2Classify * p1Vec) + log(pClass1)
    p0 = sum(vec2Classify * p0Vec) + log(1.0 - pClass1)
    print("p1: ", p1)
    print("p0: ", p0)
    if p1 > p0:
        return 1
    else:
        return 0

# testing
def testingBayes():

    listOfPosts, listClasses = loadDataSet()
    trainMat = listOfPosts

    numSamples = len(trainMat)
    numFeatures = len(trainMat[0])

    p0V, p1V, pAb = trainBayes(array(trainMat), array(listClasses))

    print(p0V, p1V, pAb)

    newPerson = [6.00, 130, 8]
    
    print(newPerson, "classified as: ", classifyBayes(array(newPerson), p0V, p1V, pAb))

    

testingBayes()