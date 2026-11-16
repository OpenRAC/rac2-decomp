#include "include_asm.h"
#include "names.h"

extern void boss_part_init_health_pal(int);
extern void boss_part_count_frame(int);

/* Per-frame update of the boss part object: runs its main update, then counts a frame. (PAL) */
void boss_part_update_pal(int part)
{
    boss_part_init_health_pal(part);
    boss_part_count_frame(part);
}


