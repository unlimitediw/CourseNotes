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
* For 4D Tensor (H x W x DEPTH x N)
  * D = Heigth x Weight x Depth
  * N: Batch Size (Number of images on batch)
  * M: Number of Outputs (hidden nerons)
* Forward Propagation:
  * The input will be reshaped to (N,D) then dot product with (D,M)
  * D is just like features and H x W is the pixel
* BackPropagation:
  * All gradients have the same dimension as it's original inputs
  * regression problem is the same, but outputlayer_delta is z rather than a, other things are all same as classification problem.
  
### Relu Layer (Rectified-Linear unit Layer)
* Use this layer at the output of any linear layer (e.g FC layers or CONV layers)
* Backward:
  1. Get a mask of all elements on the input bigger than zero
  2. Multiply by dout, dx = dout * (x > 0)
* Activation layer is used to make the model non-linear
  
### Dropout Layer
* Input: Anyshape
* Parameters:
  * p: Dropout probability
  * mask: Neurons selected
  * seed: Control random function
* Use on fully connected layers or max-pooling layers (noise augmentation)
* multiply mask on both forward and backword

### Convolution Layer
* Parameters:
  * N - Batch size (number of images on the 4d tensor)
  * F - number of filters on the convolution layer 
  * kW/kH: Kernel Width/Height (Normally we use squareimages, so kW = kH
  * H/W: Image height/width (Normally H=W)
  * H'/W': Convolved image height/width (Remains the same as input if proper padding is used)
  * Stide: Number of pixels that the convolution sliding window will travel
  * Padding: Zeros added to the border of the image to keep the input and output size the same
  * Depth: Volume input depth (ie if the input is a RGB image depth will be 3)
  * Output depth: Volume output depth (same as F)
* On the forward propagation each filter will look something different on the image (convolve each input depth with a different filter)
* Back-propagation:
  * Thinking in 1d, the result is same as 2d.
  * [The position of X will not change, w window will shift. Each time window will generate a new value and shift one unit position](https://leonardoaraujosantos.gitbooks.io/artificial-inteligence/content/convolution_layer.html)
  1. dx must have the same size of X, so we need padding.
  2. dout must have the same size of Y
  3. To save programming effort we want to calculate the gradient as a convolution
  4. On dX gradient all elements are been multiplied by W so we're probably convolving W and dout
  * dx = w * dy, dw = x * dy, index is decided by the window

### Pooling layer
* Parameters:
  * Previous input parameters
  * Strides (S)
  * Pooling windows sizes (H_P,W_P)
* Reduce dimensions but not depth:
  * By have less spatial information you gain computation performance
  * Less spatial information also means less parameters, so less chance to overfit
  * You get some translation invariance
* Backward Propagation:
  * For max-pooling, the gradient with repect to the input of the max pooling layer will be a tensor make of zeros except on the places that was selected during the forward propagation.

### Batch Norm layer
* [Some Ref](https://arxiv.org/pdf/1502.03167v3.pdf)
* feature scaling make the job of gradient descent easier -> normalize the activation of every Fullyed Connected layer or Convolution layer.
* (x - empiricalMean(x))/(var(x)**0.5)
* Advantages:
  1. Improve grdient flow,used on very deep models (Resnet: Residual Networks)
  2. Allow higher learning rates
  3. Reduce dependency on initialization
  4. Gives some kind of regularization
  5. As a rule of thumb if you use Dropout + BatchNorm you don't need L2 regularization
* Force you activations (CONV, FC) to be unit standard deviation and zero mean
* Back Propagation
  * Block 1/x: dx = - (1 / (xcached^2)) x dout
  * Block sqrt(x-epsilon): dx = (1 / (2(sqrt(xcached - e))) x dout
  * Block x^2: dx = 2 x xcached x dout
  * Block summation: dx = (x / N) x dout
  
  
