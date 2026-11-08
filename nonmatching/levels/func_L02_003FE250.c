/* 8 November 2026, permuter round 4 (35 min -j3, base 85): best 60 = 1 position, but only via `if (str) <arm1> else <arm1>` before the arms (str read before set: makes str conflict with unit, unit -> $s0), invalid. Also hoisting the 0x2f5e lookup above 0x2f44 (80, changes call order). Declaration order of text/unit/str and arm2 spellings (buffer vs unit in sprintf/str) give no change. C below unchanged, 5 words. */
/* 8 November 2026, region donors (v101/m8h): draw-1 diff is a global-alloc preference (unit $s1); no matched function has the value<10000 sprintf/str=unit shape, and register-role windows over +0x130..+0x180 find no donor. Nothing to transcribe. */
/* 8 November 2026 (permuter, 25 min -j4, draw-1 block of func_L02_003FE250 only): best score 60 (base 85), never 0; the
 * gains are invalid C (an extra `if (str)` read before set duplicating arm1) or y3 reused as the value<10000 flag. No winner. */
/* 8 November 2026 (round 3, ~20 runs): no gain; the C below stays at 5/5 words, all in draw 1 (unit $s1, retail $s0).
 * Why unit takes $s1: str gets an $s1 preference from the counts copy (its source temp is local-allocated
 * to $s1), and global.c expand_preferences copies it to unit through arm2's `str = unit` (unit dies there, no
 * conflict). find_reg then takes that copy preference, since $s1 is already "used so far" (local temps and the
 * hud_coord y values come first in the queue). Retail must break this link (no unit/str link, or a conflict).
 * No gain: arm2 with its own `char *p` (unit gets $s0, but p crosses no call, so sched1 moves the copy above the
 * sprintf and p shares arm1's v0); arm2 `str = buffer` or sprintf on buffer (cse makes it str = unit again);
 * do-while(0) around arm2 (+nop, unit still $s1); str set before the arms or before the counts `if`; arm1
 * `do { str = buffer; } while(0)` before the sprintf (meant to make str and unit conflict; 38/28). */
/* 8 November 2026 (round 2, ~30 runs): best C below 1300/1300 bytes, 5/5 words (was 23/23).
 * Counts-copy wall found: it is gcse's cprop, not cse. With str = buffer AFTER the sprintf, cse1 keeps
 * `str = tmp` (tmp = the sprintf's precomputed buffer argument), but hud_coord's dead tests put the y code in
 * new basic blocks, so cprop (global only) rewrites the strlen/draw uses of str to tmp; cse2 then keeps tmp
 * and deletes the copy. -fno-gcse proves it (counts block exact, but the D_001395B8 high half is rebuilt).
 * Fix used below: counts y written without the dead-test helper, `y3 = (int)((float)Y * scale + 0.5f);`,
 * so copy and uses share one block; then `do { c3 = ...; } while(0);` puts y in $s1 and colour in $s0.
 * The whole counts block now matches. No donor: donor.py best 0.33; no matched src/ C uses 0x2f3e/0x2f44.
 * Left: draw-1 `unit` takes $s1 (retail $s0): global.c expand_preferences passes str's $s1 preference
 * (from the counts copy of local-allocated tmp) to unit through arm2's `str = unit`. No gain: arm1 str
 * before the sprintf, arm2 without unit, str reused by a later label (keeps the copy but that label
 * gets $s5), str initialised to buffer, groups around the counts str, F1 str after y (copy lands late). */
