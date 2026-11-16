/* func_US2_0034DBE0 (3,316 bytes): the USA v2.00 copy of func_0034CEA0 (src/game/0034CEA0-menu-g8.c), the
 * weapon quick-select HUD. Hud.ammoIcon is followed by 0x10 more bytes and boltText is 0xB0, so
 * the fields after it move +0x20. The larger object also moves PRE's expression-hash
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

extern MenuSlots *g_radial_menu_pages[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern ItemRecord g_weapon_table[];
extern int g_help_entry_state[], g_item_ammo_counts[];
typedef struct { char pad00[0x22B4]; unsigned char state; char pad22B5[0x217]; int value; } HeroHudState;
extern HeroHudState g_hero_state;
extern int g_player_stats[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));
extern float g_hud_ammo_scale_factor __attribute__((sda));
extern char g_str_hud_ammo_format[], g_str_count_format[];
extern int save_count_items_above_baseline(void);
extern void object_set_flag_value(void *, int);
extern UIColor *object_get_fourth_field(void *);
extern void hud_set_widget_value_pair(void *, int, int);
extern void *menu_return_object_unchanged(void *);
extern void shop_choose_item_colors(int, int *, int *, int *);
extern void object_set_first_pair(void *, int, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern int weapon_get_usable_selected(void);
extern void menu_set_screen_value_restart_fades(void *, int, int);
extern void anim_step_morph(void *);
extern void anim_update_keyframe(void *, int);
extern void menu_set_first_field(void *, int);
extern void meter_set_value_start_timers(void *, int);
extern void meter_screen_update(void *);
extern void fade_start_backward(void *, int);
extern void fade_start_direction(void *, int);
extern void fade_set_speed(void *, float);
extern float *object_get_field_a(void *);
extern int sprintf(char *, const char *, ...);
extern int func_001157AC(const char *);
extern float fade_reset_amount(void *);
extern int fade_swap_field_28(void *, int);
#define ITEM(n) (&D_00239BA0[D_00139568[n]])

/* Updates the item status HUD: the radial menu slots, the selected item's icon, ammo and bolt counters, fading
   widgets and meter. (USA v2.00) */
