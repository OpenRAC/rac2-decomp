#include "names.h"
/* func_002CD250 in its own unit, a sibling of func_002D01D0: retail reads D_001A8CFC both
   absolute and through $gp, so the file is compiled at -G32 (config/cflags.txt). */
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern char *g_resident_data_base;
extern short g_sequence_active_flag[];
extern char g_menu_page_options[];
extern MenuFields g_menu_cursor_fields;
extern FlagTarget *g_menu_flag_target_list[];
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
        g_pause_menu_state.value = (int)g_menu_page_options;
        if (g_resident_data_base != 0 && *(void **)(g_resident_data_base + 0x3F364) != 0)
            tex_upload_queued_blocks(*(void **)(g_resident_data_base + 0x3F364));
    } else if (flags & 0x900) {
        if (g_resident_data_base != 0 && *(void **)(g_resident_data_base + 0x3F364) != 0)
            tex_upload_queued_blocks(*(void **)(g_resident_data_base + 0x3F364));
        result = 1;
    } else
        func_0029C208(flags);
    if (g_resident_data_base != 0) {
        int cur = menu_get_setting_value();
        if (old == cur && g_sequence_active_flag[0] == 0
            && ((g_menu_cursor_fields.f50 == cur && g_menu_cursor_fields.f44 == 2) || (g_menu_cursor_fields.f54 == cur && g_menu_cursor_fields.f44 == 4)))
            g_menu_flag_target_list[0]->flags &= -5;
        else
            g_menu_flag_target_list[0]->flags |= 4;
        g_menu_cursor_fields.f58 = cur;
    }
    return result;
}
