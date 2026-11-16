#include "include_asm.h"
#include "names.h"
extern int IsPointInCuboid(void *point, int index);
extern void FastVecSub(float *out, const float *a, const float *b);
extern void matrix_mul_vec3(float *out, const float *a, const float *b);
extern void timer_start_countdown(int a0, float a1);
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern char g_hero_position[];
extern char g_camera_l02_position[];
extern char *g_matrix_l02_record_table;
extern float g_grab_highlight_level __attribute__((sda));

/* Flags the actor's target when its record is on screen, and refreshes it afterwards. */
void grab_target_update_highlight_pal(char *arg0) {
    char *p = *(char **)(arg0 + 0x68);
    float v[4];

    if (*(int *)(p + 0xDC) == 0) {
        if (IsPointInCuboid(g_hero_position, *(int *)(p + 0xC4)) != 0) {
            FastVecSub(v, (float *)g_camera_l02_position,
                          (float *)(g_matrix_l02_record_table + (*(int *)(p + 0xC4) << 7) + 0x30));
            matrix_mul_vec3(v, v, (float *)(g_matrix_l02_record_table + (*(int *)(p + 0xC4) << 7) + 0x40));
            if (v[0] > 0.0f) {
                *(int *)(p + 0xDC) = 1;
                timer_start_countdown(1, 10.0f);
            }
        }
    } else {
        if (g_grab_highlight_level >= 1.0f) {
            hero_reset_position_and_direction((int)g_hero_position,
                              (int)(g_matrix_l02_record_table + (*(int *)(p + 0xC4) << 7) + 0x70), 0, 1);
            *(short *)(g_hero_position + 0x160) = 8;
        }
    }
}
