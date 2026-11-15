#include "common.h"

/* func_PAL_L05_003168F8, the PAL copy of func_L05_00314E28: the same C with the 50 Hz timers and
   speeds rescaled, plus a D_001A79F0 != 0x33 guard on the 0xFA0 effect. */

extern void vec_fast_to_int_helper(char *, char *);
extern void quaternion_to_rotation_basis(char *, char *);
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(char *);
extern void math_store_angle_update_result(char *, char *, int, int, float);
extern void moby_compute_local_point(char *, char *, float, float, float);
extern char *func_PAL_L05_0042A240(char *, int, int, int, int, int, int, int, int, int, int, float);
extern int math_random_int_below(int kind);
extern float math_random_signed_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *func_PAL_L05_0041EA08(char *, char *, char *, int, int, int, int, int, float);

typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap[0xC];
    short count;
    char gap2[0x146];
    char *objects[3];
} Scene05;
extern Scene05 D_L05_001BD3C0;
extern char D_L05_00294A90[];
extern int g_current_map_index __attribute__((sda));

void func_PAL_L05_003168F8(void)
{
    float pos[4] __attribute__((aligned(16)));
    union {
        float matrix[12];
        struct { float dest[4], delta[4]; } vectors;
    } scratch __attribute__((aligned(16)));
    int i;
    char *obj;
    anim_start_startup_animations();
    for (i = 0; i < D_L05_001BD3C0.count; i++) {
        char *current = D_L05_001BD3C0.objects[i];
        if (current && *(short *)(current + 0xAA) == 0xE29)
            *(unsigned short *)(current + 0x34) |= 0x800;
        if (*(short *)(current + 0xAA) == 0xD54) func_PAL_002E7270(current);
        if (current) {
            int effect_class = 0xFA0;
            if (*(short *)(current + 0xAA) == effect_class && g_current_map_index != 0x33) {
                char *state = *(char **)(current + 0x68);
                if (state) math_store_angle_update_result(current, state + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
            }
        }
    }
    if (g_current_map_index != 5 || D_L05_001BD3C0.mode) return;
    obj = D_L05_001BD3C0.objects[2];
    if (D_L05_001BD3C0.timer == 0x52) {
        vec_fast_to_int_helper(*(char **)(obj + 0x58) + 0x10, (char *)scratch.matrix);
        quaternion_to_rotation_basis((char *)scratch.matrix, obj + 0xC0);
        moby_compute_local_point(obj, (char *)pos, 4.0f, 3.0f, 5.0f);
        func_PAL_L05_0042A240((char *)pos, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
        moby_compute_local_point(obj, (char *)pos, 9.0f, 4.0f, 4.0f);
        func_PAL_L05_0042A240((char *)pos, 35, 50, 30, 30, 30, 50, 1, 1, 1, 1, 1.0f);
    }
    if ((unsigned int)(D_L05_001BD3C0.timer - 0x22) < 0x5f && !math_random_int_below(4)) {
        float sign = 1.0f;
        float *entry;
        if (math_random_int_below(2)) sign = -1.0f;
        entry = (float *)(D_L05_00294A90 + math_random_int_below(3) * 32);
        moby_compute_local_point(obj, (char *)pos, entry[0], entry[1], entry[2]);
        moby_compute_local_point(obj, (char *)scratch.vectors.dest, entry[4], entry[5], entry[6]);
        scratch.vectors.dest[0] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[1] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[2] += math_random_signed_float_range(0.5f, 1.5f);
        FastVecSub((char *)scratch.vectors.delta, (char *)scratch.vectors.dest, (char *)pos);
        vec_scale_to_length((char *)scratch.vectors.delta, (char *)scratch.vectors.delta, 1.4000001f);
        func_PAL_L05_0041EA08(obj, (char *)pos, (char *)scratch.vectors.delta, 0x46BE20, 0x327814, 1, 0, 1, sign);
    }
}
