/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g.
 * us: 0/4; us2: 0/4; pal: absent.
 * 1336/1332 bytes; frame 0x60. Real input ramps, negated-less-than NaN behavior, full 16-byte
 * axis, three five-FP spring calls, 64-bit controller view and signed halfword timer/inversion
 * behavior are retained. The roll duration is captured before conversion, as retail does.
 * Float/control-flow allocation differs.
 * Reopen: Independent controller ramp/FP lifetime witness; no false volatile or register pins.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    int reserved; s16 direction, timer; float inverse;
    s16 delay, other_timer, other_delay; u16 reserved12; float other_inverse;
} RollState;
extern char D_00138180[];
extern int D_001A79F0;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 D_001A7A44;
extern float D_L05_001B1A68 __attribute__((sda));
extern float D_L05_001B1B74[] SDATA(D_L05_001B1B74);
extern float D_L05_001B1A40[] SDATA(D_L05_001B1A40);
extern u16 D_L05_001B1AE8 __attribute__((sda));
extern u16 D_L05_001B1AEC __attribute__((sda));
extern u16 D_L05_001B1AF0 __attribute__((sda));
extern u16 D_L05_001B1AF4 __attribute__((sda));
extern int D_L05_001B1B20 __attribute__((sda));
extern int D_L05_002A18E0;
extern void func_L05_00442880(void *);
extern float func_00282C48(float);
extern int func_L05_00379F38(void);
extern int func_L05_004459B0(void *);
extern float func_00282DB0(void *, void *);
extern int func_L05_00442F90(void *);
extern float func_002702C8(float *, float, float, float, float, float);
extern int func_00282978(void *);
extern float func_00283CE0(int);

void func_L05_00442A58(u8 *camera, float *horizontalOutput, float *verticalOutput)
{
    Vector axis;
    u8 *angles = *(u8 **)(camera + 0x70) + 0x50;
    float horizontal, vertical;
    float *ramps = D_L05_001B1B74;
    RollState *roll;
    u8 *movement;
    u32 held;
    func_L05_00442880(camera);
    vertical = *(float *)(D_00138180 + 0x10C);
    horizontal = -*(float *)(D_00138180 + 0x108);
    if (!(func_00282C48(vertical) < D_L05_001B1A68)) {
        ramps[1] = 0.0f;
        if (ramps[1] < vertical)
            vertical -= D_L05_001B1A68;
        else
            vertical += D_L05_001B1A68;
        vertical /= 1.0f - D_L05_001B1A68;
    } else if (vertical != 0.0f) {
        vertical = 0.0f;
        ramps[1] = 0.0f;
    } else {
        held = *(u32 *)(D_00138180 + 0x1A0);
        if (held & 0x1000) {
            vertical = -ramps[1];
            ramps[1] += ramps[2];
            if (ramps[1] > 1.0f) ramps[1] = 1.0f;
        } else if (held & 0x4000) {
            vertical = ramps[1];
            ramps[1] += ramps[2];
            if (ramps[1] > 1.0f) ramps[1] = 1.0f;
        } else {
            ramps[1] = 0.0f;
        }
    }
    if (horizontal == 0.0f) {
        held = *(u32 *)(D_00138180 + 0x1A0);
        if (held & 0x8000) {
            horizontal = ramps[0];
            ramps[0] += ramps[2];
            if (ramps[0] > 1.0f) ramps[0] = 1.0f;
        } else if (held & 0x2000) {
            horizontal = -ramps[0];
            ramps[0] += ramps[2];
            if (ramps[0] > 1.0f) ramps[0] = 1.0f;
        } else {
            ramps[0] = 0.0f;
        }
    } else {
        ramps[0] = 0.0f;
    }
    if ((D_001A79F0 != 5 && D_001A79F0 != 10) || func_L05_00379F38() == 0) {
        if (!(horizontal < 0.0f)) horizontal *= horizontal;
        else horizontal = -(horizontal * horizontal);
        if (!(vertical < 0.0f)) vertical *= vertical;
        else vertical = -(vertical * vertical);
    }
    if (angles[0x1E] == 0 && (horizontal != 0.0f || vertical != 0.0f)) {
        angles[0x1F] = 0;
        angles[0x1E] = 1;
    } else if (angles[0x1E] == 1) {
        angles[0x1F] = 0;
    }
    axis.q = 0;
    axis.f[3] = 1.0f;
    axis.f[2] = 1.0f;
    if (angles[0x1E] < 2 &&
        ((*(u32 *)(D_00138180 + 0x1A4) & 3) || func_L05_004459B0(camera)) &&
        func_00282C48(func_00282DB0(&axis, camera)) < 0.7f)
        angles[0x1E] = 2;
    if (func_L05_00442F90(camera) != 0) {
        *horizontalOutput = 0.0f;
        *verticalOutput = 0.0f;
    }
    *verticalOutput = (-vertical * 0.017453294f) * *(float *)(angles + 0x74);
    *horizontalOutput = (horizontal * 0.017453294f) * *(float *)(angles + 0x78);
    *(float *)(angles + 0x64) = func_002702C8((float *)(angles + 0x54),
        *(float *)(angles + 0x64), *verticalOutput, *(float *)(angles + 0xC),
        *(float *)(angles + 0x10), *(float *)(angles + 0x14));
    *(float *)(angles + 0x68) = func_002702C8((float *)(angles + 0x58),
        *(float *)(angles + 0x68), *horizontalOutput, *(float *)angles,
        *(float *)(angles + 4), *(float *)(angles + 8));
    movement = *(u8 **)(camera + 0x70);
    *(float *)(movement + 0x40) = func_002702C8((float *)(movement + 0x44),
        *(float *)(movement + 0x40), vertical, D_L05_001B1A40[0],
        D_L05_001B1A40[1], D_L05_001B1A40[2]);
    *verticalOutput = *(float *)(angles + 0x64);
    *horizontalOutput = *(float *)(angles + 0x68);
    roll = (RollState *)(*(u8 **)(camera + 0x70) + 0xD4);
    if (roll->timer != 0 && func_00282978(&roll->timer) != 0)
        roll->direction = 0;
    if (roll->delay == 0) {
        if (*(u64 *)(D_00138180 + 0x1A0) & 12) {
            u16 duration = D_L05_001B1AE8;
            roll->timer = duration;
            roll->inverse = 1.0f / func_00283CE0((s16)duration);
            roll->delay = (u16)roll->timer + D_L05_001B1AEC;
            roll->direction = (*(u32 *)(D_00138180 + 0x1A0) & 4) ? -1 : 1;
            if (D_001A7A44 != 0)
                roll->direction = roll->direction == -1 ? 1 : -1;
        }
    } else {
        func_00282978(&roll->delay);
    }
    if (func_00282978(&roll->other_delay) != 0 && D_L05_002A18E0 != 0 && D_001A79F0_gp != 20) {
        held = *(u32 *)(D_00138180 + 0x1A0);
        if ((held & 3) == 3 || (held & 12) == 12) {
            u16 duration = D_L05_001B1AF0;
            roll->other_delay = D_L05_001B1AF4;
            D_L05_001B1B20 = 7;
            roll->other_timer = duration;
            roll->other_inverse = 1.0f / func_00283CE0((s16)duration);
        }
    }
}
