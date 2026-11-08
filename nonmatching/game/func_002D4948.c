/* 8 November 2026 (Sonnet round 2): re-measured 1216/1220. Search forms tried now: `D = 0; for (; D < 21; D++)` and a loop with the increment last (both 1216, unchanged), do-while with a local i and `D = i` after (1180), `D = i` stored inside the loop (1204), `i = D` index copy (1204), `settings` in the test instead of the global (1216, 275 words, worse). Greedy sweep of every declaration position among kind3/kind4/settings/a..g/line/n/i: no gain. Permuter (-j2, 1500 s): only the 1105 dead `do { } while (0)` again. The $a3 copy is still missing. */
/* 8 November 2026 (Sonnet round): re-measured 1216/1220. A `j` loop index with `i = j;` copy in the body and a final `D_001ABA74 = j` gives 1200 bytes. 25 min permuter (-j2, base 1850): best 1105 is only an empty `do { } while (0);` before the break (not honest); nothing else. */
/* 7 November 2026: still 1216/1220, US 0/28. The search is retail's except the $a3 index copy
 * (retail: a2 = a3 + 1; a3 = a2) and the exit test copied after the loop passes. Aligned diff: the
 * missing word is that copy; everything above +0x3F0 matches. -fcall-used-hi1 -fcall-used-lo1
 * -fcall-used-accum1 (loop hoisting threshold 64): byte-identical output, retail's invariants are
 * already hoisted, so this is not a hoisting miss. Also no change: while/do-while/`&&` exit forms,
 * an inline match helper, a do/while(0) group on the init or the increment. Worse: a local index
 * stored after or inside the loop (1200-1204), a do/while(0) around the match test (1196), an
 * if/return-1 helper (1236). Only the always-false guard restores the copy (then +0xD0 v0/v1).
 */
/* 4 November 2026 source audit: removed the always-false preset-search guard.
 * The previous controlled result below is historical and cannot qualify this
 * revised draft. Production remains assembly; no linked or native credit.
 * Fresh check: 1216/1220 bytes, US and PAL 0/28 each; US2 name absent.
 * Profile: -O2 -G8 -ffunction-sections. Reopen on a real preset-search control-flow witness.
 */
/* func_002D4948: near miss. Opus 5.5 xhigh (opus-2), 31 October 2026. Unit: a -G8 sibling such as
   src/game/002D3390-002D4948-g8.c, default flags (it needs $gp for D_001ABA74). Remove the marker
   from src/game/002D3390.c when trying it.

   Best check.py: 1220/1220 bytes, 0 of 28 USA places, PAL 0 of 28; not in the v2.00 catalogue. Two
   words differ once relocations are masked: +0xD0 and +0xD8, $v0 where retail has $v1. The final
   search and everything else are retail's. NOT LANDABLE as written: the search below holds an
   always-false test (`if (D_001ABA74 >= 21) D_001ABA74 = 0;`), a form the guide forbids. Without
   that test: 1216/1220 bytes, retail's search shape is lost.

   Established by measurement and by reading ee/gcc (jump.c, stmt.c, haifa-sched.c, alias.c):
   - Retail's search is the plain `for`, with the copy of its exit test made on the jump pass AFTER
     the loop passes (toplev.c runs a JUMP_AFTER_REGSCAN pass before cse2), not at jump1. Evidence:
     $a3, a copy live across the back edge, needs cse1 to follow that edge, which it does only past
     the BARRIER of the entry jump; so the entry jump still existed at cse1. Invariants then land
     above the peeled test, T+8 is the first address, and all of it reproduces here.
   - duplicate_loop_exit_test refuses on a CODE_LABEL, CALL_INSN, LOOP_BEG or LOOP_CONT note, a
     libcall note, an asm, or over 30 insns. Length cannot refuse it here: stmt.c rolls an exit only
     within those same 30, and jump.c retries after merging the jump-over-jump. What works is a label
     inside the rolled test that survives jump1 and that cse1 removes. It must leave the match test's
     jump within the 30: the arm plus its test can add at most 4 insns (jump dump ordinal 28; at 29
     the match test is not rolled and nothing peels). An arm of one register set is if-converted at
     jump1 and has no label, so it copies at jump1; a one-insn store (`sw $zero`) works.
   - `const` on D_0026CFD0 is real, not a trick: unchanging reads have no anti-dependences on later
     stores, which is what puts `addiu $t1` before `lw $v1` as in retail. The text tables are not
     const: const on them changes the bytes (+16), and retail rereads them across the call.
   - +0xD0: retail's `items` load is before `addu $s0,$s0,$v0` in sched1's order, so T overlaps it and
     it takes $v1. Here sched1 issues kind-9 li and sll at 15, sb and la at 16, addu at 17, and the load
     only at 18 (store then load, latency 2). So the address path needs one cycle more, or the store
     one cycle less.

   Tried for +0xD0, same or worse: `D_001A8C28[]` incomplete (right register, but lui/addiu split, 3
   words); kind 9 as a first-block local (doubled live length still wins it $s5 over kind 8; kinds 8
   and 1 as locals swap $s4/$s5, so those two are literals); a separate `first` variable (+8 bytes);
   passing the expression directly to the call; `if (a != 0) line = X; else line = X;` after the
   kind-9 store (1228 bytes, all allocation moves). Earlier notes on `found` flags and early-return
   predicates: those refuse the copy too, but keep a real branch. A `break` arm with a dead store does
   nothing: its label falls at the end of the moved code, outside the exit test.
   Next: a real construct in the search that leaves a label until cse1 (func_002D3D88's match shows
   real tests can vanish with no trace when they test a register already live, but that form lasts to
   jump2 and is too late here); then the extra cycle at +0xD0.

   Needs only the declarations below. */

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
    char reserved138[0x94];
    char *items;
    int count;
    int timer;
} CallbackState;

