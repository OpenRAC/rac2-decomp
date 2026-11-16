#include "names.h"
/* func_00284268: sets up the anti-aliased frame-buffer state D_001A6480 and writes its seven
 * strip and sprite packet loops (adapted from RAC1 framebuf.c, SetupFS_AA_buffer). A unit of its
 * own for -fno-rerun-loop-opt and -frac2-no-extra-increment-givs (config/cflags.txt): every loop
 * advances its cursor several times per iteration and retail keeps each increment, as GCC 2.95's
 * strength reduction does, where this tree's default turns all but the last into givs
 * (docs/build/compiler-notes.md). The two D_001A6860 loops index q[n] with n++ after each store, so
 * the cursor is a reduced giv of n whose init comes last in the pre-header; the other five use
 * *p++. */
typedef unsigned int u128_FAB40 __attribute__((mode(TI)));

typedef struct {
    unsigned long NLOOP:15;
    unsigned long EOP:1;
    unsigned long pad16:16;
    unsigned long id:14;
    unsigned long PRE:1;
    unsigned long PRIM:11;
    unsigned long FLG:2;
    unsigned long NREG:4;
    unsigned long REGS0:4;
    unsigned long REGS1:4;
    unsigned long REGS2:4;
    unsigned long REGS3:4;
    unsigned long REGS4:4;
    unsigned long REGS5:4;
    unsigned long REGS6:4;
    unsigned long REGS7:4;
    unsigned long REGS8:4;
    unsigned long REGS9:4;
    unsigned long REGS10:4;
    unsigned long REGS11:4;
    unsigned long REGS12:4;
    unsigned long REGS13:4;
    unsigned long REGS14:4;
    unsigned long REGS15:4;
} GifTag_FAB40;

typedef struct {
    unsigned long FBP:9;
    unsigned long rest:55;
} GsFbp_FAB40;

typedef struct {
    unsigned long pmode;
    unsigned long smode2;
    GsFbp_FAB40 dispfb;
    unsigned long display;
    unsigned long bgcolor;
    unsigned long pad028;
    GifTag_FAB40 giftag0;       /* 0x030 */
    GsFbp_FAB40 frame0;         /* 0x040 */
    unsigned long draw0[15];
    GifTag_FAB40 giftag1;       /* 0x0C0 */
    GsFbp_FAB40 frame1;         /* 0x0D0 */
    unsigned long draw1[15];
    short display_width;        /* 0x150 */
    short display_height;
    short psm;
    short fbp0;
    short storage_width;        /* 0x158 */
    short storage_height;
    short storage_psm;
    short fbp1;
    short target_width;         /* 0x160 */
    short target_height;
    short target_psm;
    short target_fbp;
    short display_offset_x;     /* 0x168 */
    short display_offset_y;
    short zpsm;
    short zbp;
    int reserved170;            /* 0x170 */
} FsAa_FAB40;

#define MACRO_ADDR __attribute__((section(".sdata")))
extern FsAa_FAB40 g_screen_adjust_offsets;
extern FsAa_FAB40 *g_fs_aa_buffer_table MACRO_ADDR;
extern int g_vram_fb_offset MACRO_ADDR, g_vram_display_address MACRO_ADDR, g_vram_zbuffer_address MACRO_ADDR;
extern int g_widescreen_flag MACRO_ADDR;
extern int g_display_x[] __attribute__((sda)), g_display_y[] __attribute__((sda));
extern int g_display_mag_h[] __attribute__((sda)), g_display_mag_v[] __attribute__((sda));
extern int g_display_width[] __attribute__((sda)), g_display_height[] __attribute__((sda));
extern int g_prev_display_x[] __attribute__((sda)), g_prev_display_y[] __attribute__((sda));
extern int g_prev_display_mag_h[] __attribute__((sda)), g_prev_display_mag_v[] __attribute__((sda));
extern int g_prev_display_width[] __attribute__((sda)), g_prev_display_height[] __attribute__((sda));
extern char g_dma_strip_packet_second[], g_dma_strip_packet_first[], g_dma_packet_source[], g_dma_packet_copy[];
extern char g_gfx_clear_packet_a[], g_gfx_clear_packet_b[], g_gfx_clear_packet_c[], g_gfx_clear_packet_d[], g_gfx_shadow_packet[];
extern void sceGsSetDefDispEnv(void *, short, short, short, short, short);
extern int sceGsSetDefDrawEnv(void *, short, short, short, short, short);
extern void BuildAspectBlitStrips(int, int);
extern void FlushCache(int);
extern void mem_copy_aligned(void *, void *, int);

