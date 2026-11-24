#include "include_asm.h"
#include "names.h"

extern int math_random_int_below(int mode);

extern float coll_get_ground_height_at_position(char *object, char *local);

extern void func_00282D30_7(char *local, int value, float scale);

extern float func_002A7878_1(float low, float high);

extern void *part_spawn_bubble(char *object, char *local, float amount, float base);

extern char *func_0029EFD0_1(int);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern void part_draw_spinning_billboard_pair(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_002FDBD8_1(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

typedef int TI128 __attribute__((mode(TI)));

extern int D_18C0A0;

extern int D_18C0B4;

extern int g_hero_ledge_move_flag;

extern void anim_start_blended(char *object, int mode, int a2, int a3);

extern void table_clear_entry_flag(int value);

extern void vec_clear_128(char *quad);

extern void func_002A10E8(char *object);

extern void func_002A0F48(char *object);

extern void cam_pick_state_from_hero_turn(int value);

extern int hero_l00_set_move_state(int a, int b);

extern void level_clear_second_table_entry(void);

extern void level_restore_lighting(char *object, int mode);

/* Level state saved by func_L00_00390E10 and restored by func_L00_00390F28. */
typedef struct {
    char pad0[0x30];
    float f30;
    float f34;
    float f38;
    float f3C;
    unsigned char b40;
    unsigned char b41;
    unsigned char b42;
} LevelSavedState_390E10;

extern int g_lighting_saved_flag __attribute__((section(".sdata")));
extern float g_fog_near __attribute__((section(".sdata")));
extern float g_fog_far __attribute__((section(".sdata")));
extern float g_fog_near_intensity __attribute__((section(".sdata")));
extern float g_fog_far_intensity __attribute__((section(".sdata")));
extern unsigned char g_fog_color_r __attribute__((section(".sdata")));
extern unsigned char g_fog_color_g __attribute__((section(".sdata")));
extern unsigned char g_fog_color_b __attribute__((section(".sdata")));
extern float g_light_far_param __attribute__((section(".sdata")));
extern float g_light_falloff_param __attribute__((section(".sdata")));
extern int g_light_scale_first __attribute__((section(".sdata")));
extern int g_light_distance_param __attribute__((section(".sdata")));
extern int g_light_scale_second __attribute__((section(".sdata")));
extern void SetBackgroundColor(int, int, int);

typedef unsigned char u8;

typedef float f32;

/* Prototype775 is a research label. Field names below describe only the
 * independently observed byte23 and binary32 word2C operations. */
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;

extern void moby_mark_spawned(NativeUpdate775View *object);

typedef struct {
    char prefix[0x760];
    float aimAxis[4];
    char pad770[0xAC0];
    unsigned int buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1050];
    int level;
    char pad2298[0x24];
    unsigned char busy;
    char pad22BD[0x277];
    int cooldown;
} LaunchHero;
extern LaunchHero g_hero_state;
extern unsigned int g_pad_pressed_flags;
extern void moby_transform_joint_to_world(char *, int, char *);
/* Interleaved declarations preserve the EE ABI's independent GPR and FP argument order. */
extern void CalculateAimedLaunchVelocity(void *, void *, void *, float, float, float, float, void *);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, void *, int, int, float);
extern int math_fast_float_d(int *), weapon_spend_ammo(int, int);
extern void cancel_hero_item_animation(void), start_equipped_item_animation(void);
extern int PlayMobySound(int, int, char *);
extern char *decoy_create_projectile(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void decoy_glove_draw_projectile(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

typedef struct { float value[3]; } QuerySettings;
extern QuerySettings g_fin_query_settings;
typedef struct { char prefix[0x1A0]; unsigned int held, pressed; } LaunchInput;
extern LaunchInput g_pad_state;
extern char *SelectBestTargetInCone(void *, void *, int *, void *, int, int, float, float, float, float, float, int, void *);
extern char *part_l00_spawn_spinning_debris(char *, char *);
extern void ref_L00_00397E60_00(void *, void *);
extern void bomb_glove_draw_projectile(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0038F178 is defined in L00_0038F178-effects.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Spawns a small puff of sparks at the object, unless the random check says to skip it. */
void part_spawn_spark_puff(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (math_random_int_below(5))
        return;
    base = coll_get_ground_height_at_position(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    part_spawn_bubble(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors g_spark_particle_colors;
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int gfx_swap_packed_color_channels(int, int);
extern char *part_spawn_scaling(void *, void *, int, int, int, int, int, int);
extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_mix_on_inner_data(void *, void *, void *, float);
extern float IntToFloat(int);
extern int FastDecTimer(short *);

/* Per-frame update of a drifting spark particle: sheds colored sparks, slows down, and removes itself when it fades or leaves the map. */
void spark_particle_update(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (math_random_int_below(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = g_spark_particle_colors;
        random.quad = 0;
        random.f[0] = math_random_float_range(-1.0f, 1.0f);
        random.f[1] = math_random_float_range(-1.0f, 1.0f);
        random.f[2] = math_random_float_range(-1.0f, 1.0f);
        direction.quad = random.quad;
        vec_scale_to_length(&direction, &direction, 1.0f / 60.0f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = gfx_swap_packed_color_channels(colors.color[math_random_int_below(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            part_spawn_scaling(object + 0x10, &direction, color,
                         gfx_swap_packed_color_channels(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         45, 50, 120, 1);
        } else {
            part_spawn_scaling(object + 0x10, &direction, colors.color[math_random_int_below(4)],
                         0x4FFF, 45, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    FastVecAdd(object + 0x10, object + 0x10, state);
    moby_mix_on_inner_data(object, state, state, 0.0040555559f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        moby_mark_spawned((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = IntToFloat(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  IntToFloat(*(short *)(state + 0x1A) / 4);
    }
    if (FastDecTimer((short *)(state + 0x18)))
        moby_mark_spawned((NativeUpdate775View *)object);
}

/* func_L00_0038F8B8 is defined in L00_0038F8B8.c. */

/* func_L00_0038FC48 is defined in L00_0038FC48-g8.c. */


/* Calls a callee with the constant 167 and, when it returns a non-zero object, stores the argument pointer at +4 of the object held at +104, clears the words at +0, +8 and +12 of that object, sets byte +48 to 255, the halfword at +50 to 126 and bytes +49 and +32 to 0, then returns the object. */
char *tether_create_holder(char *owner)
{
    char *object = func_0029EFD0_1(167 /* moby class 167 */);
    int *vars;

    if (object != 0) {
        vars = *(int **)(object + 104);
        vars[1] = (int)owner;
        vars[0] = 0;
        vars[2] = 0;
        vars[3] = 0;
        *(unsigned char *)(object + 48) = 255;
        *(short *)(object + 50) = 126;
        object[49] = 0;
        object[32] = 0;
    }
    return object;
}

/* Saves the current lighting and fog settings into the object, then switches the level to a dim, close-range look. */
void level_save_and_dim_lighting(char *object)
{
    LevelSavedState_390E10 *st = *(LevelSavedState_390E10 **)(object + 0x68);
    float f30 = g_fog_near;
    float f34 = g_fog_far;
    float f38 = g_fog_near_intensity;
    float f3C = g_fog_far_intensity;

    g_lighting_saved_flag = 1;
    st->f30 = f30;
    st->f34 = f34;
    st->f38 = f38;
    st->f3C = f3C;
    st->b40 = g_fog_color_r;
    st->b41 = g_fog_color_g;
    st->b42 = g_fog_color_b;
    g_fog_color_r = 0x40;
    g_fog_color_g = 0x60;
    g_fog_color_b = 0x40;
    g_fog_near = 0.0f;
    g_fog_far = 131072.0f;
    g_fog_near_intensity = 255.0f;
    g_light_far_param = 147456.0f;
    g_light_falloff_param = 144.0f;
    g_light_scale_second = 144;
    g_light_scale_first = 144;
    g_light_distance_param = 0x50000;
    g_fog_far_intensity = 0.0f;
    SetBackgroundColor(g_fog_color_r, g_fog_color_g, g_fog_color_b);
}



/* Releases the second argument's object: clears a word of the sub-object at +0x68, clears
 * two globals, hands its +0x14 word over before clearing it, then runs five helpers and the
 * first argument through one more. */
void tether_release(char *actor, char *tether)
{
    char *tetherRef = tether;
    char *actorRef = actor;
    int *vars = *(int **)tetherRef;

    vars = (int *)*(int *)((char *)vars + 0x68);
    if (vars != 0)
        vars[1] = 0;
    D_18C0A0 = 0;
    cam_pick_state_from_hero_turn(*(int *)(tetherRef + 0x14));
    *(int *)(tetherRef + 0x14) = 0;
    hero_l00_set_move_state(0, 1);
    level_restore_lighting(actorRef, 1);
    level_clear_second_table_entry();
    table_clear_entry_flag(*(int *)(tetherRef + 0x4C));
    moby_mark_spawned((NativeUpdate775View *)actorRef);
    g_hero_ledge_move_flag = 0;
}





/* Gates on the sub-object's tag byte, mirrors one status bit from that object into its own
 * halfword, clamps the wrapped value at +4 against a signed window and finishes with the
 * three transform helpers; original game role is unknown. */
extern int g_tether_fin_counter;

extern void func_310440(char *object);

extern void func_310838(char *object, int mode, int delta);

extern float func_31A7C0(float low, float high);

extern float func_31F1C8(float angle);

extern float func_2EF0F8(float value, float amount);

extern void func_312D18(char *object);

void tether_fin_piece_update(char *object)
{
    char *vars = *(char **)(object + 0x68);
    char *other = *(char **)(vars + 8);
    unsigned char tag = *(unsigned char *)(other + 0x20);

    if (tag == 0 || (tag & 0xF0) == 0xF0) {
        func_310440(object);
        return;
    }
    if (other != 0) {
        if ((*(unsigned short *)(object + 0x34) & 1) != (*(unsigned short *)(other + 0x34) & 1)) {
            unsigned short bits = *(unsigned short *)(object + 0x34) & 0xFFFE;

            *(unsigned short *)(object + 0x34) = bits;
            bits |= *(unsigned short *)(*(char **)(vars + 8) + 0x34) & 1;
            *(unsigned short *)(object + 0x34) = bits;
        }
    }
    if (g_tether_fin_counter < 0x19)
        *(unsigned short *)(object + 0x34) |= 0x41;
    {
        int current = *(int *)(vars + 4);
        int next = current - 0xC0;
        int delta = -0xC0;

        *(int *)(vars + 4) = next;
        if (next >= 0x1001) {
            delta = -0x10C0;
            *(int *)(vars + 4) = current - 0x10C0;
        } else if (next < 0) {
            delta = 0xF40;
            *(int *)(vars + 4) = current + 0xF40;
        }
        func_310838(*(char **)(object + 0x24), 0, delta);
    }
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24)
                                * *(float *)(vars + 0xC) * func_31A7C0(0.5f, 1.0f);
    *(float *)(object + 0xF4) = func_2EF0F8(*(float *)(object + 0xF4),
                                             func_31F1C8(*(float *)(vars + 0xC)));
    func_312D18(object);
}

/* Builds the object for type 0xB3 and, when the constructor returns one, fills its fields,
 * clears a quad at +0xF0, records the argument in the sub-object at +0x68 and copies three
 * quads from the argument before running two helpers. Returns the object. */
char *tether_create_fin_piece(char *source)
{
    char *p = source;
    char *object = func_0029EFD0_1(0xB3 /* moby class 179 */);

    if (object != 0) {
        int *vars = *(int **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) = 0x204;
        *(unsigned char *)(object + 0x23) = 0x50;
        *(char *)(object + 0x20) = 0;
        vars[2] = (int)p;
        vec_clear_128(object + 0xF0);
        *(TI128 *)(object + 0xC0) = *(TI128 *)(p + 0xC0);
        *(TI128 *)(object + 0xD0) = *(TI128 *)(p + 0xD0);
        *(TI128 *)(object + 0xE0) = *(TI128 *)(p + 0xE0);
        func_002A10E8(object);
        func_002A0F48(object);
    }
    return object;
}

/* func_L00_003959C0 is defined in L00_003959C0-g8.c. */

/* func_L00_00395A88 is defined in L00_00395A88-g8.c. */

/* func_L00_00396078 is defined in L00_00396078-g64.c. */


/* func_L00_003973E8 is defined in L00_003973E8-g8.c. */

/* Selects an aim target before advancing the projectile launcher state. */
/* Per-frame update of the Bomb Glove moby. */
void UpdateAimedProjectileLauncher(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16];
    QuerySettings settings;
    char direction[16];
    int foundCount;
    char *target;
    int ready;
    moby_transform_joint_to_world(actor, 0, position);
    settings = g_fin_query_settings;
    target = SelectBestTargetInCone(actor + 0x10, g_hero_state.aimAxis, &foundCount, 0, 0, 0,
                          0.3926991f, 0.7853982f, 11.1f, 0.0f, 0.0f, 0, &settings);
    CalculateAimedLaunchVelocity(direction, position, target, 1.5f, g_hero_state.level == 29 ? 11.0f : 10.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0;
    }
    else g_hero_state.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((g_pad_state.held & g_hero_state.buttons) == 0 || g_hero_state.busy || g_hero_state.resource < 23 || !ready) break;
        if (weapon_spend_ammo(-1, 1)) {
            start_equipped_item_animation();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        if (g_pad_state.pressed & g_hero_state.buttons) PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!math_fast_float_d((int *)(state + 0x20))) break;
        *(char **)(part_l00_spawn_spinning_debris(position, direction) + 0xB8) = actor;
        cancel_hero_item_animation();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (math_fast_float_d((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_00397E60_00(bomb_glove_draw_projectile, actor);
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void bomb_glove_draw_projectile(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        part_draw_spinning_billboard_pair(1.0f, context, context->vector_10, 0);
    }
}




/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
/* Per-frame update of the Decoy Glove moby. */
void UpdateProjectileLauncher(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    moby_transform_joint_to_world(actor, 0, position);
    CalculateAimedLaunchVelocity(direction, position, 0, 1.5f, g_hero_state.level == 29 ? 11.0f : 5.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = coll_trace_projectile_to_impact(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (g_hero_state.level == 29) {
        if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0;
    }
    else g_hero_state.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((g_pad_pressed_flags & g_hero_state.buttons) == 0 || g_hero_state.busy || g_hero_state.resource < 9 || !ready) break;
        if (weapon_spend_ammo(-1, 1)) {
            start_equipped_item_animation();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!math_fast_float_d((int *)(state + 0x20))) break;
        *(char **)(decoy_create_projectile(position, direction) + 0xB8) = actor;
        cancel_hero_item_animation();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (math_fast_float_d((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(decoy_glove_draw_projectile, actor);
}

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void decoy_glove_draw_projectile(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_1(1.0f, context, context->vector_10, 0);
    }
}

/* The mode word at 0x18C0B4 must be 8 and the object's byte 0x43 must not be 6; the
 * helper then takes the object with mode 6, zero and ten. */
/* Per-frame update of the Helipack moby: keeps the hero in the flying pose. */
void helipack_update(char *object)
{
    if (D_18C0B4 == 8) {
        if (*(unsigned char *)(object + 0x43) != 6)
            anim_start_blended(object, 6, 0, 10);
    }
}

/* func_L00_0039E158 is defined in L00_0038F178-rail.c. */

/* multiply binary32 field2C by exact1.025f then subtract3 modulo256 from byte23; call original pointer helper if updated byte below4; no original semantic field names recovered */
void part_update_fading_shrinking(NativeUpdate775View *object)
{
    object->field2C *= 1.025f;
    object->field23 -= 3;
    if (object->field23 < 4)
        moby_mark_spawned(object);
}

/* func_L00_0039E600 is defined in L00_0039E600.c. */


/* func_L00_003A09F8 is defined in L00_0038F178-tile.c. */

/* func_L00_003A0C00 is in L00_003A0C00.c. */

