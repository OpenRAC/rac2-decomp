#include "include_asm.h"

/* A row of a choice list: its label, the byte it edits and up to four choice labels. */
typedef struct {
    int text;
    unsigned char *value;
    int choices[4];
} ChoiceRow;

typedef struct {
    char pad00[0x34];
    ChoiceRow *rows;
    int selected;
} ChoiceMenu;

/* A menu page: the page the back button opens and the menu taking input. */
typedef struct {
    char pad00[0xE0];
    int back;
    char padE4[4];
    void *focus;
    char padEC[0x128 - 0xEC];
    int pendingFocus;
} MenuPage;

/* The menu system D_001F2840: its current page, the page to open next and the flag that
 * keeps the menu from closing. */
typedef struct {
    char pad[0x14];
    MenuPage *owner;
    int next;
    char pad1[0x134 - 0x1C];
    int active;
} CtxB6;

extern int D_00138180[];

extern void func_002DF190(int, int);

/* Qwen draft (branch qwen/autonomy, 385de342), checked by tools/check.py */
void func_002D5B58(short param_1, int param_2, int *param_3);

/* func_002D7AC8: owner ABI/declaration review retained. */
extern int D_001C51D4;

extern void F70997ba9_FUN_002FC560(int a, int b);

extern void F70997ba9_FUN_0027C540(int a);

extern void *F70997ba9_FUN_00288FB8(int id);

extern int F70997ba9_FUN_0027F198(void *p, int i);

extern void F70997ba9_FUN_0027F120(void);

extern void F70997ba9_FUN_0027F5B8(int a, int b, long c, void *d, int e);

extern void F70997ba9_FUN_0027F110(void);

extern void F70997ba9_FUN_0027C660(void);

typedef int s32;

extern s32 func_002DE550 (s32);

/* Qwen draft (branch qwen/autonomy, f0b23b24), checked by tools/check.py */
typedef unsigned long long undefined8;

typedef unsigned int undefined4;

extern undefined4 func_002DE618(undefined4);

#ifndef RAC2_T_TWO_F73AF1964
#define RAC2_T_TWO_F73AF1964
typedef struct { signed char a, b; } TWO_F73af1964;
#endif

extern void func_0027C540_1(int);

extern void func_0027F538(int, int, long, signed char *, int);

extern int  func_0028E588(int, int);

extern int  func_0028E640(int);

extern void func_0028F410(float, float, float, float, float, int, int, int);

extern void func_0027C660_1(void);

extern signed char D_L01_001ABE90[];

extern signed char D_L01_001ABE98[];

extern int func_002DE3A0(int);

extern int func_002DE550_1(int);

extern int func_002C9A60(void);

extern int func_L00_002F3478(void);

extern int func_00339760(int);

extern int D_L00_001A904C_8 __attribute__((sda));

void func_002D5E98(int param_1)
{
  int auStack_20[4];

  auStack_20[0] = 0;
  func_002D5B58(*(short *)(param_1 + 2), *(int *)(param_1 + 4), &auStack_20[0]);
  return;
}
/* func_002D5EC0 is in 002D5E98-list-g8.c. */

INCLUDE_ASM("asm/game", func_002D6230);

/* func_002D68D8 is in 002D5E98-g8.c. */


typedef struct { char pad[4]; short mode; } Mode2D6E78;
typedef struct { char pad[0x29C]; int flags[5]; int selected; } Map2D6E78;
typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern Mode2D6E78 D_001A63A8;
extern Map2D6E78 D_001C4FA0;
extern State2D6E78 D_001F2840;
extern unsigned char D_001F291B;
extern void func_002B7AD0(void);

