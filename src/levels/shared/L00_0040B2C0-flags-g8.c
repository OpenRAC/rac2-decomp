#include "include_asm.h"
#include "names.h"


typedef int TI128 __attribute__((mode(TI)));
extern float D_L00_001AF7A4 __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

/* Same body as func_L00_003ACC88, with this function's own callees. */
extern float ref_L00_0040B2C0_00 __attribute__((sda));
/* Finds a point at a fixed offset from the object, turned by the object's rotation. */
void func_L00_0040B2C0(char *moby, char *outPos)
{
    float worldOffset[4];
    float localOffset[4];
    TI128 zeroVec = 0;

    *(TI128 *)localOffset = zeroVec;
    localOffset[0] = ref_L00_0040B2C0_00;
    localOffset[3] = 1.0f;
    *(TI128 *)worldOffset = *(TI128 *)localOffset;
    matrix_mul_vec3(worldOffset, worldOffset, moby + 0xC0);
    FastVecAdd(outPos, worldOffset, moby + 0x10);
}
