#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);

/* Turns the stored position into one relative to the parent part, or copies it directly when there is no parent. */
void moby_get_pos_rel_parent(u8 *moby, u8 *outPos)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x95) == 0) {
        matrix_mul_vec3(outPos, vars + 0x400, *(u8 **)(vars + 0x418) + 0xC0);
        FastVecAdd(outPos, outPos, *(u8 **)(vars + 0x418) + 0x10);
        return;
    }
    qcopy(outPos, vars + 0x400);
}
