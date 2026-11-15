/* func_L04_00422318: Barlow level object update (hint triggers and the vendor checks).
 *
 * -G8 because the short globals below are gp-relative. -frac2-gcse-unsplit-edges keeps the
 * q->active read at the join after the call test: with split edges PRE inserts it on the
 * critical edge instead. Retail reads q->active three times; thread_jumps sends the nonzero
 * first test to a fresh label, so cse1 does not know the value at the D_L04_001B0D00 test,
 * and PRE turns the else-if read into a copy.
 * D_001A7AF8[0x27] is an unsplit address (MACRO_ADDR) because retail loads it with its own
 * lui at each of its two tests, while the neighbouring flags are gp-relative.
 * Statistic record 52 uses the same saturating update as the other hint records
 * (see func_00289178 and L12_00398E50-g8.c): the test folds, and the time is read again.
 */
#include "common.h"
typedef struct { unsigned short count, pad; unsigned int maximum; int levels; } Statistics;
typedef struct { unsigned char b[0x76]; } HintFlags;
typedef union { char b[0x2600]; int i[0x980]; char *p[0x980]; } HeroState;
extern HeroState D_00189E20;
extern char D_00189EA0[];
extern Statistics D_0018C958[], D_0018C750[], D_0018C360[];
extern HintFlags D_001395B8;
extern char D_L04_00296748[];
extern unsigned char D_001A7AFA, D_001A7B05;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_001A79F0;
extern unsigned int D_001A7390;
extern char *D_L04_001B24DC __attribute__((sda));
extern int D_L04_001B0CFC __attribute__((sda));
extern int D_L04_001B0D00 __attribute__((sda));

typedef struct { void *object; int state; float intensity; } HintFlare;
extern HintFlare D_L04_001B9980;
extern int func_002ACBC8(void *,int);
extern int func_00288E18(int,int);
extern void func_0028A180(int,int);
extern void func_L04_00422D40(void *);
extern void func_L00_00382CE8(void *);
extern float func_L04_00422A00(void *);
extern void func_L04_00422DA8(void);
extern void func_L00_002E6CF0(void *,void *);
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
static __inline__ unsigned int BarlowLevelBit(int level) { return 1U << level; }

static __inline__ unsigned int BarlowHintPlayed(Statistics *hint, int level) { return hint->levels & BarlowLevelBit(level); }

typedef struct { char pad[0x14]; unsigned char active; } BarlowVendor;

