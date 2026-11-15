#include "names.h"
/* Level 10 handler: two attack modes, live-target choice and the sound handle.
   Sound entries are 0x70 apart from D_00188660; the motion block is a struct view. */

typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern char D_00188660[];
extern u8 *D_L10_001B251C __attribute__((sda));
extern u8 *D_L10_001C3B40[];
extern char ref_L10_00418D88_00[];
extern s32 func_002ED688(u8 *);
extern int func_L00_00367720(void);
extern void func_L10_004190F0(u8 *);
extern void func_L05_00379E60(int, int, int, int);
extern void func_L05_0037C160(u8 *);
extern int func_L05_0037B538(u8 *, int, int, int);
extern void func_002E59F8(s32);
extern int func_002E5CF8(int, int, char *);
extern void func_L05_0037B948(u8 *, int, float);
extern void func_L10_004191E8(void *);
extern int func_L05_0037B888(char *);
extern void func_L05_0037B6D0(char *);
extern int func_00282948(void *);
extern void func_L10_00419348(u8 *);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002E5DA0(int, int, char *, int);

typedef struct { char pad0[0x104]; int f104; int f108; int pad10c; int f110; int pad114[2]; int f11C; u8 *f120; } Motion;

/* Updates the two attack modes, chooses a live target and maintains its sound. */
/* Update for moby class 3987, a flying enemy. It attacks, picks a live target and keeps its sound going. */
void func_L10_00418D88(u8 *self) {
    char *state = *(char **)(self + 0x68);
    Motion *motion = (Motion *)GetMobyMotionData(self);
    Motion *otherMotion;
    u8 *target, *current;
    int handle, i, count;
    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        if (!GetStoredPointerValue()) return;
        RestoreFlyingObjectState(self);
        if (*(int *)(state + 0x264))
            AppendLevelObject((int)self, (int)ref_L10_00418D88_00, 0, 0);
        break;
    case 1:
        *(float *)(self + 0x2C) = 0.019999999552965164f;
        UpdateObjectMovementState(self);
        if (ProcessObjectCollisionHit(self, 0, 0, 0)) {
            handle = *(int *)(state + 0x26C);
            if (handle != -1) {
                char *e = gSoundState + handle * 0x70;
                if (*(u8 **)(e + 0x88) == self && *(u8 *)(e + 0x74)) StopSoundVoice(handle);
            }
            *(int *)(state + 0x26C) = -1;
            PlayMobySound(1, 0, (char *)self);
        }
        if (motion->f110) {
            CheckPlayerInViewAndRange(self, 0, 176.0f);
            if (*(int *)(state + 0x260) != -1) {
                motion->f11C = 1;
                motion->f120 = D_L10_001B251C + (*(int *)(state + 0x260) << 8);
            }
            if (motion->f108 && motion->f104) UpdateLightningObjectState(self);
            if (CanObjectTakeNextStep((char *)self)) StartObjectMovementState((char *)self);
            FastFloatHelperD(state + 0x268);
            SpawnTailTrailMarks_L10(self);
        }
        break;
    case 2:
        *(float *)(self + 0x2C) = 0.07999999821186066f;
        UpdateObjectMovementState(self);
        ProcessObjectCollisionHit(self, 0, 0, 0);
        if (!motion->f110) break;
        CheckPlayerInViewAndRange(self, 0, 176.0f);
        current = motion->f120;
        if (current) {
            otherMotion = (Motion *)GetMobyMotionData(current);
            if (!otherMotion->f110) motion->f120 = 0;
        }
        if (!current || !motion->f120) {
            count = ProcessCollisionHit(self + 0x10, 0, self, 0, 80.0f);
            for (i = 0; i < count; i++) {
                target = D_L10_001C3B40[i];
                if (*(s16 *)(target + 0xAA) == 0xCBE /* moby class 3262 */) {
                    otherMotion = (Motion *)GetMobyMotionData(target);
                    if (otherMotion->f110) {
                        motion->f120 = target;
                        motion->f11C = 0;
                        break;
                    }
                }
            }
        }
        if (motion->f104) UpdateLightningObjectState(self);
        if (CanObjectTakeNextStep((char *)self)) StartObjectMovementState((char *)self);
        FastFloatHelperD(state + 0x268);
        SpawnTailTrailMarks_L10(self);
        break;
    }
    {
    char *e = gSoundState + *(int *)(state + 0x26C) * 0x70;
    if (*(u8 **)(e + 0x88) != self || !*(u8 *)(e + 0x74))
        *(int *)(state + 0x26C) = PlaySoundFromClassBank(3, 6, (char *)self, 0xF93);
    }
}
