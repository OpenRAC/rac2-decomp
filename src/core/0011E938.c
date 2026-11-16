#include "common.h"
#include "structs.h"
#include <stdarg.h>

extern int r1_func_0011B2F8();

extern int r1_func_0011B4C8();

extern void *memcpy(void *, const void *, unsigned int);

extern int r1_D_0012FDB0;

extern char r1_D_00158500[];

extern char r1_D_00158300[];

extern char r1_D_00158528[];

extern int r1_func_001151B4();

extern char r1_D_0012FCEC[];

extern char r1_D_001580A8[];

extern int r1_D_0012FDA8;

extern int r1_func_0011CDE0();

struct SifLoadCmd {
    int module_addr;
    int arg_len;
};

#define SIFCMD ((struct SifLoadCmd *) r1_D_00158300)

extern int sceSifLoadModuleBuffer(int arg0, int arg1, int arg2, void *arg3);

/* rac1-decomp src/core/0011CCE0.c: func_0011CCE0 */
/* _lf_bind (libkernl.a eeloadfile.o): unless already bound (r1_D_0012FDB0
 * >= 0), bind the IOP loadfile RPC server (r1_func_0011B2F8, 0x80000006),
 * busy-waiting 0x100000 counts between tries until its server pointer
 * (+0x24) is set; a failed bind returns -1. Then mark it bound, call
 * function 0xFF (r1_func_0011B4C8) for the 4-byte reply at r1_D_00158300
 * (-0x10001 if the call fails) and copy it to r1_D_00158528.
 *
 * The success path has its own `return 0`: its $v0 = 0 is scheduled
 * ahead of the inlined memcpy, which moves the copy's registers up by
 * one as in retail. The already-bound test jumps to the shared one. */
/* Connects to the IOP file loader server once and reads its start-up reply. */
int iop_loadfile_bind_server(void) {
    int i;

    if (r1_D_0012FDB0 >= 0)
        goto done;

    for (;;) {
        char *slot = r1_D_00158500;

        if (r1_func_0011B2F8(slot, 0x80000006, 0) < 0)
            return -1;

        if (*(int *)(slot + 0x24) != 0) {
            r1_D_0012FDB0 = 0;
            if (r1_func_0011B4C8(slot, 0xFF, 0, 0, 0, r1_D_00158300, 4, 0, 0) < 0)
                return 0xFFFEFFFF;
            memcpy(r1_D_00158528, r1_D_00158300, 4);
            return 0;
        }

        for (i = 0x100000; i != -1; i--)
            ;
    }

done:
    return 0;
}
extern int iop_loadfile_buffers_equal(void);
extern char g_iop_loadfile_reference[];
extern char g_iop_loadfile_state_2[];
extern char *g_iop_loadfile_magic;
extern int memcmp(void *, void *, int);

/* Compares three small buffers to see whether they all agree. Returns 1 only if they do. */
int iop_loadfile_buffers_equal(void) {
    char *reference = g_iop_loadfile_reference;
    char *state = g_iop_loadfile_state_2;
    int result = 0;
    if (memcmp(state, reference, 4) != 0) {
        if (memcmp(state, g_iop_loadfile_magic, 4) != 0)
            result = memcmp(reference, g_iop_loadfile_magic, 4) != 0;
    }
    return result;
}


extern int g_iop_loadfile_state;
extern char g_iop_loadfile_state_2[];
extern void *memset(void *, int, int);

/* Marks the module loader as not ready and clears its saved buffer. */
int iop_loadfile_reset_state(void) {
    g_iop_loadfile_state = -1;
    memset(g_iop_loadfile_state_2, 0, 4);
    return 0;
}

/* rac1-decomp src/core/0011CCE0.c: func_0011CE70 */
/* _sceSifLoadModuleBuffer. Adapted from Lombyte (GPL-3.0) for PAL. */
/* Asks the IOP to load a module from a buffer and returns the module result. */
int sceSifLoadModuleBuffer(int module_addr, int arg_len, int args, void *out_arg) {
    int *result_out = out_arg;
    int error_code;
    int module_result;

    error_code = 0xFFFF0000;
    if (iop_loadfile_bind_server() < 0) {
        return error_code;
    }
    if (r1_func_0011CDE0() != 0) {
        return 0xFFFEFFFC;
    }
    SIFCMD->module_addr = module_addr;
    if (args != 0) {
        if (arg_len >= 0xFD) {
            memcpy(r1_D_00158300 + 0x104, (void *) args, 0xFC);
            SIFCMD->arg_len = 0xFC;
        } else {
            memcpy(r1_D_00158300 + 0x104, (void *) args, arg_len);
            SIFCMD->arg_len = arg_len;
        }
    } else {
        SIFCMD->arg_len = 0;
    }
    if (r1_func_0011B4C8(r1_D_00158500, 6, 0, r1_D_00158300, 0x200, r1_D_00158300, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    module_result = SIFCMD->module_addr;
    *result_out = SIFCMD->arg_len;
    return module_result;
}
