#include "include_asm.h"
#include "names.h"

extern float D_L23_001AFAA0 __attribute__((sda));

extern float D_L23_001B13C8 __attribute__((sda));

extern void func_3242D0(int, int, int);

extern void enemy_handle_hit_sparks(char *);

extern void func_31AF00(int, int, char *);

extern void func_2F8EA8(char *, int, float);

extern float func_2F91F0(float, float);

/* Updates the tether glow of an object: starts its effect once, then advances the glow angle each frame. */
void tether_update_glow(char *moby) {
    char *state = *(char **)(moby + 0x68);

    if (*(unsigned char *)(state + 0x371) == 0)
        func_31AF00(*(int *)(state + 0x2A0), 2, state + 0x370);
    func_2F8EA8(state + 0x380, 2, *(float *)(state + 0x3B0));
    *(float *)(state + 0x3B0) = func_2F91F0(*(float *)(state + 0x3B0),
                                            D_L23_001AFAA0 * 0.000290888245f);
}

/* Starts an object: sets its look and size according to its initial state, then runs the shared setup. */
void moby_init_look(char *moby) {
    char *state = *(char **)(moby + 0x68);
    unsigned char kind = *(unsigned char *)(moby + 0x20);

    if (kind == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x100;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(float *)(state + 0x20) = 2000.0f;
        *(short *)(state + 0x24) = 2000;
        *(short *)(moby + 0x7C) = 0x3FF;
        func_3242D0(moby, 1, 0);
        *(unsigned short *)(moby + 0x34) |= 0x4000;
    } else if (kind == 1) {
        float f = D_L23_001B13C8;

        if (f != 0.0f) {
            *(float *)(state + 0x20) = f;
            *(short *)(state + 0x24) = f;
        }
        func_3242D0(moby, 2, 0);
    }
    enemy_handle_hit_sparks(moby);
}

extern int D_L23_001B36B0;

extern float D_L23_001AFAB4 __attribute__((sda));

extern char g_hero_position[];

extern void FastVecSub(char *out, char *a, char *b);

extern void vec_scale_to_length(char *out, char *in, float length);

extern float FastVecDot(char *a, char *b);

/* in state 8, with the flag at 0x001B36B0 clear, the object drawn and the half-word at +0x324 of
   its state set: compares the normalised offset from D_00189EA0 with the vector at +0xC0 of the
   object D_00189EA0 holds at +0x2210, and within the threshold hands back the float at +0x27C */
int weapon_get_targetable_point(char *moby, float *outValue) {
    char *state = *(char **)(moby + 0x68);
    char dir[16];

    if (*(unsigned char *)(moby + 0x20) == 8 && D_L23_001B36B0 == 0 &&
        *(unsigned char *)(moby + 0x31) != 0 && *(short *)(state + 0x324) != 0) {
        FastVecSub(dir, moby + 0x10, g_hero_position);
        vec_scale_to_length(dir, dir, 1.0f);
        if (FastVecDot(dir, (char *)(*(int *)(g_hero_position + 0x2210) + 0xC0)) <= D_L23_001AFAB4) {
            *outValue = *(float *)(*(char **)(moby + 0x68) + 0x27C);
            return 1;
        }
    }
    return 0;
}
