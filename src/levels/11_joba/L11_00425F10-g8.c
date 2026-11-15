#include "common.h"

extern void *g_group_id_lists[];

/* Reached with `lw $a2,0x45AC($gp)`, so this unit is built -G8. */
extern u8 *g_moby_l11_table;

extern s32 D_L11_001AED04;
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern s32 FloatToInt(f32);
extern s32 path_build_route_nodes(void *, s32, void *, s32);
extern void STUB_printf(void *, ...);
extern char D_L11_001B1008[];
extern f32 math_random_signed_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern void moby_set_flag_bit(void *, s32);
/* Void: no direct call reads $v0, and a void definition matches every place. */
extern void moby_set_controller_speed_limits(void *, f32, f32, f32, f32);

extern char D_L11_002BADF8[];
extern char D_L11_001BA8C0[];
extern s32 D_L11_001AED00, D_L11_001B35B8, D_L11_001B30C8;
extern u8 *CreateMoby(s32);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, s32, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void func_002A0F48(void *);
extern void moby_copy_joint_transform_to_object(void *, void *, s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_transform_joint_point(void *, s32, void *);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void func_002A05A8(void *);
extern void copy_matrix3x4(void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, f32);
extern void mat_normalize_columns(void *);
extern void func_002A10E8(void *);
extern void part_spawn_explosion_with_sparks(void *, void *, f32, f32, s32);
extern s32 moby_apply_damage_to_object(void *, void *, s32);
extern void part_l11_spawn_paired_sparks(void *, s32);
extern void gfx_start_color_fade(void *, void *);
extern void MarkGroupClassCF5CF6Members(void *);
extern s32 moby_count_group_not_in_state(s32, s32);
extern s32 hero_check_distance_zones(void *, void *, s32, s32, f32, f32, s32);
extern void SetDeathBits(void *, s32, s32);

/* Initializes linked objects, updates damage, and releases children on removal. */
s32 jobian_lieutenant_update(u8 *object) {
    f32 vectors[16];
    s32 damage;
    u16 *ids;
    u8 *data = *(u8 **)(object + 0x68);
    if (object[0x20] == 0) {
        object[0x30] = 0x80;
        D_L11_001AED04++;
        *(s32 *)(data + 0x5B0) = 0;
        *(void **)(data + 0x18) = data + 0x140;
        *(f32 *)(object + 0x18) = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        *(s32 *)(data + 0x554) = 0;
        *(s32 *)(data + 0x560) = 0;
        *(s32 *)(data + 0x568) = 0;
        data[0x48] = FloatToInt(20.0f);
        data[0x4A] = FloatToInt(14.0f);
        if (*(s32 *)(data + 0x528)) {
            *(s32 *)(data + 0x520) = path_build_route_nodes(object, *(s32 *)(data + 0x524), data + 0x320, 16);
            STUB_printf(D_L11_001B1008, *(s32 *)(data + 0x520));
        }
        if (*(f32 *)(data + 0x298) == 0.0f)
            *(f32 *)(data + 0x298) = math_random_signed_float_range(15.0f, 25.0f) * 0.01745329424738884f;
        else
            *(f32 *)(data + 0x298) *= 0.01745329424738884f;
        if (math_random_int_below(2) == 1) {
            *(u16 *)(object + 0x34) |= 0x8000;
            moby_set_flag_bit(object, 1);
        }
        data[0x70] = 31;
        *(s32 *)(data + 0xA8) = 4;
        data[0x72] = 7;
        data[0x71] = 6;
        data[0x76] = 8;
        *(f32 *)(data + 0x7C) = 0.20000002f;
        *(f32 *)(data + 0x80) = 0.125f;
        *(f32 *)(data + 0x84) = 0.00555555569f;
        *(f32 *)(data + 0x88) = 0.00972222257f;
        *(f32 *)(data + 0x8C) = 0.00416666688f;
        *(f32 *)(data + 0x90) = 0.75f;
        *(f32 *)(data + 0x94) = 0.75f;
        *(s32 *)(data + 0x9C) = 0;
        data[0xCC] = 5;
        data[0xCD] = 10;
        data[0xCE] = 8;
        data[0xCF] = 15;
        data[0xD2] = 6;
        data[0xD3] = 11;
        *(f32 *)(data + 0x10C) = 0.5f;
        *(f32 *)(data + 0xB8) = 0.18f;
        if (*(s32 *)(data + 0x5B8) != -1)
            *(s32 *)(data + 0xDC) = *(s32 *)(data + 0x5B8);
        *(void **)(data + 0x188) = data + 0x2A0;
        *(f32 *)(data + 0x174) = 0.25f;
        *(f32 *)(data + 0x140) = 0.75f;
        *(f32 *)(data + 0x144) = 0.75f;
        *(f32 *)(data + 0x148) = 0.6f;
        *(f32 *)(data + 0x14C) = 0.6f;
        if (*(s32 *)(data + 0x288) != -1)
            *(s32 *)(data + 0x17C) = *(s32 *)(data + 0x288);
        *(f32 *)(data + 0x150) = 1.483530044555664f;
        *(f32 *)(data + 0x16C) = 0.00138888892f;
        *(f32 *)(data + 0x170) = 1.483530044555664f;
        *(f32 *)(data + 0x174) = 1.5f;
        moby_set_controller_speed_limits(object, 0.00152777787f, 0.0458333343f, 0.00116355298f, 0.104719773f);
        data[0x28] = 3;
        data[0x29] = 1;
        *(f32 *)(data + 0x30) = 0.75f;
        *(f32 *)(data + 0x28C) = data[0x34];
        data[0x2E] = 1;
        if (*(s32 *)(data + 0x26C)) {
            moby_set_state(object, 1, 5);
            if (*(s32 *)(data + 0x270) != -1) {
                *(u8 **)(data + 0x274) = g_moby_l11_table + (*(s32 *)(data + 0x270) << 8);
                qcopy_nc(object + 0x10, *(u8 **)(data + 0x274) + 0x10);
                qcopy_nc(object + 0xF0, *(u8 **)(data + 0x274) + 0xF0);
                *(s32 *)(object + 0x98) = 0;
                *(u16 *)(object + 0x34) &= 0xAFFF;
                *(u8 **)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = object;
                *(u8 **)(data + 0x280) = CreateMoby(0x911 /* moby class 2321 */);
                if (!*(u8 **)(data + 0x280)) return 1;
                (*(u8 **)(data + 0x280))[0x30] = object[0x30];
                (*(u8 **)(data + 0x280))[0x31] = 0;
                func_002A0F48(*(u8 **)(data + 0x280));
                qcopy_nc(*(u8 **)(data + 0x280) + 0x10, object + 0x10);
                *(f32 *)(*(u8 **)(data + 0x280) + 0x18) += 0.75f;
                *(u8 **)(data + 0x278) = CreateMoby(0xFF9 /* moby class 4089 */);
                if (!*(u8 **)(data + 0x278)) return 1;
                (*(u8 **)(data + 0x278))[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
                (*(u8 **)(data + 0x278))[0x31] = 1;
                *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
                func_002A0F48(*(u8 **)(data + 0x278));
                moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x278), 1, 0);
                *(s32 *)(data + 0x290) = 0;
            } else {
                STUB_printf(D_L11_002BADF8);
                *(s32 *)(data + 0x26C) = 0;
                moby_set_state(object, 4, 0);
                return 1;
            }
        } else {
            moby_set_state(object, 4, 0);
            if (object[0x43]) anim_start_blended(object, 0, 0, 0);
            if (*(s32 *)(data + 0x540) == 1) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 13) anim_start_blended(object, 13, 0, 0);
            } else if (*(s32 *)(data + 0x540) == 2) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 15) anim_start_blended(object, 15, 5, 0);
            } else if (*(s32 *)(data + 0x540) == 3) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 15) anim_start_blended(object, 15, 0, 0);
            } else if (*(s32 *)(data + 0x54C) != -1) {
                moby_set_state(object, 11, 0);
                if (object[0x43] != 4) anim_start_blended(object, 4, 0, 0);
            }
            *(u8 **)(data + 0x29C) = CreateMoby(0x9AC /* moby class 2476 */);
            if (!*(u8 **)(data + 0x29C)) return 1;
            (*(u8 **)(data + 0x29C))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x29C) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x29C))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x29C) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x29C));
            *(s32 *)(*(u8 **)(data + 0x29C) + 0x98) = 0;
            moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x29C), 3, 0);
            *(u8 **)(data + 0x278) = CreateMoby(0xFF9 /* moby class 4089 */);
            if (!*(u8 **)(data + 0x278)) return 1;
            (*(u8 **)(data + 0x278))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x278))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x278));
            moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x278), 2, 0);
        }
        qcopy_nc(data + 0x110, object + 0x10);
        *(f32 *)(data + 0x120) = 1.0f;
        *(f32 *)(data + 0x12C) = 8.0f;
        *(f32 *)(data + 0x130) = 10.0f;
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, D_L11_001BA8C0) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    if (data[0x2E] == 2) {
        if (*(void **)(data + 0x29C)) {
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        if (*(void **)(data + 0x278)) {
            moby_mark_spawned(*(void **)(data + 0x278));
            *(void **)(data + 0x278) = 0;
        }
        if (*(void **)(data + 0x280)) {
            moby_mark_spawned(*(void **)(data + 0x280));
            *(void **)(data + 0x280) = 0;
        }
        return 1;
    }
    if (*(void **)(data + 0x29C)) moby_copy_joint_transform_to_object(object, *(void **)(data + 0x29C), 3, 0);
    if (*(u8 **)(data + 0x278)) {
        moby_transform_joint_point(object, 2, vectors);
        qcopy_nc(*(u8 **)(data + 0x278) + 0x10, vectors + 12);
        func_002A05A8(*(void **)(data + 0x278));
        func_002A0F48(*(void **)(data + 0x278));
        copy_matrix3x4(*(u8 **)(data + 0x278) + 0xC0, vectors);
        math_apply_axis_rotation_to_quat(*(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xE0, 3.14159298f);
        mat_normalize_columns(*(u8 **)(data + 0x278) + 0xC0);
        func_002A10E8(*(void **)(data + 0x278));
        *(u16 *)(*(u8 **)(data + 0x278) + 0x34) |= 6;
    }
    if (*(f32 *)(data + 0x20) <= 1.0f) {
        if (*(u8 **)(data + 0x29C)) {
            part_spawn_explosion_with_sparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        *(s32 *)(data + 0x290) = 0;
    }
    *(s32 *)(data + 0x290) = 0;
    damage = moby_apply_damage_to_object(object, data + 0x60, 0);
    if (damage) {
        u8 *attacker = *(u8 **)(data + 0x38);
        if (attacker) {
            s32 cls = *(s16 *)(attacker + 0xAA);
            if (cls != 0x47 /* moby class 71 */ && cls != 0xDD9 /* moby class 3545 */ && cls != 0xD1B /* moby class 3355 */ && cls != 0xCE7 /* moby class 3303 */ && cls != MOBY_CLASS_JOBIAN_SAUR_BEAST && cls != 0)
                D_L11_001AED00 = 0;
        }
        if (object[0xBC] == 1)
            (g_moby_l11_table + (*(s32 *)(data + 0x548) << 8))[0x20] = 4;
        if (*(f32 *)(object + 0x48) != 1.0f) *(f32 *)(object + 0x48) = 1.0f;
        if (*(s32 *)(data + 0x290)) {
            moby_transform_joint_to_world(object, 3, vectors);
            part_l11_spawn_paired_sparks(vectors, 8);
        }
        if (damage == 5) {
            *(f32 *)(data + 0xF4) = 0.837758183f;
            *(s32 *)(data + 0xF0) = 0;
            if (*(u8 **)(data + 0x29C)) {
                part_spawn_explosion_with_sparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
                moby_mark_spawned(*(void **)(data + 0x29C));
                *(void **)(data + 0x29C) = 0;
            }
        }
        *(s32 *)(data + 0x290) = 0;
        data[0x57] = 0xD2;
        gfx_start_color_fade(object, data + 0x50);
        if (object[0x95] != 2) MarkGroupClassCF5CF6Members(object);
        if ((u32)(damage - 4) < 2 && D_L11_001B35B8 >= object[0x21] && moby_count_group_not_in_state(object[0x21], -1) >= 2) {
            ids = g_group_id_lists[object[0x21]];
            do {
                u8 *entry = g_moby_l11_table + ((*ids & 0x7FFF) << 8);
                if (*(s16 *)(entry + 0xAA) == 0xCF6 /* moby class 3318 */ && !*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)ids++ >= 0);
        }
    }
    *(s16 *)(data + 0x264) = hero_check_distance_zones(object, data + 0x268, *(s32 *)(data + 0x250), *(s32 *)(data + 0x254), *(f32 *)(data + 0x258), *(f32 *)(data + 0x25C), 0);
    if (object[0x95] != 4) {
        f32 floor = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        *(f32 *)(object + 0x18) -= 0.313333333f;
        if (*(f32 *)(object + 0x18) < floor) *(f32 *)(object + 0x18) = floor;
    }
    if (*(f32 *)(object + 0x18) < 61.0f && D_L11_001B30C8 >= 6) {
        moby_mark_spawned(*(void **)(data + 0x278));
        SetDeathBits(object, 0, 3);
        if (D_L11_001B35B8 >= object[0x21] && moby_count_group_not_in_state(object[0x21], -1) >= 2) {
            u16 *deathIds = g_group_id_lists[object[0x21]];
            do {
                u8 *entry = g_moby_l11_table + ((*deathIds & 0x7FFF) << 8);
                if (!*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)deathIds++ >= 0);
        }
        if (*(u8 **)(data + 0x29C)) {
            part_spawn_explosion_with_sparks(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        D_L11_001AED04--;
        return 1;
    }
    return 0;
}

/* Flags every record of the id list whose class halfword is 0xD07. */
void saur_beast_flag_id_list(u8 *moby) {
    void *list;
    u16 *id_ptr;
    u8 *moby_table;

    if (moby[0x21] == 0xFF)
        return;
    list = g_group_id_lists[moby[0x21]];
    if (list == 0)
        return;
    id_ptr = list;
    moby_table = g_moby_l11_table;
    do {
        u8 *entry = moby_table + ((*id_ptr & 0x7FFF) << 8);

        if (*(s8 *)(entry + 0x20) >= 0 && *(s16 *)(entry + 0xAA) == MOBY_CLASS_JOBIAN_SAUR_BEAST)
            *(s16 *)(*(u8 **)(entry + 0x68) + 0x276) = 1;
    } while (*(s16 *)id_ptr++ >= 0);
}

typedef int TI128 __attribute__((mode(TI)));

/* The flat quad the effect submits: four positions, four colours, four uv
   pairs and the four GS words (primitive, texture, mode, registers). */
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectQuad;

typedef struct {
    TI128 saved;
    EffectQuad quad;
    float a[4];
    float b[4];
    float c[4];
    TI128 corner;
} EffectQuadFrame;

extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern char D_L11_001BA8C0[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L11_001B1138[] __attribute__((sda));
extern float D_L11_001B113C[] __attribute__((sda));

/* The quad between the two end points at +0x230 and +0x240: each side
   is pulled a tenth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted. */
void saur_beast_draw_beam_quad(char *obj, void *q)
{
    EffectQuadFrame quad_frame;
    char *vars;
    int i;

    quad_frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quad_frame.c, vars + 0x230, vars + 0x240);
    FastVecSub(quad_frame.a, vars + 0x230, D_L11_001BA8C0);
    FastVecSub(quad_frame.b, vars + 0x240, D_L11_001BA8C0);
    FastVecCross(quad_frame.a, quad_frame.a, quad_frame.c);
    vec_scale_to_length(quad_frame.a, quad_frame.a, 0.1f);
    FastVecCross(quad_frame.b, quad_frame.b, quad_frame.c);
    vec_scale_to_length(quad_frame.b, quad_frame.b, 0.1f);
    quad_frame.quad.texture = GetEffectTextureDescriptor(7);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = 0x7000000048UL;
    quad_frame.quad.primitive = 0;
    quad_frame.quad.color[0] = quad_frame.quad.color[1] = quad_frame.quad.color[2] = quad_frame.quad.color[3] = 0x2F0000FF;
    for (i = 0; i < 4; i++) {
        quad_frame.quad.uv[i][0] = D_L11_001B1138[i * 2];
        quad_frame.quad.uv[i][1] = D_L11_001B113C[i * 2];
    }
    FastVecSub(&quad_frame.corner, vars + 0x230, quad_frame.a);
    quad_frame.quad.position[0] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x230, quad_frame.a);
    quad_frame.quad.position[1] = quad_frame.corner;
    FastVecSub(&quad_frame.corner, vars + 0x240, quad_frame.b);
    quad_frame.quad.position[2] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x240, quad_frame.b);
    quad_frame.quad.position[3] = quad_frame.corner;
    draw_world_quad(&quad_frame.quad, 0, 0);
}

extern char D_L11_001BA8C0[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L11_001B1138[] __attribute__((sda));
extern float D_L11_001B113C[] __attribute__((sda));

/* The quad between the two end points at +0x230 and +0x240: each side
   is pulled a twentieth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted (then drawn again as the overlay). */
void saur_beast_draw_beam_quad_overlay(char *obj, void *q)
{
    EffectQuadFrame quad_frame;
    char *vars;
    int i;

    quad_frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quad_frame.c, vars + 0x230, vars + 0x240);
    FastVecSub(quad_frame.a, vars + 0x230, D_L11_001BA8C0);
    FastVecSub(quad_frame.b, vars + 0x240, D_L11_001BA8C0);
    FastVecCross(quad_frame.a, quad_frame.a, quad_frame.c);
    vec_scale_to_length(quad_frame.a, quad_frame.a, 0.05f);
    FastVecCross(quad_frame.b, quad_frame.b, quad_frame.c);
    vec_scale_to_length(quad_frame.b, quad_frame.b, 0.05f);
    quad_frame.quad.texture = GetEffectTextureDescriptor(0x13);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = 0x8000000048UL;
    quad_frame.quad.primitive = 0;
    quad_frame.quad.color[0] = quad_frame.quad.color[1] = quad_frame.quad.color[2] = quad_frame.quad.color[3] = 0x2FFFFFFF;
    for (i = 0; i < 4; i++) {
        quad_frame.quad.uv[i][0] = D_L11_001B1138[i * 2];
        quad_frame.quad.uv[i][1] = D_L11_001B113C[i * 2];
    }
    FastVecSub(&quad_frame.corner, vars + 0x230, quad_frame.a);
    quad_frame.quad.position[0] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x230, quad_frame.a);
    quad_frame.quad.position[1] = quad_frame.corner;
    FastVecSub(&quad_frame.corner, vars + 0x240, quad_frame.b);
    quad_frame.quad.position[2] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x240, quad_frame.b);
    quad_frame.quad.position[3] = quad_frame.corner;
    draw_world_quad(&quad_frame.quad, 0, 0);
    quad_frame.quad.texture = GetEffectTextureDescriptor(0x10);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = 0x8000000048UL;
    quad_frame.quad.primitive = 0;
    draw_world_quad(&quad_frame.quad, 0, 0);
}
