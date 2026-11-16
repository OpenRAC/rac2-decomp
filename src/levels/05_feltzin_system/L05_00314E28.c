#include "include_asm.h"
#include "common.h"

extern void FastVecAdd(char *, char *, char *);
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
extern int g_bouncing_shot_model_id __attribute__((sda));
extern int g_ripple_l05_x __attribute__((sda)), g_ripple_l05_y __attribute__((sda));
extern Material g_item_l05_slot_table[];
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

extern void FastVecSub(void *, void *, void *);
typedef int RibbonWord __attribute__((mode(TI)));
typedef struct { float v[4]; } RibbonVector __attribute__((aligned(16)));
typedef struct {
    RibbonVector position[4];
    unsigned int color[4];
    float uv[8];
    unsigned long primitive, texture, mode, registers;
} RibbonPacket;


/* Quadword copies, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_3065F8(char *block);

extern void func_306630(char *dst, char *src, char *src2);

extern void func_306660(char *dst, char *src, char *src2);

extern void func_3066A0(char *dst, char *src, float value);

extern void func_306AD8(char *dst, char *src, char *object);

extern char *func_328508(int id);

extern char *feltzin_helper_create(char *a0, int a1);

extern int func_332AB8(int kind);

extern float func_332B50(float a, float b);

extern float func_332C18(void);

extern int func_334CB8(char *object, char *state, int value);

extern void func_32AF08(char *object);

extern int func_32E728(char *object, int flag, int *mode, char *out);

extern void func_33B330(char *dst, float a, float b, float c);

extern void func_3719A8(int a0, int a1, char *object, int a3);

extern char *func_379CA0(char *object);

extern void func_379FA0(char *object, int a1, int a2, int a3, float f0, float f1, float f2,
                        float f3, int a8, int a9, int a10);

extern void func_37AEC0(char *object, int flag);

extern void donor_transform_copy(char *object);

extern int func_379860(char *object);

extern void func_379E60(char *object, int a1, int a2, int a3);

extern void func_332708(char *object, int a1, int a2, int a3);

extern void func_37C160(char *object);

extern void func_37B538(char *object, int a1, int a2, int a3);

extern void func_37B948(char *object, int a1, float a2);

extern int func_37B888(char *object);

extern void func_37B6D0(char *object);

extern void func_3062A0(char *block);

extern int func_307840(char *buf, float value);

extern void func_2FF698(void *fn, char *object);

extern void blast_call_helper_no_args(void);

extern char g_beam_owned_records[];

/* sda: one absolute `lw` macro load at -G0, as in retail. */
extern char *g_feltzin_target_mobys __attribute__((sda));

extern void beam_fire_burst(char *object);

extern char g_sound_state[];
extern int snd_play_from_class_bank(int, int, char *, int);
extern void beam_clear_record_owners(void);
extern void feltzin_enemy_init_with_helpers(char *obj);
extern void feltzin_enemy_fire_shot(char *object);
extern void tail_trail_spawn_marks_b(char *object);
extern void beam_update_records(char *obj);
extern void heavy_lancer_update(void);

/* The fields of the record func_379CA0 returns that func_L05_00415B38 uses; +0x120 is the
   target moby (its position is at +0x10), +0x11C says one is set. */
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;

extern void tail_trail_spawn_burst(char *object);
extern float func_3067D8(char *a, char *b);
extern void feltzin_enemy_init_position(char *obj);
extern void feltzin_enemy_fire_burst_shot(char *object);
extern void tail_trail_spawn_marks_a(char *obj);

extern void feltzin_enemy_init_position_fast(char *obj);

extern int func_2F6C50(char *a0, char *a1, int a2, char *a3, int a4);

extern void func_329960(char *object, int a1, char *out);

extern void func_37AC80(float value);

extern char g_collision_l05_result[];

extern char g_hero_l05_state[];

extern char g_beam_records[];

extern int g_feltzin_challenge_state[];

extern char *g_feltzin_enemy_table __attribute__((sda));


extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(char *);
extern void math_store_angle_update_result(char *, char *, int, int, float);
extern void vec_fast_to_int_helper(char *, char *);
extern void quaternion_to_rotation_basis(char *, char *);
extern void moby_compute_local_point(char *, char *, float, float, float);
extern char *part_spawn_shockwave_burst(char *, int, int, int, int, int, int, int, int, int, int, float);
extern int math_random_int_below(int kind);
extern float math_random_signed_float_range(float, float);
extern char *moby_spawn_shot_effect(char *, char *, char *, int, int, int, int, int, float);

typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap[0xC];
    short count;
    char gap2[0x146];
    char *objects[3];
} Scene05;
extern Scene05 g_scene_objects;
extern char g_scene_spawn_entries[];
extern int g_current_map_index __attribute__((sda));


