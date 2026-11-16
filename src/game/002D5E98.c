#include "include_asm.h"
#include "names.h"

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

extern int g_pad_state[];

extern void snd_play_menu_sound_if_enabled(int, int);

/* Qwen draft (branch qwen/autonomy, 385de342), checked by tools/check.py */
int menu_process_request(short param_1, int param_2, int *param_3);

/* func_002D7AC8: owner ABI/declaration review retained. */
extern int g_menu_choice;

extern void F70997ba9_FUN_002FC560(int a, int b);

extern void F70997ba9_FUN_0027C540(int a);

extern char *F70997ba9_FUN_00288FB8(int id);

extern int F70997ba9_FUN_0027F198(void *p, int i);

extern void F70997ba9_FUN_0027F120(void);

extern void F70997ba9_FUN_0027F5B8(int a, int b, long c, void *d, int e);

extern void F70997ba9_FUN_0027F110(void);

extern void F70997ba9_FUN_0027C660(void);

typedef int s32;

extern char *menu_stream_chunk_claim_free (s32);

/* Qwen draft (branch qwen/autonomy, f0b23b24), checked by tools/check.py */
typedef unsigned long long undefined8;

typedef unsigned int undefined4;

extern undefined4 release_menu_stream_buffer(undefined4);

#ifndef RAC2_T_TWO_F73AF1964
#define RAC2_T_TWO_F73AF1964
typedef struct { signed char a, b; } TWO_F73af1964;
#endif

extern void func_0027C540_1(int);

extern void text_draw_small(int, int, long, signed char *, int);

extern int  GetIconFrame(int, int);

extern int  GetFrameTexture(int);

extern void DrawRotatedSprite(float, float, float, float, float, int, int, int);

extern void func_0027C660_1(void);

extern signed char g_menu_arrow_offset_a[];

extern signed char g_menu_arrow_offset_b[];

extern void menu_stream_chunk_table_init(int);

extern char *func_002DE550_1(int);

extern void menu_clear_block_fields(void);

extern void level_clear_first_table_entry(void);

extern void popup_set_flag_on(int);

extern int D_L00_001A904C_8 __attribute__((sda));

/* Starts a menu action using the two values stored in the menu object. */
void menu_start_action(int args)
{
  int result[4];

  result[0] = 0;
  menu_process_request(*(short *)(args + 2), *(int *)(args + 4), &result[0]);
  return;
}
/* func_002D5EC0 is in 002D5E98-list-g8.c. */

/* func_002D6230 is in 002D5E98-render-g8.c. */

/* func_002D68D8 is in 002D5E98-g8.c. */


typedef struct { char pad[4]; short mode; } Mode2D6E78;
typedef struct { char pad[0x29C]; int flags[5]; int selected; } Map2D6E78;
typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern Mode2D6E78 g_music_state;
extern Map2D6E78 g_map_overlay_state;
extern State2D6E78 g_pause_menu_state;
extern unsigned char g_map_selection_flag;
extern void load_request_disc_read_break(void);

/* Cancels a pending map choice by flipping its flag back and clearing the selection. */
int menu_cancel_map_selection(void)
{
    if (g_music_state.mode == 0) {
        Map2D6E78 *map = &g_map_overlay_state;
        int index = map->selected;
        if (index != -1) {
            g_map_selection_flag = 0;
            map->flags[index] ^= 0x1000;
            map->selected = -1;
        }
    }
    if (g_music_state.mode != 0) {
        State2D6E78 *state = &g_pause_menu_state;
        if (state->active != 0) {
            Map2D6E78 *map;
            load_request_disc_read_break();
            state->active = 0;
            map = &g_map_overlay_state;
            map->flags[map->selected] = -1;
            map->selected = -1;
        }
    }
    return 0;
}

extern int menu_update_entry_states(int *);
extern int menu_list_active_entries(unsigned int, unsigned int, unsigned int, int);
extern int g_selected_map_index;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 g_page_preview;
extern int g_level_page_entry_value[];

/* Sets up a preview of the selected entry by loading its two data words from the tables. */
int menu_preview_entry_init(int *object)
{
    menu_update_entry_states(object);
    *(int *)((char *)object + 0xA0) = menu_list_active_entries(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)object + 0x30;
        int index = g_selected_map_index;

        if (*(int *)(base + (index << 2)) != -1) {
            g_page_preview.f3C = -0x240;
            g_page_preview.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)g_level_page_entry_value = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)object + 0xA4) = 0;
    return 0;
}


