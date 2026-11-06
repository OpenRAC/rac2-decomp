#include "common.h"

/* func_PAL_L11_0044CC18, the PAL copy of func_L11_004471A8: the same C, where the timer's reload
   value is scaled to 50 Hz and 1.0f / 60.0f becomes 0.020000001f. D_L11_001B19A8 is a word: USA's
   halfword load is its narrowing to the u16 timer, which the scale here no longer allows. */

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern s32 func_00282978(void *);
extern float *func_L11_004417E8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_PAL_L11_00465B28(void *, void *, void *, float, float, float, float);
extern TI128 D_00189EA0;
extern s32 D_L11_001B19A8 __attribute__((sda));
extern s32 D_L11_001B19AC __attribute__((sda));
extern float D_L11_001B19B0 __attribute__((sda));
extern float D_L11_001B19B4 __attribute__((sda));

typedef struct JobObject JobObject;

/* The record behind an object's +0x68 pointer for the kind handled by this function. */
typedef struct {
    u8 pad00[0x20];
    float health;           /* +0x20 */
    u8 pad24[0x34 - 0x24];
    u8 f34;
    u8 pad35[0x1FC - 0x35];
    u16 spawnTimer;         /* +0x1FC */
} JobState;

struct JobObject {
    u8 pad00[0x68];
    JobState *state;        /* +0x68 */
};

/* Spawns the effect at a random point around the object's anchor when its timer runs out. */
void func_PAL_L11_0044CC18(JobObject *object)
{
    float position[4], velocity[4], acceleration[4];
    JobState *state = object->state;
    float angle;
    float *base;
    int chance;
    u16 timer;

    if (func_00282978(&state->spawnTimer)) {
        timer = (D_L11_001B19A8 * 5 + 2) / 6;
        chance = D_L11_001B19AC;
        state->spawnTimer = timer;
        if (!func_002A77E0(chance)) {
            qcopy(position, &D_00189EA0);
            func_00282CF0(velocity, position, func_L11_004417E8(object));
            velocity[2] = 0;
            func_00282F20(velocity, velocity, D_L11_001B19B4);
            func_00282CC0(position, velocity, func_L11_004417E8(object));
            position[2] += 5.0f;
        } else {
            angle = func_002A7878(-3.1415927410125732f, 3.1415927410125732f);
            base = func_L11_004417E8(object);
            position[0] = base[0] + D_L11_001B19B4 * func_00283180(angle);
            base = func_L11_004417E8(object);
            position[1] = base[1] + D_L11_001B19B4 * func_00283198(angle);
            position[2] = func_L11_004417E8(object)[2] + 5.0f;
        }
        *(TI128 *)acceleration = 0;
        acceleration[2] = D_L11_001B19B0 * 0.020000001f;
        *(TI128 *)velocity = *(TI128 *)acceleration;
        func_PAL_L11_00465B28(object, velocity, position, state->health, (float)state->f34, 1.0f,
                          550.0f);
    }
}
