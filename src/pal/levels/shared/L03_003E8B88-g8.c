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
void path_puzzle_update_glow_color_pal(u8 *a0) {
    u8 *rec = *(u8 **)(a0 + 0x68);
    u32 c[2];
    f32 f13;
    f32 r;

    if (a0[0x20] == 5 || *(short *)(rec + 0x6A) == 0) {
        c[0] = g_path_puzzle_glow_color_a;
        c[1] = g_path_puzzle_glow_color_b;
        f13 = g_path_puzzle_glow_ease_rate_a * 0.0003490659f;
    } else if (*(short *)(rec + 0x68) != 0) {
        c[0] = g_path_puzzle_glow_color_c;
        c[1] = g_path_puzzle_glow_color_d;
        f13 = g_path_puzzle_glow_ease_rate_b * 0.0003490659f;
    } else {
        c[0] = g_path_puzzle_glow_color_e;
        c[1] = g_path_puzzle_glow_color_f;
        f13 = g_path_puzzle_glow_ease_rate_b * 0.0003490659f;
    }
    r = FastAddRotations(*(f32 *)(rec + 0x78), f13);
    *(f32 *)(rec + 0x78) = r;
    *(u32 *)(a0 + 0x78) = ref_L01_0031BC68_00(c[0], c[1], r);
}
