#include "include_asm.h"
#include "names.h"

/* Functions of 0032EB28.c whose retail body reaches its resident object through $gp
   (`addiu $v0,$gp,-0x16C8`). A file named *-g8.c is built with -G8 (config/cflags.txt),
   which is what makes the compiler emit that form. */

extern int D_001AD928 __attribute__((sda));
extern int D_001AD908 __attribute__((sda));
extern void F7242f0a4_FUN_00335AE0(void *);

/* Sets up an object with the first shared table of actions. */
void func_00335D80(void *object) {
    *(void **)object = &D_001AD928;
    F7242f0a4_FUN_00335AE0(object);
}

/* Sets up an object with the second shared table of actions. */
void func_00335DA0(void *object) {
    *(void **)object = &D_001AD908;
    F7242f0a4_FUN_00335AE0(object);
}

extern float D_L00_001B2708 __attribute__((sda));
extern void func_00300A00(int, int, float, float, float, float, float);

/* Draws a screen element at its stored place and size, unless it is switched off. */
void func_00336320(char *object)
{
    float *first;
    float *second;
    if (**(float **)(object + 0x10) == 0.0f)
        return;
    if (*(int *)(object + 0x40) == 0)
        return;
    first = *(float **)object;
    second = *(float **)(object + 4);
    DrawScaledObjectTwoAxes(*(int *)(object + 0x40), **(int **)(object + 0xC), first[0], first[1],
                 second[0], second[1] * D_L00_001B2708, **(float **)(object + 0x38));
}

extern void func_002FC808(void);
extern void func_00330EC0(void *);
extern void func_002FDBD8(void *, void *, int, float);
extern float ref_L00_00330E48_00 __attribute__((sda));
/* Draws the ring effect while it is small and draws its trail while it is active. */
void func_00330E48(char *owner)
{
    char *data;
    AppendVu1DmaChainTable3();
    data = *(char **)(owner + 0x68);
    if (*(float *)(data + 0x64) < ref_L00_00330E48_00)
        DrawShockwaveRing(owner);
    if (*(int *)(data + 0x78))
        DrawSpinningBillboardPair(data + 0x30, data + 0x40, 0, 0.2f);
}

extern int D_001B1688;
extern char *D_001B1B68;
extern float ref_L00_00330BC0_00 __attribute__((sda));
extern float func_00282E48(void *, void *);
extern void func_00302440(void *, void *);

