#include "common.h"

extern unsigned char g_bouncing_weapon_index;
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_spark_puff(void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_projectile_model_id __attribute__((sda));
extern int g_splash_ripple_param_a __attribute__((sda)), g_splash_ripple_param_b __attribute__((sda));
extern Collision g_collision_l17_result;
extern Material g_item_l17_material_table[];
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

/* Read once as a GP macro load in a delay slot and otherwise as lui/lw, as at -G0 in retail. */
extern int g_spark_effect_state __attribute__((sda));
typedef struct { char pad[0x30]; int phase, frame; char gap[0x15C]; char *actor; } CutsceneState;
extern CutsceneState g_cutscene_l17_state;
typedef struct EffectMoby {
    char pad0[0x28]; struct EffectMoby *next; char pad1[8]; unsigned short flags;
    char pad2[0x62]; int unknown; char pad3[0xE]; short classId;
} EffectMoby;
extern EffectMoby *g_effect_moby_list __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
typedef struct { char pad0[4]; int state; char pad1[2]; unsigned char opacity, age; } EffectTail;
typedef struct { char pad0[8]; unsigned char color, size; short life; char pad1[0x14]; EffectTail tail; } CutsceneParticle;
/* Each register bank keeps the callee's order (a0-t0: position, spin, axis, colour, count;
   f12-f15: jitter, lo, hi, size); the interleaving gives retail's argument setup order. */
extern CutsceneParticle *SpawnSpinningSparkParticle(void *, int, float, float, void *, float, unsigned int, float, int);
extern int FloatToInt(float);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void FastVecAdd(char *, char *, char *);


extern char g_hero_state[];

extern char g_path_l17_table[];

extern char g_path_point_template[];

extern char g_path_transform_template[];

extern void matrix_mul_vec3(void *, void *, void *);

extern void func_2EEEB8(void *, void *, void *);

extern int func_2EEB28(char *);

extern int func_2F00C0(float);

extern float func_2EF4E0(float);

extern float math_fabs(float);

extern float func_2F00B0(int);

extern void func_332E48(char *);

extern void anim_start_immediate();

extern void falling_object_wake_up();

extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float vec_distance_xy(void *, void *);
extern void path_clamp_move_to_area(void *, void *, void *, void *, float);
/* Picks a random open spot to the side of a start point. It tries left and right first, then
   wider diagonal spots, and stops each try at walls. Returns 1 if the first tries worked. */
int coll_find_clear_side_point(float *origin, float *target, void *out, void *object, float radius, float height)
{
    Vec left, right, farLeft, farRight, start;
    float heading, angle, dleft, dright, finalDistance;
    heading = mat_fast_helper_a(target[0] - origin[0], target[1] - origin[1]);
    angle = FastAddRotations(heading, 1.5707965f);
    left.f[0] = math_fast_sin_or_cos_a(angle) * radius;
    left.f[1] = math_fast_sin_or_cos_b(angle) * radius;
    left.f[2] = 0;
    FastVecAdd((char *)&left, (char *)&left, (char *)origin);
    angle = fast_subtract_rotations(heading, 1.5707965f);
    right.f[0] = math_fast_sin_or_cos_a(angle) * radius;
    right.f[1] = math_fast_sin_or_cos_b(angle) * radius;
    right.f[2] = 0;
    FastVecAdd((char *)&right, (char *)&right, (char *)origin);
    start.q = *(Quad *)origin;
    path_clamp_move_to_area(&start, &left, &left, object, height);
    start.q = *(Quad *)origin;
    path_clamp_move_to_area(&start, &right, &right, object, height);
    dleft = vec_distance_xy(origin, &left);
    dright = vec_distance_xy(origin, &right);
    if (radius < dleft + dright) {
        if (math_random_float_range(0, dleft + dright) < dleft) qcopy(out, &left);
        else qcopy(out, &right);
        return 1;
    }
    angle = FastAddRotations(heading, 0.78539824f);
    farLeft.f[0] = math_fast_sin_or_cos_a(angle) * 12.0f;
    farLeft.f[1] = math_fast_sin_or_cos_b(angle) * 12.0f;
    farLeft.f[2] = 0;
    FastVecAdd((char *)&farLeft, (char *)&farLeft, (char *)origin);
    angle = fast_subtract_rotations(heading, 0.78539824f);
    farRight.f[0] = math_fast_sin_or_cos_a(angle) * 12.0f;
    farRight.f[1] = math_fast_sin_or_cos_b(angle) * 12.0f;
    farRight.f[2] = 0;
    FastVecAdd((char *)&farRight, (char *)&farRight, (char *)origin);
    start.q = *(Quad *)origin;
    path_clamp_move_to_area(&start, &farLeft, &farLeft, object, height);
    start.q = *(Quad *)origin;
    path_clamp_move_to_area(&start, &farRight, &farRight, object, height);
    finalDistance = vec_distance_xy(origin, &farLeft);
    dright = vec_distance_xy(origin, &farRight);
    if (math_random_float_range(0, finalDistance + dright) < finalDistance) qcopy(out, &farLeft);
    else qcopy(out, &farRight);
    return 0;
}




/* divides two sub-object measurements taken through the float accessor, scales the ratio by a fixed
   2*pi-scale constant, folds the result through two helpers and packs a colour byte into the object's
   high word */
/* Fades a particle's colour over its lifetime and removes the particle when its time is up. */
void part_update_fading(char *particle)
{
    float life_ratio;
    float wave;
    char *extra;

    if (particle == 0)
        return;
    extra = particle + 0x20;
    if (func_2EEB28(particle + 0x24) != 0) {
        func_332E48(particle);
        return;
    }
    life_ratio = func_2F00B0(*(short *)(extra + 4)) / func_2F00B0(*(short *)(extra + 6));
    wave = func_2EF4E0(life_ratio * 6.283186f);
    *(int *)(particle + 4) = (*(int *)(particle + 4) & 0x00FFFFFF)
                       + (func_2F00C0(math_fabs(func_2F00B0(*(int *)(extra + 0xC)) * wave)) << 24);
}



/* Activates the scene's effect mobys during phase 6 and emits paired sparks from the
   scene actor during two frame windows of phases 4 and 5. */
void cutscene_update_spark_effects(unsigned char *self) {
    Vec velocity, point;
    char *obj;
    CutsceneParticle *first, *second;
    EffectTail *detail;
    int amount, state;

    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        self[0x20] = 1;
        break;
    case 1:
        if (g_spark_effect_state != 2)
            break;
        if (g_cutscene_l17_state.phase == 6) {
            EffectMoby *effect_moby;
            for (effect_moby = g_effect_moby_list; effect_moby; effect_moby = effect_moby->next) {
                if (effect_moby->classId == MOBY_CLASS_GRULCH || effect_moby->classId == 0x1249) {
                    effect_moby->unknown = 0;
                    effect_moby->flags = (effect_moby->flags | 0x43) & 0xEFFF;
                }
            }
        }
        state = g_spark_effect_state;
        if (state != 2)
            break;
        if (g_cutscene_l17_state.phase == 4 && (unsigned)(g_cutscene_l17_state.frame - 301) < 59) {
            obj = g_cutscene_l17_state.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                moby_transform_joint_to_world(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = math_random_int_below(16);
                if (math_random_int_below(2))
                    amount = -amount;
                first = SpawnSpinningSparkParticle(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 16;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                amount = 16;
                second = SpawnSpinningSparkParticle(&point, amount, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                /* Retail tests the first spark again before writing the second. */
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = amount;
                    second->color = math_random_int_below(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
                state = g_spark_effect_state;
            }
        }
        if (state != 2)
            break;
        if (g_cutscene_l17_state.phase == 5 && g_cutscene_l17_state.frame >= 531) {
            obj = g_cutscene_l17_state.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                moby_transform_joint_to_world(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = math_random_int_below(16);
                if (math_random_int_below(2))
                    amount = -amount;
                first = SpawnSpinningSparkParticle(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 16;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                amount = 16;
                second = SpawnSpinningSparkParticle(&point, amount, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = amount;
                    second->color = math_random_int_below(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
            }
        }
        break;
    }
}

/* Moves a flying projectile one step. When it hits something it either makes a splash of small
   drops or marks itself finished and sets off its hit effect. */
void splash_projectile_update(unsigned char *obj) {
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
        ((Material *)((u32)g_item_l17_material_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
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
            RippleDisturb(g_splash_ripple_param_a, g_splash_ripple_param_b, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = g_collision_l17_result.point.f[2];
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
            Collision *collision = &g_collision_l17_result;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &g_collision_l17_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_projectile_model_id && *(short *)(model + 0xAA) != 0x336)
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



/* Moves a projectile one step and counts its age. When it hits something it sets off a small
   hit effect if it is young, or a bigger one if it is older. */
void aging_projectile_update(char *obj) {
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
    frame.packet.material = (g_bouncing_weapon_index + g_item_l17_material_table)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_collision_l17_result;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &g_collision_l17_result;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_projectile_model_id && *(short *)(model + 0xAA) != 0x336)
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
            collision = &g_collision_l17_result;
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



/* func_L17_003A14A0 is defined in L17_0032C070-burst-g8.c. */

/* func_L17_003A4740 is defined in L17_0032C070-grid.c. */

/* func_L17_003BCBC8 is defined in L17_0032C070-g8.c: the -G8 profile of that
   unit is what makes its register allocation come out right. */

/* func_L17_003BCC30 is defined in L17_0032C070-path.c. */

/* func_L17_003BCEC0 is defined in L17_0032C070-path.c. */

/* func_L17_003BD310 is defined in L17_0032C070-hazard-g8.c. */

/* runs seven two-stage transforms over a record reached from an id in the sub-object; the id -1
   aborts, and the last id is echoed into the shared resident word */
/* Moves a seven-point path so it follows the platform (turned and shifted to match it) and
   remembers that path in the player data. */
void platform_attach_path_to_lift(char *moby)
{
    char *vars;
    char *point;
    char *template;
    char *position;
    char *matrix;
    char *hero;
    int path_ref;
    int i;

    vars = *(char **)(moby + 0x68);
    path_ref = *(int *)(vars + 0xD0);
    if (path_ref == -1)
        return;
    path_ref = *(int *)(g_path_l17_table + path_ref * 4);
    if (*(int *)path_ref != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    template = g_path_point_template;
    point = path_ref + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(point, template, matrix);
        template += 0x10;
        func_2EEEB8(point, point, position);
        point += 0x10;
    }
    hero = g_hero_state;
    *(unsigned short *)(hero + 0x24FE) = *(unsigned short *)(vars + 0xD0);
}

/* func_L17_003C3330 is defined in L17_0032C070-lift-g8.c. */






/* func_L17_003C4090 is defined in L17_0032C070-motion-g8.c. */

/* func_L17_003C45A0 is defined in L17_0032C070-carrier-g8.c. */



/* raises the state word to 0x920 and runs a three-argument setup, or, when it is already 0x929,
   re-runs the 0x71B0 activation if the object is still unmarked */
/* Starts a ride platform: a class 0x920 one in its first state moves on to state 1, and a class
   0x929 one in its first state runs its own set-up. */
void ride_platform_start(int moby)
{
    if (*(short *)(moby + 0xAA) == 0x920) {
        if (*(unsigned char *)(moby + 0x20) == 0) {
            *(unsigned char *)(moby + 0x20) = 1;
            anim_start_immediate(moby, 1, 0);
            return;
        }
    }
    if (*(short *)(moby + 0xAA) == 0x929) {
        if (*(unsigned char *)(moby + 0x20) == 0)
            falling_object_wake_up(moby);
    }
}



/* true for the sub-state 0x922 when the object's stage byte sits in the 2..6 window */
/* Returns 1 while a class 0x922 platform is in one of its states 2 to 6, which is while it is
   carrying the player along. */
int ride_platform_is_carrying(int moby)
{
    if (*(short *)(moby + 0xAA) != 0x922)
        return 0;
    return *(unsigned char *)(moby + 0x20) - 2U < 5;
}

/* true when the level's shared record names the given sub-state; the shared word at
   0x34E closes the answer when the record is not the level's own */
/* Returns 1 when the given object is the one the player is standing on or attached to. */
int platform_is_object_under_player(int moby)
{
    char *hero = g_hero_state;

    if (*(int *)(hero + 0x229C) == 3 || *(int *)(hero + 0x2294) == 0x1B) {
        if (*(int *)(hero + 0x588) != moby)
            goto zero;
        return 1;
    }
    if (*(short *)(hero + 0x34E) != 0)
        goto zero;
    if (*(int *)(hero + 0x33C) == moby)
        return 1;
zero:
    return 0;
}

/* twin of func_L17_003C3250 on the 0x128 sub-object id and its own table */
/* Same as func_L17_003C3250, but for the second path of the platform. */
void platform_attach_path_to_transform(char *moby)
{
    char *vars;
    char *point;
    char *template;
    char *position;
    char *matrix;
    char *hero;
    int path_ref;
    int i;

    vars = *(char **)(moby + 0x68);
    path_ref = *(int *)(vars + 0x128);
    if (path_ref == -1)
        return;
    path_ref = *(int *)(g_path_l17_table + path_ref * 4);
    if (*(int *)path_ref != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    template = g_path_transform_template;
    point = path_ref + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(point, template, matrix);
        template += 0x10;
        func_2EEEB8(point, point, position);
        point += 0x10;
    }
    hero = g_hero_state;
    *(unsigned short *)(hero + 0x24FE) = *(unsigned short *)(vars + 0x128);
}


/* func_L17_003C69A8 is defined in its dedicated-g8.c source. */

/* func_L17_003C6CE8 is defined in its dedicated-g8.c source. */

/* func_L17_003C7018 is defined in L17_0032C070-g8.c (this unit has no $gp access for it). */

/* func_L17_003C71B0 is matched in L17_003C71B0.c (built with -mno-split-addresses). */

/* Stores the second argument in the object's sub-record at 0xA4. */
void platform_set_path_index(char *moby, int path_index)
{
    *(int *)(*(char **)(moby + 0x68) + 0xA4) = path_index;
}



/* func_L17_003C7680 is matched in L17_0032C070-platform-g8.c. */

/* true when the sub-object word at 0xBC holds the value two */
/* Returns 1 when the platform's second path is in its waiting stage (stage 2). */
int platform_is_waiting(int moby)
{
    return *(int *)(*(int *)(moby + 0x68) + 0xBC) == 2;
}
