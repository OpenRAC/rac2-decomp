/* Picks the nearest path record during two timed windows and draws its four transformed corners. */
#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

/* Known prefix only; no complete game-object extent is inferred. */
typedef struct { u8 reserved_00[0x34]; int timer; } L02_State;
extern L02_State D_L02_001BE200;
extern void FastVecAdd(void *, void *, void *);

extern unsigned short **D_L02_001A9014 __attribute__((sda));
extern u8 *D_L02_001B3C1C __attribute__((sda));
extern float D_L02_001B2640[] MACRO_ADDR;
extern float vec_distance_xy(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void DrawQuadWithRotatedUVs(void *, int, int, int, int);
/* Draws a glowing quad on the nearest path record while two timed windows are active, using a fixed target point for each window. */
void path_draw_nearest_record_quad(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float target_pos[4] __attribute__((aligned(16)));
    float temp_vec[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    unsigned short *entry;
    u8 *record;
    u8 *best_record;
    float best_dist;
    float dist;
    int effect_id;
    int best_index;
    int window;
    int row;

    for (window = 0; window < 2; window++) {
        effect_id = -1;
        if (window == 0) {
            if (D_L02_001BE200.timer >= 0x3B6) {
                if (D_L02_001BE200.timer < 0x547) {
                    *(TI128 *)temp_vec = 0;
                    temp_vec[0] = 495.0f;
                    temp_vec[1] = 587.0f;
                    temp_vec[2] = 513.0f;
                    qcopy(target_pos, temp_vec);
                    effect_id = 0x3F;
                }
            }
        }
        if (window == 1) {
            if (D_L02_001BE200.timer >= 0x4E2) {
                if (D_L02_001BE200.timer < 0x5DD) {
                    *(TI128 *)temp_vec = 0;
                    temp_vec[0] = 515.0f;
                    temp_vec[1] = 596.0f;
                    temp_vec[2] = 512.0f;
                    qcopy(target_pos, temp_vec);
                    effect_id = 0x40;
                }
            }
        }
        if (effect_id != -1) {
            best_index = -1;
            best_dist = 99999.0f;
            for (entry = D_L02_001A9014[*(int *)vars];
                 entry != 0 && ((short)entry[-1] >= 0 || entry == D_L02_001A9014[*(int *)vars]) &&
                 (record = D_L02_001B3C1C + ((*entry & 0x7FFF) << 6)) != 0;
                 entry++) {
                dist = vec_distance_xy(record + 0x30, target_pos);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_index = *entry & 0x7FFF;
                }
            }
            if (best_index != -1) {
                best_record = D_L02_001B3C1C + (best_index << 6);
                for (row = 0; row < 4; row++) {
                    matrix_mul_vec3(matrix + row * 4, D_L02_001B2640 + row * 4, best_record);
                    FastVecAdd(matrix + row * 4, matrix + row * 4, best_record + 0x30);
                }
                DrawQuadWithRotatedUVs(matrix, effect_id, 2, 0xFF808080, 0);
            }
        }
    }
}
