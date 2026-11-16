#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x264]; float scale;
    unsigned char pad1[0x278 - 0x268]; float height;
    unsigned char pad2[4]; float angle;
    unsigned char first_flag, second_flag, pad3[2];
    float distance, clearance; int valid;
    unsigned char pad4[0x340 - 0x294]; int enabled;
    unsigned char pad5[0x2290 - 0x344]; void *object;
    unsigned char pad6[0x22BD - 0x2294]; unsigned char gate;
} HeroProbeState;
extern HeroProbeState g_hero_state;
typedef struct {
    unsigned char pad0[0x18]; void *object;
    unsigned char pad1[4]; float hit_position[4];
    unsigned char pad2[0x10]; float direction[4];
} SceneProbeState;
extern SceneProbeState g_collision_result;
extern int g_frame_l00_counter MACRO_ADDR;
extern void ref_L00_002C2DE8_00(void);
extern int hero_test_reach_blend(float *, float, float);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern int moby_is_in_special_class_range(void *);
extern void hero_build_relative_point(float *, float, float, int, float);
extern int CollLine(void *, void *, int, void *, int);
extern float fast_vec_dist(void *, void *);
extern int coll_test_point(void *, int, void *, float);

void hero_probe_ground_and_ledge_pal(void)
{
    float first[4], second[4], probe[4];
    if (g_hero_state.gate != 0) return;
    ref_L00_002C2DE8_00();
    if (g_frame_l00_counter % 3 == 0) {
        g_hero_state.height = 4.0f;
        g_hero_state.first_flag = 0;
        g_hero_state.second_flag = 0;
        if (hero_test_reach_blend(&g_hero_state.height, 0.7f, 4.0f)) {
            g_hero_state.angle = mat_fast_helper_a(g_collision_result.direction[2], vec_length_xy(g_collision_result.direction));
            if (g_collision_result.object) {
                g_hero_state.second_flag = 1;
                if (moby_is_in_special_class_range(g_collision_result.object)) g_hero_state.first_flag = 1;
            }
        }
    }
    if (g_frame_l00_counter % 5 == 0) {
        int hit;
        float distance, offset;
        g_hero_state.valid = 0;
        g_hero_state.distance = 0.0f;
        if (g_hero_state.enabled == 0) return;
        hero_build_relative_point(first, 1.1f, 0.0f, 1, 1.0f);
        hero_build_relative_point(second, 1.1f, 0.0f, 1, -20.0f);
        if (second[2] < 0.5f) second[2] = 0.5f;
        distance = 20.0f;
        hit = CollLine(first, second, 2, g_hero_state.object, 0);
        if (hit) distance = fast_vec_dist(first, g_collision_result.hit_position);
        if (!hit || 3.0f < distance) {
            offset = -0.4f;
            do {
                hero_build_relative_point(probe, offset + 1.1f, 0.0f, 1, 0.0f);
                if (!coll_test_point(probe, 2, 0, g_hero_state.scale)) {
                    g_hero_state.valid = 1;
                    if (!hit) g_hero_state.distance = 20.0f;
                    else g_hero_state.distance = distance;
                    g_hero_state.clearance = g_hero_state.scale + offset;
                    if (g_hero_state.clearance < 0.0f) g_hero_state.clearance = 0.0f;
                    return;
                }
                offset += 0.1f;
            } while (offset < 0.5f);
        }
    }
}
