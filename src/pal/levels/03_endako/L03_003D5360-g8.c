#include "include_asm.h"
#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] __attribute__((sda));
extern f32 D_L03_001B0648 __attribute__((sda));
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  b18;
    u8  b19;
    u16 h1A;
    u16 pad1C;
    u8  b1E;
    u8  b1F;
    u8  pad20[0x10];
    u16 h30;
    u16 h32;
    s32 i34;
} L03_003D21F8_Obj;
extern L03_003D21F8_Obj *D_L03_001B0670 __attribute__((sda));
extern u32 D_L03_001B3458;
extern void *cam_alloc_override_slot(s32 size);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   g_sound_state[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));

/* case 0 spawns the object and points the actor at it; case 1 clears the
   object while the state word still reads zero, and clears the word otherwise */
void func_PAL_L03_003D6398(char *a0)
{
    char *s0 = a0;

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        D_L03_001B0670 = cam_alloc_override_slot(4);
        moby_set_state(s0, 1, -1);
        *(u8 *)(s0 + 0x30) = 0xFF;
        break;
    case 1: {
        u32 v = D_L03_001B3458;

        if (v == 0) {
            D_L03_001B0670->f00 = -1.0f;
            D_L03_001B0670->f04 = -1.0f;
            D_L03_001B0670->f08 = -1.0f;
            D_L03_001B0670->f0C = -1.0f;
            D_L03_001B0670->f10 = -1.0f;
            D_L03_001B0670->f14 = -1.0f;
            D_L03_001B0670->b18 = 0;
            D_L03_001B0670->b19 = 0;
            D_L03_001B0670->h1A = 0;
            D_L03_001B0670->b1E = 0;
            D_L03_001B0670->b1F = 0;
            D_L03_001B0670->h30 = 0;
            D_L03_001B0670->i34 = 6;
            D_L03_001B0670->h32 = 100;
        } else {
            D_L03_001B3458 = 0;
        }
        break;
    }
    }
}
