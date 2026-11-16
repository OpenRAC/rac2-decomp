/* func_PAL_L00_0040FF58, the PAL copy of func_L00_0040B398: the same C, where scale D_L00_001B2D50[g]. */
#include "common.h"

/* Allocates a record and tags it released-empty; returns it, or zero when the allocation failed. */
typedef struct {
    char reserved00[0x18];
    int active;
    char reserved1C[0x14];
} SettingSlot;

typedef struct {
    float amount;
    float scale;
    int kind;
    float multiplier;
} SettingRow;

typedef struct { SettingRow rows[238]; } SettingsBank;

extern SettingSlot g_setting_slot_table[30];
extern SettingsBank g_shot_settings_bank;

typedef float Vector[4] __attribute__((aligned(16)));

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
typedef struct ScaleRecord {
    char pad00[0x50];
    float value;
    char pad54[0x8c];
} ScaleRecord;
extern ScaleRecord g_weapon_l00_table[];

typedef struct PlayerState {
    /* 0x0000 */ char pad0000[0x750];
    /* 0x0750 */ Vector up;
    /* 0x0760 */ Vector forward;
    /* 0x0770 */ char pad0770[0x1b20];
    /* 0x2290 */ char *object;
    /* 0x2294 */ int mode;
    /* 0x2298 */ char pad2298[0x254];
    /* 0x24EC */ short orientation;
} PlayerState;
extern PlayerState g_hero_state;

extern Vector g_cam_follow_matrix[3];   /* camera basis rows */
    /* camera position */
    /* collision hit point */
/* Spawns a projectile (moby 0xED7) from owner at position, aimed at target or along the view. */
extern int FastDecTimer(void *);
extern void math_l00_interpolate_cubic_vector(void *, void *, void *, void *, void *, float);
extern short g_strand_timers[] __attribute__((sda));
extern short g_strand_alphas[] __attribute__((sda));
extern short g_strand_periods[] __attribute__((sda));
extern float g_hero_aim_vector[4];
extern float g_lightning_strand_step_length __attribute__((sda));
extern float g_lightning_strand_jitter __attribute__((sda));
extern Vector g_lightning_strand_points[][10];

/* Updates four jagged lightning strands: when a strand timer ends it makes a new curve, otherwise it jitters the points a little. (PAL: 50 Hz timings) */
void lightning_strands_update_pal(char *object)
{
    Vector point, delta, out, diffs[10];
    char *state = *(char **)(object + 0x68);
    int strand, i, j, k, l, n;

    for (strand = 0; strand < 4; strand++) {
        if (FastDecTimer(&g_strand_timers[strand])) {
            g_strand_alphas[strand] = 0;
            g_strand_timers[strand] = (((int)(g_strand_periods[strand]) * 5 + 2) / 6);
            qcopy(point, state + 0x30);
            point[0] += math_random_float_range(-0.5f, 0.5f);
            point[1] += math_random_float_range(-0.5f, 0.5f);
            point[2] += math_random_float_range(-0.5f, 0.5f);
            FastVecSub(delta, point, g_hero_aim_vector);
            vec_scale_to_length(delta, delta, g_lightning_strand_step_length);
            FastVecAdd(delta, point, delta);
            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9)
                    t = 1.0f;
                math_l00_interpolate_cubic_vector(out, g_hero_aim_vector, point, state + 0x40, delta, t);
                qcopy(g_lightning_strand_points[strand][i], out);
            }
        } else {
            for (j = 1; j < 10; j++) {
                FastVecSub(diffs[j], g_lightning_strand_points[strand][j], (&((Vector *)g_lightning_strand_points)[strand * 10 + j])[-1]);
                diffs[j][0] += math_random_signed_float_range(0.0f, 0.05f);
                diffs[j][1] += math_random_signed_float_range(0.0f, 0.05f);
                diffs[j][2] += math_random_signed_float_range(0.0f, 0.05f);
            }
            qcopy(g_lightning_strand_points[strand][0], g_hero_aim_vector);
            for (k = 1; k < 10; k++)
                FastVecAdd(g_lightning_strand_points[strand][k], (&((Vector *)g_lightning_strand_points)[strand * 10 + k])[-1], diffs[k]);
        }
        for (l = 2; l < 9; l++) {
            qcopy(point, g_lightning_strand_points[0][l]);
            point[0] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[1] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[2] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            qcopy(g_lightning_strand_points[1][l], point);
        }
        for (n = 2; n < 9; n++) {
            qcopy(point, g_lightning_strand_points[0][n]);
            point[0] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[1] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[2] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            qcopy(g_lightning_strand_points[2][n], point);
        }
        for (i = 2; i < 9; i++) {
            qcopy(point, g_lightning_strand_points[0][i]);
            point[0] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[1] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            point[2] += math_random_signed_float_range(0.0f, g_lightning_strand_jitter);
            qcopy(g_lightning_strand_points[3][i], point);
        }
    }
}
