/* 6 November 2026: retained source unchanged (944/948). Literal `1.0f` in both the call and the
 * sampling loop (no `one`) gives retail's two `mov.s $f13,$f21` (call delay slot and loop numerator):
 * loop.c hoists the constant and cse2 turns it into a copy of the call's 1.0. But the copy lands
 * after the duplicated first iteration, so cross-jumping fails (1016 bytes). Retail sets it before
 * the blez, so the numerator is a pseudo set before the loop that gcse does not propagate.
 * `one` set after the call, inside the if, or next to rate: all tie the base.
 */
/* 3 November 2026; retained C, no linked match.
 * Real operand captures and a choice write cursor, following current RAC1
 * pick_idle_fidget, remain 944/948 bytes and 0/27 US places (frame 0xD0).
 * Both stack vectors are complete 16-byte objects, and the second qcopy
 * still reads the first stack copy. RAC1 independently uses choices[20].
 * The actual hero-origin operand is captured before the candidate loop.
 * This does not resolve the origin/-1 hoist threshold or the sampling
 * numerator copy. No scalar/flag sweep or dummy references were added.
 */
/* opus-1 (Claude Opus 5.5 xhigh), v1781: 944/948 bytes, 0/27 USA v1.01 places, 0/27 v2.00.
 * Profile: -O2 -G0 -ffunction-sections -frac2-hazard-labels. All declarations are below.
 *
 * Solved here: the sampling loop. A plain `for` duplicates its whole first iteration in front of
 * the loop (jump.c duplicate_loop_exit_test); the post-reload cross-jump pass then merges that
 * copy into the loop body, leaving retail's `blez; b body; lw v0,0(sp)`. The merge needs both
 * copies in the same registers, so `table`, `size`, `rate` and `cursor` are set before the loop.
 * `entry = &records[index]` reduces to retail's `addiu s1,s1,0x70` and gives `lwc1 0x58(base)`.
 *
 * Two differences remain, both named by the x.i.loop and greg dumps of tools/regalloc.py:
 * 1. Retail keeps origin in $fp, used once by the first qcopy, and sets -1 inside the first loop.
 *    Here the loop pass hoists -1 and it takes $fp, so origin is rebuilt as lui/addiu in the loop.
 *    threshold is 61 here (inferred from the moved and not-desirable lines of the dump), less 3 per
 *    insn moved (loop.c move_movables). Retail needs
 *    0.0f moved and -1 not, so the rerun pass must see 59 or 60 real insns with 0.0f the first
 *    movable. This wording has 58, with the mult's 0x70 first. Literal 0.0f gives 59 but 0x70
 *    still comes first and 0.0f stays in the loop. A separate non-sda D_001A79F0 gives +1 but a
 *    different load. Shift-spelled stride: not reduced. Entry set in the increment: two sets, no giv.
 * 2. Retail has `mov.s $f13,$f21` before the blez and divides by $f13. Here both copies divide by
 *    $f21: `one` is gone, presumably by gcse copy propagation (not confirmed in a gcse dump), and
 *    -fno-gcse breaks the prologue. A copy that survives, or a numerator reaching both copies
 *    from the loop pass, should close it.
 * The second qcopy reads the stack copy as retail does; typed TI copies fold it back to origin.
 */
#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef union { Vector q; float f[4]; } ChoiceVector;
typedef struct {
    unsigned char pad0[0xE0]; float origin[4];
    unsigned char pad1[0x1B8 - 0xF0]; int count;
    unsigned char pad2[0x208 - 0x1BC]; short gate;
    unsigned char pad3[0xC28 - 0x20A]; int flags;
    unsigned char pad4[0x2290 - 0xC2C]; void *object;
    unsigned char pad5[0x22A4 - 0x2294]; int mode;
    unsigned char pad6[0x22BB - 0x22A8]; unsigned char byte_22bb;
    unsigned char pad7[0x24CC - 0x22BC]; int state;
} HeroChoiceState;
extern HeroChoiceState D_00189E20;
extern int D_001A79F0 __attribute__((sda));
extern int D_001A7398 __attribute__((sda));
extern unsigned char D_00139568[];
extern unsigned char D_L00_00262570[];
typedef struct {
    unsigned char pad0[0x50]; int selector;
    unsigned char pad1[4]; float weight;
    unsigned char pad2[4]; int inactive;
    unsigned char pad3[12];
} ChoiceRecord;
extern ChoiceRecord D_L00_0025BC00[4];
extern int D_L00_0025BDB0;
extern int func_L00_002ADEA0(int);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_002A7878(float, float);

int func_L00_002CA4E0(int *selected)
{
    int choices[20], count = 0, index;
    ChoiceRecord *entry, *records;
    ChoiceVector raised, origin;
    ChoiceVector *startp, *endp;
    float *origin_source;
    int *next;
    float sum, draw;
    if (D_00189E20.gate != 0) return 0;
    if (D_00189E20.state == 1) {
        *selected = 3;
        if (D_L00_0025BDB0 != 0) return 0;
        if ((D_00189E20.flags & 2) == 0) return 0;
        return func_002A7878(0.0f, 1.0f) < 0.33f;
    }
    records = D_L00_0025BC00;
    startp = &origin;
    endp = &raised;
    origin_source = D_00189E20.origin;
    next = choices;
    for (index = 0; index < 4; index++) {
        float zero = 0.0f;
        int area;
        entry = &records[index];
        if (entry->inactive != 0 || entry->weight == zero) continue;
        area = func_L00_002ADEA0(0);
        if (entry->selector != -1 && entry->selector != area) continue;
        if (index == 2) {
            if (D_001A79F0 != 7 && D_001A79F0 != 0x13) continue;
            if (D_00189E20.byte_22bb == 2) continue;
            qcopy(startp, origin_source);
            qcopy(endp, startp);
            raised.f[2] += 8.0f;
            if (func_002761F8(startp, endp, 2, D_00189E20.object, 0)) continue;
        }
        if (index == 3 && (D_00189E20.mode != 1 || D_00189E20.count > 50 || D_00189E20.state > 1)) continue;
        *next = index;
        count++;
        next++;
    }
    if (!count) return 0;
    sum = 0.0f;
    for (index = 0; index < count; index++) {
        sum += 1.0f / (float)(int)(D_L00_0025BC00[choices[index]].weight * 60.0f);
    }
    draw = func_002A7878(0.0f, 1.0f);
    if (draw < sum) {
        float one = 1.0f;
        ChoiceRecord *table = D_L00_0025BC00;
        int size = sizeof(ChoiceRecord);
        float rate = 60.0f;
        int *cursor = choices;
        for (index = 0; index < count; index++, cursor++) {
            int choice = *cursor;
            *selected = choice;
            sum -= one / (float)(int)(*(float *)((char *)table + choice * size + 0x58) * rate);
            if (sum < draw) break;
        }
        if (D_001A7398 == 30 && D_L00_00262570[D_00139568[30] * 0xE0 + 4] == 0) {
            if (*selected == 1) *selected = 0x91;
            else if (*selected == 2) *selected = 0x92;
        }
        return 1;
    }
    return 0;
}
