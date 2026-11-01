#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x464]; unsigned char collected[0]; } ControllerLevelState;
extern ControllerLevelState D_L00_0021DDB0;
extern unsigned char D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern unsigned char *D_L00_001B1E9C __attribute__((sda));
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_001B1010[];
typedef struct { char pad[0x30]; int phase, frame; char pad2[0x15c]; int first, second; } Controller10;
extern Controller10 D_L00_001BCAC0;
extern void func_0029F338(void *);
extern void func_00325B70(int, void *, int, int);
extern void func_PAL_003273B8(int, float, void *, int, void *);
extern float func_00283B98(float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_0026FEB8(void *);
typedef struct { char pad[0x20]; unsigned char state; char pad2[3]; char *classData; char pad3[0xC]; unsigned short flags; char pad4[0x62]; int field98; } ControllerMoby10;

void func_PAL_L00_00412320(unsigned char *object)
{
    int *state = *(int **)(object + 0x68);
    unsigned char *counter;

    switch (object[0x20]) {
    case 0:
        state[9] = 0;
        state[10] = 0;
        state[12] = 0;
        state[13] = 0;
        object[0x30] = 255;
        object[0x20] = 1;
        if (!D_L00_0021DDB0.collected[(short)*(unsigned short *)(object + 0xb2)]) {
            int n = D_0019B4A8[((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10)];
            /* One 3-bit count per nibble; the low bit of the number picks the nibble. */
            if (!((*(unsigned short *)(object + 0xb2) & 1) ? (n >> 4) & 7 : n & 7)) {
                return;
            }
        }
        if (state[17] != -1) {
            func_0029F338(D_L00_001B1E9C + (state[17] << 8));
        }
        if (state[16] != -1) {
            func_0029F338(D_L00_001B1E9C + (state[16] << 8));
        }
        break;
    case 1:
        if (D_L00_001A8F00 != 2 && state[8] != -1) {
            ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[8] << 8));
            other->flags = (other->flags & 0xffbe) | 0x1000;
            other->field98 = *(int *)(other->classData + 0x10);
        }
        if (D_L00_001BCAC0.phase == 1 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[8] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                if (state[17] != -1) {
                    func_0029F338(D_L00_001B1E9C + (state[17] << 8));
                }
                if (state[16] != -1) {
                    func_0029F338(D_L00_001B1E9C + (state[16] << 8));
                }
                if (*(unsigned short *)(object + 0xb2) & 1) {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10));
                    if (((*counter >> 4) & 7) != 7) {
                        *counter += 16;
                    }
                } else {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10));
                    if ((*counter & 7) != 7) {
                        ++*counter;
                    }
                }
                func_00325B70(D_L00_001BCAC0.first, state + 9, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first;
                if (D_L00_001BCAC0.frame >= 1976) {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.436332345f);
                    func_PAL_003273B8(first, *(float *)(state + 11), state + 9, 1, D_L00_001A8F20);
                } else {
                    func_PAL_003273B8(first, *(float *)(state + 11), state + 9, 0, D_L00_001A8F20);
                }
            }
            if (D_L00_001BCAC0.frame == 223) {
                int i;
                for (i = 0; i < 2; i++) {
                    ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[i] << 8));
                    if (other && other->state != 254 && other->state != 253) {
                        func_002E5CF8(0, 0, other);
                        other->state = 1;
                    }
                }
            }
            if (D_L00_001BCAC0.frame == 226) {
                func_0026FEB8(D_L00_001B1010);
            }
        }
        if (D_L00_001A8F00 != 2) {
            if (state[9]) {
                func_0029F338((void *)state[9]);
                func_0029F338((void *)state[10]);
                state[9] = 0;
                state[10] = 0;
            }
            if (state[12]) {
                func_0029F338((void *)state[12]);
                func_0029F338((void *)state[13]);
                state[12] = 0;
                state[13] = 0;
            }
        }
        if (D_L00_001BCAC0.phase == 2 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[4] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                {
                    int i;
                    for (i = 0; i < 3; i++) {
                        ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[5 + i] << 8));
                        other->field98 = 0;
                        other->flags = (other->flags | 0x41) & 0xefff;
                    }
                }
                func_00325B70(D_L00_001BCAC0.first, state + 9, 0, 2);
                func_00325B70(D_L00_001BCAC0.second, state + 12, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first, second = D_L00_001BCAC0.second;
                if (D_L00_001BCAC0.frame < 780) {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.261799425f);
                    *(float *)(state + 14) = func_00283B98(*(float *)(state + 14), 0.261799425f);
                    func_PAL_003273B8(first, *(float *)(state + 11), state + 9, 1, D_L00_001A8F20);
                    func_PAL_003273B8(second, *(float *)(state + 14), state + 12, 1, D_L00_001A8F20);
                } else {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.087266475f);
                    *(float *)(state + 14) = func_00283B98(*(float *)(state + 14), 0.087266475f);
                    func_PAL_003273B8(first, *(float *)(state + 11), state + 9, 0, D_L00_001A8F20);
                    func_PAL_003273B8(second, *(float *)(state + 14), state + 12, 0, D_L00_001A8F20);
                }
            }
        }
        break;
    }
}

