#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

/* Rotated sprite construction follows RAC1 draw.c (GPL-3.0). */
typedef struct { float x, y, z, w; } QuadPoint;
typedef struct { unsigned int tag, addr, vif0, vif1; } QuadDmaTag;
union QuadCursor { QuadDmaTag *tag; int *words; unsigned char *bytes; int addr; };
extern union QuadCursor g_dma_packet_cursor __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);

/* Write the measured GS privileged 64-bit register configuration in order. */
typedef unsigned long long GsRegisterValue;

extern GsRegisterValue D_001A6488[3];

/* Scalar GS setup wrapper; pinned standard integer arguments and helper calls. */
extern void gfx_build_screen_sprite_packet(int width, int height, int address, int mode);

extern void VU1_addGSregister(unsigned int reg, unsigned long value);

extern void DrawCenteredCaptureBackground(int width, int height);

/* Qwen draft (branch qwen/autonomy, 00dc80b4), checked by tools/check.py */
/* Wrapper function that calls func_00284EA8 and returns.
 * Stack frame is used only to save/restore the return address (ra).
 * The function follows standard MIPS ABI conventions:
 * - addiu sp,sp,-0x10 allocates 16 bytes on the stack
 * - sd ra,0x(sp) saves the return address
 * - jal calls the external helper
 * - delay slot is a nop
 * - ld ra,0x(sp) restores the return address
 * - jr ra returns to caller
 * - _addiu sp,sp,0x10 deallocates stack
 */
void gfx_call_sync_helper(void);

/* Qwen draft (branch qwen/autonomy, b9c5326c), checked by tools/check.py */
void menu_draw_pause_panels(int);

/* Family 489bf28ebf58470c (120 B, 2 placements): call every registered
 * callback with its paired argument, bounded by a resident count word.
 *
 * The three resident globals are reached with `lui`+`lw` / `lui`+`addiu`
 * pairs that the ASSEMBLER macro expands from a single RTL insn; this only
 * happens when the externs carry the `sda` attribute (SYMBOL_REF_FLAG), which
 * suppresses gcc's HIGH/LO_SUM address split.  Without it the compiler keeps
 * the `%hi` in an extra callee-saved register and the body is 3 words long.
 */
typedef void (*fn_t)(int);

extern int D_L02_001B3078 __attribute__((sda));

   /* resident callback count */
extern fn_t D_L02_001B3058[] __attribute__((sda));

 /* callback table        */
extern int D_L02_001B3068[] __attribute__((sda));

extern int Ff67aa9df_D_001A7350 __attribute__((sda));

extern int Ff67aa9df_D_001A7354 __attribute__((sda));

extern void gfx_append_flat_quad_packet(void *v, void *x);

/* Sets the graphics chip's display registers (background colour, screen buffers) to their start-up values. */
void ResetGsRegistersPr(void)
{
    GsRegisterValue framebuffer, display;
    GS_BGCOLOR = 0;
    GS_PMODE = 0xffa1;
    GS_SMODE2 = D_001A6488[0];
    framebuffer = D_001A6488[1];
    GS_DISPFB1 = framebuffer;
    GS_DISPFB2 = framebuffer;
    display = D_001A6488[2];
    GS_DISPLAY1 = display;
    GS_DISPLAY2 = display;
    GS_EXTWRITE = 0;
}

/* Set up aligned GS buffer state and emit pinned register/clear helper calls; source identity and matching require complete-unit qualification */
/* Sets up a small off-screen drawing buffer near the end of video memory and clears it. */
void gfx_setup_offscreen_target(int width, int height)
{
    int sum = width + height;
    int address;

    if (sum > 16)
        sum = 16;
    address = 0x3ff000 - (4 << sum);
    address = (address >> 13) << 13;
    gfx_build_screen_sprite_packet(width, height, address, 1);
    VU1_addGSregister(0x47, 0x30000UL);
    VU1_addGSregister(0x42, 0x8000000044UL);
    DrawCenteredCaptureBackground(0x100, 0x100);
    VU1_addGSregister(0x42, 0x8000000044UL);
}

