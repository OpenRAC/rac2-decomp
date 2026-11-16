#include "include_asm.h"

#include "common.h"
extern s8 g_hero_state[];
extern f32 ref_L00_003DC1C0_00 __attribute__((sda));
extern f32 ref_L00_003DC1C0_01 __attribute__((sda));
extern f32 ref_L00_003DC1C0_02 __attribute__((sda));
extern f32 ref_L00_003DC1C0_03 __attribute__((sda));
extern s32 ref_L00_003DC1C0_04(s32, s32, s32, s32, f32, f32, f32, f32);
extern f32 ref_L00_003DC1C0_05(f32, f32);
extern void ref_L00_003DC1C0_06(s32, s32, s32, f32);
extern void ref_L00_003DC1C0_07(s32, s32, s32, s32, f32, f32, f32, f32);

/* Tries to throw something in an arc away from the camera and, if that fails, tilts the vector a little (PAL: 50 Hz scales). */
s32 weapon_throw_along_camera_arc_pal(s32 object, s32 out_vector, s32 unused, s32 flags) {
    s8 *hero;
    s32 target;
    s32 result;

    hero = g_hero_state;
    result = ref_L00_003DC1C0_04(*(s32 *)(hero + 0x2290) + 0xC0, 5, 0, flags, ref_L00_003DC1C0_01, *(f32 *)(hero + 0x98), 0.39269909f, 0.39269909f);
    ref_L00_003DC1C0_07(out_vector, object + 0x10, result, 0, ref_L00_003DC1C0_02, ref_L00_003DC1C0_05(ref_L00_003DC1C0_02, ref_L00_003DC1C0_01), ref_L00_003DC1C0_00 * 0.020000001f, ref_L00_003DC1C0_03 * 0.00040000002f);
    if (result == 0) {
        target = *(s32 *)(hero + 0x2290) + 0xE0;
        ref_L00_003DC1C0_06(out_vector, out_vector, target, ref_L00_003DC1C0_05(-0.19634955f, 0.19634955f));
    }
    return result;
}
