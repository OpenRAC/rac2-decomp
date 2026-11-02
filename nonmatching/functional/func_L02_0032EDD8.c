/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, 2026-10-29: current-toolchain USA near miss, 308/308 bytes,
 * 0/9 places, first mismatch +0x84. Profile:
 * -O2 -G0 -ffunction-sections -fno-strength-reduce.
 * The old 284-byte draft lost the second walked pointer. Explicitly walking the
 * records argument as the position, alongside rec as the base, and disabling
 * strength reduction retains both. Separate block-scoped path/count locals give
 * retail's argument registers and load-before-pointer-increment call sequences.
 * Only five instructions in the loop preheader differ: rec is copied before the
 * count test; the table base is materialized after the position pointer; position
 * initialization uses rec instead of its original argument register. Loop body,
 * saved registers, size and alignment then agree. A guarded for keeps the saved
 * registers but adds a second count test. A guarded do removes that test but
 * swaps the index/position saved registers. Block-scoped index, increment order,
 * and explicit break forms tie; goto loses loop optimization/alignment (288 bytes).
 * Default optimization and typed/walked-pointer forms remain 284 bytes; a typed
 * record with strength reduction disabled gives 300 bytes. Reopen with a truthful
 * loop/preheader form that preserves the index's allocation priority.
 */
extern char *D_L02_001FF1C0[];
extern int func_002A8AF0(float *p, float *v, int n);
extern float func_00282E80(void *a, void *b);

int func_L02_0032EDD8(float *point, char *records, int count, int *index) {
    char *rec;
    int i;

    if (*index != -1) {
        char *entry;
        int n;
        entry = D_L02_001FF1C0[*(int *)(records + *index * 32)];
        n = *(int *)entry;
        entry += 0x10;
        if (func_002A8AF0(point, (float *)entry, n) != 0)
            return 1;
    }
    rec = records;
    records += 0x10;
    for (i = 0; i < count; ++i) {
        if (i != *index && func_00282E80(point, records) <= *(float *)(rec + 0x1C)) {
            char *entry;
            int n;
            entry = D_L02_001FF1C0[*(int *)rec];
            n = *(int *)entry;
            entry += 0x10;
            if (func_002A8AF0(point, (float *)entry, n) != 0) {
                *index = i;
                return 1;
            }
        }
        records += 0x20;
        rec += 0x20;
    }
    *index = -1;
    return 0;
}
