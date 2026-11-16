#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef short s16;

typedef int s32;

/* the selected state object, and the two candidate pointers beside it */
extern u8 *g_mothership_boss_moby __attribute__((sda));

/* the same word read through an absolute access */
extern u8 *D_L23_001B1484_2;

extern s32 g_enemy_charged_shot_moby __attribute__((sda));

extern s32 g_hero_charged_shot_moby __attribute__((sda));

extern s32 g_hero_moby __attribute__((nosda));

extern s32 g_counter_effect_active __attribute__((sda));

extern s16 g_effect_sound_handle_a __attribute__((sda));

extern s16 g_effect_sound_handle_b __attribute__((sda));

extern void gfx_free_point_light(s32);

extern void gfx_add_draw_callback_first(void *, void *);

extern void counter_effect_init_position(void *);

extern void counter_effect_count_frame(void *);

extern void gfx_draw_spinning_quad_table(void);

extern void effect_controller_init_link_table(void *);

extern void effect_controller_count_frame(void *);

extern void hero_spawn_trail_effect(void *);

extern void gfx_draw_spinning_star_quads(void *);

extern void hero_draw_trail_ribbons(void *);

extern s32 mothership_is_held(void);

extern s32 mothership_is_blast_timer_running(void);

extern s32 mothership_is_blast_cooling_down(void);

extern float g_trail_ribbon_phase __attribute__((sda));

/* reports whether the current state object carries byte 0x20 equal to four */
/* Says whether the current boss-fight object is in state 4. Returns 0 if there is none. */
s32 boss_is_fight_state_four(void) {
    u8 *state = g_mothership_boss_moby;

    if (state == 0) {
        return 0;
    }
    return state[0x20] == 4;
}

extern s32 g_hero_charge_sound_handle __attribute__((sda));

extern s32 g_enemy_charge_sound_handle __attribute__((sda));

/* two absolute level words: sized past the $gp limit so each store is a bare symbol through $at */
extern s32 g_charged_shot_flag[4] __attribute__((sda));

extern s32 g_screen_effect[4] __attribute__((sda));

extern void snd_stop_voice(s32 handle);

extern void moby_mark_spawned(u8 *object);

/* releases the handle of the slot chosen by the key, then the object the slot holds */
/* Cleans up a charged shot: stops its charging sound, stops its glow and removes the shot
   object. The key tells whether it belongs to the hero or to the enemy. */
void charged_shot_release(s32 key, s32 flag) {
    s32 *slot;
    s32 handle;
    u8 *obj;
    u8 *vars;

    if (key == g_hero_moby) {
        handle = g_hero_charge_sound_handle;
        slot = &g_hero_charged_shot_moby;
        if (handle != -1) {
            snd_stop_voice(handle);
            g_hero_charge_sound_handle = -1;
        }
    } else {
        handle = g_enemy_charge_sound_handle;
        slot = &g_enemy_charged_shot_moby;
        if (handle != -1) {
            snd_stop_voice(handle);
            g_enemy_charge_sound_handle = -1;
        }
    }
    obj = (u8 *)*slot;
    if (obj != 0) {
        if (*(s16 *)(obj + 0xAA) != 0x1190 /* moby class 4496 */) {
            *slot = 0;
        } else {
            if (flag == 0 && obj[0x20] != 0) {
                return;
            }
            vars = *(u8 **)(obj + 0x68);
            g_charged_shot_flag[0] = 0;
            g_screen_effect[0] = 0;
            if (*(s16 *)(vars + 0x2C) != -1) {
                gfx_free_point_light(*(s16 *)(vars + 0x2C));
            }
            moby_mark_spawned((u8 *)*slot);
            *slot = 0;
        }
    }
}

/* returns one of the two pinned words, chosen by the measured key */
/* Gets the charged shot object that belongs to the hero or to the enemy, depending on the
   key. */
s32 charged_shot_get_for_owner(s32 key) {
    s32 *word = &g_enemy_charged_shot_moby;

    if (key == g_hero_moby) {
        word = &g_hero_charged_shot_moby;
    }
    return *word;
}

