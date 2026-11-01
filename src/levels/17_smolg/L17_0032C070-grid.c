#include "common.h"

/* The screen rectangle is one array: an element read with an offset is two instructions and
   never fills a slot. The scroll word's pointer is set outside the inner loop: loop hoists it, it
   gets no register, and reload builds the address beside the load. */

extern int D_001A7340[] MACRO_ADDR;
extern int D_L17_001AF52C[];
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned long func_0027C878(int);
extern int func_002A77E0(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

void func_L17_003A4740(char *self) {
    char *data = *(char **)(self + 0x68);
    float fv[2];
    unsigned long packet;
    int nx, ny, i, j;
    float pv[2];
    float base, a, b;
    int color;
    int t0, t1;

    fv[0] = func_00283CE0(D_001A7340[2]);
    fv[1] = func_00283CE0(D_001A7340[3]);
    packet = func_0027C878(0x1E);
    nx = D_001A7340[0] / 32 + 1;
    ny = D_001A7340[1] / 32 + 1;

    for (i = 0; i < nx; i++) {
        int *p = D_L17_001AF52C;
        for (j = 0; j < ny; j++) {
            pv[0] = (float)(i * 32);
            pv[1] = (float)(j * 32);
            base = (float)*p;
            a = func_00283CE0(*(int *)(data + 0x140));
            b = func_00283CE0(0x5A);
            color = (func_00283CF0(a * 127.5f / b) << 24) + 0xFF7F7F;
            t0 = func_002A77E0(0x20);
            t1 = func_002A77E0(0x20);
            func_0027E018(func_00283CF0(pv[0] - base), func_00283CF0(pv[1] - base), 0x20, 0x20, t0, t1, 0x20, 0x20, color, packet);
        }
    }
}
