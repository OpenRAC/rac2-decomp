#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x1830];
    char *player;
    char reserved1834[0xA60];
    int mode;
} L04DispatchGlobals;
extern L04DispatchGlobals g_hero_state;
extern int g_grouped_object_slot_counts[8] __attribute__((sda));
extern short g_grouped_object_short_table[10] __attribute__((sda));
extern int g_grouped_object_out_value_a __attribute__((sda));
extern int g_grouped_object_out_value_b __attribute__((sda));
extern char g_water_l04_grid_data[], g_grouped_object_call_arg_b[], g_grouped_object_call_arg_c[], g_grouped_object_call_arg_d[];
extern void group_run_shared_routine(void);
extern void gfx_add_draw_callback_third(void);
extern void water_init_object_pal(void *);
extern void water_update_controller_pal(void *);
extern void water_advance_controller_state(void *);
extern void water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);

void grouped_object_update_by_state_pal(char *object)
{
    char *state;
    L04DispatchGlobals *globals = &g_hero_state;
    char *player = globals->player;
    if (player && *(short *)(player + 0xAA) == 0x45 &&
        (unsigned char)player[0x20] != 0xFE && (unsigned char)player[0x20] != 0xFD &&
        globals->mode == 0x31) return;
    state = *(char **)(object + 0x68);
    if (state) {
        int index = *(int *)(state + 0x18);
        int increment = 1;
        if (index != -1) increment = g_grouped_object_slot_counts[index];
        {
            int args[13];
            increment += *(int *)(state + 0x10);
            args[0] = 10;
            args[1] = increment;
            args[8] = (int)&g_grouped_object_out_value_a;
            args[9] = (int)&g_grouped_object_out_value_b;
            args[2] = (int)g_water_l04_grid_data;
            args[3] = (int)g_grouped_object_call_arg_b;
            args[4] = (int)g_grouped_object_short_table;
            args[5] = (int)g_grouped_object_slot_counts;
            args[6] = (int)g_grouped_object_call_arg_c;
            args[7] = (int)g_grouped_object_call_arg_d;
            args[11] = (int)group_run_shared_routine;
            args[12] = (int)gfx_add_draw_callback_third;
            args[10] = (int)object;
            switch ((unsigned char)object[0x20]) {
            case 0:
                water_init_object_pal(args);
                water_add_splash_entry(object, *(float *)(state + 0x28));
                /* Fall through. */
            case 1:
                water_update_controller_pal(args);
                break;
            case 2:
                water_advance_controller_state(args);
                break;
            }
            water_update_ripple_patches(args);
        }
    }
}
