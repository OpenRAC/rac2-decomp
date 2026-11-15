#include "common.h"

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
    char pad0[0x498];
    float *origin;              /* +0x498: position the widgets are placed from */
    char pad49C[4];
    char detail[0x18];          /* +0x4A0 */
    char name[0x44];            /* +0x4B8 */
    int column;                 /* +0x4FC */
    int row;                    /* +0x500 */
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

/* Moves the cursor on the item grid, shows the name and ammo of the item under it and returns the choice when cross is pressed. */
int func_00346C60(ItemMenu *menu, int buttons)
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
    int oldSelection = menu->column + menu->row * 4;
    int selection, nextValue;
    int *color;
    int entry, item, ammo, maxAmmo;
    ItemRecord *record, *initialRecord;
    char *text;

    if (buttons & 0x1000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = menu->row - 1;
        menu->row = nextValue < 0 ? 5 : nextValue;
    } else if (buttons & 0x4000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = menu->row + 1;
        menu->row = nextValue <= 5 ? nextValue : 0;
    } else if (buttons & 0x8000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = menu->column - 1;
        menu->column = nextValue < 0 ? 3 : nextValue;
    } else if (buttons & 0x2000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = menu->column + 1;
        menu->column = nextValue <= 3 ? nextValue : 0;
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
    if (oldSelection != selection)
        PingPongBlendValues(0, 0, 1, 0, 1);
    color = GetFieldC((char *)menu + 0xE4);
    *color = PingPongBlendValues(0x60442D00, 0x70FFFEED, 20, 0, 0);

    SetFirstFloat4((char *)menu + 0x0, pos0[0] + menu->origin[0], pos0[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x4C, pos4C[0] + menu->origin[0], pos4C[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x130, pos130[0] + menu->origin[0], pos130[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x98, pos98[0] + menu->origin[0], pos98[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0xE4,
                  cursor[0] + menu->origin[0] + (float)menu->column * 53.5f,
                  cursor[1] + menu->origin[1] + (float)menu->row * 47.0f, 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x17C, pos17C[0] + menu->origin[0], pos17C[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x210, pos210[0] + menu->origin[0], pos210[1] + menu->origin[1], 0.0f, 0.0f);

    gSelectedItemMaterial = -1;
    if (selection >= 0) {
        entry = D_00259F58[selection][3];
        item = gItemSlotToRecord[entry];
        initialRecord = &gWeaponTable_00239BA0[item];
        if (initialRecord->byte04) {
            gItemOwnedFlags[entry] = 1;
            D_001A7B30[entry] = 1;
        }
        if (gItemOwnedFlags[entry]) {
            text = menu->detail;
            gSelectedItemMaterial = gWeaponTable_00239BA0[gItemSlotToRecord[entry]].material;
            Sprintf(menu->name, GetLocalizedString(gWeaponTable_00239BA0[gItemSlotToRecord[entry]].name));
            record = &gWeaponTable_00239BA0[gItemSlotToRecord[entry]];
            ammo = gItemAmmoCounts[entry];
            maxAmmo = record->maxAmmo;
            if (record->usesAmmo) {
                text += Sprintf(text, D_001AE528, GetLocalizedString(0x2DC9));
                if (ammo < 1000)
                    text += Sprintf(text, D_001AE530, ammo);
                else
                    text += Sprintf(text, D_001AE538, ammo / 1000, ammo % 1000);
                if (maxAmmo < 1000)
                    Sprintf(text, D_001ADF98, maxAmmo);
                else
                    Sprintf(text, D_001AE548, maxAmmo / 1000, maxAmmo % 1000);
            } else {
                Sprintf(text, ref_00346C60_00, GetLocalizedString(0x2DB9));
            }
            if (buttons & 0x40) {
                result = selection;
                PlaySoundFromGlobalBank(4, 0, 0);
                D_001F2880[0] = entry;
            }
        } else {
            menu->detail[0] = 0;
            menu->name[0] = 0;
            if (buttons & 0x40)
                PlaySoundFromGlobalBank(5, 0, 0);
        }
    }

    SetFirstFloat4((char *)menu + 0x258, pos258[0] + menu->origin[0], pos258[1] + menu->origin[1], 0.0f, 0.0f);
    SetFirstFloat4((char *)menu + 0x2A0, pos2A0[0] + menu->origin[0], pos2A0[1] + menu->origin[1], 0.0f, 0.0f);
    return result;
}
