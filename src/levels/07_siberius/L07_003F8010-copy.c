#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);
extern void moby_update_ground_check(void *);
extern void func_002A0F48(void *);
extern void moby_transform_joint_point(char *, int, char *);
extern void copy_matrix3x4(void *, void *);
/* The third argument to func_0029FC20 is a full 64-byte affine matrix. */
/* Keeps the two parts attached to the object in place: copies position and rotation to the first and places the second using the object transform. */
void ship_attach_parts(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *mainPart = *(u8 **)(vars + 0x410);
    struct { u8 basis[48]; u8 translation[16]; } __attribute__((aligned(16))) transform;
    if (mainPart != 0) {
        qcopy(mainPart + 0x10, moby + 0x10);
        qcopy(mainPart + 0xF0, moby + 0xF0);
        moby_update_ground_check(mainPart);
    }
    func_002A0F48(*(u8 **)(vars + 0x410));
    if (*(u8 **)(vars + 0x414) != 0) {
        moby_transform_joint_point((char *)moby, 0, (char *)&transform);
        copy_matrix3x4(*(u8 **)(vars + 0x414) + 0xC0, transform.basis);
        qcopy(*(u8 **)(vars + 0x414) + 0x10, transform.translation);
    }
    func_002A0F48(*(u8 **)(vars + 0x414));
}
