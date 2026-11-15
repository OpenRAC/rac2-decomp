/* func_PAL_00303950, the PAL copy of func_00302848: the same C, where scale func_002A7820(D_001AE900_blk[5], D_001AE900_blk[6]). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F302848;

extern s32 D_001AE930 __attribute__((sda));
extern s32 D_001AE900 SDATA(D_001AE900);
extern s32 D_001AE928 __attribute__((sda));
extern float D_001AE920[] SDATA(D_001AE920);
extern s32 D_001AE92C __attribute__((sda));
extern float D_001AE8F0 SDATA(D_001AE8F0);
extern float D_001AE8E8 SDATA(D_001AE8E8);
extern s32 D_001AE900_blk[] __asm__("D_001AE900") MACRO_ADDR;
extern float D_001AE920_blk[] __asm__("D_001AE920") MACRO_ADDR;
extern float D_001AE8E8_blk[] __asm__("D_001AE8E8") MACRO_ADDR;
extern float D_001AE8F0_blk[] __asm__("D_001AE8F0") MACRO_ADDR;
extern char D_001A8BD0[16] __attribute__((sda));
extern u8 *D_001F0000[];
extern s32 g_game_time[4] __attribute__((sda));

extern s32 math_random_int_below(s32);
extern void *part_spawn_ground_effect(char *, float, float, s32, s32, float, s32, s32, char *, s32);
extern char *part_spawn_fading(char *, s32, s32, s32, s32, s32, s32, float);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, char *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern s32 FastTweenColor(s32, s32, float);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);

/* Spawns the object's trail puff; when not suppressed and flag one of the resident word is set it also emits the tinted streak. */
void func_PAL_00303950(char *obj, s32 quiet)
{
    V4_F302848 zero;
    V4_F302848 vec;
    char *rec = *(char **)(obj + 0x68);
    char *puff;
    char *pos;
    s32 tint, color;

    qzero(&zero);
    if (math_random_int_below(D_001AE930) == 0)
        part_spawn_ground_effect(obj + 0x10, D_001AE920[0], D_001AE920_blk[1], D_001AE92C, D_001AE900_blk[1], 0.0f, 2, math_random_int_below(1) ? -D_001AE928 : D_001AE928, D_001A8BD0, 0);
    pos = obj + 0x10;
    puff = part_spawn_fading(pos, D_001AE900, *(u8 *)(rec + 0x41), 0, 0, 2, 0, D_001AE8F0);
    if (puff != 0)
        puff[2] = *D_001F0000[0x98E];
    if (quiet == 0 && (g_game_time[0] & 1)) {
        vec_random_direction(&vec, 0.0f, 0.05f);
        FastVecAdd(&vec, &vec, pos);
        zero.f[2] = -(math_random_float_range(D_001AE8E8, D_001AE8E8_blk[1]) * 0.020000001f);
        tint = (((int)(math_random_int_range(D_001AE900_blk[5], D_001AE900_blk[6])) * 5 + 2) / 6);
        color = FastTweenColor(D_001AE900_blk[2], D_001AE900_blk[3], math_random_float_range(0.0f, 1.0f));
        part_spawn_hero_relative(&vec, &zero, color, tint, math_random_int_below(0xFF), 0, D_001AE8F0_blk[2]);
    }
}
