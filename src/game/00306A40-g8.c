#include "common.h"
typedef struct { float x,y,z,w; } Vec;
typedef struct ProjectileObject ProjectileObject;
typedef struct {
    Vec velocity, initial, previous, next;
    int timer40, field44, effect48;
    short field4c;
    signed char managerIndex, flightEffect;
    int field50;
    char pad54[8];
    int timer5c, field60, field64, field68, slot;
    ProjectileObject *attachment;
    float attachX, attachY, attachZ;
} ProjectileData;
struct ProjectileObject {
    char pad00[0x10]; Vec position;
    unsigned char state;
    char pad21[2]; unsigned char field23;
    char *classData;
    char pad28[0xc]; short flags;
    char pad36[0x12]; float playback;
    char pad4c[0x1c]; ProjectileData *data;
    char pad6c[0x2c]; int collision;
    char pad9c[0xe]; short classId;
    char padac[0x14]; float transform[12];
};
typedef struct { Vec from,to,velocity; ProjectileObject *object; int *filter; int mode; float radius,step,scale; int zero48,zero4c,flag; int surface; int flag58; float epsilon; } Sweep;
extern int g_megaturret_slot_counter;
extern float g_megaturret_speed __attribute__((sda)), g_megaturret_sweep_step __attribute__((sda));
extern ProjectileObject *g_turret_target_moby;
extern int g_game_mode NOT_SDA;
extern int g_surface_height_tiles __attribute__((sda));
extern int g_surface_box_count;
typedef struct { int owners[64]; int active[64]; int extra[8]; int count, flag, limit; } ProjectileManager;
extern ProjectileManager ref_00306A40_00;
extern ProjectileObject *ref_00306A40_01[];
typedef struct { float x, y, z; } Position3;
extern Position3 ref_00306A40_02[];
extern void moby_get_facing_direction(void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *),multiply_matrix3x3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void part_steer_effect_direction(int,void *,int);
extern void vec_add_object_direction_scaled(void *,void *,float);
extern void vec_transform_or_copy(void *,void *);
extern int CollideSweptSphere(Sweep *);
extern int weapon_get_group(int);
extern void RippleDisturb(int,int,int,float,float,float,float);
extern ProjectileObject *moby_spawn_scaled_effect(void *,float);
extern int slot_list_add(void *,void *);
extern void projectile_cleanup_table_2(void);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void anim_start_blended_with_flags(void *,int,int,int,int);
extern void table_clear_entry_flag(int);
extern void FastVecSub(void *,void *,void *),matrix_from_basis_rows(void *,void *),transform_vector(void *,void *,void *);
extern float moby_get_anim_value(void *);
extern void megaturret_find_target(void *),megaturret_aim_at_target(void *),megaturret_fire_shot(void *);
extern int part_alloc_effect_slot(void *,int,float,float,float),slot_alloc_for_object(void *,int);
extern void megaturret_update_fall(void *),projectile_apply_random_push_2(void *);
extern void part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern void slot_free(int),slot_list_remove(void *,int),moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *,void *,void *), part_advance_grow_effect_2(void *);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern void projectile_check_hit_break_2(void *),moby_follow_attached_motion_2(void *),projectile_draw_effects_2(void *);
extern void gfx_register_overlay_draw_callback(void (*)(void *),void *);
/* The state machine of an object fired at a surface: flies and sweeps for a hit, sticks or
   bursts on what it hit, then follows what it stuck to until it is destroyed. */
