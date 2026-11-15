#include "common.h"
#include "structs.h"

extern int r1_func_00118C70(void *);

extern void r1_func_001208E4();

extern void r1_func_00118B20(int, void *, int);

extern void r1_func_00118C80(int);

extern int sceCdSyncS(int);

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern void *r1_D_00159840;

/*
 * _sceCd_cd_callback: the N-command completion callback. Latch *arg0 into
 * r1_D_00131414 and r1_D_00131418; status 0xB clears r1_D_00131414/r1_D_001313F0 and
 * returns; otherwise signal the r1_D_001313E8 semaphore (r1_func_00118CA0,
 * iSignalSema, int return) and r1_D_001313E0 too if r1_D_001313D4 and the
 * handler r1_D_00159840 are set, else clear r1_D_001313F0; finally clear
 * r1_D_00131414.
 *
 * Every global it touches is read and written as `volatile`, through
 * `__asm__` aliases (the file's plain `extern int` declarations below
 * stay as they are). That gives retail's two reloads of r1_D_00131414, the
 * bare `nop`s after both jal (the semaphore-id loads cannot go into the
 * slots) and the unfilled `b` slot; with fewer volatiles the size
 * changes. Exact under 2.9-ee only: 2.95.3's GCSE copies the %hi of
 * r1_D_00131414 into $16 (`lui $2` + `move $16,$2`) where retail loads
 * `lui $16` directly (SIZE 164/160).
 */
extern volatile int r1_D_00131414_v __asm__("r1_D_00131414");

extern volatile int r1_D_00131418_v __asm__("r1_D_00131418");

extern volatile int r1_D_001313D4_v __asm__("r1_D_001313D4");

extern volatile int r1_D_001313E0_v __asm__("r1_D_001313E0");

extern volatile int r1_D_001313E8_v __asm__("r1_D_001313E8");

extern volatile int r1_D_001313F0_v __asm__("r1_D_001313F0");

extern void *volatile r1_D_00159840_v __asm__("r1_D_00159840");

extern int r1_func_00118CA0(int);

extern int r1_D_001313E0;

extern int r1_D_001313E8;

extern int r1_D_001313F0;

extern int r1_D_001313D4;

extern int r1_D_001313EC;

/* DeleteSema returns int; declared void, the lui after each call would take
   $v0 instead of retail's $v1. */
extern int r1_func_00118C80_i(int) __asm__("r1_func_00118C80");

extern void r1_func_00118C90(int);

extern void r1_func_0011AA68(int);

extern void r1_func_0011AA38(int arg0, int arg1, int arg2);

extern int r1_D_001313E4;

extern int r1_D_001313FC;

extern void r1_func_00120C58(void);

typedef struct {
    char pad[0x24];
    void *serve;
} SifRpcClientData;

extern int r1_func_00120B28(void);

extern int r1_func_00118CC0(int);

extern int r1_func_00118BF0(int, void *);

extern void r1_func_0011AE20(int);

extern int r1_func_0011B2F8(void *, unsigned int, int);

extern void r1_func_0011A6C8();

extern int r1_D_001313DC;

extern int r1_D_001313D0;

extern int r1_D_001313F8;

extern int r1_D_00159850;

extern char r1_D_00159858[];

extern char r1_D_00152FB0[];

extern char r1_D_00152FD8[];

extern char r1_D_00132590[];

extern int cd_scmd_check_ready(int);

/* rac1-decomp src/core/001208E8.c: func_00120910 */
/* sceCdDelayThread: sleep on an alarm. Same stack-descriptor idiom as
   r1_func_0011BBF0 (a SemaParam: initCount [2] = 0, maxCount [1] = 1,
   option [5] = 0). The second argument to r1_func_00118B20 (SetAlarm) is the
   address of r1_func_001208E4's *second* instruction -- retail builds it as
   one %hi/%lo pair on `r1_func_001208E4 + 4`, so it is a code address the
   source names by symbol, not a separate label. `unsigned short arg0` is
   what puts `andi $17,$4,0xFFFF` in the prologue.

   Exact under 2.9-ee with the stores written initCount, maxCount, option
   (as r1_func_0011B710). Under 2.95.3 it was 24/104: that build front-loads
   `sd $31` where retail interleaves the descriptor stores between the
   `$16` and `$31` saves. */
