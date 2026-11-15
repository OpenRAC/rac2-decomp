#include "include_asm.h"
#include "common.h"

extern int hero_is_current_selected_id(char *object);
extern int CollLine(void *a, void *b, int mode, void *self, int flag);
extern char g_hero_position[];
extern int ref_L14_003DE908_00;

/* Tells whether the object is hit by the player or by the aim ray. */
int moby_is_hit_by_player_or_aim(char *moby)
{
    char buf[0x20];

    if (hero_is_current_selected_id(moby) != 0)
        return 1;
    qcopy(buf, g_hero_position);
    qcopy(buf + 0x10, g_hero_position);
    *(float *)(buf + 0x18) = *(float *)(buf + 0x18) - 3.0f;
    if (CollLine(buf, buf + 0x10, 0x10, 0, 0) != 0 && ref_L14_003DE908_00 == (int)moby)
        return 1;
    return 0;
}