/* Watches the player's progress on this level and shows the right hint messages, and also checks on the vendor. */
void func_L04_00422318(char *moby)
{
    char *vars=*(char **)(moby+0x68);
    BarlowVendor *vendor;
    unsigned int now, old;
    switch(B(moby,0x20)) {
    case 0:
        B(moby,0x30)=255; I(vars,0x10)=2400; B(moby,0x20)=1;
        ResetLensFlareLightPosition(moby);
        InitSparkleTable(moby);
        break;
    case 1:
        if (IsPointInCuboid(gHeroPosition,I(vars,0)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !gSubtitleHistory[2519].count && !D_0018C360[115].count) {
            RequestSubtitleVoiceLine(0x9D7,0x2E); gSubtitleHistory[46].count=65535;
        }
        if (IsPointInCuboid(gHeroPosition,I(vars,0xC)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7AFA) {
            if (++I(vars,0x10)>1200) { RequestSubtitleVoiceLine(0x9DE,0x35); I(vars,0x10)=0; }
        }
        if (IsPointInCuboid(gHeroPosition,I(vars,0x28)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && D_001A7AFA && (I(gHeroPosition,0x2214)==0 || I(gHeroPosition,0x2214)==2) && (((D_001395B8.b[116]>>gCurrentMapIndex)^1)&1)) {
            now=D_001A7390; old=gSubtitleHistory[35].maximum;
            if(now-old>300 || !old) RequestSubtitleVoiceLine(0x9CC,0x23);
            else if(old<now) gSubtitleHistory[35].maximum=now;
        }
        if(IsPointInCuboid(gHeroPosition,I(vars,0x40))) D_001395B8.b[116]|=BarlowLevelBit(gCurrentMapIndex);
        if(IsPointInCuboid(gHeroPosition,I(vars,8)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7B05 && gSubtitleHistory[49].levels>=0) RequestSubtitleVoiceLine(0x9DA,0x31);
        if(gHeroState.i[2215]==18 && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && IsPointInCuboid(gHeroState.b+0x80,I(vars,0x14))) {
                ++I(vars,0x18);
                if(IsPointInCuboid(gHeroState.b+0x80,I(vars,0x14)) && I(vars,0x18)>240) {
                    now=D_001A7390; old=gSubtitleHistory[50].maximum;
                    if(now-old>1080 || !old) RequestSubtitleVoiceLine(0x9DB,0x32);
                    else if(old<now) gSubtitleHistory[50].maximum=now;
                }
        } else {
            if(gHeroState.i[2215]==17) gSubtitleHistory[50].count=65535;
            else I(vars,0x18)=0;
        }
        if(!(D_001395B8.b[117]&16) && IsPointInCuboid(gHeroPosition,I(vars,0x44)) && *(short *)(gHeroPosition+0x247C) && (D_001A7390-gProgressStatistics[38].maximum>432000 || !gProgressStatistics[38].count)) {
            D_001395B8.b[117]|=16; QueueHintMessage(0xA3C,0x93);
        }
        if(IsPointInCuboid(gHeroPosition,I(vars,0x48)) && D_001A7390-gProgressStatistics[20].maximum>72000 && !(BarlowHintPlayed(&gSubtitleHistory[32], gCurrentMapIndex))) RequestSubtitleVoiceLine(0x9C9,0x20);
        if(gItemOwnedFlags[0x27] && IsPointInCuboid(gHeroPosition,I(vars,0x2C))) {
            now=D_001A7390; old=gSubtitleHistory[51].maximum;
            if(now-old>1080 || !old) RequestSubtitleVoiceLine(0x9DC,0x33);
            else if(old<now) gSubtitleHistory[51].maximum=now;
            if(gHeroState.i[1170]==39 && gHeroState.p[0x1220/4]) {
                char *vehicle=*(char **)(gHeroState.p[0x1220/4]+0x68);
                if(I(vehicle,0x54) && !I(vehicle,0x5C)) gSubtitleHistory[51].count=65535;
            }
        }
        if(I(vars,0x1C)!=-1 && gItemOwnedFlags[0x27]) {
            vendor=*(BarlowVendor **)(gMobyPool_L04+(I(vars,0x1C)<<8)+0x68);
            if(IsPointInCuboid(gHeroPosition,I(vars,0x20))) {
                if(!vendor->active && !D_L04_001B0CFC) {
                    if(gSubtitleHistory[52].count) {
                        old=gSubtitleHistory[52].maximum;
                        if(D_001A7390-old>1080 || !old) RequestSubtitleVoiceLine(0x9DD,0x34);
                        else if(old<D_001A7390) gSubtitleHistory[52].maximum=D_001A7390;
                        return;
                    }
                    if(gSubtitleHistory[52].count<65535) gSubtitleHistory[52].count++;
                    if(gSubtitleHistory[52].maximum<D_001A7390) gSubtitleHistory[52].maximum=D_001A7390;
                    gSubtitleHistory[52].levels = (gSubtitleHistory[52].levels | BarlowLevelBit(gCurrentMapIndex)) | 0x80000000;
                    return;
                }
            }
            if(vendor->active && D_L04_001B0D00) { D_L04_001B0CFC=1; gSubtitleHistory[52].count=65535; }
            else if(!vendor->active) D_L04_001B0D00=1;
        }
        if(IsPointInCuboid(gHeroPosition,I(vars,4)) && D_001A7390-gProgressStatistics[9].maximum>108000 && !(BarlowHintPlayed(&gSubtitleHistory[12], gCurrentMapIndex))) RequestSubtitleVoiceLine(0x9B5,12);
        break;
    }
    gLensFlare.intensity=QueryScreenPointValue(moby);
    AddDrawCallbackToList1(DrawLensFlare_L04,moby);
}
