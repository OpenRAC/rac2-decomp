#include "include_asm.h"



typedef struct { short field[12]; } TextLayout;
typedef struct { int id; int kind; int rest[4]; } ShopEntry;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xB8];
    ShopEntry entries[0];
} PurchaseModel;
typedef struct { char prefix[0x88]; unsigned short price; char rest[0x56]; } ShopClass;
extern unsigned char D_00139568[];
extern char D_L00_00262570[];
extern int D_L00_001B25A8 __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern char D_L00_001AD798[7];
extern char D_L00_001AD6C8[3];
extern void *func_00115484(void *, int, unsigned int);
extern void func_00280200(TextLayout *, unsigned long long, unsigned char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_002F6510(void);
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel D_L00_0022F7C0;
extern float D_L00_001B25E0 __attribute__((sda));
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_00288FB8(int);
extern void func_0027FA10(int, int, unsigned long long, unsigned char *, int);

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
extern PanelColors D_L00_001AD768;
extern int D_L00_001B1BB8[] __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
/* The top counter's mode word and scale: the shared D_L00_001B2700 is another variable in some levels. */
extern int ref_US2_L00_00378C38_00 __attribute__((sda));
extern float ref_US2_L00_00378C38_01 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern void func_002F9BC0(char *, int);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

/* Measured from func_002FAE68: the state it steps and the status block it tests. */
typedef struct { char pad[0x38]; int st; } CardPrompt;
typedef struct {
    char p0[0x8]; int f8;
    char p1[0x8]; int f14;
    char p2[0x4]; int f1C;
    char p3[0x88]; int fA8;
    char p4[0x8]; int fB4;
    char p5[0x4]; int fBC;
    char p6[0x9C]; int f15C;
    char p7[0x4]; int f164;
    int f168;
} CardStatus;
extern void *D_0026DBE0[];
extern CardPrompt D_0021F240;
extern CardStatus D_001393E0;
extern int D_001A7A20 __attribute__((sda));
extern void func_002F88D8(char *);
extern void func_002FADB0(void);

/* func_US2_L00_00378C38, the v2.00 copy of func_L00_003778F0: the same panel, where the top
 * counter's y depends on ref_US2_L00_00378C38_00 and its icon's y and height on D_001A7B90. */
void func_US2_L00_00378C38(void) {
    PanelColors colors;
    char text[256];
    char *model = (char *)&D_L00_0022F7C0;
    int index = *(int *)(model + 0x80);
    float y;
    int icon;
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
                  (unsigned char *)func_00288FB8(0x3022), -1);
    func_002F9BC0(text, D_L00_0022F7C0.items[index].price);
    func_0027F5B8(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    func_0027FB40(D_001A7340 >> 1, (int)(D_L00_001B25E0 * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  D_L00_0022F7C0.items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    func_002F9BC0(text, D_001A79FC);
    y = ref_US2_L00_00378C38_01 * 17.0f + 0.5f;
    func_0027F980(444, ref_US2_L00_00378C38_00 == 1 ? (int)(y + -4.0f) : (int)y, 0x80FFFFFFULL,
                  (unsigned char *)text, -1);
    icon = func_0028E588(0xEAA2, 3);
    func_0028EA58(icon, 458,
                  D_001A7B90 ? (int)(D_L00_001B25E0 * 15.0f + 0.5f) - 3 : (int)(D_L00_001B25E0 * 15.0f + 0.5f),
                  32,
                  D_001A7B90 ? (int)(D_L00_001B25E0 * 32.0f + 0.5f) - 2 : (int)(D_L00_001B25E0 * 32.0f + 0.5f),
                  colors.word);
}




/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern int func_US2_00280440(int, int, unsigned long long, unsigned char *, int, int, float);
extern void func_0028E868(int, int, int, int, int, int);

/* func_US2_L00_00379928, the v2.00 copy of func_L00_00378578: the same panel, with its prompts drawn
 * through func_US2_00280440 at scale 0.7 and moved up when D_001A7B90 is set. */
void func_US2_L00_00379928(void) {
    UpgradeModel *model = (UpgradeModel *)&D_L00_0022F7C0;
    int index = model->index;
    int mode;
    int y;
    if (model->state != 0) {
        if (model->cells[index].price <= D_001A79FC) {
            func_US2_00280440(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x31C7), -1, 82, 0.7f);
            func_US2_00280440(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x31C4), -1, 82, 0.7f);
        } else {
            int top;
            mode = D_001A7B90;
            y = (int)(D_L00_001B25E0 * 214.0f + 0.5f);
            top = mode ? y - 11 : y;
            func_US2_00280440(444, top, 0x80F0F0F0ULL,
                              (unsigned char *)func_00288FB8(0x31B0), -1, 82, 0.7f);
        }
    } else {
        func_US2_00280440(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0x31B1), -1, 82, 0.7f);
        func_US2_00280440(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)func_00288FB8(0x2BE5), -1, 82, 0.7f);
    }
    {
        int icon = func_0028E588(0xEAA8, 1);
        mode = D_001A7B90;
        y = (int)(D_L00_001B25E0 * 64.0f + 0.5f);
        func_0028E868(icon, 402, mode ? y - 3 : y, 89, (int)(D_L00_001B25E0 * 115.0f + 0.5f), 64);
    }
    func_0027FB40(445, (int)(D_L00_001B25E0 * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)func_00288FB8(0x30A8), -1);
    func_0027FB40(445, (int)(D_L00_001B25E0 * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)func_00288FB8(0x30A9), -1);
}

/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */


/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
void func_US2_L00_00379C50(void) {
    TextLayout copy;
    /* This 24-byte workspace becomes the four-color array after drawing text. */
    union { TextLayout layout; unsigned int colors[4]; } seed;
    char text[256];
    PurchaseModel *model = (PurchaseModel *)&D_L00_0022F7C0;
    int index;
    int message;
    unsigned short unit_price;
    if (model->active == 0) return;
    func_00115484(&seed.layout, 0, 24);
    seed.layout.field[0] = 120;
    seed.layout.field[1] = (short)(D_L00_001B25E0 * 200.0f + 0.5f);
    seed.layout.field[2] = 160;
    seed.layout.field[3] = 352;
    seed.layout.field[4] = 256;
    seed.layout.field[5] = (short)(D_L00_001B25E0 * 160.0f + 0.5f);
    seed.layout.field[6] = 184;
    seed.layout.field[7] = (short)(D_L00_001B25E0 * 72.0f + 0.5f);
    seed.layout.field[8] = 16;
    seed.layout.field[9] = 3;
    copy = seed.layout;
    index = model->index;
    if (model->entries[index].kind == 1) {
        int selected_id = model->entries[index].id;
        unit_price = ((ShopClass *)D_L00_00262570)[D_00139568[selected_id]].price;
        if ((int)unit_price <= D_001A79F8) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 12) * D_L00_001B25E0 + 0.5f);
            func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x31B3), -1);
            func_00115DA8(text, D_L00_001AD798, D_L00_001B25A8);
            copy.field[5] = (short)((float)(copy.field[0] + 40) * D_L00_001B25E0 + 0.5f);
            func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)text, -1);
            func_00115DA8(text, D_L00_001AD6C8, (unsigned int)D_L00_001B25A8 *
                ((ShopClass *)D_L00_00262570)[D_00139568[model->entries[model->index].id]].price);
            func_0027FA10(256, (int)(D_L00_001B25E0 * 180.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
            seed.colors[0] = 0x60F0F0B0;
            seed.colors[1] = 0x60F0F0B0;
            seed.colors[2] = 0x60F0F0B0;
            seed.colors[3] = 0x60F0F0B0;
            func_0028EA58(func_0028E588(0x7567, 0), 260, (int)(D_L00_001B25E0 * 180.0f + 0.5f),
                          16, (int)(D_L00_001B25E0 * 16.0f + 0.5f), seed.colors);
            return;
        }
        message = 0x31B4;
    } else {
        if (D_001A79F8 >= func_002F6510()) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 6) * D_L00_001B25E0 + 0.5f);
            message = 0x31B5;
        } else goto no_money;
    }
    func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(message), -1);
    return;
no_money:
    func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x31B4), -1);
}


typedef struct { int price; int rest[2]; } ConfirmRow;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xBC];
    ConfirmRow rows[0];
} ConfirmModel;
extern void *memset(void *, int, unsigned int);

/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
void func_US2_L00_0037A050(void) {
    TextLayout copy;
    TextLayout layout;
    ConfirmModel *model = (ConfirmModel *)&D_L00_0022F7C0;
    int top;
    float scale;
    if (model->active == 0) return;
    memset(&layout, 0, sizeof(layout));
    top = 314;
    scale = D_L00_001B25E0;
    layout.field[0] = (short)(scale * 120.0f + 0.5f);
    layout.field[1] = (short)(scale * top + 0.5f);
    layout.field[2] = top;
    layout.field[3] = 486;
    layout.field[4] = 400;
    layout.field[5] = (short)(scale * 217.0f + 0.5f);
    layout.field[6] = 164;
    layout.field[7] = (short)(scale * 186.0f + 0.5f);
    layout.field[8] = 16;
    layout.field[9] = 3;
    copy = layout;
    if (D_001A79F8 >= model->rows[model->index].price) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x31B5), -1);
    } else {
        func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x31B4), -1);
    }
}




/* func_US2_L00_0037A5D0, the v2.00 copy of func_002FAE68: the same state machine, where the
 * prompts are looked up in the text table. */
void func_US2_L00_0037A5D0(void) {
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    unsigned int rc2_selector = (unsigned int)(D_0021F240.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.f8 == 2) {
            if (D_001393E0.f14 != 0) {
                D_001393E0.f164 = 0x18;
                D_0021F240.st = 3;
                D_001393E0.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (D_0021F240.st != 0) {
            D_0021F240.st = 4;
        } else {
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.f1C == 1) {
                    func_002F88D8((char *)func_00288FB8(0x313A));
                } else if (D_001393E0.f1C >= 3) {
                    func_002F88D8((char *)func_00288FB8(0x3138));
                } else {
                    func_002F88D8((char *)func_00288FB8(0x3139));
                }
            } else {
                func_002F88D8((char *)func_00288FB8(0x3137));
            }
            func_002FADB0();
            if (D_0021F240.st != 0) {
                D_0021F240.st = 4;
            } else {
                D_0021F240.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
            D_001393E0.f164 = 0x18;
            D_001393E0.f168 = 1;
            D_0021F240.st = 5;
            goto rc2_switch_end;
        }
        D_0021F240.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.fBC == 1) {
                    func_002F88D8((char *)func_00288FB8(0x313A));
                } else if (D_001393E0.fBC >= 3) {
                    func_002F88D8((char *)func_00288FB8(0x3138));
                } else {
                    func_002F88D8((char *)func_00288FB8(0x3139));
                }
            } else {
                func_002F88D8((char *)func_00288FB8(0x3137));
            }
            func_002FADB0();
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001393E0.f1C == 0) {
                int a = D_001393E0.f8;
                if (a == 2 && D_001393E0.f14 != 0) {
                    D_0021F240.st = a;
                    goto rc2_switch_end;
                }
            }
            if (D_001393E0.fBC == 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
                D_0021F240.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;

rc2_switch_end: ;
}
}
