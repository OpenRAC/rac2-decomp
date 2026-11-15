#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern void func_PAL_0029CB40(void);
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_PAL_001ABA40 __attribute__((sda));
extern int D_PAL_001ABA44[] __attribute__((sda));

extern void text_draw_right_aligned_small(int v, int p7, unsigned long long k, char *r, int m1);

extern void DrawMobysSetup(void);

extern void mem_fill_scratch_area(void);

extern void mem_save_scratch_area(void);

extern void mem_restore_scratch_area(void);

extern int tex_run_upload_and_setup(void);

extern void hud_init_lighting_colors(void *);

extern void hud_reset_render_state(void *);

extern void func_PAL_00350E98(char *);

extern void gfx_draw_shadowed_sprite(void *, char *);

extern void gfx_wait_for_dma_status_bits(u64);

extern void PatchMobyGifs(void);

/* func_PAL_002CE388, the PAL copy of func_002CD3C0: the same C, where the text
 * position comes from two PAL words (469, 359) in place of 0x1B5 and the scaled
 * 367, the string id becomes 0xB60 and the owner field moves to +0x3FA9C. Retail
 * reads the first word through $gp and the second through lui, as it does the
 * next pair at 0x1ABA48 in func_PAL_002CE9BC, hence the two declaration forms. */
int func_PAL_002CE388(void)
{
    SetupGifPaging(0);
    func_PAL_0029CB40();
    text_draw_right_aligned_small(D_PAL_001ABA40, D_PAL_001ABA44[0], 0x80F0F0F0ULL, (char *)GetLocalizedString(0xb60), -1);
    DoGifPaging();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7a9c) != 0) {
            char *owner;
            DrawMobysSetup();
            mem_fill_scratch_area();
            mem_save_scratch_area();
            owner = *(char **)(D_001A8CFC[0] + 0x38000 + 0x7a9c);
            hud_init_lighting_colors(owner);
            hud_reset_render_state(owner);
            func_PAL_00350E98(owner);
            gfx_draw_shadowed_sprite(owner, owner + 0xC00);
            mem_restore_scratch_area();
            tex_run_upload_and_setup();
            gfx_wait_for_dma_status_bits(0x10);
            PatchMobyGifs();
        }
    }
    return 0;
}
