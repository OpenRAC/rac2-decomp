/* func_PAL_L14_0042C5AC, the PAL copy of func_L14_00426F28: the same C, where the two sound names become
   text lookups (func_00288FB8(0xFE0)/(0xFE1)), 240 becomes 200, 181 becomes 151, the 1/60 step becomes
   0.020000001f, the period is scaled by 5/6 and read before the tick counter, and the callee is PAL's own. */

#include "common.h"

/* The light object: state byte, an update flag, the visibility flags, its state block,
   a frame counter and a word cleared when it shuts down. */
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
extern unsigned char D_0018C0D4 NOT_SDA;
extern int D_L14_001B20C8;
extern int D_L14_001B17C0 SDATA(D_L14_001B17C0);
extern float D_L14_001B17C4 SDATA(D_L14_001B17C4);
extern float D_L14_001B17C8 SDATA(D_L14_001B17C8);
extern float D_L14_001B17D0 SDATA(D_L14_001B17D0);
extern float D_L14_001B17D4 MACRO_ADDR;

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
extern void func_PAL_L00_0030FBC0(char *, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void func_PAL_L14_0042C988(void *);
extern void searchlight_draw_glow(char *a0);

/* A prison searchlight: waits for the alarm, sweeps while it lasts, then fades out. */
void func_PAL_L14_0042C5AC(PrisonLight *object)
{
    PrisonLightState *state = object->vars;
    float angle, denominator;
    int period, ticks;
    unsigned int counter, previous;
    unsigned short flags;

    switch (object->state) {
    case 0:
        moby_set_state(object, 1, -1);
        state->sound = -1;
        break;
    case 1:
        if (D_0018C0D4 != 1)
            break;
        if (object->update)
            func_PAL_L14_0042C988(object);
        if (part_find_owned_effect_slot(object, 0x10000, 0) || flag_is_third_pending_set(object)) {
            func_PAL_L00_0030FBC0(GetLocalizedString(0xFE0), 200);
            moby_set_state(object, 2, -1);
        }
        if (((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            state->sound = PlayMobySound(0, 4, object);
        break;
    case 2:
        period = (D_L14_001B17C0 * 5 + 2) / 6;
        ticks = D_L14_001B20C8;
        angle = IntToFloat(ticks % period);
        denominator = IntToFloat(period);
        angle *= 6.2831855f;
        angle /= denominator;
        angle = math_fast_sin_or_cos_b(angle - 3.1415927f);
        ApproachValue(&state->level, D_L14_001B17C4 * angle + D_L14_001B17C8, D_L14_001B17D0 * 0.020000001f);
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, object);
        counter = object->frames;
        previous = counter++;
        object->frames = counter;
        if (previous >= 151)
            state->done = 1;
        if (state->sound != -1 && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            snd_stop_voice(state->sound);
        state->sound = -1;
        if (!D_0018C0D4) {
            func_PAL_L00_0030FBC0(GetLocalizedString(0xFE1), 200);
            flags = object->flags;
            object->pending = 0;
            flags |= 0x41;
            flags &= 0xefff;
            object->flags = flags;
            moby_set_state(object, 3, -1);
        }
        break;
    case 3:
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, object);
        ApproachValue(&state->level, 0.0f, D_L14_001B17D4 * 0.020000001f);
        if (state->level == 0.0f)
            moby_mark_spawned(object);
        break;
    }
}
