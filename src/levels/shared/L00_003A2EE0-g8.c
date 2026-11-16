/* Scoped weapon update: targeting, zoom, firing, reload and muzzle light. */
#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
typedef union { u8 b[0x200]; s32 i[0x80]; } GameState;
typedef union { u8 b[0x70]; s32 i[0x1C]; char *p[0x1C]; } SoundSlot;

typedef struct {
    s16 zoomed;
    s16 fire_timer;
    f32 reload;
    f32 zoom_max;
    f32 zoom;
    s32 light;
    s32 flash;
    s32 model;
    char *record;
    s32 sound;
    s32 hud;
    s32 shots;
    s16 locked;
    s16 blink;
    char *target;
} ScopeState;

typedef struct { f32 radius, spread, power, reserved; f32 position[4]; } MuzzleLight;
typedef struct { u8 pad[0x54]; f32 rate; u8 tail[0x88]; } WeaponEntry;
typedef struct { u8 b[0x10]; } TargetRecord;

extern char g_hero_state[];
extern char g_pad_state[];
extern SoundSlot g_sound_state[];
extern u16 g_trigger_id_word[];
extern u8 g_beam_weapon_index[];

extern s32 g_render_state_word;
extern s32 g_frame_l00_counter;
extern f32 g_zoom_saved_param_a __attribute__((sda));
extern f32 g_zoom_saved_param_b __attribute__((sda));
extern f32 g_zoom_saved_param_c __attribute__((sda));
extern f32 g_zoom_saved_param_d __attribute__((sda));
extern f32 g_zoom_fov_value_a;
extern f32 g_zoom_fov_value_b;
extern f32 g_zoom_fov_value_c;
extern f32 g_zoom_fov_value_d;
extern f32 g_fast_math_ratio[];
extern char g_camera_l00_position[];
extern char *g_hit_l00_result[];
extern MuzzleLight g_light_table[];
extern WeaponEntry g_weapon_l00_table[];
extern TargetRecord g_target_hud_records[];

