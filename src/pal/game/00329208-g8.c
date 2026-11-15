#include "include_asm.h"
#include "names.h"
extern int g_game_time;
extern char *D_001B1B68;
extern float ref_L00_00327A60_00 __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern void pickup_start_fly_if_idle(void *, void *);

void func_PAL_00329208(char *object)
{
    char *cursor;
    if (g_game_time & 1) {
        cursor = D_001B1B68;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (fast_vec_dist(cursor + 0x10, object + 0x10) < ref_L00_00327A60_00)
                    pickup_start_fly_if_idle(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}
