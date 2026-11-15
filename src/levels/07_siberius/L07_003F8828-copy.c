#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

/* Stores a position for the object, adjusted by its parent part when it has one. */
void func_L07_003F8828(u8 *moby, u8 *inPos)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x95) == 0) {
        u8 *result = vars + 0x400;

        FastVecSub(result, inPos, *(u8 **)(vars + 0x418) + 0x10);
        TransformVectorByObjectOrGiven(*(u8 **)(vars + 0x418), result, result, 0);
        return;
    }
    qcopy(vars + 0x400, inPos);
}
