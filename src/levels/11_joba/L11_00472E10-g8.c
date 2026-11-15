#include "names.h"
/* func_L11_00472E10: per-frame update of a Joba moby tied to a save-data nibble.
   On its first frame it may call func_L00_002B9D60 with a fixed position; within 32 units
   of the hero it keeps a func_L00_0035F5A0 slot (level 11 only), otherwise frees it. When
   func_002B38B8 is true, its level flag is set or its nibble is non-zero, it frees its
   eight child mobys, increments the 3-bit nibble (saturating at 7), releases the slot
   and removes itself.
   Built -O2 -G8 in its own unit. The child loop is a plain index loop over the state
   words, which gives the loop-invariant -1 $s4 and the state pointer $s3 as retail. */

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 D_001A7B2B;
extern int g_current_map_index;
extern u8 D_0019B4A8[];
typedef struct { u8 prefix[0x464]; u8 flags[1]; } LevelFlags;
extern LevelFlags D_L11_0021F8B0;
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern u8 *g_moby_l11_table __attribute__((sda));
extern int moby_is_in_selected_zone(void *);
extern void state_set_flag_one(void);
extern void hero_reset_position_and_direction(float *, float *, int, int);
extern float vec_distance_xy(void *, void *);
extern int snd_start_in_slot(int, int, int);
extern void snd_stop_voice(int);
extern int flag_is_third_pending_set(u8 *);
extern void moby_mark_spawned(void *);

/* Updates a collectible spot (moby class 4478): when it is taken it frees its child mobys, counts it in the save data and removes itself. */
void collectible_spot_update(u8 *moby) {
    float position[4];
    float rotation[4];
    int *childIds = *(int **)(moby + 0x68);
    int count, slot;
    u8 *record;
    u8 *counter;
    if (moby[0x20] == 0) {
        if (D_001A7B2B) {
            u16 id = *(u16 *)(moby + 0xB2);
            int bits;
            if (D_L11_0021F8B0.flags[(short)id] == 0) {
                bits = D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400];
                if (*(u16 *)(moby + 0xB2) & 1) bits = (bits >> 4) & 7;
                else bits &= 7;
                if (bits == 0 && moby_is_in_selected_zone(moby + 0x10)) {
                    state_set_flag_one();
                    position[0] = 363.18f;
                    position[1] = 680.68f;
                    position[2] = 155.73f;
                    rotation[2] = 2.3561947f;
                    rotation[0] = 0;
                    rotation[1] = 0;
                    hero_reset_position_and_direction(position, rotation, 0, 1);
                }
            }
        }
        moby[0x20] = 1;
    }
    if (vec_distance_xy(moby + 0x10, g_hero_position) < 32.0f) {
        if (g_current_map_index == 11) {
            record = g_sound_state + childIds[8] * 0x70;
            if (*(int *)(record + 0x88) != *(int *)(g_hero_position + 0x2210) || record[0x74] == 0)
                childIds[8] = snd_start_in_slot(27, 6, *(int *)(g_hero_position + 0x2210));
        }
    } else {
        slot = childIds[8];
        if (slot != -1) {
            record = g_sound_state + slot * 0x70;
            if (*(int *)(record + 0x88) == *(int *)(g_hero_position + 0x2210) && record[0x74]) snd_stop_voice(slot);
        }
        childIds[8] = -1;
    }
    if (!flag_is_third_pending_set(moby)) {
        u16 id = *(u16 *)(moby + 0xB2);
        int bits;
        if (!D_L11_0021F8B0.flags[(short)id]) {
            bits = D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400];
            if ((*(u16 *)(moby + 0xB2) & 1)
                ? ((bits >> 4) & 7) != 0
                : (bits & 7) != 0) goto cleanup;
            return;
        }
    }
cleanup:
    for (count = 0; count < 8; count++) {
        if (childIds[count] != -1) moby_mark_spawned(g_moby_l11_table + childIds[count] * 0x100);
    }
    {
        int counter_id = *(u16 *)(moby + 0xB2);
        if (counter_id & 1) {
            counter = &D_0019B4A8[((short)counter_id >> 1) + g_current_map_index * 0x400];
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = &D_0019B4A8[((short)counter_id >> 1) + g_current_map_index * 0x400];
            if ((*counter & 7) != 7) ++*counter;
        }
    }
    {
        int final_slot = childIds[8];
        if (final_slot != -1) {
            record = g_sound_state + final_slot * 0x70;
            if (*(int *)(record + 0x88) == *(int *)(g_hero_position + 0x2210) && record[0x74]) snd_stop_voice(final_slot);
        }
        childIds[8] = -1;
        moby_mark_spawned(moby);
    }
}
