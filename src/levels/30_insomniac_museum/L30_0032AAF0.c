#include "common.h"
#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0x138]; float f138, f13C; } InputExtra;

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern void part_spawn_spark_puff(void *);
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_thrown_l30_model_id __attribute__((sda));
extern int g_ripple_pos_x __attribute__((sda)), g_ripple_pos_y __attribute__((sda));
extern Collision g_collision_l30_result;
extern Material g_item_l30_material_table[];
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


extern char g_hero_position[];
extern char g_museum_water_grids[];
extern char g_museum_water_grid_points[];

extern void *memset(char *, int, int);
extern int IsPointInCuboid(char *, int);
extern void anim_start_blended(char *, int, int, int);
extern void cam_reset_entry(int);
extern char g_music_state[];
extern char g_museum_entry_vec[];
extern char g_museum_trigger_table[];
extern char g_museum_trigger_flag[];
extern char g_museum_exhibit_models[];
extern int func_2FB3C8(int);
extern void func_3132D8(void *, unsigned int, int, int, int, int, int, int, int, int);
extern void func_316DB8(char *);
extern int func_32C0D0(char *, int);
extern void func_320FD0(char *, int, int);

typedef struct {
    float x;
    float y;
    float z;
    float u;
    float v;
    float w;
} Vec6;

typedef struct {
    unsigned char pad[0x1E0];
    unsigned short mode;
    unsigned char pad2[0x1FB0 - 0x1E2];
    float f1FB0;
    float f1FB4;
    unsigned char pad3[0x22BC - 0x1FB8];
    unsigned char flag;
} D00189E20_View;

extern D00189E20_View g_hero_state;

typedef struct {
    unsigned char pad[0x124];
    float f124;
    float f128;
    float f12C;
    unsigned char pad2[8];
    float f138;
    float f13C;
} D00138180_View;

extern D00138180_View g_pad_state;

extern float func_321018(float);




/* Blends smoothly between two numbers; the third number says how far along to go, from 0 to 1. */
float math_l30_lerp_float(float from, float to, float blend) {
    return from * (1.0f - blend) + to * blend;
}

typedef struct {
    float x;
    float y;
} L30Pair2f;

/* Clears the 0x1B00-byte block and lays a 24-by-24 grid of two-float cells over the table at
   0x235560: every cell's first float comes from its row index and its second from its column,
   both on a one-sixth step starting at -2. */
/* Sets up the museum water surface: it clears the heights and lays out the 24 by 24 points of the water grid. */
void museum_water_init_grid(void) {
    int i;
    int j;

    memset(g_museum_water_grids, 0, 0x1B00);
    for (i = 0; i < 24; i++) {
        L30Pair2f *row = (L30Pair2f *)(g_museum_water_grid_points + i * 0xC0);

        for (j = 0; j < 24; j++) {
            row[j].x = i * (1.0f / 6.0f) + -2.0f;
            row[j].y = j * (1.0f / 6.0f) + -2.0f;
        }
    }
}

/* func_L30_00382FB8 is defined in L30_00382FB8-g8.c. */

/* func_L30_003830D8 needs the -g8 sibling: it reaches its globals through $gp.
   Its C is in nonmatching/levels/ for now. */


/* func_L30_003831E8 is defined in L30_003831E8-g8.c. */

/* func_L30_00383398 is in L30_00383398-g8.c. */

/* func_L30_00383928 is in L30_00383928-g8.c. */

/* func_L30_003840E0 uses small data in L30_0032AAF0-g8.c. */

/* Updates a museum trigger object (moby class 4839). It starts up, then watches a value and switches between its two waiting states as the value turns on and off. */
void museum_trigger_update(char *obj) {
    char *vars = *(char **)(obj + 0x68);

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        if (*(int *)vars == -1) {
            func_316DB8(obj);
        } else {
            func_320FD0(obj, 1, -1);
        }
        break;
    case 1:
        if (func_32C0D0(g_museum_trigger_table, *(int *)vars) != 0) {
            *(unsigned char *)g_museum_trigger_flag = 1;
            func_320FD0(obj, 2, -1);
        }
        break;
    case 2:
        if (func_32C0D0(g_museum_trigger_table, *(int *)vars) != 0) {
            *(unsigned char *)g_museum_trigger_flag = 1;
        } else {
            *(unsigned char *)g_museum_trigger_flag = 0;
            func_320FD0(obj, 1, -1);
        }
        break;
    }
}

/* func_L30_003844C8 is in L30_003844C8-g8.c. */

/* Walks the context's 27-word handle table and adopts the first live one the shared probe
   accepts, stamping its index at +0x144 and the handle at +0x140; -1 when none is live. */
/* Looks through the object's list of entries for the first one that is still active and remembers it. */
int museum_find_active_exhibit_entry(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    int i;

    for (i = 0; i < 27; i++) {
        int handle = *(int *)(vars + i * 4);

        if (handle != -1 && IsPointInCuboid(g_hero_position, handle) != 0) {
            *(int *)(vars + 0x140) = *(int *)(vars + i * 4);
            *(int *)(vars + 0x144) = i;
            return *(int *)(vars + i * 4);
        }
    }
    return -1;
}

/* Draws the currently picked entry on the screen with a fixed color. */
void museum_draw_selected_exhibit_entry(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    Vec6 buf;
    int model;

    g_hero_state.mode = 5;
    g_hero_state.flag = 1;
    buf = *(Vec6 *)g_museum_entry_vec;
    model = func_2FB3C8(*(int *)(g_museum_exhibit_models + *(int *)(vars + 0x144) * 4));
    func_3132D8(&buf, 0x80F0F0F0, model, 1, 0, -1, 0, 0, 0, 0);
}


