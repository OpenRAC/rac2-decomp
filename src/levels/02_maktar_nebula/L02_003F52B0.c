#include "common.h"

/* Prefix view of the effect-position field; not a complete global layout. */
typedef struct { char pad[0xB0]; float effect_position[4]; } EffectPositionView;
extern EffectPositionView D_00189E20;
/* Keep the destination address as the assembler's absolute-address macro. */
extern char D_L02_001B3210[] __attribute__((sda));
extern char *D_L02_001AD410 __attribute__((sda));
extern void func_L02_003F5390(char *);
extern void func_L02_003F54D8(char *);
extern void func_L02_003F56C0(char *);
extern void func_L02_003F5710(char *);
extern void func_002833B8(char *, float);
extern void func_002A7750(u8 *, s32, s32);

/* Updates this actor: sets up a fixed point and its camera on the first frame, then runs its per-frame checks. */
void func_L02_003F52B0(char *moby) {
    switch (*(u8 *)(moby + 0x20)) {
    case 0: {
        EffectPositionView *heroBlock = &gHeroState;

        float *source;
        char *dest;
        heroBlock->effect_position[1] = 200.0f;
        heroBlock->effect_position[0] = 500.0f;
        heroBlock->effect_position[2] = 500.0f;
        heroBlock->effect_position[3] = 1.0f;
        source = heroBlock->effect_position;
        dest = D_L02_001B3210;
        qcopy(dest, source);
        *(u8 *)(moby + 0x30) = 0xFF;
        CollectMatchingRecordIndices(moby);
        set_scale_matrix(D_L02_001AD410 + 0x40, 1.0f);
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1:
        UpdateSwayingPieces(moby);
        AdvanceActorCycleTimer(moby);
        UpdateHeroHeightZoneFlags(moby);
        break;
    }
}
