#include <stdio.h>
#include <math.h>
#include "../centigrad.h"

#define EPSILON 1e-6

int test_tensor_creation() {
    int shape[2] = {2, 2};
    double data[4] = {1.0, 2.0, 3.0, 4.0};
    Value t = cg_tensor(data, shape, 2);
    int pass = fabs(t.data[0] - 1.0) < EPSILON && fabs(t.data[1] - 2.0) < EPSILON && fabs(t.data[2] - 3.0) < EPSILON && fabs(t.data[3] - 4.0) < EPSILON;
    cg_free(&t);
    return pass;
}

int test_zeroes() {
    int shape[3] = {2, 2, 1};
    Value z = cg_zeroes(shape, 3);
    int total = 1;
    for (int i = 0; i < z.n_dim; i++) total *= z.shape[i];
    int pass = 1;
    for (int i = 0; i < total; i++) {
        if (fabs(z.data[i]) > EPSILON) { pass = 0; break; }
    }
    cg_free(&z);
    return pass;
}

int test_tensor_add_mul_backward() {
    int shape[2] = {2, 2};
    double a_data[4] = {1,2,3,4};
    double b_data[4] = {2,2,2,2};
    Value a = cg_tensor(a_data, shape, 2);
    Value b = cg_tensor(b_data, shape, 2);
    Value c = cg_add(&a, &b);
    Value d = cg_mul(&a, &b);

    int total = 1; for (int i = 0; i < c.n_dim; i++) total *= c.shape[i];
    int pass = 1;
    for (int i = 0; i < total; i++) {
        if (fabs(c.data[i] - (a_data[i] + b_data[i])) > EPSILON) { pass = 0; break; }
        if (fabs(d.data[i] - (a_data[i] * b_data[i])) > EPSILON) { pass = 0; break; }
    }

    cg_backward(&d);
    // for d = a * b, grad_a = b, grad_b = a
    for (int i = 0; i < total; i++) {
        if (fabs(a.grad[i] - b.data[i]) > EPSILON) { pass = 0; break; }
        if (fabs(b.grad[i] - a.data[i]) > EPSILON) { pass = 0; break; }
    }

    cg_free(&a); cg_free(&b); cg_free(&c); cg_free(&d);
    return pass;
}

int main() {
    int passed = 0;
    int total = 3;
    printf("Tensor Test 1: Tensor creation... %s\n", test_tensor_creation() ? (passed++, "PASS") : "FAIL");
    printf("Tensor Test 2: Zeroes... %s\n", test_zeroes() ? (passed++, "PASS") : "FAIL");
    printf("Tensor Test 3: Add/Mul/Backward... %s\n", test_tensor_add_mul_backward() ? (passed++, "PASS") : "FAIL");
    printf("\n%d/%d tensor tests passed.\n", passed, total);
    return passed == total ? 0 : 1;
}