/* 8 November 2026 (USA v1.01, check.py only, ~55 runs): best C below 1300/1300 bytes (was 1296), 0/1 places,
 * 23 mine-only / 23 retail-only words in an opcode-level alignment (the 7 November label_y C gave ~60).
 * Profile: -O2 -G8 -ffunction-sections (own unit L02_003FE250-g8.c; -fmove-all-movables worse here: retail
 * keeps 7, 8 and 0.5 inside the loop). Ported from func_L11_00443D78: hud_coord in the box and text draws,
 * per-draw y/colour locals, D_L02_001B12A4/12A8/12AC plain extern, record base as byte array * 0xe0,
 * draw-1 arm copies. New here: the loop draw uses this level's scaled_coord (L02_003FF6E8-g8.c), whose
 * smaller dead test leaves the rerun loop at 60 insns, so loop.c hoists the table symbol and reduces
 * &D_L02_001B1190[i] to retail's pointer giv (hud_coord: 63 insns, giv rejected); its half is a local h
 * also set before the SEL!=0 draw, so it is not a movable (retail reloads 0.5 in the loop); one `text`
 * for every label fixes the a1/a3 order of the 0x2f3f/0x2f42 draws.
 * Left (same wall as func_L11_00443D78): the counts block has no `addiu s1,sp,0x30; daddu s5,s1` pair;
 * cse folds str and the buffer argument into one pseudo in every form tried (str before/after the
 * sprintf, via unit or a block-local p, sprintf(str,..), do-while groups). Without that pseudo the
 * D_001395B8 base takes $s1 (retail $s4, the reused high register), str $s4 and the high part $s5
 * (retail reversed), draw-1 arm2 copies str before the call, and the loop-top alignment nop appears.
 * -fno-gcse 24/24, -fno-schedule-insns 1292 bytes, -frac2-gcse-unsplit-edges no change. */
/* 7 November 2026, label_y sweep: every text label y is label_y(text or buf, (float)Y, D_L02_001B3E04, 0.5f, 1), mode D_L02_001B3E00 (accepted HUD label idiom, definition above the function). Same profile: 1296/1300 bytes (was 1304), sweep-harness masked aligned diff 129 -> 123. Header box conversions through label_y too: worse. */
/*
 * GPT-6.1 Sol high tier, task v0936, 2026-10-29.
 * USA v1.01, pinned game -O2 -G8 -ffunction-sections.
 * Retained check.py: 1304/1300 bytes, 0 of 1 places match; no linked check.
 * A reused float for input conversion, multiplication, and addition makes
 * the three header conversions serial. It still uses f2 for the working
 * value and f0 for 0.5, where retail uses f0 and f2 respectively; independent
 * style/geometry loads still move into the conversions.
 * The byte-table address is hoisted to entry and stays live into the loop,
 * adding s6; retail starts its high-half lifetime after header conversion
 * and rebuilds the base for the loop. The constant 7 is also loop-hoisted.
 * Inline coordinate arguments and goto-based loop exits tie the old draft;
 * incomplete-array sda on the byte table retains 1304 bytes with worse base
 * sharing. A two-case switch is 1288 bytes with the wrong branch structure.
 * -frac2-gcse-unsplit-edges and -fno-schedule-insns2 do not solve either issue.
 * Canonical text styles are u64, matching their existing C implementations;
 * SDATA gives the unknown-sized pointer table a GP view without a false bound.
 * Next: recover the original UI rounding/layout expression and the byte-table
 * base scopes. All declarations are below; use a dedicated -g8.c unit.
 */
#include "common.h"
extern void func_L02_003FDDE8(char *,int);
extern int func_L02_003FE1B0(int), func_L02_003F9B70(int), func_L02_003FCDF8(int);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int);
extern void func_00280270(void *,u64,char *,int);
extern void func_0027F538(int,int,u64,char *,int);
extern void func_0027F5B8(int,int,u64,char *,int);
extern int func_00288D58(void);
extern float D_L02_001B3E04;
extern int D_L02_001B12A4;
extern int D_L02_001B12A8;
extern int D_L02_001B12AC;
extern char D_L02_001B1228[], D_L02_001B1328[];
extern unsigned char D_001395B8[], D_00139568[];
extern int *D_L02_001B1190[] SDATA(D_L02_001B1190);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L02_00264A70[];
extern int D_L02_001B1294 __attribute__((sda));
extern int D_L02_001B1298 __attribute__((sda));
extern int D_L02_001B129C __attribute__((sda));
extern int D_L02_001B12A0 __attribute__((sda));
extern int D_L02_001B12B0 __attribute__((sda));
extern int D_L02_001B12B8 __attribute__((sda));
extern int D_L02_001B12BC __attribute__((sda));
extern int D_L02_001B12C0 __attribute__((sda));
extern int D_L02_001B12C8 __attribute__((sda));
extern int D_L02_001B12CC __attribute__((sda));
extern int D_L02_001B12D0 __attribute__((sda));
extern int D_L02_001B12D8 __attribute__((sda));
extern int D_L02_001B12DC __attribute__((sda));
extern int D_L02_001B12E0 __attribute__((sda));
extern int D_L02_001B12E8 __attribute__((sda));
extern int D_L02_001B12EC __attribute__((sda));
extern int D_L02_001B12F0 __attribute__((sda));
extern int D_L02_001B12F8 __attribute__((sda));
extern int D_L02_001B12FC __attribute__((sda));
extern int D_L02_001B1300 __attribute__((sda));
extern int D_L02_001B1308 __attribute__((sda));
extern int D_L02_001B130C __attribute__((sda));
extern int D_L02_001B1310 __attribute__((sda));
extern int D_L02_001B1318 __attribute__((sda));
extern int D_L02_001B131C __attribute__((sda));
extern int D_L02_001B1320 __attribute__((sda));
extern int D_L02_001B3E00;
#define SEL (*(short *)(state+0x118))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L02_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

