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
    char temp[16];
    int low;
    int high;
    int which;
    int i;
    int n;
    char *found;
    char *out;

    if (g_current_map_index[0] != 0)
        return;

    low = -1;
    high = 9999;
    which = 0;
    if (g_tutorial_probe_context.state == 0) {
        low = 183;
        high = 308;
        which = 1;
    }
    if (low == -1)
        return;

    if (g_tutorial_probe_context.timer >= low && g_tutorial_probe_context.timer <= high) {
        g_tutorial_probe_context.out = g_tutorial_probe_out_a;

        found = 0;
        for (i = 0; i < g_tutorial_probe_context.count; i++) {
            char *obj = g_tutorial_probe_context.objects[i];

            if (*(short *)(obj + 0xAA) == 0xD54) {
                found = obj;
                break;
            }
        }

        if (found) {
            char *matrix;

            out = g_tutorial_probe_out_b;
            matrix = found + 0xC0;
            for (n = 0; n < 4; n++) {
                matrix_mul_vec3(out, g_tutorial_probe_points + n * 16, matrix);
                FastVecAdd(out, out, found + 0x10);
                FastVecSub(temp, g_camera_l00_position, out);
                vec_scale_to_length(temp, temp, 0.15f);
                FastVecAdd(out, out, temp);
                out += 16;
            }
        }
        *(char **)(g_tutorial_probe_context.out + 0x68) = g_tutorial_probe_context.objects[which];
    } else {
        g_tutorial_probe_context.out = 0;
    }
}
