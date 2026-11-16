#include "include_asm.h"
#include "common.h"

extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern void part_spawn_spark_puff(void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_thrown_l26_model_id __attribute__((sda));
extern int g_ripple_l26_x __attribute__((sda)), g_ripple_l26_y __attribute__((sda));
extern Collision g_projectile_l26_collision;
extern Material g_item_l26_materials[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle(void *);
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
extern void *part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void FastVecAdd(char *, char *, char *);



extern void func_002EE358(void *, void *, void *);
extern void func_00324530(void *, void *, void *, void *);
extern float func_002EE9C8(float, float);

extern void func_002EE5F0(void *, void *, float);
extern void func_002EE440(void *, void *, void *);



/* The hero record of L26_002FC8D8-g64.c; its part list at +0x18C holds `count` objects. */
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44 - 0x38];
    short count;
    char gap46[0x18C - 0x46];
    char *parts[0];
} Hero;
extern Hero g_hero_part_state;
typedef struct { char pad[0x34]; unsigned short flags; char gap[0xAA - 0x36]; short id; } Object;
extern int g_current_map_index[] __attribute__((sda));
extern float g_part_offset_positions[][4] SDATA(D_L26_001A9450);
/* Min/max pairs: the first three lower bounds are read through $gp, every other bound absolute.
   The upper bounds are the second words of their pairs ([1]); the offset form keeps those absolute
   macro loads out of call delay slots, as in retail. */
extern float g_part_acceleration_params[] __attribute__((sda));
extern float D_L26_001A9420_gp SDATA(D_L26_001A9420);
extern unsigned int g_part_color_range[] __attribute__((sda));
extern unsigned int D_L26_001A9428_gp SDATA(D_L26_001A9428);
extern int g_part_kind_range[] __attribute__((sda));
extern int D_L26_001A9430_gp SDATA(D_L26_001A9430);
extern int g_part_duration_range[] __attribute__((sda));
extern int g_part_size_range[] __attribute__((sda));
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern char *part_spawn_trail(void *, void *, void *, unsigned int, unsigned int, int, int, int, int);
extern int FloatToInt(float);

/* Walks the hero's part objects (sets flag 0x800 on id 0xE29, calls func_002E64A0 for id 0xD54,
   passes id 4000 objects with private data to func_L00_00326048) and, while D_001A79F0 is 26, the
   hero mode is 0 and its timer below 260, emits eight particles from part 3's transform with
   ranged colour, kind, duration and size. */
