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

* Segmentation
