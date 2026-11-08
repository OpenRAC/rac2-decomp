/* 8 November 2026 (m2z, caller-save angle): global.c:1516 tries caller-saves only when find_reg found no register (best_reg < 0), so CALLER_SAVE_PROFITABLE (4*calls < refs) never decides s-register versus call-clobbered while an s-register is free. cc1 -S on the retained C with and without -fno-caller-saves: identical body (0 lines differ). Uses s0-s5 with s6/s7 free across 38 calls; the draw-1 unit s1/s0 tie is priority order, not caller-saves. Angle closed; no check.py runs. */
/* 8 November 2026 (permuter round two, 35 min -j3, whole function, seeded from the C below): best score 60 (base 85), never 0.
/* 8 November 2026, region donors (v101/m8h): same draw-1 unit $s1 preference as func_L02_003FE250; no matched function has the value<10000 sprintf/str=unit shape. Nothing to transcribe. */
/* 8 November 2026 (permuter, 25 min -j4, draw-1 block of func_L02_003FE250 only): best score 60 (base 85), never 0; the
 * gains are invalid C (an extra `if (str)` read before set duplicating arm1) or y3 reused as the value<10000 flag. No winner. */
/* 8 November 2026 (round 18, ~6 runs): best C below 1332/1332 bytes, 5/5 words (was 10/10). Using `text`
 * for the draw-1 label (as in func_L02_003FE250) gives retail's $s2. Using `text` for the 0x2f3f/0x2f42/0x2f43
 * labels fixes their a1/a3 order. The only diff left is draw-1 unit ($s1, retail $s0); same cause as L02:
 * Why unit takes $s1: str gets an $s1 preference from the counts copy (its source temp is local-allocated
 * to $s1), and global.c expand_preferences copies it to unit through arm2's `str = unit` (unit dies there, no
 * conflict). find_reg then takes that copy preference, since $s1 is already "used so far" (local temps and the
 * hud_coord y values come first in the queue). Retail must break this link (no unit/str link, or a conflict).
 * No gain: arm2 with its own `char *p` (unit gets $s0, but p crosses no call, so sched1 moves the copy above the
 * sprintf and p shares arm1's v0); arm2 `str = buffer` or sprintf on buffer (cse makes it str = unit again);
 * do-while(0) around arm2 (+nop, unit still $s1); str set before the arms or before the counts `if`; arm1
 * `do { str = buffer; } while(0)` before the sprintf (meant to make str and unit conflict; 38/28). */
/* 8 November 2026 (round 17, ~15 runs): best C below 1332/1332 bytes (was 1324), 10/10 words (was 23/27).
 * Same fix as func_L02_003FE250 (-fmove-all-movables profile unchanged); the a1/a3 order of the
 * 0x2f3f/0x2f42 draws is also still left, and draw-1 label/unit are $s0/$s1 (retail $s2/$s0).
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
/* 8 November 2026 (round 16, ~38 runs): no gain over the round-15 C below (23/27 words).
 * Counts copy: every form folds str and the buffer address into one register (str before/after the
 * sprintf, via unit/label/p, str set before the counts `if` or before the label call); the RTL shows cse
 * replacing str by the argument temp (or the reverse), so the copy never reaches global-alloc.
 * A do-while(0) group around the counts `str = buffer` gives 1332 bytes but only via an extra nop
 * (24/30). -fno-gcse also gives 1332 bytes, but the D_001395B8 high part is then rebuilt per use (32/34).
 * Swaps: global-alloc (dump -dg) allocates the gcse-made D_001395B8 high pseudo last, after str (str $s4,
 * retail $s5); draw-1 label never conflicts with a pseudo held in $s1, so it takes $s1. No gain: groups
 * around draw 1, its label/unit/value line, the arms, or the SEL tests; label_y(label/str/value, .., one)
 * in draw 1 (one moves off $s1); a local strlen result in the 0x2f3f/0x2f42 draws (a1/a3 order unchanged). */
