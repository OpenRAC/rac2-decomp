#include "common.h"


extern unsigned char g_bouncing_weapon_index;
extern void cam_compute_view_direction(void *, void *, int);
extern void part_spawn_spark_puff(void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_flying_model_id __attribute__((sda));
extern int g_ripple_param_a __attribute__((sda)), g_ripple_param_b __attribute__((sda));
extern Collision g_hero_ground_collision;
extern Material g_item_l03_record_table[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int GetCollHitMaterial(void);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern void vec_clear_128(void *);
extern char *moby_spawn_scaled_effect(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern void *part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);


/* func_L03_002CCB70 is in the sibling file L03_002CCB70-decider.c (its own profile). */


extern char D_00189E20_8[];
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void coll_push_vector_from_negative_axes(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float cam_get_view_space_angle(void *);
extern float cam_get_view_space_height(void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern char g_collision_direction[];

extern char g_collision_start_point[];
typedef int MotionQuad __attribute__((mode(TI)));

/* The level's runtime block: its mode word and timer, and a counted list of objects. */
typedef struct {
    u8 pad00[0x30];
    u32 mode;
    s32 timer;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} EndakoState;

extern EndakoState g_endako_state;
extern s32 g_current_map_index __attribute__((sda));
extern f32 g_object_scale SDATA(D_L03_001A9420);
extern s32 g_object_timer SDATA(D_L03_001A9424);
/* Four rows of three quadwords, filled from twelve joints of one object. */
extern Quad g_joint_world_matrices[][3];
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, u32, u32, f32);
extern void EmitScaledObjectParticles(void *);
extern void moby_transform_joint_to_world(void *, s32, void *);

/* Solve the forward collision time for each of the resident movement modes. */
float hero_solve_motion_collision_time(float time, float acceleration, float height)
{
    float end[4], direction[4], curve[4], start[4];
    float root0a, root0b, root1a, root1b, root2a, root2b;
    float speed, position;
    char *state = D_00189E20_8;
    switch (*(unsigned char *)(state + 0x22C3)) {
    case 0: {
        float half;
        if (height < 0.0f) {
            char *pos = state + 0x80;
            FastVecScale(end, state + 0xF0, time);
            end[2] -= (time * time + time) * (acceleration * 0.5f);
            FastVecAdd(end, end, pos);
            *(MotionQuad *)direction = *(MotionQuad *)(state + 0x80);
            coll_push_vector_from_negative_axes(direction, end);
            qcopy(direction, pos);
            if (CollLine(direction, end, 0xD22, 0, 0)) {
                if (cam_get_view_space_angle(g_collision_direction) <= 0.8726647f)
                    height = *(float *)(g_collision_direction - 0x18);
            }
        }
        if (height > 0.0f) {
            char *root = D_00189E20_8;
            half = acceleration * -0.5f;
            if (math_solve_quadratic(&root0a, &root0b, half,
                    *(float *)(root + 0xF8) - half,
                    *(float *)(root + 0x88) - height) > 0
                    && root0a > 0.0f)
                return root0a;
        }
        break;
    } case 1: {
        float half;
        char *velocity;
        char *pos;
        qcopy(direction, state + 0x2A0);
        velocity = state + 0xF0;
        vec_scale_to_length(direction, direction, acceleration);
        pos = state + 0x80;
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        coll_push_vector_from_negative_axes(start, end);
        if (CollLine(pos, end, 0xD22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = cam_get_view_space_height(velocity) - half;
            position = cam_get_view_space_height(pos);
            position -= cam_get_view_space_height(g_collision_start_point);
            if (math_solve_quadratic(&root1a, &root1b, half, speed, position) > 0
                    && root1a > 0.0f)
                return root1a;
        }
        break;
    } case 2: {
        float half;
        char *velocity = state + 0xF0;
        char *pos = state + 0x80;
        curve[2] = 100.0f;
        curve[1] = 100.0f;
        curve[0] = 100.0f;
        FastVecSub(direction, pos, curve);
        vec_scale_to_length(direction, direction, acceleration);
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        coll_push_vector_from_negative_axes(start, end);
        if (CollLine(pos, end, 0xD22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = cam_get_view_space_height(velocity) - half;
            position = cam_get_view_space_height(pos);
            position -= cam_get_view_space_height(g_collision_start_point);
            if (math_solve_quadratic(&root2a, &root2b, half, speed, position) > 0
                    && root2a > 0.0f)
                return root2a;
        }
        break;
    } }
    return time;
}


/* Runs every frame in the Endako level. It marks and updates certain objects in the level list and moves the end-of-level scene along step by step. */
void level_update_objects(void)
{
    EndakoState *state;
    u8 *object;
    s32 i;
    Quad a, b;

    anim_start_startup_animations();
    for (i = 0; i < g_endako_state.count; i++) {
        object = g_endako_state.objects[i];
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xE29 /* moby class 3625 */)
            *(u16 *)(object + 0x34) |= 0x800;
        if (*(s16 *)(object + 0xAA) == 0xD54 /* moby class 3412 */)
            UpdateEquipmentPieces(object);
        if (object != 0 && *(s16 *)(object + 0xAA) == MOBY_CLASS_TV_SCREENS) {
            u8 *vars = *(u8 **)(object + 0x68);
            if (vars != 0)
                math_store_angle_update_result(object, vars + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
        }
    }
    if (g_current_map_index != 3)
        return;
    state = &g_endako_state;
    if (state->mode < 3) {
        u8 *main_object = state->objects[1];
        *(f32 *)(main_object + 0x2C) = *(f32 *)(*(u8 **)(main_object + 0x24) + 0x24) * g_object_scale;
    }
    if (state->mode == 6)
        EmitScaledObjectParticles(state->objects[1]);
    if (state->mode == 8)
        EmitScaledObjectParticles(state->objects[3]);
    if (state->mode == 7 && state->timer == 0x424) {
        u8 *target;
        s32 row, col, k;

        g_object_timer = state->timer;
        target = state->objects[2];
        for (row = 0; row < 4; row++)
            for (col = 0; col < 3; col++)
                moby_transform_joint_to_world(target, row * 3 + col, &g_joint_world_matrices[row][col]);
        for (k = 0; k < 4; k++) {
            Quad (*rows)[3] = g_joint_world_matrices;
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][1]);
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][2]);
        }
    }
}

extern u8 *g_level_entry_list;

/* Counts the entries in the level list that are type 1 and not yet switched off. Returns 1 when there is no list. */
s32 level_count_active_entries(void)
{
    u8 *list = g_level_entry_list;
    u8 *entry;
    s32 count = 0;

    if (list == 0)
        return 1;
    entry = list;
    while (*(s16 *)entry != 0) {
        if (*(s16 *)(entry + 0x24) == 1) {
            if ((*(u16 *)(entry + 0x10) & 2) == 0)
                count++;
        }
        entry += 0x28;
    }
    return count;
}


extern void *moby_get_vars_word_18(char *a0);
extern float mat_fast_helper_a(float a, float b);
extern float FastAddRotations(float a, float b);
extern int FastDecTimer(short *p);
extern int math_random_int_range(int a0, int a1);
/* The callee's parameters are listed in the order the retail code sets the
   registers up in: int, int, float, int, float, float. */
extern int moby_move_to_target_temp_limits(char *a0, char *a1, float f12, char *a2, float f13, float f14);

/* Aim the record at the shape the caller found. */
/* Works out which way an enemy should turn toward its target, adding a sideways sway that flips direction every so often. */
int enemy_aim_toward_target(char *self, float *target, char *third, float amount, float f13, float f14)
{
    char *data = (char *)moby_get_vars_word_18(self);
    float angle;

    if (data == 0)
        return 8;
    angle = mat_fast_helper_a(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = math_random_int_range(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return moby_move_to_target_temp_limits(self, target, angle, third, f13, f14);
}

/* func_L03_00383FE8 is in its -G8 sibling unit. */


/* func_L03_003844D8 is in its -G8 sibling unit. */


/* Moves a flying object along its path each frame and checks what it hits. On a hit it either bursts into a splash with sparks or bounces off and tells the object to react. */
void flying_object_update_splash(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, ctx, position);
    part_steer_effect_direction(*(int *)(ctx + 0x1C), ctx, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(ctx, ctx);
    vec_add_object_direction_scaled(position, ctx, 0.0030555557f);
    part_emit_sparkle(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_item_l03_record_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, (int)&frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(g_ripple_param_a, g_ripple_param_b, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            vec_clear_128(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = g_hero_ground_collision.point.f[2];
            effect = moby_spawn_scaled_effect(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.050000004f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.050000004f, 0.10833334f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2(&frame.position, spread, math_random_int_below(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &g_hero_ground_collision;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &g_hero_ground_collision;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_flying_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
    }
}


/* Moves a flying object along its path each frame and checks what it hits. On a hit it bounces off, using a different reaction once it has bounced many times. */
void flying_object_update_bounce(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (g_bouncing_weapon_index + g_item_l03_record_table)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_hero_ground_collision;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &g_hero_ground_collision;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_flying_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_hero_ground_collision;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(obj, &frame.velocity, &frame.normal);
    }
}
