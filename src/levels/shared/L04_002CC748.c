#include "common.h"
typedef struct { float v[4]; } RibbonPoint;
typedef struct {
    float vertex[4][4]; unsigned int color[4]; float uv[8]; u64 state[4];
} RibbonPacket;
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void draw_world_quad(void *, int, int);
extern void FastVecCross(void *, void *, void *);

extern void FastVecScale(void *, void *, float);
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern char D_L04_001B9680[];
extern void transform_vector(void *, void *, void *);
extern int is_vector_outside_clip(void *);
extern void ripple_emit_sub_block(int, int);

extern int D_001A8F00[] __attribute__((sda));
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
extern char D_L04_001C3D40[];
extern float fade_get_value(void);
extern float fade_reduce_value(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(f32 *,f32 *,f32 *);
extern void hero_build_relative_point(void *,int,float,float,float);
extern void hero_l04_enter_state(int,int);
extern char *part_find_owned_effect_slot(void *,int,int);
extern void AdjustPlayerHealth(int);
extern void hero_play_sound(int,int);
extern void hero_flatten_push_vector(void *,int,float,float);
extern void cam_scale_view_space_height(void *,void *,float);
#define AB(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define AH(p,o) (*(short *)((char *)(p)+(o)))
#define AI(p,o) (*(int *)((char *)(p)+(o)))
#define AF(p,o) (*(float *)((char *)(p)+(o)))
#define AP(p,o) (*(char **)((char *)(p)+(o)))
typedef union {
    unsigned char b[0x2500];
    short h[0x1280];
    int i[0x940];
    float f[0x940];
    char *p[0x940];
} GroundHero;
#define GROUND_HERO (*(GroundHero *)&D_00189E20)

typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8, field7AC, field7B0, field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290, field2294, field2298, field229C;
} RippleHero;
#define RIPPLE_HERO (*(RippleHero *)&D_00189E20)
extern void STUB_printf(void *, int, int, int, int);
extern void water_select_table_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void func_002FD1B8_ripple(void *, int, int, float, float, float, float) __asm__("func_002FD1B8");
extern int point_in_path_xy(void *, void *, int);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern char D_L04_001ADA00[];
extern char *g_route_path_table[];
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
#define WINT(p,o) (*(int *)((char *)(p)+(o)))
#define WFLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define WPTR(p,o) (*(char **)((char *)(p)+(o)))

extern u32 FastDecTimer(u8 *);
extern void part_kill(void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);

