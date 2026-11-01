#include "include_asm.h"



extern void func_PAL_L00_00390C40(char *object);
extern void func_PAL_L00_00390828(char *object);
extern float func_00283B98(float value, float step);
extern void func_PAL_L00_00390728(char *object);
extern void func_00300190(char *target, char *source);
extern void func_00300248(char *target, char *source);
extern void func_PAL_L00_003920F8(char *object);

/* Dispatches on a byte mode at object+32: mode 0 updates two float angles from a linked node and runs a follow-up call; mode 1 refreshes a 16-byte block and a node copy then calls a final update. */
void func_PAL_L00_00390540(char *object)
{
    char *s0 = object;
    unsigned char mode = *(unsigned char *)(s0 + 32);
    char *s1 = *(char **)(s0 + 104);
    float result;

    switch (mode) {
    case 0:
        if (*(int *)(s1 + 20) != 0) {
            func_PAL_L00_00390C40(s0);
        } else {
            func_PAL_L00_00390828(s0);
        }
        result = func_00283B98(*(float *)(s0 + 240), 0.04188791f);
        *(float *)(s0 + 240) = result;
        result = func_00283B98(*(float *)(s0 + 244), 0.15707967f);
        *(float *)(s0 + 244) = result;
        func_PAL_L00_00390728(s0);
        break;
    case 1:
        func_00300190((char *)(s0 + 16), (char *)(s0 + 16));
        func_00300248(s1, s1);
        func_PAL_L00_003920F8(s0);
        break;
    }
}



