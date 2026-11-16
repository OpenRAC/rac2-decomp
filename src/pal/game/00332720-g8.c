#include "include_asm.h"
#include "names.h"
extern int g_game_time;
extern char *g_moby_list_head;
extern float ref_L00_00330BC0_00 __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern int pickup_start_fly_if_idle(void *, void *);

/* Every other frame, makes each nearby class 19 moby start to fly away from the object (PAL: same as USA v1.01). */
void moby_push_nearby_away_pal(char *object)
{
    char *cursor;
    if (g_game_time & 1) {
        cursor = g_moby_list_head;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (fast_vec_dist(cursor + 0x10, object + 0x10) < ref_L00_00330BC0_00)
                    pickup_start_fly_if_idle(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}
