#include "include_asm.h"

#include "common.h"
extern float Fe617c30b_FUN_00283CE0(int a);
extern void Fe617c30b_FUN_00282D30(char *p, char *q, float f);
extern void Fe617c30b_FUN_00282CC0(char *p, char *q, char *r);
extern int Fe617c30b_FUN_002A9568(int a, int b, float f);
extern int Fe617c30b_FUN_00282978(char *p);
extern void Fe617c30b_FUN_002B9180(char *p);

/* func_002BAE50 is matched in its own unit, src/game/002BAE50.c (default flags). */

/* Scales a particle over its lifetime, moves it with a slowing velocity, steps its color and removes it when its time is up (PAL). */
void part_update_scaling_pal(char *part)
{
    char *data = part + 32;
    int lifetime;
    int scaled;
    int time_left;
    float f;

    lifetime = *(int *)(data + 28);
    time_left = *(short *)(part + 10);
    scaled = *(short *)(data + 24) * (lifetime - time_left) / lifetime + *(short *)(data + 26);

    f = Fe617c30b_FUN_00283CE0(scaled) * 1000.0f;
    *(float *)(part + 12) = f;
    Fe617c30b_FUN_00282D30(data, data, 0.976f);
    Fe617c30b_FUN_00282CC0(part + 16, part + 16, data);
    *(unsigned char *)(part + 8) = *(unsigned char *)(part + 8) + 1;
    f = Fe617c30b_FUN_00283CE0(*(int *)(data + 28));
    *(int *)(part + 4) = Fe617c30b_FUN_002A9568(*(int *)(data + 20), *(int *)(data + 16),
                               (float)*(short *)(part + 10) / f);
    if (Fe617c30b_FUN_00282978(part + 10) != 0)
        Fe617c30b_FUN_002B9180(part);
}


extern void part_kill(char *);
extern s32 math_fast_float_d(void *);
extern void vec_transform_or_copy(char *, char *);

/* Moves a particle with a transform, grows it with a step value and fades its alpha out over the last 5 frames, removing it when its timer runs out. */
void part_update_moving_fade_out_pal(u8 *part)
{
    u8 *part_ptr = part;
    u8 *data = part + 0x20;

    if (math_fast_float_d((char *)data) != 0) {
        part_kill((char *)part_ptr);
        return;
    }
    {
        u8 *pos = part_ptr + 0x10;

        vec_transform_or_copy((char *)pos, (char *)pos);
    }
    *(f32 *)(part_ptr + 0xC) = *(f32 *)(part_ptr + 0xC) + *(f32 *)(data + 4);
    if (*(s32 *)(data) < 5) {
        *(unsigned int *)(part_ptr + 4) = (*(unsigned int *)(part_ptr + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(data) * 127 / 5) << 24);
    }
}


/* func_PAL_002BBCC0 lives in 002BBCC0.c. */

extern int Fb77d67f1_FUN_00282948(char *p);
extern void Fb77d67f1_FUN_002B9180(char *p);

/* Grows a particle with a step value and fades its alpha out over the last 5 frames, removing it when its timer runs out. */
void part_update_growing_fade_out_pal(char *part)
{
    char *data = part + 32;

    if (Fb77d67f1_FUN_00282948(data) != 0) {
        Fb77d67f1_FUN_002B9180(part);
        return;
    }
    *(float *)(part + 12) = *(float *)(part + 12) + *(float *)(data + 4);
    if (*(int *)(part + 32) < 5)
        *(int *)(part + 4) = (*(int *)(part + 4) & 0xFFFFFF)
                         | ((*(int *)(part + 32) * 127 / 5) << 24);
}