/* Clears the saved selection by setting it to -1. */
int menu_clear_saved_selection(void)
{
    g_menu_choice = -1;
    return 0;
}

/* Runs the shared reset step and does nothing else. */
int menu_run_reset_step(void) {
    menu_stream_chunk_table_init(1);
    return 0;
}

extern int g_effects_volume[] __attribute__((sda));
extern int g_menu_settings_values[];

/* Copies one saved value into the settings table. */
int menu_copy_settings_value(void) {
    g_menu_settings_values[0] = g_effects_volume[0];
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
extern Settings2D7B18 g_is_pal_video __attribute__((sda));
extern int *g_map_select_list __attribute__((sda));
extern void map_set_current_and_refresh(int);
extern void snd_set_default_group_volumes(void);
extern void snd_send_cmd11_one_value(int);

/* Sound menu input: back and close, row navigation, volume sliders and the mode toggle. */
int SoundOptionsMenuInput(Menu2D7B18 *menu)
{
    int previous;
    int old_slider1;
    int old_slider0;

    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x900) != 0 && ((CtxB6 *)&g_pause_menu_state)->active == 0)
        return 1;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x10) != 0) {
        int back = ((CtxB6 *)&g_pause_menu_state)->owner->back;
        int result;

        /* One shared exit: it keeps the 0/-1 choice a branch, not a conditional move. */
        if (back != 0) {
            ((CtxB6 *)&g_pause_menu_state)->next = back;
        } else if (((CtxB6 *)&g_pause_menu_state)->active == 0) {
            result = -1;
            goto back_done;
        }
        result = 0;
back_done:
        return result;
    }

    previous = menu->selection;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x1000) != 0)
        menu->selection = (previous + 2) % 3;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x4000) != 0)
        menu->selection = (menu->selection + 1) % 3;
    if (menu->selection != previous || ((CtxB6 *)&g_pause_menu_state)->owner->pendingFocus != 0) {
        snd_play_menu_sound_if_enabled(1, 0x11);
        if (menu->flags & 0x20)
            map_set_current_and_refresh(g_map_select_list[menu->selection]);
    }

    old_slider1 = g_is_pal_video.slider1;
    old_slider0 = g_is_pal_video.slider0;
    if ((((Pad2D7B18 *)g_pad_state)->held & 0x2000) != 0) {
        if (menu->selection == 0) {
            int next = g_is_pal_video.slider0 + 3;
            g_is_pal_video.slider0 = next < 1025 ? next : 1024;
        }
        if (menu->selection == 1) {
            int next = g_is_pal_video.slider1 + 3;
            g_is_pal_video.slider1 = next < 1025 ? next : 1024;
        }
    }
    if ((((Pad2D7B18 *)g_pad_state)->held & 0x8000) != 0) {
        if (menu->selection == 0) {
            int next = g_is_pal_video.slider0 - 3;
            g_is_pal_video.slider0 = next >= 0 ? next : 0;
        }
        if (menu->selection == 1) {
            int next = g_is_pal_video.slider1 - 3;
            g_is_pal_video.slider1 = next >= 0 ? next : 0;
        }
    }
    if (old_slider1 != g_is_pal_video.slider1 || old_slider0 != g_is_pal_video.slider0)
        snd_set_default_group_volumes();

    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x40) != 0) {
        if (menu->selection == 2)
            g_is_pal_video.mode = !g_is_pal_video.mode;
        snd_send_cmd11_one_value(!g_is_pal_video.mode);
        snd_play_menu_sound_if_enabled(0, 0x11);
    }
    return 0;
}

/* func_002D7DB8 is in 002D5E98-audio.c. */


/* Empty menu step that does nothing. */
int menu_step_noop(void) {
    return 0;
}

typedef struct { char pad0[0x36C]; int offset; char pad370[0x16B0 - 0x370]; int start; int length; } Stream2D81B0;
typedef struct { unsigned int key; unsigned int flags; } Slot2D81B0;
extern Stream2D81B0 g_copy_setup_data;
#define MACRO_ADDR __attribute__((section(".sdata")))
extern Slot2D81B0 g_menu_chunk_table[] MACRO_ADDR;
extern int g_block_load_disc_handle;

