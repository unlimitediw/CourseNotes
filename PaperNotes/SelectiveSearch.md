[Link](//ivi.fnwi.uva.nl/isis/publications/2013/UijlingsIJCV2013/UijlingsIJCV2013.pdf)
> What it want to do?

* combine exhaustive search, segmentation and data-driven selective search.
* Goal: generate a class-independent, data-driven, selective search strategy that generates a small set of high quality object locations.
* Research questions:
  * What are good diversification strategies for adapting segmentation as a selective search strategy?
  * How effective is selective search in creating a small set of high quality locations within an image?
  * Can we use selective search to employ more powerful and appearance models for object recognition?
  

> Relative Work

* Exhaustive Search
  * Most of sliding window techniques use a coarse search grid and fixed aspect ratios, using weak classifiers and economic image features such as HOG.
  * Part-based object localisation method: [performs an exhaustive search using a linear SVM and HOG features](http://cs.brown.edu/people/pfelzens/papers/lsvm-pami.pdf).
  * Use the appearance model to guide the search which reduce the constraints of using regular grid and the number of locations visited by the branch and bound technique.

* Segmentation
  * Generate a set of class independent object hypotheses using segmentation and rank the semgments. 

> Selective Search

* Caputure All Scales, Diversification and Fast to Compute.
* Hierachical Grouping Algorithm:
#
    Input: (colour) image
    Output: Set of object location hypotheses L
    
    Obtain initial regions R = {r1, ... ,rn} using efficient graph based image segmentation
    Initialise similarity set S = Nan
    foreach Neighbouring region (ri, rj):
      Calculate similarity s(ri, rj)
      S = S and s(ri, rj)
    while S != Nan:
      Get highest similarity s(ri,rj) = max(S)
      Merge corresponding regions rt = ri and rj
      Remove similarities regarding ri: S = S\s(ri,r*) (for all)
      Remove similarities regarding rj: S = S\s(r*,rj)
      Calculate sirtmilarity set St between rt and its neighbours S = S and St, R = R and rt
      
    Extract object location boxes L from all regions in R
    