int func_002D6E78(void)
{
    if (D_001A63A8.mode == 0) {
        Map2D6E78 *map = &D_001C4FA0;
        int index = map->selected;
        if (index != -1) {
            D_001F291B = 0;
            map->flags[index] ^= 0x1000;
            map->selected = -1;
        }
    }
    if (D_001A63A8.mode != 0) {
        State2D6E78 *state = &D_001F2840;
        if (state->active != 0) {
            Map2D6E78 *map;
            func_002B7AD0();
            state->active = 0;
            map = &D_001C4FA0;
            map->flags[map->selected] = -1;
            map->selected = -1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/game", func_002D6F38);

extern void func_0029D830(int *);
extern int func_0029DB28(unsigned int, unsigned int, unsigned int, int);
extern int D_001C51D0;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 D_0025A6E0;
extern int D_0025A620[];

int func_002D75E8(int *arg0)
{
    func_0029D830(arg0);
    *(int *)((char *)arg0 + 0xA0) = func_0029DB28(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)arg0 + 0x30;
        int index = D_001C51D0;

        if (*(int *)(base + (index << 2)) != -1) {
            D_0025A6E0.f3C = -0x240;
            D_0025A6E0.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)D_0025A620 = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)arg0 + 0xA4) = 0;
    return 0;
}

INCLUDE_ASM("asm/game", func_002D7698);


int func_002D7AC8(void)
{
    D_001C51D4 = -1;
    return 0;
}

int func_002D7AE0(void) {
    func_002DE3A0(1);
    return 0;
}

extern int D_001A7BA0[] __attribute__((sda));
extern int D_001886B0[];

int func_002D7B00(void) {
    D_001886B0[0] = D_001A7BA0[0];
    return 0;
}

typedef struct { char pad[0x1c0]; int held; int pressed; } Pad2D7B18;
typedef struct {
    char pad00[0x30];
    unsigned int flags;
    char pad34[0xC];
    int selection;
} Menu2D7B18;
/* D_001A7B90 is the 40-byte saved settings block (func_00298E08 copies it whole). Read as
   fields, its symbol+offset macro loads never fill a delay slot, as in retail. The two
   sliders are numbered by the menu row that edits them. */
typedef struct {
    char pad00[8];
    int mode;
    int slider1;
    int slider0;
    char pad14[0x28 - 0x14];
} Settings2D7B18;
extern Settings2D7B18 D_001A7B90 __attribute__((sda));
extern int *D_001AA4F0 __attribute__((sda));
extern void func_00295C50(int);
extern void func_002E4860(void);
extern void func_00132938(int);

/* Sound menu input: back and close, row navigation, volume sliders and the mode toggle. */
int func_002D7B18(Menu2D7B18 *menu)
{
    int previous;
    int old_slider1;
    int old_slider0;

    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x900) != 0 && ((CtxB6 *)&D_001F2840)->active == 0)
        return 1;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x10) != 0) {
        int back = ((CtxB6 *)&D_001F2840)->owner->back;
        int result;

        /* One shared exit: it keeps the 0/-1 choice a branch, not a conditional move. */
        if (back != 0) {
            ((CtxB6 *)&D_001F2840)->next = back;
        } else if (((CtxB6 *)&D_001F2840)->active == 0) {
            result = -1;
            goto back_done;
        }
        result = 0;
back_done:
        return result;
    }

    previous = menu->selection;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x1000) != 0)
        menu->selection = (previous + 2) % 3;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x4000) != 0)
        menu->selection = (menu->selection + 1) % 3;
    if (menu->selection != previous || ((CtxB6 *)&D_001F2840)->owner->pendingFocus != 0) {
        func_002DF190(1, 0x11);
        if (menu->flags & 0x20)
            func_00295C50(D_001AA4F0[menu->selection]);
    }

    old_slider1 = D_001A7B90.slider1;
    old_slider0 = D_001A7B90.slider0;
    if ((((Pad2D7B18 *)D_00138180)->held & 0x2000) != 0) {
        if (menu->selection == 0) {
            int next = D_001A7B90.slider0 + 3;
            D_001A7B90.slider0 = next < 1025 ? next : 1024;
        }
        if (menu->selection == 1) {
            int next = D_001A7B90.slider1 + 3;
            D_001A7B90.slider1 = next < 1025 ? next : 1024;
        }
    }
    if ((((Pad2D7B18 *)D_00138180)->held & 0x8000) != 0) {
        if (menu->selection == 0) {
            int next = D_001A7B90.slider0 - 3;
            D_001A7B90.slider0 = next >= 0 ? next : 0;
        }
        if (menu->selection == 1) {
            int next = D_001A7B90.slider1 - 3;
            D_001A7B90.slider1 = next >= 0 ? next : 0;
        }
    }
    if (old_slider1 != D_001A7B90.slider1 || old_slider0 != D_001A7B90.slider0)
        func_002E4860();

    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x40) != 0) {
        if (menu->selection == 2)
            D_001A7B90.mode = !D_001A7B90.mode;
        func_00132938(!D_001A7B90.mode);
        func_002DF190(0, 0x11);
    }
    return 0;
}

