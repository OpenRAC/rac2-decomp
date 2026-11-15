#include "common.h"
#include "structs.h"

extern int r1_func_0011B4C8();

extern char r1_D_0015B108[];

extern int r1_D_0015B180;

 /* exit */
extern void debug_print_stub(void *, ...);

extern int dbc_set_dma_buffer(int);

extern char r1_D_00153658[];

extern char r1_D_00153678[];

extern int sceDbcCreateSocket(void *, int, int);

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern int r1_D_0015B600[];

extern char r1_D_0015B580[];

extern void r1_func_00119288(void *, void *);

/* EIntr returns the previous interrupt state; the file declares it void.
   A call that returns a value changes how the lookup after it is
   allocated. */
extern int r1_func_0011D9A8_i(void) __asm__("r1_func_0011D9A8");

extern void *memcpy(void *, const void *, unsigned int);

extern char r1_D_001536B8[];

extern int sceDbcGetDepNumber(int);

extern void r1_func_00119288(void *a, void *b);

extern char r1_D_001537A0[];

/* rac1-decomp src/core/001236F0.c: func_001247E8 */
/* Same RPC shape as func_00128250 above (9 args: $4-$11 plus one stack
   slot), but with a different command id and an error path.

   The request word goes into the buffer at +4. It has to be written
   through a local pointer, not as (&r1_D_0015B180)[1]: the latter folds to
   the symbol r1_D_0015B180+4, so the compiler builds THAT address and then
   subtracts 4 to pass the buffer. With `buf`, one lui/addiu serves both
   the store and the two pointer arguments, as retail does.

   The test is written >= 0 so the error path is the fall-through and the
   success path is the branch target, letting the result load sit in the
   bgez delay slot. */
/* Gives the controller server the shared buffer to use. */
int dbc_set_dma_buffer(int buffer_addr) {
    int *request = &r1_D_0015B180;

    request[1] = buffer_addr;
    if (r1_func_0011B4C8(r1_D_0015B108, 0x80000904, 0, request, 0x400,
                      request, 0x400, 0, 0) >= 0) {
        return r1_D_0015B180;
    } else {
        debug_print_stub(r1_D_00153658);
        return 0;
    }
}

/* rac1-decomp src/core/001236F0.c: func_00124858 */
/* sceDbcCreateSocket (libdbc): copy the caller's socket record (five
   header words, then a 16-byte name) into the RPC buffer r1_D_0015B180, set
   its port (arg1, word 10) and mode (arg2, word 11), then run the
   create-socket RPC (0x80000901) through cd_base. Prints and returns 0
   on failure, else the reply's word 9.

   The header words are copied as pointers. Their alias set then differs
   from the int port/mode stores, so the header loads need not wait for
   those stores; the scheduler then places `i = 0` ahead of them, and the
   loop registers come out in $t0-$t2 as in retail. namesrc/namedst are
   precomputed so each byte address is one base+index add, and the call
   re-takes &r1_D_0015B180 for its buffer arguments. */
/* Asks the controller server to create a socket for a controller port. Returns 0 on failure. */
int sceDbcCreateSocket(void *socket_record, int port, int mode) {
    int *request = &r1_D_0015B180;
    char *namesrc = (char *)socket_record + 0x14;
    char *namedst = (char *)request + 0x14;
    int i;

    request[10] = port;
    request[11] = mode;
    ((void **)request)[0] = ((void **)socket_record)[0];
    ((void **)request)[1] = ((void **)socket_record)[1];
    ((void **)request)[2] = ((void **)socket_record)[2];
    ((void **)request)[3] = ((void **)socket_record)[3];
    ((void **)request)[4] = ((void **)socket_record)[4];
    for (i = 0; i < 0x10; i++) {
        namedst[i] = namesrc[i];
    }
    if (r1_func_0011B4C8(r1_D_0015B108, 0x80000901, 0, &r1_D_0015B180, 0x400,
                       &r1_D_0015B180, 0x400, 0, 0) < 0) {
        debug_print_stub(r1_D_00153678);
        return 0;
    }
    return request[9];
}

/* rac1-decomp src/core/001236F0.c: func_00124920 */
/*
 * sceDbcGetDepNumber(port) (libdbc): write back the 0x80-byte DMA buffer
 * r1_D_0015B580 (r1_func_00119288), then with interrupts off (DIntr/EIntr)
 * copy its first 0x40 bytes into the link-state table r1_D_0015B600. A port
 * whose state is not 1 (linked) returns -12. Otherwise RPC 0x80000903
 * with the port as the request word; returns the reply's second word, or
 * reports the failure (func_00128898) and returns 0.
 *
 * The RPC buffer is re-taken as &r1_D_0015B180 for the call's arguments and
 * `buf` is only assigned where it is used, so the table base and the
 * buffer share retail's saved register.
 */
/* Finds out which device is plugged into a controller port. Returns a negative number if nothing is linked. */
int sceDbcGetDepNumber(int port) {
    int *request;

    r1_func_00119288(r1_D_0015B580, r1_D_0015B580 + 0x80);
    r1_func_0011D960();
    memcpy(r1_D_0015B600, r1_D_0015B580, 0x40);
    r1_func_0011D9A8_i();
    if (r1_D_0015B600[port] != 1) {
        return -0xC;
    }
    request = &r1_D_0015B180;
    request[0] = port;
    if (r1_func_0011B4C8(r1_D_0015B108, 0x80000903, 0, &r1_D_0015B180, 0x400,
                       &r1_D_0015B180, 0x400, 0, 0) < 0) {
        debug_print_stub(r1_D_001536B8);
        return 0;
    }
    return request[1];
}


/* rac1-decomp src/core/001236F0.c: func_00124A70 */
/* RPC 0x8000091A round trip on r1_D_0015B180 (the buffer is both request
   and reply), copying the reply's bytes to arg3. `r` is assigned in both
   arms of the copy guard with one return; two returns would be
   cross-jumped into one. */
/* Sends a command to the controller server and copies the reply bytes to the caller. */
int dbc_send_command(int port, int command, int *count_ptr, char *dst) {
    int *request = &r1_D_0015B180;
    unsigned char *src;
    int i;
    int result;

    request[0] = port;
    request[1] = command;
    request[2] = *count_ptr;
    if (r1_func_0011B4C8(r1_D_0015B108, 0x8000091A, 0, request, 0x400, request, 0x400, 0, 0) < 0) {
        debug_print_stub(r1_D_001537A0);
        return 0;
    }
    result = request[0x23];
    if (result >= 0) {
        *count_ptr = request[2];
        i = 0;
        if (i < request[2]) {
            src = (unsigned char *)request + 0xC;
            do {
                dst[i] = src[i];
                i++;
            } while (i < request[2]);
            result = request[0x23];
        } else {
            result = request[0x23];
        }
    }
    return result;
}
