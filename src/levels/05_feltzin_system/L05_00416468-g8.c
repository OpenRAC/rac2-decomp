#include "names.h"
/* Built with -G8 (the beam texture is reached through $gp) and -fno-strength-reduce, which
   keeps the record counter counting up as in retail. */
#include "common.h"

/* The 128 interpolation records of L05_004161B0.c: position, next, offset, origin, then the
   owner at +0x40; 0x50 bytes each. */
extern char g_beam_records[];
extern int g_beam_l05_strip_texture __attribute__((sda));
extern float math_random_angle(void);
/* func_L05_00416698(start, end, color, texture, width): the width is declared before the
   texture; each register bank keeps its order (a0-a3, f12). */
extern void gfx_l05_draw_beam_strip(void *, void *, unsigned int, float, int);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);

/* Draws a two-layer beam from position to next and four glow sprites at origin and next for
   every interpolation record the object owns. */
void DrawOwnedBeamRecords(char *obj)
{
    char *table = g_beam_records;
    char *next = table + 0x10;
    char *origin = table + 0x30;
    char *position = table;
    int i;

    for (i = 0; i < 128; i++) {
        if (*(char **)(origin + 0x10) == obj) {
            gfx_l05_draw_beam_strip(position, next, 0x807F7F7F, 0.025f, g_beam_l05_strip_texture);
            gfx_l05_draw_beam_strip(position, next, 0x60008000, 0.05f, g_beam_l05_strip_texture);
            gfx_draw_billboard_quad(origin, 0x31, 0x60008000, 1, 1.35f, 0.35f, math_random_angle());
            gfx_draw_billboard_quad(origin, 0x31, 0x807F7F7F, 1, 1.0f, 0.35f, math_random_angle());
            gfx_draw_billboard_quad(next, 0x31, 0x60008000, 1, 0.125f, 0.08f, math_random_angle());
            gfx_draw_billboard_quad(next, 0x31, 0x807F7F7F, 1, 0.08f, 0.08f, math_random_angle());
        }
        origin += 0x50;
        next += 0x50;
        position += 0x50;
    }
}
