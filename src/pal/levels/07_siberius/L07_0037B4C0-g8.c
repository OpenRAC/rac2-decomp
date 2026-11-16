#include "include_asm.h"

#include "common.h"
extern void moby_set_state(unsigned char *, int, int);
extern float FastAddRotations(float, float);
extern float FastVecLength(void *);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void gfx_setup_scale_record(int, int);
extern int g_cutscene_l07_active_flag __attribute__((nosda));
extern unsigned short **g_group_l07_id_lists;
extern unsigned char *g_matrix_l07_record_table;
extern float g_group_rotation_speeds[] SDATA(D_L07_001AEBF8);
typedef struct {
    int groups[3];
    float angles[3];
} RotState;

void func_PAL_L07_0037B4C0(unsigned char *a0)
{
    RotState *state = *(RotState **)(a0 + 0x68);
    int i;
    unsigned short *p;
    unsigned char *e;
    float v[4];
    float loc[3];
    float *q;
    int k;
    int m;
    float t;
    float ang;

    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (g_cutscene_l07_active_flag != 0)
            return;
        for (i = 0; i < 3; i++) {
            if (state->groups[i] == -1) {
                continue;
            }
            /* The transfer helper also preserves the original address recomputation. */
            qzero_nc(v);
            ang = FastAddRotations(state->angles[i], g_group_rotation_speeds[i] * 0.0003490659f);
            state->angles[i] = ang;
            v[2] = ang;
            for (p = g_group_l07_id_lists[state->groups[i]];
                 p != 0 && ((short)p[-1] >= 0 || p == g_group_l07_id_lists[state->groups[i]]);
                 p++) {
                e = g_matrix_l07_record_table + ((*p & 0x7FFF) << 6);
                if (e == 0)
                    break;
                q = loc;
                for (k = 0; k < 3; k++)
                    q[k] = *(float *)(e + 0xC + k * 16);
                t = FastVecLength(e);
                euler_rotation_basis(e, v);
                vec_scale_to_length(e, e, t);
                vec_scale_to_length(e + 0x10, e + 0x10, t);
                for (m = 0; m < 3; m++)
                    *(float *)(e + 0xC + m * 16) = q[m];
                gfx_setup_scale_record(*p & 0x7FFF, 1);
            }
        }
        break;
    }
}
