#include "common.h"
#include "structs.h"
#include <stdarg.h>

     /* DeleteSema */
extern int r1_func_00118CB0(int);

typedef signed int s32_1B4C8;

extern s32_1B4C8 r1_func_00118CB0();

extern int r1_D_0012FD9C;

extern void iop_file_init_lock_sema(void);

extern int r1_D_0012FD9C NOT_SDA;

extern s32 r1_func_00118CB0(s32);

/* rac1-decomp src/core/00119D88.c: func_0011BC40 */
/* Takes the file system lock, creating it first if needed. */
int iop_file_lock(void) {
    iop_file_init_lock_sema();
    r1_func_00118CB0(r1_D_0012FD9C);
    return 0;
}
