/* functional: high. The matching draft with one name fixed: the weather origin is D_L01_001B94C0 (lui 0x1C - 0x6B40), not D_L01_001C94C0. Same reads, writes and calls as retail. SAME on 4 calls (level 01), 532 of 542 instructions ran; the unrun ones (level 512 counting as special, the D_L01_001AF640 >= 0 override, an unknown state going straight to the final copy, the reset call when func_002829D8 fires, the speed clamp to the minimum) were read against retail. */
/* func_L01_00399510 (2168 bytes): the level's rain/snow emitter: picks the heavy or light profile by level, then each frame spawns drops around the hero (count scaled by the camera's height), lifting them to the floor, and extra splashes; finally stores the hero origin for the next frame. */
/* GPT-6.1 Sol (high), USA v1.01 retained reconstruction, 29 October 2026.
 * Best check.py result: 2164 bytes versus 2168, 0 of 3 places match
 * (levels 01, 15, 19). Relocations remain unvalidated because sizes differ.
 * Profile: -O2 -G8 -mno-split-addresses -ffunction-sections -ffast-math
 *          -g -frac2-hazard-labels.
 * The earlier 2144-byte draft recompiles unchanged under this toolchain.
 * This version uses ordinary TI copies, a measured hero position/rotation
 * view, short-lived radial offsets, and guarded countdown do/while loops.
 * It recovers the retail 0x110 frame, offset-result f20 reuse and bnez
 * backedges. The two clamp max.s operand orders now follow retail too.
 * Remaining: broad GPR/address construction and scheduling differences.
 * The first loop hoists -jitter, occupying f22 and moving length to f21;
 * retail computes -jitter inside each velocity branch and keeps length f22.
 * Hero position versus containing-object base lifetimes still differ.
 * Normalization divisions have the right order, but surrounding scheduling
 * and pointer construction remain different.
 * Other measured controls: default split-addresses gave 2124 bytes;
 * -fno-gcse gave 2136 bytes and a wrong 0x100 frame. Explicitly retaining
 * heroPosition gave 2192 bytes; a private-state struct gave 2176 bytes and
 * spilled its pointer. That struct aligned the normalization instruction
 * sequence, but did not resolve the address or first-loop allocation issues.
 * Next useful experiment: recover the original per-region hero pointer
 * lifetimes and a source explanation for branch-local jitter negation.
 * All required declarations follow; no additional helper is needed.
 */
#include "common.h"
typedef unsigned int WeatherQuad __attribute__((mode(TI)));
typedef struct {
    char pad[0x140];
    float position[4];
    float rotation[4];
} WeatherHero;

