#include "names.h"
/* func_002CBC58 (2,100 bytes, 28 places): draws the pause-menu panels. -G8 sibling of 002C7748.c.
 * The crop arithmetic follows the renderer in RAC1's src/game/pause.c.
 * Retail keeps `panels` zero from the entry and selects the page's list with movn. gcse's constant
 * propagation would fold that entry zero into a conditional move formed by the jump pass after
 * cse1 (movz, 2092 bytes), so the selection has to stay a branch until gcse is over:
 *   panels = page->panels; panels = (T)((char *)panels + none);
 * `none` is a set-once zero (allowed by owner ruling, 9 November 2026). The arm is two insns for
 * the first jump pass; cprop turns the add into a no-op, the jump pass before cse2 (the only one
 * that deletes dead sets, jump.c after_regscan) leaves one insn and forms the cmov there.
 * The D_0025A058 arm is empty: its test leaves retail's dead load of D_001AB910.
 * The bounds loop reads the page after the D_001AA450[j] test through a loop-local `st`, which
 * gives retail's beqz slot and preheader order.
 */
#include "common.h"

typedef struct PanelCBC58 PanelCBC58;
struct PanelCBC58 {
    int unused;
    int (*draw)(PanelCBC58 *);
    int pad8[2];
    int flags, pad14;
    int x, y, width, height;
};
typedef struct { int x, y, width, height; } RectCBC58;
typedef struct { RectCBC58 bounds[14]; char padE0[12]; PanelCBC58 *panels[14]; } PageCBC58;
typedef struct {
    int mode, active;
    char pad8[12];
    PageCBC58 *page;
    char pad18[8];
    void *buffer;
    char pad24[0x144];
    int field168, field16C;
    char pad170[0x50];
    float fade, step, target;
} StateCBC58;
extern StateCBC58 g_pause_menu_state;
extern int g_screen_height, D_001A72DC;
extern int D_001AB91C __attribute__((sda));
extern volatile int D_001AB910 __attribute__((sda));
extern int D_001AA450[14] SDATA(D_001AA450);
extern int D_001AA43C __attribute__((sda));
extern int D_001AB92C __attribute__((sda));
extern int D_001AB930 __attribute__((sda));
extern long D_001A7470 __attribute__((sda));
extern char D_00259018[], D_0025A738[], D_0025A498[], D_0025A190[], D_0025A058[];
extern PanelCBC58 D_00259EE0;
extern char D_001AB920[], D_001AB928[];
typedef struct { char pad[0x1A0]; int flags; char pad1A4[0x20]; int pressed; } PadCBC58;
extern PadCBC58 g_pad_state;
extern void (*D_00210AD0)(void) __attribute__((nosda));
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_upload_image_to_gs_packets(void *, int, int);
extern void gfx_write_clear_color_packets(void);
extern void gfx_set_clear_color_packet(int,int,int,int);
extern void SetupGifPaging(int), DoGifPaging(void);
extern void hud_update_record_handlers(void), level_run_callbacks_and_draw(void), func_0029C2D0(void), func_0029C340(void);
extern void VU1_addGSregister(int, long);
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void STUB_printf(void *);
extern int menu_set_clip_rect(PanelCBC58 *), menu_fading_image_draw(PanelCBC58 *);
extern int menu_text_list_draw_checkboxes(PanelCBC58 *), menu_panel_draw(PanelCBC58 *);
extern void gfx_setup_screen_copy_draw_state(int,int,int,float);
extern void gfx_draw_screen_rect_with_depth(int,int,int,int,long,int,int);
extern void gfx_run_screen_effect_setup(void);
extern void DrawTexturedQuad(int,int,int,int,int,int,int,int,long,long);
extern void mem_restore_scratch_area(void),PatchMobyGifs(void);
extern int tex_run_upload_and_setup(void);
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern int FloatToInt(float);

