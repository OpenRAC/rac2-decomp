#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;

extern int func_00343060(u8 *);
extern void func_00335E68(u8 *, int);
extern void func_00335E38(void *, float, float, float, float);
extern float D_001AE214;
extern float D_001AE210 __attribute__((sda));
/* Hides the menu's label when its list is empty, otherwise places it next to the menu. */
void func_003435C8(u8 *menu) {
    if (GetMenuListCount(menu + 0x298) == 0) {
        SetFlagValue(menu + 0x1F8, 0);
    } else {
        int *position = *(int **)(menu + 0x288);
        SetFirstFloat4(menu + 0x1F8, D_001AE210 + *(float *)position,
                      D_001AE214 + *(float *)((u8 *)position + 4), 0.0f, 0.0f);
    }
}

extern const char *func_00288FB8(int);
extern void func_00115DA8(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern void func_00115AC0(void *, int, int);
extern char D_001AE220[];
extern char D_001ADBC8[];
extern float D_001AE218 __attribute__((sda));
extern float D_001AE21C;
/* Fills in the menu's title text for the current mode and puts it in place. */
void func_00343638(char *object)
{
    char buffer[256];
    float *position;
    SetFlagValue((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x294)) {
    case 0:
        Sprintf(buffer, D_001AE220, GetLocalizedString(0x2D51), GetLocalizedString(0x2D55));
        break;
    case 2:
        Sprintf(buffer, D_001AE220, GetLocalizedString(0x2D54), GetLocalizedString(0x2D55));
        break;
    case 1:
        Sprintf(buffer, D_001AE220, GetLocalizedString(0x2D52), GetLocalizedString(0x2D55));
        break;
    }
    if (strlen_001157AC(buffer) >= 49)
        Sprintf(object + 0x120, D_001ADBC8, GetLocalizedString(0));
    else
        strncpy(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x288);
    SetFirstFloat4(object + 0x1B0, D_001AE218 + position[0], D_001AE21C + position[1], 0.0f, 0.0f);
}
