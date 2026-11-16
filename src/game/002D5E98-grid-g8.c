#include "include_asm.h"
#include "common.h"
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern void DoGifPaging(void);

extern int g_grid_cell_width __attribute__((sda)), g_grid_cell_height __attribute__((sda)), g_grid_cell_gap __attribute__((sda));
extern int g_menu_panel_fill_color __attribute__((sda));
extern int g_frame_counter_3;
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_game_flag_table[];
extern unsigned int help_find_record_marker_by_class(unsigned int);
extern int subtract_integer_with_clamp(int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern void hud_draw_sprite_subpixel_no_color(int, int, int, int, int, int);

typedef struct { char pad[0x14]; char *owner; char pad18[0x40-0x18]; int slots[65]; int override144; int override148; } GridContext;
extern GridContext g_pause_menu_state;
extern unsigned char g_item_slot_to_record[];
typedef struct { unsigned char pad[4]; unsigned char purchased; unsigned char pad05[7]; int slot; unsigned char pad10[0x3C-0x10]; unsigned short icon; unsigned char pad3E[224-0x3E]; } GridItem;
extern GridItem g_weapon_table[];
extern void menu_row_icon_draw(char *, short *, int, int, int, int);
extern int GetIconFrame(int, int);

/* Draws a grid of item icons with a pulsing frame on the highlighted one. */
int DrawMenuItemGrid(char *object)
{
    int probe[4];
    short *record = *(short **)(object + 0x48);
    int active = *(char **)(g_pause_menu_state.owner + 0xE8) == object;
    int xStart, xStep, yStart, yStep;
    int width, height, areaWidth, areaHeight, gap;
    int index, column, x, state, bottom, right;
    int texture;
    unsigned long colour, pulse;
    GridItem *entry;
    VU1_addGSregister(66, 0x8000000044ULL);
    VU1_addGSregister(71, 11);
    SetupGifPaging(0);
    width = g_grid_cell_width;
    height = g_grid_cell_height;
    areaWidth = *(int *)(object + 0x20) << 4;
    areaHeight = *(int *)(object + 0x24) << 4;
    gap = g_grid_cell_gap;
    if (*(int *)(object + 0x44) >= 2) {
        xStart = *(int *)(object + 0x34) << 4;
        xStep = width + (areaWidth -
                (*(int *)(object + 0x34) << 5) - *(int *)(object + 0x44) * width) /
                (*(int *)(object + 0x44) - 1);
    } else {
        xStart = (areaWidth - width) >> 1;
        xStep = 0;
    }
    if (*(int *)(object + 0x30) & 2) {
        yStep = height + gap;
        yStart = *(int *)(object + 0x38) << 4;
    } else if (*(int *)(object + 0x40) >= 2) {
        yStart = *(int *)(object + 0x38) << 4;
        yStep = height + (areaHeight -
                (*(int *)(object + 0x38) << 5) - *(int *)(object + 0x40) * height) /
                (*(int *)(object + 0x40) - 1);
    } else {
        yStep = 0;
        yStart = (areaHeight - height) >> 1;
    }
    index = 0;
    {
    int row, y;
    y = yStart;
    for (row = 0; row < *(int *)(object + 0x40); row++) {
        x = xStart;
        for (column = 0; column < *(int *)(object + 0x44); column++) {
            bottom = y + height;
            right = x + width;
            state = 0;
            if (record[2] == 0 ? *(g_item_owned_flags + record[3]) : *(g_game_flag_table + record[3])) {
                if ((unsigned short)record[2] == 0) {
                    entry = &g_weapon_table[g_item_slot_to_record[record[3]]];
                    state = 0;
                    if (g_pause_menu_state.slots[entry->slot] == record[3])
                        state = ((*(int *)(object + 0x30) ^ 1) & 1) << 2;
                    if (state == 0) {
                        int owned = 3;
                        if (!entry->purchased) owned = 0;
                        state = owned;
                    }
                    if (g_pause_menu_state.override144 && (*(int *)(object + 0x30) & 8)) state = 2;
                    if (g_pause_menu_state.override148 && (*(int *)(object + 0x30) & 4)) state = 2;
                    if (help_find_record_marker_by_class((unsigned short)record[0]))
                        menu_row_icon_draw(object, record, column, row, x >> 4, (y >> 4) + 36);
                }
                if (active && *(int *)(object + 0x3C) == index) {
                    pulse = (unsigned int)(((subtract_integer_with_clamp((g_frame_counter_3 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                    colour = state == 4 ? (unsigned long)(int)0x80101010u : (unsigned long)g_menu_panel_fill_color;
                    AppendScreenRectPacket(x - 48, y - 48, right + 48, bottom + 48, pulse, 1);
                    AppendScreenRectPacket(x - 16, y - 16, right + 16, bottom + 16, colour, 1);
                }
                if (state == 4)
                    AppendScreenRectPacket(x - 64, y - 64, right + 64, bottom + 64, 0x80FFFFFFUL, 1);
                texture = GetIconFrame(g_weapon_table[g_item_slot_to_record[record[3]]].icon, record[1]);
                hud_draw_sprite_subpixel_no_color(texture, x, y, width, height, 128);
                if (state == 2)
                    AppendScreenRectPacket(x - 64, y - 64, right + 64, bottom + 64, 0x60202020UL, 1);
            } else if (active && *(int *)(object + 0x3C) == index) {
                pulse = (unsigned int)(((subtract_integer_with_clamp((g_frame_counter_3 & 63) - 32) + 64) * 0x10202) | 0x80000000u);
                colour = (unsigned long)g_menu_panel_fill_color;
                AppendScreenRectPacket(x - 48, y - 48, right + 48, bottom + 48, pulse, 1);
                AppendScreenRectPacket(x - 16, y - 16, right + 16, bottom + 16, colour, 1);
            }
            index++;
            record += 5;
            x += xStep;
        }
        y += yStep;
    }
    }
    DoGifPaging();
    return 2;
}
