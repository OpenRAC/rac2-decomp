#include "common.h"
#include "structs.h"
#include <stdarg.h>

extern void *r1_D_0012F86C NOT_SDA;

/* rac1-decomp src/core/00116070.c: func_001160D8 */
/* newlib's rand(), as newlib writes it: one expression that reads
   _REENT (r1_D_0012F86C) twice. +0x58 is _REENT->_next, which srand
   (r1_func_001160C8 above) sets. */
int func_001163B0(void) {
    return (*(unsigned int *)((char *)r1_D_0012F86C + 0x58) =
            *(unsigned int *)((char *)r1_D_0012F86C + 0x58) * 1103515245 + 12345) & 0x7FFFFFFF;
}

/* func_00116E10 is in 00116E10.c. */

/* func_00117278 is in 00117278.c with its O0 quadword-save profile. */

INCLUDE_ASM("asm/core", func_00117650);

INCLUDE_ASM("asm/core", func_00117848);

/* func_00117CA0 is in 00117CA0.c. */

/* func_001182B8 is in 001182B8.c. */

/* func_00118460 is in 00118460.c with the game compiler profile. */

/* func_00118548 is in 00118548.c with the game compiler profile. */

/* func_001184D0 is in 001184D0.c with the game compiler profile. */

INCLUDE_ASM("asm/core", func_001185E8);

/* func_00118BC0 is in 00118BC0.c with quadword saves. */

/* func_00118D98 is in 00118D98.c with quadword saves. */

/* func_00119AC0 is in 00119AC0.c with quadword saves. */

/* func_00119BF8 is in 00119BF8.c with quadword saves. */

/* func_00118CC8 is defined in 00118CC8.c with quadword saves. */

INCLUDE_ASM("asm/core", func_0011A7F8);
