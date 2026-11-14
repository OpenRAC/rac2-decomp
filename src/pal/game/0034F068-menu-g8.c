/* func_PAL_0034F068 (3,316 bytes): the PAL copy of func_0034CEA0 (src/game/0034CEA0-menu-g8.c), the
 * weapon quick-select HUD. Hud.ammoIcon is followed by 0x10 more bytes and boltText is 0xB0, so
 * the fields after it move +0x20 and the func_0034CAE8 argument is 8 instead of 10. The larger object also moves PRE's expression-hash
 * buckets: -frac2-gcse-hash-fp-59 and -frac2-gcse-hash-parm-91 (tools/compiler/transformers/
 * gcse_hash_fp_59.py, owner ruling of 14 November 2026) take the place of the v1.01 unit's fp-54
 * and parm-85 and give retail's spill-slot order. The v1.01 unit's FAKEMATCH sites are kept
 * (fakematches allowed in PAL and USA v2.00 functions, owner ruling of 14 November 2026).
 * The v1.01 header follows.
 */
/* func_0034CEA0 (3,316 bytes, boot): the weapon quick-select HUD. A FAKEMATCH unit (owner ruling,
 * 13 November 2026; config/fakematch.tsv): three marked sites below. It builds with the switches of
 * tools/compiler/transformers/cea0_rules.py and earlier ones (config/cflags.txt;
 * docs/build/compiler-notes.md). */
#include "include_asm.h"

typedef unsigned int UIWord;
typedef union { UIWord word; unsigned char bytes[4]; } UIColor;
typedef struct { int present; char pad[20]; int item; } MenuSlot;
typedef struct { MenuSlot *slots; } MenuSlots;
typedef struct { int present; unsigned char enabled; char pad5[0x37]; unsigned short icon; char pad3E[0x2E]; int capacity; char pad70[0x18]; unsigned short flags; char pad8A[4]; unsigned short maxAmmo; char pad90[0x50]; } ItemRecord;

typedef struct { char data[0x3C]; } Ui3C;
typedef struct { char data[0x48]; } Ui48;
typedef struct { char data[0x4C]; } Ui4C;
typedef struct { char pad00[0x10]; float value; char pad14[8]; int state; char pad20[0x68]; } Ui88;
typedef struct { char pad00[0x10]; float value; char pad14[8]; int state; char pad20[0x74]; } Ui94;
typedef struct {
    Ui4C ammoDigits[2];
    Ui4C ammoBar;
    char ammoText[0x1C];
    Ui48 ammoIcon;
    char padAmmoIcon[0x10];
    Ui3C selectedIcon;
    Ui4C boltDigits[2];
    char boltText[0xB0];
    int *boltCount;
    Ui4C background;
    Ui4C alphaSource;
    Ui4C slotColors[8];
    Ui4C prompt;
    Ui3C slots[8];
    char pad7E4[4];
    char meter[0x404];
    Ui88 hideWidgets[6];
    Ui94 ammoWidgets[3];
    Ui88 middleWidget;
    Ui94 endAmmoWidget;
    Ui94 boltWidgets[4];
    char pad1444[8];
    Ui88 warningWidgets[2];
    int ammo, maxAmmo, ammoTimer, ammoHidden, boltTimer, boltHidden;
    int hideTimer, hidden, selectionMode, selected, boltMode, alternateBolts;
} Hud;