/* func_002D7DB8 is in 002D5E98-audio.c. */


int func_002D81A8(void) {
    return 0;
}

typedef struct { char pad0[0x36C]; int offset; char pad370[0x16B0 - 0x370]; int start; int length; } Stream2D81B0;
typedef struct { unsigned int key; unsigned int flags; } Slot2D81B0;
extern Stream2D81B0 D_0014B540;
#define MACRO_ADDR __attribute__((section(".sdata")))
extern Slot2D81B0 D_001B1F50[] MACRO_ADDR;
extern int D_001F2958;

/* Halves the stream length while it marks the slots whose key is older than the clock and
   (outside the mode) asks for the next block; the result picks state 1 or 3. */
int func_002D81B0(char *object)
{
    int length;
    int i;
    unsigned int *key;
    unsigned int *flags;

    func_002DE3A0(1);
    *(int *)(object + 0x54) = 0;
    *(int *)(object + 0x38) = 0;
    length = D_0014B540.length;
    D_0014B540.length = length / 2;
    flags = &D_001B1F50[0].flags;
    key = &D_001B1F50[0].key;
    for (i = 0; i < 5; i++) {
        if (*key != 0 && *key < D_001F2840.limit)
            *flags |= 2;
        flags += 2;
        key += 2;
    }
    *(int *)(object + 0x50) = 0;
    if (D_001A63A8.mode == 0) {
        if (func_002B7B18(D_001F2958, D_0014B540.start + D_0014B540.offset, D_0014B540.length) != 0)
            *(int *)(object + 0x50) = 1;
        else
            *(int *)(object + 0x50) = 3;
    }
    *(int *)(object + 0x10) |= 4;
    D_0014B540.length = length;
    return 0;
}

extern short D_001A63AC;
extern void func_002B7AD0(void);
extern int D_001B1840 __attribute__((sda));
extern int D_00254EA4;

int func_002D82C8(char *object)
{
    if (D_001A63AC != 0 && *(int *)(object + 0x50) == 1)
        func_002B7AD0();
    func_002DE3A0(1);
    {
        int value = *(int *)(object + 0x54);
        if (value != 0) {
            D_00254EA4 = *(int *)(object + 0x38);
            D_001B1840 = value;
        }
    }
    return 0;
}

extern unsigned char D_001A7BB4 __attribute__((sda));
extern int D_00254E78[];
extern int func_002B7B18(int, int, int);
extern void func_00282AB0(void *, void *, int);

/* The loader object of func_002D81B0: its flags, the entry table it replaced and its state. */
typedef struct {
    char pad00[0x10];
    int flags;
    char pad14[0x38 - 0x14];
    int saved_count;
    char pad3C[0x50 - 0x3C];
    int state;
    int saved_base;
} Loader2D8338;

