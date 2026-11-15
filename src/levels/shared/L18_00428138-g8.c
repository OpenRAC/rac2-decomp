#include "common.h"
extern int D_L18_001AFBB0;
typedef struct { u8 pad[0x1E0]; s16 guard; u8 pad2[0x20B2]; int mode; } Player;
extern Player D_L18_00189E20;
extern float D_L18_001B1284 __attribute__((sda));
extern float D_L18_001B1280 __attribute__((sda));
extern float D_L18_001B126C __attribute__((sda));
extern u16 D_L18_001B1240 __attribute__((sda));
extern u8 D_L18_001B1308[];
extern float func_00308AD0(void *, void *);
extern void func_003476C8(void *, float, float, float, float);
extern void moby_start_or_forward_anim(void *, int, int, float);
extern void func_00335668(void *, int, int);
extern void func_002C27F0(void *, int);
/* Checks whether the player is close enough for the enemy to notice. If so, it starts the alert move and returns 1. */
int enemy_try_notice_player(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    float range;
    if (D_L18_001AFBB0 || D_L18_00189E20.guard || D_L18_00189E20.mode == 0x6F) return 0;
    range = D_L18_001B1284;
    switch (*(s16 *)(moby + 0xAA)) {
    case 0xEC0 /* moby class 3776 */:
        if (func_00308AD0(moby + 0x10, state + 0x220) < D_L18_001B126C && !*(s16 *)(state + 0x396) && !D_L18_001AFBB0 && D_L18_00189E20.mode != 0x6F) {
            func_003476C8(moby, *(float *)(state + 0x3CC) * 0.00027777778f, *(float *)(state + 0x3C8) * 0.016666668f, *(float *)(state + 0x3DC) * 0.0000048481374f, *(float *)(state + 0x3D8) * 0.00029088824f);
            *(u16 *)(state + 0x392) = D_L18_001B1240;
            moby_start_or_forward_anim(moby, 10, 0, 10.0f);
            func_00335668(moby, 6, -1);
            return 1;
        }
        return 0;
    case 0xED4 /* moby class 3796 */:
        range = D_L18_001B1280;
    case 0xEE1 /* Receiver Bot */:
        if (func_00308AD0(moby + 0x10, state + 0x220) < range && !*(s16 *)(state + 0x396) && !D_L18_001AFBB0 && D_L18_00189E20.mode != 0x6F) {
            moby_start_or_forward_anim(moby, 10, 0, 10.0f);
            func_00335668(moby, 6, -1);
            return 1;
        }
        return 0;
    default:
        func_002C27F0(D_L18_001B1308, *(s16 *)(moby + 0xAA));
        return 0;
    }
}
