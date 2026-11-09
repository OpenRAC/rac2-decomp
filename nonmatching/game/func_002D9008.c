/* 9 November 2026 (o86, dump-driven): re-measured 1480/1484 (the -4 is the purchased fallback: retail li/daddu/movn = 3 insns,
 * ours li/movz = 2). Mechanism: jump1 if-conversion (jump.c ~1060) builds S = cond ? aval : T(3); then either cse1 replaces
 * T by state (state = 3 in the same block makes state the class head: `state = 3; if (!purchased) state = 0;` gives the
 * wanted (ne p 0) ? T : 0 at .jump but (reg 105) at .cse), or regmove fixup_match (regmove.c ~2990) ties T to state via
 * alternative 1's "0" (`state == 0 && purchased`: (eq p 0) ? 0 : T at .cse, ? 0 : 105 at .regmove). Retail is the cmove
 * alternative with const 0 tied (reload's daddu s6,0) and T in v0: needs T not tied by regmove (T set in another block =
 * reg_is_remote_constant_p, or an insn mentioning state between T's set and the cmove) and not a dummy reload in reload.c
 * (T must not die there), or op3 = state unfolded by cse. 3 check.py runs; madd, s5/s6, frame untouched. */
/* 9 November 2026 (o38, PRE slot order): the 0x30/0x34 swap IS gcse PRE bucket order: spills y+yStep (plus reg reg, hash 14669+y+s) and row+1 (14030+r), S=163; retail needs row+1 first. Fixed by declaring row and y in a block around the row loop (regs 153/154): row+1 now bucket 2, slots match retail, 84 -> 81 aligned rows (sp +0x10 shifted); C below updated. Other S that would also work: 155/157/169-175. Still blocked by the 0x10 frame gap, madd, movz, s5/s6. */
/* 9 November 2026 (Sonnet round 3, lessons 42-49): re-measured 1480/1484, 69 rows differ once sp offsets are ignored (208 raw). Retail has `mult; addu` with D_00239BA0 base in its own reg; madd goes away only with a two-statement `entry = D_00239BA0; entry += D_00139568[record[3]];` (state block) and a block-local `icon = D_00239BA0; icon += ...` (icon site), but both shift gcse/preheader allocation (row+1/y+step spills lost, 73-197 rows, 1472-1488 bytes), so not kept; one-expression spellings (cast, char* base, tbl local, ctx local, raw unsigned-int sum) all still madd. Purchased fallback: 5 spellings (if, &&, ?: with state/0, state=0 first) identical movz. Permuting the five global loads (119 orders) changes nothing. s5/s6: retail state has 13 refs, hoisted y+height 9 (ours swapped counts), so not a ref-count tie. Frame 0xA0/0xB0 untouched (no honest 16-byte local found). */
/* 8 November 2026 (Sonnet round 2, lesson 49): removed fake locals `key` (retail reloads record[3] from the halfword each time) and `entry` for the icon lookup (written as D_00239BA0[D_00139568[record[3]]].icon); now 1480/1484 bytes (was 1472), 208 differing rows (251 before; no pad[4] needed any more). Also tried: gap/areaWidth/areaHeight as expressions (worse, 284), texture inlined into the call (same), bottom as one local set per row (261, worse), `y += yStep, row++` (-2). Left: s5/s6 state/bottom swap, spill slots 0x30/0x34 order, madd (mtlo/madd) where retail has mult+addu for D_00239BA0 indexing (every spelling of the index expression gives madd), purchased movz vs movn. */
/* 8 November 2026 (Sonnet round): rewrite from retail asm and Ghidra reproduces the same C; unchanged 1472/1484, 51 lines. With a diagnostic int pad[4] the 0xB0 frame and all stack offsets match; 1 -O2 -G8 permuter run (1500 s, -j2) best 1480/1484 (worse), none cleanable. Purchased-state spelling 'state==0 && purchased' still gives movz, not movn. */
/* Claude, task v101 wcD, 8 November 2026: retained near miss, body revised.
 * Profile: -O2 -G8 -ffunction-sections (dedicated -g8.c unit, no extra flags).
 * check.py: 1472/1484 bytes, 0 of 28 USA v1.01 places; 51 differing lines
 * (stack offsets ignored) versus 60 for the 29 October body below this header.
 *
 * Changes this round (all retail-backed): the state == 4 white outline is
 * drawn outside the active-cursor block (retail's bne delay slot preloads 4
 * and branches to it; Ghidra agrees); the item state is computed in `state`
 * itself (retail keeps it in one saved register, no copy); the row loop is
 * `row++, y += yStep` with no nextY (GCSE then creates retail's row+1 / y+step
 * spill slots 0x30/0x34; nextY gave the wrong slot order); bottom is written
 * as y + height at each draw (same code as a bottom local).
 *
 * Frame: retail 0xB0 never touches its lowest 16 bytes. A diagnostic unused
 * `int pad[4];` local gives the exact 0xB0 frame and aligns every stack offset
 * up to the inner-loop preheader, so retail had one 16-byte local whose uses
 * were all optimised away. That is invented padding (not covered by the
 * oversized-array ruling), so it is not in the body; needs an owner ruling or
 * a real source local.
 *
 * Remaining: (1) purchased fallback: retail `li v0,3; daddu s6,0; movn s6,v0,v1`
 * ((ne c 0) ? 3 : state with state tied to 0); every spelling (ternary, if/else,
 * fresh temp, inline helper, else-if chain, goto, char/bitfield tests, cse and
 * jump flags) gives `li s,3; movz s,zero,c` because jump1 if-converts and cse
 * folds the known zero. (2) state/bottom get s5/s6 swapped: global-alloc
 * priority state 105/218 vs hoisted bottom 16/35. (3) preheader: retail reloads
 * width and copies x+16+width slot 0x38 to 0x4C through memory (+2 insns);
 * row+1/y+step compute order swapped. (4) owned-test byte in a0 (first arm) vs
 * v1 in retail's second arm: retail used two pseudos. -frac2-gcse-unsplit-edges
 * and -frac2-keep-block-order change nothing. ~30 checks, us only.
 */
