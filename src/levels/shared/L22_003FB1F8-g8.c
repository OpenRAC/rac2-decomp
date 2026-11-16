#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *CreateMoby(int);
extern f32 math_random_angle(void);
extern void set_identity_rotation_rows(void *);
extern void part_init_effect_slots(void *);
extern int g_linked_object_spawn_counter;

/* Creates a moby of class 3642 linked to the owner at the given position, with a size scale; a nonzero flag gives it a staggered timer. */
char *SpawnLinkedScaledObject(char *owner, TI128 *pos, int staggered, f32 scale) {
    char *created = (char *)CreateMoby(0xE3A /* moby class 3642 */);
    if (created != 0) {
        u8 *ctl = *(u8 **)(created + 0x68);
        *(short *)(ctl + 0x2A) = staggered;
        if ((short)staggered != 0) {
            int counter = g_linked_object_spawn_counter;
            g_linked_object_spawn_counter = counter + 1;
            *(u16 *)(created + 0x96) = (counter + 2) % 31;
        }
        /* This order also preserves the retail flag-store scheduling. */
        *(u8 *)(created + 0x30) = 0xFF;
        *(u16 *)(created + 0x34) |= 0x108;
        *(u16 *)(created + 0x32) = 0x50;
        *(u8 *)(created + 0x31) = 1;
        *(u8 *)(created + 0x20) = 0;
        *(f32 *)(created + 0x2C) = *(f32 *)(*(u32 *)(created + 0x24) + 0x24) * scale;
        *(u32 *)(ctl + 0x20) = (u32)owner;
        *(f32 *)(ctl + 0x4C) = math_random_angle();
        qcopy(created + 0x10, pos);
        *(u16 *)(created + 0x34) |= 0x41;
        set_identity_rotation_rows(created + 0xC0);
        part_init_effect_slots(created);
    }
    return created;
}
