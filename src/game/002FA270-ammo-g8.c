#include "names.h"
/* func_002FA270 (1,552 bytes, 28 places): draws the ammo and item list rows of the vendor
 * menu, the icon with its overlay and the count text. -G8 sibling of 002F9BC0.c.
 * Own unit: -O2 -G8 -ffunction-sections -frac2-fix-scratch-reuse (config/cflags.txt).
 * - The first D_00239BA0 lookup is (IconInfo *)((char *)D_00239BA0 + idx * 224): addu v0,v0,s2.
 * - alpha1 <<= 24; alpha0 <<= 24; before the colour stores, as retail's in-place sll.
 * - x = y + (D_001AD3B4 + b) as a temp for the first call gives retail's grouping.
 * - The icon height h is rounded by a fix_truncsfsi2 right after the y rounding. Its integer
 *   scratch is never emitted on the R5900, but the register reload names for it decides which
 *   loads sched2 may lift above it. Retail's order is the one obtained when the second of two
 *   consecutive truncations reuses the first one's scratch: -frac2-fix-scratch-reuse
 *   (docs/build/compiler-notes.md; it changes no other USA v1.01 function). Allowed by owner
 *   ruling, 12 November 2026.
 * The small-data names follow retail's $gp (0x1AEFF0): D_001AD3B0..D_001AD3C8.
 */
#include "common.h"
typedef struct { int id, kind, spare[3], locked; } ItemRow;
typedef struct { int frame, id, spare[2]; } AmmoRow;
typedef struct {
    int state, tick;
    char pad08[0x64];
    int scroll;
    char pad70[0x10];
    int selected;
    char pad84[0xbc];
    union { ItemRow item[64]; AmmoRow ammo[96]; } rows;
} ListState;
typedef struct { char pad00[4]; unsigned char color; char pad05[0x37]; unsigned short icon; char pad3e[0xa2]; } IconInfo;
extern ListState g_vendor_menu_state;
extern unsigned char g_item_slot_to_record[];
extern IconInfo g_weapon_table[];
extern float D_001B2280[] MACRO_ADDR;
extern int g_is_pal_video MACRO_ADDR;
extern int g_screen_width MACRO_ADDR, g_screen_height MACRO_ADDR;
extern void gfx_set_scissor_clamped(int,int,int,int);
extern int subtract_integer_with_clamp(int);
extern void DrawFramebufferRect(int,int,int,int,int,int,unsigned int);
extern int GetIconFrame(int,int);
extern unsigned int ui_get_item_color(int);
extern void hud_draw_sprite_gradient(int,int,int,int,int,unsigned int *);
extern char *GetLocalizedString(int);
extern int text_measure_width_small_scaled(char *,int,float);
static __inline__ int screen_y(int y) { int result = (int)((float)y * D_001B2280[0] + 0.5f); if (g_is_pal_video) result += 4; return result; }
extern int D_001AD39C MACRO_ADDR;
extern int D_001AD394 MACRO_ADDR;
extern int D_001AD3A4 MACRO_ADDR;
extern int D_001AD3AC MACRO_ADDR;
extern int D_001AD3A8 MACRO_ADDR;
extern int D_001AD3CC MACRO_ADDR;
extern int D_001AD398 __attribute__((sda));
extern int D_001AD390 __attribute__((sda));
extern int D_001AD3A0 __attribute__((sda));
extern int D_001AD3B0 __attribute__((sda));
extern int D_001AD3B4 __attribute__((sda));
extern int D_001AD3B8 __attribute__((sda));
extern int D_001AD3C0 __attribute__((sda));
extern int D_001AD3C8 __attribute__((sda));
extern int D_001AD3BC __attribute__((sda));
static __inline__ void draw_icon(int tex, int x, int y, int size, unsigned int *colors)
{
    hud_draw_sprite_gradient(tex, x, screen_y(y), size, (int)((float)size * D_001B2280[0] + 0.5f), colors);
}

/* Draws the scrolling row of ammo icons in the vendor menu, each with its overlay pictures and
   a pulsing frame around the selected one. */
void DrawAmmoSelectList(void)
{
    int pulse, x;
    int frame_left, inset;
    int i, index, y, icon, overlay, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    char *text;
    double distance;
    gfx_set_scissor_clamped(D_001AD390,D_001AD394,(int)((float)D_001AD398 * D_001B2280[0]+0.5f),screen_y(D_001AD39C));
    if (g_vendor_menu_state.scroll < 0) g_vendor_menu_state.scroll += 4;
    else if (g_vendor_menu_state.scroll > 0) g_vendor_menu_state.scroll -= 4;
    i = -5;
    frame_left = 233;
    inset = 4;
    pulse = ((subtract_integer_with_clamp(((g_vendor_menu_state.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    DrawFramebufferRect(frame_left-(D_001AD3A0+inset),screen_y(325-D_001AD3A4),D_001AD3A8+285,screen_y(D_001AD3AC+381),g_screen_width,g_screen_height,
        pulse);
    inset = 2;
    DrawFramebufferRect(frame_left-(D_001AD3A0+inset),screen_y(327-D_001AD3A4),D_001AD3A8+283,screen_y(D_001AD3AC+379),g_screen_width,g_screen_height,0x80442d00);
    y = g_vendor_menu_state.scroll - 47;
    do {
        index = i + g_vendor_menu_state.selected;
        if (index >= 0 && index < *(int *)((char *)&g_vendor_menu_state+0x740)) {
            icon = GetIconFrame(((IconInfo *)((char *)g_weapon_table + g_item_slot_to_record[g_vendor_menu_state.rows.ammo[index].id] * 224))->icon,0);
            overlay = GetIconFrame(0xeaa3,g_vendor_menu_state.rows.ammo[index].frame);
            special = 0;
            kind = g_weapon_table[g_item_slot_to_record[g_vendor_menu_state.rows.ammo[index].id]].color;
            switch (g_vendor_menu_state.rows.ammo[index].id) {
            case 12: case 14: case 17: case 18: case 53: special = 1; break;
            }
            color = ui_get_item_color(special && kind == 1 ? 2 : kind) & 0xffffff;
            distance = (double)(256.0f - (float)(y+2));
            if (distance < 0.0) distance = -distance;
            alpha0 = 128 - (int)(distance * 0.75);
            distance = (double)(256.0f - (float)(y+40));
            if (distance < 0.0) distance = -distance;
            alpha1 = 128 - (int)(distance * 0.75);
            if (alpha0 < 0) alpha0 = 0;
            if (alpha1 < 0) alpha1 = 0;
            alpha1 <<= 24;
            alpha0 <<= 24;
            colors[3] = colors[1] = alpha1|color;
            colors[2] = colors[0] = alpha0|color;
            x = y+(D_001AD3B4+inset);
            draw_icon(icon,x+D_001AD3C8,D_001AD3B0+D_001AD3CC,D_001AD3C0,colors);
            draw_icon(overlay,y+(D_001AD3B4+inset),D_001AD3B0-D_001AD3B8,D_001AD3B8,colors);
            icon = GetIconFrame(0xeaa3,3);
            draw_icon(icon,y+(D_001AD3B4+inset),(D_001AD3B0-D_001AD3B8)+D_001AD3BC,D_001AD3B8,colors);
        }
        i++;
        y += 56;
    } while (i < 7);
}
