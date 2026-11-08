#include "common.h"

/* func_L03_003E3A00 draws the node puzzle's overlay: the route walked so far, a marker from the
   current node towards each neighbour already in the visited list, two labels, a pulsing
   progress bar, a column of cells, then four lines of text.
   A unit of its own: -G8 for the $gp data, -g for the nop pair before div.s (+0x464), and
   -frac2-gcse-unsplit-edges, without which PRE's copy of the node table's %hi at the
   visited-list scan's entry counts at loop depth 3 (refs 14 instead of 12): the %hi then
   outranks the node index in global allocation and takes $a3 instead of $t0 (+0xF8). */

typedef struct { int x[4]; } Vec;
typedef struct { f32 x, y, z, w; } PuzzleNode;
typedef struct { f32 m[12]; } Matrix;

typedef struct {
    u8 route[16];
    u8 pad10[0x10];
    u8 path[16];
    u8 pad30[0x10];
    u8 visited[6];
    u8 pad46[0xA];
    s16 node;
    u8 pad52[6];
    float phase;
    s16 previous;
    s16 count;
    u8 pad60[2];
    s16 mode;
    u8 pad64[4];
    s16 amount;
} PuzzleState;

extern int D_L03_001B0B50 __attribute__((sda));
extern int D_L03_001B0B58 __attribute__((sda));
extern u32 D_L03_001B0B84 __attribute__((sda));
extern u32 D_L03_001B0B88 __attribute__((sda));
extern u32 D_L03_001B0B8C __attribute__((sda));
extern u32 D_L03_001B0B94 __attribute__((sda));
extern int D_L03_001B0B98 __attribute__((sda));
extern int D_L03_001B0BA8 __attribute__((sda));
extern int D_L03_001B0BB8 __attribute__((sda));
extern float D_L03_001B0BC8 __attribute__((sda));
extern float D_L03_001B0BCC __attribute__((sda));
extern float D_L03_001B0BD0 __attribute__((sda));
extern float D_L03_001B0BD4 __attribute__((sda));
extern float D_L03_001B0BD8[8] __attribute__((sda, section(".sdata")));
extern float D_L03_001B3284[] __attribute__((sda));
extern float D_L03_001B3284_1 __attribute__((sda));
extern PuzzleNode D_L03_0029BBF0[14];
extern int D_0024A7B0[14][6];
extern u8 *D_L03_001A904C;
extern int D_L03_001B2548;
extern int D_L03_001B3280;
/* Absolute views of the cell colours, the bar box and the cell box, whose first words are read
   through $gp. */
extern int D_L03_001B0B98_1[] MACRO_ADDR;
extern int D_L03_001B0BA8_1[] MACRO_ADDR;
extern int D_L03_001B0BB8_1[] MACRO_ADDR;
extern Vec D_L03_001B0BF8, D_L03_001B0C08;
extern float D_L03_001B0BDC[] MACRO_ADDR;
extern char D_L03_001B0C18[];

extern void func_L03_003E4148(u8 *, u32, u32, void *, void *, float, int);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_00336D50(void *, int);
extern void func_00300A00(char *, u32, float, float, float, float, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, u64, char *, int);

