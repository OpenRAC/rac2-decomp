/* 8 November 2026, Claude Opus 5.5 (task v101/m3k), USA v1.01.
 * Best: 1452/1452 bytes, 0/28 places, 6 differing instructions (was 45).
 * Profile: own unit, -O2 -G64 -Wa,-G64 -ffunction-sections -g
 *   -Wa,--r5900-la-addend=sn (owner-allowed option), every D_001A9428 and
 *   D_001A93D0 access through the _gp alias (C below).
 * New this round:
 * - 32x32 mask loop now exact: fresh block-scope i, j (the function-level i
 *   conflicted with $v0/$v1/$a0 from the earlier calls, so it could not take
 *   $v1), index `j / 8 + (i << 2)`, and the two constants as locals
 *   `limit = 256.0f, center = 15.5f` (gives retail's 256-first hoist order).
 *   The i+1 copy in $a3 then appears without any extra source.
 * - Both coefficient loops become exact (register choice and loop-2 order)
 *   when the ax store uses the canonical D_001A9428 instead of the
 *   D_001A9428_gp alias. Cause: alias.c base_alias_check says "differing
 *   symbols never alias", so the alias store floats free of the bx/by/ay
 *   stores; retail keeps them in source order (bx, ax, by, ay). But the
 *   canonical form makes ax's pointer setup lui+addiu (1456 bytes). Retail's
 *   offset-0 $gp / offset lui mix fits an assembler that uses lui whenever
 *   `la` has an addend (the comment in gas tc-mips.c load_address says so;
 *   the code there does not). So this is a toolchain blocker, not a source
 *   one. Below keeps the alias (right size).
 * - Float declaration order matters for global-alloc ties (45 vs 49).
 * Still different:
 *   (1) prologue: retail lui/lw of func_00295C50's arg before v0 = -1.
 *       Load into a local: the load moves ahead of the base addiu as well.
 *       nosda scalar splits lui into another register.
 *   (2) the coefficient loops (see above).
 *   (3) func_0029D4D0 setup: sched2 priorities tie (all 34). The 0x238 store
 *       has 3 dependents like the $a0 move and a lower LUID, so it is picked
 *       first. Retail picks the a0/a1 moves first, then the store, then
 *       s2 = &D_001A95B8 before the jal. Moving the 0x240 store, a `file`
 *       local, or reusing `packed` for the name does not help (the last two
 *       add a saved register).
 * 8 November 2026 (assembler check): our gas matches EE binutils as shipped
 *   (SCE 991111 as.exe also keeps $gp for `la sym+off`). SN ps2eeas (-G64)
 *   uses lui for any nonzero addend, la and lw/sw alike. Env probe in gas
 *   load_address/M_LA_AB: la+addend -> lui, with every D_001A9428/D_001A93D0
 *   access through the _gp alias: both coefficient loops exact, 45 -> 9
 *   differing instructions (only (1) and (3) left). The canonical name does
 *   not help: ASTRA P20 makes offset-0 `la` lui (.extern comes after use).
 *   Forced on over 8906 units (all releases): la-only changes 1 matched unit
 *   (L00_003F9570-g8: retail `la D_L00_001B0A70+16` is $gp); la+lw/sw (SN
 *   rule) changes 18. Not landed.
 * 8 November 2026 (task v101/m8d, own unit with the option on its cflags
 *   line): reproduced 9 differing instructions, then closed the prologue:
 *   `int none = -1;` declared at function top and stored once at 0x238.
 *   The pseudo spans calls, so reload rematerializes the li right before the
 *   store; sched1 then keeps base addiu, `lw $4` in source order and sched2
 *   ties give retail's addiu / lui+lw / li. Local `arg` copies, a `state`
 *   base pointer, `slot` pointer, comma forms: all keep the wrong order
 *   (the arg copy raises the load's priority). Using `none` for the final
 *   loop's -1 stores too puts it in $23 (worse).
 *   Left: (3) only, 6 instructions at 0x295274..0x295288. sched1 puts the
 *   0x238 store first (reg weight -1 vs 0/+1 for the $a0/$a1 moves) and
 *   sched2 keeps it (tie, LUID). Tried: result in a local and the 0x240
 *   store first (same), 0x240 store before the call (regs change),
 *   `state` base local, `dst` copy of scratch, scratch + 0x9A800 as the
 *   argument (adds li/ori/addu). -fno-schedule-insns gives the right
 *   prologue but changes registers everywhere (not pursued).
 * 8 November 2026 (round 2, m8d): instrumented a scratch copy of haifa-sched
 *   (prints priority/weight/dependents/LUID per ready insn). sched1 t=5: the
 *   0x238 store, $a0 move and 0x240 store all p35 w0; the store wins on
 *   LUID (it is not register weight). sched2 t=5: all p34, class 3; store
 *   has 3 dependents (805 anti, the later `lw $2` and the func_0028B2B8
 *   call_value, both anti via patch 0029's kept $2 use), $a0 move 3, $a1
 *   move only 2 ($5 output, call). So $a1 can never outrank the store
 *   while both are ready at t=5; retail needs the store not ready there.
 *   Likely retail shape: the s1 base addiu scheduled after the call and
 *   pulled into the delay slot from after. Tried (all same order): slot
 *   pointer reused for 0x240 (regs change), a0/a1 locals, store inside the
 *   call's argument (comma), result local + 0x240 store after the call.
 * 8 November 2026 (round 3, m8d): retail sets s1 = s6+%lo(D_001C4FA0) in
 *   the delay slot of jal func_002EED58: a plain address, not a load and
 *   not the call result, so there is no honest way to make it depend on
 *   the call ($17 and $22 are callee-saved; sched2 hoists it at p35).
 *   Re-deriving the base after the call (`int *st = D_001C4FA0;` after the
 *   result local) gives the same code. Base-from-result or re-read forms
 *   would add a load or a dummy op (not allowed). Open: something that
 *   lowers the store's sched2 dependents to 2 or raises the moves' priority. */
