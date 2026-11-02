/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, task v1626 (2026-10-29): retained improved near miss.
 * Current toolchain, -O2 -G8 -ffunction-sections -frac2-hazard-labels:
 * 5680/5680 bytes; check.py: 0 of 2 USA v1.01 places match (L03/L14),
 * first difference +0x1358. Eight instruction positions differ, excluding
 * relocation address immediates; this is not a linked match.
 *
 * Improvements over the historical drafts below:
 * - MotionInit's measured fields at +0x134/+0x144, with acceleration assigned
 *   first, reproduce both initial FPR choices AND retail's load/store order.
 * - State 22 uses qzero_nc for both independent, aligned local vectors. The
 *   second bare clear invalidates CSE's address value, so the second vector's
 *   address is rebuilt after its clear, as in retail. No surrounding accesses
 *   depend on either cleared local's old contents.
 * - A scoped pointer to other, initialized AFTER other.f[2] = height, keeps
 *   &other in s6; inline object+0xC0 expressions spill the matrix pointer to
 *   sp+0x30 and the rotation pointer to sp+0x34, matching retail allocation.
 * - Reversing the two final zero assignments reproduces their retail schedule.
 *
 * Remaining state-22 differences:
 * +0x1358..+0x1364: cc1 emits li.s 0.8 before li v0,0x940; retail reverses
 * those independent constant preparations.
 * +0x139C..+0x13A8: cc1 emits matrix-address add, other.z store, spill store,
 * point argument; retail emits other.z store, matrix add, point argument, spill.
 * Everything else aligns in check.py's side-by-side disassembly apart from
 * unresolved address immediates. Relocation consistency and linked placement
 * remain unqualified because the text differs. PAL/US2 and linking not run.
 *
 * New negative measurements: inline matrix alone was 5668 bytes; an explicit
 * vector pointer introduced before its clear disturbed position allocation.
 * Initializing that pointer before the class switch uses s7 instead of s6.
 * Per-arm height initialization changes switch flow; loading the class into a
 * local, a measured class struct field, and named vector component fields each
 * tie this retained version. Stopped after 11 source candidates at this tie;
 * reopen with a new scheduling hypothesis, not equivalent type spellings.
 * All required declarations are included below. Older notes are dated history
 * and their residual-difference descriptions are superseded by this block.
 */
#define MACRO_ADDR __attribute__((section(".sdata")))
/* Finisher F1 (2026-10-26, base f5fab978 with qzero_nc): 1391 of 1420 instructions aligned with
 * registers (was 1363 on this head). What moved it:
 *  - qzero_nc(&point) in state 22 (qzero(&other) keeps the clobber);
 *  - the hero distance in state 4 through the union view (HERO->f[0x80 / 4], [0x84 / 4]):
 *    retail addresses D_00189E20 with 0x80/0x84 offsets, not D_00189EA0;
 *  - cases 19 and 20 read SP(0x358) inline instead of through `target` (its pointer then
 *    takes $v0 as in retail);
 *  - state 22's class switch has `case 0x93C:` with the default (0x93C is a class id from
 *    state 1). A case below 0x940 that goes to the default gives retail's `slti 0x941` test:
 *    emit_case_nodes only emits the bound test when the root's other child is not a single
 *    value, and jump deletes the dead 0x93C compare;
 *  - other.f[2] = height (no reload of point.f[2]);
 *  - in the member loop the index store comes first (its D_L03_001B2A1C load is then in the
 *    beqz slot as retail, before the two -1 stores).
 * Left: state 0's two float temps (D_L03_001AFEE0 in $f1, 0.0016666667f in $f0 in retail:
 * local-alloc tie, swapping the two statements breaks cross-jumping), and state 22's
 * allocation: retail keeps &other in $s6 and spills object+0xC0 (sp+0x30) and object+0xF0
 * (sp+0x34); here $s6 is object+0xC0 and the slots are swapped.
 * F3 (2026-10-26): same 1391/1420 on 795143e6. State 1's pair after sched1 (lreg): insn 67
 * reg111 = D_L03_001AFEE0, insn 71 reg112 = 0.0016666667f, stores 0x144 (111) then 0x134
 * (112). Both lives are 2 (equal priority), so qty order (birth) gives 111 $f0. Retail needs
 * 112 to rank first while sched2 still emits the load first and the 0x144 store first. Tried,
 * no change: locals for either value in any order, a comma expression, MACRO_ADDR or an sda
 * array for D_L03_001AFEE0. Swapping the stores gives retail's registers but the li.s first.
 */
