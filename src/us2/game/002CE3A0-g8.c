#include "common.h"

/* func_US2_002CE3A0, the USA v2.00 copy of func_002CD3C0: the same C, where the text position
   (437, 367 in the data) comes from a pair of globals, the string becomes 0x2BE5 and the owner
   field moves by 0x688. */

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern int g_centered_text_x __attribute__((sda));
extern int g_centered_text_y[] __attribute__((sda));
extern void func_US2_0029CFE0(void);
extern char *g_resident_data_base[] __attribute__((sda));

extern int text_draw_centered_small(int v, int p7, unsigned long long k, char *r, int m1);

extern void DrawMobysSetup(void);

extern void mem_fill_scratch_area(void);

extern void mem_save_scratch_area(void);

extern void mem_restore_scratch_area(void);

extern int tex_run_upload_and_setup(void);

extern void hud_init_lighting_colors(void *);

extern void hud_reset_render_state(void *);

extern void menu_attach_slot_packets_us2(char *);

extern void gfx_draw_shadowed_sprite(void *, char *);

extern void gfx_wait_for_dma_status_bits(u64);

extern void PatchMobyGifs(void);

int func_US2_002CE3A0(void)
{
    SetupGifPaging(0);
    func_US2_0029CFE0();
    text_draw_centered_small(g_centered_text_x, g_centered_text_y[0], 0x80F0F0F0ULL, (char *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    if (g_resident_data_base[0] != 0) {
        if (*(int *)((char *)g_resident_data_base[0] + 0x38000 + 0x79EC) != 0) {
            char *owner;
            DrawMobysSetup();
            mem_fill_scratch_area();
            mem_save_scratch_area();
            owner = *(char **)(g_resident_data_base[0] + 0x38000 + 0x79EC);
            hud_init_lighting_colors(owner);
            hud_reset_render_state(owner);
            menu_attach_slot_packets_us2(owner);
            gfx_draw_shadowed_sprite(owner, owner + 0xC00);
            mem_restore_scratch_area();
            tex_run_upload_and_setup();
            gfx_wait_for_dma_status_bits(0x10);
            PatchMobyGifs();
        }
    }
    return 0;
}
