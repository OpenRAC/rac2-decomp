#include "names.h"
/* func_US2_0028DC24 (2,584 bytes): USA v2.00 release of the radial weapon-select panel
 * (v1.01 func_0028D1E8). Like PAL, it draws the panel at fixed coordinates and passes the
 * vertical scale to func_00300A00 instead of scaling each Y position. Own unit:
 * -O2 -G8 -ffunction-sections -frac2-loop-align-in-loop-only (config/cflags.txt).
 */
#include "common.h"

typedef struct { int xy[8][2]; } RadialPositions;
typedef struct { int ids[8]; } RadialLabels;
typedef struct { int icon, frame; int rest[5]; } RadialItem;
extern RadialPositions D_001A8E30;
extern RadialLabels D_001A8E70;
extern short D_001B189C[] __attribute__((sda));
extern int g_radial_slot_count;
extern RadialItem **g_radial_menu_pages;
extern int g_radial_menu_page_index __attribute__((sda));
extern char *D_001A8CFC;
extern float D_001B23A8;
extern float IntToFloat(int);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int table_find_by_id(char *,int);
extern void gfx_draw_scaled_object_two_axes(char *,int,float,float,float,float,float);
extern int math_ping_pong_blend_values(int,int,int,int,int);
extern void AppendScreenRectPacket(int,int,int,int,unsigned long,int);
extern int GetIconFrame(int,int);
extern void hud_draw_sprite_gradient(int,int,int,int,int,int *);
extern int GetLocalizedString(int);
extern int func_001157AC(char *);
extern int FastTweenColor(int,int,float);
extern int text_draw_centered_small(int,int,u64,char *,int);

static __inline__ void draw_background(char *tex, int color, float sx, float rot)
{
    gfx_draw_scaled_object_two_axes(tex, color, 129.0f, 208.0f, sx, D_001B23A8, rot);
}

int func_US2_0028DC24(unsigned char *o)
{
    int total = D_001B189C[2] + D_001B189C[4] + D_001B189C[3];
    RadialPositions positions = D_001A8E30;
    int colors[4], colors2[4];
    float open, text, angle, zero;
    char *tex;
    int sel;
    char *label;
    int i, selectedAvailable, x, y, frame, available, color, previous;
    unsigned char *fade = o + 0x70;
    open = IntToFloat(o[0x70]) / IntToFloat(8);
    if (open > 1.0f) open = 1.0f;
    else if (open < 0.0f) open = 0.0f;
    text = IntToFloat(fade[1]) / IntToFloat(8);
    if (text > 1.0f) text = 1.0f;
    else if (text < 0.0f) text = 0.0f;
    /* FAKEMATCH: do { } while (0) group; its loop notes make the read after the last draw a
     * scheduling barrier, so the last draw loads $f12 before $a1 as retail (v1.01 has the same group) */
    do {
        zero = 0.0f;
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 8);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 9);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 10);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 11);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 12);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 13);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 14);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 15);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 7);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 7);
        draw_background(tex, 0x60442D00, -1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 134);
        draw_background(tex, 0x55F0C070, 1.0f, zero);
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 134);
        draw_background(tex, 0x55F0C070, -1.0f, zero);
    } while (0);
    if (*(int *)(o+0x74) >= 0) {
        colors[0] = math_ping_pong_blend_values(0x80442D00,0x80FFDE8D,25,0,0);
        previous = *(int *)(o+0x74)-1;
        if (previous < 0) previous = 7;
        tex = (char *)table_find_by_id(D_001A8CFC + 0x8710, 16);
        draw_background(tex, colors[0], 1.0f, (float)previous);
        {
            int k = *(int *)(o+0x74);
            AppendScreenRectPacket(positions.xy[k][0], positions.xy[k][1],
                positions.xy[k][0]+33, positions.xy[k][1]+7, colors[0], 0);
        }
    }
    selectedAvailable = 0;
    for (i=0;i<g_radial_slot_count;i++) {
        angle = FastAddRotations((float)i * 2.0f * 3.1415927f / (float)g_radial_slot_count - 3.1415927f,1.5707964f);
        x = (int)(math_fast_sin_or_cos_a(angle)*80.0f)+114;
        y = (int)(math_fast_sin_or_cos_b(angle)*75.0f)+192;
        if (!g_radial_menu_pages[g_radial_menu_page_index][i].icon) continue;
        frame = g_radial_menu_pages[g_radial_menu_page_index][i].frame;
        previous = 0;
        if (frame == 6 && !D_001B189C[1]) frame = 7;
        available = 0;
        switch (frame) {
        case 2:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6000FF00;
                available=1; previous=1;
            }
            break;
        case 3:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6029A1FF;
                previous=1; available=1;
            }
            break;
        case 0:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x600000FF;
                previous=1; available=1;
            }
            break;
        case 1:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x60FF0000;
                previous=1; available=1;
            }
            break;
        case 6: case 7:
            if (D_001B189C[2]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 4:
            if (D_001B189C[3]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 8:
            if (D_001B189C[4]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 9:
            if (D_001B189C[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        }
        if (previous) hud_draw_sprite_gradient(GetIconFrame(g_radial_menu_pages[g_radial_menu_page_index][i].icon,10),x+2,y+2,28,26,colors);
        if (available) {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x80FFDE8D;
        } else {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x40808080;
        }
        hud_draw_sprite_gradient(GetIconFrame(g_radial_menu_pages[g_radial_menu_page_index][i].icon,frame),x,y,30,28,colors2);
    }
    sel = *(int *)(o+0x74);
    if (selectedAvailable && sel>=0 && sel<8) {
        RadialLabels labels=D_001A8E70;
        int id=labels.ids[sel];
        if (id==0x2DCA && D_001B189C[1]) id=0x2DCB;
        label=(char *)GetLocalizedString(id);
        if (label && func_001157AC(label)) {
            float alpha = text * open;
            color=FastTweenColor(0x00E0C0A0,0x80E0C0A0,alpha);
            previous=FastTweenColor(0,0x80000000,alpha);
            text_draw_centered_small(128,200,previous,label,-1);
            text_draw_centered_small(129,201,color,label,-1);
        }
    }
    return *(int *)(o+0x58);
}
