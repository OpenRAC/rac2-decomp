#include "common.h"

typedef struct {
    float v[4];
    char *source;
    int flags;
    u8 kind;
    u8 sub;
    u16 id;
    int arg1C;
    int arg20;
} AreaMessage_F3B3AF8;

extern int g_frame_l00_counter;
extern char *g_moby_l00_list_head __attribute__((sda));
extern float g_blast_message_radius __attribute__((sda));
extern char *g_hero_moby[];
extern void vec_clear_128(void *);
extern int coll_process_hit(void *, float, int, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void ref_L00_003B3AF8_00(void *, void *);

/* Broadcasts an area message from the object, then hands the object to every kind-0x13
   object of the list within the same radius. */
void blast_broadcast_area_message(char *object)
{
    AreaMessage_F3B3AF8 msg;
    char *cursor;

    if (g_frame_l00_counter & 1) {
        msg.source = object;
        msg.flags = 0x10000;
        msg.kind = 8;
        msg.sub = 0;
        msg.id = *(u16 *)(object + 0xAA);
        msg.arg1C = 0;
        vec_clear_128(&msg);
        msg.v[3] = 5627.9248f;
        msg.arg20 = 0;
        coll_process_hit(object + 0x10, g_blast_message_radius, 0, g_hero_moby[0], &msg);
        if (g_frame_l00_counter & 1) {
            cursor = g_moby_l00_list_head;
            while (cursor) {
                int kind = *(unsigned char *)(cursor + 0x20);
                if (kind == 0xfe) return;
                if (kind == 0xfd) return;
                if (cursor && *(char **)(cursor + 0x24) &&
                    *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                    if (fast_vec_dist(cursor + 0x10, object + 0x10) < g_blast_message_radius)
                        ref_L00_003B3AF8_00(cursor, object);
                }
                cursor = *(char **)(cursor + 0x28);
            }
        }
    }
}