/* Calls a graphics helper and returns. */
void gfx_call_sync_helper(void)
{
  gfx_append_draw_list_header();
  return;
}

/* Defined in 0027BD70-g8.c. */


/* Draws a frame with every basic layer switched on. */
void gfx_render_frame_all_layers(void) {
    extern void gfx_append_draw_list_buffer_tag(int);
    extern void RenderFrame(void);
    extern int D_001B1594 __attribute__((sda));
    gfx_append_draw_list_buffer_tag(0);
    D_001B1594 = 0x7F;
    RenderFrame();
}

extern unsigned int menu_get_second_value(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern int D_001B1594 __attribute__((sda));
extern void RenderFrame(void);
extern void menu_draw_pause_panels(int);
extern void menu_draw_message_panel(void);

/* Draws a frame with extra layers switched on when the screen mode asks for it, then finishes the frame. */
void gfx_render_frame_extra_layers(void)
{
    if (menu_get_second_value() == 1) {
        gfx_append_draw_list_buffer_tag(0);
        D_001B1594 = 0x100FF;
        RenderFrame();
    } else if (menu_get_second_value() == 0) {
        menu_draw_pause_panels(1);
    }
    menu_draw_message_panel();
}


/* Calls a frame helper with zero. */
void gfx_call_frame_helper_zero(void)
{
  menu_draw_pause_panels(0);
  return;
}

/* func_0027C540: defined in 0027B948-g8.c. */



/* Defined in 0027C878-g8.c. */

extern int D_001B1608[] __attribute__((sda));
extern fn_t D_001B9E40[];
extern int D_001B9F40[];

/* Adds a draw callback and its argument to a list of up to 64. */
void gfx_register_world_draw_callback(fn_t first, int second) {
    int index = D_001B1608[0];
    if (index < 64) {
        D_001B9E40[index] = first;
        D_001B9F40[index] = second;
        D_001B1608[0] = index + 1;
    }
}

/* Calls every draw callback in that list, each with its own argument. */
void gfx_run_world_draw_callbacks(void) {
    int index;
    for (index = 0; index < D_001B1608[0]; ++index)
        D_001B9E40[index](D_001B9F40[index]);
}

extern int D_001B1610[] __attribute__((sda));
extern fn_t D_001BA240[];
extern int D_001BA340[];

/* Adds a draw callback and its argument to a second list of up to 64. */
void gfx_register_early_draw_callback(fn_t first, int second) {
    int index = D_001B1610[0];
    if (index < 64) {
        D_001BA240[index] = first;
        D_001BA340[index] = second;
        D_001B1610[0] = index + 1;
    }
}

/* Calls every draw callback in the second list. */
void gfx_run_early_draw_callbacks(void) {
    int index;
    for (index = 0; index < D_001B1610[0]; ++index)
        D_001BA240[index](D_001BA340[index]);
}

extern int D_001B1614[] __attribute__((sda));
extern fn_t D_001BA440[];
extern int D_001BA540[];

/* Calls every draw callback in a third list. */
void gfx_run_late_draw_callbacks(void) {
    int index;
    for (index = 0; index < D_001B1614[0]; ++index)
        D_001BA440[index](D_001BA540[index]);
}

extern int D_001B160C[] __attribute__((sda));
extern fn_t D_001BA040[];
extern int D_001BA140[];

/* Adds a draw callback and its argument to a fourth list of up to 64. */
void gfx_register_overlay_draw_callback(fn_t first, int second) {
    int index = D_001B160C[0];
    if (index < 64) {
        D_001BA040[index] = first;
        D_001BA140[index] = second;
        D_001B160C[0] = index + 1;
    }
}

/* Calls every draw callback in the fourth list. */
void gfx_run_overlay_draw_callbacks(void) {
    int index;
    for (index = 0; index < D_001B160C[0]; ++index)
        D_001BA040[index](D_001BA140[index]);
}

extern int D_001B1638[] __attribute__((sda));
extern fn_t D_001B1618[] __attribute__((sda));
extern int D_001B1628[] __attribute__((sda));

/* Adds a callback and its argument to a short list that holds only 4 entries. */
void gfx_register_final_draw_callback(fn_t callback, int argument) {
    int index = D_001B1638[0];
    if (index < 4) {
        D_001B1618[index] = callback;
        D_001B1628[index] = argument;
        D_001B1638[0] = index + 1;
    }
}

/* shared native body of family 489bf28ebf58470c */
  /* argument table        */

/* Calls every callback in the short list, each with its own argument. */
void gfx_run_final_draw_callbacks(void) {
    int i;
    for (i = 0; i < D_L02_001B3078; i++) {
        D_L02_001B3058[i](D_L02_001B3068[i]);
    }
}

/* Defined in 0027D160-g8.c. */

/* Defined in 0027D330-g8.c. */

extern int D_L00_001BCAF4;

extern unsigned char D_001A7BB1 __attribute__((sda));

extern float math_fast_sin_or_cos_a(float);

extern int FastTweenColor(float, int, int);

extern unsigned char *GetLocalizedString(int);

extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

/* Draws a line of text that slowly changes colour back and forth. */
void text_draw_pulsing(void)
{
    int y;
    long style;
    unsigned char *text;
    float wave;
    int counter;

    y = 0x148;
    if (D_001A7BB1) {
        y = 0x17C;
    }
    counter = D_L00_001BCAF4;
    wave = (float)(counter % 100) * 0.02f - 1.0f;
    if (wave < -1.0f) {
        wave = -1.0f;
    }
    if (1.0f < wave) {
        wave = 1.0f;
    }
    wave = math_fast_sin_or_cos_a(wave * 3.14159274f);
    wave = wave + 1.0f;
    style = FastTweenColor(wave * 0.5f, 0x7FE0E0E0, 0x5FF0C070);
    text = GetLocalizedString(0x2F20);
    text_draw_centered_medium(0x5A, y, style, text, -1);
}

/* Subtitle layout and window path adapted from OpenRAC/rac1-decomp src/game/draw.c's
 * draw_subtitles (GPL-3.0). D_001A7340 is RAC1's g_screen_extent: retail reads its
 * second word as an offset from this base, a two-word load that reorg leaves out of
 * the delay slot. Retail reads the language byte twice, so it is declared volatile. */
typedef struct { short start, end, text[6]; } SubtitleRecord;
typedef struct { char pad[0x34]; int time; char gap[0x14]; unsigned char *subs; } SubtitleState;
extern SubtitleState g_scene_playback_state;
extern volatile unsigned char D_001A7BB4[] __attribute__((sda));
extern unsigned char D_001A7B96[] __attribute__((sda));
extern int g_screen_width[] __attribute__((sda));
extern unsigned char D_001A8998[];
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void text_draw_window_medium(unsigned short *, unsigned long, unsigned char *, int);
extern void text_draw_medium(int, int, unsigned long, unsigned char *, int);
extern unsigned int func_001157AC(unsigned char *);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);