/* Halves the stream length while it marks the slots whose key is older than the clock and
   (outside the mode) asks for the next block; the result picks state 1 or 3. */
int menu_block_load_start(char *object)
{
    int length;
    int i;
    unsigned int *key;
    unsigned int *flags;

    menu_stream_chunk_table_init(1);
    *(int *)(object + 0x54) = 0;
    *(int *)(object + 0x38) = 0;
    length = g_copy_setup_data.length;
    g_copy_setup_data.length = length / 2;
    flags = &g_menu_chunk_table[0].flags;
    key = &g_menu_chunk_table[0].key;
    for (i = 0; i < 5; i++) {
        if (*key != 0 && *key < g_pause_menu_state.limit)
            *flags |= 2;
        flags += 2;
        key += 2;
    }
    *(int *)(object + 0x50) = 0;
    if (g_music_state.mode == 0) {
        if (load_start_disc_read(g_block_load_disc_handle, g_copy_setup_data.start + g_copy_setup_data.offset, g_copy_setup_data.length) != 0)
            *(int *)(object + 0x50) = 1;
        else
            *(int *)(object + 0x50) = 3;
    }
    *(int *)(object + 0x10) |= 4;
    g_copy_setup_data.length = length;
    return 0;
}

extern short g_sequence_active_flag;
extern void load_request_disc_read_break(void);
extern int g_subtitle_entries __attribute__((sda));
extern int g_block_load_object_word;

/* Finishes the loader: stops a running read, then stores the loaded block values. */
int menu_block_load_finish(char *object)
{
    if (g_sequence_active_flag != 0 && *(int *)(object + 0x50) == 1)
        load_request_disc_read_break();
    menu_stream_chunk_table_init(1);
    {
        int value = *(int *)(object + 0x54);
        if (value != 0) {
            g_block_load_object_word = *(int *)(object + 0x38);
            g_subtitle_entries = value;
        }
    }
    return 0;
}

