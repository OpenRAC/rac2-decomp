#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_004033A8);



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00403780);


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_004040D8);


#include "common.h"
extern void func_002A7750(char *arg, int mode, int value);
extern void func_PAL_L00_004040D8(char *arg);
extern void func_PAL_L00_004041C0(char *arg);
extern float func_00282E80(char *arg, char *table);
extern float func_00282C48(float value);
extern void func_PAL_002B1588(int arg, int value);
extern void func_00288308(int arg);
extern void func_002AD860(int arg);
extern void func_0029F338(char *arg);
extern char D_00189EA0_2[];
extern unsigned char D_001A7B2E __attribute__((sda));
extern void func_002E6EF8(void (*f)(char *), char *arg);

/* two-state update on a record: state 0 marks a byte with 255 and either runs a shared two-call teardown when a global latch byte is set and a sub-object field is non-zero, or plays a mode/value pair plus a call; state 1 runs a setup call and two float queries against a stored table and, when both are below 2.0, plays three fixed calls and either tears down or writes 120 into a sub-object field */
void func_PAL_L00_004043A0(char *arg)
{
    int *object = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);

    switch (state) {
    case 0:
        *(unsigned char *)(arg + 48) = 255;
        if (D_001A7B2E != 0 && object[17] != 0) {
            func_0029F338((char *)object[17]);
            func_0029F338(arg);
            return;
        } else {
            func_002A7750(arg, 1, -1);
            func_PAL_L00_004040D8(arg);
        }
        break;
    case 1:
        func_PAL_L00_004041C0(arg);
        if (func_00282E80(arg + 16, D_00189EA0_2) < 2.0f) {
            if (func_00282C48(*(float *)(arg + 24) - *(float *)(D_00189EA0_2 + 8)) < 2.0f) {
                func_PAL_002B1588(4658, -1);
                func_00288308(54);
                func_002AD860(54);
                if (object[17] != 0) {
                    func_0029F338((char *)object[17]);
                    func_0029F338(arg);
                    return;
                }
                object[16] = 100;
            }
        }
        break;
    }
}