extern void vec_scale_to_length(float *, float *, float);
extern float FastVecDot(void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern float cam_get_view_space_vector_length(void *);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern void cam_set_view_space_height(void *, void *, float);
extern void hero_build_move_impulse(float, float);
extern float ApproachValue(float *, float, float);
extern void hero_approach_speed(float, float);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern void hero_steer_heading(int, float, float, float);
extern void ApproachHeroVelocity(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_start_pose_offset(float, float, float);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int GetCollHitMaterial(void);
extern void hero_resolve_stick_direction(int, float);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern unsigned char D_L04_001B9540[];
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
typedef struct {
    unsigned char pad0[0x20];
    HopVector field20;
    unsigned char pad30[0x68];
    float yaw;
    unsigned char pad9C[0x54];
    HopVector velocity;
    unsigned char pad100[0x60];
    HopVector momentum;
    unsigned char pad170[0x4];
    float flat_speed;
    unsigned char pad178[0x18];
    HopVector move_dir;
    float move_yaw;
    float yaw_rate;
    float yaw_error;
    unsigned char pad1AC[0x4];
    float target_speed;
    float ground_speed;
    int state_timer;
    unsigned char pad1BC[0x164];
    float field320;
    unsigned char pad324[0x24];
    short field348;
    short field34A;
    unsigned char pad34C[0x108];
    float field454;
    unsigned char pad458[0x18];
    HopVector field470;
    HopVector field480;
    unsigned char pad490[0x4];
    float field494;
    unsigned char pad498[0x6];
    unsigned char field49E;
    unsigned char pad49F[0xF];
    short field4AE;
    unsigned char pad4B0[0xC];
    float ledge_jump_speed;
    float high_jump_drift_yaw;
    float takeoff_yaw;
    unsigned char pad4C8[0xC];
    int field4D4;
    float air_target_speed;
    float high_jump_drift_speed;
    unsigned char pad4E0[0x10];
    HopVector field4F0;
    unsigned char pad500[0x20];
    float jump_gravity;
    short field524;
    unsigned char pad526[0x2];
    short field528;
    unsigned char pad52A[0x3];
    unsigned char field52D;
    unsigned char pad52E[0x532];
    HopVector move_impulse;
    unsigned char padA70[0x14];
    float fieldA84;
    unsigned char padA88[0x1B0];
    float anim_frame;
    unsigned char padC3C[0x804];
    HopVector field1440;
    unsigned char pad1450[0x4];
    short field1454;
    unsigned char pad1456[0x2];
    float field1458;
    unsigned char pad145C[0x36];
    unsigned char field1492;
    unsigned char pad1493[0xE01];
    int state;
    unsigned char pad2298[0x4];
    int control_mode;
    unsigned char pad22A0[0x23];
    unsigned char field22C3;
    unsigned char pad22C4[0x1F4];
    float stick_magnitude;
} HopPlayer;
typedef struct {
    unsigned char pad0[0x158];
    float yaw;
    unsigned char pad15C[0x370 - 0x15C];
    HopVector direction;
} HopSavedState;
#define HOP_SAVED (*(HopSavedState *)D_L04_001B9540)
#define HOP_PLAYER (*(HopPlayer *)&D_00189E20)

extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);

typedef struct {
    u32 unknown;
    s32 data_offset;
    s32 length;
    s32 extra;
} PackedHeaderCountView;


typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 g_hero_state;
extern void math_update_wrapped_angle_offset(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
extern void moby_scale_owner_words_by_angles(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
/* Starts the hero's turn-and-sway animation when in the matching state. */
void hero_start_turn_sway_anim(void) {
    if (g_hero_state.field2294 != 0x7C)
        return;
    math_update_wrapped_angle_offset(g_hero_state.field2290, &g_hero_state.field7A8, &g_hero_state.field7AC,
                  0.3f, 0.116355299949646f, -1.0f);
}

/* Starts the second hero sway animation when in the matching state. */
void hero_start_second_sway_anim(void) {
    if (g_hero_state.field2294 != 0x7C)
        return;
    moby_scale_owner_words_by_angles(g_hero_state.field2290, &g_hero_state.field7B0, &g_hero_state.field7B4,
                  0.174532949924469f, 0.02617994323372841f, 0.03490659222006798f);
}

/* Check the hero's surface contact and optionally apply its movement impulse. */
int hero_check_surface_contact(int update) {
    char *surfaceEntry, *surfaceMoby;
    HopVector delta;
    int isSpecial;
    float impulseAmount;

    if (GROUND_HERO.i[0x229C / 4] == 20) return 0;
    if (GROUND_HERO.i[0x229C / 4] == 7) return 0;
    if (GROUND_HERO.i[0x2294 / 4] == 0x31) return 0;
    if (GROUND_HERO.h[0x1DC / 2]) return 0;
    if (D_001A8F00[0]) return 0;
    GROUND_HERO.i[0x249C / 4] = 0;
    surfaceMoby = GROUND_HERO.p[0x2290 / 4];
    if (AB(surfaceMoby, 0xA8) == 255) return 0;
    surfaceEntry = D_L04_001C3D40 + AB(surfaceMoby, 0xA8) * 64;
    if (AP(surfaceEntry, 0x38) != surfaceMoby) return 0;
    if (!(AI(surfaceEntry, 0x24) & 9)) return 0;
    if (AF(surfaceEntry, 0x2C) != 0.0f) {
        D_001A7A33 = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && !GROUND_HERO.b[0x22B4]) {
        AF(surfaceEntry, 0x2C) = fade_reduce_value(AF(surfaceEntry, 0x2C));
        if (AF(surfaceEntry, 0x2C) == 0.0f) return 0;
    }
    GROUND_HERO.p[0x249C / 4] = AP(surfaceEntry, 0x20);
    if (!update) return 1;
    hero_clear_tracked_slots();
    isSpecial = 0;
    if (AI(surfaceEntry, 0x30) & 1) {
        qcopy(&delta, surfaceEntry + 0x10);
        if (AF(surfaceEntry, 0x1C) == 5627.925f) isSpecial = 1;
    } else if (AP(surfaceEntry, 0x20)) {
        FastVecSub(delta.f, (float *)(GROUND_HERO.b + 0x80),
                     (float *)(AP(surfaceEntry, 0x20) + 0x10));
    } else {
        hero_build_relative_point(&delta, 0, -1.0f, 0.0f, 0.0f);
    }
    if (!GROUND_HERO.b[0x22B4]) {
        char *surfaceMoby = GROUND_HERO.p[0x249C / 4];
        if (surfaceMoby && (AH(surfaceMoby, 0xAA) == 0x4EB /* moby class 1259 */ || AH(surfaceMoby, 0xAA) == 0x558 /* moby class 1368 */)) {
            hero_l04_enter_state(0x7D, 1);
            return 1;
        }
        if ((GROUND_HERO.i[0x2294 / 4] == 1 ||
             GROUND_HERO.i[0x2294 / 4] == 0x1D || GROUND_HERO.i[0x1500 / 4]) &&
            !(AI(surfaceEntry, 0x24) & 8)) {
            char *surfaceMoby = part_find_owned_effect_slot(GROUND_HERO.p[0x2290 / 4], 1, 0);
            if (surfaceMoby) AdjustPlayerHealth(FloatToInt(AF(surfaceMoby, 0x2C)));
            if (!GROUND_HERO.i[0x24CC / 4]) hero_l04_enter_state(0x16, 1);
            GROUND_HERO.h[0x1DC / 2] = 0x4D;
            if (!GROUND_HERO.h[0x21C / 2]) GROUND_HERO.h[0x21C / 2] = 0x12;
            hero_play_sound(20, 0);
            return 0;
        }
        if (GROUND_HERO.i[0x229C / 4] == 0x12) hero_l04_enter_state(0x72, 1);
        else if (GROUND_HERO.i[0x229C / 4] == 0x11) hero_l04_enter_state(0x73, 1);
        else if (AI(surfaceEntry, 0x24) & 8) hero_l04_enter_state(0x8C, 1);
        else hero_l04_enter_state(0x16, 1);
        if (GROUND_HERO.i[0x2294 / 4] == 0x8C) {
            qzero(&delta);
        } else {
            impulseAmount = 0.055000003427267075f;
            if (GROUND_HERO.b[0x1497]) impulseAmount = 0.0f;
            hero_flatten_push_vector(&delta, isSpecial, impulseAmount, 0.028333336f);
            if (isSpecial && AB(surfaceEntry, 0x28) == 4)
                cam_scale_view_space_height(&delta, &delta, 2.0f);
        }
    }
    FastVecAdd(GROUND_HERO.b + 0xF0, GROUND_HERO.b + 0xF0, &delta);
    FastVecAdd(GROUND_HERO.b + 0x110, GROUND_HERO.b + 0x110, &delta);
    return 1;
}


/* func_L04_002DB970 is defined in L04_002CC748-collision-g8.c. */

/* func_L04_002DBE70 is defined in L04_002CC748-movement.c. */

/* Per-state airborne steering; shares the hop-velocity state cases with
   rac1-decomp's hero_update_hop_velocity. */
void hero_steer_airborne_by_state(void) {
    float probe_start[4], probe_end[4], yaw, speed, rate;

    if (HOP_PLAYER.state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 16) {
        if (HOP_PLAYER.state_timer >= 55) {
            ApproachValue(&HOP_PLAYER.jump_gravity, 0.0069444444961845875f, 0.0019444444915279746f);
        }
        if (HOP_PLAYER.state_timer < 55) {
            HOP_PLAYER.target_speed = HOP_PLAYER.field454;
        } else {
            HOP_PLAYER.target_speed = 0.05833333730697632f;
        }
        hero_approach_speed(0.012222222983837128f, 0.0125f);
        cam_set_view_space_vector_length(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
        cam_offset_point_by_side_direction(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, HOP_PLAYER.ground_speed);
    } else if (HOP_PLAYER.state == 27) {
        if (HOP_PLAYER.state_timer >= 41) {
            hero_steer_heading(0, 0.04f, 0.2f, 0.2501639127731323f);
            ApproachHeroVelocity(0.0055555556900799274f);
        }
        if (HOP_PLAYER.anim_frame >= 13.0f && HOP_PLAYER.anim_frame <= 30.0f) {
            if (HOP_PLAYER.anim_frame > 27.0f) {
                ApproachValue(&HOP_PLAYER.ledge_jump_speed, 0.0f, 0.002222222276031971f);
            } else {
                ApproachValue(&HOP_PLAYER.ledge_jump_speed, 0.03333333507180214f, 0.002222222276031971f);
            }
        }
        probe_start[1] = 0.0f;
        probe_start[0] = HOP_PLAYER.ledge_jump_speed;
        probe_start[2] = FastVecDot(HOP_PLAYER.velocity.f, HOP_PLAYER.field20.f);
        matrix_mul_vec3(HOP_PLAYER.velocity.f, probe_start, &HOP_PLAYER);
    } else if (HOP_PLAYER.state == 11) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.takeoff_yaw;
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field480.f);
        hero_steer_heading(0, 0.04f, 0.2f, 0.116355299949646f);
        if (HOP_PLAYER.field4D4 != 3) {
            HOP_PLAYER.ground_speed = HOP_PLAYER.air_target_speed;
        } else {
            HOP_PLAYER.ground_speed = 0.0f;
        }
        if (HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.stick_magnitude * 0.0833333358168602f;

            if (drift < 0.03333333507180214f) drift = 0.03333333507180214f;
            ApproachValue(&HOP_PLAYER.high_jump_drift_speed, drift, 0.010277777910232544f);
            HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
        } else if (HOP_PLAYER.field49E && HOP_PLAYER.field4AE < 12) {
            ApproachValue(&HOP_PLAYER.high_jump_drift_speed, 0.0f, 0.002222222276031971f);
        } else {
            ApproachValue(&HOP_PLAYER.high_jump_drift_speed, 0.07f, 0.002222222276031971f);
        }
        if (!HOP_PLAYER.field22C3) {
            HOP_PLAYER.velocity.f[0] = math_fast_sin_or_cos_a(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
            HOP_PLAYER.velocity.f[1] = math_fast_sin_or_cos_b(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
        } else {
            cam_set_view_space_vector_length(probe_start, HOP_PLAYER.field470.f, HOP_PLAYER.high_jump_drift_speed);
            cam_set_view_space_height(probe_start, probe_start, 0.0f);
            cam_set_view_space_vector_length(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
            FastVecAdd(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
        }
        if (!HOP_PLAYER.field22C3 && !HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.air_target_speed * math_fast_sin_or_cos_b(FastDiffRots(HOP_PLAYER.takeoff_yaw, HOP_PLAYER.high_jump_drift_yaw));

            HOP_PLAYER.velocity.f[0] += math_fast_sin_or_cos_a(HOP_PLAYER.takeoff_yaw) * drift;
            HOP_PLAYER.velocity.f[1] += math_fast_sin_or_cos_b(HOP_PLAYER.takeoff_yaw) * drift;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
    } else if (HOP_PLAYER.state == 17) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.field4F0.f[3];
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field4F0.f);
        if (HOP_PLAYER.state_timer >= 10) {
            hero_steer_heading(-1, 0.041999999433755875f, 0.2f, 0.1978040188550949f);
        }
        if (HOP_PLAYER.state_timer >= 9) {
            if (!HOP_PLAYER.field348) {
                HOP_PLAYER.velocity.f[0] = math_fast_sin_or_cos_a(HOP_PLAYER.move_yaw) * 0.08166667073965073f;
                HOP_PLAYER.velocity.f[1] = math_fast_sin_or_cos_b(HOP_PLAYER.move_yaw) * 0.08166667073965073f;
            } else {
                cam_set_view_space_vector_length(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
                vec_scale_to_length(probe_start, HOP_PLAYER.move_dir.f, 0.08166667073965073f);
                FastVecAdd(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
            }
        }
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 0x81 && !D_001A8FF0) {
        hero_steer_heading(0, 0.04f, 0.2f, HOP_PLAYER.field494);
        HOP_PLAYER.ground_speed = 0.0f;
    } else {
        if (HOP_PLAYER.state == 44) {
            yaw = HOP_PLAYER.yaw;
            HOP_PLAYER.yaw_error = math_approach_with_velocity(&yaw, HOP_PLAYER.move_yaw, &HOP_PLAYER.yaw_rate,
                                      0.018f, 0.2f, 0.12217307090759277f, 0);
            {
                float delta = fast_subtract_rotations(yaw, HOP_PLAYER.yaw);

                hero_start_pose_offset(0.0f, 0.0f, delta);
            }
        } else {
            float saved = HOP_PLAYER.move_yaw;

            qcopy(probe_start, HOP_PLAYER.move_dir.f);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.move_yaw = HOP_SAVED.yaw;
                qcopy(HOP_PLAYER.move_dir.f, HOP_SAVED.direction.f);
            }
            hero_steer_heading(0, 0.04f, 0.2f, HOP_PLAYER.field494);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.field1458 = saved;
                qcopy(HOP_PLAYER.field1440.f, probe_start);
                HOP_PLAYER.move_yaw = saved;
                qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field1440.f);
            }
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        rate = 0.0055555556900799274f;
        if (HOP_PLAYER.target_speed < D_001A7DC0 * 0.0033333336468786f) {
            if (HOP_PLAYER.control_mode == 2) {
                float decel = HOP_PLAYER.fieldA84;

                if (HOP_PLAYER.field1492) decel = 0.000047222223947152495f;
                speed = cam_get_view_space_vector_length(HOP_PLAYER.velocity.f);
                ApproachValue(&speed, 0.0f, decel);
                cam_set_view_space_vector_length(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, speed);
                return;
            }
            if (HOP_PLAYER.field34A) {
                rate = 0.003055555745959282f;
            } else if (HOP_PLAYER.field524) {
                rate = 0.0005555555690079927f;
            } else {
                rate = 0.002222222276031971f;
            }
        }
        if (HOP_PLAYER.field528 && HOP_PLAYER.field1492) {
            rate = 0.00013888889225199819f;
            if (HOP_PLAYER.stick_magnitude > 0.9f) {
                BuildOffsetVectorPair(probe_start, probe_end, 0, 0.5f, -1.5f);
                probe_start[0] += math_fast_sin_or_cos_a(HOP_PLAYER.move_yaw) * 0.7f;
                probe_start[1] += math_fast_sin_or_cos_b(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[0] += math_fast_sin_or_cos_a(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[1] += math_fast_sin_or_cos_b(HOP_PLAYER.move_yaw) * 0.7f;
                if (CollLine(probe_start, probe_end, 2, 0, 0) && GetCollHitMaterial() != 7) {
                    HOP_PLAYER.target_speed = 0.0833333358168602f;
                    rate = 0.0027777778450399637f;
                }
            }
            if (HOP_PLAYER.state == 15) {
                hero_resolve_stick_direction(0, 0.0416666679084301f);
                rate = 0.0008333333535119891f;
            }
            if (HOP_PLAYER.field320 > 0.2617994248867035f) {
                HOP_PLAYER.target_speed = 0.0f;
                rate = HOP_PLAYER.field320 * 0.003183098277077079f;
            }
        }
        ApproachHeroVelocity(rate);
    }
}
#undef HOP_PLAYER
#undef HOP_SAVED

#define NOT_SDA __attribute__((section(".data")))

extern int r1_D_0012FCF0 NOT_SDA;

/* rac1-decomp src/core/00118A40.c: func_00118EC0 */
/* Clears a leftover global flag. */
void level_clear_leftover_flag(void) {
    r1_D_0012FCF0 = 0;
}

typedef int L04Quad __attribute__((mode(TI)));

/* the record the level's spawner builds: flag bytes, a halfword, a float,
   two sixteen-byte blocks and the fields that follow them */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u8  pad04[4];
    u8  field08;
    u8  field09;
    u16 field0A;
    f32 field0C;
    L04Quad field10;
    L04Quad field20;
    f32 field30;
    f32 field34;
    u16 field38;
} L04Record;

/* the second half of the record, at +0x20 */
typedef struct {
    u8  pad00[0xC];
    u32 field0C;
    f32 field10;
    f32 field14;
    u16 field18;
} L04RecordTail;

/* the record the level's other spawner builds: the same flag bytes, a word
   and a colour, then a sixteen-byte block and the fields that follow it */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    u32 field0C;
    L04Quad field10;
    u8  pad20[0xC];
    f32 field2C;
    L04Quad field30;
} L04Spawned;

/* the block at +0x30: a sixteen-byte vector and the float inside its last word */
typedef struct {
    L04Quad v;
} L04Vector;

extern void *part_alloc(s32 kind);
extern s32 FloatToInt(f32 value);
extern s32 math_random_int_below(s32 limit);
extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);
extern void FastVecSub(f32 *dst, f32 *a, f32 *b);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;

/* func_L04_0030C4C0 is matched in L04_0030C4C0.c (built with -frac2-qcopy and -g). */

/* Draws a camera-facing ribbon along a polyline, one quad per segment; each point's fourth
   float is its half width.  The first segment uses first_texture, the last one last_texture
   and the others middle_texture. */
void DrawCameraFacingRibbon(RibbonPoint *line, int first_texture, int middle_texture,
                     int last_texture, int count, unsigned int color)
{
    RibbonPacket q;
    RibbonPoint *points;
    float camera[4];
    float cross[4];
    float side[4];
    float camera_delta[4];
    float segment[4];
    float width;
    int i = 0;
    int changed;

    changed = 0;
    qcopy(camera, D_L04_001B9680);
    points = line;
    line = 0;
    gfx_init_quad_packet_state(&q, first_texture, 0, 0x80);
    q.color[3] = color;
    q.color[2] = color;
    q.color[1] = color;
    q.color[0] = color;
    q.uv[0] = 0.0f;
    q.uv[1] = 0.0f;
    q.uv[2] = 1.0f;
    q.uv[3] = 0.0f;
    q.uv[4] = 0.0f;
    q.uv[5] = 1.0f;
    q.uv[6] = 1.0f;
    q.uv[7] = 1.0f;
    FastVecSub(camera_delta, points[0].v, camera);
    FastVecSub(segment, points[1].v, points[0].v);
    FastVecCross(cross, segment, camera_delta);
    width = points[0].v[3];
    vec_scale_to_length(side, cross, width);
    FastVecAdd(q.vertex[0], points[0].v, side);
    FastVecSub(q.vertex[1], points[0].v, side);
    for (i = 1; i < count; i++) {
        FastVecSub(camera_delta, points[i].v, camera);
        FastVecSub(segment, points[i].v, points[i - 1].v);
        FastVecCross(cross, segment, camera_delta);
        width = points[i].v[3];
        vec_scale_to_length(side, cross, width);
        FastVecAdd(q.vertex[2], points[i].v, side);
        FastVecSub(q.vertex[3], points[i].v, side);
        draw_world_quad(&q, 0, 0);
        if (!changed) {
            if (i == count - 2) gfx_init_quad_packet_state(&q, last_texture, 0, 0x80);
            else gfx_init_quad_packet_state(&q, middle_texture, 0, 0x80);
            changed = 1;
        } else if (i == count - 2) {
            gfx_init_quad_packet_state(&q, last_texture, 0, 0x80);
        }
        qcopy(q.vertex[0], q.vertex[2]);
        qcopy(q.vertex[1], q.vertex[3]);
    }
}


ASM_FUNC("asm/levels", func_L04_0030EDE0);

ASM_FUNC("asm/levels", func_L04_0030FA30);

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} MobStruct;

typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 mobs[1];          /* the array the count field bounds */
} MobListStruct;

/* the list of mobs: level 04 has it at 0x001BD380, every level at its own address */
extern MobListStruct ref_L04_0031D630_00;

/* shared callee, named by its catalogue row (04:0031D3C8) */
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *mob);
extern void math_store_angle_update_result(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_002E64A0, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048. */
void level_update_mob_list_by_type(void) {
    s32 i;

    anim_start_startup_animations();
    for (i = 0; i < ref_L04_0031D630_00.count; i++) {
        MobStruct *mob = (MobStruct *)ref_L04_0031D630_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29 /* moby class 3625 */) {
            mob->flags |= 0x800;
        }
        if (mob->type == 0xD54 /* moby class 3412 */) {
            UpdateEquipmentPieces(mob);
        }
        if (mob != 0 && mob->type == 0xFA0 /* TV Screens */ && mob->p68 != 0) {
            math_store_angle_update_result(mob, (void *)((u8 *)mob->p68 + 0xC), 0x80AAAAD2, 0x80396464, 0.0610865355f);
        }
    }
}

ASM_FUNC("asm/levels", func_L04_0032F1D8);

ASM_FUNC("asm/levels", func_L04_0032F340);

ASM_FUNC("asm/levels", func_L04_0032F3C0);

ASM_FUNC("asm/levels", func_L04_0032F62C);

ASM_FUNC("asm/levels", func_L04_0032F994);


/* sched1 hoists the last statement of */
/* Fills in the default settings of a small movement-control block. */
void MoveCtl_Init(char *settings)
{
    *(int *)(settings + 0) = 640;
    *(float *)(settings + 8) = 0.5f;
    *(int *)(settings + 20) = 0;
    *(float *)(settings + 4) = 1.0f;
    *(float *)(settings + 12) = 0.5f;
    *(int *)(settings + 16) = 0;
    *(float *)(settings + 36) = 2.7f;
    *(int *)(settings + 24) = 0;
    *(float *)(settings + 32) = 0.3f;
    *(float *)(settings + 28) = 0.3f;
    *(float *)(settings + 40) = 1.57f;
    *(float *)(settings + 44) = 0.1f;
}

/* func_L04_0033CC00 is defined in L04_002CC748-movement.c. */

/* func_L04_0033D0C0 is defined in L04_0033D0C0.c. */

extern s32 GetFirstMobyInGroup(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u32 *out, u32 value, s32 arg2, s32 arg3);
/* Looks up the object linked to this one and returns it, or 0 if none. */
s32 moby_find_linked_object(u8 *srcObj) {
    u32 out = 0;
    if (GetFirstMobyInGroup(&out, *(u8 *)(srcObj + 0x21), 0, 0) == -1)
        return 0;
    if (out != (u32)srcObj)
        return out;
    if (GetNextMobyInGroup(&out, out, 0, 0) != -1)
        return out;
    return 0;
}


extern void scale_vector(void *buf, u32 value, float scale);
extern void math_fast_helper_a(void *buf, float value);
/* Turns a number into a vector and passes it on with a value. */
void vec_apply_scaled_value(u32 value, float f) {
    u8 buf[16];
    scale_vector(buf, value, 0.0009765625f);
    math_fast_helper_a(buf, f);
}

/* func_L04_00344568 is in L04_002CC748-axis.c. */

extern void copy_matrix_rotation(void *dst, void *src);
extern f32 FastVecDot(void *a, void *b);
extern f32 square_root(f32 x);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern void FastVecCross(void *dst, void *a, void *b);
extern void mat_fast_helper_b(void *dst, void *src);
extern void multiply_matrix(void *a, void *b, void *c);
extern void transform_vector(void *a, void *b, void *c);
extern void mat_get_euler_angles(f32 *src, f32 *out);

/* Copies the caller's matrix into a local one, takes the two aim angles off
   the target vector, springs one of them, and turns the copy by the three
   angles before handing its axes to the caller. */
void mat_aim_with_spring(void *srcMatrix, void *outAngles, void *springVelocity, void *targetVec, f32 springAccel, f32 springDamp, f32 maxStep)
{
    f32 springPos;
    f32 buf0[16];
    f32 buf1[16];
    f32 mat[16];
    f32 vec[4];
    f32 res[4];
    f32 savedRoll;
    f32 pitchAngle;
    f32 yawAngle;
    f32 baseAngle;

    savedRoll = *(f32 *)((u8 *)outAngles + 8);
    springPos = 0.0f;
    copy_matrix_rotation(mat, srcMatrix);
    pitchAngle = FastVecDot(targetVec, mat + 8);
    baseAngle = mat_fast_helper_a(pitchAngle, square_root(1.0f - pitchAngle * pitchAngle));
    FastVecCross(res, targetVec, mat + 8);
    if (res[2] < 0.99f) {
        yawAngle = mat_fast_helper_a(res[0], res[1]);
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = -yawAngle;
        mat_fast_helper_b(buf1, vec);
        multiply_matrix(mat, buf1, mat);
        transform_vector(res, res, buf1);
        pitchAngle = mat_fast_helper_a(res[2], res[0]);
        vec[0] = 0.0f;
        vec[1] = -pitchAngle;
        vec[2] = 0.0f;
        mat_fast_helper_b(buf0, vec);
        multiply_matrix(mat, buf0, mat);
        transform_vector(res, res, buf0);
    } else {
        yawAngle = 0.0f;
        pitchAngle = 0.0f;
    }
    math_approach_with_velocity(&springPos, baseAngle, (f32 *)springVelocity, springAccel, springDamp, maxStep, 0);
    vec[0] = 0.0f;
    vec[1] = 0.0f;
    vec[2] = springPos;
    mat_fast_helper_b(buf1, vec);
    multiply_matrix(mat, buf1, mat);
    vec[1] = pitchAngle;
    vec[2] = 0.0f;
    mat_fast_helper_b(buf0, vec);
    multiply_matrix(mat, buf0, mat);
    vec[1] = 0.0f;
    vec[2] = yawAngle;
    mat_fast_helper_b(buf1, vec);
    multiply_matrix(mat, buf1, mat);
    mat_get_euler_angles(mat, (f32 *)outAngles);
    *(f32 *)((u8 *)outAngles + 8) = savedRoll;
}

typedef struct {
    u8 pad00[0x18E];
    s16 head;
    s32 count;
    u8 pad194[0x13C];
    f32 history[30];
} PadHistory;

extern PadHistory g_pad_state;

/* Returns the float steps entries back from the head of a 30-entry history ring (steps capped
   at the ring's count); RAC1's read_pad_float_history. */
float pad_read_float_history(int steps)
{
    if (g_pad_state.count < steps)
        steps = g_pad_state.count;
    return g_pad_state.history[(g_pad_state.head - steps + 30) % 30];
}

extern s32 func_001163B0(void);
extern void moby_transform_joint_to_world(void *moby, s32 joint, void *out);
/* the level's pointer to the byte the record carries in its second flag byte */
extern u8 *ref_L04_00358868_00[];

/* the block at +0x20 of the record of kind 0x1A: what func_002BE7E8 reads to keep
   the effect on its target or on one of the target's joints */
typedef struct {
    void *target;
    u16 timer;
    s16 joint;
    u32 duration;
    s32 alpha;
} L04Follow;

typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    s32 color;
    u8  seed;
    u8  field09;
    u16 field0A;
    f32 field0C;
    s32 position[4];
    L04Follow follow;
} L04Effect1A;

