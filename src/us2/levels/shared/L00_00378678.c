#include "include_asm.h"



INCLUDE_ASM("asm/us2/levels", func_US2_L00_00378C38);




INCLUDE_ASM("asm/us2/levels", func_US2_L00_00379928);

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
extern void func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_00288FB8(int);
extern void func_0027FA10(int, int, unsigned long long, unsigned char *, int);

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




INCLUDE_ASM("asm/us2/levels", func_US2_L00_0037A5D0);
