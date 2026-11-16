#include "include_asm.h"
#include "names.h"

extern void cam_update_zone_control(void);

/* runs the level's one-shot start-up; the caller uses this only for its side effects */
int level_run_startup_pal(void)
{
    cam_update_zone_control();
    return 0;
}

