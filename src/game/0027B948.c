#include "include_asm.h"

/* Rotated sprite construction follows RAC1 draw.c (GPL-3.0). */
typedef struct { float x, y, z, w; } QuadPoint;
typedef struct { unsigned int tag, addr, vif0, vif1; } QuadDmaTag;
union QuadCursor { QuadDmaTag *tag; int *words; unsigned char *bytes; int addr; };
extern union QuadCursor D_001B22A8 __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283198(float);
extern int func_00283CF0(float);

/* Write the measured GS privileged 64-bit register configuration in order. */
typedef unsigned long long GsRegisterValue;

extern GsRegisterValue D_001A6488[3];

/* Scalar GS setup wrapper; pinned standard integer arguments and helper calls. */
extern void func_00285030(int width, int height, int address, int mode);

extern void func_002FC560(unsigned int reg, unsigned long value);

extern void func_00285398(int width, int height);

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
void func_0027BA48(void);

/* Qwen draft (branch qwen/autonomy, b9c5326c), checked by tools/check.py */
void func_002CBC58(int);

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

extern void func_0027EA28(void *v, void *x);

void func_0027B948(void)
{
    GsRegisterValue framebuffer, display;
    *(volatile GsRegisterValue *)0x120000e0 = 0;
    *(volatile GsRegisterValue *)0x12000000 = 0xffa1;
    *(volatile GsRegisterValue *)0x12000020 = D_001A6488[0];
    framebuffer = D_001A6488[1];
    *(volatile GsRegisterValue *)0x12000070 = framebuffer;
    *(volatile GsRegisterValue *)0x12000090 = framebuffer;
    display = D_001A6488[2];
    *(volatile GsRegisterValue *)0x12000080 = display;
    *(volatile GsRegisterValue *)0x120000a0 = display;
    *(volatile GsRegisterValue *)0x120000d0 = 0;
}

/* Set up aligned GS buffer state and emit pinned register/clear helper calls; source identity and matching require complete-unit qualification */
void func_0027B9C0(int width, int height)
{
    int sum = width + height;
    int address;

    if (sum > 16)
        sum = 16;
    address = 0x3ff000 - (4 << sum);
    address = (address >> 13) << 13;
    func_00285030(width, height, address, 1);
    func_002FC560(0x47, 0x30000UL);
    func_002FC560(0x42, 0x8000000044UL);
    func_00285398(0x100, 0x100);
    func_002FC560(0x42, 0x8000000044UL);
}

void func_0027BA48(void)
{
  func_00284EA8();
  return;
}

INCLUDE_ASM("asm/game", func_0027BA68);

/* Defined in 0027BD70-g8.c. */


void func_0027C480(void) {
    extern void func_00284F40(int);
    extern void func_0027BD70(void);
    extern int D_001B1594 __attribute__((sda));
    func_00284F40(0);
    D_001B1594 = 0x7F;
    func_0027BD70();
}

extern unsigned int func_00285850(void);
extern void func_00284F40(int);
extern int D_001B1594 __attribute__((sda));
extern void func_0027BD70(void);
extern void func_002CBC58(int);
extern void func_002859C8(void);

void func_0027C4A8(void)
{
    if (func_00285850() == 1) {
        func_00284F40(0);
        D_001B1594 = 0x100FF;
        func_0027BD70();
    } else if (func_00285850() == 0) {
        func_002CBC58(1);
    }
    func_002859C8();
}


void func_0027C520(void)
{
  func_002CBC58(0);
  return;
}

/* func_0027C540: defined in 0027B948-g8.c. */



/* Defined in 0027C878-g8.c. */

extern int D_001B1608[] __attribute__((sda));
extern fn_t D_001B9E40[];
extern int D_001B9F40[];

void func_0027CDC8(fn_t first, int second) {
    int index = D_001B1608[0];
    if (index < 64) {
        D_001B9E40[index] = first;
        D_001B9F40[index] = second;
        D_001B1608[0] = index + 1;
    }
}

void func_0027CE18(void) {
    int index;
    for (index = 0; index < D_001B1608[0]; ++index)
        D_001B9E40[index](D_001B9F40[index]);
}

extern int D_001B1610[] __attribute__((sda));
extern fn_t D_001BA240[];
extern int D_001BA340[];

void func_0027CE90(fn_t first, int second) {
    int index = D_001B1610[0];
    if (index < 64) {
        D_001BA240[index] = first;
        D_001BA340[index] = second;
        D_001B1610[0] = index + 1;
    }
}