void megaturret_update(ProjectileObject *self)
{
    Vec old_pos;
    int filter[2];
    Vec direction, velocity, quaternion, axis;
    float matrix[12];
    Sweep sweep;
    Vec relative;
    float inverse[16];
    ProjectileData *vars = self->data;
    ProjectileObject *hit;
    float angle;
    int hit_result, slot_counter;

    switch (self->state) {
    case 0:
        self->state = 1;
        slot_counter = g_megaturret_slot_counter;
        vars->slot = slot_counter;
        g_megaturret_slot_counter = (slot_counter + 1) % 100;
        self->collision = 0;
        /* fall through */
    case 1:
        moby_get_facing_direction(&self->position, &direction);
        vec_scale_to_length(&velocity, &self->transform[8], 1.0f);
        FastVecCross(&axis, &velocity, &direction);
        angle = FastVecDot(&velocity, &direction) / 2.0f;
        FastVecScale(&quaternion, &axis, math_fast_sin_or_cos_b(angle));
        quaternion.w = math_fast_sin_or_cos_a(angle);
        quaternion_to_rotation_basis(&quaternion, matrix);
        multiply_matrix3x3(self->transform, matrix, self->transform);
        qcopy(&old_pos, &self->position);
        FastVecAdd(&self->position, &self->position, vars);
        part_steer_effect_direction(vars->flightEffect, vars, 0);
        vec_add_object_direction_scaled(&self->position, vars, g_megaturret_speed * 0.00027777778f);
        vec_transform_or_copy(&self->position, &self->position);
        filter[0] = 0;
        filter[1] = 0xc5a;
        qcopy(&sweep.from, &old_pos);
        qcopy(&sweep.to, &self->position);
        qcopy(&sweep.velocity, vars);
        sweep.object = self;
        sweep.filter = filter;
        sweep.mode = 2;
        sweep.radius = 0.13f;
        sweep.step = g_megaturret_sweep_step;
        sweep.scale = 0.5555556f;
        sweep.zero48 = 0;
        sweep.zero4c = 0;
        sweep.flag = 1;
        sweep.flag58 = 1;
        sweep.epsilon = 0.0962f;
        hit_result = CollideSweptSphere(&sweep);
        qcopy(&self->position, &sweep.to);
        qcopy(vars, &sweep.velocity);
        if (hit_result != 2)
            break;
        hit = sweep.object;
        if (!hit || (hit->classId != MOBY_CLASS_DECOY && hit->classId != MOBY_CLASS_MINITURRET && hit->classId != MOBY_CLASS_MEGATURRET)) {
            qzero_nc(vars);
            vars->attachment = hit;
            if (hit) {
                vars->attachX = hit->position.x;
                vars->attachY = hit->position.y;
                vars->attachZ = hit->position.z;
            }
            hit_result = weapon_get_group(sweep.surface);
            if (hit_result == 2) {
                vars->velocity.z = -0.025000002f;
                self->state = 7;
                if (!sweep.surface) {
                    RippleDisturb(g_surface_height_tiles, g_surface_box_count, 1, self->position.x, self->position.y, 0.5f, -0.35f);
                    hit = moby_spawn_scaled_effect(&self->position, 2.0f);
                    if (hit)
                        hit->field23 = 0x70;
                }
            } else if (hit_result == 1) {
                self->state = 8;
            } else {
                vars->managerIndex = slot_list_add(&ref_00306A40_00, self);
                projectile_cleanup_table_2();
                if (ref_00306A40_00.active[vars->managerIndex]) {
                    self->state = 2;
                    snd_play_from_class_bank(1, 0, self, MOBY_CLASS_MEGATURRET);
                    anim_start_blended_with_flags(self, 1, 0, 0, 0);
                } else {
                    self->state = 6;
                }
            }
            table_clear_entry_flag(vars->flightEffect);
            ref_00306A40_01[vars->slot] = g_turret_target_moby;
            if (g_turret_target_moby) {
                FastVecSub(&relative, &self->position, &g_turret_target_moby->position);
                matrix_from_basis_rows(inverse, ref_00306A40_01[vars->slot]->transform);
                transform_vector(&relative, &relative, inverse);
                {
                    /* Set twice, so alias analysis keeps the row's stores in order with the stack. */
                    int row = vars->slot * 12;

                    row += (int)ref_00306A40_02;
                    ((float *)row)[0] = relative.x;
                    ((float *)row)[1] = relative.y;
                    ((float *)row)[2] = relative.z;
                }
            }
            self->collision = *(int *)(self->classData + 0x10);
        } else {
            FastVecScale(vars, vars, 1.1f);
        }
        break;
    case 2:
        if (moby_get_anim_value(self) >= 6.5f) {
            anim_start_blended_with_flags(self, 2, 0, 0, 0);
            self->state = 3;
        }
        break;
    case 3:
        megaturret_find_target(self);
        goto attachment;
    case 4:
        megaturret_aim_at_target(self);
        megaturret_fire_shot(self);
    attachment: {
        ProjectileObject *attached = vars->attachment;

        if (attached) {
            if (attached->state == 254)
                goto detached;
            if (attached->state != 253)
                break;
        detached:
            self->collision = 0;
            vars->flightEffect = part_alloc_effect_slot(self, 0, 1.0f, 1.0f, 1.0f);
            self->state = 1;
            vars->attachment = 0;
        }
    }
        break;
    case 5:
        if (moby_get_anim_value(self) <= 1.0f) {
            anim_start_blended_with_flags(self, 0, 0, 0, 0);
            self->playback = 1.0f;
            self->state = 6;
        }
        break;
    case 6:
        if (ref_00306A40_00.active[vars->managerIndex]) {
            self->state = 2;
            snd_play_from_class_bank(1, 0, self, MOBY_CLASS_MEGATURRET);
            anim_start_blended_with_flags(self, 1, 0, 0, 0);
            vars->effect48 = slot_alloc_for_object(self, 0);
        }
        break;
    case 7:
        megaturret_update_fall(self);
        projectile_apply_random_push_2(self);
        break;
    case 8:
        snd_play_from_class_bank(3, 0, self, MOBY_CLASS_MEGATURRET);
        part_spawn_explosion_with_sparks(self, &self->position, -1, 0.5f, 13.0f);
        self->state = 9;
        self->flags |= 0x41;
        break;
    case 9: {
        int invalid = -1;

        if (vars->effect48 != invalid)
            slot_free(vars->effect48);
        if (vars->managerIndex != invalid)
            slot_list_remove(&ref_00306A40_00, vars->managerIndex);
        moby_mark_spawned(self);
        return;
    }
    }
    if (self->state >= 2 && ref_00306A40_01[vars->slot]) {
        /* Set twice, as above. */
        int row = vars->slot * 12;

        row += (int)ref_00306A40_02;
        direction.x = ((float *)row)[0];
        direction.y = ((float *)row)[1];
        direction.z = ((float *)row)[2];
        direction.w = 0;
        matrix_mul_vec3(&direction, &direction, ref_00306A40_01[vars->slot]->transform);
        FastVecAdd(&self->position, &ref_00306A40_01[vars->slot]->position, &direction);
    }
    if (self->state == 3 || self->state == 4)
        part_advance_grow_effect_2(self);
    vec_fast_helper_b(&vars->timer5c);
    if (math_fast_float_d(&vars->timer40) || g_game_mode == 0x6f)
        if (self->state != 9)
            self->state = 8;
    if (self->state == 3 || self->state == 4) {
        projectile_check_hit_break_2(self);
        if (!ref_00306A40_00.active[vars->managerIndex]) {
            anim_start_blended_with_flags(self, 1, 11, 0, 0);
            self->state = 5;
            self->playback = -1.0f;
            slot_free(vars->effect48);
            vars->effect48 = -1;
            vars->field4c = 1;
            vars->field50 = 0;
            vars->field44 = 0;
            vars->field64 = 0;
            qcopy(&vars->next, &vars->initial);
            qcopy(&vars->previous, &vars->initial);
        }
    }
    if (self->state < 8 && vars->attachment)
        moby_follow_attached_motion_2(self);
    gfx_register_overlay_draw_callback(projectile_draw_effects_2, self);
}
