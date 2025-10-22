#include "value.h"
#include <stddef.h>
#include <math.h>
#include <stdlib.h>

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

// ops
Value cg_add(Value* val_1, Value* val_2) {
    Value res = cg_value_pp(val_1->data + val_2->data, val_1, val_2);
    res.op = ADD;
    return res;
}

Value cg_mul(Value* val_1, Value* val_2) {
    Value res = cg_value_pp(val_1->data * val_2->data, val_1, val_2);
    res.op = MUL;
    return res;
}

Value cg_pow(Value* val, double power) {
    Value res = cg_value_p(pow(val->data, power), val);
    res.op = POW;
    return res;
}

Value cg_sub(Value* val_1, Value* val_2) {
    Value* zero = malloc(sizeof(Value));
    Value* neg_2 = malloc(sizeof(Value));

    zero->data = 0;
    zero->grad = 0;
    zero->op = NONE;
    zero->total_prev = 0;
    zero->prev[0] = NULL;
    zero->prev[1] = NULL;
    zero->is_alloc = true;

    neg_2->data = -val_2->data;
    neg_2->grad = 0;
    neg_2->op = ADD;
    neg_2->total_prev = 2 + val_2->total_prev;
    neg_2->prev[0] = zero;
    neg_2->prev[1] = val_2;

    return cg_add(val_1, neg_2);
}

Value cg_div(Value* val_1, Value* val_2) {
    Value* inv_2 = malloc(sizeof(Value));

    inv_2->data = 1/val_2->data;
    inv_2->grad = 0;
    inv_2->op = POW;
    inv_2->total_prev = 0;
    inv_2->prev[0] = NULL;
    inv_2->prev[1] = NULL;
    inv_2->is_alloc = true;

    return cg_mul(val_1, inv_2);
}