/* Advances the loader: starts the read, then unpacks the loaded block and relocates its entries. */
int func_002D8338(char *object)
{
    Loader2D8338 *loader = (Loader2D8338 *)object;

    switch (loader->state) {
    case 2:
        break;
    case 0:
        if (D_001A63AC == 0) {
            Stream2D81B0 *stream = &D_0014B540;

            if (func_002B7B18(D_001F2958, stream->start + stream->offset, stream->length))
                loader->state = 1;
            else
                loader->state = 3;
        }
        break;
    case 1:
        if (D_001A63AC == 0) {
            char *data = D_001F2840.loaded;
            int *header = (int *)(data + ((int *)data)[D_001A7BB4]);
            int count = *header++;
            int size = *header++;
            char *base;
            int i;

            func_00282AB0(data, header, ((size + 3) & ~3) - 8);
            loader->saved_base = D_001B1840;
            loader->saved_count = D_00254E78[11];
            D_00254E78[11] = count;
            base = D_001F2840.loaded;
            D_001B1840 = (int)base;
            for (i = 0; i < D_00254E78[11]; i++) {
                int reloc = (int)base - 8;

                ((int *)base)[i * 4] += reloc;
            }
            loader->state = 2;
            loader->flags &= ~4;
        }
        break;
    }
    return 0;
}

/* func_002D89D8 is defined in 002D5E98-listbox.c. */

extern char *D_001A8CFC[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139868[];
extern unsigned char D_00239BA0[];
typedef struct { unsigned char reserved[0x6C]; int handle; } WidgetClass2D8EC0;
extern void *func_0034E5B8(void *);
extern void func_00335E68(unsigned char *, int);
extern void func_00336B98(char *, int);
extern void func_00336B90(unsigned char *, int);
extern void func_0034E220(char *, int, int, int, int);
void func_002D8EC0(char *source, short *row, int first, int second, int x, int y)
{
    int index = second * *(int *)(source + 0x44) + first;
    unsigned char *widget = (unsigned char *)func_0034E5B8(D_001A8CFC[0] + 0x36F28) + index * 0x48;
    func_00335E68(widget, 0);
    if (((WidgetClass2D8EC0 *)(D_00139568[row[3]] * 0xE0 + (unsigned int)D_00239BA0))->handle != 0) {
        func_00335E68(widget, 1);
        func_00336B98((char *)widget, D_00139868[row[3]] >> 5);
        func_00336B90(widget, ((WidgetClass2D8EC0 *)(D_00139568[row[3]] * 0xE0 + (unsigned int)D_00239BA0))->handle);
    }
    func_0034E220(D_001A8CFC[0] + 0x36F28, index, x, y, 0x80);
}


INCLUDE_ASM("asm/game", func_002D9008);

#define NOT_SDA __attribute__((section(".data")))

extern unsigned char r1_D_001414F4 NOT_SDA;

/* A short-returning inline keeps retail's branch: the select happens in
   HImode, which has no movcc pattern, so jump.c cannot turn it into the
   xori/movz a promoted `short` local gets. */
static inline short pauseFlagState_r002D95D8(void) {
    if (r1_D_001414F4 != 1) {
        return 3;
    }
    return 0;
}

/* rac1-decomp src/game/pause.c: func_0021EDD8 */
/* The select sits in a `static inline short` helper so that it stays a
   branch: jump.c turns an if into movz/movn only when its arm sets a
   full register, and the inline's short return value is a subreg. */
int func_002D95D8(char *arg0) {
    char *p = *(char **)(arg0 + 0x34);
    *(short *)(p + 2) = pauseFlagState_r002D95D8();
    return 0;
}

/* Scans the object's 24 effect slots: a slot whose entry flag is clear, whose
   "used" byte is set, and whose table word is zero is skipped.  Slot 7 also
   skips a live, in-range material.  The remaining slots dispatch by slot
   number: most first test the material on the shared record, and every slot
   that is still live is handed to the effect runner with the "run" flag. */
typedef struct {
    char pad00[0x44];
    char *entries[0x18];
    unsigned char used[0x18];
} EffectSlots_2D9600;

extern int D_00261920[];

extern void func_002DF158(char *, int);

int func_002D9600(EffectSlots_2D9600 *o)
{
    int i;

    for (i = 0; i < 0x18; i++) {
        char *entry;
        unsigned char id;

        if (o->entries[i] == 0)
            continue;
        if (o->used[i] != 0)
            continue;
        if (D_00261920[i] == 0)
            continue;
        if (i == 7
            && *(short *)(o->entries[7] + 0xAA) == 0x4A
            && *(unsigned char *)(o->entries[0] + 0x42)
                   != *(unsigned char *)(o->entries[0] + 0x43))
            continue;
        switch (i - 1) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 9:
        case 10:
        case 11:
            entry = o->entries[0];
            if ((*(unsigned long long *)(entry + 0x40) & 0xFFFF0000ULL) != 0x99990000ULL)
                goto call;
            id = *(unsigned char *)(entry + 0x40);
            if (id < 0x4D)
                goto call;
            if (id < 0x92)
                continue;
            break;
        }
    call:
        func_002DF158(o->entries[i], 1);
    }
    return 4;
}