/* 8 November 2026 (round 15, USA v1.01, check.py only, ~85 runs): best C below 1324/1332 bytes, 0/1 places,
 * 23 mine-only / 27 retail-only words in an opcode-level alignment (the 7 November label_y C gives 109/107
 * the same way). Profile: -O2 -G8 -ffunction-sections -fmove-all-movables (frame 0xD0 with retail's ghost $s7;
 * hoists 8, 0xE0 and `half` = $f20 out of the loop). Changes: every draw uses hud_coord (owner ruling
 * 8 November, result as its own handle), which serializes the three box conversions; y and colour are
 * per-draw locals (mfc1 straight into $s1, colour $s0); D_L11_001B1664/1668/166C plain extern (retail's
 * `lw rX,sym` macro form, not nosda); `one = 1` used by the SEL==1 test gives retail's prologue $s1;
 * draw-1 arm2 `unit = buffer; ...; str = unit;` and arm1 `...; str = buffer;` give retail's copies;
 * `half = 0.5f` at the loop top and again after it; record base as a byte array with *0xe0;
 * counts label in its own local (t1).
 * Left: draw-1 label in $s1 (retail $s2) and str/D_001395B8-hi swapped ($s4/$s5); the counts draw has
 * no `daddu s5,s1` copy (retail keeps the buffer address in $s1 and copies it to str before the inner
 * call; every str/p/unit/buffer form here folds to one register); so the loop-top alignment nop is
 * missing (-8 bytes); a1/a3 move order in the 0x2f3f/0x2f42 draws. No gain: label_y with handle
 * label/state/box/x global (state lengthens a life, x global adds a load), `one` as active in
 * draw 1/counts (one drops to $s4-$s6), one shared y (or y = one), text shared for all labels,
 * colour before y in the late draws, separate per-draw str, -fno-gcse(-fno-rerun-loop-opt). */
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
extern int D_L11_001B1664;
extern int D_L11_001B1668;
extern int D_L11_001B166C;
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
extern unsigned char D_L11_00279BA0[];
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
extern int D_L11_001B3E00;
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
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

void func_L11_00443D78(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*label,*unit,*str,*t1,*t2,*t3,*t4,*t5; int i,value,y2,y3,y4,y5,y6,y7,y8,one,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half;
    one=1;
    func_L11_00443940(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L11_00443CE0(SEL)));
    bx=hud_coord((float)D_L11_001B1660, D_L11_001B3E04, 0.5f);
    by=hud_coord((float)D_L11_001B1664, D_L11_001B3E04, 0.5f);
    bh=hud_coord((float)D_L11_001B1658, D_L11_001B3E04, 0.5f);
    func_002802E0(box,bx,by,D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,bh,D_L11_001B1670,3);
    c1=D_L11_001B1650; func_00280270(box,c1,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[func_L11_0043E108(0)]) goto counts;
    if(SEL==one && !D_001395B8[func_L11_0043E108(one)]) goto counts;
    {
        text=((char *)func_00288FB8(0x2f44)); unit=((char *)func_00288FB8(0x2f5e)); value=func_L11_00442958(SEL);
        if(value<10000) { func_00115DA8(buffer,D_L11_001B15A0,text,value,unit); str=buffer; }
        else { unit=buffer; func_00115DA8(unit,D_L11_001B16E8,text); str=unit; }
        y2=hud_coord((float)D_L11_001B167C, D_L11_001B3E04, 0.5f); c2=D_L11_001B1680; func_0027F5B8(D_L11_001B1678,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[func_L11_0043E108(SEL)]) {
        t1=((char *)func_00288FB8(0x2f3e));
        func_00115DA8(buffer,D_L11_001B16E8,t1,D_001395B8[func_L11_0043E108(SEL)]); str=buffer;
        y3=(int)((float)D_L11_001B16AC * D_L11_001B3E04 + 0.5f); do { c3=D_L11_001B16B0; } while(0); func_0027F5B8(D_L11_001B16A8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { t1=((char *)func_00288FB8(0x2f40)); y4=hud_coord((float)D_L11_001B168C, D_L11_001B3E04, 0.5f); c4=D_L11_001B1690; func_0027F538(D_L11_001B1688,y4,c4,t1,func_001157AC(t1)); }
    for(i=SEL+1;i<13;i++) {
        half=0.5f;
        if(!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
        if(i>=11 && !func_00288D58()) continue;
        if(i==8 && !((MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0))->enabled) continue;
        t2=((char *)func_00288FB8(0x2f41)); y5=hud_coord((float)D_L11_001B169C, D_L11_001B3E04, half); c5=D_L11_001B16A0; func_0027F538(D_L11_001B1698,y5,c5,t2,func_001157AC(t2)); break;
    }
    half=0.5f;
    text=((char *)func_00288FB8(0x2f3f)); y6=hud_coord((float)D_L11_001B16BC, D_L11_001B3E04, half); c6=D_L11_001B16C0; func_0027F538(D_L11_001B16B8,y6,c6,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f42)); y7=hud_coord((float)D_L11_001B16DC, D_L11_001B3E04, half); c7=D_L11_001B16E0; func_0027F538(D_L11_001B16D8,y7,c7,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f43)); y8=hud_coord((float)D_L11_001B16CC, D_L11_001B3E04, half); c8=D_L11_001B16D0; func_0027F538(D_L11_001B16C8,y8,c8,text,func_001157AC(text));
}