/* A size scaled for the display and rounded (hud_size, as in src/levels/08_tabora/
   L08_0041D808-g8.c): scaled_coord's test in its float form, on the display mode its caller
   reads, compared with the 1 of this function's own mode test. The test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int hud_size(int mode, float value, float scale, float half)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == 1)
        scaled = 1.0f;
    return result;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c). The display-mode test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A label's y coordinate (a text line or a sprite) scaled for the display and rounded to a whole
   pixel (label_y, as in src/levels/08_tabora/L08_0041D808-g8.c). Its display-mode and handle tests
   do not change the result: flow deletes them after allocation. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L03_003E3A00(u8 *p)
{
    PuzzleState *q = *(PuzzleState **)(p + 0x68);
    int color, i;
    float a, b, half, t;

    {
        int i, j;
        PuzzleNode tip, axis;
        Matrix rotation;

        if (q->mode == D_L03_001B0B50)
            color = D_L03_001B0B88;
        else
            color = D_L03_001B0B84;
        i = 0;
        if (q->route[1] != 255)
            do {
                j = i + 1;
                func_L03_003E4148(p, color, color, &D_L03_0029BBF0[q->route[i]],
                                  &D_L03_0029BBF0[q->route[j]], q->phase, D_L03_001B0B94);
                i = j;
                if (i >= 15)
                    break;
            } while (q->route[i + 1] != 255);

        {
            int i, j, k, found;

            for (i = 0; i < 6; i++) {
                k = D_0024A7B0[q->node][i];
                if (k == q->previous || k == -1)
                    continue;
                if (q->mode == D_L03_001B0B50 && k == q->path[1])
                    continue;
                found = 0;
                for (j = 0; j < 6 && q->visited[j] != 255; j++)
                    if (q->visited[j] == k) {
                        found = 1;
                        break;
                    }
                func_00282DD8(&axis, &D_L03_0029BBF0[q->node], &D_L03_0029BBF0[k]);
                func_002ACE78(&axis, &axis, 0.17453294992446899f);
                func_00283958(&axis, &rotation);
                func_00283098(&tip, &D_L03_0029BBF0[q->node], &rotation);
                func_00282F20(&tip, &tip, 1.0f);
                if (found)
                    func_L03_003E4148(p, D_L03_001B0B8C & 0xFFFFFF, D_L03_001B0B8C, &tip,
                                      &D_L03_0029BBF0[q->node], -q->phase, 0);
            }
        }
    }
    if (D_L03_001A904C) {
        char *s;
        int y, entry = 0x8710;
        float z, half;

        half = 0.5f;
        s = func_00336D50(D_L03_001A904C + entry, 0xCB);
        y = label_y(s, D_L03_001B0BCC, D_L03_001B3284[0], half, 1);
        z = 0.0f;
        func_00300A00(s, 0x60442D00, D_L03_001B0BC8, (float)y, D_L03_001B0BD0, D_L03_001B0BD4, z);
        s = func_00336D50(D_L03_001A904C + entry, 0xCC);
        y = label_y(s, D_L03_001B0BCC, D_L03_001B3284[0], half, 1);
        func_00300A00(s, 0x55F0C070, D_L03_001B0BC8, (float)y, D_L03_001B0BD0, D_L03_001B0BD4, z);
    }
    half = 0.5f;
    {
        int x, left, top, right, bottom;
        int pulse;

        pulse = func_00283D38(0x80F0C070, 0x40F0C070,
                          func_00283198(func_00283CE0(D_L03_001B2548 % 60) * 0.10471976548433304f
                                        - 3.14159274f) * half + half);
        a = func_00283CE0(q->amount);
        b = func_00283CE0(D_L03_001B0B58);
        left = D_L03_001B0BA8 + 2;
        x = func_00283CF0((float)(D_L03_001B0BA8_1[1] - D_L03_001B0BA8_1[3] - 4) * a / b
                          + (float)(D_L03_001B0BA8_1[3] - 2));
        t = D_L03_001B3284[0];
        top = scaled_coord(x, t, half, 1);
        right = D_L03_001B0BA8_1[2] - 2;
        bottom = scaled_coord(D_L03_001B0BA8_1[3] - 2, t, half, 1);
        func_0028FC48(left, top, right, bottom, pulse, 0);
    }
    {
        int x, end, top, bottom, left, right;
        float step, fx;

        a = func_00283CE0(D_L03_001B0BB8_1[1] - D_L03_001B0BB8_1[3]);
        b = func_00283CE0(D_L03_001B0B50);
        step = a / b;
        for (i = 0; i < D_L03_001B0B50; i++) {
            float scale;

            x = func_00283CF0((float)D_L03_001B0BB8_1[3] + (float)i * step);
            fx = (float)x;
            end = func_00283CF0(fx + step + 3.0f);
            scale = D_L03_001B3284_1;
            if (i >= q->count) {
                bottom = scaled_coord(end, scale, half, 1);
                top = hud_size(D_L03_001B3280, fx, scale, half);
                func_0028FC48(D_L03_001B0BB8, bottom, D_L03_001B0BB8_1[2], top, D_L03_001B0B98_1[2], 0);
                {
                    float t;

                    left = D_L03_001B0BB8 + 2;
                    t = D_L03_001B3284[0];
                    bottom = scaled_coord(end + 2, t, half, 1);
                    right = D_L03_001B0BB8_1[2] - 2;
                    top = scaled_coord(x - 2, t, half, 1);
                    func_0028FC48(left, bottom, right, top, D_L03_001B0B98, 0);
                }
            } else {
                bottom = scaled_coord(end, scale, half, 1);
                top = hud_size(D_L03_001B3280, fx, scale, half);
                func_0028FC48(D_L03_001B0BB8, bottom, D_L03_001B0BB8_1[2], top, D_L03_001B0B98_1[1], 0);
            }
        }
    }
    {
        int i, x, y;
        Vec ids, offs;
        char text[128];

        ids = D_L03_001B0BF8;
        offs = D_L03_001B0C08;
        for (i = 0; i < 4; i++) {
            float a, offset;

            func_00115DA8(text, D_L03_001B0C18, func_00288FB8(ids.x[i]));
            x = func_00283CF0(D_L03_001B0BD8[i * 2]);
            offset = (float)offs.x[i];
            a = D_L03_001B0BDC[i * 2] * D_L03_001B3284[0] + 0.5f;
            if (D_L03_001B3280 == 1)
                y = (int)(a + offset);
            else
                y = (int)a;
            y = func_00283CF0((float)y);
            func_0027FB40(x, y, 0x80808080, text, 128);
        }
    }
}
