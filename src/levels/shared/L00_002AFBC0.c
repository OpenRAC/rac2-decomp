#include "include_asm.h"

extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_002F6BE0(int, int, char *, char *, char *, int, int);
extern void func_L00_00322EC8(char *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002B32F8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(char *);
extern void func_L00_002C42E0(int, int);
extern void func_L00_002F6B90(int);
extern int D_00138320[];
extern char D_L00_002F8588[];
extern char D_L00_002F85D0[];
extern char D_L00_002F8AD8[];

extern void func_L00_002AED68(void);

extern void func_L00_002AF860(void);

extern void func_L00_002AEB18(void);

extern float func_00282C48_2(float d);

#ifndef RAC2_T_ROW_F3392E4BC
#define RAC2_T_ROW_F3392E4BC
typedef float Row_F3392e4bc[4];
#endif

extern char D_00189E20_12[];

extern void func_0029F338_1(void *moby);

#ifndef RAC2_T_V4_FA012328C
#define RAC2_T_V4_FA012328C
typedef int V4_Fa012328c __attribute__((mode(TI)));
#endif

extern char D_00189F20[];

extern char D_00189F30[] __attribute__((sda));

extern void func_L00_002B39D8(void);

extern void func_00282C88_4(void *p);

extern void func_002B8518(void);

extern void func_L00_002D3CF8_1(int, int);

extern void func_L00_002D3C68_1(int, int, float);

extern void func_L00_002D3BD8_1(int, int);

extern void func_L00_002D3B58(int, int, float);

typedef unsigned char u8;

typedef int s32;

typedef float f32;

extern u8 D_00189E20_1[];

typedef struct { u8 prefix[0xc38]; f32 plane; f32 depth; } GornFloatInterval64;

#ifndef RAC2_T_V4_F6B9E759F
#define RAC2_T_V4_F6B9E759F
typedef struct {
    f32 x, y, z, w;
} V4_F6b9e759f;
#endif

#ifndef RAC2_T_M4_F6B9E759F
#define RAC2_T_M4_F6B9E759F
typedef struct {
    V4_F6b9e759f r[4];
} M4_F6b9e759f;
#endif

extern V4_F6b9e759f D_00189EA0_1[];

extern void func_00283410_5(M4_F6b9e759f *, V4_F6b9e759f *);

extern void func_00283788_3(M4_F6b9e759f *, M4_F6b9e759f *, V4_F6b9e759f *);

extern void func_002AB6D8_3(M4_F6b9e759f *, V4_F6b9e759f *);

extern int func_002830C0(float *, char *, char *);

extern float func_00283248_1(float, float);

extern float func_002AA898(float *, float, char *, float, float, float, int);

extern void func_L00_002B3DC0_1(float, float, float);

extern char D_00189FB0[];

#ifndef RAC2_T_V4S_F31E44309
#define RAC2_T_V4S_F31E44309
typedef struct {
    f32 x, y, z, w;
} V4S_F31e44309;
#endif

extern V4S_F31e44309 D_00189E20_10[];

extern void func_00282D30_6(V4S_F31e44309 *, V4S_F31e44309 *, f32);

extern void func_002A7470(void *, int, int, int);
typedef struct {
    char pad0[6];
    unsigned char flag;
} HeroItemMobyClass;

typedef struct {
    char pad0[0x24];
    HeroItemMobyClass *cls;
    char pad28[9];
    unsigned char visible;
    short drawDistance;
    unsigned short flags;
    char pad36[2];
    long long spawnFrame;
    char pad40[0x23];
    unsigned char mode;
    void (*update)(char *);
} HeroItemMoby;

/* One of the hero's item slots, 0x50 bytes each. */
typedef struct {
    HeroItemMoby *moby;     /* 0x00 */
    HeroItemMoby *other;    /* 0x04 */
    HeroItemMoby *extra;    /* 0x08 */
    char pad0C[4];
    int buttonMask;         /* 0x10 */
    int respawnFrame;       /* 0x14 */
    unsigned char ammoFlag; /* 0x18 */
    char pad19[0x24 - 0x19];
    int state;              /* 0x24 */
    int id;                 /* 0x28 */
    char pad2C[0x50 - 0x2C];
} HeroItemSlot;

typedef struct {
    char pad0[0x1220];
    HeroItemSlot slots[5];      /* 0x1220 */
    char pad13B0[0x2290 - 0x13B0];
    HeroItemMoby *heroMoby;     /* 0x2290 */
    char pad2294[39];
    unsigned char itemFlag;     /* 0x22BB */
    char pad22BC[12];
    int pendingItem;            /* 0x22C8 */
    char pad22CC[24];
    int selectedItem0;          /* 0x22E4 */
    char pad22E8[8];
    int selectedItem3;          /* 0x22F0 */
    char pad22F4[520];
    short packDisabled;         /* 0x24FC */
} HeroItemsCreateState;
extern HeroItemsCreateState D_00189E20_items;
extern unsigned char D_00139568[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_001A7398[] __attribute__((sda));
extern int D_00139688[];
extern int D_L00_001B18D8[] __attribute__((sda)), D_L00_001B19C8[] __attribute__((sda));
typedef struct {
    char pad0[0xA0];
    short joint;
    char padA2[14];
} HeroItemEase;
extern HeroItemEase D_0018B9A0[];
typedef struct {
    char pad0[0x14];
    int object;
    int other;
    unsigned char flag;
    char pad1[0x71];
    unsigned short ammo;
    char pad2[0x50];
} HeroItemDefinition;
extern HeroItemDefinition D_L00_00262570[];
extern void func_00294988(int);
extern HeroItemMoby *func_0029EFD0(int);
extern void func_00282A60(void *, int, int);
extern void func_L00_00390938(int);

/* calls three measured no-argument functions in sequence */
void func_L00_002AFBC0(void) {
 func_L00_002AED68();
 func_L00_002AF860();
 func_L00_002AEB18();
}

#define ITEM_DEF(id) (&D_L00_00262570[D_00139568[id]])
#define HERO_ITEMS (&D_00189E20_items)

/* Spawns the mobys for the hero's equipped item slots, releasing disabled slots. */
void func_L00_002AFBF0(void)
{
    HeroItemMoby *moby;
    int disabled;

    if (!HERO_ITEMS->slots[0].moby && D_L00_001B18D8[0] > HERO_ITEMS->slots[0].respawnFrame &&
        (!HERO_ITEMS->pendingItem || HERO_ITEMS->pendingItem == HERO_ITEMS->selectedItem0)) {
        int id = HERO_ITEMS->selectedItem0;
        int saved, i;

        if (!id) {
            if (D_001A7A00[8] || (saved = D_001A7398[0]) == 0)
                id = 10;
            else
                id = saved;
        }
        func_00294988(ITEM_DEF(id)->object);
        for (i = 0; i < 3; i++) {
            func_00282A60(&D_0018B9A0[i], 0, sizeof(HeroItemEase));
            D_0018B9A0[i].joint = -1;
        }
        HERO_ITEMS->slots[0].id = id;
        moby = func_0029EFD0(ITEM_DEF(id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[0].state = 2;
            HERO_ITEMS->slots[0].moby = moby;
            HERO_ITEMS->slots[0].ammoFlag = 0;
            if (ITEM_DEF(id)->ammo && !D_00139688[id])
                HERO_ITEMS->slots[0].ammoFlag = 255;
            if (id == 10) {
                HERO_ITEMS->slots[0].buttonMask = 128;
                HERO_ITEMS->slots[0].state = 2;
                func_002A7470(moby, 1, 0, 1);
            } else {
                HERO_ITEMS->slots[0].buttonMask = 32;
            }
            HERO_ITEMS->itemFlag = ITEM_DEF(HERO_ITEMS->slots[0].id)->flag;
        }
    }

    if (!HERO_ITEMS->slots[3].moby) {
        int id = HERO_ITEMS->selectedItem3;

        if (!id) {
            id = D_001A7398[3];
            if (!id || id == 8 || id == 4) {
                id = D_001A7A00[0x9] ? 3 : 2;
                if (id)
                    D_001A7398[3] = id;
            }
        }
        HERO_ITEMS->slots[3].id = id;
        moby = func_0029EFD0(ITEM_DEF(id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[3].state = 2;
            HERO_ITEMS->slots[3].moby = moby;
            if (HERO_ITEMS->packDisabled)
                moby->flags |= 0x41;
            if (!HERO_ITEMS->packDisabled && (HERO_ITEMS->slots[3].id == 3 || HERO_ITEMS->slots[3].id == 8)) {
                func_L00_00390938(0);
                func_L00_00390938(1);
            }
        }
    }

    if (!HERO_ITEMS->slots[3].other) {
        moby = func_0029EFD0(ITEM_DEF(1)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[3].state = 2;
            HERO_ITEMS->slots[3].other = moby;
            if (HERO_ITEMS->packDisabled)
                moby->flags |= 0x41;
        }
    }

    disabled = 0;
    if (*(short *)(D_001A7A00 + 0x18) == 4 || D_001A7A00[0x49]
        || D_001A7A00[0x42] || D_001A7A00[0x4B] || D_001A7A00[0x4A])
        disabled = 1;
    if (HERO_ITEMS->slots[2].moby && disabled) {
        func_0029F338_1(HERO_ITEMS->slots[2].moby);
        HERO_ITEMS->slots[2].moby = 0;
    }
    if (!HERO_ITEMS->slots[2].moby && !disabled) {
        HeroItemMoby *slotMoby;
        int id = D_001A7398[2];

        if (!id)
            id = 47;
        HERO_ITEMS->slots[2].id = id;
        slotMoby = func_0029EFD0(ITEM_DEF(id)->object);
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            slotMoby->flags |= 2;
            slotMoby->update = 0;
            if (slotMoby->cls->flag)
                slotMoby->mode = 16;
            slotMoby->flags |= 0x800;
            HERO_ITEMS->slots[2].moby = slotMoby;
            HERO_ITEMS->slots[2].state = 2;
        }
    }

    disabled = 0;
    if (*(short *)(D_001A7A00 + 0x18) == 4 || D_001A7A00[0x49]
        || D_001A7A00[0x42] || D_001A7A00[0x4B] || D_001A7A00[0x4A])
        disabled = 1;
    if (disabled) {
        if (HERO_ITEMS->slots[1].moby) {
            func_0029F338_1(HERO_ITEMS->slots[1].moby);
            HERO_ITEMS->slots[1].moby = 0;
        }
        if (HERO_ITEMS->slots[1].other) {
            func_0029F338_1(HERO_ITEMS->slots[1].other);
            HERO_ITEMS->slots[1].other = 0;
        }
    }
    if (!HERO_ITEMS->slots[1].moby && !disabled) {
        if (D_L00_001B19C8[0] < 3)
            HERO_ITEMS->slots[1].id = D_001A7398[1] = (*(short *)(D_001A7A00 + 0x24));
        else
            HERO_ITEMS->slots[1].id = D_001A7398[1];
        if (!HERO_ITEMS->slots[1].id)
            HERO_ITEMS->slots[1].id = 52;
        moby = func_0029EFD0(ITEM_DEF(HERO_ITEMS->slots[1].id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            moby->update = 0;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[1].moby = moby;
            HERO_ITEMS->slots[1].state = 2;
        }
        moby = func_0029EFD0(ITEM_DEF(HERO_ITEMS->slots[1].id)->other);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            moby->update = 0;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[1].other = moby;
            HERO_ITEMS->slots[1].state = 2;
        }
    }

    if (!HERO_ITEMS->slots[4].moby && D_001A7A00[0xFD]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(5)->object);
        HERO_ITEMS->slots[4].id = 5;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (slotMoby->cls->flag)
                slotMoby->mode = 16;
            HERO_ITEMS->slots[4].moby = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
    if (!HERO_ITEMS->slots[4].other && D_001A7A00[0x12A]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(50)->object);
        HERO_ITEMS->slots[4].id = 50;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            HERO_ITEMS->slots[4].other = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
    if (!HERO_ITEMS->slots[4].extra && D_001A7A00[0xFF]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(7)->object);
        HERO_ITEMS->slots[4].id = 7;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            HERO_ITEMS->slots[4].extra = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
}

#undef HERO_ITEMS
#undef ITEM_DEF


/* Nested 3x3 sweep over two rows-of-four arrays: sums the results of calling the same routine with the difference of each of the nine element pairs, returns the sum. */
float func_L00_002B0480(Row_F3392e4bc *a, Row_F3392e4bc *b)
{
    float sum = 0.0f;
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            sum += func_00282C48_2(a[i][j] - b[i][j]);
    return sum;
}

/* func_L00_002B0528 is in L00_002B0528-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_002B0968);

/* for one fixed 80-byte slot: stores a value, rewrites a state word, dispatches through a function pointer at entry+100 unless the entry is null or carries a 253/254 sentinel, then releases two stored entry pointers, skipping the second when the slot index is 3 */
void func_L00_002B1230(int slot, int value)
{
    char *e;
    void (*fn)(char *);

    {
        char *p = D_00189E20_12 + slot * 80;

        *(int *)(p + 4660) = value;
        if (*(int *)(p + 4676) != 3) {
            *(int *)(p + 4676) = 3;
            e = *(char **)(p + 4640);
            if (e != 0) {
                if (*(unsigned char *)(e + 32) != 254) {
                    if (*(unsigned char *)(e + 32) != 253) {
                        fn = *(void (**)(char *))(e + 100);
                        if (fn != 0)
                            fn(e);
                    }
                }
            }
        }
    }
    {
        char *q = D_00189E20_12 + slot * 80;

        e = *(char **)(q + 4640);
        *(int *)(q + 4676) = 0;
        *(int *)(q + 4680) = 0;
        if (e != 0) {
            func_0029F338_1(e);
            *(char **)(q + 4640) = 0;
        }
        e = *(char **)(q + 4644);
        if (e != 0 && slot != 3) {
            func_0029F338_1(e);
            *(char **)(q + 4644) = 0;
        }
    }
}

typedef struct {
    u8 pad0[0x98];
    f32 f98;
    u8 pad1[0x1A0 - 0x9C];
    f32 f1A0;
    f32 f1A4;
    f32 f1A8;
    u8 pad2[0x1B0 - 0x1AC];
    f32 f1B0;
    f32 f1B4;
    u8 pad3[0x1FC - 0x1B8];
    short a;
    u8 pad4[0xA70 - 0x1FE];
    f32 fA70;
    f32 fA74;
    f32 fA78;
    u8 pad4b[0x1FB0 - 0xA7C];
    f32 f1FB0;
    f32 f1FB4;
    u8 pad5[0x22C3 - 0x1FB8];
    u8 flag;
    u8 pad6[0x24F4 - 0x22C4];
    short b;
} D00189E20_Overlay;

extern D00189E20_Overlay D_00189E20;

extern void func_002AA2E8(float *, float, float);

/* The level's own dispatch table: 31 absolute code addresses, five of them (the cases
 * 14, 26, 27, 43 and 44) pointing at the arm that writes the two shorts and the rest at
 * the return.  It lives in the level's data, so it is named by its address. */
extern void *D_L00_002A00A0[31];

/* Dispatches on the argument through the level's table: the five listed cases write
 * 0x46 at +0x1FC and 3 at +0x24F4 of the resident block, the other twenty-six and every
 * argument out of the range only return. */
void func_L00_002B1308(int a0)
{
    /* Keeps the two arms alive: the addresses land in the discarded .data. */
    static void *cases[31] = {
        &&arm, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&arm, &&arm, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&arm, &&arm
    };

    if ((unsigned int)(a0 - 14) < 31) {
        goto *D_L00_002A00A0[a0 - 14];
    } else {
        goto ret;
    }
arm:
    D_00189E20.b = 3;
    D_00189E20.a = 0x46;
ret:
    return;
}

INCLUDE_ASM("asm/levels", func_L00_002B1350);

extern void func_L00_002B1350(int);
/* Read through its macro symbol: the copy reorg puts in a branch delay slot assembles
 * $gp-relative, the one in ordinary flow as lui/lw. */
extern int D_L00_001B18D8[] __attribute__((sda));

/* Per-frame pass over the seven 80-byte slots at +0x1220: an empty slot is released; in
 * state 2 a slot counts a tick, is released and, for a flagged entry whose animation set
 * allows it, starts animation 1; in state 3 it counts a byte tick and slots 0 and 1 (or a
 * flagged entry) are reinstalled with the shared value plus 2.  The entry's update
 * callback then runs, except for slot 6, a 253/254 sentinel entry, or slot 0 while the
 * block's word at +0x1500 is set and its mode at +0x1248 is not 10. */
void func_L00_002B1F90(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        u8 *base = D_00189E20_1;
        u8 *slot = base + i * 80;
        u8 *entry = *(u8 **)(slot + 0x1220);
        void (*callback)(char *);

        if (entry != 0) {
            switch (*(int *)(slot + 0x1244)) {
            case 2:
                ++*(int *)(slot + 0x1240);
                func_L00_002B1350(i);
                if ((entry[0x60] & 2) && entry[0x43] == 0
                    && (*(u8 **)(entry + 0x24))[0xC] >= 2)
                    func_002A7470(entry, 1, 0, 2);
                break;
            case 3:
                ++slot[0x123B];
                if ((entry[0x60] & 2) || i == 1 || i == 0)
                    func_L00_002B1230(i, D_L00_001B18D8[0] + 2);
                break;
            }
            {
                u8 *block = D_00189E20_1;

                if (*(int *)(block + 0x1500) != 0 && i == 0
                    && *(int *)(block + 0x1248) != 10)
                    continue;
            }
            if (entry != 0 && entry[0x20] != 254 && entry[0x20] != 253 && i != 6) {
                callback = *(void (**)(char *))(entry + 0x64);
                if (callback != 0)
                    callback((char *)entry);
            }
        } else {
            func_L00_002B1350(i);
        }
    }
}


/* func_L00_002B2200 is in L00_002B2200-g8.c. */


/* Reset the hero update state, install the requested mode and object, and update the mode-one counters. */
void func_L00_002B2A40(int mode, int value, char *object)
{
    char *p;
    char *current;
    int count;

    func_L00_002AF7D0();
    p = (char *)D_00189E20_1;
    p[0x22B6] = 1;
    func_L00_002B1F90();
    *(int *)(p + 0x2290) = *(int *)(p + 0xC18);
    func_L00_00322EC8(p + 0x18E0);
    func_L00_00322EC8(p + 0x1A30);
    current = *(char **)(p + 0x2290);
    *(int *)(current + 0x9C) = -1;
    if (mode != 4 || (unsigned char)p[0x22B4] != mode)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *q = (char *)D_00189E20_1;

        q[0x22B4] = (char)mode;
        *(int *)(q + 0xC14) = (int)object;
        *(int *)(q + 0x2290) = (int)object;
        if ((unsigned char)mode == 1 && (D_00138320[0] & 0x10) != 0) {
            func_L00_002F6BE0(0x23, 0, D_L00_002F8588,
                             D_L00_002F85D0, D_L00_002F8AD8, 0, 0);
            func_L00_002F6B90(3);
        }
        {
            char *r = (char *)D_00189E20_1;

            func_L00_002B32F8();
            *(float *)(r + 0x250) = *(float *)(r + 0x258);
            *(float *)(r + 0x254) = *(float *)(r + 0x25C);
            *(unsigned short *)(*(char **)(r + 0x2290) + 0x34) |= 6;
            *(float *)(r + 0xC24) = *(float *)(r + 0xC20) = 1.0f;
            func_L00_002D24B8();
            func_002A677C(*(char **)(r + 0x2290));
            *(short *)(r + 0x24F2) = (short)value;
            if (mode == 1) {
                *(short *)(r + 0x24D4) = *(short *)(r + 0x24CC);
                count = *(int *)(r + 0x24D0);
                *(int *)(r + 0x24CC) = count;
                if (count >= 5)
                    *(int *)(r + 0x24CC) = 4;
            }
            func_L00_002C42E0(value, 2);
        }
    }
}

/* Zeroes a 16-byte global block, calls a setup helper, runs a per-slot reset helper over seven 16-byte units of a global table, then clears three word fields of a block 256 bytes below the table base. */
void func_L00_002B2BD0(void)
{
    char *p;

    *(volatile V4_Fa012328c *)D_00189F30 = 0;
    func_L00_002B39D8();
    p = D_00189F20;
    func_00282C88_4(p);
    func_00282C88_4(p - 16);
    func_00282C88_4(p + 16);
    func_00282C88_4(p + 32);
    func_00282C88_4(p + 48);
    func_00282C88_4(p + 96);
    func_00282C88_4(p - 96);
    p = p - 256;
    *(int *)(p + 420) = 0;
    *(int *)(p + 376) = 0;
    *(int *)(p + 368) = 0;
    func_002B8518();
}


/* dispatch on the second integer argument: each arm runs a pair of sub-calls passing the first argument twice, the second call also forwarding the float argument */
void func_L00_002B2C58(int a, int b, float x, float y)
{
    if (b != 0) {
        func_L00_002D3CF8_1(a, a);
        func_L00_002D3C68_1(a, a, y);
    } else {
        func_L00_002D3BD8_1(a, a);
        func_L00_002D3B58(a, a, y);
    }
}

/* func_L00_002B2CC8 is in L00_002B2CC8-interact.c. */

INCLUDE_ASM("asm/levels", func_L00_002B30E8);

/* tests the signed short identifier at offset 0xaa of a nonnull object against 71 */
s32 func_L00_002B3248(u8 *object) {
 if(object==0) return 0;
 return *(short *)(object+0xaa)==71;
}

extern int D_00138320[];

extern char D_L00_001B8FF0[];

extern float D_L00_001B8DD8;

extern float func_L00_002B9B38(char *, int);

extern float func_00282C48(float);

extern float func_00283C80(float, float);

int func_L00_002B3268(float x) {
    float r;

    if ((D_00138320[0] & 3) != 0) {
        if (D_00189E20.flag != 0)
            r = func_00282C48(func_L00_002B9B38(D_L00_001B8FF0, 0));
        else
            r = func_00283C80(D_00189E20.f98, D_L00_001B8DD8);
        if (r < x)
            return 0;
        return 1;
    }
    return 0;
}

/* func_L00_002B32F8 is in L00_002B32F8-hero.c. */

/* func_L00_002B35A0 is in L00_002B35A0.c. */

/* func_L00_002B36E0 is in L00_002B36E0-hero.c. */

extern char D_0018BDD0[];

extern float func_00282DF0(char *);

float func_L00_002B3900(void) {
    float a = func_00282C48(D_00189E20.f1FB0);
    float b = func_00282C48(D_00189E20.f1FB4);
    float c;
    float v;

    if (b < a)
        c = func_00282C48(D_00189E20.f1FB0);
    else
        c = func_00282C48(D_00189E20.f1FB4);
    v = (c + func_00282DF0(D_0018BDD0)) * 0.5f;
    if (1.0f < v)
        v = 1.0f;
    return v;
}

/* Test whether a scalar lies below a plane within its configured depth, rejecting unordered values */
int func_L00_002B3998(f32 value)
{
    GornFloatInterval64 *root = (GornFloatInterval64 *)D_00189E20_1;
    if (value < root->plane) {
        if (root->plane - value <= root->depth)
            return 1;
    }
    return 0;
}

/* clears the two floats at the head of the window block; the second store is the one the
   scheduler parks in the jr delay slot, so it is written second */
void func_L00_002B39D8(void)
{
    D_00189E20.f1B0 = 0.0f;
    D_00189E20.f1B4 = 0.0f;
}

/* builds one 64-byte block from a 3-float vector of the incoming scalars and another from a static table record one element in, combines them, then scales the result again from that record */
void func_L00_002B3DC0(f32 a1, f32 a2, f32 a3) {
    V4_F6b9e759f in;
    M4_F6b9e759f m1;
    M4_F6b9e759f m2;
    in.x = a1;
    in.y = a2;
    in.z = a3;
    func_00283410_5(&m1, &in);
    func_00283410_5(&m2, &D_00189EA0_1[1]);
    func_00283788_3(&m2, &m2, &m1);
    func_002AB6D8_3(&m2, &D_00189EA0_1[1]);
}

/* Fills a two-float scratch buffer from one region of a fixed global, passes it with three forwarded floats and an out-parameter to another callee, stores the returned float back into the global, then feeds that out value to a final callee. */
void func_L00_002B3E40(int a0, float a1, float a2, float a3)
{
    float tmp[2];
    char *p = D_00189FB0;
    float out;
    float r;

    func_002830C0(tmp, p, p - 336);
    r = func_00283248_1(tmp[0], tmp[1]);
    out = 0.0f;
    *(float *)(p + 24) = func_002AA898(&out, r, p + 20, a1, a2, a3, a0);
    func_L00_002B3DC0_1(0.0f, 0.0f, out);
}

void func_L00_002B3EF8(int a0, float x, float y, float z) {
    if (D_00189E20.flag != 0)
        func_L00_002B3E40(a0, x, y, z);
    else
        D_00189E20.f1A8 = func_002AA898(&D_00189E20.f98, D_00189E20.f1A0, (char *)&D_00189E20.f1A4, x, y, z, a0);
}


/* func_L00_002B3F68 is in L00_002B3F68.c. */

void func_L00_002B41B8(float x, float y) {
    if (D_00189E20.f1B4 < D_00189E20.f1B0)
        func_002AA2E8(&D_00189E20.f1B4, D_00189E20.f1B0, x);
    else
        func_002AA2E8(&D_00189E20.f1B4, D_00189E20.f1B0, y);
}


extern char D_00189F10[];

extern void func_00282F20(char *, void *, float);

void func_L00_002B42D8(void *obj) {
    func_00282F20(D_00189F10, obj, *(float *)(D_00189F10 + 0xC4));
}

/* func_L00_002B4308 is in L00_002B4308.c. */

/* func_L00_002B4458 is in L00_002AFBC0-surface.c. */

/* func_L00_002B47A8 is in L00_002AFBC0-vectors.c. */

/* func_L00_002B5250 is in L00_002AFBC0-snap.c. */

extern void func_002AF000(char *, float, float, float);

extern void func_00282D30(char *, char *, float);

extern void func_00282C88(char *);

void func_L00_002B54F8(float x, float y) {
    char *p = (char *)&D_00189E20 + 0xA60;
    float r;

    func_002AF000(p, D_00189E20.fA70, D_00189E20.fA78, D_00189E20.fA74);
    func_00282D30(p, p, x);
    r = func_00282DF0(p);
    if (r <= y)
        func_00282C88(p);
    else
        func_00282F20(p, p, r - y);
}




/* func_L00_002B5B60 is in L00_002B5B60-motion.c. */

/* scales four 16-byte records of a static table in place by a scalar, then multiplies one float field of a later record by the same scalar */
void func_L00_002B6118(f32 a0) {
    V4S_F31e44309 *p = &D_00189E20_10[17];
    func_00282D30_6(p, p, a0);
    func_00282D30_6(p + 1, p + 1, a0);
    func_00282D30_6(p - 2, p - 2, a0);
    func_00282D30_6(p + 5, p + 5, a0);
    D_00189E20_10[27].y = D_00189E20_10[27].y * a0;
}

/* func_L00_002B6198 is in L00_002AFBC0-velocity.c. */

/* func_L00_002B6560 is in L00_002B6560.c. */


INCLUDE_ASM("asm/levels", func_L00_002B75A0);

/* func_L00_002B7718 is in L00_002B7718-g8.c. */