/* Sleeps for a number of ticks by setting an alarm that wakes this thread, then waiting on it. */
void cd_sleep_with_alarm(unsigned short delay_ticks) {
    int sema_param[8];
    int alarm_sema;
    sema_param[2] = 0;
    sema_param[1] = 1;
    sema_param[5] = 0;
    alarm_sema = r1_func_00118C70(sema_param);
    r1_func_00118B20(delay_ticks, (char *)r1_func_001208E4 + 4, alarm_sema);
    r1_func_00118CB0(alarm_sema);
    r1_func_00118C80(alarm_sema);
}

/* rac1-decomp src/core/001208E8.c: func_00120978 */
/* Sets the CD callback handler and returns the previous one. Does nothing if the CD system is busy. */
void *sceCdCallback(void *new_handler) {
    void *old_handler;
    int intr_was_on;
    if (sceCdSyncS(1) != 0) {
        return 0;
    }
    intr_was_on = r1_func_0011D960();
    old_handler = r1_D_00159840;
    r1_D_00159840 = new_handler;
    if (intr_was_on != 0) {
        r1_func_0011D9A8();
    }
    return old_handler;
}

/* rac1-decomp src/core/001208E8.c: func_001209D8 */
/* Runs when a CD command finishes. Records the status and wakes up the thread waiting for the result. */
void cd_command_done_callback(int *cmd_status) {
    r1_D_00131414_v = *cmd_status;
    r1_D_00131418_v = r1_D_00131414_v;
    if (r1_D_00131414_v == 0xB) {
        r1_D_00131414_v = 0;
        r1_D_001313F0_v = 0;
        return;
    }
    r1_func_00118CA0(r1_D_001313E8_v);
    if (r1_D_001313D4_v != 0 && r1_D_00159840_v != 0) {
        r1_func_00118CA0(r1_D_001313E0_v);
    } else {
        r1_D_001313F0_v = 0;
    }
    r1_D_00131414_v = 0;
}

typedef struct {
    int n0;
    int n1;
    char *dst0;
    char *dst1;
    char buf0[0x40];
    char buf1[0x40];
} CdRecv;
extern void r1_func_001209D8(int *arg0);

/* rac1-decomp src/core/001208E8.c: func_001246D0 */
/* Copies the two small result buffers from the CD reply packet to their destinations, then finishes the command. */
void cd_copy_reply_buffers(int buf_addr) {
    CdRecv *recv = (CdRecv *)(buf_addr | 0x20000000);
    int i;

    if (recv->n0 > 0) {
        char *dst0 = recv->dst0;
        for (i = 0; i < recv->n0; i++) dst0[i] = recv->buf0[i];
    }
    if (recv->n1 > 0) {
        char *dst1 = recv->dst1;
        for (i = 0; i < recv->n1; i++) dst1[i] = recv->buf1[i];
    }
    r1_func_001209D8((int *)&r1_D_00131414_v);
}

extern int r1_func_00118C70(void *);
extern int r1_D_001313E0;
extern int r1_D_001313E8;
extern int r1_D_001313EC;
extern int r1_D_001313F0;
struct SemaParam_120B28 {
    s32 currentCount;
    s32 maxCount;
    s32 initCount;
    s32 numWaitThreads;
    u32 attr;
    u32 option;
};
extern volatile s32 r1_D_001313E0_120B28[] __asm__("r1_D_001313E0");
extern s32 r1_D_001313E8_120B28[] __asm__("r1_D_001313E8");
extern s32 r1_D_001313EC_120B28[] __asm__("r1_D_001313EC");
extern volatile s32 r1_D_001313F0_120B28[] __asm__("r1_D_001313F0");
extern s32 r1_func_00118C70_120B28(struct SemaParam_120B28 *) __asm__("r1_func_00118C70");


/* rac1-decomp src/core/001208E8.c: func_00124780 */
/* cmd_sem_init: unless both command semaphores already exist, create them
   (count 1, max 1) and the completion semaphore (count 0) through
   r1_func_00118C70 (CreateSema), then clear r1_D_001313F0.
   Adapted from Lombyte's project (GPL-3.0): src/sdk/library/cmd_sem_init.c, cmd_sem_init. */
