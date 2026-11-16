/* func_US2_002CCC18 (2,100 bytes, 28 places): USA v2.00 copy of func_002CBC58.
 * Draws the pause-menu panels. -G8 sibling of 002CCAA0.c.
 */
#include "common.h"

typedef struct PanelCCC18 PanelCCC18;
struct PanelCCC18 {
    int unused;
    int (*draw)(PanelCCC18 *);
    int pad8[2];
    int flags, pad14;
    int x, y, width, height;
};
typedef struct { int x, y, width, height; } RectCCC18;
typedef struct { RectCCC18 bounds[14]; char padE0[12]; PanelCCC18 *panels[14]; } PageCCC18;
typedef struct {
    int mode, active;
    char pad8[12];
    PageCCC18 *page;
    char pad18[8];
    void *buffer;
    char pad24[0x144];
    int field168, field16C;
    char pad170[0x50];
    float fade, step, target;
} StateCCC18;
extern StateCCC18 g_pause_menu_state;
extern int g_screen_height, g_vram_display_address;
extern int g_pause_debug_flag_a __attribute__((sda));
extern volatile int g_pause_menu_busy_flag __attribute__((sda));
extern int g_pause_panel_enabled_flags[14] SDATA(D_001AA450);
extern int g_menu_panel_fill_color __attribute__((sda));
extern int g_pause_debug_flag_b __attribute__((sda));
extern int g_pause_second_pass_flag __attribute__((sda));
extern long g_quad_texture __attribute__((sda));
extern char g_menu_page_pause[], g_pause_page_d[], g_pause_page_c[], g_pause_page_b[], g_pause_page_a[];
extern PanelCCC18 g_pause_panel;
extern char g_str_pause_debug_a[], g_str_pause_debug_b[];
typedef struct { char pad[0x1A0]; int flags; char pad1A4[0x20]; int pressed; } PadCCC18;
extern PadCCC18 g_pad_state;
extern void (*g_pause_panels_draw_hook)(void) __attribute__((nosda));
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_upload_image_to_gs_packets(void *, int, int);
extern void gfx_write_clear_color_packets(void);
extern void gfx_set_clear_color_packet(int,int,int,int);
extern void SetupGifPaging(int), DoGifPaging(void);
extern void hud_update_record_handlers(void), func_US2_0029CD18(void), func_US2_0029D108(void), func_US2_0029D178(void);
extern void VU1_addGSregister(int, long);
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void STUB_printf(void *);
extern int menu_set_clip_rect(PanelCCC18 *), menu_fading_image_draw(PanelCCC18 *);
extern int func_US2_002D9178(PanelCCC18 *), func_US2_002DB700(PanelCCC18 *);
extern void gfx_setup_screen_copy_draw_state(int,int,int,float);
extern void gfx_draw_screen_rect_with_depth(int,int,int,int,long,int,int);
extern void func_US2_00280FB8(void);
extern void DrawTexturedQuad(int,int,int,int,int,int,int,int,long,long);
extern void mem_restore_scratch_area(void),PatchMobyGifs(void);
extern int tex_run_upload_and_setup(void);
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern int FloatToInt(float);

void menu_draw_pause_panels_us2(int mode)
{
    PanelCCC18 **panels = 0;
    int none = 0;
    StateCCC18 *state = &g_pause_menu_state;
    int pass, i, j, x, y, w, h, lw, lh, result;
    int left, top, right, bottom, tw, th;
    float delta;
    gfx_append_draw_list_buffer_tag(0);
    gfx_upload_image_to_gs_packets(state->buffer, g_vram_display_address, g_screen_height << 11);
    if (!mode) {
    gfx_write_clear_color_packets();
    gfx_set_clear_color_packet(0,0,0,0x38);
    if (g_pause_menu_state.mode == 4 && state->active) {
    if (g_pause_debug_flag_a) {
        void *page = state->page;
        if (page == g_menu_page_pause) {
            SetupGifPaging(0); g_pause_panels_draw_hook(); DoGifPaging(); return;
        }
        if (page == g_pause_page_d) {
            SetupGifPaging(0); hud_update_record_handlers(); func_US2_0029CD18(); DoGifPaging(); return;
        }
        if (page == g_pause_page_c && !g_pause_menu_busy_flag) {
            SetupGifPaging(0); func_US2_0029D108(); DoGifPaging();
        } else if (g_pause_menu_state.page == (void *)g_pause_page_b && !g_pause_menu_busy_flag) {
            SetupGifPaging(0); func_US2_0029D178(); DoGifPaging(); return;
        } else if (g_pause_menu_state.page == (void *)g_pause_page_a && !g_pause_menu_busy_flag) {
            ;
        }
    }
    VU1_addGSregister(0x47,0x5360B);
    if (g_pause_menu_state.field168) {
        DrawMobysSetup(); mem_fill_scratch_area(); mem_save_scratch_area();
    }
    if (g_pause_menu_state.page) {
        panels = g_pause_menu_state.page->panels;
        panels = (PanelCCC18 **)((char *)panels + none);
    }
    if ((g_pad_state.flags&15)==15 && (g_pad_state.pressed&15))
        STUB_printf(g_str_pause_debug_a);
    for (j=0;j<14;j++) {
        StateCCC18 *st = &g_pause_menu_state;
        if (g_pause_panel_enabled_flags[j]) {
            PageCCC18 *pg = st->page;
            if (panels && panels[j]) {
                panels[j]->x = pg->bounds[j].x - pg->bounds[j].width/2;
                panels[j]->y = st->page->bounds[j].y - st->page->bounds[j].height/2;
                panels[j]->width = st->page->bounds[j].width;
                panels[j]->height = st->page->bounds[j].height;
                if (panels[j] == &g_pause_panel) panels[j]->height=256;
            }
        }
    }
    if ((g_pad_state.flags&15)==15 && (g_pad_state.pressed&15))
        STUB_printf(g_str_pause_debug_b);
    for (pass=0;pass<2;pass++) {
        for (i=0;i<14;i++) {
            PanelCCC18 *p;
            if (!panels || !(p=panels[i]) || (p->flags&4) || !g_pause_panel_enabled_flags[i] || !p->draw) continue;
            if (!pass && !(p->flags&2)) continue;
            if (pass==1 && (p->flags&2)) continue;
            if (p->flags&1) { p->draw(p); continue; }
            x=p->x; y=p->y; w=p->width; h=p->height;
            lw=7; while ((1<<lw)<w) lw++;
            lh=7; while ((1<<lh)<h) lh++;
            while (lw+lh>=18) lh--;
            if ((panels[i]->draw == menu_set_clip_rect || panels[i]->draw == menu_fading_image_draw ||
                 panels[i]->draw == func_US2_002D9178 || panels[i]->draw == func_US2_002DB700) && !(panels[i]->flags&8)) {
                gfx_setup_screen_copy_draw_state(lw,lh,0,1.0f);
                gfx_draw_screen_rect_with_depth(0,0,1<<lw,1<<lh,g_menu_panel_fill_color,0,0);
                result=panels[i]->draw(panels[i]);
                func_US2_00280FB8();
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
            if (g_pause_debug_flag_b)
                DrawTexturedQuad(x,y,w,h,left,top,right-left,bottom-top,0x80808080L,g_quad_texture);
        }
        if (g_pause_second_pass_flag && !pass && g_pause_menu_state.field168) {
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
