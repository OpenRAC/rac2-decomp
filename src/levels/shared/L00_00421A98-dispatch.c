#include "include_asm.h"
#include "names.h"
typedef int TI __attribute__((mode(TI)));
extern void *D_L00_002A2E30[7];
extern TI func_00334710(int, TI *);
extern void func_00282CC0(void *, void *, void *);
/* Adds a stored or transformed vector, returning whether the mode accepts it. */
/* Offsets a point by the camera's stored offset (or its current position) depending on the mode. Returns 0 for the plain modes and 1 otherwise. */
int func_L00_00421A98(char *self, void *src, void *dst, int mode)
{
    /* Only the level's existing dispatch table is read at runtime. */
    static void *arms[7] = {&&transformed, &&direct, &&zero, &&zero, &&zero, &&zero, &&zero};
    TI local;
    int ret = 1;
    char *vector = *(char **)(self + 0x70) + 0x60;
    if ((unsigned int)(mode - 1) >= 7) goto direct;
    goto *D_L00_002A2E30[mode - 1];
zero:
    FastVecAdd(dst, src, vector);
    ret = 0;
    goto done;
transformed:
    CopyHeroVectorToOut((int)self, &local);
    FastVecAdd(dst, src, &local);
    goto done;
direct:
    FastVecAdd(dst, src, vector);
done:
    return ret;
}