extern unsigned char g_language __attribute__((sda));
extern int g_subtitle_state[];
extern int load_start_disc_read(int, int, int);
extern void mem_copy_aligned(void *, void *, int);

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
int menu_block_loader_update(char *object)
{
    Loader2D8338 *loader = (Loader2D8338 *)object;

    switch (loader->state) {
    case 2:
        break;
    case 0:
        if (g_sequence_active_flag == 0) {
            Stream2D81B0 *stream = &g_copy_setup_data;

            if (load_start_disc_read(g_block_load_disc_handle, stream->start + stream->offset, stream->length))
                loader->state = 1;
            else
                loader->state = 3;
        }
        break;
    case 1:
        if (g_sequence_active_flag == 0) {
            char *data = g_pause_menu_state.loaded;
            int *header = (int *)(data + ((int *)data)[g_language]);
            int count = *header++;
            int size = *header++;
            char *base;
            int i;

            mem_copy_aligned(data, header, ((size + 3) & ~3) - 8);
            loader->saved_base = g_subtitle_entries;
            loader->saved_count = g_subtitle_state[11];
            g_subtitle_state[11] = count;
            base = g_pause_menu_state.loaded;
            g_subtitle_entries = (int)base;
            for (i = 0; i < g_subtitle_state[11]; i++) {
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

extern char *g_resident_data_base[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern int g_help_entry_state[];
extern unsigned char g_weapon_table[];
typedef struct { unsigned char reserved[0x6C]; int handle; } WidgetClass2D8EC0;
extern void *menu_return_object_unchanged(void *);
extern void object_set_flag_value(unsigned char *, int);
extern void meter_set_value(char *, int);
extern void meter_set_max(unsigned char *, int);
extern void radial_menu_place_item(char *, int, int, int, int);
/* Draws one icon for a menu row at the given spot, using the row image if it has one. */
void menu_row_icon_draw(char *source, short *row, int first, int second, int x, int y)
{
    int index = second * *(int *)(source + 0x44) + first;
    unsigned char *widget = (unsigned char *)menu_return_object_unchanged(g_resident_data_base[0] + 0x36F28) + index * 0x48;
    object_set_flag_value(widget, 0);
    if (((WidgetClass2D8EC0 *)(g_item_slot_to_record[row[3]] * 0xE0 + (unsigned int)g_weapon_table))->handle != 0) {
        object_set_flag_value(widget, 1);
        meter_set_value((char *)widget, g_help_entry_state[row[3]] >> 5);
        meter_set_max(widget, ((WidgetClass2D8EC0 *)(g_item_slot_to_record[row[3]] * 0xE0 + (unsigned int)g_weapon_table))->handle);
    }
    radial_menu_place_item(g_resident_data_base[0] + 0x36F28, index, x, y, 0x80);
}


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
/* Stores a pause state value (3 or 0) in the object data. */
int menu_set_pause_flag_state(char *object) {
    char *data = *(char **)(object + 0x34);
    *(short *)(data + 2) = pauseFlagState_r002D95D8();
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

extern int g_effect_slot_flags[];

extern void hud_add_to_active_total(char *, int);

int part_update_effect_slots(EffectSlots_2D9600 *o)
{
    int i;

    for (i = 0; i < 0x18; i++) {
        char *entry;
        unsigned char id;

        if (o->entries[i] == 0)
            continue;
        if (o->used[i] != 0)
            continue;
        if (g_effect_slot_flags[i] == 0)
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
        hud_add_to_active_total(o->entries[i], 1);
    }
    return 4;
}

/* Draws five text labels in a column, sized to the widest one. */
int menu_label_column_draw(int *object)
{
    int maxWidth;
    int width;
    int xPos;
    int rowStep;
    int yPos;

    F70997ba9_FUN_002FC560(66, 68);
    F70997ba9_FUN_002FC560(71, 11);
    F70997ba9_FUN_0027C540(0);
    maxWidth = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11613), -1);
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11625), -1);
    if (width >= maxWidth)
        maxWidth = width;
    if (*(int *)0x1A79F0 != 0) {
        width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11614), -1);
        if (width >= maxWidth)
            maxWidth = width;
    }
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11626), -1);
    if (width >= maxWidth)
        maxWidth = width;
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11627), -1);
    if (width >= maxWidth)
        maxWidth = width;
    width = F70997ba9_FUN_0027F198(F70997ba9_FUN_00288FB8(11599), -1);
    if (width >= maxWidth)
        maxWidth = width;
    xPos = (object[8] - maxWidth) >> 1;
    if (xPos <= 1)
        xPos = 2;
    rowStep = object[9] / (*(int *)0x1A79F0 != 0 ? 7 : 6);
    F70997ba9_FUN_0027F120();
    yPos = rowStep - 6;
    F70997ba9_FUN_0027F5B8(xPos, yPos, 0x80FFA888L, F70997ba9_FUN_00288FB8(11613), -1);
    yPos += rowStep;
    F70997ba9_FUN_0027F5B8(xPos, yPos, 0x80FFA888L, F70997ba9_FUN_00288FB8(11625), -1);
    yPos += rowStep;
    F70997ba9_FUN_0027F5B8(xPos, yPos, 0x80FFA888L, F70997ba9_FUN_00288FB8(11626), -1);
    yPos += rowStep;
    F70997ba9_FUN_0027F5B8(xPos, yPos, 0x80FFA888L, F70997ba9_FUN_00288FB8(11627), -1);
    yPos += rowStep;
    F70997ba9_FUN_0027F5B8(xPos, yPos, 0x80FFA888L, F70997ba9_FUN_00288FB8(11599), -1);
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

extern ScreenPos_2DA118 g_screen_adjust_offsets;
extern unsigned long long g_menu_image_texture;

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

extern void DrawTexturedQuad(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws the object at the screen position in D_001A6480, sized by the object's own width
   and height. The draw's colour is a grey 0x808080 whose top byte comes from the object's
   counter: with the 0x40000 flag set it is the counter itself, scaled and clamped, and
   without it the colour is plain 0x80808080. Returns 0 when the object draws nothing. */
int menu_fading_image_draw(Object_2DA118 *object)
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
        DrawTexturedQuad(0, 0, g_screen_adjust_offsets.x, g_screen_adjust_offsets.y, 0, 0, object->width, object->height, color, g_menu_image_texture);
    } else {
        color = 0x80808080ULL;
        DrawTexturedQuad(0, 0, g_screen_adjust_offsets.x, g_screen_adjust_offsets.y, 0, 0, object->width, object->height, color, g_menu_image_texture);
    }
    return 0x10;
}

