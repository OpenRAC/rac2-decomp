/* func_PAL_002CCAC8 (2,100 bytes, 28 places): PAL copy of func_002CBC58.
 * Draws the pause-menu panels. -G8 sibling of 002CC7B8.c.
 */
#include "common.h"

typedef struct PanelCCAC8 PanelCCAC8;
struct PanelCCAC8 {
    int unused;
    int (*draw)(PanelCCAC8 *);
    int pad8[2];
    int flags, pad14;
    int x, y, width, height;
};
typedef struct { int x, y, width, height; } RectCCAC8;
typedef struct { RectCCAC8 bounds[14]; char padE0[12]; PanelCCAC8 *panels[14]; } PageCCAC8;
typedef struct {
    int mode, active;
    char pad8[12];
    PageCCAC8 *page;
    char pad18[8];
    void *buffer;
    char pad24[0x144];
    int field168, field16C;
    char pad170[0x50];
    float fade, step, target;
} StateCCAC8;
extern StateCCAC8 g_pause_menu_state;
extern int g_screen_height, D_001A72DC;
extern int D_001AB91C __attribute__((sda));
extern volatile int D_001AB910 __attribute__((sda));
extern int D_001AA450[14] SDATA(D_001AA450);
extern int D_001AA43C __attribute__((sda));
extern int D_001AB92C __attribute__((sda));
extern int D_001AB930 __attribute__((sda));
extern long D_001A7470 __attribute__((sda));
extern char D_00269018[], D_0026A738[], D_0026A498[], D_0026A190[], D_0026A058[];
extern PanelCCAC8 D_00269EE0;
extern char D_001AB920[], D_001AB928[];
typedef struct { char pad[0x1A0]; int flags; char pad1A4[0x20]; int pressed; } PadCCAC8;
extern PadCCAC8 D_00148200;
extern void (*D_00210B00)(void) __attribute__((nosda));
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_upload_image_to_gs_packets(void *, int, int);
extern void gfx_write_clear_color_packets(void);
extern void gfx_set_clear_color_packet(int,int,int,int);
extern void SetupGifPaging(int), DoGifPaging(void);
extern void func_PAL_0028ECD8(void), func_PAL_0029C8A0(void), func_PAL_0029CC68(void), func_PAL_0029CCD8(void);
extern void VU1_addGSregister(int, long);
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void STUB_printf(void *);
extern int menu_set_clip_rect(PanelCCAC8 *), menu_fading_image_draw(PanelCCAC8 *);
extern int func_PAL_002D9108(PanelCCAC8 *), func_PAL_002DB6C8(PanelCCAC8 *);
extern void gfx_setup_screen_copy_draw_state(int,int,int,float);
extern void gfx_draw_screen_rect_with_depth(int,int,int,int,long,int,int);
extern void func_PAL_00280EC8(void);
extern void DrawTexturedQuad(int,int,int,int,int,int,int,int,long,long);
extern void mem_restore_scratch_area(void),PatchMobyGifs(void);
extern int tex_run_upload_and_setup(void);
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern int FloatToInt(float);

void func_PAL_002CCAC8(int mode)
{
    PanelCCAC8 **panels = 0;
    int none = 0;
    StateCCAC8 *state = &g_pause_menu_state;
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
        if (page == D_00269018) {
            SetupGifPaging(0); D_00210B00(); DoGifPaging(); return;
        }
        if (page == D_0026A738) {
            SetupGifPaging(0); func_PAL_0028ECD8(); func_PAL_0029C8A0(); DoGifPaging(); return;
        }
        if (page == D_0026A498 && !D_001AB910) {
            SetupGifPaging(0); func_PAL_0029CC68(); DoGifPaging();
        } else if (g_pause_menu_state.page == (void *)D_0026A190 && !D_001AB910) {
            SetupGifPaging(0); func_PAL_0029CCD8(); DoGifPaging(); return;
        } else if (g_pause_menu_state.page == (void *)D_0026A058 && !D_001AB910) {
            ;
        }
    }
    VU1_addGSregister(0x47,0x5360B);
    if (g_pause_menu_state.field168) {
        DrawMobysSetup(); mem_fill_scratch_area(); mem_save_scratch_area();
    }
    if (g_pause_menu_state.page) {
        panels = g_pause_menu_state.page->panels;
        panels = (PanelCCAC8 **)((char *)panels + none);
    }
    if ((D_00148200.flags&15)==15 && (D_00148200.pressed&15))
        STUB_printf(D_001AB920);
    for (j=0;j<14;j++) {
        StateCCAC8 *st = &g_pause_menu_state;
        if (D_001AA450[j]) {
            PageCCAC8 *pg = st->page;
            if (panels && panels[j]) {
                panels[j]->x = pg->bounds[j].x - pg->bounds[j].width/2;
                panels[j]->y = st->page->bounds[j].y - st->page->bounds[j].height/2;
                panels[j]->width = st->page->bounds[j].width;
                panels[j]->height = st->page->bounds[j].height;
                if (panels[j] == &D_00269EE0) panels[j]->height=256;
            }
        }
    }
    if ((D_00148200.flags&15)==15 && (D_00148200.pressed&15))
        STUB_printf(D_001AB928);
    for (pass=0;pass<2;pass++) {
        for (i=0;i<14;i++) {
            PanelCCAC8 *p;
            if (!panels || !(p=panels[i]) || (p->flags&4) || !D_001AA450[i] || !p->draw) continue;
            if (!pass && !(p->flags&2)) continue;
            if (pass==1 && (p->flags&2)) continue;
            if (p->flags&1) { p->draw(p); continue; }
            x=p->x; y=p->y; w=p->width; h=p->height;
            lw=7; while ((1<<lw)<w) lw++;
            lh=7; while ((1<<lh)<h) lh++;
            while (lw+lh>=18) lh--;
            if ((panels[i]->draw == menu_set_clip_rect || panels[i]->draw == menu_fading_image_draw ||
                 panels[i]->draw == func_PAL_002D9108 || panels[i]->draw == func_PAL_002DB6C8) && !(panels[i]->flags&8)) {
                gfx_setup_screen_copy_draw_state(lw,lh,0,1.0f);
                gfx_draw_screen_rect_with_depth(0,0,1<<lw,1<<lh,D_001AA43C,0,0);
                result=panels[i]->draw(panels[i]);
                func_PAL_00280EC8();
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