/* Level setup pass: tweaks flags on a few scenery objects and, in the intro cutscene, spawns sparks around a target object. */
void feltzin_init_scene_objects(void)
{
    float pos[4] __attribute__((aligned(16)));
    union {
        float matrix[12];
        struct { float dest[4], delta[4]; } vectors;
    } scratch __attribute__((aligned(16)));
    int i;
    char *obj;
    anim_start_startup_animations();
    for (i = 0; i < g_scene_objects.count; i++) {
        char *current = g_scene_objects.objects[i];
        if (current && *(short *)(current + 0xAA) == 0xE29 /* moby class 3625 */)
            *(unsigned short *)(current + 0x34) |= 0x800;
        if (*(short *)(current + 0xAA) == 0xD54 /* moby class 3412 */) UpdateEquipmentPieces(current);
        if (current && *(short *)(current + 0xAA) == MOBY_CLASS_TV_SCREENS) {
            char *state = *(char **)(current + 0x68);
            if (state) math_store_angle_update_result(current, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
        }
    }
    if (g_current_map_index != 5 || g_scene_objects.mode) return;
    obj = g_scene_objects.objects[2];
    if (g_scene_objects.timer == 0x62) {
        vec_fast_to_int_helper(*(char **)(obj + 0x58) + 0x10, (char *)scratch.matrix);
        quaternion_to_rotation_basis((char *)scratch.matrix, obj + 0xC0);
        moby_compute_local_point(obj, (char *)pos, 4.0f, 3.0f, 5.0f);
        part_spawn_shockwave_burst((char *)pos, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
        moby_compute_local_point(obj, (char *)pos, 9.0f, 4.0f, 4.0f);
        part_spawn_shockwave_burst((char *)pos, 35, 50, 30, 30, 30, 50, 1, 1, 1, 1, 1.0f);
    }
    if ((unsigned int)(g_scene_objects.timer - 0x29) < 0x72 && !math_random_int_below(4)) {
        float sign = 1.0f;
        float *entry;
        if (math_random_int_below(2)) sign = -1.0f;
        entry = (float *)(g_scene_spawn_entries + math_random_int_below(3) * 32);
        moby_compute_local_point(obj, (char *)pos, entry[0], entry[1], entry[2]);
        moby_compute_local_point(obj, (char *)scratch.vectors.dest, entry[4], entry[5], entry[6]);
        scratch.vectors.dest[0] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[1] += math_random_signed_float_range(0.5f, 1.5f);
        scratch.vectors.dest[2] += math_random_signed_float_range(0.5f, 1.5f);
        FastVecSub((char *)scratch.vectors.delta, (char *)scratch.vectors.dest, (char *)pos);
        vec_scale_to_length((char *)scratch.vectors.delta, (char *)scratch.vectors.delta, 1.1666667461395264f);
        moby_spawn_shot_effect(obj, (char *)pos, (char *)scratch.vectors.delta, 0x46BE20, 0x327814, 1, 0, 1, sign);
    }
}


/* func_L05_00367340 is defined in L05_00367340-g8.c (it reads its list through $gp). */

/* Moves a bouncing shot, checks what it hits, and either pops with a spray of bits or bounces off the surface. */
void bouncing_l05_shot_update(unsigned char *obj) {
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
    char *vars = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
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
    part_emit_sparkle(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_item_l05_slot_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(g_ripple_l05_x, g_ripple_l05_y, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = ((Collision *)g_collision_l05_result)->point.f[2];
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
            Collision *collision = ((Collision *)g_collision_l05_result);
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = ((Collision *)g_collision_l05_result);
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_bouncing_shot_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (obj[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
    }
}

/* Moves a bouncing shot, checks what it hits, and bounces it off the surface or explodes it once it has bounced enough. */
void bouncing_shot_update_with_limit(char *obj) {
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
    char *vars = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
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
    part_spawn_spark_puff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (g_bouncing_weapon_index + g_item_l05_slot_table)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = ((Collision *)g_collision_l05_result);
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = ((Collision *)g_collision_l05_result);
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_bouncing_shot_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = ((Collision *)g_collision_l05_result);
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(obj, &frame.velocity, &frame.normal);
    }
}



/* func_L05_00414F90 is in L05_00314E28-f7-g8.c. */

/* Per-frame update. On the first frame it initializes the object; afterwards it points the record
   at moby state+0x260, renews the D_00188660 slot in state+0x270 near that target at random and the
   one in state+0x26C when the object no longer owns it. */
void feltzin_enemy_a_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *info;
    char *rec, *rec2;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        feltzin_enemy_init_position(object);
        func_3065F8(buf);
        if (*(int *)(state + 0x264) != 0)
            func_379E60(object, 0, 0, 0);
        return;
    }
    info = (Target05 *)func_379CA0(object);
    if (info->mode == 0)
        return;
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 32.0f);
        if (info->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                info->has_target = 1;
                info->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
                if (func_3067D8(info->target + 0x10, object + 0x10) < 10.0f) {
                    rec2 = g_sound_state + *(int *)(state + 0x270) * 0x70;
                    if (*(char **)(rec2 + 0x88) != object ||
                        *(unsigned char *)(rec2 + 0x74) == 0) {
                        if (func_332AB8(0x190) == 0)
                            *(int *)(state + 0x270) =
                                snd_play_from_class_bank(0xE, 0, object, 0xFBF);
                    }
                }
            }
            if (info->x104 != 0)
                feltzin_enemy_fire_burst_shot(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            tail_trail_spawn_marks_a(object);
        }
    }
    rec = g_sound_state + *(int *)(state + 0x26C) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x26C) = snd_play_from_class_bank(0, 6, object, 0xF73);
}

