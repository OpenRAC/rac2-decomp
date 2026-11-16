#include "names.h"
/* Carried from rac3-decomp (src/frontbin/3BE448.c, func_003C2DC0): the same instructions.
   Ages the 16 watched objects of D_001B1AC0: a slot whose object is gone (flag 0x80 at
   +0x20, or +0x42 no longer 0xFF) is cleared; an object at rest that has waited 20 frames
   and whose current entry matches gets +0x44 = 1 - +0x4C and is passed to func_002A05A8;
   otherwise its counter in D_001B1B00 counts up. */

#include "common.h"

typedef struct { u8 p0[0x13]; u8 f13; } WatchEntry;
typedef struct { u8 p0[0x48]; WatchEntry *arr[1]; } WatchTable;
typedef struct {
    u8 p0[0x20];
    u8 f20;
    u8 p21[3];
    WatchTable *f24;
    u8 p28[9];
    u8 f31;
    u8 p32[0x10];
    u8 f42;
    u8 f43;
    f32 f44;
    u8 p48[4];
    f32 f4C;
} WatchObject;

extern WatchObject *g_watched_objects[16];
extern s32 g_watched_object_ages[16];
extern void func_002A05A8();

/* Checks the 16 watched objects each frame, drops the ones that are gone, and acts on those that have been still for 20 frames. */
void moby_update_watched_objects(void) {
    s32 i = 0;
    WatchObject *watched;
    do {
        watched = g_watched_objects[i];
        if (watched != 0) {
            if (watched->f20 & 0x80) { g_watched_objects[i] = 0; goto z; }
            if (watched->f42 != 0xFF) { g_watched_objects[i] = 0; goto z; }
            if (watched->f31 == 0 && g_watched_object_ages[i] >= 20) {
                if (watched->f24->arr[watched->f43]->f13 == watched->f42) {
                    watched->f44 = 1.0f - watched->f4C;
                    func_002A05A8(g_watched_objects[i]);
                }
            } else {
                g_watched_object_ages[i]++;
            }
        } else {
z:
            g_watched_object_ages[i] = 0;
        }
        i++;
    } while (i < 16);
}
