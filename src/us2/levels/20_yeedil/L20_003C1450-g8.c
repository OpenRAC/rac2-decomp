#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_mark_table_entry_flagged(u8);
extern float IntToFloat(int);
extern int math_fast_float_d(void *);
extern void group_raise_from_saved_heights(void *);
extern void hero_exit_vehicle_mode_us2(void *);
extern void level_capture_checkpoint_state(void *, void *);
extern void group_lower_save_heights(void *);
extern void cam_lock_entry(s32);
extern char *g_group_l20_member_table;
extern u8 g_moby_nibble_table[] NOT_SDA;
extern struct { u8 header[0x464]; u8 collected[0]; } g_collected_l20_flags_2;
extern char g_hero_state[];
extern s32 g_current_map_index[] __attribute__((sda));
typedef struct {
    s32 group, timer;
    f32 inverseDuration;
    s32 target, parameter;
    u8 expectedState, flag15, exitVehicle, flag17;
} ScriptState;
typedef struct {
    u8 pad00[0x20];
    u8 mode;
    u8 pad21[0x68 - 0x21];
    ScriptState *script;
    u8 pad6C[0xB0 - 0x6C];
    u8 channel, padB1;
    u16 uid;
} ScriptMoby;

void scripted_pickup_update_us2(ScriptMoby *self) {
    ScriptState *state = self->script;

    switch (self->mode) {
    case 0: {
        u16 uid;
        int bits;

        if (state->target < 0 || state->group < 0 || state->parameter < 0) {
            moby_mark_spawned(self);
            break;
        }
        uid = self->uid;
        if (g_collected_l20_flags_2.collected[(s16)uid]) {
            self->mode = 3;
            break;
        }
        bits = g_moby_nibble_table[((s16)uid >> 1) + (g_current_map_index[0] << 10)];
        if ((uid & 1) ? (bits >> 4) & 7 : bits & 7) {
            self->mode = 3;
            break;
        }
        self->mode = 1;
        group_lower_save_heights(self);
        break;
    }
    case 1: {
        u16 uid;

        if (*(u8 *)((state->target << 8) + (s32)g_group_l20_member_table + 0x20) == state->expectedState) {
            uid = self->uid;
        } else {
            if (!state->flag15 || !flag_is_third_pending_set(self))
                break;
            uid = self->uid;
        }
        if (uid & 1) {
            u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));

            if (((*entry >> 4) & 7) != 7)
                *entry += 0x10;
        } else {
            u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));

            if ((*entry & 7) != 7)
                ++*entry;
        }
        if (state->flag17)
            moby_mark_table_entry_flagged(self->channel);
        self->mode = 2;
        state->timer = 120;
        {
            float duration = IntToFloat(120);
            state->inverseDuration = 1.0f / duration;
        }
        cam_lock_entry(state->parameter);
        break;
    }
    case 2:
        math_fast_float_d(&state->timer);
        group_raise_from_saved_heights(self);
        if (state->timer == 0) {
            char *hero = g_hero_state;

            if (*(s32 *)(hero + 0x2294) == 0x6F)
                break;
            if (state->exitVehicle)
                hero_exit_vehicle_mode_us2(0);
            if (state->flag17)
                level_capture_checkpoint_state(hero + 0x80, hero + 0x90);
            self->mode = 3;
        }
        break;
    }
}
