#include "include_asm.h"
#include "names.h"

extern short func_002B7CE0_1(int);
extern int func_002B7B18_1(char *, int, int);

/* Calls one callee with the argument 1, then a second callee with (first, second, third argument) keeping its result, calls the first callee again with 1, and returns the kept result. */
int load_read_disc_with_pause_pal(char *dest, int sector, int sector_count)
{
    int result;

    func_002B7CE0_1(1);
    result = func_002B7B18_1(dest, sector, sector_count);
    func_002B7CE0_1(1);
    return result;
}

