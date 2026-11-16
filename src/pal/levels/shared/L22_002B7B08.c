#include "include_asm.h"


#include "common.h"
extern char g_hero_state[];
extern void hero_build_relative_point(void *, float, float, float, int);
extern float cam_get_view_space_vector_length(void *);
extern float vec_length_xy(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_set_view_space_height(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern float cam_get_view_space_angle(void *);
extern float FastVecDot(void *, void *);
typedef struct {
    char pad0[0x18]; void *object; int count;
    char pad20[0x20]; float normal[4];
} CollisionResult;
extern CollisionResult g_collision_l22_result;

/* Checks ahead of the hero for walls and slides the hero's speed along them so it does not run into the wall (PAL). */
void hero_slide_along_walls_pal(int force) {
    float start[4], end[4], extended_start[4], extended_end[4];
    float reach, scale, zero, angle;
    int hit;
    char *velocity = g_hero_state + 0xF0;
    if (cam_get_view_space_vector_length(velocity) < 0.002f) return;
    {
        char *hero = velocity - 0xF0;
        reach = 0.37f;
        scale = 0.5f;
        if ((unsigned)(*(int *)(hero + 0x229C) - 17) < 2) {
            reach = 0;
            scale = 0.7f;
        } else if (*(u8 *)(hero + 0x22B4) == 1) {
            reach = 0.35f;
            scale = 0.27f;
        } else if (*(u8 *)(hero + 0x22B4) == 2) {
            reach = 1;
            scale = 5;
        }
        zero = 0;
        hero_build_relative_point(start, zero, zero, reach, 1);
        hero_build_relative_point(extended_start, zero, zero, reach * 0.3f, 1);
    }
    if (force != 0 || vec_length_xy(g_hero_state + 0xF0) < 0.01f) {
        vec_scale_to_length(end, g_hero_state, scale);
        vec_scale_to_length(extended_end, g_hero_state, scale * 1.4f);
    } else {
        cam_set_view_space_height(end, g_hero_state + 0xF0, 0);
        vec_scale_to_length(end, end, scale);
        FastVecScale(extended_end, end, 1.4f);
    }
    FastVecAdd(end, end, start);
    hit = -1;
    FastVecAdd(extended_end, extended_end, extended_start);
    {
        char *hero = g_hero_state;
        if (CollLine(extended_start, extended_end, 2, *(void **)(hero + 0x2290), 0) && g_collision_l22_result.count > 0)
            hit = GetCollHitMaterial();
    }
    angle = 0;
    {
        char *hero = g_hero_state;
        if (CollLine(start, end, 2, *(void **)(hero + 0x2290), 0) && g_collision_l22_result.count > 0)
            angle = cam_get_view_space_angle(g_collision_l22_result.normal);
    }
    if (angle >= 0.8726647f || hit == 8 || hit == 12) {
        char *hero = g_hero_state;
        CollisionResult *contact = &g_collision_l22_result;
        float *normal = contact->normal;
        float dot;
        *(void **)(hero + 0x270) = contact->object;
        cam_set_view_space_height(normal, normal, 0);
        vec_scale_to_length(normal, normal, 1);
        dot = FastVecDot(normal, hero + 0xF0);
        if (dot < 0) {
            FastVecScale(normal, normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, normal);
        }
    }
}

