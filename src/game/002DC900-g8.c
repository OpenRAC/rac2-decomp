#include "names.h"
/* The save-info slots at D_001393E0, as in func_0029B0B0 (0029AE78.c): the entries start at 0x30.
 * The other fields' roles are unknown. D_00258D70 holds two ints per entry. */
typedef struct {
    int first, second, third, fourth;
    char stamp[8];
    int invalid;
} SlotEntry_002DC900;

typedef struct {
    char pad000[0x8];
    int state;
    char pad00C[0x30 - 0xC];
    SlotEntry_002DC900 entries[4];
    char pad0A0[0x15C - 0xA0];
    int mode;
    int pad160;
    int selected;
} Slots_002DC900;

extern Slots_002DC900 g_memcard_state;
extern char g_pause_menu_state[];
extern int D_00258D70[];
extern int D_001ABBEC __attribute__((sda));
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern char *GetLocalizedString(int);
extern char *text_format_location_name(char *, int);
extern void text_draw_centered_small(int, int, unsigned long, char *, int);

/* Menu line for the current slot: prints its name (and the follow-up line)
   while the menu is in its listing state. */
int save_slot_location_text_draw(int *box)
{
    char buf[64];
    char *menuRoot = g_pause_menu_state;
    Slots_002DC900 *saveInfo = &g_memcard_state;
    int locationIndex;
    int extraText;
    int lineOffset;

    locationIndex = saveInfo->entries[*(int *)(*(char **)(*(char **)(menuRoot + 0x14) + 0xE8) + 0x40)].first % 0x1C;
    SetupGifPaging(0);
    if (saveInfo->mode < 3 && saveInfo->selected < 0 && *(int *)(menuRoot + 0x164) >= 11 && saveInfo->state == 2) {
        if (locationIndex == -1) {
            text_draw_centered_small(box[6], box[7] + D_001ABBEC / 2, 0x80F0F0F0, GetLocalizedString(0x2F14), -1);
        } else {
            extraText = D_00258D70[locationIndex * 2 + 1];
            lineOffset = 0;
            if (extraText < 0) lineOffset = D_001ABBEC >> 1;
            text_draw_centered_small(box[6], box[7] + lineOffset, 0x80F0F0F0, text_format_location_name(buf, locationIndex), -1);
            if (extraText >= 0) {
                text_draw_centered_small(box[6], box[7] + D_001ABBEC, 0x80F0F0F0, GetLocalizedString(D_00258D70[locationIndex * 2 + 1]), -1);
            }
        }
    }
    DoGifPaging();
    return 2;
}
