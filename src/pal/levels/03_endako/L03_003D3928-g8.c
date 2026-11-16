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

/* Debris from a smashed trash can: waits for the spawn to finish, breaks when hit by a Ratchet
   weapon or touched, fades out after a while (PAL: 50 Hz timings). */
void trash_can_debris_update_pal(char *obj)
{
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (cam_moby_update_pal(obj)) {
            moby_set_state(obj, 1, -1);
            *(u16 *)(obj + 0x34) |= 0x2000;
        }
        break;
    case 1:
        if ((g_frame_l03_counter & 15) == (((int)obj >> 8) & 15)) {
            int count = coll_process_hit(0.2f, obj + 0x10, 0, obj, 0);
            if (count > 0) {
                int remaining = count;
                char **hit_list = g_nearby_l03_moby_list;
                do {
                    int type = *(s16 *)(*hit_list + 0xAA);
                    if (type == 0xFF3 || type == 0xFFD)
                        moby_set_state(obj, 3, -1);
                    --remaining;
                    ++hit_list;
                } while (remaining);
            }
        }
        if (vec_distance_xy(obj + 0x10, &g_shared_trace_point) < 0.3f)
            moby_set_state(obj, 3, -1);
        {
            u32 frame_count = *(u16 *)(obj + 0x96);
            u32 old_count = frame_count++;
            *(u16 *)(obj + 0x96) = frame_count;
            if (old_count > 500 && !*(u8 *)(obj + 0x31))
                moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
    case 3: {
        int fade_step = *(u8 *)(obj + 0x20) == 2 ? 2 : 8;
        int alpha = *(u8 *)(obj + 0x23);
        if (alpha < fade_step) moby_mark_spawned(obj);
        else *(u8 *)(obj + 0x23) = alpha - fade_step;
        break;
    }
    }
}