/* Shows the subtitle that matches the current time, as plain text or in a dark box. */
void DrawSubtitles(void)
{
    SubtitleRecord *p;
    int idx;
    if (!g_scene_playback_state.subs) return;
    idx = 0;
    if ((unsigned int)(D_001A7BB4[0] - 2) < 4) idx = D_001A7BB4[0] - 1;
    for (p = (SubtitleRecord *)g_scene_playback_state.subs; p->start >= 0; ++p) {
        if (g_scene_playback_state.time < p->start) continue;
        if (p->end < g_scene_playback_state.time) continue;
        if (!D_001A7B96[0] && g_scene_playback_state.subs[p->text[idx]] != '*') continue;
        if (g_scene_playback_state.subs[p->text[idx]] == '*') {
            int y = 0x40;
            int alpha = 0xB0000000;
            unsigned char *str;
            if (g_scene_playback_state.subs[p->text[idx] + 1] != '*') y = g_screen_width[1] - 0xC8;
            else if (D_001A7BB1) y = 0x18;
            if (p->end - g_scene_playback_state.time < 0x12)
                alpha = (int)(p->end - (long)(g_scene_playback_state.time - 1)) << 27;
            else if (g_scene_playback_state.time - p->start < 0x12)
                alpha = (int)(g_scene_playback_state.time - (long)(p->start - 1)) << 27;
            str = g_scene_playback_state.subs + p->text[idx];
            if (str[1] != '*')
                text_draw_centered_medium(0x100, 0xD0, alpha | 0xE0E0E0, str, -1);
            else
                text_draw_medium(0x20, y, alpha | 0xE0E0E0, str, -1);
        } else {
            unsigned short win[16];
            short w, h;
            int hw, hh;
            int extent = g_screen_width[1];
            FontSetWindow(win, 0xC8, 0x1A4, 0x28, 0x1D8, 0x100,
                          D_001A7BB1 ? extent - 0x36 : extent - 0x64, 0x12, 7);
            text_draw_window_medium(win, 0x80B0B0B0UL, &g_scene_playback_state.subs[p->text[idx]], -1);
            win[5] -= 4;
            w = win[6];
            h = win[7];
            hh = (h >> 1) + 5;
            hw = (w >> 1) + 10;
            if ((short)win[5] + hh > g_screen_width[1] - 0x14)
                win[5] = g_screen_width[1] - ((h >> 1) + 0x19);
            gfx_draw_rounded_box((short)win[5] - hh, (short)win[5] + hh, 0x100 - hw, 0x100 + hw, 0x60, 0x40404);
            win[9] &= ~4;
            if (func_001157AC(&g_scene_playback_state.subs[p->text[idx]]) < 0x96)
                text_draw_window_medium(win, 0x80B0B0B0UL, &g_scene_playback_state.subs[p->text[idx]], -1);
            else
                text_draw_window_medium(win, 0x80B0B0B0UL, D_001A8998, -1);
            return;
        }
    }
}

