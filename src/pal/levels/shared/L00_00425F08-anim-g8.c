/* func_PAL_L00_00425F08, the PAL copy of func_L00_00420C38: the same C, where the tuning values are
   ints, the blend timers read from them are scaled to 50 Hz, and the h34C threshold 0x37 becomes 0x2E.
   In its own unit: it reads the level's tuning values through $gp and is built
   with -g. The state byte has no local: every test re-reads s->state, gcse's reaching register for
   those loads is what stays in $a1 unmasked, and each compare keeps its own andi. */
#include "common.h"

/* The parts of the hero this state machine reads. */
typedef struct {
    char pad0[0x34C];
    short h34C;                   /* 0x34C */
    char pad34E[0x49E - 0x34E];
    u8 b49E;                      /* 0x49E */
    char pad49F[0x2294 - 0x49F];
    int state;                    /* 0x2294 */
    char pad2298[4];
    int ctrl;                     /* 0x229C */
} HeroAnim;

/* The animation state at +0x60 of the object's state. */
typedef struct {
    char pad0[0x10];
    float a[4];                   /* 0x10 */
    float b[4];                   /* 0x20 */
    char sound[0x94];             /* 0x30 */
    u8 state, prev;               /* 0xC4 */
    short timer;                  /* 0xC6 */
    float rate, rate2, level;     /* 0xC8 */
    short timer2;                 /* 0xD4 */
    u8 pad[1];
    u8 flag;                      /* 0xD7 */
} Anim;

extern HeroAnim g_hero_state;
extern float IntToFloat(int);
extern int FastDecTimer(void *);
extern void cam_compute_offset(void *, int, float);
extern int g_weapon_anim_skip_flag __attribute__((sda));
extern int g_camera_default_frame_count __attribute__((sda)), g_weapon_anim_ctrl4_frames __attribute__((sda)), g_weapon_anim_ctrl2_frames __attribute__((sda)), g_weapon_aim_in_frames __attribute__((sda));
extern int g_weapon_aim15_in_frames __attribute__((sda)), g_weapon_aim_out_frames __attribute__((sda)), g_weapon_anim_return_frames __attribute__((sda)), g_weapon_aim5_in_frames __attribute__((sda));
extern int g_weapon_anim_state12_frames __attribute__((sda)), g_weapon_anim_state12_exit_frames __attribute__((sda)), g_weapon_anim_timer2_frames __attribute__((sda)), g_weapon_anim_state9_exit_frames __attribute__((sda));
extern float g_weapon_aim_in_level __attribute__((sda)), g_weapon_aim15_level __attribute__((sda)), g_weapon_aim5_level __attribute__((sda)), g_weapon_anim_base_level __attribute__((sda));

/* Switch to state n, with t frames of blend. */
#define GO(n, t) { s->prev = s->state; s->state = n; s->timer = t; s->rate = 1.0f / func_00283CE0(s->timer); return; }

/* Switch to aiming state n: start both blends, play the sound and keep the current pose. */
#define AIM(n, t2, t, lv, fl, snd, from, to) { float one = 1.0f; \
    s->prev = s->state; s->state = n; \
    s->timer2 = ((s32)(t2) * 5 + 2) / 6; s->rate2 = one / func_00283CE0(s->timer2); \
    s->timer = t; s->rate = one / func_00283CE0(s->timer); \
    s->level = lv; s->flag = 0; \
    func_003349E8(snd, fl, lv); \
    qcopy(to, from); return; }

