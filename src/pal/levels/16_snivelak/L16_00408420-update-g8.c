/* func_PAL_L16_00408420, the PAL copy of func_L16_00403900: the same C at 50 Hz, with the random
 * timers and frame counts scaled by 5/6, the blend ticks 10 > 8, and the per-frame rates raised. */
#include "common.h"
/* Interfaces as the call sites load them; ignored results stay unqualified.
 * Retail's call to func_PAL_L16_004099C0 loads a1, f12 and f13 although the callee
 * never reads them, so this caller declares the arguments it really passes. */
extern int func_PAL_L16_004095E0(void *), func_002B3890(void *);
extern int func_002A7820(int, int), func_00282978(short *);
extern void func_PAL_002A7E68(void *, int, int, int), func_002A7750(void *, int, int);
extern void func_PAL_002A7650(void *, int, int), func_002A7A00(void *, float, float);
extern float func_00282C48(float), func_002A78D8(float, float), func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern u8 *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, u8, float, float);
extern void func_PAL_003120C0(void *), func_002AB650(void *), func_0029F338(void *);
extern int func_002E5CF8(int, int, void *);
extern void *func_PAL_L16_0040AC00(void *, int, int, int, int, int, int, int, float, int, int);
extern int func_L01_00322288(int, float), func_PAL_L09_0032B088(char *, int);
extern int func_PAL_L16_004099C0(void *, void *, float, float);
extern float func_00283248(float, float), func_00282E80(void *, void *), func_00283C80(float, float);
extern float func_002AAA00(float *, float *, float, float, float, float, int);
extern int func_PAL_002AF6C0(void *, float);
extern void func_0029FCC0(char *, int, char *);
extern void *func_PAL_L16_0040A008(void *, void *, void *, int, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_PAL_L16_00409AD0(void *);
typedef struct {
    u8 unknown00[0x80];
    float position80[4];
    u8 unknown90[0x50];
    float aimPositionE0[4];
    u8 unknownF0[0x2290 - 0xf0];
    u8 *target2290;
} PlayerView;
extern PlayerView D_00189E20 NOT_SDA;
extern float D_L16_001A8F20[4] __attribute__((sda));
extern u8 *D_L16_001BFF58 NOT_SDA;
/* Partial view shared with the matched sibling death/debris update. */
extern struct {
    u8 pad000[0x160];
    float strength;
    u8 pad164[4];
    int duration, timer;
    u8 pad170[0x10];
    float damping;
    u8 pad184[4];
    int lifetime;
} D_L16_001B99C0;

/* Both destruction exits are written out. Sched2 still sees func_0029F338 in
 * the debris block, and its extra dependence decides that block's order; jump2
 * then merges the exits, so the early-out branches into the debris tail. */
void func_PAL_L16_00408420(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float position[4] __attribute__((aligned(16)));
    float aim[4] __attribute__((aligned(16)));
    u8 *child;
    int i, attack;
    float angle, pitch;
    float *pitchField3, *pitchField6, *pitchField7, *pitchField5;
    if (func_PAL_L16_004095E0(moby)) {
        func_0029F338(moby);
        return;
    }
    switch (moby[0x95]) {
    case 0:
        if (func_002B3890(moby)) *(short *)(state + 0x25e) = ((s32)(func_002A7820(0, 30)) * 5 + 2) / 6;
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
            func_002A7750(moby, 5, 2);
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
                func_002A7750(moby, 4, 2);
            }
            if (*(int *)(state + 0x294) != -1) {
                func_002A7750(moby, 3, 2);
                if (!*(int *)(state + 0x2a8) || *(int *)(state + 0x2ac))
                    if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
            }
        } else if (*(int *)(state + 0x264) && func_00282978((short *)(state + 0x25e))) {
            func_002A7750(moby, 2, 1);
            *(int *)(state + 0x264) = 0;
            if (*(int *)(state + 0x258) < 250)
                *(int *)(state + 0x258) = ((s32)(func_002A7820(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (*(int *)(state + 0x260) == 1 || *(int *)(state + 0x2b4) == 1)
            func_002A7750(moby, 5, 2);
        break;
    case 2:
        if (*(int *)(state + 0x260) == 1) break;
        if (*(int *)(state + 0x2b4) != 1 && moby[0x20] != 4 && moby[0x20] != 3) {
            func_002A7750(moby, 1, 0);
            if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
            *(int *)(state + 0x258) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        if (*(float *)(state + 0x20) <= 0.0f) {
            func_PAL_002A7650(moby, 0, 3);
            for (i = 0; i < 5; i++) {
                func_002A7A00(position, 0.16000001f, 0.24000001f);
                position[2] = func_00282C48(position[2]);
                position[2] *= 2.5f;
                func_00282CC0(position, position, D_L16_001A8F20);
                child = func_PAL_002735D0(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, position, 255, 30.0f, 15.0f);
                *(void (**)(void *))(child + 0x64) = func_PAL_003120C0;
            }
            func_002E5CF8(0, 0, moby);
            func_PAL_L16_0040AC00(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 2.0f, 1, 1);
            func_PAL_L16_0040AC00(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 1.0f, 1, 1);
            D_L16_001B99C0.damping = 0.1f;
            D_L16_001B99C0.lifetime = 75;
            D_L16_001B99C0.strength = 0.2f;
            D_L16_001B99C0.duration = 50;
            D_L16_001B99C0.timer = 0;
            func_0029F338(*(void **)(state + 0x274));
            position[0] = func_002A78D8(0.5f, 4.0f) * 0.020000001f;
            position[1] = func_002A78D8(0.0f, 4.0f) * 0.020000001f;
            position[2] = func_002A7878(7.0f, 9.0f) * 0.020000001f;
            position[2] = func_00282C48(position[2]);
            position[2] += position[2];
            func_00282CC0(position, position, D_L16_001A8F20);
            child = func_PAL_002735D0(moby, 3, 0xecb, 0, moby + 0x10,
                moby + 0xf0, position, 255, 180.0f, 25.0f);
            func_002AB650(child);
            func_0029F338(moby);
            return;
        }
        if (!(moby[0x60] & 2)) break;
        *(int *)(state + 0x2b8) = 0;
        *(short *)(state + 0x25c) = 0;
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
            func_002A7750(moby, 5, 2);
            if (*(int *)(state + 0x298) != -1) func_002A7750(moby, 6, -1);
        } else {
            func_002A7750(moby, 2, 1);
            if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
            *(int *)(state + 0x258) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
        }
        if (*(int *)(state + 0x2ac)) {
            func_002A7750(moby, 4, 2);
            if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
        }
        break;
    }
    attack = moby[0x20];
    switch (attack) {
    case 1:
    case 2:
        break;
    case 3:
        if (!*(int *)(state + 0x2ac))
            func_L01_00322288((int)moby, func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
                D_00189E20.position80[1] - *(float *)(moby + 0x14)));
        if (func_PAL_L16_004099C0(moby, moby + 0x10, 0.0f, 0.0f)) {
            if (*(int *)(state + 0x298) != -1) {
                func_002A7750(moby, 6, -1);
                if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
            } else {
                func_002A7750(moby, 5, -1);
                if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
            }
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
                func_002A7750(moby, 4, 2);
                *(float *)(state + 0x28c) = *(float *)(moby + 0x18) + 260.0f;
            }
        }
        if (!*(int *)(state + 0x2ac)) {
            pitchField3 = (float *)(moby + 0xf4);
            pitch = func_00283248(func_00282E80(moby + 0x10, D_00189E20.target2290 + 0x10),
                *(float *)(D_00189E20.target2290 + 0x18) - *(float *)(moby + 0x18));
            func_002AAA00(pitchField3, (float *)(state + 0x270),
                -pitch, 0.005026549f, 0.005026549f, 0.25132746f, 0);
        }
        if (!func_PAL_002AF6C0(moby, 1.5f)) break;
        angle = func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14));
        if (!(func_00283C80(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        func_0029FCC0((char *)moby, 2, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        func_0029FCC0((char *)moby, 3, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        break;
    case 6:
        func_L01_00322288((int)moby, func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14)));
        if (func_PAL_L09_0032B088((char *)moby, *(int *)(state + 0x298)) &&
            *(int *)(state + 0x29c) != -1) func_002A7750(moby, 7, -1);
        pitchField6 = (float *)(moby + 0xf4);
        pitch = func_00283248(func_00282E80(moby + 0x10, D_00189E20.target2290 + 0x10),
            *(float *)(D_00189E20.target2290 + 0x18) - *(float *)(moby + 0x18));
        func_002AAA00(pitchField6, (float *)(state + 0x270),
            -pitch, 0.005026549f, 0.005026549f, 0.25132746f, 0);
        if (!func_PAL_002AF6C0(moby, 1.5f)) break;
        angle = func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14));
        if (!(func_00283C80(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        func_0029FCC0((char *)moby, 2, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        func_0029FCC0((char *)moby, 3, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 7:
        func_L01_00322288((int)moby, func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14)));
        if (func_PAL_L09_0032B088((char *)moby, *(int *)(state + 0x29c)) &&
            *(int *)(state + 0x298) != -1) func_002A7750(moby, 6, -1);
        pitchField7 = (float *)(moby + 0xf4);
        pitch = func_00283248(func_00282E80(moby + 0x10, D_00189E20.target2290 + 0x10),
            *(float *)(D_00189E20.target2290 + 0x18) - *(float *)(moby + 0x18));
        func_002AAA00(pitchField7, (float *)(state + 0x270),
            -pitch, 0.005026549f, 0.005026549f, 0.25132746f, 0);
        if (!func_PAL_002AF6C0(moby, 1.5f)) break;
        angle = func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14));
        if (!(func_00283C80(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        func_0029FCC0((char *)moby, 2, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        func_0029FCC0((char *)moby, 3, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 4:
        func_002AA548((float *)(moby + 0x18), (float *)(state + 0x290),
            *(float *)(state + 0x28c), 0.018000001f, 0.004f, 0.080000006f);
        if (!(*(float *)(state + 0x28c) - *(float *)(moby + 0x18) < 0.3f) ||
            *(int *)(state + 0x2ac)) break;
        if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
        func_002A7750(moby, 5, -1);
        if (*(int *)(state + 0x298) != -1) func_002A7750(moby, 6, -1);
        break;
    case 5:
        func_L01_00322288((int)moby, func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14)));
        pitchField5 = (float *)(moby + 0xf4);
        pitch = func_00283248(func_00282E80(moby + 0x10, D_00189E20.target2290 + 0x10),
            *(float *)(D_00189E20.target2290 + 0x18) - *(float *)(moby + 0x18));
        func_002AAA00(pitchField5, (float *)(state + 0x270),
            -pitch, 0.005026549f, 0.005026549f, 0.25132746f, 0);
        if (!func_PAL_002AF6C0(moby, 1.5f)) break;
        angle = func_00283248(D_00189E20.position80[0] - *(float *)(moby + 0x10),
            D_00189E20.position80[1] - *(float *)(moby + 0x14));
        if (!(func_00283C80(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        func_0029FCC0((char *)moby, 2, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        func_0029FCC0((char *)moby, 3, (char *)position);
        func_00282CF0(aim, D_00189E20.aimPositionE0, position);
        func_00282F20(aim, aim, 1.0000001f);
        if (!func_002761F8(position, D_00189E20.aimPositionE0, 0, moby, 0)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == D_00189E20.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            func_PAL_L16_0040A008(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    }
    if ((unsigned int)moby[0x20] - 6 < 2) {
        if (moby[0x42] == 3) {
            if (++*(int *)(state + 0x2b8) > 200) {
                if (moby[0x43]) func_PAL_002A7E68(moby, 0, 0, 8);
                *(int *)(state + 0x2b8) = 0;
            }
        } else if (!moby[0x42] && ++*(short *)(state + 0x25c) > 50) {
            if (moby[0x43] != 3) func_PAL_002A7E68(moby, 3, 0, 8);
            *(short *)(state + 0x25c) = 0;
        }
    }
    func_PAL_L16_00409AD0(moby);
}
