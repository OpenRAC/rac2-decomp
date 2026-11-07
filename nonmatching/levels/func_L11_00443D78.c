/* 7 November 2026, label_y sweep: every text label y=Y(v) is label_y(text, (float)v, D_L11_001B3E04, 0.5f, 1), mode D_L11_001B3E00; the box keeps Y() (accepted HUD label idiom, definition above the function). Same profile: 1344/1332 bytes (was 1324), sweep-harness masked aligned diff 278 -> 143. Handle = the label x global: worse. */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1324/1332 bytes, 0/1 placements; first difference size mismatch.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* GPT-6.1 Sol high-effort retained attempt, USA v1.01.
 * Profile: dedicated -O2 -G8 -ffunction-sections unit.
 * Best check.py result: 1324 bytes versus retail 1332, 0 of 1 places match.
 * Retail serializes the three initial coordinate conversions; this C computes
 * their float expressions together and converts to integers at argument setup.
 * Saved-register allocation, some branch-likely choices, record-base address
 * folding and load scheduling also differ. The 0xD0 frame size agrees.
 * Ten checker runs on the pinned upstream toolchain did not improve the draft.
 * Correcting text-drawing style arguments to u64 is byte-neutral, as is using
 * direct coordinate arguments with a truthful incomplete GP pointer table.
 * Disabling sched1 gives 1312 bytes; disabling both schedulers gives 1332 bytes
 * with the wrong 0xC0 frame and extensive differences. -mno-split-addresses
 * gives 1296 bytes; -fno-gcse gives 1324; -fno-expensive-optimizations gives
 * 1312. Separate per-draw locals plus macro-address declarations give 1312.
 * A long conversion introduces runtime helper calls (1388 bytes), so retain int.
 * Allocator diagnostics show the fix:SI results combined into call arguments;
 * investigate a naturally different lowering before retrying scheduling flags.
 * All required declarations are included below. No linked build was run.
 * 3 November 2026 (Claude Opus 5.5): with the current compiler this body is
 * 1324/1332 bytes and about 175 rows. Writing Y() as a static __inline__
 * function (int or float parameter, with or without a float local) changes
 * nothing, so inlining boundaries are not what serializes retail's three
 * conversions.
 */
#include "common.h"
extern void func_L11_00443940(void *,int);
extern int func_L11_00443CE0(int), func_L11_0043E108(int), func_L11_00442958(int), func_00288D58(void);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_0027F5B8(int,int,u64,char *,int), func_0027F538(int,int,u64,char *,int);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int),func_00280270(void *,u64,char *,int);
extern int D_L11_001B1650 __attribute__((sda));
extern int D_L11_001B1654 __attribute__((sda));
extern int D_L11_001B1658 __attribute__((sda));
extern int D_L11_001B165C __attribute__((sda));
extern int D_L11_001B1660 __attribute__((sda));
extern int D_L11_001B1664 __attribute__((nosda));
extern int D_L11_001B1668 __attribute__((nosda));
extern int D_L11_001B166C __attribute__((nosda));
extern int D_L11_001B1670 __attribute__((sda));
extern int D_L11_001B1674 __attribute__((sda));
extern int D_L11_001B1678 __attribute__((sda));
extern int D_L11_001B167C __attribute__((sda));
extern int D_L11_001B1680 __attribute__((sda));
extern int D_L11_001B1684 __attribute__((sda));
extern int D_L11_001B1688 __attribute__((sda));
extern int D_L11_001B168C __attribute__((sda));
extern int D_L11_001B1690 __attribute__((sda));
extern int D_L11_001B1694 __attribute__((sda));
extern int D_L11_001B1698 __attribute__((sda));
extern int D_L11_001B169C __attribute__((sda));
extern int D_L11_001B16A0 __attribute__((sda));
extern int D_L11_001B16A4 __attribute__((sda));
extern int D_L11_001B16A8 __attribute__((sda));
extern int D_L11_001B16AC __attribute__((sda));
extern int D_L11_001B16B0 __attribute__((sda));
extern int D_L11_001B16B4 __attribute__((sda));
extern int D_L11_001B16B8 __attribute__((sda));
extern int D_L11_001B16BC __attribute__((sda));
extern int D_L11_001B16C0 __attribute__((sda));
extern int D_L11_001B16C4 __attribute__((sda));
extern int D_L11_001B16C8 __attribute__((sda));
extern int D_L11_001B16CC __attribute__((sda));
extern int D_L11_001B16D0 __attribute__((sda));
extern int D_L11_001B16D4 __attribute__((sda));
extern int D_L11_001B16D8 __attribute__((sda));
extern int D_L11_001B16DC __attribute__((sda));
extern int D_L11_001B16E0 __attribute__((sda));