void func_0027CEE0(void) {
    int index;
    for (index = 0; index < D_001B1610[0]; ++index)
        D_001BA240[index](D_001BA340[index]);
}

extern int D_001B1614[] __attribute__((sda));
extern fn_t D_001BA440[];
extern int D_001BA540[];

void func_0027CF58(void) {
    int index;
    for (index = 0; index < D_001B1614[0]; ++index)
        D_001BA440[index](D_001BA540[index]);
}

extern int D_001B160C[] __attribute__((sda));
extern fn_t D_001BA040[];
extern int D_001BA140[];

void func_0027CFD0(fn_t first, int second) {
    int index = D_001B160C[0];
    if (index < 64) {
        D_001BA040[index] = first;
        D_001BA140[index] = second;
        D_001B160C[0] = index + 1;
    }
}

void func_0027D020(void) {
    int index;
    for (index = 0; index < D_001B160C[0]; ++index)
        D_001BA040[index](D_001BA140[index]);
}

extern int D_001B1638[] __attribute__((sda));
extern fn_t D_001B1618[] __attribute__((sda));
extern int D_001B1628[] __attribute__((sda));

void func_0027D098(fn_t callback, int argument) {
    int index = D_001B1638[0];
    if (index < 4) {
        D_001B1618[index] = callback;
        D_001B1628[index] = argument;
        D_001B1638[0] = index + 1;
    }
}

/* shared native body of family 489bf28ebf58470c */
  /* argument table        */

void func_0027D0E8(void) {
    int i;
    for (i = 0; i < D_L02_001B3078; i++) {
        D_L02_001B3058[i](D_L02_001B3068[i]);
    }
}

/* Defined in 0027D160-g8.c. */

/* Defined in 0027D330-g8.c. */

extern int D_L00_001BCAF4;

extern unsigned char D_001A7BB1 __attribute__((sda));

extern float func_00283180(float);

extern int func_00283D38(float, int, int);

extern unsigned char *func_00288FB8(int);

extern int func_0027FB40(int, int, long, unsigned char *, int);

void func_0027D4B8(void)
{
    int y;
    long style;
    unsigned char *text;
    float f;
    int v;

    y = 0x148;
    if (D_001A7BB1) {
        y = 0x17C;
    }
    v = D_L00_001BCAF4;
    f = (float)(v % 100) * 0.02f - 1.0f;
    if (f < -1.0f) {
        f = -1.0f;
    }
    if (1.0f < f) {
        f = 1.0f;
    }
    f = func_00283180(f * 3.14159274f);
    f = f + 1.0f;
    style = func_00283D38(f * 0.5f, 0x7FE0E0E0, 0x5FF0C070);
    text = func_00288FB8(0x2F20);
    func_0027FB40(0x5A, y, style, text, -1);
}

/* Subtitle layout and window path adapted from OpenRAC/rac1-decomp src/game/draw.c's
 * draw_subtitles (GPL-3.0). D_001A7340 is RAC1's g_screen_extent: retail reads its
 * second word as an offset from this base, a two-word load that reorg leaves out of
 * the delay slot. Retail reads the language byte twice, so it is declared volatile. */
typedef struct { short start, end, text[6]; } SubtitleRecord;
typedef struct { char pad[0x34]; int time; char gap[0x14]; unsigned char *subs; } SubtitleState;
extern SubtitleState D_001B8840;
extern volatile unsigned char D_001A7BB4[] __attribute__((sda));
extern unsigned char D_001A7B96[] __attribute__((sda));
extern int D_001A7340[] __attribute__((sda));
extern unsigned char D_001A8998[];
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_00280200(unsigned short *, unsigned long, unsigned char *, int);
extern void func_0027F5B8(int, int, unsigned long, unsigned char *, int);
extern unsigned int func_001157AC(unsigned char *);
extern void func_0027EB88(int, int, int, int, int, int);

