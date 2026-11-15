#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void vec_random_direction(char *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern char *func_PAL_L02_0032D5F8(char *, int, char *, char *, int, int, float *, void *, void *, float);
extern void moby_mark_spawned(char *);
extern char D_L02_001A8F20[] __attribute__((sda));

void func_PAL_L11_0044EDC0(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0) {
        vec_random_direction((char *)vec, 0.120000005f, 0.20000002f);
        FastVecAdd(vec, vec, D_L02_001A8F20);
        func_PAL_L02_0032D5F8(self, 0x9D8, *(char **)(state + 0x354) + 0x10, *(char **)(state + 0x354) + 0xF0,
                    0, 0, vec, D_L02_001A8F20, D_L02_001A8F20, 0.004f);
    }
    moby_mark_spawned(*(char **)(state + 0x354));
    *(char **)(state + 0x354) = 0;
}


extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void func_PAL_002A0F68(char *);
extern void set_moby_color(char *, int, int, int);
extern int func_PAL_002B3F18(char *, char *, char *);
extern int moby_spawn_linked(char *, int, float, float);
extern void get_moby_color(char *, int *, int *, int *);
extern u16 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((sda));

/* func_L11_00449330 is in L11_00449330.c: PAL's level 11 has other code at its place,
   so the calls to it from this unit go through its symbol. */

void func_PAL_L11_0044F150(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    int colors[4];
    int green, blue;

    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x366) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x36E) = active;
    moby_set_controller_speed_limits(object, 0.008f, 0.124000005f,
                  0.005026549f, 0.5026549f);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x36E) != 0) {
        moby_set_state(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_PAL_002A7E68(object, 0, 0, 0);
        func_PAL_002A0F68(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        if (*(u8 *)(object + 0x43) != 0)
            func_PAL_002A7E68(object, 0, 0, 8);
        moby_set_state(object, 3, 1);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    security_robot_spawn_held_item(object);
    *(short *)(state + 0x36C) = mode;
    *(int *)(state + 0x200) = 0;
    func_PAL_002B3F18(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x354) != 0) {
        get_moby_color(object, &colors[0], &colors[1], &colors[2]);
        green = colors[1];
        blue = colors[2];
        set_moby_color(*(char **)(state + 0x354), colors[0], green, blue);
    }
}

