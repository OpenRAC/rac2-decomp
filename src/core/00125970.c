#include "common.h"
#include "structs.h"

extern int r1_func_0011BF80(void *path, int mode);

extern int r1_func_0011C5C0(int fd, void *buf, int len);

extern void r1_func_0011C208(int fd);

extern int r1_func_00112380(void *arg0);

extern char r1_D_00153130[];

/* rac1-decomp src/core/00121D18.c: func_00121D18 */
/* Read a small text file a byte at a time into a 0x100-byte stack buffer,
 * stopping at a NUL or the buffer limit, then strtol() the tail starting
 * 9 bytes before the end and compare it against a build number. Same
 * open/read/close triplet as r1_func_0012D2A0 above. */
int func_00125970(void) {
    int fd;
    char buf[0x100];
    char *p;
    unsigned int n;

    fd = r1_func_0011BF80(r1_D_00153130, 1);
    if (fd < 0) {
        return -1;
    }
    n = 0;
    p = buf;
    while (n < 0x100) {
        r1_func_0011C5C0(fd, p, 1);
        if (*p++ == 0) {
            break;
        }
        n++;
    }
    r1_func_0011C208(fd);
    return 0x1315670 < r1_func_00112380(&buf[n - 9]);
}

ASM_FUNC("asm/core", func_00125A10);

extern void r1_func_0011A6C8();
typedef struct {
    short interMode;
    short outMode;
    short ffMode;
    short version;
} GsGParam;
typedef struct {
    unsigned long pmode;
    unsigned long smode2;
    unsigned long dispfb;
    unsigned long display;
    unsigned long bgcolor;
} GsDispEnv;
extern GsGParam *r1_func_00121D08(void);
extern void r1_func_00121DB8(int, int *, int *, int *, int *);
extern char r1_D_00153140[];
extern int r1_func_00121D18(void);

/* rac1-decomp src/core/00121D18.c: func_00125A20 */
void func_00125A20(GsDispEnv *disp, short psm, short w, short h, short dx, short dy) {
    GsGParam *gp;
    int dx1, dy1, dx2, dy2;
    int mode;
    short omode;
    unsigned short imode;

    gp = r1_func_00121D08();
    if (gp->outMode != 2 && gp->outMode != 3 && r1_func_00121D18() != 0) {
        r1_func_00121DB8(gp->outMode, &dx1, &dy1, &dx2, &dy2);
    } else {
        dy2 = 0;
        dx2 = 0;
        dy1 = 0;
        dx1 = 0;
    }
    imode = gp->interMode;
    disp->pmode = 0x66;
    if (gp->interMode != 0) {
        if (gp->ffMode != 0) {
            disp->smode2 = 3;
        } else {
            disp->smode2 = 1;
        }
    } else {
        disp->smode2 = 2;
    }
    disp->dispfb = ((unsigned long)(psm & 0xF) << 15) |
                   ((unsigned long)(((w + 63) >> 6) & 0x3F) << 9);
    omode = gp->outMode;
    if (omode == 2) {
        if ((short)imode == 1) {
            int magh = (w + 2559) / w;
            unsigned long dxo = (unsigned long)dx1 + 636;
            disp->display = ((((unsigned long)(magh - 1) << 23) |
                            (((dx * magh + dxo) & 0xFFF) |
                             ((unsigned long)(gp->ffMode ? (h << 1) - 1 : h - 1) << 44))) |
                            (((unsigned long)(dy + dy1 + 50) & 0xFFF) << 12)) |
                            ((unsigned long)(magh * w - 1) << 32);
        } else {
            int magh = (w + 2559) / w;
            unsigned long dxo = (unsigned long)dx1 + 636;
            magh = (w + 2559) / w;
            disp->display = ((((unsigned long)((w + 2559) / w - 1) << 23) |
                            (((dx * ((w + 2559) / w) + dxo) & 0xFFF) |
                             ((unsigned long)(h - 1) << 44))) |
                            (((unsigned long)(dy + dy1 + 25) & 0xFFF) << 12)) |
                            ((unsigned long)((w + 2559) / w * w - 1) << 32);
        }
    } else if (omode == 3) {
        if ((short)imode == 1) {
            int magh = (w + 2559) / w;
            unsigned long dxo = (unsigned long)dx1 + 656;
            disp->display = ((((unsigned long)(magh - 1) << 23) |
                            (((dx * magh + dxo) & 0xFFF) |
                             ((unsigned long)(gp->ffMode ? (h << 1) - 1 : h - 1) << 44))) |
                            (((unsigned long)(dy + dy1 + 72) & 0xFFF) << 12)) |
                            ((unsigned long)(magh * w - 1) << 32);
        } else {
            int magh = (w + 2559) / w;
            unsigned long dxo = (unsigned long)dx1 + 656;
            magh = (w + 2559) / w;
            disp->display = ((((unsigned long)((w + 2559) / w - 1) << 23) |
                            (((dx * ((w + 2559) / w) + dxo) & 0xFFF) |
                             ((unsigned long)(h - 1) << 44))) |
                            (((unsigned long)(dy + dy1 + 36) & 0xFFF) << 12)) |
                            ((unsigned long)((w + 2559) / w * w - 1) << 32);
        }
    } else if (omode == 0x50) {
        unsigned long dxo = (unsigned long)(dx * 2) + 232;
        disp->display = ((((unsigned long)(h - 1) << 44) |
                          ((((720 - w) / 2 * 2 + (unsigned long)dx1 + dxo) & 0xFFF) | 0x800000)) |
                         (((unsigned long)(dy + dy1 + 35) & 0xFFF) << 12)) |
                        ((unsigned long)(w * 2 - 1) << 32);
    } else {
        r1_func_0011A6C8(r1_D_00153140);
    }
    disp->bgcolor = 0;
}

/* rac1-decomp src/core/00122140.c: func_00122140 */
/* Push a GS display-environment struct's quadword fields to the GS
 * privileged registers, picking the register set by the mode flag at
 * offset 6 of the GParam block (r1_func_00121D08's return). */
void func_00125D94(GsDispEnv *env) {
    GsGParam *info = r1_func_00121D08();

    if (info->version == 1) {
        GS_PMODE = env->pmode;
        GS_DISPFB1 = env->dispfb;
        GS_DISPLAY1 = env->display;
        GS_EXTDATA = env->bgcolor;
    } else {
        GS_PMODE = env->pmode;
        GS_SMODE2 = env->smode2;
        GS_DISPFB2 = env->dispfb;
        GS_DISPLAY2 = env->display;
        GS_BGCOLOR = env->bgcolor;
    }
}

