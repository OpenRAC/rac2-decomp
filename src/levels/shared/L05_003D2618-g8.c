#include "common.h"

typedef struct { float v[4][4]; int color[4]; float uv[4][2]; unsigned long gs[4]; } QuadD2618;
typedef struct { int index; float scale; int mode; } StateD2618;
extern unsigned long GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(u32, u64);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(int *);
extern void euler_to_matrix(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void add_vectors(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void draw_world_quad(void *, void *, int);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void moby_mark_spawned(void *);
extern int g_quad_init_arg __attribute__((sda));
extern int g_blend_mode_c __attribute__((sda));
extern int g_blend_mode_d __attribute__((sda));
extern int g_blend_mode_a __attribute__((sda));
extern int g_blend_mode_b __attribute__((sda));
extern float g_quad_scale __attribute__((sda));
extern float g_effect_slot_state __attribute__((sda));
extern int g_quad_l05_color __attribute__((sda));
extern struct { char pad[0x140]; float pos[4]; } g_hero_l05_state;
extern int g_emitter_group_timers[][4], g_emitter_group_alphas[][4], g_emitter_group_fade_rates[][4];
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VectorD2618;
extern VectorD2618 g_emitter_group_positions[][4];
extern float g_emitter_vertex_speeds[][4][137];
extern float g_emitter_vertex_offsets[][4][137][4];
extern float g_glow_quad_offsets[][4];
extern short g_glow_quad_corner_indices[][4][3];
extern float g_glow_quad_vertices[][4];
extern float g_glow_l05_quad_uvs[][2];
extern float g_glow_effect_scales[] MACRO_ADDR;
extern float g_glow_effect_sizes[] MACRO_ADDR;
extern float g_glow_effect_angles_a[] MACRO_ADDR;
extern float g_glow_effect_angles_b[] MACRO_ADDR;
extern int g_glow_effect_alphas[] MACRO_ADDR;
extern int g_glow_effect_blends[] MACRO_ADDR;
extern int g_glow_effect_timers[] MACRO_ADDR;
extern char *g_spawned_effect_mobys[] MACRO_ADDR;

/* Selects the quad's texture and resets its GS tags. */
static inline void InitQuadD2618(QuadD2618 *q, int texture)
{
    q->gs[1] = GetEffectTextureDescriptor(texture);
    q->gs[2] = 0xFF9000000260UL;
    q->gs[0] = 0;
}

/* One axis of the object's rotation. */
static inline float RotationAxisD2618(char *object, int axis)
{
    return ((float *)(object + 0xF0))[axis];
}

/* One axis of the object's position, which follows four words after the object's start. */
static inline float PositionAxisD2618(char *object, int axis)
{
    return ((float *)object)[4 + axis];
}

/* Turns rotation to face the camera from the object's position. */
static inline void FaceCameraD2618(float *rotation, char *object)
{
    float x, y;
    x = g_hero_l05_state.pos[0] - *(float *)(object + 0x10);
    y = g_hero_l05_state.pos[1] - PositionAxisD2618(object, 1);
    rotation[0] = RotationAxisD2618(object, 0);
    rotation[1] = RotationAxisD2618(object, 1);
    rotation[2] = RotationAxisD2618(object, 2);
    rotation[3] = 0;
    rotation[2] = mat_fast_helper_a(x, y);
    x = vec_distance_xy(object + 0x10, g_hero_l05_state.pos);
    rotation[1] = -mat_fast_helper_a(x, g_hero_l05_state.pos[2] - PositionAxisD2618(object, 2));
}

/* Faces the camera, then draws four layers of a 128-quad mesh, a growing flash quad and, in mode 0,
   two spinning glow quads. Once func_00282948 reports on D_L05_001B2FE8 and the alpha at
   D_L05_001B2FA0 falls below zero, calls func_0029F338 and returns; otherwise calls func_002FC560. */
void DrawAnimatedMeshAndGlowEffect(char *object)
{
    QuadD2618 q;
    float matrix[16];
    float rotation[4];
    float temporary[4];
    float scratch[4];
    StateD2618 *state = *(StateD2618 **)(object + 0x68);
    int vertex;
    int corner;
    int inactive;
    InitQuadD2618(&q, g_quad_init_arg);
    VU1_addGSregister(0x47, 0x53001);
    FaceCameraD2618(rotation, object);
    {
        /* Declared after the setup: its pseudo number orders the spill slots of gcse's temporaries. */
        int group;
        for (group = 0; group < 4; group++) {
            inactive = 0;
            if (math_fast_float_d(&g_emitter_group_timers[state->index][group]) ||
                !g_emitter_group_timers[state->index][group]) {
                inactive = 1;
                g_emitter_group_timers[state->index][group] = 0;
            }
            euler_to_matrix(matrix, rotation);
            matrix[12 + 0] = g_emitter_group_positions[state->index][group].x;
            matrix[12 + 1] = g_emitter_group_positions[state->index][group].y;
            matrix[12 + 2] = g_emitter_group_positions[state->index][group].z;
            matrix[12 + 3] = 1.0f;
            q.color[0] = q.color[1] = q.color[2] = q.color[3] = g_quad_l05_color;
            {
                unsigned long blend = (unsigned long)g_blend_mode_a;
                blend |= (unsigned long)g_blend_mode_b << 2;
                blend |= (unsigned long)g_blend_mode_c << 4;
                blend |= (unsigned long)g_blend_mode_d << 6;
                blend |= ((unsigned long)g_emitter_group_alphas[state->index][group] << 32);
                q.gs[3] = blend;
            }
            if (inactive == 1) {
                g_emitter_group_alphas[state->index][group] -= g_emitter_group_fade_rates[state->index][group];
                if (g_emitter_group_alphas[state->index][group] < 0)
                    g_emitter_group_alphas[state->index][group] = 0;
            }
            if (inactive == 0) {
                for (vertex = 0; vertex < 137; vertex++) {
                    if (vertex % 5 == 0 && vertex > 5) {
                        FastVecScale(temporary, g_glow_quad_offsets[vertex], g_emitter_vertex_speeds[state->index][group][vertex]);
                        add_vectors(scratch, g_emitter_vertex_offsets[state->index][group][vertex], temporary);
                    }
                }
            } else {
                for (vertex = 0; vertex < 137; vertex++) {
                    if (vertex % 5 == 0 && vertex > 5) {
                        FastVecScale(temporary, g_glow_quad_offsets[vertex], g_emitter_vertex_speeds[state->index][group][vertex] * 0.25f);
                        add_vectors(scratch, g_emitter_vertex_offsets[state->index][group][vertex], temporary);
                    }
                }
            }
            for (vertex = 0; vertex < 128; vertex++) {
                for (corner = 0; corner < 4; corner++) {
                    int vi = g_glow_quad_corner_indices[vertex][corner][0];
                    int ti = g_glow_quad_corner_indices[vertex][corner][1];
                    FastVecAdd(temporary, g_glow_quad_vertices[vi], g_emitter_vertex_offsets[state->index][group][vi]);
                    FastVecScale(q.v[corner], temporary, g_quad_scale * state->scale);
                    q.uv[corner][0] = g_glow_l05_quad_uvs[ti][0];
                    q.uv[corner][1] = g_glow_l05_quad_uvs[ti][1];
                    g_glow_l05_quad_uvs[ti][0] += 0.0001f;
                    if (g_glow_l05_quad_uvs[ti][0] > 8.0f)
                        g_glow_l05_quad_uvs[ti][0] -= 8.0f;
                }
                if (fast_vec_dist(object + 0x10, g_hero_l05_state.pos) > 10.0f)
                    draw_world_quad(&q, matrix, 0);
            }
        }
    }
    InitQuadD2618(&q, 0x43);
    {
        unsigned long blend = (unsigned long)g_blend_mode_a;
        blend |= (unsigned long)g_blend_mode_b << 2;
        blend |= (unsigned long)g_blend_mode_c << 4;
        blend |= (unsigned long)g_blend_mode_d << 6;
        blend |= ((unsigned long)g_glow_effect_alphas[state->index] << 32);
        q.gs[3] = blend;
    }
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = 0x7F204080;
    q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
    q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
    q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
    q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
    q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
    euler_to_matrix(matrix, rotation);
    FastVecScale(q.v[0], q.v[0], g_glow_effect_scales[state->index] * state->scale);
    FastVecScale(q.v[1], q.v[1], g_glow_effect_scales[state->index] * state->scale);
    FastVecScale(q.v[2], q.v[2], g_glow_effect_scales[state->index] * state->scale);
    FastVecScale(q.v[3], q.v[3], g_glow_effect_scales[state->index] * state->scale);
    matrix[12 + 0] = *(float *)(object + 0x10);
    matrix[12 + 1] = *(float *)(object + 0x14);
    matrix[12 + 2] = *(float *)(object + 0x18);
    matrix[12 + 3] = 1;
    draw_world_quad(&q, matrix, 0);
    g_glow_effect_scales[state->index] += 0.4f;
    g_glow_effect_alphas[state->index] -= 5;
    if (g_glow_effect_alphas[state->index] < 0) g_glow_effect_alphas[state->index] = 0;
    if (state->mode == 0) {
        float *angle_a, *size, *angle_b;
        int color = 0x7F8080FF;
        q.gs[1] = GetEffectTextureDescriptor(0x44);
        angle_a = g_glow_effect_angles_a;
        size = g_glow_effect_sizes;
        angle_b = g_glow_effect_angles_b;
        q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
        {
            unsigned long blend = (unsigned long)g_blend_mode_a;
            blend |= (unsigned long)g_blend_mode_b << 2;
            blend |= (unsigned long)g_blend_mode_c << 4;
            blend |= (unsigned long)g_blend_mode_d << 6;
            blend |= ((unsigned long)g_glow_effect_blends[state->index] << 32);
            q.gs[3] = blend;
        }
        q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
        q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
        q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
        q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
        q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
        rotation[0] = angle_a[state->index];
        euler_to_matrix(matrix, rotation);
        FastVecScale(q.v[0], q.v[0], size[state->index] * state->scale);
        FastVecScale(q.v[1], q.v[1], size[state->index] * state->scale);
        FastVecScale(q.v[2], q.v[2], size[state->index] * state->scale);
        FastVecScale(q.v[3], q.v[3], size[state->index] * state->scale);
        matrix[12 + 2] = math_fast_sin_or_cos_b(-rotation[1]);
        matrix[12 + 0] = math_fast_sin_or_cos_a(-rotation[2]) * (1.0f - math_fabs(matrix[12 + 2]));
        matrix[12 + 1] = -math_fast_sin_or_cos_b(-rotation[2]) * (1.0f - math_fabs(matrix[12 + 2]));
        matrix[12 + 2] *= state->scale;
        matrix[12 + 0] *= state->scale;
        matrix[12 + 1] *= state->scale;
        matrix[12 + 2] += *(float *)(object + 0x18);
        matrix[12 + 0] += *(float *)(object + 0x10);
        matrix[12 + 1] += *(float *)(object + 0x14);
        matrix[12 + 3] = 1;
        draw_world_quad(&q, matrix, 0);
        q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
        q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
        q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
        q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
        q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
        q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
        rotation[0] = angle_b[state->index];
        euler_to_matrix(matrix, rotation);
        FastVecScale(q.v[0], q.v[0], size[state->index] * state->scale);
        FastVecScale(q.v[1], q.v[1], size[state->index] * state->scale);
        FastVecScale(q.v[2], q.v[2], size[state->index] * state->scale);
        FastVecScale(q.v[3], q.v[3], size[state->index] * state->scale);
        matrix[12 + 2] = math_fast_sin_or_cos_b(-rotation[1]);
        matrix[12 + 0] = math_fast_sin_or_cos_a(-rotation[2]) * (1.0f - math_fabs(matrix[12 + 2]));
        matrix[12 + 1] = -math_fast_sin_or_cos_b(-rotation[2]) * (1.0f - math_fabs(matrix[12 + 2]));
        matrix[12 + 2] *= state->scale * 2;
        matrix[12 + 0] *= state->scale * 2;
        matrix[12 + 1] *= state->scale * 2;
        matrix[12 + 2] += *(float *)(object + 0x18);
        matrix[12 + 0] += *(float *)(object + 0x10);
        matrix[12 + 1] += *(float *)(object + 0x14);
        matrix[12 + 3] = 1;
        draw_world_quad(&q, matrix, 0);
        angle_a[state->index] = FastAddRotations(angle_a[state->index], 0.04654212296009064f);
        angle_b[state->index] = fast_subtract_rotations(angle_b[state->index], 0.04654212296009064f);
        size[state->index] += 0.02f;
    }
    if (math_fast_float_d(g_glow_effect_timers + state->index)) {
        g_glow_effect_blends[state->index] -= 2;
        if (g_glow_effect_blends[state->index] < 0) {
            g_glow_effect_blends[state->index] = 0;
            g_spawned_effect_mobys[state->index] = 0;
            g_effect_slot_state -= 1.0f;
            moby_mark_spawned(object);
            return;
        }
    }
    VU1_addGSregister(0x47, 0x5360B);
}
