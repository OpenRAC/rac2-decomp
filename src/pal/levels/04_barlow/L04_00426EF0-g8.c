/* func_PAL_L04_00426EF0, the PAL copy of func_L04_00422318: Barlow level object update (hint
 * triggers and the vendor checks). The same C, where the time is scaled to 50 Hz at each read and
 * the intervals become 250, 900, 200, 360000, 60000 and 90000. Each repeated division is merged
 * by cse but keeps its divide-by-zero trap, so the reads stay written out. Record 52 reads
 * maximum directly: an `old` local there moves the load ahead of the division.
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

void func_PAL_L04_00426EF0(char *m)
{
    char *p=*(char **)(m+0x68);
    BarlowVendor *q;
    unsigned int old;
    switch(B(m,0x20)) {
    case 0:
        B(m,0x30)=255; I(p,0x10)=2400; B(m,0x20)=1;
        func_L04_00422D40(m);
        func_L00_00382CE8(m);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0,I(p,0)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_0018C958[2519].count && !D_0018C360[115].count) {
            func_00288E18(0x9D7,0x2E); D_0018C958[46].count=65535;
        }
        if (func_002ACBC8(D_00189EA0,I(p,0xC)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7AFA) {
            if (++I(p,0x10)>1200) { func_00288E18(0x9DE,0x35); I(p,0x10)=0; }
        }
        if (func_002ACBC8(D_00189EA0,I(p,0x28)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && D_001A7AFA && (I(D_00189EA0,0x2214)==0 || I(D_00189EA0,0x2214)==2) && (((D_001395B8.b[116]>>D_001A79F0)^1)&1)) {
            old=D_0018C958[35].maximum;
            if(((s32)(D_001A7390) * 5 + 2) / 6-old>250 || !old) func_00288E18(0x9CC,0x23);
            else if(old<((s32)(D_001A7390) * 5 + 2) / 6) D_0018C958[35].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
        }
        if(func_002ACBC8(D_00189EA0,I(p,0x40))) D_001395B8.b[116]|=BarlowLevelBit(D_001A79F0);
        if(func_002ACBC8(D_00189EA0,I(p,8)) && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && !D_001A7B05 && D_0018C958[49].levels>=0) func_00288E18(0x9DA,0x31);
        if(D_00189E20.i[2215]==18 && !I(D_L04_00296748,0) && I(D_L04_00296748,0x24)==-1 && func_002ACBC8(D_00189E20.b+0x80,I(p,0x14))) {
                ++I(p,0x18);
                if(func_002ACBC8(D_00189E20.b+0x80,I(p,0x14)) && I(p,0x18)>200) {
                    old=D_0018C958[50].maximum;
                    if(((s32)(D_001A7390) * 5 + 2) / 6-old>900 || !old) func_00288E18(0x9DB,0x32);
                    else if(old<((s32)(D_001A7390) * 5 + 2) / 6) D_0018C958[50].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                }
        } else {
            if(D_00189E20.i[2215]==17) D_0018C958[50].count=65535;
            else I(p,0x18)=0;
        }
        if(!(D_001395B8.b[117]&16) && func_002ACBC8(D_00189EA0,I(p,0x44)) && *(short *)(D_00189EA0+0x247C) && (((s32)(D_001A7390) * 5 + 2) / 6-D_0018C750[38].maximum>360000 || !D_0018C750[38].count)) {
            D_001395B8.b[117]|=16; func_0028A180(0xA3C,0x93);
        }
        if(func_002ACBC8(D_00189EA0,I(p,0x48)) && ((s32)(D_001A7390) * 5 + 2) / 6-D_0018C750[20].maximum>60000 && !(BarlowHintPlayed(&D_0018C958[32], D_001A79F0))) func_00288E18(0x9C9,0x20);
        if(D_001A7AF8[0x27] && func_002ACBC8(D_00189EA0,I(p,0x2C))) {
            old=D_0018C958[51].maximum;
            if(((s32)(D_001A7390) * 5 + 2) / 6-old>900 || !old) func_00288E18(0x9DC,0x33);
            else if(old<((s32)(D_001A7390) * 5 + 2) / 6) D_0018C958[51].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
            if(D_00189E20.i[1170]==39 && D_00189E20.p[0x1220/4]) {
                char *vehicle=*(char **)(D_00189E20.p[0x1220/4]+0x68);
                if(I(vehicle,0x54) && !I(vehicle,0x5C)) D_0018C958[51].count=65535;
            }
        }
        if(I(p,0x1C)!=-1 && D_001A7AF8[0x27]) {
            q=*(BarlowVendor **)(D_L04_001B24DC+(I(p,0x1C)<<8)+0x68);
            if(func_002ACBC8(D_00189EA0,I(p,0x20))) {
                if(!q->active && !D_L04_001B0CFC) {
                    if(D_0018C958[52].count) {
                        if(((s32)(D_001A7390) * 5 + 2) / 6-D_0018C958[52].maximum>900 || !D_0018C958[52].maximum) func_00288E18(0x9DD,0x34);
                        else if(D_0018C958[52].maximum<((s32)(D_001A7390) * 5 + 2) / 6) D_0018C958[52].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                        return;
                    }
                    if(D_0018C958[52].count<65535) D_0018C958[52].count++;
                    if(D_0018C958[52].maximum<((s32)(D_001A7390) * 5 + 2) / 6) D_0018C958[52].maximum=((s32)(D_001A7390) * 5 + 2) / 6;
                    D_0018C958[52].levels = (D_0018C958[52].levels | BarlowLevelBit(D_001A79F0)) | 0x80000000;
                    return;
                }
            }
            if(q->active && D_L04_001B0D00) { D_L04_001B0CFC=1; D_0018C958[52].count=65535; }
            else if(!q->active) D_L04_001B0D00=1;
        }
        if(func_002ACBC8(D_00189EA0,I(p,4)) && ((s32)(D_001A7390) * 5 + 2) / 6-D_0018C750[9].maximum>90000 && !(BarlowHintPlayed(&D_0018C958[12], D_001A79F0))) func_00288E18(0x9B5,12);
        break;
    }
    D_L04_001B9980.intensity=func_L04_00422A00(m);
    func_L00_002E6CF0(func_L04_00422DA8,m);
}
