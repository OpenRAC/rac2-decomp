#include "include_asm.h"

typedef int L00_00387370_TI128 __attribute__((mode(TI)));
extern void func_00282CC0(void *out, void *target, void *source);
extern void func_002FE880(void *target, void *source, float value);
extern int func_002761F8(void *out, void *target, int size, void *owner, int mode);
extern float D_L00_001AEF30 __attribute__((sda));

/* Copies the object's 16-byte block into the local copy, hands it to the shared
   test and, when the test accepts it, marks the object. */
void func_PAL_L00_0038A370(void *owner)
{
    char *target = (char *)owner + 0x10;
    char *source = *(char **)((char *)owner + 0x68);
    char local[16];

    *(L00_00387370_TI128 *)local = *(L00_00387370_TI128 *)target;
    func_00282CC0(target, target, source);
    func_002FE880(target, source, D_L00_001AEF30 * 4.0000003e-05f);
    if (func_002761F8(local, target, 0x10, owner, 0) != 0)
        *((unsigned char *)owner + 0x20) = 8;
}
