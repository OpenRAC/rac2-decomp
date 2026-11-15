#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void euler_rotation_basis(u8 *, u8 *);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float math_random_float_range(float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void moby_mark_spawned(void *);

void func_PAL_L07_00415B88(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    TI128 effect;
    float length, ratio;
    switch (object[0x20]) {
    case 0:
        *(unsigned short *)(object + 0x34) |= 0x100;
        euler_rotation_basis(object + 0xc0, object + 0xf0);
        if (*(int *)(state + 0xc) == 1) FastVecScale(object + 0xe0, object + 0xe0, 2.0f);
        else if (*(int *)(state + 0xc) == -1) FastVecScale(object + 0xe0, object + 0xe0, 0.5f);
        if (*(int *)(state + 0x24) == 0) {
            *(int *)(state + 0x10) = 0;
            *(int *)(state + 0x14) = 0;
            *(float *)(state + 0x18) = -(math_random_float_range(3.0f, 6.0f) * 0.020000001f);
        } else FastVecScale(state + 0x10, state + 0x10, 0.020000001f);
        *(float *)(state + 4) = math_random_float_range(13.0f, 20.0f) * 0.00040000002f;
        length = FastVecLength(object + 0xe0);
        ratio = *(float *)(object + 0x2c) / *(float *)(*(char **)(object + 0x24) + 0x24);
        ratio *= length * -10.0f;
        *(float *)(state + 0x20) = ratio;
        if (*(float *)(state + 8) == 0.0f)
            *(float *)(state + 8) = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) && !*(int *)state)
            moby_set_state(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        FastVecAdd(object + 0x10, object + 0x10, state + 0x10);
        *(float *)(state + 0x18) -= *(float *)(state + 4);
        if (*(int *)(state + 0x24)) {
            moby_compute_local_point(object, &effect, 0.0f, 0.0f, *(float *)(state + 0x20));
            coll_sweep_from_object(object, &effect, 0x4010000, 0, 1, 0, 2.0f * (*(float *)(object + 0x2c) / *(float *)(*(char **)(object + 0x24) + 0x24)), 8.0f, 1.0f);
        }
        if (*(float *)(object + 0x18) + *(float *)(state + 0x20) < *(float *)(state + 8))
            moby_set_state(object, 4, -1);
        break;
    case 4:
        PlayMobySound(0, 0, object);
        if (object[0x31]) {
            effect = 0;
            ((float *)&effect)[2] = 0.060000002f;
            func_PAL_002B15D8(object, 3, &effect, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
        moby_mark_spawned(object);
        break;
    }
}