/* releases both measured handles and clears them */
/* Stops both looping sounds and marks them as not playing. */
void snd_stop_both_looping(void) {
    s16 handle = g_effect_sound_handle_a;

    if (handle != -1) {
        gfx_free_point_light(handle);
        g_effect_sound_handle_a = -1;
    }
    handle = g_effect_sound_handle_b;
    if (handle != -1) {
        gfx_free_point_light(handle);
        g_effect_sound_handle_b = -1;
    }
}

/* releases the measured handles and seeds the frame */
/* Per-frame update of the effect controller object. It sets up on the first frame, runs
   the active effect, and stops the looping sounds when they are no longer needed. */
void effect_controller_update(u8 *moby) {
    s32 *payload = *(s32 **)(moby + 0x68);

    effect_controller_init_link_table(moby);
    if (D_L23_001B1484_2 != 0) {
        if (mothership_is_held() != 0) {
            gfx_add_draw_callback_first((void *)gfx_draw_spinning_star_quads, moby);
        } else if (mothership_is_blast_timer_running() != 0) {
            gfx_add_draw_callback_first((void *)hero_draw_trail_ribbons, moby);
        } else if (mothership_is_blast_cooling_down() != 0) {
            hero_spawn_trail_effect(moby);
        } else {
            payload[1] = 0;
        }
        if (mothership_is_blast_timer_running() == 0) {
            s16 handle = g_effect_sound_handle_a;

            if (handle != -1) {
                g_trail_ribbon_phase = 0.02f;
                gfx_free_point_light(handle);
                g_effect_sound_handle_a = -1;
            }
        }
        if (mothership_is_blast_cooling_down() == 0) {
            s16 handle = g_effect_sound_handle_b;

            if (handle != -1) {
                gfx_free_point_light(handle);
                g_effect_sound_handle_b = -1;
            }
        }
    }
    effect_controller_count_frame(moby);
}

/* refreshes the two counters around the measured callback */
/* Per-frame update of a small effect object. It runs the effect while the boss fight is
   active and counts frames. */
void counter_effect_update(void *moby) {
    counter_effect_init_position(moby);
    if (D_L23_001B1484_2 != 0) {
        if (g_counter_effect_active != 0) {
            gfx_add_draw_callback_first((void *)gfx_draw_spinning_quad_table, moby);
        }
    }
    counter_effect_count_frame(moby);
}


extern s32 g_boss_fight_timer;

extern s32 g_boss_fight_start_value __attribute__((sda));

extern int PlayMobySound(int, int, u8 *);

/* publishes the boot stamp once, seeding the shared state first */
/* Starts the boss fight state once and remembers the starting time. */
void boss_start_fight_once(void) {
    if (g_boss_fight_timer == 0) {
        u8 *state = g_mothership_boss_moby;

        if (state != 0) {
            PlayMobySound(0x10, 0, state);
        }
    }
    g_boss_fight_timer = g_boss_fight_start_value;
}

/* the three words at 0x1B17B0 are copied to the stack; the entries picked by the timing tests are chosen by a helper */
typedef struct {
    s32 v[3];
} L23Table3;

extern L23Table3 g_boss_attack_table;

typedef struct {
    u8 pad[0x18];
    s32 f18;
    s32 f1C;
} L23Block1F90;

extern L23Block1F90 g_hud_counters;

typedef struct {
    u8 pad[0x1874];
    s32 f1874;
} D00189E20_View;

extern D00189E20_View g_hero_state;

extern s32 math_random_int_below(s32);

/* collects the timing entries that apply and returns one of them at random (-1 when none does) */
/* Picks a random attack that is ready to be used. Returns -1 when none is ready. */
s32 boss_pick_random_ready_attack(void) {
    u8 *obj = *(u8 **)(g_mothership_boss_moby + 0x68);
    L23Table3 table = g_boss_attack_table;
    s32 count = 0;

    if (g_hero_state.f1874 < *(s16 *)(obj + 0x2F4) - 5) {
        table.v[0] = 0;
        count = 1;
    }
    if (count == 0 || !(g_hero_state.f1874 < *(s16 *)(obj + 0x2F4) / 2)) {
        if (g_hud_counters.f18 < *(s16 *)(obj + 0x2FA)) {
            table.v[count++] = 1;
        }
        if (g_hud_counters.f1C < *(s16 *)(obj + 0x2FE)) {
            table.v[count++] = 2;
        }
    }
    if (count == 0) {
        return -1;
    }
    switch (math_random_int_below(count)) {
    case 0:
        return table.v[0];
    case 1:
        return table.v[1];
    case 2:
    default:
        return table.v[2];
    }
}

