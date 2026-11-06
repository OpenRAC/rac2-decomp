#include "include_asm.h"

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern PanelColors D_L00_001AD768;
extern int D_L00_001B1BB8[] __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
/* PAL-only mode word and scale of the top counter, 0x120 and 0x124 past D_L00_001B25E0; the shared
   D_L00_001B2700 is another variable in levels 5, 10, 15 and 25. */
extern int ref_PAL_L00_0037A4B0_00 __attribute__((sda));
extern float ref_PAL_L00_0037A4B0_01 __attribute__((sda));
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern int func_PAL_002802D8(int, int, unsigned long long, unsigned char *, int, int, float);
extern unsigned char D_001A7BB4 __attribute__((sda));
extern void func_0028E868(int, int, int, int, int, int);

extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int func_00288FB8(int);
extern void func_0027FA10(int, int, unsigned long long, unsigned char *, int);
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern void func_PAL_002FAB40(char *, int);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);
extern unsigned int func_L00_002F3DD0(int);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);

void func_PAL_L00_00379EF0(void) {
    unsigned int colors[4];
    char text[256];
    char *model = D_L00_0022F7C0;
    int price = *(int *)(model + 0x144 + *(int *)(model + 0x80) * 12);
    int y;
    unsigned long long color;
    if (price > 0) {
        func_0027FA10(140, (int)(D_L00_001B25E0 * 290.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)func_00288FB8(0x114E), -1);
        colors[0] = 0x60F0F0B0;
        colors[1] = 0x60F0F0B0;
        colors[2] = 0x60F0F0B0;
        colors[3] = 0x60F0F0B0;
        func_0028EA58(func_0028E588(0x7567, 0), 156,
                      (int)(D_L00_001B25E0 * 290.0f + 0.5f), 16,
                      (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
        func_PAL_002FAB40(text, price);
        color = 0x80F0F0F0ULL;
        if (price > D_001A79F8) color = 0x802020F0ULL;
        func_0027F5B8(176, (int)(D_L00_001B25E0 * 290.0f + 0.5f), color, (unsigned char *)text, -1);
        y = (int)(D_L00_001B25E0 * 363.0f + 0.5f) + 7;
        if (!D_001A7B90) y -= 7;
        func_0027FB40(256, y, 0x80F0F0F0ULL,
            (unsigned char *)func_00288FB8(func_L00_002F3DD0(*(int *)(model + 0x148 + *(int *)(model + 0x80) * 12))), -1);
    } else {
        y = (int)(D_L00_001B25E0 * 363.0f + 0.5f) + 7;
        if (!D_001A7B90) y -= 7;
        func_0027FB40(256, y, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x109C), -1);
    }
}



/* func_PAL_L00_0037A4B0, the PAL copy of func_L00_003778F0: the same C, where the top counter and
   its icon take PAL's vertical adjustments and the label text id becomes 0x10A0. */
void func_PAL_L00_0037A4B0(void) {
    PanelColors colors;
    char text[256];
    char *model = D_L00_0022F7C0;
    int index = *(int *)(model + 0x80);
    float v;
    int y;
    int h;
    int icon;
    int mode;
    colors = D_L00_001AD768;
    D_L00_001B1BB8[1] = 0;
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  -192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  -192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    func_0027FA10(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)func_00288FB8(0x10a0), -1);
    func_PAL_002FAB40(text, ((ShopModel *)model)->items[index].price);
    func_0027F5B8(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    func_0027FB40(D_001A7340 >> 1, (int)(D_L00_001B25E0 * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  ((ShopModel *)model)->items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    func_PAL_002FAB40(text, D_001A79FC);
    v = ref_PAL_L00_0037A4B0_01 * 17.0f + 0.5f;
    func_0027F980(444, ref_PAL_L00_0037A4B0_00 == 1 ? (int)(v + -4.0f) : (int)v, 0x80FFFFFFULL, (unsigned char *)text, -1);
    icon = func_0028E588(0xEAA2, 3);
    mode = D_001A7B90;
    y = (int)(D_L00_001B25E0 * 15.0f + 0.5f);
    h = (int)(D_L00_001B25E0 * 32.0f + 0.5f);
    func_0028EA58(icon, 458, mode ? y - 3 : y, 32, mode ? h - 2 : h, colors.word);
}




/* func_PAL_L00_0037B1A0, the PAL copy of func_L00_00378578: the same panel, with its prompts drawn
   through func_PAL_002802D8 at scale 0.7 and moved up when D_001A7B90 is set. Retail really tests
   the language byte and carries both arms in full, although they draw the same two strings. */
void func_PAL_L00_0037B1A0(void) {
    UpgradeModel *model = (UpgradeModel *)D_L00_0022F7C0;
    int index = model->index;
    int mode;
    int y;
    if (model->state != 0) {
        if (model->cells[index].price <= D_001A79FC) {
            func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x113B), -1, 82, 0.7f);
            func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x1138), -1, 82, 0.7f);
        } else {
            int top;
            mode = D_001A7B90;
            y = (int)(D_L00_001B25E0 * 214.0f + 0.5f);
            top = mode ? y - 11 : y;
            func_PAL_002802D8(444, top, 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x1124), -1, 82, 0.7f);
        }
    } else if (D_001A7BB4 == 2) {
        func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0x1125), -1, 82, 0.7f);
        func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0xB60), -1, 82, 0.7f);
    } else {
        func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0x1125), -1, 82, 0.7f);
        func_PAL_002802D8(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0xB60), -1, 82, 0.7f);
    }
    {
        int icon = func_0028E588(0xEAA8, 1);
        mode = D_001A7B90;
        y = (int)(D_L00_001B25E0 * 64.0f + 0.5f);
        func_0028E868(icon, 402, mode ? y - 3 : y, 89, (int)(D_L00_001B25E0 * 115.0f + 0.5f), 64);
    }
    func_0027FB40(445, (int)(D_L00_001B25E0 * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)func_00288FB8(0x13DB), -1);
    func_0027FB40(445, (int)(D_L00_001B25E0 * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)func_00288FB8(0x13DC), -1);
}
