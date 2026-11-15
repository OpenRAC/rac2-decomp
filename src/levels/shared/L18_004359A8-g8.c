#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[8];
    char *kinds[2];
} Vars4359A8;

typedef struct {
    u8 pad00[0x68];
    Vars4359A8 *vars;
} Moby4359A8;

extern f32 D_L18_001B1640 __attribute__((sda));
extern f32 D_L18_001B1644 __attribute__((sda));
extern f32 D_L18_001B1648 __attribute__((sda));
extern f32 D_L18_001B164C __attribute__((sda));
extern f32 D_L18_001B1650 __attribute__((sda));
extern f32 D_L18_001B1654 __attribute__((sda));
extern s32 D_L18_001B165C __attribute__((sda));
extern s32 D_L18_001B1660 __attribute__((sda));
extern s32 D_L18_001B1664 __attribute__((sda));
extern f32 D_L18_001B1678[2] __attribute__((sda));
extern f32 D_L18_001B1680[2] __attribute__((sda));
extern f32 D_L18_001B1688[2] __attribute__((sda));
extern char *D_L18_001B1690[2] __attribute__((sda));
extern char D_L18_001B3720[] __attribute__((sda));

extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern char *part_create_orbiting_effect(char *p0, float f0, float f1, float f2, float f3, float f4, s16 p1, char *p2, s32 p3, char *p4);

/* Spawns a burst of small effect objects with random positions, sizes and kinds, picking one of two looks for each. */
void part_l18_spawn_random_burst(Moby4359A8 *self) {
    Vars4359A8 *vars = self->vars;
    s32 i;
    s32 variant;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    for (i = 0; i < D_L18_001B165C; i++) {
        variant = math_random_int_below(2);
        x = D_L18_001B1648 + math_random_float_range(-D_L18_001B164C, D_L18_001B164C);
        y = D_L18_001B1650 + math_random_float_range(-D_L18_001B1654, D_L18_001B1654);
        z = -((D_L18_001B1640 + math_random_float_range(-D_L18_001B1644, D_L18_001B1644)) * 0.00029088825f);
        w = D_L18_001B1678[variant] + math_random_float_range(-D_L18_001B1688[variant], D_L18_001B1688[variant]);
        part_create_orbiting_effect(D_L18_001B3720, x, y, z, w, D_L18_001B1680[variant], D_L18_001B1660 + math_random_int_below(D_L18_001B1664 - D_L18_001B1660), vars->kinds[variant], variant, D_L18_001B1690[variant]);
    }
}
