#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern u8 *g_moby_l04_group_lists[];
extern u8 *g_moby_l04_pool __attribute__((sda));

extern void FastVecSub(char *a0, char *a1, char *a2);
extern float FastVecDot(char *a0, char *a1);
extern void coll_world_pos_to_grid_cell(void *input, int *out_x, int *out_y);
extern int part_l00_alloc_effect_slot(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, f32 *a6);
extern s32 g_screen_width __attribute__((sda));
extern s32 g_screen_height;
extern f32 D_L04_001B31EC __attribute__((sda));
extern char D_L04_001B9680[];

/* Projects the object into the screen, and while its position is inside the
   view asks the level's cursor helper to follow it. */


/* walks the entry's two-byte id list and flags each live object of one class */
/* Goes through the objects in this object's group and flags every Gadgetron Hound in it so it reacts. */
void gadgetron_hound_flag_group(u8 *object) {
    u8 *mobyPool;
    u8 *idList;
    u16 *idPtr;
    char *other;

    if (object[0x21] == 0xFF)
        return;
    idList = g_moby_l04_group_lists[object[0x21]];
    if (idList == 0)
        return;
    idPtr = (u16 *)idList;
    mobyPool = g_moby_l04_pool;
    for (;;) {
        other = (char *)(mobyPool + (*idPtr & 0x7FFF) * 256);
        if ((s8)other[0x20] >= 0) {
            if (*(s16 *)(other + 0xAA) == MOBY_CLASS_GADGETRON_HOUND_OF_CUDDLY_DEATH) {
                *(u16 *)(*(u32 *)(other + 0x68) + 0x306) = 1;
            }
        }
        if ((s16)*idPtr < 0)
            break;
        idPtr++;
    }
}

/* same walk, one class flag and a visit counter instead */
/* Goes through the objects in this object's group and flags every Tribesman in it and counts how many times this was done. */
void tribesman_flag_group(u8 *object) {
    u8 *mobyPool;
    u8 *idList;
    u16 *idPtr;
    char *other;

    if (object[0x21] == 0xFF)
        return;
    idList = g_moby_l04_group_lists[object[0x21]];
    if (idList == 0)
        return;
    idPtr = (u16 *)idList;
    mobyPool = g_moby_l04_pool;
    for (;;) {
        other = (char *)(mobyPool + (*idPtr & 0x7FFF) * 256);
        if ((s8)other[0x20] >= 0) {
            if (*(s16 *)(other + 0xAA) == MOBY_CLASS_TRIBESMAN) {
                char *vars = *(char **)(other + 0x68);
                *(u16 *)(vars + 0x276) = 1;
                *(u32 *)(vars + 0x574) += 1;
            }
        }
        if ((s16)*idPtr < 0)
            break;
        idPtr++;
    }
}

typedef int TI128 __attribute__((mode(TI)));

extern u16 **D_L04_001A9014;
extern u8 *D_L04_001B2B54;
extern u8 D_L04_001B17E0[8] __attribute__((sda));
extern u8 D_L04_001B17D8[8] __attribute__((sda));
extern u8 D_L04_001B17D0[8] __attribute__((sda));
extern s32 D_L04_001B1800 __attribute__((sda));

extern void moby_set_state(void *a0, s32 a1, s32 a2);
extern void *part_find_owned_effect_slot(void *a0, s32 a1, s32 a2);
extern void ScatterObjectPieces(void *a0, void *a1, void *a2, void *a3, s32 a4, s32 a5, s32 a6,
                              s32 a7, s32 a8, s32 a9, s32 a10);
extern void part_spawn_scaled_bolts(void *a0, s32 a1, f32 f12);
extern void vec_local_offset_to_world(void *a0, void *a1, f32 f12, f32 f13, f32 f14);
/* Integer and float arguments take separate registers, so the interleaving below changes no
   register, only the order the caller loads them in; this is the measured order. */
extern void SpawnExplosionEffects(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern void moby_mark_spawned(void *a0);

extern s32 D_L04_001A8F00;
extern u8 D_001A7A40;
extern u8 D_L04_001B1DE0;
extern u8 D_L04_001B1DE1;
extern f32 D_L04_001B1E00;
extern f32 D_L04_001B1E04;
extern f32 D_L04_001B1E08;
extern void func_3325E0(void *a0, void *a1, void *a2);

/* func_L04_004389C0 reads D_001A79F0 through $gp; it is in
   src/levels/04_barlow/L04_004389C0-g8.c. */

/* The level's list of live objects: the count is at +0x44 and the entries at +0x18C. */
typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 *entries[16];
} L04Base004;

extern L04Base004 D_L04_001BD380;

/* Walks the level's list of objects and, for the one with the object's own id, asks the
   level's helper to clear it and sets the level's three timers. */
void conversation_clear_target_on_talk(u8 *object) {
    u32 *entry;
    s32 i;

    if (D_L04_001A8F00 == 2) {
        if (D_001A7A40 != 0) {
            for (i = 0; i < D_L04_001BD380.count; i++) {
                entry = D_L04_001BD380.entries[i];
                if (*(s16 *)((u8 *)entry + 0xAA) == *(s16 *)(object + 0xAA)) {
                    if (D_L04_001B1DE1 == 0) {
                        func_3325E0(entry, 0, &D_L04_001B1DE0);
                        D_L04_001B1E00 = 2.75f;
                        D_L04_001B1E04 = 2.75f;
                        D_L04_001B1E08 = 2.75f;
                    }
                }
            }
        }
    }
}

/* State 0 arms the object and moves it to state 1; state 1 moves to state 2 once func_002A9640
   finds a match while the state word is clear; state 2 makes the three func_002ABBB8 calls,
   sets bit 2 of byte +0x1E of every entity of the group at +4 and calls func_0029F338. */
void barlow_effect_burst_update(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    f32 A[4] __attribute__((aligned(16)));
    f32 B[4] __attribute__((aligned(16)));
    u16 *idPtr;
    u8 *entity;

    switch (object[0x20]) {
    case 0:
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) != 0) {
            if (*(s32 *)state == 0)
                moby_set_state(object, 2, -1);
        }
        object[0xA8] = 0xFF;
        break;
    case 2:
        ScatterObjectPieces(object, D_L04_001B17E0, D_L04_001B17D8, D_L04_001B17D0, 0x7F, 0,
                          D_L04_001B1800, 1, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts(object, 5, 0.0f);
        *(TI128 *)A = 0;
        A[2] = 0.16666667f;
        vec_local_offset_to_world(object, B, 0.0f, 0.0f, 4.0f);
        SpawnExplosionEffects(object, A, B, 0.0f, 0.0f, 50, 10, 10, 3.0f, 1.0f, 9.0f, 2.25f, -1, 15.0f, 1, 7,
                      -1, 0, 0x810001);
        SpawnExplosionEffects(object, A, B, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      1, 0x810001);
        SpawnExplosionEffects(object, A, B, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      2, 0x810001);
        if (*(s32 *)(state + 4) != 0) {
            for (idPtr = D_L04_001A9014[*(s32 *)(state + 4)];
                 idPtr != 0 &&
                 ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == D_L04_001A9014[*(s32 *)(state + 4)]);
                 idPtr++) {
                entity = D_L04_001B2B54 + ((*idPtr & 0x7FFF) << 5);
                if (entity == 0)
                    break;
                entity[0x1E] |= 4;
            }
        }
        moby_mark_spawned(object);
        break;
    }
}
