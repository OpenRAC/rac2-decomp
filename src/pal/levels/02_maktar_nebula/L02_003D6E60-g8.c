#include "include_asm.h"

extern int D_L02_001B01E0 __attribute__((sda));
extern int D_L02_001FF6B8[];
extern float D_L02_001BA500[4];
extern int func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern void *func_002A9640(char *, int, int);
extern int func_PAL_002B1A50(char *, void *, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_L02_003DB880(char *);
extern void func_L02_003FC020(void *, void *);
extern void func_L02_003D4900(char *);
extern int func_002B3BA8(char *, int, int, int, float, float);

void func_PAL_L02_003D8388(char *self) {
    char *state = *(char **)(self + 0x68);
    char *damage;

    if (*(unsigned char *)(self + 0x20) == 0) {
        D_L02_001B01E0 = 1;
        *(unsigned char *)(state + 0x48) = func_00283CF0(15.0f);
        *(unsigned char *)(state + 0x4A) = func_00283CF0(24.0f);
        *(unsigned char *)(state + 0xD7) = 1;
        *(unsigned char *)(state + 0x29) = 1;
        *(unsigned char *)(state + 0x1F9) = 1;
        *(short *)(state + 0x32E) = 0;
        *(int *)(state + 0x310) = 0;
        *(short *)(state + 0x318) = 0;
        *(short *)(state + 0x31A) = 0;
        *(int *)(state + 0x300) = 0;
        *(float *)(state + 0x8C) = 0.006f;
        *(float *)(state + 0x94) = 5.0f;
        *(float *)(state + 0x9C) = 0.15f;
        *(float *)(state + 0xBC) = 0.25f;
        *(float *)(state + 0xB8) = 0.1f;
        *(unsigned char *)(state + 0x28) = 3;
        *(float *)(state + 0x110) = *(float *)(state + 0x90) = 3.0f;
        *(float *)(state + 0x114) = 2.0f;
        *(float *)(state + 0x11C) = *(float *)(state + 0x118) = *(float *)(state + 0x1E4) = 0.5f;
        *(float *)(state + 0x120) = 1.1344641f;
        *(float *)(state + 0x140) = 0.52359885f;
        *(float *)(state + 0x144) = 0.01f;
        *(float *)(state + 0x13C) = 0.008f;
        func_L02_003D4900(self);
    }
    if (*(unsigned char *)(self + 0x31)) {
        if (func_00282E48(self + 0x10, D_L02_001BA500) < 60.0f) {
            func_002A93B0(self);
            *(unsigned char *)(self + 0x6F) = 0x38;
        }
    }
    if (*(short *)(state + 0x330) == 0) {
        damage = func_002A9640(self, 0x10000, 0);
        if (damage) {
            if (*(unsigned char *)(self + 0x20) < 5 ||
                (*(unsigned char *)(self + 0x20) == 10 && *(short *)(state + 0x324) < 5))
                *(int *)(damage + 0x2C) = 0;
            {
                char *source = *(char **)(damage + 0x20);
                if (source) {
                    if (*(short *)(source + 0xAA) == 0xC89 || *(short *)(source + 0xAA) == 0xBFE)
                        *(float *)(damage + 0x2C) *= 0.3f;
                }
            }
            D_L02_001FF6B8[*(unsigned char *)(state + 0x37)] += (int)(*(float *)(damage + 0x2C) * 32.0f);
        }
        if (func_PAL_002B1A50(self, state + 0x60, 0)) {
            if (*(int *)(self + 0x98) == 0)
                *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            {
                char *source = *(char **)(state + 0x38);
                if (source && *(short *)(source + 0xAA) != 0x47 && *(short *)(source + 0xAA) != 0)
                    D_L02_001B01E0 = 0;
            }
            if (*(unsigned char *)(self + 0x95) == 4) {
                if (*(unsigned char *)(self + 0x43) != 16)
                    func_PAL_002A7E68(self, 16, 0, 2);
            }
            if (*(unsigned char *)(self + 0x95) == 3 && *(float *)(state + 0x20) <= 0.0f) {
                if (*(unsigned char *)(self + 0x43) != 4)
                    func_PAL_002A7E68(self, 4, 0, 2);
            }
        }
        if (*(unsigned char *)(self + 0x20) != 0 && *(unsigned char *)(state + 0x2E) == 2) {
            char *source = *(char **)(state + 0x310);
            if (source && *(unsigned char *)(source + 0x20) != 0xFE &&
                *(unsigned char *)(source + 0x20) != 0xFD && *(unsigned char *)(source + 0x20) >= 3) {
                func_L02_003DB880(source);
                func_L02_003FC020(*(void **)(self + 0xB8), *(void **)(state + 0x310));
            }
            func_L02_003D4900(self);
        }
    }
    *(short *)(state + 0x322) = func_002B3BA8(self, *(int *)(state + 0x314), 0, 0, 100.0f, 100.0f);
    *(int *)(state + 0x30C) = *(int *)(state + 0x210);
}
