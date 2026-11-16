#include "include_asm.h"

#include "common.h"
extern u8 g_hero_prev_position[];
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern u8 g_hero_l12_state_records[];
extern s32 func_315148();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern s32 g_moby_list_start __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *g_moby_l12_group_lists[];
extern s32 g_current_map_index __attribute__((sda));
extern s32 GetFirstMobyInGroup(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_unlocked_item_flags MACRO_ADDR;
extern u32 g_object_state_flags_f, g_pad_held_flags;
extern u8 g_requirement_queue[];
extern u8 *CreateMoby(int);
extern void moby_set_state(void *, s32, s32);
extern char *GetLocalizedString(int);
extern s32 *g_path_zone_table[];
extern s32 point_in_path_xy(void *, void *, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);

u8 *squirrel_alert_for_object_pal(s32 index, u8 *obj)
{
    u16 *list = g_moby_l12_group_lists[index];
    u16 *entry;
    u8 *found = 0;

    if (list == 0) {
        return 0;
    }
    entry = list;
    do {
        u8 *rec = (u8 *)g_moby_list_start + (*entry & 0x7FFF) * 0x100;

        if (*(s16 *)(rec + 0xAA) == 0xFB4) {
            u8 *vars = *(u8 **)(rec + 0x68);
            s32 *zone = g_path_zone_table[*(s32 *)(vars + 0x138)];

            if (point_in_path_xy(obj + 0x10, zone + 4, zone[0]) != 0) {
                if (rec[0x20] == 9) {
                    *(u16 *)(rec + 0x34) = (*(u16 *)(rec + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(rec + 0x98) = *(s32 *)(*(u8 **)(rec + 0x24) + 0x10);
                    if (rec[0x43] != 5) {
                        func_PAL_002A7E68(rec, 5, 0, 8);
                    }
                    moby_set_state(rec, 10, -1);
                } else if (rec != 0 && rec[0x20] != 0xFE && rec[0x20] != 0xFD) {
                    moby_set_state(rec, 11, 4);
                    if (rec[0x43] != 7) {
                        func_PAL_002A7E68(rec, 7, 0, 0x11);
                    }
                }
                *(u8 **)(vars + 0x374) = obj;
                found = rec;
                break;
            }
        }
    } while ((s16)*entry++ >= 0);
    return found;
}

