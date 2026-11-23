/* func_PAL_L00_003AA2D8, the PAL copy of func_L00_003A6C30: the same C, with the frame timers
 * (D_L00_001AF6C0 to D_L00_001AF6CC, read whole here, and D_001A7390) scaled to 50 Hz,
 * the frame constants 10, 9 and 40 at 8, 7 and 33, and the 1/60 step at 1/50.
 * The null-candidate arm keeps two stores of the timer: the extra reference puts state in $s2.
 * Built with -g like its template.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
struct Rac2Native_5f824a0e369ccf7b_src_record { u8 b0,b1,b2,b3; u16 s4,s6,s8,s10,s12; u8 e,f; };
typedef struct { char prefix[0x50]; float speed, rate; char middle[0x18]; float damage; char tail[0x6C]; } WeaponEntry;
typedef struct { float radius, spread, power, reserved; float position[4]; } MuzzleLight;

extern char g_hero_state[];
extern int g_pad_state[];
extern u8 g_item_slot_to_record[];
extern Statistics g_progress_statistics[];
extern u32 g_frame_counter;
extern u32 g_current_map_index;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_lancer_shot_rumble_waves[], g_lancer_held_rumble_waves[];
extern int g_game_l00_mode;
extern float g_lancer_horizontal_arc;
extern float g_lancer_range;
extern float g_lancer_vertical_arc;
extern int g_lancer_fire_held;
extern int g_lancer_state_short __attribute__((sda));
extern int g_lancer_state_int __attribute__((sda));
extern int g_other_weapon_state_short __attribute__((sda));
extern int g_other_weapon_state_int __attribute__((sda));
extern float g_camera_l00_position[4];
extern char *g_area_hit_targets[];
extern WeaponEntry g_weapon_l00_table[];
extern MuzzleLight g_light_table[];

extern void lancer_init_pal(char *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_b(void *);
extern float *moby_get_private_value_0(char *);
extern int moby_is_in_special_class_range(char *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *moby_get_or_find_target(void *, void *, float, float, float, float, float, int);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern float IntToFloat(int);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern s32 hero_l00_set_action_pal(int, int);
extern void EmitParticleTrailLayers_pal(char *);
extern void part_spawn_line_at_moby_pal(char *);
extern void start_equipped_item_animation_pal(void);
extern void cancel_hero_item_animation_pal(void);
extern int gfx_add_point_light(void *, int, float, float);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int PlayMobySound(int, int, char *);
extern int actuator_play_waves(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int actuator_is_channel_active(int);
extern char *CreateTargetedMovingEffect_pal(void *, char *, char *, float);
extern char *SpawnAimedShot_pal(void *, char *, char *);
extern int coll_process_hit(float, void *, int, void *, int);
extern void QueueMobyImpact(void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_spark_burst_3_pal(void *, int, int);
extern void actuator_end_looping_waves(int);
extern void gfx_free_point_light(int);
extern void matrix_mul_vec3(void *, void *, void *);

#define TYPE(m) (*(short *)((m) + 0xAA))

/* Per-frame update of the lancer: locks onto a target, shows the HUD markers, fires and drives the beam (PAL: 50 Hz timings). */
void lancer_update_pal(char *moby)
{
    Vector muzzle, targetPosition, playerPoint, offset, direction;
    char damage[0x30] __attribute__((aligned(16)));
    Vector center;
    char *state = *(char **)(moby + 0x68);
    char *target = 0;
    float previousRange, horizontal, vertical;
    int specialMode = ((Hero *)g_hero_state)->i[0x1244 / 4] == 3;

    if (g_game_l00_mode == 8)
        return;
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 2;
        lancer_init_pal(moby);
    }
    horizontal = g_lancer_horizontal_arc;
    previousRange = g_lancer_range;
    if (TYPE(moby) == 0x5D2)
        g_lancer_range = 20.0f;
    else
        g_lancer_range = 30.0f;
    if (TYPE(moby) == 0x5D2)
        moby_transform_joint_to_world(moby, 0, muzzle);
    else {
        FastVecScale(muzzle, moby + 0xD0, -1.3f);
        FastVecAdd(muzzle, muzzle, moby + 0x10);
    }
    {
        float *dst = (float *)(state + 0x14);
        dst[0] = muzzle[0];
        dst[1] = muzzle[1];
        dst[2] = muzzle[2];
    }
    FastVecScale(playerPoint, (char *)((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.75f);
    FastVecAdd(playerPoint, &((Hero *)g_hero_state)->f[0x80 / 4], playerPoint);
    vertical = g_lancer_vertical_arc;
    g_lancer_horizontal_arc = g_lancer_vertical_arc = 0.1047197655f;
    *(int *)(state + 0x2C) = 0;
    FastDecTimer(state + 6);
    {
        char *locked = *(char **)state;
        if (locked) {
            float *component;
            target = locked;
            component = moby_get_private_value_0(target);
            if (component) {
                FastVecScale(offset, target + 0xE0, component[4]);
                FastVecAdd(targetPosition, target + 0x10, offset);
            } else {
                qcopy(targetPosition, target + 0x10);
            }
            if (!locked || *(u8 *)(locked + 0x20) == 0xFE || *(u8 *)(locked + 0x20) == 0xFD
                || (component && *component <= 0.0f && !moby_is_in_special_class_range(locked))
                || !*(u8 *)(locked + 0x31) || ((Hero *)g_hero_state)->h[0x24EC / 2]) {
                target = 0;
                *(short *)(state + 4) = -1;
                *(int *)state = 0;
                *(int *)(state + 8) = 0;
            } else {
                ((Hero *)g_hero_state)->ptr[0xBF8 / 4] = locked;
            }
        }
    }
    if (!((Hero *)g_hero_state)->i[0x1500 / 4] && *(u8 *)(moby + 0x20) == 1 && !((Hero *)g_hero_state)->h[0x24EC / 2] && *(short *)(state + 6) == 0) {
        char *candidate;
        vec_build_spherical_offset(offset, 1.0f, ((Hero *)g_hero_state)->f[0x778 / 4], ((Hero *)g_hero_state)->f[0x774 / 4]);
        candidate = moby_get_or_find_target(playerPoint, offset, vertical, horizontal, previousRange, 0.7853982449f, 0.6108652949f, 1);
        if (candidate) {
            if (candidate == *(char **)(state + 0x30)) {
                if (math_fast_float_d(state + 0x34)) {
                    float *component;
                    target = candidate;
                    *(char **)state = target;
                    *(short *)(state + 4) = *(short *)(target + 0xAA);
                    *(int *)(state + 8) = 0;
                    *(short *)(state + 6) = ((s32)(TYPE(moby) == 0x5D2 ? g_lancer_state_short : g_other_weapon_state_short) * 5 + 2) / 6;
                    component = moby_get_private_value_0(candidate);
                    if (component) {
                        *(float *)(state + 8) = component[4];
                        FastVecScale(direction, *(char **)state + 0xE0, component[4]);
                        FastVecAdd(targetPosition, *(char **)state + 0x10, direction);
                    } else {
                        qcopy(targetPosition, *(char **)state + 0x10);
                    }
                }
            } else {
                *(int *)(state + 0x34) = ((s32)(TYPE(moby) == 0x5D2 ? g_lancer_state_int : g_other_weapon_state_int) * 5 + 2) / 6;
            }
        } else {
            *(int *)state = 0;
            *(short *)(state + 4) = -1;
            *(int *)(state + 8) = 0;
            target = 0;
            if (TYPE(moby) == 0x5D2)
                *(int *)(state + 0x34) = ((s32)g_lancer_state_int * 5 + 2) / 6;
            else
                *(int *)(state + 0x34) = ((s32)g_other_weapon_state_int * 5 + 2) / 6;
        }
        *(char **)(state + 0x30) = candidate;
    } else if (((Hero *)g_hero_state)->i[0x1500 / 4]) {
        *(int *)state = 0;
    }
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 29 || ((Hero *)g_hero_state)->i[0x1500 / 4]) {
        hud_add_moby_marker(moby, 1.0f, *(float *)(state + 0xC) > 0.0f && get_ammo(-1) ? 0x600000FF : 0x600FFF0F, 0, 0x26, 0.0f, -1, 90.0f, 4);
    }
    if (*(char **)state) {
        float distance = fast_vec_dist(g_camera_l00_position, targetPosition);
        hud_add_moby_marker(moby, math_fabs(0.9f - distance * 0.006666667f * 0.65f), 0xFF0FFF0F, targetPosition, 0x26, 0.0f, -1, 90.0f, 4);
    }
    if (*(int *)(state + 0x28) > 0
        && (*(int *)(state + 0x28) > 6 || !(g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) || !get_ammo(-1)))
        (*(int *)(state + 0x28))--;
    if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43) && (*(u8 *)(moby + 0x60) & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    switch (*(u8 *)(moby + 0x20)) {
    case 1: {
        int ready;
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
            hero_l00_set_action_pal(29, 1);
        ready = 1;
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 29)
        {
            ready = 0;
            if (math_fast_float_d(&((Hero *)g_hero_state)->i[0x2534 / 4]))
                ready = 1;
        }
        else
            ((Hero *)g_hero_state)->i[0x2534 / 4] = 33;
        if (vec_fast_helper_b(state + 0xC) && !((Hero *)g_hero_state)->b[0x22BC] && (g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                int count, i;
                g_lancer_fire_held = 1;
                if (g_progress_statistics[33].count < 0xFFFF)
                    g_progress_statistics[33].count++;
                if (((s32)g_frame_counter * 5 + 2) / 6 > g_progress_statistics[33].maximum)
                    g_progress_statistics[33].maximum = ((s32)g_frame_counter * 5 + 2) / 6;
                g_progress_statistics[33].levels = (g_progress_statistics[33].levels | (1u << g_current_map_index)) | 0x80000000u;
                if (TYPE(moby) == 0x5D2)
                    EmitParticleTrailLayers_pal(moby);
                else
                    part_spawn_line_at_moby_pal(moby);
                if (*(short *)(state + 0x10) == 0) {
                    start_equipped_item_animation_pal();
                    *(short *)(state + 0x10) = 1;
                }
                if (*(u8 *)(moby + 0x43) != 2)
                    anim_start_blended_pal(moby, 2, 0, 0);
                if (*(int *)(state + 0x24) == -1)
                    *(int *)(state + 0x24) = gfx_add_point_light(moby + 0x10, 0, 4.0f, 0.0f);
                *(int *)(state + 0x28) = 8;
                snd_play_from_class_bank(0, 0, moby, TYPE(moby));
                if (TYPE(moby) == 0x5D2)
                    actuator_play_waves(g_lancer_shot_rumble_waves);
                else if (*(int *)(state + 0x3C) < 0)
                    *(int *)(state + 0x3C) = actuator_play_waves(g_lancer_held_rumble_waves);
                if (TYPE(moby) == 0x5D2)
                    CreateTargetedMovingEffect_pal(muzzle, moby, target, previousRange);
                else
                    SpawnAimedShot_pal(muzzle, moby, target);
                {
                    WeaponEntry *entry = g_item_slot_to_record[0x1E] + g_weapon_l00_table;
                    *(float *)(state + 0xC) = 1.0f / entry->rate;
                }
                count = coll_process_hit(0.5f, muzzle, 0, moby, 0);
                for (i = 0; i < count; i++) {
                    float *component;
                    if (g_area_hit_targets[i] == ((Hero *)g_hero_state)->ptr[0x2290 / 4])
                        continue;
                    component = moby_get_private_value_0(g_area_hit_targets[i]);
                    if (!component)
                        continue;
                    *(int *)(damage + 0x14) = 0x10000;
                    *(int *)(damage + 0x20) = 1;
                    *(char **)(damage + 0x10) = moby;
                    *(float *)(damage + 0x1C) = (g_item_slot_to_record[0x1E] + g_weapon_l00_table)->damage;
                    FastVecSub(offset, g_area_hit_targets[i] + 0x10, muzzle);
                    vec_scale_to_length(offset, offset, (g_item_slot_to_record[0x1E] + g_weapon_l00_table)->speed * 0.020000001f);
                    qcopy(damage, offset);
                    vec_scale_to_length(damage, damage, 1.0f);
                    *(float *)(damage + 0xC) = 5627.9248046875f;
                    *(short *)(damage + 0x1A) = TYPE(moby);
                    *(u8 *)(damage + 0x18) = 1;
                    *(u8 *)(damage + 0x19) = 1;
                    QueueMobyImpact(g_area_hit_targets[i], damage);
                    cam_compute_view_direction(g_area_hit_targets[i] + 0x10, direction, 1);
                    FastVecScale(direction, direction, component[4]);
                    FastVecAdd(center, direction, g_area_hit_targets[i] + 0x10);
                    part_l00_spawn_spark_burst_3_pal(center, 0x19, 1);
                }
            } else {
                if ((g_pad_state[0x1A4 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) || g_lancer_fire_held == 1) {
                    PlayMobySound(1, 0, moby);
                    g_lancer_fire_held = 0;
                }
                {
                    WeaponEntry *entry = g_item_slot_to_record[0x1E] + g_weapon_l00_table;
                    *(float *)(state + 0xC) = 1.0f / entry->rate;
                }
            }
        }
        if (!((g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) && get_ammo(-1) && ((Hero *)g_hero_state)->b[0x22B8])) {
            if (*(int *)(state + 0x3C) >= 0) {
                actuator_end_looping_waves(*(int *)(state + 0x3C));
                *(int *)(state + 0x3C) = -1;
            }
        }
        if (*(int *)(state + 0x3C) > 0 && !actuator_is_channel_active(*(int *)(state + 0x3C) - 1))
            *(int *)(state + 0x3C) = -1;
        if (!((g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) && get_ammo(-1))
            && !(((Hero *)g_hero_state)->i[0x1D8 / 4] < 8 && ((Hero *)g_hero_state)->b[0x22B8])) {
            cancel_hero_item_animation_pal();
            *(short *)(state + 0x10) = 0;
        }
        break;
    }
    case 2:
        cancel_hero_item_animation_pal();
        if (vec_fast_helper_b(state + 0xC))
            *(u8 *)(moby + 0x20) = 1;
        break;
    }
    if (*(int *)(state + 0x24) != -1) {
        if (specialMode || *(int *)(state + 0x28) <= 0) {
            gfx_free_point_light(*(int *)(state + 0x24));
            *(int *)(state + 0x24) = -1;
        } else {
            float ratio;
            qzero_nc(offset);
            offset[0] = 2.0f;
            offset[2] = 2.0f;
            matrix_mul_vec3(offset, offset, &((Hero *)g_hero_state)->f[0x730 / 4]);
            (*(int *)(state + 0x24) + g_light_table)->position[0] = ((Hero *)g_hero_state)->f[0x80 / 4] + offset[0];
            (*(int *)(state + 0x24) + g_light_table)->position[1] = ((Hero *)g_hero_state)->f[0x84 / 4] + offset[1];
            (*(int *)(state + 0x24) + g_light_table)->position[2] = ((Hero *)g_hero_state)->f[0x88 / 4] + offset[2];
            (*(int *)(state + 0x24) + g_light_table)->position[3] = 4.0f;
            {
                float b;
                ratio = IntToFloat(*(int *)(state + 0x28));
                b = IntToFloat(8);
                ratio /= b;
                /* Both weapons light the muzzle the same way. */
                if (TYPE(moby) == 0x5D2) {
                    (*(int *)(state + 0x24) + g_light_table)->radius = ratio;
                    (*(int *)(state + 0x24) + g_light_table)->spread = ratio * 0.5f;
                    (*(int *)(state + 0x24) + g_light_table)->power = (*(int *)(state + 0x24) + g_light_table)->spread;
                } else {
                    (*(int *)(state + 0x24) + g_light_table)->radius = ratio;
                    (*(int *)(state + 0x24) + g_light_table)->spread = ratio * 0.5f;
                    (*(int *)(state + 0x24) + g_light_table)->power = (*(int *)(state + 0x24) + g_light_table)->spread;
                }
            }
        }
    }
}