void func_PAL_L00_00425F08(char *moby)
{
    char *p = *(char **)(moby + 0x70);
    Anim *s = (Anim *)(p + 0x60);
    if (g_weapon_anim_skip_flag) { g_weapon_anim_skip_flag = 0; return; }
    if (s->state == 0) {
        if (g_hero_state.ctrl == 2 || g_hero_state.ctrl == 30) GO(1, g_weapon_anim_ctrl2_frames)
        if (g_hero_state.state == 15) AIM(3, g_weapon_aim15_in_frames, g_weapon_aim_out_frames, g_weapon_aim15_level, 1, p + 0x90, p + 0x70, p + 0x80)
        if (g_hero_state.state == 12) GO(8, g_weapon_anim_state12_frames)
        if (g_hero_state.state == 11) AIM(6, g_weapon_aim_in_frames, g_weapon_aim_out_frames, g_weapon_aim_in_level, 0, p + 0x90, p + 0x70, p + 0x80)
        if ((unsigned)(g_hero_state.state - 13) < 2) {
            AIM(5, g_weapon_aim5_in_frames, g_weapon_anim_state12_frames, g_weapon_aim5_level, 1, p + 0x90, p + 0x70, p + 0x80)
        }
        if (g_hero_state.ctrl == 4) GO(2, g_weapon_anim_ctrl4_frames)
        return;
    }
    if (s->state == 2 && (g_hero_state.state == 0x81 || g_hero_state.state == 0x5B)) GO(1, g_weapon_anim_ctrl2_frames)
    if (s->state != 9 && s->state != 1 && g_hero_state.state == 0x14) {
        s->prev = s->state; s->state = 9;
        s->timer2 = ((s32)(g_weapon_anim_timer2_frames) * 5 + 2) / 6;
        s->rate2 = 1.0f / IntToFloat(s->timer2);
        s->timer = 0; s->rate = 1.0f; s->level = g_weapon_anim_base_level; s->flag = 0;
        cam_compute_offset(s->sound, 1, g_weapon_anim_base_level);
        qcopy(s->b, s->a);
        return;
    }
    if ((s->state == 1 || s->state == 2) && g_hero_state.ctrl != 4 && g_hero_state.ctrl != 2 && g_hero_state.ctrl != 30 && g_hero_state.state != 0x81) {
        s->timer = 0; s->rate = 1.0f; s->state = 0;
        return;
    }
    if (s->state == 7) {
        if (!g_hero_state.b49E) AIM(6, g_weapon_aim_in_frames, g_weapon_aim_out_frames, g_weapon_aim_in_level, 1, s->sound, s->a, s->b)
        if (g_hero_state.ctrl == 2) GO(1, ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6)
    }
    if (s->state == 4 && g_hero_state.ctrl != 4) {
        if (g_hero_state.ctrl == 2) {
            s->prev = 4; s->state = 1;
            s->timer = ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6; s->rate = 1.0f / IntToFloat(s->timer);
            return;
        } else {
            s->prev = 4; s->state = 0;
            s->timer = ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6; s->rate = 1.0f / IntToFloat(s->timer);
            return;
        }
    }
    if (s->state == 3 && g_hero_state.state == 11) AIM(6, g_weapon_aim_in_frames, g_weapon_aim_out_frames, g_weapon_aim_in_level, 1, s->sound, s->a, s->b)
    if (s->state == 5 && g_hero_state.state == 12) GO(8, g_weapon_anim_state12_frames)
    if (s->state == 8 && g_hero_state.state != 12) GO(0, ((s32)(g_weapon_anim_state12_exit_frames) * 5 + 2) / 6)
    if (s->state == 6 && g_hero_state.state != 11) GO(0, ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6)
    if ((s->state == 3 || s->state == 5) && g_hero_state.ctrl != 4) GO(0, ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6)
    if ((s->state == 9 && (g_hero_state.ctrl == 2 || g_hero_state.h34C >= 0x2E)) ||
        (s->state == 10 && (g_hero_state.ctrl == 2 || g_hero_state.h34C >= 0x2E))) {
        float one = 1.0f;
        char *q;
        s->prev = s->state; s->state = 1;
        s->timer = ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6;
        s->rate = one / IntToFloat(s->timer);
        q = *(char **)(moby + 0x70) + 0x20;
        *(short *)q = ((s32)(g_camera_default_frame_count) * 5 + 2) / 6;
        *(float *)(q + 0x24) = one / IntToFloat(*(short *)q);
        qcopy(moby + 0x40, moby);
        return;
    }
    if (s->state == 9 && g_hero_state.state != 0x14) GO(10, g_weapon_anim_state9_exit_frames)
    if (s->state == 10 && FastDecTimer(&s->timer2)) {
        s->prev = s->state; s->state = 0;
        s->timer = ((s32)(g_weapon_anim_return_frames) * 5 + 2) / 6; s->rate = 1.0f / IntToFloat(s->timer);
    }
}
