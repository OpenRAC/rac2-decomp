#include "include_asm.h"

extern char *D_001A8CFC;
extern int D_001A7340, D_001A7908;
extern int D_001ABA70 __attribute__((sda));
extern float D_001B23A8;
extern char D_001AB9C0[], D_001AB9F8[];
extern void func_0027C540(long);
extern void func_0027C660(void);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern void func_0027F538(int, int, unsigned long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);

int func_PAL_002D3850(void)
{
    char text[64];
    char *heading_format;
    char *option_format;
    float depth;

    func_0027C540(0);
    depth = 0.56f;
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0x8B), 0x60442D00,
                 (float)(D_001A7340 / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0x8C), 0x55F0C070,
                 (float)(D_001A7340 / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0x8D), 0x55F0C070,
                 (float)(D_001A7340 / 2), (float)D_001ABA70,
                 1.0f, D_001B23A8, depth);
    func_0027FAA8(D_001A7340 / 2, 65, 0x80F0F0F0UL, func_00288FB8(0x1408), -1);
    func_0027FAA8(D_001A7340 / 2, 321, 0x80F0F0F0UL, func_00288FB8(0xB5F), -1);
    func_0027FAA8(D_001A7340 / 2, 346, 0x80F0F0F0UL, func_00288FB8(0xB60), -1);

    heading_format = D_001AB9C0;
    func_00115DA8(text, heading_format, func_00288FB8(0x1408));
    func_0027F538(134, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    option_format = D_001AB9F8;
    func_00115DA8(text, option_format, func_00288FB8(D_001A7908 ? 0xBD7 : 0xBD8));
    func_0027FAA8(349, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    func_0027C660();
    return 0;
}
