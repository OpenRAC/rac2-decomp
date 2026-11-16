#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
typedef unsigned int B781AimQuad __attribute__((mode(TI)));
extern float math_fabs(float);
extern float math_approach_with_velocity(void *, void *, float, float, float, float, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void *moby_spawn_at_parent_pose(void *, int, float);
extern int vec_apply_scaled_value(void *, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void bike_animate_boost_flame_streak(void *);
extern void *part_spawn_object_following_effect(void *, void *, unsigned int, float, int, int, float, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void emit_trail_effects_pal(void *, void *, void *, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void FastVecSub(void *, void *, void *);

/* Leans the bike into its turns, keeps its child (rider) moby posed on it, and draws the boost flame and the race-item effect. */
void racer_update_bike_lean_pal(unsigned char *moby, unsigned char *vars)
{
    float point[4];
    float end[4];
    float total = *(float *)(vars + 0x138) + *(float *)(vars + 0x13c);
    float a, b, c, angle, factor;
    if (total < 0.10000001f) total = 0.10000001f;
    a = *(float *)(vars + 0x130) * 11.459153f;
    b = total * 2.2573361f;
    c = *(float *)(vars + 0x130) * 23.873238f;
    a = a * math_fabs(a);
    c = 1.0f - (1.0f - c) * (1.0f - c);
    if (b > 1.0f) b = 1.0f;
    if (*(float *)(vars + 0x1f4) != 0.0f) {
        if (math_fabs(*(float *)(moby + 0xf0) - *(float *)(vars + 0x1f4)) < 0.003f) *(float *)(vars + 0x1f4) = 0.0f;
        factor = *(float *)(vars + 0x1f8);
        angle = *(float *)(vars + 0x1f4);
    } else {
        factor = 1.0f;
        angle = (factor - b) * a + b * c;
        if (angle > factor) angle = factor;
        if (angle < -1.0f) angle = -1.0f;
        angle *= -0.52359885f;
    }
    math_approach_with_velocity(moby + 0xf0, vars + 0x128, angle, factor * 0.050400004f, 0.648f, factor * 0.03316126f, 0);
    if (*(unsigned char **)(vars + 0x8c)) {
        unsigned char *child = *(unsigned char **)(vars + 0x8c);
        if ((child[0x60] & 2) && child[0x42]) anim_start_blended_pal(child, 0, 0, 2);
        *(short *)(*(unsigned char **)(vars + 0x8c) + 0x32) = 30;
        (*(unsigned char **)(vars + 0x8c))[0x31] = 1;
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0x10) = *(B781AimQuad *)(moby + 0x10);
        *(B781AimQuad *)(*(unsigned char **)(vars + 0x8c) + 0xf0) = *(B781AimQuad *)(moby + 0xf0);
        (*(unsigned char **)(vars + 0x8c))[0x30] = 0;
        func_PAL_002A0F68(*(void **)(vars + 0x8c));
        func_002A0F48(*(void **)(vars + 0x8c));
        *(unsigned short *)(*(unsigned char **)(vars + 0x8c) + 0x34) |= 6;
    } else *(void **)(vars + 0x8c) = moby_spawn_at_parent_pose(moby, 0x8ef, 0.25f);
    if ((*(unsigned char **)(vars + 0x164))[0xbc] == 5) {
        if (vec_apply_scaled_value(moby, 20.0f) != -1) {
            gfx_add_draw_callback_third(bike_animate_boost_flame_streak, moby);
            part_spawn_object_following_effect(vars + 0x200, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            part_spawn_object_following_effect(vars + 0x210, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            part_spawn_object_following_effect(vars + 0x220, moby, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
        }
    }
    if (*(int *)(vars + 0x244)) {
        FastVecSub(point, *(unsigned char **)(vars + 0x164) + 0x10, moby + 0x10);
        if (func_L00_002EE290(point) < 100.0f) {
            *(B781AimQuad *)(point) = *(B781AimQuad *)(moby + 0x10);
            point[2] -= 0.25f;
            *(B781AimQuad *)(end) = *(B781AimQuad *)(moby + 0x10);
            emit_trail_effects_pal(moby, end, vars + 0xd0, *(float *)(vars + 0x138) + *(float *)(vars + 0x13c));
        }
    }
}


