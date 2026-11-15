#include "include_asm.h"
#include "names.h"
/* Picks the aim target: the indexed one, or the nearest candidate of four kinds (player,
 * two moby lists and a table) within range, and records it in the aim block. */
#include "common.h"

extern int D_001A8CA0 __attribute__((sda));
extern int weapon_is_target_in_range(char *p, char *q, float f12, float f13);
extern float weapon_rate_aim_target(char *object, char *target);

typedef int Vec128_2B3BA8 __attribute__((mode(TI)));

typedef struct {
    Vec128_2B3BA8 position;
    char *target;
    int found;
    int unused;
    int kind;
} Aim_2B3BA8;

typedef struct {
    char pad0[0xD0];
    Vec128_2B3BA8 position;
    char pad1[0x2290 - 0xE0];
    char *moby;
    int state;
} Player_2B3BA8;

extern Player_2B3BA8 g_hero_state;
extern int g_current_game_mode __attribute__((sda));
extern short D_001B1CB0[2] __attribute__((sda));
extern short D_001B1CF0[2] __attribute__((sda));
extern char *D_001B1B5C __attribute__((sda));
extern int D_001A8CD4 __attribute__((sda));
extern char *D_001C13E8[];
extern char *weapon_pick_best_linked_target(char *, int, int *);
extern float *moby_get_private_value_0(char *);
extern void vec_add_transformed_point(char *, char *, float, float, float);

/* Picks what the object should aim at: a chosen target, or the best-rated one among the player, decoys, other objects in a table and a fourth group, and records it. */
int weapon_select_aim_target(char *self, int index, Vec128_2B3BA8 *point, int force, float range, float height)
{
    float origin[4] __attribute__((aligned(16)));
    int kind;
    Aim_2B3BA8 *aim;
    char *best;
    char *mob;
    float best_distance;
    int best_kind;
    int i;

    if ((*(unsigned short *)(self + 0x34) & 0x20) == 0)
        return 0;
    aim = *(Aim_2B3BA8 **)(*(char **)(self + 0x68) + 0xC);
    if (point != 0)
        *(Vec128_2B3BA8 *)origin = *point;
    else
        *(Vec128_2B3BA8 *)origin = *(Vec128_2B3BA8 *)(self + 0x10);
    aim->target = g_hero_state.moby;
    qcopy(&aim->position, &g_hero_state.position);
    aim->kind = 0;
    aim->found = 0;
    if (force == 0) {
        if (g_current_game_mode != 0)
            return 0;
        if (g_hero_state.state == 0x6F)
            return 0;
    }
    if (index != -1) {
        mob = weapon_pick_best_linked_target(self, index, &kind);
        if (mob != 0) {
            aim->target = mob;
            aim->found = 1;
            aim->kind = kind;
            if (mob != g_hero_state.moby) {
                float *info;
                qcopy(&aim->position, mob + 0x10);
                info = moby_get_private_value_0(mob);
                if (info != 0) {
                    if (D_001A8CA0 == 0)
                        *(float *)((char *)aim + 8) += info[4];
                    else
                        vec_add_transformed_point(mob, (char *)aim, 0.0f, 0.0f, info[4]);
                }
            }
        }
        return aim->found;
    } else {
        best_distance = 9999999.0f;
        best = 0;
        best_kind = 0;
        mob = g_hero_state.moby;
        if (weapon_is_target_in_range(mob, (char *)origin, range, height)) {
            float distance = weapon_rate_aim_target(self, mob);
            if (distance < best_distance) {
                best = mob;
                best_distance = distance;
                best_kind = 1;
            }
        }
        for (i = 1; i <= D_001B1CB0[0]; i++) {
            mob = D_001B1B5C + (D_001B1CB0[i] << 8);
            if (mob != 0 && *(short *)(mob + 0xAA) == MOBY_CLASS_DECOY
                && *(unsigned char *)(mob + 0x20) != 0xFE
                && *(unsigned char *)(mob + 0x20) != 0xFD
                && *(unsigned char *)(mob + 0x20) == 3
                && weapon_is_target_in_range(mob, (char *)origin, range, height)) {
                float distance = weapon_rate_aim_target(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 2;
                }
            }
        }
        for (i = 0; i < D_001A8CD4; i++) {
            mob = D_001C13E8[i];
            if (weapon_is_target_in_range(mob, (char *)origin, range, height)) {
                float distance = weapon_rate_aim_target(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 3;
                }
            }
        }
        for (i = 1; i <= D_001B1CF0[0]; i++) {
            mob = D_001B1B5C + (D_001B1CF0[i] << 8);
            if (mob != 0 && *(short *)(mob + 0xAA) == MOBY_CLASS_DARK_SHEEP
                && *(unsigned char *)(mob + 0x20) != 0xFE
                && *(unsigned char *)(mob + 0x20) != 0xFD
                && weapon_is_target_in_range(mob, (char *)origin, range, height)) {
                float distance = weapon_rate_aim_target(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 4;
                }
            }
        }
        if (best != 0) {
            aim->kind = best_kind;
            aim->found = 1;
            aim->target = best;
            if (best == g_hero_state.moby) {
                qcopy(&aim->position, &g_hero_state.position);
            } else {
                float *info;
                qcopy(&aim->position, best + 0x10);
                info = moby_get_private_value_0(best);
                if (info != 0) {
                    if (D_001A8CA0 != 0)
                        vec_add_transformed_point(best, (char *)aim, 0.0f, 0.0f, info[4]);
                    else
                        *(float *)((char *)aim + 8) += info[4];
                }
            }
        }
    }
    return aim->found;
}
