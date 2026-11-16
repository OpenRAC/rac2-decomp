#include "include_asm.h"
#include "names.h"

/* The model ends in a variable-length table of 16-byte records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int first; int limit; int third; int fourth; } cells[0]; /* Variable-length trailing table. */
} LimitModel;
extern LimitModel g_purchase_menu_model;

extern int g_menu_title_x __attribute__((sda));

extern int g_menu_title_y;

extern int save_count_items_above_baseline(void);

extern char *GetLocalizedString(int);

extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

/* Shows one of two messages depending on whether the player has reached the limit for the selected item. */
void DrawSelectedItemLimitStatus(void)
{
    LimitModel *base = &g_purchase_menu_model;
    int index;
    int limit;
    int currentAmount;

    if (base->state == 0)
        return;
    index = base->index;
    limit = base->cells[index].limit;
    currentAmount = save_count_items_above_baseline();
    if (currentAmount >= limit)
        text_draw_centered_medium(g_menu_title_x, g_menu_title_y, 0x80F0F0F0, GetLocalizedString(0x1129), -1);
    else
        text_draw_centered_medium(g_menu_title_x, g_menu_title_y, 0x80F0F0F0, GetLocalizedString(0x1128), -1);
}
