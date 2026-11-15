#include "common.h"
#include "structs.h"

/* libgraph's sceGsGParam, as far as this reads it. */
typedef struct {
    short interlace; /* 0x00 */
    short omode;     /* 0x02 */
    short ffmode;    /* 0x04 */
    short version;   /* 0x06 */
    int unk_08;      /* 0x08 */
} GsGParam;

extern GsGParam *r1_func_00121D08(void);

extern void r1_func_00118ED0(void);

extern long r1_func_00118F60(void);

extern void r1_func_0011A6C8();

extern void r1_func_0011A6C8(void *);

extern char r1_D_001532D0[];

typedef struct {
    long q[12];
} GsLoadImage;

/* rac1-decomp src/core/001224B0.c: func_00122598 */
/* Returns the current field, bit 13 of the GS CSR (read directly at
   0x12001000, or through r1_func_00118F60), when the display is
   interlaced, and 1 otherwise. In the second arm the bit is taken from
   the call's result before the interlace test, as retail does. */
/* The libgraph interface carries a 32-bit mode argument. This retail graph011
   body ignores it; callers pass zero. Independent interface witness:
   https://github.com/open-goal/jak-project/blob/master/game/graphics/sceGraphicsInterface.h
   (sceGsSyncV(u32 mode)). Only the signature is used, with no HLE code copied. */
/* Returns which screen field is being drawn when the picture is interlaced, otherwise 1. */
int sceGsSyncV(int unused_mode) {
    GsGParam *g_param = r1_func_00121D08();
    long csr;

    if (g_param->unk_08 == 0) {
        r1_func_00118ED0();
        if (g_param->interlace != 1) {
            return 1;
        }
        return (GS_CSR >> 13) & 1;
    }
    csr = (r1_func_00118F60() >> 13) & 1;
    if (g_param->interlace != 1) {
        return 1;
    }
    return csr;
}

ASM_FUNC("asm/core", func_00126284);

/* func_0012646C is defined in 0012646C-store.c. */

/* rac1-decomp src/core/00122818.c: func_00122958 */
/* sceGsExecLoadImage(src, dst): waits for the GS transfer unit
 * (0x1000A000 bit 8) to go idle, starts an image load from src (its
 * 0x70000000 scratchpad segment tagged with bit 31) sized by the 15-bit
 * field in src->q[10], waits again and starts the transfer to dst.
 * Returns -1 after 0x1000000 polls in total. The abort is written out in
 * each loop, not shared through a goto: the compiler merges the two copies
 * into retail's single call, where a shared label needs an extra branch. */
/* Copies an image into the graphics chip with two transfers and waits for the channel each time. */
int sceGsExecLoadImage(GsLoadImage *src, void *dst) {
    unsigned int poll_count = 0;

    while (D2_CHCR & 0x100) {
        if (poll_count++ > 0x1000000) {
            r1_func_0011A6C8(r1_D_001532D0);
            return -1;
        }
    }

    D2_QWC = 6;
    if (((unsigned int)src & 0x70000000) == 0x70000000) {
        D2_MADR = ((unsigned int)src & 0x0FFFFFFF) | 0x80000000;
    } else {
        D2_MADR = (unsigned int)src & 0x0FFFFFFF;
    }
    D2_CHCR = 0x101;

    while (D2_CHCR & 0x100) {
        if (poll_count++ > 0x1000000) {
            r1_func_0011A6C8(r1_D_001532D0);
            return -1;
        }
    }

    D2_QWC = (unsigned int)(int)(src->q[10] & 0x7FFF);
    if (((unsigned int)dst & 0x70000000) == 0x70000000) {
        D2_MADR = ((unsigned int)dst & 0x0FFFFFFF) | 0x80000000;
    } else {
        D2_MADR = (unsigned int)dst & 0x0FFFFFFF;
    }
    D2_CHCR = 0x101;
    return 0;
}


extern int r1_func_00119328(int);
extern int r1_func_00118AA0(int, int);
extern int r1_func_00118A90(int, void *, int);
extern void r1_func_00119390(int);

/* rac1-decomp src/core/00123168.c: func_00123168 */
/* sceGsSyncVCallback: install (or, called with arg0 == 0, uninstall) the
   V-sync handler at offset 8/0xC of the GParam block, under
   DisableIntc/EnableIntc of INTC 2 (VBLANK start) around the
   AddIntcHandler/RemoveIntcHandler syscalls. Returns the previous
   handler. */
/* Sets or removes the handler that runs on each screen refresh and returns the old one. */
int sceGsSyncVCallback(void *handler) {
    char *g_param = (char *)r1_func_00121D08();
    int intc_line = 2;
    int prev_handler = *(int *)(g_param + 8);

    if (handler == 0) {
        r1_func_00119328(intc_line);
        r1_func_00118AA0(intc_line, *(int *)(g_param + 0xC));
        *(int *)(g_param + 0xC) = 0;
        *(int *)(g_param + 8) = 0;
    } else {
        if (prev_handler != 0) {
            r1_func_00119328(intc_line);
            r1_func_00118AA0(intc_line, *(int *)(g_param + 0xC));
        }
        *(int *)(g_param + 8) = (int)handler;
        *(int *)(g_param + 0xC) = r1_func_00118A90(intc_line, handler, -1);
        r1_func_00119390(intc_line);
    }
    return prev_handler;
}