/* Draws all the panels of the pause menu and fades the screen. */
void menu_draw_pause_panels(int mode)
{
    PanelCBC58 **panels = 0;
    int none = 0;
    StateCBC58 *state = &g_pause_menu_state;
    int pass, i, j, x, y, w, h, lw, lh, result;
    int left, top, right, bottom, tw, th;
    float delta;
    gfx_append_draw_list_buffer_tag(0);
    gfx_upload_image_to_gs_packets(state->buffer, D_001A72DC, g_screen_height << 11);
    if (!mode) {
    gfx_write_clear_color_packets();
    gfx_set_clear_color_packet(0,0,0,0x38);
    if (g_pause_menu_state.mode == 4 && state->active) {
    if (D_001AB91C) {
        void *page = state->page;
        if (page == D_00259018) {
            SetupGifPaging(0); D_00210AD0(); DoGifPaging(); return;
        }
        if (page == D_0025A738) {
            SetupGifPaging(0); hud_update_record_handlers(); level_run_callbacks_and_draw(); DoGifPaging(); return;
        }
        if (page == D_0025A498 && !D_001AB910) {
            SetupGifPaging(0); func_0029C2D0(); DoGifPaging();
        } else if (g_pause_menu_state.page == (void *)D_0025A190 && !D_001AB910) {
            SetupGifPaging(0); func_0029C340(); DoGifPaging(); return;
        } else if (g_pause_menu_state.page == (void *)D_0025A058 && !D_001AB910) {
            ;
        }
    }
    VU1_addGSregister(0x47,0x5360B);
    if (g_pause_menu_state.field168) {
        DrawMobysSetup(); mem_fill_scratch_area(); mem_save_scratch_area();
    }
    if (g_pause_menu_state.page) {
        panels = g_pause_menu_state.page->panels;
        panels = (PanelCBC58 **)((char *)panels + none);
    }
    if ((g_pad_state.flags&15)==15 && (g_pad_state.pressed&15))
        STUB_printf(D_001AB920);
    for (j=0;j<14;j++) {
        StateCBC58 *st = &g_pause_menu_state;
        if (D_001AA450[j]) {
            PageCBC58 *pg = st->page;
            if (panels && panels[j]) {
                panels[j]->x = pg->bounds[j].x - pg->bounds[j].width/2;
                panels[j]->y = st->page->bounds[j].y - st->page->bounds[j].height/2;
                panels[j]->width = st->page->bounds[j].width;
                panels[j]->height = st->page->bounds[j].height;
                if (panels[j] == &D_00259EE0) panels[j]->height=256;
            }
        }
    }
    if ((g_pad_state.flags&15)==15 && (g_pad_state.pressed&15))
        STUB_printf(D_001AB928);
    for (pass=0;pass<2;pass++) {
        for (i=0;i<14;i++) {
            PanelCBC58 *p;
            if (!panels || !(p=panels[i]) || (p->flags&4) || !D_001AA450[i] || !p->draw) continue;
            if (!pass && !(p->flags&2)) continue;
            if (pass==1 && (p->flags&2)) continue;
            if (p->flags&1) { p->draw(p); continue; }
            x=p->x; y=p->y; w=p->width; h=p->height;
            lw=7; while ((1<<lw)<w) lw++;
            lh=7; while ((1<<lh)<h) lh++;
            while (lw+lh>=18) lh--;
            if ((panels[i]->draw == menu_set_clip_rect || panels[i]->draw == menu_fading_image_draw ||
                 panels[i]->draw == menu_text_list_draw_checkboxes || panels[i]->draw == menu_panel_draw) && !(panels[i]->flags&8)) {
                gfx_setup_screen_copy_draw_state(lw,lh,0,1.0f);
                gfx_draw_screen_rect_with_depth(0,0,1<<lw,1<<lh,D_001AA43C,0,0);
                result=panels[i]->draw(panels[i]);
                gfx_run_screen_effect_setup();
            } else result=panels[i]->draw(panels[i]);
            VU1_addGSregister(0x42,0x8000000064L);
            VU1_addGSregister(0x47,0x43);
            if (result&1) continue;
            tw=1<<lw; th=1<<lh; left=0; right=tw; top=0; bottom=th;
            if (result&2) { right=w; bottom=h; }
            else if (result&8) {
                left=(right-w)/2;
                right-=left;
                left=left > -1 ? left : 0;
                top=(bottom-h)/2;
                bottom-=top;
                top=top > -1 ? top : 0;
                if (tw<right) right=tw;
                if (th<bottom) bottom=th;
            } else if (result&4) {
                if (w<h) { left=right/2-w*right/(h*2); right-=left; }
                else { top=bottom/2-h*bottom/(w*2); bottom-=top; }
            } else if (!(result&16)) continue;
            if (D_001AB92C)
                DrawTexturedQuad(x,y,w,h,left,top,right-left,bottom-top,0x80808080L,D_001A7470);
        }
        if (D_001AB930 && !pass && g_pause_menu_state.field168) {
            mem_restore_scratch_area(); tex_run_upload_and_setup(); gfx_wait_for_dma_status_bits(16); PatchMobyGifs();
            g_pause_menu_state.field168=0; g_pause_menu_state.field16C=0;
        }
    }
    gfx_write_clear_color_packets();
    if (g_pause_menu_state.fade != g_pause_menu_state.target) {
        delta=g_pause_menu_state.target-g_pause_menu_state.fade;
        if (delta>g_pause_menu_state.step) delta=g_pause_menu_state.step;
        else if (delta < -g_pause_menu_state.step) delta=-g_pause_menu_state.step;
        g_pause_menu_state.fade+=delta;
    }
    if (g_pause_menu_state.fade != 0.0f)
        gfx_set_clear_color_packet(0,0,0,FloatToInt(g_pause_menu_state.fade*128.0f));
    VU1_addGSregister(0x42,0x8000000044L);
    VU1_addGSregister(0x47,0x5360B);
    }
    }
}
