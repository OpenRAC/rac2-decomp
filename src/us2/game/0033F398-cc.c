/* func_US2_0033F398, the USA v2.00 copy of func_0033E348: the same C, where rename func_00348128 becomes func_US2_00348E60. */

extern int func_US2_0033F398(int);

extern int func_US2_00348E60(unsigned char *);

/* Qwen draft (branch qwen/autonomy, 4419d477), checked by tools/check.py */
int func_US2_0033F398(int owner)
{
    return func_US2_00348E60((unsigned char *)(owner + 0x2e0));
}

extern void func_0033AE28(char *);
extern void func_0033B018(char *, float, float);
extern void func_0033AE28(char *p);
extern void func_0033B018(char *p, float x, float y);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
