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

/* Draws a quad at the path record nearest to a fixed spot, while the level timer is inside one of two windows. (PAL: 50 Hz timings) */
void path_draw_nearest_record_quad_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float anchor[4] __attribute__((aligned(16)));
    float anchor_src[4] __attribute__((aligned(16)));
    float quad[16] __attribute__((aligned(16)));
    unsigned short *entry;
    u8 *record_entry;
    u8 *record;
    float best_dist;
    float dist;
    int texture;
    int best_id;
    int i;
    int k;

    for (i = 0; i < 2; i++) {
        texture = -1;
        if (i == 0) {
            if (g_mob_list.timer >= 0x318) {
                if (g_mob_list.timer < 0x466) {
                    *(TI128 *)anchor_src = 0;
                    anchor_src[0] = 495.0f;
                    anchor_src[1] = 587.0f;
                    anchor_src[2] = 513.0f;
                    qcopy(anchor, anchor_src);
                    texture = 0x3F;
                }
            }
        }
        if (i == 1) {
            if (g_mob_list.timer >= 0x3E8) {
                if (g_mob_list.timer < 0x4E3) {
                    *(TI128 *)anchor_src = 0;
                    anchor_src[0] = 515.0f;
                    anchor_src[1] = 596.0f;
                    anchor_src[2] = 512.0f;
                    qcopy(anchor, anchor_src);
                    texture = 0x40;
                }
            }
        }
        if (texture != -1) {
            best_id = -1;
            best_dist = 99999.0f;
            for (entry = g_record_lists[*(int *)vars];
                 entry != 0 && ((short)entry[-1] >= 0 || entry == g_record_lists[*(int *)vars]) &&
                 (record_entry = g_record_table + ((*entry & 0x7FFF) << 6)) != 0;
                 entry++) {
                dist = vec_distance_xy(record_entry + 0x30, anchor);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_id = *entry & 0x7FFF;
                }
            }
            if (best_id != -1) {
                record = g_record_table + (best_id << 6);
                for (k = 0; k < 4; k++) {
                    matrix_mul_vec3(quad + k * 4, g_path_quad_vectors + k * 4, record);
                    FastVecAdd(quad + k * 4, quad + k * 4, record + 0x30);
                }
                DrawQuadWithRotatedUVs(quad, texture, 2, 0xFF808080, 0);
            }
        }
    }
}

