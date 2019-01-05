<a name="back"></a>
# Use SVM to solve Adult Census problem

1. [Project Description](#project)
2. [Dataset Preprocessing and Interpretation](#preprocessing)
3. [Linear Soft Margin SVM](#svm)
4. [Kernel SVM and Performance Imporving](#performance)


<a name="project"></a>
## Project Description


* In this exercise, I implement my own linear soft SVM with rbf, linear and polynomial kernel to solve the Adult Census Income problem. I first do the data preprocessing to abandon the rows containing '?' and select the features with highest priority as model input features. After that, I design and train my linear soft SVM model with different kernels and validate it by 10-fold-cross validation while visualize it like drawing boundary at the same time. In the model training process I also compare the performance of my model with different kernels, different hyperparameters such as 'C', 'sigma', 'tolerance' and so on. At the end. I also add the bagging methods to improve my svm model and evaluate a boosting methods to compare with svm to compare with the svm model. I finally using learning curves to show the performance for different methods.

* '>= 50k' is the same meaning as '>50k' in my project.
* [back to menu](#back)
<a name="preprocessing"></a>
## Dataset preprocessing and interpretation

There are three parts of preprocessing: data purify, dealing with discrete features and feature selection
* Data purify: removing the rows with data containing '?'

   * coding:
    
             data = data[data.occupation != '?']
             keys = data.keys()
             for key in keys:
                 if data[key].dtype != 'int64':
             data = data[data[key] != '?']
   * explanation:
      * The datatype of 'data' is 'pandas.core.frame.DataFrame' which is a csv file readed pandas. Furthermore, it provide a 'vector operation: data = data[data.occupation == target]' which allow you to keep the target data without loop it manually. In this place, the target is the data not equal to '?'. 

* Dealing with discrete features:
divide the discrete features into four parts (@unlimitediw):
  1. Correlated Feature: the feature which has some correlation in it's values. For instance, to the feature 'education', it is obviously that Preschool < Doctorate and so on.              
      * treatment: to the well-distributed integer clssificated feature, we can diretly used it as a input feature with normalization while to the high correlated data such as the education, we can convert it to well-distributed integer classified feature 'education num' in a proper weighted way.
      * types:
         * age: used directly as continous numeric variable e.g 19
         * education: changed to education num and used directly e.g 9(which is HS-grad) 
         * education num: used directly as continous numeric variable e.g 9
         * hours.per.week: used directly as continous numeric variable e.g 40
  2. Independent Feature: the feature which has no relationship in it's values such as the native country
      * treatment: 
        * It is possible to use some techinque of PCA and One hot coding to evaluate these classification features or just turn it to boolean data type.
        * Although we can not find the correlation inside of it directly, we can first do the clustering depends on the class relation with label. Forexample: to the occupation, we calculate the percentage of '>50k' of each class of occupation and rank it. After that, create a new boolean feature that takes the left half as strong occupation and the right half as the weak occupation.
      * types:
         * native country: used by one hot coding e.g  [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] as a vector variable(which is 'Yugoslavia').
         * race: same as previous
         * occupation: same as previous
  3. Boolean Feature: these kind of data is the most basic one, we don't need to do any treatment with it.
      * treatment: It is the most basic feature and we can just set the true as 1 and false as -1 and take it as input feature.
      * types:
         * sex: domain[-1,1]. 1 means male, -1 means female and used as numeric variable directly.
  4. Compound Feature: some feature is very hard to find the relation inside of it. May be some parts of it are correlated but other are not and the classification of this feature is not well-distributed.
      * treatment: Someway same as the independent features. However, there may some different since it still has some correlation inside some of it's feature classes and we may deploy the data unequally with more heuristic instruction. For instance, we can rank the feature classes based on percentage of '>=50k' and average the feature classes with transistion statUs such as 'Married-spouse-absent' and 'Married-civ-spouse' because it is too close.
      * types:
         * marital status: replace each class in the feature by the value of (proportion of #">50k"/#"<=50k" in this class) and use it as numeric value directly.
         * workclass: same as marital status

* Spilt the dataset for stratified 10-fold-cross validation.
    * coding:
    
            class KFold(object):
                def __init__(self, X, Y, foldTotal=10):
                    self.X = X
                    self.Y = Y
                    self.foldTotal = foldTotal
                    self.spiltLength = len(self.Y) // foldTotal

                def spilt(self, foldTime):
                    '''
                    It will be a little not well distributed because there is a remain for len(self.Y) // foldTotal.
                    But the remain will smaller than foldTotal and does not matter comparing with the large training set.
                    :param foldTime: the counter of spilt operation
                    :return: training data of input and label, validating
                    '''

                    validateStart = foldTime * self.spiltLength
                    validateEnd = (foldTime + 1) * self.spiltLength
                    trainX = np.concatenate((self.X[:validateStart], self.X[validateEnd:]))
                    trainY = np.concatenate((self.Y[:validateStart], self.Y[validateEnd:]))
                    validateX = self.X[validateStart:validateEnd]
                    validateY = self.Y[validateStart:validateEnd]
                    return trainX, trainY, validateX, validateY
    * Explanation:
    
        It is basically the same as 'sklearn.model_selection.KFold' but I put the data and label address inside of the class rather than just return the index outside which I believe that it will be more clear to usage. Furthermore, I don't let the KFold class to do preprocessing of spilt because it is memory cost for large size of data.

* Feature Analysis and Selection:
    * Feature unify: As previous section explained, I converted all discrete feature to continuous feature or basic boolean feature with 1 and -1 as input. Furhtermore, I will do the information gain calculation to select data first rather than normalization.
    * Information Gain ranking: 
        * coding:
            * Information Gain Calculator:
          
                    class EntropyGainHelper(object):
                        def __init__(self,Y):
                            self.Entropy = self.calEntropy(Y)

                        def calEntropy(self, Y):
                            m = len(Y)
                            typeDic = {}
                            for elem in Y:
                                if elem not in typeDic:
                                    typeDic[elem] = 1
                                else:
                                    typeDic[elem] += 1
                            res = 0
                            for key in typeDic.keys():
                                res -= typeDic[key] / m * math.log2(typeDic[key] / m)
                            return res

                        # attention: input X should be transformed to X.T previously
                        # then C = X[i]
                        def calEG(self, C, Y):
                            charTypeDic = {}
                            m = len(Y)
                            res = self.Entropy
                            for i in range(m):
                                if C[i] not in charTypeDic:
                                    charTypeDic[C[i]] = [Y[i]]
                                else:
                                    charTypeDic[C[i]].append(Y[i])
                            for key in charTypeDic.keys():
                                res -= len(charTypeDic[key])/m * self.calEntropy(charTypeDic[key])
                            return res
             * Continuous feature preprocessing:
                    
                    # feature 2, 10, 11 are fnlwgt, capital gain and capital loss respectively
                    X[2] //= 400
                    X[10] //= 2000
                    X[11] //= 2000
                
             * Feature Information Gain Visulization and Selection:
                    
                    data = df.values
                    # character selection
                    Ecal = EntropyGainGenerator.EntropyGainHelper(Y)
                    charaNameList = ['age', 'workclass', 'fnlwgt', 'education', 'educationNum', 'marital status', 'occupation',
                                     'relationship', 'race', 'sex', 'capital gain', 'capital loss', 'hours.per.week', 'native country']
                    charaEGDic = {}
                    for i in range(len(X)):
                        charaEGDic[charaNameList[i]] = Ecal.calEG(X[i], Y)
                    sort_key = sorted(charaEGDic, key=lambda x: charaEGDic[x])[::-1]
                    rankingEG = []
                    for key in sort_key:
                        rankingEG.append((key, charaEGDic[key]))
                    for val in rankingEG:
                        # print(val)
                        pass
                        
        * Explanation: 
            * For the first part: It return the information gain after slecting one feature with functions:
                * E = -sum(p * log(p))
                    * ![](https://github.com/unlimitediw/SVM/blob/master/Image/EntropyCal.PNG)
                * Gain = E - sum(featureP * featureE)
                    * ![](https://github.com/unlimitediw/SVM/blob/master/Image/InformationGain.PNG)
            * For the second part: Apart from discrete data, continuous data also need preprocessing to get the information gain. Instead of use the knowledge of integral, I simply convert it to discrete data for the convenient of information gain calculation.
            * For the third part: I use the class in first part to calculate the information gain for each feature, rank it and visualize it in next section.
        * Visulization:
            * Salary(label) distribution: 75.1% of people' salary <= 50K
                * ![](https://github.com/unlimitediw/SVM/blob/master/Image/SalaryDistribution.png)
            * Information Gain Ranking （After converting continuous data to discrete data):
                * ![](https://github.com/unlimitediw/SVM/blob/master/Image/IGRank.png)
                
            * Highest Information gain feature:
                * ![](https://github.com/unlimitediw/SVM/blob/master/Image/dataplotRelationMarried.png)
            * Education and Age data plot:
                * ![](https://github.com/unlimitediw/SVM/blob/master/Image/eduandAge.png)

        * Analysis:
            * If we simply applied information gain calculator to these features, the continuous datatype features of 'fnlwgt' and the discrete datatype 'relationship' will be the two feature with highest information gain which are 0.5806 and 0.1662. 
            * The highest discrete two information gain features are "relationship" and "married status". Nevertheless, there is no too much correlation inside the classes of it and we need to do PCA and specify scalar with these classification features. Thus, I use the more intuitionistic features with high information gain: "age" and "education num"
            * One advantage of using age and education num is that it is more intuitionistic than other features. As you can see, the adult with higher age and education num will have more chance to get a ">50k" salary.
            * We should not use continuous datatype to our information gain model because in feature selection, the entropy is not calculated on the actual attributes, but on the class label. If you wanted to find the entropy of a continuous variable, you could use Differential entropy metrics such as KL divergence, but that's not the point about feature selection. [reference](https://datascience.stackexchange.com/questions/24876/how-can-i-compute-information-gain-for-continuous-valued-attributes)
            * I do not selection the discrete feature 'relationship' because as I metion previously, there is not too much correlation inside of the classes of the feature and is not appropriate to SVM model.
            * Finally, the two features age and educationNum with entropy gain of 0.0975 and 0.0934 repspectively are the highest information gain features after removing the continuous features of 'fnlwgt', 'captial gain' and no correlated feature 'relationship' and 'marital status'
                
* [back to menu](#back)
<a name="svm"></a>
## Linear Soft Margin SVM and Kernel SVM

* p.s I implement my own solver. Please review the coding below. If you want to run and check it please visit my git and the source code is in the MLGWU folder
* Before showing my validation result and decision boundary I want to display my handwork coding for my svm training model, linear svm trainer, kernel svm trainer with some kernel functions and smo algorithm inside.
    * Train SVM Model code including linear soft svm, kernel svm with 'rbf' and 'polynomial:

            class SVM_HAND(object):
                def __init__(self, C, XSample, YSample, tolerance = .1, sigma = 3, kernel = 'rbf'):
                    self.XSample = XSample
                    self.YSample = YSample
                    self.C = C
                    self.alpha = np.zeros(YSample.shape)
                    self.b = 0
                    self.sigma = sigma
                    self.kernel = kernel
                    self.m = len(YSample)
                    self.SMO(XSample, YSample, C,tolerance = tolerance)

                def Kernel(self, xi, xj):
                    '''

                    :param xi: np.ndarray
                    :param xj: np.ndarray
                    :param sigma: the lower the sigma, the sharper the model
                    :param kernel: type of kernel
                    :return: gaussian kernel of <xi,xj>
                    '''
                    if self.kernel == 'linear':
                        return xi.dot(xj)
                    if self.kernel == 'rbf':
                        l2_square = np.sum(np.square(xi - xj), axis=-1)
                        k = -np.float64(l2_square/self.sigma ** 2)
                        return np.exp(k)
                    if self.kernel == 'polynomial':
                        return (1 + xi.dot(xj)) ** 2

                def predict(self,x):
                    kernel = self.Kernel(self.XSample, x)
                    result = np.sum(self.alpha * self.YSample * kernel) + self.b
                    return 1 if result >= 0 else -1

                def Hypo(self, x):
                    '''
                    :param alpha: the alpha i weight for sample point
                    :param yi: yi for sample point
                    :param b: threshold for solution
                    :param xi: xi for sample point
                    :param xj: xj for input data
                    :return: yj for predict result
                    '''

                    kernel = self.Kernel(self.XSample, x)
                    result = np.sum(self.alpha * self.YSample * kernel) + self.b
                    return result

                def LHBound(self, yi, yj, alphai, alphaj, C):
                    '''

                    :param yi: label for sample data
                    :param yj: label for input data
                    :param alphai: training alphai
                    :param alphaj: training alphaj
                    :param C:
                    :return:
                    '''
                    if yi != yj:
                        L = max(0, alphaj - alphai)
                        H = min(C, C + alphaj - alphai)
                    else:
                        L = max(0, alphai + alphaj - C)
                        H = min(C, alphai + alphaj)
                    return L, H

                def Eta(self, xi, xj):
                    return 2 * self.Kernel(xi, xj) - self.Kernel(xi, xi) - self.Kernel(xj, xj)

                def AlphaJUpdate(self, alphaJOld, yj, Ei, Ej, eta, H, L):
                    alphaJNew = alphaJOld - yj * (Ei - Ej) / eta
                    if alphaJNew > H:
                        return H
                    elif alphaJNew < L:
                        return L
                    else:
                        return alphaJNew

                def AlphaIUpdate(self, alphaIOld, alphaJOld, alphaJNew, yi, yj):
                    return alphaIOld + yi * yj * (alphaJOld - alphaJNew)

                def BUpdate(self, bOld, Ei, Ej, xi, xj, yi, yj, alphaINew, alphaJNew, alphaIOld, alphaJOld):
                    b1 = bOld - Ei - yi * (alphaINew - alphaIOld) * self.Kernel(xi, xi) - yj * (
                            alphaJNew - alphaJOld) * self.Kernel(xi, xj)
                    if 0 < alphaINew < self.C:
                        return b1
                    b2 = bOld - Ej - yi * (alphaINew - alphaIOld) * self.Kernel(xi, xj) - yj * (
                            alphaJNew - alphaJOld) * self.Kernel(xj, xj)
                    if 0 < alphaJNew < self.C:
                        return b2
                    else:
                        return (b1 + b2) / 2

                def SMO(self, XSample, YSample, C, tolerance=.1, maxPasses=5):
                    '''
                    :param C:
                    :param tolerance:
                    :param maxPasses:
                    :param XSample:
                    :param YSample:
                    :param X:
                    :param sigma:
                    :param kernelT:
                    :return: alpha
                    '''
                    passes = 0
                    self.m = len(YSample)
                    while passes < maxPasses:
                        num_changed_alphas = 0
                        for i in range(self.m):
                            # Calculate Ei using f(xi) - y(i)
                            hypoI = self.Hypo(self.XSample[i])
                            Ei = hypoI - YSample[i]
                            if (YSample[i] * Ei < -tolerance and self.alpha[i] < C) or (
                                    YSample[i] * Ei > tolerance and self.alpha[i] > 0):
                                # Randomly select a j != i
                                j = i
                                while i == j:
                                    j = np.random.randint(1, self.m)
                                # Calculate Ej using f(xj) - y(j)
                                hypoJ = self.Hypo(self.XSample[j])
                                Ej = hypoJ - YSample[j]
                                # Memo old alpha
                                alphaIOld = self.alpha[i]
                                alphaJOld = self.alpha[j]
                                # Compute L and H
                                L, H = self.LHBound(YSample[i], YSample[j], alphaIOld, alphaJOld, C)
                                if L == H:
                                    continue
                                # Compute eta
                                eta = self.Eta(XSample[i], XSample[j])
                                if eta >= 0:
                                    continue
                                # Compute and clip new value for alphaj using
                                self.alpha[j] = self.AlphaJUpdate(alphaJOld,YSample[j],Ei,Ej,eta,H,L)
                                if self.alpha[j] > H:
                                    self.alpha[j] = H
                                elif self.alpha[j] < L:
                                    self.alpha[j] = L
                                if abs(self.alpha[j] - alphaJOld) < 10 ^ -5:
                                    continue
                                # Determine value for alphai
                                self.alpha[i] = self.AlphaIUpdate(alphaIOld,alphaJOld,self.alpha[j],YSample[i],YSample[j])
                                # Compute b
                                self.b = self.BUpdate(self.b, Ei, Ej, XSample[i], XSample[j], YSample[i], YSample[j], self.alpha[i],
                                                 self.alpha[j],
                                                 alphaIOld, alphaJOld)
                                num_changed_alphas += 1
                        print(num_changed_alphas,passes)
                        if num_changed_alphas == 0:
                            passes += 1
                        else:
                            passes = 0

    * validate the svm model with 10-fold-cross-validation 
        * part of model and prediction accuracy generation:
        
                dataset = KF.KFold(X, Y)
                totalAccuracy = 0
                for i in range(10):
                    trainX, trainY, validateX, validateY = dataset.spilt(i)
                    C = 0.3
                    SVM_SAMPLE = SH.SVM_HAND(C, trainX, trainY, tolerance=0.1, kernel='rbf')
                    localAccuracy = validate(validateX, validateY, SVM_SAMPLE)
                    print("local Accuracy for", i, "time:", format(localAccuracy, '.3f'))
                    totalAccuracy += localAccuracy
                totalAccuracy /= 10
                print(format(totalAccuracy, '.3f'))

                plotData()
                plotBoundary(SVM_SAMPLE, 0, 100, 0, 20)
                
        * part of 10-fold-cross-validation:
        
                class KFold(object):
                    def __init__(self, X, Y, foldTotal=10):
                        self.X = X
                        self.Y = Y
                        self.foldTotal = foldTotal
                        self.spiltLength = len(self.Y) // foldTotal

                    def spilt(self, foldTime):
                        '''
                        It will be a little not well distributed because there is a remain for len(self.Y) // foldTotal.
                        But the remain will smaller than foldTotal and does not matter comparing with the large training set.
                        :param foldTime: the counter of spilt operation
                        :return: training data of input and label, validating
                        '''

                        validateStart = foldTime * self.spiltLength
                        validateEnd = (foldTime + 1) * self.spiltLength
                        trainX = np.concatenate((self.X[:validateStart], self.X[validateEnd:]))
                        trainY = np.concatenate((self.Y[:validateStart], self.Y[validateEnd:]))
                        validateX = self.X[validateStart:validateEnd]
                        validateY = self.Y[validateStart:validateEnd]
                        return trainX, trainY, validateX, validateY

* Result and Analysis:
    * Accuracy:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearValidateAcc.png)
    * Support Vectors:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearSupportVectors.png)
    * Decision Boundary:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearDecisionBoundary.png)

    * In this problem I select age and education num to make the visualization more intuitionistic and use 10-fold validation and data ramdomlize to relieve the overfitting problem.
    
* Change C and evaluate model:
    * Relationship between C and SVM performance:
        * SVM perfomance relationship with C value in linear svm model is really not obvious. Generally speaking, though, Larger C means the SVM model will be more strict and has less error point. However, the C value will only affect the performance in this model slightly.
        * To this kaggle data source, the age and education num features in data is not highly related to the C value in the linear svm model. However, in the svm model with 'rbf' kernel and 'polynomial' kernel, it affect the performance seriously. In 'rbf' kernel, higher C will make the boundary more strict and special which will generate many small boundary for particific area. In polynomial model, higher or lower C will even make the boudary out of the data area.
        * Generally speaking, the larger C value means that the model is more strict and will not allow more error points.
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/Crelationship.png)
        
    * decision boudary with smaller C 0.01:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearCp01.png)
    * decision boudary with medium C 1:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearC1.png)
    * decision boundary with larger C 3:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearCp03.png)
    

* Train SVM using all features:
    * part 1:
      * More about feature preprocessing: For the calssification type feature, I want to use one hard coding to define the discrete features. However, in this project, more features is still a disaster so I can only a little bunch of data and some important features to train and test. Furthermore, for some features that have similarity I will aggregate it and simply flatten the classification data such as marital status into a series of boolean features such as Speparted[0,1], Never-married[0,1].
      * For some continuous feature such as fnlgwt and capital, standardization normalization is especially important or the other features affect will be neglected.
        * e.g
            
              Xnames = ['age','education num','hours','capital gain','capital loss','fnlwgt','sex','Never married, Divorced']
              X = [33,5,40,0,0,0.31,1,0]
    * part 2: I will also do the feature normalization with Standardization since the range of values of raw data varies widely such as capital gain. The range of all features should be normalized so that each feature contributes approximately proportionately to the final distance.
        * Scaling code:
            
                mean = np.mean(Q[i])
                std = np.std(Q[i])
                Q[i] = (Q[i] - mean) / std
        * p.s it works very well. In my multi feature SVM model and MLP model, the accuracy boost 4 to 6% with this standardization.

    * part 3: Multifeature Linear Soft SVM performance
        * It is really slow to train many features with linear soft svm since the kernel of it is X.T.dot(X) and it will take O(c * d ^ 2 * m ^ 2) to finish the model training, However to some kernel such as 'rbf', the time complexity will be only O(c * d * m ^ 2) which will be faster
        * The way to find best C: I simply run a loop with increasing of C value and train and test model in each loop to find the best C value.
    * Part 4: detemine optimal value of C
        * I use a serious of increasing C to test the performance of my multi features linear svm model. And will finally choose the C with highest performance.
        * The accuracy in relation to C:
            * ![](https://github.com/unlimitediw/SVM/blob/master/Image/Multifeature.png)
            * There is only a little improvement(less than 1%) with the usage of multi features and it is due to my pool computer performance which can not affort the parameters optimization process.
            * However, soft linear svm will cause too many error points in any way so it is reasonable.
        * The final accuracy of prediction of test data is 77.8% finally with 1500 training data and 1500 testing data.
        * My optimal C value is 0.02 in this linear soft-margin model.
        

* [back to menu](#back)
<a name="performance"></a>
## Kernel SVM and Performance Imporving

* p.s Despide of the SMO, I also implemented my own neural network model in this section
* Performance Comparision for different kernel:
    * The test data size is 814, the training data is 3000
    * '>=50k' is positive in my model.
    * Linear Kernel:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/LinearDecisionBoundary.png)
        * C value: 0.01
        * True Positive: 87
        * FalsePositive: 48
        * TrueNegative: 547
        * FalseNegative: 132
        
        * Accuracy: 0.78
        * Precision: 0.64
        * Recall: 0.40
        * F1-Score: 0.49 
        * Variance: 0.00402
        * (Sorry I can not understant what variance needed in this project So I used the variance of (TP,FP,TN,FN) at this place and will explain other variance to Grader if needed later)
    * RBF Kernel:
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/DecisionBoundary.png)
        * C value: 0.5
        * True Positive: 101
        * FalsePositive: 41
        * TrueNegative: 554
        * FalseNegative: 118
        
        * Accuracy: 0.81
        * Precision: 0.71
        * Recall: 0.46
        * F1-Score: 0.56
        * Variance: 0.00251
        
    * Polynomial Kernel
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/PolynomialBoundary.png)
        * C value: 0.000001
        * True Positive: 90
        * FalsePositive: 50
        * TrueNegative: 545
        * FalseNegative: 129
        
        * Accuracy: 0.78
        * Precision: 0.64
        * Recall: 0.41
        * F1-Score: 0.50
        * Variance: 0.00318

* Using Multi Layer Perceptron to get higher Performance.
    * feature preprocessing: 
        * pick all the numeric features as input data:
            * age, fnlwgt, education num, capital gain, capital loss, hour.per.week
        * data normalization:
            * using Standardization
    * model construction:
        * Simply construct a 2 layer neural network to solve this problem.
        * The final result is generated by a simple sigmoid function
    * coding part A(MLP):
        * Layer setting: 
            
                input_layer_size = 6  # plus 1 for X0
                hidden_layer_size = 3  # plus 1 for X0
                output_layer_size = 1  # salary
        * Method in MLP:
        
              Y_0 = Y == "<=50K"
              Y_1 = Y == ">50K"
              Y[Y_0] = 0
              Y[Y_1] = 1

              data = df.values


              from sklearn.model_selection import train_test_split

              X = X[[0,2,4,10,11,12], :]
              X = X.T
              Y = Y.astype('int')
              X = np.float64(X)

              def standarize(X):
                  X = X.T
                  for i in range(1,len(X)):
                      mean = np.mean(X[i])
                      std = np.std(X[i])
                      X[i] = (X[i] - mean) / std
                  X = X.T
              standarize(X)
              X, X_show, Y, Y_show = train_test_split(X, Y, test_size=0.8, random_state=15)
              pos = np.asarray([X_show[t] for t in range(X_show.shape[0]) if Y_show[t] == 1])
              neg = np.asarray([X_show[t] for t in range(X_show.shape[0]) if Y_show[t] == -1])

              input_layer_size = 6  # plus 1 for X0
              hidden_layer_size = 3  # plus 1 for X0
              output_layer_size = 1  # digits

              # First step: insert 1 to X
              # Second step: construct a 784,25 shape random set matrix
              # Third step: construct a 26 * 10 shape random set matrix
              # Fourth step: do the forward propagation
              # calculate the lost at the end and do backward propagation

              X = np.insert(X, 0, 1, axis=1)

              X, X_test, Y, Y_test = train_test_split(X, Y, test_size=0.1, random_state=1)

              m = len(X)
              # theta initialization
              def genRandThetas():
                  epsilon = 0.12
                  # attention, theta is at left
                  theta1_shape = (hidden_layer_size, input_layer_size + 1)
                  theta2_shape = (output_layer_size, hidden_layer_size + 1)
                  return np.random.rand(*theta1_shape) * 2 * epsilon - epsilon, np.random.rand(*theta2_shape) * 2 * epsilon - epsilon

              # if we need to use fmin_cg, we should use flattenParams and reshapeParams
              def flattenParams(Thetas):
                  flattened_list = [mytheta.flatten() for mytheta in Thetas]
                  combined = list(itertools.chain.from_iterable(flattened_list))
                  assert len(combined) == (input_layer_size+1)*hidden_layer_size + \
                                          (hidden_layer_size+1)*output_layer_size
                  return np.array(combined).reshape((len(combined), 1))


              def reshapeParams(flattened_list):
                  theta1 = flattened_list[:(input_layer_size + 1) * hidden_layer_size].reshape(
                      (hidden_layer_size, input_layer_size + 1))
                  theta2 = flattened_list[(input_layer_size + 1) * hidden_layer_size:].reshape(
                      (output_layer_size, hidden_layer_size + 1))

                  return [theta1,theta2]

              def flattenX(X):
                  train_size = len(X)
                  return np.array(X.flatten()).reshape((train_size*(input_layer_size+1),1))

              def reshapeX(X,preSize):
                  return np.array(X).reshape((preSize,input_layer_size+1))


              # Feedforward
              def propagateForward(X, Thetas):
                  # Thetas = [theta1, theta2]
                  features = X
                  z_memo = []
                  for i in range(len(Thetas)):
                      theta = Thetas[i]
                      z = theta.dot(features).reshape((theta.shape[0], 1))
                      # activation should be 0-0.5, 0.5-1
                      a = expit(z)
                      z_memo.append((z, a))
                      if i == len(Thetas) - 1:
                          return np.array(z_memo)
                      a = np.insert(a, 0, 1)  # add X0
                      features = a

              def computeCost(Thetas, X, Y, my_lambda=0.):
                  Thetas = reshapeParams(Thetas)
                  X = reshapeX(X,m)
                  total_cost = 0.
                  train_size = m
                  try:
                      for i in range(train_size):
                          cur_X = X[i]
                          cur_Y = Y[i]
                          hyper = propagateForward(cur_X.T, Thetas)[-1][1]
                          cost = - (cur_Y * np.log(hyper)) - (1 - cur_Y)*(np.log(1 - hyper))
                          total_cost += cost
                  except:
                      print("train_size should be smaller than X size")
                  total_cost = float(total_cost) / train_size

                  # avoid overfitting
                  total_reg = 0.
                  for theta in Thetas:
                      total_reg += np.sum(theta*theta)
                  total_reg *= float(my_lambda) / (2 * train_size)
                  return total_cost + total_reg


              # Backpropagation part
              def sigmoidGradient(z):
                  # expit = 1/(1+e^z)
                  # dummy is the activation layer
                  dummy = expit(z)
                  return dummy * (1 - dummy)


              def backPropagate(Thetas, X, Y, my_lambda=0.):
                  Thetas = reshapeParams(Thetas) # ccc
                  X = reshapeX(X,m)
                  train_size = m
                  Delta1 = np.zeros((hidden_layer_size, input_layer_size + 1))
                  Delta2 = np.zeros((output_layer_size, hidden_layer_size + 1))
                  for i in range(train_size):
                      cur_X = X[i]
                      cur_Y = Y[i]
                      a1 = cur_X.reshape((input_layer_size + 1, 1))
                      temp = propagateForward(cur_X, Thetas)
                      z2 = temp[0][0]
                      a2 = temp[0][1]
                      z3 = temp[1][0]
                      a3 = temp[1][1]
                      # delta is just a diff, Delta is gradient
                      delta3 = a3 - cur_Y
                      # bp should remove first X0
                      # Thetas[1].T[1:,:].dot(delta3) is the theta.dot(pre_error)
                      delta2 = Thetas[1].T[1:, :].dot(delta3) * sigmoidGradient(z2)
                      a2 = np.insert(a2, 0, 1, axis=0)
                      # Delta = (antriTri + regular)/size
                      # delat.dot(activation) + pre = new antiTri
                      # print(delta3.shape,a2.T.shape,Delta2.shape)
                      Delta1 += delta2.dot(a1.T)
                      Delta2 += delta3.dot(a2.T)
                      # Finally Delta = derivative of theta for each layer

                  D1 = Delta1 / train_size
                  D2 = Delta2 / train_size

                  # Regularization:
                  D1[:, 1:] += (my_lambda / train_size) * Thetas[0][:, 1:]
                  D2[:, 1:] += (my_lambda / train_size) * Thetas[1][:, 1:]

                  return flattenParams([D1, D2]).flatten()



              def trainNN2(X, Y, my_lambda=0.):
                  theta1, theta2 = genRandThetas()
                  f_theta = flattenParams([theta1,theta2])
                  result = scipy.optimize.fmin_cg(computeCost, x0=f_theta, fprime=backPropagate, args=(flattenX(X), Y, my_lambda),
                                                  maxiter=30, disp=True, full_output=True)
                  return reshapeParams(result[0])


              # argmax for softmax
              def predictNN(X, Thetas):
                  output = propagateForward(X, Thetas)[-1][1]
                  return 1 if output > 0.5 else 0


              def computeAccuracy(Thetas, X, Y):
                  correct = 0
                  total = X.shape[0]
                  print(X.shape)
                  for i in range(total):
                      hyper = predictNN(X[i], Thetas)
                      print(hyper,Y[i])
                      if hyper == Y[i]:
                          correct += 1
                  return "%0.1f%%" % (100 * correct / total)
              # Predict validating and testing
              learn = trainNN2(X,Y)
              print(computeAccuracy(learn,X_test,Y_test))

* Learning curve:
    * svm with rbf
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/RBFLearnCurve.png)
    * 2 layers neural network
        * ![](https://github.com/unlimitediw/SVM/blob/master/Image/MLPLearnCurve.png)

* Performance Evaluation:
    * 'rbf' kernel soft svm:
      * Explain: The performance of svm is not bad comparing to the perceptron since it project the low dimensional features into high dimensions and use soft svm which allow some acceptable error exist in the margin and keep the marigin larger by SMO algorithm.
      * Learning curve evaluation: small sample training data will let the model overfitting and perform well in the training data set but bad at test or validation set. As the training data incresing, the error of validation/test drop and the training accuracy decrease which will help us to avoid overfitting.
      
    * Logistic regression with Perceptron:
      * Explain: although logistic regression model can handle classification problem, it can only solve the linear separable data. To this complicated salary prediction data, it works very bad but it can be improved by adding multilayer which turn this problem separable by neuron network. The accuracy is nearly no improvement with only 76% and 75.1% of adults are "<50k" original.
    
    * Multiple layer Perceptron(neural network)
      * In my 2 Layers perceptron nural network. The accuracy boost from 76% as a simple perceptron to 81% which perform pretty good in this non linear separable model.
      * Explain: MLP can solve linear non separable problem very well. Except for the input nodes, each node is a neuron that uses a nonlinear activation function which will turn it becomes a strong non linear tool. MLP allows approximate solutions for extremely complex problems like fitness approximation and this adult salary problem.
    * I used 10-cross-validation and some independent test set to evaluated my MLP model.

* More about MLP advantages:
  * As you can see from the learning curve. The difference between training error and test error is always small which means that the model is not overfitting while the accuracy is maintain at a level of 81%. 
  * At the same time, although the accuracy performance is similiar to the svm model with 'rbf' kernel. There is a high possibility to improve the MLP model with more hidden layers and broading the hidden layer.

* PS: It is my SMO alogrithm implementation which is also showed previously. 

            class SVM_HAND(object):
                def __init__(self, C, XSample, YSample, tolerance = .1, sigma = 3, kernel = 'rbf'):
                    self.XSample = XSample
                    self.YSample = YSample
                    self.C = C
                    self.alpha = np.zeros(YSample.shape)
                    self.b = 0
                    self.sigma = sigma
                    self.kernel = kernel
                    self.m = len(YSample)
                    self.SMO(XSample, YSample, C,tolerance = tolerance)

                def Kernel(self, xi, xj):
                    '''

                    :param xi: np.ndarray
                    :param xj: np.ndarray
                    :param sigma: the lower the sigma, the sharper the model
                    :param kernel: type of kernel
                    :return: gaussian kernel of <xi,xj>
                    '''
                    if self.kernel == 'linear':
                        return xi.dot(xj)
                    if self.kernel == 'rbf':
                        l2_square = np.sum(np.square(xi - xj), axis=-1)
                        k = -np.float64(l2_square/self.sigma ** 2)
                        return np.exp(k)
                    if self.kernel == 'polynomial':
                        return (1 + xi.dot(xj)) ** 2

                def predict(self,x):
                    kernel = self.Kernel(self.XSample, x)
                    result = np.sum(self.alpha * self.YSample * kernel) + self.b
                    return 1 if result >= 0 else -1

                def Hypo(self, x):
                    '''
                    :param alpha: the alpha i weight for sample point
                    :param yi: yi for sample point
                    :param b: threshold for solution
                    :param xi: xi for sample point
                    :param xj: xj for input data
                    :return: yj for predict result
                    '''

                    kernel = self.Kernel(self.XSample, x)
                    result = np.sum(self.alpha * self.YSample * kernel) + self.b
                    return result

                def LHBound(self, yi, yj, alphai, alphaj, C):
                    '''

                    :param yi: label for sample data
                    :param yj: label for input data
                    :param alphai: training alphai
                    :param alphaj: training alphaj
                    :param C:
                    :return:
                    '''
                    if yi != yj:
                        L = max(0, alphaj - alphai)
                        H = min(C, C + alphaj - alphai)
                    else:
                        L = max(0, alphai + alphaj - C)
                        H = min(C, alphai + alphaj)
                    return L, H

                def Eta(self, xi, xj):
                    return 2 * self.Kernel(xi, xj) - self.Kernel(xi, xi) - self.Kernel(xj, xj)

                def AlphaJUpdate(self, alphaJOld, yj, Ei, Ej, eta, H, L):
                    alphaJNew = alphaJOld - yj * (Ei - Ej) / eta
                    if alphaJNew > H:
                        return H
                    elif alphaJNew < L:
                        return L
                    else:
                        return alphaJNew

                def AlphaIUpdate(self, alphaIOld, alphaJOld, alphaJNew, yi, yj):
                    return alphaIOld + yi * yj * (alphaJOld - alphaJNew)

                def BUpdate(self, bOld, Ei, Ej, xi, xj, yi, yj, alphaINew, alphaJNew, alphaIOld, alphaJOld):
                    b1 = bOld - Ei - yi * (alphaINew - alphaIOld) * self.Kernel(xi, xi) - yj * (
                            alphaJNew - alphaJOld) * self.Kernel(xi, xj)
                    if 0 < alphaINew < self.C:
                        return b1
                    b2 = bOld - Ej - yi * (alphaINew - alphaIOld) * self.Kernel(xi, xj) - yj * (
                            alphaJNew - alphaJOld) * self.Kernel(xj, xj)
                    if 0 < alphaJNew < self.C:
                        return b2
                    else:
                        return (b1 + b2) / 2

                def SMO(self, XSample, YSample, C, tolerance=.1, maxPasses=5):
                    '''
                    :param C:
                    :param tolerance:
                    :param maxPasses:
                    :param XSample:
                    :param YSample:
                    :param X:
                    :param sigma:
                    :param kernelT:
                    :return: alpha
                    '''
                    passes = 0
                    self.m = len(YSample)
                    while passes < maxPasses:
                        num_changed_alphas = 0
                        for i in range(self.m):
                            # Calculate Ei using f(xi) - y(i)
                            hypoI = self.Hypo(self.XSample[i])
                            Ei = hypoI - YSample[i]
                            if (YSample[i] * Ei < -tolerance and self.alpha[i] < C) or (
                                    YSample[i] * Ei > tolerance and self.alpha[i] > 0):
                                # Randomly select a j != i
                                j = i
                                while i == j:
                                    j = np.random.randint(1, self.m)
                                # Calculate Ej using f(xj) - y(j)
                                hypoJ = self.Hypo(self.XSample[j])
                                Ej = hypoJ - YSample[j]
                                # Memo old alpha
                                alphaIOld = self.alpha[i]
                                alphaJOld = self.alpha[j]
                                # Compute L and H
                                L, H = self.LHBound(YSample[i], YSample[j], alphaIOld, alphaJOld, C)
                                if L == H:
                                    continue
                                # Compute eta
                                eta = self.Eta(XSample[i], XSample[j])
                                if eta >= 0:
                                    continue
                                # Compute and clip new value for alphaj using
                                self.alpha[j] = self.AlphaJUpdate(alphaJOld,YSample[j],Ei,Ej,eta,H,L)
                                if self.alpha[j] > H:
                                    self.alpha[j] = H
                                elif self.alpha[j] < L:
                                    self.alpha[j] = L
                                if abs(self.alpha[j] - alphaJOld) < 10 ^ -5:
                                    continue
                                # Determine value for alphai
                                self.alpha[i] = self.AlphaIUpdate(alphaIOld,alphaJOld,self.alpha[j],YSample[i],YSample[j])
                                # Compute b
                                self.b = self.BUpdate(self.b, Ei, Ej, XSample[i], XSample[j], YSample[i], YSample[j], self.alpha[i],
                                                 self.alpha[j],
                                                 alphaIOld, alphaJOld)
                                num_changed_alphas += 1
                        print(num_changed_alphas,passes)
                        if num_changed_alphas == 0:
                            passes += 1
                        else:
                            passes = 0

* [back to menu](#back)

