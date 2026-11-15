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
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision g_collision_result;
extern Material g_weapon_l00_table[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void func_PAL_L00_00392250(void *);
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
extern void func_PAL_002C0838(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(void *);
extern void table_clear_entry_flag(int);
extern void func_PAL_L00_00390F48(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

void func_PAL_L12_00396400(unsigned char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, ctx, position);
    part_steer_effect_direction(*(int *)(ctx + 0x1C), ctx, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(ctx, ctx);
    vec_add_object_direction_scaled(position, ctx, 0.0044f);
    func_PAL_L00_00392250(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_weapon_l00_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            vec_clear_128(ctx);
            *(float *)(ctx + 8) = -0.030000001f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
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
                func_PAL_002C0838(&frame.position, spread, math_random_int_below(2), lifetime);
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
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0xF1)
                    goto finish;
                reread = &g_collision_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
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
        func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
    }
}


extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void func_PAL_L00_00391958(void *, void *, void *);
extern void func_PAL_L00_00392500(void *);

void func_PAL_L12_00396818(char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.00044f);
    func_PAL_L00_00392500(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + g_weapon_l00_table)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_collision_result;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0xF2)
                goto finish;
            reread = &g_collision_result;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_result;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 17)
            func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
        else
            func_PAL_L00_00391958(obj, &frame.velocity, &frame.normal);
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
    long long savedColor;       /* 0xB8 */
    char padC0[6];
    short fC6;                  /* 0xC6 */
    unsigned char respawns;     /* 0xC8 */
    unsigned char respawnTimer; /* 0xC9: 255 for never */
    unsigned char burstFrame;   /* 0xCA */
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
    short drawDistance;         /* 0x32 */
    unsigned short flags;       /* 0x34 */
    char pad36[2];
    long long color;            /* 0x38 */
    char pad40[0x68 - 0x40];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0x98 - 0x6C];
    int collision;              /* 0x98 */
    char pad9C[0xA8 - 0x9C];
    unsigned char hitSlot;      /* 0xA8 */
    char padA9;
    short oClass;               /* 0xAA */
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
    CrateMoby *collHitMoby;     /* 0x26C */
    CrateMoby *f270;            /* 0x270 */
    char pad274[0x33C - 0x274];
    CrateMoby *groundMoby;      /* 0x33C */
    char pad340[0x34E - 0x340];
    short airFrames;            /* 0x34E */
    char pad350[0x588 - 0x350];
    CrateMoby *ledgeMoby;       /* 0x588 */
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
extern char D_001BF000[];
extern int D_0018C0BC;


extern void func_PAL_00313A70(CrateMoby *);
extern CrateHit *part_find_owned_effect_slot(CrateMoby *, int, int);
extern int moby_is_in_special_class_range(CrateMoby *);
extern void vec_clear_128(void *);
extern void GroundAttachedUpdate(CrateMoby *);
extern void *moby_spawn_linked_child(CrateMoby *, int);
extern int flag_set_first_pending(CrateMoby *);
extern void func_PAL_00313538(CrateMoby *, int, CrateHit *);
extern void func_PAL_003133E0(CrateMoby *);
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
extern void PlayMobySound(int, int, CrateMoby *);
extern void set_moby_color(CrateMoby *, int, int, int);

