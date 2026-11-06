#include "include_asm.h"

#include "common.h"

/* func_PAL_00314678, the PAL copy of func_00313210: the same C, where the frame counts
 * 49 and 255 become 41 and 212, the mix's scale follows, and the lifetime is scaled to
 * 50 Hz. */

/* The particle pairs' instance data. */
typedef struct {
    char pad00[0x57];
    unsigned char altColors;    /* 0x57: use the second pair of colours */
    short timer[4];             /* 0x58: frames left for each pair */
    float angle[4];             /* 0x60: rotation of each pair, 0 to 255 */
} PairVars;

/* The moby fields this unit reads. */
typedef struct {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    char pad20[0x68 - 0x20];
    PairVars *vars;             /* 0x68 */
} Moby;

extern void func_00282CF0(float *out, float *a, float *b);
extern void func_00282CC0(float *out, float *a, float *b);
extern void func_00282F20(float *out, float *vector, float scale);
extern int func_00282978(short *timer);
extern float func_00283CE0(int value);
extern float func_00282C48(float value);
extern int func_00283CF0(float value);
extern int func_00283D38(unsigned int from, unsigned int to, float amount);
extern unsigned char *func_002C2FD8(float *position, int color, int angle, int, int, int, int,
                                    float size);
extern float D_001B5340[];                              /* the camera position */
extern int D_001AF174 __attribute__((sda));             /* the pairs' lifetime */
extern unsigned int D_001AF1C4 __attribute__((sda));    /* the colour pairs */
extern unsigned int D_001AF1C8 __attribute__((sda));
extern unsigned int D_001AF1CC __attribute__((sda));
extern unsigned int D_001AF1D0 __attribute__((sda));
extern int D_001AF1D4 __attribute__((sda));
extern int D_001AF1D8 __attribute__((sda));
extern float D_001AF1E0[4] __attribute__((sda));       /* spin per frame */
extern float D_001AF1F0[4] __attribute__((sda));       /* size */
extern float D_001AF200[4] __attribute__((sda));       /* height */
extern unsigned char *D_001F2540[];                     /* the texture table */

/* The loop reaches each pair's entries by byte offset (4 per float, 2 per timer), from a
 * fresh base pointer at every access: indexing them by pair, or sharing one base pointer,
 * changes the code. */
static __inline__ float *PairAngle(PairVars *vars, int offset)
{
    float *angles = vars->angle;

    return (float *)((char *)angles + offset);
}

static __inline__ short *PairTimer(PairVars *vars, int offset)
{
    short *timers = vars->timer;

    return (short *)((char *)timers + offset);
}

#define ANGLE(offset)        (*PairAngle(vars, (offset)))
#define TIMER(offset)        (*PairTimer(vars, (offset)))
#define ENTRY(table, offset) (*(float *)((offset) + (char *)(table)))

/* Draws the moby's four particle pairs, in a row behind it as seen from the camera, while
 * their timers run: each spins and fades with its timer. Returns 1 while one is above 40. */
int func_PAL_00314678(Moby *self)
{
    float position[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int count;
    int active = 0;
    PairVars *vars = self->vars;
    short *timer = vars->timer;
    int floatOffset = 0;
    int timerOffset = 0;
    int span = 212;
    float baseZ;
    float remaining;
    float mix;
    float duration;
    int oldAlpha;
    int color;
    int alpha;
    unsigned char *particle;

    func_00282CF0(position, D_001B5340, self->position);
    func_00282F20(position, position, -0.3f);
    func_00282F20(step, position, 0.1f);
    count = 3;
    func_00282CC0(position, position, self->position);
    baseZ = position[2];
    do {
        if (func_00282978(timer) == 0) {
            if (TIMER(timerOffset) >= 41)
                active = 1;
            ANGLE(floatOffset) += ENTRY(D_001AF1E0, floatOffset);
            if (ANGLE(floatOffset) >= 255.0f)
                ANGLE(floatOffset) -= 255.0f;
            else if (ANGLE(floatOffset) <= 0.0f)
                ANGLE(floatOffset) += 255.0f;

            mix = func_00282C48(0.5f - func_00283CE0(span - TIMER(timerOffset)) * 0.004716981f);
            if (vars->altColors)
                color = func_00283D38(D_001AF1CC, D_001AF1D0, mix);
            else
                color = func_00283D38(D_001AF1C4, D_001AF1C8, mix);
            oldAlpha = color >> 24;
            duration = func_00283CE0(((s32)(D_001AF174) * 5 + 2) / 6);
            remaining = 1.0f - (float)TIMER(timerOffset) / duration;
            alpha = func_00283CF0(func_00283CE0(oldAlpha) * (1.0f - remaining)) << 24;
            color = alpha | (color & 0xFFFFFF);

            position[2] = baseZ + ENTRY(D_001AF200, floatOffset);
            particle = func_002C2FD8(position, color, func_00283CF0(ANGLE(floatOffset)) & 255,
                                     D_001AF1D8, 0, 2, 1,
                                     ENTRY(D_001AF1F0, floatOffset) * remaining);
            if (particle != 0)
                particle[2] = D_001F2540[62][0];
            particle = func_002C2FD8(position, alpha | 0xFFFFFF,
                                     func_00283CF0(ANGLE(floatOffset)) & 255, D_001AF1D8,
                                     D_001AF1D4, 2, 1,
                                     ENTRY(D_001AF1F0, floatOffset) * 0.7f * remaining);
            if (particle != 0)
                particle[2] = D_001F2540[62][0];
            func_00282CC0(position, position, step);
        }
        floatOffset += 4;
        timerOffset += 2;
        timer++;
    } while (--count >= 0);
    return active;
}
