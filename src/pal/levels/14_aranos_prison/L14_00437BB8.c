#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int math_fast_float_d(void *);
extern int flag_set_first_pending(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);

void func_PAL_L14_00437BB8(char *object)
{
    int *state = *(int **)(object + 0x68);
    switch ((unsigned char)object[0x20]) {
    case 0:
        state[10] += 63;
        state[11] += 63;
        state[12] += 63;
        state[13] += 63;
        state[14] += 63;
        state[15] = 10;
        state[16] = -1;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        moby_set_state(object, math_random_int_range(2, 3), -1);
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->active)
                snd_stop_voice(state[16]);
            state[16] = -1;
            state[3] = ((s32)(math_random_int_range(state[0], state[1])) * 5 + 2) / 6;
        }
        if (((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->active)
            state[16] = prisonStartSound(0, 4, object);
        if (math_fast_float_d(state + 3))
            moby_set_state(object, 1, -1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->active)
                snd_stop_voice(state[16]);
            state[16] = -1;
            state[3] = ((s32)(math_random_int_range(state[0], state[1])) * 5 + 2) / 6;
        }
        if (((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + state[16] * 112))->active)
            state[16] = prisonStartSound(1, 4, object);
        if (math_fast_float_d(state + 3))
            moby_set_state(object, 1, -1);
        break;
    }
    gfx_add_draw_callback_third(gfx_draw_scrolling_surface_quad, object);
}