static inline void store(unsigned long *d, unsigned long v) {
    *d = v;
}

/* Sets up the anti-aliased screen mode. It fills in the screen description and builds the packets that blit the picture to the screen in 16 vertical strips. */
void SetupFS_AA_buffer(int display_width, int display_height, int storage_width, int storage_height,
                   int display_offset_x, int display_offset_y) {
    unsigned long *q;
    unsigned long *out;

    g_fs_aa_buffer_table = &g_screen_adjust_offsets;
    g_screen_adjust_offsets.display_width = display_width;
    g_screen_adjust_offsets.display_height = display_height;
    g_screen_adjust_offsets.reserved170 = 0;
    g_screen_adjust_offsets.storage_width = storage_width;
    g_screen_adjust_offsets.storage_height = storage_height;
    g_screen_adjust_offsets.display_offset_x = display_offset_x;
    g_screen_adjust_offsets.display_offset_y = display_offset_y;
    g_screen_adjust_offsets.storage_psm = 1;
    g_screen_adjust_offsets.psm = 0;
    g_screen_adjust_offsets.target_psm = 0;
    g_screen_adjust_offsets.zpsm = 0x31;
    g_screen_adjust_offsets.fbp1 = g_vram_fb_offset >> 13;
    g_screen_adjust_offsets.fbp0 = g_vram_display_address >> 13;
    g_screen_adjust_offsets.zbp = g_vram_zbuffer_address >> 13;
    sceGsSetDefDispEnv(&g_screen_adjust_offsets, 1, storage_width, storage_height, display_offset_x,
                  display_offset_y);
    g_fs_aa_buffer_table->dispfb.FBP = g_screen_adjust_offsets.fbp1;
    if (g_widescreen_flag) g_fs_aa_buffer_table->display = 0x1BF4FF00834140UL;
    {
        int dx, dy, magh, magv, dw, dh;
        g_display_x[0] = dx = g_fs_aa_buffer_table->display & 0xFFF;
        g_display_y[0] = dy = (g_fs_aa_buffer_table->display >> 12) & 0x7FF;
        g_display_mag_h[0] = magh = (g_fs_aa_buffer_table->display >> 23) & 0xF;
        g_display_mag_v[0] = magv = (g_fs_aa_buffer_table->display >> 27) & 3;
        g_display_width[0] = dw = (g_fs_aa_buffer_table->display >> 32) & 0xFFF;
        dh = (g_fs_aa_buffer_table->display >> 44) & 0x7FF;
        g_prev_display_x[0] = dx;
        g_prev_display_y[0] = dy;
        g_prev_display_mag_h[0] = magh;
        g_prev_display_mag_v[0] = magv;
        g_prev_display_width[0] = dw;
        g_display_height[0] = dh;
        g_prev_display_height[0] = dh;
    }
    sceGsSetDefDrawEnv(&g_fs_aa_buffer_table->frame0, g_screen_adjust_offsets.psm, g_screen_adjust_offsets.display_width,
                  g_screen_adjust_offsets.display_height, 3, g_screen_adjust_offsets.zpsm);
    g_fs_aa_buffer_table->frame0.FBP = g_screen_adjust_offsets.fbp0;
    *(long *)&g_fs_aa_buffer_table->draw0[1] =
        (long)g_screen_adjust_offsets.zbp | ((unsigned long)(g_screen_adjust_offsets.zpsm & 0xF) << 24);
    *(u128_FAB40 *)&g_fs_aa_buffer_table->giftag0 = 0;
    g_fs_aa_buffer_table->giftag0.NLOOP = 8;
    g_fs_aa_buffer_table->giftag0.EOP = 1;
    g_fs_aa_buffer_table->giftag0.NREG = 1;
    g_fs_aa_buffer_table->giftag0.REGS0 = 0xE;
    sceGsSetDefDrawEnv(&g_fs_aa_buffer_table->frame1, g_screen_adjust_offsets.storage_psm, g_screen_adjust_offsets.storage_width,
                  g_screen_adjust_offsets.storage_height, 0, 0);
    g_fs_aa_buffer_table->frame1.FBP = g_screen_adjust_offsets.fbp1;
    *(long *)&g_fs_aa_buffer_table->draw1[1] = 1UL << 32;
    *(u128_FAB40 *)&g_fs_aa_buffer_table->giftag1 = 0;
    g_fs_aa_buffer_table->giftag1.NLOOP = 8;
    g_fs_aa_buffer_table->giftag1.EOP = 1;
    g_fs_aa_buffer_table->giftag1.NREG = 1;
    g_fs_aa_buffer_table->giftag1.REGS0 = 0xE;

    q = (unsigned long *)g_dma_strip_packet_second;
    out = q;
    *out++ = 0x408B400000000001UL;
    *out++ = 0xEEEE;
    *out++ = 0x30000;
    *out++ = 0x47;
    *out++ = 5;
    *out++ = 8;
    *out++ = 0x100000261UL;
    *out++ = 0x14;
    *out++ = (((long)g_fs_aa_buffer_table->fbp0 << 5) |
              ((long)((g_fs_aa_buffer_table->display_width >> 6) & 0x3F) << 14) |
              ((long)g_fs_aa_buffer_table->psm << 20)) | 0xEA8000000UL;
    *out++ = 6;
    *out++ = 0x4400000000008010UL;
    *out = 0x5353;
    if (g_widescreen_flag) {
        int n;
        int i;
        for (i = 0, n = 12; i < 16; i++) {
            store(&q[n], i * g_fs_aa_buffer_table->display_width);
            n++;
            store(&q[n], (i * 0x280 + (0x8000 - g_fs_aa_buffer_table->storage_width * 8)) |
                   ((long)(0x7FF8 - g_fs_aa_buffer_table->storage_height * 8) << 16));
            n++;
            store(&q[n], (i + 1) * g_fs_aa_buffer_table->display_width |
                   ((long)g_fs_aa_buffer_table->display_height << 20));
            n++;
            store(&q[n], ((i + 1) * 0x280 + (0x8000 - g_fs_aa_buffer_table->storage_width * 8)) |
                   ((long)(g_fs_aa_buffer_table->storage_height * 8 + 0x7FF8) << 16));
            n++;
        }
    } else {
        int n;
        int i;
        for (i = 0, n = 12; i < 16; i++) {
            store(&q[n], i * g_fs_aa_buffer_table->display_width);
            n++;
            store(&q[n], (i * g_fs_aa_buffer_table->storage_width +
                          (0x8000 - g_fs_aa_buffer_table->storage_width * 8)) |
                   ((long)(0x7FF8 - g_fs_aa_buffer_table->storage_height * 8) << 16));
            n++;
            store(&q[n], (i + 1) * g_fs_aa_buffer_table->display_width |
                   ((long)g_fs_aa_buffer_table->display_height << 20));
            n++;
            store(&q[n], ((i + 1) * g_fs_aa_buffer_table->storage_width +
                          (0x8000 - g_fs_aa_buffer_table->storage_width * 8)) |
                   ((long)(g_fs_aa_buffer_table->storage_height * 8 + 0x7FF8) << 16));
            n++;
        }
    }
    out = q + 76;
    *out++ = 0x4400000000008001UL;
    *out++ = 0x4410;
    *out++ = 0x181;
    *out++ = 0x80000000UL;
    *out++ = (0x7FF8 - g_fs_aa_buffer_table->storage_width * 8) |
             ((long)(0x7FF8 - g_fs_aa_buffer_table->storage_height * 8) << 16);
    *out++ = (0x7FF8 - g_fs_aa_buffer_table->storage_width * 8) |
             ((long)(g_fs_aa_buffer_table->storage_height * 8 + 0x7FF8) << 16);

    BuildAspectBlitStrips(0, 0);

    q = (unsigned long *)g_dma_strip_packet_first;
    out = q;
    *out++ = 0x408B400000000001UL;
    *out++ = 0xEEEE;
    *out++ = 0x31001;
    *out++ = 0x47;
    *out++ = 5;
    *out++ = 8;
    *out++ = 0x100000261UL;
    *out++ = 0x14;
    *out++ = (((long)g_fs_aa_buffer_table->fbp0 << 5) |
              ((long)((g_fs_aa_buffer_table->display_width >> 6) & 0x3F) << 14) |
              ((long)g_fs_aa_buffer_table->psm << 20)) | 0xEA8000000UL;
    *out++ = 6;
    *out++ = 0x4400000000008010UL;
    *out = 0x5353;
    {
        unsigned long *p = q + 12;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = i << 9;
            *p++ = (i * 0x200 + 0x7000) | ((long)(0x8000 - g_fs_aa_buffer_table->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x200) | ((long)g_fs_aa_buffer_table->display_height << 20);
            *p++ = (i * 0x200 + 0x7200) | ((long)(g_fs_aa_buffer_table->display_height * 8 + 0x7FF0) << 16);
        }
    }

    q = (unsigned long *)g_dma_packet_source;
    out = q;
    *out++ = 0x1000000000000001UL;
    *out++ = 0xE;
    *out++ = 0x30000;
    *out++ = 0x47;
    *out++ = 0x2400000000008001UL;
    *out++ = 0x10;
    *out++ = 0x106;
    *out++ = 0x80000000UL;
    *out++ = 0x2400000000008010UL;
    *out = 0x44;
    {
        unsigned long *p = q + 10;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = (i * 0x200 + 0x6FF8) |
                   ((long)(0x7FF8 - g_fs_aa_buffer_table->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x71F8) | ((long)(g_fs_aa_buffer_table->display_height * 8 + 0x7FF8) << 16);
        }
    }

    mem_copy_aligned(g_dma_packet_copy, g_dma_packet_source, 0x150);

    q = (unsigned long *)g_gfx_clear_packet_a;
    {
        unsigned long *p = q + 8;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = (i * 0x200 + 0x6FF8) |
                   ((long)(0x7FF8 - g_fs_aa_buffer_table->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x71F8) | ((long)(g_fs_aa_buffer_table->display_height * 8 + 0x7FF8) << 16);
        }
    }

    q = (unsigned long *)g_gfx_clear_packet_b;
    {
        unsigned long *p = q + 8;
        int i;
        for (i = 0; i < 16; i++) {
            if (g_widescreen_flag) {
                *p++ = (i * 0x280 + 0x6BF8) |
                       ((long)(0x7FF8 - g_fs_aa_buffer_table->storage_height * 8) << 16);
                *p++ = ((i + 1) * 0x280 + 0x6BF8) |
                       ((long)(g_fs_aa_buffer_table->storage_height * 8 + 0x7FF8) << 16);
            } else {
                *p++ = (i * 0x200 + 0x6FF8) |
                       ((long)(0x7FF8 - g_fs_aa_buffer_table->storage_height * 8) << 16);
                *p++ = ((i + 1) * 0x200 + 0x6FF8) |
                       ((long)(g_fs_aa_buffer_table->storage_height * 8 + 0x7FF8) << 16);
            }
        }
    }

    q = (unsigned long *)g_gfx_clear_packet_c;
    {
        unsigned int y = 0, x = 0;
        int i;
        unsigned long *p = q + 24;
        for (i = 0; i < 16; i++) {
            *p++ = x;
            *p++ = y;
            x += 0x200;
            *p++ = x | ((long)g_fs_aa_buffer_table->display_height << 20);
            y += 0x100;
            *p++ = y | 0x10000000;
        }
    }

    q = (unsigned long *)g_gfx_clear_packet_d;
    {
        unsigned int y = 0, x = 0;
        int i;
        unsigned long *p = q + 24;
        for (i = 0; i < 16; i++) {
            *p++ = x;
            *p++ = y;
            x += 0x200;
            *p++ = x | ((long)g_fs_aa_buffer_table->display_height << 20);
            y += 0x40;
            *p++ = y | 0x4000000;
        }
    }

    {
        unsigned long *r = (unsigned long *)g_gfx_shadow_packet;
        int fbp = g_vram_display_address;
        r[2] = ((long)fbp >> 13) | 0xFFFFFF00080000UL;
        r[10] = ((fbp >> 8) | 0x24020000) | 0x640000000UL;
    }
    FlushCache(0);
}
