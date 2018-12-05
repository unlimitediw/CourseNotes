# Deep Learning
* [Reference](https://leonardoaraujosantos.gitbooks.io/artificial-inteligence/content/)
### Convolution Neural Network
> normal pattern 'CONV -> ReLU -> Pool -> Conv -> ReLU -> Pool -> FC -> Softmax_loss]
* Convolution layer Hyper parameters:
  * Kernel size(K): Small is better -> but if is on the first layer, takes a lot of memory
  * Stride(S): How many pixels the kernel window will slide
  * Zero Padding(pad): Put zeros on the image border to allow the conv output size be the same as the input size(F = 1, PAD = 0; F = 3, PAD = 1; F = 5, PAD = 2; F = 7, Pad = 3)
  * Number of filters(F): Number of patterns that the conv layer will look for.
* Number of parameters (weights)(example)
  * input: 32 x 32 x 3 (RGB image)
  * CONV:
    * Kernel(F): 5 x 5, Stride:1, Pad:2, numFilters:10
* Amount of memory:
  * Input 32 x 32 x 3 = 3K
  * C1: 32 x 32 x 10 = 10K
  * P1 = ...

### Fully Connected Layer
*
