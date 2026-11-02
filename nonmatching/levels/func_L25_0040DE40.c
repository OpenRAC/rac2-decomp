/* func_L25_0040DE40: near miss, 1840/1852 bytes, 0 of 1 place (USA v1.01, 2 November 2026).

   Profile: its own unit, `-O2 -G8 -ffunction-sections`.

   Family F35 (func_L05_00421B98, func_L10_00424CD0, func_L15_00431590, same opcodes): the HUD
   icon pairs and the countdown. This is the func_L05_00421B98 draft (1836/1852 on the current
   compiler, 418 rows) with every icon row written through SCREEN_Y, the vanished-test macro
   func_L10_004227A0's note describes: `dst = (int)scaled; if (D_L05_001B2D80 == 1) scaled +=
   1.0f;`. 1840 bytes and 305 rows. The countdown box keeps its real +1.0f.
   What differs: retail loads the -1/1/0 constants again in each icon block and issues the y
   chain before them, with $a0 = v0 last; here they are shared from the first block. Tried,
   worse: an empty do-while after the test, with or without -malign-loops=2 (389 rows), and a
   statement-expression SCREEN_Y inside the call (304 rows, 1840 bytes; with the do-while 367). */

#include "common.h"

extern char *D_L05_001B13B0 __attribute__((sda));
extern int D_L05_001B354C __attribute__((sda));
extern int D_L05_001B3548 __attribute__((sda));
extern int D_L05_001B1428 __attribute__((sda));
extern int D_L05_001B142C;
extern int D_L05_001B1430 __attribute__((sda));
extern int D_L05_001B1434;
extern int D_L05_001B1438 __attribute__((sda));
extern int D_L05_001B143C;
extern int D_L05_001B1440 __attribute__((sda));
extern int D_L05_001B1444;
extern int D_L05_001A904C;
extern int D_L05_001B2D80;
extern float D_L05_001B2D84;
extern int D_001A79FC;
extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);

#define SCREEN_Y(dst, y0)                          \
    {                                              \
        float scaled = (y0) * D_L05_001B2D84 + 0.5f;   \
        dst = (int)scaled;                         \
        if (D_L05_001B2D80 == 1)                   \
            scaled = scaled + 1.0f;                \
    }

#define DRAW(sprite, color, x0, y0, a, b, c)                               \
    {                                                                      \
        int id_ = func_00336D50(D_L05_001A904C + 0x8710, sprite);          \
        int y_;                                                            \
        SCREEN_Y(y_, (float)(y0));                                         \
        func_00300A00(id_, color, (float)(x0), (float)y_, a, b, c);        \
    }

void func_L25_0040DE40(int first, int second, int third, int fourth)
{
    char text[0x80];
    char *state = *(char **)(D_L05_001B13B0 + 0x68);
    float scale;
    int time;

    if (D_L05_001B354C == 0) {
        D_L05_001B354C = 1;
        D_L05_001B3548 = D_001A79FC;
    }
    if (D_L05_001A904C == 0)
        return;
    if (first) {
        DRAW(0xBD, 0x60442D00, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
        DRAW(0xBE, 0x55F0C070, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
    }
    if (second && D_L05_001B3548 < D_001A79FC) {
        if (func_00282948(state + 0x50) == 0) {
            time = *(int *)(state + 0x50);
            if (time >= 0x123) {
                scale = func_00283CE0(300 - time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                DRAW(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
                DRAW(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
            } else if (time < 10) {
                scale = func_00283CE0(time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                DRAW(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
                DRAW(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
            } else {
                DRAW(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
                DRAW(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
                {
                    unsigned int colors[4] = { 0x8080F0F0, 0x8080F0F0, 0x8080F0F0, 0x8080F0F0 };
                    {
                        int id = func_0028E588(0xEAA2, 3);
                        int x = D_L05_001B1430 - 0x33;
                        float y = (float)(D_L05_001B1434 - 13) * D_L05_001B2D84 + 0.5f;
                        if (D_L05_001B2D80 == 1)
                            y += 1.0f;
                        func_0028EA58(id, x, (int)y, 0x1C, 0x1C, colors);
                    }
                    func_00115DA8(text, "%d", D_001A79FC);
                    func_0027F5B8(D_L05_001B1430 + 5, (int)((float)(D_L05_001B1434 + 2) * D_L05_001B2D84 + 0.5f),
                                  0x80808080ULL, (unsigned char *)text, 0x80);
                }
            }
        } else {
            D_L05_001B3548 = D_001A79FC;
            *(int *)(state + 0x50) = 300;
        }
    }
    if (third) {
        DRAW(0xC1, 0x60442D00, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
        DRAW(0xC2, 0x55F0C070, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
    }
    if (fourth) {
        DRAW(0xC1, 0x60442D00, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
        DRAW(0xC2, 0x55F0C070, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
    }
}
