#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern int g_frame_l03_counter MACRO_ADDR;
extern Vector g_laser_bot_beam_origin __attribute__((sda));
extern Vector g_laser_bot_beam_end __attribute__((sda));
extern u8 g_effect_descriptor_default[] MACRO_ADDR;
extern u8 g_collision_direction[];
extern Vector g_shared_trace_point MACRO_ADDR;
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void QueueMobyImpact(void *, void *);
extern void laser_bot_emit_beam_particles(u8 *, Vector *, Vector *, int);

/* Traces the entity's beam, applies hit damage and records its endpoints. */
void laser_bot_trace_beam(u8 *self) {
    Vector from, to;
    u8 hit[0x30];
    u8 *st = *(u8 **)(self + 0x68);
    int enabled;

    if (g_frame_l03_counter & 1) {
        *(s16 *)(st + 0x334) = (*(s16 *)(st + 0x334) + 1) % 4;
        if (*(s16 *)(st + 0x336) < 3)
            ++*(s16 *)(st + 0x336);
        g_laser_bot_beam_end.f[0] = *(float *)(st + 0x33C);
        matrix_mul_vec3(&from, &g_laser_bot_beam_origin, self + 0xC0);
        FastVecAdd(&from, &from, self + 0x10);
        enabled = 0;
        matrix_mul_vec3(&to, &g_laser_bot_beam_end, self + 0xC0);
        FastVecAdd(&to, &to, self + 0x10);
        make_hit_descriptor(hit, self, self[0x95] == 2 ? 0x10001 : 1,
                     g_effect_descriptor_default, (float)st[0x34]);
        if (CollLine(&from, &to, 0, self, hit)) {
            u8 *direction = g_collision_direction;
            u8 *ctx = direction - 0x40;
            if (mat_fast_helper_a(vec_length_xy(direction), *(float *)(ctx + 0x48)) > 1.396263599395752f)
                enabled = 1;
            qcopy(&to, direction - 0x20);
            if (*(u8 **)(ctx + 0x18)) {
                u8 *obj = *(u8 **)(ctx + 0x18);
                int type = *(s16 *)(obj + 0xAA);
                if (type < 0x1F4)
                    goto no_damage;
                if (type >= 0x209)
                    goto no_damage;
                {
                    make_hit_descriptor(hit, self, 0x10000, g_effect_descriptor_default, (float)st[0x34]);
                    QueueMobyImpact(*(u8 **)(ctx + 0x18), hit);
                }
            }
        }
no_damage:
        if (*(s16 *)(st + 0x336) >= 3)
            laser_bot_emit_beam_particles(self, &to,
                             (Vector *)((((*(s16 *)(st + 0x334) + 3) % 4) * 32) +
                                        (u32)st + 0x2B0), enabled);
        if (*(int *)(st + 0x298))
            qcopy(&g_shared_trace_point, &to);
        /* The endpoint slots do not overlap the ring index at +0x334. */
        qcopy_nc(st + 0x2A0 + *(s16 *)(st + 0x334) * 32, &from);
        qcopy(st + 0x2B0 + *(s16 *)(st + 0x334) * 32, &to);
    }
}
