#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_0039BE70, level 00's copy of func_PAL_0030FB38: the same C. */
extern char *part_find_owned_effect_slot(char *, int, int);
extern int math_fast_float_d(int *);
extern int PlayMobySound(int, int, char *);
extern void gfx_start_color_fade_pal(char *, char *);
extern void vec_add_random_offset(float *, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void gfx_update_color_fade_pal(char *, char *);

/* Checks whether something hit the object. It takes damage from each hit and bursts when its health runs out (PAL). */
void moby_apply_hit_damage_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit_effect = part_find_owned_effect_slot(moby, 0x30001, 0);
    float blast_dir[4];

    math_fast_float_d((int *)(vars + 0x28));
    math_fast_float_d((int *)(vars + 0x2C));
    if (hit_effect != 0 && (*(int *)(hit_effect + 0x20) != *(int *)(vars + 0x34) ||
                     *(int *)(vars + 0x28) == 0)) {
        *(int *)(vars + 0x34) = *(int *)(hit_effect + 0x20);
        *(int *)(vars + 0x28) = 25;
        if (*(int *)(vars + 0x2C) == 0) {
            if (*(unsigned short *)(hit_effect + 0x28) == 0x101 && *(int *)(vars + 0x30) == 0) {
                *(int *)(vars + 0x2C) = 83;
                *(int *)(vars + 0x30) = 1;
            } else {
                *(int *)(vars + 0x30) = 0;
            }
        }
        PlayMobySound(0, 0, moby);
        *(float *)(vars + 0x24) -= *(float *)(hit_effect + 0x2C);
        gfx_start_color_fade_pal(moby, vars);
        if (*(float *)(vars + 0x24) < 0.0f) {
            vec_add_random_offset(blast_dir, 0.6f);
            SpawnExplosionEffects_pal(moby, blast_dir, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            moby[0x20] = 6;
        }
    }
    ((unsigned char *)moby)[0xA8] = 0xFF;
    gfx_update_color_fade_pal(moby, vars);
}

/* func_PAL_L00_0039C018, level 00's copy of func_PAL_0030FCE8. */


extern char g_hero_state[];
extern char ref_PAL_L00_0039C018_00[];

extern void moby_get_facing_direction(char *, float *);
extern void FastVecSub(float *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(float *, float *, float);
extern float FastVecDot(float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int CollLine(float *, float *, int, int, int);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern int moby_move_and_collide(char *, float *, float, float, float, int);

/* Pushes a springy object down when the player stands on it and lets it bounce back up. Keeps it above the floor (PAL). */
void moby_spring_away_from_player_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hero = g_hero_state;
    short hero_flag = *(short *)(hero + 0x202);
    float facing[4] __attribute__((aligned(16)));
    float to_hero[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float along[4] __attribute__((aligned(16)));
    float ray_end[4] __attribute__((aligned(16)));
    float ray_start[4] __attribute__((aligned(16)));
    float ground_point[4] __attribute__((aligned(16)));
    float ground_along[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float to_ground[4] __attribute__((aligned(16)));
    float goal;
    float projection;
    int ground_mode;
    float along_len, side_len, step, ground_dist, fall_speed;

    if (*(int *)(vars + 0x44) == 0 && hero_flag == 0)
        return;
    moby_get_facing_direction(moby + 0x10, facing);
    ground_dist = 0.0f;
    FastVecSub(to_hero, moby + 0x10, hero + 0x80);
    projection = FastVecDot(to_hero, facing);
    FastVecScale(along, facing, projection);
    FastVecSub(side, to_hero, along);
    along_len = FastVecLength(along);
    side_len = FastVecLength(side);
    FastVecScale(ray_end, facing, -2.5f);
    FastVecAdd(ray_end, moby + 0x10, ray_end);
    FastVecScale(ray_start, facing, 0.5f);
    FastVecAdd(ray_start, moby + 0x10, ray_start);
    if (CollLine(ray_start, ray_end, 2, 0, 0)) {
        qcopy(ground_point, ref_PAL_L00_0039C018_00);
        ground_mode = 0;
    } else {
        ground_mode = 1;
    }
    if (ground_mode == 0) {
        FastVecSub(push, ground_point, moby + 0x10);
        projection = FastVecDot(push, facing);
        FastVecScale(ground_along, facing, projection);
        ground_dist = FastVecLength(ground_along);
    }
    if (*(int *)(vars + 0x44) == 0) {
        if (!(side_len < 1.0f))
            return;
        if (!(along_len < 1.3f))
            return;
        *(int *)(vars + 0x44) = 1;
    }
    qcopy(push, side);
    goal = side_len - 1.4f;
    if (goal > 0.0f)
        goal = 0.0f;
    if (hero_flag == 0)
        goal = 0.0f;
    math_spring_float_to_goal(&goal, 0.0f, (float *)(vars + 0x48), 0.0288000014f, 0.432000041f, 0.080000006f);
    if (goal == 0.0f && *(float *)(vars + 0x48) == 0.0f && ground_dist < 0.02f)
        *(int *)(vars + 0x44) = 0;
    if (side_len < *(float *)(vars + 0x48))
        *(float *)(vars + 0x48) = side_len;
    if (*(float *)(vars + 0x48) < side_len)
        vec_scale_to_length(push, push, *(float *)(vars + 0x48));
    moby_move_and_collide(moby, push, 0.5f, 0.4f, 0.0f, 0);
    if (ground_mode == 0) {
        if (FastVecDot(ground_along, facing) > 0.0f) {
            qcopy(moby + 0x10, ground_point);
            *(float *)(vars + 0x4C) = 0.0f;
        } else {
            fall_speed = *(float *)(vars + 0x4C) - 0.0096000005f;
            *(float *)(vars + 0x4C) = fall_speed;
            FastVecScale(push, facing, fall_speed);
            FastVecAdd(moby + 0x10, push, moby + 0x10);
            FastVecSub(to_ground, ground_point, moby + 0x10);
            if (FastVecDot(to_ground, facing) > 0.0f) {
                qcopy(moby + 0x10, ground_point);
                *(float *)(vars + 0x4C) = 0.0f;
            }
        }
    } else {
        *(float *)(vars + 0x4C) -= 0.0096000005f;
        FastVecScale(push, facing, *(float *)(vars + 0x4C));
        FastVecAdd(moby + 0x10, push, moby + 0x10);
    }
}

