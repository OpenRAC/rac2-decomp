/* func_L04_00419918, the hoverbike race controller of Barlow and Joba. Its own -G8 unit,
 * built with -g (config/cflags.txt): the line notes give retail's nop pair before case 2's div.s. */
#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));

extern char D_00189E20[];
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot D_00188660[];
extern int D_00138320 NOT_SDA;
extern int D_00138324 NOT_SDA;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A7904 MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_L04_001A7CD0 MACRO_ADDR;
extern float D_L04_001A7CCC MACRO_ADDR;
extern int D_L04_001A7CD4 MACRO_ADDR;
extern int D_L04_001A8ED0 MACRO_ADDR;
/* The race flag words; [5] is the flag func_L04_00402D90 sets. */
extern int D_L04_001A8ED0_flags[] __asm__("D_L04_001A8ED0") MACRO_ADDR;
extern int D_L04_001A8F00 MACRO_ADDR;
extern int D_L04_001A8F08 MACRO_ADDR;
extern int D_L04_001A8FE4 MACRO_ADDR;
extern int D_L04_001A8FE8 MACRO_ADDR;
extern void *D_L04_001AA6A0 MACRO_ADDR;
extern void *D_L04_001AA6A4 MACRO_ADDR;
extern void *D_L04_001AA6A8 MACRO_ADDR;
extern void *D_L04_001AA6AC MACRO_ADDR;
extern u8 *D_L04_001B08F4 __attribute__((sda));
extern int D_L04_001B08F0 __attribute__((sda));
extern int D_L04_001B08F8 __attribute__((sda));
extern int D_L04_001B08FC __attribute__((sda));
extern int D_L04_001B0900 __attribute__((sda));
extern int D_L04_001B0908 __attribute__((sda));
extern int D_L04_001B090C __attribute__((sda));
/* D_L04_001B0910 in Barlow; in Joba that name is bound to another variable. */
extern int ref_L04_00419918_01 __attribute__((sda));
extern u8 *D_L04_001B0914 __attribute__((sda));
extern int D_L04_001B0918 __attribute__((sda));
extern int D_L04_001B091C __attribute__((sda));
extern int D_L04_001B0924 __attribute__((sda));
extern int D_L04_001B092C __attribute__((sda));
extern int D_L04_001B0930 __attribute__((sda));
extern int D_L04_001B0934 __attribute__((sda));
extern int D_L04_001B0938 __attribute__((sda));
extern int D_L04_001B0BBC __attribute__((sda));
extern int D_L04_001B0BC0 __attribute__((sda));
extern float D_L04_001B1F20 __attribute__((sda));
extern int D_L04_001B2008 __attribute__((sda));
extern u8 *D_L04_001B24DC MACRO_ADDR;
extern u8 *D_L04_001B25CC MACRO_ADDR;
extern int D_L04_001B31D4 MACRO_ADDR;
extern char D_L04_001B31A0[] MACRO_ADDR;
extern char D_L04_001B9540[];
extern char D_L04_001B9680[];
extern Quad D_L04_001BFAF0;
extern float D_L04_001BDC30 NOT_SDA;
extern void func_L00_002B30E8(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_L04_002E7C08(int, int);
extern void func_00272198(float);
extern int func_00277258(void *, int, void *, float);
extern void func_0027AB40(void);
extern void func_L00_002E6EF8(void *, void *);
extern void func_0027D330(int);
extern int func_00282948(void *);
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283360(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00288308(int);
extern int func_00288E18(int, int);
extern void func_L00_00303530(int, int);
extern void func_0029B758(int, void *);
extern void func_0029F338(void *);
extern void func_0029F978(void *, int, void *);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void func_002A7398(void *, int, int);
extern float func_002A7878(float, float);
extern void func_002A91F0(void *, float *);
extern void func_002A93B0(void *);
extern void func_002AD7B8(int);
extern int func_002B0C28(int, int, int);
extern int func_L00_003268E8(int);
extern int func_002B38B8(void *);
extern void func_L01_00323310(int, int);
extern void func_002C96F8(float, float, void *, void *, void *, void *);
extern void func_002DF3F8(void *, void *);
extern int func_002E4AC8(void);
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern int func_002E5E58(int, int, void *);
extern int func_L00_0035F5A0(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern void func_L00_003672F8(void);
extern int func_L04_00400AB0(void *, void *, int);
extern int func_L04_0040A1D0(int);
extern int func_L04_0040A268(int);
extern void func_L04_0040A310(void *);
extern void func_L04_0040A3B8(void *, int);
extern void func_L04_0040A5C0(void *);
extern void func_L04_0040A958(void *, int);
extern void func_L04_0040AC30(void *, void *);
extern void func_L04_0040BA68(void *, void *);
extern void func_L04_0040E248(void *, void *);
extern void func_L04_0040F5D0(void *);
extern void func_L04_00410518(void *, void *, void *, void *, void *, int);
extern int func_L04_00410E48(int, int, float);
extern int func_L04_00412308(void *, void *);
extern void func_L04_00412E38(void *, void *, float, float);
extern void func_L04_00415EA8(void *);
extern void func_L04_00417308(void);
extern void func_L04_00418A58(void *, void *);
extern void func_L04_00418BF0(void *, void *);
extern void func_L04_004195E0(void *);
extern void func_L04_0043ABE0(void);
extern void func_L04_0040AC80(void);
/* func_L04_0040AC98 in Barlow; Joba places its copy elsewhere. */
extern void ref_L04_00419918_00(void);
extern void func_L04_0040ACA8(void);
extern void func_L04_0040AD28(void);
extern void func_L04_0040CDD0(void);
extern void func_L04_00411298(void);
extern void func_00132B28(int);
extern void func_00132028(void);

#define M_(p, t, o) (((struct { u8 pad[o]; t v; } *)(p))->v)
#define I(p, o) M_(p, int, o)
#define F(p, o) M_(p, float, o)
#define H(p, o) M_(p, unsigned short, o)
#define P(p, o) M_(p, u8 *, o)
#define Q(p, o) M_(p, Quad, o)
typedef struct { u8 b[0x100]; } MobyRec;
typedef struct { int v[1]; } IdList;
typedef struct { u8 b[0x80]; } NodeRec;
#define MOBY(i) (((MobyRec *)D_L04_001B24DC)[i].b)
#define NODE(i) (((NodeRec *)D_L04_001B25CC)[i].b)

/* The hoverbike race controller of Barlow and Joba: spawns the bikes and the course, waits for
   the hero to mount, runs the countdown, the race and the finish, and puts everything back. */
void func_L04_00419918(u8 *self)
{
    Vector a;
    Vector b;
    u8 *s = P(self, 0x68);
    u8 *o;
    int k, flag, path;
    IdList *ids;
    float *fp;
    int id;
    float d;

    if (self[0x31] != 0 && fast_vec_dist(self + 0x10, D_L04_001B9680) < 24.0f) {
        UpdateMobyGroundCheck(self);
        self[0x6F] = 22;
    }
    if ((D_L04_001A8F08 == 2 || D_L04_001A8F00 == 2) && D_L04_001B0BC0 == 0 && gCurrentMapIndex != 11) {
        H(self, 0x34) = (H(self, 0x34) | 0x41) & ~0x1000;
        I(self, 0x98) = 0;
        D_L04_001B0BC0 = 1;
        return;
    }
    if (D_L04_001A8F08 != 2 && D_L04_001A8F00 != 2 && D_L04_001B0BC0 != 0) {
        H(self, 0x34) = (H(self, 0x34) & ~0x41) | 0x1000;
        I(self, 0x98) = I(P(self, 0x24), 0x10);
        D_L04_001B0BC0 = 0;
    }
    switch (self[0x20]) {
    case 0:
        I(s, 0x748) = -1;
        I(s, 0x74C) = -1;
        I(s, 0x714) = -1;
        I(s, 0x3BC) = -1;
        I(s, 0x328) = -1;
        I(s, 0x330) = -1;
        I(s, 0x334) = -1;
        D_L04_001AA6A0 = SetRaceStateFlagsA;
        D_L04_001AA6A4 = ref_L04_00419918_00;
        D_L04_001AA6A8 = SetRaceStateFlagsC;
        D_L04_001AA6AC = ref_L04_00419918_00;
        set_identity_rotation_rows(D_L04_001B31A0);
        D_L04_001B0914 = self;
        InitBarlowAnimationPaths();
        self[0x30] = 0x40;
        H(self, 0x32) = 0x40;
        self[0x20] = 1;
        RecomputeBranchRouteLinks(self);
        H(self, 0x34) |= 0x400;
        if (D_001A7904 == 3) {
            D_L04_001B08FC = 1;
            ResetHeroPositionAndDirection(NODE(I(s, 0x19C)) + 0x30, NODE(I(s, 0x19C)) + 0x70, 0, 1);
            D_001A7904 = 0;
            SetFlagToOne();
        } else {
            D_L04_001B08FC = 0;
        }
        Q(s, 0x2D0) = Q(self, 0x10);
        Q(s, 0x2E0) = Q(self, 0xF0);
        qzero(s + 0x290);
        qzero(s + 0x2A0);
        I(s, 0x314) = -1;
        I(s, 0x494) = -1;
        F(s, 0x660) = 0.01f;
        F(s, 0x664) = 0.02f;
        F(s, 0x668) = 0.03f;
        F(s, 0x66C) = 0.04f;
        I(s, 0x318) = 0;
        I(s, 0x498) = 0;
        I(s, 0x640) = 0;
        if (gCurrentMapIndex == 4) {
            I(s, 0x648) = 0x48;
            I(s, 0x644) = 0x4D;
        } else {
            I(s, 0x648) = 0x41;
            I(s, 0x644) = 0x42;
        }
        I(s, 0x768) = 0;
        I(s, 0x764) = 40;
        fp = (float *)(s + 0x370);
        for (k = 0; k < 21; k++) {
            int id = ((int *)(s + 0x1E4))[k];

            if (id != -1) {
                u8 *rider = P(MOBY(id), 0x68);

                I(rider, 0x120) = -1;
                I(rider, 0x124) = 0;
                I(rider, 0x1C4) = -1;
                I(rider, 0x1C8) = 0;
            }
        }
        I(s, 0x340) = 0;
        I(s, 0x344) = 0;
        for (k = 0; k < 5; k++) {
            I(s, 0x344) += GetCourseWinCount(k);
            I(s, 0x340) += GetCourseFinishCount(k);
        }
        for (k = 0; k < 6; k++) {
            fp[k] = RandomFloatRange(0.0f, 1.0f);
        }
        if (gCurrentMapIndex == 11 && GetCourseWinCount(0) > 0 && gItemOwnedFlags[0x36] == 0) {
            UnlockHelpEntry(0x36);
        } else if (gCurrentMapIndex == 4 && GetCourseWinCount(0) > 0) {
            MarkFlagAndAppendToList(5);
        }
        if (s[0x441] == 0) {
            AttachManipulator(self, 5, s + 0x440);
        }
        return;
    case 1:
        flag = D_L04_001B08FC != 0;
        if (I(s, 0x238) == -1 || IsThirdPendingFlagSet(MOBY(I(s, 0x238))) != 0) {
            StepAngleOffset(self, s, 0.02f, 0.00029f);
            flag = 1;
            F(self, 0x18) = F(s, 0x2D8) + FastSinOrCosB(F(s, 0x38C)) * 0.04f;
            qzero_nc(a);
            a[0] = F(s, 0x38C);
            BuildRotationFromAngles(s + 0x450, a);
            if (I(s, 0x238) != -1) {
                u8 *m = MOBY(I(s, 0x238));

                I(m, 0x98) = 0;
                H(m, 0x34) |= 0x43;
                if (I(s, 0x1E0) != -1) {
                    m = MOBY(I(s, 0x1E0));
                    I(m, 0x98) = 0;
                    H(m, 0x34) |= 0x43;
                }
            }
        }
        d = fast_vec_dist(gHeroState + 0x80, self + 0x10);
        if (D_L04_001B08FC == 0) {
            if (!flag || !(d < 5.5f) || D_L04_001B2008 < 4) {
                return;
            }
            if (I(gHeroState, 0x229C) == 0x1F || I(gHeroState, 0x2294) == 0x1D
                || I(gHeroState, 0x2294) == 0x1C || I(gHeroState, 0x2294) == 1
                || D_L04_001A8F00 == 2 || D_L04_001A8F08 == 2) {
                return;
            }
            if (D_L04_001B0924 == 0 && IsVoicePlayingForOwner(self, I(s, 0x330)) == 0) {
                I(s, 0x330) = StartEffectInSlot(gCurrentMapIndex == 4 ? 0x16 : 0x1A, 5, self);
                SetSoundSlotField(I(s, 0x330), FloatToInt(IntToFloat(0x400) * 0.75f));
            }
        }
        TryClaimNotice(4, 0x27A1, 1);
        if (D_L04_001B08FC == 0 && D_L04_001B0924 == 0 && !(D_00138324 & 0x10)) {
            return;
        }
        {
            int sound = I(s, 0x330);

            if (sound != -1) {
                SoundSlot *slot = (SoundSlot *)((char *)gSoundState + sound * 0x70);

                if (slot->owner == (char *)self && slot->active) {
                    StopSoundVoice(sound);
                }
            }
            I(s, 0x330) = -1;
        }
        if (gCurrentMapIndex == 0xCE) {
            EnterHeroState_L04(0x86, 1);
        } else {
            if (I(s, 0x198) != -1) {
                if (I(s, 0x19C) != -1) {
                    CaptureCheckpointState(NODE(I(s, 0x19C)) + 0x30, NODE(I(s, 0x19C)) + 0x70);
                } else {
                    CaptureCheckpointState(self + 0x10, self + 0xF0);
                }
                FadeToBlack(0x10);
                ResetHeroPositionAndDirection(NODE(I(s, 0x198)) + 0x30, NODE(I(s, 0x198)) + 0x70, 0x31, 1);
                Q(self, 0x10) = Q(NODE(I(s, 0x198)), 0x30);
                Q(self, 0xF0) = Q(NODE(I(s, 0x198)), 0x70);
            }
            EnterHeroState_L04(0x31, 1);
            LoadSceneChunk(1, I(s, 0x488));
            I(s, 0x58) |= 1;
            I(s, 0x340) = 0;
            F(s, 0x28) = 2.0f;
            I(s, 0x54) = 0;
            F(s, 0x40) = 0.008333334f;
            F(s, 0x24) = 0.1f;
            F(s, 0x20) = 0.25f;
            F(s, 0x2C) = 2.0f;
            F(s, 0x30) = 1.0f;
            F(s, 0x44) = 0.008333334f;
            F(s, 0x48) = 0.5f;
            F(s, 0x4C) = 0.0033333334f;
            I(s, 0x270) = 0;
            gCurrentLap = 0;
            gRaceTimeTicks = 0;
            D_L04_001B0918 = 0;
            I(s, 0x31C) = 0;
        }
        H(self, 0x34) |= 0x41;
        {
            u8 *m = 0;

            if (I(s, 0x1DC) != -1) {
                m = MOBY(I(s, 0x1DC));
            }
            if (m != 0) {
                H(m, 0x34) |= 0x41;
                if (D_L04_001B08F4 != 0) {
                    H(D_L04_001B08F4, 0x34) |= 0x41;
                }
            }
        }
        self[0x20] = 2;
        if (D_L04_001B0924 != 0) {
            self[0xBC] = 2;
        } else {
            StoreLevelObjectValuePair(0, DrawRaceResultsPanel);
            self[0xBC] = 0;
        }
        D_L04_001B08FC = 0;
        I(s, 0x394) = 150;
        self[0x30] = 0xFF;
        ReleaseMatchingResource(4);
        gHeroState[0x22B5] = 1;
        I(P(gHeroState, 0x2290), 0x98) = 0;
        QueueKeyedRequest(I(s, 0x488), -1);
        return;
    case 2:
        if (I(gHeroState, 0x2294) == 0x86) {
            u8 *bike = P(gHeroState, 0x2290);
            float ratio = F(bike, 0x2C) / F(P(bike, 0x24), 0x24);

            F(self, 0x2C) = F(P(self, 0x24), 0x24) * ratio;
            return;
        }
        if (D_L04_001B0908 != 0) {
            D_L04_001A8ED0 = 2;
            UpdateSoundVoices();
            FadeToBlack(0x10);
            if (D_L04_001B0908 == 2) {
                ResetRaceController(self, 1);
            } else {
                ResetRaceController(self, 0);
            }
            D_L04_001B0908 = 0;
            return;
        }
        if (ref_L04_00419918_01 != 0) {
            D_L04_001A8ED0 = 1;
            H(self, 0x34) &= ~0x41;
            ReleaseRacerLinkState(self, s);
            I(s, 0x320) = -1;
            self[0x20] = 4;
            ref_L04_00419918_01 = 0;
            return;
        }
        switch (self[0xBC]) {
        case 0:
            D_L04_001B0BBC = 0;
            UpdateRaceSelectionMenu(self, s);
            StoreLevelObjectValuePair(0, DrawRaceResultsPanel);
            return;
        case 1:
            UpdateHoverbikeRiderEntryState(self, s);
            if (*(u8 *)&D_00138324 != 0) {
                PlaySoundFromGlobalBank(4, 0, 0);
                self[0xBC] = 3;
            }
            return;
        case 2:
            D_L04_001A8ED0 = 0;
            o = 0;
            if (I(s, 0x1DC) != -1) {
                o = MOBY(I(s, 0x1DC));
            }
            if (o != 0) {
                H(o, 0x34) &= ~0x41;
                if (D_L04_001B08F4 != 0) {
                    H(D_L04_001B08F4, 0x34) &= ~0x41;
                }
                Q(o, 0x10) = Q(self, 0x10);
                Q(o, 0xF0) = Q(self, 0xF0);
                o[0x30] = 0;
                StartAnimationImmediate(o, 0, 0);
                func_002A05A8(o);
                func_002A0F48(o);
            }
            H(self, 0x34) &= ~0x41;
            D_L04_001B091C = 0;
            D_L04_001B31D4 = 0;
            StoreLevelObjectValuePair(0, DrawRaceRulerHud);
            D_L04_001B0930 = 0;
            D_L04_001B0938 = 0;
            ClearEffectEntriesByOwner(0);
            D_L04_001B08F0 = 0;
            InitHoverbikeRaceCourse(self);
            gHeroState[0x22B5] = 1;
            I(P(gHeroState, 0x2290), 0x98) = 0;
            if (D_L04_001B0924 != 0) {
                self[0xBC] = 1;
                H(self, 0x96) = 120;
                D_L04_001B0924 = 0;
                return;
            }
            self[0xBC] = 3;
        case 3:
            D_L04_001B092C = 0;
            ActivateLinkedRacers(self);
            RefreshActiveEffectRecords(self);
            self[0xBC] = 4;
        case 4:
            UpdateHoverbikeRiderEntryState(self, s);
            if (I(s, 0x394) < 120 && D_L04_001B31D4 == 0) {
                PlayMobySound(0xD, 0, self);
                D_L04_001B31D4++;
            } else if (I(s, 0x394) < 90 && D_L04_001B31D4 == 1) {
                PlayMobySound(0xD, 0, self);
                D_L04_001B31D4++;
            } else if (I(s, 0x394) < 60 && D_L04_001B31D4 == 2) {
                PlayMobySound(0xD, 0, self);
                D_L04_001B31D4++;
            } else if (I(s, 0x394) < 30 && D_L04_001B31D4 == 3) {
                PlayMobySound(0xD, 0, self);
                D_L04_001B31D4++;
            }
            FastFloatHelperD(s + 0x394);
            if (I(s, 0x394) != 0) {
                return;
            }
            PlayMobySound(0xE, 0, self);
            self[0xBC] = 5;
            if (D_00138320 & 0x40) {
                D_L04_001B0930 = 0;
            } else {
                D_L04_001B0930 = 1;
            }
            return;
        case 5:
            UpdateHoverbikeRiderEntryState(self, s);
            if (D_L04_001B0934 != 0) {
                RequestSubtitleVoiceLine(0xA26, 0x7D);
                D_L04_001B0934 = 0;
            }
            if (UpdatePlayerRaceProgress(self, s) != 0) {
                return;
            }
            UpdateHoverbikeRailGrindTrick(self, s);
            AddDrawCallbackToList3(DrawRacerGlowEffects, self);
            if (F(self, 0x18) < F(s, 0x26C) || IsRacerInJumpWindow(I(s, 0x314), I(s, 0x318), F(self, 0x18)) != 0) {
                ReleaseRacerSoundHandles(self, s);
                self[0xBC] = 6;
                H(self, 0x96) = 1;
            }
            if (D_L04_001B0900 == 0) {
                return;
            }
            FadeToBlack(0x10);
            ResetRaceController(self, 1);
            I(s, 0x340) = 0;
            D_L04_001B0900 = 0;
            return;
        case 6:
            if (P(s, 0x4C4) != 0) {
                I(P(P(s, 0x4C4), 0x68), 0x1C0) = 0;
                P(s, 0x4C4) = 0;
            }
            if (I(s, 0x724) != 0) {
                I(s, 0x724) = 0;
            }
            I(s, 0x720) = 0;
            AddDrawCallbackToList3(DrawRacerGlowEffects, self);
            o = 0;
            I(s, 0x30C) = 0;
            I(s, 0x27C) = 0;
            if (I(s, 0x1DC) != -1) {
                o = MOBY(I(s, 0x1DC));
            }
            ReleaseRacerSoundHandles(self, s);
            if (o != 0) {
                H(o, 0x34) |= 0x41;
                if (D_L04_001B08F4 != 0) {
                    H(D_L04_001B08F4, 0x34) |= 0x41;
                }
                F(o, 0x2C) = F(P(o, 0x24), 0x24) * 0.25f;
                H(o, 0x32) = 0x7F;
                o[0x31] = 1;
                Q(o, 0x10) = Q(self, 0x10);
                Q(o, 0xF0) = Q(self, 0xF0);
                o[0x30] = 0;
                func_002A05A8(o);
                func_002A0F48(o);
                H(o, 0x34) |= 6;
            }
            if (--H(self, 0x96) != 0) {
                return;
            }
            FadeToBlack(0x10);
            ids = (IdList *)(s + 0x110);
            id = ids->v[I(s, 0x270)];
            if (id != -1) {
                Q(a, 0) = Q(NODE(id), 0x30);
                Q(b, 0) = Q(NODE(ids->v[I(s, 0x270)]), 0x70);
            } else if (I(s, 0x198) == -1) {
                RecordHeroPlayCounters();
                return;
            } else {
                Q(a, 0) = Q(NODE(I(s, 0x198)), 0x30);
                Q(b, 0) = Q(NODE(I(s, 0x198)), 0x70);
            }
            D_L04_001B1F20 = 1.0f;
            SetCameraTransitionFrames(10.0f);
            if (TestPointAgainstCollision(a, 4, self, F(s, 0x20)) != 0) {
                Q(a, 0) = D_L04_001BFAF0;
            }
            ResetRacerState(self, 1);
            ClearEffectEntriesByOwner(self);
            ResetHeroPositionAndDirection(a, b, 0x31, 1);
            gHeroState[0x22B7] = 1;
            gHeroState[0x22B5] = 1;
            I(s, 0x49C) = -1;
            I(s, 0x4A0) = -1;
            F(s, 0x4A4) = -1.0f;
            I(s, 0x4B0) = 0;
            I(s, 0x4A8) = 0;
            I(s, 0x4AC) = 0;
            Q(self, 0x10) = Q(a, 0);
            Q(self, 0xF0) = Q(b, 0);
            FindNearestRoutePoint(self, s, s + 0x314, s + 0x318, s + 0x310, gCurrentLap);
            H(self, 0x34) &= ~0x41;
            if (o != 0) {
                Q(o, 0x10) = Q(self, 0x10);
                Q(o, 0xF0) = Q(self, 0xF0);
                StartAnimationImmediate(o, 0, 0);
                func_002A05A8(o);
                func_002A0F48(o);
                H(o, 0x34) &= ~0x41;
                if (D_L04_001B08F4 != 0) {
                    H(D_L04_001B08F4, 0x34) &= ~0x41;
                }
            }
            self[0xBC] = 5;
            self[0x30] = 0xFF;
            H(self, 0x34) |= 0x400;
            return;
        }
        return;
    case 3:
        D_L04_001A8ED0 = 1;
        UpdateHoverbikeRiderEntryState(self, s);
        D_L04_001B08F8++;
        if (F(self, 0x18) < F(s, 0x26C) || IsRacerInJumpWindow(I(s, 0x314), I(s, 0x318), F(self, 0x18)) != 0) {
            float ahead, along;
            int node = FindNearestRoutePointIndex(self, P(s, 0x6D0), 1);

            /* The path's points are 16-byte records from +0x10. */
            Q(self, 0x10) = Q(((Vector *)P(s, 0x6D0))[node], 0x10);
            along = IntToFloat(node) * F(P(s, 0x6D0), 0x1C);
            if (D_L04_001B08F0 != 0) {
                ahead = along + 15.0f;
            } else {
                ahead = along + 5.0f;
            }
            F(s, 0x6D8) = ahead;
            SampleKeyTrack(ahead, F(P(s, 0x6D0), 0x1C), P(s, 0x6D0), s + 0x654, s + 0x6D4, s + 0x6A0);
            FindNearestRoutePoint(self, s, s + 0x314, s + 0x318, s + 0x310, gCurrentLap);
        }
        StoreLevelObjectValuePair(0, DrawRaceStandingsHud);
        FastFloatHelperD(s + 0x398);
        if (D_L04_001A7CD0 == 0) {
            if (I(s, 0x398) > 0 || !(D_00138324 & 0x10)) {
                return;
            }
            D_L04_001A7CD0 = 1;
            D_L04_001A7CCC = 0.05f;
            D_L04_001A7CD4 = 0;
        }
        if (D_L04_001A7CD4 != 1) {
            return;
        }
        SendSoundCommand23(0x5D);
        snd_Pump();
        D_L04_001A8ED0_flags[5] = 0;
        ReleaseRacerLinkState(self, s);
        self[0x20] = 4;
        QueueKeyedRequest(I(s, 0x488), -1);
        return;
    case 4:
        D_L04_001A8ED0 = 1;
        I(D_L04_001B9540, 0x160) = 0;
        I(D_L04_001B9540, 0x168) = 0;
        I(D_L04_001B9540, 0x180) = 0;
        I(D_L04_001B9540, 0x188) = 0;
        I(D_L04_001B9540, 0x16C) = 0;
        if (D_L04_001A7CD0 == 0) {
            D_L04_001A7CD0 = 1;
            D_L04_001A7CCC = 0.05f;
            D_L04_001A7CD4 = 0;
        }
        if ((unsigned int)(D_L04_001A7CD4 - 1) >= 2) {
            return;
        }
        RefreshActiveEffectRecords(self);
        D_L04_001A8ED0 = 0;
        H(self, 0x34) &= ~0x41;
        StoreLevelObjectValuePair(0, 0);
        if (I(s, 0x19C) != -1) {
            if (I(s, 0x320) == -1 || (gCurrentRaceIndex == 0 && GetCourseWinCount(0) == 1)) {
                u8 *bike;

                path = I(s, 0x480);
                if (gCurrentMapIndex == 11) {
                    path = I(s, 0x484);
                }
                Q(a, 0) = Q(NODE(I(s, 0x19C)), 0x70);
                if (D_L04_001B0BBC != 0) {
                    a[2] = 0.92f;
                }
                if (I(s, 0x320) == 1 && gCurrentRaceIndex == 0) {
                    gCurrentRaceIndex = I(s, 0x320);
                }
                if (D_L04_001B08F4 != 0) {
                    MarkMobySpawned(D_L04_001B08F4);
                    D_L04_001B08F4 = 0;
                }
                bike = P(gHeroState, 0x2290);
                gHeroState[0x22B5] = 0;
                I(bike, 0x98) = I(P(bike, 0x24), 0x10);
                ResetHeroPositionAndDirection(NODE(I(s, 0x19C)) + 0x30, a, 0, 1);
                {
                    u8 *ride = P(gHeroState, 0x2290);

                    F(ride, 0x2C) = F(P(ride, 0x24), 0x24);
                }
                Q(self, 0x10) = Q(s, 0x2D0);
                Q(self, 0xF0) = Q(s, 0x2E0);
                self[0x20] = 1;
                F(self, 0x2C) = F(P(self, 0x24), 0x24);
                LoadSceneChunk(0, path);
                {
                    float q = FastSinOrCosB(0.56217057f) / FastSinOrCosA(0.56217057f);

                    D_L04_001BDC30 = q;
                }
                UpdateViewContext();
                for (k = 0; k < 21; k++) {
                    int id = ((int *)(s + 0x1E4))[k];

                    if (id != -1) {
                        u8 *rider = P(MOBY(id), 0x68);

                        I(rider, 0x2C8) = 0;
                        rider[0x251] = 0;
                        if (P(rider, 0x8C) != 0) {
                            MarkMobySpawned(P(rider, 0x8C));
                            P(rider, 0x8C) = 0;
                        }
                    }
                }
                return;
            }
            if (GetCourseWinCount(gCurrentRaceIndex) == 1) {
                gCurrentRaceIndex++;
                if (gCurrentRaceIndex >= 5) {
                    gCurrentRaceIndex = 4;
                }
            }
            ResetRaceController(self, 1);
        } else {
            ResetRaceController(self, 1);
            D_L04_001B0900 = 0;
        }
        return;
    }
}