extern CallbackState D_001F2840;

/* A 256-byte menu line. */
typedef struct {
    char pad00[0x20];
    unsigned char b20;
    char pad21[2];
    unsigned char b23;
    char pad24[8];
    float alpha;
    unsigned char b30;
    unsigned char b31;
    short width;
    unsigned short style;
    char pad36[0x62];
    int w98;
    char pad9C[0xE];
    short text;
    char padAC[0x10];
    unsigned char kind;
    char padBD[0x33];
    float colour[3];
    char padFC[4];
} MenuLine_002D4948;

typedef struct {
    int a;
    int b;
    unsigned int mask;
    unsigned int value;
    int data;
} OptionPreset_002D4948;

typedef struct {
    char pad0[0x3C];
    int w3C;
} Layout_002D4948;

extern unsigned int D_001A7AF0;
/* Text ids per setting value. */
extern short D_001A8C28[4];
extern short D_001A8C30[4];
extern short D_001A8C38[4];
extern short D_001A8C40[4];
extern short D_001A8C48[4];
extern short D_001A8C50[4];
extern short D_001A8C58[4];

extern const OptionPreset_002D4948 D_0026CFD0[21];
extern Layout_002D4948 D_0025D478;
extern int D_001ABA74 __attribute__((sda));
extern char *func_002DE550(int);
extern void func_0029F0C8(MenuLine_002D4948 *, int);
extern void func_002A0468(MenuLine_002D4948 *, int, int, int, int);
extern void func_002A0F48(MenuLine_002D4948 *);

/* Builds the options menu from the settings word D_001A7AF0, then finds the preset
   matching the settings. */
int func_002D4948(void)
{
    int kind3 = 3;
    int kind4 = 4;
    unsigned int settings = D_001A7AF0;
    int a = (settings >> 2) & 3;
    int b = (settings >> 4) & 1;
    int c = (settings >> 6) & 1;
    int d = (settings >> 7) & 3;
    int e = (settings >> 9) & 1;
    int f = (settings >> 10) & 3;
    int g = (settings >> 14) & 3;
    MenuLine_002D4948 *line;
    int n;
    int i;

    D_001F2840.items = func_002DE550(1);
    line = (MenuLine_002D4948 *)D_001F2840.items;
    func_0029F0C8(line, 0xD54);
    line->kind = 9;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x100);
    func_0029F0C8(line, D_001A8C28[a]);
    line->kind = 8;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x200);
    func_0029F0C8(line, D_001A8C28[a]);
    line->kind = 8;
    line->style |= 0x8000;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x300);
    func_0029F0C8(line, D_001A8C30[b]);
    line->kind = 0;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x400);
    func_0029F0C8(line, D_001A8C38[c]);
    line->kind = 1;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x500);
    func_0029F0C8(line, D_001A8C38[c]);
    line->kind = 1;
    line->style |= 0x8000;
    n = 6;
    if (D_001A8C40[d] != 0) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + 0x600);
        n = 7;
        func_0029F0C8(line, D_001A8C40[d]);
        line->kind = 2;
    }
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C48[e]);
    line->kind = kind3;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C48[e]);
    line->kind = kind3;
    line->style |= 0x8000;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C50[f]);
    line->kind = kind4;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C50[f]);
    line->kind = kind4;
    line->style |= 0x8000;
    if ((D_001A7AF0 >> 12) & 1) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, 0x10E2);
        line->kind = 5;
    }
    if ((D_001A7AF0 >> 13) & 1) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, 0x10E4);
        line->kind = 6;
    }
    if (g != 0) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, D_001A8C58[g]);
        line->kind = 7;
    }
    for (i = 0; i < n; i++) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + i * 0x100);
        line->width = 0x1FF;
        func_002A0468(line, 0x202020, 14, 14, 0);
        line->width = 0xFF;
        line->b31 = 1;
        line->b30 = 0xFF;
        if (line->text == 0x10E3) {
            line->b23 = 0xFF;
        }
        line->b20 = 0;
        line->w98 = 0;
        line->alpha = 1.0f;
        line->colour[0] = 0.211843f;
        line->colour[1] = 0.33421f;
        line->colour[2] = -2.782353f;
        func_002A0F48(line);
    }
    D_001F2840.count = n;
    D_001F2840.timer = 300;
    for (D_001ABA74 = 0; D_001ABA74 < 21; D_001ABA74++) {
        if ((D_001A7AF0 & D_0026CFD0[D_001ABA74].mask) == D_0026CFD0[D_001ABA74].value) {
            break;
        }
    }
    D_0025D478.w3C = -0x244;
    return 0;
}

