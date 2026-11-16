#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

typedef unsigned long u64;

extern void VU1_addGSregister(u32,u64);

extern void VU1_addGSregister(unsigned int reg, unsigned long value);

typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

extern short g_screen_copy_page;
extern void gfx_build_screen_sprite_packet(int width, int height, int address, int mode);
extern void gfx_configure_projection(int width, int height, float scale, float a, float b, float c, float d);

typedef struct { u8 pad[0x10]; float *result; u32 threshold; u8 gap[4]; int flags; short x, y, w, h; u8 tail[8]; } CopyRegion;

extern CopyRegion g_screen_copy_regions[];

extern s32 g_is_pal_video;

extern s32 g_widescreen_flag __attribute__((sda));

extern s32 func_00124418(void);

extern void sceGsResetGraph(s32,s32,s32,s32);

typedef struct { u8 before[0x158]; short a,b,c; u8 gap[10]; short d,e; } DisplayState;

extern DisplayState g_screen_adjust_offsets;

extern void sceGsSetDefDispEnv(u8 *,short,short,short,short,short);

/* Family c1edda5cc3fa91ec — 148 bytes, levels/2_maktar_nebula and levels/11_joba.

   Write the four-word ring header and advance the resident pointer; when the
   pointer is null, hand the sibling buffer 48 bytes further on to the stop
   helper instead. Every reference reads the global again, and the last store
   addresses it through $gp (a delay-slot form the pinned -G0 profile cannot
   express). */
extern int *D_L02_001B3D08_1 __attribute__((sda));

extern int g_fs_aa_buffer_table __attribute__((sda));

extern void g_gfx_draw_list_init(void *);

extern volatile int * volatile D_L02_001B3D08_2 __attribute__((sda));

extern volatile int * volatile D_L02_001B3D08_4 __attribute__((sda));

extern char g_dma_packet_source[];

extern char g_dma_packet_copy[];

/* Adds up the widths of the letters in a piece of text, using a letter-width table. */
s32 measure_text_width(u8 *text,s32 length,u8 *glyphs) {
 s32 width=0,i=0;
 u8 *p;
 if(length!=0 && text[0]!=0) {
  p=text;
  do {
   s32 advance=*(signed char *)(glyphs+p[0]*4+3);
   i++; p++;
   if(advance!=0) width+=advance;
   if(i==length) break;
  } while(p[0]!=0);
 }
 return width;
}

extern u8 g_font_glyphs_small[];

/* Measures how wide text will be in the small font. */
s32 text_measure_width_small(u8 *text, s32 length) {
    return measure_text_width(text, length, g_font_glyphs_small);
}

extern u8 g_font_glyphs_medium[];

/* Measures how wide text will be in the medium font. */
s32 text_measure_width_medium(u8 *text, s32 length) {
    return measure_text_width(text, length, g_font_glyphs_medium);
}

extern u8 g_font_glyphs_large[];

/* Measures how wide text will be in the large font. */
s32 text_measure_width_large(u8 *text, s32 length) {
    return measure_text_width(text, length, g_font_glyphs_large);
}

extern int text_measure_width_scaled(u8 *, int, u8 *, float);

/* Measures how wide text will be in the small font at a given size. */
int text_measure_width_small_scaled(u8 *text, int length, float scale) {
    return text_measure_width_scaled(text, length, g_font_glyphs_small, scale);
}

/* func_0027F2A8 is in 0027F128-font-g8.c. */

extern u64 GetEffectTextureDescriptor(int);
extern void text_draw_line(int, int, u64, u8 *, int, u64, u8 *);

/* Draws text in the small font at the given screen position. */
void text_draw_small(int x, int y, u64 style, u8 *text, int length)
{
    u64 font = GetEffectTextureDescriptor(1);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_small);
}

/* Draws text in the medium font at the given screen position. */
void text_draw_medium(int x, int y, u64 style, u8 *text, int length)
{
    u64 font = GetEffectTextureDescriptor(2);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_medium);
}



/* func_0027F640 -- see src/game/0027F128-font-g8.c (built with -G8). */


/* func_0027F980 is matched in 0027F980.c. */

/* func_0027FA10 is matched in 0027F980.c. */



/* func_0027FAA8 is matched in 0027F980.c. */

