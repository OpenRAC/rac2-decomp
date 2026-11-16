#include "names.h"
/* func_PAL_L23_0041F458, the PAL copy of func_L23_0041A3B8: the same C, where rename func_L23_00422540 becomes func_PAL_L23_00427920; rename func_L23_0041BF18 becomes func_PAL_L23_00420FF8; rename func_L23_004280D8 becomes func_PAL_L23_0042D620; rename func_0032C700 becomes func_PAL_L00_003FB330. */
/* func_PAL_L23_0041F458: Damosel effect trigger. Kind 0xF objects spawn the burst at
   D_L23_001B3850 along the object's state direction and play sound 0x21; kinds 0x10 and
   0xC, once the timer threshold is reached and the blink mask is full, aim it at target_pos and
   play sound 0x1A (with the explosion) or 0x21. Returns 1 when the object was handled.

   The kind 0xF arm groups its effect in a nonempty one-pass statement, as current RAC1 game
   C does (docs/build/compiler-notes.md, source methods shared with RAC1): its loop notes keep the
   `la` of D_L23_001B3850 ahead of the two frame-address arguments. func_L00_0035F5A0 returns
   int, as its matched definition does. -mno-split-addresses keeps retail's adjacent
   lui/addiu pairs; D_L23_001B3850 is MACRO_ADDR so each use rematerializes its address. */

#include "common.h"

extern float g_mothership_aim_dot __attribute__((sda));

extern float g_mothership_fire_threshold __attribute__((sda));

extern int g_mothership_line_clear;

extern char g_mothership_shot_origin[] MACRO_ADDR;

extern char g_mothership_aim_direction[];

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecSub(char *, char *, char *);

extern char *directed_shot_create_pal(char *, char *, float *);

extern unsigned char *flying_shot_create_child_pal(char *, char *, char *, int, float);

extern int snd_start_in_slot(int, int, int);

extern char *SpawnExplosion_pal(char *, int, int, int, int, int, int, int, float, float, int, int, int, char *);

extern void mothership_turn_joints_pal(char *, float, float);

int mothership_fire_weapon_pal(char *boss, char *target_pos) {
    char *state = *(char **)(boss + 0x68);
    float shot_scale;
    float shot_vel[4];
    int kind = *(unsigned char *)(boss + 0x20);

    if (kind != 0xF) {
        if (kind == 0x10 || kind == 0xC) {
            if (g_mothership_line_clear == 0)
                return 0;
        } else
            return 0;
    } else {
        if ((*(unsigned short *)(boss + 0x96) & 3) != 2)
            return 1;
        do {
            vec_scale_to_length((char *)shot_vel, g_mothership_aim_direction, *(short *)(state + 0x33A) * 0.020000001f);
            shot_scale = *(float *)(state + 0x300) * 1.5f;
            directed_shot_create_pal(g_mothership_shot_origin, (char *)shot_vel, &shot_scale);
        } while (0);
        snd_start_in_slot(0x21, 0, 0);
        return 1;
    }
    if (!(g_mothership_aim_dot >= g_mothership_fire_threshold))
        return 1;
    mothership_turn_joints_pal(boss, 2.0f, 2.0f);
    if (*(unsigned char *)(boss + 0x20) == 0x10) {
        int blink_level = *(short *)(state + 0x336);
        if ((*(unsigned short *)(boss + 0x96) & ((1 << (9 - blink_level)) - 1)) != ((1 << (9 - blink_level)) - 1))
            return 1;
        FastVecSub((char *)shot_vel, target_pos, g_mothership_shot_origin);
        vec_scale_to_length((char *)shot_vel, (char *)shot_vel, *(short *)(state + 0x33C) * 0.020000001f);
        flying_shot_create_child_pal(boss, (char *)shot_vel, g_mothership_shot_origin, 0, *(float *)(state + 0x304));
        SpawnExplosion_pal(g_mothership_shot_origin, 0, 2, 3, 2, 2, 0xA, 0, 0.5f, 20.0f, 1, 1, 0, 0);
        snd_start_in_slot(0x1A, 0, 0);
    } else {
        int blink_level = *(short *)(state + 0x334);
        if ((*(unsigned short *)(boss + 0x96) & ((1 << (9 - blink_level)) - 1)) != ((1 << (9 - blink_level)) - 1))
            return 1;
        FastVecSub((char *)shot_vel, target_pos, g_mothership_aim_direction);
        vec_scale_to_length((char *)shot_vel, (char *)shot_vel, *(short *)(state + 0x33A) * 0.020000001f);
        directed_shot_create_pal(g_mothership_shot_origin, (char *)shot_vel, (float *)(state + 0x300));
        snd_start_in_slot(0x21, 0, 0);
    }
    return 1;
}
