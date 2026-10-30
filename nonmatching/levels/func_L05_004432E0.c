/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections.
 * us: 0/4; us2: 0/4; pal: absent.
 * 1060/1116 bytes; frame 0x70 instead of0x60. Camera motion includes actual five-FP spring
 * inputs, world 20 interpolation, world 15 height clamps, signed halfword roll timer, six ordered
 * bounds tests and radial camera correction. Pointer lifetimes and clamp/float scheduling
 * differ.
 * Reopen: Independent camera record lifetime and scalar scheduling evidence.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern char *D_L05_001B1EC4, *D_L05_001B251C;
extern int D_001A79F0;
extern float D_L05_001B1AC0[] SDATA(D_L05_001B1AC0);
extern float D_L05_001B1BD0[] SDATA(D_L05_001B1BD0);
extern float D_L05_001B1A7C __attribute__((sda));
extern char *D_L05_001B2614 __attribute__((sda));
extern u8 *D_L05_00221D88;
extern char D_L05_001B3600[];
extern int func_L05_00379F38(void);
extern float func_002702C8(float *, float, float, float, float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_L05_004432E0(u8 *camera)
{
    Vector motion, offset;
    u8 *parameters = *(u8 **)(D_L05_001B1EC4 + *(s16 *)(camera + 0x84) * 32 + 0x1C);
    u8 *entity = (u8 *)D_L05_001B251C + (*(int *)(parameters + 0x20) << 8);
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *movement = *(u8 **)(camera + 0x70);
    float *tuning = D_L05_001B1BD0;
    float *position = (float *)(camera + 0x30);
    u8 *roll;
    int i;
    if (D_001A79F0 != 20) {
        float speed, acceleration;
        if (*(int *)(state + 0x34) != 0) {
            speed = func_L05_00379F38() != 0 ? D_L05_001B1AC0[2] : D_L05_001B1AC0[1];
            acceleration = tuning[8];
        } else {
            speed = D_L05_001B1AC0[0];
            acceleration = tuning[9];
        }
        *(float *)(state + 0x38) = func_002702C8((float *)(state + 0x3C),
            *(float *)(state + 0x38), speed * 0.016666668f, acceleration, 0.2f, 0.0f);
    }
    func_00282D30(&motion, entity + 0xC0, *(float *)(state + 0x38));
    func_00282CC0(position, position, &motion);
    qzero(movement + 0x30);
    if (D_001A79F0 == 20) {
        u8 *angles = *(u8 **)(camera + 0x70) + 0x50;
        float deltaZ = (tuning[1] + (tuning[0] - tuning[1]) *
            (-*(float *)(angles + 0x64) / (*(float *)(angles + 0x74) * 0.017453294f))) * 0.016666668f;
        float forward;
        position[2] += deltaZ;
        *(float *)(movement + 0x38) = deltaZ;
        forward = (tuning[3] + (tuning[2] - tuning[3]) *
            (*(float *)(angles + 0x68) / (*(float *)(angles + 0x78) * 0.017453294f))) * 0.016666668f;
        func_00282D30(&offset, camera + 0x10, forward);
        func_00282CC0(position, position, &offset);
        func_00282CC0(movement + 0x30, movement + 0x30, &offset);
    }
    if (D_001A79F0 == 15) {
        float oldHeight = position[2];
        float weight = *(float *)(movement + 0x40);
        float selected = func_L05_00379F38() != 0 ? tuning[6] : tuning[5];
        position[2] += (tuning[7] + (selected - tuning[7]) * weight) * 0.016666668f;
        if (position[2] < 400.0f) position[2] = 400.0f;
        else if (position[2] > 650.0f) position[2] = 650.0f;
        *(float *)(movement + 0x38) = position[2] - oldHeight;
    }
    roll = *(u8 **)(camera + 0x70) + 0xD4;
    if (*(s16 *)(roll + 4) != 0) {
        float amount = tuning[4] * func_00283198(
            func_00283CE0(*(s16 *)(roll + 6)) * *(float *)(roll + 8) * 3.1415927f);
        if (*(s16 *)(roll + 4) == 1) amount = -amount;
        func_00282D30(&offset, camera + 0x10, amount);
        func_00282CC0(position, position, &offset);
        func_00282CC0(movement + 0x30, movement + 0x30, &offset);
    }
    for (i = 0; i < 3; i++)
        if (position[i] < 5.0f) position[i] = 5.0f;
    for (i = 0; i < 3; i++)
        if (position[i] > 1000.0f) position[i] = 1000.0f;
    if (func_L05_00379F38() == 0 && D_L05_00221D88 != 0) {
        int index = **(int **)(D_L05_00221D88 + 0x68);
        if (index >= 0) {
            char *record = D_L05_001B2614 + (index << 7);
            float limit = func_00282DF0(record) - D_L05_001B1A7C;
            float distance;
            func_00282CF0(&offset, record + 0x30, position);
            distance = func_00282DF0(&offset);
            if (limit < distance) {
                func_00282F20(&offset, &offset, distance - limit);
                func_00282CC0(position, position, &offset);
            }
        }
    }
    qcopy(D_L05_001B3600, position);
}
