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
extern int D_L00_001AD7A0 __attribute__((sda));
extern int D_L00_001AD7A4;
extern int save_count_items_above_baseline(void);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

void func_US2_L00_0037A218(void)
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
        text_draw_centered_medium(D_L00_001AD7A0, D_L00_001AD7A4, 0x80F0F0F0, GetLocalizedString(0x31B5), -1);
    else
        text_draw_centered_medium(D_L00_001AD7A0, D_L00_001AD7A4, 0x80F0F0F0, GetLocalizedString(0x31B4), -1);
}
