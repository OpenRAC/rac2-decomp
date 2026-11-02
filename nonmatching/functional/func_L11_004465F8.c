/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Claude Opus 5.5 (xhigh), task v2037; C from GPT-6.1 Sol (high), task v1211. USA v1.01.
 * Best check with the repo's compiler: 1660/1660 bytes, 0/1 places; seven
 * instructions differ, all at +0x194..+0x1AC (0044678C..004467A4).
 * Compile separately with -O2 -G32 -ffunction-sections -Wa,-G32.
 *
 * What differs: the first RGB mask's split SI constant is stored after both its
 * lui and its ori; retail stores only the completed value. The extra store moves
 * setup by one instruction and replaces retail's final nop.
 *
 * Compiler lead, private test only: with the narrowed-guard cc1 of task v2028
 * (/tmp/v2028/narrow.47gx/cc1, not in the repo) this exact C gives check.py
 * "1 of 1 places match" on us, pal and us2. Not run: linked build,
 * tools/build.py all --strict, tests/test_reload_reg_used_guard.py.
 *
 * Cause: sched1 splits (set R 0xFFFFFF) into lui and ior. R has no hard register,
 * so the lui gets an output reload and the ior a combined in-out RELOAD_OTHER one.
 * tools/compiler/transformers/reload_reg_used_guard.py reads reload_reg_used, which
 * also holds that reload's own mark, so inheritance is cancelled and
 * delete_output_reload never fires. Why retail acts like the narrow test is unexplained.
 *
 * Retail evidence: a scan of the USA boot executable and every file under
 * baserom/levels finds no lui; sw slot; ori; sw slot at all (lui to ori within 9
 * instructions), and the same scan does find this draft's store in our object.
 * Single-store shapes with a later load of the slot are in 11 functions, among them
 * func_L15_00437B68 (0xFFFFFF, slot 0xD4, one store, one load). Not all are spills:
 * func_L00_003ED850's is a struct store.
 *
 * Tried with the stock compiler, none removes the first store:
 * - No mask local: same two stores, and the temp moves to slot 0xA0.
 * - lui and ior adjacent after sched1 (no float hoists, probe only): still two stores.
 * - -g: the same seven rows. -fno-schedule-insns: 1632 bytes. -fno-rerun-loop-opt: 1680.
 * Read in the source, not tested: flow2 keeps every store through sp (flow.c:3278), and
 * cse folds a copy from a separate constant temp because CONST_COSTS is 0.
 * A real memory mask was not tried: stores do not hoist, so it needs a written-out
 * if around a do-while and something that keeps the local in memory.
 *
 * Earlier findings: staged GS assignments avoid tree balancing. Explicit corner
 * pointers and next_i, assigned after the fourth corner copy, recover spill order;
 * whether the original had them or PRE made those slots is open. Only the first
 * loop's constant is hoisted because each move lowers loop.c's threshold by 3.
 * Scalar, one-field struct and one-element array masks tie byte for byte.
 * A 64-bit mask changes spill order; 64-bit colors grow the body to 1704.
 * -mno-split-addresses does not fix the store and changes addressing.
 * All required declarations follow.
 */