int func_002D9798(int *arg0)
{
    int min;
    int v;
    int slot;
    int count;
    int off;

    F70997ba9_FUN_002FC560(66, 68);
    F70997ba9_FUN_002FC560(71, 11);
    F70997ba9_FUN_0027C540(0);
    min = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11613), -1);
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11625), -1);
    if (v >= min)
        min = v;
    if (*(int *)0x1A79F0 != 0) {
        v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11614), -1);
        if (v >= min)
            min = v;
    }
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11626), -1);
    if (v >= min)
        min = v;
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11627), -1);
    if (v >= min)
        min = v;
    v = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11599), -1);
    if (v >= min)
        min = v;
    slot = (arg0[8] - min) >> 1;
    if (slot <= 1)
        slot = 2;
    count = arg0[9] / (*(int *)0x1A79F0 != 0 ? 7 : 6);
    F70997ba9_FUN_0027F120();
    off = count - 6;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(11613), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(11625), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(11626), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(11627), -1);
    off += count;
    F70997ba9_FUN_0027F5B8(slot, off, 0x80FFA888L, F70997ba9_FUN_00288FB8(11599), -1);
    F70997ba9_FUN_0027F110();
    F70997ba9_FUN_0027C660();
    return 2;
}

/* func_002D99E8 is built from 002D99E8-g8.c for small-data access. */



/* func_002D9DA0 is in 002D5E98-texture.c. */

/* The screen position the object is drawn at, and the 64-bit packet its draw call carries. */
typedef struct {
    char pad[0x160];
    short x;
    short y;
} ScreenPos_2DA118;

extern ScreenPos_2DA118 D_001A6480;
extern unsigned long long D_001C5208;

typedef struct {
    char pad[0x34];
    int flags;
    int width;
    int height;
    char pad2[4];
    int state;
    char pad3[0x10];
    int count;
    int value;
} Object_2DA118;

