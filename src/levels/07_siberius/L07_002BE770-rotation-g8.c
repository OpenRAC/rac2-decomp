#include "common.h"

extern void moby_set_state(unsigned char *, int, int);
extern float FastAddRotations(float, float);
extern float FastVecLength(void *);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void gfx_setup_scale_record(int, int);

extern int D_L07_001C9780 __attribute__((nosda));
extern unsigned short **D_L07_001A9014;
extern unsigned char *D_L07_001B295C;
extern float D_L07_001AEBF8[] SDATA(D_L07_001AEBF8);

typedef struct {
    int groups[3];
    float angles[3];
} RotState;

/* Slowly spins the linked groups of level pieces around their own centers. */
void UpdateRotatingTransformGroups(unsigned char *moby)
{
    RotState *group_state = *(RotState **)(moby + 0x68);
    int i;
    unsigned short *matrix_index_ptr;
    unsigned char *matrix_entry;
    float rotation[4];
    float loc[3];
    float *saved_pos;
    int axis_index;
    int axis_index2;
    float scale;
    float new_angle;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (D_L07_001C9780 != 0)
            return;
        for (i = 0; i < 3; i++) {
            if (group_state->groups[i] == -1) {
                continue;
            }
            /* The transfer helper also preserves the original address recomputation. */
            qzero_nc(rotation);
            new_angle = FastAddRotations(group_state->angles[i], D_L07_001AEBF8[i] * 0.00029088824f);
            group_state->angles[i] = new_angle;
            rotation[2] = new_angle;
            for (matrix_index_ptr = D_L07_001A9014[group_state->groups[i]];
                 matrix_index_ptr != 0 && ((short)matrix_index_ptr[-1] >= 0 || matrix_index_ptr == D_L07_001A9014[group_state->groups[i]]);
                 matrix_index_ptr++) {
                matrix_entry = D_L07_001B295C + ((*matrix_index_ptr & 0x7FFF) << 6);
                if (matrix_entry == 0)
                    break;
                saved_pos = loc;
                for (axis_index = 0; axis_index < 3; axis_index++)
                    saved_pos[axis_index] = *(float *)(matrix_entry + 0xC + axis_index * 16);
                scale = FastVecLength(matrix_entry);
                euler_rotation_basis(matrix_entry, rotation);
                vec_scale_to_length(matrix_entry, matrix_entry, scale);
                vec_scale_to_length(matrix_entry + 0x10, matrix_entry + 0x10, scale);
                for (axis_index2 = 0; axis_index2 < 3; axis_index2++)
                    *(float *)(matrix_entry + 0xC + axis_index2 * 16) = saved_pos[axis_index2];
                gfx_setup_scale_record(*matrix_index_ptr & 0x7FFF, 1);
            }
        }
        break;
    }
}
