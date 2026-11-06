#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00391958);


typedef int Quad __attribute__((mode(TI)));
extern int D_L00_001B19C8 __attribute__((section(".sdata")));
extern void func_00282D30(void *, void *, float);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(Quad *);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float), func_00283CF0(float);
extern void func_002B00D8(void *, float *, float *, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
/* func_PAL_L00_00392250, the PAL copy of func_L00_0038F178: the same C, where the kind, duration and size take the 50 Hz scale, 0.016666668f becomes 0.020000001f and 0.0011111111f becomes 0.0016000001f. */
void func_PAL_L00_00392250(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float offset[4], velocity[4], jitter[4];
    float *jitterPoint, *velocityPoint;
    int firstColor, lastColor, kind, duration, size, count;
    if (D_L00_001B19C8 & 7) return;
    jitterPoint = jitter;
    velocityPoint = velocity;
    count = 0;
    do {
        count--;
        func_00282D30(offset, state, 0.5f);
        func_002A7A00(jitterPoint, 0.0f, 0.020000001f);
        func_00282CC0(offset, jitterPoint, offset);
        func_00282C88((Quad *)velocityPoint);
        offset[3] = func_002A7878(0.25f, 0.15f);
        velocity[3] = func_002A7878(0.15f, 0.05f);
        firstColor = func_00283D38(0x804080FF, 0x8040FFFF, func_002A7878(0.0f, 1.0f));
        lastColor = func_00283D38(0x80104040, 0x80002080, func_002A7878(0.0f, 1.0f));
        kind = func_00283CF0(((func_002A7878(0.0f, 1.0f) + 1.0f) * 5.0f + 2.0f) * 0.16666667f);
        duration = func_00283CF0(((func_002A7878(-0.5f, 0.5f) + 1.0f) * 150.0f + 2.0f) * 0.16666667f);
        size = func_00283CF0(((func_002A7878(-0.5f, 0.5f) + 1.0f) * 50.0f + 2.0f) * 0.16666667f);
        func_002B00D8(actor + 0x10, velocityPoint, velocityPoint, (float)duration * 0.0016000001f);
        func_002BAA28(actor + 0x10, offset, velocityPoint, firstColor, lastColor, kind, duration, size, 0x10019);
    } while (count >= 0);
}

extern int F6eb4f363_FUN_002A77E0(int mode);
extern float F6eb4f363_FUN_002A90F8(char *object, char *local);
extern void F6eb4f363_FUN_00282D30(char *local, int value, float scale);
extern float F6eb4f363_FUN_002A7878(float low, float high);
extern void F6eb4f363_FUN_002BF728(char *object, char *local, float amount, float base);

/* func_00303568 is defined in 00303568.c. */




/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

void func_PAL_L00_00392500(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(4))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}


extern int func_002A77E0(int mode);
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef float f32;
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;
extern void func_0029F338(NativeUpdate775View *object);
typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors D_L00_001AF010;
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002AAFA0(int, int);
extern void func_002BAE50(void *, void *, int, int, int, int, int, int);
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003253A0(void *, void *, void *, float);
extern float func_00283CE0(int);
extern int func_00282978(short *);