/* GPT-6.1 Sol high, task v1140, 29 October 2026: retained near miss.
 * Profile: -O2 -G8 -ffunction-sections (default split addresses).
 * check.py: 1480/1484 bytes, 0 of 28 USA v1.01 places match; not linked.
 * All required declarations are below; compile in a dedicated -g8.c unit.
 *
 * Improvement over v0601: put each x + width + border expression at its
 * draw call, rather than sharing precomputed bounds. GCC then reproduces
 * retail's six independent right-edge column induction values. The typed
 * 224-byte item table emits mult/addu rather than the raw-pointer madd;
 * the context view also preserves the root-relative slot/override accesses.
 * Delaying index initialization until after layout recovers setup scheduling.
 *
 * Remaining: 0xA0 frame versus retail 0xB0. Retail never accesses its first
 * 16 stack bytes; this draft's active/xStart/yStep/width/height/index/row
 * spill slots are each 16 bytes lower. Later spill order and scheduling
 * differ. The item-state temporary is copied from a caller-saved register
 * to s7, whereas retail computes directly in s6; its purchased-state
 * fallback is movz instead of retail's zero initialization plus movn.
 * A single shared state was 1476 bytes with worse saved-register allocation.
 * Reordering declarations fixes relative early spill order, not the frame.
 * Typed grid/cell views did not improve the 1476-byte form. A real rectangle
 * struct stored all four fields and fell to 1432 bytes/0x90 frame, so it does
 * not explain retail's unused stack space. No invented padding was retained.
 * Next: independent evidence for the missing stack allocation and the
 * item-state lifetime/conditional selection. Twelve checks, one allocator
 * diagnostic; no alternate-release checks or linked builds were run.
 */
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(int);
extern void func_0027C660(void);

