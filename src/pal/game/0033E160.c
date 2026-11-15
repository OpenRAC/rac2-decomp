#include "include_asm.h"
#include "names.h"

extern char *GetLocalizedString(int);
extern void func_PAL_0033CF78(void *, char *, char *, char *);
extern void func_PAL_0033CD50(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);
extern int snd_play_from_global_bank(int a, int b, int c);
extern void UpdateViewContext(void);
extern unsigned char D_001A7BB1;

/* func_PAL_0033E160, the PAL copy of func_0033C2D8: the same C, with the three-string setup added. */
int func_PAL_0033E160(char *object, int mask)
{
    float *v;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0x10FC);
    second = GetLocalizedString(0xB5F);
    func_PAL_0033CF78(child, text, second, GetLocalizedString(0xB60));
    func_PAL_0033CD50(child);
    v = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, v[0], v[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0) {
        D_001A7BB1 = D_001A7BB1 == 0;
        snd_play_from_global_bank(4, 0, 0);
        UpdateViewContext();
    }
    return (mask >> 6) & 1;
}
