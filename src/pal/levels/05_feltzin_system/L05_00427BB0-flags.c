#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern s32 math_fast_float_d(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern void *state_get_stored_pointer_value(u8 *a0);
extern void level_append_object(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 moby_process_collision_hit(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 list_count_ready_objects(u8 *a0);
extern s32 math_random_int_range(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern u8 *func_0037B440(s32 a0);
extern void feltzin_target_spawner_init_pal(u8 *a0);
extern void feltzin_target_spawn_random_pal(u8 *a0);
extern s32 g_sdata_word_unused_b __attribute__((sda));
extern s32 g_sdata_word_unused_c __attribute__((sda));
extern u8 g_feltzin_challenge_state[];
extern u8 g_feltzin_timer[];
extern s32 g_feltzin_mission_index;
extern u8 *g_spot_record_table;
extern u8 g_feltzin_challenge_param_a[];
extern u8 g_feltzin_challenge_param_b[];
extern u8 g_feltzin_challenge_param_c[];
extern u8 g_level_data_block[];
extern u8 *g_level_byte_ptr_table[];
extern u32 g_spawn_list_table[];
extern u8 *g_feltzin_target_mobys[] __attribute__((sda));
extern s32 g_sdata_word_unused_a __attribute__((sda));

/* State 0 waits for func_L00_00367720, then enters state 1. State 1 calls func_L05_0037B538 and, when the
   +0x26C timer of its state expires, picks an entry of the object's id list and passes that object
   (this one when the list has fewer than two entries) to func_PAL_L05_00427D70. */
void feltzin_target_spawner_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    s32 i;
    s32 list_count;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        if (state_get_stored_pointer_value(moby) == 0)
            return;
        feltzin_target_spawner_init_pal(moby);
        if (*(s32 *)(vars + 0x264) == 0)
            return;
        level_append_object(moby, 0, 0, 0);
        return;
    }

    moby_process_collision_hit(moby, 0, 1, 1);
    if (*(s32 *)(vars + 0x264) == 0)
        return;
    if (math_fast_float_d(vars + 0x26C) == 0)
        return;
    target = 0;
    list_count = list_count_ready_objects(moby);

    if (list_count >= 2) {
        s32 count = math_random_int_range(0, list_count - 1);
        u16 *entry_ptr = (u16 *)g_spawn_list_table[moby[0x21]];
        u16 entry;
        i = 0;
        do {
            entry = *entry_ptr;
            list_count = entry & 0x7FFF;
            if (i == count)
                goto found;
            i++;
            entry_ptr++;
        } while ((s16)entry >= 0);
        goto done;
found:
        target = g_feltzin_target_mobys[0] + (list_count << 8);
    } else {
        target = moby;
    }
done:
    if (target != 0)
        feltzin_target_spawn_random_pal(target);
    *(s32 *)(vars + 0x26C) = 0x64;
}