/* Builds the record of kind 0x1A that follows TARGET for DURATION frames, with COLOR
   and its alpha byte: it starts at the target, or at its joint JOINT moved 0.4 toward
   D_L04_001B9680 when JOINT is not -1. */
L04Effect1A *SpawnJointFollowParticle(void *target, s32 color, u32 duration, u32 joint, f32 value)
{
    L04Effect1A *p = part_alloc(0x1A);

    if (p != 0) {
        L04Follow *f = &p->follow;

        f->target = target;
        f->alpha = color >> 24;
        f->joint = joint;
        f->duration = duration;
        f->timer = duration;
        if ((s16)joint == -1) {
            qcopy(p->position, (u8 *)target + 0x10);
        } else {
            f32 pos[4], dir[4];

            moby_transform_joint_to_world(f->target, (s16)joint, pos);
            FastVecSub(dir, (f32 *)D_L04_001B9680, pos);
            vec_scale_to_length(dir, dir, 0.4f);
            FastVecAdd(p->position, pos, dir);
        }
        p->seed = func_001163B0();
        p->color = color;
        p->field09 = FloatToInt(4.0f) + 0x70;
        p->field03 = 0x48;
        p->field0C = value;
        p->field01 = 0;
        p->field02 = *ref_L04_00358868_00[0];
    }
    return p;
}


extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
/* func_L04_0035F3E0 is defined in L04_0035F3E0-qcopy.c. */

/* Creates a short-lived sparkle effect at a position with a given size. */
void *part_spawn_sparkle(void *spawnPos, void *spawnVel, u32 lifeTime, f32 effectSize) {
    L04Record *newEffect = (L04Record *)(u32)part_alloc(0x5E);
    L04RecordTail *effectTail;
    L04Quad velCopy;

    if ((u32)newEffect != 0) {
        newEffect->field10 = *(L04Quad *)spawnPos;
        effectTail = (L04RecordTail *)((u8 *)newEffect + 0x20);
        newEffect->field09 = (u8)(FloatToInt(2.0f) + 0x40);
        newEffect->field03 = 0x48;
        newEffect->field01 = 0;
        newEffect->field02 = *(u8 *)ref_L04_00362768_00;
        newEffect->field0C = effectSize * 105000.0f;
        newEffect->field08 = (u8)math_random_int_below(0xFF);
        newEffect->field0A = (u16)lifeTime;
        velCopy = *(L04Quad *)spawnVel;
        newEffect->field20 = velCopy;
        effectTail->field0C = 0;
        effectTail->field10 = 0.5f;
        effectTail->field14 = effectSize;
        effectTail->field18 = (u16)(math_random_int_below(2) - 1);
    }
    return (u32)newEffect;
}

