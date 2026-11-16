#include "common.h"

extern void *CreateMoby(int);
extern float mat_fast_helper_a(float, float);
extern float vec_length_xy(void *);
extern char *part_spawn_sized(char *, int, float, unsigned int, float, int);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern int PlayMobySound(int, int, char *);
extern char g_hero_state_block[];

/* Creates a streaking projectile that flies along a direction with a trail, and tells the Receiver Bot owner that it fired. */
char *receiver_bot_spawn_streak_projectile(void *position, char *owner, float *direction,
                       int kind, int flags, float x, float y, float z)
{
    char *object = CreateMoby(0x1263 /* moby class 4707 */);
    char *state;
    float angle;
    int lifetime;

    if (object) {
        struct { unsigned short value; } mark;
        int half;
        mark.value = 255;
        *(unsigned short *)(object + 0x34) = 0x100;
        ((unsigned char *)object)[0x30] = mark.value;
        half = 255;
        *(unsigned short *)(object + 0x32) = half;
        state = *(char **)(object + 0x68);
        object[0x20] = 0;
        qcopy(state, direction);
        qcopy(object + 0x10, position);
        *(float *)(object + 0xf8) = mat_fast_helper_a(direction[0], direction[1]);
        angle = vec_length_xy(direction);
        *(float *)(object + 0xf4) = -mat_fast_helper_a(angle, direction[2]);
        *(char **)(state + 0x30) = part_spawn_sized(object, -1, 0.1f, 0xf0208080, 0.01f, 0x60);
        *(float *)(state + 0x1c) = y;
        qcopy(object + 0xc0, state);
        FastVecCross(object + 0xd0, object + 0xc0, g_hero_state_block);
        vec_scale_to_length(object + 0xd0, object + 0xd0, -1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        angle = FastVecLength(direction);
        angle = *(float *)(state + 0x1c) / angle;
        lifetime = FloatToInt(angle);
        *(float *)(state + 0x24) = z;
        *(int *)(state + 0x34) = lifetime;
        *(float *)(state + 0x20) = x;
        *(int *)(state + 0x28) = kind;
        *(int *)(state + 0x2c) = flags;
        *(char **)(state + 0x10) = owner;
        if (*(short *)(owner + 0xaa) == MOBY_CLASS_RECEIVER_BOT)
            PlayMobySound(5, 0, owner);
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
    }
    return object;
}
