/* func_L07_00336860 - 400 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Right size (400), 7 masked diff lines, only register/order:
   - table byte: retail `lw $v1,sym($v0)` ... `lbu $a0,0($v1)` (sb $a0 in the
   7878 call slot); mine uses $v0 for both.
   - retail loads the counter D_L07_001B2534 (lui $v0; lw $v0,0x2534($v0))
   BEFORE `swc1 $f0,0xC($s1)` and stores with `lui $at; sw`; mine loads after
   the swc1 with the lui kept in $v1.
   Tried: MACRO_ADDR on the counter (needed to get lui $at on the store; on
   the tables it forces $gp, bad), temp for the float, temp for the counter
   (worse). */

/* replaces the INCLUDE_ASM marker in src/levels/07_siberius/L07_002BE770.c (default -G0; add #include "common.h" for qcopy) */
extern u8 *func_002B9030(int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern u8 *D_L07_001FEEA4;
extern u8 *D_L07_001FEF00;
extern int D_L07_001B2534 MACRO_ADDR;

/* Spawns one particle at pos with the motion record at vel; flags pick a long life and a colour bump. */
u8 *func_L07_00336860(u8 *pos, u8 *vel, int fast, int tint)
{
    u8 *p = func_002B9030(0x68);
    u8 *m;
    u8 *table;

    if (p != 0) {
        m = p + 0x20;
        *(s32 *)(m + 0x10) = func_002A7820(0x20, 0x50);
        *(s32 *)(p + 4) = 0x808080;
        p[9] = func_00283CF0(2.0f) - 0x10;
        p[1] = 0;
        p[3] = 0x48;
        if (func_002A77E0(2))
            table = D_L07_001FEEA4;
        else
            table = D_L07_001FEF00;
        p[2] = table[0];
        *(float *)(p + 0xC) = func_002A7878(0.1f, 0.24f) * 210000.0f;
        p[8] = func_002A77E0(0xFF);
        qcopy(p + 0x10, pos);
        qcopy(m, vel);
        *(u16 *)(p + 0xA) = 1 << func_002A7820(6, 10);
        if (fast) {
            *(u16 *)(p + 0xA) = 0x78;
            *(s32 *)(m + 0x14) = 1;
        }
        if (tint)
            *(s32 *)(p + 4) += *(s32 *)(m + 0x10) << 24;
        *(float *)(m + 0xC) = (float)func_002A7820(0, 0x64);
        D_L07_001B2534 = D_L07_001B2534 + 1;
    }
    return p;
}
