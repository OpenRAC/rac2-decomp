#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44 - 0x38];
    short count;
    char gap46[0x18C - 0x46];
    char *parts[0];
} Hero;
extern Hero g_hero_part_state;
typedef struct { char pad[0x34]; unsigned short flags; char gap[0xAA - 0x36]; short id; } Object;
extern int g_current_map_index[] __attribute__((sda));
extern float g_part_offset_positions[][4] SDATA(D_L26_001A9450);
extern float g_part_acceleration_params[] __attribute__((sda));
extern float D_L26_001A9420_gp SDATA(D_L26_001A9420);
extern unsigned int g_part_color_range[] __attribute__((sda));
extern unsigned int D_L26_001A9428_gp SDATA(D_L26_001A9428);
extern int g_part_kind_range[] __attribute__((sda));
extern int D_L26_001A9430_gp SDATA(D_L26_001A9430);
extern int g_part_duration_range[] __attribute__((sda));
extern int g_part_size_range[] __attribute__((sda));
extern void anim_start_startup_animations(void);
extern void func_US2_002E72D8(void *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern char *part_spawn_trail(void *, void *, void *, unsigned int, unsigned int, int, int, int, int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);

/* func_US2_L26_002FD970, the USA v2.00 copy of func_L26_002FCCC0: the same C, where the id 4000 call
   to func_L00_00326048 also requires D_001A79F0 != 51, and func_002E64A0 becomes func_US2_002E72D8. */
void func_US2_L26_002FD970(void) {
    Vec transform[4];
    Vec position;
    Vec velocity;
    Vec acceleration;
    Hero *hero;
    char **slot;
    char *object;
    char *effect;
    unsigned int color;
    int kind;
    int duration;
    int size;
    int i;
    int j;
    int flags = -1;
    anim_start_startup_animations();
    for (i = 0; i < g_hero_part_state.count; i++) {
        hero = &g_hero_part_state;
        slot = &hero->parts[i];
        object = *slot;
        if (object && ((Object *)object)->id == 0xE29) {
            ((Object *)object)->flags |= 0x800;
        }
        if (((Object *)object)->id == 0xD54) func_US2_002E72D8(object);
        if (object && *(short *)(object + 0xAA) == 4000 && g_current_map_index[0] != 51 && *(char **)(object + 0x68))
            math_store_angle_update_result(object, (float *)(*(char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.061086535f);
    }
    if (g_current_map_index[0] == 26 && g_hero_part_state.mode == 0 && g_hero_part_state.timer < 260) {
        object = g_hero_part_state.parts[3];
        moby_transform_joint_point(object, 0, (char *)transform);
        object += 0x10;
        qcopy((transform + 3), object);
        for (j = 0; j < 8; j++) {
            transform_vector(&position, g_part_offset_positions[j & 1], transform);
            vec_scale_to_length(&velocity, transform, 0.06666667f);
            velocity.f[3] = D_L26_001A9420_gp;
            qzero_nc(&acceleration);
            acceleration.f[3] = g_part_acceleration_params[1];
            color = FastTweenColor(D_L26_001A9428_gp, g_part_color_range[1], math_random_float_range(0.0f, 1.0f));
            {
                unsigned int rgb = color & 0xFFFFFF;
                kind = math_random_int_range(D_L26_001A9430_gp, g_part_kind_range[1]);
                duration = math_random_int_range(g_part_duration_range[0], g_part_duration_range[1]);
                size = math_random_int_range(g_part_size_range[0], g_part_size_range[1]);
                effect = part_spawn_trail(&position, &velocity, &acceleration, color, rgb,
                                       kind, duration, size, flags);
                if (effect) effect[9] = FloatToInt(2.0f) - 16;
            }
        }
    }
}