typedef int TI16 __attribute__((mode(TI)));

/* level words written as bare symbols through $at: each sized past the $gp limit */
extern s32 g_charged_shot_color_a[3] __attribute__((sda));

extern s32 g_charged_shot_color_b[3] __attribute__((sda));

extern long long g_charged_shot_command_words[2] __attribute__((sda));

extern long long g_charged_shot_zero_words[2] __attribute__((sda));

/* a plain small extern: $gp in the delay slot reorg copies it into, absolute where it stays */
extern s32 g_hero_special_mode;

extern s16 gfx_add_point_light(TI16 *, s32, float, float);

extern u8 *CreateMoby(s32);

/* allocates the object, records it in the word chosen by the key and fills its fields and the level block */
/* Creates a charged shot object for the hero or the enemy and sets it up. Does nothing if
   that side already has one. */
u8 *charged_shot_create(u8 *owner, TI16 *position) {
    u8 *obj;
    u8 *payload;
    s32 *word;

    obj = CreateMoby(0x1190 /* moby class 4496 */);
    word = &g_enemy_charged_shot_moby;
    if (owner == (u8 *)g_hero_moby) {
        word = &g_hero_charged_shot_moby;
    }
    if (obj != 0 && *word == 0) {
        *(u8 *)(obj + 0x30) = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x31) = 1;
        *(u8 **)(obj + 0xB8) = owner;
        *(u8 *)(obj + 0x20) = 0;
        payload = *(u8 **)(obj + 0x68);
        *(TI16 *)(obj + 0x10) = *position;
        *word = (s32)obj;
        g_charged_shot_color_a[0] = 0xFF;
        g_charged_shot_color_b[0] = 0x00FFFFFF;
        g_charged_shot_command_words[0] = 0x1F00000042LL;
        g_charged_shot_zero_words[0] = 0;
        g_charged_shot_flag[0] = 0;
        g_screen_effect[0] = 0;
        *(s32 *)(payload + 0x10) = 0;
        *(s16 *)(payload + 0x2C) = gfx_add_point_light(position, 0, 0.0f, 0.0f);
    }
    if (g_hero_special_mode != 0) {
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(TI16 *)(obj + 0xC0) = *(TI16 *)(owner + 0xC0);
        *(TI16 *)(obj + 0xD0) = *(TI16 *)(owner + 0xD0);
        *(TI16 *)(obj + 0xE0) = *(TI16 *)(owner + 0xE0);
    }
    return obj;
}

extern s32 snd_start_in_slot(s32, s32, s32);

/* makes sure the word chosen by the flag holds an object, then moves it to the given position */
/* Makes sure a charged shot exists for one side, then moves it to the given spot. */
void charged_shot_spawn_or_move(u8 *owner, TI16 *position, s32 isHero) {
    s32 *word = &g_enemy_charged_shot_moby;
    TI16 local;
    TI16 *pos = &local;
    u8 *obj;
    u8 *payload;
    u8 *found;

    if (isHero != 0) {
        word = &g_hero_charged_shot_moby;
    }
    local = *position;
    if (*word == 0) {
        charged_shot_create(owner, &local);
        if (isHero != 0) {
            g_hero_charge_sound_handle = snd_start_in_slot(0x14, 0, 0);
        } else {
            g_enemy_charge_sound_handle = snd_start_in_slot(0x14, 0, 0);
        }
        found = (u8 *)*word;
        if (found == 0) {
            return;
        }
        obj = found;
        payload = *(u8 **)(obj + 0x68);
        if (*(s16 *)(obj + 0xAA) != 0x1190 /* moby class 4496 */) {
            return;
        }
        *(s16 *)(payload + 0x40) = isHero;
        *(s32 *)(payload + 0x48) = 0;
        *(s32 *)(payload + 0x44) = 0;
    }
    obj = (u8 *)*word;
    *(TI16 *)(obj + 0x10) = *pos;
    payload = *(u8 **)(obj + 0x68);
    *(s16 *)(payload + 0x2E) = 1;
}

