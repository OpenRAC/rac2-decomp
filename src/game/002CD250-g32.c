#include "names.h"
/* func_002CD250 in its own unit, a sibling of func_002D01D0: retail reads D_001A8CFC both
   absolute and through $gp, so the file is compiled at -G32 (config/cflags.txt). */
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern char *D_001A8CFC;
extern short D_001A63AC[];
extern char D_00259328[];
extern MenuFields D_00259E70;
extern FlagTarget *D_00259E54[];
extern int menu_get_setting_value(void);
extern void tex_upload_queued_blocks(void *);
extern int func_0029C208(int);

/* Handles button input for a menu page: confirm picks the selected item, back closes the page, and the cursor highlight flag stays in step with the selection. */
int menu_handle_selection_input(void)
{
    int result = 0;
    int old = menu_get_setting_value();
    int flags = g_pad_state.flags;

    if (flags & 0x10) {
        g_pause_menu_state.value = (int)D_00259328;
        if (D_001A8CFC != 0 && *(void **)(D_001A8CFC + 0x3F364) != 0)
            tex_upload_queued_blocks(*(void **)(D_001A8CFC + 0x3F364));
    } else if (flags & 0x900) {
        if (D_001A8CFC != 0 && *(void **)(D_001A8CFC + 0x3F364) != 0)
            tex_upload_queued_blocks(*(void **)(D_001A8CFC + 0x3F364));
        result = 1;
    } else
        func_0029C208(flags);
    if (D_001A8CFC != 0) {
        int cur = menu_get_setting_value();
        if (old == cur && D_001A63AC[0] == 0
            && ((D_00259E70.f50 == cur && D_00259E70.f44 == 2) || (D_00259E70.f54 == cur && D_00259E70.f44 == 4)))
            D_00259E54[0]->flags &= -5;
        else
            D_00259E54[0]->flags |= 4;
        D_00259E70.f58 = cur;
    }
    return result;
}