extern int D_001A79F0 NOT_SDA;
extern int D_L01_001C9A40 NOT_SDA;
extern int D_L01_001A94C0 SDATA(D_L01_001A94C0);
extern float D_L01_001AF62C SDATA(D_L01_001AF62C);
extern float D_L01_001AF630 SDATA(D_L01_001AF630);
extern float D_L01_001AF634 SDATA(D_L01_001AF634);
extern float D_L01_001AF640 SDATA(D_L01_001AF640);
extern int D_L01_001AF644 SDATA(D_L01_001AF644);
extern float D_L01_001AF648 SDATA(D_L01_001AF648);
extern float D_L01_001AF64C SDATA(D_L01_001AF64C);
extern float D_L01_001AF650 SDATA(D_L01_001AF650);
extern float D_L01_001AF654 SDATA(D_L01_001AF654);
extern float D_L01_001B27B0 SDATA(D_L01_001B27B0);
extern float D_L01_001B2F00 NOT_SDA;
extern int D_L01_001B2F04 NOT_SDA;
extern float D_L01_001B2EF0 NOT_SDA;
extern float D_L01_001B2EF4[] NOT_SDA;
extern float D_L01_001B208C NOT_SDA;
extern float D_L01_001B2090 NOT_SDA;
extern char D_L01_001B94C0[];
extern char D_L01_001B27A0[];
extern int func_002ACD38(void *);
extern void func_L01_003993C8(int);
extern int func_002829D8(void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L00_00323F28(void *, void *, float, float, float);
extern float func_002B0520(void *);
extern void func_002B0668(void *);
extern void func_L01_00326DD8(void *, int, void *, float);
extern void func_L01_00331CA0(void *, int, void *, float);

void func_L01_00399510(char *m)
{
    float pos[4], delta[4], origin[4], velocity[4], velocity2[4];
    int special, extras, count, i, level;
    float falloff, speed, minimum, jitter;
    char *p;

    if (!func_002ACD38(m + 0x10))
        return;
    D_L01_001A94C0 = D_L01_001C9A40;
    level = D_001A79F0;
    switch (level) {
    case 12: case 19: case 512: special = 1; break;
    default: special = 0; break;
    }
    switch (special) {
    case 1:
        falloff = 0.2f; speed = 5.0f; minimum = 0.5f;
        jitter = 0.01666666753590107f; extras = 0;
        break;
    case 0:
    default:
        falloff = 0.15f; extras = 1; speed = 18.0f;
        minimum = D_L01_001AF62C; jitter = 0.033333335070610046f;
        break;
    }
    if (D_L01_001AF640 >= 0.0f)
        minimum = D_L01_001AF640;
    p = *(char **)(m + 0x68);
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        *(unsigned char *)(m + 0x20) = 2;
        *(unsigned char *)(m + 0x30) = 255;
        func_L01_003993C8(special);
        p += 0x30;
        goto finish;
    case 2: {
        float x, y, scale, z;
        WeatherHero *hero;
        if (func_002829D8(&D_L01_001B2F00))
            func_L01_003993C8(special);
        p += 0x30;
        func_00282CF0(delta, D_L01_001B94C0, p);
        x = D_L01_001B2090 - D_L01_001AF64C;
        y = D_L01_001B208C - D_L01_001AF650;
        *(WeatherQuad *)(D_L01_001B27A0) = *(WeatherQuad *)(delta);
        count = D_L01_001B2F04;
        if (x < 0.0f) x = 0.0f;
        if (y < 0.0f) y = 0.0f;
        x /= 1.0f - D_L01_001AF64C;
        y /= 1.0f - D_L01_001AF650;
        z = func_00283CE0(count);
        scale = 1.0f - (x > y ? x : y) * D_L01_001AF654;
        count = func_00283CF0(z * scale);
        hero = (WeatherHero *)(D_L01_001B94C0 - 0x140);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(hero->position);
        func_L00_00323F28(origin, origin, 16.0f, hero->rotation[2], hero->rotation[1]);
        origin[2] = hero->position[2] + D_L01_001AF630;
        if (count > 0) {
            i = count;
            do {
                float offset, length, z, floor, scale;
                *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
                offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, D_L01_001AF634);
                pos[0] += offset;
                offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, D_L01_001AF634);
                pos[1] += offset;
                func_00282CF0(velocity, pos, hero->position);
                length = func_00282E20(velocity);
                if (length <= 8.0f) {
                    velocity2[0] = D_L01_001B2EF0 + func_002A7878(-jitter, jitter);
                    velocity2[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
                    velocity2[2] = -(speed * 0.01666666753590107f);
                } else {
                    scale = speed - (length - 8.0f) * falloff;
                    if (scale < minimum) scale = minimum;
                    velocity2[0] = D_L01_001B2EF0 + func_002A7878(-jitter, jitter);
                    velocity2[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
                    velocity2[2] = -(scale * 0.01666666753590107f);
                }
                velocity2[3] = 0.0f;
                D_L01_001B27B0 = hero->position[2] - D_L01_001AF648;
                z = func_002B0520(pos);
                if (z < hero->position[2] + D_L01_001AF630) {
                    int flag = 0;
                    floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                    if (length > 8.0f) flag = D_L01_001AF644;
                    if (special == 0) func_L01_00326DD8(pos, flag, velocity2, floor);
                    if (special == 1) func_L01_00331CA0(pos, flag, velocity2, floor);
                }
            } while (--i != 0);
        }
        count = (int)((float)count * 1.4f);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(hero->position);
        origin[2] = hero->position[2] + D_L01_001AF630;
        if (count > 0) {
            i = count;
            do {
                float offset, z, floor;
                velocity[0] = D_L01_001B2EF0 + func_002A7878(-jitter, jitter);
                velocity[1] = D_L01_001B2EF4[0] + func_002A7878(-jitter, jitter);
                velocity[2] = -(speed * 0.01666666753590107f);
                velocity[3] = 0.0f;
                *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
                offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 8.0f);
                pos[0] += offset;
                offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 8.0f);
                pos[1] += offset;
                D_L01_001B27B0 = hero->position[2] - D_L01_001AF648;
                z = func_002B0520(pos);
                if (z < hero->position[2] + D_L01_001AF630) {
                    floor = z < D_L01_001B27B0 ? D_L01_001B27B0 : z;
                    if (special == 0) func_L01_00326DD8(pos, 0, velocity, floor);
                    if (special == 1) func_L01_00331CA0(pos, 0, velocity, floor);
                }
            } while (--i != 0);
        }
        break;
    }
    default:
        p += 0x30;
        goto finish;
    }
    if (extras) {
        WeatherHero *hero = (WeatherHero *)(D_L01_001B94C0 - 0x140);
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        func_L00_00323F28(origin, origin, 30.0f, hero->rotation[2], hero->rotation[1]);
        origin[2] = hero->position[2] + D_L01_001AF630;
        if (count > 0) {
            i = count;
            do {
                float offset;
                *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
                offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 30.0f);
                pos[0] += offset;
                offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 30.0f);
                pos[1] += offset;
                func_002B0668(pos);
            } while (--i != 0);
        }
        *(WeatherQuad *)(origin) = *(WeatherQuad *)(D_L01_001B94C0);
        func_L00_00323F28(origin, origin, 4.0f, hero->rotation[2], hero->rotation[1]);
        origin[2] = hero->position[2] + D_L01_001AF630;
        if (count > 0) {
            i = count;
            do {
                float offset;
                *(WeatherQuad *)(pos) = *(WeatherQuad *)(origin);
                offset = func_00283180(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 8.0f);
                pos[0] += offset;
                offset = func_00283198(func_002A7878(0.0f, 6.2831854820251465f));
                offset *= func_002A7878(0.0f, 8.0f);
                pos[1] += offset;
                func_002B0668(pos);
            } while (--i != 0);
        }
    }
finish:
    *(WeatherQuad *)(p) = *(WeatherQuad *)(D_L01_001B94C0);
}
