/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, 2026-10-29: retained near miss, not linked.
 * Pinned game compiler, -O2 -G0 -ffunction-sections, USA v1.01:
 * 348/348 bytes, 0/1 places, first mismatch +0x10; 34 non-relocation
 * instruction words differ (36 rows including relocated register differences).
 * Separating both loops' moby and ID-pointer locals improves the previous
 * draft's allocation: the first loop now uses retail's v0 moby/v1 state.
 * Remaining: data/ID/slot/end/invalid-value registers and preamble ordering.
 * The state-zero path always returns; final FD tests retain retail's beql.
 * Measured: moving the remaining index/slot locals into their loop blocks
 * and moving ID initialization into the for initializer give identical bytes.
 * Typed fixed arrays retain a countdown rather than retail's signed pointer
 * bound. Two integer offsets retain an extra per-iteration address add;
 * deriving IDs from the slot collapses both pointers (336 bytes).
 * Explicit integer-address do/while loops also reach 348 bytes, with worse
 * preamble scheduling; an ordinary switch changes the dispatch layout.
 * Next: a distinct source lifetime/control-flow hypothesis for the second
 * loop's current-ID value versus the slot induction pointer. No register
 * pins, volatile casts, barriers, compiler changes, or new flags were used.
 * Required declarations are included below; no headers are needed.
 */

extern char *D_L19_001B2A1C __attribute__((sda));
extern void func_0029F338(char *);

void func_L19_00380918(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);
    unsigned char state = *(unsigned char *)(a0 + 0x20);

    if (state == 0) {
        char *pool;
        char *m;
        int *idp;
        int *slot;
        int i;

        *(unsigned char *)(a0 + 0x20) = 1;
        pool = D_L19_001B2A1C;
        idp = (int *)(s0 + 0x10);
        for (i = 0x30; i < 0x50; i += 4, idp++) {
            slot = (int *)(s0 + i);
            m = pool + (*idp << 8);
            if (m == 0) {
                *slot = -1;
                continue;
            }
            if (*(unsigned char *)(m + 0x20) == 0xFE) {
                *slot = -1;
                continue;
            }
            if (*(unsigned char *)(m + 0x20) != 0xFD)
                *slot = *(short *)(m + 0xAA);
            else
                *slot = -1;
        }
        if (*(int *)s0 == 0) {
            *(unsigned char *)(a0 + 0x20) = 2;
            *(unsigned short *)(a0 + 0x34) |= 2;
            return;
        }
        return;
    } else if (state != 1) {
        return;
    }
    {
        char *pool = D_L19_001B2A1C;
        char *m;
        int n = 0;
        int id;
        int cur;
        int *idp;
        int *slot;
        int i;

        idp = (int *)(s0 + 0x10);
        for (i = 0x30; i < 0x50; i += 4, idp++) {
            slot = (int *)(s0 + i);
            id = *idp;
            if (id == -1) {
                *slot = -1;
                continue;
            }
            cur = *slot;
            if (cur == -1) {
                *slot = -1;
                continue;
            }
            m = pool + (id << 8);
            if (m == 0) {
                *slot = -1;
                continue;
            }
            if (*(short *)(m + 0xAA) != cur) {
                *slot = -1;
                continue;
            }
            if (*(unsigned char *)(m + 0x20) == 0xFE) {
                *slot = -1;
                continue;
            }
            if (*(unsigned char *)(m + 0x20) != 0xFD)
                n++;
            else
                *slot = -1;
        }
        if (n < *(int *)s0)
            func_0029F338(a0);
    }
}