/* Creates the CD command semaphores if they do not exist yet. */
void cd_create_semaphores(void) {
    struct SemaParam_120B28 sema;

    if ((r1_D_001313E8_120B28[0] != -1) && (r1_D_001313EC_120B28[0] != -1)) {
        return;
    }
    sema.option = 0;
    sema.initCount = 1;
    sema.maxCount = 1;
    /* Both results use the same record; storing the first handle inside
       the second call's argument puts the store in that jal's delay slot,
       as retail has it (the open residual of the old near-miss). */
    r1_D_001313EC_120B28[0] = r1_func_00118C70_120B28(
        (r1_D_001313E8_120B28[0] = r1_func_00118C70_120B28(&sema)) ? &sema : &sema);
    sema.initCount = 0;
    r1_D_001313E0_120B28[0] = r1_func_00118C70_120B28(&sema);
    r1_D_001313F0_120B28[0] = 0;
}

/* rac1-decomp src/core/001208E8.c: func_00120BC0 */
/*
 * cdvd_exit (libcdvd.a cdvd000.o): if the callback thread exists
 * (r1_D_001313D4, cb_thid), set the callback number (r1_D_00131414,
 * sceCdCbfunc_num) to -1 and SignalSema its semaphore (r1_D_001313E0,
 * cb_semid); DeleteSema the N-command, S-command and callback
 * semaphores; then remove SIF command handler 0x80000012 with interrupts
 * off, re-enabling them if DIntr said they were on.
 *
 * The do-while (0) around the store leaves loop notes in the block, which
 * the scheduler treats as a barrier: the store stays ahead of the
 * semaphore-id load, as in retail, and the load still fills the jal's
 * delay slot. Without it the load is hoisted above the store.
 */
/* Shuts down the CD system: wakes the callback thread, deletes the semaphores and removes the command handler. */
void cd_shutdown(void) {
    int intr_was_on;
    if (r1_D_001313D4 != 0) {
        do {
            r1_D_00131414_v = -1;
        } while (0);
        r1_func_00118C90(r1_D_001313E0);
    }
    r1_func_00118C80_i(r1_D_001313E8);
    r1_func_00118C80_i(r1_D_001313EC);
    r1_func_00118C80_i(r1_D_001313E0);
    intr_was_on = r1_func_0011D960();
    r1_func_0011AA68(0x80000012);
    if (intr_was_on != 0) {
        r1_func_0011D9A8();
    }
}


/* rac1-decomp src/core/001208E8.c: func_00120CA0 */
/* Installs the CD command handler with interrupts off and marks the CD system as ready. */
int cd_install_command_handler(void) {
    int intr_was_on;

    r1_D_001313E4 = 1;
    intr_was_on = r1_func_0011D960();
    r1_func_0011AA38(0x80000012, (int)((char *)r1_func_00120C58 + 8), 0);
    if (intr_was_on != 0) {
        r1_func_0011D9A8();
    }
    r1_D_001313E4 = 0;
    r1_D_001313FC = 1;
    return 1;
}


/* rac1-decomp src/core/001208E8.c: func_00120D28 */
/* _sceCd_scmd_prechk (libcdvd.a cdvd000.o) */
/* Checks that a CD system command can start. Takes the lock and connects to the CD server, retrying until it answers. */
int cd_scmd_check_ready(int cmd_id) {
    int spin;
    volatile int *sem = &r1_D_001313E8;

    r1_func_00120B28();
    if (*sem != r1_func_00118CC0(*sem)) {
        if (r1_D_001313D0 > 0) {
            r1_func_0011A6C8(r1_D_00152FB0, cmd_id, r1_D_001313DC);
        }
        return 0;
    }
    r1_D_001313DC = cmd_id;
    r1_func_00118BF0(r1_D_00159850, r1_D_00159858);
    if (sceCdSyncS(1) != 0) {
        r1_func_00118C90(*sem);
        return 0;
    }
    r1_func_0011AE20(0);
    if (r1_D_001313F8 >= 0) {
        return 1;
    }
    while (1) {
        if (r1_func_0011B2F8(r1_D_00132590, 0x80000595, 0) < 0) {
            if (r1_D_001313D0 > 0) {
                r1_func_0011A6C8(r1_D_00152FD8);
            }
            for (spin = 0x100000; spin != -1; spin--)
                ;
        } else {
            if (((SifRpcClientData *)r1_D_00132590)->serve != 0) {
                break;
            }
            for (spin = 0x100000; spin != -1; spin--)
                ;
        }
    }
    r1_D_001313F8 = 0;
    return 1;
}
