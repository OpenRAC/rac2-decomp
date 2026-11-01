#include "include_asm.h"


typedef struct { short s[12]; } FontWindow;
struct CheatMenuEntry { int text_id; unsigned char *enabled_flag; int enabled_text_id, disabled_text_id, reserved10; };
struct CheatsMenu { char pad[0x20]; int width,height; char pad28[8]; int flags; struct CheatMenuEntry *entries; int selected_entry; };
extern void func_002FC560(int, unsigned long);
extern void func_0027C540(int);
extern void func_0027C660(void);
extern void *func_00115484(void *,int,unsigned int);
extern char *func_00288FB8(int);
extern void func_00280190(FontWindow *,unsigned long,char *,int);
extern void func_0027F538(int,int,unsigned long,char *,int);
extern void func_0027F980(int,int,unsigned long,char *,int);

int func_PAL_002DC0B8(struct CheatsMenu *menu) {
    FontWindow text_window;
    short window_fields[12];
    struct CheatMenuEntry *entry;
    int entry_count;
    int entry_index;
    int draw_index;
    int draw_y;
    int line_spacing;
    int color;
    int enabled;

    func_002FC560(0x47, 0x2004B);
    func_0027C540(0);
    if ((menu->flags & 1) && menu->entries->text_id == 0) {
        func_00115484(window_fields, 0, sizeof(window_fields));
        window_fields[1] = menu->height + 1;
        window_fields[3] = menu->width + 1;
        window_fields[4] = menu->width >> 1;
        window_fields[0] = 1;
        window_fields[2] = 1;
        window_fields[5] = menu->height / 3;
        window_fields[8] = 16;
        window_fields[9] = 1;

        text_window = *(FontWindow *)window_fields;
        func_00280190(&text_window, 0x80FFA888, func_00288FB8(0xC1C), -1);
    }
    /* Entries end at a zero text ID; each retail entry occupies 0x14 bytes. */
    entry_count = 0;
    while (menu->entries[entry_count].text_id != 0) {
        entry_count++;
    }
    line_spacing = menu->height / (entry_count + 1);
    draw_y = menu->height / (entry_count + 1) - 8;
    entry_index = 0;
    draw_index = 0;
    if (menu->entries[0].text_id != 0) {
        do {
            entry = &menu->entries[draw_index];
            color = entry_index == menu->selected_entry ? 0x8020FFFF : 0x80FFA888;
            enabled = 0;
            if (entry->enabled_flag != 0) {
                enabled = *entry->enabled_flag;
            }
            func_0027F538(0xC, draw_y, color, func_00288FB8(entry->text_id), -1);
            func_0027F980(
                menu->width - 0xC, draw_y, 0x80FFA888,
                func_00288FB8(enabled ? entry->enabled_text_id : entry->disabled_text_id),
                -1);
            draw_y += line_spacing;
            draw_index++;
            entry_index++;
        } while (menu->entries[entry_index].text_id != 0);
    }
    func_0027C660();
    return 2;
}

