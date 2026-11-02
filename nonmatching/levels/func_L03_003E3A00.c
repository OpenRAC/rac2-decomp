/* func_L03_003E3A00: near miss, 1856/1860 bytes, 0 of 8 places (USA v1.01, 1 November 2026).

   Profile: its own `-g8` unit, `-O2 -G8 -ffunction-sections -g` (-g for the nop pair before
   the div.s). The $gp words are sda; the words retail reads absolute (lui/lw, or lui $at/lwc1
   for the int loaded straight into an FPR) are MACRO_ADDR; the two 16-byte rows copied with
   ldl/ldr are aligned(1).

   The puzzle HUD: the walked path, the open turns from the current node, the button prompts,
   the timer bar, the path-length boxes and the four counters. Calls, constants and data agree
   with retail.
   What differs: allocation. Retail keeps the path record in $s1, the colour in $s2 and the node
   table in $s3, and the first loop's index lives only in $a0 (its successor crosses the call
   in $s0); here they are $s3/$s1/$s4 and the index needs its own saved register. Retail also
   spills &axis (sp + 0x10) to 0xD0 at entry and reuses it as the base of the last loop's row,
   which says the two 16-byte rows overlay the vectors at sp + 0 and sp + 0x10.
   Measured: overlaying them with a union and a `next` variable, 1844 bytes (frame 0x140);
   the same loop as a do-while on `next`, worse. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { f32 x, y, z, w; } PuzzleNode;
/* The path record at +0x68 of the puzzle object (see L03_003E26C8-g8.c). */
typedef struct {
    u8 order[16];
    u8 visited[16];
    u8 path[16];
    u8 facing[16];
    u8 choices[16];
    s16 current;
    s16 next;
    u8 pad54[4];
    f32 width;
    s16 last;
    s16 length;
    s16 maximumLength;
    s16 cursor;
    s16 depth;
    s16 pending;
    s16 timer;
} PuzzlePath;
typedef struct { int value[4]; } Row4;

