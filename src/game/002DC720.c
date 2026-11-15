#include "include_asm.h"
#include "names.h"

/* Draws a menu text box: the box from the menu's own geometry (func_002DE810), then per
   state (+0x50) either the -1 terminated list of text ids at +0x34, centred by the line
   count at +0x3C, flagging +0x54 when it ends 0x18 above the bottom, or the single text
   id at +0x34 (states 4, 11, 15, 19). */
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(long);
extern void pack_image_descriptor(void *, char *);
extern char *GetLocalizedString(int);
extern void text_draw_window_small(void *, unsigned long, char *, int);
extern void DoGifPaging(void);

int text_timed_pages_draw(char *menu_text_box)
{
    short box[12];
    int ypos;
    int text_start_y_offset;
    int i;

    VU1_addGSregister(0x47, 0x30000);
    VU1_addGSregister(0x42, 0x8000000044LL);
    SetupGifPaging(0);
    pack_image_descriptor(box, menu_text_box);
    box[9] = 9;
    box[3] = *(int *)(menu_text_box + 0x18) + *(int *)(menu_text_box + 0x20);
    box[0] = *(int *)(menu_text_box + 0x1C) + 4;
    box[1] = *(int *)(menu_text_box + 0x1C) + *(int *)(menu_text_box + 0x24) - 4;
    box[2] = *(int *)(menu_text_box + 0x18);
    box[4] = *(int *)(menu_text_box + 0x18) + (*(int *)(menu_text_box + 0x20) >> 1);
    box[10] = 0;
    box[11] = 0;
    switch (*(int *)(menu_text_box + 0x50)) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 18:
        text_start_y_offset = (*(int *)(menu_text_box + 0x3C) >> 4) - 4;
        ypos = *(int *)(menu_text_box + 0x1C) - text_start_y_offset;
        for (i = 0; (*(int **)(menu_text_box + 0x34))[i] != -1; i++) {
            box[5] = ypos;
            box[11] = (*(int *)(menu_text_box + 0x3C) >> 4) & 0xF;
            text_draw_window_small(box, 0x80FFA888L, GetLocalizedString((*(int **)(menu_text_box + 0x34))[i]), -1);
            ypos += box[7];
            ypos += 10;
        }
        if (ypos + 0x18 < *(int *)(menu_text_box + 0x1C) + *(int *)(menu_text_box + 0x24))
            *(int *)(menu_text_box + 0x54) = 1;
        break;
    case 4:
    case 11:
    case 15:
    case 19:
        box[5] = *(int *)(menu_text_box + 0x1C) + 0x20;
        text_draw_window_small(box, 0x80FFA888L, GetLocalizedString(*(int *)(menu_text_box + 0x34)), -1);
        break;
    case 0:
        break;
    }
    DoGifPaging();
    return 2;
}
