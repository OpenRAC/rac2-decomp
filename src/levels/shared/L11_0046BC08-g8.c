#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;

/* One bolt's row of the level's vertex table (640 bytes). */
typedef struct { Vector core[20]; Vector wave[20]; } BoltBuffer;

/* The bolt's state record (object + 0x68). */
typedef struct {
    Vector start;   /* 0x00 */
    Vector end;     /* 0x10 */
    char pad20[12];
    int count;      /* 0x2C */
    int pad30;
    int path;       /* 0x34 */
    int row;        /* 0x38 */
} BoltState;

extern int g_lightning_point_count __attribute__((sda));
extern int g_lightning_rebuild_flag __attribute__((sda));
extern float g_lightning_bolt_length __attribute__((sda));
extern float g_lightning_start_angle __attribute__((sda));
extern float g_lightning_l11_horizontal_phase __attribute__((sda));
extern float g_lightning_vertical_angle __attribute__((sda));
extern BoltBuffer g_ribbon_row_table[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* When the bolt's reset flag is set: lays the row's core points on the straight line
 * from start towards end, one step apart, and clears the jitter and wave phases. */
void ResetBoltPointsToLine(char *object)
{
    Vector delta, step;
    BoltState *state = *(BoltState **)(object + 0x68);
    Vector *prev;
    int i;

    if (g_lightning_rebuild_flag) {
        g_lightning_rebuild_flag = 0;
        FastVecSub(&delta, &state->end, &state->start);
        vec_scale_to_length(&step, &delta, g_lightning_bolt_length / (float)g_lightning_point_count);
        qcopy_nc(&g_ribbon_row_table[state->row].core[0], &state->start);
        for (i = 1; i < g_lightning_point_count; i++) {
            /* Previous point: the row's points from index -1. */
            prev = &g_ribbon_row_table[state->row].core[-1];
            FastVecAdd(&g_ribbon_row_table[state->row].core[i], &prev[i], &step);
        }
        g_lightning_start_angle = 0.0f;
        g_lightning_l11_horizontal_phase = 0.0f;
        g_lightning_vertical_angle = 0.0f;
    }
}
