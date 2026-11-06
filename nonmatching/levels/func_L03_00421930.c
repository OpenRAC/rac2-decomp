/* 6 November 2026, round 2: C below unchanged (416/412, 0/1 USA). A do/while(0) group around
 * the last two, the last three or one AC0 call, or around func_002A7750, gives 420/412 each;
 * base and stride stay local-alloc quantities in s0/s1 (lui into s0), since loop notes do
 * not split the block. Retail needs them global (obj s0, base s1, stride s2, p s3).
 */
/* 4 November 2026 current-RAC1 source-method trial; retained, not linked.
 * Two new real-operation group trials (the first append call and the state-pointer read) each
 * produce 420/412 bytes, 0/1 USA placements. Neither promotes table/stride allocation as
 * required; the older best C below is retained.
 */
/* opus-1 xhigh, USA v1.01: 416 bytes / 412 retail, 0 of 1 places match.
 * (The earlier form of the alpha test, >= 2 first, gives 412/412 with the wrong
 * final layout; the arm order below reproduces retail's layout.)
 * The remaining rows appear to follow from one allocation difference: retail has obj s0,
 * table base s1, stride s2, p s3; here base s0, stride s1, obj s2, p s3.
 * Base and stride are single-block, single-death pseudos in case 0, so local-alloc
 * takes them first and ties the %hi temp to the base. Retail's `lui v0` then
 * `addiu s1, v0` shows both were global pseudos there. The extra 4 bytes and both
 * dispatch delay slots come from this: `ld s0` can fill them only while s0 is dead
 * in case 0; with obj in s0 reorg must steal `lh a1` into a beql.
 * Priorities (floor_log2(refs) * refs / length) would need obj > base > stride > p:
 * obj 13 refs, length 71 = .549; base 5, 21 = .476; p 7, 34 = .412; stride 5, 25 = .400
 * (base and stride lengths are local-alloc qty lengths halved, an estimate).
 * So stride also needs length <= 24, or p length >= 36, and any added ref of p
 * (8 refs) lifts p above obj. A test between the AC0 calls does make both global
 * (obj s0, lui v0) but then gave p s1, base s2, stride s3 and leaves its own words.
 * The split probably lies after the first AC0 call, since mtc1 f20 sits above the A98
 * call in the same block. No allowed construct found that splits it and leaves no code.
 * No change from: -G8 unit, explicit base/stride locals, typed record array.
 * Declarations needed are below; compiled in the plain .c unit, not linked.
 */
#include "include_asm.h"
#include "common.h"

extern char D_L03_00259A30[];
extern void func_L00_00322A98(u8 *, char *);
extern void func_L00_00322AC0(char *, s32, s32, float);
extern void func_L00_00322BE0(char *, s32);
extern void func_L00_00322EC8(char *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_00273B70(u8 *);
extern void func_0029F338(void *);

#define REC(o) (&D_L03_00259A30[*(s16 *)(p + 0x36) * 0x150])

void func_L03_00421930(u8 *obj)
{
    u8 *p = *(u8 **)(obj + 0x68);

    switch (obj[0x20]) {
    case 0:
        func_L00_00322A98(obj, REC(obj));
        func_L00_00322AC0(REC(obj), 0x28, 2, 0.0f);
        func_L00_00322AC0(REC(obj), 0x14, 4, 0.0f);
        func_L00_00322AC0(REC(obj), 0xA, 6, 0.0f);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        func_L00_00322BE0(REC(obj), 0);
        if (func_00273B70(obj) != 0) {
            func_002A7750(obj, 2, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 2:
        func_00273B70(obj);
        func_L00_00322EC8(REC(obj));
        if (obj[0x23] < 2) {
            func_0029F338(obj);
        } else {
            obj[0x23] -= 2;
        }
        break;
    }
}
