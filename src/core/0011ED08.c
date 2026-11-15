#include "common.h"
#include "structs.h"

extern int sceSifLoadModuleBuffer(int arg0, int arg1, int arg2, void *arg3);

/* rac1-decomp src/core/0011CCE0.c: func_0011D078 */
/* Loads an IOP module from a buffer when the caller does not need the extra result value. */
int iop_load_module_buffer_no_result(int moduleAddr, int argLen, int args) {
    char buf[0x10];
    return sceSifLoadModuleBuffer(moduleAddr, argLen, args, buf);
}