/* func_0027FB40 is matched in 0027F980.c. */


/* func_0027FBD8 is matched in 0027F980.c. */

/* func_0027FC70 is matched in 0027F128-fpw-g8.c. */

extern void FontPrintWindow(unsigned short *, u64, u8 *, int, u64, u8 *);

/* Draws word-wrapped text inside a text box using the small font. */
void text_draw_window_small(unsigned short *layout, u64 style, u8 *text, int length)
{
    u64 font = GetEffectTextureDescriptor(1);
    FontPrintWindow(layout, style, text, length, font, g_font_glyphs_small);
}

/* Draws word-wrapped text inside a text box using the medium font. */
void text_draw_window_medium(unsigned short *layout, u64 style, u8 *text, int length)
{
    u64 font = GetEffectTextureDescriptor(2);
    FontPrintWindow(layout, style, text, length, font, g_font_glyphs_medium);
}


/* Draws word-wrapped text inside a text box using the large font. */
void text_draw_window_large(unsigned short *layout, u64 style, u8 *text, int length)
{
    u64 font = GetEffectTextureDescriptor(3);
    FontPrintWindow(layout, style, text, length, font, g_font_glyphs_large);
}

/* Fills in a text box: its edges, the anchor point, line height and layout flags. */
void FontSetWindow(unsigned short *window,s32 yMin,s32 yMax,s32 xMin,s32 xMax,s32 xAnchor,s32 yStart,s32 lineHeight,s32 flags) {
 window[0]=yMin;window[1]=yMax;window[2]=xMin;window[3]=xMax;
 window[4]=xAnchor;window[5]=yStart;window[8]=lineHeight;window[9]=flags;
 window[6]=0;window[7]=0;window[10]=0;window[11]=0;
}


/* func_00280328 -- see src/game/0027F128-packet-g8.c (built with -G8). */

/* Sets up the screen-copy draw state for a texture of the given size and brightness scale. */
void gfx_setup_screen_copy_draw_state(int width, int height, int use_saved, float scale) {
    int address;

    if (use_saved) {
        address = g_screen_copy_page << 13;
    } else {
        int shift = width + height;
        if (shift > 16) shift = 16;
        address = 0x3FF000 - (4 << shift);
        address = (address >> 13) << 13;
    }
    gfx_build_screen_sprite_packet(width, height, address, 0);
    gfx_configure_projection(1 << width, 1 << height, scale, 0.0f, 524288.0f, 255.0f, 0.0f);
    if (use_saved) {
        VU1_addGSregister(0x47, 0UL);
    } else {
        VU1_addGSregister(0x47, 0x30000UL);
    }
    VU1_addGSregister(0x42, 0x8000000044UL);
}

extern void gfx_append_draw_list_header(void);
extern void gfx_init_view_context(void);
extern void UpdateViewContext(void);

/* Sends the three screen-effect setup steps one after the other. */
void gfx_run_screen_effect_setup(void) {
    gfx_append_draw_list_header();
    gfx_init_view_context();
    UpdateViewContext();
}

/* func_00280630 -- see src/game/0027F128-g8.c (built with -G8). */

/* The share of a region's pixels whose low 24 bits do not exceed the region's threshold. */
void ComputeRegionThresholdRatio(u32 *pixels, int index) {
    CopyRegion *region = &g_screen_copy_regions[index];
    s32 total = region->w * region->h;
    s32 count = 0;
    s32 i;

    for (i = 0; i < total; i++) {
        if ((pixels[i] & 0xFFFFFF) > region->threshold) count++;
    }
    *(&g_screen_copy_regions[index])->result = (float)(total - count) / (float)total;
}

/* func_00280710 -- see src/game/0027F128-copy-g8.c (built with -G8). */

ASM_FUNC("asm/game", func_002808F8);

/* Original assembly: RAC1 game/render/drawquad.c, func_001F7DD8. */
ASM_FUNC("asm/game", func_00280A70);

/* Original assembly: lqc2/sqc2/vdiv and VU0 vector ops; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00280B30);

ASM_FUNC("asm/game", func_00280B90);

ASM_FUNC("asm/game", func_00281154);

ASM_FUNC("asm/game", func_002811D4);

ASM_FUNC("asm/game", func_00281214);

/* Original assembly: RAC1 overlays/shared/glint_effects.c, func_L00_001FDE48. */
ASM_FUNC("asm/game", func_00281810);


