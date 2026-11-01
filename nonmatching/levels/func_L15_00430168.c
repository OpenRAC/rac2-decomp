/* func_L15_00430168: HUD panel. Flags tried: -O2 -G8 -ffunction-sections. 1072/1064 bytes.
   Control flow and tables read right; float registers rotated (alpha is f20 in retail), and
   retail keeps the constant 1 in s0, s2 across calls ahead of each D_L15_001B2E80 test. */
#include "common.h"
extern int D_001A7340;
extern unsigned char D_001A7A0A;
extern char *D_L15_001A904C;
extern int D_L15_001B15C8 __attribute__((sda));
extern int D_L15_001B1520[] __attribute__((sda));
extern int D_L15_001B15D8[][3] __attribute__((sda));
extern int D_L15_001B2E80;
extern float D_L15_001B2E84;
extern int D_L15_001B36A4;
extern unsigned int func_001157AC(const char *);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027F5B8(int, int, unsigned long long, char *, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern char *func_00288FB8(int);
extern void func_00300968(char *, int, float, float, float, float);
extern char *func_00336D50(char *, int);
extern void func_L05_00303000(int, int, int, int, unsigned long long, char *, int);

int func_L15_00430168(void)
{
    char buf[0x80];
    float alpha = func_00283CE0(D_001A7340) * 0.5f;

    if (D_L15_001A904C != 0) {
        char *text;
        int shade, x, n;
        float y;

        text = func_00336D50(D_L15_001A904C + 0x8710, 0x45);
        y = (int)(D_L15_001B2E84 * 200.0f + 0.5f);
        func_00300968(text, 0x60442D00, alpha, y, 1.0f, 0.0f);
        text = func_00336D50(D_L15_001A904C + 0x8710, 0x44);
        y = (int)(D_L15_001B2E84 * 200.0f + 0.5f);
        func_00300968(text, 0x55F0C070, alpha, y, 1.0f, 0.0f);
        func_00115DA8(buf, func_00288FB8(0x2F72), D_L15_001B15C8 + 1);
        text = func_00288FB8(0x2F93);
        shade = func_00283CF0(alpha);
        y = D_L15_001B2E84 * 46.0f + 0.5f;
        if (D_L15_001B2E80 == 1)
            x = y + -2.0f;
        else
            x = y;
        func_0027FB40(shade, x, 0x80F0F0F0ULL, text, func_001157AC(text));
        text = func_00288FB8(0x31CB);
        x = D_L15_001B2E84 * 131.0f + 0.5f;
        func_L05_00303000(0x75, x, 0x118, 0x190, 0x80F0F0F0ULL, text, func_001157AC(text));
        n = D_L15_001B1520[D_L15_001B36A4] - 1;
        if (n >= 3)
            n = 2;
        n = D_L15_001B15D8[D_L15_001B36A4][n];
        if (D_001A7A0A != 0)
            n *= 10;
        if (n == 0)
            func_00115DA8(buf, func_00288FB8(0x11FF));
        else
            func_00115DA8(buf, func_00288FB8(0x2FC6), n);
        x = D_L15_001B2E84 * 210.0f + 0.5f;
        func_L05_00303000(0x75, x, 0x118, 0x190, 0x80F0F0F0ULL, buf, func_001157AC(buf));
        y = D_L15_001B2E84 * 294.0f + 0.5f;
        if (D_L15_001B2E80 == 1)
            x = y + 3.0f;
        else
            x = y;
        func_0027F5B8(0x75, x, 0x80F0F0F0ULL, func_00288FB8(0x31CC), -1);
        y = D_L15_001B2E84 * 294.0f + 0.5f;
        if (D_L15_001B2E80 == 1)
            x = y + 3.0f;
        else
            x = y;
        func_0027F5B8(0x112, x, 0x80F0F0F0ULL, func_00288FB8(0x31CD), -1);
    }
    return 1;
}
