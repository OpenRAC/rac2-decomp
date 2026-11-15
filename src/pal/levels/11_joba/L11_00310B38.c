#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L11_0030F060;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L11_0030F060 *mobs[1];
} MobList_L11_0030F060;

extern MobList_L11_0030F060 ref_L11_0030F060_00;
extern int g_current_map_index __attribute__((sda));
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void level_start_progress_cue(void *);

/* func_PAL_L11_00310B38, the PAL copy of func_L11_0030F060: the same C, where the 0xFA0 mob's call
   is skipped in game state 0x33 and its float argument 0.0610865355f becomes 0.07330384f (6/5 for 50 Hz).
   Walks the level's list of mobs; when the game state is 0xB and the list's word at +0x30 is 2 it
   queues func_L11_0030ED58. */
void func_PAL_L11_00310B38(void) {
    int i;

    anim_start_startup_animations();
    for (i = 0; i < ref_L11_0030F060_00.count; i++) {
        Mob_L11_0030F060 *mob = ref_L11_0030F060_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_PAL_002E7270(mob);
        if (mob != 0) {
            int kind = 0xFA0;

            if (mob->type == kind && g_current_map_index != 0x33 && mob->p68 != 0)
                math_store_angle_update_result(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }
    if (g_current_map_index == 0xB && ref_L11_0030F060_00.mode == 2)
        gfx_add_draw_callback_first(level_start_progress_cue, 0);
}
