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
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void moby_mark_spawned(void *);

/* Updates a falling Siberius debris piece (moby class 4776): it drifts down, hurts what it touches, then bursts into an effect and disappears. */
void siberius_debris_update(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    TI128 effect;
    float length, ratio;
    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x100;
        euler_rotation_basis(moby + 0xc0, moby + 0xf0);
        if (*(int *)(vars + 0xc) == 1) FastVecScale(moby + 0xe0, moby + 0xe0, 2.0f);
        else if (*(int *)(vars + 0xc) == -1) FastVecScale(moby + 0xe0, moby + 0xe0, 0.5f);
        if (*(int *)(vars + 0x24) == 0) {
            *(int *)(vars + 0x10) = 0;
            *(int *)(vars + 0x14) = 0;
            *(float *)(vars + 0x18) = -(math_random_float_range(3.0f, 6.0f) * 0.016666668f);
        } else FastVecScale(vars + 0x10, vars + 0x10, 0.016666668f);
        *(float *)(vars + 4) = math_random_float_range(13.0f, 20.0f) * 0.00027777778f;
        length = FastVecLength(moby + 0xe0);
        ratio = *(float *)(moby + 0x2c) / *(float *)(*(char **)(moby + 0x24) + 0x24);
        ratio *= length * -10.0f;
        *(float *)(vars + 0x20) = ratio;
        if (*(float *)(vars + 8) == 0.0f)
            *(float *)(vars + 8) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !*(int *)vars)
            moby_set_state(moby, 2, -1);
        moby[0xa8] = 255;
        break;
    case 2:
        FastVecAdd(moby + 0x10, moby + 0x10, vars + 0x10);
        *(float *)(vars + 0x18) -= *(float *)(vars + 4);
        if (*(int *)(vars + 0x24)) {
            moby_compute_local_point(moby, &effect, 0.0f, 0.0f, *(float *)(vars + 0x20));
            coll_sweep_from_object(moby, &effect, 0x4010000, 0, 1, 0, 2.0f * (*(float *)(moby + 0x2c) / *(float *)(*(char **)(moby + 0x24) + 0x24)), 8.0f, 1.0f);
        }
        if (*(float *)(moby + 0x18) + *(float *)(vars + 0x20) < *(float *)(vars + 8))
            moby_set_state(moby, 4, -1);
        break;
    case 4:
        PlayMobySound(0, 0, moby);
        if (moby[0x31]) {
            effect = 0;
            ((float *)&effect)[2] = 0.050000004f;
            part_spawn_masked_debris(moby, 3, &effect, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
        moby_mark_spawned(moby);
        break;
    }
}
