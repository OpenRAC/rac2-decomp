#include "common.h"

/* func_PAL_L09_0041FC4C, the PAL copy of func_L09_0041A700: the same C, where 0.10472f becomes 0.12566373f. */

extern int PlayMobySound(int, int, void *);
extern float vec_distance_xy(void *, void *);
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);

typedef struct {
    char pad0[0x33C];
    char *standing;
    char pad340[0x34E - 0x340];
    short busy;
} TriggerPlayer;
extern TriggerPlayer g_hero_state;
extern int g_current_map_index __attribute__((sda));
/* Flag bytes indexed by level * 16 + owner; 3-bit counters indexed by level * 1024, two per byte. */
extern u8 g_moby_group_flags[];
extern u8 g_moby_nibble_table[];
typedef struct { u8 pad[0x464]; u8 spent[0]; } TriggerCellFlags;
extern TriggerCellFlags g_dobbo_flags;
extern char *g_floor_l09_switch_player;
extern char *g_floor_l09_switch_player_2;

typedef struct TriggerState { float angle; int enabled; } TriggerState;
typedef struct {
    char pad00[0x10];
    float position[4];
    u8 status;
    char pad21[0x68 - 0x21];
    TriggerState *state;
    char pad6C[0x78 - 0x6C];
    unsigned int color;
    char pad7C[0xB0 - 0x7C];
    u8 owner;
    char padB1;
    u16 id;
    char padB4[0xBC - 0xB4];
    u8 activated;
} TriggerObject;

/* Updates a floor switch: pulses its colour, then lights up and counts a press when the player steps on it or an ally gets close (PAL: 6 degree pulse step). */
void floor_l09_switch_update_pal(TriggerObject *trigger)
{
    TriggerState *trigger_state = trigger->state;
    int shade, level;
    int green, red;
    char *player;
    float pos[4] __attribute__((aligned(16)));

    switch (trigger->status) {
    case 0:
        trigger_state->angle = math_random_angle();
        trigger->status = 1;
        trigger->position[2] -= 0.35f;
        break;
    case 1:
        /* Pulse the colour: the angle advances 6 degrees per update. */
        trigger_state->angle = FastAddRotations(trigger_state->angle, 0.12566373f);
        shade = FloatToInt((math_fast_sin_or_cos_b(trigger_state->angle) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        green = (shade << 8) | (int)0x80000000;
        red = shade << 16;
        trigger->color = (red | green) | shade;
        if (g_hero_state.standing != (char *)trigger || g_hero_state.busy) {
            /* Loaded only on this path: reorg moves it into the bne delay slot. */
            level = g_current_map_index;
            if (!(g_moby_group_flags[trigger->owner + level * 16] & 0x80) || trigger_state->enabled) {
                int id;
                if (!trigger_state->enabled) return;
                id = trigger->id;
                if (!g_dobbo_flags.spent[(short)id]) {
                    int count = g_moby_nibble_table[((short)id >> 1) + (level << 10)];
                    if (id & 1) {
                        if (((count >> 4) & 7) != 0) goto activate;
                        goto proximity;
                    } else if (!(count & 7)) goto proximity;
                }
            }
        }
activate:
        {
            int id;
            trigger->status = 2;
            trigger->activated = 1;
            trigger->color = 0x80208020;
            PlayMobySound(0, 0, trigger);
            id = trigger->id;
            if (id & 1) {
                u8 *counts = &g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
                if (((*counts >> 4) & 7) != 7) *counts += 16;
            } else {
                u8 *counts = &g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
                if ((*counts & 7) != 7) ++*counts;
            }
        }
proximity:
        if (trigger_state->enabled) {
            player = g_floor_l09_switch_player;
            if (!player) {
                player = g_floor_l09_switch_player_2;
                if (!player) return;
            }
            /* Retail fills this raised copy but measures from the position itself. */
            qcopy(pos, trigger->position);
            pos[2] += 0.35f;
            if (vec_distance_xy(trigger->position, player + 0x10) < 0.5f) {
                int id = trigger->id;
                if (id & 1) {
                    u8 *counts = &g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
                    if (((*counts >> 4) & 7) != 7) *counts += 16;
                } else {
                    u8 *counts = &g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
                    if ((*counts & 7) != 7) ++*counts;
                }
                trigger->status = 2;
                trigger->activated = 1;
                trigger->color = 0x80208020;
                PlayMobySound(0, 0, trigger);
            }
        }
        break;
    }
}
