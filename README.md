# centigrad
### A neural network library written in C

This is my attempt at writing my own neural network library. It's based on
Karpathy's micrograd and is written in C as an additional challenge. All of the
code (excluding tests) has been written without using AI.

The project is in progress. At this moment only a gradient calculation engine
is implemented. All of the implemented tests are passing at this moment.

# Docs

The central component of the library is Value - a structure representing a number.
It can be created using the ```Value cg_value(double data)``` function. Besides the
data Value stores the previous Values in the chain as well as the calculated gradient.

On these values some operations can be performed - cg_add, cg_mul, cg_pow, cg_sub,
cg_div. All of these functions accept two pointers to Values (except cg_pow which
accepts a single Value pointer and a double power). These functions automatically
store the parent values in the created value creating a tree.

To calculate gradient for each Value within a tree a special function can be
used - ```void cg_backward(Value* value)```. Given the topmost value within the
tree it will calculate gradients for each Value within the tree.


At the end, ```void cg_free(Value* val)``` should be called for each value to free
potential intermediate Values allocated by some of the operations functions.

# Roadmap
[x] Backward gradient calculation
[] Tensors, matrices + operations on them
[] Optimization algorithms builtin (Gradient Descent, etc)
[] Common ML components builtin (ReLU, convolution, etc)

By the end I plan advanced ML models to be possible to implement using centigrad
like convolution, diffusion and transformers. 
