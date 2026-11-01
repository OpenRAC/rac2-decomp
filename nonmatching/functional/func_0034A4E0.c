/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Opus 5.5, xhigh: -O2 -G0 -ffunction-sections, own unit. 804/804 bytes, 0/28 places (us).
 * 41 of 201 instructions differ: 39 are one rotation of callee-saved registers, 2 one slot.
 * Retail also differs per release only in the D_001A8CFC %lo, so one C can match all three.
 *
 * Measured, each closing a real difference from the older drafts:
 * - The four tables are const. Without RTX_UNCHANGING reads, *last and *group get true
 *   dependencies on the block copies and sched1 delays value's copy; a1 then is not free as
 *   copy 1's scratch. const gives retail's frame 0x80, five saves (s3 is an unused scratch of
 *   movstrsi_internal) and every first-block register.
 * - tier = 1; if (value > 20) tier = 2; gives slti/movn with 1 in the long-lived t8, which cse2
 *   reuses for *last = 1. A ternary or if/else gives slt 20<value/movz or a branch.
 * - Statement order *last, firsts, tier, *group, clamp, seconds places the stores as retail.
 *
 * What still differs:
 * 1. Retail has "swc1 f21,(a3); jal; lwc1 f21,0x10(sp); mov.s f12,f20", so the result load
 *    precedes the first call in RTL, and arm 1 starts slt, addiu, movn, lwc1. That order needs
 *    the *offset store to have no dependency on the load, that is a const_double source at
 *    sched1, which reload_cse then turns into f21 (-fno-rerun-cse-after-loop shows this exactly,
 *    but loses the t8 sharing, so retail has cse2). cse2 always rewrites the literal to the
 *    result pseudo, adding two to the store chain's priority. Below, arm 1 reads the result
 *    after its first call as the nearest wording: right order, wrong slot. No truthful wording
 *    that keeps the const through cse2 was found. A separate zero local folds to sw $zero; a
 *    separate loaded local puts the zero in f1.
 * 2. Retail allocates object s0, last and 0x8710 s1, left s2. Here left s0, object s1, the rest
 *    s2: left has priority 27/48 against object's 64/119. A shared variable for 0x8710 is
 *    needed (a per-arm local takes s0 in local-alloc), but its REG_EQUIV sets lower its priority.
 *    Per-arm local left/right give s0 0x8710, s1 left, s2 right and object tied to right.
 * Next: find what keeps *offset's literal out of cse2's table, then recheck the rotation.
 * Not tried: nothing was linked. Needs the declarations below.
 */
extern void func_00336390(char *, char *, int);
typedef struct { float values[3]; } StageFloatTable;
typedef struct { int values[3]; } StageIntTable;
extern const StageFloatTable D_001AE628, D_001AE638;
extern const StageIntTable D_001AE648, D_001AE658;
extern void func_003363C0(unsigned char *, float);
extern char *D_001A8CFC[] __attribute__((sda));

float func_0034A4E0(char *object, int value, int *count, int *group,
                    float *scale, int *first, int *second, int *last,
                    float *offset)
{
    StageFloatTable scales, results;
    StageIntTable firsts, seconds;
    int index, tier, text;
    float position, result = 0.0f;
    char *left;

    scales = D_001AE628;
    results = D_001AE638;
    *last = 0;
    index = value - 1;
    firsts = D_001AE648;
    tier = 1;
    if (value > 20) tier = 2;
    *group = tier;
    if (index < 0) index = 0;
    seconds = D_001AE658;
    if (value >= 1 && value <= 20) {
        position = (float)(index / 4);
        *count = 6;
        *scale = scales.values[0];
        *first = firsts.values[0];
        *second = seconds.values[0];
        *offset = 0.0f;
        left = object + 0x5C;
        object += 0xA8;
        func_003363C0((unsigned char *)left, position);
        result = results.values[0];
        func_003363C0((unsigned char *)object, position);
        text = 0x8710;
        func_00336390(left, D_001A8CFC[0] + text, 17);
        func_00336390(object, D_001A8CFC[0] + text, 18);
    } else if (value >= 21 && value <= 40) {
        int row = index / 4 - 5;
        if (row < 0) row = 0;
        position = (float)row;
        *count = 10;
        *scale = scales.values[1];
        *first = firsts.values[1];
        *second = seconds.values[1];
        *offset = -0.5f;
        result = results.values[1];
        left = object + 0x5C;
        object += 0xA8;
        func_003363C0((unsigned char *)left, position);
        func_003363C0((unsigned char *)object, position);
        text = 0x8710;
        func_00336390(left, D_001A8CFC[0] + text, 19);
        func_00336390(object, D_001A8CFC[0] + text, 20);
    } else if (value >= 41 && value <= 80) {
        int row = index / 4 - 10;
        if (row < 0) row = 0;
        position = (float)row;
        *count = 10;
        *scale = scales.values[2];
        *first = firsts.values[2];
        *second = seconds.values[2];
        *offset = -0.5f;
        *last = 1;
        result = results.values[2];
        left = object + 0x5C;
        object += 0xA8;
        func_003363C0((unsigned char *)left, position);
        func_003363C0((unsigned char *)object, position);
        text = 0x8710;
        func_00336390(left, D_001A8CFC[0] + text, 21);
        func_00336390(object, D_001A8CFC[0] + text, 22);
    }
    return result;
}
