#include "common.h"
#include "structs.h"

extern int func_0011EB00(int arg0, int arg1, int arg2, void *arg3);

/* rac1-decomp src/core/0011CCE0.c: func_0011D078 */
/* Loads an IOP module from a buffer when the caller does not need the extra result value. */
int func_0011ED08(int moduleAddr, int argLen, int args) {
    char buf[0x10];
    return LoadModuleBuffer(moduleAddr, argLen, args, buf);
}
