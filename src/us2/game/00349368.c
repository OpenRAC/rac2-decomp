#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;

/* lot6 -- measured bodies with sizes recorded in the catalogue. */
void func_US2_00349368(u8 *a0, s32 a1, s32 a2) { a0 += a1 * 4; *(s32 *)(a0 + 0x488) = a2; }


extern int GetLocalizedString(int a);
extern void hud_set_widget_field_b(char *a, int b);

/* stores the count in a field, then loops count times calling one helper on each successive 72-byte slot and passing the result to a second helper. */
void func_US2_00349378(char *a0, int a1, int *a2)
{
    int i;

    *(int *)(a0 + 1204) = a1;
    for (i = 0; i < a1; i++)
        hud_set_widget_field_b(a0 + 536 + i * 88, GetLocalizedString(a2[i]));
}
