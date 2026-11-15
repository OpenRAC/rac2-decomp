#include "common.h"

typedef struct { float x, y; } MenuListPosition;
typedef struct { unsigned int values[4]; } MenuColourQuad;
typedef struct { int x0, x1, y0, y1; } MenuClipRectangle;

typedef struct {
    MenuListPosition *position;
    float iconSize, unused08, rowHeight;
    int count, selected, state, backward, firstVisible, lastVisible;
    int ids[25];
    void *allocation;
    int scrollOffset, frames;
} MenuList;

extern const int D_001AE1CC __attribute__((sda));
extern int snd_play_from_global_bank(int, int, void *);

/* Moves the menu list cursor up or down when the player presses the direction buttons, scrolls smoothly, and works out which entries are on screen. */
int UpdateListSelection(MenuList *self, int flags)
{
    int row;
    int offset;
    int selection;
    self->frames++;
    switch (self->state) {
    case 0:
        if ((flags & 0x1000) && self->selected > 0) {
            snd_play_from_global_bank(3, 0, 0);
            self->backward = 1;
            self->state = 1;
        } else if ((flags & 0x4000) && self->selected < self->count - 1) {
            snd_play_from_global_bank(3, 0, 0);
            self->backward = 0;
            self->state = 1;
        }
        break;
    case 1:
        self->scrollOffset = 0;
        self->state = 2;
        /* Fall through to advance the first scroll step. */
    case 2:
        if (!self->backward) offset = self->scrollOffset - 4;
        else offset = self->scrollOffset + 4;
        self->scrollOffset = offset;
        if ((float)offset >= self->rowHeight || (float)offset <= -self->rowHeight) {
            if (!self->backward) selection = ++self->selected;
            else selection = --self->selected;
            self->selected = selection;
            if (selection < 0) self->selected = 0;
            if (self->selected > self->count - 1) self->selected = self->count - 1;
            self->state = flags ? self->state : 0;
            self->state = self->selected == 0 || self->selected == self->count - 1 ? 0 : self->state;
            self->scrollOffset = 0;
        }
        break;
    }
    row = self->selected;
    self->firstVisible = 0;
    if (row > 0) {
        if (0 > -D_001AE1CC) do {
            row--;
            self->firstVisible--;
        } while (row > 0 && self->firstVisible > -D_001AE1CC);
    }
    row = self->selected;
    self->lastVisible = 0;
    if (row < self->count - 1) {
        while (row < self->count - 1 && self->lastVisible < D_001AE1CC) {
            row++;
            self->lastVisible++;
        }
    }
    return 0;
}

extern void menu_panel_draw_frame(MenuListPosition **);
extern int ComputeListEntryAlpha(char *, float, float, float, float, int);
extern unsigned char g_item_slot_to_record[], g_weapon_table[];
extern MenuColourQuad D_001AE1D8, D_001AE1E8;
extern float D_001AE1D0 __attribute__((sda));
extern int D_001AE1D4 __attribute__((sda));
extern int D_001B23C0 __attribute__((sda));
extern MenuClipRectangle D_001B23B0 MACRO_ADDR;
extern MenuClipRectangle menuClipGP SDATA(D_001B23B0);
extern int g_screen_width MACRO_ADDR, g_screen_height MACRO_ADDR;
extern int screenWidthGP SDATA(D_001A7340);
extern void gfx_set_scissor_clamped(int, int, int, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, int *);

/* Draws the visible entries of a menu list with their icons, fading them out toward the top and bottom edges. */
void menu_list_draw_entries(MenuList *object)
{
    float high, low, current;
    int index, topAlpha, bottomAlpha, texture;
    MenuColourQuad normal, alternate;
    char *colours;
    MenuClipRectangle clip;
    unsigned char *entry;
    menu_panel_draw_frame(&object->position);
    low = object->position->y + object->rowHeight * -4.0f;
    high = object->position->y + object->iconSize * 0.5f;
    for (index = object->firstVisible;
            index <= object->lastVisible && object->count; index++) {
        normal = D_001AE1D8;
        alternate = D_001AE1E8;
        entry = g_weapon_table + g_item_slot_to_record[object->ids[object->selected + index]] * 224;
        colours = (char *)&normal;
        if (*(int *)entry && entry[4]) colours = (char *)&alternate;
        current = (float)index;
        topAlpha = ComputeListEntryAlpha((char *)object, low,
                object->position->y + object->rowHeight * current + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        bottomAlpha = ComputeListEntryAlpha((char *)object, low,
                object->position->y + object->rowHeight * current + object->iconSize + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        *(unsigned int *)(colours + 0) = (*(unsigned int *)(colours + 0) & 0xFFFFFF) | ((unsigned int)topAlpha << 24);
        *(unsigned int *)(colours + 4) = (*(unsigned int *)(colours + 4) & 0xFFFFFF) | ((unsigned int)topAlpha << 24);
        *(unsigned int *)(colours + 8) = (*(unsigned int *)(colours + 8) & 0xFFFFFF) | ((unsigned int)bottomAlpha << 24);
        *(unsigned int *)(colours + 12) = (*(unsigned int *)(colours + 12) & 0xFFFFFF) | ((unsigned int)bottomAlpha << 24);
        if (D_001B23C0 == 0) {
            clip.y0 = 63;
            clip.y1 = 340;
            clip.x1 = screenWidthGP - 1;
            clip.x0 = 0;
            D_001B23C0 = 1;
            menuClipGP = clip;
        }
        gfx_set_scissor_clamped(D_001B23B0.x0, D_001B23B0.x1, D_001B23B0.y0, D_001B23B0.y1);
        entry = g_weapon_table + g_item_slot_to_record[object->ids[object->selected + index]] * 224;
        texture = GetIconFrame(*(unsigned short *)(entry + 0x3C), 0);
        hud_draw_sprite_gradient(texture, (int)object->position->x,
                (int)(object->position->y + object->rowHeight * current + (float)object->scrollOffset),
                (int)object->iconSize, (int)object->iconSize, (int *)colours);
        gfx_set_scissor_clamped(0, g_screen_width - 1, 0, g_screen_height - 1);
    }
}
