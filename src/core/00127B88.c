#include "common.h"
#include "structs.h"

extern void r1_func_00118C90(int);

extern int r1_func_0011B6B8(void *);

extern int r1_D_00132EAC;

extern int sceMcSync(int, int *, int *);

extern char r1_D_00159B00[];

extern char r1_D_0015B0C0[];

extern int r1_D_00132EA8;

extern void mc_delay_thread(int);

extern int *r1_D_00159B28;

extern int *r1_D_00159B2C;

extern int *r1_D_00159B30;

extern int r1_D_00159B80;

extern int r1_func_0011B4C8();

extern int r1_func_00118CC0(int);

extern char r1_D_0015A000[];

extern int r1_func_0011AD70(void *, int);

extern int r1_D_00159B80_a[] __asm__("r1_D_00159B80");

extern char r1_D_00159BB0[];

extern void *r1_func_00116B00(void *, const void *, int);

extern char r1_D_0015B108[];

extern int r1_D_0015B180;

extern void r1_func_0011A6C8();

extern int r1_func_0011AE20(int);

extern int r1_func_0011B2F8(void *, int, int);

extern char r1_D_0015B130[];

extern char r1_D_001535D8[];

extern char r1_D_001535F0[];

extern char r1_D_00153618[];

extern char r1_D_00153640[];

extern int r1_D_0015B600[];

extern char r1_D_0015B580[];

extern void r1_func_001138B8(int) __attribute__((noreturn));

 /* exit */
extern void debug_print_stub(void *, ...);

extern int dbc_set_dma_buffer(int);

/* rac1-decomp src/core/001236F0.c: func_00123F30 */
/* sceMcSync(mode, &cmd, &result): polls the pending memory card command
   (or waits for it when mode is 0) and hands back its result. Exact
   only under 2.9-ee: 2.95.3's gcse leaves two extra %hi copies. */
/* Checks whether the last memory card command has finished, and can wait for it to finish. */
int sceMcSync(int mode, int *cmd, int *result) {
    int r;

    if (r1_D_00132EA8 == 0) {
        return -1;
    }
    r = r1_func_0011B6B8(r1_D_00159B00);
    if (mode == 0 && r != 0) {
        while (r1_func_0011B6B8(r1_D_00159B00) != 0) {
            mc_delay_thread(0x3C);
        }
        r = 0;
    }
    r = (r == 0);
    if (cmd != 0) {
        *cmd = r1_D_00132EA8;
    }
    if (r != 0) {
        r1_D_00132EA8 = 0;
        if (result != 0) {
            *result = *(int *)r1_D_0015B0C0;
        }
        r1_func_00118C90(r1_D_00132EAC);
    }
    return r;
}

/* rac1-decomp src/core/001236F0.c: func_00124010 */
/* Copies the card type, free space and format state out of the reply to the caller's variables. */
void mc_copy_get_info_reply(int replyAddr) {
    char *reply = (char *)(replyAddr | 0x20000000);
    if (r1_D_00159B28 != 0) *r1_D_00159B28 = *(int *)(reply + 0x0);
    if (r1_D_00159B2C != 0) *r1_D_00159B2C = *(int *)(reply + 0x4);
    if (r1_D_00159B30 != 0) *r1_D_00159B30 = *(int *)(reply + 0x90);
}

/* rac1-decomp src/core/001236F0.c: func_00124068 */
/* sceMcGetInfo-style RPC 1 (libmc): asks for the card type, free space
   and format state (each only when its result pointer is given); the
   reply lands in r1_D_0015A000 and func_00127C68 copies it out. */
