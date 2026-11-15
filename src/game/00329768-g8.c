#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));
typedef struct { char pad[0x10]; EffectVector position; } EffectObject;
typedef struct { char pad[0x24]; int kind; char *object; char pad2[0x3C]; int active; } EffectWorld;

extern EffectWorld g_music_state;
extern float D_001B0228 SDATA(D_001B0228);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(float *, float *, float);
extern float FastAddRotations(float, float);
extern float coll_get_ground_height_at_position(void *, void *);
extern void vec_clear_128(void *);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void part_spawn_drifting_2(void *, void *, int);
extern float fast_vec_dist(void *, void *);
extern int moby_place_at_collision_point_mirror(void *, void *);
extern void hero_check_under_falling_object(void *);
extern void part_spawn_ground_impact_effect(void *);
extern int SampleSurfaceHeightMap(void *, void *, float, float, float);
extern void part_emit_spark_burst(void *);
extern int PlayMobySound(int, int, void *);
extern void part_spawn_bubble(void *, void *, float, float);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void moby_do_nothing(void);

/* Updates a flying chunk (class 3032): it drops under gravity, sprays sparks, lands on the ground, bounces and fades out. */
void falling_chunk_update(char *moby)
{
    float previous_pos[4] __attribute__((aligned(16)));
    float hit[4], zero[4], random[4];
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(moby + 0x68);
    int i;
    float height;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        moby[0x20]=1;
        *(unsigned short *)(moby + 0x34)|=8;
        *(int *)(state + 0x40)=0;
        *(int *)(state + 0x38)=0;
        *(int *)(state + 0x48)=0;
        if (!g_music_state.active && g_music_state.kind==-1) {
            g_music_state.object=moby;
            g_music_state.kind=0xDB8;
        }
    case 1:
        qcopy(previous_pos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        *(float *)(state + 8)-=0.003055555745959282f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        coll_get_ground_height_at_position(moby + 0x10, hit);
        vec_clear_128(zero);
        for (i=7;i>=0;i--) {
            random[0]=math_random_signed_float_range(0, D_001B0228);
            random[1]=math_random_signed_float_range(0, D_001B0228);
            random[2]=math_random_signed_float_range(0, D_001B0228);
            FastVecAdd(random, random, moby + 0x10);
            part_spawn_drifting_2(random, state, math_random_int_range(20, 40));
        }
        fast_vec_dist(previous_pos, moby + 0x10);
        if (moby_place_at_collision_point_mirror(moby, previous_pos)) {
            hero_check_under_falling_object(moby);
            if (*(int *)(state + 0x38)==2) moby[0x20]=2;
            else {
                if (*(int *)(state + 0x38)) {
                    *(float *)(moby + 0x18)+=1;
                    *(EffectVector *)velocity = ((EffectObject *)moby)->position;
                    part_spawn_ground_impact_effect(velocity);
                    *(float *)(moby + 0x18)-=1;
                    SampleSurfaceHeightMap(moby + 0x18, velocity, *(float *)(moby + 0x10), *(float *)(moby + 0x14), *(float *)(moby + 0x18));
                    if (!*(int *)(state + 0x44)) part_emit_spark_burst(moby);
                }
                moby[0x20]=3;
                *(int *)(state + 0x34)=80;
            }
        }
        break;
    case 2:
        qcopy(previous_pos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        *(float *)(state + 8)-=0.003055555745959282f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        hero_check_under_falling_object(moby);
        if (*(int *)(state + 0x38)==1) {
            PlayMobySound(0, 0, moby);
            moby[0x20]=3;
            *(int *)(state + 0x34)=80;
            *(float *)(moby + 0x18)+=1;
            *(EffectVector *)position = ((EffectObject *)moby)->position;
            part_spawn_ground_impact_effect(position);
            *(float *)(moby + 0x18)-=1;
            SampleSurfaceHeightMap(moby + 0x18, velocity, *(float *)(moby + 0x10), *(float *)(moby + 0x14), *(float *)(moby + 0x18));
            if (!*(int *)(state + 0x44)) part_emit_spark_burst(moby);
        }
        break;
    case 3: {
        float one, low, high, scale;
        qcopy(previous_pos, moby + 0x10);
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        FastVecScale(state, state, 0.8f);
        *(float *)(state + 8)-=0.002444444689899683f;
        *(float *)(moby + 0xF4)=FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
        *(float *)(moby + 0xF8)=FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));
        fast_vec_dist(previous_pos, moby + 0x10);
        *(float *)(state + 0x14)*=0.8f;
        *(float *)(state + 0x18)*=0.8f;
        if ((unsigned char)moby[0x23] >= 3)
            moby[0x23] -= 2;
        else
            moby[0x23] = 0;
        one = 1.0f;
        low = -0.5f;
        high = 0.5f;
        scale = 0.2f;
        *(float *)(moby + 0x18)+=one;
        height=coll_get_ground_height_at_position(moby + 0x10, hit);
        *(float *)(moby + 0x18)-=one;
        velocity[0]=math_random_float_range(low, high);
        velocity[1]=math_random_float_range(low, high);
        velocity[2]=math_random_float_range(low, 2);
        velocity[3]=0;
        vec_scale_to_length(velocity, velocity, math_random_float_range(0.06666667f, 0.13333334f)*scale);
        part_spawn_bubble(moby + 0x10, velocity, math_random_float_range(0.05f, 0.1f)*210000.0f, height);
        if (math_fast_float_d(state + 0x34)) moby[0x20]=4;
        break;
    }
    case 4:
        if (!*(int *)(state + 0x40)) {
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    gfx_register_overlay_draw_callback(moby_do_nothing, moby);
}
