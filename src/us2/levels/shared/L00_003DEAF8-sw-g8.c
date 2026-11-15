#include "include_asm.h"

#include "common.h"
extern char D_001B27B0[] __attribute__((section(".sdata")));
extern int D_001B27C0 MACRO_ADDR;
extern char *D_001B27CC[] MACRO_ADDR;
extern char *D_001B27CC_gp SDATA(D_001B27CC);
extern int D_001B27C4;
extern int D_001B27C8;
extern float D_001B00F8 __attribute__((sda)), D_001B0108 __attribute__((sda)), D_001B010C __attribute__((sda));
extern int D_001B00FC __attribute__((sda)), D_001B0100 __attribute__((sda));
extern int g_current_game_mode __attribute__((sda));
extern int D_001A8CFC[] MACRO_ADDR;
extern int D_0018C0B4[], D_00138324[];
extern char *D_001AD7EC[] MACRO_ADDR;
extern char *D_001B5390[];
extern char D_001BAFC0[], g_collision_hit[];
typedef struct { char pad[0x2290]; char *target; int state; } PlayerState;
extern PlayerState D_00189E20_9;
extern float D_0022AC90[][2];
extern void moby_forward_position_call(char *, char *, int);
extern void moby_get_facing_direction(char *, char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int CollLine(char *, char *, int, char *, int);
extern int GetCollHitMaterial(void);
extern int ForceClaimNotice(int, int, int);
extern float math_random_angle(void), math_random_signed_float_range(float, float);
extern void func_US2_0029C548(int, void (*)(void));
extern void hud_draw_timer(void), moby_call_setup_b(void), helper_set_active_flag(void);
extern void part_steer_effect_direction(char *, char *, int);
extern void vec_transform_or_copy(char *, char *), shop_trigger_current_state_effect(char *, char *);
extern void vec_add_object_direction_scaled(char *, char *, float);
extern void vec_clear_128(char *);
extern void func_US2_L00_002C4560(int, int);
extern void part_setup_object_effect_entry(char *, char *, char *);
extern void anim_start_blended(char *, int, int, int);
extern void PlayMobySound(int, int, char *);
extern void func_US2_00327AB0(char *), moby_steer_heading_to_target(char *), moby_move_with_friction(char *), moby_find_nearby_same_kind(char *);
extern void snd_play_on_threshold_cross(void);
extern int math_fast_float_d(char *), CollideSweptSphere(char *), weapon_get_group(int);
extern float FastVecLength(char *);
extern void part_spawn_blast_effect_moby(char *, char *, char *, float);
extern void DamageNearbyMobys(char *), table_clear_entry_flag(int), moby_mark_spawned(char *);
extern void gfx_register_final_draw_callback(void (*)(char *), char *), ring_update_if_below_threshold(char *);
extern void copy_matrix_rotation(char *, char *);
extern void mat_get_euler_angles(char *, char *);
extern int moby_transform_point_and_rotation_by_parent(char *, char *, char *, char *, char *, char *);
extern void euler_rotation_basis(char *, char *), part_queue_ground_shadow(char *, float);
extern void hud_draw_timer(void), ref_US2_L00_003DEAF8_00(void), helper_set_active_flag(void);

void func_US2_L00_003DEAF8(char *object)
{
    char oldpos[16], ahead[16], behind[16];
    char *data = *(char **)(object + 0x68);
    PlayerState *player;
    int i, result;
    float (*randoms)[2];
    if ((unsigned char)object[0x20] >= 2) {
        moby_forward_position_call(object, D_001B27B0, 1);
    } else {
        char *p = object + 0x10;
        moby_get_facing_direction(p, D_001B27B0);
    }
    FastVecScale(D_001B27B0, D_001B27B0, -1.0f);
    FastVecScale(ahead, object + 0xE0, D_001B0108);
    FastVecAdd(ahead, object + 0x10, ahead);
    FastVecScale(behind, object + 0xE0, -1.0f);
    FastVecAdd(behind, object + 0x10, behind);
    if (CollLine(ahead, behind, 2, object, 0)) {
        if (GetCollHitMaterial() == 2) {
            FastVecScale(D_001B27B0, D_001BAFC0, 0.0009765625f);
            vec_scale_to_length(D_001B27B0, D_001B27B0, -1.0f);
            *(int *)(D_001B27B0 + 0x14) = 1;
        } else D_001B27C4 = 0;
        if (GetCollHitMaterial() == 6)
            D_001B27C8 = 1;
        else D_001B27C8 = 0;
    } else {
        D_001B27C4 = 0;
        *(int *)(D_001B27B0 + 0x18) = 0;
    }
    ForceClaimNotice(6, 0, 1);
    /* Each case is its own block: the address-taken locals leave their stack slots when the
     * switch ends, and the attachment block below reuses that space. */
    switch ((unsigned char)object[0x20]) {
    case 0: {
        object[0x20] = 1;
        *(int *)(data + 0x18) = 0;
        *(float *)(object + 0x2C) = 0.00025f;
        D_001B27C0 = 1800;
        *(int *)(object + 0x98) = 0;
        randoms = D_0022AC90;
        i = 97;
        do {
            i--;
            (*randoms)[0] = math_random_angle();
            (*randoms)[1] = math_random_signed_float_range(720.0f, 2160.0f) * 0.0002908882452175021f;
            randoms++;
        } while (i >= 0);
        if (D_001A8CFC[0]) func_US2_0029C548(0, hud_draw_timer);
    }
        /* fall through */
    case 1: {
        player = &D_00189E20_9;
        if (player->state == 98 || g_current_game_mode == 2 || player->state == 111 || player->state == 100 || player->state == 99 ||
            player->state == 23 || player->state == 24 || player->state == 129 || player->state == 39) {
            ref_US2_L00_003DEAF8_00();
            object[0x20] = 7;
            helper_set_active_flag();
            *(int *)(data + 0x20) = 0;
            break;
        }
        *(float *)(object + 0x2C) += 0.01f;
        if (*(float *)(object + 0x2C) > 0.0181099995970726f)
            *(float *)(object + 0x2C) = 0.0181099995970726f;
        qcopy(oldpos, object + 0x10);
        FastVecAdd(object + 0x10, object + 0x10, data);
        part_steer_effect_direction(D_001B27CC[0], data, 0);
        vec_transform_or_copy(object + 0x10, object + 0x10);
        shop_trigger_current_state_effect(data, data);
        vec_add_object_direction_scaled(object + 0x10, data, 0.003055555745959282f);
        if (CollLine(oldpos, object + 0x10, 2, object, 0)) {
            char *hitinfo = g_collision_hit;
            char *hit = *(char **)(hitinfo + 0x18);
            if (hit && (hit == player->target || *(short *)(hit + 0xAA) == 0x907)) break;
            qcopy(object + 0x10, hitinfo + 0x20);
            vec_clear_128(data);
            ForceClaimNotice(6, 0, 1);
            func_US2_L00_002C4560(28, 1);
            part_setup_object_effect_entry(object + 0x10, object + 0xF0, object);
            object[0x20] = 2;
            anim_start_blended(object, 1, 0, 10);
            *(int *)(object + 0x48) = 0;
            return;
        }
        break;
    }
    case 2: {
        object[0x20] = 3;
        PlayMobySound(2, 0, object);
        if (D_0018C0B4[0] != 28 || g_current_game_mode == 2) {
            ref_US2_L00_003DEAF8_00();
            object[0x20] = 9;
            *(int *)(data + 0x20) = 0;
        }
        break;
    }
    case 3: {
        func_US2_00327AB0(object);
        moby_steer_heading_to_target(object);
        moby_move_with_friction(object);
        moby_find_nearby_same_kind(object);
        snd_play_on_threshold_cross();
        if (math_fast_float_d((char *)&D_001B27C0)) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        if (D_00138324[0] & 0x20) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        if (D_0018C0B4[0] != 28 || g_current_game_mode == 2) {
            ref_US2_L00_003DEAF8_00();
            object[0x20] = 9;
            *(int *)(data + 0x20) = 0;
        }
        break;
    }
    case 4: {
        struct {
            char start[16], end[16], velocity[16];
            char *owner;
            int flags, mode;
            float radius, friction, elasticity;
            int field48, field4c, enabled, surface, field58;
        } collision;
        qcopy(oldpos, object + 0x10);
        FastVecAdd(object + 0x10, object + 0x10, data);
        vec_add_object_direction_scaled(object + 0x10, data, 0.006111111491918564f);
        vec_transform_or_copy(object + 0x10, object + 0x10);
        shop_trigger_current_state_effect(data, data);
        qcopy(collision.start, oldpos);
        qcopy(collision.end, object + 0x10);
        qcopy(collision.velocity, data);
        collision.radius = 0.2f;
        collision.friction = 0.85f;
        collision.elasticity = 0.75f;
        collision.enabled = 1;
        collision.owner = object;
        collision.flags = 0;
        collision.mode = 0;
        collision.field48 = 0;
        collision.field4c = 0;
        collision.field58 = 0;
        result = CollideSweptSphere((char *)&collision);
        qcopy(object + 0x10, collision.end);
        qcopy(data, collision.velocity);
        if (result == 2) {
            if (weapon_get_group(collision.surface) || collision.surface == 12) {
                object[0x20] = 9;
                *(int *)(data + 0x20) = 10;
            } else {
                object[0x20] = result;
                vec_clear_128(data);
            }
        } else if (FastVecLength(data) > 0.4f) {
            object[0x20] = 9;
            *(int *)(data + 0x20) = 10;
        }
        break;
    }
    case 9: {
        object[0x20] = 5;
        helper_set_active_flag();
    }
        /* fall through */
    case 5: {
        char direction[16];
        if (math_fast_float_d(data + 0x20)) {
            vec_scale_to_length(direction, object + 0xC0, 1.0f);
            part_spawn_blast_effect_moby(object, object + 0x10, direction, *(float *)(object + 0x18));
            PlayMobySound(1, 0, object);
            object[0x20] = 6;
            *(unsigned short *)(object + 0x34) |= 0x41;
            if (D_0018C0B4[0] != 28 || g_current_game_mode == 2) {
                ref_US2_L00_003DEAF8_00();
                *(int *)(data + 0x20) = 0;
            } else *(int *)(data + 0x20) = D_001B0100;
            *(int *)(data + 0x24) = 0;
        }
        break;
    }
    case 6: {
        DamageNearbyMobys(object);
        *(float *)(data + 0x24) += D_001B00F8 * (1.0f / 60.0f);
        if (math_fast_float_d(data + 0x20) && !*(int *)(data + 0x28)) object[0x20] = 8;
        break;
    }
    case 7: {
        if (math_fast_float_d(data + 0x20)) object[0x20] = 8;
        break;
    }
    case 8: {
        if (D_0018C0B4[0] == 28) func_US2_L00_002C4560(0, 1);
        if (*(short *)(D_001B5390[0] + 0x86) == 27) ref_US2_L00_003DEAF8_00();
        D_001B00FC = 0;
        func_US2_0029C548(0, 0);
        table_clear_entry_flag((int)D_001B27CC_gp);
        moby_mark_spawned(object);
        return;
    }
    }
    gfx_register_final_draw_callback(ring_update_if_below_threshold, object);
    if ((unsigned char)object[0x20] >= 2 && D_001AD7EC[0]) {
        char angles[16], adjusted[16], matrix[64];
        copy_matrix_rotation(matrix, object + 0xC0);
        mat_get_euler_angles(matrix, angles);
        moby_transform_point_and_rotation_by_parent(object, D_001AD7EC[0], object + 0x10, angles, object + 0x10, adjusted);
        euler_rotation_basis(object + 0xC0, adjusted);
    }
    part_queue_ground_shadow(object, D_001B010C);
}
