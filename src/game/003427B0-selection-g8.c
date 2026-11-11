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
extern int func_002E5E58(int, int, void *);

int func_00342978(MenuList *self, int flags)
{
    int row;
    int offset;
    int selection;
    self->frames++;
    switch (self->state) {
    case 0:
        if ((flags & 0x1000) && self->selected > 0) {
            func_002E5E58(3, 0, 0);
            self->backward = 1;
            self->state = 1;
        } else if ((flags & 0x4000) && self->selected < self->count - 1) {
            func_002E5E58(3, 0, 0);
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

extern void func_00343068(MenuListPosition **);
extern int func_003427C0(char *, float, float, float, float, int);
extern unsigned char D_00139568[], D_00239BA0[];
extern MenuColourQuad D_001AE1D8, D_001AE1E8;
extern float D_001AE1D0 __attribute__((sda));
extern int D_001AE1D4 __attribute__((sda));
extern int D_001B23C0 __attribute__((sda));
extern MenuClipRectangle D_001B23B0 MACRO_ADDR;
extern MenuClipRectangle menuClipGP SDATA(D_001B23B0);
extern int D_001A7340 MACRO_ADDR, D_001A7344 MACRO_ADDR;
extern int screenWidthGP SDATA(D_001A7340);
extern void func_002FC620(int, int, int, int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, int *);

void func_00342BE8(MenuList *object)
{
    float high, low, current;
    int index, first, second, texture;
    MenuColourQuad normal, alternate;
    char *colours;
    MenuClipRectangle clip;
    unsigned char *entry;
    func_00343068(&object->position);
    low = object->position->y + object->rowHeight * -4.0f;
    high = object->position->y + object->iconSize * 0.5f;
    for (index = object->firstVisible;
            index <= object->lastVisible && object->count; index++) {
        normal = D_001AE1D8;
        alternate = D_001AE1E8;
        entry = D_00239BA0 + D_00139568[object->ids[object->selected + index]] * 224;
        colours = (char *)&normal;
        if (*(int *)entry && entry[4]) colours = (char *)&alternate;
        current = (float)index;
        first = func_003427C0((char *)object, low,
                object->position->y + object->rowHeight * current + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        second = func_003427C0((char *)object, low,
                object->position->y + object->rowHeight * current + object->iconSize + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        *(unsigned int *)(colours + 0) = (*(unsigned int *)(colours + 0) & 0xFFFFFF) | ((unsigned int)first << 24);
        *(unsigned int *)(colours + 4) = (*(unsigned int *)(colours + 4) & 0xFFFFFF) | ((unsigned int)first << 24);
        *(unsigned int *)(colours + 8) = (*(unsigned int *)(colours + 8) & 0xFFFFFF) | ((unsigned int)second << 24);
        *(unsigned int *)(colours + 12) = (*(unsigned int *)(colours + 12) & 0xFFFFFF) | ((unsigned int)second << 24);
        if (D_001B23C0 == 0) {
            clip.y0 = 63;
            clip.y1 = 340;
            clip.x1 = screenWidthGP - 1;
            clip.x0 = 0;
            D_001B23C0 = 1;
            menuClipGP = clip;
        }
        func_002FC620(D_001B23B0.x0, D_001B23B0.x1, D_001B23B0.y0, D_001B23B0.y1);
        entry = D_00239BA0 + D_00139568[object->ids[object->selected + index]] * 224;
        texture = func_0028E588(*(unsigned short *)(entry + 0x3C), 0);
        func_0028EA58(texture, (int)object->position->x,
                (int)(object->position->y + object->rowHeight * current + (float)object->scrollOffset),
                (int)object->iconSize, (int)object->iconSize, (int *)colours);
        func_002FC620(0, D_001A7340 - 1, 0, D_001A7344 - 1);
    }
}
