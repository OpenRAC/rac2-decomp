#include "include_asm.h"

#include "common.h"
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0x24]; int slots[4]; char p50[0xE4]; int fallback; char p138[0xC]; int wrap; int edge; char p14c[0xC]; int busy; } MenuRoot;
typedef struct { char reserved[0x1C4]; int flags; } PadState;
typedef struct GridMenu { char p00[0x30]; int flags; char p34[8]; int index; int rows; int cols; void *entries; struct GridMenu *up; struct GridMenu *down; void *left; void *right; } GridMenu;
typedef struct { char p00[6]; short item; char p08[2]; } GridEntry;
typedef struct { char p00[0xC]; int slot; char p10[0xD0]; } WeaponInfo;
extern MenuRoot D_001F2840;
extern PadState D_00138180;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern unsigned char D_00139568[];
extern WeaponInfo D_00239BA0[];
extern void func_002DF190(int, int);

int func_PAL_002D75A0(GridMenu *menu)
{
    int flags;
    int cols;
    int old;
    int row;
    int rows;
    int col;
    int x;

    if (*(GridMenu **)(D_001F2840.owner + 0xE8) != menu)
        return 0;
    if ((D_00138180.flags & 0x900) && D_001F2840.fallback == 0)
        return 1;
    flags = D_00138180.flags;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.owner + 0xE0);
        int status;
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    cols = menu->cols;
    old = menu->index;
    rows = menu->rows;
    col = old % cols;
    row = old / cols;
    x = col;
    if (flags & 0x1000) {
        if (row != 0)
            menu->index = old - cols;
        else if (menu->up != 0) {
            GridMenu *link = menu;
            int skip;
            int lcols;
            int lrows;
            do {
                link = link->up;
                skip = 0;
                lrows = link->rows;
                lcols = link->cols;
                if (D_001F2840.wrap) {
                    if (link->flags & 8)
                        skip = 1;
                    else
                        skip = 0;
                }
                if (D_001F2840.edge && (link->flags & 4))
                    skip = 1;
            } while (skip);
            *(GridMenu **)(D_001F2840.owner + 0x128) = link;
            if (lcols == 5)
            {
                x = col + 1;
                if (menu->cols != 3)
                    x = col;
            }
            if (lcols == 3 && menu->cols == 5) {
                x = x - 1;
                if (x > 2)
                    x = 2;
                else if (x < 0)
                    x = 0;
            }
            link->index = (lrows - 1) * lcols + (x < lcols - 1 ? x : lcols - 1);
        } else if (!(menu->flags & 0x8000))
            menu->index = cols * (rows - 1) + old;
    }
    if (D_00138180.flags & 0x4000) {
        if (row + 1 < rows)
            menu->index = menu->index + cols;
        else if (menu->down != 0) {
            GridMenu *link = menu;
            int skip;
            int lcols;
            do {
                link = link->down;
                skip = 0;
                lcols = link->cols;
                if (D_001F2840.wrap) {
                    if (link->flags & 8)
                        skip = 1;
                    else
                        skip = 0;
                }
                if (D_001F2840.edge && (link->flags & 4))
                    skip = 1;
            } while (skip);
            *(GridMenu **)(D_001F2840.owner + 0x128) = link;
            if (lcols == 5 && menu->cols == 3)
                x = x + 1;
            if (lcols == 3 && menu->cols == 5) {
                x = x - 1;
                if (x > 2)
                    x = 2;
                else if (x < 0)
                    x = 0;
            }
            link->index = x < lcols - 1 ? x : lcols - 1;
        } else if (!(menu->flags & 0x8000))
            menu->index = menu->index - menu->cols * (menu->rows - 1);
    }
    if (D_00138180.flags & 0x8000) {
        if (x != 0)
            menu->index = menu->index - 1;
        else if (menu->left != 0)
            *(void **)(D_001F2840.owner + 0x128) = menu->left;
        else if (!(menu->flags & 0x8000))
        {
            int index = menu->index - 1;
            menu->index = index + menu->cols;
        }
    }
    if (D_00138180.flags & 0x2000) {
        if (x + 1 < cols)
            menu->index = menu->index + 1;
        else if (menu->right != 0)
            *(void **)(D_001F2840.owner + 0x128) = menu->right;
        else if (!(menu->flags & 0x8000))
        {
            int index = menu->index + 1;
            menu->index = index - menu->cols;
        }
    }
    if (menu->index != old || *(int *)(D_001F2840.owner + 0x128) != 0)
        func_002DF190(1, 0x11);
    if (D_00138180.flags & 0x40) {
        MenuRoot *root;
        GridEntry *entry;
        int slot;
        if (!((menu->flags ^ 1) & 1))
            return 0;
        root = &D_001F2840;
        if (root->busy != 0)
            return 0;
        entry = (GridEntry *)menu->entries + menu->index;
        if (entry->item != 0 && D_001A7AF8[entry->item] != 0) {
            WeaponInfo *info = &D_00239BA0[D_00139568[entry->item]];
            slot = info->slot;
            func_002DF190(0, 0x11);
            root->busy = 10;
            if (root->slots[slot] == entry->item && slot != 0 && slot != 3)
                root->slots[slot] = 0;
            else
                D_001F2840.slots[slot] = entry->item;
        } else
            func_002DF190(2, 0x11);
    }
    return 0;
}
