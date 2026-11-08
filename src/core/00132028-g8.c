/* func_00132028, 488 bytes, boot: 989snd's snd_Pump (RAC1's snd_FlushSoundCommands).
   Once the pending RPC completes it runs the return callback or the callbacks
   queued with the other command buffer; it finishes a CD read (cache flush, then
   the read callback with the reply word); sends the next batch when idle; and
   polls a stop request. Returns whether an RPC or a CD read is still in flight.

   The default split-address profile keeps retail's separate `addiu $a0,$gp,...`
   for the count table: -mno-split-addresses makes (plus reg symbol) a legal address
   and folds it into the indexed load. D_001A7080[1] is the first return word of the
   reply buffer: read as an element it stays out of the delay slot, which retail fills
   from the branch's target; a scalar at that address is moved into the slot. */
#include "common.h"

typedef void (*SndCallback)(int, long);
typedef struct {
    SndCallback fn;
    int pad4;
    long arg;
} SndCommand;

extern int D_001A7480 __attribute__((sda));                 /* current buffer */
extern void (*D_001A7490)(int) __attribute__((sda));        /* stop callback */
extern int D_001A7494 __attribute__((sda));                 /* stop requested */
extern int D_001A7498 __attribute__((sda));
extern int D_001A749C __attribute__((sda));                 /* return pending */
extern int *D_001A74A0[2] __attribute__((sda));             /* counts */
extern SndCommand *D_001A74B0[2] __attribute__((sda));      /* commands */
extern int *D_001A74B8[2] __attribute__((sda));             /* replies */
extern int D_001A74C0 __attribute__((sda));                 /* batch index */
extern int D_001A74C4 __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));                 /* CD read pending */
extern SndCallback D_001A74D0 __attribute__((sda));         /* CD read callback */
extern SndCallback D_001A74E0 __attribute__((sda));         /* return callback */
extern long D_001A74E8 __attribute__((sda));                /* its argument */
/* The CD read callback's argument. No second context is known to write it: this pump
   runs in its callers' thread (func_00132498's commit, d71286afe). The volatile is
   kept only because the unit needs it: without it, or as an incomplete sda array
   (D_001A74D8[0]), func_00132028 is 16 bytes short and matches 0 of 1 in USA v1.01,
   PAL and v2.00 (the accesses become $gp-relative and retail's beql into this block
   is lost). Measured 8 November 2026 with both set-side volatile rules, the EE tree's
   and GCC 2.95's. */
extern volatile long D_001A74D8 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
extern int D_001A7080[] MACRO_ADDR;                         /* reply buffer */

extern int func_00132220(void);
extern void func_0011AEA0(int);
extern void func_00133108(void);
extern int func_00133580(int);

int func_00132028(void)
{
    int i;
    int idx;
    SndCallback fn;
    long arg;

    if (D_001A7480 != 0 && func_00132220() != 0) {
        if (D_001A749C != 0) {
            if (D_001A74E0 != 0)
                D_001A74E0(D_001A7080[1], D_001A74E8);
            D_001A74E0 = 0;
            D_001A749C = 0;
        } else {
            idx = D_001A74C0 != 1;
            for (i = 0; i < *D_001A74A0[idx]; i++) {
                if (D_001A74B0[idx][i].fn != 0)
                    D_001A74B0[idx][i].fn(D_001A74B8[idx][i + 1], D_001A74B0[idx][i].arg);
            }
        }
    }
    if (D_001A74C8 != 0) {
        func_0011AEA0(0);
        if (D_001A7180 != -1u) {
            if (D_001A74D0 != 0) {
                arg = D_001A74D8;
                fn = D_001A74D0;
                D_001A74D0 = 0;
                D_001A74D8 = 0;
                fn(D_001A7180, arg);
            }
            D_001A7180 = 0;
            D_001A74C8 = 0;
        }
    }
    if (D_001A7480 == 0) {
        if (*D_001A74A0[D_001A74C0] != 0 && D_001A74C4 == 0)
            func_00133108();
    }
    if (D_001A7494 != 0) {
        func_00133580(1);
        if (D_001A7498 != 0) {
            D_001A7494 = 0;
            D_001A7498 = 0;
            if (D_001A7490 != 0)
                D_001A7490(1);
        }
    }
    return D_001A7480 != 0 || D_001A74C8 != 0;
}

