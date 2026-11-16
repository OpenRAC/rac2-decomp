#include "include_asm.h"

#include "common.h"
extern int flag_is_third_pending_set(char *);
extern int flag_set_first_pending(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_blast_effect_moby_pal(char *, void *, void *, float);
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
void burst_debris_update_pal(char *moby)
{
    float vec[4] __attribute__((aligned(16)));
    int i;
    float child_param_a, child_param_b;
    char *child;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(moby)) {
            matrix_mul_vec3(vec, g_debris_velocity_matrix, moby + 0xC0);
            FastVecAdd(vec, vec, moby + 0x10);
            part_spawn_blast_effect_moby_pal(moby, vec, moby + 0xD0, 0.0f);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby))
            PlayMobySound(0, 0, moby);
        for (i = 0; i < 9; i++) {
            vec[0] = math_random_float_range(g_debris_velocity_range[0], g_debris_velocity_range[4]) * 0.020000001f;
            vec[1] = math_random_float_range(g_debris_velocity_range[1], g_debris_velocity_range[5]) * 0.020000001f;
            vec[2] = math_random_float_range(g_debris_velocity_range[2], g_debris_velocity_range[6]) * 0.020000001f;
            matrix_mul_vec3(vec, vec, moby + 0xC0);
            child_param_a = math_random_signed_float_range(g_debris_child_param_range[0], g_debris_child_param_range[1]);
            child_param_b = math_random_float_range(D_L07_001B0C30_gp[2], g_debris_child_param_range[3]);
            child = cam_moby_create_pal(moby, 2, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0, vec, 255, child_param_a, child_param_b);
            if (child) {
                *(void (**)(char *))(child + 0x64) = burst_debris_update_pal;
                *(unsigned short *)(child + 0x34) |= 0x2000;
                moby_set_state(child, 3, -1);
            }
        }
        moby_mark_spawned(moby);
        break;
    case 3:
        if (flag_set_first_pending(moby))
            *(unsigned short *)(moby + 0x96) = ((s32)(math_random_int_range(0, 60)) * 5 + 2) / 6;
        cam_moby_update_pal(moby);
        if (*(unsigned short *)(moby + 0x96) == 0 || --*(unsigned short *)(moby + 0x96) == 0) {
            if (*(unsigned char *)(moby + 0x23) >= 4)
                *(unsigned char *)(moby + 0x23) -= 4;
            else
                moby_mark_spawned(moby);
        }
        break;
    }
}
