#include "names.h"
/* Seven-state controller of a Dobbo level object.  It has a unit of its own for its switch
 * table.  It reads the entity table in both of retail's forms: $gp through the sda name, and
 * the tied absolute macro load (lui $r; lw $r) through the MACRO_ADDR alias. */
#include "common.h"
extern char *g_moby_record_table __attribute__((sda));
extern char *D_L09_001B285C_1 MACRO_ADDR;
extern char *g_dobbo_point_table __attribute__((sda));
extern s32 g_frame_l09_counter;
extern s16 g_current_music_id[] __attribute__((nosda));
extern s32 g_current_map_index MACRO_ADDR;
extern u8 g_game_flag_table[];
extern s32 g_subtitle_pending_word __attribute__((nosda));
extern s32 g_controller_active __attribute__((nosda));
extern s32 g_game_mode __attribute__((nosda));
extern char g_hero_position[];
typedef struct { u8 pad[0x464]; u8 active[0]; } DobboFlags;
extern DobboFlags g_dobbo_flags;
extern u8 g_moby_nibble_table[][0x400];
extern s32 dobbo_check_hero_trigger(s32, s32);
extern void dobbo_set_linked_state(s32, u8);
extern void dobbo_activate_linked_if_valid(s32, s32, s32, s32);
extern void dobbo_release_linked(char *);
extern s32 dobbo_release_linked_if_ready(char *);
extern void dobbo_update_item_indicator(char *);
extern void moby_mark_spawned(char *);
extern void state_set_flag_one(void);
extern void hero_reset_position_and_direction(char *, char *, s32, s32);
extern void moby_set_flags_by_index(s32, s32, s32, s32);
extern int MemcardSave(s32, s32);
extern void moby_set_state(char *, s32, s32);
extern s32 flag_set_first_pending(char *);
extern void script_queue_keyed_request(s32, s32);
extern s32 coll_point_inside_region(char *, s32);
#define FIELD(p,o) (*(s32 *)((p)+(o)))
/* Per-frame update of the Dobbo switch controller (moby class 3485): it turns linked lights, doors and lifts on and off as the hero uses it. */
void switch_controller_update(u8 *obj)
{
    char *data = *(char **)(obj + 0x68);
    s32 mode, bits;
    u32 id;
    s32 index2;
    s32 index4;
    s32 index5;
    s32 index6;
    s32 index7;
    s32 index8;
    s32 index10;
    s32 index11;
    s32 index12;
    obj[0x30] = 0xFF;
    switch ((u8)obj[0x20]) {
    case 0:
        if (g_frame_l09_counter == 0) {
            index2 = FIELD(data,0x58);
            if (index2 != -1) {
                mode = (u8)g_moby_record_table[(index2 << 8)+0x20];
                if (mode != 254) {
                    if (mode == 253) goto skip58;
                    if (dobbo_check_hero_trigger(FIELD(data,0xC),-1)) {
                        moby_mark_spawned(g_moby_record_table + (FIELD(data,0x58) << 8));
                        FIELD(data,0x58) = -1;
                    }
                }
            }
skip58:
            if ((u8)g_game_flag_table[0x2D] && FIELD(data,0x60) != -1) {
                char *other;
                state_set_flag_one();
                other = D_L09_001B285C_1;
                other += FIELD(data,0x60) << 8;
                hero_reset_position_and_direction(other+0x10,other+0xF0,0,1);
                g_game_flag_table[0x2D] = 0;
            }
            if ((u8)g_game_flag_table[0x1E]) {
                index4 = FIELD(data,0x40);
                if (index4 != -1 && FIELD(data,0x48) != -1)
                    FIELD(*(char **)(g_moby_record_table+(index4<<8)+0x68),0) = FIELD(data,0x48);
            }
            index5 = FIELD(data,0x50);
            if (index5 == -1) goto inactive;
            {
                id = *(u16 *)((index5<<8) + (u32)g_moby_record_table + 0xB2);
                if (g_dobbo_flags.active[(s16)id]) goto active;
                bits = g_moby_nibble_table[g_current_map_index][(s16)id>>1];
                if (!((id & 1) ? ((bits>>4)&7) : (bits&7))) goto inactive;
active:
    moby_set_flags_by_index(FIELD(data,0x4C),1,1,1);
                dobbo_release_linked(obj);
                goto after_active;
inactive:
    moby_set_flags_by_index(FIELD(data,0x4C),0,0,0);
after_active:
                dobbo_release_linked_if_ready(obj);
            }
            if (!(u8)g_game_flag_table[0xA3]) {
                g_game_flag_table[0xA3] = 1;
                MemcardSave(0,-1);
            }
        }
        if (g_frame_l09_counter < 6) break;
        dobbo_activate_linked_if_valid(FIELD(data,0x30),0,0,-1);
        dobbo_activate_linked_if_valid(FIELD(data,0x34),0,0,-1);
        dobbo_activate_linked_if_valid(FIELD(data,0x38),0,-1,-1);
        dobbo_activate_linked_if_valid(FIELD(data,0x3C),0,0,0);
        moby_set_flags_by_index(FIELD(data,0x50),0,0,0);
        moby_set_flags_by_index(FIELD(data,0x54),0,0,-1);
        moby_set_flags_by_index(FIELD(data,0x58),0,0,0);
        moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
        moby_set_flags_by_index(FIELD(data,0x68),0,0,0);
        moby_set_flags_by_index(FIELD(data,0x64),0,0,-1);
        if (dobbo_check_hero_trigger(FIELD(data,0),FIELD(data,0x20))) {
            dobbo_set_linked_state(FIELD(data,0x24),2);
            moby_set_flags_by_index(FIELD(data,0x50),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x54),0,0,-1);
            moby_set_flags_by_index(FIELD(data,0x58),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
            moby_set_flags_by_index(FIELD(data,0x4C),0,0,0);
            moby_set_state(obj,1,-1);
        } else if (dobbo_check_hero_trigger(FIELD(data,4),FIELD(data,0x24))) {
            dobbo_set_linked_state(FIELD(data,0x20),2);
            moby_set_flags_by_index(FIELD(data,0x50),1,1,1);
            moby_set_flags_by_index(FIELD(data,0x54),1,1,-1);
            moby_set_flags_by_index(FIELD(data,0x58),1,1,1);
            index6 = FIELD(data,0x54);
            if (index6 != -1 && (u8)g_moby_record_table[(index6<<8)+0x20] >= 3) {
                moby_set_flags_by_index(FIELD(data,0x5C),1,1,-1);
            } else {
                moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
            }
            if (!dobbo_release_linked_if_ready(obj) && g_subtitle_pending_word < 0) {
                moby_set_flags_by_index(FIELD(data,0x68),1,1,1);
                moby_set_flags_by_index(FIELD(data,0x64),1,-1,-1);
            }
            moby_set_state(obj,2,-1);
        } else if (coll_point_inside_region(g_hero_position,FIELD(data,0x10))) {
            dobbo_set_linked_state(FIELD(data,0x20),2);
            moby_set_flags_by_index(FIELD(data,0x50),1,1,1);
            moby_set_flags_by_index(FIELD(data,0x54),1,1,-1);
            moby_set_flags_by_index(FIELD(data,0x58),1,1,1);
            moby_set_flags_by_index(FIELD(data,0x5C),1,1,-1);
            if (!dobbo_release_linked_if_ready(obj) && g_subtitle_pending_word < 0) {
                moby_set_flags_by_index(FIELD(data,0x68),1,1,1);
                moby_set_flags_by_index(FIELD(data,0x64),1,-1,-1);
            }
            moby_set_state(obj,4,-1);
        }
        dobbo_update_item_indicator(obj);
        break;
    case 1:
        if (flag_set_first_pending(obj) && g_current_music_id[0] != FIELD(data,0x78))
            script_queue_keyed_request(FIELD(data,0x78),FIELD(data,0x74));
        if (!dobbo_check_hero_trigger(FIELD(data,4),FIELD(data,0x24))) break;
        dobbo_set_linked_state(FIELD(data,0x20),2);
        moby_set_flags_by_index(FIELD(data,0x50),1,1,1);
        moby_set_flags_by_index(FIELD(data,0x54),1,1,-1);
        moby_set_flags_by_index(FIELD(data,0x58),1,1,1);
        moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
        index7 = FIELD(data,0x58);
        if (index7 == -1 || (u8)g_moby_record_table[(index7<<8)+0x20] == 254 ||
            (u8)g_moby_record_table[(index7<<8)+0x20] == 253) {
            dobbo_activate_linked_if_valid(FIELD(data,0x3C),1,1,1);
            FIELD(data,0x58) = -1;
        }
        moby_set_state(obj,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(obj) && g_current_music_id[0] != FIELD(data,0x70))
            script_queue_keyed_request(FIELD(data,0x70),FIELD(data,0x74));
        index8 = FIELD(data,0x58);
        if (index8 == -1) goto after_release;
        mode = (u8)g_moby_record_table[(index8<<8)+0x20];
        if (mode == 254) goto release;
        if (mode != 253) goto after_release;
release:
        dobbo_activate_linked_if_valid(FIELD(data,0x3C),1,1,1);
        FIELD(data,0x58) = -1;
after_release:
        if (dobbo_check_hero_trigger(FIELD(data,0),FIELD(data,0x20))) {
            dobbo_set_linked_state(FIELD(data,0x24),2);
            moby_set_flags_by_index(FIELD(data,0x50),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x54),0,0,-1);
            moby_set_flags_by_index(FIELD(data,0x58),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
            moby_set_flags_by_index(FIELD(data,0x4C),0,0,0);
            moby_set_state(obj,1,-1);
        } else if (g_controller_active && dobbo_check_hero_trigger(FIELD(data,0xC),-1)) {
            dobbo_activate_linked_if_valid(FIELD(data,0x30),1,1,-1);
            g_game_flag_table[0x1E] = 1;
            index10 = FIELD(data,0x40);
            if (index10 != -1 && FIELD(data,0x48) != -1)
                FIELD(*(char **)(g_moby_record_table+(index10<<8)+0x68),0) = FIELD(data,0x48);
            dobbo_update_item_indicator(obj);
            moby_set_state(obj,3,-1);
        }
        if ((u32)((u8)obj[0x20] - 1) < 2) break;
        /* State 3's common follow-up is also reached after the transition. */
    case 3:
        index11 = FIELD(data,0x54);
        if (index11 != -1 && (u8)g_moby_record_table[(index11<<8)+0x20] >= 3)
            moby_set_flags_by_index(FIELD(data,0x5C),1,1,-1);
        if (!dobbo_release_linked_if_ready(obj) && g_subtitle_pending_word < 0) {
            moby_set_flags_by_index(FIELD(data,0x68),1,1,1);
            moby_set_flags_by_index(FIELD(data,0x64),1,-1,-1);
        }
        if (!dobbo_check_hero_trigger(FIELD(data,0xC),-1)) goto reset_to_2;
        if (g_game_mode == 0x31) {
            dobbo_update_item_indicator(obj);
            dobbo_set_linked_state(FIELD(data,0x24),2);
            dobbo_activate_linked_if_valid(FIELD(data,0x3C),0,0,0);
            moby_set_state(obj,4,-1);
        }
        break;
    case 4:
        if (dobbo_check_hero_trigger(FIELD(data,0x10),-1)) {
            dobbo_activate_linked_if_valid(FIELD(data,0x30),0,0,-1);
            dobbo_release_linked_if_ready(obj);
            moby_set_state(obj,5,-1);
        }
        break;
    case 5:
        dobbo_update_item_indicator(obj);
        if (!dobbo_check_hero_trigger(FIELD(data,0xC),-1)) break;
        dobbo_release_linked(obj);
        dobbo_set_linked_state(FIELD(data,0x24),0);
        index12 = FIELD(data,0x6C);
        if (index12 != -1) {
            char *other = g_dobbo_point_table + (index12<<7);
            hero_reset_position_and_direction(other+0x30,other+0x70,0,0);
        }
        dobbo_release_linked_if_ready(obj);
        moby_set_state(obj,6,-1);
        break;
    case 6:
        dobbo_release_linked_if_ready(obj);
        if (dobbo_check_hero_trigger(FIELD(data,0),FIELD(data,0x20))) {
            moby_set_flags_by_index(FIELD(data,0x50),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x54),0,0,-1);
            moby_set_flags_by_index(FIELD(data,0x58),0,0,0);
            moby_set_flags_by_index(FIELD(data,0x5C),0,0,-1);
            dobbo_set_linked_state(FIELD(data,0x24),2);
            moby_set_state(obj,1,-1);
        } else if (!dobbo_check_hero_trigger(FIELD(data,0xC),-1)) {
reset_to_2:
            dobbo_set_linked_state(FIELD(data,0x24),0);
            moby_set_state(obj,2,-1);
        } else if (g_game_mode == 0x31) {
            dobbo_update_item_indicator(obj);
            dobbo_set_linked_state(FIELD(data,0x24),2);
            dobbo_activate_linked_if_valid(FIELD(data,0x3C),0,0,0);
            moby_set_state(obj,4,-1);
        }
        break;
    }
}