extern int D_001ABAD8 __attribute__((sda)), D_001ABADC __attribute__((sda)), D_001ABAE8 __attribute__((sda));
extern int D_001AA43C __attribute__((sda));
extern int D_001B1598;
extern unsigned char D_001A7AF8[], D_001395B8[];
extern unsigned int func_002884B0(unsigned int);
extern int func_00282C30(int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern void func_0028EE98(int, int, int, int, int, int);

typedef struct { char pad[0x14]; char *owner; char pad18[0x40-0x18]; int slots[65]; int override144; int override148; } GridContext;
extern GridContext D_001F2840;
extern unsigned char D_00139568[];
typedef struct { unsigned char pad[4]; unsigned char purchased; unsigned char pad05[7]; int slot; unsigned char pad10[0x3C-0x10]; unsigned short icon; unsigned char pad3E[224-0x3E]; } GridItem;
extern GridItem D_00239BA0[];
extern void func_002D8EC0(char *, short *, int, int, int, int);
extern int func_0028E588(int, int);

int func_002D9008(char *object)
{
    short *record = *(short **)(object + 0x48);
    int active = *(char **)(D_001F2840.owner + 0xE8) == object;
    int xStart, xStep, yStart, yStep;
    int width, height, areaWidth, areaHeight, gap;
    int index, column, x, state;
    int texture;
    unsigned long colour, pulse;
    GridItem *entry;
    func_002FC560(66, 0x8000000044ULL);
    func_002FC560(71, 11);
    func_0027C540(0);
    width = D_001ABAD8;
    height = D_001ABADC;
    areaWidth = *(int *)(object + 0x20) << 4;
    areaHeight = *(int *)(object + 0x24) << 4;
    gap = D_001ABAE8;
    if (*(int *)(object + 0x44) >= 2) {
        xStart = *(int *)(object + 0x34) << 4;
        xStep = width + (areaWidth -
                (*(int *)(object + 0x34) << 5) - *(int *)(object + 0x44) * width) /
                (*(int *)(object + 0x44) - 1);
    } else {
        xStart = (areaWidth - width) >> 1;
        xStep = 0;
    }
    if (*(int *)(object + 0x30) & 2) {
        yStep = height + gap;
        yStart = *(int *)(object + 0x38) << 4;
    } else if (*(int *)(object + 0x40) >= 2) {
        yStart = *(int *)(object + 0x38) << 4;
        yStep = height + (areaHeight -
                (*(int *)(object + 0x38) << 5) - *(int *)(object + 0x40) * height) /
                (*(int *)(object + 0x40) - 1);
    } else {
        yStep = 0;
        yStart = (areaHeight - height) >> 1;
    }
    index = 0;
    {
    int row, y;
    for (row = 0, y = yStart; row < *(int *)(object + 0x40); y += yStep, row++) {
        x = xStart;
        for (column = 0; column < *(int *)(object + 0x44); column++) {
            state = 0;
            if (record[2] == 0 ? D_001A7AF8[record[3]] : D_001395B8[record[3]]) {
                if ((unsigned short)record[2] == 0) {
                    entry = &D_00239BA0[D_00139568[record[3]]];
                    state = 0;
                    if (D_001F2840.slots[entry->slot] == record[3])
                        state = ((*(int *)(object + 0x30) ^ 1) & 1) << 2;
                    if (state == 0) { if (!entry->purchased) state = 0; else state = 3; }
                    if (D_001F2840.override144 && (*(int *)(object + 0x30) & 8)) state = 2;
                    if (D_001F2840.override148 && (*(int *)(object + 0x30) & 4)) state = 2;
                    if (func_002884B0((unsigned short)record[0]))
                        func_002D8EC0(object, record, column, row, x >> 4, (y >> 4) + 36);
                }
                if (active && *(int *)(object + 0x3C) == index) {
                    pulse = (unsigned int)(((func_00282C30((D_001B1598 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                    colour = state == 4 ? (unsigned long)(int)0x80101010u : (unsigned long)D_001AA43C;
                    func_0028FC48(x - 48, y - 48, x + width + 48, y + height + 48, pulse, 1);
                    func_0028FC48(x - 16, y - 16, x + width + 16, y + height + 16, colour, 1);
                }
                if (state == 4)
                    func_0028FC48(x - 64, y - 64, x + width + 64, y + height + 64, 0x80FFFFFFUL, 1);
                texture = func_0028E588(D_00239BA0[D_00139568[record[3]]].icon, record[1]);
                func_0028EE98(texture, x, y, width, height, 128);
                if (state == 2)
                    func_0028FC48(x - 64, y - 64, x + width + 64, y + height + 64, 0x60202020UL, 1);
            } else if (active && *(int *)(object + 0x3C) == index) {
                pulse = (unsigned int)(((func_00282C30((D_001B1598 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                colour = (unsigned long)D_001AA43C;
                func_0028FC48(x - 48, y - 48, x + width + 48, y + height + 48, pulse, 1);
                func_0028FC48(x - 16, y - 16, x + width + 16, y + height + 16, colour, 1);
            }
            index++;
            record += 5;
            x += xStep;
        }
    }
    }
    func_0027C660();
    return 2;
}
