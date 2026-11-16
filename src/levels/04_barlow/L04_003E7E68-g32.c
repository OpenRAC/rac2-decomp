#include "include_asm.h"
#include "names.h"

/* The shared state record supplies the active player and current mode. */
typedef struct {
    char reserved00[0x1830];
    char *player;
    char reserved1834[0xA60];
    int mode;
} L04DispatchGlobals;
extern L04DispatchGlobals g_hero_state;

/* Eight group counts and ten signed slot indices, addressed through $gp. */
extern int g_grouped_object_slot_counts[8] __attribute__((sda));
extern short g_grouped_object_short_table[10] __attribute__((sda));
extern int g_grouped_object_out_value_a __attribute__((sda));
extern int g_grouped_object_out_value_b __attribute__((sda));
extern char g_water_l04_grid_data[], g_grouped_object_call_arg_b[], g_grouped_object_call_arg_c[], g_grouped_object_call_arg_d[];
extern void group_run_shared_routine(void);
extern void gfx_add_draw_callback_third(void);
extern void water_init_object(void *);
extern void water_update_controller(void *);
extern void water_advance_controller_state(void *);
extern void water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);

/* Runs the shared per-frame code for an object that belongs to a group, calling a different routine for each of its states. */
void grouped_object_update_by_state(char *moby)
{
    char *vars;
    L04DispatchGlobals *globals = &g_hero_state;
    char *player = globals->player;
    if (player && *(short *)(player + 0xAA) == 0x45 &&
        (unsigned char)player[0x20] != 0xFE && (unsigned char)player[0x20] != 0xFD &&
        globals->mode == 0x31) return;
    vars = *(char **)(moby + 0x68);
    if (vars) {
        int groupIndex = *(int *)(vars + 0x18);
        int slotCount = 1;
        if (groupIndex != -1) slotCount = g_grouped_object_slot_counts[groupIndex];
        {
            int callArgs[13];
            slotCount += *(int *)(vars + 0x10);
            callArgs[0] = 10;
            callArgs[1] = slotCount;
            callArgs[8] = (int)&g_grouped_object_out_value_a;
            callArgs[9] = (int)&g_grouped_object_out_value_b;
            callArgs[2] = (int)g_water_l04_grid_data;
            callArgs[3] = (int)g_grouped_object_call_arg_b;
            callArgs[4] = (int)g_grouped_object_short_table;
            callArgs[5] = (int)g_grouped_object_slot_counts;
            callArgs[6] = (int)g_grouped_object_call_arg_c;
            callArgs[7] = (int)g_grouped_object_call_arg_d;
            callArgs[11] = (int)group_run_shared_routine;
            callArgs[12] = (int)gfx_add_draw_callback_third;
            callArgs[10] = (int)moby;
            switch ((unsigned char)moby[0x20]) {
            case 0:
                water_init_object(callArgs);
                water_add_splash_entry(moby, *(float *)(vars + 0x28));
                /* Fall through. */
            case 1:
                water_update_controller(callArgs);
                break;
            case 2:
                water_advance_controller_state(callArgs);
                break;
            }
            water_update_ripple_patches(callArgs);
        }
    }
}
