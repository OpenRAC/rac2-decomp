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
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(void *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern char *part_spawn_trail(void *, void *, void *, unsigned int, unsigned int, int, int, int, int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);

/* func_PAL_L26_002FE890, the PAL copy of func_L26_002FCCC0: the same C, where the id 4000 call also
   requires D_001A79F0 != 51, its angle and the particle velocity scale by 6/5, the timer limit is 217
   and kind, duration and size take the 50 Hz scale. func_002E64A0 becomes func_PAL_002E7270. The
   bounds after the first three are read at offsets from D_L26_001A9430 and -1 is passed directly:
   the offset form keeps those absolute macro loads out of call delay slots, and a local for -1 moves
   the stack argument's store after the register moves. */
void func_PAL_L26_002FE890(void) {
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
    anim_start_startup_animations();
    for (i = 0; i < g_hero_part_state.count; i++) {
        hero = &g_hero_part_state;
        slot = &hero->parts[i];
        object = *slot;
        if (object && ((Object *)object)->id == 0xE29) {
            ((Object *)object)->flags |= 0x800;
        }
        if (((Object *)object)->id == 0xD54) func_PAL_002E7270(object);
        if (object && *(short *)(object + 0xAA) == 4000 && g_current_map_index[0] != 51 && *(char **)(object + 0x68))
            math_store_angle_update_result(object, (float *)(*(char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.07330384f);
    }
    if (g_current_map_index[0] == 26 && g_hero_part_state.mode == 0 && g_hero_part_state.timer < 217) {
        object = g_hero_part_state.parts[3];
        moby_transform_joint_point(object, 0, (char *)transform);
        object += 0x10;
        qcopy((transform + 3), object);
        for (j = 0; j < 8; j++) {
            transform_vector(&position, g_part_offset_positions[j & 1], transform);
            vec_scale_to_length(&velocity, transform, 0.080000006f);
            velocity.f[3] = D_L26_001A9420_gp;
            qzero_nc(&acceleration);
            acceleration.f[3] = g_part_acceleration_params[1];
            color = FastTweenColor(D_L26_001A9428_gp, g_part_color_range[1], math_random_float_range(0.0f, 1.0f));
            {
                unsigned int rgb = color & 0xFFFFFF;
                kind = (math_random_int_range(D_L26_001A9430_gp, g_part_kind_range[1]) * 5 + 2) / 6;
                duration = (math_random_int_range(g_part_kind_range[2], g_part_kind_range[3]) * 5 + 2) / 6;
                size = (math_random_int_range(g_part_kind_range[4], g_part_kind_range[5]) * 5 + 2) / 6;
                effect = part_spawn_trail(&position, &velocity, &acceleration, color, rgb,
                                       kind, duration, size, -1);
                if (effect) effect[9] = FloatToInt(2.0f) - 16;
            }
        }
    }
}
