#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; struct { f32 x, y, z, w; } f; } V;
typedef struct { V rows[8]; } Transform;

/* A GS sprite packet: four corners, their colours and texture coordinates, then its registers. */
typedef struct {
    V v[4];            /* 0x00 */
    u32 color[4];      /* 0x40 */
    f32 uv[4][2];      /* 0x50 */
    u64 reg[4];        /* 0x70 */
} Packet;

typedef struct {
    s32 transform;     /* 0x00: index into D_L12_001B2F8C[0] */
    f32 phase;         /* 0x04 */
    u8 pad08[0x34 - 0x08];
    f32 position;      /* 0x34 */
    u8 pad38[0x4C - 0x38];
    s32 hit;           /* 0x4C */
    u8 pad50[0x54 - 0x50];
    s32 target;        /* 0x54 */
} Vars;

typedef struct {
    u8 pad00[0x68];
    Vars *vars;        /* 0x68 */
} Moby;

extern Transform *g_path_waypoint_table[] __attribute__((sda));
extern u32 g_barrier_quad_color __attribute__((sda));
extern f32 g_barrier_l12_uv_table[4][2] MACRO_ADDR;
extern f32 D_L12_001B1B30_gp[4][2] SDATA(D_L12_001B1B30) __attribute__((sda));
extern s32 g_barrier_texture_id __attribute__((sda));
extern s32 g_barrier_gs_state_a __attribute__((sda));
extern s32 g_barrier_gs_state_b __attribute__((sda));
extern f32 g_barrier_strip_retreat __attribute__((sda));
extern f32 g_barrier_strip_advance __attribute__((sda));
extern f32 g_barrier_strip_half_width __attribute__((sda));
extern f32 g_barrier_strip_phase_step __attribute__((sda));
extern u32 g_barrier_next_quad_color __attribute__((sda));
extern V g_line_end_point;
extern V g_hero_prev_position;

