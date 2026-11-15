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

extern float D_00138280[];
extern float D_00138284[];
extern s32 D_001A7BA8 MACRO_ADDR;
extern s32 D_001A7BA4 MACRO_ADDR;
extern s32 g_current_map_index MACRO_ADDR;
extern unsigned int D_001A7390 MACRO_ADDR;
extern L00_00424F98_Counter g_progress_statistics;
extern s32 ref_L00_00424F98_00 __attribute__((sda));
extern s32 ref_L00_00424F98_01 __attribute__((sda));
extern float ref_L00_00424F98_02 __attribute__((sda));
extern float ref_L00_00424F98_03 SDATA(ref_L00_00424F98_03);

/* The vehicle's steering and throttle inputs, with the stunt counter: holding the
   stick centred for a second counts one run and records the best time. */
void ship_read_steer_and_throttle(char *vehicle, float *steerOut, float *throttle_out)
{
    L00_00424F98_Input *input = (L00_00424F98_Input *)(*(char **)(vehicle + 0x70) + 0x1C0);
    L00_00424F98_Counter *counter;
    unsigned int run_count;
    float stick_y;

    if (input->flags & 1) {
        *steerOut = 0.0f;
    } else {
        *steerOut = D_00138280[0];
        if (D_001A7BA8 == 0)
            *steerOut = -*steerOut;
    }
    if (*steerOut == 0.0f) {
        ref_L00_00424F98_00 = 0;
        ref_L00_00424F98_01 = 0;
        if (input->steer != 0.0f)
            *steerOut = input->steer;
    } else {
        input->steer_out = ref_L00_00424F98_02;
        counter = &g_progress_statistics;
        run_count = counter->count;
        if ((unsigned short)run_count < 3U) {
            ref_L00_00424F98_00++;
            if (ref_L00_00424F98_01 == 0 && ref_L00_00424F98_00 > 0x3C) {
                if ((unsigned short)run_count < 0xFFFF)
                    counter->count = run_count + 1;
                if (D_001A7390 > counter->best)
                    counter->best = D_001A7390;
                ref_L00_00424F98_01 = 1;
                counter->flags = (counter->flags | (1u << g_current_map_index)) | 0x80000000u;
            }
        }
    }
    if (input->flags & 2) {
        *throttle_out = 0.0f;
    } else {
        stick_y = D_00138284[0];
        *throttle_out = -stick_y;
        if (D_001A7BA4 == 0)
            *throttle_out = stick_y;
        if (*throttle_out != 0.0f)
            return;
    }
    {
        float throttle = input->throttle;
        *throttle_out = throttle / ref_L00_00424F98_03;
    }
}
