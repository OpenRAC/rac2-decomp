/* func_L22_003A2780 - 520 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file src/levels/shared/L22_003A2780.c (default flags + qcopy
   helper), marker removal in L22_0039D708.c needed. 488 vs 520 bytes (2
   places).
   Logic decoded (path walk in 8.0 steps; func_L22_003A2988 clips;
   func_002761F8 collision test; qcopy origin<-next). Retail saved-reg layout:
   s0=end, s2=start, s1=st,
   s4=&cur(sp+0x40) with a second alias s7=s4, fp=&origin(sp+0x20),
   s5=&dir(sp+0x10), s3=&step(sp+0x50), s0 re-bound to &next(sp+0x30); mine
   allocates fewer pointer pseudos. */

#include "common.h"

extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002761F8(void *, void *, int, int, int);
extern void func_L22_003A2988(void *, float);

s32 func_L22_003A2780(u8 *obj, f32 *start, f32 *end) {
    u8 *st;
    f32 target[4] __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));
    f32 origin[4] __attribute__((aligned(16)));
    f32 next[4] __attribute__((aligned(16)));
    f32 cur[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    f32 dist;
    s32 done;

    if (func_00282E48(start, end) > 50.0f) {
        return 0;
    }
    st = *(u8 **)(obj + 0x68);
    qcopy(target, end);
    func_L22_003A2988(target, *(f32 *)(st + 0x114) + *(f32 *)(st + 0x110));
    func_00282CF0(dir, target, start);
    func_00282F20(dir, dir, 8.0f);
    qcopy(cur, start);
    qcopy(origin, start);
    func_L22_003A2988(target, *(f32 *)(st + 0x114) + *(f32 *)(st + 0x110));
    done = 0;
    do {
        dist = func_00282E48(cur, target);
        if (dist < 8.0f) {
            if (dist < 0.0f) {
                return 1;
            }
            func_00282F20(step, dir, dist);
            done = 1;
            func_00282CC0(next, cur, step);
        } else {
            func_00282CC0(next, cur, dir);
        }
        func_L22_003A2988(next, *(f32 *)(st + 0x114) + *(f32 *)(st + 0x110));
        if (func_002761F8(origin, next, 0x12, 0, 0) != 0) {
            return 0;
        }
        qcopy(origin, next);
        func_00282CC0(cur, cur, dir);
    } while (done == 0);
    return 1;
}