extern void moby_set_state(void *, s32, s32);

extern void boss_part_handle_hit(u8 *);

/* the timer the second state copies into the sub-object */
extern float g_mothership_max_health __attribute__((sda));

/* state 0 arms the draw distances and a 2000-tick timer and moves to state 1; state 1 copies the
   shared timer when it is set and moves to state 2; both then run the per-frame handler */
/* Starts the object's life: sets its health, then runs its hit handler every frame. */
void boss_part_init_health(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 state = moby[0x20];

    if (state == 0) {
        *(u16 *)(moby + 0x32) = 0xFF;
        moby[0x30] = 0xFF;
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x100;
        *(float *)(vars + 0x20) = 2000.0f;
        *(s16 *)(vars + 0x24) = 2000;
        *(u16 *)(moby + 0x7C) = 0x3FF;
        moby_set_state(moby, 1, 0);
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x4000;
    } else if (state == 1) {
        float t = g_mothership_max_health;

        if (t != 0.0f) {
            *(float *)(vars + 0x20) = t;
            *(s16 *)(vars + 0x24) = (s16)t;
        }
        moby_set_state(moby, 2, 0);
    }
    boss_part_handle_hit(moby);
}

extern s32 g_trail_ribbon_color_scale_a __attribute__((sda));

extern s32 g_trail_ribbon_color_scale_b __attribute__((sda));

extern float g_trail_ribbon_width_scale_a __attribute__((sda));

extern float g_trail_ribbon_width_scale_b __attribute__((sda));

extern float g_trail_ribbon_width_scale_c __attribute__((sda));

extern s32 g_trail_ribbon_halo_value __attribute__((sda));

/* the three floats come before the two trailing words: that argument order is what keeps the
   two arms of the second call from sharing more than the jal */
extern void DrawColoredRibbonWithHalo(void *obj, s32 a, s32 b, s32 c, float x, float y, float z, s32 d, s32 e);

/* draws the record twice: once plain (or with the override word when byte 0x2B is set), once scaled */
/* Draws the energy ribbon of a trail object, once normally and once larger as a glow. */
void trail_draw_ribbon(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (vars[0x2A] == 0) {
        DrawColoredRibbonWithHalo(vars + 0x30, vars[0x28], vars[0x29], 5,
                          *(float *)(vars + 0x10), *(float *)(vars + 0x14), *(float *)(vars + 0x18),
                          *(s32 *)vars, *(s32 *)(vars + 4));
        return;
    }
    if (vars[0x2B] != 0) {
        DrawColoredRibbonWithHalo(vars + 0x30, vars[0x28], vars[0x29], 5,
                          *(float *)(vars + 0x10), *(float *)(vars + 0x14), *(float *)(vars + 0x18),
                          g_trail_ribbon_halo_value, g_trail_ribbon_halo_value);
    } else {
        DrawColoredRibbonWithHalo(vars + 0x30, vars[0x28], vars[0x29], 5,
                          *(float *)(vars + 0x10), *(float *)(vars + 0x14), *(float *)(vars + 0x18),
                          *(s32 *)vars, *(s32 *)(vars + 4));
    }
    DrawColoredRibbonWithHalo(vars + 0x30, vars[0x28] * g_trail_ribbon_color_scale_a, vars[0x29] * g_trail_ribbon_color_scale_b, 5,
                      *(float *)(vars + 0x10) * g_trail_ribbon_width_scale_a, *(float *)(vars + 0x14) * g_trail_ribbon_width_scale_b,
                      *(float *)(vars + 0x18) * g_trail_ribbon_width_scale_c, *(s32 *)vars, *(s32 *)(vars + 4));
}
