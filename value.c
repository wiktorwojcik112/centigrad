#include "value.h"
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Value creators
Value cg_value(double data) {
    Value value;

    value.data = data;
    value.grad = 0;
    value.total_prev = 0;
    value.op = NONE;
    value.is_alloc = false;

    value.prev[0] = NULL;
    value.prev[1] = NULL;

    return value;
}

Value cg_value_p(double data, Value* prev) {
    Value value;

    value.data = data;
    value.grad = 0;
    value.total_prev = 1 + prev->total_prev;
    value.op = NONE;
    value.is_alloc = false;

    value.prev[0] = prev;
    value.prev[1] = NULL;

    return value;
}

Value cg_value_pp(double data, Value* prev_1, Value* prev_2) {
    Value value;

    value.data = data;
    value.grad = 0;
    value.total_prev = 2 + prev_1->total_prev + prev_2->total_prev;
    value.op = NONE;
    value.is_alloc = false;

    value.prev[0] = prev_1;
    value.prev[1] = prev_2;

    return value;
}

