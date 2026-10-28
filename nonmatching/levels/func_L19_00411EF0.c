/* func_L19_00411EF0 - 592 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Belongs in L19_003E9400-g8.c (needs D_L19_001B2B0C[] sda, extern
   func_2BBFD8/func_318240 decls already in that file).
   3 masked diff lines: `andi v1,v0,0xFFFF` (mine) vs `daddu v1,v0,zero`
   (retail) for `(*(u16*)(a0+0x96))++ >= 0x20`;
   and `lwc1 f0,0x2420(at)` vs retail `f1` in the state-3 compare. Tried local
   u16/u32 with n++ / n+1 (loses the copy, +/-1 insn). */

extern int D_00138324[];
extern int D_L19_001A89B4 __attribute__((sda));
extern char D_L19_00189E20[];
extern char *D_L19_001B9A90[];
extern float D_L19_001B2420[] __attribute__((sda));
extern s16 D_L19_0018A000[];
extern s32 func_321CD8(char *a0);
extern void func_323C48(s32 a0, s32 a1, s32 a2);
extern void func_31B6F8(float *a0, float f12, float f13);
extern void func_301090(s32 a0, s32 a1);
extern void func_35D0D8(s32 a0);

void func_L19_00411EF0(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 0) {
        *(u8 *)(a0 + 0x30) = 0xFF;
        func_318240(a0, 1, -1);
        *(s32 *)(s2 + 0x18) = -1;
    }
    if (*(u8 *)(a0 + 0x20) == 1) {
        if (func_321CD8(a0) != 0) {
            s32 kind = *(s32 *)(s2 + 8);
            if (kind == 0) {
                func_323C48(8, 0x27FA, 1);
            } else if (kind == 1) {
                func_323C48(8, 0x27FC, 1);
            } else {
                func_323C48(8, 0x27F9, 1);
            }
            if (D_00138324[0] & 0x10) {
                if (D_L19_001A89B4 == 8) {
                    char *st = D_L19_00189E20;
                    if (*(s16 *)(st + 0x1E0) == 0) {
                        if (*(s16 *)(D_L19_001B9A90[0] + 0x86) != 5) {
                            *(u16 *)(a0 + 0x96) = 0;
                            *(s16 *)(st + 0x1E0) = 2;
                            func_318240(a0, 2, -1);
                        }
                    }
                }
            }
        }
    }
    if (*(u8 *)(a0 + 0x20) == 2) {
        func_31B6F8(D_L19_001B2420, 1.0f, 0.033333335f);
        if ((*(u16 *)(a0 + 0x96))++ >= 0x20) {
            char *s0;
            s32 idx = *(s32 *)(s2 + 4);
            char *st = D_L19_00189E20;
            *(s32 *)(st + 0x334) = 0;
            *(s32 *)(st + 0x330) = 0;
            s0 = D_L19_001B2B0C[0] + (idx << 7);
            func_301090(*(s32 *)s2, *(s32 *)(s2 + 0x10));
            func_2BBFD8(s0 + 0x30, s0 + 0x70, 0, 1);
            D_L19_001B2420[0] = 1.0f;
            func_318240(a0, 3, -1);
        } else {
            D_L19_0018A000[0] = 2;
        }
    }
    if (*(u8 *)(a0 + 0x20) == 3) {
        func_31B6F8(D_L19_001B2420, 0.0f, 0.033333335f);
        if (D_L19_001B2420[0] <= 0.0f) {
            D_L19_001B2420[0] = 0.0f;
            func_318240(a0, 1, -1);
            if (*(s32 *)(s2 + 0x18) != -1) {
                func_35D0D8(*(s32 *)(s2 + 0x18));
                *(s32 *)(s2 + 0x18) = -1;
            }
        }
    }
}
