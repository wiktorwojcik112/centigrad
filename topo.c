#include <stdlib.h>
#include "topo.h"

// Helper function declaration
int analyse_val(Value* val, int next_idx, Value** sorted, int size);

Value** cg_build_topo(Value *top_val) {
    int size = top_val->total_prev + 1;
    Value** sorted = malloc(sizeof(Value*) * size);
    for (int i = 0; i < size; i++) sorted[i] = NULL;
    sorted[0] = top_val;
    int next_idx = 1;
    analyse_val(top_val, next_idx, sorted, size);
    return sorted;
}

// Returns the next idx after analysing the entire tree
int analyse_val(Value* val, int next_idx, Value** sorted, int size) {
    if (next_idx != 1) {
        for (int i = 0; i < size; i++) {
            if (sorted[i] == val) return next_idx;
            if (sorted[i] == NULL) break;
        }
    }
    sorted[next_idx] = val;
    next_idx++;
    if (val->prev[0] != NULL) {
        next_idx = analyse_val(val->prev[0], next_idx, sorted, size);
    }
    if (val->prev[1] != NULL) {
        next_idx = analyse_val(val->prev[1], next_idx, sorted, size);
    }
    return next_idx;
}
