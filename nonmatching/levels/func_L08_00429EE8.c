/* func_L08_00429EE8 - 452 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Same size is not reached (464 vs 452), ~100 diff lines: loop shape and
   constant hoisting.
   Retail: three induction regs (s3=i, s4=&scroll[i] and s5=&entry[i] as
   lui/addiu bases loaded in the prologue, s7 = i*4 added to a per-iteration
   `lui/addiu D_001B39A0`), table base fp=0x2604A0 built after the first call,
   and the 0.2f/-8.0f/8.0f constants rebuilt inside the loop.
   Mine hoists 0.2f into $f20 and builds the bases differently. Callee
   names/args are right (func_002FC560(0x47,0x51001),
   func_L08_0042A980(entry,i), func_L08_0042A0B0 x2 with 7 args,
   func_L08_00389B68(2,0x47,0x5340B,0x42,0x8000000044)). */

/* replaces the INCLUDE_ASM marker in src/levels/08_tabora/L08_00423970.c (default -G0) */
extern f32 D_L08_001B3A20[];
extern s32 D_L08_001B39A0[];
extern u8 D_L08_002604A0[];
extern void func_002FC560(u32 reg, u32 value);
extern int func_L02_002F1658(void);
extern void func_L08_0042A980(s32 a0, s32 a1);
extern void func_L08_0042A0B0(s32 a0, s32 a1, u8 *a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int func_002A7820(int, int);
extern void func_L08_00389B68(s32 a0, s32 a1, s32 a2, s32 a3, unsigned long a4);

/* Steps the three lanes: wraps each scroll offset and re-stamps the two ring segments. */
void func_L08_00429EE8(u8 *object)
{
    s32 *context = *(s32 **)(object + 0x68);
    f32 *scroll = D_L08_001B3A20;
    s32 *entry = D_L08_001B3A30;
    s32 i;
    s32 x;
    s32 y;
    u8 *inner;

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 3; i++, scroll++, entry++) {
        if (*entry == 0)
            continue;
        if (D_L08_001B39A0[i] < 2)
            continue;
        if (func_L02_002F1658()) {
            *scroll = *scroll - 0.2f;
            if (*scroll <= -8.0f)
                *scroll = *scroll + 8.0f;
        }
        inner = D_L08_002604A0 + (i * 2 + 1) * 0x140;
        func_L08_0042A980(*entry, i);
        y = context[1] + 0x3F;
        x = context[0] + 0x3F;
        func_L08_0042A0B0(y, x, D_L08_002604A0 + i * 2 * 0x140, 0x80, 0x40, i, -1);
        func_L08_0042A0B0(y, x, inner, 0x30, 0x10, i, func_002A7820(1, 0x14));
    }
    func_L08_00389B68(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
