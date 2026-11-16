#include "names.h"
/* func_PAL_L03_00426850, the PAL copy of func_L03_00421398: the same C, where rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L00_0032A530 becomes func_PAL_L00_0032C600. */
#include "common.h"
extern u8 g_effect_descriptor_default[] MACRO_ADDR;
typedef struct { float v[4]; } __attribute__((aligned(16))) VecF720;
extern VecF720 g_collision_start_point, g_camera_pose_buffer;
extern float g_laser_beam_uv_v[] MACRO_ADDR;
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern u8 *part_find_owned_effect_slot(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void fading_effect_update(void);
extern void ScatterObjectPieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, void *);
typedef struct { u8 pad[0x120]; int entries[10]; int count; int active; } EntryGroup;
extern u8 g_barrel_entry_groups[];
typedef struct { u8 header[0x464]; u8 entries[0]; } TriggerTable;
extern TriggerTable g_trigger_l03_flags;
extern u8 g_moby_nibble_table[];
extern int g_current_map_index __attribute__((sda));
typedef struct { unsigned short key; char reserved02[10]; } SelectorRow;
extern SelectorRow g_subtitle_history[];
extern int g_object_group_count;
extern u8 *g_moby_record_base;
extern u16 *g_entity_id_lists[];
extern float g_barrier_piece_speeds[2] __attribute__((sda)), g_barrier_piece_spin[2] __attribute__((sda)), g_barrier_piece_lifetimes[2] __attribute__((sda));
/* A four-state object. State 0 clears the 16 entry groups, then removes the object when its trigger
   entry is set or its 3-bit counter in the level's save bits (high nibble for an odd id, low nibble
   for an even one) is nonzero; otherwise it moves to state 1. State 1 waits for a hit from an object
   of class 0xCFC no lower than half a unit beneath it and sends every entity of its id list to state
   2. States 2 and 3 spawn rows of three explosions at rising heights on a timer, then state 3 raises
   the counter (up to 7), sets subtitle row 60's key to 0xFFFF, scatters the object's pieces and removes it. The row
   pointer is set at the store so the table keeps its own lui/addiu base, as retail has it. */
void endako_exploding_barrier_update_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 pos[16] __attribute__((aligned(16)));
    u8 *hit, *other;
    u16 *cursor;
    int i, j, index, bits;
    u8 *counter;
    SelectorRow *rows;

    if (!state) {
        moby_mark_spawned(moby);
        return;
    }
    switch (moby[0x20]) {
    case 0: {
        int group;

        for (group = 0; group < 16; group++) {
            for (j = 0; j < ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->count; j++)
                if (((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->entries[j])
                    ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->entries[j] = 0;
            ((EntryGroup *)(g_barrel_entry_groups + group * 0x150))->active = 0;
        }
        index = *(s16 *)(moby + 0xB2);
        if (g_trigger_l03_flags.entries[index]) {
            moby_mark_spawned(moby);
        } else {
            bits = g_moby_nibble_table[(index >> 1) + (g_current_map_index << 10)];
            if (*(u16 *)(moby + 0xB2) & 1) {
                if ((bits >> 4) & 7) moby_mark_spawned(moby);
                else moby_set_state(moby, 1, -1);
            } else {
                if (bits & 7) moby_mark_spawned(moby);
                else moby_set_state(moby, 1, -1);
            }
        }
        break;
    }
    case 1:
        hit = part_find_owned_effect_slot(moby, 0x10000, 0);
        if (hit && (other = *(u8 **)(hit + 0x20)) && *(s16 *)(other + 0xAA) == 0xCFC /* moby class 3324 */ &&
            *(float *)(moby + 0x18) <= *(float *)(other + 0x18) + 0.5f) {
            for (cursor = g_entity_id_lists[moby[0x21]];
                 moby[0x21] != 0xFF && moby[0x21] <= g_object_group_count && cursor != 0 &&
                 ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == g_entity_id_lists[moby[0x21]]); cursor++) {
                other = g_moby_record_base + ((*cursor & 0x7FFF) << 8);
                if (!other) break;
                moby_set_state(other, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(int *)(state + 4) = 192;
            for (i = -1; i < 2; i++) {
                vec_local_offset_to_world(moby, pos, (float)(i << 3), -6.0f, 5.0f);
                SpawnExplosion_pal(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 8;
        } else if (math_fast_float_d(state + 4)) {
            for (i = -1; i < 2; i++) {
                vec_local_offset_to_world(moby, pos, (float)(i << 3), -6.0f, 15.0f);
                SpawnExplosion_pal(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 8;
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        if (!math_fast_float_d(state + 4)) break;
        for (i = -1; i < 2; i++) {
            vec_local_offset_to_world(moby, pos, (float)(i << 3), -6.0f, 25.0f);
            SpawnExplosion_pal(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, i == 0, 0);
        }
        if (*(u16 *)(moby + 0xB2) & 1) {
            counter = g_moby_nibble_table + ((*(s16 *)(moby + 0xB2) >> 1) + (g_current_map_index << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = g_moby_nibble_table + ((*(s16 *)(moby + 0xB2) >> 1) + (g_current_map_index << 10));
            if ((*counter & 7) != 7) *counter += 1;
        }
        rows = g_subtitle_history;
        rows[60].key = 0xFFFF;
        if (*(int *)state)
            ScatterObjectPieces_pal(moby, g_barrier_piece_lifetimes, g_barrier_piece_spin, g_barrier_piece_speeds,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, fading_effect_update);
        else
            ScatterObjectPieces_pal(moby, g_barrier_piece_lifetimes, g_barrier_piece_spin, g_barrier_piece_speeds,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, 0);
        moby_mark_spawned(moby);
        break;
    }
}
