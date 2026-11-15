/* func_002AD250 in its own unit: it copies 128 bits, and the retail's copy
   keeps both addresses in registers (`lq $v0,0($sX)` / `sq $v0,0($v1)`).
   That is the compiler's opt-in grouped copy, so config/cflags.txt gives this
   file "-O2 -G0 -ffunction-sections -frac2-qcopy"; the flag changes every
   TImode copy in a unit, so the unit holds this function alone. */

#include "include_asm.h"
#include "names.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

/* The matrix the engine copies into place. */
typedef struct { char pad[64]; } Matrix64_002AA800;

extern int func_002AD0B0(unsigned char *a);
extern void func_00283410(char *dst, char *src);
extern void func_00283698(char *dst, char *src);
extern void func_00283098(char *a, char *b, char *c);

/* Puts the matrix of the object the second argument names into the third
   argument, and its two 128-bit fields into the fourth; without the object's
   flag the fields stay as they are. */
int func_002AD250(void *unused, void *object, void *input, void *output)
{
    Matrix64_002AA800 targetMatrix, tempMatrix, sourceMatrix;
    char *target = (char *)GetMobyPrivateValue2((unsigned char *)object);

    if (target == 0) {
        *(TI128 *)output = *(TI128 *)input;
        return 0;
    }
    euler_to_matrix((char *)&targetMatrix, target);
    if (*(int *)(target + 0x3C) & 2) {
        euler_to_matrix((char *)&sourceMatrix, target + 0x20);
        matrix_from_basis_rows((char *)&tempMatrix, (char *)&sourceMatrix);
        matrix_mul_vec3((char *)output, (char *)input, (char *)&tempMatrix);
        matrix_mul_vec3((char *)output, (char *)output, (char *)object + 0xC0);
    } else {
        matrix_mul_vec3((char *)output, (char *)input, (char *)&targetMatrix);
    }
    return 1;
}
