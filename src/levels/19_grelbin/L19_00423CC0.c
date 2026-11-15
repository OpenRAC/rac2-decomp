#include "common.h"

extern void func_0029F338(void *);

extern int func_002ACBC8(char *, int);

extern void func_002A7750(char *, int, int);

extern int D_001A79F0[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);

extern unsigned char D_00189EA0[];

extern unsigned char D_0019B4A8[];

/* The state table has an unknown trailing extent. */
extern struct {
    unsigned char pad[0x464];
    unsigned char state[0];
} D_L19_0021EA30;

void func_L19_00423CC0(char *a0)
{
    char *q1, *q2;
    int obj = *(int *)(a0 + 0x68);

    if (obj == 0) {
        func_0029F338(a0);
        return;
    }
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(int *)(a0 + 0x98) = 0;
        *(unsigned short *)(a0 + 0x34) = (*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(a0, 1, -1);
        *(unsigned char *)(a0 + 0x30) = 0xFF;
        break;
    case 2:
    default:
        break;
    case 1:
        if (IsPointInCuboid(D_00189EA0, *(int *)obj) != 0) {
            int h = *(unsigned short *)(a0 + 0xB2);
            if (h & 1) {
                unsigned char *e = &D_0019B4A8[((short)h >> 1) + (D_001A79F0_gp << 10)];
                if (((*e >> 4) & 7) != 7) {
                    *e += 0x10;
                }
            } else {
                unsigned char *e = &D_0019B4A8[((short)h >> 1) + (D_001A79F0_gp << 10)];
                if ((*e & 7) != 7) {
                    *e += 1;
                }
            }
            *(unsigned short *)(a0 + 0x34) = (*(unsigned short *)(a0 + 0x34) & 0xFFBE) | 0x1000;
            q1 = *(char **)(a0 + 0x24);
            *(int *)(a0 + 0x98) = *(int *)(q1 + 0x10);
            *(int *)(a0 + 0x98) = *(int *)(q1 + 0x10);
            func_002A7750(a0, 2, -1);
        }
        {
            int h = *(unsigned short *)(a0 + 0xB2);

            if (D_L19_0021EA30.state[(short)h] == 0) {
                int c = D_0019B4A8[((short)h >> 1) + (D_001A79F0[0] << 10)];

                if (!((h & 1) ? ((c >> 4) & 7) : (c & 7)))
                    return;
            }
        }
        *(unsigned short *)(a0 + 0x34) = (*(unsigned short *)(a0 + 0x34) & 0xFFBE) | 0x1000;
        q2 = *(char **)(a0 + 0x24);
        *(int *)(a0 + 0x98) = *(int *)(q2 + 0x10);
        *(int *)(a0 + 0x98) = *(int *)(q2 + 0x10);
        func_002A7750(a0, 2, -1);
        break;
    }
}