/* Defined in 0027D900-g8.c. */

/* Defined in 0027DB68-g8.c. */

/* func_0027DDC0 is in 0027B948-g8.c (-G8: retail re-materialises the address of the
   packet pointer for every access, which only that flag reproduces). */

/* func_0027DE50 lives in 0027DE50-sdata.c. */

/* Defined in 0027DE50-g8.c. */


/* func_0027E018 is in 0027E018.c. */


/* Adapted from OpenRAC/rac1-decomp src/game/draw.c's emit_textured_rectangle (GPL-3.0).
 * RAC2 writes a 16-word GS packet with a per-vertex colour, a closing (5, 0) pair and
 * z in the top of each XYZ word; the CLAMP word is built up in retail's OR order. */
/* Draws a picture on a rectangle, with a separate colour for each corner. */
void EmitTexturedRectangle(float x, float y, float w, float h, int u, int v, int uw, int vh,
                   const unsigned int *rgba, unsigned long tex)
{
    int x0 = FloatToInt(x * 16.0f) + g_screen_width[4] - 8;
    int x1 = FloatToInt((x + w) * 16.0f) + g_screen_width[4] - 8;
    int y0 = FloatToInt(y * 16.0f) + g_screen_width[5] - 8;
    int y1 = FloatToInt((y + h) * 16.0f) + g_screen_width[5] - 8;
    int vb;
    int ub;
    int s0, s1;
    QuadDmaTag *header;
    QuadDmaTag *tag;
    long *p;
    long max_u, min_u, min_v, clamp, wide_u, z;

    if (x0 > 0x9000 || x1 < 0x7000 || y0 > 0x9000 || y1 < 0x7000) {
        return;
    }
    ub = u + uw;
    z = (long)0xFFFFF0 << 32;
    s0 = u * 16;
    s1 = ub * 16;
    g_dma_packet_cursor.tag->tag = 0x10000009;
    g_dma_packet_cursor.tag->addr = 0;
    g_dma_packet_cursor.tag->vif0 = 0;
    g_dma_packet_cursor.tag->vif1 = 0x50000009;
    wide_u = u;
    max_u = ((long)ub << 14) | 0xA;
    min_u = (wide_u << 4) | max_u;
    min_v = min_u | ((long)v << 24);
    vb = v + vh;
    clamp = min_v | ((long)vb << 34);
    header = g_dma_packet_cursor.tag;
    g_dma_packet_cursor.tag = header + 1;
    *(long *)(header + 1) = 0x0400000000008001;
    *(long *)&g_dma_packet_cursor.tag->vif0 = 0x8531531531531068;
    tag = g_dma_packet_cursor.tag;
    g_dma_packet_cursor.tag = tag + 1;
    p = (long *)(tag + 1);
    p[0] = clamp;
    p[1] = tex;
    p[2] = 0x15C;
    p[3] = rgba[0];
    p[4] = (v << 20) + s0;
    p[5] = x0 | ((long)y0 << 16) | z;
    p[6] = rgba[1];
    p[7] = (v << 20) + s1;
    p[8] = x1 | ((long)y0 << 16) | z;
    p[9] = rgba[2];
    p[10] = (vb << 20) + s0;
    p[11] = x0 | ((long)y1 << 16) | z;
    p[12] = rgba[3];
    p[13] = (vb << 20) + s1;
    p[14] = x1 | ((long)y1 << 16) | z;
    p[15] = 5;
    g_dma_packet_cursor.bytes += 0x80;
}


