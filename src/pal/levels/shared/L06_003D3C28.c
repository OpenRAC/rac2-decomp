#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
extern int g_projectile_model_ref __attribute__((sda));
extern int g_ripple_object __attribute__((sda)), g_ripple_param __attribute__((sda));
extern Collision g_collision_result;
extern Material g_weapon_l00_table[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle_pal(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern void vec_clear_128(void *);
extern char *moby_spawn_scaled_effect(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void *part_spawn_spark_2_pal(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(void *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion_pal(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Updates a thrown object: it moves each frame, checks what it hits, and either bounces off or splashes into a spray of particles (PAL). */
void thrown_l06_object_update_pal(unsigned char *obj) {
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
    } state;
    char *vars = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    state.velocity.q = 0;
    state.velocity.f[2] = 0.040000003f;
    state.normal.q = 0;
    state.normal.f[2] = 1.0f;
    qcopy(&state.old, position);
    FastVecAdd(position, vars, position);
    part_steer_effect_direction(*(int *)(vars + 0x1C), vars, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(vars, vars);
    vec_add_object_direction_scaled(position, vars, 0.0044f);
    part_emit_sparkle_pal(obj);
    state.packet.moby = obj;
    state.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0xF2)
        state.packet.flags = 0x830001;
    state.packet.enabled = 1;
    state.packet.material =
        ((Material *)((u32)g_weapon_l00_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&state.packet.vector, vars);
    vec_fast_normalize_helper(&state.packet.vector, &state.packet.vector, 1.0f);
    state.packet.vector.f[2] = 1.0f;
    state.packet.vector.f[3] = 5627.925f;
    state.packet.kind = 2;
    state.packet.class_id = *(unsigned short *)(obj + 0xAA);
    state.packet.active = 1;
    if (CollLine(&state.old, position, 0x10, obj, &state.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(g_ripple_object, g_ripple_param, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.030000001f;
            state.position.f[0] = *(float *)(obj + 0x10);
            state.position.f[1] = *(float *)(obj + 0x14);
            state.position.f[2] = g_collision_result.point.f[2];
            effect = moby_spawn_scaled_effect(&state.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &state.spread;
            i = 15;
            do {
                --i;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.060000002f);
                state.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                state.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                state.spread.f[2] = math_random_float_range(0.060000002f, 0.13000001f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2_pal(&state.position, spread, math_random_int_below(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &g_collision_result;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0xF1)
                    goto finish;
                reread = &g_collision_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_projectile_model_ref && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&state.velocity, vars, &reread->normal);
                vec_scale_to_length(&state.velocity, &state.velocity, 0.040000003f);
                vec_scale_to_length(&state.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&state.velocity, vars, &collision->normal);
                vec_scale_to_length(&state.velocity, &state.velocity, 0.040000003f);
                vec_scale_to_length(&state.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&state.velocity, (char *)&state.velocity, vars);
    }
finish:
    if (obj[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion_pal(obj, &state.velocity, &state.normal);
    }
}


extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst_pal(void *, void *, void *);
extern void part_spawn_spark_puff_pal(void *);

/* Updates a falling object: it moves, checks what it touches, and bounces or breaks when it hits something (PAL). */
void falling_l06_object_update_pal(char *obj) {
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
    } state;
    char *vars = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    state.velocity.q = 0;
    state.velocity.f[2] = 0.040000003f;
    state.normal.q = 0;
    state.normal.f[2] = 1.0f;
    qcopy(&state.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &state.surface, 0);
    FastVecScale(&state.surface, &state.surface, 0.00044f);
    part_spawn_spark_puff_pal(obj);
    state.packet.moby = obj;
    state.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0xF2)
        state.packet.flags = 0x830001;
    state.packet.enabled = 1;
    state.packet.material = (g_bouncing_weapon_index + g_weapon_l00_table)->material;
    qcopy(&state.packet.vector, vars);
    vec_fast_normalize_helper(&state.packet.vector, &state.packet.vector, 1.0f);
    state.packet.kind = 2;
    state.packet.vector.f[3] = 5627.925f;
    state.packet.class_id = *(unsigned short *)(obj + 0xAA);
    state.packet.vector.f[2] = 1.0f;
    state.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&state.old, position, 0x10, obj, &state.packet)) {
        collision = &g_collision_result;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0xF2)
                goto finish;
            reread = &g_collision_result;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_projectile_model_ref && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&state.velocity, vars, &reread->normal);
            vec_scale_to_length(&state.velocity, &state.velocity, 0.040000003f);
            vec_scale_to_length(&state.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_result;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&state.velocity, vars, &collision->normal);
            vec_scale_to_length(&state.velocity, &state.velocity, 0.040000003f);
            vec_scale_to_length(&state.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&state.velocity, (char *)&state.velocity, vars);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 17)
            part_spawn_big_explosion_pal(obj, &state.velocity, &state.normal);
        else
            part_l00_spawn_impact_burst_pal(obj, &state.velocity, &state.normal);
    }
}


