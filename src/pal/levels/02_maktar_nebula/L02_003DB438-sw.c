#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
extern float D_L02_001B03E0[4] __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
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
extern float func_00283CE0(int);
extern void func_PAL_L02_003DBA08(char *);

void func_PAL_L02_003DB438(char *self) {
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
        func_002A7750(self, 2, -1);
        if (*(unsigned char *)(self + 0x43) != 0) func_PAL_002A7E68(self, 0, 0, 0);
        *(float *)(self + 0x48) = 0.0f;
        func_00282F20(updated, self + 0xD0, 2.0f);
        func_00282CC0(self + 0x10, self + 0x10, updated);
        qcopy(state, self + 0x10);
        *(char **)(state + 0x1C) = func_0029EFD0(0x1172);
        if (*(char **)(state + 0x1C) == 0) return;
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 0x41;
        *(unsigned char *)(*(char **)(state + 0x1C) + 0x30) = *(unsigned char *)(self + 0x30);
        *(short *)(*(char **)(state + 0x1C) + 0x32) = 0;
        func_0029FCC0(self, 0, (char *)position);
        func_00283098(transformed, D_L02_001B03E0, self + 0xC0);
        func_00282CC0(position, transformed, position);
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
        func_002AB028(*(char **)(state + 0x1C) + 0xC0);
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
        break;
    case 1:
        if (func_002B3868(self)) *(short *)(state + 0x22) = 16;
        if (!func_00282978(state + 0x22)) {
            func_00282F20(updated, self + 0xD0, 2.0f / func_00283CE0(16));
            func_00282CC0(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            qcopy(self + 0x10, state);
            *(float *)(self + 0x48) = 0.0f;
            func_002A7750(self, 2, -1);
        }
        break;
    case 3:
        if (func_002B3868(self)) *(short *)(state + 0x22) = 16;
        if (!func_00282978(state + 0x22)) {
            func_00282F20(updated, self + 0xD0, -2.0f / func_00283CE0(16));
            func_00282CC0(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            *(float *)(self + 0x48) = 0.0f;
            func_002A7750(self, 4, -1);
        }
        break;
    case 4:
        func_002A7750(self, 5, -1);
        *(float *)(self + 0x48) = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 1) func_PAL_002A7E68(self, 1, 0, 0);
        func_PAL_L02_003DBA08(self);
        break;
    case 5:
        if (*(unsigned char *)(self + 0x60) & 2) {
            *(short *)(state + 0x20) = 75;
            *(float *)(self + 0x48) = 0.0f;
            func_002A7750(self, 6, -1);
        }
        break;
    case 6:
        if (!*(short *)(state + 0x20)) {
        *(float *)(self + 0x48) = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 2) func_PAL_002A7E68(self, 2, 0, 0);
        func_002A7750(self, 7, -1);
        } else {
            func_00282978(state + 0x20);
        }
        break;
    case 7:
        if (*(unsigned char *)(self + 0x60) & 2) {
            if (*(unsigned char *)(self + 0x43) != 3) func_PAL_002A7E68(self, 3, 0, 0);
            func_002A7750(self, 1, -1);
        }
        break;
    }
    if (*(char **)(state + 0x1C) && *(float *)(self + 0x48) != 0.0f) {
        func_0029FCC0(self, 0, (char *)updated);
        func_00283098(position, D_L02_001B03E0, self + 0xC0);
        func_00282CC0(updated, position, updated);
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
        func_002AB028(childMatrix + 0xC0);
        }
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
    }
}
