#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_L00_002D7940(char *p);
extern void func_L00_002D7958(char *dst, char *src, f32 x);
extern void func_L00_00427C78(char *p);

extern char D_00189EA0[];

/* Installs two aligned control vectors, raises the first Z component and
 * copies it into the saved state before clearing and refreshing the blend. */
void func_L00_004284B0(char *camera)
{
    char *state;
    char *blendVec;
    char *cameraAlias = camera;
    {
        char *initial = *(char **)(camera + 0x70);
        char *block = initial + 0xB0;
        qcopy(block, gHeroPosition);
        *(f32 *)(block + 8) += 2.0f;
        qcopy(initial + 0xC0, gHeroPosition + 0x10);
        state = *(char **)(camera + 0x70);
        qcopy(state + 0x80, block);
    }
    blendVec = state + 0x14;
    ZeroFiveWords(blendVec);
    *(f32 *)(state + 0x1C) = 4.64f;
    CopyVec5WithFirstBlended(cameraAlias + 0x50, blendVec, 0.0f);
    InitCameraBlendValues_L00_2(cameraAlias);
}
