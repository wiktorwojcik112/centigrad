#include "value.h"
#include "topo.h"
#include <math.h>

#define NULL (void *)0

void cg_backward(Value* value) {
    Value** topo = cg_build_topo(value);
    
    value->grad = 1;

    for (int i = 1; i <= value->total_prev; i++) {
        Value* out = topo[i];

        Value* prev_1 = out->prev[0];
        Value* prev_2 = out->prev[1];

        switch (out->op) {
            case ADD:
                prev_1->grad += out->grad;
                prev_2->grad += out->grad;
                break;
            case MUL:
                prev_1->grad += prev_2->data * out->grad;
                prev_2->grad += prev_1->data * out->grad;
                break;
            case POW:
                prev_1->grad += (prev_2->data * pow(prev_1->data, prev_2->data-1)) * out->grad;
                break;
            case NONE:
                break;
        }
    }
}
