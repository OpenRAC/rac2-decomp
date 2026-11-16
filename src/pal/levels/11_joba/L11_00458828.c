#include "include_asm.h"

#include "common.h"
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void func_PAL_002A0F68(char *);
extern void set_moby_color(char *, int, int, int);
extern int part_spawn_damage_debris_pal(char *, char *, char *);
extern int moby_spawn_linked(char *, int, float, float);
extern u16 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((sda));

void flamethrower_robot_init_pal(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);

    *(u8 *)(state + 0x2E) = 1;
    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x2D2) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x2D8) = active;
    moby_set_controller_speed_limits(object, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    if (*(u8 *)(object + 0x43) != 2)
        func_PAL_002A7E68(object, 2, 0, 0);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x2D8) != 0) {
        moby_set_state(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_PAL_002A7E68(object, 2, 0, 0);
        func_PAL_002A0F68(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(short *)(state + 0x2D4) = mode;
    *(u8 *)(state + 0x6A) = 0;
    *(int *)(state + 0x200) = 0;
    part_spawn_damage_debris_pal(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}


extern void vec_random_direction(void *a0, float f12, float f13);
extern void func_PAL_002B15D8(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern char *SpawnExplosion_pal(char *, int, int, int, int, int, int, int,
                         float, float, int, int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_002B15D8(char *, int, void *, float, float, float, float, int);

void flamethrower_robot_deactivate_pal(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];

    *(short *)(state + 0x2D2) = 0;
    *(int *)(state + 0x2C4) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        SpawnExplosion_pal(object + 0x10, 0, 5, 5, 25, 20, 10, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        snd_play_from_class_bank(0, 0, object, 0xDF7);
        vec_random_direction(direction, 0.10000001f, 0.14000002f);
        FastVecAdd(direction, direction, state + 0xD0);
        func_PAL_002B15D8(object, 0xFF0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    func_PAL_002A7E68(object, 0, 0, 3);
    func_PAL_002A0F68(object);
    moby_set_state(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}

