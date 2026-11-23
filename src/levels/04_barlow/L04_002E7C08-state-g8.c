/* func_L04_002E7C08 (04_barlow): the hero's state entry, family F3. It changes the action at 0x2294, initialises the
 * movement parameters of the new state and picks its animation: a jump table on the new state id.
 * Ported from func_L19_002C44F8 (src/levels/19_grelbin/L19_002C44F8.c, whose header explains how the parameter
 * blocks were read off retail: store order by sched1 register weight, early-set locals, shared constants).
 * Differences from the L19 routine: no states 0x79, 0x7D, 0x86, 0x8D-0x91, 0x94; state 0x2E (cases 0, 2 and 3 redirect to it, and the state-2 group runs its slide); no 0x38 or 0x92 arms in the 7-group; no inner 0x93 case; case 4 has no 0x22B4 == 4 shortcut.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef TI128 V4_F6a70b950;
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
typedef struct {
    char pad0[35];        /* 0   */
    unsigned char f35;    /* 35  */
    char pad36[8];        /* 36  */
    float f44;            /* 44  */
    unsigned char f48;    /* 48  */
    unsigned char f49;    /* 49  */
    unsigned short f50;   /* 50  */
    unsigned short f52;   /* 52  */
    char pad54[2];        /* 54  */
    long long f56;        /* 56  */
    char pad64[34];       /* 64  */
    unsigned char f98;    /* 98  */
    char pad99[21];       /* 99  */
    int f120;             /* 120 */
    unsigned short f124;  /* 124 */
    char pad126[26];      /* 126 */
    int f152;             /* 152 */
    char pad156[14];      /* 156 */
    short f170;           /* 170 */
} Src_F66766f2b;

