#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int first; int limit; int third; int fourth; } cells[0];  
} LimitModel;
extern LimitModel g_purchase_menu_model;
extern int g_menu_title_x __attribute__((sda));
extern int g_menu_title_y;
extern int save_count_items_above_baseline(void);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

/* Shows one of two messages depending on whether the player has reached the limit for the selected item. */
void shop_draw_selected_item_limit_status_us2(void)
{
    LimitModel *base = &g_purchase_menu_model;
    int index;
    int limit;
    int r;

    if (base->state == 0)
        return;
    index = base->index;
    limit = base->cells[index].limit;
    r = save_count_items_above_baseline();
    if (r >= limit)
        text_draw_centered_medium(g_menu_title_x, g_menu_title_y, 0x80F0F0F0, GetLocalizedString(0x31B5), -1);
    else
        text_draw_centered_medium(g_menu_title_x, g_menu_title_y, 0x80F0F0F0, GetLocalizedString(0x31B4), -1);
}