extern void func_0027E018(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws the object at the screen position in D_001A6480, sized by the object's own width
   and height. The draw's colour is a grey 0x808080 whose top byte comes from the object's
   counter: with the 0x40000 flag set it is the counter itself, scaled and clamped, and
   without it the colour is plain 0x80808080. Returns 0 when the object draws nothing. */
int func_002DA118(Object_2DA118 *object)
{
    int state = object->state;
    int shade;
    unsigned long long color;

    if (state < 2) {
        return 0;
    }
    if (object->count < 0) {
        return 0;
    }
    if ((object->flags & 0x40000) != 0) {
        if (state == 2) {
            shade = object->value << 5;
            if (shade > 0x80) {
                shade = 0x80;
            }
        } else {
            shade = (4 - object->value) << 5;
            if (shade < 0) {
                shade = 0;
            }
        }
        color = (shade << 24) | 0x808080;
        func_0027E018(0, 0, D_001A6480.x, D_001A6480.y, 0, 0, object->width, object->height, color, D_001C5208);
    } else {
        color = 0x80808080ULL;
        func_0027E018(0, 0, D_001A6480.x, D_001A6480.y, 0, 0, object->width, object->height, color, D_001C5208);
    }
    return 0x10;
}

/* Re-initialises a state block: clears field 68, builds two sub-records from the flag word at field 52 masked with 0x200, substitutes a default record for any that came back zero, then clears field 92, sets fields 84 and 80 to -1 and returns 0. */
s32 func_002DA238 (s32 self)
{
  *(s32 *) (self + 68) = 0;
  *(s32 *) (self + 72) = func_002DE550 (*(s32 *) (self + 52) & 0x200);
  *(s32 *) (self + 76) = func_002DE550 (*(s32 *) (self + 52) & 0x200);
  if ((*(s32 *) (self + 52) & 0x200) == 0)
    {
      if (*(s32 *) (self + 72) == 0)
        *(s32 *) (self + 72) = func_002DE550 (1);
      if (*(s32 *) (self + 76) == 0)
        *(s32 *) (self + 76) = func_002DE550 (1);
    }
  *(s32 *) (self + 92) = 0;
  *(s32 *) (self + 80) = -1;
  *(s32 *) (self + 84) = -1;
  return 0;
}

typedef struct {
    char reserved[0x44];
    int state;
    unsigned int first, second;
    int index, pending;
} Handles_2DCB28;

extern void func_002B7CE0(int);

int func_002DA2D0(Handles_2DCB28 *object) {
    object->first = func_002DE618(object->first);
    object->second = func_002DE618(object->second);
    object->index = -1;
    object->pending = -1;
    object->state = -1;
    func_002B7CE0(1);
    return 0;
}

/* func_002DA328 is in 002D5E98-stream.c. */

INCLUDE_ASM("asm/game", func_002DA9A8);

INCLUDE_ASM("asm/game", func_002DAD18);

/* func_002DAE90 is in 002D5E98-g8.c. */

/* The map screen's frame: the page and image being shown and the two frame textures. */
typedef struct {
    char pad[0x230];
    int page;
    int image;
    char pad238[0x268 - 0x238];
    unsigned long long tex0;
    char pad270[8];
    unsigned long long tex1;
} Dialog2DAF68;
extern char *D_001F2854;
extern char D_0025E680[];
extern int D_00261998[];
/* The frame counter as an incomplete sda array: retail's tied absolute macro load. */
extern int D_001B1598[] __attribute__((sda));
extern void func_002FC560(int, unsigned long long);
extern void func_0028F278(unsigned long long, int, int, int, int, int, int, int, int, int);

/* Draws the textured frame around the map dialog, scrolling the inner texture. */
int func_002DAF68(void)
{
    int inset[4];
    int left;
    int top;
    int width;
    int height;
    int style;
    int border;
    int scroll;
    int page;
    Dialog2DAF68 *dialog;

    if (((Dialog2DAF68 *)&D_001C4FA0)->image < 0)
        return 0;
    page = ((Dialog2DAF68 *)&D_001C4FA0)->page;
    if (page == 5 || page == 10 || page == 15)
        return 0;
    if (page >= 21 && page != 24)
        return 0;

    if (D_001F2854 == D_0025E680) {
        inset[1] = 50;
        inset[2] = 38;
        inset[3] = 25;
        left = 29;
        top = 77;
        width = 191;
        height = 178;
        inset[0] = 0;
    } else {
        inset[1] = 38;
        inset[2] = 28;
        inset[3] = 20;
        left = 30;
        top = 76;
        inset[0] = 0;
        width = 153;
        height = 140;
    }
    dialog = (Dialog2DAF68 *)&D_001C4FA0;
    style = D_00261998[dialog->image];
    scroll = (D_001B1598[0] + dialog->image * 0x2AB) % 2048;
    border = inset[style];

    func_002FC560(0x47, 0);
    func_002FC560(8, 0);
    if (style == 0) {
        func_0028F278(dialog->tex0, left << 4, top << 4, 7, 7, width << 4, height << 4, 0, 0, 0x80);
    } else {
        func_0028F278(dialog->tex0, (left + border) << 4, (top + border) << 4, 7, 7,
                      (width - border * 2) << 4, (height - border * 2) << 4, scroll, 0, 0x80);
        func_002FC560(8, 5);
        func_0028F278(dialog->tex1, left << 4, top << 4, 7, 7, width << 4, height << 4, 0, 0, 0x80);
    }
    func_002FC560(0x47, 0x360B);
    return 4;
}

/* func_002DB3C0 is in 002DB3C0.c. */

/* Choice list input: close, back, row navigation and cycling the selected row's value. */
int func_002DB648(ChoiceMenu *menu)
{
    CtxB6 *menuSystem = (CtxB6 *)&D_001F2840;
    int result;
    int previous;

    if (menuSystem->owner->focus != menu)
        return 0;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x900) != 0 && menuSystem->active == 0)
        return 1;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x10) != 0) {
        CtxB6 *menus = (CtxB6 *)&D_001F2840;
        int back = menus->owner->back;

        /* The shared exit keeps the 0/-1 choice a branch rather than a conditional move. */
        if (back != 0) {
            menus->next = back;
        } else if (menus->active == 0) {
            result = -1;
            goto back_done;
        }
        result = 0;
back_done:
        return result;
    }

    previous = menu->selected;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x1000) != 0 && previous != 0)
        menu->selected = previous - 1;
    if ((((Pad2D7B18 *)D_00138180)->pressed & 0x4000) != 0) {
        int selected = menu->selected;

        if (menu->rows[selected + 1].text != 0)
            menu->selected = selected + 1;
    }
    if (previous != menu->selected)
        func_002DF190(1, 0x11);

    {
        ChoiceRow *row = &menu->rows[menu->selected];
        int *choices = row->choices;
        int count = 0;

        if (choices[0] != 0) {
            do {
                count++;
            } while (choices[count] != 0 && count < 4);
        }
        if ((((Pad2D7B18 *)D_00138180)->pressed & 0x40) != 0) {
            unsigned char *value = row->value;

            if (value != 0) {
                *value = (*value + 1) % count;
                func_002DF190(0, 0x11);
            }
        }
    }
    return 0;
}

