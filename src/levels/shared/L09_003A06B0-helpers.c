#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int id);

extern float mat_fast_helper_a(float x, float y);

extern float vec_length_xy(char *a);

extern void func_002A0F48(char *a);

extern char *part_spawn_sized(char *object, int a1, u32 a2, int a3, float f12, float f13);


/* Creates a small moving effect object at a position, aims it along a direction and returns it. */
char *moby_spawn_aimed_effect(char *object, char *direction, char *position, float speed)
{
    char *spawned = CreateMoby(0x3A6 /* moby class 934 */);
    char *vars;
    float length;

    if (spawned != 0) {
        *(u8 *)(spawned + 0x30) = 0xFF;
        *(u16 *)(spawned + 0x32) = 0xFF;
        *(u8 *)(spawned + 0x31) = 1;
        *(u8 *)(spawned + 0x20) = 0;
        *(u64 *)(spawned + 0x38) = *(u64 *)(object + 0x38);
        qcopy(spawned + 0x10, position);
        vars = *(char **)(spawned + 0x68);
        qcopy(vars, direction);
        *(char **)(vars + 0x3C) = object;
        *(u32 *)(vars + 0x38) = 0xF0;
        *(float *)(vars + 0x40) = speed;
        *(float *)(spawned + 0xF8) = mat_fast_helper_a(*(float *)direction, *(float *)(direction + 4));
        length = vec_length_xy(direction);
        *(float *)(spawned + 0xF4) =
            -mat_fast_helper_a(length, *(float *)(direction + 8));
        *(char **)(vars + 0x48) =
            part_spawn_sized(spawned, -1, 0xF0208080, 0x60, 0.1f, 0.01f);
        func_002A0F48(spawned);
        *(u8 *)(spawned + 0x31) = 0;
        *(u16 *)(spawned + 0x34) |= 1;
    }
    return spawned;
}
