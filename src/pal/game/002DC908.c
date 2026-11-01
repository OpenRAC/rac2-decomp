#include "include_asm.h"

#include "common.h"
typedef struct { short s[12]; } PromptTextBox;
typedef struct { int words[4]; } PromptCornerColors;
typedef struct { int left, top, right, bottom; } PromptBounds;
typedef struct {
    char reserved00[0x18];
    int left, top, width, height;
} PromptMenuPrefix;
extern int D_001F2924;
extern unsigned char D_001ABB78[];
extern int D_001B1E10 SDATA(D_001B1E10) __attribute__((sda));
extern int D_001AA43C SDATA(D_001AA43C) __attribute__((sda));
extern PromptCornerColors D_001B1E00[] SDATA(D_001B1E00) __attribute__((sda));
extern PromptBounds D_001ABB80[] MACRO_ADDR;
extern PromptBounds D_001ABB80_gp[] SDATA(D_001ABB80) __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C540(int);
extern int func_00288FB8(int);
extern void func_00280200(unsigned short *, unsigned long, unsigned char *, int);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern void func_0027C660(void);

int func_PAL_002DC908(PromptMenuPrefix *menu)
{
    unsigned char *text;
    int kind;
    func_002FC560(0x42, 0x44ULL);
    func_002FC560(0x47, 0x2004BULL);
    func_0027C540(0);
    text = D_001ABB78;
    kind = D_001F2924;
    switch (kind) {
    case 0:
    case 1:
    case 2:
        text = (unsigned char *)func_00288FB8(0xC0A);
        break;
    case 3:
        text = (unsigned char *)func_00288FB8(0xC0D);
        break;
    }
    {
        PromptTextBox box = {{menu->top, menu->top + menu->height + 1,
                              menu->left, menu->left + menu->width + 1,
                              (menu->left + menu->width) >> 1, menu->top + 5,
                              menu->width - 5, menu->height - 5, 16, 5}};
        if (!D_001B1E10) {
            D_001B1E10 = 1;
            D_001B1E00[0] = (PromptCornerColors){{D_001AA43C, D_001AA43C, D_001AA43C, D_001AA43C}};
        }
        func_00280200((unsigned short *)&box, 0x80000000UL, text, -1);
        box.s[5] = (menu->height - box.s[7]) >> 1;
        box.s[9] ^= 4;
        func_00280200((unsigned short *)&box, 0x80000000UL, text, -1);
        {
            int top = D_001ABB80[0].top;
            int bottom = D_001ABB80[0].bottom;
            int right = D_001ABB80[0].right;
            func_0027EAE8(D_001ABB80_gp[0].left, top, right, bottom, 0, &D_001B1E00[0]);
        }
        box.s[0]--;
        box.s[1]--;
        box.s[2]--;
        box.s[3]--;
        box.s[4]--;
        box.s[5]--;
        func_00280200((unsigned short *)&box, 0x80F0F0F0UL, text, -1);
    }
    func_0027C660();
    return 2;
}

