/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* func_L11_00451178 (4,824 B, 1 place): finisher F3, 2026-10-26. The Joba twin of
 * func_L02_0040A4A8 (same particle loop: alpha = 127 after the 0x48 store, the template through
 * tmpl; see that unit's header). Profile -O2 -G8 -ffunction-sections -frac2-gcse-unsplit-edges.
 * 1206 of 1206 instructions, 4824 bytes; every instruction equal except 7 words in case 12.
 * What closed it:
 *  - one function-scope scratch array work[6] at sp+0x10: retail reuses sp+0x10..0x5F for the
 *    head's aim vector, case 7's bounds[2] + matrix[4], case 9's hand/shot/dir and case 12's
 *    5-quad buffer. Block-scoped vectors cannot share it here: an address-taken block local is
 *    preserved to the enclosing level by every following expression statement (function.c
 *    preserve_temp_slots), so the head's vector would stay live and push the frame to 0x180;
 *  - pos = object + 0x10 set in each head arm, after the call in the state->0x2D8 arm (retail's
 *    compute-then-copy);
 *  - case 5 before case 6, each with its own movement-flag test (no fall-through);
 *  - -G8 sda floats for the gp block D_L11_001B1D04..001B1D24, D_L11_001A8F20 as MACRO_ADDR
 *    (one la insn at the call), D_L11_001C0D18 as an incomplete array, the boot pointers nosda;
 *  - case 12's row copy as qcopy() in a counted loop: a TI copy lets loop.c reverse the loop;
 *  - the spill slots: retail's sp+0xC4 &work[1], 0xC8 &work[4], 0xCC tmpl, 0xD0 state+0x2B0,
 *    0xD4 object+0xC0, 0xD8 object+0xF0 is pseudo-number order (none gets a hard register from
 *    global; reload1.c gives slots in pseudo order). As gcse PRE copies the case-12 addresses
 *    come in hash-bucket order (max_cuid 1175, 587 buckets) and always after tmpl, so they are
 *    function-scope pointers declared out, scale, tmpl, spin, rows, axis.
 * Left (7 words, case 12 head): retail sets the spilled pointers in the order spin, out, axis,
 * scale, rows (stores to 0xD0, 0xC4, 0xD8, 0xC8, 0xD4); here out and scale are always adjacent
 * (0xD0, 0xC4, 0xC8, 0xD8, 0xD4 at best; all 120 orders of the five assignments give 12
 * sequences, none retail's; assigning them before the func_002B3868 call moves the frame ones
 * out of the block), and the state+0x1A8 clear is scheduled after the lw $s0 reload where
 * retail has it before.
 * v1932 (opus-1, 2026-10-31), recompiled on v2/c05: this body still gives 4824/4824 bytes, 0/1
 * places, 6 words differ (+0x1088..0x1094, +0x10D4/+0x10EC). Why single-set locals cannot fix
 * it: haifa-sched adjust_priority raises an insn that becomes ready when the func_002B3868 call
 * issues to the call's priority if birthing_insn_p (dest live, REG_N_SETS == 1). out and scale
 * are $1-based, so they depend on the call ($1 = $at is call-clobbered) and get boosted ahead of
 * axis. Retail's pointers are gcse PRE reaching registers (REG_N_SETS > 1, never boosted), as in
 * matched func_L11_0044AFC8. The natural wording (drop out/scale/tmpl/spin/rows/axis, write the
 * addresses directly, &particle for tmpl; the v1925 wip) gives retail's exact instruction order,
 * the 0x1A8 clear included. Only 15 spill-slot offsets then differ, because PRE numbers reaching
 * regs in bucket order, bucket = (14029 + regno + const) % S, S = (max_cuid/2)|1. That wording
 * has max_cuid 1176 (S 589): $1+176 wraps below $1+32. Retail's slots need S in 575..585, i.e.
 * max_cuid 1148..1171, 5 to 28 fewer insns after cse1 (or S 599 with state's pseudo >= 88, which
 * means 20+ more). Checked: deleting three object[0xBC] = 1 stores (max_cuid 1170) gives retail's
 * slots with no other change. Count-neutral: pointer locals inside one EBB, split head tests,
 * int vs float 0x1A8 clear, a byte-offset qcopy in the row loop. These change code: hoisted
 * &work[0]/&work[2] locals in case 9, a ?: argument for case 9's func_002A7750.
 * PERMUTE-FLAGS: -O2 -G8 -ffunction-sections -frac2-gcse-unsplit-edges
 *
 * closer D, 1 November 2026: the natural wording scores 19 words here. Merging the `object[0x60] & 2`
 * tails of cases 5, 6 and 10 with a shared label would lower max_cuid, but retail keeps those tails
 * apart (4,784 to 4,808 bytes), so the 5 to 28 fewer insns have to come from elsewhere.
 * Dropping the started, launch and goal locals scores 18 words; the first difference stays at +0xA24.
 *
 * closer D, later: MACRO_ADDR on D_00189E20 or D_L11_001C0D18 (one fewer insn each, same-register lui/addiu) moves
 * code, 29 to 57 words. They are not the missing 5 to 28 insns.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L11_Palette;
extern L11_Palette D_L11_00200440;
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern float D_L11_001B1D04 __attribute__((sda));
extern float D_L11_001B1D08 __attribute__((sda));
extern s32 D_L11_001B1D0C __attribute__((sda));
extern u16 D_L11_001B1D10 __attribute__((sda));
extern float D_L11_001B1D14 __attribute__((sda));
extern float D_L11_001B1D18 __attribute__((sda));
extern float D_L11_001B1D1C __attribute__((sda));
extern float D_L11_001B1D20 __attribute__((sda));
extern float D_L11_001B1D24 __attribute__((sda));
extern u8 *D_L11_001C0D18[];
extern u8 *D_0018C0B0 __attribute__((nosda));
extern u8 *D_0018C2BC __attribute__((nosda));
extern char D_L11_001A8F20[] MACRO_ADDR;

extern void func_L11_00452450(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern void func_002A7470(u8 *, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(u8 *, void *, u8 *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern s32 func_002B3890(u8 *);
extern s32 func_002B3868(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L11_00452F30(u8 *, u8 *);
extern void func_L11_004530C0(u8 *);
extern void func_L02_00333438(u8 *, void *);
extern void func_L01_00321178(u8 *, void *);
extern s32 func_L11_00441808(u8 *, u8 *);
extern void func_002B5278(u8 *, float);
extern s32 func_00282978(void *);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_L11_004530E0(u8 *);
extern s32 func_002B4FF0(u8 *, float *, float);
extern void func_L02_00333480(u8 *, void *, void *);
extern s32 func_002B50E0(u8 *, void *, float);
extern s32 func_00283DB8(void *, float);
extern void func_0029FC20(u8 *, s32, void *);
extern void func_0029FCC0(u8 *, s32, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 func_002A8C28(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *func_002C16C0(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_L11_00340500(u8 *, void *);
extern float func_0029F530(u8 *);
extern s32 func_002AEB60(u8 *, float);
extern void func_00283098(void *, void *, void *);
extern void func_003280C8(float, u8 *, void *, void *, s32, s32);
extern s32 func_002B1C20(u8 *, void *);
extern void func_L02_003FC248(u8 *, s32, s32);
extern void func_L11_00452DF8(u8 *);
extern void func_002AB6D8(void *, void *);
extern void func_L07_00321D68(u8 *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A3F10(u8 *, s32, s32 *, void *);
extern void func_002B4090(float, float, float, u8 *, void *);
extern void func_002833F0(void *, void *);
extern void func_L11_00452810(u8 *);
extern void func_L11_004528A0(u8 *);
extern void func_L00_002E6EF8(void (*)(u8 *), void *);

/* Update the Joba sentry's patrol, alert, attack and launch states. */
void func_L11_00451178(u8 *object)
{
    ActorVector target;
    ActorVector work[6];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    s32 count;
    ActorVector *out;
    ActorVector *scale;
    ActorVector *tmpl;
    float *spin;
    ActorVector *rows;
    u8 *axis;
    u8 *state;
    u8 *pos;
    float heading;
    float angle;
    float range;

    state = *(u8 **)(object + 0x68);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4 && object[0x20] != 12 && object[0x20] != 11))
        return;
    func_L11_00452450(object);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4))
        return;
    if (*(s16 *)(state + 0x2D2) == 0 && object[0x95] == 3) {
        func_002A7750(object, 4, 2);
        if (func_002A77E0(2)) {
            if (object[0x43] != 2)
                func_002A7470(object, 2, 0, 10);
        } else if (object[0x43] != 3)
            func_002A7470(object, 3, 0, 10);
    }
    if (*(u8 **)(state + 0x2C4))
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2C4) + 0x10);
    else
        target.quad = *(TI128 *)(D_00189E20 + 0x80);
    if (*(s16 *)(state + 0x2D8)) {
        func_00282CF0(&work[0], &target, object + 0x10);
        pos = object + 0x10;
        heading = 0.0f;
        angle = func_002B04E0(object, &work[0], state + 0x230);
    } else {
        pos = object + 0x10;
        heading = func_00283248(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        angle = func_00283C80(heading, *(float *)(object + 0xF8));
    }
    range = func_00282E48(pos, &target);
    if (object[0x95] == 2) {
        u8 *goal;
        if (func_002B3890(object)) {
            if (object[0x43] != 9)
                func_002A7470(object, 9, 0, 10);
            object[0xBC] = 0;
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
            func_L11_00452F30(object, func_L11_004417E8(*(u8 **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 301) {
            switch (func_002A77E0(5)) {
            case 0: if (object[0x43] != 2) func_002A7470(object, 2, 0, 10); break;
            case 1: if (object[0x43] != 3) func_002A7470(object, 3, 0, 10); break;
            case 2: if (object[0x43] != 5) func_002A7470(object, 5, 0, 10); break;
            case 3: if (object[0x43] != 6) func_002A7470(object, 6, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = func_002A77E0(100);
        }
        if (*(s16 *)(state + 0x2D2)) {
            func_002A7750(object, 5, 3);
            if (func_002A77E0(2)) {
                if (object[0x43] != 1) func_002A7470(object, 1, 0, 10);
            } else if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
        }
        if (angle > 2.7925272f)
            func_L11_004530C0(object);
        goal = state + 0x2A0;
        if (!object[0xBC] && func_00282E80(pos, goal) < 0.5f)
            object[0xBC] = 1;
        else if (*(s16 *)(state + 0x2D8))
            func_L02_00333438(object, goal);
        else
            func_L01_00321178(object, goal);
    }
    switch (object[0x20]) {
    case 3:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) func_002A7470(object, 2, 0, 0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (object[0xBC] == 0 && *(s16 *)(state + 0x2D4) < (s32)*(u16 *)(object + 0x96)) {
            if (object[0x43] != 9) func_002A7470(object, 9, 0, 10);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (func_L11_00441808(*(u8 **)(object + 0xB8), pos))
                func_002A7750(object, 4, 2);
            func_L01_00321178(object, func_L11_004417E8(*(u8 **)(object + 0xB8)));
        }
        break;
    case 5:
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 6:
        if (func_002B3868(object)) {
            if (object[0x43] != 8) func_002A7470(object, 8, 0, 10);
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.003490659f, 0.4188791f);
        }
        func_002B5278(object, heading);
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 7:
        if (func_002B3868(object)) {
            if (object[0x43] != 9) func_002A7470(object, 9, 0, 15);
            *(u16 *)(state + 0x2D6) = 0;
        }
        if (D_L11_001B1D24 < range)
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
        else if (range < D_L11_001B1D20)
            func_002B60B0(object, 0.0011111111f, 0.033333335f, 0.0005817765f, 0.052359886f);
        if (object[0x42] != 12 && range < D_L11_001B1D18 && angle < 1.5707965f) {
            if (object[0x43] != 12) func_002A7470(object, 12, 0, 10);
        } else if (object[0x42] == 12 && D_L11_001B1D1C < range) {
            if (object[0x43] != 9) func_002A7470(object, 9, 0, 15);
        } else if (object[0x42] != 12 && D_L11_001B1D04 < range && range < D_L11_001B1D08 && !func_002A77E0(D_L11_001B1D0C)) {
            if (func_00282978(state + 0x2D6) && object[0x31]) {
                u8 *other;
                s16 id;
                if (!func_002761F8(pos, &target, 1, object, 0) ||
                    ((other = D_L11_001C0D18[0]) != 0 && (id = *(s16 *)(other + 0xAA)) != 0xD98 && id != 0xDCF &&
                     id != 0xDF4 && id != 0xDF7 && id != 0xDF9 && id != 0xD37)) {
                    func_002A7750(object, 9, -1);
                    *(u16 *)(state + 0x2D6) = D_L11_001B1D10;
                }
            }
        } else if (range > 2.8f) {
            if (*(s16 *)(state + 0x2D8))
                func_L02_00333438(object, &target);
            else if (!func_L11_004530E0(object))
                func_002B4FF0(object, target.f, *(float *)(state + 0x2C8));
        } else if (*(s16 *)(state + 0x2D8)) {
            func_00282CF0(&work[0], &target, pos);
            func_L02_00333480(object, pos, &work[0]);
        } else
            func_002B50E0(object, pos, heading);
        if (angle > 2.7925272f)
            func_L11_004530C0(object);
        if (object[0x42] == 12) {
            work[1].quad = 0;
            work[1].f[0] = *(float *)(object + 0x10);
            work[1].f[1] = *(float *)(object + 0x14);
            work[1].f[2] = *(float *)(object + 0x18);
            work[1].f[3] = 2.0f;
            work[0].quad = work[1].quad;
            if (object[0x31] || func_00283DB8(work, 128.0f) > 0) {
                s32 i;
                s32 j;
                func_0029FC20(object, 4, &work[2]);
                qcopy(&work[1], &work[3]);
                func_0029FCC0(object, 4, &effect);
                func_00282F20(&near_point, work + 1, 0.85f);
                func_00282F20(&far_point, work + 1, 1.6f);
                func_00282F20(&velocity, work + 3, 0.25f);
                func_00282F20(work + 1, work + 1, 3.0f);
                func_00282CC0(&near_point, &near_point, &effect);
                func_00282CC0(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                tmpl = &particle;
                far_point.f[2] -= 0.1f;
                i = 2;
                do {
                    float first;
                    float second;
                    float third;
                    func_002ACB48(effect.f, 0.1f);
                    first = func_002A7878(0.2f, 0.4f) * 210000.0f;
                    second = func_002A7878(1.0f, 1.5f) * 210000.0f;
                    third = func_002A78D8(0.0f, 0.01f);
                    func_002C65A0(&effect, &velocity, 9, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        func_002A8C28(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                } while (--i >= 0);
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = func_002C16C0(&near_point, tmpl, 15, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L11_00200440.ids;
                        part[3] = 0x44;
                        if (func_002A7820(0, 1)) {
                            u8 *tail;
                            u16 alpha;
                            part[3] = 0x48;
                            alpha = 127;
                            *(u32 *)(part + 4) = 0x70707F;
                            tail = part + 0x20;
                            tail[0x11] = 0x70;
                            tail[0x12] = 0x70;
                            tail[0x13] = 0x70;
                            *(u16 *)(tail + 0x1E) = alpha;
                        }
                    }
                }
            }
        }
        break;
    case 9:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 7) func_002A7470(object, 7, 0, 10);
        }
        if (!object[0xBC] && angle < D_L11_001B1D14 * 0.017453294f) {
            object[0xBC] = 1;
            if (object[0x43] != 17) func_002A7470(object, 17, 0, 10);
        } else if (*(s16 *)(state + 0x2D8))
            func_L11_00340500(object, &target);
        else
            func_002B5278(object, heading);
        if (object[0xBC] == 1) {
            float dist = func_0029F530(object);
            if (func_002AEB60(object, 17.0f)) {
                work[2].quad = 0;
                work[2].f[2] = 1.0f;
                func_0029FCC0(object, 4, &work[0]);
                if (*(u8 **)(state + 0x2C4))
                    func_00283098(&work[2], &work[2], *(u8 **)(state + 0x2C4) + 0xC0);
                else
                    func_00283098(&work[2], &work[2], D_0018C0B0 + 0xC0);
                func_00282CC0(&work[2], &work[2], &target);
                func_00282CF0(&work[1], &work[2], &work[0]);
                func_00282F20(&work[1], &work[1], 0.33333334f);
                func_003280C8((float)state[0x35], object, &work[1], &work[0], 0, 0);
            } else if (dist < 17.0f && object[0x43] == 17) {
                float first;
                float second;
                func_0029FCC0(object, 4, &work[0]);
                first = func_002A7878(1.0f, 1.5f) * 210000.0f;
                second = func_002A7878(0.2f, 0.4f) * 210000.0f;
                func_002C65A0(&work[0], D_L11_001A8F20, 4, 0x808080, 9, 0x4F, 0, first, second, func_002A78D8(0.0f, 0.1f), 0);
            }
            if (object[0x60] & 2) {
                if (D_0018C2BC == object || !func_002A77E0(6))
                    func_002A7750(object, 10, -1);
                else
                    func_002A7750(object, 7, -1);
            }
        }
        break;
    case 10:
        if (func_002B3868(object) && object[0x43] != 11)
            func_002A7470(object, 11, 0, 7);
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 11: {
        s32 flags = func_002B1C20(object, state + 0x50);
        if (object[0x42] == 15) {
            if (!func_002A77E0(30) || (flags & 1)) {
                if (func_0029F530(object) < 15.0f && *(s16 *)(state + 0x2D8) && !func_002A77E0(2))
                    func_002A7750(object, 12, -1);
                else {
                    func_L02_003FC248(object, 0, -1);
                    func_L11_00452DF8(object);
                }
            }
        } else if (flags & 2)
            func_002A7750(object, 7, 3);
        break;
    }
    case 12: {
        u8 *launch = state + 0x1A0;
        s32 started = func_002B3868(object);
        spin = (float *)(state + 0x2B0);
        out = &work[1];
        axis = object + 0xF0;
        scale = &work[4];
        rows = (ActorVector *)(object + 0xC0);
        if (started) {
            s32 k;
            func_00282CF0(launch, func_L11_004417E8(*(u8 **)(object + 0xB8)), pos);
            *(float *)(state + 0x1A8) = 0.0f;
            func_00282F20(launch, launch, func_002A7878(3.0f, 5.0f) * 0.016666668f);
            *(s16 *)(state + 0x2D8) = 0;
            for (k = 0; k < 3; k++) {
                spin[k] = func_002A7878(240.0f, 720.0f) * 0.00029088825f;
                qcopy(&work[k], &rows[k]);
            }
            func_002AB6D8(work, axis);
            if (object[0x43] != 18) func_002A7470(object, 18, 0, 30);
            *(u16 *)(object + 0x34) &= 0xEFFF;
        }
        *(float *)(state + 0x1A8) -= *(float *)(state + 0x12C);
        func_L07_00321D68(object, launch);
        func_00282D30(spin, spin, 0.98f);
        {
            float f = *(float *)(object + 0x2C) * 0.0009765625f;
            count = 3;
            func_002A3F10(object, 1, &count, out);
            func_00282D30(&work[0], scale, f);
        }
        func_002B4090(*(float *)(state + 0x2B0), *(float *)(state + 0x2B4), *(float *)(state + 0x2B8), object, work);
        func_002833F0(rows, axis);
        if (*(float *)(object + 0x18) < ((float *)func_L11_004417E8(*(u8 **)(object + 0xB8)))[2] + 5.0f ||
            !func_002A77E0(450) || *(u16 *)(object + 0x96) >= 301) {
            func_L02_003FC248(object, 0, -1);
            func_L11_00452DF8(object);
        }
        break;
    }
    }
    func_L11_00452810(object);
    func_L00_002E6EF8(func_L11_004528A0, object);
}
