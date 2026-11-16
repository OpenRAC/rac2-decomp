#include "names.h"
/* func_PAL_L02_003FF858, the PAL copy of func_L02_003FB120: the same C, where the timer reload is
   read as a word and scaled for 50 Hz at the store, and the callee is func_PAL_L02_00405040. */
#include "include_asm.h"
#include "moby_classes.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

extern unsigned char *g_moby_l02_pool[3] __attribute__((sda));

extern u32 g_entity_group_lists[];

extern char g_hero_state[];

extern f32 g_arena_tally_sum_weight __attribute__((sda));

extern f32 g_arena_tally_count_weight __attribute__((sda));

extern f32 g_arena_tally_hero_weight __attribute__((sda));

extern s32 g_arena_tally_reload_time __attribute__((sda));

extern void actor_pick_idle_message_pal(char *, s32, f32, f32);

extern int snd_start_in_slot(s32, s32, s32);

extern s32 FastDecTimer(char *);

#define GROUP(off) (*(s32 *)(state + (off)))

/* Counts the entities of the object's group (state word 0x40) whose state byte (+0x20) is not 0xFE,
   0xFD or 1 and that are of one of six kinds, and sums a float of their private data (+0x20; for
   the first four kinds only when it is positive, and then it also counts them). The count, the sum
   and the hero's value at +0x24CC are kept at +0x60, +0x64 and +0x68; the amount each of them
   dropped by since the last call is handed to func_PAL_L02_00405040 (a drop of the hero's value also
   starts effect 0x17) and added to the int, float and float fields of the record that the index
   at +0x11C names in the four 16-byte records at the start of the state. A weighted sum over the
   four records (1 for the current one down to 1/4 for the oldest, the three fields scaled by
   D_L02_001B121C, 1218 and 1220) goes to +0x6C; when the timer at +0x11E has run out the index
   steps, the new record is cleared and the timer is reloaded from D_L02_001B1214.

   The unit is built with -g (config/cflags.txt) for the single `nop` retail has in front of the
   weight division: the assembler pads a `div.s` that follows a -g line label by two nops when
   the division is a statement of its own, and by one when the statement shares its source line
   with the two before it, as written here. */
void arena_update_enemy_tally_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    u16 *group_start;

    if (GROUP(0x40) != 0xFF) {
        group_start = (u16 *)g_entity_group_lists[GROUP(0x40)];
        if (group_start != 0) {
            u16 *entry_ptr = group_start;
            char *member;
            s32 count = 0;
            s32 kind;
            f32 sum = 0.0f;
            f32 value;

            do {
                member = (char *)g_moby_l02_pool[0] + ((*entry_ptr & 0x7FFF) << 8);
                if (member != 0 && *(u8 *)(member + 0x20) != 0xFE && *(u8 *)(member + 0x20) != 0xFD &&
                    *(u8 *)(member + 0x20) != 1) {
                    kind = *(s16 *)(member + 0xAA);
                    if (kind == 0x9CA || kind == 0xB22 || kind == MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER || kind == MOBY_CLASS_PX6_BLADEBALL) {
                        value = *(f32 *)(*(char **)(member + 0x68) + 0x20);
                        sum += value;
                        if (value > 0.0f)
                            count++;
                    } else if (kind == MOBY_CLASS_CHAINBLADE || kind == MOBY_CLASS_B2_BRAWLER_LEGS) {
                        count++;
                        sum += *(f32 *)(*(char **)(member + 0x68) + 0x20);
                    }
                }
            } while ((s16)*entry_ptr++ >= 0);
            {
                char *hero = g_hero_state;
                s32 i;
                s32 slot;
                s32 slot_sum;
                f32 weight;
                f32 count_avg;
                f32 sum_avg;
                f32 hero_avg;

                actor_pick_idle_message_pal(moby, *(s32 *)(state + 0x60) - count, *(f32 *)(state + 0x64) - sum,
                                  *(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC));
                if (*(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC) > 0.0f)
                    snd_start_in_slot(0x17, 0, 0);
                if (count < *(s32 *)(state + 0x60))
                    *(s32 *)(state + ((s16) * (s16 *)(state + 0x11C) << 4)) +=
                        *(s32 *)(state + 0x60) - count;
                if (sum < *(f32 *)(state + 0x64)) {
                    char *b4 = state + 4;
                    f32 *field_ptr = (f32 *)(b4 + ((s16) * (s16 *)(state + 0x11C) << 4));

                    *field_ptr += *(f32 *)(state + 0x64) - sum;
                }
                if ((f32) * (s32 *)(hero + 0x24CC) < *(f32 *)(state + 0x68)) {
                    char *b8 = state + 8;
                    f32 *field_ptr = (f32 *)(b8 + ((s16) * (s16 *)(state + 0x11C) << 4));

                    *field_ptr += *(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC);
                }
                *(f32 *)(state + 0x64) = sum;
                *(s32 *)(state + 0x60) = count;
                *(f32 *)(state + 0x68) = (f32) * (s32 *)(hero + 0x24CC);
                count_avg = 0.0f;
                sum_avg = 0.0f;
                hero_avg = 0.0f;
                for (i = 4; i > 0; i--) {
                    char *b4;
                    char *b8;

                    slot_sum = *(s16 *)(state + 0x11C) + i; slot = slot_sum - slot_sum / 4 * 4; weight = 1.0f / (5.0f - (f32)i);
                    b4 = state + 4;
                    b8 = state + 8;
                    sum_avg += weight * *(f32 *)(b4 + (slot << 4));
                    count_avg += weight * (f32) * (s32 *)(state + (slot << 4));
                    hero_avg += weight * *(f32 *)(b8 + (slot << 4));
                }
                *(f32 *)(state + 0x6C) =
                    g_arena_tally_sum_weight * sum_avg + g_arena_tally_count_weight * count_avg + g_arena_tally_hero_weight * hero_avg;
                {
                    char *timer = state + 0x11E;

                    if (FastDecTimer(timer)) {
                        char *b4 = state + 4;
                        char *b8 = state + 8;
                        s32 reload = g_arena_tally_reload_time;
                        s32 next_index;
                        s32 new_index;

                        next_index = (s16)(*(u16 *)(state + 0x11C) + 1);
                        new_index = next_index - next_index / 4 * 4;
                        *(s16 *)(state + 0x11C) = new_index;
                        *(s32 *)(state + ((s16)new_index << 4)) = 0;
                        *(s32 *)(b4 + ((s16) * (s16 *)(state + 0x11C) << 4)) = 0;
                        *(s32 *)(b8 + ((s16) * (s16 *)(state + 0x11C) << 4)) = 0;
                        *(u16 *)(state + 0x11E) = ((s32)reload * 5 + 2) / 6;
                    }
                }
            }
        }
    }
}