void func_0027D5C0(void)
{
    SubtitleRecord *p;
    int idx;
    if (!D_001B8840.subs) return;
    idx = 0;
    if ((unsigned int)(D_001A7BB4[0] - 2) < 4) idx = D_001A7BB4[0] - 1;
    for (p = (SubtitleRecord *)D_001B8840.subs; p->start >= 0; ++p) {
        if (D_001B8840.time < p->start) continue;
        if (p->end < D_001B8840.time) continue;
        if (!D_001A7B96[0] && D_001B8840.subs[p->text[idx]] != '*') continue;
        if (D_001B8840.subs[p->text[idx]] == '*') {
            int y = 0x40;
            int alpha = 0xB0000000;
            unsigned char *str;
            if (D_001B8840.subs[p->text[idx] + 1] != '*') y = D_001A7340[1] - 0xC8;
            else if (D_001A7BB1) y = 0x18;
            if (p->end - D_001B8840.time < 0x12)
                alpha = (int)(p->end - (long)(D_001B8840.time - 1)) << 27;
            else if (D_001B8840.time - p->start < 0x12)
                alpha = (int)(D_001B8840.time - (long)(p->start - 1)) << 27;
            str = D_001B8840.subs + p->text[idx];
            if (str[1] != '*')
                func_0027FB40(0x100, 0xD0, alpha | 0xE0E0E0, str, -1);
            else
                func_0027F5B8(0x20, y, alpha | 0xE0E0E0, str, -1);
        } else {
            unsigned short win[16];
            short w, h;
            int hw, hh;
            int extent = D_001A7340[1];
            func_002802E0(win, 0xC8, 0x1A4, 0x28, 0x1D8, 0x100,
                          D_001A7BB1 ? extent - 0x36 : extent - 0x64, 0x12, 7);
            func_00280200(win, 0x80B0B0B0UL, &D_001B8840.subs[p->text[idx]], -1);
            win[5] -= 4;
            w = win[6];
            h = win[7];
            hh = (h >> 1) + 5;
            hw = (w >> 1) + 10;
            if ((short)win[5] + hh > D_001A7340[1] - 0x14)
                win[5] = D_001A7340[1] - ((h >> 1) + 0x19);
            func_0027EB88((short)win[5] - hh, (short)win[5] + hh, 0x100 - hw, 0x100 + hw, 0x60, 0x40404);
            win[9] &= ~4;
            if (func_001157AC(&D_001B8840.subs[p->text[idx]]) < 0x96)
                func_00280200(win, 0x80B0B0B0UL, &D_001B8840.subs[p->text[idx]], -1);
            else
                func_00280200(win, 0x80B0B0B0UL, D_001A8998, -1);
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
void func_0027E1A0(float x, float y, float w, float h, int u, int v, int uw, int vh,
                   const unsigned int *rgba, unsigned long tex)
{
    int x0 = func_00283CF0(x * 16.0f) + D_001A7340[4] - 8;
    int x1 = func_00283CF0((x + w) * 16.0f) + D_001A7340[4] - 8;
    int y0 = func_00283CF0(y * 16.0f) + D_001A7340[5] - 8;
    int y1 = func_00283CF0((y + h) * 16.0f) + D_001A7340[5] - 8;
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
    D_001B22A8.tag->tag = 0x10000009;
    D_001B22A8.tag->addr = 0;
    D_001B22A8.tag->vif0 = 0;
    D_001B22A8.tag->vif1 = 0x50000009;
    wide_u = u;
    max_u = ((long)ub << 14) | 0xA;
    min_u = (wide_u << 4) | max_u;
    min_v = min_u | ((long)v << 24);
    vb = v + vh;
    clamp = min_v | ((long)vb << 34);
    header = D_001B22A8.tag;
    D_001B22A8.tag = header + 1;
    *(long *)(header + 1) = 0x0400000000008001;
    *(long *)&D_001B22A8.tag->vif0 = 0x8531531531531068;
    tag = D_001B22A8.tag;
    D_001B22A8.tag = tag + 1;
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
    D_001B22A8.bytes += 0x80;
}


/* Adapted from OpenRAC/rac1-decomp src/game/draw.c's append_rotated_sprite_quad,
 * itself adapted from Lombyte src/rendering/append_rotated_sprite_quad.c
 * (GPL-3.0). RAC2 ends the packet with a zero word. */
void func_0027E4A8(float center_x, float center_y, float quad_width, float quad_height,
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
    vertical_edge.x = quad_height * func_00283198(angle);
    vertical_edge.y = quad_height * func_00283180(angle);
    horizontal_edge.x = quad_width * func_00283180(angle);
    horizontal_edge.y = -quad_width * func_00283198(angle);
    inverse_pivot_u = 1.0f - pivot_u;
    func_00282D30(&temporary, &vertical_edge, inverse_pivot_v);
    func_00282CC0(&top_left, &center, &temporary);
    func_00282D30(&temporary, &horizontal_edge, inverse_pivot_u);
    func_00282CF0(&top_left, &top_left, &temporary);
    func_00282D30(&temporary, &vertical_edge, inverse_pivot_v);
    func_00282CC0(&top_right, &center, &temporary);
    func_00282D30(&temporary, &horizontal_edge, pivot_u);
    func_00282CC0(&top_right, &top_right, &temporary);
    func_00282D30(&temporary, &vertical_edge, pivot_v);
    func_00282CF0(&bottom_left, &center, &temporary);
    func_00282D30(&temporary, &horizontal_edge, inverse_pivot_u);
    func_00282CF0(&bottom_left, &bottom_left, &temporary);
    func_00282D30(&temporary, &vertical_edge, pivot_v);
    func_00282CF0(&bottom_right, &center, &temporary);
    func_00282D30(&temporary, &horizontal_edge, pivot_u);
    func_00282CC0(&bottom_right, &bottom_right, &temporary);
    D_001B22A8.tag->tag = 0x10000007;
    D_001B22A8.tag->addr = 0;
    D_001B22A8.tag->vif0 = 0;
    D_001B22A8.tag->vif1 = 0x50000007;
    tag = D_001B22A8.tag;
    packet_words = (unsigned long *)(tag + 1);
    D_001B22A8.tag = tag + 1;
    packet_words[0] = 0xB400000000008001;
    packet_words[1] = 0x53535353106;
    packet_words[2] = texture_tex0;
    packet_words[3] = 0x154;
    packet_words[4] = color;
    packet_words[5] = texture_left | texture_top;
    packet_words[6] =
        (func_00283CF0(top_left.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(func_00283CF0(top_left.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[7] = texture_right | texture_top;
    packet_words[8] =
        (func_00283CF0(top_right.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(func_00283CF0(top_right.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[9] = texture_left | texture_bottom;
    packet_words[10] =
        (func_00283CF0(bottom_left.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(func_00283CF0(bottom_left.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[11] = texture_right | texture_bottom;
    packet_words[12] =
        (func_00283CF0(bottom_right.x * 16.0f) + Ff67aa9df_D_001A7350 - 8) |
        ((unsigned long)(func_00283CF0(bottom_right.y * 16.0f) + Ff67aa9df_D_001A7354 - 8) << 16) |
        ((unsigned long)z_and_fog << 32);
    packet_words[13] = 0;
    D_001B22A8.tag = (QuadDmaTag *)((unsigned char *)D_001B22A8.tag + 0x70);
}


/* Defined in 0027E920.c. */

/* Defined in 0027EA28.c. */

void func_0027EAE8(int i0, int i1, int i2, int i3, int tag, void *x)
{
    long long v[4];

    v[0] = (((i0 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[1] = (((i2 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[2] = (((i0 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[3] = (((i2 << 4) + Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    func_0027EA28(v, x);
}

extern void func_0027DE50(int a, int b, int c, int d, unsigned long e);

void func_0027EB88(int x, int y, int z, int w, int hi, int lo)
{
    int c = (hi << 24) | lo;

    func_0027DE50(x, y, z, w, c);
    func_0027DE50(x + 1, y - 1, z - 2, z, c);
    func_0027DE50(x + 2, y - 2, z - 3, z - 2, c);
    func_0027DE50(x + 4, y - 4, z - 4, z - 3, c);
    func_0027DE50(x + 1, y - 1, w, w + 2, c);
    func_0027DE50(x + 2, y - 2, w + 2, w + 3, c);
    func_0027DE50(x + 4, y - 4, w + 3, w + 4, c);
}

extern void func_0027DE50(int a, int b, int c, int d, unsigned long e);

void func_0027ECC8(int x, int y, int z, int w, int v)
{
    int c = (v & 0xFF000000) | 4;

    func_0027DE50(x, y, z, w, c);
    func_0027DE50(x - 1, x + 1, z + 3, w + 5, v);
    func_0027DE50(x - 3, x - 5, z - 1, w - 3, v);
    func_0027DE50(x - 5, y - 3, z - 1, z + 1, v);
    func_0027DE50(x + 3, y + 1, z - 3, z - 5, v);
    func_0027DE50(y - 1, y + 1, z - 3, w - 3, v);
    func_0027DE50(y + 3, y + 5, z + 3, w + 1, v);
    func_0027DE50(x + 3, y + 3, w - 1, w + 1, v);
    func_0027DE50(x + 1, y - 3, w + 3, w + 5, v);
}


/* Defined in 0027EE58.c. */
