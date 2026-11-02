/* Retained manual C reconstruction; not linked and not matching.
 * Profile: -O2 -G8 -ffunction-sections
 * Local tools/check.py measurements: us: 908 compiled bytes, 0/1 placements, exit 1; us2: 908 compiled bytes, 0/1 placements, exit 1; pal: 908 compiled bytes, 0/1 placements, exit 1.
 * Retail extent: 924 bytes. No exact-C credit and no full build performed.
 * Residual: 908 versus 924 bytes (-16), 0x60 frame. GP coordinate/color objects are explicit; FP argument order/saved registers and selection loop scheduling differ. Joba has one special entry.
 * Reopen: Reopen with a qualified selection-table layout and measured pulse/label allocation hypothesis.
 * Arrays with unknown total extent remain incomplete. Pointer-offset views do
 * not establish the full sizes or ownership of game records.
 *
 * 2026-11-03 (USA v1.01, 11:00443940, check.py only; about 35 compiles):
 * - Callees verified against retail jal targets (func_00336D50 = 11:0048DFD0,
 *   func_00300A00 = 11:00394D98, func_L00_0037B7B0 = 11:00390018,
 *   func_00283D38 = 11:00301748, func_00288D58 = 11:00306870,
 *   func_002FC560 = 11:0038FD70, func_L11_0043E108). No semantic error found.
 * - Body below now uses the sibling func_L11_00443498 shapes: MenuRecord for
 *   D_L11_00279BA0 (retail adds base then reads +4) and an SDATA incomplete
 *   table for D_L11_001B14F8, emitted as one `la` that gas turns into retail's
 *   `addiu $v1,$gp,0x2508`. Default profile: 912 bytes.
 * - Loop: retail recomputes the table address every iteration (la/sll/addu,
 *   lw a1, jal, lw a0,8(a1)) and does not hoist 8, 0xE0 or 0x8710. loop.c
 *   pass 1 (69 insns) keeps the la (savings 1, threshold already lowered by
 *   the moved lui/addiu pairs), so no giv. -frerun-loop-opt's pass 2 (59 insns)
 *   hoists the la (initial threshold 60 or 61; each move lowers it by 3) and
 *   then strength-reduces TABLE[i]. Adding `-fno-rerun-loop-opt` to the unit
 *   (profile already used by 7 files) reproduces retail's whole loop shape and
 *   registers s1..s5 exactly: 904 bytes. Source alternatives tried without
 *   effect on the pass-2 count: if-based colour, combined condition, inline
 *   rounding helper; a while loop with three `i++` stops the reduction
 *   (biv_count 2) but hoists the la and does not cross-jump; an inline
 *   availability helper moves the draw out of the loop.
 * - Remaining -20 bytes with that profile: (1) each of the four
 *   func_00300A00 calls in retail keeps the label in a separate pseudo
 *   (`daddu a2,v0` after the text call, `daddu a0,a2` in front of/in the
 *   draw call's delay slot); here combine merges label into a0
 *   (`(set a0 v0)`) and sched1 lifts it. Not changed by a nested call,
 *   an FP-first prototype order, -fno-regmove, -fno-gcse,
 *   -fno-expensive-optimizations, -fno-cse-skip-blocks, -f(no-)force-mem,
 *   -fno-caller-saves; -fno-schedule-insns keeps the late copy but loses
 *   all retail scheduling. (2) retail's loop head carries one alignment nop
 *   (0x443BA4); expected to follow once the four copies restore the layout.
 *   (3) Entry allocation: retail object s0, 0x8710 s1 (later colour),
 *   state s2, 0.5f f22, 1.0f f20, 0.0f f21 loaded late; here object s1,
 *   0x8710 s0, 0.5f f21, 1.0f f22 loaded early.
 * - Next: find why combine keeps the label copy (something setting v0 or a
 *   block boundary between the text call and the draw call's argument
 *   moves), then recheck entry allocation.
 */
/* Draws the contextual selection help and locates the next available entry. */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int field1a0;
} InputView;
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern u8 *D_L11_001A904C;
extern float D_L11_001B3E04;
extern int D_L11_001B30C8;
extern unsigned char D_00138180[];
extern unsigned char D_00139568[], D_001395B8[];
extern unsigned char D_L11_00279BA0[];
/* The class pointer table is addressed through gp. */
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L11_0043E108(unsigned int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);
extern float D_L11_001B161C __attribute__((sda));
extern int D_L11_001B1620 __attribute__((sda));
extern int D_L11_001B1624 __attribute__((sda));
extern int D_L11_001B1628 __attribute__((sda));
extern int D_L11_001B162C __attribute__((sda));
extern int D_L11_001B1630 __attribute__((sda));
extern int D_L11_001B1634 __attribute__((sda));
extern unsigned int D_L11_001B1638 __attribute__((sda));
extern unsigned int D_L11_001B163C __attribute__((sda));
extern unsigned int D_L11_001B1644 __attribute__((sda));
extern unsigned int D_L11_001B1648 __attribute__((sda));

void func_L11_00443940(u8 *object, int enabled)
{
    u8 *state;
    int label, phase, i;
    unsigned int color;
    float pulse;
    if (D_L11_001A904C == 0) return;
    func_L00_0037B7B0();
    state = *(u8 **)(object + 0x68);
    label = func_00336D50(D_L11_001A904C + 0x8710, 0x49);
    func_00300A00((char *)label, D_L11_001B163C, (float)D_L11_001B1620,
        (float)(int)((float)D_L11_001B1624 * D_L11_001B3E04 + 0.5f), D_L11_001B161C, 1.0f, 0.0f);
    label = func_00336D50(D_L11_001A904C + 0x8710, 0x48);
    func_00300A00((char *)label, D_L11_001B1638, (float)D_L11_001B1620,
        (float)(int)((float)D_L11_001B1624 * D_L11_001B3E04 + 0.5f), D_L11_001B161C, 1.0f, 0.0f);
    phase = D_L11_001B30C8 % 50;
    if (phase >= 25) pulse = 1.0f - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L11_001B1638, D_L11_001B163C, pulse);
    if (enabled) {
        if (*(short *)(state + 0x1e8) != 0) {
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4b);
            func_00300A00((char *)label, (((InputView *)D_00138180)->field1a0 & 0x8000) ? D_L11_001B1644 : color,
                (float)D_L11_001B1628, (float)(int)((float)D_L11_001B162C * D_L11_001B3E04 + 0.5f), D_L11_001B161C, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x1e8) + 1; i < 13; i++) {
            if (!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
            if (i >= 11 && !func_00288D58()) continue;
            if (i == 8) {
                MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0);
                if (!choice->enabled) continue;
            }
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4a);
            func_00300A00((char *)label, (((InputView *)D_00138180)->field1a0 & 0x2000) ? D_L11_001B1648 : color,
                (float)D_L11_001B1630, (float)(int)((float)D_L11_001B1634 * D_L11_001B3E04 + 0.5f), D_L11_001B161C, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}
