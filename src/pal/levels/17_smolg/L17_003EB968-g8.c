#include "include_asm.h"
#include "common.h"
extern u8 *part_l17_spawn_fading(f32, s32, s32, s32);
extern f32 g_effect_spawner_seconds __attribute__((sda));
extern void moby_set_state(void *, s32, s32);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);
extern void moby_mark_spawned(void *);
extern s32 g_hit_burst_piece_param __attribute__((sda));
extern s32 g_hit_burst_piece_table_c __attribute__((sda));
extern s32 g_hit_burst_piece_table_b __attribute__((sda));
extern s32 g_hit_burst_piece_table_a __attribute__((sda));

/* Sets the object's stage up: the first stage asks the level's own spawner for a child and
   gives up its handle, the second one only releases the handle. */
void hit_l17_burst_update_pal(s32 obj)
{
    u8 stage = *(u8 *)(obj + 0x20);

    switch (stage) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x4010001, 0) != 0) {
            moby_set_state(obj, 2, -1);
            *(u8 *)(obj + 0xA8) = 0xFF;
        }
        break;
    case 2:
        part_explode_object_into_pieces(obj, &g_hit_burst_piece_table_c, &g_hit_burst_piece_table_b, &g_hit_burst_piece_table_a,
                          0xFFFF, 0, g_hit_burst_piece_param, 0, 0xFFFF, 0xFF, 0);
        SpawnExplosion(obj + 0x10, 0, 12, 10, 10, 10, 0, 0,
                      *(f32 *)(obj + 0x2C) * 10.0f, 20.0f, 1, 0, 0, 0);
        moby_mark_spawned(obj);
        break;
    }
}

typedef int Quad __attribute__((mode(TI)));
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
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
extern char *moby_get_private_value_2(void *);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);

/* Steers toward the linked object and maintains its movement sound. */
void follower_l17_update_pal(char *obj)
{
    float stage[4] __attribute__((aligned(16)));
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
    stage[0] = math_fast_sin_or_cos_a(F(obj, 0xF8)) * (0.080000006f);
    stage[1] = math_fast_sin_or_cos_b(F(obj, 0xF8)) * (0.080000006f);
    stage[2] = 0;
    mat_combine_and_store(state + 0x50, stage, obj + 0xF0, obj + 0xF0);

    if (I(state, 0x90) == -1 ||
        !moby_get_private_value_2(g_moby_l17_pool + (I(state, 0x90) << 8))) {
        F(state, 0x9C) = F(state, 0x98) * (0.020000001f);
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
    stage[0] = math_fast_sin_or_cos_a(F(obj, 0xF8)) * F(state, 0x9C);
    stage[1] = math_fast_sin_or_cos_b(F(obj, 0xF8)) * F(state, 0x9C);
    stage[2] = 0;
    mat_combine_and_store(state + 0x50, stage, obj + 0xF0, obj + 0xF0);
    F(obj, 0x48) = F(state, 0x9C) * 12.499999f;

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
