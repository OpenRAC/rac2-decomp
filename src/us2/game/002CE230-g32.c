#include "names.h"
/* func_US2_002CE230 (368 bytes, boot + 27 levels): USA v2.00's copy of v1.01's func_002CD250
   (src/game/002CD250-g32.c, where its notes are). The field it reads at D_001A8CFC + 0x3F364 in
   v1.01 sits at 0x3F9EC here (a field of the large object moved), so v1.01's C cannot build to both
   and tools/carry.py --demote lists func_002CD250 in config/us2/not_carried.tsv. Every other word
   is v1.01's. Compiled at -G32 like v1.01's unit (config/cflags.txt). */
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

int func_US2_002CE230(void)
{
    int result = 0;
    int old = menu_get_setting_value();
    int flags = g_pad_state.flags;

    if (flags & 0x10) {
        g_pause_menu_state.value = (int)D_00259328;
        if (D_001A8CFC != 0 && *(void **)(D_001A8CFC + 0x3F9EC) != 0)
            tex_upload_queued_blocks(*(void **)(D_001A8CFC + 0x3F9EC));
    } else if (flags & 0x900) {
        if (D_001A8CFC != 0 && *(void **)(D_001A8CFC + 0x3F9EC) != 0)
            tex_upload_queued_blocks(*(void **)(D_001A8CFC + 0x3F9EC));
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
