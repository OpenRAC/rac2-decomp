#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: every body here reaches a global through $gp.
   The small-data symbols are declared with the sda attribute, which makes the
   compiler emit the bare GPREL16 form; the type needs a size at most the -G8
   threshold, and the typedefs have to come before the externs. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long s64;
typedef float f32;

/* 0x1AEFF0 + 0xF10 : the level word func_L20_002B93E0 reads through $gp. */
extern s32 D_L20_001AFF00 __attribute__((sda));

/* 0x1AEFF0 - 0x7C60 : the word the retail reads both absolutely and through
   $gp, so it needs two names: the sda one is the $gp form, the plain one the
   absolute form.  A plain extern is the absolute form here: marking it nosda
   makes cc1 keep the address in a register of its own and the load does not
   match the retail any more (see nonmatching/levels/func_L20_002B93E0.c). */
extern s32 D_001A7390 __attribute__((sda));
extern s32 D_001A7390_1;

/* 0x1AEFF0 - 0x72F8 : the float the retail copies through $gp. */
extern float D_001A7CF8 __attribute__((sda));

/* 0x1AEFF0 - 0x7660 : the word the retail reads absolutely (plain extern, see
   the note on D_001A7390_1 above). */
extern s32 D_001A79F0;

/* 0x140000 - 0x69A2 : the byte the retail reads absolutely. */
extern u8 D_0013965E __attribute__((nosda));

extern char D_00189E20[];
extern char D_00189EA0[];
extern char D_0018C958[];
extern float D_002683EC __attribute__((nosda));

/* The calls func_L20_002B93E0 makes. */
extern void func_L00_002D24E8(void);
extern void func_L18_002D0C00(void);
extern void func_L00_002ACA08(void);
extern void func_L00_002ACF88(char *, char *, char *);
extern void func_L00_002B8930(void);
extern s32 func_00282978(s32);
extern void func_L20_002D7730(s32, s32);
extern s32 func_00288E18(s32, s32);
extern void func_L20_002DEBE0(void);
extern void func_L00_002AE0C8(void);
extern void func_L00_002B9CA8(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9600(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_L00_002A5840(void);
extern void func_L00_002A5CB0(void);
extern void func_L00_002A6008(void);
extern void func_002E5CF8(void *, void *, void *);
extern void func_L00_003080D0(void *);
extern void func_L18_00428100(s32);
extern void func_L00_002A9760(void);
extern void func_002A677C(s32);

/* The hero's per-frame update: the state-1 fixups, then in state 4 (outside cutscenes, not
   in mode 0x6F) the arming check and the resident timestamp catch-up; then the sub-updates,
   gated twice more by the state byte, and the hand-off of the hero's record. Same game code as
   func_L18_002C41F0. */
/* Runs the hero once per frame: checks for damage, updates timers and hands the hero over to the game. */
void func_L20_002B93E0(void)
{
    char *base;
    char *blk;
    char *hero;
    unsigned int now;
    unsigned int then;

    AdvanceHeroAnimation();
    UpdateHeroFrameInput();
    ProcessHeroActionCommand();

    base = gHeroState;
    if (*(u8 *)(base + 0x22B4) == 1) {
        FindHeroLedgeGrab(base + 0x80, base + 0x90, base + 0x550);
        UpdateHeroMotionResponseParameters();
    }
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (D_L20_001AFF00 == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (FastDecTimer(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        YeedilEnterHeroAction(0x91, 1);
                    }
                    if (gCurrentMapIndex == 0x14) {
                        if (D_0013965E == 0) {
                            blk = gSubtitleHistory;
                            if (D_001A7390_1 - *(unsigned int *)(blk + 0x7900) >= 0xB5) {
                                if (RequestSubtitleVoiceLine(0xA15, 0x6C) != 0) {
                                    now = D_001A7390;
                                    then = *(unsigned int *)(blk + 0x7900);
                                    if (then < now) {
                                        *(unsigned int *)(blk + 0x7900) = now;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    base = gHeroState;
    YeedilUpdateHeroActionDecider();
    RebuildRegionObjectMembership();

    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    UpdateDelayedSounds();
    UpdateAllAttachmentRecords();
    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    UpdateHeroMobyFromHero();
    FadeScreenEffect();
    ApplyHeroAxisScales();
    if (*(u8 *)(base + 0x22B4) == 1) {
        D_002683EC = D_001A7CF8;
        UpdateHeroGlowAndExtraManipulators();
        UpdateHeroJointEffect();
        UpdateHeroHeldObject_L00();
        if (*(u32 *)(base + 0x24E4) != 0) {
            PlayMobySound((void *)(*(u32 *)(base + 0x24E4) + 0x10), 0,
                          (void *)(*(u32 *)(base + 0x2290)));
            *(u16 *)(base + 0x2520) = 0x39;
            *(u16 *)(base + 0x2522) = *(u16 *)(base + 0x24E4);
        }
        *(s32 *)(base + 0x24E4) = 0;
    }
    {
        char *pos = gHeroPosition;
        char *g;

        ClearMapBitsAroundPosition(pos);
        g = pos - 0x80;
        if (*(u8 *)(g + 0x22B4) == 4 && D_L20_001AFF00 == 0 && *(s16 *)(g + 0x1E0) == 0 &&
            *(int *)(g + 0x2294) != 0x6F)
            StartReceiverBotSequence(*(int *)(g + 0x2290));
    }
    UpdateHeroMobyProbedHeightBounds();
    hero = gHeroState;
    func_002A677C(*(int *)(hero + 0x2290));
}
