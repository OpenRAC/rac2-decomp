#include "common.h"

/* Borrowed player-state prefix; this view never owns an allocation. */
typedef struct {
    u8 reserved00[0x250];
    float parameter250, parameter254, parameter258, parameter25c;
    u8 reserved260[4];
    float parameter264;
    u8 reserved268[0xC24 - 0x268];
    float scale;
    u8 reservedc28[0x1888 - 0xC28];
    void *entry_table;
    u8 reserved188c[0x2294 - 0x188C];
    s32 state;
    u8 reserved2298[0x24F0 - 0x2298];
    u8 special_level;
} LevelPlayerPrefix;

extern LevelPlayerPrefix g_hero_state;
extern s32 g_current_map_index[] __attribute__((sda));
extern s32 g_hero_aim_speed_start[] __attribute__((sda));
extern char g_pickup_entry_table[];
extern void hero_clear_queued_anim(void);
extern s32 hero_l22_set_action(s32, s32);
extern void trail_reset_slots(void);

/* Install this level's player parameters and start the shared subsystems. */
void level_init_player_params(void)
{
    s32 special_level = g_current_map_index[0] == 0x1A;
    LevelPlayerPrefix *state = &g_hero_state;

    state->parameter250 = 0.8f;
    state->parameter254 = 0.7f;
    state->parameter264 = 0.45f;
    state->parameter258 = 0.8f;
    state->parameter25c = 0.7f;
    state->scale = 1.0f;
    state->special_level = special_level;
    g_hero_aim_speed_start[0] = 0;
    state->state = 0;
    hero_clear_queued_anim();
    hero_l22_set_action(0, 1);
    trail_reset_slots();
    state->entry_table = g_pickup_entry_table;
}
