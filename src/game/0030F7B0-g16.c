#include "common.h"

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

extern void FastVecSub(float *out, float *a, float *b);
extern void FastVecAdd(float *out, float *a, float *b);
extern void vec_scale_to_length(float *out, float *vector, float scale);
extern int FastDecTimer(short *timer);
extern float IntToFloat(int value);
extern float math_fabs(float value);
extern int FloatToInt(float value);
extern int FastTweenColor(unsigned int from, unsigned int to, float amount);
extern unsigned char *part_spawn_fading(float *position, int color, int angle, int, int, int, int,
                                    float size);
extern float g_camera_eye_state[];                              /* the camera position */
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
 * their timers run: each spins and fades with its timer. Returns 1 while one is above 48. */
int EmitFourTimedParticlePairs(Moby *self)
{
    float position[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int count;
    int active = 0;
    PairVars *vars = self->vars;
    short *timer = vars->timer;
    int floatOffset = 0;
    int timerOffset = 0;
    float baseZ;
    float remaining;
    float mix;
    float duration;
    int oldAlpha;
    int color;
    int alpha;
    unsigned char *particle;

    FastVecSub(position, g_camera_eye_state, self->position);
    vec_scale_to_length(position, position, -0.3f);
    vec_scale_to_length(step, position, 0.1f);
    count = 3;
    FastVecAdd(position, position, self->position);
    baseZ = position[2];
    do {
        if (FastDecTimer(timer) == 0) {
            if (TIMER(timerOffset) >= 49)
                active = 1;
            ANGLE(floatOffset) += ENTRY(D_001AF1E0, floatOffset);
            if (ANGLE(floatOffset) >= 255.0f)
                ANGLE(floatOffset) -= 255.0f;
            else if (ANGLE(floatOffset) <= 0.0f)
                ANGLE(floatOffset) += 255.0f;

            mix = math_fabs(0.5f - IntToFloat(255 - TIMER(timerOffset)) * 0.003921569f);
            if (vars->altColors)
                color = FastTweenColor(D_001AF1CC, D_001AF1D0, mix);
            else
                color = FastTweenColor(D_001AF1C4, D_001AF1C8, mix);
            oldAlpha = color >> 24;
            duration = IntToFloat(D_001AF174);
            remaining = 1.0f - (float)TIMER(timerOffset) / duration;
            alpha = FloatToInt(IntToFloat(oldAlpha) * (1.0f - remaining)) << 24;
            color = alpha | (color & 0xFFFFFF);

            position[2] = baseZ + ENTRY(D_001AF200, floatOffset);
            particle = part_spawn_fading(position, color, FloatToInt(ANGLE(floatOffset)) & 255,
                                     D_001AF1D8, 0, 2, 1,
                                     ENTRY(D_001AF1F0, floatOffset) * remaining);
            if (particle != 0)
                particle[2] = D_001F2540[62][0];
            particle = part_spawn_fading(position, alpha | 0xFFFFFF,
                                     FloatToInt(ANGLE(floatOffset)) & 255, D_001AF1D8,
                                     D_001AF1D4, 2, 1,
                                     ENTRY(D_001AF1F0, floatOffset) * 0.7f * remaining);
            if (particle != 0)
                particle[2] = D_001F2540[62][0];
            FastVecAdd(position, position, step);
        }
        floatOffset += 4;
        timerOffset += 2;
        timer++;
    } while (--count >= 0);
    return active;
}