/* Opus handoff (big8, 2026-10-26): func_L03_003C1BF0, 5680 bytes, 2 places
 * (L03 0x003C1BF0, L14 0x003C5250). Built on the earlier corrected draft (5552 bytes,
 * 0.66 aligned). Step 0: one function. Two jump tables: jtbl_L03_002A8F40 (9 entries,
 * byte +0x95, case 0 explicit) and jtbl_L03_002A8F70 (22 entries, byte +0x20 minus 1).
 * Profile: -O2 -G8 -ffunction-sections -frac2-hazard-labels (the label on the hazard nop
 * in state 22). Measured in src/levels/shared/L03_003C1BF0.c: 5680 bytes (size equal),
 * 1397/1420 opcodes aligned, 1366 with registers; every state but 22 is aligned.
 * What moved it from 936 to 1394 aligned:
 *  - state bodies in retail address order: 1, 2, 4, 3, 5, 6/8, 7, 12, 13, 9, 10, 11, 14,
 *    15, 16, 17, 18, 19, 20, 21, 22; states 14, 18 and 20 written out per arm (retail has
 *    three bodies and cross-jumps their func_002A7750 tails);
 *  - state 1 is a switch on the moby class (0x940, 0x93C, 0xA59, 0x964/default) and calls
 *    func_002B38B8 on pvars+0x354;
 *  - then-arm first where retail falls through (states 4, 10, 11, 15);
 *  - hero fields through the union view (0x26C, 0x270, +0x80 as base+offset), but
 *    D_00189E20 + 0x80 as a plain symbol address for func_00282E80 and the 419BD8 test;
 *  - u16 incomplete arrays for D_0018CB20/38/2C, D_0018CDCC/E4, D_0018CF58 (lui+lhu/sh),
 *    D_0018CB4C[] and D_L03_001BFDD8[]; (int)object >> 8 (sra); u32 dispatch;
 *  - MACRO_ADDR for D_L03_001B2548, _1B2A1C, _1B2A20: retail reads them absolutely in
 *    flow and $gp-relative in delay slots;
 *  - pvars+0x358 re-read in state 15; state 15's sign test reads back +0x344 after
 *    zeroing it; the final float clears through a local zero.
 * State 22's class switch: 0.8f first, case 0x964 setting 0.3f and falling into case 0x940's
 * store, default storing separately (this gave the retail size).
 * Still off, all in state 22: retail's tree also tests <0x941 before 0x964 (GCC emits that
 * only when the right child is not a single value: a third case or range is missing),
 * object+0x10 kept in $fp, object+0xC0 / object+0xF0 spilled to sp+0x30/0x34, -1 and 0xF2D hoisted into s5/s7 for the member loop.
 */
