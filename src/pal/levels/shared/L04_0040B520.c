#include "include_asm.h"



#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int FloatToInt(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void FastVecSub(void *, void *, void *);
extern int FastDecTimer(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern void euler_rotation_basis(void *, void *);
extern void part_l00_spawn_explosion_burst_pal(void *, void *, float, float, int);
extern char *SpawnExplosion_pal(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern int coll_test_point(void *, int, float, void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void mat_from_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern float g_scratch_direction_quad[];
extern void racer_draw_trail_pal(void *);
extern void FastVecAdd(void *, void *, void *);

/* Updates a debris piece: counts down its life, spins and falls, bounces off surfaces, then explodes or fades out and removes itself (PAL: 50 Hz timings). */
void debris_l04_piece_update_pal(unsigned char *moby)
{
    float old_point[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[13];
    float bounce[4];
    float axis[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(vars + 0x32) += 1;
    switch (moby[0x20]) {
    case 1:
        if (FastDecTimer(vars + 0x30)) {
            moby[0x20] = (*(int *)(vars + 0x34) & 1) ? 3 : 2;
            *(short *)(vars + 0x30) = FloatToInt(8.666667f);
            return;
        }
        if (*(int *)(vars + 0x34) & 4) gfx_add_draw_callback_third(racer_draw_trail_pal, moby);
        break;
    case 2:
        matrix_mul_vec3(old_point, vars + 0x20, moby + 0xc0);
        FastVecAdd(old_point, old_point, moby + 0x10);
        if (*(int *)(vars + 0x34) & 2) part_l00_spawn_explosion_burst_pal(moby, old_point, 0.3f, 10.0f, -1);
        else SpawnExplosion_pal(moby + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (FastDecTimer(vars + 0x30)) {
        case 0:
        destroy:
            moby_mark_spawned(moby);
            return;
        }
        moby[0x23] = FloatToInt((float)*(short *)(vars + 0x30) * 14.76923f);
        break;
    }
    euler_rotation_basis(rot, vars + 0x10);
    matrix_mul_vec3(old_point, vars + 0x20, moby + 0xc0);
    multiply_matrix3x3(moby + 0xc0, rot, moby + 0xc0);
    matrix_mul_vec3(point, vars + 0x20, moby + 0xc0);
    FastVecSub(delta, point, old_point);
    FastVecSub(moby + 0x10, moby + 0x10, delta);
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    *(float *)(vars + 8) -= *(float *)(vars + 0x38);
    radius = *(float *)(vars + 0x2c);
    matrix_mul_vec3(probe, vars + 0x20, moby + 0xc0);
    FastVecAdd(probe, probe, moby + 0x10);
    if (coll_test_point(probe, 0, radius, moby)) {
        vec_scale_to_length(g_scratch_direction_quad, g_scratch_direction_quad, 1.0f);
        speed = FastVecLength(vars);
        dot = FastVecDot(vars, g_scratch_direction_quad);
        if (dot < 0.0f) {
            vec_fast_normalize(vars, vars, g_scratch_direction_quad);
            vec_scale_to_length(bounce, g_scratch_direction_quad, dot * 0.5f);
            FastVecAdd(vars, vars, bounce);
            vec_scale_to_length(vars, vars, speed);
            FastVecCross(axis, g_scratch_direction_quad, vars);
            vec_scale_to_length(axis, axis, 1.0f);
            math_build_axis_angle_quat(axis, axis, FastVecLength(vars + 0x10));
            mat_from_rotation(axis, matrix);
            mat_get_euler_angles(matrix, vars + 0x10);
            if (*(short *)(vars + 0x32) >= 13) *(short *)(vars + 0x30) = 0;
        }
    }
}

