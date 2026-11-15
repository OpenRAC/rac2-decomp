#include "common.h"

extern int D_L10_001B1648 __attribute__((sda));

extern u8 D_L10_0042BEE0[];

extern int func_003179F0(void *a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern f32 func_00309B38(f32 f12, f32 f13);
extern void func_00301B98(void *a0, void *a1);

extern void func_00307C68(char *a0, int a1, int a2, int a3, f32 f12, f32 f13, f32 f14);

/* Three func_00307C68(p + 0x10, 11, colour, 1, ...) calls, each colour with a random
   alpha byte; the first alpha also sets +0x1C of this level's D_L10_001C7800 record. */
extern int D_L10_00221CFC __attribute__((section(".data")));
extern int D_L10_001B13A4 __attribute__((sda));
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern void *func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L10_00425798(void);
extern void func_L10_00425410(int, int);
extern void func_L05_00379F48(int);
extern int D_L10_001B13F8 __attribute__((sda));
extern int D_L10_001B13FC __attribute__((sda));
extern int D_L10_001B1444 __attribute__((sda));
extern int D_L10_001B1390 __attribute__((sda));
extern int D_L10_001B1424 __attribute__((sda));
extern char *D_L10_001B251C;
extern void func_L10_0039D5E0(void *, void *, int, int, int, int, int, int, float, float, float, float);
extern int func_00282948(void *);
extern void func_L10_00425888(void);
extern int func_0029B3E0(int, int);
extern void func_L00_003294F0(void *, int);
extern void func_002AD7B8(int);

typedef struct { int idx; u8 pad[0x28]; int f2C; } G221CD0;
extern G221CD0 D_L10_00221CD0;
extern u8 *D_001B2614;
extern void func_L05_0037B280(void *, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern void func_L10_00419188(void *);
extern void *func_L05_00379ED0(int);
extern int func_L10_0037D200(void *);
extern void func_L10_00423DC8(void *, int);
extern int func_L05_0037B3A0(void *);
extern void func_0027D330(int);
extern void func_L10_00423500(void *);

extern int func_002A7820(int low, int high);
extern f32 func_002A7878(f32 low, f32 high);
extern f32 func_002A7940(void);
extern void func_00281EB8(void *at, int kind, unsigned int colour, int count, f32 size,
                          f32 rate, f32 spin);
extern f32 func_00283CE0(int);
extern u8 D_L10_001C7800[];

/* First call: resets the D_L10_001B13A4 block, marks every class-0xF85 moby, spawns 75
   objects and the effect box. Then, until the 0xF85 moby reports done, each timer expiry
   either closes the D_L10_001B1444 sequence (with D_L10_001B1390 raised around the
   func_0029B3E0 call, which returns an int) or restarts state 0 through func_L10_00423DC8. */
void func_L10_00424028(char *object)
{
    char **mobyList;
    int result;
    char *vars = *(char **)(object + 0x68);
    char *targetMoby;
    int i;
    if (!gMissionInitialized) {
        typedef int Quad __attribute__((mode(TI)));
        union { Quad q; float f[4]; } av, bv;
        D_L10_00221CFC = 0;
        gMissionInitialized = 1;
        D_L10_001B13F8 = 0;
        D_L10_001B13FC = 0;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        mobyList = GetLevelObjectList();
        result = GetLevelSavedValue();
        for (i = 0; i < result; i++) {
            if (*(short *)(mobyList[i] + 0xAA) == 0xF85 /* moby class 3973 */) SpawnEntryListObjectsWithFlag(mobyList[i], 1);
        }
        DestroyLeftoverCloudObjects();
        SpawnCloudObjects(75,16);
        av.q = 0; bv.q = 0;
        av.f[0] = 469.63f; av.f[1] = 407.93f; av.f[2] = 502.79f;
        bv.f[0] = 476.13f; bv.f[1] = 415.41f; bv.f[2] = 502.79f;
        CreateEnergyStrip(&av,&bv,1,2000000,0x7F7F7F,0xFF1010,70,70,0.5f,0.2f,0.402f,1.12225f);
    }
    targetMoby = FindLevelObjectByClassId(0xF85 /* moby class 3973 */);
    result = targetMoby ? CountAliveGroupMobys(targetMoby) : 0;
    if (!result) {
        InitAllRegisteredEntries();
        if (D_L10_001B1444) {
            if (FastFloatHelperD(vars + 0x58)) {
                *(int *)(vars + 0x58) = 10;
                gMissionCompletionCounts++;
                ClampAndStoreCompletionCounts();
                MemcardSave(0,-1);
                gMissionCompletionCounts--;
                SetObjectFlagBit(D_L10_001B251C + *(int *)(vars + 0x2C) * 256,1);
                D_L10_001B1424 = 0;
                D_L10_001B1444 = 0;
                SetPlayerStateField18(1);
                MarkFlagAndAppendToList(12);
            }
        } else if (FastFloatHelperD(vars + 0x58)) {
            FinishMissionAndGrantReward(object,0);
            D_L10_001B13F8 = 0;
            D_L10_001B13FC = 0;
        }
    }
}

/* Mission controller for the second challenge: sets it up on the first frame, then ends the
   round when the first target group is gone or the second group is cleared. */
void func_L10_00424290(u8 *moby) {
    u8 **mobyList;
    int mobyCount;
    int i;
    u8 *current;
    void *targetMoby;
    int targetsLeft;

    if (gMissionInitialized == 0) {
        gMissionInitialized = 1;
        D_L10_00221CD0.f2C = 0;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        mobyList = GetLevelObjectList();
        mobyCount = GetLevelSavedValue();
        for (i = 0; i < mobyCount; i++) {
            current = mobyList[i];
            switch (*(short *)(current + 0xAA)) {
            case 0xCBE /* moby class 3262 */:
                SpawnEntryListObjectsWithFlag(current, 1);
                break;
            case 0xF93 /* moby class 3987 */:
                SpawnEntryListObjectsWithFlag(current, 1);
                func_L05_0037CEE0(mobyList[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                func_L05_0037D608(mobyList[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                SetGroupMobyStates(mobyList[i]);
                break;
            }
        }
        DestroyLeftoverCloudObjects();
        SpawnCloudObjects(0x2D, 12);
    }
    targetMoby = FindLevelObjectByClassId(0xF93 /* moby class 3987 */);
    targetsLeft = targetMoby ? CountAliveGroupMobys(targetMoby) : 0;
    if (targetsLeft == 0) {
        FinishMissionAndGrantReward(moby, 1);
    }
    if (CountReadyListObjects(FindLevelObjectByClassId(0xCBE /* moby class 3262 */)) == 0) {
        FadeToBlack(0x1E);
        SetPlayerStateField18(0);
        ResetHrugisMissionState(moby);
    }
}

/* Two-state start-up for a cloud puff: state 0 lays the record at +0x10 out (position
   reset, colour limits, the builder call, its handle in the $gp variable), and states 0
   and 1 both fade the +0xF8 value down; anything else goes straight to the update. */
void func_L10_0042BE20(u8 *moby) {
    u8 *puff = moby;
    u8 state = *(u8 *)(puff + 0x20);
    f32 zero;

    switch (state) {
    case 0:
        *(int *)(puff + 0x1C) = 0;
        *(u8 *)(puff + 0x20) = 1;
        zero = *(f32 *)(puff + 0x1C);
        *(u16 *)(puff + 0x32) = 0x1FF;
        *(u8 *)(puff + 0x30) = 0xFF;
        *(f32 *)(puff + 0x10) = 512.0f;
        *(f32 *)(puff + 0x14) = 512.0f;
        *(f32 *)(puff + 0x18) = 512.0f;
        D_L10_001B1648 = func_003179F0(puff + 0x10, 40.0f, zero, zero, zero, 1.0f);
    case 1:
        *(f32 *)(puff + 0xF8) =
            func_00309B38(*(f32 *)(puff + 0xF8), 0.00981747824699f);
        break;
    default:
        break;
    }
    func_00301B98(D_L10_0042BEE0, puff);
}

/* The cloud puff's burst: three layers of particles at the object's position, coloured
   0x800000, 0x808080 and 0x804040 under random alphas, then the entry of D_L10_001C7800
   named by D_L10_001B1648 takes half of a value for the first alpha at +0x1C. */
void func_L10_0042BEE0(u8 *object)
{
    int alpha;
    u8 *entry;

    alpha = RandomIntRange(1, 0x80) << 24;
    object += 0x10;
    DrawBillboardQuad_00281EB8(object, 0xB, (RandomIntRange(0x20, 0x80) << 24) | 0x800000, 1,
                  RandomFloatRange(8.0f, 15.0f), 0.01f, RandomAngle());
    DrawBillboardQuad_00281EB8(object, 0xB, alpha | 0x808080, 1, RandomFloatRange(4.0f, 12.0f), 0.025f,
                  RandomAngle());
    DrawBillboardQuad_00281EB8(object, 0xB, (RandomIntRange(0, 0x80) << 24) | 0x804040, 1,
                  RandomFloatRange(8.0f, 17.0f), 0.05f, RandomAngle());
    entry = D_L10_001C7800 + (D_L10_001B1648 << 5);
    *(f32 *)(entry + 0x1C) = IntToFloat(alpha >> 24) * 0.5f;
}
