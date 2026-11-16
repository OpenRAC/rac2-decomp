#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} L02_Mob;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L02_Mob *mobs[1];
} L02_MobList;

extern L02_MobList g_mob_list;

/* sda in this -G0 unit gives the bare-symbol load: retail has it as `lui`/`lw` in the loop and after
   it and, as the filler of the first branch's delay slot, as the one-instruction `$gp` form gas
   makes of it there. */
extern int g_current_map_index __attribute__((sda));

extern void anim_start_startup_animations(void);

extern void UpdateEquipmentPieces_us2(void *);

extern void math_store_angle_update_result(void *, void *, int, int, float);

extern void gfx_add_draw_callback_first(void *, void *);

extern void cutscene_draw_intro_overlays(void *);

/* func_US2_L02_00301998, the USA v2.00 copy of func_L02_00300CE8: the same C, where the 0xFA0 mobs' call
   is skipped in game state 0x33, func_002E64A0 becomes func_US2_002E72D8, and the mob pointer is read as
   base + i * 4 + 0x18C rather than D_L02_001BE200.mobs[i], as in func_US2_L14_00305238. */
void level_update_moby_list_effects_us2(void) {
    int i;

    anim_start_startup_animations();
    for (i = 0; i < g_mob_list.count; i++) {
        L02_Mob *mob = ((L02_MobList *)((u8 *)&g_mob_list + i * 4))->mobs[0];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            UpdateEquipmentPieces_us2(mob);
        if (mob != 0 && mob->type == 0xFA0 && g_current_map_index != 0x33 && mob->p68 != 0)
            math_store_angle_update_result(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
    }
    if (g_current_map_index == 2 && g_mob_list.mode == 2)
        gfx_add_draw_callback_first(cutscene_draw_intro_overlays, 0);
}
