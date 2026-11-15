#include "common.h"
extern int D_001A72F4 MACRO_ADDR, D_001A72D4 MACRO_ADDR, D_001A7304 MACRO_ADDR;
extern int D_001A72D0 MACRO_ADDR;
extern void func_0011AEA0(int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int func_001265B0(void *, void *);
extern int func_001244B8(int, unsigned short);
typedef struct { int type, packed, offset, size; } UploadChunk;
typedef struct { long w[12]; } UploadImage __attribute__((aligned(16)));
/* RAC1 loaders.c upload_texture_images provides the first upload loop;
 * RAC2 also uploads the following 32-bit image entries from a separate cursor. */
/* Uploads a level's texture images, then its palettes, to video memory and tracks the next free spot. */
void func_00293000(int base, int count, int palettes, UploadChunk *list)
{
    UploadImage image;
    int i, j, cursor;
    D_001A72D4 = D_001A72D0 = D_001A72F4;
    for (i = 0; i < count; i++, list++) {
        int addr = base + list->size;
        int packed = list->packed;
        int vramPos = D_001A72D0;
        int w = packed & 0xffff;
        int h = packed >> 16;
        if (list->type == 0x13) {
            int dbw = w >> 6;
            int sz;
            if (dbw < 1) dbw = 1;
            func_00126288(&image, vramPos >> 8, dbw, 0x13, 0, 0, w, h);
            sz = w*h;
            if (sz < 0x100) sz = 0x100;
            D_001A72D0 += sz;
        } else if (list->type == 2) {
            func_00126288(&image, vramPos >> 8, 1, 2, 0, 0, 16, 16);
            D_001A72D0 += 0x200;
        } else if (list->type == 0) {
            func_00126288(&image, vramPos >> 8, 1, 0, 0, 0, 16, 16);
            D_001A72D0 += 0x400;
        }
        FlushCache(0);
        ExecGsLoadImage(&image, (void *)addr);
        WaitGsPathsIdle(0,0);
    }
    D_001A72D4 = D_001A72D0;
    cursor = D_001A7304;
    for (j=0; j<palettes; j++, list++) {
        int packed = list->packed;
        int addr = base + list->offset;
        int w = packed & 0xffff;
        int h = packed >> 16;
        int dbw = w >> 6;
        if (dbw < 1) dbw = 1;
        func_00126288(&image, cursor >> 8, dbw, 0x1b, 0, 0, w, h);
        cursor += w*h*4;
        FlushCache(0);
        ExecGsLoadImage(&image,(void *)addr);
        WaitGsPathsIdle(0,0);
    }
}