/* Re-initialises a state block: clears field 68, builds two sub-records from the flag word at field 52 masked with 0x200, substitutes a default record for any that came back zero, then clears field 92, sets fields 84 and 80 to -1 and returns 0. */
s32 menu_state_block_reset (s32 self)
{
  *(s32 *) (self + 68) = 0;
  *(s32 *) (self + 72) = menu_stream_chunk_claim_free (*(s32 *) (self + 52) & 0x200);
  *(s32 *) (self + 76) = menu_stream_chunk_claim_free (*(s32 *) (self + 52) & 0x200);
  if ((*(s32 *) (self + 52) & 0x200) == 0)
    {
      if (*(s32 *) (self + 72) == 0)
        *(s32 *) (self + 72) = menu_stream_chunk_claim_free (1);
      if (*(s32 *) (self + 76) == 0)
        *(s32 *) (self + 76) = menu_stream_chunk_claim_free (1);
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

extern short snd_pump_music_and_disc_read(int);

/* Resets the object stream handles and selection to -1 and starts a stream step. */
int menu_stream_handles_reset(Handles_2DCB28 *object) {
    object->first = release_menu_stream_buffer(object->first);
    object->second = release_menu_stream_buffer(object->second);
    object->index = -1;
    object->pending = -1;
    object->state = -1;
    snd_pump_music_and_disc_read(1);
    return 0;
}

/* func_002DA328 is in 002D5E98-stream.c. */

/* A menu panel: drawn as a texture rectangle (at its own position with flag 8 of the first
   flags word, else at the screen size in D_001A6480), or for modes 0 and 1 as a message. */
typedef struct {
    char pad0[0x10];
    unsigned int placement;
    char pad14[4];
    int x, y;
    int width, height;
    char pad28[0xC];
    unsigned int flags;
    int u_width, v_height;
    char pad40[4];
    int mode;
    int texture[2];
    int choice[2];
    int active;
} MenuPanel2DA9A8;

/* RAC1's font window (pause.c struct TextRegion). */
typedef struct {
    short top, bottom, left, right;
    short anchor_x, anchor_y;
    short measured_width, rendered_height;
    short line_advance;
    unsigned short flags;
    short subpixel_x, subpixel_y;
} TextWindow2DA9A8;

typedef struct { short pad0[2]; short type; short id; short pad8; } MenuRow2DA9A8;
typedef struct { char pad0[0x48]; MenuRow2DA9A8 *rows; } MenuRows2DA9A8;
typedef struct { char pad0[0xE8]; MenuRows2DA9A8 *rows; } MenuOwner2DA9A8;

typedef struct { char pad0[8]; int state; char padC[0x150]; int stage; char pad160[4]; int status; } Scene2DA9A8;
extern Scene2DA9A8 g_memcard_state;

/* D_001F2840 seen through the fields this function reads. */
typedef struct {
    char pad0[0x14];
    MenuOwner2DA9A8 *owner;
    char pad18[0x120];
    int message_override, message;
    char pad140[0x24];
    int age;
} Menu2DA9A8;
#define Menu_2DA9A8 (*(Menu2DA9A8 *)&D_001F2840)

extern unsigned char g_item_owned_flags[];
extern unsigned char g_game_flag_table[];
extern int request_is_current_slot(int);
extern char *GetLocalizedString(int);
extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern void text_draw_window_medium(TextWindow2DA9A8 *, long, unsigned char *, int);
extern unsigned long long load_texture_file(int);

/* Draws the menu panel. Modes 0 and 1 print message 0x2E00 (or the menu's override) centred
   in the panel, as a black shadow and then in colour one pixel up and left, and return 2
   (1 when the panel's 0x100 flag is clear). Other modes draw the chosen texture and return 16,
   or 1 when flag 4 is set and the chosen row's entry is not available. */
int menu_panel_draw(MenuPanel2DA9A8 *menu)
{
    unsigned long long texture;
    unsigned char *text;
    MenuRow2DA9A8 *row;
    int message;

    if (menu->active < 0 || request_is_current_slot(6)) return 0;
    if (menu->mode < 2) {
        if (!(menu->flags & 0x100)) return 1;
        if (g_memcard_state.state == 2
            && !(g_memcard_state.stage < 3 && g_memcard_state.status < 0 && Menu_2DA9A8.age > 10)) {
            SetupGifPaging(0);
            message = 0x2E00;
            if (Menu_2DA9A8.message_override) message = Menu_2DA9A8.message;
            text = GetLocalizedString(message);
            {
                TextWindow2DA9A8 window = {1, menu->height + 1, 1, menu->width + 1,
                                           menu->width >> 1, 5, 0, 0, 16, 5};
                text_draw_window_medium(&window, 0x80000000L, text, -1);
                window.anchor_y = (menu->height - window.rendered_height) >> 1;
                window.flags ^= 4;
                text_draw_window_medium(&window, 0x80000000L, text, -1);
                window.top--;
                window.bottom--;
                window.left--;
                window.right--;
                window.anchor_x--;
                window.anchor_y--;
                text_draw_window_medium(&window, 0x80FFA888L, text, -1);
            }
            DoGifPaging();
        }
        return 2;
    }
    if (menu->flags & 4) {
        unsigned int selection = (menu->mode < 4) ^ 1;
        row = &Menu_2DA9A8.owner->rows->rows[menu->choice[selection]];
        if (row->type == 0) {
            short id = row->id;
            if (!g_item_owned_flags[id]) return 1;
        }
        if (row->type == 1 && !g_game_flag_table[row->id]) return 1;
    }
    SetupGifPaging(0);
    if (menu->mode < 4) texture = load_texture_file(menu->texture[0]);
    else texture = load_texture_file(menu->texture[1]);
    if (menu->placement & 8)
        DrawTexturedQuad(menu->x, (char *)menu->y, menu->width, menu->height, 0, 0,
                      menu->u_width, menu->v_height, 0x80808080ULL, texture);
    else
        DrawTexturedQuad(0, 0, g_screen_adjust_offsets.x, g_screen_adjust_offsets.y, 0, 0,
                      menu->u_width, menu->v_height, 0x80808080ULL, texture);
    DoGifPaging();
    return 16;
}

/* The stream block D_0014B540 seen as its two tables of five {start, length} reads,
   picked by D_001A7BB4 modulo 5. */
typedef struct { int start, length; } StreamRead2DAD18;
typedef struct {
    char pad0[0x36C];
    int offset;
    char pad370[0xDD0 - 0x370];
    StreamRead2DAD18 first[5];
    StreamRead2DAD18 second[5];
} StreamReads2DAD18;

/* Starts the read of the object's first, then its second stream once D_001A63AC is clear:
   states 0 to 4, or -1 when a read is refused. */
int menu_stream_reads_update(Handles_2DCB28 *object)
{
    switch (object->state) {
    case 0:
        if (object->first != 0) {
            if (g_sequence_active_flag != 0)
                break;
            {
                StreamReads2DAD18 *reads = (StreamReads2DAD18 *)&g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(object->first,
                                  reads->first[g_language % 5].start + offset,
                                  reads->first[g_language % 5].length) != 0)
                    object->state++;
                else
                    object->state = -1;
            }
        }
        break;
    case 1:
        if (g_sequence_active_flag != 0)
            break;
        object->state = 2;
        break;
    case 2:
        if (object->second != 0) {
            if (g_sequence_active_flag != 0)
                break;
            {
                StreamReads2DAD18 *reads = (StreamReads2DAD18 *)&g_copy_setup_data;
                int offset = reads->offset;

                if (load_start_disc_read(object->second,
                                  reads->second[g_language % 5].start + offset,
                                  reads->second[g_language % 5].length) != 0)
                    object->state++;
                else
                    object->state = -1;
            }
        }
        break;
    case 3:
        if (g_sequence_active_flag != 0)
            break;
        object->state = 4;
        break;
    }
    return 0;
}

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
extern char *g_active_menu_object;
extern char g_level_page_root[];
extern int g_dialog_style_table[];
/* The frame counter as an incomplete sda array: retail's tied absolute macro load. */
extern int g_frame_counter_3[] __attribute__((sda));
extern void VU1_addGSregister(int, unsigned long long);
extern void hud_draw_sprite_region(unsigned long long, int, int, int, int, int, int, int, int, int);

/* Draws the textured frame around the map dialog, scrolling the inner texture. */
int DrawMenuPreviewImage(void)
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

    if (((Dialog2DAF68 *)&g_map_overlay_state)->image < 0)
        return 0;
    page = ((Dialog2DAF68 *)&g_map_overlay_state)->page;
    if (page == 5 || page == 10 || page == 15)
        return 0;
    if (page >= 21 && page != 24)
        return 0;

    if (g_active_menu_object == g_level_page_root) {
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
    dialog = (Dialog2DAF68 *)&g_map_overlay_state;
    style = g_dialog_style_table[dialog->image];
    scroll = (g_frame_counter_3[0] + dialog->image * 0x2AB) % 2048;
    border = inset[style];

    VU1_addGSregister(0x47, 0);
    VU1_addGSregister(8, 0);
    if (style == 0) {
        hud_draw_sprite_region(dialog->tex0, left << 4, top << 4, 7, 7, width << 4, height << 4, 0, 0, 0x80);
    } else {
        hud_draw_sprite_region(dialog->tex0, (left + border) << 4, (top + border) << 4, 7, 7,
                      (width - border * 2) << 4, (height - border * 2) << 4, scroll, 0, 0x80);
        VU1_addGSregister(8, 5);
        hud_draw_sprite_region(dialog->tex1, left << 4, top << 4, 7, 7, width << 4, height << 4, 0, 0, 0x80);
    }
    VU1_addGSregister(0x47, 0x360B);
    return 4;
}

/* func_002DB3C0 is in 002DB3C0.c. */

/* Choice list input: close, back, row navigation and cycling the selected row's value. */
int UpdateMenuChoiceList(ChoiceMenu *menu)
{
    CtxB6 *menuSystem = (CtxB6 *)&g_pause_menu_state;
    int result;
    int previous;

    if (menuSystem->owner->focus != menu)
        return 0;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x900) != 0 && menuSystem->active == 0)
        return 1;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x10) != 0) {
        CtxB6 *menus = (CtxB6 *)&g_pause_menu_state;
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
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x1000) != 0 && previous != 0)
        menu->selected = previous - 1;
    if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x4000) != 0) {
        int selected = menu->selected;

        if (menu->rows[selected + 1].text != 0)
            menu->selected = selected + 1;
    }
    if (previous != menu->selected)
        snd_play_menu_sound_if_enabled(1, 0x11);

    {
        ChoiceRow *row = &menu->rows[menu->selected];
        int *choices = row->choices;
        int count = 0;

        if (choices[0] != 0) {
            do {
                count++;
            } while (choices[count] != 0 && count < 4);
        }
        if ((((Pad2D7B18 *)g_pad_state)->pressed & 0x40) != 0) {
            unsigned char *value = row->value;

            if (value != 0) {
                *value = (*value + 1) % count;
                snd_play_menu_sound_if_enabled(0, 0x11);
            }
        }
    }
    return 0;
}

