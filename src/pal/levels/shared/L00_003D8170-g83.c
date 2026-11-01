#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x80]; float x, y; } PositionBase;
extern PositionBase D_00189E20 __attribute__((nosda));
extern char D_00189EA0[] __attribute__((nosda));
extern float D_L00_001B0788 __attribute__((sda));
extern float D_L00_001B078C __attribute__((sda));
extern float D_L00_001B0790 __attribute__((sda));
extern float D_L00_001B07B8 __attribute__((sda));
extern float D_L00_001B07BC __attribute__((sda));
extern float D_L00_001B07C0 __attribute__((sda));
extern float D_L00_001B07C4 __attribute__((sda));
extern float D_L00_001B07C8 __attribute__((sda));
extern void ref_L00_003EBC68_00(void *, void *, void *);
extern float ref_L00_003EBC68_01(void *, void *);
extern void ref_L00_003EBC68_02(void *, void *, void *, float, float, float);
extern void ref_L00_003EBC68_03(void *, void *, float);
extern void ref_L00_003EBC68_04(void *, void *, void *);
extern void ref_L00_003EBC68_05(void *, void *, float);
extern int ref_L00_003EBC68_06(void *, void *, int, float, float, float);
extern float ref_L00_003EBC68_07(void *);
extern float ref_L00_003EBC68_08(float, float);
extern float ref_L00_003EBC68_09(float);
extern float ref_L00_003EBC68_10(float);
extern float ref_L00_003EBC68_11(float, float);
extern void ref_L00_003EBC68_12(void *, void *, void *, float, float, float);

void func_PAL_L00_003D85E0(char *object, char *state)
{
    float difference[4], offset[4];
    float distance, angle, correction, speed;
    int hit;
    char *target;
    ref_L00_003EBC68_00(difference, state, object + 0x10);
    distance = ref_L00_003EBC68_01(object + 0x10, D_00189EA0);
    ref_L00_003EBC68_01(object + 0x10, state);
    switch (*(unsigned char *)(object + 0xbc)) {
    case 0:
        ref_L00_003EBC68_02(object, state, state + 0x30,
                           0.0025132746f, 0.0012566373f, 0.2303835f);
        *(unsigned char *)(object + 0xbc) = 2;
        break;
    case 2:
        target = *(char **)(state + 0x28);
        if (!target)
            ref_L00_003EBC68_02(object, state, state + 0x30,
                               0.0025132746f, 0.0012566373f, 0.2303835f);
        else
            ref_L00_003EBC68_02(object, target + 0x10, state + 0x30,
                               D_L00_001B0788 * 6.981318e-06f,
                               D_L00_001B078C * 6.981318e-06f,
                               D_L00_001B0790 * 0.0003490659f);
        ref_L00_003EBC68_03(difference, difference, 0.048f);
        ref_L00_003EBC68_00(difference, difference, state + 0x10);
        if (distance > 1.3f)
            ref_L00_003EBC68_03(difference, difference, 0.1872f);
        else
            ref_L00_003EBC68_03(difference, difference, 0.36f);
        difference[2] *= 0.88f;
        ref_L00_003EBC68_04(state + 0x10, state + 0x10, difference);
        if (*(unsigned char *)(object + 0x20) == 2)
            ref_L00_003EBC68_05(state + 0x10, state + 0x10, 0.054000005f);
        hit = ref_L00_003EBC68_06(object, state + 0x10, 0, 1.0f, 0.5f, 0.0f);
        speed = ref_L00_003EBC68_07(state + 0x10);
        if (hit) {
            if (speed < 0.005f) {
                if (++*(unsigned char *)(state + 0x26) > 17 && !*(unsigned char *)(object + 0x31)) {
                    qcopy(object + 0x10, state);
                    *(unsigned char *)(state + 0x26) = 0;
                }
            }
        } else {
            *(unsigned char *)(state + 0x26) = 0;
        }
        if (distance < 1.1f) {
            correction = 1.1f - distance;
            angle = ref_L00_003EBC68_08(D_00189E20.x - *(float *)(object + 0x10),
                                      D_00189E20.y - *(float *)(object + 0x14));
            *(float *)(state + 0x10) -= correction * ref_L00_003EBC68_09(angle) * 0.14400001f;
            *(float *)(state + 0x14) -= correction * ref_L00_003EBC68_10(angle) * 0.14400001f;
        }
        break;
    default:
        *(unsigned char *)(object + 0xbc) = 0;
        if (distance > 1.3f) *(unsigned char *)(object + 0xbc) = 2;
        break;
    }
    *(float *)(state + 0x54) = ref_L00_003EBC68_11(*(float *)(state + 0x54), D_L00_001B07C4);
    ref_L00_003EBC68_03(offset, object + 0xe0, *(float *)(state + 0x50));
    ref_L00_003EBC68_00(object + 0x10, object + 0x10, offset);
    *(float *)(state + 0x50) = ref_L00_003EBC68_10(*(float *)(state + 0x54)) * D_L00_001B07C8;
    ref_L00_003EBC68_03(offset, object + 0xe0, *(float *)(state + 0x50));
    ref_L00_003EBC68_04(object + 0x10, object + 0x10, offset);
    ref_L00_003EBC68_12(object, state + 0x48, state + 0x4c, D_L00_001B07B8, D_L00_001B07BC, D_L00_001B07C0);
}