/* Adapted from OpenRAC/rac1-decomp src/game/draw.c's append_rotated_sprite_quad,
 * itself adapted from Lombyte src/rendering/append_rotated_sprite_quad.c
 * (GPL-3.0). RAC2 ends the packet with a zero word. */
/* Draws a picture that can be turned to any angle, turned around a chosen centre point. */
void AppendRotatedSpriteQuad(float center_x, float center_y, float quad_width, float quad_height,
                   float angle, int texture_width, int texture_height,
                   long texture_tex0, long z_and_fog, int color,
                   unsigned char flip_u, unsigned char flip_v,
                   float pivot_u, float pivot_v)
{
    QuadPoint vertical_edge;
    QuadPoint horizontal_edge;
    QuadPoint center;
    QuadPoint temporary;
    QuadPoint top_left;
    QuadPoint top_right;
    QuadPoint bottom_left;
    QuadPoint bottom_right;
    QuadDmaTag *tag;
    unsigned long *packet_words;
    int texture_left;
    int texture_right;
    int texture_top;
    int texture_bottom;
    float inverse_pivot_u;
    float inverse_pivot_v;

    if (flip_u != 0) {
        texture_left = ((unsigned int)texture_width << 4);
        texture_right = 0x10;
    } else {
        texture_right = ((unsigned int)texture_width << 4);
        texture_left = 0x10;
    }
    if (flip_v != 0) {
        texture_top = ((unsigned int)texture_height << 20);
        texture_bottom = 0x100000;
    } else {
        texture_bottom = ((unsigned int)texture_height << 20);
        texture_top = 0x100000;
    }
    center.x = center_x;
    center.y = center_y;
    inverse_pivot_v = 1.0f - pivot_v;
    vertical_edge.x = quad_height * math_fast_sin_or_cos_b(angle);
    vertical_edge.y = quad_height * math_fast_sin_or_cos_a(angle);
    horizontal_edge.x = quad_width * math_fast_sin_or_cos_a(angle);
    horizontal_edge.y = -quad_width * math_fast_sin_or_cos_b(angle);
    inverse_pivot_u = 1.0f - pivot_u;
    FastVecScale(&temporary, &vertical_edge, inverse_pivot_v);
    FastVecAdd(&top_left, &center, &temporary);
    FastVecScale(&temporary, &horizontal_edge, inverse_pivot_u);
    FastVecSub(&top_left, &top_left, &temporary);
    FastVecScale(&temporary, &vertical_edge, inverse_pivot_v);
    FastVecAdd(&top_right, &center, &temporary);
    FastVecScale(&temporary, &horizontal_edge, pivot_u);
    FastVecAdd(&top_right, &top_right, &temporary);
    FastVecScale(&temporary, &vertical_edge, pivot_v);
    FastVecSub(&bottom_left, &center, &temporary);
    FastVecScale(&temporary, &horizontal_edge, inverse_pivot_u);
    FastVecSub(&bottom_left, &bottom_left, &temporary);
    FastVecScale(&temporary, &vertical_edge, pivot_v);
    FastVecSub(&bottom_right, &center, &temporary);
    FastVecScale(&temporary, &horizontal_edge, pivot_u);
    FastVecAdd(&bottom_right, &bottom_right, &temporary);
    g_dma_packet_cursor.tag->tag = 0x10000007;
    g_dma_packet_cursor.tag->addr = 0;
    g_dma_packet_cursor.tag->vif0 = 0;
    g_dma_packet_cursor.tag->vif1 = 0x50000007;
    tag = g_dma_packet_cursor.tag;
    packet_words = (unsigned long *)(tag + 1);
    g_dma_packet_cursor.tag = tag + 1;
    packet_words[0] = 0xB400000000008001;
    packet_words[1] = 0x53535353106;
    packet_words[2] = texture_tex0;
    packet_words[3] = 0x154;
    packet_words[4] = color;
    packet_words[5] = texture_left | texture_top;
    packet_words[6] =
        (FloatToInt(top_left.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(FloatToInt(top_left.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[7] = texture_right | texture_top;
    packet_words[8] =
        (FloatToInt(top_right.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(FloatToInt(top_right.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[9] = texture_left | texture_bottom;
    packet_words[10] =
        (FloatToInt(bottom_left.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(FloatToInt(bottom_left.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[11] = texture_right | texture_bottom;
    packet_words[12] =
        (FloatToInt(bottom_right.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(FloatToInt(bottom_right.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[13] = 0;
    g_dma_packet_cursor.tag = (QuadDmaTag *)((unsigned char *)g_dma_packet_cursor.tag + 0x70);
}


/* Defined in 0027E920.c. */

/* Defined in 0027EA28.c. */

/* Draws a plain rectangle from two x values and two y values. */
void gfx_draw_screen_rectangle(int i0, int i1, int i2, int i3, int tag, void *x)
{
    long long corners[4];

    corners[0] = (((i0 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    corners[1] = (((i2 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    corners[2] = (((i0 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    corners[3] = (((i2 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    gfx_append_flat_quad_packet(corners, x);
}

extern void gfx_draw_colored_rectangle(int a, int b, int c, int d, unsigned long e);

/* Draws a box with stepped, rounded corners from a stack of thin rectangles. */
void gfx_draw_rounded_box(int x, int y, int z, int w, int hi, int lo)
{
    int c = (hi << 24) | lo;

    gfx_draw_colored_rectangle(x, y, z, w, c);
    gfx_draw_colored_rectangle(x + 1, y - 1, z - 2, z, c);
    gfx_draw_colored_rectangle(x + 2, y - 2, z - 3, z - 2, c);
    gfx_draw_colored_rectangle(x + 4, y - 4, z - 4, z - 3, c);
    gfx_draw_colored_rectangle(x + 1, y - 1, w, w + 2, c);
    gfx_draw_colored_rectangle(x + 2, y - 2, w + 2, w + 3, c);
    gfx_draw_colored_rectangle(x + 4, y - 4, w + 3, w + 4, c);
}

extern void gfx_draw_colored_rectangle(int a, int b, int c, int d, unsigned long e);

/* Draws an outline made of small rectangles around a box. */
void gfx_draw_box_outline(int x, int y, int z, int w, int v)
{
    int c = (v & 0xFF000000) | 4;

    gfx_draw_colored_rectangle(x, y, z, w, c);
    gfx_draw_colored_rectangle(x - 1, x + 1, z + 3, w + 5, v);
    gfx_draw_colored_rectangle(x - 3, x - 5, z - 1, w - 3, v);
    gfx_draw_colored_rectangle(x - 5, y - 3, z - 1, z + 1, v);
    gfx_draw_colored_rectangle(x + 3, y + 1, z - 3, z - 5, v);
    gfx_draw_colored_rectangle(y - 1, y + 1, z - 3, w - 3, v);
    gfx_draw_colored_rectangle(y + 3, y + 5, z + 3, w + 1, v);
    gfx_draw_colored_rectangle(x + 3, y + 3, w - 1, w + 1, v);
    gfx_draw_colored_rectangle(x + 1, y - 3, w + 3, w + 5, v);
}


/* Defined in 0027EE58.c. */
