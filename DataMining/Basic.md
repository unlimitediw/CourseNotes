Topics:
* Data and Data Types: object(instance), attribute(discrete or continue variables, fields...)
  * categorical: nominal(no meaning - one hard encoding), ordinal.
  * Type of Data Sets: 
    * Record: Data that consists of a collection of records
    * Ordered: like genomic sequence, spatial temporal data
    * Graph: such as generic graph and HTML Links -> capture relation between nodes
* Data Quality
  * Noise and outliers: an invalid signal overlapping valid data
  * Missing values
    * Eliminate Data Objects
    * Estimate Missing Values
    * Ignore the Missing Value During Analysis
    * Replace with all possible values(weighted by their probabilities)
  * Duplicate data: may be from different sources(duplicate when merge)
* Data preprocessing
  * Aggregation: Combining two or more attributes into a single attribute(data reduction, change of scale, more stable)
  * Sampling: at preliminary and final, entire is too bif; if the sample is representative.
    * Simple Random Sampling: equal probability
    * Stratified sampling: split the data into several partitions, draw random samples from each partition
    * Sampling without/with replacement
  * Dimesionality Reduction: Curse of Dimensionality
    * PCA
  * Feature Subset Selection
    * Redundant features (e.g price and sales tax)
    * Irrelevant features (e.g student ID and GPA)
    * (Tech) Brute-force approach
    * (Tech) Embedded approach
    * (Tech) Filter approach
    * (Tech) Wrapper approach
  * Feature Creation: Create new features which are more efficient
    * Feature Extraction - domain specific
    * Feature Construction - combining features
    * Mapping Data to new space: e.g fourier transform, attrbute transformation like e^x, logx, mmnorm and stand~...
  * Discretization and Binarization
  * Attribute Transformation
* Similarity and dissimilarity
  * Similarity: Numerical measure of how alike two data objects are, often range in (0,1)
  * Dissimilarity: Numerical measure of how different are two data objects.
* Data exploration and visualization
* Euclidean Distance & Cosine Similarity
* Evaluating Correlation
* Data Exploration
  * Visualization and calculation to better understand characteristics of data
  * Key motivations of data exploration
    * Helping to select the right tool for preprocessing or analysis
    * Making use of human's abilities to recognize patterns: people can recognize patterns not captured by data analysis tools
  * Related to the area of EDA(Exploratory Data Analysis)
    * Clustering and anomaly detection are major areas of interest, not just exploratory
* Summary Statistics
  * Frequency - counts
  * Center - mean
  * Spread - standard deviation
  
  