/* Starts the countdown for the picked entry if nothing else is running; returns 1 if it did, 0 if not. */
int museum_start_exhibit_entry_timer(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    char *game_state = (char *)g_music_state;
    int idx;

    if (*(int *)(game_state + 0x68) == 0 && *(int *)(game_state + 0x24) == -1) {
        char *entry;

        idx = *(int *)(vars + 0x144);
        if (idx != -1) {
            entry = vars + idx * 4;
            *(int *)(game_state + 0x24) = (*(int *)(entry + 0x70) & 0x3FFF) + 0xBB8;
            *(int *)(game_state + 0x28) = 0;
            return 1;
        }
    }
    return 0;
}

/* func_L30_00386300 lives in the -g8 sibling: it reaches its globals through $gp. */

/* Moves a thrown object for one frame and checks what it hits. It bounces off surfaces and sprays sparks when it lands. */
void projectile_step_thrown_sparks(unsigned char *obj) {
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
        ((Material *)((u32)g_item_l30_material_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
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
            RippleDisturb(g_ripple_pos_x, g_ripple_pos_y, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            vec_clear_128(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = g_collision_l30_result.point.f[2];
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
            Collision *collision = &g_collision_l30_result;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &g_collision_l30_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_thrown_l30_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
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


/* Moves a thrown object for one frame and bounces it off whatever it hits; after many bounces it ends in a different way. */
void projectile_step_thrown(char *obj) {
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
    frame.packet.material = (g_bouncing_weapon_index + g_item_l30_material_table)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_collision_l30_result;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &g_collision_l30_result;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_thrown_l30_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
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
            collision = &g_collision_l30_result;
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




/* Reads the player's stick and button input into four numbers, keeping the stick values between -1 and 1. */
void hover_read_inputs_basic(float *stick_x, float *stick_y, float *stick_z, float *button) {
    *stick_x = -g_hero_state.f1FB0;
    *stick_z = -g_hero_state.f1FB4;
    *stick_y = func_321018(g_pad_state.f128) - func_321018(g_pad_state.f124);
    *button = g_pad_state.f12C;
    if (*stick_x > 1.0f) {
        *stick_x = 1.0f;
    } else if (*stick_x < -1.0f) {
        *stick_x = -1.0f;
    }
    if (*stick_y > 1.0f) {
        *stick_y = 1.0f;
    } else if (*stick_y < -1.0f) {
        *stick_y = -1.0f;
    }
}

/* func_L30_003B3F70 uses small data in L30_003B3F70-g8.c. */

/* func_L30_003BE478 uses small data in L30_0032AAF0-g8.c. */

/* Moves a museum info stand to its next state and plays the matching animation and sound. */
void museum_info_stand_advance_state(char *obj) {
    char *vars = *(char **)(obj + 0x68);

    if (*(unsigned char *)(obj + 0x20) == 1) {
        if (*(unsigned char *)(obj + 0x43) != 1) {
            anim_start_blended(obj, 1, 0, 5);
        }
        *(unsigned char *)(obj + 0x20) = 2;
    } else {
        if (*(unsigned char *)(obj + 0x43) != 2) {
            anim_start_blended(obj, 2, 0, 5);
        }
        *(unsigned char *)(obj + 0x20) = 5;
        if (*(int *)(vars + 0xC) != -1) {
            cam_reset_entry(*(int *)(vars + 0xC));
        }
    }
}



/* func_L30_003D9E60 is defined in L30_003D9E60-g8.c. */

/* func_L30_003DA040 is matched in its own unit, src/levels/shared/L30_003DA040-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* func_L30_003E1BA0 is defined in L30_003E1BA0-g8.c. */

/* func_L30_003E1E78 uses small data in L30_003E1E78-g8.c. */

/* func_L30_00404608 needs the -g8 sibling too; its C is in nonmatching/levels/. */


/* func_L30_0040AE38 is defined in L30_0040AE38-g8.c. */

extern int g_current_map_index MACRO_ADDR;

/* Reads the player's controls for the hover vehicle into six numbers, keeping the stick values between -1 and 1. */
void hover_read_inputs_full(float *stick_x, float *stick_y, float *stick_z, float *button_a, float *strafe, float *button_b) {
    int mode;

    *stick_x = -g_hero_state.f1FB0;
    *stick_z = -g_hero_state.f1FB4;
    *stick_y = func_321018(g_pad_state.f128) - func_321018(g_pad_state.f124);
    mode = g_current_map_index;
    if (mode == 8 || mode == 0x10 || mode == 0x15 || mode == 0x1E) {
        *button_a = g_pad_state.f12C;
        *button_b = 0.0f;
    } else {
        *button_b = g_pad_state.f12C;
        *button_a = 0.0f;
    }
    *strafe = func_321018(g_pad_state.f138) - func_321018(g_pad_state.f13C);
    if (*stick_x > 1.0f) {
        *stick_x = 1.0f;
    } else if (*stick_x < -1.0f) {
        *stick_x = -1.0f;
    }
    if (*stick_y > 1.0f) {
        *stick_y = 1.0f;
    } else if (*stick_y < -1.0f) {
        *stick_y = -1.0f;
    }
    if (*strafe > 1.0f) {
        *strafe = 1.0f;
    } else if (*strafe < -1.0f) {
        *strafe = -1.0f;
    }
}


/* func_L30_0040B9D8 is defined in L30_0040B9D8-g8.c. */

/* func_L30_0040C270 is defined in L30_0040C270-g8.c. */
