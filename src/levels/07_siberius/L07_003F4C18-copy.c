#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);

/* Gets the world positions of the two ends of the beam, following its support object if it has one. */
void beam_get_end_points(u8 *moby, u8 *start, u8 *end)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 **)(vars + 0x20) != 0) {
        matrix_mul_vec3(start, vars, *(u8 **)(vars + 0x20) + 0xC0);
        FastVecAdd(start, start, *(u8 **)(vars + 0x20) + 0x10);
        matrix_mul_vec3(end, vars + 0x10, *(u8 **)(vars + 0x20) + 0xC0);
        FastVecAdd(end, end, *(u8 **)(vars + 0x20) + 0x10);
        return;
    }
    qcopy(start, vars);
    qcopy(end, vars + 0x10);
}
