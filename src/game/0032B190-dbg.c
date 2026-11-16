#include "include_asm.h"
#include "names.h"

/* func_0032B190 in its own -g unit: the second fade's division carries the
   statement-boundary padding. */

extern unsigned long GetEffectTextureDescriptor(int);
extern void gfx_draw_colored_rectangle(int, int, int, int, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_square(float);
extern float math_ease_out_quad(float);
extern void DrawQuadFaces(void *);
extern void part_draw_ring_piece_flashes(void *);
extern void part_draw_trail_nodes(void *);
extern short g_screen_adjust_offsets[];
extern unsigned long g_screen_fade_texture_desc[] __attribute__((sda));

/* Per-frame screen fade of the object: while it is in state 2 (and stays there
   after func_0032C2E8) the white overlay fades in over 60 frames, otherwise it
   fades out after frame 105 over 15 frames. */
void gfx_update_screen_fade(unsigned char *object)
{
    char *vars = *(char **)(object + 0x68);
    unsigned char state;
    float t;
    int v;

    g_screen_fade_texture_desc[0] = GetEffectTextureDescriptor(-1);
    state = object[0x20];
    if (state == 2) {
        DrawQuadFaces(object);
        if (object[0x20] == state) {
            t = IntToFloat(*(int *)(vars + 4)) / IntToFloat(0x3C);
            v = FloatToInt(math_square(1.0f - t) * 128.0f);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], (v << 24) | 0xFFFFFF);
            part_draw_ring_piece_flashes(object);
            goto done;
        }
    }
    if (*(int *)(vars + 4) >= 0x6A) {
        t = IntToFloat(*(int *)(vars + 4) - 0x69) / IntToFloat(0xF);
        v = FloatToInt(math_ease_out_quad(t) * 128.0f);
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], (v << 24) | 0xFFFFFF);
    }
done:
    part_draw_trail_nodes(object);
}
