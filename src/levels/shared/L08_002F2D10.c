#include "include_asm.h"
#include "common.h"

typedef u64 TI128 __attribute__((mode(TI)));

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern u8 *g_hero_moby;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int ref_L08_0039DBE8_00 __attribute__((sda));
extern int ref_L08_0039DBE8_01 __attribute__((sda)), ref_L08_0039DBE8_02 __attribute__((sda));
extern Collision ref_L08_0039DBE8_03;
extern Material ref_L08_0039DBE8_04[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void ref_L08_0039DBE8_06(void *);
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
extern void part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void ref_L08_0039DBE8_05(void *, void *, void *);
extern void FastVecAdd(char *, char *, char *);

typedef int Quad_L08_003B2DB0 __attribute__((mode(TI)));

typedef struct {
    float dir[4];                 /* 0x00 */
    float f10;                    /* 0x10 */
    int f14;                      /* 0x14 */
    int owner;                    /* 0x18 */
    short h1C, h1E;               /* 0x1C */
    float f20;                    /* 0x20 */
    int f24, f28;                 /* 0x24 */
} Bolt_L08_003B2DB0;
typedef struct {
    char pad0[0x10];
    float pos[4];                 /* 0x10 */
    char pad20[0x23 - 0x20];
    u8 b23;                       /* 0x23 */
    char pad24[0x2C - 0x24];
    float scale;                  /* 0x2C */
    u8 b30, b31;                  /* 0x30 */
    short h32;                    /* 0x32 */
    u16 h34;                      /* 0x34 */
    char pad36[0x68 - 0x36];
    Bolt_L08_003B2DB0 *state;     /* 0x68 */
    char pad6C[0xF0 - 0x6C];
    int fF0;                      /* 0xF0 */
    float fF4, fF8;               /* 0xF4 */
} Moby_L08_003B2DB0;

extern char g_hero_position[];
extern Moby_L08_003B2DB0 *CreateMoby(int);
extern float fast_vec_dist(void *, void *);
extern void *SpawnJointFollowParticle(void *, float, int, int, int);
extern void func_002A0F48(void *);


extern f32 D_L08_001BE0B0;
extern void UpdateViewContext();

extern int r1_D_0015F564_002F2D10 MACRO_ADDR;

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002F2D10)(void *);

extern DrawCallback_r002F2D10 r1_D_0018DC40_002F2D10[];

