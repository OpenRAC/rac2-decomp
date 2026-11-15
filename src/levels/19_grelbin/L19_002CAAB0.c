#include "include_asm.h"
#include "common.h"

extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
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
extern void *D_L19_001AC790 __attribute__((sda));
extern int D_L19_001B31B0 __attribute__((sda)), D_L19_001B31B8 __attribute__((sda));
extern Collision D_L19_001BFE80;
extern Material D_L19_00265870[];
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
extern char *g_moby_l19_array __attribute__((sda));
extern void moby_mark_spawned(char *);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void FastVecAdd(char *, char *, char *);


extern int D_L19_001A8F00 __attribute__((sda));

/* The cutscene record: the group of L19_0042A860.c (entity count at 0x44,
 * entity list at 0x18C) with its state and frame counter at 0x30. */
typedef struct {
    u8 pad0[0x30];
    s32 state;
    s32 frame;
    u8 pad38[0x44 - 0x38];
    s16 count;
    u8 pad46[0x18C - 0x46];
    char *items[1]; /* bounded by count */
} L19Cutscene;
extern L19Cutscene D_L19_001BD740;
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks, mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
/* Separate scalars: only a plain symbol operand is one instruction to cc1, so
 * only these reach the delay slots where retail has their $gp forms. */
