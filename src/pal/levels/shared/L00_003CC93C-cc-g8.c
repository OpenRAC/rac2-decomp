/* func_PAL_L00_003CC93C, the PAL copy of func_L00_003C8A90: the same C, where rename-macro func_L03_002C6F08 and rename func_L00_002C42E0 become func_PAL_L00_002C4480; rename func_L00_002AF568 becomes func_PAL_L00_002AF458; rename func_L00_003C94D8 becomes func_PAL_L00_003CD388; rename func_L00_00409E48 becomes func_PAL_L00_0040E9F0; rename func_L00_002AF7D0 becomes func_PAL_L00_002AF6C0. */
/* func_PAL_L00_003CC93C (UpdateLockOnWeapon): gathers the mobys in a cone ahead of the weapon, marks
 * each one, fires a shot at the target with a cooldown from the weapon table and sets a muzzle
 * light. It needs its own unit for -frac2-zero-ti-por and -frac2-hazard-labels.
 */
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
    u8 pad43[5];
    float scale;
    u8 pad4C[0x14];
    u8 flags;
    u8 pad61[7];
    void *vars;
    u8 pad6C[0x3E];
    s16 objectClass;
    u8 padAC[0xC];
    Moby *owner;
    u8 padBC[4];
    Vector right;
    Vector forward;
    Vector up;
};

typedef struct {
    float cooldown;
    u8 pad04[0xC];
    Moby *target;
    u8 pad14[8];
    s16 light;
    s16 timer;
    int unknown20;
    int sound;
} Vars;

typedef struct { float red, green, blue, pad0C; Vector pos; } Light;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;
typedef struct { int a, b, c; } AimConfig;
typedef float Vec[4] __attribute__((aligned(16)));

extern u8 g_hero_state[];
extern u32 g_pad_state[];
extern u8 g_item_slot_to_record[];
extern int g_game_l00_mode;
extern int g_charge_weapon_fire_held;
extern AimConfig g_charge_aim_config;
extern float g_camera_l00_position[];
extern Moby *g_area_hit_targets[];
extern CollisionResult g_collision_result;
extern WeaponEntry g_weapon_l00_table[];
extern Light g_light_table[];
extern u8 g_lock_on_weapon_rumble_waves[];
extern u8 g_default_vector[] __attribute__((sda));

