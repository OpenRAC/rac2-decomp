#include "include_asm.h"

extern int func_002A9640(char *a0, int a1, int a2);

typedef int TI128 __attribute__((mode(TI)));
extern char D_L14_001B1870[8] __attribute__((sda));
extern char D_L14_001B1878[8] __attribute__((sda));
extern int D_L14_001B18A0 __attribute__((sda));
extern void func_002A7750_3(char *a0, int a1, int a2);
extern void func_00282F20(void *out, void *in, float scale);
extern void func_00282CF0(void *out, void *in1, void *in2);
extern void func_00282CC0(void *out, void *in1, void *in2);
extern void func_L00_0032A258(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_002E5CF8(int, int, char *);
extern void func_0029F338(char *a0);

void func_L14_00427458(char *a0) {
    float pts[2][4] __attribute__((aligned(16)));
    char *state = *(char **)(a0 + 0x68);
    char *obj;

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        func_002A7750_3(a0, 1, -1);
        break;
    case 1:
        obj = (char *)func_002A9640(a0, 0x4010000, 0);
        if (obj != 0 && *(int *)state == 0) {
            float off[4] __attribute__((aligned(16)));
            *(TI128 *)off = 0;
            off[0] = 3.0f;
            off[1] = 3.0f;
            func_00282F20(pts[0], obj + 0x10, 8.0f);
            func_00282F20(pts[1], obj + 0x10, 18.0f);
            func_00282CF0(pts[0], pts[0], off);
            func_00282CC0(pts[1], pts[1], off);
            func_L00_0032A258(a0, pts, D_L14_001B1878, D_L14_001B1870, 0xFFFF, 0, D_L14_001B18A0, 8, 0xFFFF, 0xFF, 0);
            func_002E5CF8(0, 0, a0);
            func_002A7750_3(a0, 2, -1);
        }
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        func_0029F338(a0);
        break;
    }
}
