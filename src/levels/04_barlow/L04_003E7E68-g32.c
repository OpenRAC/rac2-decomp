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
extern int D_L04_001AFFA0[8] __attribute__((sda));
extern short D_L04_001AFFC0[10] __attribute__((sda));
extern int D_L04_001AFFD4 __attribute__((sda));
extern int D_L04_001AFFD8 __attribute__((sda));
extern char D_L04_002AF6C0[], D_L04_002405C0[], D_L04_00240660[], D_L04_002BA660[];
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
        if (groupIndex != -1) slotCount = D_L04_001AFFA0[groupIndex];
        {
            int callArgs[13];
            slotCount += *(int *)(vars + 0x10);
            callArgs[0] = 10;
            callArgs[1] = slotCount;
            callArgs[8] = (int)&D_L04_001AFFD4;
            callArgs[9] = (int)&D_L04_001AFFD8;
            callArgs[2] = (int)D_L04_002AF6C0;
            callArgs[3] = (int)D_L04_002405C0;
            callArgs[4] = (int)D_L04_001AFFC0;
            callArgs[5] = (int)D_L04_001AFFA0;
            callArgs[6] = (int)D_L04_00240660;
            callArgs[7] = (int)D_L04_002BA660;
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
