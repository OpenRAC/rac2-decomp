#include "names.h"
/* func_L23_0041A3B8: Damosel effect trigger. Kind 0xF objects spawn the burst at
   D_L23_001B3850 along the object's state direction and play sound 0x21; kinds 0x10 and
   0xC, once the timer threshold is reached and the blink mask is full, aim it at arg1 and
   play sound 0x1A (with the explosion) or 0x21. Returns 1 when the object was handled.

   The kind 0xF arm groups its effect in a nonempty one-pass statement, as current RAC1 game
   C does (docs/build/compiler-notes.md, source methods shared with RAC1): its loop notes keep the
   `la` of D_L23_001B3850 ahead of the two frame-address arguments. func_L00_0035F5A0 returns
   int, as its matched definition does. -mno-split-addresses keeps retail's adjacent
   lui/addiu pairs; D_L23_001B3850 is MACRO_ADDR so each use rematerializes its address. */

#include "common.h"


extern float D_L23_001B3728 __attribute__((sda));

extern float D_L23_001B1454 __attribute__((sda));

extern int D_L23_001B3784;

extern char D_L23_001B3850[] MACRO_ADDR;

extern char D_L23_001B3870[];

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecSub(char *, char *, char *);

extern char *directed_shot_create(char *, char *, float *);

extern unsigned char *flying_shot_create_child(char *, char *, char *, int, float);

extern int snd_start_in_slot(int, int, int);

extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int, int, int, char *);

extern void mothership_turn_joints(char *, float, float);

/* Fires the encounter weapon when it is ready: spawns the burst or the explosion shot and plays its sound. Returns 1 if the object was handled. */
int mothership_fire_weapon(char *moby, char *targetPos) {
    char *state = *(char **)(moby + 0x68);
    float tmp;
    float vec[4];
    int kind = *(unsigned char *)(moby + 0x20);

    if (kind != 0xF) {
        if (kind == 0x10 || kind == 0xC) {
            if (D_L23_001B3784 == 0)
                return 0;
        } else
            return 0;
    } else {
        if ((*(unsigned short *)(moby + 0x96) & 3) != 2)
            return 1;
        do {
            vec_scale_to_length((char *)vec, D_L23_001B3870, *(short *)(state + 0x33A) * 0.016666668f);
            tmp = *(float *)(state + 0x300) * 1.5f;
            directed_shot_create(D_L23_001B3850, (char *)vec, &tmp);
        } while (0);
        snd_start_in_slot(0x21, 0, 0);
        return 1;
    }
    if (!(D_L23_001B3728 >= D_L23_001B1454))
        return 1;
    mothership_turn_joints(moby, 2.0f, 2.0f);
    if (*(unsigned char *)(moby + 0x20) == 0x10) {
        int m = *(short *)(state + 0x336);
        if ((*(unsigned short *)(moby + 0x96) & ((1 << (9 - m)) - 1)) != ((1 << (9 - m)) - 1))
            return 1;
        FastVecSub((char *)vec, targetPos, D_L23_001B3850);
        vec_scale_to_length((char *)vec, (char *)vec, *(short *)(state + 0x33C) * 0.016666668f);
        flying_shot_create_child(moby, (char *)vec, D_L23_001B3850, 0, *(float *)(state + 0x304));
        SpawnExplosion(D_L23_001B3850, 0, 2, 3, 2, 2, 0xA, 0, 0.5f, 20.0f, 1, 1, 0, 0);
        snd_start_in_slot(0x1A, 0, 0);
    } else {
        int m = *(short *)(state + 0x334);
        if ((*(unsigned short *)(moby + 0x96) & ((1 << (9 - m)) - 1)) != ((1 << (9 - m)) - 1))
            return 1;
        FastVecSub((char *)vec, targetPos, D_L23_001B3870);
        vec_scale_to_length((char *)vec, (char *)vec, *(short *)(state + 0x33A) * 0.016666668f);
        directed_shot_create(D_L23_001B3850, (char *)vec, (float *)(state + 0x300));
        snd_start_in_slot(0x21, 0, 0);
    }
    return 1;
}
