#include "include_asm.h"

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
extern char *func_PAL_002C84A8(void *, void *, int);
extern float fast_vec_dist(void *, void *);
extern int moby_place_at_collision_point_mirror(void *, void *);
extern void func_PAL_0032B730(void *);
extern void part_spawn_ground_impact_effect(void *);
extern int SampleSurfaceHeightMap(void *, void *, float, float, float);
extern void func_PAL_0032B650(void *);
extern int PlayMobySound(int, int, void *);
extern void *func_PAL_002C0428(void *, void *, float, float);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void func_PAL_0032B920(void);

void func_PAL_0032AF58(char *self)
{
    float old[4] __attribute__((aligned(16)));
    float hit[4], zero[4], random[4];
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    int i;
    float height;
    switch ((unsigned char)self[0x20]) {
    case 0:
        self[0x20]=1;
        *(unsigned short *)(self + 0x34)|=8;
        *(int *)(state + 0x40)=0;
        *(int *)(state + 0x38)=0;
        *(int *)(state + 0x48)=0;
        if (!g_music_state.active && g_music_state.kind==-1) {
            g_music_state.object=self;
            g_music_state.kind=0xDB8;
        }
    case 1:
        qcopy(old, self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8)-=0.0044f;
        *(float *)(self + 0xF4)=FastAddRotations(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=FastAddRotations(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        coll_get_ground_height_at_position(self + 0x10, hit);
        vec_clear_128(zero);
        for (i=7;i>=0;i--) {
            random[0]=math_random_signed_float_range(0, D_001B0228);
            random[1]=math_random_signed_float_range(0, D_001B0228);
            random[2]=math_random_signed_float_range(0, D_001B0228);
            FastVecAdd(random, random, self + 0x10);
            func_PAL_002C84A8(random, state, math_random_int_range(20, 40));
        }
        fast_vec_dist(old, self + 0x10);
        if (moby_place_at_collision_point_mirror(self, old)) {
            func_PAL_0032B730(self);
            if (*(int *)(state + 0x38)==2) self[0x20]=2;
            else {
                if (*(int *)(state + 0x38)) {
                    *(float *)(self + 0x18)+=1;
                    *(EffectVector *)velocity = ((EffectObject *)self)->position;
                    part_spawn_ground_impact_effect(velocity);
                    *(float *)(self + 0x18)-=1;
                    SampleSurfaceHeightMap(self + 0x18, velocity, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
                    if (!*(int *)(state + 0x44)) func_PAL_0032B650(self);
                }
                self[0x20]=3;
                *(int *)(state + 0x34)=67;
            }
        }
        break;
    case 2:
        qcopy(old, self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8)-=0.0044f;
        *(float *)(self + 0xF4)=FastAddRotations(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=FastAddRotations(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        func_PAL_0032B730(self);
        if (*(int *)(state + 0x38)==1) {
            PlayMobySound(0, 0, self);
            self[0x20]=3;
            *(int *)(state + 0x34)=67;
            *(float *)(self + 0x18)+=1;
            *(EffectVector *)position = ((EffectObject *)self)->position;
            part_spawn_ground_impact_effect(position);
            *(float *)(self + 0x18)-=1;
            SampleSurfaceHeightMap(self + 0x18, velocity, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
            if (!*(int *)(state + 0x44)) func_PAL_0032B650(self);
        }
        break;
    case 3: {
        float one, low, high, scale;
        qcopy(old, self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, state);
        FastVecScale(state, state, 0.8f);
        *(float *)(state + 8)-=0.00352f;
        *(float *)(self + 0xF4)=FastAddRotations(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8)=FastAddRotations(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        fast_vec_dist(old, self + 0x10);
        *(float *)(state + 0x14)*=0.8f;
        *(float *)(state + 0x18)*=0.8f;
        if ((unsigned char)self[0x23] >= 3)
            self[0x23] -= 2;
        else
            self[0x23] = 0;
        one = 1.0f;
        low = -0.5f;
        high = 0.5f;
        scale = 0.2f;
        *(float *)(self + 0x18)+=one;
        height=coll_get_ground_height_at_position(self + 0x10, hit);
        *(float *)(self + 0x18)-=one;
        velocity[0]=math_random_float_range(low, high);
        velocity[1]=math_random_float_range(low, high);
        velocity[2]=math_random_float_range(low, 2);
        velocity[3]=0;
        vec_scale_to_length(velocity, velocity, math_random_float_range(0.080000006f, 0.16000001f)*scale);
        func_PAL_002C0428(self + 0x10, velocity, math_random_float_range(0.05f, 0.1f)*210000.0f, height);
        if (math_fast_float_d(state + 0x34)) self[0x20]=4;
        break;
    }
    case 4:
        if (!*(int *)(state + 0x40)) {
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    gfx_register_overlay_draw_callback(func_PAL_0032B920, self);
}
