/* 6 November 2026: bounded typed-field/lifetime follow-up; NOT a match.
 * Retained C below: US/US2/PAL 540/564 bytes, 0/1 places each.
 * Profile for a separate L23_0041CA58.c unit:
 *   -O2 -G0 -ffunction-sections -frac2-qcopy
 * The source owns sums[47], picks[7] and one aligned 16-byte vector. Its frame
 * is 0x140, against retail's 0x160; no unused padding or larger vector is justified.
 *
 * New measured improvement, diagnostic only: addressing both scans directly
 * through State.counts recovers retail's state/counts $s4/$s5 allocation and the
 * pre-search counts-pointer copy. With the inherited dead `dead = r % 3`
 * assignment, -frac2-qcopy and n-before-dst header order reach 564 bytes with
 * 66 differing instruction words (relocation fields masked), versus 76 for the
 * starting draft. That comparison still fails 0/1 in every release. The dead
 * assignment is not eligible under the worker's no-dead-store rule: dropping it,
 * or spelling only `(void)(r % 3)`, removes retail's otherwise unused divide guard,
 * its saved constant and other setup, producing the retained 540-byte body.
 *
 * New bounded negatives: meaningful one-pass groups around the initialization,
 * scans, selection phases and real bucket computations do not close the gap.
 * qcopy/qcopy_nc, natural TI/union/aligned vector storage, explicit search CFG,
 * counter reuse, bound snapshots and a counts cursor do not match. The cursor
 * lowers an offset-wise difference count but changes the indexed search code;
 * it is not the retained source. Standard loop/CSE/scheduling alternatives do
 * not improve the typed-field draft. No invalid group that changes a break's
 * target is a candidate. No compiler, tool, catalogue or linked build was changed.
 *
 * Reopen on evidence for the real arithmetic/control flow behind the leftover
 * divide guard and ownership of the extra 0x20 frame bytes. In the closer
 * diagnostic the vector destination still materializes in the search loop,
 * rather than its preheader; next-index copies, scheduling and registers differ.
 *
 * Earlier measurements (4 November 2026): removing an unused eight-float pad
 * already left a 564-byte near miss in all releases, with the smaller frame.
 * The original rolled search loop, its shared copy label and n = i + 1 before
 * the tests preserve retail's bottom-entry shape. Separate base += 0x10 steps
 * in the two bucket paths permit their shared register-addressed copy tail.
 * Frame analysis (6 November 2026): sums at 0, picks at 0xC0, vector at 0xE0;
 * retail touches none of the following 0x20 bytes before saves at 0x110.
 * func_L23_0041C7D8 -> func_L23_0041C8C0 reads only the vector's first 16 bytes.
 */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char fields[0x230];
    int counts[47];
} State;
extern char *D_L23_001FF300[];

extern void func_L23_0041CCC0(char *);

extern void func_L23_0041C7D8(char *, int);

extern int func_002A77E0(int);

extern void func_00115484(char *, int, int);

void func_L23_0041CA58(char *arg0) {
    State *state = *(State **)(arg0 + 0x68);
    int sums[47];
    int picks[7];
    float F[4] __attribute__((aligned(16)));
    TI128 *dst;
    char *base;
    int total = 0;
    int found;
    int t;
    int r;
    int i;
    int j;
    int t46;
    int n;

    func_L23_0041CCC0(arg0);
    func_002A77E0(3);
    func_00115484((char *)picks, -1, 0x1C);
    for (i = 0; i < 47; i++) {
        sums[i] = total;
        t = total - 1;
        total = t + *(int *)D_L23_001FF300[state->counts[i]];
    }
    for (j = 0; j < 7; j++) {
        found = 1;
        do {
            r = func_002A77E0(total);
            for (i = 0; i < 7; i++) {
                if (r == picks[i]) {
                    found = 1;
                    break;
                }
                if (i == 6)
                    found = 0;
            }
        } while (found == 1);
        picks[j] = r;
        t46 = (r - sums[46]) * 16;
        for (i = 0; i < 47; i++) {
            n = i + 1;
            dst = (TI128 *)F;
            if (i == 46) {
                base = D_L23_001FF300[state->counts[46]] + t46;
                base += 0x10;
    copy:
                *dst = *(TI128 *)base;
                break;
            }
            if (r >= sums[i] && r < sums[n]) {
                base = D_L23_001FF300[state->counts[i]] + (r - sums[i]) * 16;
                base += 0x10;
                goto copy;
            }
        }

        if (i != 0xA && i != 0x1B && i != 0x1C && i != 0x1F && i != 0xF) {
            func_L23_0041C7D8((char *)F, 0);
        }
    }
}
