/* Complete nonmatching reconstruction. -O2 -G8 -ffunction-sections:
 * 904/912 bytes; local US/US2/PAL each 0/1.
 * Default and -g profiles tie. Remaining: checkpoint-table address folding, conditional block order and pointer roles.
 * Reopen with independent original control-flow or lifetime evidence.
 * Aligned local vectors cover every actual 16-byte producer/consumer access.
 */
#include "common.h"
typedef struct { float v[4]; } PlatformVector __attribute__((aligned(16)));
typedef unsigned char PlatformSlot[0x100];
extern PlatformSlot *D_L19_001B2A1C;
extern u8 D_L19_0021EA30[] MACRO_ADDR, D_0019B4A8[] MACRO_ADDR;
extern int D_001A79F0;
extern void func_002A7750(void *, int, int);
extern int func_00282948(int *);
extern float func_00283180(float);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Lift a triggered platform, retaining its previous transform for riders. */
void func_L19_00423EC0(u8 *object)
{
    PlatformVector oldPosition, oldRotation, delta;
    u8 *state = *(u8 **)(object + 0x68);
    unsigned short id;
    int bits;
    qcopy(&oldPosition, object + 0x10);
    qcopy(&oldRotation, object + 0xF0);
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x74) = 0;
        *(int *)(state + 0x5C) |= 1;
        qcopy(state + 0x60, object + 0x10);
        if (*(int *)(state + 0x7C) != -1 &&
            D_L19_001B2A1C[*(int *)(state + 0x7C)][0x20] != 0xFE &&
            D_L19_001B2A1C[*(int *)(state + 0x7C)][0x20] != 0xFD) {
            id = *(u16 *)(D_L19_001B2A1C[*(int *)(state + 0x7C)] + 0xB2);
            if (D_L19_0021EA30[(short)id + 0x464]) goto alreadyDone;
            bits = D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
            if (id & 1 ? ((bits >> 4) & 7) : (bits & 7)) {
alreadyDone:
                *(u16 *)(object + 0x34) |= 2;
                func_002A7750(object, 4, -1);
                break;
            }
        }
        object[0x30] = 255;
        *(float *)(object + 0x18) -= 6.0f;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        id = *(u16 *)(D_L19_001B2A1C[*(int *)(state + 0x7C)] + 0xB2);
        if (!D_L19_0021EA30[(short)id + 0x464]) {
            bits = D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
            if (!(id & 1 ? ((bits >> 4) & 7) : (bits & 7))) break;
        }
        if (*(int *)(state + 0x80) != -1)
            D_L19_001B2A1C[*(int *)(state + 0x80)][0xBC] = 1;
        func_002A7750(object, 2, -1);
        break;
    case 2:
        if (func_00282948((int *)(state + 0x78))) func_002A7750(object, 3, -1);
        break;
    case 3:
        *(float *)(state + 0x74) += 1.0f / *(float *)(state + 0x70);
        if (*(float *)(state + 0x74) > 1.0f) *(float *)(state + 0x74) = 1.0f;
        {
            float amount = (func_00283180(*(float *)(state + 0x74) * 3.1415927f) + 1.0f) * 0.5f;
            qzero(&delta);
            delta.v[2] = -6.0f;
            func_00282D30(&delta, &delta, amount);
            func_00282CC0(object + 0x10, state + 0x60, &delta);
        }
        if (*(float *)(state + 0x74) >= 1.0f) func_002A7750(object, 4, -1);
        break;
    case 4:
        if (*(int *)(state + 0x80) == -1 ||
            D_L19_001B2A1C[*(int *)(state + 0x80)][0xBC] == 0)
            *(u16 *)(object + 0x34) |= 2;
        break;
    }
    if (object[0x20] < 4) {
        func_00282CF0(&delta, object + 0x10, &oldPosition);
        func_002AD6F0(state + 0x20, &delta, &oldRotation, object + 0xF0);
    }
}
