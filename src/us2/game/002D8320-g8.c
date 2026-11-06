/* func_US2_002D8320, the USA v2.00 copy of func_002D7698: the same C, where opening a page's
   special screen also requires the active menu to be D_0025E680 or D_0025A190. */
#include "include_asm.h"
#include "common.h"

extern char D_001F2840[];
typedef struct {
    u8 pad0[8];
    int field8;             /* 0x08 */
    u8 padC[8];
    u8 *owner;              /* 0x14: active menu screen */
    int current;            /* 0x18 */
    u8 pad1C[0xC];
    int saved;              /* 0x28 */
    u8 pad2C[0xAF];
    u8 active;              /* 0xDB */
    u8 padDC[0x18];
    int page;               /* 0xF4 */
    u8 padF8[8];
    u8 *savedOwner;         /* 0x100 */
    int savedCurrent;       /* 0x104 */
    u8 pad108[0x2C];
    int lock;               /* 0x134 */
    u8 pad138[8];
    int savedMode;          /* 0x140 */
} PageRoot;

typedef struct {
    u8 pad[0x230];
    int page;               /* 0x230: current page, 0..27 */
} PageMap;

typedef struct {
    u8 pad[0x1C4];
    u32 buttons;            /* 0x1C4 */
} PagePad;

typedef struct {
    u8 pad[0x30];
    int selection[28];      /* 0x30: selected row per page */
    int count;              /* 0xA0: rows on the current page */
} PageMenu;

typedef struct {
    char pad[0x34];
    int item;               /* 0x34 */
    int pad38;
    int timer;              /* 0x3C */
} PagePreview;

extern char D_001C4FA0[];
extern char D_00138180[];

extern PagePreview D_0025A6E0;
extern u8 D_0025E680[];
extern u8 D_0025A190[];
extern u8 D_001A7BC8[] MACRO_ADDR;  /* page available, one byte per page */
extern int D_00139768[];            /* flag bits: bit (n & 31) of word n >> 2 */
extern int D_0025A620[];
extern int D_001A7478;
extern int D_001A79F0 __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern char D_001BAD40[];

extern int func_00295A10(int);
extern void func_00295C50(int);
extern int func_002E5E58(int, int, void *);
extern void func_0029D830(void);
extern int func_US2_0029E960(int *, int *, int *, int);
extern void func_002C9E60(int);
extern int func_00288AA0(char *, int);
extern int func_00288BE8(char *);

int func_US2_002D8320(PageMenu *menu)
{
    int previous, count, old, next, mapped;
    PageMap *map;

    previous = ((PageMap *)D_001C4FA0)->page;
    if (*(PageMenu **)(((PageRoot *)D_001F2840)->owner + 0xE8) != menu) {
        if (((PageMap *)D_001C4FA0)->page < 28)
            menu->selection[((PageMap *)D_001C4FA0)->page] = -1;
        return 0;
    }
    if ((((PagePad *)D_00138180)->buttons & 0xD00) && !((PageRoot *)D_001F2840)->lock && ((PageRoot *)D_001F2840)->owner != D_0025E680)
        return 1;

    /* Next and previous available page. */
    if (((PagePad *)D_00138180)->buttons & 8) {
        for (next = ((PageMap *)D_001C4FA0)->page + 1; next < 28; next++) {
            if (D_001A7BC8[next] || D_001A79F0 == next) {
                if (func_00295A10(next) < 0)
                    return 0;
                func_00295C50(next);
                break;
            }
        }
    }
    if (((PagePad *)D_00138180)->buttons & 4) {
        for (next = ((PageMap *)D_001C4FA0)->page - 1; next >= 0; next--) {
            if (D_001A7BC8[next] || D_001A79F0 == next) {
                if (func_00295A10(next) < 0)
                    return 0;
                func_00295C50(next);
                break;
            }
        }
    }
    if (((PageMap *)D_001C4FA0)->page != previous) {
        func_002E5E58(3, 0, 0);
        func_0029D830();
    }

    /* Rows of the page, written to the scratchpad. */
    count = func_US2_0029E960((int *)0x70000000, 0, (int *)0x70000100, 1);
    menu->count = count;
    if (count) {
        u32 buttons = ((PagePad *)D_00138180)->buttons;
        int *selections = menu->selection;
        {
            int *entry = &selections[((PageMap *)D_001C4FA0)->page];
            old = *entry;
            if (buttons & 0x1000)
                *entry = (old + count - 1) % count;
        }
        if (buttons & 0x4000) {
            int *entry = &selections[((PageMap *)D_001C4FA0)->page];
            *entry = (*entry + 1) % menu->count;
        }
        {
            int *entry = &selections[((PageMap *)D_001C4FA0)->page];
            if (*entry != old)
                func_002E5E58(3, 0, 0);
        }
        if ((buttons & 0x5000) || ((PageMap *)D_001C4FA0)->page != previous) {
            int *entry;
            D_0025A6E0.timer = -576;
            entry = &selections[((PageMap *)D_001C4FA0)->page];
            D_0025A6E0.item = ((int *)0x70000000)[*entry];
            *D_0025A620 = ((int *)0x70000100)[*entry];
        }
    } else {
        D_0025A6E0.item = 0;
        *D_0025A620 = -1;
    }

    /* Back. */
    if ((((PagePad *)D_00138180)->buttons & 0x10) && ((PageRoot *)D_001F2840)->owner != D_0025E680) {
        int back = *(int *)(((PageRoot *)D_001F2840)->owner + 0xE0);
        int status;
        if (back)
            ((PageRoot *)D_001F2840)->current = back;
        else if (!((PageRoot *)D_001F2840)->lock) {
            status = -1;
            goto done;
        }
        status = 0;
done:
        return status;
    }

    /* Open the page's special screen. */
    if ((((PagePad *)D_00138180)->buttons & 0x20) && ((PageMap *)D_001C4FA0)->page >= 0) {
        if (((PageRoot *)D_001F2840)->active)
            return 0;
        if (((PageMap *)D_001C4FA0)->page == 0)
            mapped = 21;
        else if (((PageMap *)D_001C4FA0)->page == 24)
            mapped = 0;
        else
            mapped = ((PageMap *)D_001C4FA0)->page;
        map = ((PageMap *)D_001C4FA0);
        if (map->page >= 0) {
            unsigned int word = (unsigned)mapped >> 2;
            int bit = 1 << (mapped & 0x1F);
            if (D_00139768[word] & bit) {
                PageRoot *root = ((PageRoot *)D_001F2840);
                if (root->owner != D_0025E680 && root->owner != D_0025A190)
                    return 0;
                D_001A72D4 = root->saved;
                func_002C9E60(0);
                root->savedMode = D_001A7478;
                root->savedOwner = root->owner;
                root->page = map->page;
                root->savedCurrent = root->field8;
                D_001A7478 = 2;
                func_00288AA0(D_001BAD40, mapped);
                func_00288BE8(D_001BAD40);
                return 1;
            }
        }
    }
    return 0;
}
