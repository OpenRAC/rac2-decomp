#include "include_asm.h"

#include "common.h"
extern int cam_moby_update_pal(char *);
extern void moby_set_state(char *, int, int);
extern int coll_process_hit(float, void *, int, void *, int);
extern float vec_distance_xy(void *, void *);
extern void moby_mark_spawned(void *);
extern int g_frame_l03_counter;
extern char *g_nearby_l03_moby_list[];
extern int g_shared_trace_point __attribute__((sda));

void trash_can_debris_update_pal(char *a0)
{
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        if (cam_moby_update_pal(a0)) {
            moby_set_state(a0, 1, -1);
            *(u16 *)(a0 + 0x34) |= 0x2000;
        }
        break;
    case 1:
        if ((g_frame_l03_counter & 15) == (((int)a0 >> 8) & 15)) {
            int count = coll_process_hit(0.2f, a0 + 0x10, 0, a0, 0);
            if (count > 0) {
                int remaining = count;
                char **p = g_nearby_l03_moby_list;
                do {
                    int type = *(s16 *)(*p + 0xAA);
                    if (type == 0xFF3 || type == 0xFFD)
                        moby_set_state(a0, 3, -1);
                    --remaining;
                    ++p;
                } while (remaining);
            }
        }
        if (vec_distance_xy(a0 + 0x10, &g_shared_trace_point) < 0.3f)
            moby_set_state(a0, 3, -1);
        {
            u32 timer = *(u16 *)(a0 + 0x96);
            u32 old = timer++;
            *(u16 *)(a0 + 0x96) = timer;
            if (old > 500 && !*(u8 *)(a0 + 0x31))
                moby_set_state(a0, 2, -1);
        }
        break;
    case 2:
    case 3: {
        int amount = *(u8 *)(a0 + 0x20) == 2 ? 2 : 8;
        int alpha = *(u8 *)(a0 + 0x23);
        if (alpha < amount) moby_mark_spawned(a0);
        else *(u8 *)(a0 + 0x23) = alpha - amount;
        break;
    }
    }
}