/* The draw packet's texture state and its flags.

   D_00239B10 is a table of 20-byte entries. The first four words of an entry
   hold two bits of flags apiece, packed into the low half of the packet's
   64-bit flag word; the packet's own type goes in the top half. */
typedef struct { int f0, f1, f2, f3, f4; } QuadEntry;

extern QuadEntry g_quad_entry_table[];

typedef struct {
    u8 pad[0x70];
    long f70;   /* cleared here */
    long f78;   /* the font */
    long f80;   /* the texture state, 0xFF9000000260 */
    long f88;   /* the flags */
} QuadPacket;

/* Sets up the texture and flags of a quad before it is drawn. */
void gfx_init_quad_packet_state(QuadPacket *q, int fontId, int entryIndex, int typeBits) {
    QuadEntry *e;
    long flags;
    q->f78 = GetEffectTextureDescriptor(fontId);
    q->f80 = ((long)0xFF90 << 32) | 0x260;
    q->f70 = 0;
    e = &g_quad_entry_table[entryIndex];
    flags = (long)e->f0;
    flags |= (long)e->f1 << 2;
    flags |= (long)e->f2 << 4;
    flags |= (long)e->f3 << 6;
    flags |= (long)typeBits << 32;
    q->f88 = flags;
}


/* func_00281EB8 lives in 00281EB8.c. */


/* calls the measured callee with constants 0x47 and 0x513f1 */
/* Writes one fixed value to a graphics register. */
void gfx_set_gs_register_constant(void) {
 VU1_addGSregister(0x47,0x513f1UL);
}

/* Does nothing. */
void stub_no_op(void)
{
}

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); same body as RAC1 fastfunc func_001F9840, and its neighbours are RAC1 fastfunc original assembly. */
ASM_FUNC("asm/game", func_00282848);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/game", func_00282890);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fastfunc original assembly. */
ASM_FUNC("asm/game", func_002828B8);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/game", func_002828C8);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fastfunc original assembly. */
ASM_FUNC("asm/game", func_002828F0);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9850. */
ASM_FUNC("asm/game", func_00282900);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fastfunc original assembly. */
ASM_FUNC("asm/game", func_00282928);

/* Original assembly: `lwc1; nop; jr $ra; mul.s` keeps a load-delay nop before the return that this cc1 never emits (MATCHING-BLOCKERS 4); its neighbours are RAC1 fastfunc original assembly. */
ASM_FUNC("asm/game", func_00282938);

ASM_FUNC("asm/game", func_00282948);

ASM_FUNC("asm/game", func_00282978);

/* Original assembly: RAC1 overlays/shared/fast_vector_math.c, func_L00_001FEF78. */
ASM_FUNC("asm/game", func_002829A8);

/* Original assembly: $at as a working register and trapping addi/sub; the compiler cannot emit these. */
ASM_FUNC("asm/game", func_002829D8);

ASM_FUNC("asm/game", func_00282A18);

/* Original assembly: an unconditional `teq $zero,$zero,0`; this cc1 has no trap pattern that emits `teq` (only div_trap's bne/break) and rejects __builtin_trap. Same bytes as RAC1 fastfunc func_001F9978 (asm/handwritten). */
ASM_FUNC("asm/game", func_00282A28);

ASM_FUNC("asm/game", func_00282A38);

ASM_FUNC("asm/game", func_00282A60);

ASM_FUNC("asm/game", func_00282A88);

/* Original assembly: trapping add/addi in the copy loops; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00282AB0);

ASM_FUNC("asm/game", func_00282B50);

ASM_FUNC("asm/game", func_00282B78);

/* Original assembly: $at as a working base register (lui/ori $at then sw), sync, and ori after jr; the compiler cannot emit these. */
ASM_FUNC("asm/game", func_00282BA8);

ASM_FUNC("asm/game", func_00282BE0);


ASM_FUNC("asm/game", func_00282C10);

ASM_FUNC("asm/game", func_00282C30);

/* 8-BYTE LOT -- bare getters and setters, identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* Returns the absolute value of a number. */
f32 math_fabs(f32 value) { return __builtin_fabsf(value); }