/* Creates a fading streak effect at a position, moving in a given direction. */
void *part_spawn_streak(void *spawnPos, void *spawnVel, u32 lifeTime, f32 effectSize) {
    L04Spawned *newEffect = (L04Spawned *)(u32)part_alloc(0x5F);
    L04Vector *velBlock;
    f32 halfVelocity[4];

    if ((u32)newEffect != 0) {
        newEffect->field04 = 0x7F003CFF;
        newEffect->field0C = 0x7F003CFF;
        newEffect->field09 = (u8)(FloatToInt(2.0f) + 0x20);
        newEffect->field03 = 0x48;
        newEffect->field01 = 3;
        velBlock = (L04Vector *)((u8 *)newEffect + 0x30);
        newEffect->field02 = *(u8 *)ref_L04_00362940_00;
        velBlock->v = *(L04Quad *)spawnVel;
        *(f32 *)((u8 *)velBlock + 0xC) = effectSize;
        newEffect->field10 = *(L04Quad *)spawnPos;
        vec_scale_to_length(halfVelocity, (f32 *)velBlock, 0.5f);
        FastVecSub((f32 *)((u8 *)newEffect + 0x20), (f32 *)spawnPos, halfVelocity);
        newEffect->field0A = (u16)lifeTime;
        *(f32 *)((u8 *)newEffect + 0x1C) = 0.005f;
        newEffect->field08 = (u8)(*(u8 *)&newEffect->field0A - 5);
        newEffect->field2C = 1.0f;
    }
    return (u32)newEffect;
}

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;
extern int func_00282978_2a50(void *);
extern void part_kill(void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void func_00282F20_2a50(void *, void *, float);
extern void func_00282CF0_2a50(void *, void *, void *);
extern float IntToFloat(int);
extern int func_00283CF0_2a50(float);

/* Same body as func_002C7620, with this function's own callees. */
/* Moves a streak effect along its direction each frame and fades it out. */
void part_l04_update_streak(char *self) {
    Vec4 buf, offset;
    char *curPos;
    char *velBlock = self + 0x30;
    float ratio;
    int color;

    if (func_00282978_2a50(self + 0xA) != 0) {
        part_kill(self);
        return;
    }
    curPos = self + 0x10;
    buf.word = *(TI128 *)curPos;
    FastVecAdd(curPos, curPos, velBlock);
    *(float *)(velBlock + 8) = *(float *)(velBlock + 8) - *(float *)(velBlock + 0xC);
    ratio = FastVecLength(velBlock);
    func_00282F20_2a50(&offset, velBlock, ratio * 0.4f);
    func_00282CF0_2a50(self + 0x20, curPos, &offset);
    *(float *)(self + 0x2C) = 1.0f;
    if (*(short *)(self + 0xA) < *(unsigned char *)(self + 8)) {
        ratio = IntToFloat(*(short *)(self + 0xA)) / IntToFloat(*(unsigned char *)(self + 8));
        color = (func_00283CF0_2a50(ratio * 127.0f) << 24) | 0x00FFFFFF;
        *(int *)(self + 0xC) = color;
        *(int *)(self + 4) = color;
    }
}

/* func_L04_00363690 is defined in L04_00363690-qcopy.c. */

/* func_L04_00363CA0 is matched in L04_00363CA0.c (built with -frac2-qcopy). */

/* func_L04_00365300 is defined in L04_00365300.c. */

/* func_L04_00378838 is defined in L04_00378838-g8.c (it reads its list through $gp). */

/* func_L04_003A0FC8 is in L04_003A0FC8-g8.c. */


extern void memset(void *dst, s32 value, s32 size);

/* the header of one 0x1190-byte ripple patch */
typedef struct {
    u8 pad00[0x20];
    s32 field20;
    s32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    s32 field44;
} RipplePatch;

/* clears the three grids of every ripple patch and sets the patch's header fields */
void water_clear_ripple_grids(u8 *base, s32 count) {
    s32 i;
    s32 j;
    u8 *mainGrid;
    u8 *auxGrid2;
    u8 *auxGrid3;
    u8 *auxGrid4;
    u8 *auxGrid5;
    u8 *auxGrid6;
    u8 *auxGrid7;
    u8 *smallBlock;
    f32 smallValue;

    for (i = 0; i < count; i++) {
        smallBlock = base + (i * 0x1190 + 0x5D0);
        auxGrid7 = base + (i * 0x1190 + 0x590);
        auxGrid6 = base + (i * 0x1190 + 0x510);
        auxGrid5 = base + (i * 0x1190 + 0x550);
        auxGrid4 = base + (i * 0x1190 + 0x4D0);
        auxGrid3 = base + (i * 0x1190 + 0x490);
        auxGrid2 = base + (i * 0x1190 + 0x450);
        mainGrid = base + (i * 0x1190 + 0x50);
        smallValue = -0.0016f;
        for (j = 0; j < 3; j++) {
            memset(mainGrid, 0, 0x400);
            mainGrid += 0x5C0;
            memset(auxGrid2, 0, 0x40);
            auxGrid2 += 0x5C0;
            memset(auxGrid3, 0, 0x40);
            auxGrid3 += 0x5C0;
            memset(auxGrid4, 0, 0x40);
            auxGrid4 += 0x5C0;
            memset(auxGrid5, 0, 0x40);
            auxGrid5 += 0x5C0;
            memset(auxGrid6, 0, 0x40);
            auxGrid6 += 0x5C0;
            memset(auxGrid7, 0, 0x40);
            auxGrid7 += 0x5C0;
            memset(smallBlock, 0, 0x18);
            smallBlock += 0x5C0;
        }
        {
            RipplePatch *patchHeader = (RipplePatch *)(base + i * 0x1190);

            patchHeader->field30 = 1.5707964f;
            patchHeader->field34 = -1.5707964f;
            patchHeader->field38 = 0.02f;
            patchHeader->field3C = -0.031f;
            patchHeader->field40 = 0.03f;
            patchHeader->field20 = 0;
            patchHeader->field24 = 0;
            patchHeader->field28 = smallValue;
            patchHeader->field2C = smallValue;
            patchHeader->field44 = 0;
        }
    }
}


/* func_L04_0039FEA8 is matched in L04_0039FEA8.c (built with -g). */

/* func_L04_0039FEF0 is matched in L04_0039FEF0-g8.c (built with -G8). */


typedef struct {
    u8 pad00[0x20];
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
} D002A00E8Self;
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);

