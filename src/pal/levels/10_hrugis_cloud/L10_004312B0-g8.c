#include "include_asm.h"

#include "common.h"
extern int g_cloud_puff_index __attribute__((sda));
extern u8 g_cloud_puff_data[];
extern int part_l00_alloc_effect_slot_2(void *a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern f32 FastAddRotations(f32 f12, f32 f13);
extern void gfx_add_draw_callback_third(void *a0, void *a1);
extern u8 *g_spot_record_table;
extern f32 math_random_float_range(f32 low, f32 high);
extern f32 math_random_angle(void);
extern f32 IntToFloat(int);
extern u8 g_cloud_puff_table[];

/* Two-state start-up for a cloud puff: state 0 lays the record at +0x10 out (position
   reset, colour limits, the builder call, its handle in the $gp variable), and states 0
   and 1 both fade the +0xF8 value down; anything else goes straight to the update. */
void cloud_puff_startup_update_pal(u8 *a0) {
    u8 *s0 = a0;
    u8 state = *(u8 *)(s0 + 0x20);
    f32 v;

    switch (state) {
    case 0:
        *(int *)(s0 + 0x1C) = 0;
        *(u8 *)(s0 + 0x20) = 1;
        v = *(f32 *)(s0 + 0x1C);
        *(u16 *)(s0 + 0x32) = 0x1FF;
        *(u8 *)(s0 + 0x30) = 0xFF;
        *(f32 *)(s0 + 0x10) = 512.0f;
        *(f32 *)(s0 + 0x14) = 512.0f;
        *(f32 *)(s0 + 0x18) = 512.0f;
        g_cloud_puff_index = part_l00_alloc_effect_slot_2(s0 + 0x10, 40.0f, v, v, v, 1.0f);
    case 1:
        *(f32 *)(s0 + 0xF8) =
            FastAddRotations(*(f32 *)(s0 + 0xF8), 0.011780974f);
        break;
    default:
        break;
    }
    gfx_add_draw_callback_third(g_cloud_puff_data, s0);
}
