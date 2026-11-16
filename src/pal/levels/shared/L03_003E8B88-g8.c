#include "include_asm.h"

#include "common.h"
extern u32 g_path_puzzle_glow_color_a __attribute__((sda));
extern u32 g_path_puzzle_glow_color_b NOT_SDA;
extern u32 g_path_puzzle_glow_color_c NOT_SDA;
extern u32 g_path_puzzle_glow_color_d NOT_SDA;
extern u32 g_path_puzzle_glow_color_e NOT_SDA;
extern u32 g_path_puzzle_glow_color_f NOT_SDA;
extern f32 g_path_puzzle_glow_ease_rate_a __attribute__((sda));
extern f32 g_path_puzzle_glow_ease_rate_b NOT_SDA;
extern f32 FastAddRotations(f32, f32);
extern int ref_L01_0031BC68_00(int, int, f32);

/* Eases the record's own rate by the shared factor and hands the state the
   shared lookup asks for. */
void path_puzzle_update_glow_color_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u32 colors[2];
    f32 ease_rate;
    f32 angle;

    if (moby[0x20] == 5 || *(short *)(vars + 0x6A) == 0) {
        colors[0] = g_path_puzzle_glow_color_a;
        colors[1] = g_path_puzzle_glow_color_b;
        ease_rate = g_path_puzzle_glow_ease_rate_a * 0.0003490659f;
    } else if (*(short *)(vars + 0x68) != 0) {
        colors[0] = g_path_puzzle_glow_color_c;
        colors[1] = g_path_puzzle_glow_color_d;
        ease_rate = g_path_puzzle_glow_ease_rate_b * 0.0003490659f;
    } else {
        colors[0] = g_path_puzzle_glow_color_e;
        colors[1] = g_path_puzzle_glow_color_f;
        ease_rate = g_path_puzzle_glow_ease_rate_b * 0.0003490659f;
    }
    angle = FastAddRotations(*(f32 *)(vars + 0x78), ease_rate);
    *(f32 *)(vars + 0x78) = angle;
    *(u32 *)(moby + 0x78) = ref_L01_0031BC68_00(colors[0], colors[1], angle);
}
