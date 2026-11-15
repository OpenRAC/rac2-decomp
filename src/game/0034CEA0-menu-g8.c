/* func_0034CEA0 (3,316 bytes, boot): the weapon quick-select HUD. A FAKEMATCH unit (owner ruling,
 * 13 November 2026; config/fakematch.tsv): three marked sites below. It builds with the switches of
 * tools/compiler/transformers/cea0_rules.py and earlier ones (config/cflags.txt;
 * docs/build/compiler-notes.md). */
#include "include_asm.h"
#include "names.h"

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
    Ui3C selectedIcon;
    Ui4C boltDigits[2];
    char boltText[0xA0];
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

/* Updates the item and bolt HUD every frame: slot icons and colors, the selected weapon and its ammo, fades and the bolt count. */
void func_0034CEA0(Hud *self)
{
    int x, y, color, boltValue;
    int selX, selY, selColor;
    Ui3C *slotWidget;
    Ui3C *slotAlphaWidget;
    int selected, present;
    int previous, item, threshold, low;
    UIWord limit;
    Ui48 *widget;
    float scale, width;
    Ui94 *ammoWidgetA;
    Ui94 *bolt;
    UIWord slotWord;
    self->alternateBolts = CountItemsAboveBaseline();
    if (gRadialMenuPages[0]) {
        int i;
        for (i = 0; i < 8; i++) {
            if (!gRadialMenuPages[0]->slots[i].present)
            SetFlagValue(&self->slots[i], 0);
            else {
                SetFlagValue(&self->slots[i], 1);
                SetWidgetValuePair(&self->slots[i], gRadialMenuPages[0]->slots[i].present, 0);
            }
            widget = (Ui48 *)ReturnArgument_0034E5B8(D_001A8CFC[0] + 0x36F28) + i;
            SetFlagValue(widget, 0);
            /* FAKEMATCH: volatile x store + volatile D_001B18D4 load below keep the x/y/color zero stores ahead of the slot-table load (retail +0x114..+0x124) */
            *(volatile int *)&x = 0; y = 0; color = 0;
            ChooseItemColors((*(MenuSlots * volatile *)&gRadialMenuPages[0])->slots[i].item, &x, &y, &color); /* FAKEMATCH: volatile load, see above */
            {
                UIColor *c = GetFieldC(&self->slots[i]);
                c->word = (c->word & 0xFF000000) | (color & 0xFFFFFF);
            }
            widget = (Ui48 *)ReturnArgument_0034E5B8(D_001A8CFC[0] + 0x36F28) + i;
            SetFlagValue(widget, 1);
            SetFirstPair(widget, x, y);
            SetMeterMaximum(widget, 100);
            SetMeterValue(widget, 100);
            {
                ItemRecord *rec = ITEM(gRadialMenuPages[0]->slots[i].item);
                if (rec->present) {
                    int enabled = rec->enabled != 0;
                    int capacity = rec->capacity;
                    if (capacity || enabled) {
                        SetMeterMaximum(widget, capacity);
                        if (ITEM(gRadialMenuPages[0]->slots[i].item)->capacity > 0)
                            SetMeterValue(widget, D_00139868[gRadialMenuPages[0]->slots[i].item] >> 5);
                    }
                }
            }
        }
    }
    if (self->selectionMode) selected = self->selected;
    else selected = GetUsableSelectedWeapon();
    selX = 0; selY = 0; selColor = 0;
    present = ITEM(selected)->present;
    ChooseItemColors(selected, &selX, &selY, &selColor);
    GetFieldC(&self->selectedIcon)->word = selColor;
    if (selected && present) {
        SetWidgetValuePair(&self->selectedIcon, ITEM(selected)->icon, 0);
        if (!self->selectionMode)
        SetScreenValueAndRestartFades(self, ITEM(selected)->icon, 10);
    }
    StepMorphAnimation(&self->ammoWidgets[0]);
    StepMorphAnimation(&self->ammoWidgets[1]);
    StepMorphAnimation(&self->ammoWidgets[2]);
    UpdateKeyframeAnimation(&self->middleWidget, 1);
    StepMorphAnimation(&self->endAmmoWidget);
    SetFirstField(self->meter, gHeroState.value);
    {
        unsigned char state = gHeroState.state;
        if (!state) goto heroFallback;
        if (state == 1)
        SetMeterValueAndStartTimers(self->meter, 4);
        else {
heroFallback:
            SetMeterValueAndStartTimers(self->meter, D_001A7A00[0]);
        }
    }
    UpdateMeterScreen(self->meter);
    UpdateKeyframeAnimation(&self->hideWidgets[0], 1);
    UpdateKeyframeAnimation(&self->hideWidgets[1], 1);
    UpdateKeyframeAnimation(&self->hideWidgets[2], 1);
    UpdateKeyframeAnimation(&self->hideWidgets[3], 1);
    UpdateKeyframeAnimation(&self->hideWidgets[4], 1);
    {
        UIWord w = GetFieldC(&self->slots[0])->word;
        {
            int i;
            for (i = 1; i < 8; i++) {
                UIColor *c = GetFieldC(&self->slots[i]);
                c->word = (c->word & 0xFFFFFF) | ((w >> 24) << 24);
            }
        }
    }
    UpdateKeyframeAnimation(&self->hideWidgets[5], 1);
    slotWord = GetFieldC(&self->slotColors[0])->word;
    {
        int i;
        for (i = 0; i < 8; i++) {
            previous = i;
            previous--;
            if (previous < 0) previous = 7;
            if (gRadialMenuPages[0] && gRadialMenuPages[0]->slots[i].present) {
                MenuSlot *slot = &gRadialMenuPages[0]->slots[i];
                ItemRecord *rec;
                item = slot->item;
                rec = ITEM(item);
                if (rec->present && !gItemAmmoCounts[item] && rec->flags) {
                    Ui4C *w = &self->slotColors[previous];
                    /* FAKEMATCH: do { } while (0) adds loop notes, so flow counts the 0x70202080 register's refs at a deeper loop level; global then allocates it (s6) before `low`, as retail */
                    do { UIWord color = 0x70202080;
                    GetFieldC(w)->word = color; } while (0);
                } else {
                    UIWord color = 0x60442D00;
                    GetFieldC(&self->slotColors[previous])->word = color;
                }
            }
            {
                UIColor *c = GetFieldC(&self->slotColors[previous]);
                c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
            }
        }
    }
    {
        UIColor *c = GetFieldC(&self->background);
        c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
    }
    {
        UIWord promptAlpha = GetFieldC(&self->alphaSource)->word & 0xFF000000;
        {
            UIColor *c = GetFieldC(&self->prompt);
            c->word = (c->word & 0xFFFFFF) | promptAlpha;
        }
    }
    {
        UIWord alpha, alpha2;
        alpha = GetFieldC(&self->ammoIcon)->word & 0xFF000000;
        alpha2 = GetFieldC(&self->selectedIcon)->word & 0xFF000000;
        limit = GetFieldC(self)->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = GetFieldC(&self->ammoIcon);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = GetFieldC(&self->selectedIcon);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }
    bolt = &self->boltWidgets[0];
    StepMorphAnimation(bolt);
    StepMorphAnimation(&self->boltWidgets[1]);
    StepMorphAnimation(&self->boltWidgets[2]);
    StepMorphAnimation(&self->boltWidgets[3]);
    if (self->ammoTimer && --self->ammoTimer == 0) { Ui94 *firstAmmoWidget; if (!((firstAmmoWidget = &self->ammoWidgets[0])->state)) {
        StartFadeBackward(firstAmmoWidget, 0);
        StartFadeBackward(&self->ammoWidgets[1], 0);
        StartFadeBackward(&self->ammoWidgets[2], 0);
        StartFadeDirection(&self->middleWidget, -1);
        StartFadeBackward(&self->endAmmoWidget, 0);
        self->ammoHidden = 1;
    } }
    if (self->boltTimer && --self->boltTimer == 0) if (!bolt->state) {
        StartFadeBackward(bolt, 0);
        StartFadeBackward(&self->boltWidgets[1], 0);
        StartFadeBackward(&self->boltWidgets[2], 0);
        self->boltHidden = 1;
        StartFadeBackward(&self->boltWidgets[3], 0);
    }
    if (self->hideTimer && --self->hideTimer == 0 && self->hidden != 1) {
        self->hidden = 1;
        SetFlagValue(&self->prompt, 0);
        StartFadeDirection(&self->hideWidgets[0], -1);
        StartFadeDirection(&self->hideWidgets[1], -1);
        StartFadeDirection(&self->hideWidgets[2], -1);
        StartFadeDirection(&self->hideWidgets[3], -1);
        StartFadeDirection(&self->hideWidgets[4], -1);
        StartFadeDirection(&self->hideWidgets[5], -1);
        SetFadeSpeed(&self->hideWidgets[0], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
        SetFadeSpeed(&self->hideWidgets[1], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
        SetFadeSpeed(&self->hideWidgets[2], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
        SetFadeSpeed(&self->hideWidgets[3], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
        SetFadeSpeed(&self->hideWidgets[4], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
        SetFadeSpeed(&self->hideWidgets[5], gIsPalVideo[0] ? 0.14f : 0.11666667461395264f);
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
        *GetFieldAt38(&self->ammoBar) = width;
        {
            int ammo = gItemAmmoCounts[selected];
            int max;
            self->ammo = ammo;
            low = 1;
            max = ITEM(selected)->maxAmmo;
            self->maxAmmo = max;
            Sprintf(self->ammoText, D_001AE6F0, ammo, max);
        }
        count = strlen_001157AC(self->ammoText) - 3;
        if (count > 5) count = 5;
        if (count < 0) count = 0;
        width = (float)count;
        *GetFieldAt38(self) = width;
        *GetFieldAt38(&self->ammoDigits[1]) = width;
        threshold = (int)((float)ITEM(selected)->maxAmmo * 0.1f);
        if (!threshold) threshold = 1;
        if (threshold < gItemAmmoCounts[selected]) low = 0;
        if (!gItemAmmoCounts[selected]) {
            ResetFadeAmount(&self->warningWidgets[0]);
            ResetFadeAmount(&self->warningWidgets[1]);
        }
        if (low) {
            SwapFadeField0x28(&self->warningWidgets[0], 1);
            SwapFadeField0x28(&self->warningWidgets[1], 1);
        } else {
            SwapFadeField0x28(&self->warningWidgets[0], 0);
            SwapFadeField0x28(&self->warningWidgets[1], 0);
            ammoWidgetA = &self->ammoWidgets[0];
            if (!ammoWidgetA->state) {
                Ui94 *ammoWidgetB = &self->ammoWidgets[1];
                ammoWidgetA->value = 1.0f;
                ammoWidgetB->value = 1.0f;
                ammoWidgetA->state = 1;
                ammoWidgetB->state = 1;
                StepMorphAnimation(ammoWidgetA);
                StepMorphAnimation(ammoWidgetB);
            }
        }
    }
    UpdateKeyframeAnimation(&self->warningWidgets[0], 1);
    UpdateKeyframeAnimation(&self->warningWidgets[1], 1);
    {Ui94 *ammoWidget0 = &self->ammoWidgets[0];
    if (ammoWidget0->state || !present) {
        UIWord alpha, alpha2;
        alpha = GetFieldC(self)->word & 0xFF000000;
        alpha2 = GetFieldC(&self->ammoDigits[1])->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = GetFieldC(self);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = GetFieldC(&self->ammoDigits[1]);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }}
    boltValue = *(self->boltMode ? &self->alternateBolts : self->boltCount);
    Sprintf(self->boltText, D_001ADF98, boltValue);
    {
        int count;
        count = strlen_001157AC(self->boltText) - 1;
        if (count > 6) count = 6;
        if (count < 0) count = 0;
        width = (float)count;
        *GetFieldAt38(&self->boltDigits[0]) = width;
        *GetFieldAt38(&self->boltDigits[1]) = width;
    }
    UpdateMeterScreen(self->meter);
}
