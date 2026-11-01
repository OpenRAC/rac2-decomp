#include "include_asm.h"

/* Measured purchase-panel layout and pricing records. */
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

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
extern PanelColors D_L00_001AD768;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel D_L00_0022F7C0;
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_L00_001B1BB8[] __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_00288FB8(int);
extern void func_0027FA10(int, int, unsigned long long, unsigned char *, int);
extern void func_002F9BC0(char *, int);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);


extern char *func_L00_00358D50(int a0, int a1);

extern void func_00282AB0_1(char *target, char *base, int len);

typedef struct {
    short key;
    short index;
    int value;
} Query;

typedef struct {
    int key;
    int value;
} Entry32fd6f60;

extern Entry32fd6f60 D_L07_002A4100[];

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;

extern Rac2Native_acdcf1600d770d3b_ScalarConfigure116State D_00188660_2[];

/* Walks up to 25 records of 10 bytes; for each record whose 16-bit key is non-negative and whose table byte is set, resolves an object through a helper and copies/relocates it with the record's 16-bit length, capping the destination table at 25 entries. */
void func_L00_00358D98(char *a0)
{
    int i = 0;

    if (i < *(int *)a0) {
        int one = 1;
        char *d = a0 + 8;
        char *e = a0 + 4;

        do {
            char *obj = func_L00_00358D50(*(short *)(e + 14), *(short *)(e + 12));
            if (obj != 0) {
                char *t;
                if (*(short *)(e + 10) == one)
                    t = (char *)(*(int *)e + (int)obj);
                else
                    t = (char *)(*(int *)e + *(int *)(obj + 104));
                func_00282AB0_1(t, d, *(unsigned short *)(e + 8));
            }
            i++;
            d += 16;
            e += 16;
        } while (i < *(int *)a0);
    }
}

extern char D_L00_0021DE10[];

void func_L00_00358E50(void)
{
    func_L00_00358D98(D_L00_0021DE10);
}



extern int D_001B19E8 __attribute__((sda));

extern int D_001B19EC __attribute__((sda));

extern int D_001B8F0C __attribute__((sda));

extern char D_00188660_3[];

extern int func_002E5AD0(char *a0, int a1, int a2, int a3, int a4);

/* Shared slot table: the first free record of a 112-byte table is filled with the index and the
 * caller's value; returns the record number, or -1 when the index is out of range. */
int func_L00_0035F5A0(int index, int a1, int a2)
{
    int r;
    char *p;

    if (D_001B19EC == 0)
        return -1;
    index = index + D_001B8F0C;
    if (index >= D_001B19E8)
        return -1;
    r = func_002E5AD0((char *)(D_001B19EC + index * 32), a1, a2, 0, 1024);
    if (r >= 0) {
        p = D_00188660_3 + r * 112;
        *(int *)(p + 136) = a2;
        *(short *)(p + 126) = index;
    }
    return r;
}

/* Same slot table as func_L00_0035F5A0, but with the caller's own record: the helper gets the
 * slot's record, the value goes in at 0x40 and the helper's second value becomes the fifth
 * argument; the record's index word is written at 126 and the value word at 140. */
int func_L00_0035F640(int index, int a1, int a2, int a3)
{
    int r;
    char *p;

    if (index >= D_001B19E8)
        return -1;
    if (index == 0xFFFFFFFFU) {
        return -1;
    } else {
        r = func_002E5AD0((char *)(D_001B19EC + index * 32), a1, 0, a2 + 0x40, a3);
        if (r >= 0) {
            p = D_00188660_3 + r * 112;
            *(int *)(p + 140) = a2;
            *(short *)(p + 126) = index;
        }
        return r;
    }
}

/* Builds a slot index out of three weight/kind arguments and fills the same 112-byte record as
 * above; the record's value word comes from the fifth argument, the helper's from the sixth. */
