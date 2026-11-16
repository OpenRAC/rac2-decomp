#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern float g_yeedil_projectile_radius __attribute__((sda));
extern void *CreateMoby(int);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern float math_random_angle(void);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float a, float b);
/* func_L20_0044A838 is defined in L20_0044A838-g8.c. */

/* func_L20_00449BB0 is defined in L20_00449BB0-g8.c. */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
typedef struct {
    u8 pad00[0x20];
    u8 state;         
    u8 pad21[3];
    char *pClass;     
    u8 pad28[4];
    float scale;      
    u8 pad30[4];
    u16 flags;        
    u8 pad36[0x68 - 0x36];
    char *pVars;      
} Moby449FD0;

char *yeedil_projectile_spawn_pal(char *arg0, char *arg1, char *arg2, float arg3, int arg4,
                        float arg5) {
    char *obj;
    char *state;

    obj = CreateMoby(0x12EE);
    if (obj != 0) {
        moby_init_child_from_parent((u8 *)obj, (u8 *)arg0);
        qcopy(obj + 0x10, arg1);
        *(float *)(obj + 0xF0) = math_random_angle();
        *(float *)(obj + 0xF4) = math_random_angle();
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        ((Moby449FD0 *)obj)->state = 1;
        ((Moby449FD0 *)obj)->flags |= 0x100;
        ((Moby449FD0 *)obj)->scale =
            *(float *)(((Moby449FD0 *)obj)->pClass + 0x24) * g_yeedil_projectile_radius;
        state = ((Moby449FD0 *)obj)->pVars;
        qcopy(state, arg2);
        *(float *)(state + 0x14) = arg3 * 0.019867549f;
        *(int *)(state + 0x18) = arg4;
        *(float *)(state + 0x1C) = arg5;
        *(int *)(state + 0x20) = 0x32;
        *(float *)(state + 0x10) = math_random_float_range(10.0f, 20.0f) * 0.00040000002f;
    }
    return obj;
}

extern float g_turret_small_turn_step __attribute__((sda));
extern float g_turret_turn_step __attribute__((sda));
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(char *a, char *b, int c, float d, float e, float f,
                            float g);
extern float ApproachValue(float *, float, float);

void turret_turn_toward_target_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *p = arg0 + 0xF8;
    float a = *(float *)(state + 0x140) - *(float *)(arg0 + 0x10);
    float b = *(float *)(state + 0x144) - *(float *)(arg0 + 0x14);
    float c = g_turret_small_turn_step * 6.981318e-06f;
    float d = g_turret_turn_step * 0.0003490659f;
    float r;

    r = mat_fast_helper_a(a, b);
    math_approach_target_with_direction_mode(p, state + 0x1A4, 0, r, c, c, d);
    d = d * 4.0f;
    ApproachValue(arg0 + 0xF0, *(float *)(state + 0x1A8), d);
    *(float *)(state + 0x1A8) = 0.0f;
    ApproachValue(arg0 + 0x0F4, *(float *)(state + 0x1AC), d);
    *(float *)(state + 0x1AC) = 0.0f;
}
