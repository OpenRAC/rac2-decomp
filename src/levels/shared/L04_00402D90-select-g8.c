#include "common.h"

/* Field accesses at byte offsets, written as members of an unnamed struct. */
#define S32_AT(p,o) (((struct { char pad[o]; int v; } *)(p))->v)
#define PTR_AT(p,o) (((struct { char pad[o]; char *v; } *)(p))->v)
#define U16_AT(p,o) (((struct { char pad[o]; unsigned short v; } *)(p))->v)

extern int D_L04_001B0978 __attribute__((sda)), D_L04_001B0904 __attribute__((sda)), D_L04_001B090C __attribute__((sda));
/* The flag at +0x14 is element 5, as in L04_00412308-g8.c; the offset form keeps
   retail's two-word $at store, which never takes a call's delay slot. */
extern int D_L04_001A8ED0[] MACRO_ADDR;
extern char D_00189E20[] NOT_SDA, D_00138180[] NOT_SDA;
extern char *D_L04_001B24DC, *D_L04_001B08F4 __attribute__((sda));
/* Five 64-byte entries; a set bit 28 in flags lets the entry be chosen. The
   entries are members of one object, so the row address adds base first. */
typedef struct { int head; int flags; char rest[56]; } SelectEntry;
extern struct { SelectEntry entry[5]; } D_L04_002C63C0 NOT_SDA;
extern void func_00132AF8(int), func_00132B28(int);
extern int func_00132028(void);
extern void func_002B72E8(int), func_002B7320(void);
extern void func_L04_0040A3B8(char *, int);
extern int func_L04_002E7C08(int,int);
extern void func_L04_0040E248(char *, char *), func_L04_0040AC30(char *,char *);
extern int func_002E5E58(int,int,void *);
extern int func_L04_0040A1D0(int);
/* Five-entry selection: pad bits 0x8000/0x2000 move D_L04_001B0904 with wraparound;
   0x840 takes the entry if its flag is set or func_L04_0040A1D0 of the previous entry
   is positive (sound 4, else 5), and 0x10 ends through func_L04_0040AC30. loop.c
   reverses the count-up slot loop, so its counter is set after the hoisted -1. */
void func_L04_0040BA68(char *controller, char *vars)
{
    int done = 0;
    int *slot, i;
    char *obj, *extra, *child, *base;
    if (!D_L04_001B0978) {
        D_L04_001A8ED0[5] = 1;
        SendSoundCommand22(0x5d); music_Pause(0); snd_Pump();
        D_L04_001A8ED0[0] = 1;
        ResetRacerState(controller,0);
        gSelectedRaceIndex = gCurrentRaceIndex;
        D_L04_001B0978 = 1;
    }
    if (S32_AT(gHeroState,0x2294) != 0x31) EnterHeroState_L04(0x31,1);
    U16_AT(controller,0x34) |= 0x41;
    if (S32_AT(vars,0x1dc) != -1) {
        obj = gMobyPool_L04 + (S32_AT(vars,0x1dc) << 8);
        extra = D_L04_001B08F4;
        U16_AT(obj,0x34) |= 0x41;
        if (extra) U16_AT(extra,0x34) |= 0x41;
    }
    base=gMobyPool_L04;
    slot=(int *)(vars+0x1e4);
    for (i=0;i<21;i++) {
        if (slot[i] != -1) {
            obj=base+(slot[i]<<8);
            U16_AT(obj,0x34)|=0x41;
            child=PTR_AT(PTR_AT(obj,0x68),0x8c);
            if (child) U16_AT(child,0x34)|=0x41;
        }
    }
    ReleaseRacerSoundHandles(controller,vars);
    S32_AT(gHeroState,0x24a0)=26;
    gHeroState[0x22b5]=1;
    S32_AT(PTR_AT(gHeroState,0x2290),0x98)=0;
    if (S32_AT(gPadState,0x1c4)&0x8000) {
        PlaySoundFromGlobalBank(3,0,0);
        gSelectedRaceIndex=gSelectedRaceIndex-1;
        if (gSelectedRaceIndex < 0) gSelectedRaceIndex=4;
    } else if (S32_AT(gPadState,0x1c4)&0x2000) {
        PlaySoundFromGlobalBank(3,0,0);
        gSelectedRaceIndex=gSelectedRaceIndex+1;
        if (gSelectedRaceIndex >= 5) gSelectedRaceIndex=0;
    }
    if (S32_AT(gPadState,0x1c4)&0x840) {
        if ((gRaceChallengeTable.entry[gSelectedRaceIndex].flags&0x10000000) || (gSelectedRaceIndex>0 && GetCourseWinCount(gSelectedRaceIndex-1)>0)) {
            PlaySoundFromGlobalBank(4,0,0); done=1;
            gCurrentRaceIndex=gSelectedRaceIndex;
            controller[0xbc]=2;
        } else PlaySoundFromGlobalBank(5,0,0);
    } else if (S32_AT(gPadState,0x1c4)&0x10) {
        PlaySoundFromGlobalBank(4,0,0);done=1;
        ReleaseRacerLinkState(controller,vars);
        S32_AT(vars,0x320)=-1;controller[0x20]=4;
    }
    if (done) {
        SendSoundCommand23(0x5d);music_Unpause();snd_Pump();
        D_L04_001A8ED0[5]=0;D_L04_001A8ED0[0]=0;D_L04_001B0978=0;
    }
}
