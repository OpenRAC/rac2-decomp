#include "names.h"
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

extern float func_002EB478(float a, float b);
extern void func_002AEE70(char *a0, void *a1, void *a2, f32 f12, f32 f13, f32 f14);
extern void func_002AEF28(char *a0, void *a1, void *a2, f32 f12, f32 f13, f32 f14);

/* Remembers the current position and eases the object turn angles toward their new targets. */
void func_L09_003E99E0(char *object) {
    char *frame = *(char **)(object + 0x68);
    TI128 *src = (TI128 *)(object + 0x10);
    TI128 *dst = (TI128 *)(frame + 0x330);

    *dst = *src;
    UpdateWrappedAngleOffset(object, frame + 0x360, frame + 0x364, 0.2f, 0.0087266480550169945f,
                  *(f32 *)(frame + 0x338));
    ScaleOwnerWordsByAngles(object, frame + 0x358, frame + 0x35C, 0.087266474962234497f,
                  0.0072722062468528748f, 0.0090175354853272438f);
    *(f32 *)(object + 0xF0) = func_002EB478(*(f32 *)(frame + 0x340), *(f32 *)(object + 0xF0));
    *(f32 *)(object + 0xF4) = func_002EB478(*(f32 *)(frame + 0x344), *(f32 *)(object + 0xF4));
}