void func_PAL_L00_00392718(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (func_002A77E0(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = D_L00_001AF010;
        random.quad = 0;
        random.f[0] = func_002A7878(-1.0f, 1.0f);
        random.f[1] = func_002A7878(-1.0f, 1.0f);
        random.f[2] = func_002A7878(-1.0f, 1.0f);
        direction.quad = random.quad;
        func_00282F20(&direction, &direction, 0.020000001f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = func_002AAFA0(colors.color[func_002A77E0(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            func_002BAE50(object + 0x10, &direction, color,
                         func_002AAFA0(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         37, 50, 120, 1);
        } else {
            func_002BAE50(object + 0x10, &direction, colors.color[func_002A77E0(4)],
                         0x4FFF, 37, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    func_00282CC0(object + 0x10, object + 0x10, state);
    func_L00_003253A0(object, state, state, 0.00584f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        func_0029F338((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = func_00283CE0(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  func_00283CE0(*(short *)(state + 0x1A) / 4);
    }
    if (func_00282978((short *)(state + 0x18)))
        func_0029F338((NativeUpdate775View *)object);
}


/* func_PAL_L00_003929E0, the PAL copy of func_L00_0038F8B8: the same C, where 40, 23 and 60 become 33, 19 and 50, and the time stat takes the 50 Hz scale at each read. */
/* Partial resident view: only fields observed by the launch gate are named. */
typedef struct { char pad00[0xA8]; unsigned short launches; char padAA[2]; unsigned int bestTime, mask; } LaunchStats;
typedef struct {
    char pad00[0x33C]; char *support; int grounded; char pad344[0x434]; float heading;
    char pad77C[0xAB4]; unsigned int buttons; char pad1234[0xC]; int resource;
    char pad1244[0x2BC]; int special; char pad1504[0xD90]; int level;
    char pad2298[4]; int state; char pad22A0[0x1C]; unsigned char busy; char pad22BD[0x22F];
    short platform; char pad24EE[0x46]; int cooldown; char pad2538[8];
} TetherLaunchHero;
extern TetherLaunchHero D_00189E20;
extern LaunchStats D_0018C360;
extern int D_L00_001A8F00[] __attribute__((sda)), D_L00_001A8F08[] __attribute__((sda));
typedef struct { char pad00[0x1A4]; unsigned int buttons; } LaunchInput;
extern LaunchInput D_00138180;
extern unsigned int D_001A7390 __attribute__((section(".sdata")));
extern unsigned int D_001A79F0[] __attribute__((sda));
extern char *D_L00_001B8E10;
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern float func_00282E20(void *), func_00283248(float, float);
extern void func_002AF000(float *, float, float, float), func_00282CC0(void *, void *, void *);
extern void func_PAL_002A7E68(void *, int, int, int), func_PAL_L00_002F5D28(void);
extern char *func_PAL_L00_00394148(char *, char *, float, float);
extern int func_002E5CF8(int, int, char *);
/* Starts the tether when the shared input and movement gates permit it. */
void func_PAL_L00_003929E0(char *actor) {
    int *state;
    int ready;
    float point[4];
    float heading, pitch;
    if (!actor) return;
    state = *(int **)(actor + 0x68);
    ready = 1;
    func_00282948(state);
    if (D_00189E20.level == 29) { if (!func_00282948(&D_00189E20.cooldown)) ready = 0; }
    else D_00189E20.cooldown = 33;
    if (D_L00_001A8F00[0] || D_L00_001A8F08[0] != -2 || !(D_00138180.buttons & D_00189E20.buttons) || state[0] || state[1] || D_00189E20.busy) goto finish;
    if (D_00189E20.state == 7 || D_00189E20.state == 2 || D_00189E20.state == 3 || D_00189E20.state == 4 || D_00189E20.state == 5 || D_00189E20.state == 6 || D_00189E20.state == 16 || D_00189E20.state == 14 || D_00189E20.state == 9 || D_00189E20.state == 10 || D_00189E20.state == 11 || D_00189E20.state >= 13 || D_00189E20.level == 111 || D_00189E20.level == 98) goto finish;
    if ((D_L00_001B8E10 && *(short *)(D_L00_001B8E10 + 0x86) == 5) || !D_00189E20.grounded || D_00189E20.resource < 19) goto finish;
    if (D_00189E20.support && (*(short *)(D_00189E20.support + 0xAA) == 0x13E || *(short *)(D_00189E20.support + 0xAA) == 0x46F) && ready) goto finish;
    if (!func_L00_002D3F30(-1, 1)) goto denied;
    pitch = 0.0f;
    heading = D_00189E20.heading;
    if (D_00189E20.platform == 1 || D_00189E20.special) {
        pitch = func_00283248(func_00282E20(actor + 0xD0), *(float *)(actor + 0xD8));
        func_002AF000(point, 0.6f, heading, -pitch);
        func_00282CC0(point, point, actor + 0x10);
    } else {
        func_002AF000(point, 0.6f, heading, -pitch);
        func_00282CC0(point, point, actor + 0x10);
    }
    if (*(unsigned char *)(actor + 0x43) != 3) func_PAL_002A7E68(actor, 3, 0, 0);
    func_PAL_L00_002F5D28();
    *(char **)(state + 1) = func_PAL_L00_00394148(actor, (char *)point, heading, pitch);
    if (D_0018C360.launches < 0xFFFF) D_0018C360.launches++;
    if (D_0018C360.bestTime < (((int)(D_001A7390) * 5 + 2) / 6)) D_0018C360.bestTime = (((int)(D_001A7390) * 5 + 2) / 6);
    D_0018C360.mask |= 1U << D_001A79F0[0];
    D_0018C360.mask |= 0x80000000;
    state[0] = 50;
    goto finish;
denied:
    if (D_00138180.buttons & D_00189E20.buttons) func_002E5CF8(0, 0, actor);
finish:
    if ((*(unsigned char *)(actor + 0x60) & 2) && *(u8 *)(actor + 0x43) != 1) func_PAL_002A7E68(actor, 1, 0, 0);
    *(unsigned short *)(actor + 0x34) |= 4;
}
