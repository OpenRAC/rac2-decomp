#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad q; } QuadBox;

typedef struct L01_003C2680_OWNED {
    char pad0[0x68];
    float f68;
    char pad1[0x120 - 0x6C];
    float f120;
    float f124;
    float f128;
    char pad2[0x130 - 0x12C];
    Quad f130;
    Quad f140;
} L01_003C2680_OWNED;

typedef struct L01_003C2680_OBJ {
    char pad0[0x18];
    float f18;
    char pad1[0x20 - 0x1C];
    unsigned char f20;
    char pad2[0x31 - 0x21];
    unsigned char f31;
    char pad3[0x68 - 0x32];
    L01_003C2680_OWNED *f68;
    char pad4[0xAA - 0x6C];
    short fAA;
    char pad5[0xB2 - 0xAC];
    short fB2;
} L01_003C2680_OBJ;

extern void func_002A6CF0(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float level_get_water_height();
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void moby_init_controller_params(void *, void *, int, int, void *, int, int, int, void *, void *, int);
extern void moby_update_sway(void *, void *, int);
extern char D_L01_001B94C0[];
extern float D_L01_001AFF6C __attribute__((sda));
extern long long D_L01_001AFF60 __attribute__((sda));
extern long long D_L01_001AFF50 __attribute__((sda));
extern long long D_L01_001AFF40 __attribute__((sda));
extern char D_L01_002A4C50[];

/* Updates an object that sits on the water: it waits until water is present, then bobs along and reacts when the camera gets close. */
void water_surface_update(L01_003C2680_OBJ *moby)
{
    char *mobyBytes = (char *)moby;
    L01_003C2680_OWNED *vars = moby->f68;
    Quad frame[2];

    if (vars == 0) {
        func_002A6CF0(D_L01_002A4C50, moby->fAA, moby->fB2);
        return;
    }
    qcopy(&frame[0], mobyBytes + 0x10);
    qcopy(&frame[1], mobyBytes + 0xF0);
    switch (moby->f20) {
    case 0:
        if (level_get_water_height(mobyBytes + 0x10) > 0.0f) {
            vars->f120 = math_random_angle();
            vars->f124 = math_random_angle();
            vars->f128 = 0.02f;
            qcopy(&vars->f130, mobyBytes + 0xF0);
            qzero(&vars->f140);
            moby_set_state(moby, 1, -1);
        }
        moby->f18 = moby->f18 + D_L01_001AFF6C;
        moby_init_controller_params(moby, (char *)vars + 0x60, 0, 0, &D_L01_001AFF40, 0, 0, 0, &D_L01_001AFF60, &D_L01_001AFF50, 0);
        return;
    case 1:
        if (moby->f31 != 0 && vec_distance_xy(mobyBytes + 0x10, D_L01_001B94C0) < 32.0f) {
            vars->f68 = level_get_water_height() + D_L01_001AFF6C;
            moby_update_sway(moby, (char *)vars + 0x60, 0);
        }
        return;
    }
}
