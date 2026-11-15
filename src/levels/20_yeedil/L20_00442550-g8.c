#include "common.h"
typedef struct {
    unsigned char pad0[0x30];
    float point_x;
    float point_y;
    unsigned char pad1[0x48];
} Rec_42550;

extern float D_L20_001B2124 __attribute__((sda));

extern float D_L20_001B2134 __attribute__((sda));

extern char g_hero_state[];

extern Rec_42550 *D_L20_001B308C;

extern float ApproachValue(float *, float, float);

extern void StepAngleTowardTarget(char *, int, float, float);

extern float vec_distance_xy(char *, char *);

extern float coll_probe_ground_height_below(void *, int, float);

extern float mat_fast_helper_a(float, float);

extern int moby_start_effect_from_entry(char *, float);

extern int PlayMobySound(int, int, char *);

/* Makes the enemy fall and bounce on the ground while it turns toward the hero or its target. Returns 1 when the bouncing has stopped. */
int UpdateBouncingMoby(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *hero;
    char *hero_pos;
    float value;
    int path_index;
    Rec_42550 *path_point;

    ApproachValue((float *)(self + 0x48), 1.0f, 0.033333335f);

    if (*(u8 *)(self + 0x94) == 2) {
        StepAngleTowardTarget(vars + 0x1804, 1, 0.0f, D_L20_001B2124 * 0.00014544412f);
    }
    value = *(float *)(vars + 0xF8);
    hero = g_hero_state;
    *(float *)(self + 0x18) += value;

    *(float *)(vars + 0xF8) -= *(float *)(vars + 0x7C);

    if (*(int *)(hero + 0x2294) == 0x8C) {
        float value;
        hero_pos = hero + 0x80;
        value = vec_distance_xy(hero_pos, self + 0x10);
        if (value <= 4.0f) {
            value = *(float *)(hero + 0x88);
            value += 5.0f;
            *(float *)(hero + 0x88) = value;
            value = coll_probe_ground_height_below(hero_pos, 0, 0.5f);
            *(float *)(hero + 0x88) = value;
            *(unsigned short *)(hero + 0x1E0) = 5;
            *(unsigned short *)(hero + 0x1F0) = 5;
        }
        path_index = *(int *)(vars + 0x230);
        path_point = (Rec_42550 *)((path_index << 7) + (unsigned int)D_L20_001B308C);
        value = mat_fast_helper_a(path_point->point_x - *(float *)(self + 0x10), path_point->point_y - *(float *)(self + 0x14));
        moby_start_effect_from_entry(self, value);

    } else {
        moby_start_effect_from_entry(self, mat_fast_helper_a(
            *(float *)(hero + 0x80) - *(float *)(self + 0x10),
            *(float *)(hero + 0x84) - *(float *)(self + 0x14)));
    }

    if (*(float *)(self + 0x18) <= *(float *)(vars + 0xE0)) {
        float velocity;
        *(float *)(self + 0x18) = *(float *)(vars + 0xE0);
        PlayMobySound(0, 0, self);
        velocity = *(float *)(vars + 0xF8) * -D_L20_001B2134;
        *(float *)(vars + 0xF8) = velocity;
        if (velocity < 0.016666668f) {
            *(int *)(vars + 0xF8) = 0;
            return 1;
        }
    }
    return 0;
}