/* Slides the water texture coordinates a little each frame. */
void water_scroll_texture_coords(D002A00E8Self *waterPatch) {
    f32 scrollXA, scrollYA, scrollXB, scrollYB;
    s32 i;
    waterPatch->field20 = waterPatch->field20 + waterPatch->field28;
    if (waterPatch->field20 > 1.0f)
        waterPatch->field20 = waterPatch->field20 - 1.0f;
    if (waterPatch->field20 < 0.0f)
        waterPatch->field20 = waterPatch->field20 + 1.0f;
    waterPatch->field24 = waterPatch->field24 + waterPatch->field2C;
    if (waterPatch->field24 > 1.0f)
        waterPatch->field24 = waterPatch->field24 - 1.0f;
    if (waterPatch->field24 < 0.0f)
        waterPatch->field24 = waterPatch->field24 + 1.0f;
    waterPatch->field30 = func_30FE40(waterPatch->field30, waterPatch->field38);
    waterPatch->field34 = func_30FE40(waterPatch->field34, waterPatch->field3C);
    scrollXA = waterPatch->field20 + func_30F3A0(waterPatch->field30) * waterPatch->field40;
    scrollYA = waterPatch->field24 + func_30F3B8(waterPatch->field30) * waterPatch->field40;
    scrollXB = waterPatch->field20 + func_30F3A0(waterPatch->field34) * waterPatch->field40;
    scrollYB = waterPatch->field24 + func_30F3B8(waterPatch->field34) * waterPatch->field40;
    for (i = 0; i < 0x5C; i += 2) {
        if (D_002A7D90[i >> 1] == 0) {
            D_002A7A40[i] = D_002A7BC0[i] + scrollXA;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + scrollYA;
        } else {
            D_002A7A40[i] = D_002A7BC0[i] + scrollXB;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + scrollYB;
        }
    }
}

extern void RippleDisturb(u32 a0, u32 a1, void *a2);
/* Passes a water patch to the ripple function with no position. */
void water_start_ripple_patch(u32 ripplePatch, u32 param) {
    RippleDisturb(ripplePatch, param, 0);
}


/* Cull a water grid tile against the near and far clip volumes, then submit it.
 * Adapted from RAC1 cull_and_submit_water_grid_tile (GPL-3.0), itself adapted
 * from Lombyte src/overlays/shared/gameplay/entities/002b8c08.c. */
