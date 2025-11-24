#include "value.h"
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <cstdlib>

int CG_ERRNO;

// Value creators
Value cg_value(double data) {
    Value value;

    value.data = malloc(sizeof(double));
    value.grad = malloc(sizeof(double));
    value.shape = malloc(sizeof(int));
    value.n_dim = 1;
    value.data[0] = data;
    value.grad[0] = 0;
    value.shape[0] = 1;
    value.total_prev = 0;
    value.op = NONE;
    value.is_alloc = false;

    value.prev[0] = NULL;
    value.prev[1] = NULL;

    return value;
}

Value cg_tensor(double[] data, double[] shape, int n_dim) {
    Value value;

    int total_el = 1;
    value.shape = malloc(sizeof(int) * n_dim);

    for (int i = 0; i < n_dim; i++) {
        total_el *= shape[i];
        value.shape[i] = shape[i];
    }

    value.data = malloc(sizeof(double) * total_el);
    value.grad = malloc(sizeof(double) * total_el);
    value.n_dim = n_dim;

    for (int i = 0; i < total_el; i++) {
        value.data[i] = data[i];
        value.grad[i] = 0;
    }

    value.total_prev = 0;
    value.op = NONE;
    value.is_alloc = false;

    value.prev[0] = NULL;
    value.prev[1] = NULL;

    return value;
}

Value cg_zeroes(double[] shape, int n_dim) {
    int total_el = 1;
    for (int i = 0; i < n_dim; i++) {
        total_el *= shape[i];
    }

    double* data = malloc(sizeof(double) * total_el);
    for (int i = 0; i < total_el; i++) {
        data[i] = 0;
    }

    Value value = cg_tensor(data, shape, n_dim);
    free(data);

    return value;
}

void cg_set_parnt(Value* val, Value* prev_1) {
    value->total_prev = 1 + prev_1->total_prev;
    value->prev[0] = prev_1;
    value->prev[1] = NULL;
}

void cg_set_parnts(Value* val, Value* prev_1, Value* prev_2) {
    value->total_prev = 2 + prev_1->total_prev + prev_2->total_prev;
    value->prev[0] = prev_1;
    value->prev[1] = prev_2;
}

double cg_get(Value* val, int[] path, int p_len) {
    if (p_len != val->n_dim) {
        CG_ERR = -1;
        return 0;
    }

    int idx = 0;

    for (int i = 0; i < p_len; i++) {
        idx += val->shape[i] * path[i];
    }

    return val->data[idx];
}

int cg_compatible(Value* val_1, Value* val_2) {
    if (val_1->n_dim != val_2->n_dim) {
        abort();
    }

    int total_el = 1;

    for (int i = 0; i < val_1->n_dim; i++) {
        if (val_1->shape[i] != val_2->shape[i]) {
            abort();
        }

        total_el *= val_1->shape[i];
    }

    return total_el;
}
