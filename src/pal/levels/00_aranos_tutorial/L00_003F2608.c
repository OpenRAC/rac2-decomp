#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern unsigned char *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, int, int);

/* Spawns three particle bursts at the object. The second burst updates the first
 * particle's header, as retail does. */
void func_PAL_L00_003F2608(unsigned char *p)
{
    float vel[4], pos[4];
    float one = 1.0f;
    int n;
    unsigned char *first, *second, *third;
    unsigned char *particle1, *particle2, *particle3;

    vel[0] = 0.0f;
    vel[1] = -0.5f;
    vel[2] = 0.0f;
    vel[3] = one;
    n = func_002A77E0(16);
    if (func_002A77E0(2)) {
        n = -n;
    }
    qcopy(pos, p + 0x10);
    first = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (first) {
        particle1 = first + 0x20;
        *(unsigned short *)(first + 0xA) = 21;
        first[9] = func_00283CF0(4.0f) + 112;
        *(int *)(particle1 + 4) = 2;
        particle1[0xA] = 0xDF;
        particle1[0xB] = first[0xA];
    }
    second = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (second) {
        particle2 = second + 0x20;
        *(unsigned short *)(first + 0xA) = 21;
        first[9] = func_00283CF0(4.0f) + 112;
        *(int *)(particle2 + 4) = 2;
        particle2[0xA] = 0xDF;
        particle2[0xB] = first[0xA];
    }
    third = func_PAL_002BE9A8(pos, 0.05f, 1.0f, 0.97f, 16, vel, 315000.0f, 0xDFFFFFFF, 0);
    if (third) {
        int v;
        particle3 = third + 0x20;
        v = func_00283CF0(4.0f);
        *(unsigned short *)(third + 0xA) = 29;
        third[9] = v + 112;
        third[8] = func_002A77E0(255);
        *(int *)(particle3 + 4) = 2;
        particle3[0xA] = 0xDF;
        particle3[0xB] = first[0xA];
    }
}

