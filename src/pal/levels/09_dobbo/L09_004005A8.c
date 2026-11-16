#include "include_asm.h"


#include "common.h"
extern int g_beam_slot_angle_x[] MACRO_ADDR;
extern int g_beam_slot_angle_y[] MACRO_ADDR;
extern int g_beam_slot_angle_z[] MACRO_ADDR;
extern int g_beam_slot_light_handle[] MACRO_ADDR;
extern int g_beam_slot_light_handle_alt[] MACRO_ADDR;
extern int g_beam_slot_third_value[] MACRO_ADDR;
extern int g_beam_slot_flag[] MACRO_ADDR;
extern void VU1_addGSregister(int, unsigned long long);
extern void gfx_append_vectors_to_packet(int, int, unsigned long, int, unsigned long);
extern void scale_vector_xyz_in_place(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern int math_fast_helper_a(void *, float);
extern int level_is_resident_flag_clear(void);
extern float g_beam_slot_uv_scroll[16] MACRO_ADDR;
extern char g_beam_strip_buffers[][0x60];
extern int g_beam_slot_state_2[16] MACRO_ADDR;
extern unsigned char *g_sound_slot_ptrs[16][2];
extern void DrawDobboPairedGlowQuads(void *, int, int);
extern void DrawBeamLinkStrip_pal(int, int, void *, int, int, int, int, int);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void FastVecAdd(char *, char *, char *);
extern int math_random_int_range(int, int);
extern void DrawBeamLinks(char *);
extern Quad g_sound_slot_matrices[][4];
extern Quad g_sound_slot_positions[];
typedef struct {
    int x;
    int y;
} DobboLinkScreen;

/* Draws every active beam link whose bounding sphere is visible: a large and a small textured
   quad per link, with a per-link scroll offset that advances while func_L02_002F1658() is true. */
void DrawBeamLinks_pal(char *moby)
{
    Vec sphere, midpoint;
    int i, fade, x, y, big, small;
    char *small_tex;
    DobboLinkScreen *screen = *(DobboLinkScreen **)(moby + 0x68);

    VU1_addGSregister(0x47, 0x51001);
    for (i = 0; i < 16; i++) {
        if (!g_sound_slot_ptrs[i][0] || !g_sound_slot_ptrs[i][1] || g_beam_slot_state_2[i] < 2)
            continue;

        FastVecAdd((char *)&midpoint, g_sound_slot_ptrs[i][0] + 0x10, g_sound_slot_ptrs[i][1] + 0x10);
        sphere.q = midpoint.q;
        scale_vector_xyz_in_place(&midpoint, &sphere, 0.5f);
        sphere.f[3] = fast_vec_dist(g_sound_slot_ptrs[i][0] + 0x10, g_sound_slot_ptrs[i][1] + 0x10) * 0.5263158f;
        if (math_fast_helper_a(&sphere, 64.0f) == -1)
            continue;

        big = i * 2;
        small = big + 1;
        fade = g_sound_slot_ptrs[i][0][0x23];
        if (level_is_resident_flag_clear()) {
            g_beam_slot_uv_scroll[i] -= 0.24000001f;
            if (g_beam_slot_uv_scroll[i] <= -8.0f)
                g_beam_slot_uv_scroll[i] += 8.0f;
        }
        small_tex = g_beam_strip_buffers[small];
        DrawDobboPairedGlowQuads(g_sound_slot_ptrs[i][0], i, fade);
        y = screen->y + 63;
        x = screen->x + 63;
        DrawBeamLinkStrip_pal(y, x, g_beam_strip_buffers[big], 128, 64, fade, i, -1);
        DrawBeamLinkStrip_pal(y, x, small_tex, 48, 16, fade, i, math_random_int_range(1, 6));
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340BUL, 0x42, 0x8000000044UL);
}


