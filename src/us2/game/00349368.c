#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;

/* lot6 -- measured bodies with sizes recorded in the catalogue. */
void func_US2_00349368(u8 *a0, s32 a1, s32 a2) { a0 += a1 * 4; *(s32 *)(a0 + 0x488) = a2; }


extern char *GetLocalizedString(int a);
extern void hud_set_widget_field_b(char *a, int b);

/* stores the count in a field, then loops count times calling one helper on each successive 72-byte slot and passing the result to a second helper. */
/* Sets the page's label count and fills each label with the localized string for its text id. */
void menu_page_set_labels_us2(char *page, int count, int *text_ids)
{
    int i;

    *(int *)(page + 1204) = count;
    for (i = 0; i < count; i++)
        hud_set_widget_field_b(page + 536 + i * 88, GetLocalizedString(text_ids[i]));
}
