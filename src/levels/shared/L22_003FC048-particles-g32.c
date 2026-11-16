#include "common.h"

typedef struct {
    u8 pad[0x60];
    u8 * particles[8];
} Controller;
typedef struct {
    u8 pad[4];
    int colour;
    u8 pad08[4];
    float size;
} ParticleHeader;
typedef struct {
    u8 pad[8];
    float radius;
    float angle;
} ParticleState;

extern float ref_L22_003FC048_00[8] __attribute__((sda));
extern float ref_L22_003FC048_01 __attribute__((sda)), ref_L22_003FC048_02 __attribute__((sda)), ref_L22_003FC048_03 __attribute__((sda));
extern float ref_L22_003FC048_04 __attribute__((sda)), ref_L22_003FC048_05 __attribute__((sda));
extern int ref_L22_003FC048_07 __attribute__((sda));
extern u8 ref_L22_003FC048_08 __attribute__((sda));
extern u8 * g_effect_owner_moby;
extern u8 g_tether_origin[];
extern float math_fast_sin_or_cos_b(float), FastAddRotations(float, float), vec_distance_xy(void *, void *);
extern void part_rotate_anchor_table(void), part_get_anchor_position(void *, void *, int), gfx_draw_pulsing_ring(void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void FastVecScale(void *, void *, float), FastVecAdd(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern u8 * part_spawn_bluish_fade(void *, int, int, int);

/* Update existing particles and maintain eight persistent effect slots. */
void part_update_effect_particles(u8 * obj) {
    float p[4], tmp[4], point[4], origin[4], zero[4];
    Controller * ctl = *(Controller **)(obj + 0x68);
    int i, count;
    float distance;
    u8 **slot;

    if (obj[0x20] == 0) {
        int j;
        for (j = 0; j < 8; j++) {
            u8 * v = ctl->particles[j];
            if (v) {
                u8 * s = v + 0x20;
                *(float *)(s + 8) = ref_L22_003FC048_01 * math_fast_sin_or_cos_b(*(float *)(s + 12)) + ref_L22_003FC048_02;
                *(float *)(s + 12) = FastAddRotations(*(float *)(s + 12), ref_L22_003FC048_00[j]);
            }
        }
    }
    if (g_effect_owner_moby == obj)
        part_rotate_anchor_table();
    qcopy(p, obj + 0x10);
    FastVecScale(tmp, obj + 0xE0, ref_L22_003FC048_03);
    FastVecAdd(p, p, tmp);
    p[3] = 1.0f;
    if (math_fast_helper_a(p, 64.0f) < 0)
        return;
    gfx_add_draw_callback_first(gfx_draw_pulsing_ring, obj);
    if (obj[0x20])
        return;
    distance = vec_distance_xy(obj + 0x10, g_tether_origin);
    if (distance > 30.0f)
        count = 2;
    else if (distance > 10.0f)
        count = 20;
    else
        count = 40;
    for (i = 0, slot = ctl->particles; i < 8; i++, slot++) {
        u8 * v, *old;
        part_get_anchor_position(obj, point, i);
        v = part_spawn_bluish_fade(point, count, 2, 0);
        if (v) {
            u8 * s = v + 0x20;
            qcopy(origin, obj + 0x10);
            qzero_nc(zero);
            FastVecAdd(point, point, zero);
            *(float *)(s + 0x10) = *(float *)(v + 0x10)-origin[0];
            *(float *)(s + 0x14) = *(float *)(v + 0x14)-origin[1];
            *(float *)(s + 0x18) = *(float *)(v + 0x18)-origin[2];
            if (obj[0x20] == 0)
                *(u8 **)(s + 4) = obj;
            else
                *(u8 **)(s + 4) = *(u8 **)(obj + 0xB8);
            ((ParticleHeader *)v)->colour = ref_L22_003FC048_07;
            ((ParticleHeader *)v)->size = ref_L22_003FC048_04;
        }
        old = *slot;
        if (!old) {
            *slot=part_spawn_bluish_fade(point,0,1,0);
            v = *slot;
            if (v) {
                ParticleState * s = (ParticleState *)(v + 0x20);
                s->angle = 0.0f;
                s->radius = ref_L22_003FC048_02;
                ((ParticleHeader *) * slot)->size = ref_L22_003FC048_05;
                ((ParticleHeader *) * slot)->colour = ref_L22_003FC048_07;
            }
        } else {
            qcopy(old + 0x10, point);
            old[8] += ref_L22_003FC048_08;
        }
    }
}
