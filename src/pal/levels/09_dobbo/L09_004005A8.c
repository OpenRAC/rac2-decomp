#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_004005A8);

#include "common.h"
extern int D_L09_001B3620[] MACRO_ADDR;
extern int D_L09_001B3660[] MACRO_ADDR;
extern int D_L09_001B36A0[] MACRO_ADDR;
extern int D_L09_001B36E0[] MACRO_ADDR;
extern int D_L09_001B3720[] MACRO_ADDR;
extern int D_L09_001B3760[] MACRO_ADDR;
extern int D_L09_001B37A0[] MACRO_ADDR;
extern void func_002FC560(int, unsigned long long);
extern void func_L08_00389B68(int, int, unsigned long, int, unsigned long);
extern void func_00282D48(void *, void *, float);
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern int func_L02_002F1658(void);
extern float D_L09_001B37E0[16] MACRO_ADDR;
extern char D_L09_00256510[][0x60];
extern int D_L09_001B35E0[16] MACRO_ADDR;
extern unsigned char *D_L09_00255E90[16][2];
extern void func_L09_003FCA58(void *, int, int);
extern void func_PAL_L09_00400D98(int, int, void *, int, int, int, int, int);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_00282CC0(char *, char *, char *);
extern int func_002A7820(int, int);
extern void func_L09_003FBF98(char *);
extern Quad D_L09_00255F10[][4];
extern Quad D_L09_00256310[];
typedef struct {
    int x;
    int y;
} DobboLinkScreen;

/* Draws every active beam link whose bounding sphere is visible: a large and a small textured
   quad per link, with a per-link scroll offset that advances while func_L02_002F1658() is true. */
void func_PAL_L09_00400B48(char *moby)
{
    Vec sphere, midpoint;
    int i, fade, x, y, big, small;
    char *small_tex;
    DobboLinkScreen *screen = *(DobboLinkScreen **)(moby + 0x68);

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 16; i++) {
        if (!D_L09_00255E90[i][0] || !D_L09_00255E90[i][1] || D_L09_001B35E0[i] < 2)
            continue;

        func_00282CC0((char *)&midpoint, D_L09_00255E90[i][0] + 0x10, D_L09_00255E90[i][1] + 0x10);
        sphere.q = midpoint.q;
        func_00282D48(&midpoint, &sphere, 0.5f);
        sphere.f[3] = func_00282E48(D_L09_00255E90[i][0] + 0x10, D_L09_00255E90[i][1] + 0x10) * 0.5263158f;
        if (func_00283DB8(&sphere, 64.0f) == -1)
            continue;

        big = i * 2;
        small = big + 1;
        fade = D_L09_00255E90[i][0][0x23];
        if (func_L02_002F1658()) {
            D_L09_001B37E0[i] -= 0.24000001f;
            if (D_L09_001B37E0[i] <= -8.0f)
                D_L09_001B37E0[i] += 8.0f;
        }
        small_tex = D_L09_00256510[small];
        func_L09_003FCA58(D_L09_00255E90[i][0], i, fade);
        y = screen->y + 63;
        x = screen->x + 63;
        func_PAL_L09_00400D98(y, x, D_L09_00256510[big], 128, 64, fade, i, -1);
        func_PAL_L09_00400D98(y, x, small_tex, 48, 16, fade, i, func_002A7820(1, 6));
    }
    func_L08_00389B68(2, 0x47, 0x5340BUL, 0x42, 0x8000000044UL);
}


