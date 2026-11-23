#include "include_asm.h"

#include "common.h"
typedef float UpdateVector[4] __attribute__((aligned(16)));
typedef struct { char pad[0x54]; float rate; char rest[0x88]; } UpdateTuning;
typedef struct {
    char pad000[0x760];
    float direction[4];
    char pad770[0xBF8-0x770];
    int saved;
    char padBFC[0x1230-0xBFC];
    int input;
    char pad1234[0x1244-0x1234];
    int state;
    char pad1248[0x1450-0x1248];
    int controller;
    char pad1454[0x1500-0x1454];
    int scope;
    char pad1504[0x2290-0x1504];
    void *camera;
    int mode;
    char pad2298[0x22B8-0x2298];
    u8 active;
    char pad22B9[3];
    u8 blocked;
    char pad22BD[0x24EC-0x22BD];
    short alternate;
    char pad24EE[0x2534-0x24EE];
    int delay;
} HeroUpdate;
extern HeroUpdate g_hero_state;
extern float g_vaporizer_horizontal_size __attribute__((sda));
extern float g_vaporizer_vertical_size __attribute__((sda));
extern float g_vaporizer_depth_size __attribute__((sda));
extern float g_vaporizer_blend_angle __attribute__((sda));
extern float g_zoom_fov_value_a MACRO_ADDR;
extern float g_zoom_fov_value_b MACRO_ADDR;
extern float g_zoom_fov_value_c MACRO_ADDR;
extern float g_zoom_fov_value_d MACRO_ADDR;
extern int g_render_state_word MACRO_ADDR;
extern int g_frame_l00_counter;
typedef struct { UpdateVector position; char pad[0x220]; UpdateVector forward; } ScopeCamera;
extern ScopeCamera g_camera_l00_position;
extern u8 *g_hit_l00_result NOT_SDA;
extern float g_fast_math_ratio NOT_SDA;
extern int g_pad_pressed_flags NOT_SDA;
extern int g_pad_state[];
extern unsigned char g_beam_weapon_index NOT_SDA;
extern UpdateTuning g_weapon_l00_table[];
typedef struct { float red, green, blue, unused; UpdateVector position; } ScopeLight;
extern ScopeLight g_light_table[];
extern char g_vaporizer_sound_records[];
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern void cam_set_value_target(int, int, float, float, float, float);
extern void gfx_free_point_light(int);
extern void gfx_update_frame_time_scales(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float *moby_get_private_value_0(char *);
extern int moby_is_in_special_class_range(char *);
extern int get_ammo(int);
extern void hud_add_moby_marker(char *, unsigned int, int, int, int, int, float, float, float);
extern float mat_fast_helper_a(float, float);
extern int AcquireEntitySlot(char *, int, int *);
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern char *mem_round_up_to_16(char *);
extern void mem_fast_helper_b(void *, int);
extern void ref_L00_003E3A18_00(int);
extern s32 hero_l00_set_action_pal(int, int);
extern int math_fast_float_d(int *);
extern int weapon_spend_ammo(int, int);
extern void start_equipped_item_animation_pal(void);
extern int actuator_play_waves(void *);
extern void anim_start_blended_pal(char *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern void actuator_end_looping_waves(int);
extern int FastDecTimer(short *);
extern void AimAndSpawnBeamWithMuzzleFlashes_pal(char *);
extern int vec_fast_helper_b(float *);
extern int gfx_add_point_light(float, void *, unsigned int, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern float IntToFloat(int);
typedef struct {
    short scoped;
    short firingDelay;
    float cooldown, initialFov, zoomFov;
    int light, flashTimer, resource, sound;
    char *resourceBase;
    int unused;
    short targeting, targetFrames;
    u8 *target;
} ScopedWeaponState;

/* Update targeting, zoom, fire/recharge states and the muzzle light.
 * Debug labels reproduce retail division padding; keep the tuning lookup and
 * the reciprocal on separate lines.
 */
void vaporizer_update_pal(u8 *object)
{
    UpdateVector position, first, second;
    int loaded;
    ScopedWeaponState *data = *(ScopedWeaponState **)(object + 0x68);
    u8 *target;
    float *health;
    char *base, *cursor;
    int *offsets;
    UpdateTuning *tuning;
    char **slot;
    int remaining, canFire;
    unsigned int color;
    float angle, fraction, intensity;
    float horizontal, vertical, blend;

    if ((u8)object[0x42] == (u8)object[0x43] && ((u8)object[0x60] & 2))
        anim_start_blended_with_flags(object, 1, 0, 2, 0);
    if (g_hero_state.state == 3) {
        if ((u8)object[0x20] == 0) return;
        g_zoom_fov_value_b = g_vaporizer_horizontal_size;
        g_zoom_fov_value_c = g_vaporizer_vertical_size;
        g_zoom_fov_value_d = g_vaporizer_depth_size;
        g_zoom_fov_value_a = g_vaporizer_blend_angle;
        cam_set_value_target(0, 3, 1.1243411302566528f, 0.005f, 0.2f, 0.0f);
        if (data->light >= 0) gfx_free_point_light(data->light);
        data->light = -1;
        g_render_state_word = 224;
        gfx_update_frame_time_scales(1);
        return;
    }
    if (g_hero_state.mode == 111) {
        if ((u8)object[0x20] == 4) return;
        object[0x20] = 4;
        if (data->light >= 0) gfx_free_point_light(data->light);
        data->light = -1;
        g_zoom_fov_value_b = g_vaporizer_horizontal_size;
        g_zoom_fov_value_c = g_vaporizer_vertical_size;
        g_zoom_fov_value_d = g_vaporizer_depth_size;
        g_zoom_fov_value_a = g_vaporizer_blend_angle;
        cam_set_value_target(0, 3, 1.1243411302566528f, 0.005f, 0.2f, 0.0f);
        gfx_update_frame_time_scales(1);
        return;
    }
    if ((u8)object[0x20] == 4) object[0x20] = 1;
    qcopy(position, object + 0x10);
    if (g_hero_state.scope) {
        if (g_frame_l00_counter & 4) {
            data->target = 0;
            data->targeting = 0;
            vec_scale_to_length(first, g_camera_l00_position.forward, 128.0f);
            FastVecAdd(first, first, g_camera_l00_position.position);
            if (CollLine(g_camera_l00_position.position, first, 16, g_hero_state.camera, 0)) {
                target = g_hit_l00_result;
                if (target && (u8)target[0x31]) {
                    health = moby_get_private_value_0(target);
                    if (moby_is_in_special_class_range(target) || (health && *health > 0.0f &&
                        *(char **)(target + 0x24) && *(short *)(*(char **)(target + 0x24) + 0x46) == 5)) {
                        data->target = target;
                        data->targeting = 1;
                    }
                }
            }
        }
        if (g_hero_state.delay == 0) {
            if (data->targeting) {
                if (++data->targetFrames > 17) data->targetFrames = 0;
                if (data->cooldown <= 0.0f && get_ammo(-1) && data->targetFrames >= 9)
                    hud_add_moby_marker(object, 0x400000FF, 0, 32, -1, 4, 1.5f, 0.0f, 90.0f);
            }
            if (data->cooldown > 0.0f && get_ammo(-1)) color = 0x600000FF;
            else color = 0x600FFF0F;
            hud_add_moby_marker(object, color, 0, 39, -1, 4, 2.0f, 0.0f, 90.0f);
        }
    }
    switch ((u8)object[0x20]) {
    case 0:
        data->scoped = 0;
        data->cooldown = 0.36666667461395264f;
        object[0x20] = 3;
        angle = mat_fast_helper_a(1.0f, g_fast_math_ratio);
        angle += angle;
        data->initialFov = angle;
        data->zoomFov = angle + (0.174532949924469f - angle) * 0.25f;
        g_vaporizer_horizontal_size = g_zoom_fov_value_b;
        g_vaporizer_vertical_size = g_zoom_fov_value_c;
        g_vaporizer_depth_size = g_zoom_fov_value_d;
        g_vaporizer_blend_angle = g_zoom_fov_value_a;
        data->flashTimer = 0;
        data->targeting = 0;
        data->targetFrames = 0;
        data->target = 0;
        data->light = -1;
        data->resource = AcquireEntitySlot(object, 0, &loaded);
        if (!loaded) {
            cursor = level_get_slot_body(*(short *)(object + 0xAA), data->resource);
            data->resourceBase = cursor;
            base = cursor;
            offsets = level_get_slot_header(*(short *)(object + 0xAA), data->resource);
            cursor = mem_round_up_to_16(base + 12);
            slot = (char **)base;
            for (remaining = 2; remaining >= 0; remaining--) {
                *slot = cursor;
                cursor += 0xF00;
                slot++;
            }
            cursor = mem_round_up_to_16(cursor);
            offsets[0] = cursor - base;
            mem_fast_helper_b(cursor, 0x120);
            cursor = mem_round_up_to_16(cursor + 0x120);
            offsets[1] = cursor - base;
            mem_fast_helper_b(cursor, 0x1E00);
        }
        if (data->resource >= 0) ref_L00_003E3A18_00(data->resource);
        break;
    case 1:
        if (g_hero_state.mode == 1) hero_l00_set_action_pal(29, 1);
        if (g_hero_state.scope) {
            if (data->scoped == 0) g_render_state_word = 0;
            data->scoped = 1;
        }
        if (g_hero_state.controller) g_hero_state.saved = g_hero_state.controller;
        if (g_hero_state.scope) {
            if (g_pad_pressed_flags & 8) data->zoomFov -= 0.01f;
            else if (g_pad_pressed_flags & 2) data->zoomFov += 0.01f;
            if (data->zoomFov > data->initialFov) data->zoomFov = data->initialFov;
            else if (data->zoomFov < 0.174532949924469f) data->zoomFov = 0.174532949924469f;
            cam_set_value_target(0, 3, data->zoomFov, 0.02f, 0.2f, 0.0f);
            gfx_update_frame_time_scales(0);
        } else if (data->scoped) {
            data->zoomFov = data->initialFov + (0.174532949924469f - data->initialFov) * 0.25f;
            cam_set_value_target(0, 3, data->initialFov, 0.005f, 0.2f, 0.0f);
            data->scoped = 0;
            g_render_state_word = 224;
            gfx_update_frame_time_scales(1);
        }
        fraction = (data->zoomFov - 0.174532949924469f) / (data->initialFov - 0.174532949924469f);
        horizontal = (g_vaporizer_horizontal_size - 0.03f) * fraction + 0.03f;
        vertical = (g_vaporizer_vertical_size - 0.4f) * fraction + 0.4f;
        blend = (g_vaporizer_blend_angle - 0.010471977293491364f) * fraction + 0.010471977293491364f;
        g_zoom_fov_value_b = horizontal;
        g_zoom_fov_value_a = blend;
        g_zoom_fov_value_c = vertical;
        canFire = 1;
        if (g_hero_state.scope) {
            if (!math_fast_float_d(&g_hero_state.delay)) canFire = 0;
        } else g_hero_state.delay = 33;
        if (g_hero_state.blocked == 0 && (g_pad_state[0x1A4/4] & g_hero_state.input) && canFire) {
            if (weapon_spend_ammo(-1, 1)) {
                start_equipped_item_animation_pal();
                data->sound = actuator_play_waves(g_vaporizer_sound_records);
                data->firingDelay = 2;
                object[0x20] = 2;
                anim_start_blended_pal(object, 2, 0, 0);
            } else PlayMobySound(1, 0, object);
            if ((g_pad_state[0x1A0/4] & g_hero_state.input) && get_ammo(-1) && g_hero_state.active) break;
            if (data->sound >= 0) {
                actuator_end_looping_waves(data->sound);
                data->sound = -1;
            }
        }
        break;
    case 2:
        if (g_hero_state.controller) g_hero_state.saved = g_hero_state.controller;
        if (FastDecTimer(&data->firingDelay) || data->scoped) {
            PlayMobySound(0, 0, object);
            AimAndSpawnBeamWithMuzzleFlashes_pal(object);
            tuning = (UpdateTuning *)(g_beam_weapon_index * 224 + (char *)g_weapon_l00_table);
        data->cooldown = 1.0f / tuning->rate;
            object[0x20] = 3;
        }
        break;
    case 3:
        if (vec_fast_helper_b(&data->cooldown)) object[0x20] = 1;
        break;
    }
    if (data->flashTimer) {
        if (math_fast_float_d(&data->flashTimer)) {
            if (data->light >= 0) gfx_free_point_light(data->light);
            data->light = -1;
        } else {
            if (data->light == -1)
                data->light = gfx_add_point_light(10.0f, object + 0x10, 0xFF0000FF, 0.0f);
            if (data->light >= 0) {
                if (g_hero_state.alternate == 1) {
                    moby_transform_joint_to_world(object, 0, first);
                    vec_scale_to_length(second, object + 0xD0, -1.5f);
                } else {
                    moby_transform_joint_to_world(object, 0, first);
                    vec_scale_to_length(second, g_hero_state.direction, 1.5f);
                }
                FastVecAdd(g_light_table[data->light].position, first, second);
                g_light_table[data->light].position[3] = 10.0f;
                intensity = IntToFloat(data->flashTimer);
                intensity /= IntToFloat(25);
                g_light_table[data->light].red = intensity;
                intensity *= 0.7f;
                g_light_table[data->light].green = intensity;
                g_light_table[data->light].blue = 0;
            }
        }
    }
}
