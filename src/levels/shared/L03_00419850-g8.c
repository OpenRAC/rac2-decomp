#include "include_asm.h"
#include "common.h"


typedef struct { f32 v[4]; } Vec4 __attribute__((aligned(16)));

extern f32 g_marker_sprite_height_offset __attribute__((sda));
extern s32 g_marker_sprite_texture __attribute__((sda));
extern f32 g_marker_sprite_size __attribute__((sda));

extern unsigned char *effect_create_timed(Vec4 *, u8 *, s32, s32, f32, s32, s32, s32);

/* Draws a small marker sprite just above the object. */
void moby_draw_marker_sprite(u8 *object)
{
    Vec4 frame;
    u8 *state = *(u8 **)(object + 0x68);

    qcopy(&frame, object + 0x10);
    frame.v[2] = frame.v[2] + g_marker_sprite_height_offset;
    effect_create_timed(&frame, object, *(s32 *)(state + 0x10) + 2,
                      g_marker_sprite_texture, g_marker_sprite_size, 0x20, 2, 0xFF);
}
