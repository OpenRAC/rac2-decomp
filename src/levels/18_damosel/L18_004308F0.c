#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

/* Built with -frac2-hazard-labels (config/cflags.txt). The second `t20 <= 0.0f` test reuses
   the compare its other path already made, so a forward branch reaches the join label
   between that c.le.s and its bc1fl. Retail keeps the label on the hazard nop the assembler
   inserts there; GNU as without the switch moves it behind the nop, and the bc1f at +0xE4
   lands one word late (docs/build/compiler-notes.md, labels in front of the hazard nop). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern u16 *g_condition_target_lists[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));

extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern s32 moby_apply_damage_to_object(u8 *, u8 *, s32);
extern void SetDeathBits(u8 *, s32, s32);
extern s32 math_random_int_below(s32);
extern int part_spawn_damage_debris(u8 *, u8 *, u8 *);
extern u8 *CreateMoby(s32);
extern void func_002A0F48(u8 *);
extern void anim_start_blended(u8 *, s32, s32, s32);
extern void get_moby_color(u8 *, s32 *, s32 *, s32 *);
extern void set_moby_color(u8 *, s32, s32, s32);
extern s32 weapon_select_aim_target(u8 *, s32, s32, s32, float, float);
extern void extermibot_destroy_piece_and_parts(u8 *);
extern void extermibot_release_all_group_pieces(u8 *);
extern void extermibot_set_anim_on_parts(u8 *, s32, s32, s32);
extern s32 extermibot_is_in_attack_state(u8 *);

/* Handles hits on an Extermibot: its damage reactions, its death, the extra part it spawns, and keeping its attached parts sized and placed. */
void extermibot_update_hits(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *hit;
    u8 *otherMoby;
    u16 *idList;
    u8 savedAnim;
    s32 b0;
    s32 b1;
    s32 b2;
    float health;

    hit = part_find_owned_effect_slot(object, 0x10000, 1);
    if (hit != 0) {
        if (*(u8 **)(hit + 0x20) != 0) {
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == MOBY_CLASS_EXTERMIBOT_LEGS || *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0xF9E /* moby class 3998 */)
                *(s32 *)(hit + 0x2C) = 0;
        }
        if ((u8)(object[0x20] - 1) < 2)
            *(s32 *)(hit + 0x2C) = 0;
    }
    savedAnim = object[0x94];
    if (moby_apply_damage_to_object(object, state + 0x50, 0)) {
        if (object[0x94] == 0xD || object[0x94] == 9 || object[0x94] == 0xA || object[0x94] == 0xB ||
            object[0x94] == 0xC || object[0x94] == 5)
            object[0x94] = savedAnim;
        health = *(float *)(state + 0x20);
        if (*(u8 **)(state + 0x7C0) == 0) {
            if (health <= 0.0f) {
                SetDeathBits(object, 0, 3);
                extermibot_destroy_piece_and_parts(object);
                return;
            }
        }
        if (health <= 0.0f && math_random_int_below(7) == 0) {
            *(float *)(state + 0x20) = 8.0f;
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            moby_set_state(object, 0xE, -1);
            *(s16 *)(state + 0x88) = 0;
            state[0x6A] = 0;
        } else {
            extermibot_set_anim_on_parts(object, object[0x43], 0, 3);
        }
        extermibot_release_all_group_pieces(object);
    }
    object[0xA8] = 0xFF;
    if (*(u8 **)(state + 0x188) != 0 && *(s16 *)(*(u8 **)(state + 0x188) + 0xAA) == 0xF59 /* moby class 3929 */) {
        SetDeathBits(object, 0, 3);
        extermibot_destroy_piece_and_parts(object);
    }
    if (*(u8 **)(state + 0x7C0) != 0) {
        part_spawn_damage_debris(*(u8 **)(state + 0x7C0), *(u8 **)(*(u8 **)(state + 0x7C0) + 0x68) + 0x20, state + 0x20);
        if (!(*(u16 *)(*(u8 **)(state + 0x7C0) + 0x7C) & 2) && *(u8 **)(state + 0x7C4) == 0) {
            u8 *newPart = CreateMoby(0xF0C /* moby class 3852 */);
            *(u8 **)(state + 0x7C4) = newPart;
            if (newPart != 0) {
                newPart[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x32) = *(u16 *)(object + 0x32);
                *(long *)(*(u8 **)(state + 0x7C4) + 0x38) = *(long *)(object + 0x38);
                func_002A0F48(*(u8 **)(state + 0x7C4));
                *(s32 *)(*(u8 **)(state + 0x7C4) + 0x98) = 0;
                if ((*(u8 **)(state + 0x7C4))[0x43] != 0x14)
                    anim_start_blended(*(u8 **)(state + 0x7C4), 0x14, 0, 3);
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= 6;
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= *(u16 *)(object + 0x34) & 0x8000;
                *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                    *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
            } else {
                extermibot_destroy_piece_and_parts(object);
            }
        }
        if (*(u8 **)(state + 0x7C0) != 0) {
            get_moby_color(object, &b0, &b1, &b2);
            set_moby_color(*(u8 **)(state + 0x7C0), b0, b1, b2);
        }
    }
    if (*(u8 **)(state + 0x7C4) != 0) {
        get_moby_color(object, &b0, &b1, &b2);
        set_moby_color(*(u8 **)(state + 0x7C4), b0, b1, b2);
    }
    if (*(s16 *)(state + 0x7F4) != -1) {
        *(u16 *)(state + 0x7F6) = 0;
        for (idList = g_condition_target_lists[object[0x21]];
             object[0x21] != 0xFF && object[0x21] <= g_max_l18_group_index[0] && idList != 0 &&
             ((idList != 0 && (s16)idList[-1] >= 0) || idList == g_condition_target_lists[object[0x21]]);
             idList++) {
            otherMoby = g_moby_l18_table[0] + ((*idList & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (extermibot_is_in_attack_state(otherMoby))
                *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F6) + 1;
        }
    } else {
        *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F4);
    }
    if (*(float *)(object + 0x18) < 90.0f ||
        (*(float *)(state + 0x800) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x800)))
        extermibot_destroy_piece_and_parts(object);
    if (state[0x2E] == 2)
        extermibot_destroy_piece_and_parts(object);
    if (*(float *)(state + 0x20) <= 0.0f) {
        if (object[0x20] != 0xD)
            extermibot_destroy_piece_and_parts(object);
    }
    *(s32 *)(state + 0x79C) =
        weapon_select_aim_target(object, *(s32 *)(state + 0x790), 0, 0, *(float *)(state + 0x794), 0.0f);
    if (object[0x20] < 4) {
        if (object[0x20] != 3)
            return;
        if (object[0xBC] == 0)
            return;
    }
    if (*(float *)(state + 0x7E8) < 1.5f) {
        *(float *)(state + 0x7E8) = *(float *)(state + 0x7E8) + 0.01f;
        *(float *)(object + 0x2C) = *(float *)(*(u8 **)(object + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C0) != 0)
            *(float *)(*(u8 **)(state + 0x7C0) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C0) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C4) != 0)
            *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C8) != 0)
            *(float *)(*(u8 **)(state + 0x7C8) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C8) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
    }
}
