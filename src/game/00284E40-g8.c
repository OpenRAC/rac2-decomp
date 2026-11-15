#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern u8 *D_001A742C;
typedef struct { u8 before[0x158]; short a,b,c; u8 gap[10]; short d,e; } DisplayState;
extern DisplayState D_001A6480;
extern void func_00125A20(u8 *,short,short,short,short,short);

/* Passes the stored display parameters to func_00125A20. */
void func_00284E40(void) {
    func_00125A20(D_001A742C,D_001A6480.c,D_001A6480.a,D_001A6480.b,D_001A6480.d,D_001A6480.e);
}
