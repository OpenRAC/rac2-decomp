#include "common.h"

typedef int Quad __attribute__((mode(TI)));
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Partial view from a sound-slot anchor; anchors are spaced 0x70 bytes apart. */
typedef struct {
    char pad[0x74];
    unsigned char active;
    char pad75[0x13];
    void *owner;
} SoundAnchor;

extern unsigned char g_sound_state[];
extern char *g_moby_l17_pool;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern int moby_get_private_value_2(void *);
extern void moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);

/* Steers toward the linked object and maintains its movement sound. */
void follower_l17_update(char *obj)
{
    float velocity[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);

    if (!B(obj, 0x20)) {
        I(state, 0xA0) = -1;
        B(obj, 0x20) = 1;
    }
    I(state, 0x8C) |= 4;
    H(state, 0x3E) |= 8;
    velocity[0] = math_fast_sin_or_cos_a(F(obj, 0xF8)) * (1.0f / 15.0f);
    velocity[1] = math_fast_sin_or_cos_b(F(obj, 0xF8)) * (1.0f / 15.0f);
    velocity[2] = 0;
    mat_combine_and_store(state + 0x50, velocity, obj + 0xF0, obj + 0xF0);

    if (I(state, 0x90) == -1 ||
        !moby_get_private_value_2(g_moby_l17_pool + (I(state, 0x90) << 8))) {
        F(state, 0x9C) = F(state, 0x98) * (1.0f / 60.0f);
    } else {
        moby_transform_point_and_rotation_by_parent(obj, g_moby_l17_pool + (I(state, 0x90) << 8),
                      obj + 0x10, obj + 0xF0, target, dir);
        target[2] = 0;
        FastVecSub(delta, target, obj + 0x10);
        *(Quad *)target = *(Quad *)delta;
        dir[0] = math_fast_sin_or_cos_a(F(obj, 0xF8));
        dir[1] = math_fast_sin_or_cos_b(F(obj, 0xF8));
        dir[2] = 0;
        F(state, 0x9C) = FastVecDot(target, dir);
    }
    velocity[0] = math_fast_sin_or_cos_a(F(obj, 0xF8)) * F(state, 0x9C);
    velocity[1] = math_fast_sin_or_cos_b(F(obj, 0xF8)) * F(state, 0x9C);
    velocity[2] = 0;
    mat_combine_and_store(state + 0x50, velocity, obj + 0xF0, obj + 0xF0);
    F(obj, 0x48) = F(state, 0x9C) * 14.999999f;

    if (math_fabs(F(obj, 0x48)) < 0.1f) {
        if (I(state, 0xA0) != -1) {
            SoundAnchor *effect = (SoundAnchor *)(g_sound_state + I(state, 0xA0) * 0x70);
            if (effect->owner == obj && effect->active)
                snd_stop_voice(I(state, 0xA0));
        }
        I(state, 0xA0) = -1;
    } else {
        SoundAnchor *effect = (SoundAnchor *)(g_sound_state + I(state, 0xA0) * 0x70);
        if (effect->owner != obj || !effect->active)
            I(state, 0xA0) = PlayMobySound(0, 4, obj);
    }
}
