/* snd_BankLoadByLoc and snd_BankLoadFromIOP (989snd): synchronous bank loads over RPC.

   Both end by waiting for the RPC reply word, which RAC1 writes as a plain
   if/do-while. Here that spelling gets one NOP too many: retail's wait loop reads the
   word with two instructions and is padded by words, while this compiler's padding
   pass counts a macro load as one insn. So the loop reads through D_001A7180_abs, a
   split %hi/%lo pair that counts as two, and has to keep that %hi inside the loop:
   - the jump to `done` enters the loop from outside, so loop.c leaves it alone; it
     is still a real loop, whose label keeps retail's .p2align 3. Nothing is hoisted,
     so the sentinel is a local set in front of the loop;
   - -fno-gcse stops PRE hoisting the %hi instead.
   -fno-cse-follow-jumps keeps the separate read at `reread`, which reorg moves into
   the branch's delay slot, where retail reads the reply again through $gp. */
#include "common.h"

extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
/* The RPC reply word: a macro load outside delay slots, $gp inside them. */
extern unsigned int D_001A7180 MACRO_ADDR;
/* The same word for the final wait loops, read as a split %hi/%lo pair. */
extern unsigned int D_001A7180_abs __asm__("D_001A7180") NOT_SDA;
extern int D_001A71C0 MACRO_ADDR;
extern int D_001A71C4 MACRO_ADDR;
extern int D_001A7140 MACRO_ADDR;
extern char D_001A7578[];
extern char D_001A7600[];
extern char D_001A7630[];
extern char D_001A7650[];
extern char D_001A7730[];
extern char D_001A7760[];

extern void func_00115D48(const void *, ...);
extern int func_00133580(int);
extern void func_00132028(void);
extern void func_0011AEA0(int);
extern int func_0011D810(const void *);
extern int func_0011D620(const void *, int, int, int *, int, unsigned int *, int, int, int);

unsigned int func_00132318(int loc, int offset) {
    unsigned int reply;
    unsigned int busy;

    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7600);
        return 0;
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7630);
        return 0;
    }
    D_001A71C0 = loc;
    D_001A71C4 = offset;
    D_001A7180 = -1u;
    while (func_0011D810(&D_001A7140) != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7578);
        snd_Pump();
        func_0011AEA0(0);
    }
    if (func_0011D620(&D_001A7140, 3, 1, &D_001A71C0, 8, &D_001A7180, 4, 0, 0) < 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7650);
        D_001A7488 = 0x106;
        return 0;
reread:
        reply = D_001A7180;
        goto done;
    }
    if (D_001A7180 != -1u)
        goto reread;
    busy = -1u;
    for (;;) {
        func_0011AEA0(0);
        reply = D_001A7180_abs;
        if (reply != busy) {
done:
            return reply;
        }
    }
}

unsigned int func_001326D8(int arg0) {
    unsigned int reply;
    unsigned int busy;

    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0)
            return 0;
        func_00115D48(D_001A7730);
        return 0;
    }
    D_001A71C0 = arg0;
    D_001A7180 = -1u;
    while (func_0011D810(&D_001A7140) != 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7578);
        snd_Pump();
        func_0011AEA0(0);
    }
    if (func_0011D620(&D_001A7140, 0x59, 1, &D_001A71C0, 4, &D_001A7180, 4, 0,
                      0) < 0) {
        if (D_001A74F8 == 0)
            func_00115D48(D_001A7760);
        D_001A7488 = 0x106;
        return 0;
reread:
        reply = D_001A7180;
        goto done;
    }
    if (D_001A7180 != -1u)
        goto reread;
    busy = -1u;
    for (;;) {
        func_0011AEA0(0);
        reply = D_001A7180_abs;
        if (reply != busy) {
done:
            return reply;
        }
    }
}
