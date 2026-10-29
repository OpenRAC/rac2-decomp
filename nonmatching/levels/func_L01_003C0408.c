/* Retained orbit steering, 2026-10-28: best732/736B,0/1US.
 * Five bounded trials. Default724; real absolute arena-table pointer with
 * no-split-addresses732. Re-reading the target directly fixes swapped temp
 * GPRs. Separate division/multiply retains true operation order. Debug labels
 * and existing hazard-label profile tie732, so neither is a required flag.
 * Best profile -O2 -G0 -ffunction-sections -mno-split-addresses.
 * Remaining gap: hero global base/addend, height-return FP register schedule,
 * and branch target on pre-division nops. Three732-byte trials tied; stop.
 * Return isfloat: mode1 returns distanceF23, fallback returns-1000F0.
 * Arena stride128, full center30..3F; private extent2F0 includes threshold2EC.
 * Target point2A0..2AF copied in full beforeXY adjustments; height2E8 restored.
 * Hero owner remains an incomplete external byte array; typed position view
 * gives real offset80 without pretending that the whole hero is only90 bytes.
 */
#include "common.h"
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L01_003BFDC8(void *, int, int, int);
extern int func_L01_00321178(void *, void *);
extern void func_002B5278(void *, float);
typedef struct { u8 prefix[0x30]; float position[4]; u8 rest[0x40]; } ArenaRow;
extern ArenaRow *D_L01_001B264C NOT_SDA;
extern float D_L01_001AFED0_gp SDATA(D_L01_001AFED0);
extern u8 D_00189E20[];
typedef struct { u8 prefix[0x80]; float position[4]; } HeroPositionView;

/* The128-byte arena rows contain a complete16-byte center at+30. The private
 * target point2A0 is a complete copy before its XY adjustments. Mode1 returns
 * measured distance; the hero-facing fallback returns the actual-1000 sentinel. */
float func_L01_003C0408(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float distance, current_angle, target_angle, difference, magnitude;
    if (*(int *)(state + 0x124) == 1) {
        distance = func_00282E80(object + 0x10, *(u8 **)(state + 0x120) + 0x10);
        current_angle = func_00283248(
            *(float *)(object + 0x10) - D_L01_001B264C[*(int *)(state + 0x2CC)].position[0],
            *(float *)(object + 0x14) - D_L01_001B264C[*(int *)(state + 0x2CC)].position[1]);
        target_angle = func_00283248(
            *(float *)(*(u8 **)(state + 0x120) + 0x10) - D_L01_001B264C[*(int *)(state + 0x2CC)].position[0],
            *(float *)(*(u8 **)(state + 0x120) + 0x14) - D_L01_001B264C[*(int *)(state + 0x2CC)].position[1]);
        difference = func_00283BE0(target_angle, current_angle);
        magnitude = func_00282C48(difference);
        if (*(float *)(state + 0x2EC) < distance) {
            if (object[0x43] != state[0x2E1])
                func_L01_003BFDC8(object, state[0x2E1], 0, 20);
            if (magnitude < D_L01_001AFED0_gp * 0.01745329424738884f) {
                qcopy(state + 0x2A0, *(u8 **)(state + 0x120) + 0x10);
            } else {
                difference /= magnitude;
                difference *= 0.0872664749622345f;
                qcopy(state + 0x2A0, D_L01_001B264C[*(int *)(state + 0x2CC)].position);
                *(float *)(state + 0x2A0) += func_00283180(func_00283B98(current_angle, difference)) * 38.0f;
                *(float *)(state + 0x2A4) += func_00283198(func_00283B98(current_angle, difference)) * 38.0f;
            }
            func_L01_00321178(object, state + 0x2A0);
        } else {
            if (object[0x43] != state[0x2E2] && object[0x95] != 3)
                func_L01_003BFDC8(object, state[0x2E2], 0, 20);
                func_002B5278(object, func_00283248(*(float *)(*(u8 **)(state + 0x120) + 0x10) - *(float *)(object + 0x10),
                *(float *)(*(u8 **)(state + 0x120) + 0x14) - *(float *)(object + 0x14)));
        }
        *(float *)(object + 0x18) = *(float *)(state + 0x2E8);
        return distance;
    } else {
        if (object[0x43] != state[0x2E2] && object[0x95] != 3)
            func_L01_003BFDC8(object, state[0x2E2], 0, 20);
        func_002B5278(object, func_00283248(((HeroPositionView *)D_00189E20)->position[0] - *(float *)(object + 0x10),
            ((HeroPositionView *)D_00189E20)->position[1] - *(float *)(object + 0x14)));
        *(float *)(object + 0x18) = *(float *)(state + 0x2E8);
        return -1000.0f;
    }
}
