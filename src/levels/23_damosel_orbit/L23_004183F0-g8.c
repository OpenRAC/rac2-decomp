#include "include_asm.h"
#include "names.h"

/* func_L23_004183F0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B15B4 __attribute__((sda));

extern TI128 D_L23_001B3800 __attribute__((sda));

extern char D_L23_001B3810[16] __attribute__((sda));

extern volatile int D_L23_001B37F0;

extern volatile int D_L23_001B37F4;

extern volatile int D_L23_001B36AC;

extern volatile int D_L23_001B36B0;

extern char *D_L23_00259560[];

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
        D_L23_001B3800 = *(TI128 *)jointPos;
        FastVecScale(D_L23_001B3810, moby + 0xE0, D_L23_001B15B4);
        FastVecAdd(D_L23_001B3810, D_L23_001B3810, *(char **)(state + 0x59C) + 0x10);
        moby_transform_joint_point(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointMatrix);
        FastVecScale((char *)backOffset, (char *)(jointMatrix + 8), -16.0f);
        FastVecAdd((char *)jointPos, (char *)jointPos, (char *)backOffset);
        math_fast_float_d(state + 0x598);
        if (*(int *)(state + 0x598) == 0) {
            *(int *)(state + 0x59C) = 0;
            *(int *)(state + 0x594) = (*(int *)(state + 0x594) + 1) % 4;
            effectA = D_L23_001B37F0;
            if (effectA != 0) {
                moby_mark_spawned(effectA);
                D_L23_001B37F0 = 0;
            }
            effectB = D_L23_001B37F4;
            if (effectB != 0) {
                moby_mark_spawned(effectB);
                D_L23_001B37F4 = 0;
            }
        }
    }
    D_L23_001B36AC = 0;
    objPtr = D_L23_00259560;
    i = 24;
    do {
        i--;
        if (!(*(unsigned short *)(*objPtr + 0x34) & 1))
            D_L23_001B36AC = D_L23_001B36AC + 1;
        objPtr++;
    } while (i >= 0);
    best = 0;
    bestDist = 3000.0f;
    if (D_L23_001B36B0 == 0) {
        for (j = 0; j < 25; j++) {
            char *obj = D_L23_00259560[j];

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
