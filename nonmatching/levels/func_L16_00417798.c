/* 30 October 2026 recheck: -O2 -G8 -ffunction-sections, 504/504 bytes.
 * USA v1.01 and v2.00: 0/1 placements each, first mismatch +0x128.
 * PAL identity absent. A full 16-byte BurstPoint view ties this source.
 * MACRO_ADDR and -mno-split-addresses hoist the table before the preceding call;
 * the positive countdown still differs. The preheader's constant/table order
 * and split-address temporary remain unresolved; no linked match is claimed.
 */
/* Opus big44, 26 October 2026: -O2 -G8 -ffunction-sections, 126/126 words, 122 identical.
 * D_L16_001B1BB0 is a plain incomplete array (retail builds it with %hi/%lo after the call;
 * the old sda declaration hoisted it). Left: preheader order only. Retail sets the hoisted
 * stack-argument constant 1 ($s3) in the call slot, then the table, then the counter 2;
 * this cc1 emits counter, constant, table. Same family as the probe-loop preheader question.
 */
#include "common.h"
/* Nonmatching reconstruction; game compiler, -O2 -G8 -ffunction-sections.
   us: 16_snivelak: instruction at +0x12c differs.
   us2: 16_snivelak: instruction at +0x12c differs.
   pal: func_L16_00417798 is in neither catalogue of pal.
   Same 504-byte extent after replacing a conditional expression by explicit branches. The constant setup/table-pointer scheduling near +0x12c still differs. Reopen with a measured table-address and loop setup model. */
extern char D_L16_001B1B70[8] __attribute__((sda));
extern char D_L16_001B1B68[8] __attribute__((sda));
extern char D_L16_001B1B60[8] __attribute__((sda));
extern s32 D_L16_001B1B90 __attribute__((sda));
extern f32 D_L16_001B1BB0[];
extern s32 func_00282948(char *);
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, u32, s32);
extern void func_L00_0032A258(char *, char *, char *, char *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L00_00324F18(char *, char *, f32, f32, f32);
extern void func_0032C700(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void func_0029F338(char *);

/* Alternates its hit color, then emits the three configured destruction bursts. */
void func_L16_00417798(char *self) {
    char pos[16];
    char *st = *(char **)(self + 0x68);
    f32 *point;
    s32 i;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(u16 *)(self + 0x34) |= 16;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (func_00282948(st + 4)) {
            if (*(u32 *)(self + 0x78) & 1)
                *(u32 *)(self + 0x78) = 0x7F60800E;
            else *(u32 *)(self + 0x78) = 0x7F4C6C01;
            *(s32 *)(st + 4) = 2;
        }
        if (func_002A9640(self, 0x04010000, 0) && *(s32 *)st == 0)
            func_002A7750(self, 2, -1);
        *(u8 *)(self + 0xA8) = 255;
        break;
    case 2:
        func_L00_0032A258(self, D_L16_001B1B70, D_L16_001B1B68, D_L16_001B1B60, 65535, 0, D_L16_001B1B90, 0, 65535, 255, 0);
        for (point = D_L16_001B1BB0, i = 2; i >= 0; i--, point += 4) {
            func_L00_00324F18(self, pos, point[0], point[1], point[2]);
            func_0032C700(pos, 0, 12, 12, 12, 12, 12, 0, 1, 0, 0, 0, *(f32 *)(self + 0x2C), 20.0f);
        }
        if (D_L16_001B1B90 >= 0) {
            *(u16 *)(self + 0x7C) = (1 << D_L16_001B1B90) | 0x8000;
            func_002A7750(self, 3, -1);
        } else func_0029F338(self);
        break;
    }
}