typedef struct {
    char pad0[256];       /* 0   */
    int a[4];             /* 256 */
    int b[4];             /* 272 */
    Src_F66766f2b *c[4];            /* 288 */
    float d[4];           /* 304 */
    int pad320;           /* 320 */
    Src_F66766f2b *src;             /* 324 */
    int count;            /* 328 */
} List_F66766f2b;
extern f32 math_fabs(f32);
extern void vec_clear_128(TI128 *);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_signed_float_range(f32, f32);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern void vec_clamp_length(float *, float);
extern s32 math_l00_return_argument(s32);
extern void hero_clear_slot_records(void);
extern u32 hero_get_slot_object(s32);
extern s32 hero_is_in_special_kind_or_mode(void);
extern f32 hero_get_recent_float(int);
extern void cancel_hero_item_animation(void);
extern void hero_reset_speeds_and_vectors(void);
extern s32 moby_is_class_71(u8 *);
extern void hero_scale_saved_vectors(f32);
extern f32 hero_get_direction_angle_delta(void *, int);
extern int hero_play_sound(int, int);
extern int hero_classify_input_direction(void);
extern void hero_select_anim_frame(s32, s32);
extern f32 cam_get_view_space_vector_length(char *);
extern void cam_set_view_space_height(V4_F6a70b950 *, V4_F6a70b950 *, float);
extern int actuator_play_pattern(unsigned int);
extern void actuator_stop_all(void);
extern void level_init_pending_slot(void *, char *);
extern void level_append_record_to_table(List_F66766f2b *, int, int, float);
extern void level_release_slot_list(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern int snd_start_in_slot(int, int, int);
extern void hero_start_move_state_walk_or_run(int);
extern s32 enemy_get_kind_index(u8 *);
extern void enemy_reset_timer_by_kind(u8 *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern f32 vec_length_xy(void *);
extern f32 fast_vec_dist(void *, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern s32 FloatToInt(f32);
extern void anim_start_blended(void *, int, int, int);
/* These calls use side effects only; their original scalar return contracts remain unqualified. */
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void RippleDisturb(void *, s32, u32, f32, f32, f32, f32);
extern void AdjustPlayerHealth(int);
extern void hero_play_footstep_sound_dust(int, int, int, int);
extern void hero_clear_tracked_slots(void);
extern void part_emit_hero_dust_and_debris(int, int, int);
extern void hero_create_item_slot_objects(int, int);
extern void hero_resolve_stick_direction(int, f32);
extern void hero_l00_select_aim_target(f32, f32, f32);
extern void hero_setup_attached_object_transform(void);
extern int hero_try_start_grab(void);
extern void set_hero_animation(int, int, f32);
extern void UpdateHeroAimTarget(f32, f32, f32);
extern s32 hero_get_weapon_animation_id(int);
extern u32 g_frame_counter;
extern s32 g_is_pal_video;
extern u8 g_unlocked_item_flags[8];
extern u8 g_hero_animation_by_index[8] __attribute__((sda));
extern u8 g_hero_state_ptr_table[8] __attribute__((sda));
extern s32 g_hero_state_entries[][11];
extern u8 *g_water_ripple_grid;
extern s32 g_water_ripple_size;
extern u8 g_hero_state[];
extern u32 g_current_map_index;
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
extern Statistics g_statistics_table[];
extern Statistics g_progress_statistics[];
extern s32 g_game_l04_mode;
extern s32 g_hero_l04_lock_flag_b __attribute__((sda));
extern f32 g_hero_enter_state_float_a __attribute__((sda));
extern f32 g_hero_enter_state_float_b __attribute__((sda));
extern s32 g_hero_l04_animation_ids[2] __attribute__((sda));
extern f32 g_hero_state_float_rows[][25];
extern u8 g_hero_l04_state_data_table[];
typedef struct { u8 pad0[0x148]; f32 f148; u8 pad14C[0x400 - 0x14C]; s32 i400; } L19State_1B9900;
extern L19State_1B9900 g_hero_l04_state;

/* All resident fields below are views of the single player-state object. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
#define HP ((Hero *)D_00189E20)
#define BYTE(o) (HP->b[(o)])
#define HALF(o) (HP->uh[(o)/2])
#define SHORT(o) (HP->h[(o)/2])
#define WORD(o) (HP->i[(o)/4])
#define BITS(o) (HP->u[(o)/4])
#define REAL(o) (HP->f[(o)/4])
#define PTR(o) (HP->ptr[(o)/4])
#define VEC(o) (D_00189E20 + (o))
#define COPY_VECTOR(dst,src) (*(TI128 *)VEC(dst) = *(TI128 *)VEC(src))

/* Changes the player's action, initializes its movement parameters and selects animation. */
s32 hero_l04_set_move_state(s32 action, s32 animate) {
    u8 *objectSnapshot;
    u8 *hit_10, *hit_29, *hit_44, *hit_45, *hit_52;
    s32 oldStep;
    u8 wasGliding;
    u8 oldWeapon;
    s32 current, mode, index;
    f32 angle_13;
    u32 animation_13;
    u32 animation_14;
    s32 selected_13;
    s32 selected_14;
    s32 selected_15;
    s32 selected_83;
    s32 selected_8, selected_9, selected_18, selected_21, selected_22, selected_52;
    u32 animation_16, animation_21, animation_22, animation_41, animation_43, animation_53;
    f32 frames;
    f32 angle_53;
    f32 value_18, value_21, value_22, value_37;
    if (WORD(0x229C) == 0x14 && (action != 0x61 || animate != 2)) return 0;
    if ((g_game_l04_mode == 2 || g_game_l04_mode == 6) && animate != 2) return 0;
    if (WORD(0x24CC) == 0 && (WORD(0x229C) == 2 || WORD(0x229C) == 7)) {
        if (action != 6 && action != 0x39 && action != 0x43 && action != 0x91 &&
            action != 0x5F && action != 0x74 && action != 0x78 && action != 0x79 &&
            action != 0x7C && action != 0x67 && action != 0x7D && action != 0x7F) return 0;
    }
    objectSnapshot = PTR(0x2290);
    oldStep = WORD(0x2298);
    wasGliding = BYTE(0x22B7);
    WORD(0x22AC) = WORD(0x22A0);
    WORD(0x22B0) = WORD(0x22A4);
    WORD(0x22A8) = WORD(0x1B8);
    WORD(0x22A0) = WORD(0x2294);
    WORD(0x22A4) = WORD(0x229C);
    WORD(0x2294) = action;
    WORD(0x2298) = 0;
    if (BYTE(0x22B5) == 1) BYTE(0x22B5) = 0;
    BYTE(0x22BC) = 0;
    if (BYTE(0x22B4) == 0) {
        *(s32 *)(PTR(0x2290) + 0x9C) = 0;
        BYTE(0x22BD) = 0;
        BYTE(0x22B7) = 0;
        BYTE(0x22C2) = 0;
        BYTE(0x22BF) = 0;
        HALF(0x2504) = 0;
        level_release_slot_list((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x18E0));
    }
    /* A change of action stops the vibration, but not while 0x1FA counts down: the 50 ticks
     * after the wrench slam's rumble starts as it strikes the ground. */
    if (SHORT(0x1FA) == 0) actuator_stop_all();
    hero_create_item_slot_objects(WORD(0x22A0), WORD(0x2294));
    WORD(0x1188) = 0;
    switch (action) {
    case 0:
        WORD(0x229C) = 0;
        BITS(0x24A0) = 0;
        if (WORD(0x1248) == 0x1A) cancel_hero_item_animation();
        BYTE(0x24EF) = 0;
        WORD(0x11A0) = math_random_int_range(50, 100);
        hero_clear_slot_records();
        if (BYTE(0x22B4)) { hero_start_move_state_walk_or_run(0); return 1; }
        COPY_VECTOR(0x160, 0x120);
        if (BYTE(0x1492) && vec_length_xy(VEC(0x160)) > 0.00833333377f) { hero_l04_set_move_state(0x2E, 1); return 0; }
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { hero_l04_set_move_state(0x76, 1); return 0; }
        WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        if (hero_get_weapon_animation_id(0) == 0x51) set_hero_animation(hero_get_weapon_animation_id(0), 0, 18.0f); else set_hero_animation(hero_get_weapon_animation_id(0), 0, -1.0f);
        goto finish;
    case 0x64:
        WORD(0x229C) = 0; BITS(0x24A0) = 0;
        vec_clear_128((TI128 *)VEC(0x160)); WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        if (hero_get_weapon_animation_id(0) == 0x51) set_hero_animation(hero_get_weapon_animation_id(0), 0, 18.0f); else set_hero_animation(hero_get_weapon_animation_id(0), 0, -1.0f);
        goto finish;
    case 0x3D:
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 9.0f);
        if (PTR(0x1854)) anim_start_blended(PTR(0x1854), 0, 0, 9);
        goto finish;
    case 0x39:
        WORD(0x229C) = 20; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        set_hero_animation(0x45, 0, 12.0f); goto finish;
    case 0x7C:
        WORD(0x229C) = 20; HALF(0x1F0) = 10000; BITS(0x24A0) = 0;
        REAL(0x79C) = REAL(0x330) - 0.37f; WORD(0x24CC) = 0;
        REAL(0x794) = REAL(0x118) * 0.2f;
        if (REAL(0x794) < -0.116666674614f) REAL(0x794) = -0.116666674614f;
        BYTE(0x22B7) = 1; REAL(0x790) = REAL(0x88) - REAL(0x79C); BITS(0x7A0) = 0;
        if (!animate) goto finish;
        set_hero_animation(0x6D, 0, 11.0f); goto finish;
    case 0x32: {
        s32 n;
        WORD(0x229C) = 17; BITS(0x24A0) = 11; BYTE(0x22B7) = 1; BITS(0xA3C) = 0;
        if (WORD(0x22A4) == 18) { hero_play_sound(3, 0); WORD(0x2298) = 1; }
        else WORD(0xA34) = 45;
        WORD(0x1188) = 0x68; BITS(0xA20) = 0;
        n = 12;
        if (!animate) goto finish;
        set_hero_animation(0x3B, 0, n); goto finish; }
    case 0x34: {
        s32 f; s32 n;
        WORD(0x229C) = 17; n = 11; BYTE(0x22B7) = 1; WORD(0xA34) = 60; BITS(0x24A0) = n;
        if (WORD(0x22A4) == 18) { hero_play_sound(3, 0); WORD(0x2298) = 1; }
        WORD(0x1188) = 0x68; BITS(0xA20) = 0;
        f = WORD(0x22A0) == 0x32 ? 15 : n;
        if (animate) set_hero_animation(0x3D, 0, f);
        goto finish;
    }
    case 0x33:
        WORD(0x229C) = 17; BITS(0x24A0) = 11; BYTE(0x22B7) = 1;
        COPY_VECTOR(0x160, 0x120); WORD(0x1188) = 0x68;
        selected_8 = WORD(0x22A0) == 0x34 ? -2 : 35;
        if (!animate) goto finish;
        set_hero_animation(0x3C, 0, (f32)selected_8); goto finish;
    case 0x36:
        WORD(0x229C) = 18; BYTE(0x22B7) = 1; BITS(0x24A0) = 0; HALF(0xA4A) = 0;
        if (WORD(0x22A4) == 17) {
            part_emit_hero_dust_and_debris(3, 10, 0);
            if (g_water_ripple_grid) RippleDisturb(g_water_ripple_grid, g_water_ripple_size, 0, REAL(0x80), REAL(0x84), 0.4f, 0.3f);
        } else if (REAL(0x118) < -0.00833333376795f) {
            selected_9 = FloatToInt(math_fabs(REAL(0x118)) * 300.0f);
            if (selected_9 > 40) selected_9 = 40;
            part_emit_hero_dust_and_debris(3, selected_9, 1);
            if (g_water_ripple_grid) RippleDisturb(g_water_ripple_grid, g_water_ripple_size, 0, REAL(0x80), REAL(0x84), 0.5f, -0.4f);
            HALF(0xA4A) = 75;
        }
        REAL(0x794) = REAL(0x118) * 0.37f; WORD(0x798) = 0;
        if (REAL(0x794) < -0.116666674614f) REAL(0x794) = -0.116666674614f;
        REAL(0x79C) = REAL(0x330); BITS(0x7A0) = 0;
        REAL(0x790) = (REAL(0x88) - REAL(0x330)) - -0.12f;
        COPY_VECTOR(0x160, 0x120); REAL(0x168) = 0;
        vec_clamp_length((f32 *)VEC(0x160), 0.0916666686535f);
        WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        set_hero_animation(0x3A, 0, 22.0f); goto finish;
    case 0x72: case 0x73:
        WORD(0x229C) = 7; BITS(0x24A0) = 0;
        hero_scale_saved_vectors(0.5f); BYTE(0x22B7) = 1; COPY_VECTOR(0xF0, 0x110);
        hit_10 = part_find_owned_effect_slot(PTR(0x2290), 1, 0);
        if (hit_10) AdjustPlayerHealth(FloatToInt(*(f32 *)(hit_10 + 0x2C)));
        else AdjustPlayerHealth(1);
        HALF(0x1DC) = 77;
        if (animate) {
            if (WORD(0x2294) == 0x72) set_hero_animation(0x69, 3, -3.0f);
            else set_hero_animation(0x68, 3, -3.0f);
            *(f32 *)(PTR(0x2290) + 0x44) = g_hero_state_float_rows[WORD(0xC30)][WORD(0xC34)++];
            goto finish;
        }
        goto finish;
    case 0x35:
        BITS(0x24A0) = 0; WORD(0x229C) = 18; BITS(0xA3C) = 0;
        BYTE(0x22B7) = 1; WORD(0x798) = 45; WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        set_hero_animation(0x5E, 0, 17.0f); goto finish;
    case 0x67:
        WORD(0x229C) = 20; BYTE(0x22B7) = 1; BITS(0x24A0) = 0;
        if (SHORT(0xA4E) > 50 && g_progress_statistics[12].count < 0xFFFF) g_progress_statistics[12].count++;
        if (g_frame_counter > g_progress_statistics[12].maximum) g_progress_statistics[12].maximum = g_frame_counter;
        g_progress_statistics[12].levels = (g_progress_statistics[12].levels | (1u << g_current_map_index)) | 0x80000000u;
        if (WORD(0xA50) > 2 && g_progress_statistics[29].count < 0xFFFF) g_progress_statistics[29].count++;
        if (g_frame_counter > g_progress_statistics[29].maximum) g_progress_statistics[29].maximum = g_frame_counter;
        g_progress_statistics[29].levels = (g_progress_statistics[29].levels | (1u << g_current_map_index)) | 0x80000000u;
        COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        set_hero_animation(0x58, 0, 10.0f); goto finish;
    case 0x7F:
        WORD(0x229C) = 20; BYTE(0x22B7) = 1; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        set_hero_animation(0x79, 0, 10.0f); goto finish;
    case 0x85:
        WORD(0x229C) = 32; BITS(0x24A0) = 8; BYTE(0x22B7) = 1; BYTE(0x22C2) = 1;
        if (animate) set_hero_animation(0x4F, 0, 5.0f);
        REAL(0x98) = *(f32 *)(PTR(0x1830) + 0xF8);
        *(TI128 *)VEC(0x80) = *(TI128 *)(PTR(0x1830) + 0x10);
        vec_clear_128((TI128 *)VEC(0xF0)); goto finish;
    case 1:
        BITS(0x24A0) = 4;
        WORD(0x229C) = 0;
        if (BYTE(0x22BA)) goto finish;
        animation_16 = hero_get_weapon_animation_id(1);
        if (PTR(0x2290)[0x43] == animation_16 || !animate) goto finish;
        set_hero_animation(animation_16, 0, 18.0f); goto finish;
    case 0x2F:
        WORD(0x229C) = 8; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x110);
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 5.0f); HALF(0x1EC) = 7;
        goto finish;
    case 2: case 0x70: case 0x2E:
        WORD(0x229C) = 1;
        BITS(0x24A0) = 0;
        if (WORD(0x22A4) != 4 && WORD(0x22B0) != 4) REAL(0x1B4) = cam_get_view_space_vector_length((char *)VEC(0x120));
        COPY_VECTOR(0x3F0, 0);
        BITS(0x410) = 0;
        REAL(0x408) = REAL(0x98);
        if (REAL(0x1B4) > 0.11666667461395264f) REAL(0x1B4) = 0.11666667461395264f;
        BYTE(0x40F) = 0;
        hero_resolve_stick_direction(0, 1.0f);
        value_18 = FastDiffRots(REAL(0x98), REAL(0x1A0));
        if (value_18 > 1.5707964897155762f &&
            (WORD(0x22A4) == 4 || WORD(0x22A0) == 3 || WORD(0x22AC) == 3)) REAL(0x1B4) = 0;
        WORD(0x1188) = 0x68;
        if (BYTE(0x149A)) {
            if (SHORT(0x34C) == 0 || REAL(0x31C) < 0.3f) { hero_l04_set_move_state(0x76, 1); return 0; }
        }
        if (BYTE(0x1492) || WORD(0x2294) == 0x2E) {
            if (REAL(0x1B4) > 0.128333330f) REAL(0x1B4) = 0.128333330f;
            BITS(0xF8) = 0;
            vec_clamp_length((f32 *)VEC(0xF0), 0.128333330f);
            WORD(0x2294) = 0x2E; BITS(0x404) = 0;
            set_hero_animation(0x37, 0, 8.0f); goto finish;
        }
        if (BYTE(0x22B9) || WORD(0x2294) == 0x70) {
            WORD(0x2294) = 0x70; set_hero_animation(0x59, 0, 8.0f); goto finish;
        }
        WORD(0x2298) = 0;
        BYTE(0x40C) = 0; BYTE(0x40E) = 0;
        if (!animate) goto finish;
        selected_18 = WORD(0x24CC) == 1 ? 12 : 8;
        if (WORD(0x22AC) == 0x22 || WORD(0x22A0) == 0x22) selected_18 = 15;
        if (WORD(0x22AC) == 0x83 || WORD(0x22A0) == 0x83) selected_18 = 15;
        if (WORD(0x22A0) == 0x13) selected_18 = 13;
        if (WORD(0x22AC) == 6 || WORD(0x22AC) == 0x2C) selected_18 = 18;
        if (WORD(0x22B0) == 4 && BYTE(0x49C) > 5) selected_18 = 13;
        set_hero_animation(WORD(0x2298) + 3, g_hero_l04_animation_ids[WORD(0x2298)], (f32)selected_18); goto finish;
    case 0x7B: {
        s32 n = -2;
        WORD(0x229C) = 28; WORD(0x1188) = 0x68; BITS(0x24A0) = 0;
        COPY_VECTOR(0xF0, 0x110);
        if (WORD(0x1298) != 0x36) { WORD(0x2304) = WORD(0x1298); WORD(0x22CC) = 0x36; }
        if (!animate) goto finish;
        set_hero_animation(0x8B, 0, n); goto finish; }
    case 0x62:
        WORD(0x229C) = 1; BITS(0x24A0) = 0; REAL(0x1B4) = vec_length_xy(VEC(0x120));
        BYTE(0x22BC) = 1;
        if (!BYTE(0x22B4)) cancel_hero_item_animation();
        if (!animate) goto finish;
        if (BYTE(0x22B4) == 1) { set_hero_animation(2, 0, 8.0f); goto finish; }
        if (BYTE(0x22B4) != 0) goto finish;
        set_hero_animation(WORD(0x2298) + 3, g_hero_l04_animation_ids[WORD(0x2298)], 8.0f); goto finish;
    case 3:
        WORD(0x229C) = 1; BITS(0x24A0) = 0;
        COPY_VECTOR(0x160, 0x120);
        if (BYTE(0x1492)) { hero_l04_set_move_state(0x2E, 1); return 0; }
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { hero_l04_set_move_state(0x76, 1); return 0; }
        if (hero_try_start_grab()) return 0;
        if (hero_get_weapon_animation_id(0) == 0x51) {
            if (!animate) goto finish;
            if (hero_l04_set_move_state(0, 0)) set_hero_animation(hero_get_weapon_animation_id(0), 0, 18.0f);
            return 0;
        }
        if (!animate) goto finish;
        animation_21 = objectSnapshot[0x42];
        {
            value_21 = REAL(0xC38); selected_21 = 6;
            if (math_l00_return_argument(animation_21) == 4 && value_21 > 3.0f && value_21 < 16.0f) selected_21 = 5;
            set_hero_animation(selected_21, 4, 9.0f);
            goto finish;
        }
    case 0x63:
        WORD(0x229C) = 1; BITS(0x24A0) = 0;
        REAL(0x1B4) = cam_get_view_space_vector_length((char *)VEC(0x120)); COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        animation_22 = objectSnapshot[0x42]; {
            value_22 = REAL(0xC38); selected_22 = 6;
            if (math_l00_return_argument(animation_22) == 4 && value_22 > 3.0f && value_22 < 16.0f) selected_22 = 5;
            set_hero_animation(selected_22, 4, 9.0f);
            goto finish;
        }
    case 4:
        WORD(0x229C) = 12; BITS(0x24A0) = 0;
        REAL(0x1B4) = vec_length_xy(VEC(0x120));
        if (REAL(0x1B4) > 0.11666667461395264f) REAL(0x1B4) = 0.11666667461395264f;
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { hero_l04_set_move_state(0x76, 1); return 0; }
        WORD(0x1188) = 0x68;
        COPY_VECTOR(0x160, 0x120);
        vec_clamp_length((float *)VEC(0x160), 0.11666667461395264f);
        if (REAL(0x178) > 0.05833333730697632f) hero_play_sound(9, 0);
        if (animate) {
            if (PTR(0x2290)[0x42] == hero_get_weapon_animation_id(0)) set_hero_animation(13, 2, 9.0f);
            else set_hero_animation(13, 2, 14.0f);
            hero_select_anim_frame(3, 18);
        }
        goto finish;
    case 0x8A:
        WORD(0x229C) = 33; BITS(0x24A0) = 0;
        if (g_statistics_table[13].count < 0xFFFF) g_statistics_table[13].count++;
        if (g_frame_counter > g_statistics_table[13].maximum) g_statistics_table[13].maximum = g_frame_counter;
        g_statistics_table[13].levels = (g_statistics_table[13].levels | (1u << g_current_map_index)) | 0x80000000u;
        REAL(0x1A0) = mat_fast_helper_a(*(f32 *)(PTR(0xB10) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xB10) + 0x14) - REAL(0x84));
        BITS(0xB1C) = 0; { if (animate) { set_hero_animation(0x2F, 2, 5.0f); hero_select_anim_frame(10, 14); } goto finish; }
    case 0x8B:
        WORD(0x229C) = 33; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        goto finish;
    case 0x23:
        WORD(0x229C) = 13; BITS(0x24A0) = 7;
        if (g_statistics_table[13].count < 0xFFFF) g_statistics_table[13].count++;
        if (g_frame_counter > g_statistics_table[13].maximum) g_statistics_table[13].maximum = g_frame_counter;
        g_statistics_table[13].levels = (g_statistics_table[13].levels | (1u << g_current_map_index)) | 0x80000000u;
        REAL(0x1A0) = mat_fast_helper_a(*(f32 *)(PTR(0xAA4) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xAA4) + 0x14) - REAL(0x84));
        if (WORD(0x22A0) == 0x28) COPY_VECTOR(0x160, 0xF0);
        { if (animate) { set_hero_animation(0x2F, 2, 5.0f); hero_select_anim_frame(10, 14); } goto finish; }
    case 0x24:
        WORD(0x229C) = 13; BITS(0x24A0) = 7; BITS(0xAA0) = 0;
        BITS(0xAB4) = 0; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        set_hero_animation(0x30, 1, 10.0f); goto finish;
    case 0x25:
        WORD(0x229C) = 13; BITS(0x24A0) = 7; BYTE(0x22BC) = 1;
        BITS(0xAA0) = 0; BITS(0xAB4) = 0;
        REAL(0xABC) = fast_vec_dist(VEC(0x80), PTR(0xAA4) + 0x10);
        if (!animate) goto finish;
        set_hero_animation(0x30, 1, 5.0f); goto finish;
    case 0x2B:
        WORD(0x229C) = 14; BITS(0x24A0) = 7;
        if (g_statistics_table[13].count < 0xFFFF) g_statistics_table[13].count++;
        if (g_frame_counter > g_statistics_table[13].maximum) g_statistics_table[13].maximum = g_frame_counter;
        g_statistics_table[13].levels = (g_statistics_table[13].levels | (1u << g_current_map_index)) | 0x80000000u; HALF(0xAFE) = 1;
        BITS(0xAE8) = 0; BYTE(0x22BC) = 1; PTR(0xAD4) = PTR(0xAD0);
        HALF(0xADC) = 0; HALF(0xAFC) = 0; BITS(0xAF4) = 0; BITS(0xAF8) = 0;
        hit_29 = *(u8 **)(PTR(0xAD0) + 0x68);
        REAL(0xAE0) = *(f32 *)(hit_29 + 4);
        if (*(f32 *)(hit_29 + 0x10) == REAL(0xAE8)) *(f32 *)(hit_29 + 0x14) = *(f32 *)(hit_29 + 0xC);
        else *(f32 *)(hit_29 + 0x14) = *(f32 *)(hit_29 + 0x10);
        REAL(0xB04) = 0.025f; REAL(0xB08) = 0.33f; REAL(0xB0C) = 0.1833333373f;
        vec_clear_128((TI128 *)VEC(0xA0)); HALF(0x206) = 40;
        if (*(f32 *)(hit_29 + 0x24) != 0.0f) REAL(0xB04) = *(f32 *)(hit_29 + 0x24);
        if (*(f32 *)(hit_29 + 0x28) != 0.0f) REAL(0xB08) = *(f32 *)(hit_29 + 0x28);
        if (*(f32 *)(hit_29 + 0x2C) != 0.0f) REAL(0xB0C) = *(f32 *)(hit_29 + 0x2C);
        REAL(0xAEC) = mat_fast_helper_a(*(f32 *)(PTR(0xAD4) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xAD4) + 0x14) - REAL(0x84));
        REAL(0xAE4) = fast_vec_dist(VEC(0x80), PTR(0xAD4) + 0x10);
        REAL(0xAF0) = 0.007500000298f;
        if (WORD(0x22A4) == 4) REAL(0xAF0) = REAL(0x520);
        else if (WORD(0x22A4) == 2) REAL(0xAF0) = REAL(0xA80);
        if (animate) { set_hero_animation(0x34, 0, 11.0f); REAL(0xC20) = 0.7f; }
        goto finish;
    case 0x2C:
        WORD(0x229C) = 2; BITS(0x24A0) = 7;
        vec_clear_128((TI128 *)VEC(0xA0)); COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        set_hero_animation(11, 0, 15.0f); goto finish;
    case 0x17:
        WORD(0x229C) = 3; BITS(0x24A0) = 13;
        REAL(0x57C) = 0.0061111114919f; REAL(0x580) = REAL(0x88);
        if (WORD(0x22A4) == 4) { REAL(0x57C) = REAL(0x520); REAL(0x580) = REAL(0x490); }
        BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        if (REAL(0x174) > 0.0583333373069f) set_hero_animation(0x20, 0, 9.0f);
        else set_hero_animation(0x20, 1, 11.0f);
        goto finish;
    case 0x18:
        WORD(0x229C) = 3; BYTE(0x22BF) = 1; BITS(0x24A0) = 13;
        BYTE(0x22BC) = 1; WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        set_hero_animation(0x21, 0, 6.0f); goto finish;
    case 0x19:
        WORD(0x229C) = 3; BITS(0x24A0) = 13; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        set_hero_animation(0x24, 0, 6.0f); goto finish;
    case 0x1A:
        WORD(0x229C) = 3; BITS(0x24A0) = 13; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        set_hero_animation(0x25, 0, 6.0f); goto finish;
    case 0x76:
        WORD(0x229C) = 2; BITS(0x24A0) = 0; COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        set_hero_animation(11, 0, 12.0f); goto finish;
    case 6: case 0x74:
        WORD(0x229C) = 2; BITS(0x24A0) = 0;
        if (WORD(0x2294) == 0x74) {
            WORD(0x229C) = 0x14;
            if (BYTE(0x22B4) == 1) {
                if (g_current_map_index == 3) snd_start_in_slot(17, 0, (s32)PTR(0x2290));
                else if (g_current_map_index == 14) snd_start_in_slot(21, 0, (s32)PTR(0x2290));
            }
        }
        REAL(0xA80) = 0.006111111491918564f;
        REAL(0xA84) = 0.0019444444915279746f;
        if (WORD(0x2294) == 0x74) {
            if (!BYTE(0x22B4)) HALF(0x24D6) = hero_play_sound(14, 0x20);
            REAL(0xA90) = math_random_signed_float_range(0.05235988646745682f, 0.07272206246852875f);
            REAL(0xA94) = math_random_signed_float_range(0.05235988646745682f, 0.07272206246852875f);
        }
        WORD(0x1188) = 0x68; WORD(0x2298) = 0;
        COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        if (REAL(0x31C) > 1.75f) { set_hero_animation(11, 0, 12.0f); WORD(0x2298) = 1; goto finish; }
        set_hero_animation(10, 0, 10.0f); goto finish;
    case 0x82: {
        s32 n = -2;
        WORD(0x229C) = 30; BITS(0x24A0) = 0;
        if (WORD(0x22A0) != 0x16) {
            value_37 = REAL(0x5B8); REAL(0x5B0) = 50.0f;
            if (value_37 != 0.0f) { REAL(0x5B0) = value_37; REAL(0x5B8) = 0; }
        }
        BYTE(0x24EF) = 1; WORD(0x1188) = 0x68; WORD(0x7A8) = 0;
        HALF(0x5BE) = 0; WORD(0x5A8) = 0; WORD(0x5A4) = 0;
        COPY_VECTOR(0xF0, 0x110); HALF(0x5BC) = 7;
        if (!animate) goto finish;
        set_hero_animation(0x13, 0, n); goto finish; }
    case 8: {
        s32 n = -2;
        WORD(0x229C) = 5; WORD(0x1188) = 0x68; BITS(0x24A0) = 0;
        if (REAL(0x170) > 0.075f) hero_scale_saved_vectors(0.075f / REAL(0x170));
        WORD(0x24C8) = 0; COPY_VECTOR(0xF0, 0x110);
        if (!animate) goto finish;
        set_hero_animation(0x13, 0, n); goto finish; }
    case 7: case 9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF: case 0x10: case 0x11:
    case 0x12: case 0x1B: case 0x28: case 0x29: case 0x38: case 0x45: case 0x48: case 0x5B: case 0x66:
    case 0x6E: case 0x81: case 0x89: case 0x92:
        if (WORD(0x2294) != 0x81 && PTR(0x33C) &&
            (*(s16 *)(PTR(0x33C) + 0xAA) == 0x9B9 || *(s16 *)(PTR(0x33C) + 0xAA) == 0xF05)) {
            hero_l04_set_move_state(0x81, 1); return 0;
        }
        if (WORD(0x2294) != 0x6E && SHORT(0x348) == 1 && action != 0xE &&
            action != 0x38 && !g_hero_l04_lock_flag_b) { hero_l04_set_move_state(0x6E, 1); return 0; }
        if (WORD(0x22A0) == 0x11 && !BYTE(0x24DA)) BYTE(0x24DB)++;
        else BYTE(0x24DB) = 0;
        if (SHORT(0x1F2)) { hero_l04_set_move_state(0x82, 1); return 0; }
        if (SHORT(0x212)) {
            WORD(0x2294) = WORD(0x22A0); WORD(0x2298) = oldStep; WORD(0x1B8) = WORD(0x22A8);
            return 0;
        }
        WORD(0x229C) = 4;
        if ((u32)(action - 0x28) < 2) BITS(0x24A0) = 3; else BITS(0x24A0) = 0x50;
        if (WORD(0x2294) == 7 || WORD(0x2294) == 0xF || WORD(0x2294) == 0xD ||
            (WORD(0x2294) == 0xB && WORD(0x22A4) != 4)) {
            oldWeapon = BYTE(0x149D);
            hero_play_footstep_sound_dust(oldWeapon, 0, 0, 30);
            hero_play_footstep_sound_dust(oldWeapon, 1, 0, 30);
        }
        COPY_VECTOR(0xF0, 0x120);
        if (WORD(0x2294) != 0x12 && BYTE(0x1494) && REAL(0x88) < REAL(0x330) + 0.5f)
            part_emit_hero_dust_and_debris(3, 0x10, 0);
        {
        f32 c504, c514, c4A4;
        REAL(0x490) = REAL(0x88);
        REAL(0x520) = 0.00825f;
        WORD(0x448) = -1;
        REAL(0x500) = 0.0055555556900799274f;
        c504 = 0.0030555557459592819f;
        REAL(0x510) = 2.5f;
        HALF(0x528) = BYTE(0x1492);
        c514 = 0.5f;
        c4A4 = 0.099166668951511383f;
        HALF(0x51A) = 80; REAL(0x494) = 0.25016391277313232f;
        REAL(0x4A0) = 0.83333337306976318f; BYTE(0x49E) = 0; BYTE(0x49C) = 0;
        BITS(0x4B0) = 0;
        BITS(0x4B4) = 0; BYTE(0x49D) = 0; REAL(0x504) = c504; HALF(0x524) = 0; BYTE(0x52C) = 0;
        BYTE(0x52E) = 0; BYTE(0x52F) = 0;
        HALF(0x52A) = 70; HALF(0x526) = 0; REAL(0x514) = c514; REAL(0x4A4) = c4A4;
        REAL(0x458) = 0.0f; BYTE(0x49F) = 0;
        BITS(0x594) = 0; HALF(0x24D8) = 0;
        }

        if (WORD(0x2294) == 7) {
            SHORT(0x4AC) = 5; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x50C) = 2.3f; REAL(0x4A8) = 1.28f; REAL(0x508) = 1.28f; BYTE(0x52C) = 1; BYTE(0x52E) = 1; HALF(0x518) = 15; BYTE(0x52F) = 1; REAL(0x458) = 0.0096525000408291817f;

        }
        else if (WORD(0x2294) == 0x81) {
            SHORT(0x4AC) = 5; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x4A8) = g_hero_enter_state_float_a; REAL(0x50C) = g_hero_enter_state_float_a + 0.5f; REAL(0x508) = g_hero_enter_state_float_a; HALF(0x518) = 15; HALF(0x51A) = 400; REAL(0x510) = 300.0f; REAL(0x520) = g_hero_enter_state_float_b * 0.0002777777845f; HALF(0x526) = 1200; HALF(0x52A) = 1200; REAL(0x4A4) = 0.11666667461395264f;
            if (g_current_map_index == 16) REAL(0x4A4) = 0.0f;
            level_init_pending_slot(PTR(0x2290), (char *)VEC(0x18E0));
            level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 70, 2, 0.0f);
            level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 35, 4, 0.0f);
            level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 17, 6, 0.0f);

        }
        else if (WORD(0x2294) == 0x12) {
            f32 frames18;
            SHORT(0x4AC) = 2; REAL(0x4B8) = 0.6f; REAL(0x4A8) = 0.1f; frames18 = 18.0f; REAL(0x4C8) = frames18; REAL(0x4CC) = 28.0f; REAL(0x4D0) = 14.0f; REAL(0x50C) = 0.2f; REAL(0x508) = 0.1f; HALF(0x518) = 10;
            if (REAL(0x24C4) < 1.25f) {
                SHORT(0x4AC) = 15; REAL(0x50C) = 1.98f;
                REAL(0x508) = 1.95f; REAL(0x4A8) = 1.95f;
            } else {
                f32 step = REAL(0x4B0);
                cam_set_view_space_height((V4_F6a70b950 *)VEC(0xF0), (V4_F6a70b950 *)VEC(0xF0), step);
                BYTE(0x49D) = 1; WORD(0x430) = 2;
                WORD(0x434) = 0x25; REAL(0x438) = step; REAL(0x43C) = frames18;
                BITS(0x440) = 0x28; PTR(0x444) = g_hero_l04_state_data_table;
            }
            BYTE(0x49F) = 1; BYTE(0x22B7) = 1;
        }
        else if (WORD(0x2294) == 9) {
            SHORT(0x4AC) = 5; REAL(0x4B8) = 0.6f; REAL(0x4A8) = 1.0f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 11.0f; REAL(0x50C) = 2.7f; REAL(0x508) = 1.0f; HALF(0x518) = 15; REAL(0x4A4) = 0.099166668951511383f; BYTE(0x52C) = 1; BYTE(0x52E) = 1; BYTE(0x52F) = 1;

        }
        else if (WORD(0x2294) == 0x6E) {
            REAL(0x4A8) = 2.7f; SHORT(0x4AC) = 5; BYTE(0x52C) = 1; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x50C) = 2.75f; REAL(0x508) = 2.7f; HALF(0x518) = 5; BYTE(0x49F) = 1; BYTE(0x52E) = 0; BYTE(0x52F) = 0; REAL(0x4A4) = 0.11602500081062317f;

        }
        else if (WORD(0x2294) == 10) {
            REAL(0x4A8) = 1.9f; SHORT(0x4AC) = 5; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 18.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 10.0f;
            REAL(0x50C) = 1.95f; REAL(0x508) = 1.9f; HALF(0x518) = 14;
            REAL(0x520) = 0.003055555746f; BYTE(0x52E) = 1;
            HALF(0x51A) = 120; HALF(0x52A) = 90; HALF(0x526) = 70;

        }
        else if (WORD(0x2294) == 0x10) {
            REAL(0x4C8) = 18.0f; SHORT(0x4AC) = 5; REAL(0x4B8) = 0.8f;
            REAL(0x4CC) = 30.0f; REAL(0x4D0) = 11.0f; REAL(0x4A8) = 1.5f;
            REAL(0x50C) = 1.55f; REAL(0x508) = 1.5f; HALF(0x518) = 1;
            actuator_play_pattern(20);
            REAL(0x50C) = 0.9f; REAL(0x4A8) = 0.4f; REAL(0x508) = 0.4f;
            if (REAL(0x184) < 0.3333333433f) {
                level_init_pending_slot(PTR(0x2290), (char *)VEC(0x18E0));
                level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 40, 2, 0.0f);
                level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 20, 4, 0.0f);
                level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 10, 6, 0.0f);
            }
            BYTE(0x52E) = 1; REAL(0x454) = 0.19166667759418488f;
            if (REAL(0x31C) > 1.4f) REAL(0x454) = 0.094999998807907104f;
            REAL(0x520) = 0.00236111111f; REAL(0x500) = 0.012222222983837128f; REAL(0x504) = 0.013888888992369175f;

        }
        else if (WORD(0x2294) == 0x1B) {
            SHORT(0x4AC) = 10; REAL(0x4A8) = 2.0f; REAL(0x4B8) = 0.85f;
            REAL(0x4C8) = 20.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 19.0f;
            REAL(0x50C) = 2.05f; REAL(0x508) = 2.0f; REAL(0x514) = 1.0f;
            REAL(0x520) = 0.006944444496f; HALF(0x518) = 1; BITS(0x4BC) = 0;
            BYTE(0x49F) = 1; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1; BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0x11) {
            SHORT(0x4AC) = 9; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 12.0f; REAL(0x4CC) = 20.0f; REAL(0x4D0) = 10.0f; HALF(0x518) = 12;
            if (BYTE(0x24DA)) { REAL(0x498) = 0.081666670739650726f; REAL(0x50C) = 3.35f; REAL(0x508) = 3.3f; }
            else { REAL(0x498) = 0.028333336114883423f; REAL(0x50C) = 1.85f; REAL(0x508) = 1.8f; }
            BYTE(0x49F) = 1; REAL(0x4A8) = REAL(0x508); actuator_play_pattern(27);
            HALF(0x52A) = 80; REAL(0x520) = 0.008055555634f;
            COPY_VECTOR(0x4F0, 0x4E0); HALF(0x24D8) = 1; BYTE(0x22B7) = 1; BYTE(0x52C) = 1;

        }
        else if (WORD(0x2294) == 0xD) {
            REAL(0x4A8) = 4.0f; REAL(0x4C8) = 26.0f; SHORT(0x4AC) = 9;
            REAL(0x4CC) = 38.0f; REAL(0x4D0) = 18.0f; REAL(0x50C) = 4.07f;
            REAL(0x4B8) = 0.6f; REAL(0x508) = 4.0f; HALF(0x518) = 14;
            actuator_play_pattern(20); REAL(0x510) = 4.5f; HALF(0x51A) = 120;
            REAL(0x4A4) = 0.031666666269302368f; HALF(0x526) = 37;
            if (REAL(0x184) < 0.3333333433f) {
                level_init_pending_slot(PTR(0x2290), (char *)VEC(0x18E0));
                level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 40, 3, 0.0f);
                level_append_record_to_table((List_F66766f2b *)VEC(0x18E0), 20, 5, 0.0f);
            }
            BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0xF) {
            REAL(0x4A8) = 1.65f; SHORT(0x4AC) = 9;
            REAL(0x4B8) = 0.6f; REAL(0x4C8) = 50.0f; REAL(0x4CC) = 64.0f;
            REAL(0x4D0) = 28.0f; REAL(0x50C) = 1.7f; REAL(0x508) = 1.65f;
            HALF(0x518) = 5; REAL(0x510) = 4.5f; HALF(0x51A) = 130;
            REAL(0x4A4) = 0.055000003427267075f; HALF(0x526) = 85; HALF(0x1D0) = 70; BYTE(0x49D) = 1;
            if (g_is_pal_video) WORD(0x430) = 34; else WORD(0x430) = 35;
            WORD(0x434) = WORD(0x430) + 36; REAL(0x438) = 29.0f;
            REAL(0x43C) = 50.0f; BITS(0x440) = 86; PTR(0x444) = (u8 *)g_hero_state_ptr_table;
            BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0xE) {
            f32 run = 0.7f;
            if (REAL(0x31C) < 2.0f) run = (2.5f - REAL(0x31C)) * 0.5f + 0.7f;
            SHORT(0x4AC) = -1; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 32.0f; REAL(0x4CC) = 43.0f; REAL(0x4D0) = 19.0f; REAL(0x4A8) = run;
            REAL(0x50C) = run + 0.05f; REAL(0x508) = run;
            HALF(0x518) = 14; REAL(0x514) = 1.0f; REAL(0x4A4) = 0.079166673123836517f; HALF(0x526) = 30;

        }
        else if (WORD(0x2294) == 0xB) {
            SHORT(0x4AC) = 5; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f;
            REAL(0x4A8) = 3.2f; REAL(0x4CC) = 31.0f; REAL(0x4D0) = 24.0f;
            REAL(0x50C) = 3.25f; REAL(0x508) = 3.2f; HALF(0x518) = 14;
            REAL(0x510) = 4.5f; HALF(0x52A) = 50; REAL(0x514) = 1.0f; BYTE(0x49F) = 1;
            REAL(0x4C4) = hero_get_recent_float(10); COPY_VECTOR(0x480, 0);
            WORD(0x4D4) = hero_classify_input_direction(); REAL(0x4C0) = REAL(0x1A0); COPY_VECTOR(0x470, 0x190);
            if (REAL(0x174) > 0.025000002f) REAL(0x4D8) = REAL(0x174); else REAL(0x4D8) = 0.0f;
            REAL(0x4DC) = 0.0f; BYTE(0x52C) = 1;
            if (SHORT(0x1454) && REAL(0x24B8) > 0.3f) {
                REAL(0x4C0) = REAL(0x1458); COPY_VECTOR(0x470, 0x1440);
                BYTE(0x52D) = 1; REAL(0x4DC) = 0.083333335816860199f;
            } else BYTE(0x52D) = 0;
            BYTE(0x52E) = 1;

        }
        if (REAL(0x510) == 0.0f) REAL(0x510) = REAL(0x4A8) * 1.5f;
        if (!animate) goto finish;
        if (WORD(0x2294) == 7) { set_hero_animation(7, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0x6E) { set_hero_animation(7, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0x81) { set_hero_animation(7, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0x12) { set_hero_animation(0x6B, 1, -1.0f); goto finish; }
        else if (WORD(0x2294) == 9) {
            animation_41 = 8; index = FloatToInt(REAL(0xC38));
            if (math_l00_return_argument(objectSnapshot[0x42]) == 4) animation_41 = g_hero_animation_by_index[index];
            set_hero_animation(animation_41, 0, 5.0f); goto finish;
        }
        else if (WORD(0x2294) == 10) { set_hero_animation(18, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0x10) {
            if (WORD(0x22A4) == 4 || (WORD(0x22A0) == 4 && WORD(0x1B8) < 7)) {
                set_hero_animation(0x26, 0, 8.0f); SHORT(0x4AC) += 3; goto finish;
            }
            set_hero_animation(0x26, 0, 5.0f); goto finish;
        } else if (WORD(0x2294) == 0x1B) { set_hero_animation(0x22, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0x89) { set_hero_animation(0x7D, 11, 9.0f); goto finish; }
        else if (WORD(0x2294) == 0x11) { frames = 7.0f; animation_41 = 0x23; { set_hero_animation(animation_41, 2, frames); goto finish; } }
        else if (WORD(0x2294) == 0xD) { set_hero_animation(17, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0xE) { set_hero_animation(0x16, 3, 7.0f); REAL(0xC20) = 0.8f; goto finish; }
        else if (WORD(0x2294) == 0xF) { set_hero_animation(21, 0, 5.0f); goto finish; }
        else if (WORD(0x2294) == 0xB) {
            s32 anim = WORD(0x4D4) + 28;
            if (g_unlocked_item_flags[5]) { if (anim == 28) anim = 29; else if (anim == 29) anim = 28; }
            if (WORD(0x22A4) == 4) { set_hero_animation(anim, 1, 4.0f); SHORT(0x4AC) = 1; goto finish; }
            set_hero_animation(anim, 0, 5.0f); goto finish;
        }
        goto finish;
    case 0x13: case 0x14: case 0x15: case 0x1F: case 0x22: case 0x4D: case 0x83: case 0x93:
        WORD(0x229C) = 6;
        if (WORD(0x1500) && (u32)(WORD(0x2294) - 0x13) < 3) {
            if (g_progress_statistics[1].count < 0xFFFF) g_progress_statistics[1].count++;
            if (g_frame_counter > g_progress_statistics[1].maximum) g_progress_statistics[1].maximum = g_frame_counter;
            g_progress_statistics[1].levels = (g_progress_statistics[1].levels | (1u << g_current_map_index)) | 0x80000000u;
            if (g_statistics_table[56].count < 0xFFFF) g_statistics_table[56].count++;
            if (g_frame_counter > g_statistics_table[56].maximum) g_statistics_table[56].maximum = g_frame_counter;
            g_statistics_table[56].levels = (g_statistics_table[56].levels | (1u << g_current_map_index)) | 0x80000000u;
            hero_setup_attached_object_transform(); WORD(0x2294) = WORD(0x22A0); WORD(0x229C) = WORD(0x22A4);
            goto finish;
        }
        if (action != 0x83) BITS(0x24A0) = 0;
        REAL(0xBF4) = 1.0f; WORD(0xBE8) = 0; BITS(0xBE4) = 0; HALF(0xBFE) = 0;
        switch (WORD(0x2294)) {
        case 0x14:
            if (g_progress_statistics[0].count < 0xFFFF) g_progress_statistics[0].count++;
            if (g_frame_counter > g_progress_statistics[0].maximum) g_progress_statistics[0].maximum = g_frame_counter;
            g_progress_statistics[0].levels = (g_progress_statistics[0].levels | (1u << g_current_map_index)) | 0x80000000u;
            BITS(0x24A0) = 0x50; SHORT(0xBFC) = 4; WORD(0x2300) = 0;
            hero_l00_select_aim_target(8.0f, 1.047197699546814f, -1.0f); BITS(0xC00) = 0;
            if (animate) {
                selected_14 = WORD(0x22A0) == 11 && WORD(0x22A8) < 42 ? 17 : 11;
                set_hero_animation(0x2B, 4, (f32)selected_14);
                animation_14 = hero_get_slot_object(0);
                if (moby_is_class_71((u8 *)animation_14)) anim_start_blended((u8 *)animation_14, 10, 4, selected_14 + 2);
            }
            goto finish;
        case 0x15:
            if (g_progress_statistics[1].count < 0xFFFF) g_progress_statistics[1].count++;
            if (g_frame_counter > g_progress_statistics[1].maximum) g_progress_statistics[1].maximum = g_frame_counter;
            g_progress_statistics[1].levels = (g_progress_statistics[1].levels | (1u << g_current_map_index)) | 0x80000000u;
            if (g_statistics_table[56].count < 0xFFFF) g_statistics_table[56].count++;
            if (g_frame_counter > g_statistics_table[56].maximum) g_statistics_table[56].maximum = g_frame_counter;
            g_statistics_table[56].levels = (g_statistics_table[56].levels | (1u << g_current_map_index)) | 0x80000000u;
            SHORT(0xBFC) = 3; WORD(0x2300) = 0;
            hero_l00_select_aim_target(14.0f, 0.523598849773407f, -1.0f);
            BITS(0xC0C) = BITS(0xC0C) == 0;
            if (animate) {
                selected_15 = PTR(0x2290)[0x43] == 0x1A ? 3 : 10;
                if (WORD(0x22A0) == 1) selected_15 = 17;
                set_hero_animation(0x1A, 0, (f32)selected_15); hero_select_anim_frame(6, 21);
            }
            goto finish;
        case 0x83:
            SHORT(0xBFC) = 3;
            UpdateHeroAimTarget(64.0f, 0.174532949924469f, 0.349065899848938f);
            if (animate) {
                selected_83 = PTR(0x2290)[0x43] == 0x1A ? 3 : 10;
                if (WORD(0x22A0) == 1) selected_83 = 17;
                set_hero_animation(0x1A, 0, (f32)selected_83);
            }
            goto finish;
        case 0x1F:
            if (WORD(0x1220)) {
                actuator_play_pattern(19);
                if (animate) {
                    set_hero_animation(0x60, 4, -1.0f);
                    anim_start_blended(PTR(0x1220), 3, 4, -1);
                }
                hero_l00_select_aim_target(11.0f, 0.8726646900177002f, -1.0f);
            }
            goto finish;
        case 0x13:
        if (g_statistics_table[10].count < 0xFFFF) g_statistics_table[10].count++;
        if (g_frame_counter > g_statistics_table[10].maximum) g_statistics_table[10].maximum = g_frame_counter;
        g_statistics_table[10].levels = (g_statistics_table[10].levels | (1u << g_current_map_index)) | 0x80000000u;
        {
        s32 *entry = g_hero_state_entries[SHORT(0xBFC)];
        mode = 0; WORD(0x2300) = 0;
        if ((WORD(0x22A0) == 0x13 && (f32)entry[2] > REAL(0xC38)) ||
            (WORD(0x22AC) == 0x13 && WORD(0x1B8) + WORD(0x22A8) < 27)) mode = (entry[1] + 1) % 3;
        }
        SHORT(0xBFC) = mode;
        hero_l00_select_aim_target(5.0f, 0.785398244857788f, 0.785398244857788f);
        if (animate) {
            current = 0;
            if (mode == 0) selected_13 = 5;
            else if (mode == 1) { current = 2; selected_13 = 7; }
            else { current = 4; selected_13 = 7; }
            if (WORD(0xBE8) && mode < 2) {
                if (BYTE(0x22C3)) angle_13 = hero_get_direction_angle_delta(VEC(0xBC0), 0);
                else angle_13 = FastDiffRots(REAL(0xBEC), REAL(0x98));
                selected_13 += FloatToInt(angle_13 * 1.5f);
            }
            current /= 2;
            set_hero_animation(mode + 0x17, current, (f32)selected_13);
            animation_13 = hero_get_slot_object(0);
            if (moby_is_class_71((u8 *)animation_13)) anim_start_blended((u8 *)animation_13, mode + 3, current, selected_13);
        }
        goto finish;
        case 0x22:
            if (animate) set_hero_animation(0x2C, 7, 9.0f);
            if (WORD(0x1248) == 12 && PTR(0xBE0)) {
                WORD(0xBE8) = 1;
                REAL(0xBEC) = mat_fast_helper_a(*(f32 *)(PTR(0xBE0) + 0x10) - REAL(0x80),
                                            *(f32 *)(PTR(0xBE0) + 0x14) - REAL(0x84));
                FastVecSub(VEC(0xBC0), PTR(0xBE0) + 0x10, VEC(0x80));
            }
            goto finish;
        }
        goto finish;
    case 0x77:
        WORD(0x229C) = 10; BITS(0x24A0) = 0;
        REAL(0xBF0) = FastAddRotations(REAL(0x98), 3.14159297943f);
        FastVecScale(VEC(0xBD0), VEC(0), -1.0f); REAL(0x1B4) = 0.15f;
        if (!animate) goto finish;
        frames = 8.0f; animation_43 = 0x29; { set_hero_animation(animation_43, 5, frames); goto finish; }
    case 0x16:
        WORD(0x229C) = 7; BITS(0x24A0) = 0;
        hero_scale_saved_vectors(0.5f); actuator_play_pattern(18); HALF(0x20E) = 45;
        COPY_VECTOR(0xF0, 0x120); vec_clamp_length((f32 *)VEC(0xF0), 0.1166666746f);
        hit_44 = part_find_owned_effect_slot(PTR(0x2290), 1, 0);
        if (hit_44) AdjustPlayerHealth(FloatToInt(*(f32 *)(hit_44 + 0x2C)));
        else AdjustPlayerHealth(1);
        HALF(0x1DC) = 77;
        if (!animate) goto finish;
        set_hero_animation(0x10, 3, -3.0f);
        *(f32 *)(PTR(0x2290) + 0x44) = g_hero_state_float_rows[WORD(0xC30)][WORD(0xC34)++];
        goto finish;
    case 0x8C:
        WORD(0x229C) = 7; BITS(0x24A0) = 0; hero_scale_saved_vectors(0.5f);
        BYTE(0x22BC) = 1; actuator_play_pattern(18);
        hit_45 = part_find_owned_effect_slot(PTR(0x2290), 8, 0);
        if (hit_45) AdjustPlayerHealth(FloatToInt(*(f32 *)(hit_45 + 0x2C)));
        else AdjustPlayerHealth(1);
        HALF(0x1DC) = 77;
        if (!animate) goto finish;
        set_hero_animation(0x96, 1, -3.0f);
        *(f32 *)(PTR(0x2290) + 0x44) = g_hero_state_float_rows[WORD(0xC30)][WORD(0xC34)++];
        goto finish;
    case 0x3E:
        WORD(0x229C) = 15; BITS(0x24A0) = 0;
        if (!WORD(0x640)) {
            if (PTR(0x6C4)) { AdjustPlayerHealth(FloatToInt(*(f32 *)(PTR(0x6C4) + 0x2C))); PTR(0x6C4) = 0; }
            else AdjustPlayerHealth(1);
        }
        hero_play_sound(20, 0);
        if (WORD(0x24CC) < 1) {
            angle_53 = FastAddRotations(mat_fast_helper_a(REAL(0xF0), REAL(0xF4)), 3.14159297943f);
            angle_53 = FastAddRotations(angle_53, math_random_signed_float_range(0.523598849774f, 0.610865294933f));
            REAL(0x120) = math_fast_sin_or_cos_a(angle_53) * REAL(0x644) * 0.7f;
            REAL(0x124) = math_fast_sin_or_cos_b(angle_53) * REAL(0x644) * 0.7f; REAL(0x128) = 0.075f;
            if (WORD(0x640) > 15 && WORD(0x24CC) < 2) WORD(0x24CC) = 2;
            PTR(0x2290)[0xA8] = 255; hero_l04_set_move_state(0x16, 1); HALF(0x1F4) = 150; HALF(0x1D0) = 70;
            return 0;
        }
        HALF(0x1DC) = 77; REAL(0x69C) = 0.041666667908430099f;
        if (REAL(0x680) > 0.0416666679084f) REAL(0x680) = 0.0416666679084f;
        BITS(0x674) = 0; vec_clear_128((TI128 *)VEC(0xF0)); vec_clear_128((TI128 *)VEC(0x110));
        REAL(0xF8) = 0.1833333373f;
        if (!animate) goto finish;
        frames = -3.0f; animation_53 = 16; { set_hero_animation(animation_53, 2, frames); goto finish; }
    case 0x1C:
        WORD(0x229C) = 9; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 10.0f); goto finish;
    case 0x1D:
        BITS(0x24A0) = 0x51; WORD(0x229C) = 0;
        if (math_l00_return_argument(PTR(0x2290)[0x42]) == hero_get_weapon_animation_id(0)) goto finish;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 5.0f); goto finish;
    case 0x1E:
        WORD(0x229C) = 9; BITS(0x24A0) = 0;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 10.0f); goto finish;
    case 0x6F:
        WORD(0x229C) = 9; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        cancel_hero_item_animation();
        if (!animate) goto finish;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 10.0f); goto finish;
    case 0x26:
        WORD(0x229C) = 8; BITS(0x24A0) = 0;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, 10.0f); goto finish;
    case 0x31:
        WORD(0x229C) = 9; BITS(0x24A0) = 0; BYTE(0x22B7) = 1;
        BYTE(0x22BD) = 1; BYTE(0x22BC) = 1; level_release_slot_list((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x1A30));
        if (!animate) goto finish;
        set_hero_animation(hero_get_weapon_animation_id(0), 0, -1.0f); goto finish;
    case 0x75:
        WORD(0x229C) = 9; BITS(0x24A0) = 0; BYTE(0x22B7) = 1; BYTE(0x22BC) = 1;
        vec_clear_128((TI128 *)VEC(0xF0));
        if (!animate) goto finish;
        set_hero_animation(11, 0, -1.0f); goto finish;
    case 0x60: case 0x61:
        WORD(0x229C) = 24; BYTE(0x22BC) = 1;
        level_release_slot_list((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x1A30)); cancel_hero_item_animation();
        if (animate) set_hero_animation(hero_get_weapon_animation_id(0), 0, -1.0f);
        goto finish;
    default:
        goto finish;
    }
finish:
    if (wasGliding && !BYTE(0x22B7)) BITS(0x231C) = 1;
    if (SHORT(0x348) == 0 && WORD(0x1298) == 0x13 && WORD(0x2304)) BITS(0x2320) = 1;
    if ((u32)(WORD(0x229C) - 13) > 2 && (WORD(0x2294) != 6 || WORD(0x22A0) != 0x24) &&
        WORD(0x1298) == 20 && WORD(0x2304)) BITS(0x2320) = 1;
    if (WORD(0x229C) == 20) { cancel_hero_item_animation(); BYTE(0x22BC) = 1; }
    if ((!hero_is_in_special_kind_or_mode() || WORD(0x229C) == 18) &&
        (REAL(0x330) < g_hero_l04_state.f148 || WORD(0x229C) == 0)) g_hero_l04_state.i400 = 0;
    if (WORD(0x229C) != WORD(0x22A4)) hero_clear_tracked_slots();
    WORD(0x1B8) = 0;
    BITS(0x1C0) = 0;
    if (WORD(0x229C) != WORD(0x22A4)) BITS(0x1BC) = 0;
    BITS(0x1C4) = 0;
    return 1;
}
