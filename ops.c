#include "value.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

Value cg_add(Value* val_1, Value* val_2) {
    int total_el = cg_compatible(val_1, val_2);

    double* sum = malloc(sizeof(double) * total_el);
    for (int i = 0; i < total_el; i++) {
        sum[i] = val_1->data[i] + val_2->data[i];    
    } 

    Value res = cg_tensor(sum, val_1->shape, val_1->n_dim);
    cg_set_parnts(res, val_1, val_2);

    res.op = ADD;

    free(sum);

    return res;
}

Value cg_mul(Value* val_1, Value* val_2) {
    int total_el = cg_compatible(val_1, val_2);

    double* mul = malloc(sizeof(double) * total_el);
    for (int i = 0; i < total_el; i++) {
        mul[i] = val_1->data[i] * val_2->data[i];    
    } 


    Value res = cg_tensor(mul, val_1->shape, val_1->n_dim);
    cg_set_parnts(res, val_1, val_2);

    res.op = MUL;

    free(mul);

    return res;
}

Value cg_pow(Value* val, double power) {
    int total_el = cg_compatible(val_1, val_2);

    double* powrd = malloc(sizeof(double) * total_el);
    for (int i = 0; i < total_el; i++) {
        powrd[i] = pow(val->data[i], power);    
    } 


    Value res = cg_tensor(powrd, val->shape, val->n_dim);
    cg_set_parnt(res, val);

    res.op = POW;

    free(powrd);

    return res;
}

Value cg_sub(Value* val_1, Value* val_2) {
    int total_el = cg_compatible(val_1, val_2);

    Value* zero = malloc(sizeof(Value));
    Value* neg_2 = malloc(sizeof(Value));

    (*zero) = cg_zeroes(val_1->shape, val_1->n_dim);
    (*neg_2) = cg_zeroes(val_1->shape, val_1->n_dim);

    zero->is_alloc = true;

    for (int i = 0; i < total_el; i++) {
        neg_2->data[i] = -val_2->data[i];
    }

    neg_2->op = ADD;

    cg_set_parnts(neg_2, zero, val_2);

    return cg_add(val_1, neg_2);
}

Value cg_div(Value* val_1, Value* val_2) {
    int total_el = cg_compatible(val_1, val_2);

    Value* inv_2 = malloc(sizeof(Value));
    (*inv_2) = cg_zeroes(val_1->shape, val_1->n_dim);

    for(int i = 0; i < total_el; i++) {
        inv_2->data[i] = 1/val_2->data[i];
    }

    inv_2->op = POW;

    inv_2->is_alloc = true;

    return cg_mul(val_1, inv_2);
}

void cg_free(Value* val) {
    if (val->prev[0] && val->prev[0]->is_alloc) {
        free(val->prev[0]); 
        val->prev[0] = NULL;
    }

    if (val->prev[1] && val->prev[1]->is_alloc) {
        free(val->prev[1]); 
        val->prev[1] = NULL;
    }

    free(val->data);
    free(val->grad);
}
