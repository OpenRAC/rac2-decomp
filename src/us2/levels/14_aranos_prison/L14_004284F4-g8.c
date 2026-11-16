#include "common.h"

/* func_US2_L14_004284F4, the USA v2.00 copy of func_L14_00426F28: the same C, where both messages
 * are looked up by id (func_00288FB8) and func_L00_0030DD70 becomes func_US2_L00_0030EFB8. */

extern void searchlight_draw_glow(char *);

typedef struct PrisonLight {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x10];
    u8 update;           /* 0x31 */
    u8 pad32[2];
    u16 flags;           /* 0x34 */
    u8 pad36[0x32];
    struct PrisonLightState *vars; /* 0x68 */
    u8 pad6C[0x2A];
    u16 frames;          /* 0x96 */
    u32 pending;         /* 0x98 */
} PrisonLight;

/* Its state block: the beam level, the done flag and the sound slot. */
typedef struct PrisonLightState {
    float level;         /* 0x0 */
    int done;            /* 0x4 */
    int sound;           /* 0x8 */
} PrisonLightState;

/* A sound slot as seen from D_00188660 plus 0x70 per slot number. */
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern char g_sound_state[];
extern unsigned char g_screen_mode_flag NOT_SDA;
extern int g_frame_tick_counter;
extern int g_searchlight_period SDATA(D_L14_001B17C0);
extern float g_searchlight_level_scale SDATA(D_L14_001B17C4);
extern float g_searchlight_level_offset SDATA(D_L14_001B17C8);
extern float g_searchlight_approach_rate SDATA(D_L14_001B17D0);
extern float g_searchlight_decay_rate MACRO_ADDR;

extern void moby_set_state(void *self, int state, int mode);
extern void *part_find_owned_effect_slot(void *a0, int a1, int a2);
extern int flag_is_third_pending_set(void *);
extern int PlayMobySound(int a, int b, void *self);
extern void snd_stop_voice(int);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern float ApproachValue(float *, float, float);
extern void moby_mark_spawned(void *a0);
extern char *GetLocalizedString(int);
extern void level_l00_call_module_handler_with_arg_9_us2(void *, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void part_spawn_spark_side(void *);

/* Searchlight (USA v2.00): once triggered it plays its sound and pulses the beam level, then
   fades out and removes itself. */
void searchlight_update_us2(PrisonLight *moby)
{
    PrisonLightState *state = moby->vars;
    float angle, denominator;
    int period, ticks;
    unsigned int counter, previous;
    unsigned short flags;

    switch (moby->state) {
    case 0:
        moby_set_state(moby, 1, -1);
        state->sound = -1;
        break;
    case 1:
        if (g_screen_mode_flag != 1)
            break;
        if (moby->update)
            part_spawn_spark_side(moby);
        if (part_find_owned_effect_slot(moby, 0x10000, 0) || flag_is_third_pending_set(moby)) {
            level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x2F53), 240);
            moby_set_state(moby, 2, -1);
        }
        if (((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner != moby || !((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            state->sound = PlayMobySound(0, 4, moby);
        break;
    case 2:
        ticks = g_frame_tick_counter;
        period = g_searchlight_period;
        angle = IntToFloat(ticks % period);
        denominator = IntToFloat(period);
        angle *= 6.2831855f;
        angle /= denominator;
        angle = math_fast_sin_or_cos_b(angle - 3.1415927f);
        ApproachValue(&state->level, g_searchlight_level_scale * angle + g_searchlight_level_offset, g_searchlight_approach_rate * 0.016666668f);
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, moby);
        counter = moby->frames;
        previous = counter++;
        moby->frames = counter;
        if (previous >= 181)
            state->done = 1;
        if (state->sound != -1 && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner == moby && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            snd_stop_voice(state->sound);
        state->sound = -1;
        if (!g_screen_mode_flag) {
            level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x2F54), 240);
            flags = moby->flags;
            moby->pending = 0;
            flags |= 0x41;
            flags &= 0xefff;
            moby->flags = flags;
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, moby);
        ApproachValue(&state->level, 0.0f, g_searchlight_decay_rate * 0.016666668f);
        if (state->level == 0.0f)
            moby_mark_spawned(moby);
        break;
    }
}