/* Asks the memory card for its type, free space and format state. */
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format) {
    int rpcResult;

    {
        char *client = r1_D_00159B00;
        if (*(int *)(client + 0x24) == 0) {
            return -100;
        }
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    r1_D_00159B80_a[1] = port;
    r1_D_00159B80_a[2] = slot;
    r1_D_00159B80_a[7] = (int)r1_D_0015A000;
    if (type != 0) {
        r1_D_00159B80_a[5] = 1;
    } else {
        r1_D_00159B80_a[5] = 0;
    }
    if (free != 0) {
        r1_D_00159B80_a[4] = 1;
    } else {
        r1_D_00159B80_a[4] = 0;
    }
    if (format != 0) {
        r1_D_00159B80_a[3] = 1;
    } else {
        r1_D_00159B80_a[3] = 0;
    }
    r1_D_00159B28 = type;
    r1_D_00159B2C = free;
    r1_D_00159B30 = format;
    r1_func_0011AD70(r1_D_0015A000, 0xC0);
    rpcResult = r1_func_0011B4C8(r1_D_00159B00, 1, 1, r1_D_00159B80_a, 0x30, r1_D_0015B0C0, 4, mc_copy_get_info_reply, r1_D_0015A000);
    if (rpcResult == 0) {
        r1_D_00132EA8 = 1;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return rpcResult;
}



/* rac1-decomp src/core/001236F0.c: func_00124410 */
/* sceMcDelete(port, slot, fname): rejects a null/empty fname (SignalSema,
   return -210), else strncpy's it into the shared sifParamFname
   descriptor's name field (r1_D_00159BB0+0x14), fills in port/slot/flags
   and force-terminates at the max length, then runs RPC 0xF (delete)
   through cd_base. Nonzero (queued) result SignalSemas and returns the
   handle; 0 records the command and returns 0 -- the same idiom as
   func_00127888/sceMcRead. */
/* Deletes a file on a memory card. */
int sceMcDelete(int port, int slot, char *fname) {
    char *client = r1_D_00159B00;
    char *request;
    int rpcResult;

    if (*(int *)(client + 0x24) == 0) {
        return -100;
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    if (fname == 0 || *fname == 0) {
        r1_func_00118C90(r1_D_00132EAC);
        return -210;
    }
    r1_func_00116B00(r1_D_00159BB0 + 0x14, fname, 0x3FF);
    request = r1_D_00159BB0;
    *(int *)(request + 0x0) = port;
    *(int *)(request + 0x4) = slot;
    request[0x413] = 0;
    *(int *)(request + 0x8) = 0;
    rpcResult = r1_func_0011B4C8(client, 0xF, 1, request, 0x414, r1_D_0015B0C0, 4, 0, 0);
    if (rpcResult == 0) {
        r1_D_00132EA8 = 0xF;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return rpcResult;
}

/* rac1-decomp src/core/001236F0.c: func_00124528 */
/* RPC 0x11, the same shape with two request words. */
/* Sends a memory card command that takes a port and a slot (probably the unformat command). */
int sceMcUnformat(int port, int slot) {
    char *client = r1_D_00159B00;
    int *request;
    int rpcResult;

    if (*(int *)(client + 0x24) == 0) {
        return -100;
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    request = &r1_D_00159B80;
    request[1] = port;
    request[2] = slot;
    rpcResult = r1_func_0011B4C8(client, 0x11, 1, request, 0x30, r1_D_0015B0C0, 4, 0, 0);
    if (rpcResult == 0) {
        r1_D_00132EA8 = 0x11;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return rpcResult;
}

/* rac1-decomp src/core/001236F0.c: func_001245F8 */
/* Asks the controller server for its version number. */
int dbc_get_server_version(void) {
    r1_func_0011B4C8(r1_D_0015B108, 0x80000963, 0, &r1_D_0015B180, 0x400,
                  &r1_D_0015B180, 0x400, 0, 0);
    return r1_D_0015B180;
}

/* rac1-decomp src/core/001236F0.c: func_00124650 */
/* Bind the two IOP servers 0x80000900 and 0x8000091B (retrying with a
   busy wait; exit(-1) if binding fails), check the server version
   (func_00128250: major 2), clear the 16-word table r1_D_0015B600 and read
   the configuration into r1_D_0015B580. Returns 1, or 0 on a version
   mismatch. */
/* Connects to the controller servers, checks their version and sets up the shared tables. */
int sceDbcInit(void) {
    int i;
    int version;

    r1_func_0011AE20(0);
    for (;;) {
        if (r1_func_0011B2F8(r1_D_0015B108, 0x80000900, 0) < 0) {
            debug_print_stub(r1_D_001535D8);
            r1_func_001138B8(-1);
        }
        if (*(int *)(r1_D_0015B108 + 0x24) != 0) {
            break;
        }
        i = 0x10000;
        while (i--) {
        }
    }
    for (;;) {
        if (r1_func_0011B2F8(r1_D_0015B130, 0x8000091B, 0) < 0) {
            debug_print_stub(r1_D_001535D8);
            r1_func_001138B8(-1);
        }
        if (*(int *)(r1_D_0015B130 + 0x24) != 0) {
            break;
        }
        i = 0x10000;
        while (i--) {
        }
    }
    version = dbc_get_server_version();
    if (version >> 8 != 2) {
        r1_func_0011A6C8(r1_D_001535F0);
        r1_func_0011A6C8(r1_D_00153618, 2, 0, version >> 8, version & 0xFF);
        return 0;
    }
    for (i = 15; i >= 0; i--) {
        r1_D_0015B600[i] = 0;
    }
    debug_print_stub(r1_D_00153640, r1_D_0015B580);
    dbc_set_dma_buffer((int)r1_D_0015B580);
    return 1;
}
