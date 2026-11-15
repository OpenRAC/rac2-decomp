#include "common.h"

/* The bodies that reach a global through $gp live in this -G8 sibling of
   L06_0033BDC0.c; the declarations carry the sda attribute so that cc1 emits
   the one-instruction $gp form the retail code has. */

extern void func_002A7750(void *, int, int);
extern int func_002A9640(void *, int, int);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int,
                               int, int, int);
extern void func_L01_0031A278(char *, float *, float, float, float);
extern void func_L06_00402230(char *);
extern void func_0029F338(void *);
extern void func_002A7398();
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_002E5CF8(int, int, char *);

extern float D_L06_001B0020 __attribute__((sda));
extern float D_L06_001B0028 __attribute__((sda));
extern float D_L06_001B0030 __attribute__((sda));
extern int D_L06_001B0050 __attribute__((sda));
extern float D_L06_001AFE40 __attribute__((sda));
extern char *D_L06_001B281C[] __attribute__((sda));

/* a moby's three states: idle, hit, and gone */
/* Updates a one-shot effect object (moby class 2322): it waits, then bursts into sparks and rings when hit, and goes away. */
void func_L06_00402440(char *mobyIn)
{
    char *moby = mobyIn;
    char *vars;
    float scratch[4];

    vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)(vars + 4) != 0)
            *(unsigned short *)(moby + 0x34) |= 0x8000;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0)
                SetMobyState(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        ExplodeObjectIntoPieces(moby, &D_L06_001B0030, &D_L06_001B0028, &D_L06_001B0020,
                          0xFFFF, 0, D_L06_001B0050, 6, 0xFFFF, 0xFF, 0);
        ComputeMobyLocalPoint(moby, scratch, 1.0f, 1.0f, 3.0f);
        EmitRingParticles(moby);
        MarkMobySpawned(moby);
        break;
    }
}

/* a moby that has just come alive: it takes its state, its position and the
   level's step, and it is retired when its angle has turned too far */
extern void func_L06_00400498(char *a0);

extern char *D_0018C0B0[];
extern u8 D_00188660[];
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);

/* a moby that wakes up: it takes the level's step, and it gives its handle
   back when the moby it is attached to is gone */
/* Updates a helper object (moby class 2376) that follows its parent's progress and plays or stops a looping sound as that changes. */
void func_L06_00403F60(char *mobyIn)
{
    char *moby = mobyIn;
    char *vars;
    char *parentVars;
    char *parentMoby;
    char *soundSlot;
    int parentIndex;
    int soundHandle;
    long long savedValue;

    vars = *(char **)(moby + 0x68);
    if (vars == 0)
        return;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(vars + 8) = *(float *)(moby + 0x18);
        savedValue = *(long long *)(*(char **)gHeroMoby_0018C0B0 + 0x38);
        *(unsigned char *)(moby + 0x20) = 1;
        *(long long *)(moby + 0x38) = savedValue;
        *(int *)(vars + 0x10) = 0;
        break;
    case 1:
        parentIndex = *(int *)vars;
        if (parentIndex == -1)
            break;
        parentMoby = D_L06_001B281C[0] + (parentIndex << 8);
        if (parentMoby == 0)
            break;
        parentVars = *(char **)(parentMoby + 0x68);
        *(float *)(moby + 0x18) = *(float *)(parentVars + 0) * *(float *)(vars + 4)
                               + *(float *)(vars + 8);
        if (*(float *)(parentVars + 0) != *(float *)(vars + 0x10)) {
            if (*(float *)(parentVars + 0) == 1.0f || *(float *)(parentVars + 0) == 0.0f) {
                if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0xC)) != 0) {
                    soundHandle = *(int *)(vars + 0xC);
                    if (soundHandle != -1) {
                        soundSlot = gSoundState + soundHandle * 0x70;
                        if (*(int *)(soundSlot + 0x88) == (int)moby) {
                            if (*(unsigned char *)(soundSlot + 0x74) != 0)
                                StopSoundVoice(soundHandle);
                        }
                    }
                    *(int *)(vars + 0xC) = -1;
                }
                PlayMobySound(1, 0, moby);
            } else {
                if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0xC)) == 0)
                    *(int *)(vars + 0xC) = PlayMobySound(0, 4, moby);
            }
        } else {
            if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0xC)) != 0) {
                soundHandle = *(int *)(vars + 0xC);
                if (soundHandle != -1) {
                    soundSlot = gSoundState + soundHandle * 0x70;
                    if (*(int *)(soundSlot + 0x88) == (int)moby) {
                        if (*(unsigned char *)(soundSlot + 0x74) != 0)
                            StopSoundVoice(soundHandle);
                    }
                }
                *(int *)(vars + 0xC) = -1;
            }
        }
        *(float *)(vars + 0x10) = *(float *)(parentVars + 0);
        break;
    }
}

/* An object with five states, state 0 to 4. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1DA0); `cases` only keeps the labels alive. The table's
   entry 3 is the end of the function. */
extern void *D_L06_002E1DA0[];
extern void func_L06_003FDEB8(int);
extern void func_L06_003FE178(char *);
extern int func_L00_00329520(void *, int);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002833F0(void *, void *);
extern void func_L01_002E1680(float *, float *, int, int, int, float, float, float);

extern int D_L06_001B2838 __attribute__((sda));
extern char *D_L06_001B281C_abs[3] __attribute__((sda));
extern unsigned short *D_L06_001FB3A0[];
extern char D_L06_001B9840[];
extern int D_L06_001AFC80 __attribute__((sda));
extern int D_L06_001AFC70 __attribute__((sda));
extern int D_L06_001AFC68 __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

