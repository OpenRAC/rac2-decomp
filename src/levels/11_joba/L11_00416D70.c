#include "common.h"

typedef int Vector __attribute__((mode(TI)));
extern float D_L11_001B0DA0[4] __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_0029EFD0(int);
extern void func_0029FCC0(char *, int, char *);
extern void func_00283098(void *, void *, void *);
extern void func_002A0F48(char *);
extern void func_002AB028(void *);
extern void func_002A10E8(char *);
extern int func_002B3868(char *);
extern int func_00282978(void *);
extern void func_L11_00417340(char *);

typedef struct { char pad[0x48]; float f48; } Obj48;
extern int D_L11_001B0D90 __attribute__((sda));
extern float D_L11_001B0D94 __attribute__((sda));
extern int D_L11_001B0D98 __attribute__((sda));

/* Runs a sliding gate with a child part attached to it: it plays open and close animations, moves a little, and keeps the child part in place on it. */
void func_L11_00416D70(char *self) {
    float offset[4] __attribute__((aligned(16)));
    /* Separate initial and final query events use four measured local vectors. */
    float updated[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float transformed[4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    Vector *source;
    Vector *destination;
    int i;
    qcopy(offset, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(int *)(state + 0x10) = 0;
        *(int *)(state + 0x14) = 0;
        *(int *)(state + 0x18) = 0;
        SetMobyState(self, 2, -1);
        if (*(unsigned char *)(self + 0x43) != 0) StartAnimationBlended(self, 0, 0, 0);
        ((Obj48 *)self)->f48 = 0.0f;
        vec_scale_to_length(updated, self + 0xD0, D_L11_001B0D94);
        FastVecAdd(self + 0x10, self + 0x10, updated);
        qcopy(state, self + 0x10);
        *(char **)(state + 0x1C) = CreateMoby(0x1172 /* moby class 4466 */);
        if (*(char **)(state + 0x1C) == 0) return;
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 0x41;
        *(unsigned char *)(*(char **)(state + 0x1C) + 0x30) = *(unsigned char *)(self + 0x30);
        *(short *)(*(char **)(state + 0x1C) + 0x32) = 0;
        TransformMobyJointToWorld(self, 0, (char *)position);
        matrix_mul_vec3(transformed, D_L11_001B0DA0, self + 0xC0);
        FastVecAdd(position, transformed, position);
        {
            char *child = *(char **)(state + 0x1C);
            qcopy(child + 0x10, position);
            func_002A0F48(child);
        }
        {
            Vector *row = (Vector *)(self + 0xC0);
            Vector *out = (Vector *)(*(char **)(state + 0x1C) + 0xC0);
            int count = 0;
            do {
                qcopy(out, row);
                count++;
                row++;
                out++;
            } while (count < 3);
        }
        NormalizeMatrixColumns(*(char **)(state + 0x1C) + 0xC0);
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
        break;
    case 1:
        if (SetFirstPendingFlag(self)) *(short *)(state + 0x22) = D_L11_001B0D98;
        if (!FastDecTimer(state + 0x22)) {
            vec_scale_to_length(updated, self + 0xD0, D_L11_001B0D94 / (float)D_L11_001B0D98);
            FastVecAdd(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            qcopy(self + 0x10, state);
            ((Obj48 *)self)->f48 = 0.0f;
            SetMobyState(self, 2, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) *(short *)(state + 0x22) = D_L11_001B0D98;
        if (!FastDecTimer(state + 0x22)) {
            vec_scale_to_length(updated, self + 0xD0, -D_L11_001B0D94 / (float)D_L11_001B0D98);
            FastVecAdd(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            ((Obj48 *)self)->f48 = 0.0f;
            SetMobyState(self, 4, -1);
        }
        break;
    case 4:
        SetMobyState(self, 5, -1);
        ((Obj48 *)self)->f48 = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 1) StartAnimationBlended(self, 1, 0, 0);
        PlaceAndInitChildMobys(self);
        break;
    case 5:
        if (*(unsigned char *)(self + 0x60) & 2) {
            *(short *)(state + 0x20) = D_L11_001B0D90;
            ((Obj48 *)self)->f48 = 0.0f;
            SetMobyState(self, 6, -1);
        }
        break;
    case 6:
        if (!*(short *)(state + 0x20)) {
        ((Obj48 *)self)->f48 = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 2) StartAnimationBlended(self, 2, 0, 0);
        SetMobyState(self, 7, -1);
        } else {
            FastDecTimer(state + 0x20);
        }
        break;
    case 7:
        if (*(unsigned char *)(self + 0x60) & 2) {
            if (*(unsigned char *)(self + 0x43) != 3) StartAnimationBlended(self, 3, 0, 0);
            SetMobyState(self, 1, -1);
        }
        break;
    }
    if (*(char **)(state + 0x1C) && ((Obj48 *)self)->f48 != 0.0f) {
        TransformMobyJointToWorld(self, 0, (char *)updated);
        matrix_mul_vec3(position, D_L11_001B0DA0, self + 0xC0);
        FastVecAdd(updated, position, updated);
        {
            char *child = *(char **)(state + 0x1C);
            qcopy(child + 0x10, updated);
            func_002A0F48(child);
        }
        {
        char *childMatrix = *(char **)(state + 0x1C);
        source = (Vector *)(self + 0xC0);
        destination = (Vector *)(childMatrix + 0xC0);
        for (i = 0; i < 3; i++) {
            *destination = *source;
            source++;
            destination++;
        }
        NormalizeMatrixColumns(childMatrix + 0xC0);
        }
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
    }
}
