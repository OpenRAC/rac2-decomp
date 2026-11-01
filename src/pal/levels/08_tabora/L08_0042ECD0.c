#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L08_0042ECD0);

#include "common.h"
extern float D_L08_001B3A20[] __attribute__((sda));
extern int D_L08_001B3A30[] __attribute__((sda));
extern int D_L08_001B39A0[] __attribute__((sda));
extern char D_L08_002604A0[];
extern void func_002FC560(int, u64);
extern int func_L02_002F1658(void);
extern void func_L08_0042A980(int, int);
extern void func_L08_0042A0B0(int, int, void *, int, int, int, int);
extern int func_002A7820(int, int);
extern void func_L08_00389B68(int, int, u64, int, u64);

/* The spawner's per-frame draw callback: each live slot past state 1 scrolls its phase
   (wrapping at -8) and has its two 0x140-byte strips drawn. */
void func_PAL_L08_0042F658(char *a) {
    char *q = *(char **)(a + 0x68);
    int i;

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 3; i++) {
        float *phase = &D_L08_001B3A20[i];
        int j, k, x, y;
        char *p;

        if (!D_L08_001B3A30[i] || D_L08_001B39A0[i] < 2) continue;
        j = i * 2;
        k = j + 1;
        if (func_L02_002F1658()) {
            *phase -= 0.24000001f;
            if (*phase <= -8.0f) *phase += 8.0f;
        }
        p = D_L08_002604A0 + k * 0x140;
        func_L08_0042A980(D_L08_001B3A30[i], i);
        y = *(int *)(q + 4) + 63;
        x = *(int *)q + 63;
        func_L08_0042A0B0(y, x, D_L08_002604A0 + j * 0x140, 128, 64, i, -1);
        func_L08_0042A0B0(y, x, p, 48, 16, i, func_002A7820(1, 20));
    }
    func_L08_00389B68(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}

