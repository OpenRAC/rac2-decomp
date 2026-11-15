#include "common.h"

extern char *g_moby_l02_pool;
extern float vec_distance_xy(const void *, const void *);
extern void euler_rotation_basis(void *, void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(float *, const float *, float);
extern void FastVecAdd(void *, void *, void *);

/* Moves a gate along its path points toward the next point. Returns 0 while moving, 1 or 2 when it reaches the last point, and 3 when its controller is already finished. */
int gate_move_along_path(char *object) {
    float delta[4];
    char *state = *(char **)(object + 0x68);
    char *controller = *(char **)(state + 8);
    char *other = g_moby_l02_pool + (*(int *)state << 8);
    if (*(int *)(controller + 4) == 0) {
        if (*(int *)(state + 0x14) == **(int **)(state + 0x18) - 1) {
            if (*(int *)(controller + 0x14)) {
                *(int *)(controller + 4) = 1;
                *(int *)(*(char **)(state + 8) + 8) = 20;
                *(unsigned short *)(object + 0x34) |= 0x41;
                *(unsigned short *)(other + 0x34) |= 0x41;
                {
                    char *linked = *(char **)(*(char **)(state + 8) + 0x1C);
                    qcopy(linked + 0xF0, other + 0xF0);
                    euler_rotation_basis(linked + 0xC0, linked + 0xF0);
                }
                {
                    char *linked2 = *(char **)(*(char **)(state + 8) + 0x1C);
                    *(unsigned short *)(linked2 + 0x34) &= 0xFFBE;
                }
                snd_play_from_class_bank(3, 0, object, 0x896);
                return 2;
            }
            snd_play_from_class_bank(2, 0, object, 0x896);
            return 1;
        }
        if (*(float *)(state + 0xC) < 480.0f)
            *(float *)(state + 0x10) += (0.03333f / *(float *)(state + 0x10)) * 0.00016666666488163173f;
        else
            *(float *)(state + 0x10) += (0.03333f / *(float *)(state + 0x10)) * 0.00008333333244081587f;

        FastVecSub(delta, (float *)(*(char **)(state + 0x18) + ((*(int *)(state + 0x14) << 4) + 0x20)), (float *)(object + 0x10));
        vec_scale_to_length(delta, delta, *(float *)(state + 0x10));
        FastVecAdd(object + 0x10, object + 0x10, delta);
        if (vec_distance_xy(object + 0x10, *(char **)(state + 0x18) + ((*(int *)(state + 0x14) << 4) + 0x20)) <= *(float *)(state + 0x10) * 0.88f)
            ++*(int *)(state + 0x14);
    } else return 3;
    return 0;
}
