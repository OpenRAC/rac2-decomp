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

/* Pulses the colour of a linked moby. When the hero walks into its zone, it turns the linked moby off and wakes up a third one (PAL: 50 Hz timings). */
void zone_color_pulse_update_pal(u8 *moby)
{
    s32 *vars = *(s32 **)(moby + 0x68);
    u8 *linked;
    u8 *target;
    f32 phase, period;

    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        linked = g_moby_list_start + (vars[1] << 8);
        if (linked[0x31] != 0) {
            phase = IntToFloat(g_frame_l12_counter % 50);
            period = IntToFloat(50);
            phase *= 6.2831855f;
            phase /= period;
            *(s32 *)(linked + 0x78) = PulseColor(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (vars[0] == -1)
            break;
        target = g_tracked_object_ptr;
        if (target != 0) {
            if (IsPointInCuboid(target + 0x10, vars[0])) {
                *(s32 *)(linked + 0x78) = 0x80A02020;
                moby_set_state(moby, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (vars[2] << 8), 1);
            }
        } else if (second_tracked_object_is_open()) {
            if (IsPointInCuboid(g_second_tracked_object + 0x10, vars[0])) {
                *(s32 *)(linked + 0x78) = 0x80A02020;
                moby_set_state(moby, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (vars[2] << 8), 1);
            }
        }
        break;
    }
}
