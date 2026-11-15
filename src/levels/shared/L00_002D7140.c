#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

typedef float f32;

extern void func_0026FF08(f32, f32, f32, f32, s32, s32);

/* clears object byte then calls the measured four-float helper when the field is nonnegative */
/* Ends a camera override: clears its active flag and eases the camera blend back to normal. */
void func_L00_002D7140(u8 *object) {
 object[0x1d]=0;
 if (*(f32 *)(object+0x10)>=0.0f)
  SetCameraValueTarget(1.1243411302566528f,0.005f,0.2f,0.0f,0,3);
}


extern char D_L00_001B8C80[];
extern float D_L00_001BD370;
extern float func_00283198(f32);
extern float func_00283180(f32);
extern void func_0027AB40(void);

/* Initialize the shared blend fields and the quotient of the two helper results. */
/* Sets up the starting camera blend values when a level begins. */
void func_L00_002D75F0(void) {
    u8 *camState = (u8 *)D_L00_001B8C80;
    float blendValue = 1.1243411f;
    float angle = 0.56217057f;
    float first, second;

    camState[0x3E9] = 0;
    *(float *)(camState + 0x3D4) = blendValue;
    *(float *)(camState + 0x3D8) = blendValue;
    first = FastSinOrCosB(angle);
    second = FastSinOrCosA(angle);
    D_L00_001BD370 = first / second;
    UpdateViewContext();
    *(float *)(camState + 0x3DC) = 0.005f;
    *(float *)(camState + 0x3E0) = 0.2f;
    *(int *)(camState + 0x3D0) = 0;
    *(int *)(camState + 0x3E4) = 0;
}
