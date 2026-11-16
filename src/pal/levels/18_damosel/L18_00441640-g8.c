#include "common.h"

extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void gfx_start_color_fade_pal(void *, void *), gfx_update_color_fade_pal(void *, void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float), FastAddRotations(float, float);
extern int IsPointInCuboid(void *, int), flag_set_first_pending(void *);
extern void moby_mark_spawned(void *);
extern int math_fast_float_d(void *);
extern int PlayMobySound(int, int, void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_spawn_masked_debris_pal(void *, int, void *, float, float, float, float, int);
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
    float turn_x, turn_y;
    u8 pad68[8];
    s32 start_region, fire_region, child_id;
    float base_z, velocity_z;
    s32 fire_timer;
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

/* func_PAL_L18_00441640, the PAL copy of func_L18_0043C258: the same C, where the per-frame rates scale to
 * 50 Hz and the fire delay goes through ((s32)(x) * 5 + 2) / 6. */
void bouncing_child_launcher_update_pal(LauncherObject *obj) {
    LauncherState *vars = obj->state;
    u8 *child;
    float damage, z;
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int zero;
    int low;

    damage = moby_update_aim_target_strength_pal(obj, part_find_owned_effect_slot(obj, 0x10000, 0));
    vars->health -= damage;
    if (damage > 0.0f) {
        gfx_start_color_fade_pal(obj, vars->transform);
        if (vars->health <= 0.0f) {
            SpawnExplosion_pal(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            part_spawn_masked_debris_pal(obj, 0x3a, g_explosion_effect_desc, 3, 6, 3, 6, 255);
            PlayMobySound(1, 0, obj);
            moby_mark_spawned(obj);
            return;
        }
    }
    obj->opacity = 255;
    gfx_update_color_fade_pal(obj, vars->transform);
    switch (obj->mode) {
    case 0:
        vars->base_z = obj->position[2];
        if (!vars->initialized) {
            vars->initialized = 1;
            vars->health = 1;
        }
        vars->fire_timer = -1;
        vars->scale = 1;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (vars->start_region != -1 && IsPointInCuboid(g_hero_position, vars->start_region))
            moby_set_state(obj, 2, -1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            obj->rotation[0] = 0;
            obj->rotation[1] = 0;
            z = obj->rotation[0];
            obj->position[2] = vars->base_z;
            vars->velocity_z += math_random_float_range(z, g_turret_velocity_z_max * 0.020000001f);
            vars->turn_x = math_random_float_range(z, g_turret_turn_x_max_deg * 0.0003490659f);
            vars->turn_y = math_random_float_range(z, g_turret_turn_y_max_deg * 0.0003490659f);
            obj->position[2] = vars->base_z;
            PlayMobySound(0, 0, obj);
        }
        if (obj->position[2] >= vars->base_z) {
            obj->position[2] += vars->velocity_z;
            vars->velocity_z -= g_turret_gravity * 0.00040000002f;
            if (vars->velocity_z > 0) {
                obj->rotation[0] = FastAddRotations(vars->turn_x, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(vars->turn_y, obj->rotation[1]);
            } else {
                obj->rotation[0] = FastAddRotations(-vars->turn_x, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(-vars->turn_y, obj->rotation[1]);
            }
        } else {
            moby_set_state(obj, 2, -1);
        }
        if (vars->fire_timer == 0) {
            zero = 0;
            child = protopet_count_group(vars->child_id, &zero);
            if (child) {
                vec_scale_to_length(velocity, g_turret_shot_direction, g_turret_shot_speed_max * 0.020000001f);
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                vec_add_random_offset(velocity, g_turret_muzzle_jitter * 0.020000001f);
                matrix_mul_vec3(position, g_turret_l18_muzzle_offset, obj->matrix);
                FastVecAdd(position, position, obj->position);
                protopet_launch_shot(child, position, velocity);
                low = g_turret_fire_timer_min;
                *(s32 *)(child + 0xB8) = (s32)obj;
                vars->fire_timer = ((s32)math_random_int_range(low, g_turret_fire_timer_max) * 5 + 2) / 6;
            }
        } else if (vars->fire_timer == -1) {
            if (vars->fire_region != -1 && IsPointInCuboid(g_hero_position, vars->fire_region)) {
                vars->fire_timer++;
                SpawnExplosion_pal(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(1, 0, obj);
                vec_scale_to_length(velocity, g_turret_shot_direction, g_turret_shot_speed_min * 0.020000001f);
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                vec_add_random_offset(position, g_turret_muzzle_jitter * 0.020000001f);
                FastVecAdd(velocity, velocity, position);
                part_spawn_masked_debris_pal(obj, 5, velocity, 3, 6, 3, 6, 255);
            }
        } else {
            math_fast_float_d(&vars->fire_timer);
        }
        break;
    }
    if (obj->timer < 65535)
        (obj->timer)++;
}
