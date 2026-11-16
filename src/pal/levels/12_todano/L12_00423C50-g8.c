#include "include_asm.h"

#include "common.h"
extern f32 g_burst_piece_params_a[] SDATA(D_L12_001B1F50);
extern f32 g_burst_piece_params_b[] SDATA(D_L12_001B1F58);
extern f32 g_burst_piece_params_c[] SDATA(D_L12_001B1F60);
extern s32 g_burst_piece_effect_id __attribute__((sda));
extern f32 g_burst_offset_x __attribute__((sda));
extern f32 g_burst_offset_y __attribute__((nosda));
extern f32 g_burst_offset_z __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern u8 *g_moby_list_start MACRO_ADDR;
extern s32 g_frame_l12_counter __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((nosda));
extern u8 *g_second_tracked_object __attribute__((nosda));
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern int IsPointInCuboid(void *, int);
extern void moby_set_flag_bit(u8 *, s32);
extern int second_tracked_object_is_open(void);
extern s32 g_explosion_piece_effect __attribute__((sda));
extern f32 g_explosion_piece_table_c[] SDATA(D_L12_001B2280);
extern f32 g_explosion_piece_table_b[] SDATA(D_L12_001B2288);
extern f32 g_explosion_piece_offsets[] SDATA(D_L12_001B22B0);
extern u8 *CreateMoby(int);

void func_PAL_L12_00425A08(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    u8 *rec;
    u8 *obj;
    f32 phase, d;

    switch (a0[0x20]) {
    case 0:
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        rec = g_moby_list_start + (s[1] << 8);
        if (rec[0x31] != 0) {
            phase = IntToFloat(g_frame_l12_counter % 50);
            d = IntToFloat(50);
            phase *= 6.2831855f;
            phase /= d;
            *(s32 *)(rec + 0x78) = PulseColor(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (s[0] == -1)
            break;
        obj = g_tracked_object_ptr;
        if (obj != 0) {
            if (IsPointInCuboid(obj + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(a0, 2, -1);
                if (s[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (s[2] << 8), 1);
            }
        } else if (second_tracked_object_is_open()) {
            if (IsPointInCuboid(g_second_tracked_object + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(a0, 2, -1);
                if (s[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (s[2] << 8), 1);
            }
        }
        break;
    }
}
