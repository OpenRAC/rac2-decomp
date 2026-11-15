#include "common.h"

typedef struct {
    char pad[0x1E0];
    short state;
    char pad2[0x14E];
    int a, b;
} HandlerState;

extern void func_002A7750(void *, int, int);
extern int func_L00_00324120(void *);
extern void func_002B0C28(int, int, int);
extern int D_00138324[];
extern int D_L19_001A8FB4 __attribute__((sda));
extern HandlerState D_00189E20;
extern char *D_L19_001B9A90[];
extern float D_L19_001B2420;
extern char *D_L19_001B2B0C;
extern float func_002AA2E8(float *, float, float);
extern void func_L00_00303530(int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_002E59F8(int);

/* Per-frame update for a warp pad (class 3804). It shows a prompt near the hero, and when the button is pressed it fades out, moves the hero to the target spot, and fades back in. */
void func_L19_00411EF0(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *target;
    unsigned timer;
    int waiting;
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x30) = 255;
        SetMobyState(moby, 1, -1);
        *(int *)(vars + 0x18) = -1;
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        if (IsCurrentSelectedId(moby)) {
            if (*(int *)(vars + 8) == 0) TryClaimNotice(8, 0x27FA, 1);
            else if (*(int *)(vars + 8) == 1) TryClaimNotice(8, 0x27FC, 1);
            else TryClaimNotice(8, 0x27F9, 1);
            if ((D_00138324[0] & 0x10) && D_L19_001A8FB4 == 8 && gHeroState.state == 0 && *(short *)(D_L19_001B9A90[0]+0x86) != 5) {
                *(u16 *)(moby + 0x96) = 0;
                gHeroState.state = 2;
                SetMobyState(moby, 2, -1);
            }
        }
    }
    if (*(u8 *)(moby + 0x20) == 2) {
        ApproachValue(&D_L19_001B2420, 1.0f, 0.033333335f);
        timer = *(u16 *)(moby + 0x96);
        waiting = timer++ < 0x20;
        *(u16 *)(moby + 0x96) = timer;
        if (!waiting) {
            target = D_L19_001B2B0C + (*(int *)(vars + 4)<<7);
            gHeroState.a = 0;
            gHeroState.b = 0;
            LoadSceneChunk(*(int *)vars, *(int *)(vars + 0x10));
            ResetHeroPositionAndDirection(target + 0x30, target + 0x70, 0, 1);
            D_L19_001B2420 = 1.0f;
            SetMobyState(moby, 3, -1);
        } else gHeroState.state = 2;
    }
    if (*(u8 *)(moby + 0x20) == 3) {
        ApproachValue(&D_L19_001B2420, 0.0f, 0.033333335f);
        if (D_L19_001B2420 <= 0.0f) {
            D_L19_001B2420 = 0.0f;
            SetMobyState(moby, 1, -1);
            if (*(int *)(vars + 0x18) != -1) {
                StopSoundVoice(*(int *)(vars + 0x18));
                *(int *)(vars + 0x18) = -1;
            }
        }
    }
}