/* Sets up a new enemy: starts it at a random spot around its spawn point and resets its timers. */
void feltzin_enemy_init_position(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 0x14;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x26C) = -1;
    *(int *)(state + 0x270) = -1;
    *(float *)(state + 0x180) = 20.0f;
    *(int *)(state + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.02f;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

/* Runs the object's pending effect when three guards clear, then marks the run. */
void feltzin_enemy_fire_burst_shot(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *info;

    info = func_379CA0(object);
    if (info == 0)
        return;
    if (*(int *)(info + 0x120) == 0)
        return;
    if (*(int *)(state + 0x268) != 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 1)
        func_379FA0(object, 0x60800000, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    *(int *)(state + 0x268) = 0x14;
}

/* func_L05_00415958 is defined in L05_00415958-qcopy.c. */

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set,
   clears the owners of the 128 interpolation records; afterwards it creates the two
   func_L05_00416D68 children once, points the record at moby state+0x260, and renews the
   D_00188660 slot in state+0x274 when the object no longer owns it. */
void feltzin_enemy_b_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    char *rec;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        feltzin_enemy_init_with_helpers(object);
        func_3065F8(buf);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_379E60(object, (int)beam_clear_record_owners, 0, 0);
            base = g_beam_records;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)func_379CA0(object);
    if (r->mode == 0)
        return;
    if (*(int *)(state + 0x26C) == 0 && *(int *)(state + 0x270) == 0) {
        *(int *)(state + 0x26C) = (int)feltzin_helper_create(object, 0);
        *(int *)(state + 0x270) = (int)feltzin_helper_create(object, 1);
        *(float *)(*(int *)(state + 0x26C) + 0x2C) = *(float *)(object + 0x2C);
        *(float *)(*(int *)(state + 0x270) + 0x2C) = *(float *)(object + 0x2C);
    }
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 32.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                feltzin_enemy_fire_shot(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            tail_trail_spawn_marks_b(object);
        }
    }
    rec = g_sound_state + *(int *)(state + 0x274) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x274) = snd_play_from_class_bank(1, 6, object, 0xF76);
    beam_update_records(object);
    func_2FF698(heavy_lancer_update, object);
}

/* Clears one int field of each of 128 strided records. */
void beam_clear_record_owners(void)
{
    char *base = g_beam_records;
    int *p = (int *)(base + 0x27F0);
    int i = 0x7F;

    do {
        *p = 0;
        p -= 0x14;
        i--;
    } while (i >= 0);
}

/* Sets up a new enemy: starts it at a random spot around its spawn point and creates its two helper objects when needed. */
void feltzin_enemy_init_with_helpers(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *info;
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    info = func_379CA0(obj);
    *(int *)(info + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x274) = -1;
    *(float *)(state + 0x180) = 5.0f;
    *(int *)(state + 0x268) = 0;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
    if (*(int *)(info + 0x110) == 1) {
        *(int *)(state + 0x26C) = feltzin_helper_create(obj, 0);
        *(int *)(state + 0x270) = feltzin_helper_create(obj, 1);
    } else {
        *(int *)(state + 0x26C) = 0;
        *(int *)(state + 0x270) = 0;
    }
    *(float *)(obj + 0x2C) = 0.02f;
}

/* Clears one of two state words on the object's sub-record, by mode. */
void feltzin_helper_clear_slot(int object, int mode)
{
    int state = *(int *)(object + 0x68);

    switch (mode) {
    case 0:
        *(int *)(state + 0x26C) = 0;
        break;
    case 1:
        *(int *)(state + 0x270) = 0;
        break;
    }
}

