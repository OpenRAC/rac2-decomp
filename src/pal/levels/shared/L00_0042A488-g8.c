/* func_PAL_L00_0042A488, the PAL copy of func_L00_00424F98: the same C, where the
   count limit 0x3C becomes 0x32 and the best time is scaled for 50 Hz, in the test
   and in the store. */
#include "common.h"

typedef struct {
    char pad[0x60];
    unsigned short count;
    unsigned short pad62;
    unsigned int best;
    unsigned int flags;
} L00_00424F98_Counter;

/* The vehicle's input block, at +0x1C0 of its motion record. */
typedef struct {
    char pad0[0x10];
    int flags;
    float steer_out;
    char pad18[4];
    float steer;
    char pad20[4];
    float throttle;
} L00_00424F98_Input;

extern float g_stick_axis_x[];
extern float g_stick_axis_y[];
extern s32 g_ship_steer_option MACRO_ADDR;
extern s32 g_invert_aim_option MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern unsigned int g_frame_counter MACRO_ADDR;
extern L00_00424F98_Counter g_progress_statistics;
extern s32 ref_L00_00424F98_00 __attribute__((sda));
extern s32 ref_L00_00424F98_01 __attribute__((sda));
extern float ref_L00_00424F98_02 __attribute__((sda));
extern float ref_L00_00424F98_03 SDATA(ref_L00_00424F98_03);

/* The vehicle's steering and throttle inputs, with the stunt counter: holding the
   stick centred for a second counts one run and records the best time. */
void ship_read_steer_and_throttle_pal(char *obj, float *x, float *y)
{
    L00_00424F98_Input *input = (L00_00424F98_Input *)(*(char **)(obj + 0x70) + 0x1C0);
    L00_00424F98_Counter *stats;
    unsigned int count;
    float stick_y;

    if (input->flags & 1) {
        *x = 0.0f;
    } else {
        *x = g_stick_axis_x[0];
        if (g_ship_steer_option == 0)
            *x = -*x;
    }
    if (*x == 0.0f) {
        ref_L00_00424F98_00 = 0;
        ref_L00_00424F98_01 = 0;
        if (input->steer != 0.0f)
            *x = input->steer;
    } else {
        input->steer_out = ref_L00_00424F98_02;
        stats = &g_progress_statistics;
        count = stats->count;
        if ((unsigned short)count < 3U) {
            ref_L00_00424F98_00++;
            if (ref_L00_00424F98_01 == 0 && ref_L00_00424F98_00 > 0x32) {
                if ((unsigned short)count < 0xFFFF)
                    stats->count = count + 1;
                if (((s32)(g_frame_counter) * 5 + 2) / 6 > stats->best)
                    stats->best = ((s32)(g_frame_counter) * 5 + 2) / 6;
                ref_L00_00424F98_01 = 1;
                stats->flags = (stats->flags | (1u << g_current_map_index)) | 0x80000000u;
            }
        }
    }
    if (input->flags & 2) {
        *y = 0.0f;
    } else {
        stick_y = g_stick_axis_y[0];
        *y = -stick_y;
        if (g_invert_aim_option == 0)
            *y = stick_y;
        if (*y != 0.0f)
            return;
    }
    {
        float throttle = input->throttle;
        *y = throttle / ref_L00_00424F98_03;
    }
}
