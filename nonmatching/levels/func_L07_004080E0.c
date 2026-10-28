/* func_L07_004080E0 - 596 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   592 vs 596 bytes, 45 masked diff lines (all one-instruction shift after the
   first diff). Structure, registers, movz (ok = 0; if (r == 0) ok = 1;) all
   match.
   Only difference: retail stores the byte 0x1A7A70 as `lui $at; sb
   $s4,lo($at)` before `jal func_002E5E58`, with `daddu $a2,$zero,$zero` in
   the delay slot.
   Mine puts a gp-form `sb $s4,0($gp)` in the jal delay slot (symbol is
   MACRO_ADDR/.sdata so the slot filler thinks it is 1 insn).
   Tried: sda, nosda, MACRO_ADDR, NOT_SDA, incomplete array, [16] array
   (with/without MACRO_ADDR). The 0x1A903C store (MACRO_ADDR s32) matches. */

/* goes in L07_003F4578-g8.c (-G8; qcopy from common.h; func_00282E48 and func_002A7750 declared earlier in that file) */
extern s32 D_L07_001B1560 __attribute__((sda));
extern s32 D_L07_001B1530[2] __attribute__((sda));
extern s32 D_L07_001B1538[2] __attribute__((sda));
extern s32 D_L07_001B1540[2] __attribute__((sda));
extern f32 D_L07_001B3198 __attribute__((sda));
extern f32 D_L07_001AA698 __attribute__((sda));
extern u8 D_L07_001A7A70 MACRO_ADDR;
extern s32 D_L07_001A903C MACRO_ADDR;
extern void *func_002A9640(void *, s32, s32);
extern int func_002761F8(void *, void *, int, void *, void *);
extern s32 func_002E5CF8(s32, s32, s32);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002B0A18(int, int);
extern void func_0029F338(void *a0);
extern s32 func_00282948(void *);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void func_L07_00408338(u8 *a0);

void func_L07_004080E0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *obj;
    u8 *other;
    f32 pos[4];
    f32 target[4];
    s32 ok;

    switch (a0[0x20]) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (*(s32 *)state == 0) {
            obj = func_002A9640(a0, 0x4010000, 0);
            if (obj != 0) {
                qcopy(pos, a0 + 0x10);
                pos[2] += 0.5f;
                ok = 1;
                other = *(u8 **)(obj + 0x20);
                if (other != 0) {
                    qcopy(target, other + 0x10);
                    target[2] += 0.5f;
                    if (func_00282E48((u8 *)target, (u8 *)pos) < 64.0f) {
                        ok = 0;
                        if (func_002761F8(target, pos, 2, a0, 0) == 0)
                            ok = 1;
                    }
                }
                if (ok)
                    func_002A7750(a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_002E5CF8(0, 0, (s32)a0);
        func_L00_0032A258(a0, D_L07_001B1540, D_L07_001B1538, D_L07_001B1530, 0xFFF, -1,
                          D_L07_001B1560, 0x10, 0xFFFF, 0xFF, 0);
        func_L07_00408338(a0);
        *(s32 *)(state + 4) = 0x1E0;
        if (D_L07_001A7A70 == 0) {
            D_L07_001A7A70 = 1;
            func_002E5E58(1, 0, 0);
            func_002B0A18(0x1233, -1);
            D_L07_001A903C = 1;
        }
        if (D_L07_001B1560 >= 0)
            *(u16 *)(a0 + 0x7C) = (1 << D_L07_001B1560) | 0x8000;
        else
            *(u16 *)(a0 + 0x34) |= 0x41;
        func_002A7750(a0, 3, -1);
        break;
    case 3:
        if (func_00282948(state + 4)) {
            D_L07_001AA698 = D_L07_001B3198;
            func_0029F338(a0);
        }
        break;
    }
}
