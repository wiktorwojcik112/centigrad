#ifndef OPS_H_
#define OPS_H_

Value cg_add(Value* val_1, Value* val_2);
Value cg_mul(Value* val_1, Value* val_2);
Value cg_pow(Value* val, double power);
Value cg_sub(Value* val_1, Value* val_2);
Value cg_div(Value* val_1, Value* val_2);

void cg_free(Value* val);
#endif
