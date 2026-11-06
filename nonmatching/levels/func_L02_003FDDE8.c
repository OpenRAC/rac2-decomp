/* 6 November 2026, USA v1.01, check.py only: 964/964 compiled bytes (exact size),
 * 0/1 places match. 20 non-reloc instruction differences remain across 4 draws
 * under `-O2 -G8 -ffunction-sections -fno-rerun-loop-opt -fno-gcse`.
 * 6 November 2026 (round 10): the retained C below is NOT admissible: scaled_coord's
 * `if (result != 0 && mode == active) scaled = 1.0f;` is a dead test (blocker 26), and
 * `#define TABLE` is a second name for D_L02_001B1190 (new AGENTS.md rule). Compliant form
 * (no dead test, no TABLE alias, no field copy; draw 3 body in a one-pass do/while(0) group)
 * measures 952/964 bytes, 68 real rows. Cause: combine folds `label = v0; a0 = label` into
 * `a0 = v0` within one block, so label never lives in $a2 (retail `daddu $a2,$v0` ... `daddu
 * $a0,$a2` in all four draws). Tried without effect: call written as the draw argument,
 * inline draw_text helper taking label, do/while(0) groups around the label call, if/else vs
 * ternary colour, 110-step statement-order hill-climb. Only a block split between the label
 * call and the draw call keeps the copy; no real source construct for it is known.
 *
 * Prologue and epilogue are byte-for-byte identical to retail (frame 0x60, saving
 * $s0..$s6 and $f20..$f22). All callee-saved registers match retail assignments:
 * $s0 (object), $s1 (0x8710 / 0xE0), $s2 (state / &D_L02_00264A70), $s3 (enabled / &D_00139568),
 * $s4 (color), $s5 (&D_001395B8), $s6 (&D_00138180), $f20 (1.0f), $f21 (0.0f), $f22 (0.5f).
 *
 * Progress from previous 944-byte draft:
 * 1. The inline helper `scaled_coord` with the dead display-mode test
 *    (`if (result != 0 && mode == active) scaled = 1.0f;` with `int mode = D_L02_001B3E00;`
 *    and `int one = 1;`) splits basic blocks after the y conversion without surviving to
 *    assembly (flow2 deletes the dead test), preventing CSE from hoisting 0.5f, 1.0f, 0.0f
 *    and 0x8710 into callee-saved registers across draws 3 and 4. This brought the compiled
 *    size from 944 to exactly 964 bytes.
 * 2. In retail, `label` is allocated in `global-alloc` across all four draws to $a2, and
 *    moved to $a0 before each draw call (`daddu $a0, $a2, $zero`). In naive C, `label`
 *    takes $v1. Writing the draw 4 field through c (`field = D_00138180.buttons; c = field;
 *    c = (c & 0x2000) ? D_L02_001B128C : color;`) keeps $v1 busy across the label definition,
 *    forcing `global-alloc` to assign $a2 to `label` in all four draws.
 *
 * Tried (~340 runs + 300 hill-climb iterations):
 * - Permutations of independent statements in calls 1, 2, 3, 4.
 * - Alternative expression and condition forms for buttons and color (if/else, ternary,
 *   two-step assignment, direct pointer casts `*(int *)(D_00138180 + 0x1A0)`).
 * - Separate global declaration `extern int D_00138320 __attribute__((nosda));`.
 * - Local-alloc dump analysis: in draw 3, `local-alloc` creates qty 146 for the high address
 *   and qty 148 for the loaded buttons value. QTY_CMP_PRI gives qty 146 higher priority
 *   because its live range is only 1 insn (`qty_death - qty_birth = 1` in the denominator),
 *   allocating it first to $v1, leaving $a0 for buttons. In retail, high address is $a0
 *   and buttons is $v1 (`lui $a0, 0x14; lw $v1, -0x7CE0($a0)`).
 * - Compiler flags tested: -fno-schedule-insns (944), -fno-schedule-insns2 (940),
 *   -fno-inline (924), -fno-expensive-optimizations (27 diffs), -fforce-mem (20 diffs),
 *   -fforce-addr (972), -fno-delayed-branch (1060), -fcaller-saves (20 diffs).
 *
 * Residual (20 non-reloc diffs):
 * - Draw 1 (003FDE94/003FDE98): 1-instruction swap of `daddu $a0, $a2, $zero` and `mtc1 $zero, $f21`.
 * - Draw 2 (003FDF00): 1-instruction swap of `daddu $a0, $a2, $zero` and `lwc1 $f14, 0x2270($gp)`.
 * - Draw 3 (003FDFD4-003FDFFC): address high in $v1 and buttons in $a0 (retail: address in $a0,
 *   buttons in $v1), and `scaled_coord` int conversion uses $v0 instead of $v1.
 * - Draw 4 (003FE0F8-003FE12C): buttons loaded into $a1 due to `c = field`, whereas retail
 *   loads into $v1 (`lw $v1, 0x1A0($s6)`).
 *
 * What would unblock it:
 * A source construct for draw 3 and draw 4 that loads buttons into $v1 while keeping $v0 live
 * (delaying `daddu $a2, $v0, $zero` past the button load as in retail lines 129 and 202) and
 * maintaining the $a2 assignment for `label`.
 */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int buttons;
} HelpInput;
typedef struct {
    u8 pad[4];
    u8 available;
    u8 rest[0xdb];
} HelpEntry;

