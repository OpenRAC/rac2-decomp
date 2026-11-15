/* func_PAL_L00_003A7ED8, the PAL copy of func_L00_003A48D0: the same C, where rename func_L00_003A41F0 becomes func_PAL_L00_003A77D8; rename func_L00_002C42E0 becomes func_PAL_L00_002C4480; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_003A4480 becomes func_PAL_L00_003A7A68; rename func_L00_003A5370 becomes func_PAL_L00_003A8978; rename func_L00_002D2168 becomes func_PAL_L00_002D2668; rename func_L00_002AF568 becomes func_PAL_L00_002AF458; lit 10 becomes 12. */
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
    float cooldown;
    u8 pad04[0xC];
    Moby *target;
    int lockTimer;
    float lockHeight;
    s16 light;
    s16 flash;
    Moby *candidate;
    int candidateTimer;
    int aiming;
    int sound;
} TurretVars;

typedef struct { float radius, spread, power, reserved; Vector position; } MuzzleLight;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;

extern u8 g_hero_state[], g_item_slot_to_record[];
extern Vector g_hero_position;
extern u32 g_pad_state[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001B2864 MACRO_ADDR;
extern float g_camera_l00_position[];
extern Moby *g_area_hit_targets[];
extern CollisionResult g_collision_result;
extern MuzzleLight D_L00_001C6F40[];
extern WeaponEntry D_00262570[];
extern u8 D_00294880[];

extern void func_PAL_L00_003A77D8(void *);
extern int vec_fast_helper_b(void *);
extern int func_PAL_L00_002C4480(int, int);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern void hud_add_moby_marker(void *, float, unsigned int, void *, int, float, int, float, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern Moby *moby_get_or_find_target(void *, void *, float, float, float, float, float, int);
extern int moby_get_private_value_0(Moby *);
extern int moby_is_in_special_class_range(Moby *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern float IntToFloat(int);
extern int math_fast_float_d(int *);
extern int FastDecTimer(short *);
extern int PlayMobySound(int, int, void *);
extern int coll_process_hit(float, void *, int, void *, void *);
extern void func_PAL_L00_003A7A68(Moby *);
extern void func_PAL_L00_003A8978(Moby *);
extern void func_PAL_L00_002D2668(int, int, float);
extern void func_PAL_L00_002AF458(void);
extern void slot_reset_active(int);
extern int slot_copy_records_to_free(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern void gfx_free_point_light(int);


/* Acquires a stable target, fires and drives the short muzzle light. */
void func_PAL_L00_003A7ED8(Moby *moby)
{
    TurretVars *vars = moby->vars;
    Vector direction, origin, aim, muzzle, offset, lift;
    float horizontal, vertical;
    Moby *candidate;
    int ready;

    if (moby->state == 0) {
        moby->state = 1;
        vars->light = -1;
        vars->candidateTimer = 4;
        vars->sound = -1;
        vars->flash = 0;
        vars->target = 0;
        vars->candidate = 0;
        vars->aiming = 0;
    }
    func_PAL_L00_003A77D8(moby);
    vec_fast_helper_b(vars);
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
        func_PAL_L00_002C4480(0x1D, 1);
    if (moby->animation == moby->nextAnimation && (moby->flags & 2))
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    if (((Hero *)g_hero_state)->i[0x1450 / 4] != 0)
        ((Hero *)g_hero_state)->i[0xBF8 / 4] = ((Hero *)g_hero_state)->i[0x1450 / 4];

    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D && (*(u16 *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x34) & 1)) {
        unsigned int color;
        if (vars->aiming == 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        }
        vars->aiming = 1;
        horizontal = vertical = 0.06981317699f;
        if (vars->cooldown > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(moby, 1.25f, color, 0, 0x27, 0.0f, -1, 90.0f, 4);
        qcopy(&direction, &((Hero *)g_hero_state)->q[0x760 / 16]);
        FastVecScale(&origin, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &((Hero *)g_hero_state)->q[0x80 / 16], &origin);
    } else {
        vars->aiming = 0;
        horizontal = 0.3141593039f;
        vertical = 0.2967059910f;
        if (((Hero *)g_hero_state)->h[0x24EC / 2] != 0)
            FastVecScale(&direction, &moby->forward, -1.0f);
        else
            qcopy(&direction, &((Hero *)g_hero_state)->q[0x760 / 16]);
        FastVecScale(&origin, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &((Hero *)g_hero_state)->q[0x80 / 16], &origin);
    }
    candidate = moby_get_or_find_target(&origin, &direction, horizontal, vertical, 75.0f, horizontal, horizontal, 1);

    if (vars->target != 0) {
        float *hp = ((float *)moby_get_private_value_0(vars->target));
        if (vars->target == 0 || vars->target->state == 0xFE || vars->target->state == 0xFD ||
            (hp != 0 && *hp <= 0.0f) || vars->target->alive == 0 || ((Hero *)g_hero_state)->h[0x24EC / 2] != 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        } else if (candidate != vars->target) {
            if (math_fast_float_d(&vars->lockTimer)) {
                vars->target = 0;
                vars->candidateTimer = 4;
            }
        } else {
            float distance;
            float *health;
            vars->lockTimer = 4;
            distance = fast_vec_dist(g_camera_l00_position, &candidate->position) * 0.006666667f;
            health = ((float *)moby_get_private_value_0(candidate));
            vars->lockHeight = health ? health[4] : 0.1f;
            FastVecScale(&aim, &candidate->up, vars->lockHeight);
            FastVecAdd(&aim, &candidate->position, &aim);
            hud_add_moby_marker(moby, math_fabs(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            ((Hero *)g_hero_state)->ptr[0xBF8 / 4] = (char *)candidate;
        }
    } else if (candidate == vars->candidate) {
        if (math_fast_float_d(&vars->candidateTimer)) {
            float *health;
            vars->target = candidate;
            vars->lockTimer = 4;
            health = ((float *)moby_get_private_value_0(candidate));
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
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D) {
        if (!math_fast_float_d(&((Hero *)g_hero_state)->i[0x2534 / 4]))
            ready = 0;
    }
    else
        ((Hero *)g_hero_state)->i[0x2534 / 4] = 0x21;

    if (D_L00_001A8F00 != 2 && vars->cooldown == 0.0f && ((Hero *)g_hero_state)->b[0x22BC] == 0 && moby->animation < 2 &&
        (g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) && ((Hero *)g_hero_state)->i[0x1240 / 4] >= 19 && ready) {
        if (moby->nextAnimation == 0)
            func_PAL_002A7E68(moby, 1, 0, 3);
        if (weapon_spend_ammo(-1, 1)) {
            D_L00_001B2864 = 1;
            if (candidate == 0) {
                int count, i;
                FastVecScale(&muzzle, &moby->forward, -1.0f);
                FastVecAdd(&muzzle, &muzzle, &moby->position);
                FastVecScale(&offset, &moby->right, 0.275f);
                FastVecAdd(&muzzle, &muzzle, &offset);
                count = coll_process_hit(1.0f, &muzzle, 1, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0);
                if (count != 0) {
                    for (i = 0; i < count; i++) {
                        Moby *hit = g_area_hit_targets[i];
                        float *hp = ((float *)moby_get_private_value_0(hit));
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
            PlayMobySound(0, 0, moby);
            vars->flash = 12;
            func_PAL_L00_003A7A68(moby);
            func_PAL_L00_003A8978(moby);
            if (((Hero *)g_hero_state)->i[0x229C / 4] == 0 || (((Hero *)g_hero_state)->i[0x2294 / 4] == 2 && ((Hero *)g_hero_state)->f[0x24B8 / 4] < 0.7f))
                func_PAL_L00_002D2668(0x36, 1, 8.0f);
            else
                func_PAL_L00_002AF458();
            func_PAL_002A7E68(moby, 2, 0, 0);
            vars->sound = slot_copy_records_to_free(D_00294880);
            {
                WeaponEntry *weapon = D_00262570 + g_item_slot_to_record[0x1B];
                vars->cooldown = 1.0f / weapon->rate;
            }
        } else if ((g_pad_state[0x1A4 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) || D_L00_001B2864 == 1) {
            PlayMobySound(1, 0, moby);
            D_L00_001B2864 = 0;
        }
        if (!((g_pad_state[0x1A0 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) && get_ammo(-1) && ((Hero *)g_hero_state)->b[0x22B8]) &&
            vars->sound >= 0) {
            slot_reset_active(vars->sound);
            vars->sound = -1;
        }
    }

    if (moby->animation != 2 && vars->flash > 0) {
        float alpha, width, power;
        Vector *off;
        Vector *pos;
        if (vars->flash >= 11) {
            float scale = 1.0f / IntToFloat(2);
            alpha = IntToFloat(12 - vars->flash) * scale;
            width = IntToFloat(12 - vars->flash) * (scale * 0.8f);
            power = IntToFloat(12 - vars->flash) * (scale * 0.5f);
        } else {
            float scale = 1.0f / IntToFloat(10);
            alpha = IntToFloat(vars->flash) * scale;
            width = IntToFloat(vars->flash) * (scale * 0.8f);
            power = IntToFloat(vars->flash) * (scale * 0.5f);
        }
        if (((Hero *)g_hero_state)->h[0x24EC / 2] != 0) {
            FastVecScale(&offset, &moby->forward, -1.0f);
            moby_transform_joint_to_world(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        } else {
            qcopy(&offset, &((Hero *)g_hero_state)->q[0x760 / 16]);
            moby_transform_joint_to_world(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        }
        FastVecAdd(pos, pos, off);
        FastVecScale(&lift, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0xE0, 0.3f);
        FastVecAdd(pos, pos, &lift);
        if (vars->light == -1) {
            vars->light = part_l00_alloc_effect_slot_2(pos, 8.0f, 0.0f, alpha, width, power);
        } else {
            MuzzleLight *light = &D_L00_001C6F40[vars->light];
            qcopy(&light->position, pos);
            light->position.f[3] = 8.0f;
            light->radius = alpha;
            light->spread = width;
            light->power = power;
        }
        FastDecTimer(&vars->flash);
    } else if (vars->light != -1) {
        gfx_free_point_light(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }

    if (moby->nextAnimation == 2) {
        if (vars->light != -1)
            gfx_free_point_light(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }
}
