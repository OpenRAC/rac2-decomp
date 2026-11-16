#include "include_asm.h"

#include "common.h"
extern int flag_is_third_pending_set(char *);
extern int flag_set_first_pending(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern char *func_PAL_0032F3B8(char *, void *, void *, float);
extern void moby_set_state(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern char *cam_moby_create_pal(char *, int, int, int, void *, void *, void *, int, float, float);
extern void moby_mark_spawned(char *);
extern s32 cam_moby_update_pal(char *);
extern int math_random_int_range(int, int);
extern float g_debris_velocity_range[] __attribute__((sda));
extern float g_debris_velocity_matrix[] SDATA(D_L07_001B0C20);
extern float g_debris_child_param_range[] __attribute__((sda));
extern float D_L07_001B0C30_gp[] SDATA(D_L07_001B0C30);

/* A four-state burst: state 1 passes the rotated, offset position to func_PAL_0032F3B8, state 2
   spawns nine children that run this function in state 3, where each counts down a random
   lifetime. */
void func_PAL_L07_003F27F8(char *arg)
{
    float v[4] __attribute__((aligned(16)));
    int i;
    float f, g;
    char *e;

    switch (*(unsigned char *)(arg + 0x20)) {
    case 0:
        moby_set_state(arg, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(arg)) {
            matrix_mul_vec3(v, g_debris_velocity_matrix, arg + 0xC0);
            FastVecAdd(v, v, arg + 0x10);
            func_PAL_0032F3B8(arg, v, arg + 0xD0, 0.0f);
            moby_set_state(arg, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(arg))
            PlayMobySound(0, 0, arg);
        for (i = 0; i < 9; i++) {
            v[0] = math_random_float_range(g_debris_velocity_range[0], g_debris_velocity_range[4]) * 0.020000001f;
            v[1] = math_random_float_range(g_debris_velocity_range[1], g_debris_velocity_range[5]) * 0.020000001f;
            v[2] = math_random_float_range(g_debris_velocity_range[2], g_debris_velocity_range[6]) * 0.020000001f;
            matrix_mul_vec3(v, v, arg + 0xC0);
            f = math_random_signed_float_range(g_debris_child_param_range[0], g_debris_child_param_range[1]);
            g = math_random_float_range(D_L07_001B0C30_gp[2], g_debris_child_param_range[3]);
            e = cam_moby_create_pal(arg, 2, *(short *)(arg + 0xAA), i, arg + 0x10, arg + 0xF0, v, 255, f, g);
            if (e) {
                *(void (**)(char *))(e + 0x64) = func_PAL_L07_003F27F8;
                *(unsigned short *)(e + 0x34) |= 0x2000;
                moby_set_state(e, 3, -1);
            }
        }
        moby_mark_spawned(arg);
        break;
    case 3:
        if (flag_set_first_pending(arg))
            *(unsigned short *)(arg + 0x96) = ((s32)(math_random_int_range(0, 60)) * 5 + 2) / 6;
        cam_moby_update_pal(arg);
        if (*(unsigned short *)(arg + 0x96) == 0 || --*(unsigned short *)(arg + 0x96) == 0) {
            if (*(unsigned char *)(arg + 0x23) >= 4)
                *(unsigned char *)(arg + 0x23) -= 4;
            else
                moby_mark_spawned(arg);
        }
        break;
    }
}
