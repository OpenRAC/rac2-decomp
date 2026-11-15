#include "common.h"
extern int func_00283CF0(float);
extern int D_001A7350[] __attribute__((sda)), D_001A7354[] __attribute__((sda));
typedef union { int *p; int address; } PacketCursor;
extern PacketCursor D_L05_001B2C88[] __attribute__((sda));
extern char D_L05_001ACA80[];
/* RAC1 counterpart: append_subpixel_textured_screen_quad (src/game/draw.c). */
void func_L05_003008C0(float x, float y, float w, float h, int u, int v, int uw, int vh,
                   unsigned long rgba, unsigned long tex) {
    int x0 = FloatToInt(x * 16.0f) + D_001A7350[0] - 8;
    int x1 = FloatToInt((x + w) * 16.0f) + D_001A7350[0] - 8;
    int y0 = FloatToInt(y * 16.0f) + D_001A7354[0] - 8;
    int y1 = FloatToInt((y + h) * 16.0f) + D_001A7354[0] - 8;
    int s1 = (u + uw) * 16;
    int s0 = u * 16;
    int vb = v + vh;
    long *p;
    int *base;

    D_L05_001B2C88[0].p[0] = 0x10000007;
    D_L05_001B2C88[0].p[1] = 0;
    D_L05_001B2C88[0].p[2] = 0;
    D_L05_001B2C88[0].p[3] = 0x50000007;
    base = D_L05_001B2C88[0].p;
    D_L05_001B2C88[0].p = base + 4;
    qcopy(base + 4, D_L05_001ACA80);
    p = (long *)(base + 8);
    D_L05_001B2C88[0].p = base + 8;
    p[0] = tex;
    p[1] = 0x154;
    p[2] = rgba;
    p[3] = (v << 20) + s0;
    p[4] = x0 | ((long)y0 << 16) | ((long)0xFFFFF0 << 32);
    p[5] = (v << 20) + s1;
    p[6] = x1 | ((long)y0 << 16) | ((long)0xFFFFF0 << 32);
    p[7] = (vb << 20) + s0;
    p[8] = x0 | ((long)y1 << 16) | ((long)0xFFFFF0 << 32);
    p[9] = (vb << 20) + s1;
    p[10] = x1 | ((long)y1 << 16) | ((long)0xFFFFF0 << 32);
    p[11] = 0;
    D_L05_001B2C88[0].p = (int *)((char *)D_L05_001B2C88[0].p + 0x60);
}