extern int g_current_map_index MACRO_ADDR;
extern char *D_L19_001B2814 MACRO_ADDR;
extern Vec D_L19_001B2820 MACRO_ADDR;
extern float D_L19_001B2830 MACRO_ADDR;
extern float D_L19_001B2834 MACRO_ADDR;
extern float D_L19_001B2838 MACRO_ADDR;
extern float D_L19_001B283C MACRO_ADDR;
extern float D_L19_001B2840 MACRO_ADDR;
extern int D_L19_001B2844 MACRO_ADDR;
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern int FastTweenColor(float, int, int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *part_spawn_size_changing(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *part_spawn_growing_puff(void *, void *, int, int, float, int);

/* Runs the cutscene effects: marks some actors and spawns sparks and bursts at set frames of the scene. */
void UpdateCutsceneEffects(void)
{
    Vec position, direction, axis;
    char *actor;
    int i;
    anim_start_startup_animations();
    for (i = 0; i < D_L19_001BD740.count; i++) {
        actor = D_L19_001BD740.items[i];
        if (actor && *(short *)(actor + 0xaa) == 0xe29 /* moby class 3625 */)
            *(unsigned short *)(actor + 0x34) |= 0x800;
        /* Retail makes this test without a null check: it also reads an
         * empty slot. */
        if (*(short *)(actor + 0xaa) == 0xd54 /* moby class 3412 */)
            UpdateEquipmentPieces(actor);
        if (actor && *(short *)(actor + 0xaa) == MOBY_CLASS_TV_SCREENS && *(char **)(actor + 0x68))
            math_store_angle_update_result(actor, (float *)(*(char **)(actor + 0x68) + 0xc), 0x80aaaad2, 0x80396464, 0.061086535f);
    }
    if (g_current_map_index == 19) {
        if (D_L19_001BD740.state == 4) {
            int frame = D_L19_001BD740.frame;
            if (frame == 1) {
                D_L19_001B2814 = D_L19_001BD740.items[3];
                D_L19_001B2830 = 3.5f;
                D_L19_001B2834 = 11.0f;
                D_L19_001B2838 = 10.7f;
                D_L19_001B283C = 0.0f;
                D_L19_001B2840 = 0.0f;
                D_L19_001B2844 = frame;
            }
            D_L19_001B2820.q = *(Quad *)(D_L19_001B2814 + 0x10);
            if (frame == 750) {
                D_L19_001B9900.strength = 1.0f;
                D_L19_001B9900.ticks = 15;
                D_L19_001B9900.mode = 0;
            }
            if (D_L19_001BD740.frame >= 750 && D_L19_001BD740.frame <= 770) {
                D_L19_001B2840 += D_L19_001B2838;
                if (D_L19_001B2840 >= 1.0f) {
                    do {
                        int color;
                        float angle;
                        direction.q = 0;
                        direction.f[0] = 0.72f;
                        direction.f[1] = -0.72f;
                        direction.f[3] = 1.0f;
                        color = ((u32)math_random_int_range(96, 128) << 16) | 0x1e00;
                        position.f[0] = 0.0f;
                        position.f[1] = D_L19_001B2830 * math_random_float_range(0.9f, 1.1f);
                        position.f[2] = 0.0f;
                        position.f[3] = 1.0f;
                        angle = math_random_float_range(0.0f, 6.2831855f);
                        math_apply_axis_rotation_to_quat(&position, &position, &direction, angle);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        vec_scale_to_length(&direction, &direction, math_random_float_range(1.5f, 2.5f));
                        FastVecAdd((char *)&position, (char *)&position, (char *)&direction);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&direction);
                        D_L19_001B2840 -= 1.0f;
                        {
                            int life = math_random_int_range(4, 8);
                            float speed = math_random_float_range(0.6f, 0.8f) * 210000.0f;
                            part_spawn_fading_drift(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, 0);
                        }
                        {
                            int life = math_random_int_range(4, 8);
                            float speed = math_random_float_range(0.6f, 0.8f) * 210000.0f;
                            int style = math_random_int_range(1, 7);
                            part_spawn_fading_drift(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, style);
                        }
                    } while (D_L19_001B2840 >= 1.0f);
                }
            }
            if (D_L19_001BD740.frame >= 761 && D_L19_001BD740.frame <= 839) {
                D_L19_001B283C += D_L19_001B2834;
                if (D_L19_001B283C >= 1.0f) {
                    do {
                        int color, life, style;
                        float speed, other, angle;
                        color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x803c14, 0x400000);
                        position.f[0] = 0.0f;
                        position.f[1] = 0.0f;
                        position.f[2] = D_L19_001B2830 * -0.8f;
                        position.f[3] = 1.0f;
                        direction.f[0] = 1.0f;
                        direction.f[1] = 0.0f;
                        direction.f[2] = 0.0f;
                        direction.f[3] = 1.0f;
                        /* Retail never writes axis.f[0] before this rotation. */
                        axis.f[1] = 0.0f;
                        axis.f[2] = 1.0f;
                        axis.f[3] = 1.0f;
                        math_apply_axis_rotation_to_quat(&direction, &direction, &axis, math_random_float_range(0.0f, 6.2831855f));
                        angle = math_random_float_range(0.0f, 1.5707964f);
                        math_apply_axis_rotation_to_quat(&position, &position, &direction, angle);
                        FastVecAdd((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        life = math_random_int_range(22, 55);
                        style = math_random_int_range(0, 10);
                        speed = math_random_float_range(0.5f, 1.0f) * 21000.0f;
                        other = math_random_float_range(0.7f, 1.0f) * 21000.0f;
                        part_spawn_size_changing(&position, D_L19_001A8F20, life, color, style, 128, 0, speed, other, 0.0033333334f, 3);
                        D_L19_001B283C -= 1.0f;
                    } while (D_L19_001B283C >= 1.0f);
                }
            }
        }
        if (g_current_map_index == 19 && D_L19_001BD740.state == 5 && D_L19_001BD740.frame == 1375) {
            char *burstActor = D_L19_001BD740.items[4];
            int n;
            for (n = 0; n < 47; n++) {
                int color, style, life, red, gray, high;
                float speed, angle, pitch, radius;
                radius = math_random_float_range(0.0f, 0.37f);
                angle = math_random_angle();
                pitch = math_random_angle();
                vec_build_spherical_offset(direction.f, radius, angle, pitch);
                FastVecAdd((char *)&direction, (char *)&direction, burstActor + 0x10);
                radius = math_random_float_range(0.006166667f, 0.023333333f);
                angle = math_random_angle();
                pitch = math_random_angle();
                vec_build_spherical_offset(position.f, radius, angle, pitch);
                red = math_random_int_range(47, 87);
                gray = math_random_int_range(100, 220);
                speed = math_random_float_range(70000.0f, 150000.0f);
                /* Built in two steps: as one expression cc1 regroups the four
                 * terms and shares an OR with style, unlike retail. */
                high = (red << 24) | (gray << 16) | (gray << 8);
                color = high | gray;
                style = (gray << 16) | (gray << 8) | gray;
                life = math_random_int_range(13, 42);
                part_spawn_growing_puff(&direction, &position, color, style, speed, life);
            }
        }
    }
}

/* Keeps track of up to eight linked objects and removes itself when too few of them are still alive. */
void linked_object_watcher_update(char *moby)
{
    int *vars = *(int **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 0) {
        int *ids = vars + 4;
        int *cls = vars + 12;
        char *base;
        int i;

        *(unsigned char *)(moby + 0x20) = 1;
        base = g_moby_l19_array;
        for (i = 0; i < 8; i++) {
            unsigned char *linked = (unsigned char *)(base + (ids[i] << 8));
            if (linked != 0 && linked[0x20] != 0xFE && linked[0x20] != 0xFD)
                cls[i] = *(short *)(linked + 0xAA);
            else
                cls[i] = -1;
        }
        if (vars[0] == 0) {
            *(unsigned char *)(moby + 0x20) = 2;
            *(unsigned short *)(moby + 0x34) |= 2;
        }
    } else if (*(unsigned char *)(moby + 0x20) == 1) {
        int *ids = vars + 4;
        int *cls = vars + 12;
        char *base = g_moby_l19_array;
        int alive_count = 0;
        int i;

        for (i = 0; i < 8; i++) {
            int id = ids[i];
            int saved_class;
            unsigned char *linked;
            if (id != -1 && (saved_class = cls[i]) != -1) {
                linked = (unsigned char *)(base + (id << 8));
                if (linked != 0 && *(short *)(linked + 0xAA) == saved_class && linked[0x20] != 0xFE && linked[0x20] != 0xFD) {
                    alive_count++;
                    continue;
                }
            }
            cls[i] = -1;
        }
        if (alive_count < vars[0])
            moby_mark_spawned(moby);
    }
}

/* Turns the object off while the level mode is 2 and turns it back on otherwise. */
void moby_toggle_active_by_level_mode(char *moby)
{
    if (D_L19_001A8F00 == 2) {
        *(int *)(moby + 0x98) = 0;
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    } else {
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    }
}

/* Moves a flying fragment, bounces it off what it hits, and makes a splash with drops when it lands in liquid. */
void falling_fragment_update_splash(unsigned char *fragment) {
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
    char *vars = *(char **)(fragment + 0x68), *position = (char *)fragment + 0x10;
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
    part_emit_sparkle(fragment);
    frame.packet.moby = fragment;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L19_00265870 + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(fragment + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, fragment, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L19_001B31B0, D_L19_001B31B8, 1,
                *(float *)(fragment + 0x10), *(float *)(fragment + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(fragment + 0x10);
            frame.position.f[1] = *(float *)(fragment + 0x14);
            frame.position.f[2] = D_L19_001BFE80.point.f[2];
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
            Collision *collision = &D_L19_001BFE80;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L19_001BFE80;
                model = reread->hit;
                if (*(void **)(model + 0x64) == D_L19_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                fragment[0xBC] = 1;
                qcopy(fragment + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                fragment[0xBC] = 1;
                qcopy(fragment + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        fragment[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (fragment[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion(fragment, &frame.velocity, &frame.normal);
    }
}


/* Moves a flying fragment and bounces it off whatever it hits. */
void falling_fragment_update(char *fragment) {
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
    char *vars = *(char **)(fragment + 0x68);
    char *position = fragment + 0x10;
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
    part_spawn_spark_puff(fragment);
    frame.packet.moby = fragment;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L19_00265870)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(fragment + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, fragment, &frame.packet)) {
        collision = &D_L19_001BFE80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L19_001BFE80;
            model = reread->hit;
            if (*(void **)(model + 0x64) == D_L19_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            fragment[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = fragment + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L19_001BFE80;
            if (collision->count <= 0)
                goto finish;
            fragment[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        fragment[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(fragment + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(fragment, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(fragment, &frame.velocity, &frame.normal);
    }
}


