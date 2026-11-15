#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);

/* Stores a position for the object, adjusted by its parent part when it has one. */
void moby_store_attached_pos(u8 *moby, u8 *inPos)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x95) == 0) {
        u8 *result = vars + 0x400;

        FastVecSub(result, inPos, *(u8 **)(vars + 0x418) + 0x10);
        vec_transform_by_object_or_given(*(u8 **)(vars + 0x418), result, result, 0);
        return;
    }
    qcopy(vars + 0x400, inPos);
}
