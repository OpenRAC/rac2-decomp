#include "common.h"

/* Typed views cover the fields this update reads; unknown fields retain their offsets. */
typedef union {
    u8 b[0x3F4];
    u16 uh[0x1FA];
    s32 i[0xFD];
    float f[0xFD];
    u8 *p[0xFD];
} EnemyStateView;
typedef union {
    s16 h[0x114C];
    s32 i[0x8A6];
} PlayerView;
typedef union {
    u16 uh[0x150];
    u32 ui[0xA8];
} HistoryView;
typedef union {
    u8 b[0x20];
    float f[8];
} PositionView;
extern PlayerView D_00189E20;
extern HistoryView D_0018C360;
/* This flag is save-block byte +0x4F (absolute 0x001A7A47). Keeping its
 * enclosing block preserves the two-instruction load and empty branch slot. */
extern u8 D_001A79F8[] __attribute__((sda));
extern unsigned D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern PositionView D_L18_001B97C0;
extern int D_L18_001AFBB0 __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern int D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B12FC;
extern int func_L18_00427688(void *);
extern void func_0029F338(void *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_002AEC48(void *,void *,int,float,float);
extern int func_002B0ED8(void *,void *,int);
extern void func_L18_00426F78(void *);
extern void func_L18_00427B48(void *,int);
extern void func_002A6C58(void *,int,int);
extern void func_L18_004273F0(void *);
extern void func_002A7750(void *,int,int);
/* EE argument banks preserve the pointer/index/point/force and range/height
 * orders while this declaration places the range pair before the optional point. */
extern int func_002B3BA8(void *, int, float, float, void *, int);
extern int func_002B38B8(void *);
extern void func_0029B758(int,int);
extern void func_00335438(void *,void *,int,int,int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_L18_002E0070(int,int);
extern float func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,int);
extern void func_L18_00426F28(void *,int,int,float);
extern void func_002B0C28(int,int,int);
/* Refreshes targeting and combat reactions, including the player capture transition. */
void func_L18_00427BE0(u8 *moby) {
    EnemyStateView *state = *(EnemyStateView **)(moby + 0x68);
    int hit;
    if (!moby[0x95]) {
        state->i[0x3F0/4] = -1;
        if (InitShooterEnemy(moby)) {
            MarkMobySpawned(moby);
            return;
        }
    }
    if (moby[0x31] && fast_vec_dist(moby+0x10, &gCameraPosition_L18) < 24.0f) {
        UpdateMobyGroundCheck(moby);
        moby[0x6F] = 22;
    }
    if (!(state->b[0x3B1] & 0x80) || *(s16 *)(moby+0xAA) != 0xEE1 /* Receiver Bot */) {
        state->f[0x2B0/4] = 0.0f;
        UpdateEasedNode(moby, state->b+0x240,4,1.0f,1.0f);
    } else if (gPlayerBolts[0x4F]) {
        state->f[0x2B0/4] = 0.5f / D_L18_001B12FC;
        UpdateEasedNode(moby,state->b+0x240,4,1.0f,1.0f);
    }
    if (moby[0x95] != 8 && moby[0xBC] != 1 && moby[0x95] != 7 && !D_L18_001AFBB0 && gHeroState.i[0x2294/4] != 111) {
        hit = ApplyDamageToObject(moby,state->b+0x50,0);
        if (hit) {
            RebuildScaleMatrix(moby);
            FlagShootersInGroup(moby,moby[0x21]);
            if (hit == 4) {
                SetDeathBits(moby,0,3);
                ActivateNearestSpawnedEnemy(moby);
                SetMobyState(moby,12,10);
            }
        }
        state->b[0x3B2] = state->b[0x3B3];
        SelectAimTarget_002B3BA8(moby, state->i[0x37C / 4], 0.0f, 0.0f, 0, 0);
        {
            int id = *(s16 *)(state->p[0x230/4]+0xAA);
            state->b[0x3B3] = id == 0xEC0 /* moby class 3776 */ || id == 0xED4 /* moby class 3796 */ || id == 0xEE1 /* Receiver Bot */;
        }
        if (!moby[0xBC] && moby[0x95] != 7 && IsThirdPendingFlagSet(moby)) {
            moby[0x30] = 255;
            StoreLevelObjectValuePair(0,0);
            RebuildScaleMatrix(moby);
            SetCamera5Pose(&gCameraPosition_L18,gCameraPosition_L18.b+0x10,1,0,0);
            CopyVectorToSelectedObject(&gCameraPosition_L18);
            SetCameraStateRotation(gCameraPosition_L18.b+0x10);
            if (gHeroState.i[0x2294/4] == 1 || gHeroState.i[0x2294/4] == 29)
                SetHeroAction_L18(0, 1);
            gHeroState.h[0x1E0/2] = 20;
            state->f[0x3B8/4] = (vec_distance_xy(moby+0x10,&gCameraPosition_L18)-D_L18_001B1294) / D_L18_001B1290;
            if (D_0018C360.uh[0x294/2] < 65535)
                ++D_0018C360.uh[0x294/2];
            if (D_001A7390[0] > D_0018C360.ui[0x298/4])
                D_0018C360.ui[0x298/4] = D_001A7390[0];
            D_0018C360.ui[0x29C/4] = (D_0018C360.ui[0x29C/4] | (1 << gCurrentMapIndex[0])) | 0x80000000;
            SetObjectFlagBit(moby,0);
            state->uh[0x396/2] = *(u16 *)&D_L18_001B1290;
            StartOrForwardAnimation(moby,16,0,10.0f);
            D_L18_001AFBB0 = 1;
            TryClaimNotice(6,0,20);
            SetMobyState(moby,0,7);
        }
    }
    moby[0xA8] = 255;
    if (!state->i[0x1D8/4])
        SetMobyState(moby, 12, 10);
    if (state->b[0x3E9] && (D_0019B2E8[moby[0xB0]+(D_001A79F0_gp<<4)] & 0x80))
        SetMobyState(moby, 12, 10);
    if (state->b[0x2E] == 2) {
        RebuildScaleMatrix(moby);
        FlagShootersInGroup(moby,moby[0x21]);
        ActivateNearestSpawnedEnemy(moby);
        SetMobyState(moby,11,10);
    }
}