/* Pushes nearby objects of one kind away from this object while the effect is on. */
void func_00330BC0(char *object)
{
    char *cursor;
    if (gGameTime & 1) {
        cursor = D_001B1B68;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (fast_vec_dist(cursor + 0x10, object + 0x10) < ref_L00_00330BC0_00)
                    StartPickupFlyIfIdle(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}

extern float D_001B284C;
/* The retail reaches 0x1B284C twice: through lui/lwc1 (D_001B284C) and through
   $gp+0x385C (ref_L00_0032FEA8_00).  The compiler picks one form per symbol. */
extern float ref_L00_0032FEA8_00 __attribute__((sda));
extern int D_001B2850;
extern float D_001B2854;
extern float D_001B09A0 __attribute__((sda));
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032FFD8(void *);
extern void func_00330150(void *);
extern void func_003304D8(void *);

/* Speeds up or slows down the vehicle and moves it forward by that speed. It then updates its corners, ground probes and ground contact. */
void func_0032FEA8(char *object)
{
    char *data = *(char **)(object + 0x68);
    float value;
    int flag;
    char buffer[16];

    if (gStickLength != 0.0f && D_001B2850 != 0) {
        value = *(float *)(data + 0x58) + gStickLength * (1.0f / 120.0f);
        *(float *)(data + 0x58) = value;
        if (FloatAbs(value) > D_001B09A0 * (1.0f / 60.0f))
            *(float *)(data + 0x58) = D_001B09A0 * ref_L00_0032FEA8_00 * (1.0f / 60.0f);
    } else {
        *(float *)(data + 0x58) = *(float *)(data + 0x58) * 0.85f;
    }

    flag = D_001B2850;
    value = *(float *)(data + 0x58) * 25.0f;
    *(float *)(object + 0x48) = value;
    if (flag == 0)
        *(float *)(object + 0x48) = value + (D_001B2854 + D_001B2854);

    vec_scale_to_length(buffer, object + 0xC0, *(float *)(data + 0x58));
    FastVecAdd(object + 0x10, object + 0x10, buffer);
    BuildObjectBasisVectors(object);
    SweepMobyArcProbe(object);
    SettleVehicleOnGround(object);
}

/* func_00335DC0: the retail reaches its three globals through $gp (the int at $gp+0x3710 and
   the float at $gp+0x3718) and through lui/addiu (the float at 0x1B2704), so the unit is the
   -G8 one.  The three live in the level's data, at an address that differs from level to
   level, so they are named without an address. */
extern int ref_L00_00335DC0_00 __attribute__((sda));
extern float ref_L00_00335DC0_01;
extern float ref_L00_00335DC0_02 __attribute__((sda));

/* func_00331718 reaches four of its globals through $gp, so it belongs in this unit.
   The float at the same address is reached twice under two names: once through $gp
   (ref_L00_00331718_03) and once through lui/lwc1 (ref_L00_00331718_04).

   It needs the unit ASSEMBLED with -Wa,-G32: the retail reaches the base of its two
   32-byte tables through $gp (addiu $a0,$gp,0x1940), and the assembler's relaxation of
   `la` into addiu $reg,$gp,off fires only for symbols of at most its -G threshold, which
   is 8 by default.  With -Wa,-G32 the function is the retail's 200 bytes, word for word;
   without it it is 208 bytes (the two lui/addiu pairs for the table addresses).
   config/cflags.txt needs:
       src/game/0032EB28-g8.c	-O2 -G8 -ffunction-sections -Wa,-G32
   The flag is safe for the rest of this unit: its other functions take the address of
   4-byte sda symbols, which the retail reaches through $gp as well. */
extern int *ref_L00_00331718_00 __attribute__((sda));
extern int ref_L00_00331718_01[8] __attribute__((sda));
extern float ref_L00_00331718_02[8] __attribute__((sda));
extern float ref_L00_00331718_03 __attribute__((sda));
extern float ref_L00_00331718_04;

extern float func_0029F530(int *);
extern void func_002E5CF8(int, int, int *);

/* Plays a sound whenever a tracked value crosses one of eight set levels. */
void func_00331718(void)
{
    float value;
    float threshold;
    float diff;
    float old;
    int i;

    if (ref_L00_00331718_00 == 0)
        return;
    value = GetMobyAnimationValue(ref_L00_00331718_00);
    for (i = 0; i < 8; i++) {
        threshold = ref_L00_00331718_02[i];
        diff = value - threshold;
        if (diff > 0.0f) {
            /* the positive case is handled after the join */
        } else {
            old = ref_L00_00331718_03 - threshold;
            if (old > 0.0f) {
                /* fall through to the join */
            } else {
                continue;
            }
        }
        if (diff < 0.0f) {
            PlayMobySound(ref_L00_00331718_01[i], 0, ref_L00_00331718_00);
            ref_L00_00331718_03 = value;
            return;
        }
        old = ref_L00_00331718_04 - threshold;
        if (old < 0.0f) {
            PlayMobySound(ref_L00_00331718_01[i], 0, ref_L00_00331718_00);
            ref_L00_00331718_03 = value;
            return;
        }
    }
    ref_L00_00331718_04 = value;
}

/* Switches two scale values between their normal and changed settings. */
void func_00335DC0(int a0)
{
    float value;

    ref_L00_00335DC0_00 = a0;
    value = 1.076923f;
    if (a0 == 0)
        value = 1.0f;
    ref_L00_00335DC0_01 = value;
    value = 0.9f;
    if (a0 == 0)
        value = 1.0f;
    ref_L00_00335DC0_02 = value;
}
