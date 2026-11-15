#include "common.h"
#include "structs.h"

extern int r1_D_00130BD0[];

extern char r1_D_00130428[];

extern int boot_test_hw_bit_field(void);

extern void r1_func_0011DBE8(int, int);

extern void r1_func_0011DBF8(int, void *, int);

extern int r1_func_0011DC40(int);

extern void r1_func_00118D80(int);

typedef struct {
    int num;
    int fn;
} SysEnt;

/* rac1-decomp src/core/0011DBE8.c: func_0011DCB8 */
/* When func_0011F8D0 says so, installs the kernel entries of the
   {num, fn} table at r1_D_00130BD0 (the third through r1_func_0011DC40) and
   copies 0x7A8 bytes of r1_D_00130428 to 0x80074000. Indexing the table in
   the loop keeps its base live, so the argument loads keep source
   order. */
/* Installs the system call entries and copies a block of start-up code into place when the hardware allows it. */
void kernel_install_entries(void) {
    SysEnt *t;
    unsigned int i;

    if (boot_test_hw_bit_field() == 0) {
        return;
    }
    t = (SysEnt *)r1_D_00130BD0;
    r1_func_0011DBE8(t[0].num, t[0].fn);
    r1_func_0011DBF8((int)0x80074000, r1_D_00130428, 0x7A8);
    r1_func_00118D80(0);
    r1_func_00118D80(2);
    r1_func_0011DBE8(t[1].num, t[1].fn);
    for (i = 2; i < 3; i++) {
        r1_func_0011DBE8(t[i].num, r1_func_0011DC40(t[i].num));
    }
}

/* rac1-decomp src/core/0011DD68.c: func_0011F9E4 */
/*
 * exit.o's kCopy: a byte copy loop returning 0. Exact under 2.9-ee, which
 * pads the short loop itself and leaves the branch's delay slot empty,
 * with `dst++` before the branch as retail has it. (Under 2.95.3 reorg
 * sinks `dst++` into the slot, 44 bytes against 48: the old revert.)
 */
/* Copies bytes from one place to another and returns zero. */
int mem_copy_bytes(char *dst, char *src, unsigned int n) {
    unsigned int i;
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
    return 0;
}
