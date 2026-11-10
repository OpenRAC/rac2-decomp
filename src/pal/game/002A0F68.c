#include "include_asm.h"

/* Original assembly: the PAL copy of func_002A05A8 (src/game/002A0430.c), the same routine with
   two mul.s by 1.2f (50 Hz) added. Like it: 26 trapping add/addi/sub/dsub, $at as a working
   register, and two cvt.w.s words in an encoding the compiler never emits. */
ASM_FUNC("asm/pal/game", func_PAL_002A0F68);