void func_L02_003FE250(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*unit,*str; int i,value,y2,y3,y4,y5,y6,y7,y8,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half,h;
    func_L02_003FDDE8(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L02_003FE1B0(SEL)));
    bx=hud_coord((float)D_L02_001B12A0, D_L02_001B3E04, 0.5f);
    by=hud_coord((float)D_L02_001B12A4, D_L02_001B3E04, 0.5f);
    bh=hud_coord((float)D_L02_001B129C, D_L02_001B3E04, 0.5f);
    func_002802E0(box,bx,by,D_L02_001B12A8,D_L02_001B12AC,D_L02_001B1298,bh,D_L02_001B12B0,3);
    c1=D_L02_001B1294; func_00280270(box,c1,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[func_L02_003F9B70(0)]) goto counts;
    {
        text=((char *)func_00288FB8(0x2f44)); unit=((char *)func_00288FB8(0x2f5e)); value=func_L02_003FCDF8(SEL);
        if(value<10000) { func_00115DA8(buffer,D_L02_001B1228,text,value,unit); str=buffer; }
        else { unit=buffer; func_00115DA8(unit,D_L02_001B1328,text); str=unit; }
        y2=hud_coord((float)D_L02_001B12BC, D_L02_001B3E04, 0.5f); c2=D_L02_001B12C0; func_0027F5B8(D_L02_001B12B8,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[func_L02_003F9B70(SEL)]) {
        text=((char *)func_00288FB8(0x2f3e));
        func_00115DA8(buffer,D_L02_001B1328,text,D_001395B8[func_L02_003F9B70(SEL)]); str=buffer;
        y3=(int)((float)D_L02_001B12EC * D_L02_001B3E04 + 0.5f); do { c3=D_L02_001B12F0; } while(0); func_0027F5B8(D_L02_001B12E8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)func_00288FB8(0x2f40)); h=0.5f; y4=hud_coord((float)D_L02_001B12CC, D_L02_001B3E04, h); c4=D_L02_001B12D0; func_0027F538(D_L02_001B12C8,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<14;i++) {
        if(!D_001395B8[func_L02_003F9B70(D_L02_001B1190[i][2])]) continue;
        if(i>=12 && !func_00288D58()) continue;
        if(i==7 && !((MenuRecord *)(D_L02_00264A70 + D_00139568[0x1e] * 0xe0))->enabled) continue;
        if(i==8 && !((MenuRecord *)(D_L02_00264A70 + D_00139568[0x2a] * 0xe0))->enabled) continue;
        text=((char *)func_00288FB8(0x2f41)); h=0.5f; y5=scaled_coord(D_L02_001B12DC, D_L02_001B3E04, h, 1); c5=D_L02_001B12E0; func_0027F538(D_L02_001B12D8,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)func_00288FB8(0x2f3f)); y6=hud_coord((float)D_L02_001B12FC, D_L02_001B3E04, half); c6=D_L02_001B1300; func_0027F538(D_L02_001B12F8,y6,c6,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f42)); y7=hud_coord((float)D_L02_001B131C, D_L02_001B3E04, half); c7=D_L02_001B1320; func_0027F538(D_L02_001B1318,y7,c7,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f43)); y8=hud_coord((float)D_L02_001B130C, D_L02_001B3E04, half); c8=D_L02_001B1310; func_0027F538(D_L02_001B1308,y8,c8,text,func_001157AC(text));
}