/* Spawns the object's effect after three guards, then runs the follow-up by kind. */
void feltzin_enemy_fire_shot(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *info;

    info = func_379CA0(object);
    if (info == 0)
        return;
    if (*(int *)(info + 0x120) == 0)
        return;
    if (*(int *)(state + 0x268) != 0)
        return;
    func_379FA0(object, 0x60408020, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    if (func_332AB8(3) != 0)
        func_3719A8(0, 0, object, 0xF76);
    *(int *)(state + 0x268) = 0xF;
}


/* func_L05_004161B0 lives in its own compiler-profile unit. */

/* func_L05_00416468 is defined in L05_00416468-g8.c. */


/* func_L05_00416918 is defined in L05_00416918.c. */

/* Creates a helper object attached to an owner, on the left or right side, and returns it. */
char *feltzin_helper_create(char *owner, int side)
{
    char *child = func_328508(0xF81 /* moby class 3969 */);

    if (child != 0) {
        char *child_vars = *(char **)(child + 0x68);

        *(unsigned char *)(child + 0x30) = 0xFF;
        *(unsigned short *)(child + 0x32) = 0x1FF;
        *(unsigned short *)(child + 0x34) = *(unsigned short *)(child + 0x34) | 0x100;
        *(unsigned char *)(child + 0x20) = 0;
        *(char **)(child_vars + 0x50) = owner;
        *(int *)(child_vars + 0x54) = side;
        func_3065F8(child_vars + 0x30);
        func_3065F8(child_vars + 0x40);
        donor_transform_copy(child);
        func_32AF08(child);
    }
    return child;
}

/* Builds the sub-record's three planes and blends them onto the object's transform. */

/* Blends the sub-record into the object's transform once three guards clear. */
void feltzin_helper_check_hit_attach(char *object, char *arg1)
{
    char *sub = *(char **)(object + 0x68);
    char buf[16];
    char buf2[16];
    char *r;
    char *base;
    int value;

    r = func_379CA0(*(char **)(sub + 0x50));
    func_329960(object, 0, buf);
    func_306660(buf2, buf, object + 0x10);
    if (func_2F6C50(arg1, buf, 0, object, 0) == 0)
        return;
    base = g_collision_l05_result;
    value = *(int *)(base + 0x18);
    if (value == 0)
        return;
    if (value != *(int *)(r + 0x120))
        return;
    func_306630(object + 0x10, buf2, base + 0x20);
    func_37AC80(2.0f);
    {
        char *state = g_hero_l05_state;

        *(float *)(state + 0x160) = 0.05f;
        *(int *)(state + 0x168) = 0x1E;
        *(int *)(state + 0x16C) = 0;
    }
    *(unsigned char *)(object + 0x20) = 4;
}

/* Checks whether the object was hit and, if so, switches it to its end state. */
int feltzin_helper_end_if_hit(char *object)
{
    int hit = func_334CB8(object, (char *)0x230000, 0);

    *(unsigned char *)(object + 0xA8) = 0xFF;
    if (hit != 0)
        *(unsigned char *)(object + 0x20) = 4;
}

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set, clears
   the owners of the 128 interpolation records; afterwards it points the record at moby state+0x260
   and runs func_L05_0041CE00 unless func_307840 returns -1 for the object's position. */
void feltzin_enemy_c_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    Vec buf;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        feltzin_enemy_init_position_fast(object);
        func_332708(object, 1, 0, 0);
        func_3065F8((char *)&buf);
        *(float *)(object + 0x48) = func_332B50(0.9f, 1.1f);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_379E60(object, 0, 0, 0);
            base = g_beam_owned_records;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)func_379CA0(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 64.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                beam_fire_burst(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            qcopy(&buf, object + 0x10);
            buf.f[3] = *(float *)(object + 0xC) * 0.00097656f;
            if (func_307840((char *)&buf, 100.0f) != -1)
                tail_trail_spawn_burst(object);
        }
    }
    func_2FF698(blast_call_helper_no_args, object);
}

/* Sets up a new enemy: starts it at a random spot around its spawn point and resets its timers. */
void feltzin_enemy_init_position_fast(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x268) = 0;
    *(float *)(state + 0x180) = 5.0f;
    *(float *)(obj + 0x2C) = 0.08f;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

/* func_L05_0041CB68 is defined in L05_004161B0.c (-fno-gcse profile). */

/* func_L05_0041CFE8 is defined in L05_0041CFE8-g8.c. */

/* shared native body of family 5a97ab89858c */
/* Fills a record with a default square of four corner points and clears the rest of it. */
void quad_record_init_default(char *record)
{
    *(long long *)(record + 112) = 0;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 0x0000FF9000000260LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}



/* func_L05_0041DF58 is defined in L05_0041DF58-g8.c. */

/* func_L05_0041EF00 is defined in L05_0041EF00-g8.c. */

/* func_L05_0041FC60 is built with -G8: see L05_00314E28-g8.c. */

/* func_L05_0041FD48 is built with -G8: see L05_00314E28-g8.c. */




/* func_L05_0041FFF8 is built with -G8: see L05_00314E28-g8.c. */