#include "common.h"
typedef struct {
    u8 reserved00[0x134]; float acceleration;
    u8 reserved138[12]; float max_speed;
} MotionInit;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } MotionVector;
typedef struct {
    u8 reserved00[0x18]; u8 enabled, count, kind; u8 reserved1B[0x65]; u8 payload[1];
} DispatchContext;
extern float D_00189EA0[], D_00189F00[];
extern u8 D_00189E20[];
typedef union { u8 b[0x2600]; u8 *ptr[0x980]; float f[0x980]; } Hero;
#define HERO ((Hero *)D_00189E20)
extern u16 D_0018CB20[], D_0018CB38[], D_0018CDCC[];
extern u16 D_0018CB2C[], D_0018CF58[], D_0018CDE4[];
extern int D_0018CB4C[];
extern int D_L03_001B2548 MACRO_ADDR;
extern u8 *D_L03_001B2A1C MACRO_ADDR;
extern u8 *D_L03_001B2A20 MACRO_ADDR;
extern u8 *D_L03_001BFDD8[];
extern float D_L03_001AFEE0 __attribute__((sda));
extern float D_L03_001AFEE4 __attribute__((sda));
extern float D_L03_001AFEE8 __attribute__((sda));
extern float D_L03_001AFEEC __attribute__((sda));
extern float D_L03_001AFEF0 __attribute__((sda));
extern float D_L03_001AFEF4 __attribute__((sda));
extern void func_L03_003C3220(u8 *);
extern int func_002B3890(u8 *);
extern int func_002B3868(u8 *);
extern int func_002B38B8(u8 *);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern u32 func_002B1C20(void *, DispatchContext *);
extern void func_002A7750(u8 *, s32, s32);
extern int func_00288E18(int, int);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *, int, int, int);
extern void func_L03_003C4368(u8 *, void *);
extern void func_L03_003C4240(u8 *);
extern void func_L03_003C4BD8(u8 *);
extern void func_L03_003C4A10(u8 *, void *);
extern float func_00282E80(void *, void *);
extern int func_L03_00419BD8(u32, void *, void *);
extern float func_002AA340(int *, int, int);
extern int func_L03_003C41B8(u8 *, int, int);
extern int func_L03_003C58F0(u8 *, float *);
extern float func_00283180(float), func_00283198(float), func_00283248(float, float);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float), func_00283098(void *, void *, void *);
extern int func_L01_00322288(int, float);
extern int func_00282948(void *);
extern int func_L03_003C5DC8(u8 *, u8 *);
extern u32 func_L03_004197A8(u8 *);
extern void func_L03_00419818(u8 *, u32);
extern void func_002AFDD8(char *, char *, char *, char *);
extern void func_0029F338(void *);
extern u8 *func_L03_003C4D40(u8 *);
extern void func_L03_003C5B28(u8 *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002AEB60(char *, float);
extern int func_002A8D70(float, float, float, void *, int, int, int, int, int);
extern float func_0029F530(char *);
extern float func_L02_00321C30(void *, void *, float);
extern void func_L03_00419A60(u32, u8 *, s32);
extern int func_L03_003C5CE8(u8 *);
extern u32 func_L03_003CAAC8(u8 *, u8 *);
extern void func_L03_003C5EE8(void *);
extern void func_002AC9F8(float *, float);
extern void func_0029FCC0(char *, int, char *);
extern void func_L03_003CA220(u8 *, float), func_L00_003294F0(u8 *, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002A89A8(u8 *, int, float);
extern int func_L03_00419C00(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002B5258(char *), func_L03_003C4468(u8 *), func_002A677C(u8 *);
#define SF(o) (*(float *)(state + (o)))
#define SI(o) (*(int *)(state + (o)))
#define SP(o) (*(u8 **)(state + (o)))
#define OF(o) (*(float *)(object + (o)))
#define ANIM_FRAMES(off) (*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + (off)) + 0x10))


void func_L03_003C1BF0(u8 *object)
{
    MotionVector point, other, delta;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *target, *parent, *member, *pos, *mtx, *rot;
    u32 dispatch;
    int type, code, i, entered;
    float heading, turn, distance, floor, height;
    func_L03_003C3220(object);
    switch (object[0x95]) {
    case 0:
        break;
    case 1:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.0034906589426100254f, 0.10471977293491364f);
            ((MotionInit *)state)->acceleration = 0.0016666667f;
            ((MotionInit *)state)->max_speed = D_L03_001AFEE0;
        }
        break;
    case 2:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEE8 * 0.00027777778f, D_L03_001AFEEC * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            SF(0x144) = 0.0f; SF(0x134) = 0.0055555557f;
        }
        break;
    case 3:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            SF(0x134) = 0.0055555557f; SF(0x144) = 0.1f;
        }
        break;
    case 4:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.4f;
        break;
    case 5:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.05f;
        break;
    case 6:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.006981317885220051f, 0.20943954586982727f);
        SF(0x134) = 0.005f; SF(0x144) = 0.05f;
        break;
    case 8:
        dispatch = func_002B1C20(object, (DispatchContext *)(state + 0x60));
        if (dispatch & 1) { func_0029F338(object); return; }
        if (dispatch & 2) func_002A7750(object, 2, 0);
        break;
    }
    {
        switch (object[0x20]) {
        case 1:
            if (func_002B38B8(SP(0x354))) {
                switch (*(s16 *)(object + 0xAA)) {
                case 0x940:
                    if (D_0018CB20[0] == 0) func_00288E18(0x9CF, 0x26);
                    break;
                case 0x93C:
                    if (D_0018CB38[0] == 0) func_00288E18(0x9D1, 0x28);
                    break;
                case 0xA59:
                    if (D_0018CDCC[0] == 0) func_00288E18(0xA08, 0x5F);
                    break;
                case 0x964:
                default:
                    if (D_0018CB4C[0] >= 0) func_00288E18(0x9D2, 0x29);
                    break;
                }
                func_002A7750(object, 4, 1);
            }
            break;
        case 2:
            if (HERO->ptr[0x270 / 4] == object || HERO->ptr[0x26C / 4] == object)
                func_L03_003C4368(object, &HERO->b[0x80]);
            func_L03_003C4240(object);
            if (object[0x31]) func_L03_003C4BD8(object);
            break;
        case 4:
            if (func_002B3868(object)) {
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 15);
                SI(0x380) = 2; qzero(state + 0x1B0);
            }
            if (HERO->ptr[0x270 / 4] == object || HERO->ptr[0x26C / 4] == object)
                func_L03_003C4368(object, &HERO->b[0x80]);
            func_L03_003C4240(object);
            distance = func_00282E80(object + 0x10, D_00189E20 + 0x80);
            if (D_L03_001AFEE4 < distance && func_L03_00419BD8((u32)SI(0x220), object + 0x10, D_00189E20 + 0x80)) {
                func_002A7750(object, 3, -1);
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 10);
            } else {
                if (object[0x31] && object[0x42] != 1) {
                    if (SI(0x380) < 5) func_L03_003C4A10(object, D_00189F00);
                    else func_L03_003C4BD8(object);
                }
            }
            if ((object[0x60] & 2) && object[0x42] == object[0x43]) {
                if (object[0x42] == 1)
                    func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 15);
                else if (!func_002A77E0(SI(0x380))) {
                    func_002AA340((int *)(state + 0x380), 10, 1);
                    if (object[0x43] != 1) func_002A7470(object, 1, 0, 15);
                }
            }
            break;
        case 3:
            if (!func_L03_003C41B8(object, (int)D_00189EA0, 1) || SF(0x1DC) < D_L03_001AFEE0 ||
                (SI(0x190) > 60 && SF(0x1DC) < D_L03_001AFEE4)) {
                func_002A7750(object, 4, -1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            }
            if ((D_L03_001B2548 & 15) == (((int)object >> 8) & 15))
                SI(0x360) = func_L03_003C58F0(object, D_00189EA0);
            break;
        case 5:
            if (func_002B3868(object)) {
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 20);
                SF(0x144) = 0.1f;
            }
            point.f[0] = func_00283180(SF(0x374)); point.f[1] = func_00283198(SF(0x374)); point.f[2] = 0;
            func_00282CC0(&point, &point, object + 0x10);
            func_L03_003C41B8(object, (int)&point, 1);
            if (*(u16 *)(object + 0x96) >= 61) {
                SF(0x144) = D_L03_001AFEE0;
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            }
            break;
        case 6:
        case 8:
            if (func_002B3868(object)) {
                if (object[0x20] == 8) { if (object[0x43] != 7) func_002A7470(object, 7, 0, 20); }
                else if (object[0x43] != 3) func_002A7470(object, 3, 0, 20);
            }
            func_L01_00322288((int)object, func_00283248(HERO->f[0x80 / 4] - OF(0x10), HERO->f[0x84 / 4] - OF(0x14)));
            if (object[0x60] & 2) func_002A7750(object, 4, -1);
            break;

        case 7:
            if (func_002B3868(object)) SF(0x144) = 0.1f;
            if (func_00282E80(object + 0x10, state + 0x340) > SF(0x144)) {
                func_L03_003C41B8(object, (int)(state + 0x340), 0);
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 20);
            } else if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
            if (func_00282948(state + 0x37C)) func_002A7750(object, 4, -1);
            break;
        case 12:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if ((D_L03_001B2548 & 3) == (((int)object >> 8) & 3))
                SF(0x110) = func_L03_003C5DC8(object, state + 0x340) ? 0.11f : 0.15f;
            if (!func_L03_004197A8(SP(0x358))) {
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            } else if (SF(0x1DC) < SF(0x144)) func_002A7750(object, 13, -1);
            break;
        case 13:
            if (func_002B3868(object)) {
                func_L03_00419818(SP(0x358), (u32)object); SF(0x140) = 0.174532949924469f;
                func_002AFDD8((char *)SP(0x358), (char *)(state + 0x1B0), (char *)(state + 0x1B0), 0);
                SF(0x1B4) = 0;
                func_00283098(state + 0x1B0, state + 0x1B0, SP(0x358) + 0xC0); SF(0x110) = 0;
            }
            func_L03_003C41B8(object, (int)(SP(0x358) + 0x10), 0);
            if (func_00282E80(object + 0x10, SP(0x358) + 0x10) < 0.1f) { func_0029F338(object); return; }
            break;
        case 9:
            if ((D_L03_001B2548 & 7) == (((int)object >> 8) & 7)) SP(0x358) = func_L03_003C4D40(object);
            parent = SP(0x194);
            if (parent) {
                if (SP(0x198) && *(s16 *)(SP(0x198) + 0xAA) == 0x97A) heading = OF(0xF8);
                else {
                    heading = func_00283248(*(float *)(parent + 0x10) - OF(0x10), *(float *)(parent + 0x14) - OF(0x14));
                    turn = func_00283BE0(heading, OF(0xF8));
                    heading = func_00283B98(turn < 0.0f ? -1.5707963705062866f : 1.5707963705062866f, OF(0xF8));
                }
                func_L03_003C5B28(object, heading);
            }
            target = SP(0x358);
            if (!target) {
                func_002A7750(object, 11, -1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
                break;
            }
            func_L03_003C41B8(object, (int)(target + 0x10), 0);
            if ((D_L03_001B2548 & 3) == (((int)object >> 8) & 3)) {
                qcopy(&point, object + 0x10); point.f[2] += 0.2f;
                func_00282F20(&other, object + 0xC0, 0.3330000042915344f);
                func_00282CC0(&other, &other, object + 0x10); other.f[2] += 0.2f;
                if (func_002761F8(&point, &other, 0, object, 0) && D_L03_001BFDD8[0] == SP(0x358)) {
                    func_002A7750(object, 10, -1);
                    if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
                }
            }
            break;
        case 10:
            if (func_002AEB60((char *)object, 14.0f))
                func_002A8D70(0.3330000042915344f, 4.0f, 1.0f, object, 1, 0x10000, 0, 1, 0);
            else if (object[0x60] & 2) {
                SP(0x358) = func_L03_003C4D40(object);
                if (SP(0x358)) {
                    func_002A7750(object, 9, -1);
                    if (object[0x43] != 3) func_002A7470(object, 3, func_002A77E0(ANIM_FRAMES(0x54)), 10);
                } else {
                    func_002A7750(object, 11, -1);
                    if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
                }
            }
            break;
        case 11:
            if ((D_L03_001B2548 & 7) == (((int)object >> 8) & 7)) SP(0x358) = func_L03_003C4D40(object);
            func_L03_003C4BD8(object);
            if (SP(0x358)) {
                func_002A7750(object, 9, -1);
                if (object[0x43] != 3) func_002A7470(object, 3, func_002A77E0(ANIM_FRAMES(0x54)), 20);
            } else if (*(u16 *)(object + 0x96) >= 301) {
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
            }
            break;
        case 14:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (func_002B3868(object)) D_0018CB2C[0] = -1;
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) func_002A7750(object, 15, -1);
            break;
        case 15:
            if (func_002B3868(object)) {
                if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
                *(int *)(object + 0x98) = 0;
                func_00282CF0(state + 0x340, state + 0x340, SP(0x358) + 0x10);
                func_002AFDD8((char *)SP(0x358), (char *)(state + 0x340), (char *)(state + 0x340), 0);
                SF(0x344) = 0;
                if (SF(0x340) < SF(0x344)) SF(0x340) = -3.8f;
                else SF(0x340) = 3.8f;
                func_00283098(state + 0x340, state + 0x340, SP(0x358) + 0xC0);
                func_00282CC0(state + 0x340, state + 0x340, SP(0x358) + 0x10);
            }
            heading = func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14));
            func_L01_00322288((int)object, heading);
            if (func_0029F530((char *)object) > 11.0f) func_L02_00321C30(object + 0x10, state + 0x340, 0.13333334f);
            if (object[0x60] & 2) {
                func_L03_00419A60(SI(0x220), SP(0x358) + 0x10, 1);
                func_002A7750(object, 16, -1);
                if (object[0x43] != 5) func_002A7470(object, 5, 0, 5);
                func_L00_003294F0(SP(0x358), 1);
            }
            break;
        case 16:
            if (func_002B3868(object)) SP(0x198) = 0;
            if (func_00282E80(D_00189EA0, SP(0x358) + 0x10) > 12.0f &&
                !func_L03_003C5CE8(object) && !func_L03_003CAAC8(SP(0x358), D_00189EA0))
                func_L03_003C5EE8(object);
            break;
        case 17:
            func_00282CF0(&point, state + 0x340, object + 0x10);
            func_002AC9F8(point.f, 0.4166666865348816f);
            func_00282CC0(object + 0x10, object + 0x10, &point);
            if (object[0x42] == object[0x43]) {
                qcopy(object + 0x10, state + 0x340);
                func_002A7750(object, 6, 1);
            }
            break;
        case 18:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) {
                func_002A7750(object, 19, -1);
                func_L00_003294F0(SP(0x358), 1);
            }
            break;
        case 19:
            if (func_002B3868(object) && object[0x43] != 4) func_002A7470(object, 4, 0, 10);
            func_L01_00322288((int)object, func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x42] == object[0x43]) {
                if (func_0029F530((char *)object) >= 10.0f) {
                    func_0029FCC0((char *)object, 3, (char *)&point);
                    func_L03_003CA220(SP(0x358), point.f[2] - OF(0x18));
                }
                if (object[0x60] & 2) {
                    func_002A7750(object, 6, 1); func_L00_003294F0(SP(0x358), 0);
                }
            }
            D_0018CF58[0] = -1;
            break;
        case 20:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) func_002A7750(object, 21, -1);
            break;
        case 21:
            if (func_002B3868(object)) {
                if (object[0x43] != 5) func_002A7470(object, 5, 0, 10);
                D_0018CDE4[0] = -1;
            }
            func_L01_00322288((int)object, func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x60] & 2) func_002A7750(object, 6, 1);
            else if (func_002AEB60((char *)object, 20.0f)) func_L00_003294F0(SP(0x358), 1);
            break;
        case 22: {
            MotionVector *offset;
            func_00282CC0(object + 0x10, object + 0x10, state + 0x1B0);
            qzero_nc(&point); qzero_nc(&other);
            height = 0.8f;
            switch (*(s16 *)(object + 0xAA)) {
            case 0x964:
                height = 0.3f;
            case 0x940:
                point.f[2] = height;
                break;
            case 0x93C:
            default:
                point.f[2] = height;
                break;
            }
            other.f[2] = height;
            offset = &other;
            func_00283098(&point, &point, object + 0xC0);
            if (SF(0x1B8) < 0.0f) {
                SF(0x1B8) -= SF(0x398);
                if (OF(0xF4) > 0.0f) func_002AA548(object + 0xF4, state + 0x39C, 0, 0.006981317885220051f, 0.006981317885220051f, 0.41887909173965454f);
                else OF(0xF4) = func_00283BE0(OF(0xF4), 0.41887909173965454f);
                if (OF(0x18) < SF(0x3A0)) {
                    floor = func_002A89A8(object + 0x10, 0, 0.5f);
                    if (OF(0x18) <= floor) {
                        OF(0x18) = floor; func_002A7750(object, 4, 1);
                        for (member = D_L03_001B2A1C; member <= D_L03_001B2A20; member += 256) {
                            if (*(s16 *)(member + 0xAA) == 0xF2D && func_L03_00419C00(member, object + 0x10, object + 0x10)) {
                                SI(0x220) = ((int)member - (int)D_L03_001B2A1C) >> 8;
                                SI(0x368) = -1; SI(0x36C) = -1;
                            }
                        }
                    }
                }
            } else {
                SF(0x1B8) -= SF(0x394); OF(0xF4) = func_00283BE0(OF(0xF4), 0.41887909173965454f);
            }
            func_002833F0(object + 0xC0, object + 0xF0);
            func_00283098(offset, offset, object + 0xC0);
            func_00282CF0(&delta, &point, offset);
            func_00282CC0(object + 0x10, object + 0x10, &delta);
            break;
        }
        }
    }
    code = object[0x20];
    if (code != 22 && code != 1 && code != 15 && code != 16 && (SF(0x1A0) < OF(0x18) - 0.05f || SP(0x198))) {
        float zero = 0.0f;
        OF(0xF0) = zero; OF(0xF4) = zero; func_002B5258((char *)object);
    }
    func_L03_003C4468(object);
    func_002A677C(object);
}
