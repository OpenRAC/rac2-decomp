#include "names.h"
/* func_PAL_002CE218 (368 bytes, boot + 27 levels): Europe/Australia v1.00 (PAL)'s copy of v1.01's func_002CD250
   (src/game/002CD250-g32.c, where its notes are). The field it reads at D_001A8CFC + 0x3F364 in
   v1.01 sits at 0x3FA9C here (a field of the large object moved), so v1.01's C cannot build to both
   and tools/carry.py --demote lists func_002CD250 in config/pal/not_carried.tsv. Every other word
   is v1.01's. Compiled at -G32 like v1.01's unit (config/cflags.txt). */
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

int menu_handle_selection_input_pal(void)
{
    int result = 0;
    int old = menu_get_setting_value();
    int flags = g_pad_state.flags;

    if (flags & 0x10) {
        g_pause_menu_state.value = (int)g_menu_page_options;
        if (g_resident_data_base != 0 && *(void **)(g_resident_data_base + 0x3FA9C) != 0)
            tex_upload_queued_blocks(*(void **)(g_resident_data_base + 0x3FA9C));
    } else if (flags & 0x900) {
        if (g_resident_data_base != 0 && *(void **)(g_resident_data_base + 0x3FA9C) != 0)
            tex_upload_queued_blocks(*(void **)(g_resident_data_base + 0x3FA9C));
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
