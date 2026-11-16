#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} Mob_L09_002F8FD8;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    Mob_L09_002F8FD8 *mobs[1];
} MobList_L09_002F8FD8;

extern MobList_L09_002F8FD8 ref_L09_002F8FD8_00;

extern int g_current_map_index __attribute__((sda));

extern void anim_start_startup_animations(void);

extern void UpdateEquipmentPieces_us2(void *);

extern void math_store_angle_update_result(void *, void *, int, int, float);

extern void gfx_add_draw_callback_first(void *, void *);

extern void gfx_draw_state_nine_pulsing_quad(void *);

/* func_US2_L09_002F9B28, the USA v2.00 copy of func_L09_002F8FD8: the same C, where the 0xFA0 mobs' call
   is skipped in game state 0x33, func_002E64A0 becomes func_US2_002E72D8, and the mob pointer is read as
   base + i * 4 + 0x18C rather than ref_L09_002F8FD8_00.mobs[i], as in func_US2_L14_00305238. */
void mob_list_update_flags_us2(void) {
    int i;

    anim_start_startup_animations();
    for (i = 0; i < ref_L09_002F8FD8_00.count; i++) {
        Mob_L09_002F8FD8 *mob = ((MobList_L09_002F8FD8 *)((u8 *)&ref_L09_002F8FD8_00 + i * 4))->mobs[0];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            UpdateEquipmentPieces_us2(mob);
        if (mob != 0 && mob->type == MOBY_CLASS_TV_SCREENS && g_current_map_index != 0x33 && mob->p68 != 0)
            math_store_angle_update_result(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
    }
    if (g_current_map_index == 9 && ref_L09_002F8FD8_00.mode == 1)
        gfx_add_draw_callback_first(gfx_draw_state_nine_pulsing_quad, *(void **)((char *)&ref_L09_002F8FD8_00 + 0x194));
}