/* func_002DB7F0 is in 002DB7F0.c. */

INCLUDE_ASM("asm/game", func_002DB988);

int func_002DBAA8(void)
{
    extern s32 D_00138344;
    extern s32 D_001F2858;
    extern void func_0025E680(void);
    if (D_00138344 & 0x40)
        D_001F2858 = (s32)func_0025E680;
    return 0;
}

extern void func_00288D88(int, int, int, int);

int func_002DBAD0(char *p) { int x = *(int *)(p + 0x18); int y = *(int *)(p + 0x1C); int w = *(int *)(p + 0x20); int h = *(int *)(p + 0x24); func_00288D88(x, x + w, y, y + h); return 2; }

extern char *D_001F2854;

int func_002DBB08(char *object) {
    *(int *)(D_001F2854 + 0x12C) = 0;
    *(int *)(object + 0x54) = func_002DE550(0);
    return 0;
}

undefined8 func_002DBB48(int param_1)
{
  undefined4 uVar1;
  uVar1 = func_002DE618(*(undefined4 *)(param_1 + 0x54));
  *(undefined4 *)(param_1 + 0x54) = uVar1;
  return 0;
}

extern int D_001A7420 __attribute__((sda));
extern unsigned int D_00138344;
typedef struct { char reserved00[0x14]; char *object; int value; char reserved1C[0xC8]; int clear; } SceneState;
extern SceneState ref_L00_002DBB78_00;
int func_002DBB78(void)
{
    if (D_001A7420 != 16 && D_001A7420 != 1) {
        ref_L00_002DBB78_00.value = *(int *)(ref_L00_002DBB78_00.object + 0xE0);
        return 0;
    }
    {
        unsigned int flags = D_00138344;
        if (flags & 0x20) {
            ref_L00_002DBB78_00.clear = 0;
            ref_L00_002DBB78_00.value = *(int *)(ref_L00_002DBB78_00.object + 0xE0);
            *(int *)(ref_L00_002DBB78_00.object + 0x12C) = 1;
        } else if (flags & 0x10) {
            ref_L00_002DBB78_00.value = *(int *)(ref_L00_002DBB78_00.object + 0xE0);
            *(int *)(ref_L00_002DBB78_00.object + 0x12C) = 0;
        }
    }
    return 0;
}

/* func_002DBC10 is defined in 002DBC10.c. */

