#include "include_asm.h"

#include "common.h"
extern void matrix_from_basis_rows(void *dst, void *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_transform_by_object_or_given(void *a, void *b, void *c, void *d);
extern float math_fabs(float a);
extern void matrix_mul_vec3(void *dst, void *a, void *mtx);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void entity_apply_corrected_pos(char *e, void *v);
extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern int D_L14_001B25B8 __attribute__((sda));
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

/* The twin of func_L14_003DF200 for the group word at +0x64: the same pass over the entities
   of the owner's group (not the states 0xFE and 0xFD, not the class 0xA59, accepted by
   func_L14_003C9548), with the box centred at -2.0 on the first axis: beyond 0.8 of it the
   offset is pulled back to -1.5 or -2.5, beyond 0.8 on the second axis to +-0.5, and the entity
   is handed the corrected world position (func_L14_003C9658). */
void func_PAL_L14_003CF468(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int clamped;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (p = g_group_entity_lists[*(int *)(state + 0x64)];
         (*(int *)(state + 0x64) & 0xFF) != 0xFF && *(int *)(state + 0x64) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[*(int *)(state + 0x64)]);
         p++) {
        e = g_moby_l14_pool + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (*(short *)(e + 0xAA) != 0xA59) {
                    if (entity_is_flag_set((char *)e) != 0) {
                        FastVecSub(off, e + 0x10, self + 0x10);
                        clamped = 0;
                        vec_transform_by_object_or_given(self, off, off, mtx);
                        if (math_fabs(off[0] + 2.0f) > 0.8f) {
                            clamped = 1;
                            if (off[0] > -1.5f)
                                off[0] = -1.5f;
                            else if (off[0] < -2.5f)
                                off[0] = -2.5f;
                        }
                        if (math_fabs(off[1]) > 0.8f) {
                            clamped = 1;
                            if (off[1] > 0.5f)
                                off[1] = 0.5f;
                            else if (off[1] < -0.5f)
                                off[1] = -0.5f;
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
}

