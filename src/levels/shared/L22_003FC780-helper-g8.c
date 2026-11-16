#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *CreateMoby(int);
extern void set_identity_rotation_rows(void *);
extern int g_linked_object_spawn_counter;

/* Creates a moby of class 3643 linked to the owner at the given position, with a size scale; a nonzero flag gives it a staggered timer. */
char *linked_scaled_object_spawn_spin_shrink(char *owner, TI128 *pos, int staggered, f32 scale) {
    char *created = CreateMoby(0xE3B /* moby class 3643 */);
    if (created != 0) {
        u8 *ctl = *(u8 **)(created + 0x68);
        *(short *)(ctl + 0x2A) = staggered;
        if ((short)staggered != 0) {
            int counter = g_linked_object_spawn_counter;
            g_linked_object_spawn_counter = counter + 1;
            *(u16 *)(created + 0x96) = (counter + 2) % 31;
        }
        *(u16 *)(created + 0x34) |= 0x108;
        *(u8 *)(created + 0x30) = 0xFF;
        *(u16 *)(created + 0x32) = 0x50;
        *(u8 *)(created + 0x31) = 1;
        *(u8 *)(created + 0x20) = 0;
        *(f32 *)(created + 0x2C) = *(f32 *)(*(u32 *)(created + 0x24) + 0x24) * scale;
        *(u32 *)(ctl + 0x20) = (u32)owner;
        qcopy(created + 0x10, pos);
        set_identity_rotation_rows(created + 0xC0);
    }
    return created;
}