extern MenuSlots *D_001B18D4[] __attribute__((sda));
extern unsigned char D_00139568[];
extern ItemRecord D_00239BA0[];
extern int D_00139868[], D_00139688[];
typedef struct { char pad00[0x22B4]; unsigned char state; char pad22B5[0x217]; int value; } HeroHudState;
extern HeroHudState D_00189E20;
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern float D_001AE6EC __attribute__((sda));
extern char D_001AE6F0[], D_001ADF98[];
extern int func_002B0D70(void);
extern void func_00335E68(void *, int);
extern UIColor *func_00335E20(void *);
extern void func_00336920(void *, int, int);
extern void *func_0034E5B8(void *);
extern void func_00336F20(int, int *, int *, int *);
extern void func_00336498(void *, int, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern int func_0028E260(void);
extern void func_0034CAE8(void *, int, int);
extern void func_00349B20(void *);
extern void func_00349680(void *, int);
extern void func_0034A4A8(void *, int);
extern void func_0034A4B0(void *, int);
extern void func_0034AC10(void *);
extern void func_00349AE0(void *, int);
extern void func_00349630(void *, int);
extern void func_00349678(void *, float);
extern float *func_00336318(void *);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(const char *);
extern float func_003495A0(void *);
extern int func_003495C8(void *, int);
#define ITEM(n) (&D_00239BA0[D_00139568[n]])

void func_PAL_0034F068(Hud *self)
{
    int x, y, color, rgb;
    int selX, selY, selColor;
    Ui3C *slotWidget;
    Ui3C *slotAlphaWidget;
    int selected, present;
    int previous, item, threshold, low;
    UIWord limit;
    Ui48 *widget;
    float scale, width;
    Ui94 *a0;
    Ui94 *bolt;
    UIWord slotWord;
    self->alternateBolts = func_002B0D70();
    if (D_001B18D4[0]) {
        int i;
        for (i = 0; i < 8; i++) {
            if (!D_001B18D4[0]->slots[i].present)
            func_00335E68(&self->slots[i], 0);
            else {
                func_00335E68(&self->slots[i], 1);
                func_00336920(&self->slots[i], D_001B18D4[0]->slots[i].present, 0);
            }
            widget = (Ui48 *)func_0034E5B8(D_001A8CFC[0] + 0x36F28) + i;
            func_00335E68(widget, 0);
            /* FAKEMATCH: volatile x store + volatile D_001B18D4 load below keep the x/y/color zero stores ahead of the slot-table load (retail +0x114..+0x124) */
            *(volatile int *)&x = 0; y = 0; color = 0;
            func_00336F20((*(MenuSlots * volatile *)&D_001B18D4[0])->slots[i].item, &x, &y, &color); /* FAKEMATCH: volatile load, see above */
            {
                UIColor *c = func_00335E20(&self->slots[i]);
                c->word = (c->word & 0xFF000000) | (color & 0xFFFFFF);
            }
            widget = (Ui48 *)func_0034E5B8(D_001A8CFC[0] + 0x36F28) + i;
            func_00335E68(widget, 1);
            func_00336498(widget, x, y);
            func_00336B90(widget, 100);
            func_00336B98(widget, 100);
            {
                ItemRecord *rec = ITEM(D_001B18D4[0]->slots[i].item);
                if (rec->present) {
                    int enabled = rec->enabled != 0;
                    int capacity = rec->capacity;
                    if (capacity || enabled) {
                        func_00336B90(widget, capacity);
                        if (ITEM(D_001B18D4[0]->slots[i].item)->capacity > 0)
                            func_00336B98(widget, D_00139868[D_001B18D4[0]->slots[i].item] >> 5);
                    }
                }
            }
        }
    }
    if (self->selectionMode) selected = self->selected;
    else selected = func_0028E260();
    selX = 0; selY = 0; selColor = 0;
    present = ITEM(selected)->present;
    func_00336F20(selected, &selX, &selY, &selColor);
    func_00335E20(&self->selectedIcon)->word = selColor;
    if (selected && present) {
        func_00336920(&self->selectedIcon, ITEM(selected)->icon, 0);
        if (!self->selectionMode)
        func_0034CAE8(self, ITEM(selected)->icon, 8);
    }
    func_00349B20(&self->ammoWidgets[0]);
    func_00349B20(&self->ammoWidgets[1]);
    func_00349B20(&self->ammoWidgets[2]);
    func_00349680(&self->middleWidget, 1);
    func_00349B20(&self->endAmmoWidget);
    func_0034A4A8(self->meter, D_00189E20.value);
    {
        unsigned char state = D_00189E20.state;
        if (!state) goto heroFallback;
        if (state == 1)
        func_0034A4B0(self->meter, 4);
        else {
heroFallback:
            func_0034A4B0(self->meter, D_001A7A00[0]);
        }
    }
    func_0034AC10(self->meter);
    func_00349680(&self->hideWidgets[0], 1);
    func_00349680(&self->hideWidgets[1], 1);
    func_00349680(&self->hideWidgets[2], 1);
    func_00349680(&self->hideWidgets[3], 1);
    func_00349680(&self->hideWidgets[4], 1);
    {
        UIWord w = func_00335E20(&self->slots[0])->word;
        {
            int i;
            for (i = 1; i < 8; i++) {
                UIColor *c = func_00335E20(&self->slots[i]);
                c->word = (c->word & 0xFFFFFF) | ((w >> 24) << 24);
            }
        }
    }
    func_00349680(&self->hideWidgets[5], 1);
    slotWord = func_00335E20(&self->slotColors[0])->word;
    {
        int i;
        for (i = 0; i < 8; i++) {
            previous = i;
            previous--;
            if (previous < 0) previous = 7;
            if (D_001B18D4[0] && D_001B18D4[0]->slots[i].present) {
                MenuSlot *slot = &D_001B18D4[0]->slots[i];
                ItemRecord *rec;
                item = slot->item;
                rec = ITEM(item);
                if (rec->present && !D_00139688[item] && rec->flags) {
                    Ui4C *w = &self->slotColors[previous];
                    /* FAKEMATCH: do { } while (0) adds loop notes, so flow counts the 0x70202080 register's refs at a deeper loop level; global then allocates it (s6) before `low`, as retail */
                    do { UIWord color = 0x70202080;
                    func_00335E20(w)->word = color; } while (0);
                } else {
                    UIWord color = 0x60442D00;
                    func_00335E20(&self->slotColors[previous])->word = color;
                }
            }
            {
                UIColor *c = func_00335E20(&self->slotColors[previous]);
                c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
            }
        }
    }
    {
        UIColor *c = func_00335E20(&self->background);
        c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
    }
    {
        UIWord promptAlpha = func_00335E20(&self->alphaSource)->word & 0xFF000000;
        {
            UIColor *c = func_00335E20(&self->prompt);
            c->word = (c->word & 0xFFFFFF) | promptAlpha;
        }
    }
    {
        UIWord alpha, alpha2;
        alpha = func_00335E20(&self->ammoIcon)->word & 0xFF000000;
        alpha2 = func_00335E20(&self->selectedIcon)->word & 0xFF000000;
        limit = func_00335E20(self)->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = func_00335E20(&self->ammoIcon);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = func_00335E20(&self->selectedIcon);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }
    bolt = &self->boltWidgets[0];
    func_00349B20(bolt);
    func_00349B20(&self->boltWidgets[1]);
    func_00349B20(&self->boltWidgets[2]);
    func_00349B20(&self->boltWidgets[3]);
    if (self->ammoTimer && --self->ammoTimer == 0) { Ui94 *w1; if (!((w1 = &self->ammoWidgets[0])->state)) {
        func_00349AE0(w1, 0);
        func_00349AE0(&self->ammoWidgets[1], 0);
        func_00349AE0(&self->ammoWidgets[2], 0);
        func_00349630(&self->middleWidget, -1);
        func_00349AE0(&self->endAmmoWidget, 0);
        self->ammoHidden = 1;
    } }
    if (self->boltTimer && --self->boltTimer == 0) if (!bolt->state) {
        func_00349AE0(bolt, 0);
        func_00349AE0(&self->boltWidgets[1], 0);
        func_00349AE0(&self->boltWidgets[2], 0);
        self->boltHidden = 1;
        func_00349AE0(&self->boltWidgets[3], 0);
    }
    if (self->hideTimer && --self->hideTimer == 0 && self->hidden != 1) {
        self->hidden = 1;
        func_00335E68(&self->prompt, 0);
        func_00349630(&self->hideWidgets[0], -1);
        func_00349630(&self->hideWidgets[1], -1);
        func_00349630(&self->hideWidgets[2], -1);
        func_00349630(&self->hideWidgets[3], -1);
        func_00349630(&self->hideWidgets[4], -1);
        func_00349630(&self->hideWidgets[5], -1);
        func_00349678(&self->hideWidgets[0], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
        func_00349678(&self->hideWidgets[1], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
        func_00349678(&self->hideWidgets[2], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
        func_00349678(&self->hideWidgets[3], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
        func_00349678(&self->hideWidgets[4], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
        func_00349678(&self->hideWidgets[5], D_001A7B90[0] ? 0.14f : 0.11666667461395264f);
    }
    if (selected && present) {
        int count;
        if (ITEM(selected)->capacity > 0) {
            width = (float)(D_00139868[selected] >> 5) / (float)ITEM(selected)->capacity;
            scale = D_001AE6EC * (0.5f - width * 0.5f);
            width *= 30.0f;
            scale = scale > 1.0f ? scale : 1.0f;
            width *= scale;
            width = width < 30.0f ? width : 30.0f;
        } else width = 30.0f;
        width = width > 0.0f ? width : 0.0f;
        *func_00336318(&self->ammoBar) = width;
        {
            int ammo = D_00139688[selected];
            int max;
            self->ammo = ammo;
            low = 1;
            max = ITEM(selected)->maxAmmo;
            self->maxAmmo = max;
            func_00115DA8(self->ammoText, D_001AE6F0, ammo, max);
        }
        count = func_001157AC(self->ammoText) - 3;
        if (count > 5) count = 5;
        if (count < 0) count = 0;
        width = (float)count;
        *func_00336318(self) = width;
        *func_00336318(&self->ammoDigits[1]) = width;
        threshold = (int)((float)ITEM(selected)->maxAmmo * 0.1f);
        if (!threshold) threshold = 1;
        if (threshold < D_00139688[selected]) low = 0;
        if (!D_00139688[selected]) {
            func_003495A0(&self->warningWidgets[0]);
            func_003495A0(&self->warningWidgets[1]);
        }
        if (low) {
            func_003495C8(&self->warningWidgets[0], 1);
            func_003495C8(&self->warningWidgets[1], 1);
        } else {
            func_003495C8(&self->warningWidgets[0], 0);
            func_003495C8(&self->warningWidgets[1], 0);
            a0 = &self->ammoWidgets[0];
            if (!a0->state) {
                Ui94 *a1 = &self->ammoWidgets[1];
                a0->value = 1.0f;
                a1->value = 1.0f;
                a0->state = 1;
                a1->state = 1;
                func_00349B20(a0);
                func_00349B20(a1);
            }
        }
    }
    func_00349680(&self->warningWidgets[0], 1);
    func_00349680(&self->warningWidgets[1], 1);
    {Ui94 *w3 = &self->ammoWidgets[0];
    if (w3->state || !present) {
        UIWord alpha, alpha2;
        alpha = func_00335E20(self)->word & 0xFF000000;
        alpha2 = func_00335E20(&self->ammoDigits[1])->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = func_00335E20(self);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = func_00335E20(&self->ammoDigits[1]);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }}
    rgb = *(self->boltMode ? &self->alternateBolts : self->boltCount);
    func_00115DA8(self->boltText, D_001ADF98, rgb);
    {
        int count;
        count = func_001157AC(self->boltText) - 1;
        if (count > 6) count = 6;
        if (count < 0) count = 0;
        width = (float)count;
        *func_00336318(&self->boltDigits[0]) = width;
        *func_00336318(&self->boltDigits[1]) = width;
    }
    func_0034AC10(self->meter);
}
