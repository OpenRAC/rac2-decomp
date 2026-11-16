#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x30];
    int state;
    int timer;
    char pad38[12];
    short count;
    char pad46[10];
    char *out;
    char pad54[0x138];
    char *objects[1];
} Context;
extern int g_current_map_index[] __attribute__((sda));
extern char g_tutorial_probe_points[64] SDATA(D_L00_001A93E0);
extern char g_camera_l00_position[];
extern Context g_tutorial_probe_context;
extern char g_tutorial_probe_out_a[];
extern char g_tutorial_probe_out_b[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);

/* While the timer is in its window, builds four points around the 0xD54 moby and selects an object. */
void tutorial_probe_points_update_pal(void) {
    char offset_vec[16];
    int window_start;
    int window_end;
    int object_index;
    int i;
    int point_index;
    char *probe_moby;
    char *point_out;

    if (g_current_map_index[0] != 0)
        return;

    window_start = -1;
    window_end = 9999;
    object_index = 0;
    if (g_tutorial_probe_context.state == 0) {
        window_start = 183;
        window_end = 308;
        object_index = 1;
    }
    if (window_start == -1)
        return;

    if (g_tutorial_probe_context.timer >= window_start && g_tutorial_probe_context.timer <= window_end) {
        g_tutorial_probe_context.out = g_tutorial_probe_out_a;

        probe_moby = 0;
        for (i = 0; i < g_tutorial_probe_context.count; i++) {
            char *object = g_tutorial_probe_context.objects[i];

            if (*(short *)(object + 0xAA) == 0xD54) {
                probe_moby = object;
                break;
            }
        }

        if (probe_moby) {
            char *moby_matrix;

            point_out = g_tutorial_probe_out_b;
            moby_matrix = probe_moby + 0xC0;
            for (point_index = 0; point_index < 4; point_index++) {
                matrix_mul_vec3(point_out, g_tutorial_probe_points + point_index * 16, moby_matrix);
                FastVecAdd(point_out, point_out, probe_moby + 0x10);
                FastVecSub(offset_vec, g_camera_l00_position, point_out);
                vec_scale_to_length(offset_vec, offset_vec, 0.15f);
                FastVecAdd(point_out, point_out, offset_vec);
                point_out += 16;
            }
        }
        *(char **)(g_tutorial_probe_context.out + 0x68) = g_tutorial_probe_context.objects[object_index];
    } else {
        g_tutorial_probe_context.out = 0;
    }
}
