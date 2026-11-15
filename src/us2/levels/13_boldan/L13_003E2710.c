#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
extern f32 FastAddRotations(f32, f32);
extern f32 D_L13_001B2568 __attribute__((sda));
extern u8 D_L13_001B1E60[];
extern u8 D_0019B2E8[];
extern u8 *D_L13_001B2A0C __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 g_hero_state[];
extern f32 vec_distance_xy(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern u8 D_L13_001B1C20[];
extern u8 D_L13_001B1C48[];
extern u8 D_001395B8[];
extern u8 D_L13_001B1E60[];

void func_US2_L13_003E2710(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.017453296f);
}


void func_US2_L13_003E2748(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.017453296f);
}

