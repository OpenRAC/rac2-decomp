#include "include_asm.h"

typedef float f32;
extern f32 D_L16_001B3AAC __attribute__((sda));
extern f32 func_002E73F8(f32);
extern f32 D_L16_001B1C60 __attribute__((sda));
extern f32 D_001B1C64 __attribute__((nosda));
extern f32 D_001B1C68 __attribute__((nosda));
extern f32 D_001B1C6C __attribute__((nosda));
extern f32 D_L16_001B1C70 __attribute__((sda));
extern f32 D_001B1C74 __attribute__((nosda));
extern f32 func_00313F38(f32, f32);
extern f32 D_L16_001B1E90 __attribute__((sda));
extern f32 D_L16_001B1E94 __attribute__((sda));
extern void func_002AEE70(char *, char *, char *, f32, f32, f32);
extern f32 D_L16_001B1C28 __attribute__((sda));
extern f32 D_L16_001B1C2C __attribute__((sda));
extern f32 D_L16_001B1C30 __attribute__((sda));
extern f32 D_L16_001B1C34 __attribute__((sda));

/* submits the sub-object at 0x68 with the level's angle scale */
void func_PAL_L16_00421D18(char *arg0) {
    char *p = arg0;
    char *st = *(char **)(p + 0x68);

    func_002AEE70(p, st + 4, st, D_L16_001B1E90, D_L16_001B1E94 * 0.0003490659f, -1.0f);
}
