/* Retained near miss, 2026-10-28: -g profile744/740 bytes, six compiles.
 * Moving real accumulated/count initialization to first use restores all
 * persistent GPR/FPR roles and the0xe0 frame. Clamp snapshots preserve retail
 * minimum/load/store semantics without volatile. Remaining early base scratch
 * GPRs differ, and an anticipatory shape-field read survives before collision
 * work. -fno-regmove ties; -fno-gcse changes frame to0xf0 and reaches736 bytes,
 * so both controls are removed. Reopen on a real base/shape pointer lifetime
 * witness preserving the dependent movement/clamp stores.
 * ABI audit: helper424070 forwards incominga2 to vector difference at+0x24,
 * despite the old two-argument C definition in the parent unit. The actual
 * caller also supplies an unused float radius. This draft exposes the full
 * observed interface; lead must correct/requalify the old definition before
 * any candidate promotion. Collision77258 mask is proven by savedS3 bit tests,
 * while its third input is an excluded object pointer (identity compares).
 * All six working vectors16, controllerprefix0x238, inputobjectprefix0x74,
 * global plane/direction16 each and heroowner+0x2290/flag+0x22b4 are real.
 */
#include "common.h"

typedef int TraceQuad __attribute__((mode(TI)));
extern int func_L00_004204A0(TraceQuad *);
/* Retail forwards the third pointer to vector difference; the radius bank
 * is supplied by this caller although this particular predicate ignores it. */
extern int func_L00_00424070(char *, int, void *, float);
extern int func_L00_00423CA8(char *, void *, int, float, float);
extern int func_00277258(void *, int, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern int D_L00_001B1850[] __attribute__((sda));
extern char D_00189E20[];
extern char D_L00_001BF220[], D_L00_001B8E50[];
extern float D_00138280;
extern float D_L00_001B14B4[] SDATA(D_L00_001B14B4);
extern float D_L00_001B14C8[] SDATA(D_L00_001B14C8);
extern float D_L00_001B14D0[] SDATA(D_L00_001B14D0);
struct TraceFrame {
    float initial[4], point[4], unit[4], advance[4], saved[4], difference[4];
    char *shape;
    int result;
};
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))

/* Six complete16-byte locals and real stored shape/result fields. The
 * controller prefix reaches+0x238; movement supplies its full16-byte vector.
 * Every working vector is copied or written by a verified vector producer
 * before arithmetic. Global plane/direction reads each cover16 bytes. */
int func_L00_004240D8(char *object)
{
    struct TraceFrame f;
    char *base, *movement, *state;
    float speed, accumulated;
    int i;
    f.result = 0;
    base = P(object, 0x70);
    f.shape = base + 0x60;
    movement = base + 0x160;
    state = base + 0x1f0;
    qcopy(f.initial, movement);
    accumulated = 0.0f;
    qcopy(f.point, base + 0xb0);
    speed = D_L00_001B14D0[0];
    i = 0;
    func_00282F20(f.unit, f.initial, 1.0f);
    while (1) {
        float one = 1.0f;
        float ratio;
        int count = func_00283CF0(F(state, 0x40) - one);
        if (i >= count) break;
        if (i > 0 && !func_L00_004204A0((TraceQuad *)f.point)) {
            char *hero = D_00189E20;
            if (func_00277258(f.point, D_L00_001B1850[0], P(hero, 0x2290), speed) &&
                !func_L00_00424070(object, i, f.point, speed)) {
                qcopy(f.advance, D_L00_001BF220);
                qcopy(f.saved, f.point);
                if (func_L00_00423CA8(object, f.point, i, accumulated, speed)) {
                    f.result = 1;
                    if (hero[0x22b4] != 2 && 0.05f < func_00282C48(D_00138280)) {
                        func_00282CF0(f.difference, f.advance, f.saved);
                        func_00282F20(f.difference, f.difference, one);
                        if (func_00282C48(func_00282DB0(D_L00_001B8E50, f.difference)) < 0.75f) {
                            float increment = D_L00_001B14B4[0];
                            float updated = F(state, 0x30);
                            float minimum = D_L00_001B14C8[0];
                            float length;
                            updated += increment;
                            *(short *)(state + 0x34) = 0x884;
                            F(state, 0x30) = updated;
                            length = F(movement, 0x2c);
                            if (length - updated < minimum) F(state, 0x30) = length - minimum;
                        }
                    }
                    func_00282CF0(f.difference, f.point, f.shape + 0x50);
                    func_00282F20(movement, f.difference, F(movement, 0x2c) - F(state, 0x30));
                    func_00282F20(f.unit, movement, one);
                }
            }
        }
        ++i;
        ratio = (F(movement, 0x2c) - F(state, 0x30)) / F(movement, 0x2c);
        speed += F(state, 0x44) * F(state, 0x3c);
        accumulated += speed;
        func_00282D30(f.advance, f.unit, speed * ratio);
        func_00282CC0(f.point, f.point, f.advance);
    }
    return f.result;
}
