#include <stdio.h>
#include <math.h>
#include "../centigrad.h"

#define EPSILON 1e-6

int test_value_creation() {
    Value v = cg_value(2.0);
    int pass = fabs(v.data[0] - 2.0) < EPSILON;
    cg_free(&v);
    return pass;
}

int test_basic_add() {
    Value a = cg_value(2.0);
    Value b = cg_value(3.0);
    Value c = cg_add(&a, &b);
    int pass = fabs(c.data[0] - 5.0) < EPSILON;
    cg_free(&a); cg_free(&b); cg_free(&c);
    return pass;
}

int test_basic_mul() {
    Value a = cg_value(2.0);
    Value b = cg_value(3.0);
    Value c = cg_mul(&a, &b);
    int pass = fabs(c.data[0] - 6.0) < EPSILON;
    cg_free(&a); cg_free(&b); cg_free(&c);
    return pass;
}

int test_backward_simple() {
    Value a = cg_value(2.0);
    Value b = cg_value(3.0);
    Value c = cg_mul(&a, &b);
    cg_backward(&c);
    int pass = fabs(a.grad[0] - 3.0) < EPSILON && fabs(b.grad[0] - 2.0) < EPSILON;
    cg_free(&a); cg_free(&b); cg_free(&c);
    return pass;
}

int main() {
    int passed = 0;
    int total = 4;
    printf("Test 1: Value creation... %s\n", test_value_creation() ? (passed++, "PASS") : "FAIL");
    printf("Test 2: Basic add... %s\n", test_basic_add() ? (passed++, "PASS") : "FAIL");
    printf("Test 3: Basic mul... %s\n", test_basic_mul() ? (passed++, "PASS") : "FAIL");
    printf("Test 4: Backward simple... %s\n", test_backward_simple() ? (passed++, "PASS") : "FAIL");
    printf("\n%d/%d tests passed.\n", passed, total);
    return passed == total ? 0 : 1;
}
