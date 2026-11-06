#include "common.h"

/* func_US2_00347B88, the USA v2.00 copy of func_00346C60: the same C, where the menu fields
   move (origin to +0x438, detail to +0x440, name, column and row down 0x38), the last two
   widgets sit at +0x268 and +0x2C0, and the ammo labels are text ids 0x2C5F and 0x2C4F. */
/* A 4 x 6 item grid menu: the pad moves the cursor (sound 3, wrapping at the edges), the
   widgets are placed from the menu's origin, and an owned entry under the cursor gets its
   name and ammo text (current from D_00139688, maximum from its class record, as in
   00288308.c and 00287E98.c). Cross on an owned entry plays sound 4, records it in
   D_001F2880 and returns the cursor index; on any other entry it plays sound 5. Returns -1
   otherwise. */
typedef struct {
    char pad0[4];
    unsigned char byte04;       /* +0x04: set, the entry counts as owned */
    char pad5;
    short material;             /* +0x06 */
    int name;                   /* +0x08: text id */
    char pad0C[0x7C];
    unsigned short usesAmmo;    /* +0x88 */
    char pad8A[4];
    unsigned short maxAmmo;     /* +0x8E */
    char tail[0x50];
} ItemRecord;

typedef struct {
    char pad0[0x438];
    float *origin;              /* +0x438: position the widgets are placed from */
    char pad43C[4];
    char detail[0x40];          /* +0x440 */
    char name[0x44];            /* +0x480 */
    int column;                 /* +0x4C4 */
    int row;                    /* +0x4C8 */
} ItemMenu;

extern int func_002E5E58(int, int, void *);
extern void *memset(void *, int, unsigned int);
extern int func_002A9588(int, int, int, int, int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern char D_001AE508[], D_001AE510[], D_001AE518[], D_001AE520[];
extern char D_001AE528[], D_001AE530[], D_001AE538[], D_001ADF98[], D_001AE548[];
extern char ref_00346C60_00[];
extern short D_00259F58[][5];
extern ItemRecord D_00239BA0[];
extern unsigned char D_00139568[];
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern unsigned char D_001A7B30[] MACRO_ADDR;
extern int D_00139688[];
extern int D_001ADB10 __attribute__((sda));
extern int D_001F2880[];

int func_US2_00347B88(ItemMenu *menu, int buttons)
{
    float pos0[2] __attribute__((aligned(16)));
    float pos4C[2] __attribute__((aligned(16)));
    float pos130[2] __attribute__((aligned(16)));
    float pos98[2] __attribute__((aligned(16)));
    float cursor[2] __attribute__((aligned(16)));
    float pos17C[2] __attribute__((aligned(16)));
    float pos210[2] __attribute__((aligned(16)));
    float pos258[2] __attribute__((aligned(16)));
    float pos2A0[2] __attribute__((aligned(16)));
    int result = -1;
    int old = menu->column + menu->row * 4;
    int selection, n;
    int *color;
    int entry, item, ammo, maxAmmo;
    ItemRecord *record, *initialRecord;
    char *text;

    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        n = menu->row - 1;
        menu->row = n < 0 ? 5 : n;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        n = menu->row + 1;
        menu->row = n <= 5 ? n : 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        n = menu->column - 1;
        menu->column = n < 0 ? 3 : n;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        n = menu->column + 1;
        menu->column = n <= 3 ? n : 0;
    }
    selection = menu->column + menu->row * 4;

    memset(pos0, 0, 8);
    memset(pos4C, 0, 8);
    memset(pos130, 0, 8);
    memset(pos98, 0, 8);
    __builtin_memcpy(cursor, D_001AE508, 8);
    memset(pos17C, 0, 8);
    __builtin_memcpy(pos210, D_001AE510, 8);
    __builtin_memcpy(pos258, D_001AE518, 8);
    __builtin_memcpy(pos2A0, D_001AE520, 8);
    if (old != selection)
        func_002A9588(0, 0, 1, 0, 1);
    color = func_00335E20((char *)menu + 0xE4);
    *color = func_002A9588(0x60442D00, 0x70FFFEED, 20, 0, 0);

    func_00335E38((char *)menu + 0x0, pos0[0] + menu->origin[0], pos0[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x4C, pos4C[0] + menu->origin[0], pos4C[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x130, pos130[0] + menu->origin[0], pos130[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x98, pos98[0] + menu->origin[0], pos98[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0xE4,
                  cursor[0] + menu->origin[0] + (float)menu->column * 53.5f,
                  cursor[1] + menu->origin[1] + (float)menu->row * 47.0f, 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x17C, pos17C[0] + menu->origin[0], pos17C[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x210, pos210[0] + menu->origin[0], pos210[1] + menu->origin[1], 0.0f, 0.0f);

    D_001ADB10 = -1;
    if (selection >= 0) {
        entry = D_00259F58[selection][3];
        item = D_00139568[entry];
        initialRecord = &D_00239BA0[item];
        if (initialRecord->byte04) {
            D_001A7AF8[entry] = 1;
            D_001A7B30[entry] = 1;
        }
        if (D_001A7AF8[entry]) {
            text = menu->detail;
            D_001ADB10 = D_00239BA0[D_00139568[entry]].material;
            func_00115DA8(menu->name, func_00288FB8(D_00239BA0[D_00139568[entry]].name));
            record = &D_00239BA0[D_00139568[entry]];
            ammo = D_00139688[entry];
            maxAmmo = record->maxAmmo;
            if (record->usesAmmo) {
                text += func_00115DA8(text, D_001AE528, func_00288FB8(0x2C5F));
                if (ammo < 1000)
                    text += func_00115DA8(text, D_001AE530, ammo);
                else
                    text += func_00115DA8(text, D_001AE538, ammo / 1000, ammo % 1000);
                if (maxAmmo < 1000)
                    func_00115DA8(text, D_001ADF98, maxAmmo);
                else
                    func_00115DA8(text, D_001AE548, maxAmmo / 1000, maxAmmo % 1000);
            } else {
                func_00115DA8(text, ref_00346C60_00, func_00288FB8(0x2C4F));
            }
            if (buttons & 0x40) {
                result = selection;
                func_002E5E58(4, 0, 0);
                D_001F2880[0] = entry;
            }
        } else {
            menu->detail[0] = 0;
            menu->name[0] = 0;
            if (buttons & 0x40)
                func_002E5E58(5, 0, 0);
        }
    }

    func_00335E38((char *)menu + 0x268, pos258[0] + menu->origin[0], pos258[1] + menu->origin[1], 0.0f, 0.0f);
    func_00335E38((char *)menu + 0x2C0, pos2A0[0] + menu->origin[0], pos2A0[1] + menu->origin[1], 0.0f, 0.0f);
    return result;
}
