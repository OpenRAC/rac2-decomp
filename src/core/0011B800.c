#include "common.h"
#include "structs.h"

extern int r1_D_00154600;

/*
 * InitThread: start the kernel-side service thread once. Bail with -1 if
 * the thread id r1_D_0012FCF8 is already > 0; CreateSema (r1_func_00118C70,
 * maxCount 0xFF, initCount 0) into r1_D_00154600; CreateThread
 * (r1_func_00118B50) with entry topThread (func_0011B728), stack r1_D_00154200,
 * stackSize 0x400, gpReg &_gp (r1_D_00166D00), initPriority 0, its id into
 * r1_D_0012FCF8 (DeleteSema and -1 on failure); clear r1_D_00154608[0..1],
 * StartThread(tid, r1_D_00154608), ChangeThreadPriority(GetThreadId(), 1);
 * return r1_D_0012FCF8 (re-read). Exact under 2.9-ee.
 *
 * Levers: Sony's real kernel.h structs -- ThreadParam is 12 ints with
 * `status` first (entry at +4, stack +8, stackSize +0xC, gpReg +0x10,
 * initPriority +0x14), SemaParam 6 ints -- which put the thread at sp+0
 * and the semaphore at sp+0x30 in a 0x80 frame (the old decode had a
 * 9-int struct with entry first); and the CreateSema result stored to
 * the global and the global tested, which gives retail's test of $v0
 * with the store in the bltz slot. Under 2.95.3 the CreateThread failure
 * block is laid out after the success path (48/212, same size).
 */
extern int r1_func_00118C70(void *);

extern void r1_func_00118C80(int);

extern int r1_func_00118B50(void *);

extern int r1_func_00118B70(int, void *);

extern int r1_func_00118BE0(void);

extern int r1_func_00118BA0(int, int);

extern void kernel_service_thread_run(void *);

extern int r1_D_0012FCF8;

extern char r1_D_00154200[];

extern char r1_D_00166D00[];

extern int r1_D_00154608[];

typedef struct {
    int status;
    void (*entry)(void *);
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
} ThreadParam_1195A0;

typedef struct {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
} SemaParam_1195A0;

extern int r1_D_00154A10;

/* Deci2Call (syscall 0x7C) returns the result; the file's later
   `extern void r1_func_00118E90(int, void *)` drops it, hence the alias. */
extern int r1_func_00118E90_ret(int, void *) __asm__("r1_func_00118E90");

extern void r1_func_00118E90(int arg0, void *arg1);

/* rac1-decomp src/core/00119328.c: func_001195A0 */
/* Starts the background service thread once, with its own semaphore. Returns -1 if it is already running or fails. */
int kernel_service_thread_start(void) {
    ThreadParam_1195A0 tp;
    SemaParam_1195A0 sp;
    int tid;

    if (r1_D_0012FCF8 > 0) {
        return -1;
    }
    sp.maxCount = 0xFF;
    sp.initCount = 0;
    r1_D_00154600 = r1_func_00118C70(&sp);
    if (r1_D_00154600 < 0) {
        return -1;
    }
    tp.entry = kernel_service_thread_run;
    tp.stack = r1_D_00154200;
    tp.stackSize = 0x400;
    tp.gpReg = r1_D_00166D00;
    tp.initPriority = 0;
    tid = r1_func_00118B50(&tp);
    r1_D_0012FCF8 = tid;
    if (tid < 0) {
        r1_func_00118C80(r1_D_00154600);
        return -1;
    }
    r1_D_00154608[0] = 0;
    r1_D_00154608[1] = 0;
    r1_func_00118B70(tid, r1_D_00154608);
    r1_func_00118BA0(r1_func_00118BE0(), 1);
    return r1_D_0012FCF8;
}

ASM_FUNC("asm/core", func_0011B8D8);


/* rac1-decomp src/core/00119328.c: func_00119718 */
/* libkernel sceDeci2Open(protocol, opt, handler): Deci2Call(1, {protocol,
   opt, handler, uncached &r1_D_00154A10}). Returning the call's value is
   what gives retail's schedule (tag complete before the stores, the &buf
   move ahead of the $ra save); the void spelling is 30/68. */
/* sceDeci2Open: returns Deci2Call's int result (r1_func_00118E90 is
   Deci2Call, declared void in this file, so it is reached through an
   alias). */
/* Opens a debug-network (DECI2) channel and returns its handle. */
int deci2_open_channel(unsigned short protocol, void *option, void *handler) {
    unsigned int buf[4];

    buf[0] = protocol;
    buf[1] = (unsigned int)option;
    buf[2] = (unsigned int)handler;
    buf[3] = (unsigned int)&r1_D_00154A10 | 0x20000000;
    return r1_func_00118E90_ret(1, buf);
}


/* rac1-decomp src/core/00119328.c: func_00119768 */
/* Asks the debug network to send data on a channel. */
void deci2_send_data(int sock, signed char dest) {
    int buf[4];
    buf[0] = sock;
    buf[1] = dest;
    r1_func_00118E90(0x3, buf);
}

/* rac1-decomp src/core/00119328.c: func_00119798 */
/* Polls a debug-network channel so its pending events get handled. */
void deci2_poll_channel(int sock) {
    int local = sock;
    r1_func_00118E90(0x4, &local);
}

/* rac1-decomp src/core/00119328.c: func_001197C0 */
/* Reads bytes from a debug-network channel into a buffer. */
void deci2_read_data(int sock, int buffer, unsigned short length) {
    int buf[4];
    buf[0] = sock;
    buf[1] = buffer;
    buf[2] = length;
    r1_func_00118E90(-0x5, buf);
}

/* rac1-decomp src/core/00119328.c: func_001197F8 */
/* Writes bytes to a debug-network channel from a buffer. */
void deci2_write_data(int sock, int buffer, unsigned short length) {
    int buf[4];
    buf[0] = sock;
    buf[1] = buffer;
    buf[2] = length;
    r1_func_00118E90(-0x6, buf);
}


/* rac1-decomp src/core/00119328.c: func_00119840 */
/* Closes a debug-network channel. */
void deci2_close_channel(int sock) {
    int local = sock;
    r1_func_00118E90(0x10, &local);
}

