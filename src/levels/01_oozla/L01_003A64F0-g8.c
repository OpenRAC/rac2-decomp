#include "names.h"
/* Copies the object's quad at +0x10 into v and runs it through func_00282CC0 with t
   (func_00282F20 of +0xE0 and the $gp float) and func_00282CF0 with +0xC0, copies +0xF0
   into w, then passes v and w to func_00335438, or to func_00335370 and func_003353C8
   when the +0x86 short of D_L01_001B9510's object is 5. */
#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

extern f32 g_vehicle_beam_offset_length __attribute__((sda));
extern u8 *g_vehicle_beam_object __attribute__((nosda));
extern void vec_scale_to_length(u8 *, u8 *, f32);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern void FastVecSub(u8 *, u8 *, u8 *);
extern void object_copy_vector_to_selected(u8 *);
extern void cam_set_state_rotation(u8 *);
extern void SetCamera5Pose(u8 *, u8 *, s32, s32, s32);

/* Works out a point in front of the object and a second point, then draws a line or beam between them. */
void gfx_draw_vehicle_beam(u8 *object)
{
    u128 start[1];
    u128 end[1];
    u128 offset[1];

    qcopy(start, object + 0x10);
    vec_scale_to_length((u8 *)offset, object + 0xE0, g_vehicle_beam_offset_length);
    FastVecAdd((u8 *)start, (u8 *)start, (u8 *)offset);
    FastVecSub((u8 *)start, (u8 *)start, object + 0xC0);
    qcopy(end, object + 0xF0);
    if (*(s16 *)(g_vehicle_beam_object + 0x86) != 5) {
        SetCamera5Pose((u8 *)start, (u8 *)end, 0, 0, 0);
    } else {
        object_copy_vector_to_selected((u8 *)start);
        cam_set_state_rotation((u8 *)end);
    }
}
