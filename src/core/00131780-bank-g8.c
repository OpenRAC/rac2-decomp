#include "common.h"

extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74D0 __attribute__((sda));
extern int D_001A71C0 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
/* The CD read callback (D_001A74D0) and its argument (D_001A74D8) form one SndCommand
   record (00132028-g8.c): a word callback, 4 bytes of padding and a doubleword
   argument, as the return callback and its argument at 0x001A74E0/E8 do. This
   doubleword view of the record stores the argument as its second element, an sda
   symbol+offset access, which docs/COMPILER-NOTES.md ("reorg: which global loads may
   fill a slot") shows never fills a delay slot: the store stays where retail has it. */
extern long D_001A74D0_1[] __attribute__((sda));
extern int D_001A7140 MACRO_ADDR;
extern char D_001A7578[];
extern void func_00115D48(const void *, ...);
extern void func_00132028(void);
extern void func_0011AEA0(int);
extern int func_0011D810(const void *);
extern int func_0011D620(const void *, int, int, int *, int, unsigned int *, int, int, int);
extern int D_001A71C4 MACRO_ADDR;
extern char D_001A7600[], D_001A7630[];
extern int func_00133580(int);
void func_00132498(int bank, int offset, int callback, long callback_data) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) return;
        func_00115D48(D_001A7600);
        return;
    }
    if (func_00133580(1) == 1) {
        if (D_001A74F8 != 0) return;
        func_00115D48(D_001A7630);
        return;
    }
    D_001A71C0 = bank;
    D_001A71C4 = offset;
    D_001A7180 = -1u;
    D_001A74D0 = callback;
    D_001A74D0_1[1] = callback_data;
    while (func_0011D810(&D_001A7140)) {
        if (D_001A74F8 == 0) func_00115D48(D_001A7578);
        func_00132028();
        func_0011AEA0(0);
    }
    D_001A74C8 = 1;
    func_0011D620(&D_001A7140, 3, 1, &D_001A71C0, 8, &D_001A7180, 4, 0, 0);
}