void hud_update_item_status_us2(Hud *self)
{
    int x, y, color, bolt_count;
    int selX, selY, selColor;
    Ui3C *slotWidget;
    Ui3C *slotAlphaWidget;
    int selected, present;
    int previous, item, threshold, low;
    UIWord limit;
    Ui48 *widget;
    float scale, width;
    Ui94 *ammo_widget_0;
    Ui94 *bolt;
    UIWord slotWord;
    self->alternateBolts = save_count_items_above_baseline();
    if (g_radial_menu_pages[0]) {
        int i;
        for (i = 0; i < 8; i++) {
            if (!g_radial_menu_pages[0]->slots[i].present)
            object_set_flag_value(&self->slots[i], 0);
            else {
                object_set_flag_value(&self->slots[i], 1);
                hud_set_widget_value_pair(&self->slots[i], g_radial_menu_pages[0]->slots[i].present, 0);
            }
            widget = (Ui48 *)menu_return_object_unchanged(g_resident_data_base[0] + 0x36F28) + i;
            object_set_flag_value(widget, 0);
            /* FAKEMATCH: volatile x store + volatile D_001B18D4 load below keep the x/y/color zero stores ahead of the slot-table load (retail +0x114..+0x124) */
            *(volatile int *)&x = 0; y = 0; color = 0;
            shop_choose_item_colors((*(MenuSlots * volatile *)&g_radial_menu_pages[0])->slots[i].item, &x, &y, &color); /* FAKEMATCH: volatile load, see above */
            {
                UIColor *c = object_get_fourth_field(&self->slots[i]);
                c->word = (c->word & 0xFF000000) | (color & 0xFFFFFF);
            }
            widget = (Ui48 *)menu_return_object_unchanged(g_resident_data_base[0] + 0x36F28) + i;
            object_set_flag_value(widget, 1);
            object_set_first_pair(widget, x, y);
            meter_set_max(widget, 100);
            meter_set_value(widget, 100);
            {
                ItemRecord *rec = ITEM(g_radial_menu_pages[0]->slots[i].item);
                if (rec->present) {
                    int enabled = rec->enabled != 0;
                    int capacity = rec->capacity;
                    if (capacity || enabled) {
                        meter_set_max(widget, capacity);
                        if (ITEM(g_radial_menu_pages[0]->slots[i].item)->capacity > 0)
                            meter_set_value(widget, g_help_entry_state[g_radial_menu_pages[0]->slots[i].item] >> 5);
                    }
                }
            }
        }
    }
    if (self->selectionMode) selected = self->selected;
    else selected = weapon_get_usable_selected();
    selX = 0; selY = 0; selColor = 0;
    present = ITEM(selected)->present;
    shop_choose_item_colors(selected, &selX, &selY, &selColor);
    object_get_fourth_field(&self->selectedIcon)->word = selColor;
    if (selected && present) {
        hud_set_widget_value_pair(&self->selectedIcon, ITEM(selected)->icon, 0);
        if (!self->selectionMode)
        menu_set_screen_value_restart_fades(self, ITEM(selected)->icon, 10);
    }
    anim_step_morph(&self->ammoWidgets[0]);
    anim_step_morph(&self->ammoWidgets[1]);
    anim_step_morph(&self->ammoWidgets[2]);
    anim_update_keyframe(&self->middleWidget, 1);
    anim_step_morph(&self->endAmmoWidget);
    menu_set_first_field(self->meter, g_hero_state.value);
    {
        unsigned char state = g_hero_state.state;
        if (!state) goto heroFallback;
        if (state == 1)
        meter_set_value_start_timers(self->meter, 4);
        else {
heroFallback:
            meter_set_value_start_timers(self->meter, g_player_stats[0]);
        }
    }
    meter_screen_update(self->meter);
    anim_update_keyframe(&self->hideWidgets[0], 1);
    anim_update_keyframe(&self->hideWidgets[1], 1);
    anim_update_keyframe(&self->hideWidgets[2], 1);
    anim_update_keyframe(&self->hideWidgets[3], 1);
    anim_update_keyframe(&self->hideWidgets[4], 1);
    {
        UIWord w = object_get_fourth_field(&self->slots[0])->word;
        {
            int i;
            for (i = 1; i < 8; i++) {
                UIColor *c = object_get_fourth_field(&self->slots[i]);
                c->word = (c->word & 0xFFFFFF) | ((w >> 24) << 24);
            }
        }
    }
    anim_update_keyframe(&self->hideWidgets[5], 1);
    slotWord = object_get_fourth_field(&self->slotColors[0])->word;
    {
        int i;
        for (i = 0; i < 8; i++) {
            previous = i;
            previous--;
            if (previous < 0) previous = 7;
            if (g_radial_menu_pages[0] && g_radial_menu_pages[0]->slots[i].present) {
                MenuSlot *slot = &g_radial_menu_pages[0]->slots[i];
                ItemRecord *rec;
                item = slot->item;
                rec = ITEM(item);
                if (rec->present && !g_item_ammo_counts[item] && rec->flags) {
                    Ui4C *w = &self->slotColors[previous];
                    /* FAKEMATCH: do { } while (0) adds loop notes, so flow counts the 0x70202080 register's refs at a deeper loop level; global then allocates it (s6) before `low`, as retail */
                    do { UIWord color = 0x70202080;
                    object_get_fourth_field(w)->word = color; } while (0);
                } else {
                    UIWord color = 0x60442D00;
                    object_get_fourth_field(&self->slotColors[previous])->word = color;
                }
            }
            {
                UIColor *c = object_get_fourth_field(&self->slotColors[previous]);
                c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
            }
        }
    }
    {
        UIColor *c = object_get_fourth_field(&self->background);
        c->word = (c->word & 0xFFFFFF) | ((slotWord >> 24) << 24);
    }
    {
        UIWord promptAlpha = object_get_fourth_field(&self->alphaSource)->word & 0xFF000000;
        {
            UIColor *c = object_get_fourth_field(&self->prompt);
            c->word = (c->word & 0xFFFFFF) | promptAlpha;
        }
    }
    {
        UIWord alpha, alpha2;
        alpha = object_get_fourth_field(&self->ammoIcon)->word & 0xFF000000;
        alpha2 = object_get_fourth_field(&self->selectedIcon)->word & 0xFF000000;
        limit = object_get_fourth_field(self)->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = object_get_fourth_field(&self->ammoIcon);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = object_get_fourth_field(&self->selectedIcon);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }
    bolt = &self->boltWidgets[0];
    anim_step_morph(bolt);
    anim_step_morph(&self->boltWidgets[1]);
    anim_step_morph(&self->boltWidgets[2]);
    anim_step_morph(&self->boltWidgets[3]);
    if (self->ammoTimer && --self->ammoTimer == 0) { Ui94 *first_widget; if (!((first_widget = &self->ammoWidgets[0])->state)) {
        fade_start_backward(first_widget, 0);
        fade_start_backward(&self->ammoWidgets[1], 0);
        fade_start_backward(&self->ammoWidgets[2], 0);
        fade_start_direction(&self->middleWidget, -1);
        fade_start_backward(&self->endAmmoWidget, 0);
        self->ammoHidden = 1;
    } }
    if (self->boltTimer && --self->boltTimer == 0) if (!bolt->state) {
        fade_start_backward(bolt, 0);
        fade_start_backward(&self->boltWidgets[1], 0);
        fade_start_backward(&self->boltWidgets[2], 0);
        self->boltHidden = 1;
        fade_start_backward(&self->boltWidgets[3], 0);
    }
    if (self->hideTimer && --self->hideTimer == 0 && self->hidden != 1) {
        self->hidden = 1;
        object_set_flag_value(&self->prompt, 0);
        fade_start_direction(&self->hideWidgets[0], -1);
        fade_start_direction(&self->hideWidgets[1], -1);
        fade_start_direction(&self->hideWidgets[2], -1);
        fade_start_direction(&self->hideWidgets[3], -1);
        fade_start_direction(&self->hideWidgets[4], -1);
        fade_start_direction(&self->hideWidgets[5], -1);
        fade_set_speed(&self->hideWidgets[0], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
        fade_set_speed(&self->hideWidgets[1], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
        fade_set_speed(&self->hideWidgets[2], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
        fade_set_speed(&self->hideWidgets[3], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
        fade_set_speed(&self->hideWidgets[4], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
        fade_set_speed(&self->hideWidgets[5], g_is_pal_video[0] ? 0.14f : 0.11666667461395264f);
    }
    if (selected && present) {
        int count;
        if (ITEM(selected)->capacity > 0) {
            width = (float)(g_help_entry_state[selected] >> 5) / (float)ITEM(selected)->capacity;
            scale = g_hud_ammo_scale_factor * (0.5f - width * 0.5f);
            width *= 30.0f;
            scale = scale > 1.0f ? scale : 1.0f;
            width *= scale;
            width = width < 30.0f ? width : 30.0f;
        } else width = 30.0f;
        width = width > 0.0f ? width : 0.0f;
        *object_get_field_a(&self->ammoBar) = width;
        {
            int ammo = g_item_ammo_counts[selected];
            int max;
            self->ammo = ammo;
            low = 1;
            max = ITEM(selected)->maxAmmo;
            self->maxAmmo = max;
            sprintf(self->ammoText, g_str_hud_ammo_format, ammo, max);
        }
        count = func_001157AC(self->ammoText) - 3;
        if (count > 5) count = 5;
        if (count < 0) count = 0;
        width = (float)count;
        *object_get_field_a(self) = width;
        *object_get_field_a(&self->ammoDigits[1]) = width;
        threshold = (int)((float)ITEM(selected)->maxAmmo * 0.1f);
        if (!threshold) threshold = 1;
        if (threshold < g_item_ammo_counts[selected]) low = 0;
        if (!g_item_ammo_counts[selected]) {
            fade_reset_amount(&self->warningWidgets[0]);
            fade_reset_amount(&self->warningWidgets[1]);
        }
        if (low) {
            fade_swap_field_28(&self->warningWidgets[0], 1);
            fade_swap_field_28(&self->warningWidgets[1], 1);
        } else {
            fade_swap_field_28(&self->warningWidgets[0], 0);
            fade_swap_field_28(&self->warningWidgets[1], 0);
            ammo_widget_0 = &self->ammoWidgets[0];
            if (!ammo_widget_0->state) {
                Ui94 *ammo_widget_1 = &self->ammoWidgets[1];
                ammo_widget_0->value = 1.0f;
                ammo_widget_1->value = 1.0f;
                ammo_widget_0->state = 1;
                ammo_widget_1->state = 1;
                anim_step_morph(ammo_widget_0);
                anim_step_morph(ammo_widget_1);
            }
        }
    }
    anim_update_keyframe(&self->warningWidgets[0], 1);
    anim_update_keyframe(&self->warningWidgets[1], 1);
    {Ui94 *first_ammo_widget = &self->ammoWidgets[0];
    if (first_ammo_widget->state || !present) {
        UIWord alpha, alpha2;
        alpha = object_get_fourth_field(self)->word & 0xFF000000;
        alpha2 = object_get_fourth_field(&self->ammoDigits[1])->word & 0xFF000000;
        if (limit < alpha) alpha = limit;
        {
            UIColor *c = object_get_fourth_field(self);
            if (limit < alpha2) alpha2 = limit;
            c->word = (c->word & 0xFFFFFF) | alpha;
        }
        {
            UIColor *c = object_get_fourth_field(&self->ammoDigits[1]);
            c->word = (c->word & 0xFFFFFF) | alpha2;
        }
    }}
    bolt_count = *(self->boltMode ? &self->alternateBolts : self->boltCount);
    sprintf(self->boltText, g_str_count_format, bolt_count);
    {
        int count;
        count = func_001157AC(self->boltText) - 1;
        if (count > 6) count = 6;
        if (count < 0) count = 0;
        width = (float)count;
        *object_get_field_a(&self->boltDigits[0]) = width;
        *object_get_field_a(&self->boltDigits[1]) = width;
    }
    meter_screen_update(self->meter);
}
