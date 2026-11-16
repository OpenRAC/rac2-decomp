#include "include_asm.h"
#include "common.h"
extern s8 g_pool_effect_slots[];
extern void gfx_draw_lightning_bolt(s32 a, s32 b);
extern void gfx_draw_billboard_quad(void *o, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14);
extern f32 math_random_float_range(f32 a, f32 b);

/* Draws the lightning bolt and the three glowing billboards of each effect slot that belongs to the owner (PAL build). */
void gfx_draw_owner_effect_slots_pal(s32 owner) {
    s32 i;
    s32 slot_start;
    s8 *slot;
    s8 *pool;

    pool = g_pool_effect_slots;
    slot = pool + 0x30;
    slot_start = (s32) pool;
    for (i = 0; i < 3; i++) {
        if ((*(s32 *)((s8 *)(slot) + (0x5C))) == owner) {
            gfx_draw_lightning_bolt(owner, slot_start);
            if ((*(s32 *)((s8 *)(slot) + (0x64))) == 0) {
                gfx_draw_billboard_quad(slot, 0x31, 0x3F007F00, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(slot, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(slot, 0xB, 0x10003F00, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
        slot += 0xA0;
        slot_start += 0xA0;
    }
}
