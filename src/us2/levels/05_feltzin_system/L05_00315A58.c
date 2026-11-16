#include "include_asm.h"
#include "common.h"

/* func_US2_L05_00315A58, the v2.00 copy of func_L05_00314E28: the same C, with a new test of
   D_001A79F0 against 0x33 before the class 0xFA0 update. class_id holds its constant before
   the load, so loop.c's lifetime test hoists it in the first pass, ahead of the array giv. */

extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void anim_start_startup_animations(void);
extern void func_US2_002E72D8(char *);
extern void math_store_angle_update_result(char *, char *, int, int, float);
extern void vec_fast_to_int_helper(char *, char *);
extern void quaternion_to_rotation_basis(char *, char *);
extern void moby_compute_local_point(char *, char *, float, float, float);
extern char *part_spawn_shockwave_burst(char *, int, int, int, int, int, int, int, int, int, int, float);
extern int math_random_int_below(int kind);
extern float math_random_signed_float_range(float, float);
extern char *moby_spawn_shot_effect(char *, char *, char *, int, int, int, int, int, float);

typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap[0xC];
    short count;
    char gap2[0x146];
    char *objects[3];
} Scene05;
extern Scene05 g_scene_objects;
extern char g_scene_spawn_entries[];
extern int g_current_map_index __attribute__((sda));

void func_US2_L05_00315A58(void)
{
    float pos[4] __attribute__((aligned(16)));
    union {
        float matrix[12];
        struct { float dest[4], delta[4]; } vectors;
    } scratch __attribute__((aligned(16)));
    int i;
    char *obj;
    anim_start_startup_animations();
    for (i = 0; i < g_scene_objects.count; i++) {
        char *current = g_scene_objects.objects[i];
        if (current && *(short *)(current + 0xAA) == 0xE29)
            *(unsigned short *)(current + 0x34) |= 0x800;
        if (*(short *)(current + 0xAA) == 0xD54) func_US2_002E72D8(current);
        if (current) {
            int class_id = 0xFA0;
            if (*(short *)(current + 0xAA) == class_id && g_current_map_index != 0x33) {
                char *state = *(char **)(current + 0x68);
                if (state) math_store_angle_update_result(current, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
            }
        }
    }
    if (g_current_map_index != 5 || g_scene_objects.mode) return;
    obj = g_scene_objects.objects[2];
    if (g_scene_objects.timer == 0x62) {
        vec_fast_to_int_helper(*(char **)(obj + 0x58) + 0x10, (char *)scratch.matrix);
        quaternion_to_rotation_basis((char *)scratch.matrix, obj + 0xC0);
        moby_compute_local_point(obj, (char *)pos, 4.0f, 3.0f, 5.0f);
        part_spawn_shockwave_burst((char *)pos, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
        moby_compute_local_point(obj, (char *)pos, 9.0f, 4.0f, 4.0f);
        part_spawn_shockwave_burst((char *)pos, 35, 50, 30, 30, 30, 50, 1, 1, 1, 1, 1.0f);
    }
    if ((unsigned int)(g_scene_objects.timer - 0x29) < 0x72 && !math_random_int_below(4)) {
        float sign = 1.0f;
        float *entry;
        if (math_random_int_below(2)) sign = -1.0f;
        entry = (float *)(g_scene_spawn_entries + math_random_int_below(3) * 32);
        moby_compute_local_point(obj, (char *)pos, entry[0], entry[1], entry[2]);
        moby_compute_local_point(obj, (char *)scratch.vectors.dest, entry[4], entry[5], entry[6]);
        scratch.vectors.dest[0] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[1] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[2] += math_random_signed_float_range(0.5f, 1.5f);
        FastVecSub((char *)scratch.vectors.delta, (char *)scratch.vectors.dest, (char *)pos);
        vec_scale_to_length((char *)scratch.vectors.delta, (char *)scratch.vectors.delta, 1.1666667461395264f);
        moby_spawn_shot_effect(obj, (char *)pos, (char *)scratch.vectors.delta, 0x46BE20, 0x327814, 1, 0, 1, sign);
    }
}