extern void cam_set_value_target(int, int, float, float, float, float);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern int CollLine(void *, void *, int, int, void *);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern int vec_fast_helper_b(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(int);
extern int subtitle_request_voice_line(int, int);
extern int gfx_add_point_light(float, void *, u32, float);
extern void gfx_free_point_light(s32);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended(void *, int, int, int);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern float *moby_get_private_value_0(void *);
extern int moby_is_in_special_class_range(void *);
extern void snd_stop_voice(s32);
extern int PlayMobySound(int, int, void *);
extern void start_equipped_item_animation(void);
extern s32 hero_l00_set_action(int, int);
extern int weapon_spend_ammo(int, int);
extern int get_ammo(int);
extern int slot_copy_records_to_free(TargetRecord *);
extern void slot_reset_active(int);
extern int AcquireEntitySlot(void *, int, int *);
extern char *mem_round_up_to_16(char *);
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern void gfx_update_frame_time_scales(int);
extern void beam_fire_with_muzzle_flash(void *);
extern void beam_clear_particle_pool(int);

#define HERO ((Hero *)D_00189E20)
#define GAME ((GameState *)D_00138180)

/* Per-frame update for the Pulse Rifle moby: lets the player zoom in, aim, fire and reload, and flashes the muzzle light. */
void UpdateScopedWeapon(u8 *moby)
{
    ScopeState *st = *(ScopeState **)(moby + 0x68);
    float saved[4];
    float muzzle[4];
    float offset[4];
    int found;
    int fire;

    if (HERO->i[0x1244 / 4] == 3) {
        if (moby[0x20] == 0)
            return;
        g_zoom_fov_value_b = g_zoom_saved_param_a;
        g_zoom_fov_value_c = g_zoom_saved_param_b;
        g_zoom_fov_value_d = g_zoom_saved_param_c;
        g_zoom_fov_value_a = g_zoom_saved_param_d;
        cam_set_value_target(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
        if (st->light >= 0)
            gfx_free_point_light(st->light);
        st->light = -1;
        g_render_state_word = 0xE0;
        gfx_update_frame_time_scales(1);
        return;
    }
    if (HERO->i[0x2294 / 4] == 0x6F) {
        if (moby[0x20] == 4)
            return;
        moby[0x20] = 4;
        if (st->light >= 0)
            gfx_free_point_light(st->light);
        st->light = -1;
        g_zoom_fov_value_b = g_zoom_saved_param_a;
        g_zoom_fov_value_c = g_zoom_saved_param_b;
        g_zoom_fov_value_d = g_zoom_saved_param_c;
        g_zoom_fov_value_a = g_zoom_saved_param_d;
        cam_set_value_target(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
        gfx_update_frame_time_scales(1);
        return;
    }
    if (moby[0x20] == 4)
        moby[0x20] = 1;
    qcopy(saved, moby + 0x10);
    if (moby[0x42] == moby[0x43] && (moby[0x60] & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    if (HERO->i[0x1500 / 4] != 0 && moby[0x20] != 0) {
        if (g_frame_l00_counter & 4) {
            st->target = 0;
            st->locked = 0;
            vec_scale_to_length(muzzle, g_camera_l00_position + 0x230, 128.0f);
            FastVecAdd(muzzle, muzzle, g_camera_l00_position);
            if (CollLine(g_camera_l00_position, muzzle, 0x10, HERO->i[0x2290 / 4], 0) != 0) {
                u8 *hit = (u8 *)g_hit_l00_result[0];
                if (hit != 0 && hit[0x31] != 0) {
                    float *health = moby_get_private_value_0(hit);
                    if (moby_is_in_special_class_range(hit) != 0
                        || (health != 0 && *health > 0.0f && *(u8 **)(hit + 0x24) != 0
                            && *(s16 *)(*(u8 **)(hit + 0x24) + 0x46) == 5)) {
                        st->target = (char *)hit;
                        st->locked = 1;
                    }
                }
            }
        }
        if (HERO->i[0x2534 / 4] == 0) {
            if (st->locked != 0) {
                st->blink++;
                if (st->blink > 20)
                    st->blink = 0;
                if (st->reload <= 0.0f && get_ammo(-1) != 0 && st->blink > 10)
                    hud_add_moby_marker(moby, 1.5f, 0x400000FF, 0, 0x20, 0.0f, -1, 90.0f, 4);
            }
            hud_add_moby_marker(moby, 2.0f, (st->reload > 0.0f && get_ammo(-1) != 0) ? 0x600000FF : 0x600FFF0F,
                          0, 0x27, 0.0f, -1, 90.0f, 4);
        }
    }
    switch (moby[0x20]) {
    case 0: {
        float max;
        st->zoomed = 0;
        st->reload = 0.36666667f;
        moby[0x20] = 3;
        max = mat_fast_helper_a(1.0f, g_fast_math_ratio[0]) * 2.0f;
        st->zoom_max = max;
        st->zoom = max + (0.17453295f - max) * 0.25f;
        g_zoom_saved_param_a = g_zoom_fov_value_b;
        g_zoom_saved_param_b = g_zoom_fov_value_c;
        g_zoom_saved_param_c = g_zoom_fov_value_d;
        g_zoom_saved_param_d = g_zoom_fov_value_a;
        st->flash = 0;
        st->locked = 0;
        st->blink = 0;
        st->target = 0;
        st->light = -1;
        st->sound = -1;
        st->hud = -1;
        st->model = AcquireEntitySlot(moby, 0, &found);
        if (found == 0) {
            char *record = level_get_slot_body(*(s16 *)(moby + 0xAA), st->model);
            int *size = level_get_slot_header(*(s16 *)(moby + 0xAA), st->model);
            st->record = record;
            *size = mem_round_up_to_16(record + 0x2300) - (int)record;
        }
        if (st->model >= 0)
            beam_clear_particle_pool(st->model);
        break;
    }
    case 1: {
        float zoom_blend;
        if (HERO->i[0x2294 / 4] == 1)
            hero_l00_set_action(0x1D, 1);
        fire = 1;
        if (HERO->i[0x1500 / 4] != 0) {
            fire = 0;
            if (math_fast_float_d(&HERO->i[0x2534 / 4]) != 0)
                fire = 1;
            if (st->zoomed == 0)
                g_render_state_word = 0;
            st->zoomed = 1;
        } else {
            HERO->i[0x2534 / 4] = 0x28;
        }
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        if (HERO->i[0x1500 / 4] != 0) {
            if ((GAME->i[0x1A0 / 4] & 8) && st->zoom > 0.17453295f) {
                SoundSlot *slot = &g_sound_state[st->sound];
                if ((u8 *)slot->p[0x88 / 4] != moby || slot->b[0x74] == 0)
                    st->sound = PlayMobySound(2, 4, moby);
                g_trigger_id_word[0] = 0xFFFF;
                st->zoom -= 0.01f;
            } else if ((GAME->i[0x1A0 / 4] & 2) && st->zoom < st->zoom_max) {
                SoundSlot *slot = &g_sound_state[st->sound];
                if ((u8 *)slot->p[0x88 / 4] != moby || slot->b[0x74] == 0)
                    st->sound = PlayMobySound(3, 4, moby);
                g_trigger_id_word[0] = 0xFFFF;
                st->zoom += 0.01f;
            } else {
                int h = st->sound;
                if (h != -1) {
                    SoundSlot *slot = &g_sound_state[h];
                    if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                        snd_stop_voice(h);
                }
                st->sound = -1;
            }
            if (st->zoom > st->zoom_max)
                st->zoom = st->zoom_max;
            else if (st->zoom < 0.17453295f)
                st->zoom = 0.17453295f;
            cam_set_value_target(0, 3, st->zoom, 0.02f, 0.2f, 0.0f);
            gfx_update_frame_time_scales(0);
        } else {
            int h = st->sound;
            if (h != -1) {
                SoundSlot *slot = &g_sound_state[h];
                if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                    snd_stop_voice(h);
            }
            st->sound = -1;
            if (st->zoomed != 0) {
                float max = st->zoom_max;
                st->zoom = max + (0.17453295f - max) * 0.25f;
                cam_set_value_target(0, 3, max, 0.005f, 0.2f, 0.0f);
                st->zoomed = 0;
                g_render_state_word = 0xE0;
                gfx_update_frame_time_scales(1);
            }
        }
        zoom_blend = (st->zoom - 0.17453295f) / (st->zoom_max - 0.17453295f);
        g_zoom_fov_value_b = (g_zoom_saved_param_a - 0.03f) * zoom_blend + 0.03f;
        g_zoom_fov_value_c = (g_zoom_saved_param_b - 0.4f) * zoom_blend + 0.4f;
        g_zoom_fov_value_a = (g_zoom_saved_param_d - 0.010471977f) * zoom_blend + 0.010471977f;
        if (HERO->b[0x22BC] == 0 && (GAME->i[0x1A4 / 4] & HERO->i[0x1230 / 4]) && fire) {
            if (weapon_spend_ammo(-1, 1) != 0) {
                start_equipped_item_animation();
                st->hud = slot_copy_records_to_free(g_target_hud_records);
                st->fire_timer = 2;
                moby[0x20] = 2;
                anim_start_blended(moby, 2, 0, 0);
            } else {
                PlayMobySound(1, 0, moby);
            }
        }
        if (!(GAME->i[0x1A0 / 4] & HERO->i[0x1230 / 4]) || get_ammo(-1) == 0 || HERO->b[0x22B8] == 0) {
            if (st->hud >= 0) {
                slot_reset_active(st->hud);
                st->hud = -1;
            }
        }
        break;
    }
    case 2:
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        if (FastDecTimer(&st->fire_timer) != 0 || st->zoomed != 0) {
            int h = st->sound;
            if (h != -1) {
                SoundSlot *slot = &g_sound_state[h];
                if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                    snd_stop_voice(h);
            }
            st->sound = -1;
            PlayMobySound(0, 0, moby);
            beam_fire_with_muzzle_flash(moby);
            {
                WeaponEntry *weapon = &g_weapon_l00_table[g_beam_weapon_index[0]];
                st->reload = 1.0f / weapon->rate;
            }
            moby[0x20] = 3;
            if (++st->shots == 5)
                subtitle_request_voice_line(0x9F3, 0x4A);
        }
        break;
    case 3:
        if (vec_fast_helper_b(&st->reload) != 0)
            moby[0x20] = 1;
        break;
    }
    if (st->flash != 0) {
        if (math_fast_float_d(&st->flash) != 0) {
            if (st->light >= 0)
                gfx_free_point_light(st->light);
            st->light = -1;
        } else {
            if (st->light == -1)
                st->light = gfx_add_point_light(15.0f, moby + 0x10, 0x7F608060, 0.0f);
            if (st->light >= 0) {
                float flash_fraction;
                if (HERO->h[0x24EC / 2] == 1) {
                    moby_transform_joint_to_world(moby, 0, muzzle);
                    vec_scale_to_length(offset, moby + 0xD0, -1.5f);
                } else {
                    moby_transform_joint_to_world(moby, 0, muzzle);
                    vec_scale_to_length(offset, &HERO->f[0x760 / 4], 1.5f);
                }
                {
                    float (*positions)[8] = (float (*)[8])g_light_table[0].position;
                    MuzzleLight *lights;
                    FastVecAdd(positions[st->light], muzzle, offset);
                    lights = (MuzzleLight *)((char *)positions - 0x10);
                    lights[st->light].position[3] = 15.0f;
                    flash_fraction = IntToFloat(st->flash) / IntToFloat(30);
                    lights[st->light].spread = flash_fraction;
                    lights[st->light].radius = flash_fraction * 0.75f;
                    lights[st->light].power = lights[st->light].radius;
                }
            }
        }
    }
}