extern int vec_fast_helper_b(void *);
extern int hero_l00_set_action_pal(int, int);
extern int math_fast_float_d(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void mem_fast_helper_b(void *, int);
extern void ReleaseDeadOrExpiredSlots(void *);
extern char *SelectBestTargetInCone(void *, void *, float, float, void *, void *, int, int, float, float, float, int, void *);
extern char *moby_get_private_value_0(void *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern void hud_add_moby_marker(void *, float, unsigned int, void *, int, float, int, float, int);
extern int get_ammo(int);
extern void start_equipped_item_animation_pal(void);
extern int coll_process_hit(float, void *, int, void *, void *);
extern int moby_is_in_special_class_range(void *);
extern int PlayMobySound(int, int, void *);
extern void weapon_spawn_muzzle_burst_pal(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int actuator_play_waves(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern char *pair_choose_owner_for_key(void *, void *, int, int *, int);
extern void KeyOwnerTableInsert(void *, void *, int);
extern Moby *aimed_projectile_spawn_pal(void *, void *, void *, void *, float, float, float, float);
extern int weapon_spend_ammo(int, int);
extern void actuator_end_looping_waves(int);
extern void cancel_hero_item_animation_pal(void);
extern float IntToFloat(int);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern int FastDecTimer(void *);
extern void gfx_free_point_light(int);


static __inline__ void MarkTarget(void *moby, float alpha, unsigned int color, void *position, int kind, float a, int b, float c, int d)
{
    hud_add_moby_marker(moby, alpha, color, position, kind, a, b, c, d);
}

void UpdateLockOnWeapon_pal(Moby *moby)
{
    Vars *vars = moby->vars;
    Vector direction, origin, aim;
    Moby *list[32];
    int count;
    int ready;
    int i, j;
    Moby *target;
    int animation;
    Moby **mobys;

    if (moby->state == 0) {
        vars->timer = 0;
        vars->light = -1;
        vars->target = 0;
        vars->unknown20 = 0;
        moby->state = 1;
        vars->sound = -1;
    }
    vec_fast_helper_b(vars);
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
        hero_l00_set_action_pal(0x1D, 1);
    ready = 1;
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D) {
        if (math_fast_float_d(&((Hero *)g_hero_state)->i[0x2534 / 4]) == 0)
            ready = 0;
    } else {
        ((Hero *)g_hero_state)->i[0x2534 / 4] = 0x21;
    }
    if (((Hero *)g_hero_state)->i[0x1450 / 4] != 0)
        ((Hero *)g_hero_state)->i[0xBF8 / 4] = ((Hero *)g_hero_state)->i[0x1450 / 4];
    vars->unknown20 = 0;
    if (((Hero *)g_hero_state)->h[0x24EC / 2] != 0) {
        FastVecScale(&direction, &moby->forward, -1.0f);
    } else {
        qcopy(&direction, &((Hero *)g_hero_state)->q[0x760 / 16]);
    }
    FastVecScale(&origin, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.75f);
    FastVecAdd(&origin, &((Hero *)g_hero_state)->q[0x80 / 16], &origin);
    count = 0;
    mem_fast_helper_b(list, 0x80);
    ReleaseDeadOrExpiredSlots(moby);
    /* Two scopes: config shares its slot with the vectors declared further down. */
    {
    {
        AimConfig config = g_charge_aim_config;

        SelectBestTargetInCone(&moby->position, &direction, 0.436332345f, 0.436332345f, &count, list, 0x20, 0, 48.0f, 0.785398245f, 0.785398245f, 1, &config);
    }
    }
    i = 0;
    mobys = list;
    if (count > 0) {
        do {
            float height = 0.0f;
            float *info = (float *)moby_get_private_value_0(mobys[i]);

            if (info != 0)
                height = info[4];
            if (((Hero *)g_hero_state)->i[0x1450 / 4] == 0) {
                float distance = fast_vec_dist(g_camera_l00_position, &mobys[i]->position) * 0.00666666683f;

                FastVecScale(&aim, &mobys[i]->up, height);
                FastVecAdd(&aim, &mobys[i]->position, &aim);
                MarkTarget(moby, math_fabs(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            }
            i++;
        } while (i < count);
    }
    target = 0;
    if (g_game_l00_mode == 0 && vars->cooldown == 0.0f && ((Hero *)g_hero_state)->b[0x22BC] == 0 &&
        (g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) && ((Hero *)g_hero_state)->i[0x1240 / 4] >= 0x13 && ready != 0) {
        if (((Hero *)g_hero_state)->i[0x1450 / 4] != 0)
            ((Hero *)g_hero_state)->i[0xBF8 / 4] = ((Hero *)g_hero_state)->i[0x1450 / 4];
        if (get_ammo(-1)) {
            Vec start, step, muzzle, offset;
            int hits;
            float strength;
            float *info;
            Moby *shot;

            start_equipped_item_animation_pal();
            FastVecScale(start, &moby->forward, -1.0f);
            FastVecAdd(start, start, &moby->position);
            FastVecScale(step, &moby->right, 0.275f);
            FastVecAdd(start, start, step);
            hits = coll_process_hit(1.0f, start, 1, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0);
            if (hits != 0) {
                for (j = 0; j < hits; j++) {
                    Moby *hit = g_area_hit_targets[j];
                    float *hp = (float *)moby_get_private_value_0(hit);

                    if (hit->alive != 0 && hit->health > 0 && hit != 0 && hit->state != 0xFE && hit->state != 0xFD &&
                        hit->objectClass != 0xC87 && hit->objectClass != 0xECC && hp != 0 &&
                        (*hp > 0.0f || moby_is_in_special_class_range(hit) != 0) && (hit->model == 0 || hit->model->kind != 5)) {
                        target = g_collision_result.hit;
                        vars->target = target;
                        break;
                    }
                }
            }
            strength = 0.0f;
            PlayMobySound(1, 0, moby);
            vars->timer = 0xc;
            weapon_spawn_muzzle_burst_pal(moby);
            anim_start_blended_with_flags(moby, 2, 0, 1, 0);
            moby->scale = 0.9f;
            vars->sound = actuator_play_waves(g_lock_on_weapon_rumble_waves);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            matrix_mul_vec3(offset, offset, &moby->right);
            FastVecAdd(muzzle, &moby->position, offset);
            if (target == 0) {
                int locked = 0;

                target = (Moby *)pair_choose_owner_for_key(moby, list, count, &locked, -1);
                if (target == 0)
                    goto fire;
                if (locked != 0)
                    KeyOwnerTableInsert(moby, target, 0x11);
            }
            info = (float *)moby_get_private_value_0(target);
            if (info != 0)
                strength = info[4];
        fire:
            if (((Hero *)g_hero_state)->ptr[0xBF8 / 4] != 0)
                shot = aimed_projectile_spawn_pal(moby, muzzle, ((Hero *)g_hero_state)->ptr[0xBF8 / 4], g_default_vector, strength, 2.0f, 5.0f, 0.6f);
            else
                shot = aimed_projectile_spawn_pal(moby, muzzle, target, g_default_vector, strength, 2.0f, 5.0f, 0.6f);
            if (shot != 0)
                shot->owner = moby;
            weapon_spend_ammo(-1, 1);
            g_charge_weapon_fire_held = 1;
        } else if ((g_pad_state[0x1A4 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) || g_charge_weapon_fire_held == 1) {
            PlayMobySound(2, 0, moby);
            g_charge_weapon_fire_held = 0;
        }
        if (!(g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) || ((Hero *)g_hero_state)->b[0x22B8] == 0) {
            if (vars->sound >= 0) {
                actuator_end_looping_waves(vars->sound);
                vars->sound = -1;
                cancel_hero_item_animation_pal();
            }
        }
        {
            WeaponEntry *weapon = (WeaponEntry *)(g_item_slot_to_record[0x2C] * 0xE0 + (char *)g_weapon_l00_table);

            vars->cooldown = 1.0f / weapon->rate;
        }
    }
    animation = moby->animation;
    if (animation == 2) {
        if (moby->flags & 2)
            anim_start_blended_with_flags(moby, 1, 0, 1, 0);
        if (moby->animation == animation)
            goto done;
    }
    if (vars->timer > 0) {
        float red, green, blue, t;
        Vec spot, flash, offset;

        if (vars->timer >= 0xb) {
            float scale = 1.0f / IntToFloat(2);

            red = IntToFloat(0xc - vars->timer) * scale;
            green = IntToFloat(0xc - vars->timer) * (scale * 0.8f);
            t = IntToFloat(0xc - vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        } else {
            float scale = 1.0f / IntToFloat(0xa);

            red = IntToFloat(vars->timer) * scale;
            green = IntToFloat(vars->timer) * (scale * 0.8f);
            t = IntToFloat(vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        }
        if (((Hero *)g_hero_state)->h[0x24EC / 2] != 0) {
            FastVecScale(flash, &moby->forward, -1.0f);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            matrix_mul_vec3(offset, offset, &moby->right);
            FastVecAdd(spot, &moby->position, offset);
        } else {
            qcopy(flash, &((Hero *)g_hero_state)->q[0x760 / 16]);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            matrix_mul_vec3(offset, offset, &moby->right);
            FastVecAdd(spot, &moby->position, offset);
        }
        FastVecAdd(spot, spot, flash);
        FastVecScale(offset, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.3f);
        FastVecAdd(spot, spot, offset);
        if (vars->light == -1) {
            vars->light = part_l00_alloc_effect_slot_2(spot, 8.0f, 0.0f, red, green, blue);
        } else {
            Light *light = &g_light_table[vars->light];

            qcopy(&light->pos, spot);
            light->pos.f[3] = 8.0f;
            light->red = red;
            light->green = green;
            light->blue = blue;
        }
        FastDecTimer(&vars->timer);
        return;
    }
done:
    if (vars->light != -1) {
        gfx_free_point_light(vars->light);
        vars->light = -1;
        vars->timer = 0;
    }
}
