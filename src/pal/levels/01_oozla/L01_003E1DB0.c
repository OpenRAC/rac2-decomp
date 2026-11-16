#include "include_asm.h"

#include "common.h"
extern s32 moby_l01_turn_toward_target(void *, void *);
extern f32 func_310648();
extern f32 func_310580(f32 x, f32 y);
extern s32 func_310528(s32 a, s32 b);
extern f32 func_2E3A48(f32 x);
extern f32 func_2E3A60(f32 x);
extern s32 coll_process_hit(f32 radius, void *pos, s32 flag, void *obj, s32 arg);
extern u32 g_contact_moby_list[];
extern void gfx_update_color_fade(void *, void *);
extern int FastDecTimer(void *);
extern s32 math_fast_float_d(void *);
extern void value_set_and_smooth(void *, void *, s32, s32, f32);
extern u8 *g_camera_path_configs __attribute__((sda));
extern s32 cam_is_hero_in_trigger(void *);

/* Ticks the Muckdweller's colour fade, age counter and countdown timers (PAL copy). */
void muckdweller_tick_timers_pal(u8 *moby)
{
    u32 value;
    u8 *p = *(u8 **)(moby + 0x68);

    gfx_update_color_fade(moby, p + 0x100);
    value = *(u16 *)(moby + 0x96);
    if (value <= 0xFFFE) {
        *(u16 *)(moby + 0x96) = value + 1;
    }
    FastDecTimer(p + 0x3D8);
    math_fast_float_d(p + 0x404);
    FastDecTimer(p + 0x3D6);
    value = *(s16 *)(p + 0x3DA);
    if (value != 0) {
        *(u16 *)(p + 0x3D6) = 0x12C;
        *(s16 *)(p + 0x3DA) = 0;
    }
    value_set_and_smooth(moby, p + 0x300, 1, 1, 1.8f);
}

