#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *g_entity_base __attribute__((sda));

extern u16 *g_trail_group_id_lists[];

/* The walk below reads the group count and one word through $gp; the group table of id lists is
   absolute, and the entity base (D_L26_001B1C1C above, through $gp) is the bare `lui`/`lw` pair
   here, a second name sized over 8 bytes with `sda` in this -G8 unit. */
extern int g_trail_group_count __attribute__((sda));

extern u8 *D_L26_001B1C1C_1[3] __attribute__((sda));

extern char g_trail_ribbon_template[];

extern int g_trail_effect_word_a __attribute__((sda));

extern int g_trail_effect_word_b;

extern void part_draw_trail_ribbon(void *, int, void *, void *, int, int, int, int, float);

/* For every entity of the object's group, hands six slots of its private state (+0x80 and +0x100,
   the words at +0x190 and +0x194 and the float at +0x198) to the resident effect scheduler,
   together with the level's float template D_L26_002967A0 and the two words D_L26_001B0478 and
   D_L26_001B047C. */
void part_submit_group_trail_effects(u8 *object) {
    u16 *groupIds;
    u8 *entity;
    u8 *state;

    for (groupIds = g_trail_group_id_lists[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= g_trail_group_count && groupIds != 0 &&
         ((groupIds != 0 && (short)groupIds[-1] >= 0) || groupIds == g_trail_group_id_lists[object[0x21]]);
         groupIds++) {
        entity = D_L26_001B1C1C_1[0] + ((*groupIds & 0x7FFF) << 8);
        if (entity == 0)
            break;
        state = *(u8 **)(entity + 0x68);
        part_draw_trail_ribbon(g_trail_ribbon_template, 6, state + 0x80, state + 0x100, *(int *)(state + 0x194),
                      *(int *)(state + 0x190), g_trail_effect_word_a, g_trail_effect_word_b, *(float *)(state + 0x198));
    }
}

/* Walks the record's live list and flags every entry whose id matches. */
/* func_L26_003DC128 is defined in L02_003CE9A8-g8.c. */

/* func_L26_003DBE18: while object[0x20] is 0 it seeds the private state (constants, the
   func_002B0360 sample of the position minus 1.5, and D_L26_001B05D8 degrees as radians with a
   random sign); then, when func_00282E48(position, D_L26_001B8B80) is below 24, it calls
   func_002A93B0 and sets object[0x6F] to 0x16, runs its per-frame helpers and returns 1 once the
   private byte +0x2E is 2. */
extern float g_flying_creature_turn_degrees __attribute__((sda));
extern unsigned short g_flying_creature_value_a __attribute__((sda));
extern unsigned short g_flying_creature_value_b;
extern float g_hero_l26_origin[4];
extern float gravity_get_center_distance(char *);
extern int math_random_int_below(int);
extern void enemy_spawn_child_parts(char *, char **, int, int);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void anim_start_blended(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void moby_l26_set_group_alert_flag(void *);
extern int weapon_select_aim_target(void *, int, void *, int, float, float);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(char *, char *, int);
extern void group_destroy_attached_parts(char *, char *);

/* Sets up a flying creature on its first frame. Each frame after that it reacts to the hero being
   close, updates its movement and returns 1 once it is finished and should be removed. */
int flying_creature_update_state(unsigned char *object) {
    char *private = *(char **)(object + 0x68);
    float height;
    float turn;
    if (object[0x20] == 0) {
        *(int *)(private + 0x98) = 3;
        *(float *)(private + 0x80) = 1.0f;
        private[0x60] = 7;
        *(float *)(private + 0x84) = 0.8f;
        *(float *)(private + 0x8C) = 0.15f;
        height = gravity_get_center_distance((char *)object + 0x10) - 1.5f;
        turn = g_flying_creature_turn_degrees;
        *(float *)(private + 0x100) = 1.0f;
        turn *= 0.017453294f;
        *(float *)(private + 0x90) = height;
        *(float *)(private + 0x104) = 0.5f;
        {
            int flip = math_random_int_below(2);
            float angle = turn;
            if (flip) angle = -angle;
            *(float *)(private + 0x1DC) = angle;
        }
        *(unsigned short *)(private + 0x1E2) = g_flying_creature_value_a;
        *(unsigned short *)(private + 0x1E4) = g_flying_creature_value_b;
        private[0x2E] = 1;
        *(unsigned short *)(object + 0x34) |= 0x100;
        if (*(float *)(private + 0x20) == 0.0f) {
            *(short *)(private + 0x24) = 3;
            *(float *)(private + 0x20) = 3.0f;
        }
        enemy_spawn_child_parts((char *)object, (char **)(private + 0x270), 0, 2);
        moby_set_state(object, 1, 0);
        if (object[0x43]) anim_start_blended(object, 0, 0, 0);
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_hero_l26_origin) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 0x16;
    }
    if (moby_apply_damage_to_object(object, private + 0x50, 0)) moby_l26_set_group_alert_flag(object);
    *(short *)(private + 0x224) = weapon_select_aim_target(object, *(int *)(private + 0x210), 0, 0, 16.0f, 0.0f);
    matrix_from_basis_rows(private + 0x230, object + 0xC0);
    cam_compute_view_direction((char *)object + 0x10, private + 0x260, 0);
    if ((unsigned char)private[0x2E] == 2) {
        group_destroy_attached_parts((char *)object, private + 0x270);
        return 1;
    }
    return 0;
}