#include "common.h"
extern unsigned int func_00294EC8(int);
extern int D_001C4FA0[];
extern int D_001A79F0_3[] __attribute__((sda));
typedef struct { int sector, size; } MapFile;
typedef struct {
    char pad0[0x36C];
    int base;           /* 0x36C */
    char pad370[0x14F0 - 0x370];
    MapFile files0[28]; /* 0x14F0 */
    MapFile files1[28]; /* 0x15D0 */
} MapToc;
extern char D_0014B540_1[];
typedef struct { float x0, y0, x1, y1, u0, v0, u1, v1; } UiMapEndpoints;
typedef struct { float ax, bx, ay, by; } UiMapCoefficients;
extern int D_00256028[][2];
extern UiMapEndpoints D_00255C30[];
extern UiMapCoefficients D_00255ED0[];
extern UiMapEndpoints D_001A93D0_gp[2] SDATA(D_001A93D0);
extern UiMapCoefficients D_001A9428_gp[2] SDATA(D_001A9428);
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern char *D_001BAED0 __attribute__((nosda));
extern char D_001A95A0[], D_001A95B8[];
extern unsigned char D_0018D278[];
extern void func_00295C50(int);
extern int func_002B7C80(void *, int, int);
extern int func_002EED58(void *, int, int, char *);
extern void func_0029D4D0(void *, void *);
extern void *func_0028B2B8(int, int, char *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00297730(char *, unsigned char *, int);
extern void func_00297400(u8 *, u8 *, short *);

void func_00294F10(void)
{
    int i;
    float u0, y0, v0, x1, u1, x0, y1, v1;
    char *scratch, *packed;
    int bytes;
    int none = -1;

    D_001C4FA0[4] = 1;
    { int i; for (i = 0; i < 21; i++) {
        D_001C4FA0[0x108 / 4 + i] = D_00256028[i][0];
        ((float *)D_001C4FA0)[0xB4 / 4 + i] = 0.65f;
        D_001C4FA0[0x15C / 4 + i] = D_00256028[i][1];
    } }
    D_001C4FA0[0x238 / 4] = none;
    func_00295C50(D_001A79F0_3[0]);
    { int i; for (i = 0; i < 21; i++) {
        float sx, sy;
        x0 = D_00255C30[i].x0;
        y0 = D_00255C30[i].y0;
        x1 = D_00255C30[i].x1;
        y1 = D_00255C30[i].y1;
        u0 = D_00255C30[i].u0;
        v0 = D_00255C30[i].v0;
        u1 = D_00255C30[i].u1;
        v1 = D_00255C30[i].v1;
        sx = (u0 - u1) / (x0 - x1);
        sy = (v0 - v1) / (y0 - y1);
        D_00255ED0[i].bx = sx;
        D_00255ED0[i].ax = u0 - sx * x0;
        D_00255ED0[i].by = sy;
        D_00255ED0[i].ay = v0 - sy * y0;
    } }
    { int i; for (i = 0; i < 2; i++) {
        float sx, sy;
        x0 = D_001A93D0_gp[i].x0;
        y0 = D_001A93D0_gp[i].y0;
        x1 = D_001A93D0_gp[i].x1;
        y1 = D_001A93D0_gp[i].y1;
        u0 = D_001A93D0_gp[i].u0;
        v0 = D_001A93D0_gp[i].v0;
        u1 = D_001A93D0_gp[i].u1;
        v1 = D_001A93D0_gp[i].v1;
        sx = (u0 - u1) / (x0 - x1);
        D_001A9428_gp[i].bx = sx;
        D_001A9428_gp[i].ax = u0 - sx * x0;
        sy = (v0 - v1) / (y0 - y1);
        D_001A9428_gp[i].by = sy;
        D_001A9428_gp[i].ay = v0 - sy * y0;
    } }
    if ((((MapToc *)D_0014B540_1)->files0[D_001C4FA0[0x230 / 4]].size != 0 && !D_001A7AF8[5])
        || (((MapToc *)D_0014B540_1)->files1[D_001C4FA0[0x230 / 4]].size != 0 && D_001A7AF8[5])) {
        D_001C4FA0[0x28 / 4] = 1;
        if (D_001A7AF8[5])
            bytes = ((MapToc *)D_0014B540_1)->files1[D_001C4FA0[0x230 / 4]].size << 7;
        else
            bytes = ((MapToc *)D_0014B540_1)->files0[D_001C4FA0[0x230 / 4]].size << 7;
        scratch = D_001BAED0;
        packed = scratch + 0x9A800;
        if (D_001A7AF8[5]) {
            func_002B7C80(packed, ((MapToc *)D_0014B540_1)->files1[D_001C4FA0[0x230 / 4]].sector + ((MapToc *)D_0014B540_1)->base, ((MapToc *)D_0014B540_1)->files1[D_001C4FA0[0x230 / 4]].size);
            D_001C4FA0[0x23C / 4] = 1;
        } else {
            func_002B7C80(packed, ((MapToc *)D_0014B540_1)->files0[D_001C4FA0[0x230 / 4]].sector + ((MapToc *)D_0014B540_1)->base, ((MapToc *)D_0014B540_1)->files0[D_001C4FA0[0x230 / 4]].size);
            D_001C4FA0[0x23C / 4] = 0;
        }
        D_001C4FA0[0x238 / 4] = func_002EED58(packed, bytes, 0x3C00, D_001A95A0);
        D_001C4FA0[0x240 / 4] = bytes;
        func_0029D4D0(packed, scratch);
        {
            int size = ((int *)scratch)[1] - ((int *)scratch)[0];
            D_001C4FA0[0] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2EB);
            func_00282B50((void *)D_001C4FA0[0], scratch + ((int *)scratch)[0], size);
        }
        D_001C4FA0[0] += 8;
        D_001C4FA0[1] = D_001C4FA0[0];
        {
            int size = ((int *)scratch)[2] - ((int *)scratch)[1];
            D_001C4FA0[5] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2FC);
            func_00282B50((void *)D_001C4FA0[5], scratch + ((int *)scratch)[1], size);
        }
        D_001C4FA0[2] = (int)func_0028B2B8(0x1000, 0, D_001A95B8, 0x303);
        for (i = 0; i < 8; i++) {
            D_001C4FA0[0x30 / 4 + i * 4] = -1;
            D_001C4FA0[0x34 / 4 + i * 4] = -1;
            D_001C4FA0[0x38 / 4 + i * 4] = D_001C4FA0[2] + (i << 9);
        }
        D_001C4FA0[3] = (int)func_0028B2B8(0x8000, 0, D_001A95B8, 0x30C);
        if (func_00294EC8(D_001C4FA0[0x230 / 4]))
            func_00297730((char *)D_001C4FA0[3], D_0018D278 + (D_001C4FA0[0x230 / 4] << 11), D_001C4FA0[5]);
        else
            func_00297400((u8 *)D_001C4FA0[3], (u8 *)D_001C4FA0[0], (short *)D_001C4FA0[1]);
        {
            int i, j;
            float limit = 256.0f, center = 15.5f;
            for (i = 0; i < 32; i++) {
                float dy = center - (float)i;
                float dy2 = dy * dy;
                for (j = 0; j < 32; j++) {
                    float dx = center - (float)j;
                    if (dx * dx + dy2 > limit)
                        ((u8 *)D_001C4FA0 + 0x1B0)[j / 8 + (i << 2)] |= 1 << (j % 8);
                }
            }
        }
    } else {
        D_001C4FA0[0] = 0;
        D_001C4FA0[2] = 0;
        D_001C4FA0[3] = 0;
        D_001C4FA0[1] = 0;
        D_001C4FA0[0x28 / 4] = 0;
    }
}
