#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B23E8 __attribute__((sda));

extern float D_L20_001B23EC __attribute__((sda));

extern float D_L20_001B23F0 __attribute__((sda));

extern float D_L20_001B23F8 __attribute__((sda));

extern float D_L20_001B2410 __attribute__((sda));

extern float D_L20_001B2414 __attribute__((sda));

extern float D_L20_001B241C __attribute__((sda));

extern float D_L20_001B2450 __attribute__((sda));

extern float D_L20_001B2454 __attribute__((sda));

extern int D_L20_001B2AC8 __attribute__((sda));

extern void func_002A7750(char *, int, int);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *dst, void *src, float x);

extern float func_00282E20(void *vec);

extern void func_00282F70(char *a, char *b);

extern void func_002C9218(char *a, char *b, char *c, float f);

extern void func_0032DA58(char *, char *, void *, float);

/* func_002A8C28 returns a value here: retail keeps $v0 live after the call,
   and only a non-void prototype gives the flag word $v1 instead of $v0. */
extern int func_002A8C28(char *, char *, int, int, float, float, float, int, int);

extern float func_00283B98(float, float);

extern float func_00283198(float);

extern void func_002A9288(char *, float);

extern float func_00283248(float, float);

extern float func_002AAA00(char *a, char *b, int c, float d, float e, float f,
                            float g);

extern float func_002AA2E8(float *, float, float);

extern void *func_0029EFD0(int);

extern void func_002B37E8(u8 *, u8 *);

extern float func_002A7940(void);

extern void func_002833F0(void *, void *);

extern float func_002A7878(float a, float b);

extern int func_00277F48(float f, char *a, int b, char *c, int d);

extern void func_L20_00444C18(char *arg0, char *arg1);

extern char D_L20_001B9FC0[] __attribute__((nosda));

/* Turns the turret to face its target and eases its yaw and pitch toward the aimed angles. */
void func_L20_0044AA88(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *angles = moby + 0xF8;
    float deltaX = *(float *)(state + 0x140) - *(float *)(moby + 0x10);
    float deltaY = *(float *)(state + 0x144) - *(float *)(moby + 0x14);
    float smallStep = D_L20_001B2450 * 4.84813745e-06f;
    float turnStep = D_L20_001B2454 * 0.000290888245f;
    float heading;

    heading = FastMatrixHelperA(deltaX, deltaY);
    ApproachTargetWithDirectionMode(angles, state + 0x1A4, 0, heading, smallStep, smallStep, turnStep);
    turnStep = turnStep * 4.0f;
    ApproachValue(moby + 0x0F0, *(float *)(state + 0x1A8), turnStep);
    *(float *)(state + 0x1A8) = 0.0f;
    ApproachValue(moby + 0x0F4, *(float *)(state + 0x1AC), turnStep);
    *(float *)(state + 0x1AC) = 0.0f;
}

/* Makes the object vanish with an impact effect and puts it back into its resting state. */
void func_L20_00449AE8(char *moby) {
    TI128 offset;

    FastVecSub(&offset, D_L20_001B9FC0, moby + 0x10);
    vec_scale_to_length(&offset, &offset, 1.0f);
    SpawnBlastEffectMoby(moby, moby + 0x10, &offset, *(float *)(moby + 0x18) - 0.5f);
    SweepCollisionFromObject(moby, moby + 0x10, 0x10000, 0, 6.0f, D_L20_001B23EC, 2.0f,
                  1, 0);
    *(int *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
    SetMobyState(moby, 1, -1);
}

/* func_L20_0044A838 is defined in L20_0044A838-g8.c. */

/* func_L20_00449BB0 is defined in L20_00449BB0-g8.c. */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* The moby fields func_L20_00449FD0 sets.  Written as casts of byte offsets, these four
   accesses let the scheduler put the $gp scale load after the pVars load; as struct
   members they give retail's order.  The float/int/float parameter order follows the
   0x14/0x18/0x1C fields it fills (a0-a3 and $f12/$f13 are assigned as before). */
typedef struct {
    u8 pad00[0x20];
    u8 state;        /* 0x20 */
    u8 pad21[3];
    char *pClass;    /* 0x24 */
    u8 pad28[4];
    float scale;     /* 0x2C */
    u8 pad30[4];
    u16 flags;       /* 0x34 */
    u8 pad36[0x68 - 0x36];
    char *pVars;     /* 0x68 */
} Moby449FD0;

/* Creates a new projectile (moby class 4846) at a position, with a direction, speed and lifetime, and returns it. */
char *func_L20_00449FD0(char *template, char *position, char *direction, float speed, int lifetime,
                        float extraValue) {
    char *projectile;
    char *state;

    projectile = CreateMoby(0x12EE /* moby class 4846 */);
    if (projectile != 0) {
        InitChildObjectFromParent((u8 *)projectile, (u8 *)template);
        qcopy(projectile + 0x10, position);
        *(float *)(projectile + 0xF0) = RandomAngle();
        *(float *)(projectile + 0xF4) = RandomAngle();
        euler_rotation_basis(projectile + 0xC0, projectile + 0xF0);
        ((Moby449FD0 *)projectile)->state = 1;
        ((Moby449FD0 *)projectile)->flags |= 0x100;
        ((Moby449FD0 *)projectile)->scale =
            *(float *)(((Moby449FD0 *)projectile)->pClass + 0x24) * D_L20_001B23F8;
        state = ((Moby449FD0 *)projectile)->pVars;
        qcopy(state, direction);
        *(float *)(state + 0x14) = speed * 0.016666668f;
        *(int *)(state + 0x18) = lifetime;
        *(float *)(state + 0x1C) = extraValue;
        *(int *)(state + 0x20) = 0x3C;
        *(float *)(state + 0x10) = RandomFloatRange(10.0f, 20.0f) * 0.00027777778f;
    }
    return projectile;
}

/* func_L20_0044B100 is defined in L20_0044B100-g8.c. */

/* func_L20_0044A658 is defined in L20_0044A658-g8.c. */

/* func_L20_0044A8F0 is defined in L20_0044A8F0-g8.c. */

/* func_L20_00449338 is defined in L20_00449338-g8.c. */
