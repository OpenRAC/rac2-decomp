#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
extern f32 FastAddRotations(f32, f32);
extern f32 g_hero_l13_height_limit __attribute__((sda));
extern u8 g_str_rising_platform_sound[];
extern u8 g_moby_group_flags[];
extern u8 *g_moby_slot_table __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 g_hero_state[];
extern f32 vec_distance_xy(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern u8 g_str_linked_door_msg_a[];
extern u8 g_str_linked_door_msg_b[];
extern u8 g_game_flag_table[];
extern u8 g_str_rising_platform_sound[];

/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw_us2(u8 *moby) {
    *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4), 0.017453296f);
}


/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw_alt_us2(u8 *moby) {
    *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4), 0.017453296f);
}

