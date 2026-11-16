#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void FastVecSub(void *dst, void *a, void *b);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } PrisonLiftVoice;
typedef struct {
    char pad0000[0x80];
    Vec position;                
    char pad0090[0x22B4 - 0x90];
    unsigned char mode;          
} PrisonLiftHero;
extern PrisonLiftHero g_hero_state;
extern char g_sound_state[];
extern int flag_set_first_pending(char *self);
extern int hero_is_current_selected_id(char *);
extern int IsPointInCuboid(void *, int);
extern int snd_is_voice_playing_for_owner(char *, int);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int moby_is_hit_by_player_or_aim(char *);
extern void moby_set_state(void *, int, int);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void FastVecSub(void *dst, void *a, void *b);
extern char g_sound_state[];
extern int flag_set_first_pending(char *self);
extern void gfx_add_draw_callback_third(void (*f)(char *), char *arg);

/* A lift that travels between its start height (0x68) and its target (0x64): state 0 sets it
   up, state 1 waits for the hero (or a trigger) and starts it with its travel sound, states 2
   and 3 ease it up and down and stop the sound on arrival. Riders follow its movement. */
void lift_l14_update_pal(char *moby)
{
    Vec pos, rot, delta;
    char *state = *(char **)(moby + 0x68);
    int sound;

    qcopy(&pos, moby + 0x10);
    qcopy(&rot, moby + 0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(state + 0x5C) |= 1;
        {
            float target = *(float *)(state + 0x64);
            float start = *(float *)(moby + 0x18);
            *(int *)(state + 0x74) = -1;
            *(float *)(state + 0x7C) = 0.0014000001f;
            *(float *)(state + 0x68) = start;
            *(int *)(state + 0x70) = 0;
            *(float *)(state + 0x80) = (start + target) * 0.5f;
        }
        if (*(int *)(state + 0x60) == 0) *(int *)(state + 0x6C) = 0;
        else *(int *)(state + 0x6C) = 1;
        *(unsigned char *)(moby + 0x20) = 1;
        break;
    case 1:
        if (g_hero_state.mode == 1 && *(int *)(state + 0x84)) {
            if (*(int *)(state + 0x6C) == 1) {
                moby_set_state(moby, 2, -1);
                *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            }
        } else if (hero_is_current_selected_id(moby)
                   || ((*(float *)(moby + 0x18) - *(float *)(state + 0x80)) * (g_hero_state.position.f[2] - *(float *)(state + 0x80)) < 0.0f
                       && *(int *)(state + 0x70))) {
            if (*(int *)(state + 0x6C) == 0) {
                moby_set_state(moby, 3, -1);
                if (!snd_is_voice_playing_for_owner(moby, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            } else {
                moby_set_state(moby, 2, -1);
                if (!snd_is_voice_playing_for_owner(moby, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = PlayMobySound(0, 4, moby);
            }
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(state + 0x64) - *(float *)(moby + 0x18) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(g_sound_state + sound * 0x70);
                if (voice->owner == moby && voice->active) snd_stop_voice(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!moby_is_hit_by_player_or_aim(moby)) {
                *(int *)(state + 0x6C) = 0;
                *(float *)(moby + 0x18) = *(float *)(state + 0x64);
                moby_set_state(moby, 1, -1);
            }
        } else math_step_value_toward_target(moby + 0x18, state + 0x78, *(float *)(state + 0x64), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.120000005f);
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(moby + 0x18) - *(float *)(state + 0x68) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(g_sound_state + sound * 0x70);
                if (voice->owner == moby && voice->active) snd_stop_voice(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!moby_is_hit_by_player_or_aim(moby)) {
                *(int *)(state + 0x6C) = 1;
                *(float *)(moby + 0x18) = *(float *)(state + 0x68);
                moby_set_state(moby, 1, -1);
            }
        } else {
            int ridden = hero_is_current_selected_id(moby) != 0;
            int away = IsPointInCuboid(&g_hero_state.position, *(int *)(state + 0x88)) == 0;
            if (ridden || away)
                math_step_value_toward_target(moby + 0x18, state + 0x78, *(float *)(state + 0x68), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.120000005f);
        }
        break;
    }
    FastVecSub(&delta, moby + 0x10, &pos);
    mat_combine_and_store(state + 0x20, &delta, &rot, moby + 0xF0);
}

