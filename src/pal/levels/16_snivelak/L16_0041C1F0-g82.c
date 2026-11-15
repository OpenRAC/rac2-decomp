#include "include_asm.h"

#include "common.h"
extern char D_L16_001B1B70[8] __attribute__((sda));
extern char D_L16_001B1B68[8] __attribute__((sda));
extern char D_L16_001B1B60[8] __attribute__((sda));
extern s32 D_L16_001B1B90 __attribute__((sda));
typedef struct { f32 x, y, z, w; } BurstPoint;
extern BurstPoint D_L16_001B1BB0[];
extern s32 math_fast_float_d(char *);
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, u32, s32);
extern void func_PAL_L00_0032C328(char *, char *, char *, char *, s32, s32, s32, s32, s32, s32, s32);
extern void vec_local_offset_to_world(char *, char *, f32, f32, f32);
extern char *func_PAL_L00_003FB330(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void moby_mark_spawned(char *);

/* Alternates its hit color, then emits the three configured destruction bursts. */
void func_PAL_L16_0041C9F8(char *self) {
    char pos[16];
    char *st = *(char **)(self + 0x68);
    s32 i;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(u16 *)(self + 0x34) |= 16;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(st + 4)) {
            if (*(u32 *)(self + 0x78) & 1)
                *(u32 *)(self + 0x78) = 0x7F60800E;
            else *(u32 *)(self + 0x78) = 0x7F4C6C01;
            *(s32 *)(st + 4) = 2;
        }
        if (part_find_owned_effect_slot(self, 0x04010000, 0) && *(s32 *)st == 0)
            moby_set_state(self, 2, -1);
        *(u8 *)(self + 0xA8) = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(self, D_L16_001B1B70, D_L16_001B1B68, D_L16_001B1B60, 65535, 0, D_L16_001B1B90, 0, 65535, 255, 0);
        for (i = 0; i < 3; i++) {
            vec_local_offset_to_world(self, pos, D_L16_001B1BB0[i].x, D_L16_001B1BB0[i].y, D_L16_001B1BB0[i].z);
            func_PAL_L00_003FB330(pos, 0, 12, 12, 12, 12, 12, 0, 1, 0, 0, 0, *(f32 *)(self + 0x2C), 20.0f);
        }
        if (D_L16_001B1B90 >= 0) {
            *(u16 *)(self + 0x7C) = (1 << D_L16_001B1B90) | 0x8000;
            moby_set_state(self, 3, -1);
        } else moby_mark_spawned(self);
        break;
    }
}
