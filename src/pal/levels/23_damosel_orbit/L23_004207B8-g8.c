#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern float D_L23_001B1564 __attribute__((sda));
extern void func_0029FC20(char *, int, char *);
extern void func_0029F978(char *, int, char *);
extern void func_00283898(void *, int, float);
extern float func_00283BE0(float, float);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern float func_00282DB0(char *, char *);
extern void func_00282DD8(char *, char *, char *);
extern void func_L23_00418650(char *, float);

void func_PAL_L23_004207B8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float M0[16];
    float B[4];
    float A[4];
    float C[4];
    float M2[16];
    float D[4];
    float E[4];
    float f;

    func_0029FC20(arg0, 0x22, (char *)M0);
    if (*(int *)(state + 0x604) != 0) {
        if (*(unsigned char *)(state + 0x431) == 0)
            func_0029F978(arg0, 0x22, state + 0x430);
        func_00283898(state + 0x440, 2, *(float *)(state + 0x570));
        *(float *)(state + 0x570) = func_00283BE0(*(float *)(state + 0x570), D_L23_001B1564 * 0.0003490659f);
    } else if (*(int *)(state + 0x60C) != -1) {
        func_00282CF0((char *)A, state + 0x3F0, state + 0x3E0);
        func_00282F20((char *)A, (char *)A, 10.0f);
        func_00282CC0((char *)B, (char *)A, arg0 + 0x10);
        func_L23_00418650((char *)B, 0.0f);
        func_00282CF0((char *)A, (char *)B, state + 0x3E0);
        func_00282F20((char *)A, (char *)A, 1.0f);
        func_0029FC20(arg0, *(int *)(state + 0x60C) + 1, (char *)M2);
        *(TI128 *)C = *(TI128 *)(M2 + 4);
        if (func_00282DB0((char *)C, (char *)A) < 0.95f) {
            func_00282DD8((char *)D, (char *)C, (char *)A);
            func_00282F20((char *)E, state + 0x410, 1.0f);
            if (0.0f < func_00282DB0((char *)D, (char *)E))
                f = D_L23_001B1564;
            else
                f = -D_L23_001B1564;
            if (*(unsigned char *)(state + 0x431) == 0)
                func_0029F978(arg0, 0x22, state + 0x430);
            func_00283898(state + 0x440, 2, *(float *)(state + 0x570));
            *(float *)(state + 0x570) = func_00283BE0(*(float *)(state + 0x570), -(f * 0.0003490659f));
        }
    }
}