void water_cull_and_submit_tile(f32 *pos, s32 index, s32 mode) {
    f32 corners[4][4];
    f32 near_clip[4];
    f32 far_clip[4];
    f32 offsets[4][4];
    f32 x_offset, y_offset, x_end, y_end;
    f32 half_x, half_y;
    f32 x, y;
    u32 near_bits, far_bits;
    s32 i, value, row, column;

    if (mode != 0) {
        row = index >> 2;
        column = index & 3;
        half_x = 0.5f * -D_L04_001AD848;
        half_y = 0.5f * -D_L04_001AD84C;
        x_offset = half_x * (f32)column;
        y_offset = half_y * (f32)row;
        y_end = y_offset + half_y;
        x_end = x_offset + half_x;
        offsets[0][1] = y_offset;
        offsets[0][0] = x_offset;
        offsets[1][1] = y_offset;
        offsets[1][0] = x_end;
        offsets[2][0] = x_offset;
        offsets[2][1] = y_end;
        offsets[3][0] = x_end;
        offsets[3][1] = y_end;
        x = pos[0] + D_L04_001AD848;
        y = pos[1] + D_L04_001AD84C;
        corners[0][0] = x + offsets[2][0];
        corners[0][1] = y + offsets[0][1];
        corners[0][2] = pos[2];
        corners[0][3] = 1.0f;
        corners[1][0] = x + offsets[1][0];
        corners[1][1] = y + offsets[1][1];
        corners[1][2] = pos[2];
        corners[1][3] = 1.0f;
        corners[2][0] = corners[0][0];
        corners[2][1] = y + offsets[2][1];
        corners[2][2] = pos[2];
        corners[2][3] = 1.0f;
        corners[3][0] = corners[1][0];
        corners[3][1] = corners[2][1];
        corners[3][2] = pos[2];
        corners[3][3] = 1.0f;
        near_bits = 0;
        far_bits = 0;
        for (i = 0; i < 4; i++) {
            FastVecSub(near_clip, corners[i], (float *)D_L04_001B9680);
            FastVecScale(far_clip, near_clip, 1024.0f);
            FastVecScale(near_clip, near_clip, 1024.0f);
            transform_vector(far_clip, far_clip, D_L04_001B9680 - 0x80);
            transform_vector(near_clip, near_clip, D_L04_001B9680 - 0x40);
            far_bits = (far_bits << 8) | is_vector_outside_clip(far_clip);
            near_bits = (near_bits << 8) | is_vector_outside_clip(near_clip);
        }
        if (mode == 1) {
            if ((near_bits & 0x01010101) == 0x01010101) return;
            if ((near_bits & 0x02020202) == 0x02020202) return;
            if ((near_bits & 0x04040404) == 0x04040404) return;
            if ((near_bits & 0x08080808) == 0x08080808) return;
            if (far_bits == 0) mode = 0;
            if ((near_bits & 0x20202020) == 0x20202020) return;
        } else {
            if ((near_bits & 0x01010101) == 0x01010101) return;
            if ((near_bits & 0x02020202) == 0x02020202) return;
            if ((near_bits & 0x04040404) == 0x04040404) return;
            if ((near_bits & 0x08080808) == 0x08080808) return;
            if ((near_bits & 0x20202020) == 0x20202020) return;
            mode = 0;
        }
    }
    value = (index & 3) * 4 + (index >> 2) * 0x44;
    if (mode != 0) {
        mode = 0xe;
    } else {
        mode = 0xc;
    }
    ripple_emit_sub_block(mode, value);
}

/* Build the eight cardinal and diagonal neighbor indices for each water tile. */
extern float math_fabs(float);

/* Record the neighboring cells of the 16-unit grid. */
void water_link_neighbor_patches(unsigned char *cells, int count)
{
    int i, j;
    for (i = 0; i < count; i++) {
        unsigned char *cell = cells + i * 0x1190;
        cell[0xC] = 255;
        cell[0xE] = 255;
        cell[0xD] = 255;
        cell[0xF] = 255;
        cell[0x10] = 255;
        cell[0x11] = 255;
        cell[0x12] = 255;
        cell[0x13] = 255;
        for (j = 0; j < count; j++) {
            if (i != j) {
                unsigned char *cell = cells + i * 0x1190;
                float dx = *(float *)cell - *(float *)(cells + j * 0x1190);
                float dy = *(float *)(cell + 4) - *(float *)(cells + j * 0x1190 + 4);
                if (math_fabs(dx) < 0.1f) {
                    if (math_fabs(dy - 16.0f) < 0.1f) cell[0xC] = j;
                    if (math_fabs(dy + 16.0f) < 0.1f) cell[0xE] = j;
                } else if (math_fabs(dy) < 0.1f) {
                    if (math_fabs(dx - 16.0f) < 0.1f) cell[0xD] = j;
                    if (math_fabs(dx + 16.0f) < 0.1f) cell[0xF] = j;
                } else if (math_fabs(dx + 16.0f) < 0.1f) {
                    if (math_fabs(dy - 16.0f) < 0.1f) cell[0x11] = j;
                    if (math_fabs(dy + 16.0f) < 0.1f) cell[0x13] = j;
                } else if (math_fabs(dx - 16.0f) < 0.1f) {
                    if (math_fabs(dy - 16.0f) < 0.1f) cell[0x10] = j;
                    if (math_fabs(dy + 16.0f) < 0.1f) cell[0x12] = j;
                }
            }
        }
    }
}


/* Sets the 6-bit tag (bits 24-29) of every word in the state block's sub-array. */
void water_set_tag_bits(u8 *object, u32 value) {
    u8 *state = *(u8 **)(object + 0x98);
    u32 tag;
    u8 *base;
    u32 *p;
    s32 count;
    s32 offset;
    s32 i;

    count = *(s32 *)(state + 0x8) / 4;
    tag = value & 0x3F;
    tag <<= 24;
    offset = *(s32 *)(state + 0xC) / 8;
    base = state + *(s32 *)(state + 0x4) + 0x10;
    p = (u32 *)(base + offset * 8);

    for (i = 0; i < count; i++) {
        p[i] = (p[i] & 0xC0FFFFFF) | tag;
    }
}


/* returns the packed header's signed rounded sixteen-byte block count in word units */
s32 gfx_get_packed_header_block_count(const PackedHeaderCountView *header) {
    s32 fixed = header->extra + 16;
    s32 total = header->data_offset + fixed + header->length;
    return ((total + 15) / 16) * 4;
}

/* func_L04_003A15C0 is in L04_002CC748-water-header.c. */

/* func_L04_003A1868 is in L04_002CC748-lighting-g8.c. */

