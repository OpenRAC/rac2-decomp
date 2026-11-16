#include "include_asm.h"

#include "common.h"
extern char *g_moby_record_base[] __attribute__((sda));
typedef struct {
    u8 header[0x464];
    u8 entries[0];
} TriggerTable;
extern TriggerTable g_trigger_l03_flags, g_trigger_table_state;
extern u8 g_trigger_phase_flags[] __attribute__((sda));
extern u8 g_moby_nibble_table[], g_moby_group_flags[];
extern int g_current_map_index[] __attribute__((sda));
extern char g_hero_position[];
extern int actor_is_in_states_two_to_four(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_set_group_enabled(int, int);
extern int moby_count_group_not_in_state(int, int);
extern void moby_set_state(void *, int, int);
typedef struct {
    int source, handle, active, first, second;
    int handles[4];
    int actions[4];
    int pad[3];
    int phase;
} TriggerState;

/* Runs the two trigger phases and records completion in the level tables. */
void trigger_phase_update_pal(char *obj)
{
    TriggerState *state  =  *(TriggerState **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0: {
        u16 id = *(u16 *)(obj + 0xb2);
        int bits;
        if (g_trigger_l03_flags.entries[(s16)id] != 0) goto enabled;
        bits = g_moby_nibble_table[((s16)id>>1)+(g_current_map_index[0]<<10)];
        if ((id&1) ? ((bits>>4)&7) : (bits&7)) {
        enabled:
            moby_set_group_enabled(state->first, 1);
            moby_set_group_enabled(state->second, 1);
            moby_set_state(obj, 5, -1);
        } else moby_set_state(obj, 1, -1);
        break;
    }
    case 1: {
        int yes = 0;
        if (state->source != -1 && actor_is_in_states_two_to_four(g_moby_record_base[0]+state->source*256)) yes = 1;
        else if (state->handle != -1 && IsPointInCuboid(g_hero_position, state->handle)) yes = 1;
        else if (state->active != -1) yes = moby_count_group_not_in_state(state->active, -1) == 0;
        if (yes) moby_set_state(obj, 2, -1);
        break;
    }
    case 2:
        if (*(u16 *)(obj + 0x96) >= 26) {
            moby_set_state(obj, 3, -1);
            if (state->phase == 0) moby_set_group_enabled(state->first, 1);
            else moby_set_group_enabled(state->second, 1);
        }
        break;
    case 3: {
        int *p, *q; int i;
        if (*(u16 *)(obj + 0x96) >= 26) {
            if (state->phase) {
                int invalid = -1;
                q = state->actions; p = state->handles;
                i = 3;
                do {
                    if (*p != invalid) moby_set_group_enabled(*q, 1);
                    q++;
                    i--;
                    p++;
                } while (i >= 0);
                g_trigger_table_state.entries[*(short *)(obj + 0xb2)] = *(u8 *)(obj + 0xb0) + 2;
                { u32 idx = *(u8 *)(obj + 0xb0);
                if (idx == 255 || (!(g_trigger_phase_flags[(u8)idx]&0x80) && (g_moby_group_flags[(u8)idx+(g_current_map_index[0]<<4)]&0x80)))
                    g_trigger_l03_flags.entries[*(short *)(obj + 0xb2)] = idx + 2; }
                moby_set_state(obj, 5, -1);
            } else {
                int *handles = state->handles;
                int j;
                for (j = 3;j >= 0;j--, handles++) if (*handles != -1) moby_set_group_enabled(*handles, 1);
                moby_set_state(obj, 4, -1);
            }
        }
        break;
    }
    case 4: {
        int yes = 1, i; int invalid = -1; int *p = state->handles;
        for (i = 3;i >= 0;i--, p++) if (*p != invalid && moby_count_group_not_in_state(*p, -1)) yes = 0;
        if (yes) { state->phase++; moby_set_state(obj, 2, -1); }
        break;
    }
    }
    (*(u16 *)(obj + 0x96))++;
}