/* func_00282C50 (the float minimum) is matched in its own unit, src/game/00282C50.c: it needs
   the -O1 -ffast-math profile. */

ASM_FUNC("asm/game", func_00282C58);

/* Original assembly: identical to RAC1 game/math/fastfunc.c func_001F9BB0, which rac1-decomp keeps as handwritten; 16 bytes, so below the identity rule's length. */
ASM_FUNC("asm/game", func_00282C68);

ASM_FUNC("asm/game", func_00282C78);

/* Clear one aligned 128-bit object through architectural zero. */
void vec_clear_128(TI128 *vec) { *vec = 0; }

/* Original assembly: sqc2 (COP2 store) in the return delay slot, which the compiler cannot emit. */
ASM_FUNC("asm/game", func_00282C90);

ASM_FUNC("asm/game", func_00282C98);

ASM_FUNC("asm/game", func_00282CA8);

ASM_FUNC("asm/game", func_00282CC0);

ASM_FUNC("asm/game", func_00282CD8);

ASM_FUNC("asm/game", func_00282CF0);

ASM_FUNC("asm/game", func_00282D08);

ASM_FUNC("asm/game", func_00282D30);

ASM_FUNC("asm/game", func_00282D48);

ASM_FUNC("asm/game", func_00282D60);

ASM_FUNC("asm/game", func_00282D78);

ASM_FUNC("asm/game", func_00282D90);

ASM_FUNC("asm/game", func_00282DB0);

ASM_FUNC("asm/game", func_00282DD8);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9CB8. */
ASM_FUNC("asm/game", func_00282DF0);

ASM_FUNC("asm/game", func_00282E20);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9D10. */
ASM_FUNC("asm/game", func_00282E48);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9D48. */
ASM_FUNC("asm/game", func_00282E80);

ASM_FUNC("asm/game", func_00282EB0);

ASM_FUNC("asm/game", func_00282ED8);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9DC0. */
ASM_FUNC("asm/game", func_00282F20);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9E10. */
ASM_FUNC("asm/game", func_00282F70);

/* Original assembly: lqc2/sqc2/vdiv/vwaitq VU0 ops, $at as a working register and trapping addi. */
ASM_FUNC("asm/game", func_00282FB8);

/* Original assembly: lqc2/sqc2/vrsqrt VU0 ops and $at as a working register; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283028);

ASM_FUNC("asm/game", func_00283098);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9EE8. */
ASM_FUNC("asm/game", func_002830C0);

ASM_FUNC("asm/game", func_002830F0);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9F30. */
ASM_FUNC("asm/game", func_00283108);

ASM_FUNC("asm/game", func_00283130);

ASM_FUNC("asm/game", func_00283150);

ASM_FUNC("asm/game", func_00283180);

ASM_FUNC("asm/game", func_00283198);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001F9FC0. */
ASM_FUNC("asm/game", func_002831B0);

/* Original assembly: lqc2/qmtc2/qmfc2 VU0 ops and trapping add; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283248);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA168. */
ASM_FUNC("asm/game", func_00283360);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA190. */
ASM_FUNC("asm/game", func_00283388);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA1C0. */
ASM_FUNC("asm/game", func_002833B8);

ASM_FUNC("asm/game", func_002833F0);

ASM_FUNC("asm/game", func_00283410);

ASM_FUNC("asm/game", func_00283430);

ASM_FUNC("asm/game", func_00283658);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA480. */
ASM_FUNC("asm/game", func_00283678);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA4A0. */
ASM_FUNC("asm/game", func_00283698);

/* Original assembly: lqc2/sqc2 and VU0 vector ops; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002836E8);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA4F0. */
ASM_FUNC("asm/game", func_00283738);

ASM_FUNC("asm/game", func_00283788);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA588. */
ASM_FUNC("asm/game", func_002837D0);

/* Original assembly: lqc2/sqc2/vrsqrt VU0 ops and $at as a working register; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283810);

/* Original assembly: RAC1 overlays/shared/fast_vector_math.c, func_L00_001FFED8. */
ASM_FUNC("asm/game", func_00283898);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA648. */
ASM_FUNC("asm/game", func_00283958);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA6C0. */
ASM_FUNC("asm/game", func_002839D0);

