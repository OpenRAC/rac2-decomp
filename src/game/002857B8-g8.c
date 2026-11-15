#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 D_001A7BB8;
extern void func_002FC3C0(int);
extern void func_00284000_1(void);
extern void func_00284268(int, int, int, int, int, int);

/* Calls one callee with 1 and a second with no argument, then tests an absolute global word: when it is set it calls a callee with (512, 416, 640, 448, 0, 0), otherwise (512, 416, 512, 448, 0, 0). */
void func_002857B8(void)
{
    func_002FC3C0(1);
    func_00284000_1();
    if (D_001A7BB8 != 0)
        SetupFS_AA_buffer(512, 416, 640, 448, 0, 0);
    else
        SetupFS_AA_buffer(512, 416, 512, 448, 0, 0);
}
