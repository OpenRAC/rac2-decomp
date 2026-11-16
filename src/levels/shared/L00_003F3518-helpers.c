/* Collect transformed group points and blended colors for the shared draw emitter.
 * The local snapshots remain complete 16-byte vectors in the stack workspace.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Partial global view with the complete vector consumed by the math helper. */
typedef struct {
    char reserved_000[0x140];
    float x_140;
    float y_144;
    float z_148;
    float w_14C;
} Aimvec_F0b10;

extern Aimvec_F0b10 g_scalar_transition_state;

extern int math_fast_helper_a(char *local, float value);
extern void matrix_mul_vec3(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(char *off, char *v, char *pos);
extern void vec_scale_to_length(char *dst, char *src, float angle);
extern float FastVecDot(char *, char *);
extern int math_lerp_int_fraction(int, int, float);
extern void gfx_append_point_and_color(char *, int *, char *, int *, int *);
extern void DrawOffsetBillboardBatch(int, void *, void *, float, float);

extern unsigned short **g_level_reloc_record __attribute__((sda));
extern unsigned char *g_tie_table __attribute__((sda));
extern unsigned char *g_tie_matrix_table __attribute__((sda));

/* Goes through a list of lit points near the object, keeps the ones in view, and works out
   each colour from how much the point faces the camera. Then it sends them all to be drawn. */
void gfx_draw_lit_group_points(char *obj)
{
    unsigned char *vars = *(unsigned char **)(obj + 0x68);
    char buf0[0x460] __attribute__((aligned(16)));
    char buf1[0x120] __attribute__((aligned(16)));
    char pos[16] __attribute__((aligned(16)));
    char group_point[16] __attribute__((aligned(16)));
    char offset[16] __attribute__((aligned(16)));
    char scratch[16] __attribute__((aligned(16)));
    char facing[16] __attribute__((aligned(16)));
    char facing_base[16] __attribute__((aligned(16)));
    int idx;
    int count;
    int color;
    unsigned short *index_list;
    unsigned char *entry;
    float dot;

    idx = *(int *)vars;
    count = 0;
    index_list = g_level_reloc_record[idx];
    for (; index_list != 0 && ((short)index_list[-1] >= 0 || index_list == g_level_reloc_record[*(int *)vars]) &&
           (entry = g_tie_matrix_table + ((*index_list & 0x7FFF) << 6)) != 0;
         index_list++) {
        qcopy(pos, g_tie_table + ((*index_list & 0x7FFF) << 5));
        *(float *)(pos + 12) += *(float *)(vars + 0x4C);
        if (math_fast_helper_a(pos, *(float *)(vars + 0x60)) < 0)
            continue;
        qcopy(group_point, entry + 0x30);
        *(TI128 *)scratch = 0;
        *(float *)(scratch + 0) = *(float *)(vars + 0x50);
        *(float *)(scratch + 4) = *(float *)(vars + 0x54);
        *(float *)(scratch + 8) = *(float *)(vars + 0x58);
        *(TI128 *)offset = *(TI128 *)scratch;
        matrix_mul_vec3(offset, offset, (char *)entry);
        FastVecAdd(group_point, group_point, offset);
        if (*(int *)(vars + 0x6C) != 0) {
            gfx_append_point_and_color(group_point, (int *)(vars + 0x30), buf0, (int *)buf1, &count);
            continue;
        }
        FastVecSub(scratch, (char *)&g_scalar_transition_state.x_140, group_point);
        vec_scale_to_length(scratch, scratch, 1.0f);
        *(TI128 *)facing_base = 0;
        *(float *)(facing_base + 0) = *(float *)(vars + 0x40);
        *(float *)(facing_base + 4) = *(float *)(vars + 0x44);
        *(float *)(facing_base + 8) = *(float *)(vars + 0x48);
        *(TI128 *)facing = *(TI128 *)facing_base;
        matrix_mul_vec3(facing, facing, (char *)entry);
        vec_scale_to_length(facing, facing, 1.0f);
        dot = FastVecDot(scratch, facing);
        if (*(float *)(vars + 0x3C) < dot) {
            dot = dot * 0.5f + 0.5f;
            if (*(int *)(vars + 0x38) != 0)
                dot = dot * dot;
            color = math_lerp_int_fraction(*(int *)(vars + 0x34), *(int *)(vars + 0x30), dot);
            gfx_append_point_and_color(group_point, &color, buf0, (int *)buf1, &count);
        }
    }
    DrawOffsetBillboardBatch(count, buf0, buf1, *(float *)(vars + 0x4C), *(float *)(vars + 0x5C));
}