/* Original assembly: lqc2/sqc2 and VU0 vector ops; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283A58);

/* Original assembly: qmtc2/vitof/sqc2 VU0 ops with $at as a working register; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283AF0);

/* Original assembly: lqc2/sqc2/qmtc2 and VU0 vector ops; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_00283B48);

/* Byte-identical 72-byte copy of RAC1 func_001FA748, which RAC1 marks ASM_FUNC. */
ASM_FUNC("asm/game", func_00283B98);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA790. */
ASM_FUNC("asm/game", func_00283BE0);

/* Original assembly: $at as a working register and trapping add; the compiler cannot emit these. */
ASM_FUNC("asm/game", func_00283C28);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA850. */
ASM_FUNC("asm/game", func_00283C80);

/* Original assembly: `cvt.s.w` directly after `cvt.w.s` in the FPU; this cc1's only cvt.s.w templates start from mtc1 or l.s, so it cannot emit it. */
ASM_FUNC("asm/game", func_00283CB8);

/* Original assembly: RAC1 overlays/shared/fast_vector_math.c, func_L00_002001D8. */
ASM_FUNC("asm/game", func_00283CC8);

/* SECOND LOT -- 16 to 32 bytes. */
/* integer-to-float conversion; byte-identical across all 27 levels. */
/* Turns a whole number into a float. */
f32 IntToFloat(s32 value) { return (f32)value; }

/* Original assembly: identical to RAC1 game/math/fastfunc.c func_001FA898, which rac1-decomp keeps as handwritten; 16 bytes, so below the identity rule's length. */
ASM_FUNC("asm/game", func_00283CF0);

/* Original assembly: RAC1 overlays/shared/fast_vector_math.c, func_L00_00200210. */
ASM_FUNC("asm/game", func_00283D00);

/* Original assembly: RAC1 game/math/fastfunc.c, func_001FA8A8. */
ASM_FUNC("asm/game", func_00283D38);

/* Original assembly: lqc2/VU0 vector ops, $at as a working register and trapping addi/sub. */
ASM_FUNC("asm/game", func_00283D80);

ASM_FUNC("asm/game", func_00283DB8);

ASM_FUNC("asm/game", func_00283EB0);

ASM_FUNC("asm/game", func_00283EF0);

extern long long g_clear_color_value;

/* Sets the background color of the screen from red, green and blue values. */
void SetBackgroundColor(s32 red, s32 green, s32 blue) {
    g_clear_color_value = red | ((long long)green << 8) | ((long long)blue << 16) | 0x80000000ULL;
}

/* Asks the display system for a result using the current display buffer. */
int gfx_query_display_buffer(void)
{
    extern int func_00125D98(void *);
    return func_00125D98((void *)g_fs_aa_buffer_table);
}


/* shared native body of family c1edda5cc3fa91ec */
/* Adds a small header to the draw list, or restarts the display if there is no list. */
void gfx_append_draw_list_header(void)
{
    if (D_L02_001B3D08_1 != 0) {
        *(int *)D_L02_001B3D08_1 = 0x30000009;
        *(int *)((char *)D_L02_001B3D08_1 + 4) = (g_fs_aa_buffer_table + 48) & 0x0FFFFFFF;
        *(int *)((char *)D_L02_001B3D08_1 + 8) = 0;
        *(int *)((char *)D_L02_001B3D08_1 + 12) = 0x50000009;
        D_L02_001B3D08_1 = (int *)((char *)D_L02_001B3D08_1 + 16);
    } else {
        g_gfx_draw_list_init((void *)(g_fs_aa_buffer_table + 48));
    }
}

/* shared native body of family cfd2e0cd2b82a1b7 (default profile) */
/* Adds a header to the draw list that points at one of two buffers. */
void gfx_append_draw_list_buffer_tag(int useAlt)
{
    int *list = (int *)D_L02_001B3D08_2;

    if (list == 0)
        return;
    list[0] = 0x30000015;
    if (useAlt == 0)
        D_L02_001B3D08_2[1] = (int)g_dma_packet_source;
    else
        D_L02_001B3D08_2[1] = (int)g_dma_packet_copy;
    D_L02_001B3D08_2[2] = 0;
    D_L02_001B3D08_2[3] = 0x50000015;
    D_L02_001B3D08_4 = D_L02_001B3D08_2 + 4;
}