extern u8 *D_L02_001A904C;
extern float D_L02_001B3E04;
extern int D_L02_001B30C8;
extern HelpInput D_00138180;
extern u8 D_00139568[], D_001395B8[];
extern HelpEntry D_L02_00264A70[];
extern u8 *D_L02_001B1190[] SDATA(D_L02_001B1190);
#define TABLE D_L02_001B1190

extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L02_003F9B70(int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);

extern float D_L02_001B1260 __attribute__((sda));
extern int D_L02_001B1264 __attribute__((sda));
extern int D_L02_001B1268 __attribute__((sda));
extern int D_L02_001B126C __attribute__((sda));
extern int D_L02_001B1270 __attribute__((sda));
extern int D_L02_001B1274 __attribute__((sda));
extern int D_L02_001B1278 __attribute__((sda));
extern unsigned int D_L02_001B127C __attribute__((sda));
extern unsigned int D_L02_001B1280 __attribute__((sda));
extern unsigned int D_L02_001B1288 __attribute__((sda));
extern unsigned int D_L02_001B128C __attribute__((sda));

extern int D_L02_001B3E00;

static __inline__ float scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = (float)value * scale;
    float h;
    int result;
    float coord;

    h = half;
    scaled = scaled + h;
    result = (int)scaled;
    coord = (float)result;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return coord;
}

void func_L02_003FDDE8(u8 *object, int enabled)
{
    u8 *state;
    char *label;
    int phase, i, one, entry;
    unsigned int color, c, field;
    float x, fy, pulse, half, sc, z;
    HelpEntry *r;

    if (D_L02_001A904C == 0) return;
    func_L00_0037B7B0();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;
    one = 1;
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x49);
    x = (float)D_L02_001B1264;
    fy = scaled_coord(D_L02_001B1268, D_L02_001B3E04, half, one);
    sc = 1.0f;
    z = 0.0f;
    func_00300A00(label, D_L02_001B1280, x, fy, D_L02_001B1260, sc, z);
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x48);
    x = (float)D_L02_001B1264;
    fy = scaled_coord(D_L02_001B1268, D_L02_001B3E04, half, one);
    func_00300A00(label, D_L02_001B127C, x, fy, D_L02_001B1260, sc, z);
    phase = D_L02_001B30C8 % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L02_001B127C, D_L02_001B1280, pulse);
    if (enabled) {
        if (*(short *)(state + 0x118) != 0) {
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4b);
            x = (float)D_L02_001B126C;
            if (D_00138180.buttons & 0x8000) c = D_L02_001B1288; else c = color;
            fy = scaled_coord(D_L02_001B1270, D_L02_001B3E04, 0.5f, 1);
            func_00300A00(label, c, x, fy, D_L02_001B1260, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x118) + 1; i < 14; i++) {
            if (D_001395B8[func_L02_003F9B70(*(int *)(TABLE[i] + 8))] == 0) continue;
            if (i >= 12 && !func_00288D58()) continue;
            if (i == 7) {
                r = &D_L02_00264A70[D_00139568[0x1e]];
                if (r->available == 0) continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[D_00139568[0x2a]];
                if (r->available == 0) continue;
            }
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4a);
            field = D_00138180.buttons;
            c = field;
            c = (c & 0x2000) ? D_L02_001B128C : color;
            x = (float)D_L02_001B1274;
            fy = scaled_coord(D_L02_001B1278, D_L02_001B3E04, 0.5f, 1);
            func_00300A00(label, c, x, fy, D_L02_001B1260, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}