void hero_update_part_objects(void) {
    Vec transform[4];
    Vec position;
    Vec velocity;
    Vec acceleration;
    Hero *hero;
    char **slot;
    char *object;
    char *effect;
    unsigned int color;
    int kind;
    int duration;
    int size;
    int i;
    int j;
    int flags = -1;
    anim_start_startup_animations();
    for (i = 0; i < g_hero_part_state.count; i++) {
        hero = &g_hero_part_state;
        slot = &hero->parts[i];
        object = *slot;
        if (object && ((Object *)object)->id == 0xE29 /* moby class 3625 */) {
            ((Object *)object)->flags |= 0x800;
        }
        if (((Object *)object)->id == 0xD54 /* moby class 3412 */) UpdateEquipmentPieces(object);
        if (object && *(short *)(object + 0xAA) == MOBY_CLASS_TV_SCREENS && *(char **)(object + 0x68))
            math_store_angle_update_result(object, (float *)(*(char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.061086535f);
    }
    if (g_current_map_index[0] == 26 && g_hero_part_state.mode == 0 && g_hero_part_state.timer < 260) {
        object = g_hero_part_state.parts[3];
        moby_transform_joint_point(object, 0, (char *)transform);
        object += 0x10;
        qcopy((transform + 3), object);
        for (j = 0; j < 8; j++) {
            transform_vector(&position, g_part_offset_positions[j & 1], transform);
            vec_scale_to_length(&velocity, transform, 0.06666667f);
            velocity.f[3] = D_L26_001A9420_gp;
            qzero_nc(&acceleration);
            acceleration.f[3] = g_part_acceleration_params[1];
            color = FastTweenColor(D_L26_001A9428_gp, g_part_color_range[1], math_random_float_range(0.0f, 1.0f));
            {
                unsigned int rgb = color & 0xFFFFFF;
                kind = math_random_int_range(D_L26_001A9430_gp, g_part_kind_range[1]);
                duration = math_random_int_range(g_part_duration_range[0], g_part_duration_range[1]);
                size = math_random_int_range(g_part_size_range[0], g_part_size_range[1]);
                effect = part_spawn_trail(&position, &velocity, &acceleration, color, rgb,
                                       kind, duration, size, flags);
                if (effect) effect[9] = FloatToInt(2.0f) - 16;
            }
        }
    }
}

/* Samples the record's plane at its own position and returns the resident height. */
float coll_sample_height_at_position(u8 *moby, void *plane_in, void *plane_out) {
    float sample[4];

    func_002EE358(sample, plane_in, moby + 0x10);
    func_00324530(moby, sample, sample, plane_out);
    return func_002EE9C8(sample[0], sample[1]);
}

/* Scales the three vertices of the record's triangle, ordering the middle pair
   by the caller's flag. */
void vec_scale_triangle_vertices(u8 *tri, int swap_order) {
    func_002EE5F0(tri, tri, 1.0f);
    if (swap_order != 0)
        func_002EE440(tri + 0x10, tri + 0x20, tri);
    else
        func_002EE440(tri + 0x10, tri, tri + 0x20);
    func_002EE5F0(tri + 0x10, tri + 0x10, 1.0f);
    func_002EE440(tri + 0x20, tri + 0x10, tri);
}

/* func_L26_003547D8 is defined in L26_003547D8-g8.c (it reads its list through $gp). */

/* Per-frame update for a thrown projectile: it moves along its velocity with gravity, checks what
   it hits, and on impact bounces or bursts into a spray of sparks. */
void projectile_update_thrown(unsigned char *moby) {
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
    char *vars = *(char **)(moby + 0x68), *position = (char *)moby + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, vars, position);
    part_steer_effect_direction(*(int *)(vars + 0x1C), vars, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(vars, vars);
    vec_add_object_direction_scaled(position, vars, 0.0030555557f);
    part_emit_sparkle(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_item_l26_materials + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(g_ripple_l26_x, g_ripple_l26_y, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = g_projectile_l26_collision.point.f[2];
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
            Collision *collision = &g_projectile_l26_collision;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &g_projectile_l26_collision;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_thrown_l26_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (moby[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion(moby, &frame.velocity, &frame.normal);
    }
}

/* Per-frame update for a second kind of projectile: it moves, counts its age, and when it hits
   something it bounces, then takes the normal or the stronger impact response depending on age. */
void projectile_update_bouncing_aged(char *moby) {
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
    char *vars = *(char **)(moby + 0x68);
    char *position = moby + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (g_bouncing_weapon_index + g_item_l26_materials)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &g_projectile_l26_collision;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &g_projectile_l26_collision;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_thrown_l26_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            moby[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = moby + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_projectile_l26_collision;
            if (collision->count <= 0)
                goto finish;
            moby[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(moby + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(moby, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(moby, &frame.velocity, &frame.normal);
    }
}




/* func_L26_003D4590 is defined in L26_003D4590-g8.c (it reaches data through $gp and needs -frac2-zero-ti-por). */

/* func_L26_003D4930 is matched in L26_003D4930-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L26_003D4AE8 is defined in L26_002EC840-g8.c (it reads the group count and a word through $gp). */

/* func_L26_003DB818 is defined in L26_003DB818-g8.c. */

/* func_L26_003DBE18 is defined in L26_002EC840-g8.c (it reads tuning words through $gp). */

extern int FastDecTimer(short *);
extern void group_sync_counter(void *, void *);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts(float, void *, void *, int, void *);
extern char g_str_ground_effect_name[];



/* func_L26_003DC128 lives in the -g8 sibling file (it reaches a global through $gp). */

/* func_L26_003DF7E8 is defined in L26_003DF7E8-g32.c (its tables are read through $gp). */


/* Implemented in L26_002EC840-0040C8A8.c. */