void func_PAL_L12_003A44BC(CrateMoby *moby)
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
            func_PAL_00313A70(moby);
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
        if (moby->oClass == 0x1FF) {
            vars->frame++;
        }
        if (vars->fCC == 0) {
            vars->flags |= 0x14;
            if ((vars->flags ^ 1) & 1) {
                GroundAttachedUpdate(moby);
            }
        }
        vars->linked = 0;
        if (moby->oClass == 0x1FF) {
            vars->fC6 = 100;
        } else if (moby->oClass == 0x1F5) {
            vars->linked = moby_spawn_linked_child(moby, 0);
        } else if (moby->oClass == 0x200) {
            vars->linked = moby_spawn_linked_child(moby, 1);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            vars->f100 = 0;
        }
        if (moby->oClass == 0x1F9 &&
            (((CrateHero *)g_hero_state)->f270 == moby || ((CrateHero *)g_hero_state)->collHitMoby == moby ||
             (((CrateHero *)g_hero_state)->groundMoby == moby && ((CrateHero *)g_hero_state)->airFrames == 0) ||
             ((CrateHero *)g_hero_state)->ledgeMoby == moby || touched)) {
            if (((CrateHero *)g_hero_state)->f229C == 15) {
                func_PAL_00313538(moby, 1, 0);
                func_PAL_003133E0(moby);
                break;
            }
            moby->command = 0;
            moby->state = 5;
            break;
        }
        if (hit != 0 && hit->f2C > 0.0f) {
            int doHit = 1;

            if (moby->oClass == 0x1F6 && !(hit->flags & 0x20000)) {
                doHit = 0;
            }
            if (moby->oClass == 0x1F9) {
                moby->state = 5;
                if (hit->flags & 0x20000) {
                    moby->command = 1;
                } else {
                    moby->command = FloatToInt(((math_random_float_range(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
                }
                vars->savedColor = moby->color;
                doHit = 0;
            }
            if (doHit) {
                func_PAL_00313538(moby, moby->oClass == 0x1F9, hit);
                func_PAL_003133E0(moby);
            }
            moby->hitSlot = 255;
        }
        break;
    case 2:
        if (--moby->command == 255) {
            moby->hitSlot = 255;
            moby->state = 1;
        }
        break;
    case 3:
        if (moby->oClass == 0x1F9 && vars->burstFrame < 18) {
            float radius;
            int target;

            burst.moby = moby;
            burst.f1C = 2.0f;
            qcopy(&burst, moby->forward);
            burst.f20 = 0;
            vec_scale_to_length(position, moby->up, 0.5f);
            FastVecAdd(position, position, moby->position);
            radius = IntToFloat(vars->burstFrame) * 0.05882353f;
            burst.f14 = 1;
            coll_process_hit(position, 16, moby, &burst, radius + radius);
            burst.f14 = 0x30000;
            target = coll_process_hit(position, 16, ((CrateHero *)g_hero_state)->moby, 0, radius * 3.0f);
            if (target != 0) {
                moby_queue_knockback_for_nodes(moby, position, D_001BF000, target, ((CrateHero *)g_hero_state)->moby, 0x10000, 0, 0x30000, 4.0f, 1.0f, 1.0f);
            }
            vars->burstFrame++;
        } else if (vars->respawns != 0) {
            moby->flags = (moby->flags | 0x41) & 0xEFFF;
            moby->collision = 0;
            if (moby->fB4 >= 2) {
                moby->fB4 = 1;
            }
            moby->state = 6;
            if (vars->respawnTimer != 255) {
                vars->respawnTimer = math_random_int_range(30, 60);
            }
        } else {
            moby_mark_spawned(moby);
            break;
        }
        moby->hitSlot = 255;
        break;
    case 6:
        vars->f100++;
        if (vars->respawnTimer == 255) {
            break;
        }
        qcopy(&burst, moby->position);
        burst.position[2] += 0.5f;
        burst.position[3] = 1.0f;
        if (math_fast_helper_a(&burst, (float)moby->drawDistance) != -1 || !vec_fast_helper_a(&vars->respawnTimer)) {
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
            vars->savedColor = moby->color;
        } else if (moby->command >= 13 && hit != 0) {
            moby->command = FloatToInt(((math_random_float_range(5.0f, 15.0f)) * 5.0f + 2.0f) * 0.16666667f);
        }
        if (moby->command % 50 == 47 || moby->command == 11) {
            PlayMobySound(1, 32, moby);
        }
        if (moby->command % 50 > 33 || moby->command < 12) {
            set_moby_color(moby, 200, 64, 64);
        } else {
            moby->color = vars->savedColor;
        }
        if (moby->command == 1 || D_0018C0BC == 22) {
            moby->color = vars->savedColor;
            func_PAL_00313538(moby, 1, 0);
            func_PAL_003133E0(moby);
        }
        moby->hitSlot = 255;
        moby->command--;
        break;
    case 4:
        if (vec_fast_helper_a(&moby->command)) {
            moby->state = 1;
            moby->flags &= 0xFFFE;
        }
done:
        moby->hitSlot = 255;
        break;
    }
}
