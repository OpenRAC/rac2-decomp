#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L20_001B1FD8 __attribute__((sda));

extern float D_L20_001B20B0 __attribute__((sda));

extern float D_L20_001B2110 __attribute__((sda));

extern float D_L20_001B2114 __attribute__((sda));

extern float D_L20_001B2118 __attribute__((sda));

extern float D_L20_001B211C __attribute__((sda));

extern float D_L20_001B213C __attribute__((sda));

extern float D_L20_001B2140 __attribute__((sda));

extern float D_L20_001B2144 __attribute__((sda));

extern float D_L20_001B2148 __attribute__((sda));

extern void func_002B60B0(char *, float, float, float, float);

extern void func_00282CC0(char *, char *, char *);

extern void func_00283098(char *, int *, char *);

/* Sets the motion limits of a moby from four stored settings, converting them to game units. */
void func_L20_00442140(char *moby) {
    SetControllerSpeedLimits(moby, D_L20_001B2114 * 0.000277777785f,
                  D_L20_001B2110 * 0.0166666675f,
                  D_L20_001B2118 * 4.84813745e-06f,
                  D_L20_001B211C * 0.000290888245f);
}

/* Sets the motion limits of a moby like the function above, and also stores an extra range value. */
void func_L20_00442740(char *moby, float range) {
    char *state = *(char **)(moby + 0x68);

    SetControllerSpeedLimits(moby, D_L20_001B2140 * 0.000277777785f,
                  D_L20_001B213C * 0.0166666675f,
                  D_L20_001B2148 * 4.84813745e-06f,
                  D_L20_001B2144 * 0.000290888245f);
    *(float *)(state + 0x84) = range;
}

/* Turns a point from the moby's own space into world space by rotating it and adding the moby position. */
void func_L20_00444C18(char *moby, char *point) {
    matrix_mul_vec3(point, &D_L20_001B20B0, moby + 0xC0);
    FastVecAdd(point, point, moby + 0x10);
}

extern void func_L00_002EC608(char *, int);

extern void func_L00_002EC970(TI128 *, char *, int, int, float, float);

/* Leaves a short glowing trail behind a moving moby. */
void func_L20_0043F510(char *moby) {
    TI128 position;
    char *state = *(char **)(moby + 0x68);

    DrawGlowQuad_L00(moby + 0x10, D_L20_001B1FD8);
    position = *(TI128 *)(moby + 0x10);
    DrawTaperedBeam(&position, state + 0x10, D_L20_001B1FD8, 3,
                      *(float *)(state + 0x74), 0.25f);
}

extern float D_L20_001B2024 __attribute__((sda));

extern void func_002B0990(void *, void *, int, int, float);

/* Counts up a frame counter on the moby, up to its limit, and plays its looping animation. */
void func_L20_00440150(char *moby) {
    char *state = *(char **)(moby + 0x68);
    unsigned short frameCount = *(unsigned short *)(moby + 0x96);

    if (frameCount <= 0xFFFE) {
        *(unsigned short *)(moby + 0x96) = frameCount + 1;
    }
    SetValueAndStartSmoothChange(moby, state + 0x2B0, 2, 1, D_L20_001B2024);
}

extern float D_L20_001B2090 __attribute__((sda));

extern int D_L20_001B2094 __attribute__((sda));

extern void func_00282F20(char *, char *, float);

extern void func_L20_00443B60(char *, char *, char *, float *);

extern void func_L20_0044B100(char *, char *, char *, char *, int, float, int);

/* func_L20_00444088 is defined in L20_00444088-g8.c (it needs its own flags). */

extern float D_L20_001B1FD0 __attribute__((sda));

extern float D_L20_001B1FD4;

extern int D_L20_001B1FC0 __attribute__((sda));

extern int D_L20_001B1FC4 __attribute__((nosda));

extern int D_001B1FC4 __attribute__((nosda));

extern int D_L20_001B1FC8 __attribute__((nosda));

extern int D_L20_001B1FCC __attribute__((nosda));

extern char D_L20_001A8F20[];

extern float func_002A7878(float, float);

extern int func_002A7820(int, int);

extern void func_002BDBC0(char *, char *, int, int, int, float);

/* Spawns a small particle at the moby with random speed and lifetime. */
void func_L20_0043F460(char *mobyArg) {
    char *moby = mobyArg;
    float speed;
    int lifetime;
    int colors[2];

    speed = RandomFloatRange(D_L20_001B1FD0, D_L20_001B1FD4) * 210000.0f;
    lifetime = RandomIntRange(0x14, 0x50);
    if (*(short *)(moby + 0xAA) == 0xB5A /* moby class 2906 */) {
        colors[0] = D_L20_001B1FC0;
        colors[1] = D_001B1FC4;
    } else {
        colors[0] = D_L20_001B1FC8;
        colors[1] = D_L20_001B1FCC;
    }
    SpawnGrowingPuffParticle(moby + 0x10, D_L20_001A8F20, D_L20_001B1FC0, D_L20_001B1FC4, lifetime, speed);
}
