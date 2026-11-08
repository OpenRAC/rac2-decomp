/* 9 November 2026 (o16): measured with the catalogue row shifted +8 (to 0x002DC3D0, 848 bytes),
 * the C below equals retail in all 214 instructions (opcodes and registers; relocations not
 * compared). The +8 shift itself stays unproved under docs/MATCHING-BLOCKERS.md "Entry still
 * unproved" (no traced entry; a store at the start is not an entry witness); the owner chose to
 * keep the 856-byte row. Reopen only on a traced entry or object-origin evidence. */
/* 8 November 2026: no RAC1/RAC4 twin. ~/rac1-decomp/src and ~/rac4-decomp have no timed text-page state machine with these text ids, timers (180/240/300) or the 0x900 pad test; the open question stays the catalogue entry (+0 vs +8). */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss. Final state: the catalogue entry address itself is in doubt (see the entry hypothesis below); this is a catalogue question, not C. */
/* 3 November 2026: entry hypothesis remains held after a fresh US 28-placement
 * audit. The canonical name is absent from the PAL and US2 catalogues.
 * The 856-byte row begins with `sw $zero,0x50($a0); nop`; the previous body's
 * complete control flow ends before it (boot return 0x002DC3BC, delay slot
 * 0x002DC3C0, alignment nop 0x002DC3C4). No direct transfer, aligned loaded-word
 * candidate or straight-line address construction identifies +0, +4 or +8.
 * EE scans exclude .vutext; arbitrary computed indirect targets are unresolved.
 * The twenty words at boot 0x0026CDF0 are internal case targets consumed by
 * the state-indexed load and `jr $a0`, not callback witnesses for the entry.
 * Resetting state before a multi-state switch is suspicious, but does not prove
 * that the store belongs to a different function. No entry correction is made.
 *
 * Historical retained measurement (31 October): this ordinary C body was
 * 848 bytes under -O2 -G8 -ffunction-sections, 0/28 against the unchanged row;
 * a private +8 comparison reported 28/28. That is not boundary or linked-build
 * proof and was not rerun here. Preserve the complete draft without promotion.
 * Reopen on an independently traced call/callback entry or object-origin
 * evidence that distinguishes +8 from the store-prefixed entry.
 */
#include "common.h"
/* The menu system D_001F2840 and the input words at D_00138180. */
typedef struct { char pad[0x1c0]; u64 held; } InputC3;
typedef struct { char pad[0x14]; u8 *owner; int next; char pad1[0xec-0x1c]; int mode; char pad2[0x134-0xf0]; int active; } CtxC3;
/* A timed text page: each state shows a text for a while, scrolls it, then waits. */
typedef struct {
    char pad00[0x34];
    int text;     /* 0x34: a text id or an address */
    char pad38[4];
    int scroll;   /* 0x3C */
    int timer;    /* 0x40 */
    char pad44[0x50 - 0x44];
    int state;    /* 0x50 */
    int done;     /* 0x54: cleared and tested here, set elsewhere */
} PageC3;
extern u8 D_00138180[],D_001F2840[],D_00261A08[],D_00261AB8[],D_00261B78[];
extern u8 D_001ABBA0[] SDATA(D_001ABBA0);
extern u8 D_001ABBB8[] SDATA(D_001ABBB8);
extern int D_0025ED8C[];
int func_002DC3C8(PageC3 *menu)
{
    int fast,previous,value,result;
    u8 *pad=D_00138180;
    u8 *ctx=D_001F2840;
    u8 *owner;
    fast=(((InputC3 *)pad)->held&15)==15;
    if (!((CtxC3 *)ctx)->mode || (fast && ((u32)((InputC3 *)pad)->held&16))) {
        if ((((u32 *)&((InputC3 *)pad)->held)[1]&0x900) && !((CtxC3 *)ctx)->active) return 1;
        { u8 *pad2=D_00138180;
        if (*(int *)(pad2+0x1c4)&16) {
            owner=((CtxC3 *)D_001F2840)->owner;value=*(int *)(owner+0xe0);
            if (value) { ((CtxC3 *)D_001F2840)->next=value; }
            else if (!((CtxC3 *)D_001F2840)->active) { result=-1; goto back_done; }
            result=0;
back_done:
            return result;
        }
        }
    }
    previous=menu->timer;
    menu->timer=previous-1;if (fast) menu->timer=previous-2;
    if (menu->timer<0) menu->timer=0;
    switch (menu->state) {
    case 0:
        ++menu->state;menu->timer=180;menu->scroll=0;
        D_0025ED8C[0]=0x33c0;menu->text=(int)D_00261A08;break;
    case 1:case 5:case 8:case 12:case 16:
        if (menu->timer) break;
        menu->done=0;++menu->state;break;
    case 2:case 6:case 9:case 13:case 17:
        previous=menu->scroll;menu->scroll=previous+10;
        if (fast) menu->scroll=previous+20;
        if (menu->done) {menu->timer=180;++menu->state;}break;
    case 4:
        if (menu->timer) break;
        menu->state=5;menu->timer=180;menu->scroll=0;
        D_0025ED8C[0]=0x3410;menu->text=(int)D_00261AB8;break;
    case 3:
        if (menu->timer) break;
        D_0025ED8C[0]=0x340e;menu->text=0x340f;menu->timer=240;
        menu->scroll=0;++menu->state;break;
    case 7:
        if (menu->timer) break;
        D_0025ED8C[0]=0x3458;menu->text=(int)D_00261B78;menu->timer=240;
        ++menu->state;menu->scroll=0;break;
    case 10:
        if (menu->timer) break;
        D_0025ED8C[0]=0x3488;menu->text=0x3489;menu->timer=240;
        menu->scroll=0;++menu->state;break;
    case 11:
        if (menu->timer) break;
        menu->scroll=0;menu->timer=180;D_0025ED8C[0]=0x348a;
        menu->text=(int)D_001ABBA0;menu->state=12;break;
    case 14:
        if (menu->timer) break;
        D_0025ED8C[0]=0;menu->text=0x349b;menu->timer=240;
        menu->scroll=0;++menu->state;break;
    case 15:
        if (menu->timer) break;
        menu->scroll=0;menu->timer=180;D_0025ED8C[0]=0x349d;
        menu->text=(int)D_001ABBB8;menu->state=16;break;
    case 18:
        if (menu->timer) break;
        D_0025ED8C[0]=0;menu->timer=300;menu->text=0;++menu->state;break;
    case 19:
        if (menu->timer) break;
        if (((CtxC3 *)D_001F2840)->mode) return 1;
    }
    return 0;
}
