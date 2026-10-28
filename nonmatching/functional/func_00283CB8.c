/* functional: high. Retail keeps the float to int truncation in the FPU, this spelling goes through a GPR; same value. */
/* func_00283CB8 - 16 bytes, 28 places (the boot and every level), retail at
   0x00283cb8: cvt.w.s $f0,$f12 ; cvt.s.w $f0,$f0 ; jr $ra ;
   sub.s $f0,$f12,$f0.  Retail keeps the truncated integer in the FPU;
   this cc1 moves it through a GPR (`cvt.w.s $f0,$f12 ; mfc1 $v0,$f0 ;
   nop ; mtc1 $v0,$f0 ; cvt.s.w $f0,$f0`), so the candidate is 32 bytes
   instead of 16.  Eight spellings were measured (the cast through a local,
   through an int local, as an expression, with the cast applied twice, with
   the argument used twice): all give the same GPR round trip.  The SDK
   compiler in build/compiler/sdk gives the same words.
   What would unblock it: a source whose float->int->float conversion stays
   in the FPU. */
typedef float f32;

f32 func_00283CB8(f32 a0) { f32 b = (f32)(int)a0; return a0 - b; }
