#include "value.h"
#include "topo.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

void cg_backward(Value* value) {
    if (!value) return;

    Value** topo = cg_build_topo(value);

    int total_el = 1;
    for (int i = 0; i < value->n_dim; i++) {
        total_el *= value->shape[i];
    }
    
    for (int i = 0; i < total_el; i++) {
        value->grad[i] = 1;
    }

    // topo[0] is top_val, remaining entries are other nodes; total entries = value->total_prev + 1
    int entries = value->total_prev + 1;
    for (int idx = 1; idx < entries; idx++) {
        Value* out = topo[idx];
        if (!out) continue;

        Value* prev_1 = out->prev[0];
        Value* prev_2 = out->prev[1];

        if (out->op == ADD) {
            if (prev_1) {
                int el = 1; for (int i = 0; i < prev_1->n_dim; i++) el *= prev_1->shape[i];
                for (int i = 0; i < el; i++) prev_1->grad[i] += out->grad[i];
            }
            if (prev_2) {
                int el = 1; for (int i = 0; i < prev_2->n_dim; i++) el *= prev_2->shape[i];
                for (int i = 0; i < el; i++) prev_2->grad[i] += out->grad[i];
            }
        } else if (out->op == MUL) {
            if (prev_1 && prev_2) {
                int el = cg_compatible(prev_1, prev_2);
                for (int i = 0; i < el; i++) {
                    prev_1->grad[i] += prev_2->data[i] * out->grad[i];
                    prev_2->grad[i] += prev_1->data[i] * out->grad[i];
                }
            }
        } else if (out->op == POW) {
            // Assuming pow(value, scalar) only: prev_2 may be NULL or scalar stored as single element
            if (prev_1) {
                int el = 1; for (int i = 0; i < prev_1->n_dim; i++) el *= prev_1->shape[i];
                for (int i = 0; i < el; i++) {
                    // derivative d(x^p)/dx = p * x^(p-1)
                    double p = 1.0;
                    if (prev_2) p = prev_2->data[0];
                    prev_1->grad[i] += (p * pow(prev_1->data[i], p - 1.0)) * out->grad[i];
                }
            }
        }
    }

    free(topo);
}