extern void euler_to_matrix(void *, void *);
extern u64 GetEffectTextureDescriptor(s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern f32 FastVecLength(void *);
extern f32 func_L00_002EE290(void *);
extern s32 CollLine(void *, void *, s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void draw_world_quad(void *, s32, s32);
extern void lerp_vector(void *, void *, void *, f32);

static __inline__ void CopyVector(V *dst, V *src)
{
    qcopy(dst, src);
}

/* Draws the barrier field as a row of glowing strips. Strips near the hero are cut short or skipped. */
void gfx_draw_barrier_field_strips(Moby *self)
{
    Packet quad;
    V matrix[4], initial, low, high, axis;
    V p0, p1, p2, p3, saved, cross, delta, view, measure;
    Packet next;
    Vars *st = self->vars;
    s32 i, j, collision;
    f32 phase, step, t, len, speed, retreat, advance, oldDistance;

    initial.q = 0;
    initial.f.w = 1.0f;
    euler_to_matrix(matrix, &initial);
    CopyVector(&matrix[3], &g_path_waypoint_table[0][st->transform].rows[3]);
    for (i = 0; i < 4; i++) {
        quad.color[i] = g_barrier_quad_color;
        quad.uv[i][0] = D_L12_001B1B30_gp[i][0];
        quad.uv[i][1] = g_barrier_l12_uv_table[i][1];
        if (i < 2)
            quad.v[i].f.y = -quad.v[i].f.y;
        if (i & 1)
            quad.v[i].f.z = -quad.v[i].f.z;
        quad.v[i].f.z += 0.25f;
    }
    quad.reg[1] = GetEffectTextureDescriptor(g_barrier_texture_id);
    low.q = 0;
    high.q = 0;
    quad.reg[2] = 0xFF9000000260ULL;
    quad.reg[0] = 0;
    quad.reg[3] = ((u64)g_barrier_gs_state_a << 2) | ((u64)g_barrier_gs_state_b << 6) | 0x8000000000ULL;
    low.f.y = -1.0f;
    low.f.w = 1.0f;
    high.f.y = 1.0f;
    high.f.w = 1.0f;
    if (st->position > 1.0f)
        st->position = 1.0f;
    else if (st->position < -1.0f)
        st->position = -1.0f;
    phase = st->phase;
    st->phase = phase + 0.008333334f;
    if (st->phase > 1.0f)
        st->phase -= 1.0f;
    step = 0.5f / g_path_waypoint_table[0][st->transform].rows[2].f.x;
    for (i = 3; i >= 0; i--)
        quad.v[i].f.w = 0.0f;
    for (t = -1.0f; t <= 1.0f; t += 0.05f) {
        collision = 0;
        axis.q = 0;
        axis.f.z = 1.0f;
        axis.f.w = 1.0f;
        matrix_mul_vec3(&axis, &axis, &g_path_waypoint_table[0][st->transform]);
        len = FastVecLength(&axis);
        if (st->target != -1) {
            retreat = 2.3f;
            advance = 7.0f;
        } else {
            retreat = g_barrier_strip_retreat;
            advance = g_barrier_strip_advance;
        }
        if (st->hit) {
            if (st->position - retreat / len * 1.5f <= t) {
                if (st->position + advance / len * 0.5f > t) {
                    if (st->target == -1)
                        continue;
                    collision = 1;
                }
            }
        }
        CopyVector(&p0, &low);
        CopyVector(&p1, &low);
        CopyVector(&p2, &high);
        CopyVector(&p3, &high);
        p0.f.z = t;
        p2.f.z = t;
        p1.f.z = t + 0.01f;
        p3.f.z = t + 0.01f;
        matrix_mul_vec3(&p0, &p0, &g_path_waypoint_table[0][st->transform]);
        matrix_mul_vec3(&p1, &p1, &g_path_waypoint_table[0][st->transform]);
        matrix_mul_vec3(&p2, &p2, &g_path_waypoint_table[0][st->transform]);
        matrix_mul_vec3(&p3, &p3, &g_path_waypoint_table[0][st->transform]);
        transform_vector(&p0, &p0, matrix);
        transform_vector(&p1, &p1, matrix);
        transform_vector(&p2, &p2, matrix);
        transform_vector(&p3, &p3, matrix);
        if (collision) {
            CopyVector(&saved, &p2);
            if (CollLine(&p0, &p2, 2, 0, 0)) {
                CopyVector(&p2, &g_line_end_point);
                CopyVector(&p3, &g_line_end_point);
            }
        }
        FastVecSub(&delta, &g_hero_prev_position, &p0);
        oldDistance = 0.0f;
        FastVecSub(&view, &p2, &p0);
        FastVecCross(&cross, &delta, &view);
        vec_scale_to_length(&cross, &cross, 1.0f);
        vec_scale_to_length(&quad.v[0], &cross, g_barrier_strip_half_width);
        vec_scale_to_length(&quad.v[1], &cross, -g_barrier_strip_half_width);
        vec_scale_to_length(&quad.v[2], &cross, g_barrier_strip_half_width);
        vec_scale_to_length(&quad.v[3], &cross, -g_barrier_strip_half_width);
        FastVecAdd(&quad.v[0], &quad.v[0], &p0);
        FastVecAdd(&quad.v[1], &quad.v[1], &p0);
        FastVecAdd(&quad.v[2], &quad.v[2], &p2);
        FastVecAdd(&quad.v[3], &quad.v[3], &p2);
        draw_world_quad(&quad, 0, 1);
        if (collision) {
            FastVecSub(&measure, &quad.v[2], &quad);
            oldDistance = func_L00_002EE290(&measure);
            CopyVector(&p2, &saved);
            vec_scale_to_length(&quad.v[0], &cross, g_barrier_strip_half_width);
            vec_scale_to_length(&quad.v[1], &cross, -g_barrier_strip_half_width);
            vec_scale_to_length(&quad.v[2], &cross, g_barrier_strip_half_width);
            vec_scale_to_length(&quad.v[3], &cross, -g_barrier_strip_half_width);
            FastVecAdd(&quad.v[0], &quad.v[0], &p0);
            FastVecAdd(&quad.v[1], &quad.v[1], &p0);
            FastVecAdd(&quad.v[2], &quad.v[2], &p2);
            FastVecAdd(&quad.v[3], &quad.v[3], &p2);
        }
        speed = phase + step;
        next = quad;
        lerp_vector(&next.v[0], &quad.v[0], &quad.v[2], st->phase);
        lerp_vector(&next.v[2], &quad.v[0], &quad.v[2], st->phase + g_barrier_strip_phase_step);
        lerp_vector(&next.v[1], &quad.v[1], &quad.v[3], st->phase);
        lerp_vector(&next.v[3], &quad.v[1], &quad.v[3], st->phase + g_barrier_strip_phase_step);
        for (j = 3; j >= 0; j--)
            next.color[j] = g_barrier_next_quad_color;
        phase = speed;
        if (speed > 0.0f)
            phase = speed - 1.0f;
        if (collision) {
            FastVecSub(&measure, &next, &quad);
            if (oldDistance <= func_L00_002EE290(&measure))
                continue;
        }
        draw_world_quad(&next, 0, 1);
    }
}
