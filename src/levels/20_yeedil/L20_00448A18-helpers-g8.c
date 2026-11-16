#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int);

extern void moby_init_child_from_parent(void *, void *);

extern float math_random_float_range(float, float);

extern void vec_random_direction(float *, float, float);

extern void func_002A0F48(void *);

extern int math_random_int_range(int, int);

extern float g_debris_l20_scale_max __attribute__((nosda));
extern float g_debris_l20_angle_max __attribute__((nosda));
extern float g_debris_speed_max __attribute__((nosda));
extern int g_debris_l20_life_max __attribute__((nosda));

extern float g_debris_l20_scale_min __attribute__((sda));
extern float g_debris_l20_angle_min __attribute__((sda));
extern int g_debris_l20_life_min __attribute__((sda));
extern float g_debris_speed_min __attribute__((sda));

/* Creates a small piece of debris (moby class 4698) at the given place with a random size and spin. Returns the new object. */
char *debris_l20_spawn_piece(char *owner, char *position, char *rotation, char *velocity) {
    char *obj = (char *)CreateMoby(0x125A /* moby class 4698 */);
    char *state;
    float f;

    if (obj != 0) {
        state = *(char **)(obj + 0x68);
        moby_init_child_from_parent(obj, owner);
        f = math_random_float_range(g_debris_l20_scale_min, g_debris_l20_scale_max);
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f;
        qcopy(obj + 0x10, position);
        qcopy(obj + 0xF0, rotation);
        qcopy(state, velocity);
        func_002A0F48(obj);
        vec_random_direction((float *)(state + 0x10), g_debris_l20_angle_min * 0.000290888245f,
                      g_debris_l20_angle_max * 0.000290888245f);
        f = math_random_float_range(g_debris_speed_min, g_debris_speed_max);
        *(float *)(state + 0x20) = f * 0.00027777778f;
        *(int *)(state + 0x24) = math_random_int_range(g_debris_l20_life_min, g_debris_l20_life_max);
    }
    return obj;
}
