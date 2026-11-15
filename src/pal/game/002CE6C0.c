#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void func_0029C450(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
void SetupGifPaging(long);
void DoGifPaging(void);

/*
 * Function: func_002D2EE0
 *
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

/* External functions declared with exact aliases from task.externals */

long long func_PAL_002CE860(void)
{
    SetupGifPaging(0LL);
    func_0029C450();
    DoGifPaging();
    return 0LL;
}

