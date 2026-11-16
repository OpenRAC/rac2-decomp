#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { u8 reserved_00[0x34]; int timer; } L02_State;
extern L02_State g_mob_list;
extern void FastVecAdd(void *, void *, void *);
extern unsigned short **g_record_lists __attribute__((sda));
extern u8 *g_record_table __attribute__((sda));
extern float g_path_quad_vectors[] MACRO_ADDR;
extern float vec_distance_xy(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void DrawQuadWithRotatedUVs(void *, int, int, int, int);

/* Draws a textured quad over the closest path record for two spots in set time ranges of the level (USA v1.01: path_draw_nearest_record_quad). */
void path_draw_nearest_record_quad_us2(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float target[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    unsigned short *list_entry;
    u8 *entry;
    u8 *record;
    float best_dist;
    float dist;
    int quad_index;
    int best_id;
    int pass;
    int corner;

    for (pass = 0; pass < 2; pass++) {
        quad_index = -1;
        if (pass == 0) {
            if (g_mob_list.timer >= 0x3B6) {
                if (g_mob_list.timer < 0x547) {
                    *(TI128 *)point = 0;
                    point[0] = 495.0f;
                    point[1] = 587.0f;
                    point[2] = 513.0f;
                    qcopy(target, point);
                    quad_index = 0x3F;
                }
            }
        }
        if (pass == 1) {
            if (g_mob_list.timer >= 0x4B0) {
                if (g_mob_list.timer < 0x5DD) {
                    *(TI128 *)point = 0;
                    point[0] = 515.0f;
                    point[1] = 596.0f;
                    point[2] = 512.0f;
                    qcopy(target, point);
                    quad_index = 0x40;
                }
            }
        }
        if (quad_index != -1) {
            best_id = -1;
            best_dist = 99999.0f;
            for (list_entry = g_record_lists[*(int *)vars];
                 list_entry != 0 && ((short)list_entry[-1] >= 0 || list_entry == g_record_lists[*(int *)vars]) &&
                 (entry = g_record_table + ((*list_entry & 0x7FFF) << 6)) != 0;
                 list_entry++) {
                dist = vec_distance_xy(entry + 0x30, target);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_id = *list_entry & 0x7FFF;
                }
            }
            if (best_id != -1) {
                record = g_record_table + (best_id << 6);
                for (corner = 0; corner < 4; corner++) {
                    matrix_mul_vec3(matrix + corner * 4, g_path_quad_vectors + corner * 4, record);
                    FastVecAdd(matrix + corner * 4, matrix + corner * 4, record + 0x30);
                }
                DrawQuadWithRotatedUVs(matrix, quad_index, 2, 0xFF808080, 0);
            }
        }
    }
}

