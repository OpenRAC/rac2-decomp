#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

typedef float f32;

extern void cam_set_value_target(f32, f32, f32, f32, s32, s32);

/* clears object byte then calls the measured four-float helper when the field is nonnegative */
/* Ends a camera override: clears its active flag and eases the camera blend back to normal. */
void cam_end_override(u8 *object) {
 object[0x1d]=0;
 if (*(f32 *)(object+0x10)>=0.0f)
  cam_set_value_target(1.1243411302566528f,0.005f,0.2f,0.0f,0,3);
}


extern char g_scalar_transition_state[];
extern float g_fast_math_ratio;
extern float math_fast_sin_or_cos_b(f32);
extern float math_fast_sin_or_cos_a(f32);
extern void UpdateViewContext(void);

/* Initialize the shared blend fields and the quotient of the two helper results. */
/* Sets up the starting camera blend values when a level begins. */
void cam_l00_init_blend_values(void) {
    u8 *camState = (u8 *)g_scalar_transition_state;
    float blendValue = 1.1243411f;
    float angle = 0.56217057f;
    float first, second;

    camState[0x3E9] = 0;
    *(float *)(camState + 0x3D4) = blendValue;
    *(float *)(camState + 0x3D8) = blendValue;
    first = math_fast_sin_or_cos_b(angle);
    second = math_fast_sin_or_cos_a(angle);
    g_fast_math_ratio = first / second;
    UpdateViewContext();
    *(float *)(camState + 0x3DC) = 0.005f;
    *(float *)(camState + 0x3E0) = 0.2f;
    *(int *)(camState + 0x3D0) = 0;
    *(int *)(camState + 0x3E4) = 0;
}