/* func_002DB7F0 is in 002DB7F0.c. */

/* func_002DB988 is defined in 002DB988-init-g8.c. */

/* Switches the menu draw hook to a different handler when flag 0x40 of the game flags is set. */
int menu_select_draw_hook(void)
{
    extern s32 g_menu_input_flags;
    extern s32 g_menu_select_draw_hook;
    extern void func_0025E680(void);
    if (g_menu_input_flags & 0x40)
        g_menu_select_draw_hook = (s32)func_0025E680;
    return 0;
}

extern void subtitle_empty_a(int, int, int, int);

/* Sets the screen clip box to the rectangle stored in the object. */
int menu_set_clip_rect(char *p) { int x = *(int *)(p + 0x18); int y = *(int *)(p + 0x1C); int w = *(int *)(p + 0x20); int h = *(int *)(p + 0x24); subtitle_empty_a(x, x + w, y, y + h); return 2; }

extern char *g_active_menu_object;

/* Clears the menu lock flag and creates a new handle for the object. */
int menu_lock_handle_init(char *object) {
    *(int *)(g_active_menu_object + 0x12C) = 0;
    *(int *)(object + 0x54) = menu_stream_chunk_claim_free(0);
    return 0;
}

/* Passes the object handle through a conversion step and stores the result back. */
undefined8 menu_convert_object_handle(int object)
{
  undefined4 handle;
  handle = release_menu_stream_buffer(*(undefined4 *)(object + 0x54));
  *(undefined4 *)(object + 0x54) = handle;
  return 0;
}

