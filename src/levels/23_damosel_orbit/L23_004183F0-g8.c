#include "include_asm.h"
#include "names.h"

/* func_L23_004183F0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float g_gun_direction_scale __attribute__((sda));

extern TI128 g_gun_joint_position __attribute__((sda));

extern char g_gun_aim_offset[16] __attribute__((sda));

extern volatile int g_gun_trail_effect_a;

extern volatile int g_gun_trail_effect_b;

extern volatile int g_enemy_relocate_count;

extern volatile int g_selected_moby;

extern char *g_mothership_crowd_mobys[];

extern void moby_transform_joint_to_world(char *, int, char *);

extern void moby_transform_joint_point(char *, int, char *);

extern void FastVecScale(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);

extern int math_fast_float_d(char *);

extern void moby_mark_spawned(int);

extern int weapon_get_targetable_point(char *, float *);

extern void moby_select_play_anim(char *);

extern void mothership_fire_gun_at_target(char *);

/* Updates the gun: follows its joint, ends the shot when the timer runs out, and picks the nearest visible target to fire at. */
void mothership_update_gun_pick_target(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float backOffset[4];
    float jointPos[4];
    float jointMatrix[16];
    float dist;
    char *best;
    float bestDist;
    char **objPtr;
    int i;
    int j;
    int effectA;
    int effectB;
    int visible;

    if (*(int *)(state + 0x59C) != 0) {
        moby_transform_joint_to_world(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointPos);
        g_gun_joint_position = *(TI128 *)jointPos;
        FastVecScale(g_gun_aim_offset, moby + 0xE0, g_gun_direction_scale);
        FastVecAdd(g_gun_aim_offset, g_gun_aim_offset, *(char **)(state + 0x59C) + 0x10);
        moby_transform_joint_point(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointMatrix);
        FastVecScale((char *)backOffset, (char *)(jointMatrix + 8), -16.0f);
        FastVecAdd((char *)jointPos, (char *)jointPos, (char *)backOffset);
        math_fast_float_d(state + 0x598);
        if (*(int *)(state + 0x598) == 0) {
            *(int *)(state + 0x59C) = 0;
            *(int *)(state + 0x594) = (*(int *)(state + 0x594) + 1) % 4;
            effectA = g_gun_trail_effect_a;
            if (effectA != 0) {
                moby_mark_spawned(effectA);
                g_gun_trail_effect_a = 0;
            }
            effectB = g_gun_trail_effect_b;
            if (effectB != 0) {
                moby_mark_spawned(effectB);
                g_gun_trail_effect_b = 0;
            }
        }
    }
    g_enemy_relocate_count = 0;
    objPtr = g_mothership_crowd_mobys;
    i = 24;
    do {
        i--;
        if (!(*(unsigned short *)(*objPtr + 0x34) & 1))
            g_enemy_relocate_count = g_enemy_relocate_count + 1;
        objPtr++;
    } while (i >= 0);
    best = 0;
    bestDist = 3000.0f;
    if (g_selected_moby == 0) {
        for (j = 0; j < 25; j++) {
            char *obj = g_mothership_crowd_mobys[j];

            visible = !(*(unsigned short *)(obj + 0x34) & 1);
            if (visible && weapon_get_targetable_point(obj, &dist) != 0) {
                if (best == 0) {
                    best = obj;
                    bestDist = dist;
                } else if (dist < bestDist) {
                    best = obj;
                    bestDist = dist;
                }
            }
        }
    }
    if (best != 0)
        moby_select_play_anim(best);
    if (*(int *)(state + 0x590) != 0 && *(int *)(state + 0x598) <= 0)
        mothership_fire_gun_at_target(moby);
}