int func_L00_0035F6D8(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int index;
    int sum;
    int r;
    char *p;

    if (a0 == 0xFFFFFFFFU)
        return -1;
    sum = a0 * 4 + a1 * 2;
    sum += a2;
    index = sum + D_001B8F0C;
    if (index >= D_001B19E8)
        return -1;
    r = func_002E5AD0((char *)(D_001B19EC + index * 32), a3, a4, 0, a5);
    if (r >= 0) {
        p = D_00188660_3 + r * 112;
        *(int *)(p + 136) = a4;
        *(short *)(p + 126) = index;
    }
    return r;
}

extern Entry32fd6f60 D_L00_002A3B00[];

/* Table search: walks the 8-byte records of D_L00_002A3B00 until the key is
 * found or the -1 terminator is met, and stores the record's index and value. */
void func_L00_0035F7E8(Query *q)
{
    int i = 0;

    if (D_L00_002A3B00[0].key != -1 && D_L00_002A3B00[0].key != q->key) {
        do {
            i++;
        } while (D_L00_002A3B00[i].key != -1 && D_L00_002A3B00[i].key != q->key);
    }
    q->index = i;
    q->value = D_L00_002A3B00[i].value;
}

void func_L00_0035F8D0(int value60, int selector68, int value64, int axis69, int mode6A)
{
    Rac2Native_acdcf1600d770d3b_ScalarConfigure116State *state = D_00188660_2;
    state->value_60 = value60;
    if (state->selector_68 != selector68) {
        state->selector_68 = selector68;
        state->dirty_6b |= 1;
    }
    if (state->value_64 != value64) {
        state->value_64 = value64;
        state->dirty_6b |= 4;
    }
    if (state->axis_69 != axis69 || state->mode_6a != mode6A) {
        state->mode_6a = mode6A;
        state->axis_69 = axis69;
        state->dirty_6b |= 2;
    }
}

void func_L00_0035F9F0(int value, long address) {
    int *target = (int *)(int)address;
    if (target != 0)
        *target = value;
}


INCLUDE_ASM("asm/levels", func_L00_003603C0);


extern void func_002B7B18(int value, char *target);

extern void func_002B7CE0(int value);

extern int D_L00_001BCAC0[];

extern int D_0014B540[];

/* Same body as func_L00_003046D0: compares two words of a 332-byte-stride table and calls the
 * two helpers when the entry ahead is greater; returns 1. */
int func_L00_00364EE8(int index)
{
    int j = index + 1;
    int *d = D_L00_001BCAC0;
    int *b = D_0014B540;
    int *t = (int *)((char *)b + 16040);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        func_002B7B18(hold, (char *)(cur + b[3977]));
        func_002B7CE0(0);
    }
    return 1;
}

extern unsigned short D_00152C26;

void func_L00_003672F8(void) {
    D_00152C26 = 1;
}

/* func_L00_00367308 is defined in L00_00358D98-g8.c. */

#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C_00367720 NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
int func_L00_00367720(void) {
    return (int)r1_D_0012F86C_00367720;
}





INCLUDE_ASM("asm/levels", func_L00_0036BE28);

INCLUDE_ASM("asm/levels", func_L00_0036C9AC);

INCLUDE_ASM("asm/levels", func_L00_0036C9D4);

INCLUDE_ASM("asm/levels", func_L00_0036D274);

INCLUDE_ASM("asm/levels", func_L00_0036D29C);

INCLUDE_ASM("asm/levels", func_L00_0036EF40);

INCLUDE_ASM("asm/levels", func_L00_0036EF68);

unsigned int func_L00_0036F480(void)
{
    return 0;
}

INCLUDE_ASM("asm/levels", func_L00_0036F488);

extern unsigned int D_001A7424 __attribute__((sda));

/* The level's own resident word and resident object: each place resolves its own value from
 * the retail bytes (0x001A8F00 and 0x001AC0C0 in 00_aranos_tutorial), so both are sda. */
extern int ref_L00_001A8F00_00 __attribute__((sda));

typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;

extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));

extern void func_00284E18(int a, int b, int c);

