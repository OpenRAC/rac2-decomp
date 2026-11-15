#include "common.h"

/* Prefix view of the effect-position field; not a complete global layout. */
typedef struct { char pad[0xB0]; float effect_position[4]; } EffectPositionView;
extern EffectPositionView D_00189E20;
/* Keep the destination address as the assembler's absolute-address macro. */
extern char D_L02_001B3210[] __attribute__((sda));
extern char *D_L02_001AD410 __attribute__((sda));
extern void func_L02_003F5390(char *);
extern void func_L02_003F54D8(char *);
extern void func_L02_003F56C0(char *);
extern void func_L02_003F5710(char *);
extern void func_002833B8(char *, float);
extern void func_002A7750(u8 *, s32, s32);

void func_L02_003F52B0(char *arg0) {
    switch (*(u8 *)(arg0 + 0x20)) {
    case 0: {
        EffectPositionView *g = &D_00189E20;

        float *src;
        char *dst;
        g->effect_position[1] = 200.0f;
        g->effect_position[0] = 500.0f;
        g->effect_position[2] = 500.0f;
        g->effect_position[3] = 1.0f;
        src = g->effect_position;
        dst = D_L02_001B3210;
        qcopy(dst, src);
        *(u8 *)(arg0 + 0x30) = 0xFF;
        func_L02_003F5390(arg0);
        set_scale_matrix(D_L02_001AD410 + 0x40, 1.0f);
        func_002A7750(arg0, 1, -1);
        break;
    }
    case 1:
        func_L02_003F54D8(arg0);
        func_L02_003F56C0(arg0);
        func_L02_003F5710(arg0);
        break;
    }
}
