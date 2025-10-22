#ifndef VALUE_H_
#define VALUE_H_

#include <stdbool.h>

typedef enum { ADD, MUL, POW, NONE } Operation;
/*
 * prev - can contain less elements than 2 by using NULL pointer.
 */
typedef struct Value {
    double data;
    double grad;
    struct Value* prev[2];
    int total_prev;
    Operation op;
    bool is_alloc;
} Value;


// Value creators
Value cg_value(double data);
Value cg_value_p(double data, Value* prev);
Value cg_value_pp(double data, Value* prev_1, Value* prev_2);
#endif
