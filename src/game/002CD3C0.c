#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern float D_001B23A4[] __attribute__((sda));
extern void func_0029C1A8(void);
extern char *D_001A8CFC[] __attribute__((sda));

extern int text_draw_centered_small(int v, int p7, unsigned long long k, char *r, int m1);

extern void DrawMobysSetup(void);

extern void mem_fill_scratch_area(void);

extern void mem_save_scratch_area(void);

extern void mem_restore_scratch_area(void);

extern int tex_run_upload_and_setup(void);

extern void hud_init_lighting_colors(void *);

extern void hud_reset_render_state(void *);

extern void menu_attach_slot_packets(char *);

extern void gfx_draw_shadowed_sprite(void *, char *);

extern void gfx_wait_for_dma_status_bits(u64);

extern void PatchMobyGifs(void);

/* Draws a line of menu text near the bottom of the screen, then updates and draws the menu's attached panel if there is one. */
int menu_draw_footer_and_panel(void)
{
    int y;
    float position;

    SetupGifPaging(0);
    func_0029C1A8();
    position = 367.0f;
    y = (int)(D_001B23A4[0] * position + 0.5f);
    do {
        text_draw_centered_small(0x1B5, y, 0x80F0F0F0ULL, (char *)GetLocalizedString(0x2D4F), -1);
    } while (0);
    DoGifPaging();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7364) != 0) {
            char *owner;
            DrawMobysSetup();
            mem_fill_scratch_area();
            mem_save_scratch_area();
            owner = *(char **)(D_001A8CFC[0] + 0x38000 + 0x7364);
            hud_init_lighting_colors(owner);
            hud_reset_render_state(owner);
            menu_attach_slot_packets(owner);
            gfx_draw_shadowed_sprite(owner, owner + 0xC00);
            mem_restore_scratch_area();
            tex_run_upload_and_setup();
            gfx_wait_for_dma_status_bits(0x10);
            PatchMobyGifs();
        }
    }
    return 0;
}
