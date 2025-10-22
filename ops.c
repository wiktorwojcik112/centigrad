#include "value.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

// centigrad sometimes allocates intermediate values.
// This function automatically detects them in the value and frees them.
void cg_free(Value* val) {
    if (val->prev[0] && val->prev[0]->is_alloc) {
        free(val->prev[0]); 
        val->prev[0] = NULL;
    }

    if (val->prev[1] && val->prev[1]->is_alloc) {
        free(val->prev[1]); 
        val->prev[1] = NULL;
    }
}
