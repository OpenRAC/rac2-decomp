#include "common.h"

/* Incomplete SDA arrays preserve the measured absolute accesses in this G8 unit. */
extern int g_hero_l19_mode[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned int g_frame_counter[] __attribute__((sda));
typedef struct {
    char pad[0x73C];
    unsigned int time;
} GrelbinTimestamp;
extern GrelbinTimestamp g_subtitle_history;
extern char g_sound_state[];
extern int g_pad_held_flags NOT_SDA;
extern unsigned short g_infiltrator_ball_id NOT_SDA;
extern char g_infiltrator_ball_value[] __attribute__((sda));
extern int g_infiltrator_state_flags[] __attribute__((sda));
extern void *g_infiltrator_ball_mobys[] __attribute__((sda));
extern int g_ball_progress_max __attribute__((sda));
extern int g_ball_counter_max __attribute__((sda));
extern unsigned short g_ball_counter_reset __attribute__((sda));
extern unsigned short g_ball_counter_step __attribute__((sda));
extern float g_ball_decay_rate __attribute__((sda));

extern void moby_set_state(char *, int, int);
extern f32 ApproachValue(void *, float, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern s32 snd_set_voice_pitch_bend(int, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastDecTimer(void *);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern int request_end_slot(int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawPathPuzzleHud(void);
extern void moby_set_flag_on(void *);
extern void func_L19_003D3358(void *);
extern void func_L19_003D3CA8(void *);
extern void func_L19_003D3B58(void *);
extern void func_L19_003D4308(void *);
extern void func_L19_003D40C0(void *);
extern void func_L19_003D5218(void *);
extern int func_L19_003D4490(void *);
extern int subtitle_request_voice_line(int, int);

typedef struct {
    char pad[0x40];
    unsigned char kind;
    char gap[0xF];
    short field50, field52, field54, field56;
    float field58;
    short field5c, field5e, field60, field62, field64, field66, field68, field6a;
    char tail[0x10];
    int sound;
} GrelbinState;

/* Per-frame update for the Infiltrator Ball moby. It steps through its states, tracks its charge level and sounds, and removes itself when the sequence ends. */
void infiltrator_ball_update(char *moby)
{
    GrelbinState *vars;
    int i, sound, kind;

    vars = *(GrelbinState **)(moby + 0x68);
    if (g_hero_l19_mode[0] != 7) {
        if (*(unsigned char *)(moby + 0x20))
            moby_set_state(moby, 0, -1);
        return;
    }
    ApproachValue(g_infiltrator_ball_value, 0.0f, 1.0f / 6.0f);
    g_infiltrator_state_flags[0] = 1;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        for (i = 0; i < 52; i++)
            snd_stop_voice(i);
        func_L19_003D3358(moby);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        func_L19_003D3CA8(moby);
        moby_set_state(moby, g_current_map_index[0] == 11 ? 1 : 3, -1);
        break;
    case 1:
        if (g_frame_counter[0] - g_subtitle_history.time > 1080 || !g_subtitle_history.time)
            subtitle_request_voice_line(0xA43, 0x9A);
        else if (g_subtitle_history.time < g_frame_counter[0])
            g_subtitle_history.time = g_frame_counter[0];
        moby_set_state(moby, 3, -1);
        break;
    case 2:
        if (!vars->field68) {
            moby_set_state(moby, 4, -1);
            break;
        }
        if (func_L19_003D4490(moby)) {
            vars->field6a = 1;
            func_L19_003D3B58(moby);
            PlayMobySound(4, 0, moby);
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        func_L19_003D4308(moby);
        if (vars->field56) {
            if (vars->field66 != -1) {
                vars->field52 = (unsigned short)vars->field66;
                vars->field66 = -1;
            } else {
                func_L19_003D40C0(moby);
            }
            kind = vars->kind;
            kind ^= 255;
            if (kind == 0) {
                PlayMobySound(0, 0, moby);
            } else {
                sound = PlayMobySound(1, 0, moby);
                if (sound != -1)
                    snd_set_voice_pitch_bend(sound, FloatToInt(
                        IntToFloat(vars->field5e) / IntToFloat(g_ball_progress_max)
                        * 1024.0f) + 1024);
            }
            if (vars->field5e > vars->field60) {
                vars->field60 = (unsigned short)vars->field5e;
                vars->field68 = (unsigned short)vars->field68 + g_ball_counter_step;
                if (vars->field68 > g_ball_counter_max)
                    vars->field68 = g_ball_counter_max;
            }
            if (vars->field5e == g_ball_progress_max) {
                PlayMobySound(5, 0, moby);
                moby_set_state(moby, 5, -1);
            } else {
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 4:
        if (vars->field56) {
            if (vars->field5c != vars->field50) {
                vars->field52 = (unsigned short)vars->field5c;
                func_L19_003D3B58(moby);
                PlayMobySound(2, 0, moby);
            } else {
                vars->field6a = 0;
                vars->field60 = 0;
                vars->field68 = g_ball_counter_reset;
                moby_set_state(moby, 2, -1);
            }
        } else {
            func_L19_003D4308(moby);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby))
            *(unsigned short *)(moby + 0x96) = 120;
        if (!*(unsigned short *)(moby + 0x96)) {
            g_infiltrator_ball_id = 65535;
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
            goto destroy;
        }
        (*(unsigned short *)(moby + 0x96))--;
        break;
    }
    if (g_pad_held_flags & 16) {
        if (*(unsigned char *)(moby + 0x20) == 5)
            moby_set_flag_on(g_infiltrator_ball_mobys[0]);
    destroy:
        request_end_slot(0, 0);
        moby_mark_spawned(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x20) != 5 && vars->field6a)
        FastDecTimer(&vars->field68);
    if (vars->field6a && vars->field68) {
        char *sound_slot = g_sound_state + vars->sound * 0x70;
        if (*(char **)(sound_slot + 0x88) != moby || !*(unsigned char *)(sound_slot + 0x74))
            vars->sound = PlayMobySound(3, 4, moby);
    } else {
        if (vars->sound != -1) {
            char *sound_slot = g_sound_state + vars->sound * 0x70;
            if (*(char **)(sound_slot + 0x88) == moby && *(unsigned char *)(sound_slot + 0x74))
                snd_stop_voice(vars->sound);
        }
        vars->sound = -1;
    }
    func_L19_003D5218(moby);
    vars->field58 -= g_ball_decay_rate * (1.0f / 60.0f);
    if (vars->field58 < -1.0f)
        vars->field58 += 1.0f;
    gfx_add_draw_callback_first(DrawPathPuzzleHud, moby);
}
