#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
/* The cutscene record: the group of L19_0042A860.c (entity count at 0x44,
 * entity list at 0x18C) with its state and frame counter at 0x30. */
typedef struct {
    u8 pad0[0x30];
    s32 state;
    s32 frame;
    u8 pad38[0x44 - 0x38];
    s16 count;
    u8 pad46[0x18C - 0x46];
    char *items[1]; /* bounded by count */
} L19Cutscene;
extern L19Cutscene D_L19_001BD740;
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks, mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
/* Separate scalars: only a plain symbol operand is one instruction to cc1, so
 * only these reach the delay slots where retail has their $gp forms. */
extern int D_001A79F0 MACRO_ADDR;
extern char *D_L19_001B2814 MACRO_ADDR;
extern Vec D_L19_001B2820 MACRO_ADDR;
extern float D_L19_001B2830 MACRO_ADDR;
extern float D_L19_001B2834 MACRO_ADDR;
extern float D_L19_001B2838 MACRO_ADDR;
extern float D_L19_001B283C MACRO_ADDR;
extern float D_L19_001B2840 MACRO_ADDR;
extern int D_L19_001B2844 MACRO_ADDR;
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void func_L00_002FC980(void);
extern void func_PAL_002E7270(void *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern int func_00283D38(float, int, int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002AF000(float *, float, float, float);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *func_002C7BB8(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *func_PAL_002BE880(void *, void *, int, int, float, int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(char *, char *, char *);

/* func_PAL_L19_002FBA78, the PAL copy of func_L19_002FA1A8: the same C, with
 * the 50 Hz timings and rates, the actor 4000 effect left out in level 51 as
 * in USA v2.00, and PAL's callees. */
void func_PAL_L19_002FBA78(void)
{
    Vec position, direction, axis;
    char *actor;
    int i;
    func_L00_002FC980();
    for (i = 0; i < D_L19_001BD740.count; i++) {
        actor = D_L19_001BD740.items[i];
        if (actor && *(short *)(actor + 0xaa) == 0xe29)
            *(unsigned short *)(actor + 0x34) |= 0x800;
        /* Retail makes this test without a null check: it also reads an
         * empty slot. */
        if (*(short *)(actor + 0xaa) == 0xd54)
            func_PAL_002E7270(actor);
        if (actor) {
            /* Held in a local: its longer life makes the first loop pass hoist
             * it, ahead of the items pointer. The level's 51 waits for the
             * second pass and lands after that pointer, as in retail. */
            int id = 4000;
            if (*(short *)(actor + 0xaa) == id && D_001A79F0 != 51 && *(char **)(actor + 0x68))
                func_L00_00326048(actor, (float *)(*(char **)(actor + 0x68) + 0xc), 0x80aaaad2, 0x80396464, 0.07330384f);
        }
    }
    if (D_001A79F0 == 19) {
        if (D_L19_001BD740.state == 4) {
            int frame = D_L19_001BD740.frame;
            if (frame == 1) {
                D_L19_001B2814 = D_L19_001BD740.items[3];
                D_L19_001B2830 = 3.5f;
                D_L19_001B2834 = 11.0f;
                D_L19_001B2838 = 10.7f;
                D_L19_001B283C = 0.0f;
                D_L19_001B2840 = 0.0f;
                D_L19_001B2844 = frame;
            }
            D_L19_001B2820.q = *(Quad *)(D_L19_001B2814 + 0x10);
            if (frame == 750) {
                D_L19_001B9900.strength = 1.0f;
                D_L19_001B9900.ticks = 15;
                D_L19_001B9900.mode = 0;
            }
            if (D_L19_001BD740.frame >= 750 && D_L19_001BD740.frame <= 770) {
                D_L19_001B2840 += D_L19_001B2838;
                if (D_L19_001B2840 >= 1.0f) {
                    do {
                        int color;
                        float angle;
                        direction.q = 0;
                        direction.f[0] = 0.72f;
                        direction.f[1] = -0.72f;
                        direction.f[3] = 1.0f;
                        color = ((u32)func_002A7820(96, 128) << 16) | 0x1e00;
                        position.f[0] = 0.0f;
                        position.f[1] = D_L19_001B2830 * func_002A7878(0.9f, 1.1f);
                        position.f[2] = 0.0f;
                        position.f[3] = 1.0f;
                        angle = func_002A7878(0.0f, 6.2831855f);
                        func_002ACEC0(&position, &position, &direction, angle);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        func_00282F20(&direction, &direction, func_002A7878(1.5f, 2.5f));
                        func_00282CC0((char *)&position, (char *)&position, (char *)&direction);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&direction);
                        D_L19_001B2840 -= 1.0f;
                        {
                            int life = func_002A7820(4, 8);
                            float speed = func_002A7878(0.6f, 0.8f) * 210000.0f;
                            func_002C7970(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, 0);
                        }
                        {
                            int life = func_002A7820(4, 8);
                            float speed = func_002A7878(0.6f, 0.8f) * 210000.0f;
                            int style = func_002A7820(1, 7);
                            func_002C7970(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, style);
                        }
                    } while (D_L19_001B2840 >= 1.0f);
                }
            }
            if (D_L19_001BD740.frame >= 761 && D_L19_001BD740.frame <= 839) {
                D_L19_001B283C += D_L19_001B2834;
                if (D_L19_001B283C >= 1.0f) {
                    do {
                        int color, life, style;
                        float speed, other, angle;
                        color = func_00283D38(func_002A7878(0.0f, 1.0f), 0x803c14, 0x400000);
                        position.f[0] = 0.0f;
                        position.f[1] = 0.0f;
                        position.f[2] = D_L19_001B2830 * -0.8f;
                        position.f[3] = 1.0f;
                        direction.f[0] = 1.0f;
                        direction.f[1] = 0.0f;
                        direction.f[2] = 0.0f;
                        direction.f[3] = 1.0f;
                        /* Retail never writes axis.f[0] before this rotation. */
                        axis.f[1] = 0.0f;
                        axis.f[2] = 1.0f;
                        axis.f[3] = 1.0f;
                        func_002ACEC0(&direction, &direction, &axis, func_002A7878(0.0f, 6.2831855f));
                        angle = func_002A7878(0.0f, 1.5707964f);
                        func_002ACEC0(&position, &position, &direction, angle);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        life = func_002A7820(22, 55);
                        style = func_002A7820(0, 10);
                        speed = func_002A7878(0.5f, 1.0f) * 21000.0f;
                        other = func_002A7878(0.7f, 1.0f) * 21000.0f;
                        func_002C7BB8(&position, D_L19_001A8F20, life, color, style, 128, 0, speed, other, 0.0033333334f, 3);
                        D_L19_001B283C -= 1.0f;
                    } while (D_L19_001B283C >= 1.0f);
                }
            }
        }
        if (D_001A79F0 == 19 && D_L19_001BD740.state == 5 && D_L19_001BD740.frame == 1146) {
            char *burstActor = D_L19_001BD740.items[4];
            int n;
            for (n = 0; n < 47; n++) {
                int color, style, life, red, gray, high;
                float speed, angle, pitch, radius;
                radius = func_002A7878(0.0f, 0.37f);
                angle = func_002A7940();
                pitch = func_002A7940();
                func_002AF000(direction.f, radius, angle, pitch);
                func_00282CC0((char *)&direction, (char *)&direction, burstActor + 0x10);
                radius = func_002A7878(0.0074000005f, 0.028f);
                angle = func_002A7940();
                pitch = func_002A7940();
                func_002AF000(position.f, radius, angle, pitch);
                red = func_002A7820(47, 87);
                gray = func_002A7820(100, 220);
                speed = func_002A7878(70000.0f, 150000.0f);
                /* Built in two steps: as one expression cc1 regroups the four
                 * terms and shares an OR with style, unlike retail. */
                high = (red << 24) | (gray << 16) | (gray << 8);
                color = high | gray;
                style = (gray << 16) | (gray << 8) | gray;
                life = func_002A7820(11, 35);
                func_PAL_002BE880(&direction, &position, color, style, speed, life);
            }
        }
    }
}
