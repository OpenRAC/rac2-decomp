#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F41A4C0;
extern s32 g_spray_piece_table_a __attribute__((sda));
extern s32 g_spray_piece_table_b __attribute__((sda));
extern s32 g_spray_piece_table_c __attribute__((sda));
extern s32 g_spray_piece_param __attribute__((sda));
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern void vec_local_to_world(char *, void *, float, float, float);
extern void *part_spawn_object_following_effect(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern void part_explode_object_into_pieces_pal(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void vec_local_offset_to_world(char *, void *, float, float, float);
extern char *SpawnExplosion_pal(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void moby_mark_spawned(char *);

/* The func_L20_00449178 three-state effect for level 17: the start point is taken from the
   object (func_L17_00326F38) and the closing spray is sized by the object's scale.
   func_PAL_L00_0032C328 is void here: a value-returning prototype moves the 0xFFFF
   argument's load. */
void spray_effect_update_pal(char *obj)
{
    V4_F41A4C0 v;
    s32 *rec = *(s32 **)(obj + 0x68);

    v.q = 0;
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        vec_local_to_world(obj, &v, 0.0f, 0.0f, 20.0f);
        part_spawn_object_following_effect(&v, obj, 0x10008080, -1, 336000.0f, 0.75f, 1, -1, 0, 0x60);
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x04010000, 0) != 0 && *rec == 0)
            moby_set_state(obj, 2, -1);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        part_explode_object_into_pieces_pal(obj, &g_spray_piece_table_c, &g_spray_piece_table_b, &g_spray_piece_table_a, 0xFFFF, 0, g_spray_piece_param, 0, 0xFFFF, 0xFF, 0);
        vec_local_offset_to_world(obj, &v, 0.0f, 0.0f, 20.0f);
        SpawnExplosion_pal(&v, 0, 0xC, 0xA, *(float *)(obj + 0x2C) * 10.0f, 20.0f, 0xA, 0xA, 0, 0, 1, 0, 0, 0);
        moby_mark_spawned(obj);
        return;
    }
}
