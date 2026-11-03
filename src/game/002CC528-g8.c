/* func_002CC528: stores &D_001AB628 at object+0x34 when D_001A7318 is nonzero,
 * otherwise &D_001AB658, and returns 0. Retail reaches it through data pointers.
 *
 * The catalogue entry is 0x002CC530 (32 bytes): the 8 bytes at 0x002CC528 are filler
 * left after the previous body (docs/LEVELS.md). Retail addresses the two bytes via $gp
 * and the flag as an absolute `lui`/`lw` into its own destination register, which is
 * -G8 with sda/nosda declarations plus -mno-split-addresses (the assembler expands
 * `lw $3,D_001A7318` using $3 as the address temporary). Under that profile the
 * if-converted `movn` allocates exactly as retail.
 */
#include "common.h"

extern int D_001A7318 __attribute__((nosda));
extern char D_001AB658 __attribute__((sda));
extern char D_001AB628 __attribute__((sda));

int func_002CC528(void *object)
{
    void *selected = &D_001AB658;
    if (D_001A7318)
        selected = &D_001AB628;
    ((void **)object)[13] = selected;
    return 0;
}
