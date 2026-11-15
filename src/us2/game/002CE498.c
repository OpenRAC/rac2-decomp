#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern char g_pause_menu_state[];
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState_2CC490;
extern int D_00138344;
typedef struct {
    char reserved00[0x44];
    int state;
    char reserved48[0x8];
    int handle;
    int last;
    int current;
} MenuObject_2CD4E0;
typedef struct {
    char reserved00[0x10];
    int flags;
} ToggleState_2CD4E0;
extern int D_00138344;
extern short D_001A63AC;
extern MenuObject_2CD4E0 D_00259C78;
extern ToggleState_2CD4E0 *D_00259C44;
extern int func_0029C248(int first, void *second);
extern int menu_get_setting_value(void);

int func_US2_002CE498(void)
{
    int local[4];
    int first = menu_get_setting_value();
    int result = 0;
    int flags = D_00138344;

    if (flags & 0x10) {
        int value = *(int *)(((CallbackState_2CC490 *)g_pause_menu_state)->source + 0xE0);
        if (value != 0)
            ((CallbackState_2CC490 *)g_pause_menu_state)->value = value;
        else if (((CallbackState_2CC490 *)g_pause_menu_state)->fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }

    if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C248(flags, local);
    }

    if (D_001A8CFC[0] != 0) {
        int second = menu_get_setting_value();
        if (first == second && D_001A63AC == 0 &&
            ((D_00259C78.handle == second && D_00259C78.state == 2) ||
             (D_00259C78.last == second && D_00259C78.state == 4))) {
            D_00259C44->flags &= -5;
        } else {
            D_00259C44->flags |= 4;
        }
        D_00259C78.current = second;
    }
    return result;
}

