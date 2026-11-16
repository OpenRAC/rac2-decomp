#include "include_asm.h"
#include "common.h"







extern int func_002A77E0_3(int x);

/* func_PAL_L00_004040D8, the PAL copy of func_L00_003FF7B8: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void glow_effect_init_vars_pal(char *self)
{
    float *vars = *(float **)(self + 104);
    float *cursor = vars;
    int *timers;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *cursor = (float)func_002A77E0_3(255);
        cursor++;
    }

    vars[4] = -1.0000000000000000000000e+00f;
    vars[5] = -2.2500000000000000000000e+00f;
    vars[6] = 1.2500000000000000000000e+00f;
    vars[7] = 2.5000000000000000000000e+00f;

    timers = (int *)(vars + 8);
    for (j = 0; j < 4; j++)
    {
        timers[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    vars[12] = 2.5000000000000000000000e+00f;
    vars[13] = 3.0000000000000000000000e+00f;
    vars[15] = 2.5000000000000000000000e+00f;
    vars[14] = 3.0000000000000000000000e+00f;
}


extern void moby_set_state(char *arg, int mode, int value);
extern void glow_effect_init_vars_pal(char *arg);
extern void glow_ring_effect_update_pal(char *arg);
extern float vec_distance_xy(char *arg, char *table);
extern float math_fabs(float value);
extern void value_set_entry_by_index_pal(int arg, int value);
extern void help_unlock_entry(int arg);
extern int moby_handle_request_slot_state(int arg);
extern void moby_mark_spawned(char *arg);
extern char D_00189EA0_2[];
extern unsigned char g_action_flag __attribute__((sda));
extern void func_002E6EF8(void (*f)(char *), char *arg);

/* two-state update on a record: state 0 marks a byte with 255 and either runs a shared two-call teardown when a global latch byte is set and a sub-object field is non-zero, or plays a mode/value pair plus a call; state 1 runs a setup call and two float queries against a stored table and, when both are below 2.0, plays three fixed calls and either tears down or writes 120 into a sub-object field */
void charge_boots_pickup_update_pal(char *moby)
{
    int *vars = *(int **)(moby + 104);
    unsigned char phase = *(unsigned char *)(moby + 32);

    switch (phase) {
    case 0:
        *(unsigned char *)(moby + 48) = 255;
        if (g_action_flag != 0 && vars[17] != 0) {
            moby_mark_spawned((char *)vars[17]);
            moby_mark_spawned(moby);
            return;
        } else {
            moby_set_state(moby, 1, -1);
            glow_effect_init_vars_pal(moby);
        }
        break;
    case 1:
        glow_ring_effect_update_pal(moby);
        if (vec_distance_xy(moby + 16, D_00189EA0_2) < 2.0f) {
            if (math_fabs(*(float *)(moby + 24) - *(float *)(D_00189EA0_2 + 8)) < 2.0f) {
                value_set_entry_by_index_pal(4658, -1);
                help_unlock_entry(54);
                moby_handle_request_slot_state(54);
                if (vars[17] != 0) {
                    moby_mark_spawned((char *)vars[17]);
                    moby_mark_spawned(moby);
                    return;
                }
                vars[16] = 100;
            }
        }
        break;
    }
}


