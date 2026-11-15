#include "include_asm.h"
#include "names.h"

typedef int L00_00387370_TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *out, void *target, void *source);
extern void vec_add_object_direction_scaled(void *target, void *source, float value);
extern int CollLine(void *out, void *target, int size, void *owner, int mode);
extern float D_L00_001AEF30 __attribute__((sda));

/* Copies the object's 16-byte block into the local copy, hands it to the shared
   test and, when the test accepts it, marks the object. */
void func_PAL_L00_0038A370(void *owner)
{
    char *target = (char *)owner + 0x10;
    char *source = *(char **)((char *)owner + 0x68);
    char local[16];

    *(L00_00387370_TI128 *)local = *(L00_00387370_TI128 *)target;
    FastVecAdd(target, target, source);
    vec_add_object_direction_scaled(target, source, D_L00_001AEF30 * 4.0000003e-05f);
    if (CollLine(local, target, 0x10, owner, 0) != 0)
        *((unsigned char *)owner + 0x20) = 8;
}
