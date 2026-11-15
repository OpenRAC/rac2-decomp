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
extern float D_L00_001B05C4 __attribute__((sda));
extern float D_L00_001B05C8 __attribute__((sda));
extern float D_L00_001B05CC __attribute__((sda));
extern float D_L00_001B05D0 __attribute__((sda));
extern float D_L00_001B15CC MACRO_ADDR;
extern float D_L00_001B15D0 MACRO_ADDR;
extern float D_L00_001B15D4 MACRO_ADDR;
extern float D_L00_001B15D8 MACRO_ADDR;
extern int D_L00_001AA0F8 MACRO_ADDR;
extern int g_frame_l00_counter;
typedef struct { UpdateVector position; char pad[0x220]; UpdateVector forward; } ScopeCamera;
extern ScopeCamera g_camera_l00_position;
extern u8 *D_L00_001BF218 NOT_SDA;
extern float D_L00_001BD370 NOT_SDA;
extern int D_00138320 NOT_SDA;
extern int g_pad_state[];
extern unsigned char D_0013957F NOT_SDA;
extern UpdateTuning g_weapon_l00_table[];
typedef struct { float red, green, blue, unused; UpdateVector position; } ScopeLight;
extern ScopeLight D_L00_001C6F40[];
extern char D_L00_00296AA0[];
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
extern void func_PAL_L00_002C4480(int, int);
extern int math_fast_float_d(int *);
extern int weapon_spend_ammo(int, int);
extern void func_PAL_L00_002AF458(void);
extern int slot_copy_records_to_free(void *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void PlayMobySound(int, int, char *);
extern void slot_reset_active(int);
extern int FastDecTimer(short *);
extern void func_PAL_L00_003E8788(char *);
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
void func_PAL_L00_003E7C98(u8 *object)
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
        D_L00_001B15D0 = D_L00_001B05C4;
        D_L00_001B15D4 = D_L00_001B05C8;
        D_L00_001B15D8 = D_L00_001B05CC;
        D_L00_001B15CC = D_L00_001B05D0;
        cam_set_value_target(0, 3, 1.1243411302566528f, 0.005f, 0.2f, 0.0f);
        if (data->light >= 0) gfx_free_point_light(data->light);
        data->light = -1;
        D_L00_001AA0F8 = 224;
        gfx_update_frame_time_scales(1);
        return;
    }
    if (g_hero_state.mode == 111) {
        if ((u8)object[0x20] == 4) return;
        object[0x20] = 4;
        if (data->light >= 0) gfx_free_point_light(data->light);
        data->light = -1;
        D_L00_001B15D0 = D_L00_001B05C4;
        D_L00_001B15D4 = D_L00_001B05C8;
        D_L00_001B15D8 = D_L00_001B05CC;
        D_L00_001B15CC = D_L00_001B05D0;
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
                target = D_L00_001BF218;
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
        angle = mat_fast_helper_a(1.0f, D_L00_001BD370);
        angle += angle;
        data->initialFov = angle;
        data->zoomFov = angle + (0.174532949924469f - angle) * 0.25f;
        D_L00_001B05C4 = D_L00_001B15D0;
        D_L00_001B05C8 = D_L00_001B15D4;
        D_L00_001B05CC = D_L00_001B15D8;
        D_L00_001B05D0 = D_L00_001B15CC;
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
        if (g_hero_state.mode == 1) func_PAL_L00_002C4480(29, 1);
        if (g_hero_state.scope) {
            if (data->scoped == 0) D_L00_001AA0F8 = 0;
            data->scoped = 1;
        }
        if (g_hero_state.controller) g_hero_state.saved = g_hero_state.controller;
        if (g_hero_state.scope) {
            if (D_00138320 & 8) data->zoomFov -= 0.01f;
            else if (D_00138320 & 2) data->zoomFov += 0.01f;
            if (data->zoomFov > data->initialFov) data->zoomFov = data->initialFov;
            else if (data->zoomFov < 0.174532949924469f) data->zoomFov = 0.174532949924469f;
            cam_set_value_target(0, 3, data->zoomFov, 0.02f, 0.2f, 0.0f);
            gfx_update_frame_time_scales(0);
        } else if (data->scoped) {
            data->zoomFov = data->initialFov + (0.174532949924469f - data->initialFov) * 0.25f;
            cam_set_value_target(0, 3, data->initialFov, 0.005f, 0.2f, 0.0f);
            data->scoped = 0;
            D_L00_001AA0F8 = 224;
            gfx_update_frame_time_scales(1);
        }
        fraction = (data->zoomFov - 0.174532949924469f) / (data->initialFov - 0.174532949924469f);
        horizontal = (D_L00_001B05C4 - 0.03f) * fraction + 0.03f;
        vertical = (D_L00_001B05C8 - 0.4f) * fraction + 0.4f;
        blend = (D_L00_001B05D0 - 0.010471977293491364f) * fraction + 0.010471977293491364f;
        D_L00_001B15D0 = horizontal;
        D_L00_001B15CC = blend;
        D_L00_001B15D4 = vertical;
        canFire = 1;
        if (g_hero_state.scope) {
            if (!math_fast_float_d(&g_hero_state.delay)) canFire = 0;
        } else g_hero_state.delay = 33;
        if (g_hero_state.blocked == 0 && (g_pad_state[0x1A4/4] & g_hero_state.input) && canFire) {
            if (weapon_spend_ammo(-1, 1)) {
                func_PAL_L00_002AF458();
                data->sound = slot_copy_records_to_free(D_L00_00296AA0);
                data->firingDelay = 2;
                object[0x20] = 2;
                func_PAL_002A7E68(object, 2, 0, 0);
            } else PlayMobySound(1, 0, object);
            if ((g_pad_state[0x1A0/4] & g_hero_state.input) && get_ammo(-1) && g_hero_state.active) break;
            if (data->sound >= 0) {
                slot_reset_active(data->sound);
                data->sound = -1;
            }
        }
        break;
    case 2:
        if (g_hero_state.controller) g_hero_state.saved = g_hero_state.controller;
        if (FastDecTimer(&data->firingDelay) || data->scoped) {
            PlayMobySound(0, 0, object);
            func_PAL_L00_003E8788(object);
            tuning = (UpdateTuning *)(D_0013957F * 224 + (char *)g_weapon_l00_table);
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
                FastVecAdd(D_L00_001C6F40[data->light].position, first, second);
                D_L00_001C6F40[data->light].position[3] = 10.0f;
                intensity = IntToFloat(data->flashTimer);
                intensity /= IntToFloat(25);
                D_L00_001C6F40[data->light].red = intensity;
                intensity *= 0.7f;
                D_L00_001C6F40[data->light].green = intensity;
                D_L00_001C6F40[data->light].blue = 0;
            }
        }
    }
}
