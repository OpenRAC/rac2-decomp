#include "common.h"

extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength(void *, void *);
extern void gfx_start_color_fade(void *, void *), gfx_update_color_fade(void *, void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float), FastAddRotations(float, float);
extern int IsPointInCuboid(void *, int), flag_set_first_pending(void *);
extern void moby_mark_spawned(void *);
extern int math_fast_float_d(void *);
extern int PlayMobySound(int, int, void *);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void vec_scale_to_length(void *, void *, float), matrix_mul_vec3(void *, void *, void *), vec_add_random_offset(void *, float), FastVecAdd(void *, void *, void *);
extern u8 g_hero_position[];
extern u8 g_explosion_effect_desc[] __attribute__((sda));
extern float g_turret_velocity_z_max __attribute__((sda));
extern float g_turret_turn_x_max_deg __attribute__((sda));
extern float g_turret_turn_y_max_deg __attribute__((sda));
extern float g_turret_muzzle_jitter __attribute__((sda));
extern float g_turret_shot_speed_max __attribute__((sda));
extern float g_turret_shot_speed_min __attribute__((sda));
extern float g_turret_gravity __attribute__((sda));
extern int g_turret_fire_timer_min __attribute__((sda));
extern int g_turret_fire_timer_max __attribute__((sda));
extern u8 g_turret_l18_muzzle_offset[] SDATA(D_L18_001B1AE0);
extern u8 g_turret_shot_direction[] SDATA(D_L18_001B1AF0);
extern u8 *protopet_count_group(int, int *);
extern void protopet_launch_shot(void *, void *, void *);

typedef struct {
    u8 pad00[0x20];
    float health;
    s16 initialized;
    u8 pad26[0xa];
    float scale;
    u8 pad34[0x1c];
    float transform[4];
    float turnX, turnY;
    u8 pad68[8];
    s32 startRegion, fireRegion, childId;
    float baseZ, velocityZ;
    s32 fireTimer;
} LauncherState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x47];
    LauncherState *state;
    u8 pad6c[0x2a];
    u16 timer;
    u8 pad98[0x10];
    u8 opacity;
    u8 pada9[0x17];
    float matrix[12];
    float rotation[4];
} LauncherObject;

/* Updates a launcher (moby class 4440) that hops up and down and shoots out child objects when the player triggers it. It breaks when its health runs out. */
void UpdateBouncingChildLauncher(LauncherObject *obj) {
    LauncherState *vars = obj->state;
    u8 *child;
    float damage, z;
    float velocity[4] __attribute__((aligned(16)));
    float muzzle_pos[4] __attribute__((aligned(16)));
    int zero;

    damage = moby_update_aim_target_strength(obj, part_find_owned_effect_slot(obj, 0x10000, 0));
    vars->health -= damage;
    if (damage > 0.0f) {
        gfx_start_color_fade(obj, vars->transform);
        if (vars->health <= 0.0f) {
            SpawnExplosion(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            part_spawn_masked_debris(obj, 0x3a, g_explosion_effect_desc, 3, 6, 3, 6, 255);
            PlayMobySound(1, 0, obj);
            moby_mark_spawned(obj);
            return;
        }
    }
    obj->opacity = 255;
    gfx_update_color_fade(obj, vars->transform);
    switch (obj->mode) {
    case 0:
        vars->baseZ = obj->position[2];
        if (!vars->initialized) {
            vars->initialized = 1;
            vars->health = 1;
        }
        vars->fireTimer = -1;
        vars->scale = 1;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (vars->startRegion != -1 && IsPointInCuboid(g_hero_position, vars->startRegion))
            moby_set_state(obj, 2, -1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            obj->rotation[0] = 0;
            obj->rotation[1] = 0;
            z = obj->rotation[0];
            obj->position[2] = vars->baseZ;
            vars->velocityZ += math_random_float_range(z, g_turret_velocity_z_max * (1.0f / 60.0f));
            vars->turnX = math_random_float_range(z, g_turret_turn_x_max_deg * 0.0002908882452175021f);
            vars->turnY = math_random_float_range(z, g_turret_turn_y_max_deg * 0.0002908882452175021f);
            obj->position[2] = vars->baseZ;
            PlayMobySound(0, 0, obj);
        }
        if (obj->position[2] >= vars->baseZ) {
            obj->position[2] += vars->velocityZ;
            vars->velocityZ -= g_turret_gravity * 0.00027777778450399637f;
            if (vars->velocityZ > 0) {
                obj->rotation[0] = FastAddRotations(vars->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(vars->turnY, obj->rotation[1]);
            } else {
                obj->rotation[0] = FastAddRotations(-vars->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(-vars->turnY, obj->rotation[1]);
            }
        } else {
            moby_set_state(obj, 2, -1);
        }
        if (vars->fireTimer == 0) {
            zero = 0;
            child = protopet_count_group(vars->childId, &zero);
            if (child) {
                vec_scale_to_length(velocity, g_turret_shot_direction, g_turret_shot_speed_max * (1.0f / 60.0f));
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                vec_add_random_offset(velocity, g_turret_muzzle_jitter * (1.0f / 60.0f));
                matrix_mul_vec3(muzzle_pos, g_turret_l18_muzzle_offset, obj->matrix);
                FastVecAdd(muzzle_pos, muzzle_pos, obj->position);
                protopet_launch_shot(child, muzzle_pos, velocity);
                *(s32 *)(child + 0xB8) = (s32)obj;
                vars->fireTimer = math_random_int_range(g_turret_fire_timer_min, g_turret_fire_timer_max);
            }
        } else if (vars->fireTimer == -1) {
            if (vars->fireRegion != -1 && IsPointInCuboid(g_hero_position, vars->fireRegion)) {
                vars->fireTimer++;
                SpawnExplosion(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(1, 0, obj);
                vec_scale_to_length(velocity, g_turret_shot_direction, g_turret_shot_speed_min * (1.0f / 60.0f));
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                vec_add_random_offset(muzzle_pos, g_turret_muzzle_jitter * (1.0f / 60.0f));
                FastVecAdd(velocity, velocity, muzzle_pos);
                part_spawn_masked_debris(obj, 5, velocity, 3, 6, 3, 6, 255);
            }
        } else {
            math_fast_float_d(&vars->fireTimer);
        }
        break;
    }
    if (obj->timer < 65535)
        (obj->timer)++;
}