extern int func_002B49E0(int a, int b, int c, int d, int e);

extern void func_002F5220(void);

extern void func_002E4AC8(void);

extern void func_002B9390(void);

extern void func_L00_00310048(void);

/* The tick gate's callee is a neighbouring local function in six of the programs. */
extern unsigned int ref_L00_0036FA68_00(void);

extern void func_002F52B8(void);

extern void func_00289178(void);

/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
void func_L00_0036FA68(void)
{
    L00_0036FA68_Object *object;

    func_00284E18(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (D_001A7424 & 1)) {
        if (func_002B49E0(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036FA68_00() != 0)
        return;
    func_002F5220();
    func_002E4AC8();
    func_002B9390();
    func_L00_00310048();
    object = ref_L00_001AC0C0_00;
    object->field64(object);
    func_002F52B8();
    func_00289178();
}


/* func_L00_00373D40 is defined in L00_00373D40-g8.c. */

void func_L00_00373F40(void)
{
}

INCLUDE_ASM("asm/levels", func_L00_00373F48);

/* func_L00_00374348 is defined in L00_00374348.c. */

extern int D_0022F810;

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
void func_L00_00374B98(void)
{
    switch (D_0022F810) {
    case 0:
        func_002F93B0();
        break;
    case 1:
        func_L00_00374B78();
        break;
    case 2:
        func_002F93B0();
        break;
    case 3:
        func_002F93B0();
        break;
    }
}

extern void func_3747B0(void);

void func_L00_00374B78(void) {
    func_3747B0();
}

/* func_L00_00374C18 is defined in L00_00374C18-g8.c. */



INCLUDE_ASM("asm/levels", func_L00_003769C0);



/* Draws the selected-item panel, its value and label, and the top counter. */
void func_L00_003778F0(void) {
    PanelColors colors;
    char text[256];
    char *model = (char *)&D_L00_0022F7C0;
    int index = *(int *)(model + 0x80);
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
                  (unsigned char *)func_00288FB8(0x318C), -1);
    func_002F9BC0(text, D_L00_0022F7C0.items[index].price);
    func_0027F5B8(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    func_0027FB40(D_001A7340 >> 1, (int)(D_L00_001B25E0 * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  D_L00_0022F7C0.items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    func_002F9BC0(text, D_001A79FC);
    func_0027F980(444, 17, 0x80FFFFFFULL, (unsigned char *)text, -1);
    func_0028EA58(func_0028E588(0xEAA2, 3), 458, (int)(D_L00_001B25E0 * 15.0f + 0.5f),
                  32, (int)(D_L00_001B25E0 * 32.0f + 0.5f), colors.word);
}


/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */


/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
void func_L00_00378818(void) {
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
            func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x1127), -1);
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
        message = 0x1128;
    } else {
        if (D_001A79F8 >= func_002F6510()) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 6) * D_L00_001B25E0 + 0.5f);
            message = 0x1129;
        } else goto no_money;
    }
    func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(message), -1);
    return;
no_money:
    func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x1128), -1);
}

/* Measured rows of the confirmation prompt: the price is their first word. */
typedef struct { int price; int rest[2]; } ConfirmRow;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xBC];
    ConfirmRow rows[0];
} ConfirmModel;
/* The call must reach the compiler's builtin: its argument setup order differs from a plain call. */
extern void *memset(void *, int, unsigned int);

/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
void func_L00_00378C18(void) {
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
        func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x1129), -1);
    } else {
        func_00280200(&copy, 0x80F0F0F0ULL, (unsigned char *)func_00288FB8(0x1128), -1);
    }
}

/* func_L00_00378DE0 is defined in L00_00378DE0-g8.c. */

/* func_L00_00378E90 is defined in L00_00378E90.c. */

/* func_L00_0037A2E8 is defined in L00_0037A2E8-qcopy.c. */

/* func_L00_0037A610 is defined in L00_0037A610-g8.c. */

void func_L00_0037AF58(void)
{
}