extern float D_L11_001B3E04;
extern char D_L11_001B15A0[],D_L11_001B16E8[];
extern unsigned char D_00139568[],D_001395B8[];
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern MenuRecord D_L11_00279BA0[];
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
#define Y(a) ((int)((float)(a)*D_L11_001B3E04+0.5f))
extern int D_L11_001B3E00;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L11_00443D78(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*label,*unit; int i,value,y; u64 color;
    func_L11_00443940(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L11_00443CE0(SEL)));
    func_002802E0(box,Y(D_L11_001B1660),Y(D_L11_001B1664),D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,Y(D_L11_001B1658),D_L11_001B1670,3);
    color=D_L11_001B1650; func_00280270(box,color,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[func_L11_0043E108(0)]) goto counts;
    if(SEL==1 && !D_001395B8[func_L11_0043E108(1)]) goto counts;
    {
        label=((char *)func_00288FB8(0x2f44)); unit=((char *)func_00288FB8(0x2f5e)); value=func_L11_00442958(SEL);
        if(value<10000) func_00115DA8(buffer,D_L11_001B15A0,label,value,unit);
        else func_00115DA8(buffer,D_L11_001B16E8,label);
        text=buffer; y=label_y(text, (float)D_L11_001B167C, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B1680; func_0027F5B8(D_L11_001B1678,y,color,text,func_001157AC(text));
    }
counts:
    if(D_001395B8[func_L11_0043E108(SEL)]) {
        label=((char *)func_00288FB8(0x2f3e));
        func_00115DA8(buffer,D_L11_001B16E8,label,D_001395B8[func_L11_0043E108(SEL)]);
        text=buffer; y=label_y(text, (float)D_L11_001B16AC, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B16B0; func_0027F5B8(D_L11_001B16A8,y,color,text,func_001157AC(text));
    }
    if(SEL!=0) { text=((char *)func_00288FB8(0x2f40)); y=label_y(text, (float)D_L11_001B168C, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B1690; func_0027F538(D_L11_001B1688,y,color,text,func_001157AC(text)); }
    for(i=SEL+1;i<13;i++) {
        if(!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
        if(i>=11 && !func_00288D58()) continue;
        if(i==8 && !D_L11_00279BA0[D_00139568[0x1e]].enabled) continue;
        text=((char *)func_00288FB8(0x2f41)); y=label_y(text, (float)D_L11_001B169C, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B16A0; func_0027F538(D_L11_001B1698,y,color,text,func_001157AC(text)); break;
    }
    text=((char *)func_00288FB8(0x2f3f)); y=label_y(text, (float)D_L11_001B16BC, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B16C0; func_0027F538(D_L11_001B16B8,y,color,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f42)); y=label_y(text, (float)D_L11_001B16DC, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B16E0; func_0027F538(D_L11_001B16D8,y,color,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f43)); y=label_y(text, (float)D_L11_001B16CC, D_L11_001B3E04, 0.5f, 1); color=D_L11_001B16D0; func_0027F538(D_L11_001B16C8,y,color,text,func_001157AC(text));
}
