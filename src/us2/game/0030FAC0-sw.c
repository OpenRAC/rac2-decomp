#include "include_asm.h"

#include "common.h"
typedef float VecE[4] __attribute__((aligned(16)));
extern VecE D_001BAFB0, D_001BAFA0;
typedef struct {
    u8 pad00[0x80]; VecE position; u8 pad90[0x50]; VecE pickup_target;
    u8 padF0[0x2290-0xF0]; void *moby;
    u8 pad2294[0x24A4-0x2294]; f32 reach_distance, reach_height;
    u8 pad24AC[0x20]; s32 health;
} AmmoHero;
extern AmmoHero D_00189E20;
typedef struct {
    u8 pad00[0x38]; s16 sound_multiple, sound_single;
    u8 pad3C[0x8E - 0x3C]; u16 max_ammo; u8 pad90[0x50];
} AmmoDef;
extern u8 D_00239BA0[];
extern u8 D_00139568[];
extern s32 D_00139688[];
extern void *D_0018C0B0 NOT_SDA;
extern s32 D_001B1688[] __attribute__((sda));
extern s32 D_001B24A8[] __attribute__((sda));
extern s32 D_001B24A8_gp SDATA(D_001B24A8);
extern s32 func_00282948(s32 *);
extern u32 func_0026F748(s32, s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_US2_002B18B0(s32, s32, s32);
extern void func_0029F338(void *);
extern f32 func_00282DF0(void *);
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);
extern f32 func_002A0558(void *, void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00283180(f32);
extern s32 func_00277258(void *, s32, s32, f32);
extern s32 func_002761F8(void *, void *, s32, s32, s32);
extern s32 func_00283CF0(f32);
extern s32 func_00282C30(s32);
#define EF(p, n) (*(f32 *)((u8 *)(p) + (n)))
#define EI(p, n) (*(s32 *)((u8 *)(p) + (n)))


