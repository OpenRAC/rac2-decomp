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

extern int D_L00_001B19C8;
extern char *D_L00_001B1EA8 __attribute__((sda));
extern float D_L00_001AF8C0 __attribute__((sda));
extern char *D_0018C0B0[];
extern void func_00282C88(void *);
extern int func_00277F48(void *, float, int, void *, void *);
extern float func_00282E48(void *, void *);
extern void ref_L00_003B3AF8_00(void *, void *);

/* Broadcasts an area message from the object, then hands the object to every kind-0x13
   object of the list within the same radius. */
void func_L00_003B3AF8(char *object)
{
    AreaMessage_F3B3AF8 msg;
    char *cursor;

    if (D_L00_001B19C8 & 1) {
        msg.source = object;
        msg.flags = 0x10000;
        msg.kind = 8;
        msg.sub = 0;
        msg.id = *(u16 *)(object + 0xAA);
        msg.arg1C = 0;
        func_00282C88(&msg);
        msg.v[3] = 5627.9248f;
        msg.arg20 = 0;
        func_00277F48(object + 0x10, D_L00_001AF8C0, 0, D_0018C0B0[0], &msg);
        if (D_L00_001B19C8 & 1) {
            cursor = D_L00_001B1EA8;
            while (cursor) {
                int kind = *(unsigned char *)(cursor + 0x20);
                if (kind == 0xfe) return;
                if (kind == 0xfd) return;
                if (cursor && *(char **)(cursor + 0x24) &&
                    *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                    if (fast_vec_dist(cursor + 0x10, object + 0x10) < D_L00_001AF8C0)
                        ref_L00_003B3AF8_00(cursor, object);
                }
                cursor = *(char **)(cursor + 0x28);
            }
        }
    }
}
