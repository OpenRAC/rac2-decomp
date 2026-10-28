/* Historical screen superseded by src/levels/11_joba/L11_003F3258-g8.c.
 * The sketch below is not an interface reference: the current reconstruction
 * preserves the full target-query arguments/result, two FP random arguments,
 * and the pointer return of the center lookup. Reviewed qcopy plus a narrow
 * absolute-address profile produces local matches in US, US2 and PAL.
 * Both local vectors receive complete 16-byte subtraction results before use.
 */
/* func_L11_003F3258 (388 bytes, 1 place): NOT ATTEMPTED in this wave; the body is
 * recovered below and the blockers are measured.
 *
 * THE BODY
 *
 *   s32 func_L11_003F3258(u8 *arg0, u8 *arg1, u8 *arg2)
 *
 *   The prologue is
 *
 *       addiu $sp,$sp,-0x60
 *       lui $at,0x4348 ; mtc1 $at,$f12        (200.0)
 *       daddu $a3,$zero,$zero
 *       daddu $s1,$a2,$zero ; daddu $s2,$a1,$zero ; daddu $s3,$a0,$zero
 *       mov.s $f13,$f12
 *
 *   so the body takes three pointers and the literal 200.0, and it copies that
 *   literal into $f13.
 *
 *   The body is
 *
 *       s0 = *(u8 **)(arg0 + 0x68);
 *       if (func_002B3BA8(s0, *(s32 *)(s0 + 0x25C)) != 1) {
 *           *(TI128 *)arg2 = *(TI128 *)D_00189EA0;   (lq/sq, the hi part in $v1)
 *       } else {
 *           *(s32 *)(s0 + 0x258) = 1;
 *       }
 *       func_00282CF0(sp, arg2, arg1);              (a0 = sp, a1 = arg2, a2 = arg1)
 *       func_002A7878(arg1, arg2, -5.0f);           (the 5.0 is D_L11_001B0594)
 *       f20 = 20.0f + func_00282EB0(arg1, arg2);   (the 20.0 is D_L11_001B0590)
 *       if (f20 * f20 < f0) {
 *           func_002ACB48(sp);
 *           func_00282F20(sp, sp, f20);
 *           func_00282CC0(arg2, arg1, sp);
 *       }
 *       f21 = 0.5f;
 *       v0 = func_L11_004417E8(*(s32 *)(arg0 + 0xB8));
 *       func_00282CF0(sp + 0x10, arg2, v0);
 *       func_00282F20(sp + 0x10, sp + 0x10, 16.0f);  (the 16.0 is D_L11_001B0158)
 *       func_00282CC0(arg2, v0, sp + 0x10);
 *       *(f32 *)(arg2 + 0x8) = f20;
 *       return s4;                                  (1 when f20*f20 >= f0, else 0)
 *
 * THE BLOCKERS
 *
 * - The branch-likely `bc1fl` at 0x003F3318 decides the return value, and this
 *   R5900 nullifies the delay slot of a branch-likely when the branch is NOT
 *   taken: the `addiu $s4,$zero,1` in its slot runs only when the branch is
 *   taken, so the source has to be written so that the compiler keeps that
 *   assignment in the slot.
 * - The body reaches four constants through $gp (D_L11_001B0594, D_L11_001B0590,
 *   D_L11_001B0598 and D_L11_001B0158), so it needs the -G8 profile and a -g8.c
 *   source unit when it is checked.
 * - The 128-bit copy of D_00189EA0 into the second argument keeps its address in
 *   a register (`lui $v1,0x19` ; `addiu $v1,$v1,-0x6160` ; `lq $v0,0($v1)` ;
 *   `sq $v0,0($s1)`), which this cc1 only does when the copy's address is not
 *   folded into the store.
 */
