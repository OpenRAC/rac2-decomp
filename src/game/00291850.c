#include "common.h"

/* Adapted from RAC1 src/game/loaders.c: upload_mip_texture (GPL-3.0).
 * Upload the palette and mip levels, then construct TEX0, TEX1 and MIPTBP1.
 * The per-file block-order option preserves the palette switch layout. */
extern int func_00282A18(int);
typedef struct { long w[12]; } GsLoadImage __attribute__((aligned(16)));
extern int func_00126288(GsLoadImage *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage *, void *);
extern int func_001244B8(int, unsigned short);
extern int D_001A72D0 __attribute__((sda));
extern void func_00282A60(unsigned int *, unsigned int, int);
typedef struct {
    u8 pad0[8];
    s32 width;
    s32 height;
    s32 psm;
    s32 palette_psm;
    s32 pad18;
    s32 mip_count;
    u8 data[4];
} MipTexture;

typedef struct {
    s32 palette_address;
    s32 mip_addresses[4];
    s32 palette_size;
    s32 mip_sizes[4];
    s32 palette_block;
    s32 blocks[4];
    s32 buffer_widths[4];
    s32 width_log2;
    s32 height_log2;
} MipUpload;

s32 func_00291850(MipTexture *tex, unsigned long *regs)
{
    MipUpload upload;
    GsLoadImage load_image;
    s32 i;
    s32 bytes;
    unsigned long tex0;
    unsigned long mip;
    unsigned long pal;
    unsigned long lod;

    func_00282A60((unsigned int *)&upload, 0, sizeof(upload));
    switch (tex->psm) {
    case 0:
    case 2:
        upload.palette_address = 0;
        upload.palette_size = 0;
        break;
    case 0x13:
    case 0x14:
        upload.palette_address = (s32)tex->data;
        if (tex->psm == 0x14) {
            if (tex->palette_psm == 0) {
                upload.palette_size = 0x40;
            } else {
                upload.palette_size = 0x20;
            }
        } else {
            if (tex->palette_psm == 0) {
                upload.palette_size = 0x400;
            } else {
                upload.palette_size = 0x200;
            }
        }
        break;
    default:
        break;
    }
    upload.width_log2 = log2dim(tex->width);
    upload.height_log2 = log2dim(tex->height);
    upload.mip_addresses[0] = (s32)tex->data + upload.palette_size;
    switch (tex->psm) {
    case 0:
        upload.mip_sizes[0] = tex->width * tex->height * 4;
        break;
    case 2:
        upload.mip_sizes[0] = tex->width * tex->height * 2;
        break;
    case 0x13:
        upload.mip_sizes[0] = tex->width * tex->height;
        break;
    case 0x14:
        upload.mip_sizes[0] = (tex->width * tex->height) >> 1;
        break;
    }
    if (tex->psm == 0x13 || tex->psm == 0x14) {
        upload.palette_block = D_001A72D0 >> 8;
        if (tex->psm == 0x14) {
            D_001A72D0 += 0x100;
            func_00126288(&load_image, upload.palette_block, 1, tex->palette_psm, 0, 0, 8, 2);
        } else {
            D_001A72D0 += upload.palette_size;
            func_00126288(&load_image, upload.palette_block, 1, tex->palette_psm, 0, 0, 16, 16);
        }
        func_0011AEA0(0);
        func_001265B0(&load_image, (void *)upload.palette_address);
        func_001244B8(0, 0);
    }
    for (i = 1; i < tex->mip_count; i++) {
        upload.mip_sizes[i] = upload.mip_sizes[i - 1] >> 2;
        upload.mip_addresses[i] = upload.mip_addresses[i - 1] + upload.mip_sizes[i - 1];
    }
    for (i = 0; i < tex->mip_count; i++) {
        int *width = &upload.buffer_widths[i];
        *width = tex->width >> (i + 6);
        if (*width <= 0) {
            *width = 1;
        }
        upload.blocks[i] = D_001A72D0 >> 8;
        func_00126288(&load_image, upload.blocks[i], *width, tex->psm, 0, 0,
                      tex->width >> i, tex->height >> i);
        func_0011AEA0(0);
        func_001265B0(&load_image, (void *)upload.mip_addresses[i]);
        func_001244B8(0, 0);
        bytes = upload.mip_sizes[0] >> (i * 2);
        if (bytes <= 0xFF) {
            bytes = 0x100;
        }
        D_001A72D0 += bytes;
    }
    tex0 = (unsigned long)upload.blocks[0];
    tex0 |= (unsigned long)upload.buffer_widths[0] << 14;
    tex0 |= (unsigned long)tex->psm << 20;
    tex0 |= (unsigned long)upload.width_log2 << 26;
    tex0 |= (unsigned long)upload.height_log2 << 30;
    pal = (unsigned long)upload.palette_block << 37;
    pal |= (unsigned long)1 << 34;
    tex0 |= pal;
    tex0 |= (unsigned long)tex->palette_psm << 51;
    tex0 |= (unsigned long)1 << 63;
    regs[0] = tex0;
    mip = (unsigned long)upload.blocks[1];
    mip |= (unsigned long)upload.buffer_widths[1] << 14;
    mip |= (unsigned long)upload.blocks[2] << 20;
    mip |= (unsigned long)upload.buffer_widths[2] << 34;
    lod = (unsigned long)(tex->mip_count - 1) << 2;
    mip |= (unsigned long)upload.blocks[3] << 40;
    mip |= (unsigned long)upload.buffer_widths[3] << 54;
    regs[1] = lod | 0xFFA0000000E0ULL;
    regs[2] = mip;
    return -1;
}

