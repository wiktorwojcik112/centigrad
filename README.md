# centigrad
### A neural network library written in C

This is my attempt at writing my own neural network library. It's based on
Karpathy's micrograd and is written in C as an additional challenge. All of the
code (excluding tests) has been written using minimal help from AI.

The project is in progress. At this moment only basic tensor operations and 
a gradient calculation engine is implemented. All of the implemented tests are
passing at this moment.

# Docs

## Value
The central component of the library is Value - a structure representing a tensor.
Besides the data Value stores the previous Values in the chain as well as the
calculated gradient.


## Creating values
There are two main ways to create Value.


This one creates a value containing just a single number.
```c
Value cg_value(double data)
```

And this one creates a tensor of the specified shape. The data is just a simple
array of all the values arranged linearly. The shape is decided by the shape
argument which should be an array with n_dim elements representing count of
elements in each dimension (for example, "2, 3" would be a 2x3 matrix).
```c
Value cg_tensor(double* data, int* shape, int n_dim)
```

To simplify the process there is also ```Value cg_zeroes(int* shape, int n_dim)```
which creates a tensor with just zeroes of the specified shape.

## Operations
On these values some operations can be performed - cg_add, cg_mul, cg_pow, cg_sub,
cg_div. All of these functions accept two pointers to Values (except cg_pow which
accepts a single Value pointer and a double power). All of them are element-wise
which also requires all the tensors to have the same shape at the moment. These
functions automatically store the parent values in the created value
creating a tree.

To calculate gradient for each Value within a tree a special function can be
used - ```void cg_backward(Value* value)```. Given the topmost value within the
tree it will calculate gradients for each Value within the tree.


At the end, ```void cg_free(Value* val)``` should be called for each value to free.

# Roadmap
[x] Backward gradient calculation
[x] Tensors, matrices
[] Matrix-specific operations
[] Optimization algorithms builtin (Gradient Descent, etc)
[] Common ML components builtin (ReLU, convolution, etc)

By the end I plan advanced ML models to be possible to implement using centigrad
like convolution, diffusion and transformers. 
