#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;

/* One bolt's row of the level's vertex table (640 bytes): the jittered points
 * along the path, then the same points displaced by the wave. */
typedef struct { Vector core[20]; Vector wave[20]; } BoltBuffer;

/* An entry of the level's path table: a point count, then the points. */
typedef struct { int count; int pad[3]; Vector points[1]; } Path;

/* The bolt's state record (object + 0x68). */
typedef struct {
    Vector start;   /* 0x00 */
    Vector end;     /* 0x10 */
    char pad20[12];
    int count;      /* 0x2C */
    int pad30;
    int path;       /* 0x34: index into the level's path table */
    int row;        /* 0x38: this bolt's row of the vertex table */
} BoltState;

extern int g_lightning_point_count __attribute__((sda));
extern Path *g_path_l11_table[];
extern BoltBuffer g_ribbon_row_table[];
extern float g_lightning_bolt_length __attribute__((sda));
extern float g_lightning_start_angle __attribute__((sda));
extern float g_lightning_l11_horizontal_phase __attribute__((sda));
extern float g_lightning_horizontal_phase_step __attribute__((sda));
extern float g_lightning_vertical_amplitude __attribute__((sda));
extern float g_lightning_horizontal_amplitude __attribute__((sda));
extern float g_lightning_vertical_angle __attribute__((sda));
extern float g_lightning_vertical_angle_rate __attribute__((sda));
extern float g_lightning_vertical_angle_step __attribute__((sda));
extern float g_lightning_l11_noise_min __attribute__((sda));
extern float g_lightning_l11_noise_max __attribute__((sda));
extern char g_identity_l11_matrix[] __attribute__((sda));
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float mat_fast_helper_a(float, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern int CollLine(void *, void *, int, void *, void *);

/* Rebuilds a lightning bolt along its path: each point gets a random jitter
 * (core), a copy of it is displaced by a travelling wave (wave), and every
 * second segment spawns a spark effect. */
void lightning_rebuild_bolt_points(char *object)
{
    Vector position;
    Vector direction;
    Vector delta;
    Vector step;
    Vector perpendicular;
    char effect[48] __attribute__((aligned(16)));
    BoltState *state;
    Path *path;
    Vector *wave, *prev;
    float phase, angle, amplitude, horizontalAmplitude, nx, nz, ny, f;
    float scale = g_lightning_bolt_length / (float)g_lightning_point_count;
    int i;

    state = *(BoltState **)(object + 0x68);
    g_lightning_start_angle = math_random_angle();
    g_lightning_l11_horizontal_phase = math_random_angle();
    g_lightning_vertical_angle = FastAddRotations(g_lightning_vertical_angle, g_lightning_vertical_angle_rate);
    vec_clear_128(&position);
    state->count = g_lightning_point_count;
    FastVecSub(&direction, &state->end, &state->start);
    vec_scale_to_length(&direction, &direction, 1.0f);
    FastVecScale(&step, &direction, scale);
    path = g_path_l11_table[state->path];
    qcopy_nc(&g_ribbon_row_table[state->row].core[0], &path->points[0]);
    qcopy_nc(&g_ribbon_row_table[state->row].wave[0], &path->points[0]);
    for (i = 1; i < g_lightning_point_count; i++) {
        nz = math_random_signed_float_range(g_lightning_l11_noise_min, g_lightning_l11_noise_max);
        nx = math_random_signed_float_range(g_lightning_l11_noise_min, g_lightning_l11_noise_max);
        ny = math_random_signed_float_range(g_lightning_l11_noise_min, g_lightning_l11_noise_max);
        qcopy_nc(&g_ribbon_row_table[state->row].core[i], &path->points[i]);
        f = (float)i;
        g_ribbon_row_table[state->row].core[i].z += nz;
        g_ribbon_row_table[state->row].core[i].x += nx;
        g_ribbon_row_table[state->row].core[i].y += ny;
        /* Previous point: the row's points from index -1. */
        prev = &g_ribbon_row_table[state->row].core[-1];
        FastVecSub(&delta, &g_ribbon_row_table[state->row].core[i], &prev[i]);
        phase = math_wrap_angle_to_pi(g_lightning_l11_horizontal_phase + f * g_lightning_horizontal_phase_step);
        angle = math_wrap_angle_to_pi(g_lightning_vertical_angle + f * g_lightning_vertical_angle_step);
        amplitude = g_lightning_vertical_amplitude * math_fast_sin_or_cos_b(angle);
        /* Column i of the wave points, then this bolt's row. */
        qcopy_nc(&g_ribbon_row_table[0].wave[i] + state->row * 40,
                 &g_ribbon_row_table[state->row].core[i]);
        nz = amplitude * math_fast_sin_or_cos_b(phase) + math_random_signed_float_range(0.0f, 0.1f);
        g_ribbon_row_table[state->row].wave[i].z += nz;
        angle = FastAddRotations(mat_fast_helper_a(delta.x, delta.y), 1.5707964897155762f);
        horizontalAmplitude = g_lightning_horizontal_amplitude * math_fast_sin_or_cos_a(phase);
        perpendicular.x = math_fast_sin_or_cos_a(angle) * horizontalAmplitude;
        perpendicular.y = math_fast_sin_or_cos_b(angle) * horizontalAmplitude;
        perpendicular.z = 0.0f;
        wave = g_ribbon_row_table[state->row].wave;
        FastVecAdd(&wave[i], &wave[i], &perpendicular);
        if (i > 1 && (i == g_lightning_point_count - 1 || !(i & 1))) {
            make_hit_descriptor(effect, object, 1, 10.0f, g_identity_l11_matrix);
            *(unsigned short *)(effect + 26) = *(unsigned short *)(object + 0xaa);
            CollLine(&path->points[i - 2], &path->points[i], 16, object, effect);
        }
    }
}
