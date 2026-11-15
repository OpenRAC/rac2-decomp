#include "include_asm.h"

#include "common.h"
extern float math_fabs(float a);
extern void matrix_from_basis_rows(void *dst, void *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_transform_by_object_or_given(void *a, void *b, void *c, void *d);
extern void matrix_mul_vec3(void *dst, void *a, void *mtx);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void entity_apply_corrected_pos(char *e, void *v);
extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern int D_L14_001B25B8 __attribute__((sda));

/* For every entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, that func_L14_003C9548 accepts: takes its offset from the owner in the owner's frame;
   when that is beyond 1.0 on the first axis or 1.5 on the second it is pulled back to +-0.5 or
   +-1.25, and the entity is handed the corrected world position (func_L14_003C9658). */
void func_PAL_L14_003E3370(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int clamped;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (p = g_group_entity_lists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[*(int *)(state + 0x68)]);
         p++) {
        e = g_moby_l14_pool + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (entity_is_flag_set((char *)e) != 0) {
                    FastVecSub(off, e + 0x10, self + 0x10);
                    clamped = 0;
                    vec_transform_by_object_or_given(self, off, off, mtx);
                    if (math_fabs(off[0]) > 1.0f) {
                        clamped = 1;
                        if (off[0] > 0.5f)
                            off[0] = 0.5f;
                        else if (off[0] < -0.5f)
                            off[0] = -0.5f;
                    }
                    if (math_fabs(off[1]) > 1.5f) {
                        clamped = 1;
                        if (off[1] > 1.25f)
                            off[1] = 1.25f;
                        else if (off[1] < -1.25f)
                            off[1] = -1.25f;
                    }
                    if (clamped) {
                        matrix_mul_vec3(off, off, self + 0xC0);
                        FastVecAdd(off, off, self + 0x10);
                        entity_apply_corrected_pos((char *)e, off);
                    }
                }
            }
        }
    }
}