#define GROUP (*(unsigned char *)(s1 + 0x21))
#define FOR_EACH_ID(p) \
    for (p = D_L06_001FB3A0[GROUP]; \
         GROUP != 0xFF && GROUP <= D_L06_001B2838 && p != 0 && \
         ((p != 0 && (short)p[-1] >= 0) || p == D_L06_001FB3A0[GROUP]); \
         p++)

/* Updates a switch-like object (moby classes 2155 and 2157) that controls a group of other mobys, turning them on and off. */
void func_L06_003FDA08(char *mobyIn)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&done, &&c4};
    char *s1 = mobyIn;
    char *vars;
    unsigned short *memberId;
    char *member;
    char *soundSlot;
    char *member2;
    unsigned short *memberId2;
    int cls;
    unsigned int sel;
    float sprayVelocity[4];
    float sprayPosition[4];

    sel = *(unsigned char *)(s1 + 0x20);
    vars = *(char **)(s1 + 0x68);
    if (sel < 5)
        goto *D_L06_002E1DA0[sel];
    goto done;
c0:
    *(unsigned char *)(s1 + 0x30) = 0xFE;
    InitializePathMobyGroup(*(unsigned char *)(s1 + 0x21));
    goto done;
c1:
    if (*(int *)(vars + 0x64) != -1 && IsPointInsideRegion(D_L06_001B9840, *(int *)(vars + 0x64)) != 0) {
        FOR_EACH_ID(memberId) {
            member = D_L06_001B281C_abs[0] + ((*memberId & 0x7FFF) << 8);
            if (member == 0)
                break;
            *(unsigned char *)(member + 0x31) = 0;
            *(unsigned short *)(member + 0x34) |= 1;
        }
        SetMobyState(s1, 4, -1);
    }
    UpdatePathMobySpacing(s1);
    soundSlot = gSoundState + *(int *)(vars + 0x54) * 0x70;
    if (*(int *)(soundSlot + 0x88) != (int)s1 || *(unsigned char *)(soundSlot + 0x74) == 0)
        *(int *)(vars + 0x54) = PlayMobySound(0, 4, s1);
    if (*(unsigned char *)(s1 + 0x31) == 0)
        goto done;
    if (FastFloatHelperD(vars + 0x44)) {
        if (*(unsigned short *)(s1 + 0x34) & 0x10) {
            *(unsigned short *)(s1 + 0x34) &= 0xFFEF;
            *(int *)(vars + 0x44) = *(int *)(vars + 0x48);
        } else {
            *(unsigned short *)(s1 + 0x34) |= 0x10;
            *(int *)(vars + 0x44) = 5;
        }
    }
    if (FindOwnedEffectSlot(s1, 0x4010000, 0)) {
        cls = *(short *)(s1 + 0xAA) == 0x86B /* moby class 2155 */ ? 2 : 3;
        ExplodeObjectIntoPieces(s1, &D_L06_001AFC80, &D_L06_001AFC70, &D_L06_001AFC68, 0xFFFF, 1, cls, 0, 0xFFFF,
                          0xFF, 0);
        *(short *)(s1 + 0x7C) = (1 << cls) - 0x8000;
        SpawnExplosion(s1 + 0x10, 0, 0x19, 0x14, 0x14, 0x14, 0x14, 1, 1.0f, 20.0f, 1, 0, 0, 0);
        SetMobyState(s1, 2, -1);
        *(int *)(vars + 0x38) = 0;
        *(int *)(vars + 0x14) = 0;
        *(int *)(vars + 0x58) = 0xB4;
        *(int *)(s1 + 0x98) = 0;
    }
    *(unsigned char *)(s1 + 0xA8) = 0xFF;
    *(float *)(s1 + 0xF8) = FastAddRotations(*(float *)(s1 + 0xF8), 3.141593f);
    euler_rotation_basis(s1 + 0xC0, s1 + 0xF0);
    goto done;
c4:
    if (IsPointInsideRegion(D_L06_001B9840, *(int *)(vars + 0x64)) == 0) {
        FOR_EACH_ID(memberId2) {
            member2 = D_L06_001B281C_abs[0] + ((*memberId2 & 0x7FFF) << 8);
            if (member2 == 0)
                break;
            *(unsigned char *)(member2 + 0x31) = 1;
            *(unsigned short *)(member2 + 0x34) &= 0xFFFE;
        }
        SetMobyState(s1, 1, -1);
    }
    goto done;
c2:
    *(float *)(s1 + 0xF4) = (*(float *)(s1 + 0xF4) - 0.7853982f) * 0.95f + 0.7853982f;
    euler_rotation_basis(s1 + 0xC0, s1 + 0xF0);
    *(float *)(s1 + 0x18) = *(float *)(s1 + 0x18) - 0.0200000014f;
    if (RandomIntBelow(4) == 0 && *(short *)(s1 + 0xAA) == 0x86B /* moby class 2155 */) {
        *(TI128 *)sprayVelocity = 0;
        sprayVelocity[2] = 0.083333336f;
        ComputeMobyLocalPoint(s1, sprayPosition, -1.5f, 0.0f, 1.0f);
        SpawnSparkBurst_L01(sprayPosition, sprayVelocity, 1, 0x40F0E0D0, 0, 0.041666668f, 2.0f, 1.02f);
    }
    if (FastFloatHelperD(vars + 0x58)) {
        *(unsigned char *)(s1 + 0x31) = 0;
        *(unsigned short *)(s1 + 0x34) |= 1;
        SetMobyState(s1, 3, -1);
    }
done:
    return;
}
