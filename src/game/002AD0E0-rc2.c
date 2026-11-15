#include "names.h"
/* func_002AD0E0 in its own unit: its early-out copies 128 bits through lq/sq
   with both addresses in registers, which is the compiler's opt-in grouped
   copy (config/cflags.txt gives this file -frac2-qcopy), so the unit holds
   this function alone. */

#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct { char pad[64]; } Matrix64_002AD0E0;

extern int moby_get_private_value_2(unsigned char *a);
extern void euler_to_matrix(char *dst, char *src);
extern void matrix_from_basis_rows(char *dst, char *src);
extern void matrix_mul_vec3(char *a, char *b, char *c);
extern void FastVecAdd(char *dst, char *a, char *b);
extern void FastVecSub(char *dst, char *a, char *b);
extern void multiply_matrix(char *a, char *b, char *c);
extern void mat_get_euler_angles(char *a, char *b);

/* Places the position a2 into a4 relative to the object a1 and its matrix
   target, and a3 into a5; without the object's target both are plain copies. */
int moby_transform_point_and_rotation_by_parent(void *unused, void *object, void *position, void *rotation, void *outPosition, void *outRotation)
{
    Matrix64_002AD0E0 targetMatrix, tempMatrix, sourceMatrix;
    char *target = (char *)moby_get_private_value_2((unsigned char *)object);

    if (target == 0) {
        *(TI128 *)outPosition = *(TI128 *)position;
        *(TI128 *)outRotation = *(TI128 *)rotation;
        return 0;
    }
    euler_to_matrix((char *)&targetMatrix, target);
    FastVecAdd((char *)outPosition, (char *)position, target + 0x10);
    FastVecSub((char *)outPosition, (char *)outPosition, (char *)object + 0x10);
    if (*(int *)(target + 0x3C) & 2) {
        euler_to_matrix((char *)&sourceMatrix, target + 0x20);
        matrix_from_basis_rows((char *)&tempMatrix, (char *)&sourceMatrix);
        matrix_mul_vec3((char *)outPosition, (char *)outPosition, (char *)&tempMatrix);
        matrix_mul_vec3((char *)outPosition, (char *)outPosition, (char *)object + 0xC0);
    } else {
        matrix_mul_vec3((char *)outPosition, (char *)outPosition, (char *)&targetMatrix);
    }
    FastVecAdd((char *)outPosition, (char *)outPosition, (char *)object + 0x10);
    euler_to_matrix((char *)&tempMatrix, (char *)rotation);
    multiply_matrix((char *)&tempMatrix, (char *)&targetMatrix, (char *)&tempMatrix);
    mat_get_euler_angles((char *)&tempMatrix, (char *)outRotation);
    return 1;
}