extern int g_save_menu_screen __attribute__((sda));
extern unsigned int g_menu_input_flags;
typedef struct { char reserved00[0x14]; char *object; int value; char reserved1C[0xC8]; int clear; } SceneState;
extern SceneState ref_L00_002DBB78_00;
/* Updates the menu value from its owner and sets or clears the lock flag when certain buttons are held. */
int menu_lock_flag_update(void)
{
    if (g_save_menu_screen != 16 && g_save_menu_screen != 1) {
        ref_L00_002DBB78_00.value = *(int *)(ref_L00_002DBB78_00.object + 0xE0);
        return 0;
    }
    {
        unsigned int flags = g_menu_input_flags;
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
/* Picks an entry from a table of 19 and stores it in the object. */
int menu_pick_random_table_entry(char *object) {
    *(int *)(object + 0x34) = r1_D_001D48A8[(unsigned int)r1_D_0015EE84 % 19];
    return 0;
}

extern int g_pad_state[];
extern int g_menu_list_busy_flag;
extern void snd_play_menu_sound_if_enabled(int, int);

/* Handles input for a list of 30 entries: close, back, and moving up or down with wrap-around. */
int menu_list_update_long(char *object)
{
    int flags;
    {
        int *state = g_pad_state;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (g_menu_list_busy_flag == 0)
            return 1;
    }
proceed:
    {
        int *state = g_pad_state;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = (char *)&g_pause_menu_state;
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
            snd_play_menu_sound_if_enabled(1, 17);
    }
    return 0;
}


extern int g_pad_state[];
extern int g_menu_list_busy_flag;
extern void snd_play_menu_sound_if_enabled(int, int);

/* Handles input for a list of 12 entries: close, back, and stepping forward or back with wrap-around. */
int menu_list_update_short(char *object)
{
    int flags;
    {
        int *state = g_pad_state;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (g_menu_list_busy_flag == 0)
            return 1;
    }
proceed:
    {
        int *state = g_pad_state;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = (char *)&g_pause_menu_state;
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
        snd_play_menu_sound_if_enabled(1, 17);
    } else if (flags & 0x8020) {
        *(int *)(object + 0x54) = (*(int *)(object + 0x54) + 11) % 12;
        snd_play_menu_sound_if_enabled(1, 17);
    }
    return 0;
}

/* Two-branch draw set-up: copies a 2-byte record from one of two tables into a 16-byte local, then issues a draw call with five float arguments (scale, per-instance angle, two constants, colour value) plus a 64-bit attribute word, a geometry handle, a fifth integer argument -1 and a local buffer. */
/* Draws a small arrow with a label on one side of the menu, depending on a flag in the object. */
int menu_side_arrow_draw(char *object)
{
    signed char local[16];
    float y;

    func_0027C540_1(0);
    if (*(int *)(object + 56) != 0) {
        *(TWO_F73af1964 *)local = *(TWO_F73af1964 *)g_menu_arrow_offset_a;
        text_draw_small(4, *(int *)(object + 36) / 2 - 8, 0x80FFA888, local, -1);
        y = (float)(*(int *)(object + 36) * 8);
        DrawRotatedSprite(640.0f, y, 128.0f, 256.0f, 0.0f, 32, 16, GetFrameTexture(GetIconFrame(0xE99D, 6)));
    } else {
        *(TWO_F73af1964 *)local = *(TWO_F73af1964 *)g_menu_arrow_offset_b;
        text_draw_small(*(int *)(object + 32) - 24, *(int *)(object + 36) / 2 - 8, 0x80FFA888, local, -1);
        y = (float)(*(int *)(object + 36) * 8);
        DrawRotatedSprite(192.0f, y, 128.0f, 256.0f, 3.1415927f, 32, 16, GetFrameTexture(GetIconFrame(0xE99D, 6)));
    }
    func_0027C660_1();
    return 2;
}


/* func_002DC3C8 is built from 002DC3C8-g8.c for small-data access. */

/* func_002DC720 is matched in its own unit, src/game/002DC720.c (its jump table). */

/* func_002DC900 is built from 002DC900-g8.c for small-data access. */

/* func_002DCAB8 is built from 002D5E98-g8.c for small-data access. */

/* Passes the first handle of the object through a conversion step. */
int menu_convert_first_handle(Handles_2DCB28 *object) {
    object->first = release_menu_stream_buffer(object->first);
    return 0;
}