extern void *r1_D_0018DD40_002F2D10[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
/* Adds a drawing callback and its argument to a list of up to 64 pending draw jobs. */
void gfx_queue_draw_callback(DrawCallback_r002F2D10 fn, void *arg) {
    int count = r1_D_0015F564_002F2D10;
    if (count < 0x40) {
        r1_D_0018DC40_002F2D10[count] = fn;
        r1_D_0018DD40_002F2D10[count] = arg;
        r1_D_0015F564_002F2D10 = count + 1;
    }
}

extern int text_run_helper_first_set(u8 *, int, float);
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L08_00296CD0[];

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_0027F640 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void DrawCenteredScaledText(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (text_run_helper_first_set(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(1);
    FontPrintScaled(fx, fy, color, text, length, scale, texture, D_L08_00296CD0);
}

/* Sets the saved float to 0.62 and runs the update that uses it. */
void hero_set_saved_float_and_update(void) {
    D_L08_001BE0B0 = 0.62f;
    UpdateViewContext();
}

extern void LoadPackSingleTexture();
extern void gfx_send_gs_register_packet();
extern void load_copy_header_relocate_pointers();
extern u8 D_L08_001DB5E7;
extern s32 D_L08_001DAC40[];
extern s32 D_L08_001BFEF4;

/* Runs three screen-related update steps in a row for the same value. */
void gfx_run_screen_update_steps(s32 value) {
    LoadPackSingleTexture(value);
    gfx_send_gs_register_packet(value);
    load_copy_header_relocate_pointers(D_L08_001DAC40[D_L08_001DB5E7], D_L08_001BFEF4);
}

/* Raises a number to a whole-number power (at least 1). */
f32 IntegerPower(s32 power, f32 base) {
    f32 result;
    if (power < 2)
        return base;
    result = base;
    while (power >= 2) {
        power--;
        result = result * base;
    }
    return result;
}

extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));

/* Counts the 0x100-byte records between the two pointers whose halfword at +0xAA equals A0
   and whose byte at +0x20 is neither 0xFE nor 0xFD. */
s32 moby_count_of_class(s32 classId) {
    u8 *moby = D_L08_001B29DC;
    s32 count = 0;

    for (; moby < D_L08_001B29E0; moby += 0x100) {
        if (moby != 0 && *(s16 *)(moby + 0xAA) == classId) {
            if (*(u8 *)(moby + 0x20) != 0xFE) {
                if (*(u8 *)(moby + 0x20) != 0xFD)
                    count++;
            }
        }
    }
    return count;
}

/* Switches three flags of one record; -1 leaves a group alone, 0 clears it and anything
   else sets it. */
void moby_set_visibility_flags(void *moby_arg, s32 hide_mode, s32 active_mode, s32 collision_mode) {
    u8 *moby = moby_arg;
    u8 kind;

    if (moby == 0)
        return;
    kind = *(u8 *)(moby + 0x20);
    if (kind == 0xFE)
        return;
    if (kind == 0xFD)
        return;
    if (hide_mode != -1) {
        if (hide_mode != 0)
            *(u16 *)(moby + 0x34) &= 0xFFFD;
        else
            *(u16 *)(moby + 0x34) |= 2;
    }
    if (active_mode != -1) {
        if (active_mode != 0) {
            *(u8 *)(moby + 0x31) = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
        } else {
            *(u8 *)(moby + 0x31) = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
    }
    if (collision_mode != -1) {
        if (collision_mode != 0)
            *(s32 *)(moby + 0x98) = *(s32 *)(*(s32 *)(moby + 0x24) + 0x10);
        else
            *(s32 *)(moby + 0x98) = 0;
    }
}

extern u8 *D_L08_001B29DC __attribute__((sda));
extern void moby_set_visibility_flags(void *, s32, s32, s32);

/* Changes the flags of the object with the given index in the object list; does nothing for -1. */
void moby_set_flags_by_index(s32 index, s32 hide_mode, s32 active_mode, s32 collision_mode) {
    if (index == -1)
        return;
    moby_set_visibility_flags(D_L08_001B29DC + (index << 8), hide_mode, active_mode, collision_mode);
}

/* Runs func_L08_00328B80 on every object named by entry a0 of the 0x1FB660 table: a u16
   list whose low 15 bits select the object and whose high bit ends the walk. The list
   pointer is read under two names (the guard keeps the fresh load, the walk needs a
   callee-saved register across the call). */
extern u32 D_L08_001FB660[];

void moby_set_group_flags(s32 group_index, s32 hide_mode, s32 active_mode, s32 collision_mode) {
    u16 *list = (u16 *)D_L08_001FB660[group_index];

    if (list != 0) {
        u16 *entry = list;
        do {
            moby_set_flags_by_index(entry[0] & 0x7FFF, hide_mode, active_mode, collision_mode);
        } while (*(s16 *)entry++ >= 0);
    }
}

extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(void *);

/* Splits a four-float vector: two components give an angle, 0x45AFDF66 marks an
   already-resolved vector. */
void vec_resolve_direction(u8 *input, f32 *out_angle, f32 *out_scale_a, f32 *out_scale_b) {
    f32 vec[4];

    *(TI128 *)vec = *(TI128 *)input;
    if (vec[3] != 5627.9248046875f) {
        *out_angle = mat_fast_helper_a(vec[0], vec[1]);
        return;
    }
    *out_angle = mat_fast_helper_a(vec[0], vec[1]);
    *out_scale_a = *out_scale_a * vec_length_xy(vec);
    vec[3] = 0;
    *out_scale_b = *out_scale_b * vec[2];
}

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int moby_get_private_value_0(void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void anim_start_blended(void *, int, int, int);
struct LaunchState {
    float direction[4];
    char gap10[8];
    float radius, height;
    char gap20[4];
    unsigned int flags;
    char gap28[4];
    short lifetime;
    char gap2e[14];
    unsigned char active;
    char gap3d;
    short delay;
    float heading;
    int age;
};

/* Sets up a launched object: places it on a circle around its owner, starts its timer and plays the launch animation. */
void moby_init_launched_object(unsigned char *moby, struct LaunchState *launch, int animation, int flags, int frames, float angle)
{
    int effect;
    int active;
    launch->direction[0] = math_fast_sin_or_cos_a(angle) * launch->radius;
    launch->direction[1] = math_fast_sin_or_cos_b(angle) * launch->radius;
    launch->direction[2] = launch->height;
    launch->direction[3] = 1.0f;
    {
        float heading = FastAddRotations(angle, 3.141593f);
        short lifetime = 300;
        active = 1;
        launch->age = 0;
        launch->delay = 0;
        launch->heading = heading;
        launch->lifetime = lifetime;
        launch->active = active;
    }
    effect = moby_get_private_value_0(moby);
    if (effect && *(float *)effect == 0.0f) {
        launch->flags |= 0x20;
        *(int *)(moby + 0x98) = 0;
    }
    if (launch->flags & 2)
        anim_start_blended_with_flags(moby, animation, frames, flags, active);
    else
        anim_start_blended(moby, animation, frames, flags);
}

/* Fills a sound/effect record with the owner object, its position and two speeds. Returns -1 if the owner has no usable data. */
s32 part_fill_effect_record(u8 *owner, s32 value_a, s32 value_b, u8 *out, f32 speed_a, f32 speed_b) {
    u8 *definition;
    if (owner == 0)
        return -1;
    definition = *(u8 **)(owner + 0x24);
    if (definition == 0)
        return -1;
    if (*(s32 *)(definition + 0x28) == 0)
        return -1;
    *(u32 *)(out + 0x1C) = (u32)owner;
    *(f32 *)(out + 0x14) = speed_b * 0.016666668f;
    *(f32 *)(out + 0x10) = speed_a * 0.016666668f;
    *(TI128 *)out = *(TI128 *)(owner + 0x10);
    *(s32 *)(out + 0x18) = value_b;
    *(s32 *)(out + 0x20) = value_a;
    return 1;
}

/* func_L08_00339220 lives in L08_002F2D10-g.c. */

extern void text_expand_number_template(s32, s32, void *);

/* The float varargs entry: 2.95.3 spills $a2-$a3, $t0-$t3 (eight bytes each)
   and $f12-$f18; the work is done by the shared worker on that save area. */
/* Takes a variable argument list (including floats) and hands it to the shared worker function. */
void thread_call_var_args_worker(s32 first, s32 second, ...) {
    text_expand_number_template(first, second, (char *)__builtin_next_arg(second) - 0x30);
}



/* func_L08_00363320 is in L08_00363320-g8.c. */



/* func_L08_00389B68 is in L08_00389B68-narrowsave.c. */

/* Moves a thrown projectile each frame, checks what it hits, and bounces it or sets it off. */
void thrown_l08_projectile_update(unsigned char *moby) {
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
    int sparks_left, lifetime;
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
    ref_L08_0039DBE8_06(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)ref_L08_0039DBE8_04 + g_item_slot_to_record[12] * sizeof(Material)))->material;
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
            RippleDisturb(ref_L08_0039DBE8_01, ref_L08_0039DBE8_02, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = ref_L08_0039DBE8_03.point.f[2];
            effect = moby_spawn_scaled_effect(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            sparks_left = 15;
            do {
                --sparks_left;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.050000004f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.050000004f, 0.10833334f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2(&frame.position, spread, math_random_int_below(2), lifetime);
            } while (sparks_left >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &ref_L08_0039DBE8_03;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &ref_L08_0039DBE8_03;
                model = reread->hit;
                if (*(int *)(model + 0x64) == ref_L08_0039DBE8_00 && *(short *)(model + 0xAA) != 0x336)
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
        ref_L08_0039DBE8_05(moby, &frame.velocity, &frame.normal);
    }
}


extern unsigned char D_00139574;
extern Material ref_L08_0039E000_00[];
extern Collision ref_L08_0039E000_01;
extern int ref_L08_0039E000_02 __attribute__((sda));
extern void ref_L08_0039E000_03(void *);
extern void ref_L08_0039E000_04(void *, void *, void *);
extern void ref_L08_0039E000_05(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecScale(void *, void *, float);

/* Moves a thrown projectile each frame like the one above, but counts its bounces and changes its result after 20. */
void bouncing_l08_projectile_update(char *moby) {
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
    ref_L08_0039E000_03(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + ref_L08_0039E000_00)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &ref_L08_0039E000_01;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &ref_L08_0039E000_01;
            model = reread->hit;
            if (*(int *)(model + 0x64) == ref_L08_0039E000_02 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &ref_L08_0039E000_01;
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
            ref_L08_0039E000_04(moby, &frame.velocity, &frame.normal);
        else
            ref_L08_0039E000_05(moby, &frame.velocity, &frame.normal);
    }
}



Moby_L08_003B2DB0 *SpawnDirectedEffectObject(int owner, float *pos, float *dir, int life)
{
    float pos_copy[4] __attribute__((aligned(16)));
    float dir_copy[4] __attribute__((aligned(16)));
    Moby_L08_003B2DB0 *moby;
    Bolt_L08_003B2DB0 *state;
    int life_ticks;
    float *pos_ptr = pos_copy;
    float *dir_ptr = dir_copy;

    *(Quad_L08_003B2DB0 *)pos_copy = *(Quad_L08_003B2DB0 *)pos;
    *(Quad_L08_003B2DB0 *)dir_copy = *(Quad_L08_003B2DB0 *)dir;
    moby = CreateMoby(0x4EA /* moby class 1258 */);
    if (moby) {
        state = moby->state;
        state->owner = owner;
        moby->fF0 = 0;
        moby->scale *= 4.0f;
        moby->b30 = 0xFF;
        moby->h32 = 0xFF;
        moby->b31 = 1;
        moby->fF4 = -mat_fast_helper_a(vec_length_xy(dir_ptr), dir_ptr[2]);
        moby->fF8 = mat_fast_helper_a(dir_copy[0], dir_ptr[1]);
        qcopy(moby->pos, pos_ptr);
        qcopy(state->dir, dir_ptr);
        state->f10 = math_random_float_range(-0.02617994323372841f, 0.02617994323372841f);
        state->f14 = 0;
        state->h1C = life;
        state->h1E = life;
        state->f20 = fast_vec_dist(moby->pos, g_hero_position);
        state->f24 = 0;
        state->f28 = 0;
        life_ticks = life * 5 / 4;
        moby->h34 |= 0x200;
        moby->b23 = 0x40;
        SpawnJointFollowParticle(moby, 400000.0f, 0x2F7F4F4F, life_ticks, -1);
        SpawnJointFollowParticle(moby, 160000.0f, 0x4F7F7F7F, life_ticks, -1);
        func_002A0F48(moby);
    }
    return moby;
}

typedef struct {
    Vec vector;
    void *object;
    int flags;
    u8 enabled, kind;
    u16 group;
    float radius;
    int active;
} CollisionInput;
extern Vec ref_L08_003B2F70_00, ref_L08_003B2F70_01, ref_L08_003B2F70_02;
extern int PlayMobySound(int, int, void *);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int FastDecTimer(short *);
extern void moby_mark_spawned(void *);
extern float FastVecLength(void *);
extern u8 *part_spawn_velocity_particle(void *, void *, int, int, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void coll_process_hit(void *, float, int, void *, void *);
/* Updates a flying bolt effect moby: moves it, plays a near-miss sound, and bursts into sparks when it hits something. */
void bolt_effect_update(char *moby) {
    struct { Vec old; CollisionInput collision; Vec velocity, random; } frame;
    CollisionInput *input;
    Bolt_L08_003B2DB0 *state = *(Bolt_L08_003B2DB0 **)(moby + 0x68);
    float distance = fast_vec_dist(moby + 0x10, g_hero_position);
    qcopy(&frame.old, moby + 0x10);
    FastVecAdd(moby + 0x10, moby + 0x10, (char *)state);
    if (!state->f28 && state->f24 && state->f20 < distance && distance < 3.0f) {
        PlayMobySound(0, 0, moby);
        state->f28 = 1;
    }
    if (distance < state->f20) state->f24 = 1;
    state->f20 = distance;
    if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
        *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
        *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f ||
        vec_distance_xy(moby + 0x10, &ref_L08_003B2F70_00) > 255.0f) goto destroy;
    input = 0;
    if (!*(u8 *)(moby + 0xBC)) {
        frame.collision.flags = 0x70001;
        frame.collision.radius = 3.0f;
        frame.collision.object = moby;
        frame.collision.active = 1;
        qcopy(&frame.collision.vector, state);
        FastVecSub(&frame.collision.vector, moby + 0x10, g_hero_position);
        vec_fast_normalize_helper(&frame.collision.vector, &frame.collision.vector, 1.0f);
        input = &frame.collision;
        frame.collision.vector.f[2] = 1.0f;
        frame.collision.vector.f[3] = 5627.9248046875f;
        frame.collision.enabled = 1;
        frame.collision.kind = 3;
        frame.collision.group = *(u16 *)(moby + 0xAA);
    }
    if (FastDecTimer(&state->h1C) && !*(u8 *)(moby + 0xBC)) {
        *(u8 *)(moby + 0xBC) = 1;
        state->h1C = state->h1E / 4;
    } else if (state->h1C <= 0 && *(u8 *)(moby + 0xBC)) {
destroy:
        moby_mark_spawned(moby);
        return;
    }
    if (!CollLine(&frame.old, moby + 0x10, 0, (void *)state->owner, input)) return;
    qcopy(moby + 0x10, &ref_L08_003B2F70_01);
    if (!*(u8 *)(moby + 0xBC)) {
        int spark_index;
        for (spark_index = 0; spark_index < 5; spark_index++) {
            frame.random.q = 0;
            frame.random.f[0] = math_random_float_range(-1.0f, 1.0f);
            frame.random.f[1] = math_random_float_range(-1.0f, 1.0f);
            frame.random.f[2] = math_random_float_range(-1.0f, 1.0f);
            frame.velocity.q = frame.random.q;
            vec_fast_normalize(&frame.random, state, &ref_L08_003B2F70_02);
            vec_scale_to_length(&frame.velocity, &frame.velocity, FastVecLength(&frame.random) * 0.5f);
            FastVecAdd((char *)&frame.velocity, (char *)&frame.random, (char *)&frame.velocity);
            vec_scale_to_length(&frame.velocity, &frame.velocity, math_random_float_range(0.05000000447034836f, 0.10000000894069672f));
            part_spawn_velocity_particle(moby + 0x10, &frame.velocity, 0x7F2F4F6F, math_random_int_range(10, 15), 60000.0f);
        }
    }
    SpawnExplosionEffects(moby, state, 0, 0.0f, 0.0f, 4, 3, 6, 1.1f, 0.6f, 1.0f, 0.9f, -1, 0.0f,
        0, 1, -1, 0, 0x810001);
    coll_process_hit(moby + 0x10, 1.1f, 16, moby, input);
    moby_mark_spawned(moby);
}

/* Defined in L08_003C5940-g8.c. */

/* Defined in L08_003C63F0-g8.c. */


extern void moby_transform_joint_to_world(void *, int, void *);
extern void *part_spawn_owned_effect(void *, void *);
extern float IntToFloat(int);

/* Keeps a child object at points 7 and 8 of obj: spawns a missing one,
 * otherwise moves it there and copies the parent's orientation. */
void UpdateAttachedChildObjects(char *moby) {
    float point[4] __attribute__((aligned(16)));
    char **slot = (char **)(*(char **)(moby + 0x68) + 0x80);
    char *child = 0;
    int index;
    for (index = 0; index < 2; ++index, ++slot) {
        moby_transform_joint_to_world(moby, index + 7, point);
        if (*slot == 0) {
            *slot = part_spawn_owned_effect(moby, point);
        } else {
            child = *slot;
            qcopy(child + 0x10, point);
            *(float *)(child + 0xF8) = *(float *)(moby + 0xF8);
            *(float *)(child + 0xF4) = *(float *)(moby + 0xF4);
            *(float *)(child + 0xF0) = IntToFloat(index) * 3.1415927410125732f;
        }
    }
}

/* func_L08_003C67B8 lives in L08_002F2D10-emit-g8.c. */

/* func_L08_003C6AB0 is in L08_003C6AB0-g8.c. */



/* func_L08_003CD488 lives in the -g8 sibling file (it reads the level's scalars
   through $gp). */

extern u8 *g_hero_moby;
extern void func_002A0F48();

/* func_L08_003CD600 and func_L08_003CD6C8 are matched in L08_003CD600-qcopy.c. */

/* Defined in L08_003CD648.c. */