/* Copies one 16-bit value into each water patch in a list. */
void water_copy_halfword_to_patches(u8 *dst, u16 *src, s32 count) {
    if (count <= 0)
        return;
    dst += 0x1E;
    do {
        *(u16 *)dst = *src;
        src++;
        dst += 0x1190;
        count--;
    } while (count != 0);
}

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */
void water_update_controller(char *self) {
    char *state = WPTR(WPTR(self, 0x28), 0x68);
    float x, y, half, r;

    if (WBYTE(WPTR(self, 0x28), 0xBC) >= WBYTE(state, 0x15)) {
        STUB_printf(D_L04_001ADA00, WSHORT(WPTR(self, 0x28), 0xB2),
                      WSHORT(WPTR(self, 0x28), 0xAA), WBYTE(WPTR(self, 0x28), 0xBC),
                      WBYTE(state, 0x15));
        WBYTE(WPTR(self, 0x28), 0x20) = 2;
        WBYTE(WPTR(self, 0x28), 0xBC) = 0;
        WSHORT(state, 0x16) = 60;
        WBYTE(state, 0x14) ^= 1;
        water_select_table_slot(WPTR(self, 0x28), WINT(self, 0x1C), WINT(self, 0x18));
        if (WINT(state, 0x10) >= 0 && !WBYTE(state, 0x14)) {
            int i;
            for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
                r = math_random_float_range(-4.0f, 4.0f);
                x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
                x += r;
                y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
                func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                     x, y, 1.0f, -0.05f);
            }
        }
    }
    if (WBYTE(state, 0x14)) return;
    if (WINT(state, 0x20) != -1) {
        char *p = g_route_path_table[WINT(state, 0x20)];
        if (point_in_path_xy((char *)&g_hero_state + 0x80, p + 0x10, WINT(p, 0)))
            WFLOAT(&g_hero_state, 0x330) = WFLOAT(WPTR(self, 0x28), 0x18);
    }
    half = (WFLOAT(state, 0) - WFLOAT(state, 4)) * 0.5f;
    WFLOAT(WPTR(self, 0x28), 0x18) =
        WFLOAT(state, 4) + (math_fast_sin_or_cos_a(WFLOAT(state, 8)) * half + half);
    if (RIPPLE_HERO.field229C != 20 && RIPPLE_HERO.field229C != 25 &&
        RIPPLE_HERO.field2294 != 0x39 && RIPPLE_HERO.field2294 != 0x78 &&
        RIPPLE_HERO.field2294 != 0x79)
        WFLOAT(state, 8) = FastAddRotations(WFLOAT(state, 8), WFLOAT(state, 0xC));
    if (WINT(state, 0x10) >= 0 && !math_random_int_below(200)) {
        int i;
        for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
            r = math_random_float_range(-4.0f, 4.0f);
            x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
            x += r;
            y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
            func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                 x, y, 1.0f, -0.05f);
        }
    }
}


extern u32 FastDecTimer(u8 *ptr);
/* Switches the water controller to its next state when its timer runs out. */
void water_advance_controller_state(u8 *self) {
    if (FastDecTimer((u8 *)(*(u32 *)(*(u32 *)(self + 0x28) + 0x68) + 0x16)) != 0)
        *(u8 *)(*(u32 *)(self + 0x28) + 0x20) = 1;
}

/* func_L04_003A1FE0 is matched in L04_002CC748-g8.c (built with -G8). */

/* func_L04_003A21F8 is matched in L04_002CC748-water-g8.c (built with -G8). */

typedef struct {
    u32 value;
    float factor;
    u32 pad[2];
} TblEntry;
typedef struct {
    TblEntry entries[64];
    u32 count;
} Tbl;
extern Tbl D_L04_00231E00;
/* Adds one entry to the water splash table. */
void water_add_splash_entry(u32 value, float factor) {
    D_L04_00231E00.entries[D_L04_00231E00.count].value = value;
    D_L04_00231E00.entries[D_L04_00231E00.count].factor = factor;
    D_L04_00231E00.count++;
}

extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern void part_spawn_spark_puff(void *);
typedef unsigned int B352Quad __attribute__((mode(TI)));
typedef union { B352Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern char *g_hero_moby NOT_SDA;
extern int D_L04_001AC790 __attribute__((sda));
extern Collision D_L04_001BFAC0;
extern Material D_L04_0027B470[];
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

/* Moves a falling object, bounces it off what it hits and spawns the hit effect. */
void falling_l04_debris_update(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L04_0027B470)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L04_001BFAC0;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0 /* Bomb Glove */) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L04_001BFAC0;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L04_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
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
            collision = &D_L04_001BFAC0;
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


/* func_L04_003C3BA0 is matched in L04-particle-emitter-g8.c. */

/* func_L04_003C4050 is matched in L04-particle-render-g8.c. */

/* Initialises particle i of this emitter: a random unit-cube direction, a random
   speed, size and lifetime from the emitter's three ranges, a zero age, the current
   colour, cleared flags and a start delay staggered by the particle's index. */
typedef struct {
    short first;
    u8 pad2[6];
    float life_min;
    float life_max;
    float speed_min;
    float speed_max;
    float size_min;
    float size_max;
} ParticleRanges3C4858;
/* A sixteen-byte record per spawn slot: three floats the level fills in. */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} L04SpawnRecord;

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);

void part_init_from_ranges(void *emitter, s32 i)
{
    ParticleRanges3C4858 *ranges = *(ParticleRanges3C4858 **)((u8 *)emitter + 0x68);
    L04SpawnRecord *rec;
    f32 v;

    v = math_random_signed_float_range(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[i];
    rec->x = v;
    rec->y = math_random_signed_float_range(0.0f, 1.0f);
    rec->z = math_random_signed_float_range(0.0f, 1.0f);
    D_L04_0023CA50[i] = math_random_float_range(ranges->speed_min, ranges->speed_max);
    D_L04_0023CD70[i] = math_random_float_range(ranges->size_min, ranges->size_max);
    D_L04_0023D220[i] = 0.0f;
    D_L04_0023D540[i] = math_random_float_range(ranges->life_min, ranges->life_max);
    D_L04_0023D860[i] = D_L04_001B2E74;
    D_L04_0023D9F0[i] = 0;
    D_L04_0023DB80[i] = (i - ranges->first + 1) * D_L04_001B2E70;
    D_L04_0023D158[i] = 0;
}

/* A sixteen-byte record per spawn slot (L04SpawnRecord, above). */

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;

extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);


/* Sets up one particle with a random direction, speed, size and lifetime. */
void part_init_simple(void *particleEmitter, u32 a1) {
    f32 *params = *(f32 **)((u8 *)particleEmitter + 0x68);
    L04SpawnRecord *rec;
    f32 randX;

    randX = math_random_signed_float_range(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[a1];
    rec->x = randX;
    rec->y = math_random_signed_float_range(0.0f, 1.0f);
    rec->z = math_random_signed_float_range(0.0f, 1.0f);
    {
        f32 speedMin = params[0x11];
        f32 sizeMin = params[0x13];

        D_L04_0023CA50[a1] = math_random_float_range(speedMin, speedMin + 2.0f);
        D_L04_0023CD70[a1] = math_random_float_range(sizeMin, sizeMin + 4.0f);
    }
    D_L04_0023D220[a1] = 0.0f;
    D_L04_0023D540[a1] = math_random_float_range(0.003f, 0.005f);
    D_L04_0023D158[a1] = 1;
}


extern u32 D_L04_001B2E84 __attribute__((sda));

/* adds VALUE to the running total and returns the total as it was before */
u32 math_add_to_running_total(u32 value) {
    u32 old = D_L04_001B2E84;
    D_L04_001B2E84 = old + value;
    return old;
}
