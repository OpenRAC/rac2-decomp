#include "common.h"

/* EE integer and FP banks retain the helper's two pointers and scale. */
extern void vec_scale_to_length(float, void *, void *);
extern float g_dobbo_shot_speed __attribute__((sda));
extern float g_dobbo_projectile_size __attribute__((sda));
extern s32 g_dobbo_shot_interval __attribute__((sda));
extern s32 g_dobbo_shot_sound __attribute__((sda));
extern u8 g_dobbo_shot_cooldown __attribute__((sda));
extern s32 g_dobbo_burst_count __attribute__((sda));
extern u16 g_dobbo_shot_delay __attribute__((sda));
extern float vec_distance_xy(char *a0, char *a1);
extern void moby_transform_joint_point(char *a0, s32 a1, void *a2);
extern void FastVecSub(float *a0, char *a1, float *a2);
extern char *projectile_l09_spawn(float *a0, char *a1, float *a2, s32 a3, s32 t0, float f12, float f13, float f14, float f15);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern s32 vec_fast_helper_a(char *a0);

/* Shoots at the hero when he is close: picks a muzzle, fires a shot, plays a sound and then waits to reload. */
void dobbo_fire_shots_at_hero(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    float matrix[16];
    float va[4];

    {
        if (*(u8 *)(vars + 0x42B) != 0 && vec_distance_xy(vars + 0x390, *(char **)(vars + 0x150) + 0x10) < 3.0f) {
            *(s16 *)(vars + 0x412) = 600;
            if (*(s16 *)(vars + 0x426) == 0 && *(u8 *)(vars + 0x428) == 0) {
                moby_transform_joint_point(obj, *(u8 *)(vars + 0x429) + 4, matrix);
                if (*(u8 *)(vars + 0x441) && vec_distance_xy(vars + 0x140, vars + 0x390) < 3.0f) {
                    FastVecSub(va, vars + 0x140, matrix + 12);
                } else {
                    FastVecSub(va, vars + 0x390, matrix + 12);
                }
                vec_scale_to_length(g_dobbo_shot_speed * 0.016666668f, va, va);
                projectile_l09_spawn(matrix + 12, obj, va, 1, 1, (float)*(u8 *)(vars + 0x34), g_dobbo_projectile_size, 1.0f, 0.5f);
                if (*(u8 *)(vars + 0x42A) % g_dobbo_shot_interval == 0)
                    PlayMobySound(g_dobbo_shot_sound, 0, obj);
                *(u8 *)(vars + 0x429) ^= 1;
                *(u8 *)(vars + 0x42A) += 1;
                *(u8 *)(vars + 0x428) = g_dobbo_shot_cooldown;
                if (g_dobbo_burst_count < *(u8 *)(vars + 0x42A)) {
                    *(u8 *)(vars + 0x42A) = 0;
                    *(u16 *)(vars + 0x426) = g_dobbo_shot_delay;
                }
            }
        } else if (*(u8 *)(vars + 0x428) == 0) {
            if (vec_fast_helper_a(vars + 0x42A) == 0)
                *(u8 *)(vars + 0x428) = g_dobbo_shot_cooldown;
        }
    }
}