#include "common.h"
typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; u64 gs[4]; } Quad;
extern u64 func_0027C878(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_00280B90(Quad *, int, int);
extern char *D_L11_001FF580[] NOT_SDA;
extern s32 D_L11_001B18D4[] __attribute__((sda));
extern s32 D_L11_001B18D8[] __attribute__((sda));
extern s32 D_L11_001B18DC[] __attribute__((sda));
extern s32 D_L11_001B18E0[] __attribute__((sda));
extern s32 D_L11_001B18E4[] __attribute__((sda));
extern s32 D_L11_001B18A0 __attribute__((sda));
extern float D_L11_001B18CC[] __attribute__((sda));
extern s32 D_L11_001B18D0 __attribute__((sda));
extern s32 D_L11_001B1890 __attribute__((sda));
extern s32 D_L11_001B188C __attribute__((sda));
extern s32 D_L11_001B1894 __attribute__((sda));
extern s32 D_L11_001B1898 __attribute__((sda));
extern s32 D_L11_001B189C __attribute__((sda));
extern float D_L11_001B18F4[] __attribute__((sda));
extern float D_L11_001B18B4[] __attribute__((sda));
extern float D_L11_001B18BC[] __attribute__((sda));
extern float D_L11_001B18C4[] __attribute__((sda));
extern float D_L11_001B18FC __attribute__((sda));
extern float D_L11_001B187C __attribute__((sda));
extern float D_L11_001B18F0 __attribute__((sda));
extern float D_L11_001B18E8 __attribute__((sda));
extern float D_L11_001B18F8 __attribute__((sda));
extern s32 D_L11_001B18A8[2] __attribute__((sda));
extern float D_L11_001B18B0[4][2] __attribute__((sda));
void func_L11_004465F8(char *self) {
    Quad q;
    u32 mask;
    int i, j;
    int next_i;
    float *pos1, *pos2, *pos3;
    char *state = *(char **)(self + 0x68);
    char *points;
    float height;
    if (*(float *)(state + 0x1BC) < D_L11_001B18FC) return;
    q.gs[1] = func_0027C878(D_L11_001B18A0);
    pos1 = q.pos[1];
    pos2 = q.pos[2];
    pos3 = q.pos[3];
    q.gs[2] = 0xFF9000000260ULL;
    q.gs[0] = D_L11_001B18D0 | ((s64)D_L11_001B18D4[0] << 2);
    q.gs[0] |= (s64)D_L11_001B18D8[0] << 4;
    q.gs[0] |= (s64)D_L11_001B18DC[0] << 14;
    q.gs[0] |= (s64)D_L11_001B18E0[0] << 24;
    q.gs[0] |= (s64)D_L11_001B18E4[0] << 34;
    q.gs[3] = D_L11_001B188C | ((s64)D_L11_001B1890 << 2);
    q.gs[3] |= (s64)D_L11_001B1894 << 4;
    q.gs[3] |= (s64)D_L11_001B1898 << 6;
    q.gs[3] |= (s64)D_L11_001B189C << 32;
    height = D_L11_001B18F4[0] + (D_L11_001B18F0 - D_L11_001B18F4[0]) *
        (*(float *)(state + 0x1BC) / D_L11_001B187C);
    points = D_L11_001FF580[*(int *)(state + 0x1C8)];
    for (i = 0; i < *(int *)points - 1; i = next_i) {
        mask = 0xFFFFFF;
        qcopy_nc(q.pos[0], points + (i * 16 + 0x20));
        q.pos[0][2] -= D_L11_001B18E8;
        qcopy_nc(pos1, points + (i * 16 + 0x10));
        q.pos[1][2] -= D_L11_001B18E8;
        qcopy_nc(pos2, points + (i * 16 + 0x20));
        q.pos[2][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[0][1]));
        qcopy_nc(pos3, points + (i * 16 + 0x10));
        next_i = i + 1;
        q.pos[3][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[1][1]));
        q.uv[0][1] = D_L11_001B18B4[0];
        q.uv[1][1] = D_L11_001B18BC[0];
        q.uv[2][1] = D_L11_001B18C4[0];
        q.uv[3][1] = D_L11_001B18CC[0];
        for (j = 0; j < 4; j++) {
            int index = func_00283CF0(q.uv[j][1] + 0.2f);
            float alpha;
            u32 c;
            q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
            alpha = func_00283198(*(float *)(state + 0xD0) * 3.1415927410125732f);
            c = D_L11_001B18A8[index];
            q.color[j] = func_00283D38(c & mask, c, alpha);
        }
        func_00280B90(&q, 0, 0);
        for (j = 0; j < 4; j++) {
            int index = func_00283CF0(q.uv[j][1] + 0.2f);
            float alpha;
            u32 c;
            q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
            alpha = func_00283198(*(float *)(state + 0xD4) * 3.1415927410125732f);
            c = D_L11_001B18A8[index];
            q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
        }
        func_00280B90(&q, 0, 0);
    }
    qcopy_nc(q.pos[0], points + 0x10);
    q.pos[0][2] -= D_L11_001B18E8;
    qcopy_nc(pos1, points + (*(int *)points * 16));
    q.pos[1][2] -= D_L11_001B18E8;
    qcopy_nc(pos2, points + 0x10);
    q.pos[2][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[0][1]));
    qcopy_nc(pos3, points + (*(int *)points * 16));
    q.pos[3][2] += height + D_L11_001B18F8 * func_00283180(func_00283C28(q.pos[1][1]));
    q.uv[0][1] = D_L11_001B18B4[0];
    q.uv[1][1] = D_L11_001B18BC[0];
    q.uv[2][1] = D_L11_001B18C4[0];
    q.uv[3][1] = D_L11_001B18CC[0];
    for (j = 0; j < 4; j++) {
        int index = func_00283CF0(q.uv[j][1] + 0.2f);
        float alpha;
        u32 c;
        q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
        alpha = func_00283198(*(float *)(state + 0xD0) * 3.1415927410125732f);
        c = D_L11_001B18A8[index];
        q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
    }
    func_00280B90(&q, 0, 0);
    for (j = 0; j < 4; j++) {
        int index = func_00283CF0(q.uv[j][1] + 0.2f);
        float alpha;
        u32 c;
        q.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
        alpha = func_00283198(*(float *)(state + 0xD4) * 3.1415927410125732f);
        c = D_L11_001B18A8[index];
        q.color[j] = func_00283D38(c & 0xFFFFFF, c, alpha);
    }
    func_00280B90(&q, 0, 0);
}