#define MACRO_ADDR __attribute__((section(".sdata")))

/* MACRO_ADDR: lui/lw where retail has them, $gp-relative in a delay slot
   (r1_func_0021F7D0, r1_func_002229B0). */
extern int r1_D_0015EE84 MACRO_ADDR;

extern int r1_D_001D48A8[];

/* rac1-decomp src/game/pause.c: func_00222D70 */
/* `r1_D_001D48A8[(unsigned)r1_D_0015EE84 % 19]`; the older near-miss
   predated MACRO_ADDR. */
int func_002DBE80(char *arg0) {
    *(int *)(arg0 + 0x34) = r1_D_001D48A8[(unsigned int)r1_D_0015EE84 % 19];
    return 0;
}

extern int D_00138180[];
extern int D_001F2974;
extern void func_002DF190(int, int);

int func_002DBEC0(char *object)
{
    int flags;
    {
        int *state = D_00138180;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (D_001F2974 == 0)
            return 1;
    }
proceed:
    {
        int *state = D_00138180;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = (char *)&D_001F2840;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    {
        int old = *(int *)(object + 0x40);
        if (flags & 0x40)
            *(int *)(object + 0x40) = (old + 1) % 30;
        else if (flags & 0x20)
            *(int *)(object + 0x40) = (old + 29) % 30;
        if (*(int *)(object + 0x40) != old)
            func_002DF190(1, 17);
    }
    return 0;
}


extern int D_00138180[];
extern int D_001F2974;
extern void func_002DF190(int, int);

int func_002DBF98(char *object)
{
    int flags;
    {
        int *state = D_00138180;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (D_001F2974 == 0)
            return 1;
    }
proceed:
    {
        int *state = D_00138180;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = (char *)&D_001F2840;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x2040) {
        *(int *)(object + 0x54) = (*(int *)(object + 0x54) + 1) % 12;
        func_002DF190(1, 17);
    } else if (flags & 0x8020) {
        *(int *)(object + 0x54) = (*(int *)(object + 0x54) + 11) % 12;
        func_002DF190(1, 17);
    }
    return 0;
}

/* Two-branch draw set-up: copies a 2-byte record from one of two tables into a 16-byte local, then issues a draw call with five float arguments (scale, per-instance angle, two constants, colour value) plus a 64-bit attribute word, a geometry handle, a fifth integer argument -1 and a local buffer. */
int func_002DC090(char *s0)
{
    signed char local[16];
    float y;

    func_0027C540_1(0);
    if (*(int *)(s0 + 56) != 0) {
        *(TWO_F73af1964 *)local = *(TWO_F73af1964 *)D_L01_001ABE90;
        func_0027F538(4, *(int *)(s0 + 36) / 2 - 8, 0x80FFA888, local, -1);
        y = (float)(*(int *)(s0 + 36) * 8);
        func_0028F410(640.0f, y, 128.0f, 256.0f, 0.0f, 32, 16, func_0028E640(func_0028E588(0xE99D, 6)));
    } else {
        *(TWO_F73af1964 *)local = *(TWO_F73af1964 *)D_L01_001ABE98;
        func_0027F538(*(int *)(s0 + 32) - 24, *(int *)(s0 + 36) / 2 - 8, 0x80FFA888, local, -1);
        y = (float)(*(int *)(s0 + 36) * 8);
        func_0028F410(192.0f, y, 128.0f, 256.0f, 3.1415927f, 32, 16, func_0028E640(func_0028E588(0xE99D, 6)));
    }
    func_0027C660_1();
    return 2;
}


INCLUDE_ASM("asm/game", func_002DC3C8);

/* func_002DC720 is matched in its own unit, src/game/002DC720.c (its jump table). */

/* func_002DC900 is built from 002DC900-g8.c for small-data access. */

/* func_002DCAB8 is built from 002D5E98-g8.c for small-data access. */

int func_002DCB28(Handles_2DCB28 *object) {
    object->first = func_002DE618(object->first);
    return 0;
}




INCLUDE_ASM("asm/game", func_002DDA10);

