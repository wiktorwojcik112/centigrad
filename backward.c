#include "value.h"
#include "topo.h"
#include <math.h>

#define NULL (void *)0

void cg_backward(Value* value) {
    Value** topo = cg_build_topo(value);

    int total_el = 1;
    for (int i = 0; i < value->n_dim; i++) {
        total_el *= value->shape[i];
    }
    
    for (int i = 0; i < total_el; i++) {
        value->grad[i] = 1;
    }

    for (int i = 1; i <= value->total_prev; i++) {
        Value* out = topo[i];

        Value* prev_1 = out->prev[0];
        Value* prev_2 = out->prev[1];

        int total_el = cg_compatible(prev_1, prev_2);

        switch (out->op) {
            case ADD:
                for (int i = 0; i < total_el; i++) {
                    prev_1->grad[i] += out->grad[i];
                    prev_2->grad[i] += out->grad[i];
                }
                break;
            case MUL:
                for (int i = 0; i < total_el; i++) {
                    prev_1->grad[i] += prev_2->data[i] * out->grad[i];
                    prev_2->grad[i] += prev_1->data[i] * out->grad[i];
                }
                break;
            case POW:
                for (int i = 0; i < total_el; i++) {
                    prev_1->grad[i] += (prev_2->data[i] * pow(prev_1->data[i], prev_2->data[i] - 1)) * out->grad[i];
                }
                break;
            case NONE:
                break;
        }
    }
}
