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

/* Updates a thrown projectile: moves it, tests its path for a hit, splashes and ripples when it falls into water, and bounces off or stops at a surface. */
void falling_l12_spark_update_pal(unsigned char *moby) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, vars, position);
    part_steer_effect_direction(*(int *)(vars + 0x1C), vars, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(vars, vars);
    vec_add_object_direction_scaled(position, vars, 0.0044f);
    part_emit_sparkle_pal(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_weapon_l00_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
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
            RippleDisturb(g_ripple_object, g_ripple_param, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.030000001f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = g_collision_result.point.f[2];
            effect = moby_spawn_scaled_effect(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.060000002f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.060000002f, 0.13000001f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2_pal(&frame.position, spread, math_random_int_below(2), lifetime);
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
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
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
        part_spawn_big_explosion_pal(moby, &frame.velocity, &frame.normal);
    }
}


extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst_pal(void *, void *, void *);
extern void part_spawn_spark_puff_pal(void *);

/* Updates a bouncing projectile (a variant of the one above): moves it along its direction, tests the path for a hit, and hands the bounce to the matching hit routine. */
void thrown_l12_shard_update_pal(char *moby) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.00044f);
    part_spawn_spark_puff_pal(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (g_bouncing_weapon_index + g_weapon_l00_table)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
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
            moby[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = moby + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_result;
            if (collision->count <= 0)
                goto finish;
            moby[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(moby + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 17)
            part_spawn_big_explosion_pal(moby, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst_pal(moby, &frame.velocity, &frame.normal);
    }
}


/* func_PAL_L12_003A44BC: per-frame update of a crate, after RAC1's crate_update
 * (OpenRAC/rac1-decomp, src/overlays/shared/morphoray_chicken_and_drones.c, GPL-3.0).
 * States: 0 initialize, 1 process hits, 2 class-change cooldown, 3 broken, 4 reactivation delay,
 * 5 detonation countdown, 6 wait to respawn. */
typedef struct CrateMoby CrateMoby;

typedef struct {
    char pad00[0x10];
    int collision;              /* 0x10 */
} CrateClass;

/* The hit message func_002A9640 returns. */
typedef struct {
    char pad00[0x24];
    int flags;                  /* 0x24: 0x1000000 a touch, 0x20000 detonates at once */
    char pad28[4];
    float f2C;                  /* 0x2C */
} CrateHit;

typedef struct {
    char pad00[0x1E];
    unsigned short flags;       /* 0x1E */
} CrateColl;

/* A crate's instance data. */
typedef struct {
    char pad00[0x20];
    CrateColl coll;             /* 0x20 */
    char pad40[0x90 - 0x40];
    float f90[4];               /* 0x90 */
    CrateMoby *above;           /* 0xA0: the crate stacked on this one */
    CrateMoby *below;           /* 0xA4: the crate this one stands on */
    int fA8;                    /* 0xA8 */
    int flags;                  /* 0xAC: 0xC runs the stack motion, clear bit 0 attaches to the ground */
    char padB0[4];
    int frame;                  /* 0xB4: D_001B1688 when last updated */
    long long saved_color;       /* 0xB8 */
    char padC0[6];
    short fC6;                  /* 0xC6 */
    unsigned char respawns;     /* 0xC8 */
    unsigned char respawn_timer; /* 0xC9: 255 for never */
    unsigned char burst_frame;   /* 0xCA */
    char padCB;
    int fCC;                    /* 0xCC */
    char padD0[0xFC - 0xD0];
    void *linked;               /* 0xFC */
    int f100;                   /* 0x100 */
} CrateVars;

struct CrateMoby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    unsigned char group;        /* 0x21 */
    char pad22[2];
    CrateClass *pclass;         /* 0x24 */
    char pad28[0x31 - 0x28];
    unsigned char visible;      /* 0x31 */
    short draw_distance;         /* 0x32 */
    unsigned short flags;       /* 0x34 */
    char pad36[2];
    long long color;            /* 0x38 */
    char pad40[0x68 - 0x40];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0x98 - 0x6C];
    int collision;              /* 0x98 */
    char pad9C[0xA8 - 0x9C];
    unsigned char hit_slot;      /* 0xA8 */
    char padA9;
    short class_id;               /* 0xAA */
    char padAC[0xB4 - 0xAC];
    short fB4;                  /* 0xB4 */
    char padB6[0xBC - 0xB6];
    unsigned char command;      /* 0xBC: the countdown of states 2, 4 and 5 */
    char padBD[0xC0 - 0xBD];
    float forward[4];           /* 0xC0 */
    char padD0[0x10];
    float up[4];                /* 0xE0 */
};

/* Prefix of the hero. */
typedef struct {
    char pad000[0x26C];
    CrateMoby *coll_hit_moby;     /* 0x26C */
    CrateMoby *f270;            /* 0x270 */
    char pad274[0x33C - 0x274];
    CrateMoby *ground_moby;      /* 0x33C */
    char pad340[0x34E - 0x340];
    short air_frames;            /* 0x34E */
    char pad350[0x588 - 0x350];
    CrateMoby *ledge_moby;       /* 0x588 */
    char pad58C[0x2290 - 0x58C];
    CrateMoby *moby;            /* 0x2290 */
    char pad2294[0x229C - 0x2294];
    int f229C;                  /* 0x229C */
} CrateHero;

typedef struct {
    float position[4];          /* 0x00 */
    CrateMoby *moby;            /* 0x10 */
    int f14;                    /* 0x14 */
    char pad18[4];
    float f1C;                  /* 0x1C */
    int f20;                    /* 0x20 */
    char pad24[0xC];
} __attribute__((aligned(16))) CrateBurst;

extern int g_game_time MACRO_ADDR;   /* the frame counter */
extern char g_hero_state[];
extern char g_nearby_mobys[];
extern int g_hero_mode;


extern void UpdateCrateStackMotion_pal(CrateMoby *);
extern CrateHit *part_find_owned_effect_slot(CrateMoby *, int, int);
extern int moby_is_in_special_class_range(CrateMoby *);
extern void vec_clear_128(void *);
extern void GroundAttachedUpdate(CrateMoby *);
extern void *moby_spawn_linked_child(CrateMoby *, int);
extern int flag_set_first_pending(CrateMoby *);
extern void DestroyCrate_pal(CrateMoby *, int, CrateHit *);
extern void crate_drop_loot_pal(CrateMoby *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern int coll_process_hit(void *, int, CrateMoby *, void *, float);
extern void moby_queue_knockback_for_nodes(CrateMoby *, void *, void *, int, CrateMoby *, int, int, int, float, float, float);
extern int math_random_int_range(int, int);
extern void moby_mark_spawned(CrateMoby *);
extern int math_fast_helper_a(void *, float);
extern int vec_fast_helper_a(unsigned char *);
extern void moby_set_state(CrateMoby *, int, int);
extern int GetFirstMobyInGroup(CrateMoby **, int, int, int);
extern int GetNextMobyInGroup(CrateMoby **, CrateMoby *, int, int);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern int PlayMobySound(int, int, CrateMoby *);
extern void set_moby_color(CrateMoby *, int, int, int);

void todano_crate_update_pal(CrateMoby *moby)
{
    CrateBurst burst;
    float position[4] __attribute__((aligned(16)));
    CrateMoby *found;
    CrateVars *vars = moby->vars;
    CrateHit *hit;
    int touched;
    CrateColl *coll = &vars->coll;

    if (vars->flags & 0xC) {
        if (vars->frame != g_game_time) {
            UpdateCrateStackMotion_pal(moby);
        }
    }
    if (vars->above == 0) {
        coll->flags |= 1;
    }
    hit = part_find_owned_effect_slot(moby, 0x5830001, 0);
    touched = 0;
    if (hit != 0 && hit->flags == 0x1000000) {
        hit = 0;
        touched = 1;
    }
    switch (moby->state) {
    case 0:
        if (vars->above != 0 && !moby_is_in_special_class_range(vars->above)) {
            vars->above = 0;
        }
        if (vars->below != 0 && !moby_is_in_special_class_range(vars->below)) {
            vars->below = 0;
        }
        vec_clear_128(vars->f90);
        moby->state = 1;
        vars->fA8 = 0;
        if (moby->class_id == MOBY_CLASS_AMMO_CRATE) {
            vars->frame++;
        }
        if (vars->fCC == 0) {
            vars->flags |= 0x14;
            if ((vars->flags ^ 1) & 1) {
                GroundAttachedUpdate(moby);
            }
        }
        vars->linked = 0;
        if (moby->class_id == MOBY_CLASS_AMMO_CRATE) {
            vars->fC6 = 100;
        } else if (moby->class_id == MOBY_CLASS_NANOTECH_CRATE) {
            vars->linked = moby_spawn_linked_child(moby, 0);
        } else if (moby->class_id == MOBY_CLASS_PURPLE_NANOTECH_CRATE) {
            vars->linked = moby_spawn_linked_child(moby, 1);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            vars->f100 = 0;
        }
        if (moby->class_id == MOBY_CLASS_EXPLOSIVE_CRATE &&
            (((CrateHero *)g_hero_state)->f270 == moby || ((CrateHero *)g_hero_state)->coll_hit_moby == moby ||
             (((CrateHero *)g_hero_state)->ground_moby == moby && ((CrateHero *)g_hero_state)->air_frames == 0) ||
             ((CrateHero *)g_hero_state)->ledge_moby == moby || touched)) {
            if (((CrateHero *)g_hero_state)->f229C == 15) {
                DestroyCrate_pal(moby, 1, 0);
                crate_drop_loot_pal(moby);
                break;
            }
            moby->command = 0;
            moby->state = 5;
            break;
        }
        if (hit != 0 && hit->f2C > 0.0f) {
            int do_hit = 1;

            if (moby->class_id == 0x1F6 /* moby class 502 */ && !(hit->flags & 0x20000)) {
                do_hit = 0;
            }
            if (moby->class_id == MOBY_CLASS_EXPLOSIVE_CRATE) {
                moby->state = 5;
                if (hit->flags & 0x20000) {
                    moby->command = 1;
                } else {
                    moby->command = FloatToInt(((math_random_float_range(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
                }
                vars->saved_color = moby->color;
                do_hit = 0;
            }
            if (do_hit) {
                DestroyCrate_pal(moby, moby->class_id == MOBY_CLASS_EXPLOSIVE_CRATE, hit);
                crate_drop_loot_pal(moby);
            }
            moby->hit_slot = 255;
        }
        break;
    case 2:
        if (--moby->command == 255) {
            moby->hit_slot = 255;
            moby->state = 1;
        }
        break;
    case 3:
        if (moby->class_id == MOBY_CLASS_EXPLOSIVE_CRATE && vars->burst_frame < 18) {
            float radius;
            int target;

            burst.moby = moby;
            burst.f1C = 2.0f;
            qcopy(&burst, moby->forward);
            burst.f20 = 0;
            vec_scale_to_length(position, moby->up, 0.5f);
            FastVecAdd(position, position, moby->position);
            radius = IntToFloat(vars->burst_frame) * 0.05882353f;
            burst.f14 = 1;
            coll_process_hit(position, 16, moby, &burst, radius + radius);
            burst.f14 = 0x30000;
            target = coll_process_hit(position, 16, ((CrateHero *)g_hero_state)->moby, 0, radius * 3.0f);
            if (target != 0) {
                moby_queue_knockback_for_nodes(moby, position, g_nearby_mobys, target, ((CrateHero *)g_hero_state)->moby, 0x10000, 0, 0x30000, 4.0f, 1.0f, 1.0f);
            }
            vars->burst_frame++;
        } else if (vars->respawns != 0) {
            moby->flags = (moby->flags | 0x41) & 0xEFFF;
            moby->collision = 0;
            if (moby->fB4 >= 2) {
                moby->fB4 = 1;
            }
            moby->state = 6;
            if (vars->respawn_timer != 255) {
                vars->respawn_timer = math_random_int_range(30, 60);
            }
        } else {
            moby_mark_spawned(moby);
            break;
        }
        moby->hit_slot = 255;
        break;
    case 6:
        vars->f100++;
        if (vars->respawn_timer == 255) {
            break;
        }
        qcopy(&burst, moby->position);
        burst.position[2] += 0.5f;
        burst.position[3] = 1.0f;
        if (math_fast_helper_a(&burst, (float)moby->draw_distance) != -1 || !vec_fast_helper_a(&vars->respawn_timer)) {
            goto done;
        }
        if (moby->group == 255) {
            moby_set_state(moby, 1, -1);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->collision = moby->pclass->collision;
            break;
        }
        GetFirstMobyInGroup(&found, moby->group, 0, 0);
        while (found != 0) {
            if (moby != found && !(vec_distance_xy(moby->position, found->position) > 0.1f) && found->state == 1) {
                CrateVars *other = found->vars;

                if (other->above == 0) {
                    qcopy(moby->position, found->position);
                    moby->position[2] += 1.0f;
                    other->above = moby;
                    vars->below = found;
                    vars->above = 0;
                    moby->state = 1;
                    moby->visible = 1;
                    moby->flags &= 0xFFFE;
                    moby->collision = moby->pclass->collision;
                    moby->flags |= 0x1000;
                    break;
                }
            }
            GetNextMobyInGroup(&found, found, 0, 0);
        }
        if (moby->state != 1) {
            moby->position[2] = coll_probe_ground_height_below(moby->position, 0, 0.5f);
            moby->state = 1;
            vars->above = 0;
            vars->below = 0;
            moby->visible = 1;
            moby->flags &= 0xFFFE;
            moby->collision = moby->pclass->collision;
        }
        goto done;
    case 5:
        if (moby->command == 0) {
            moby->command = 149;
            vars->saved_color = moby->color;
        } else if (moby->command >= 13 && hit != 0) {
            moby->command = FloatToInt(((math_random_float_range(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
        }
        if (moby->command % 50 == 47 || moby->command == 11) {
            PlayMobySound(1, 32, moby);
        }
        if (moby->command % 50 > 33 || moby->command < 12) {
            set_moby_color(moby, 200, 64, 64);
        } else {
            moby->color = vars->saved_color;
        }
        if (moby->command == 1 || g_hero_mode == 22) {
            moby->color = vars->saved_color;
            DestroyCrate_pal(moby, 1, 0);
            crate_drop_loot_pal(moby);
        }
        moby->hit_slot = 255;
        moby->command--;
        break;
    case 4:
        if (vec_fast_helper_a(&moby->command)) {
            moby->state = 1;
            moby->flags &= 0xFFFE;
        }
done:
        moby->hit_slot = 255;
        break;
    }
}
