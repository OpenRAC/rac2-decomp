#include "include_asm.h"

#include "common.h"
extern char g_camera_l02_position;
extern char *g_route_polygons[];
extern float math_fabs(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern void set_follow_camera_orbit_clamp_mode(int);
extern void cam_set_lock_flag(void);
extern float g_path_heading_easing_scale __attribute__((sda));
extern char *g_route_polygons[];
extern char *g_route_polygons[];
extern float FastAddRotations(float, float);

/* Updates the heading (float at +0x38 of the actor's state) from the path D_L02_001FF1C0[*state]:
   its first word is the point count and its 16-byte points start at +0x10. The segment runs from
   point i (the index at +0x30, one back when it is the last point) to point j (i plus the
   lookahead at +0x3C, at most the last point). The segment's angle (func_00283248) minus the
   angle of the hero's direction vector (floats at +0x160 of its state, the pointer at +0x70 of the
   object at D_L02_001BA500 + 0x50) turned by pi, wrapped by func_00283B98 and func_00283BE0, clears
   the heading when it is under about a tenth of a degree; otherwise func_002AAC80 eases the
   heading towards it, weighted by the progress (+0x34, minus 6, over 8, at least 0). The heading
   is then copied into the hero's state at +0x1D4, +0x1DC gets 1.0 and, from a progress of 0.9, the
   two shared calls run. Nothing happens while the hero's halfword at +0x86 is not 0. */
void path_update_hero_heading_pal(char *moby) {
    char *hero = *(char **)(&g_camera_l02_position + 0x50);
    char *state;
    char *hero_state;
    char *cam_state;
    float *hero_dir;
    char *path;
    float scale;
    float path_angle;
    float hero_angle;
    float ease_weight;
    int last;
    int from_index;
    int to_index;

    if (*(short *)(hero + 0x86) != 0)
        return;
    state = *(char **)(moby + 0x68);
    hero_state = *(char **)(hero + 0x70);
    cam_state = hero_state + 0x1C0;
    hero_dir = (float *)(hero_state + 0x160);
    path = g_route_polygons[*(int *)state];
    scale = (*(float *)(state + 0x34) - 6.0f) * 0.125f;
    if (scale < 0.0f)
        scale = 0.0f;
    last = *(int *)path - 1;
    from_index = *(int *)(state + 0x30);
    if (from_index == last)
        from_index--;
    to_index = from_index + *(int *)(state + 0x3C);
    if (to_index > last)
        to_index = last;
    {
        char *from_point = path + from_index * 16;
        char *to_point = path + to_index * 16;

        path_angle = mat_fast_helper_a(*(float *)(to_point + 0x10) - *(float *)(from_point + 0x10),
                           *(float *)(to_point + 0x14) - *(float *)(from_point + 0x14));
    }
    hero_angle = mat_fast_helper_a(hero_dir[0], hero_dir[1]);
    hero_angle = FastAddRotations(hero_angle, 3.1415927f);
    path_angle = fast_subtract_rotations(path_angle, hero_angle);
    if (math_fabs(path_angle) < 0.0017453294713050127f) {
        *(float *)(state + 0x38) = 0.0f;
    } else {
        ease_weight = scale * g_path_heading_easing_scale;
        math_approach_target_with_braking(state + 0x38, path_angle, (ease_weight + 0.5f) * 0.00040000002f,
                      (ease_weight + 0.5f) * 0.00040000002f, ease_weight * 0.020000001f);
    }
    *(float *)(cam_state + 0x1C) = 1.0f;
    *(float *)(cam_state + 0x14) = *(float *)(state + 0x38);
    if (scale >= 0.9f) {
        set_follow_camera_orbit_clamp_mode(0);
        cam_set_lock_flag();
    }
}

