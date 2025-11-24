#ifndef VALUE_H_
#define VALUE_H_

#include <stdbool.h>

typedef enum { ADD, MUL, POW, NONE } Operation;
/*
 * prev - can contain less elements than 2 by using NULL pointer.
 */
typedef struct Value {
    double* data;
    double* grad;
    int[] shape;
    int n_dim;
    struct Value* prev[2];
    int total_prev;
    Operation op;
    bool is_alloc;
} Value;


// Value creators
Value cg_value(double data);
Value cg_tensor(double[] data, double[] shape, int n_dim);

// Get an element with just zeroes of the specified shape.
Value cg_zeroes(double[] shape, int n_dim);

// Set value's parent(s)
void cg_set_parnt(Value* val, Value* prev_1);
void cg_set_parnts(Value* val, Value* prev_1, Value* prev_2);

// Get the value at the specified path
double cg_get(Value* val, int[] path, int p_len);

// Aborts if the values are incompatible (non-matching shape). Otherwise, returns
// the number of elements in a single value.
int cg_compatible(Value* val_1, Value* val_2);
#endif
