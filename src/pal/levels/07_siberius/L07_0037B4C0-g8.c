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

/* Slowly spins the linked groups of level pieces around their own centers (PAL: 50 Hz timings). */
void rotating_transform_groups_update_pal(unsigned char *moby)
{
    RotState *state = *(RotState **)(moby + 0x68);
    int i;
    unsigned short *id_ptr;
    unsigned char *record;
    float rot_euler[4];
    float saved_pos[3];
    float *saved;
    int axis;
    int axis2;
    float scale_len;
    float angle;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (g_cutscene_l07_active_flag != 0)
            return;
        for (i = 0; i < 3; i++) {
            if (state->groups[i] == -1) {
                continue;
            }
            /* The transfer helper also preserves the original address recomputation. */
            qzero_nc(rot_euler);
            angle = FastAddRotations(state->angles[i], g_group_rotation_speeds[i] * 0.0003490659f);
            state->angles[i] = angle;
            rot_euler[2] = angle;
            for (id_ptr = g_group_l07_id_lists[state->groups[i]];
                 id_ptr != 0 && ((short)id_ptr[-1] >= 0 || id_ptr == g_group_l07_id_lists[state->groups[i]]);
                 id_ptr++) {
                record = g_matrix_l07_record_table + ((*id_ptr & 0x7FFF) << 6);
                if (record == 0)
                    break;
                saved = saved_pos;
                for (axis = 0; axis < 3; axis++)
                    saved[axis] = *(float *)(record + 0xC + axis * 16);
                scale_len = FastVecLength(record);
                euler_rotation_basis(record, rot_euler);
                vec_scale_to_length(record, record, scale_len);
                vec_scale_to_length(record + 0x10, record + 0x10, scale_len);
                for (axis2 = 0; axis2 < 3; axis2++)
                    *(float *)(record + 0xC + axis2 * 16) = saved[axis2];
                gfx_setup_scale_record(*id_ptr & 0x7FFF, 1);
            }
        }
        break;
    }
}