extern PuzzleNode D_L03_0029BBF0[14];
extern int D_0024A7B0[14][6];
extern int D_L03_001B0B50 __attribute__((sda));
extern int D_L03_001B0B58 __attribute__((sda));
extern unsigned int D_L03_001B0B84 __attribute__((sda));
extern unsigned int D_L03_001B0B88 __attribute__((sda));
extern unsigned int D_L03_001B0B8C __attribute__((sda));
extern int D_L03_001B0B94 __attribute__((sda));
extern unsigned int D_L03_001B0B98 __attribute__((sda));
extern int D_L03_001B0BA8 __attribute__((sda));
extern int D_L03_001B0BB8 __attribute__((sda));
extern float D_L03_001B0BC8 __attribute__((sda));
extern float D_L03_001B0BCC __attribute__((sda));
extern float D_L03_001B0BD0 __attribute__((sda));
extern float D_L03_001B0BD4 __attribute__((sda));
extern float D_L03_001B0BD8[][2] __attribute__((sda));
extern unsigned int D_L03_001B0B9C MACRO_ADDR;
extern unsigned int D_L03_001B0BA0 MACRO_ADDR;
extern int D_L03_001B0BAC MACRO_ADDR;
extern int D_L03_001B0BB0 MACRO_ADDR;
extern int D_L03_001B0BB4 MACRO_ADDR;
extern int D_L03_001B0BBC MACRO_ADDR;
extern int D_L03_001B0BC0 MACRO_ADDR;
extern int D_L03_001B0BC4 MACRO_ADDR;
extern float D_L03_001B0BDC[][2] MACRO_ADDR;
extern Row4 D_L03_001B0BF8 MACRO_ADDR __attribute__((aligned(1)));
extern Row4 D_L03_001B0C08 MACRO_ADDR __attribute__((aligned(1)));
extern char D_L03_001B0C18[] MACRO_ADDR;
extern float D_L03_001B3284 MACRO_ADDR;
extern int D_L03_001B3280 MACRO_ADDR;
extern int D_L03_001A904C MACRO_ADDR;
extern int D_L03_001B2548 MACRO_ADDR;
extern void func_L03_003E4148(u8 *, unsigned int, unsigned int, void *, void *, int, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(float *, float *, float);
extern void func_00283958(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern int func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, unsigned long, char *, int);

/* Draws the puzzle: the walked path between the nodes, the turns still open from the current
   node, the button prompts, the timer bar, the path-length boxes and the four counters. */
void func_L03_003E3A00(u8 *p)
{
    Vector turn;
    Vector axis;
    Vector side;
    Row4 labels;
    Row4 offsets;
    char text[0x80];
    PuzzlePath *q = *(PuzzlePath **)(p + 0x68);
    unsigned int colour;
    int i, j, k, n, found;
    int x, y, top, bottom, bar;
    float scale, step, t;

    if (q->cursor == D_L03_001B0B50) {
        colour = D_L03_001B0B88;
    } else {
        colour = D_L03_001B0B84;
    }
    for (i = 0; q->order[i + 1] != 0xFF; ) {
        func_L03_003E4148(p, colour, colour, &D_L03_0029BBF0[q->order[i]],
                          &D_L03_0029BBF0[q->order[i + 1]], D_L03_001B0B94, q->width);
        if (++i >= 15) {
            break;
        }
    }

    for (j = 0; j < 6; j++) {
        n = D_0024A7B0[q->current][j];
        if (n == q->last || n == -1) {
            continue;
        }
        if (q->cursor == D_L03_001B0B50 && n == q->path[1]) {
            continue;
        }
        found = 0;
        for (k = 0; k < 6 && q->choices[k] != 0xFF; k++) {
            if (q->choices[k] == n) {
                found = 1;
                break;
            }
        }
        func_00282DD8(axis, &D_L03_0029BBF0[q->current], &D_L03_0029BBF0[n]);
        func_002ACE78(axis, axis, 0.17453295f);
        func_00283958(axis, side);
        func_00283098(turn, &D_L03_0029BBF0[q->current], side);
        func_00282F20(turn, turn, 1.0f);
        if (found) {
            func_L03_003E4148(p, D_L03_001B0B8C & 0xFFFFFF, D_L03_001B0B8C, turn,
                              &D_L03_0029BBF0[q->current], 0, -q->width);
        }
    }

    if (D_L03_001A904C != 0) {
        func_00300A00((char *)func_00336D50((char *)(D_L03_001A904C + 0x8710), 0xCB), 0x60442D00,
                      D_L03_001B0BC8, (int)(D_L03_001B0BCC * D_L03_001B3284 + 0.5f), D_L03_001B0BD0,
                      D_L03_001B0BD4, 0.0f);
        func_00300A00((char *)func_00336D50((char *)(D_L03_001A904C + 0x8710), 0xCC), 0x55F0C070,
                      D_L03_001B0BC8, (int)(D_L03_001B0BCC * D_L03_001B3284 + 0.5f), D_L03_001B0BD0,
                      D_L03_001B0BD4, 0.0f);
    }

    t = func_00283CE0(D_L03_001B2548 % 60) * 0.104719765f - 3.1415927f;
    bar = func_00283D38(0x80F0C070, 0x40F0C070, func_00283198(t) * 0.5f + 0.5f);
    scale = func_00283CE0(q->timer) / func_00283CE0(D_L03_001B0B58);
    x = func_00283CF0((float)(D_L03_001B0BAC - D_L03_001B0BB4 - 4) * scale + (float)(D_L03_001B0BB4 - 2));
    func_0028FC48(D_L03_001B0BA8 + 2, (int)((float)x * D_L03_001B3284 + 0.5f), D_L03_001B0BB0 - 2,
                  (int)((float)(D_L03_001B0BB4 - 2) * D_L03_001B3284 + 0.5f), bar, 0);

    step = func_00283CE0(D_L03_001B0BBC - D_L03_001B0BC4) / func_00283CE0(D_L03_001B0B50);
    for (i = 0; i < D_L03_001B0B50; i++) {
        float left;

        top = func_00283CF0((float)D_L03_001B0BC4 + (float)i * step);
        left = (float)top;
        bottom = func_00283CF0(left + step + 3.0f);
        if (i >= q->length) {
            func_0028FC48(D_L03_001B0BB8, (int)((float)bottom * D_L03_001B3284 + 0.5f), D_L03_001B0BC0,
                          (int)(left * D_L03_001B3284 + 0.5f), D_L03_001B0BA0, 0);
            func_0028FC48(D_L03_001B0BB8 + 2, (int)((float)(bottom + 2) * D_L03_001B3284 + 0.5f),
                          D_L03_001B0BC0 - 2, (int)((float)(top - 2) * D_L03_001B3284 + 0.5f),
                          D_L03_001B0B98, 0);
        } else {
            func_0028FC48(D_L03_001B0BB8, (int)((float)bottom * D_L03_001B3284 + 0.5f), D_L03_001B0BC0,
                          (int)(left * D_L03_001B3284 + 0.5f), D_L03_001B0B9C, 0);
        }
    }

    labels = D_L03_001B0BF8;
    offsets = D_L03_001B0C08;
    for (k = 0; k < 4; k++) {
        float v;

        func_00115DA8(text, D_L03_001B0C18, func_00288FB8(labels.value[k]));
        x = func_00283CF0(D_L03_001B0BD8[k][0]);
        v = D_L03_001B0BDC[k][0] * D_L03_001B3284 + 0.5f;
        if (D_L03_001B3280 == 1) {
            v += (float)offsets.value[k];
        }
        y = func_00283CF0((float)(int)v);
        func_0027FB40(x, y, 0x80808080, text, 0x80);
    }
}
