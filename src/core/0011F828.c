#include "common.h"
#include "structs.h"

extern void boot_init_timer_records(void);

extern void kernel_init_syscall_table(void);

extern void r1_func_0011DE38(void);

extern void r1_func_001195A0(void);

extern void r1_func_0011DCB8(void);

extern void r1_func_0011D3C8(void);

/* rac1-decomp src/core/0011D960.c: func_0011DBA8 */
/* _InitSys (libkernl.a:initsys.o): the kernel's one-shot startup sequence,
   run once from the crt0 supplement. Chains six sub-system initialisers;
   the last (InitTLBFunctions, r1_func_0011D3C8) is a tail call since this is
   void and it is the final statement. */
/* Runs the start-up steps of the low-level system code, one after another. */
void kernel_init_system(void) {
    boot_init_timer_records();
    kernel_init_syscall_table();
    r1_func_0011DE38();
    r1_func_001195A0();
    r1_func_0011DCB8();
    r1_func_0011D3C8();
}
