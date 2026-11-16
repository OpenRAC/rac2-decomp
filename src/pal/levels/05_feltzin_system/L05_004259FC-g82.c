#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned char u8;
extern s32 math_fast_float_d(u8 *a0);
extern void FadeToBlack(s32 a0);
extern char *GetLocalizedString(s32 a0);
extern int level_l00_call_module_handler_with_arg_9_pal(s32 a0, s32 a1);
extern void entry_init_all_registered(void);
extern void feltzin_challenge_reset(u8 *a0);
extern s32 g_feltzin_failure_flag __attribute__((sda));

/* Either shuts the level's spawn state down and marks the reset flag, or asks the shared
   gadget lookup for one of the two fixed item strings and forwards it to the dispatcher. */
void func_PAL_L05_00426200(u8 *a0, s32 a1)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (math_fast_float_d(p + 0x48) == 0) {
        if (a1 == 1)
            level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10E1), -1);
        else if (a1 == 3)
            level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10F6), -1);
    } else {
        /* The two stores are written against the retail order: 0x48 first. */
        *(s32 *)(p + 0x48) = 0x7D;
        *(s32 *)(p + 0x44) = 0x1770;
        FadeToBlack(0x19);
        feltzin_challenge_reset(a0);
        entry_init_all_registered();
        g_feltzin_failure_flag = 0;
    }
}

typedef signed short s16;
typedef unsigned int u32;
typedef float f32;
extern void music_Unpause(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag_pal(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_PAL_L05_00425FB0(u8 *a0, s32 a1);
extern void func_PAL_L05_00426200(u8 *a0, s32 a1);
extern s32 g_feltzin_challenge_active __attribute__((sda));
extern s32 g_feltzin_mission_index __attribute__((sda));
typedef struct { s32 count; u8 pad04[12]; s32 active; u8 pad14[24]; s32 reset; } FeltzinState;
extern u8 g_feltzin_challenge_state[];
extern u8 g_feltzin_timer[] __attribute__((section(".sdata")));
extern u8 *g_feltzin_enemy_table;

void func_PAL_L05_00426658(u8 *arg0)
{
    u8 *owner = *(u8 **)(arg0 + 0x68);
    u8 **list;
    u32 count;
    s32 index;
    s32 found;

    math_fast_float_d(g_feltzin_timer);
    if (g_feltzin_challenge_active == 0) {
        ((FeltzinState *)g_feltzin_challenge_state)->reset = 0;
        *(s32 *)g_feltzin_timer = 0x1770;
        *(s32 *)(owner + 0x44) = 0x1770;
        g_feltzin_challenge_active = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        list = level_get_object_list();
        found = level_get_saved_value();
        if (found > 0) {
            count = found;
            do {
                u8 *entry = *list;

                if (*(s16 *)(entry + 0xAA) == 0x10F5) {
                    f32 scale = 64.0f;

                    entry_spawn_list_objects_with_flag_pal(entry, 1);
                    index = ((FeltzinState *)g_feltzin_challenge_state)->count;
                    func_L05_0037CEE0(*list, (u8 *)g_feltzin_enemy_table + (index << 7) + 0x30, scale);
                    index = ((FeltzinState *)g_feltzin_challenge_state)->count;
                    func_L05_0037D608(*list, (u8 *)g_feltzin_enemy_table + (index << 7) + 0x30, scale);
                }
                count--;
                list++;
            } while (count != 0);
        }
    }
    if (((FeltzinState *)g_feltzin_challenge_state)->active == 0 && g_feltzin_mission_index >= 6) {
        func_PAL_L05_00425FB0(arg0, 1);
        return;
    }
    if (math_fast_float_d(owner + 0x44) != 0)
        func_PAL_L05_00426200(arg0, 1);
}
