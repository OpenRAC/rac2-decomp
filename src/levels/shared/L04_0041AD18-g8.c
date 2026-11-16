#include "common.h"

/* Advances a falling object through impact, particle emission and fade-out. */
typedef int Quad __attribute__((mode(TI)));
extern int g_debris_initialized __attribute__((sda));
typedef struct { char pad[0x34]; int owner; char tail[8]; } ParticleRecord;
extern ParticleRecord g_debris_particle_records[100];
typedef struct { char pad[0x24]; int kind; char *owner; char tail[0x3C]; int active; } OwnerContext;
extern OwnerContext g_music_state;
extern char g_spark_origin_quad[0x30];
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastAddRotations(float, float), fast_vec_dist(void *, void *);
extern void part_claim_spark_record(void *), SpawnObjectParticle(void *, void *, float);
extern int moby_place_at_collision_point(void *, void *);
extern void hero_check_hit_by_object(void *);
extern int PlayMobySound(int, int, void *);
extern float math_random_angle(void), math_random_float_range(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void part_spawn_white_flash(void *, void *, int, float);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *), part_update_orbiting_sparks(void *), part_update_object_particles(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern char g_debris_draw_callback_data[];
/* Updates a falling piece of debris: it falls, bursts into sparks when it hits something, then fades and goes away. */
void falling_l04_debris_update_2(char *self)
{
    float previous[4], velocity[4];
    char *state = *(char **)(self + 0x68);
    float angle, elevation;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0: {
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x48) = 0;
        {
            int initialized = g_debris_initialized;
            *(int *)(state + 0x4C) = 0;
            *(int *)(state + 0x50) = 0;
            if (!initialized) {
                int i;
                for (i = 99; i >= 0; i--) g_debris_particle_records[i].owner = 0;
                g_debris_initialized = 1;
            }
        }
        {
            OwnerContext *context = &g_music_state;
            if (!context->active && context->kind == -1) {
                context->owner = self;
                context->kind = 0xDB9;
            }
        }
    }
    /* Fall through to move the object on its first update. */
    case 1:
        *(Quad *)previous = *(Quad *)(self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.00305555575f;
        *(float *)(self + 0xF4) = FastAddRotations(*(float *)(self + 0xF4), *(float *)(state + 0x14));
        *(float *)(self + 0xF8) = FastAddRotations(*(float *)(self + 0xF8), *(float *)(state + 0x18));
        part_claim_spark_record(self);
        SpawnObjectParticle(self, self + 0x10, fast_vec_dist(previous, self + 0x10) * 0.5f);
        if (moby_place_at_collision_point(self, previous)) {
            *(unsigned char *)(self + 0x20) = 2;
            *(int *)(state + 0x44) = 20;
            *(int *)(state + 0x58) = 128;
            *(unsigned short *)(self + 0x34) |= 8;
            vec_clear_128(state);
            hero_check_hit_by_object(self);
            PlayMobySound(0, 0, self);
            FastVecScale(state + 0x20, g_spark_origin_quad + 0x20, 0.0009765625f);
            vec_scale_to_length(state + 0x20, state + 0x20, 1.0f);
            *(Quad *)(state + 0x30) = *(Quad *)g_spark_origin_quad;
            if (!*(int *)(state + 0x54)) {
                float *v = velocity;
                int i;
                for (i = 7; i >= 0; i--) {
                    angle = math_random_angle();
                    elevation = math_random_float_range(0.392699093f, 3.14159274f);
                    vec_build_spherical_offset(v, 0.13333334f, angle, elevation);
                    part_spawn_white_flash(self + 0x10, v, 0, -1.0f);
                }
            }
        }
        break;
    case 2:
        SpawnObjectParticle(self, self + 0x10, 0.1f);
        FastVecAdd(self + 0x10, self + 0x10, state);
        *(float *)(state + 8) -= 0.00152777787f;
        *(unsigned char *)(self + 0x23) -= 4;
        math_fast_float_d((int *)(state + 0x44));
        if (*(unsigned char *)(self + 0x23) > 4) *(unsigned char *)(self + 0x23) -= 4;
        if (!*(int *)(state + 0x44) && *(unsigned char *)(self + 0x23) < 4) *(unsigned char *)(self + 0x20) = 3;
        break;
    case 3:
        if (*(unsigned char *)(self + 0x23)) --*(unsigned char *)(self + 0x23);
        if (*(int *)(state + 0x58) >= 5) *(int *)(state + 0x58) -= 4;
        else if (*(int *)(state + 0x58) > 0) --*(int *)(state + 0x58);
        if (!*(long long *)(state + 0x48) && !*(int *)(state + 0x58)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(self + 0x98) = 0;
            *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 4:
        if (math_fast_float_d((int *)(state + 0x5C))) {
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    part_update_orbiting_sparks(self);
    part_update_object_particles(self);
    gfx_add_draw_callback_third(g_debris_draw_callback_data, self);
}
