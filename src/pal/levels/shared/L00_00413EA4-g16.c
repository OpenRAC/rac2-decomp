#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;
typedef struct Moby Moby;
struct Moby {
    u8 pad00[0x10];
    Vector position;
    u8 state;
    u8 pad21[3];
    struct { u8 pad00[0x46]; s16 kind; } *model;
    u8 pad28[9];
    u8 alive;
    s16 health;
    u8 pad34[0xE];
    u8 animation;
    u8 nextAnimation;
    u8 pad44[0x1C];
    u8 flags;
    u8 pad61[7];
    void *vars;
    u8 pad6C[0x3E];
    s16 objectClass;
    u8 padAC[0x14];
    Vector right;
    Vector forward;
    Vector up;
};
typedef struct {
    Moby *target;
    int lockTimer;
    float lockHeight;
    s16 light;
    s16 flash;
    Moby *candidate;
    int candidateTimer;
    s16 aiming;
    s16 charge;
    float cooldown;
    int unknown20;
    int sound;
    int beam;
    int beamTimer;
    int chargeSound;
    int unknown34;
} BlasterVars;
typedef struct { u8 pad00[4]; u8 active; u8 pad05[0x13]; Moby *owner; u8 pad1C[0x54]; } SoundSlot;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;
extern u8 g_hero_state[], g_item_slot_to_record[];
extern u32 g_pad_state[];
extern int g_item_ammo_counts[];
extern u16 g_subtitle_history[];
extern SoundSlot g_sound_state[];
extern int g_game_l00_mode MACRO_ADDR;
extern Vector g_megarocket_nozzle_offset __attribute__((sda));
extern float g_camera_l00_position[];
extern Moby *g_area_hit_targets[];
extern CollisionResult g_collision_result;
extern WeaponEntry g_weapon_table_2[];
extern u8 g_megarocket_sound_records[];
extern s32 hero_l00_set_action_pal(int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int vec_fast_helper_b(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int get_ammo(int);
extern void hud_add_moby_marker(void *, float, unsigned int, void *, int, float, int, float, int);
extern Moby *moby_get_or_find_target(void *, void *, float, float, float, float, float, int);
extern float *moby_get_private_value_0(Moby *);
extern int moby_is_in_special_class_range(Moby *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern int math_fast_float_d(int *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void ref_L00_0040F6A0_00(void (*)(Moby *), Moby *);
extern void charge_draw_glow_sprites_pal(Moby *);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void *part_spawn_burst_pal(void *, void *, int, int, unsigned int, int, float, float, float, float, float);
extern int object_value_to_grade_pal(Moby *);
extern int coll_process_hit(float, void *, int, void *, void *);
extern void particle_burst_around_object_pal(Moby *, int);
extern void charge_shot_start_effect_pal(Moby *, Vector *, int);
extern void start_equipped_item_animation_pal(void);
extern int actuator_play_waves(void *);
extern int subtitle_request_voice_line_pal(int, int);
extern void actuator_end_looping_waves(int);
extern void sequenced_child_spawn_pal(Moby *, Vector *);
extern void light_flash_update_pal(Moby *, Vector *);
#define HERO ((Hero *)D_00189E20)

/* Charges and fires the blaster: target acquisition, charge sparks and release. */
void megarocket_cannon_update_pal(Moby *moby)
{
    BlasterVars *vars = moby->vars;
    Vector nozzle, direction, origin, aim, work, spark;
    int ready, released, charged;
    float spread;
    Moby *candidate; /* the cone pick, then the locked target */

    if (moby->state == 0) {
        moby->state = 1;
        vars->light = -1;
        vars->candidateTimer = 4;
        vars->flash = 0;
        vars->target = 0;
        vars->candidate = 0;
        vars->aiming = 0;
        vars->charge = 0;
        vars->unknown20 = 0;
        vars->sound = -1;
        vars->unknown34 = -1;
        vars->beam = -1;
        vars->chargeSound = -1;
    }
    if (HERO->i[0x2294 / 4] == 1)
        hero_l00_set_action_pal(0x1D, 1);
    matrix_mul_vec3(&nozzle, &g_megarocket_nozzle_offset, &moby->right);
    FastVecAdd(&nozzle, &nozzle, &moby->position);
    if (HERO->i[0x1450 / 4] != 0)
        HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];

    if (HERO->i[0x2294 / 4] == 0x1D && (*(u16 *)(HERO->ptr[0x2290 / 4] + 0x34) & 1)) {
        unsigned int color;
        if (vars->aiming == 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        }
        vars->aiming = 1;
        spread = 0.06981317699f;
        if (vars->cooldown > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(moby, 1.25f, color, 0, 0x27, 0.0f, -1, 90.0f, 4);
        qcopy(&direction, &HERO->q[0x760 / 16]);
        FastVecScale(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &HERO->q[0x80 / 16], &origin);
    } else {
        vars->aiming = 0;
        spread = 0.349065899848938f;
        if (HERO->h[0x24EC / 2] != 0) {
            FastVecScale(&direction, &moby->forward, -1.0f);
            } else {
            qcopy(&direction, &HERO->q[0x760 / 16]);
            }
        FastVecScale(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &HERO->q[0x80 / 16], &origin);
    }
    vec_fast_helper_b(&vars->cooldown);
    if (moby->animation == moby->nextAnimation && (moby->flags & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    candidate = moby_get_or_find_target(&origin, &direction, spread, spread, 75.0f, spread, spread, 1);

    if (vars->target != 0) {
        float *hp = moby_get_private_value_0(vars->target);
        if (vars->target == 0 || vars->target->state == 0xFE || vars->target->state == 0xFD ||
            (hp != 0 && *hp <= 0.0f) || vars->target->alive == 0 || HERO->h[0x24EC / 2] != 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        } else if (candidate != vars->target) {
            if (math_fast_float_d(&vars->lockTimer)) {
                vars->target = 0;
                vars->candidateTimer = 4;
            }
        } else {
            float distance;
            vars->lockTimer = 4;
            distance = fast_vec_dist(g_camera_l00_position, &candidate->position) * 0.006666667f;
            FastVecScale(&aim, &candidate->up, vars->lockHeight);
            FastVecAdd(&aim, &candidate->position, &aim);
            hud_add_moby_marker(moby, math_fabs(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            HERO->ptr[0xBF8 / 4] = (char *)candidate;
        }
    } else if (candidate == vars->candidate) {
        if (math_fast_float_d(&vars->candidateTimer)) {
            float *health;
            vars->target = candidate;
            vars->lockTimer = 4;
            health = moby_get_private_value_0(candidate);
            if (health == 0)
                vars->lockHeight = 0.1f;
            else
                vars->lockHeight = health[4];
        }
    } else {
        vars->candidateTimer = 4;
    }
    vars->candidate = candidate;
    candidate = vars->target;

    ready = 1;
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (!math_fast_float_d(&HERO->i[0x2534 / 4]))
            ready = 0;
    } else {
        HERO->i[0x2534 / 4] = 0x21;
    }

    released = 0;
    charged = 0;
    if ((g_pad_state[0x1A0 / 4] & HERO->u[0x1230 / 4]) && get_ammo(-1)) {
        SoundSlot *slot = &g_sound_state[vars->chargeSound];
        int level;
        vars->charge++;
        if (slot[1].owner != moby || !slot[1].active)
            vars->chargeSound = PlayMobySound(6, 4, moby);
        ref_L00_0040F6A0_00(charge_draw_glow_sprites_pal, moby);
        level = g_item_ammo_counts[HERO->i[0x1248 / 4]];
        if (level >= 5)
            level = 4;
        if (level * 18 < vars->charge) {
            float size;
            int life;
            math_apply_axis_rotation_to_quat(&work, &moby->up, &moby->forward, math_random_angle());
            FastVecScale(&work, &work, math_random_float_range(1.5f, 2.0f) * 0.020000001f);
            life = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
            size = math_random_float_range(0.45f, 0.75f) * 210000.0f;
            spark.f[0] = nozzle.f[0] + math_random_signed_float_range(0.0f, 0.1f);
            spark.f[1] = nozzle.f[1] + math_random_signed_float_range(0.0f, 0.1f);
            spark.f[2] = nozzle.f[2] + math_random_signed_float_range(0.0f, 0.1f);
            part_spawn_burst_pal(&spark, &work, 12, 0x7F, 0x7F7F7F, life, size, 500.0f, 1.0f, 0.0f, 0.0f);
        }
    } else {
        if (vars->chargeSound != -1) {
            SoundSlot *slot = &g_sound_state[vars->chargeSound];
            if (slot[1].owner == moby && slot[1].active)
                snd_stop_voice(vars->chargeSound);
        }
        vars->chargeSound = -1;
        if ((g_pad_state[0x1A4 / 4] & HERO->u[0x1230 / 4]) && !get_ammo(-1))
            PlayMobySound(1, 0, moby);
        if (vars->charge != 0) {
            released = 1;
            charged = object_value_to_grade_pal(moby);
        }
        vars->charge = 0;
        vars->unknown20 = 0;
    }

    if (g_game_l00_mode == 0 && vars->cooldown == 0.0f && HERO->b[0x22BC] == 0 && ready && released &&
        HERO->i[0x1240 / 4] >= 19) {
        if (get_ammo(-1)) {
            if (candidate == 0) {
                int count, i;
                FastVecScale(&work, &moby->forward, -1.0f);
                FastVecAdd(&work, &work, &moby->position);
                FastVecScale(&spark, &moby->right, 0.275f);
                FastVecAdd(&work, &work, &spark);
                count = coll_process_hit(1.0f, &work, 1, HERO->ptr[0x2290 / 4], 0);
                if (count != 0) {
                    for (i = 0; i < count; i++) {
                        Moby *hit = g_area_hit_targets[i];
                        float *hp = moby_get_private_value_0(hit);
                        if (hit->alive == 0)
                            continue;
                        if (hit->health <= 0)
                            continue;
                        if (hit == 0)
                            continue;
                        if (hit->state == 0xFE)
                            continue;
                        if (hit->state == 0xFD)
                            continue;
                        if (hit->objectClass == 0xC87)
                            continue;
                        if (hit->objectClass == 0xECC)
                            continue;
                        if (hp == 0)
                            continue;
                        if (!(*hp > 0.0f) && !moby_is_in_special_class_range(hit))
                            continue;
                        if (hit->model == 0 || hit->model->kind != 5) {
                            candidate = g_collision_result.hit;
                            vars->target = candidate;
                            break;
                        }
                    }
                }
            }
            vars->flash = 12;
            particle_burst_around_object_pal(moby, charged);
            charge_shot_start_effect_pal(moby, &nozzle, charged);
            anim_start_blended_with_flags(moby, 2, 0, 2, 0);
            start_equipped_item_animation_pal();
            vars->sound = actuator_play_waves(g_megarocket_sound_records);
            if (charged)
                g_subtitle_history[0x3A8 / 2] = 0xFFFF;
            else if (g_subtitle_history[0x3A8 / 2] < 40 && ++g_subtitle_history[0x3A8 / 2] == 40)
                subtitle_request_voice_line_pal(0x9F7, 0x4E);
        }
        if (!((g_pad_state[0x1A0 / 4] & HERO->u[0x1230 / 4]) && get_ammo(-1) && HERO->b[0x22B8]) &&
            vars->sound >= 0) {
            actuator_end_looping_waves(vars->sound);
            vars->sound = -1;
        }
        {
            WeaponEntry *weapon = g_weapon_table_2 + g_item_slot_to_record[0x1B];
            vars->cooldown = 1.0f / weapon->rate;
        }
    }

    if (vars->beam >= 0 && math_fast_float_d(&vars->beamTimer))
        sequenced_child_spawn_pal(moby, &nozzle);
    light_flash_update_pal(moby, &nozzle);
}
