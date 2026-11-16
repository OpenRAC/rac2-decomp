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
/* Per-frame update of moby class 2482. */
void trigger_phase_update(char *obj)
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
        int triggered = 0;
        if (state->source != -1 && actor_is_in_states_two_to_four(g_moby_record_base[0]+state->source*256)) triggered = 1;
        else if (state->handle != -1 && IsPointInCuboid(g_hero_position, state->handle)) triggered = 1;
        else if (state->active != -1) triggered = moby_count_group_not_in_state(state->active, -1) == 0;
        if (triggered) moby_set_state(obj, 2, -1);
        break;
    }
    case 2:
        if (*(u16 *)(obj + 0x96) >= 31) {
            moby_set_state(obj, 3, -1);
            if (state->phase == 0) moby_set_group_enabled(state->first, 1);
            else moby_set_group_enabled(state->second, 1);
        }
        break;
    case 3: {
        int *handle_ptr, *action_ptr; int i;
        if (*(u16 *)(obj + 0x96) >= 31) {
            if (state->phase) {
                int invalid = -1;
                action_ptr = state->actions; handle_ptr = state->handles;
                i = 3;
                do {
                    if (*handle_ptr != invalid) moby_set_group_enabled(*action_ptr, 1);
                    action_ptr++;
                    i--;
                    handle_ptr++;
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
        int triggered = 1, i; int invalid = -1; int *handle_ptr = state->handles;
        for (i = 3;i >= 0;i--, handle_ptr++) if (*handle_ptr != invalid && moby_count_group_not_in_state(*handle_ptr, -1)) triggered = 0;
        if (triggered) { state->phase++; moby_set_state(obj, 2, -1); }
        break;
    }
    }
    (*(u16 *)(obj + 0x96))++;
}
