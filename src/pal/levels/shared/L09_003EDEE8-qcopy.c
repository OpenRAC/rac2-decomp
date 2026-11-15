#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
extern float FastAddRotations(float a, float b);
extern void math_update_wrapped_angle_offset(char *a0, void *a1, void *a2, f32 f12, f32 f13, f32 f14);
extern void moby_scale_owner_words_by_angles(char *a0, void *a1, void *a2, f32 f12, f32 f13, f32 f14);

void func_PAL_L09_003EDEE8(char *object) {
    char *frame = *(char **)(object + 0x68);
    TI128 *src = (TI128 *)(object + 0x10);
    TI128 *dst = (TI128 *)(frame + 0x330);

    *dst = *src;
    math_update_wrapped_angle_offset(object, frame + 0x360, frame + 0x364, 0.2f, 0.010471977f,
                  *(f32 *)(frame + 0x338));
    moby_scale_owner_words_by_angles(object, frame + 0x358, frame + 0x35C, 0.087266474962234497f,
                  0.008726647f, 0.010821043f);
    *(f32 *)(object + 0xF0) = FastAddRotations(*(f32 *)(frame + 0x340), *(f32 *)(object + 0xF0));
    *(f32 *)(object + 0xF4) = FastAddRotations(*(f32 *)(frame + 0x344), *(f32 *)(object + 0xF4));
}
