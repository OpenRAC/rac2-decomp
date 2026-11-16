#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern float g_space_ship_threshold __attribute__((sda));
extern float g_ship_align_turn_threshold __attribute__((sda));
extern s16 g_platform_mode[];
extern f32 math_fabs(f32 f);

/* Says whether the ship is lined up well enough with its target to carry on. */
s32 space_ship_is_aligned_with_target_pal(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    f32 turn_error;
    if (*(f32 *)(vars + 0x3DC) < g_space_ship_threshold) return 1;
    turn_error = math_fabs(*(f32 *)(vars + 0x414) - *(f32 *)(vars + 0x410));
    if (g_platform_mode[0] < 0x9) return 0;
    if (*(f32 *)(vars + 0x3E0) < g_space_ship_threshold) {
        if (turn_error < g_ship_align_turn_threshold) return 1;
    }
    return 0;
}
