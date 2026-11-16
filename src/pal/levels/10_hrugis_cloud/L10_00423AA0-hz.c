/* func_PAL_L10_00423AA0, the PAL copy of func_L10_0041EC10: the same C with the per-frame phase
   step 2*pi/60 becomes 2*pi/50 (0.12566373f); the callee is PAL's func_PAL_L10_00423BE0, and the
   8-byte callback is catalogued in PAL as func_L00_00410D18. */
#include "common.h"

extern u32 *func_0037BA88(u8 *arg0);
extern f32 func_00335320(void);
extern u8 *func_0037B670();
extern void func_0037BC48(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern f32 func_00309120(f32 f12);

extern f32 func_00309B38(f32 f12, f32 f13);
extern u8 func_L10_00423780(void);
extern s32 FastTweenColor(s32 a0, s32 a1, f32 f12);
extern void moby_update_empty_alt(void);
extern void pulsing_light_draw_group_glows(u8 *arg0);
extern s32 g_current_map_index[] __attribute__((sda));

extern void pulsing_light_init_pal(u8 *arg0);

/* Pulsing light: sets itself up in state 0, then steps its glow phase each frame and tints itself with it (PAL copy of pulsing_l10_light_update, 50 Hz phase step). */
void pulsing_l10_light_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 phase;
    u8 *motion;
    s32 mode;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (func_0037B670() != 0) {
            pulsing_light_init_pal(moby);
            if (*(s32 *)(vars + 0x264) != 0) {
                func_0037BC48(moby, (s32)moby_update_empty_alt, (s32)pulsing_light_draw_group_glows, 0);
            }
            *(f32 *)(vars + 0x268) = func_00335320();
        }
        break;
    case 1:
        motion = func_0037BA88(moby);
        mode = g_current_map_index[0];
        *(s32 *)((u8 *)motion + 0x14C) = 0;
        if (mode == 10 && func_L10_00423780() == 2) {
            *(u16 *)(moby + 0x34) |= 0x1000;
        } else {
            *(u16 *)(moby + 0x34) &= 0xEFFF;
        }
        func_0037D390(moby, 0, 0, 0);
        phase = func_00309B38(*(f32 *)(vars + 0x268), 0.12566373f);
        *(f32 *)(vars + 0x268) = phase;
        *(s32 *)(moby + 0x78) = FastTweenColor(0x20202020, -1, (func_00309120(phase) + 1.0f) * 0.5f);
        break;
    }
}
