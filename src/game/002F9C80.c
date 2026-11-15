#include "common.h"

typedef struct { int id, kind, spare[3], owned; } ItemRow;
typedef struct {
    int state, tick;
    char pad08[0x64];
    int scroll;
    char pad70[0x10];
    int selected;
    char pad84[0xbc];
    ItemRow rows[64];
    int count;
} ListState;
typedef struct { char pad00[4]; unsigned char color; char pad05[0x37]; unsigned short icon; char pad3e[0xa2]; } IconInfo;
extern ListState D_0021F240;
extern unsigned char D_00139568[];
extern IconInfo D_00239BA0[];
extern float D_001B2280[] MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR, D_001A7344 MACRO_ADDR;
extern void func_002FC620(int,int,int,int);
extern int func_00282C30(int);
extern void func_00285548(int,int,int,int,int,int,unsigned int);
extern int func_0028E588(int,int);
extern unsigned int func_00336EF8(int);
extern void func_0028EA58(int,int,int,int,int,unsigned int *);
extern char *func_00288FB8(int);
extern int func_0027F288(char *,int,float);
extern void func_002F97A0(float,float,unsigned long,float,char *,int);

#define screen_y(y) ((int)(D_001B2280[0] * (y) + 0.5f) + (D_001A7B90 ? 4 : 0))

/* Draws the scrolling row of item icons in the vendor menu, with a pulsing frame around the
   selected one and a label under items already owned or for sale. */
void func_002F9C80(void)
{
    int pulse;
    int i, index, y, icon, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    double distance;
    SetGsScissorClamped(58,456,(int)(D_001B2280[0]*320.0f+0.5f),screen_y(382));
    if (gVendorMenuState.scroll < 0) gVendorMenuState.scroll += 4;
    else if (gVendorMenuState.scroll > 0) gVendorMenuState.scroll -= 4;
    i = -5;
    pulse = ((subtract_integer_with_clamp(((gVendorMenuState.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    DrawFramebufferRect(229,screen_y(325),285,screen_y(381),gScreenWidth,gScreenHeight,
        pulse);
    DrawFramebufferRect(231,screen_y(327),283,screen_y(379),gScreenWidth,gScreenHeight,0x80442d00);
    y = gVendorMenuState.scroll - 47;
    do {
        index = i + gVendorMenuState.selected;
        if (index >= 0 && index < gVendorMenuState.count) {
            icon = GetIconFrame((gWeaponTable_00239BA0 + gItemSlotToRecord[gVendorMenuState.rows[index].id])->icon,0);
            if (gVendorMenuState.rows[index].owned) kind = 2;
            else {
                special = 0;
                kind = gWeaponTable_00239BA0[gItemSlotToRecord[gVendorMenuState.rows[index].id]].color;
                switch (gVendorMenuState.rows[index].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1; break;
                }
                kind = special && kind == 1 ? 2 : kind;
            }
            color = GetItemColorEntry(kind) & 0xffffff;
            distance = (double)(256.0f - (float)(y+2));
            if (distance < 0.0) distance = -distance;
            alpha0 = 128 - (int)(distance * 0.75);
            distance = (double)(256.0f - (float)(y+40));
            if (distance < 0.0) distance = -distance;
            alpha1 = 128 - (int)(distance * 0.75);
            alpha0 = alpha0 < 0 ? 0 : alpha0;
            alpha1 = alpha1 < 0 ? 0 : alpha1;
            alpha0 <<= 24;
            alpha1 <<= 24;
            colors[2] = colors[0] = alpha0 | color;
            colors[3] = colors[1] = alpha1 | color;
            DrawHudSpriteGradient(icon,y+4,screen_y(329),40,(int)(D_001B2280[0]*40.0f+0.5f),colors);
            if (gVendorMenuState.rows[index].owned) {
                char *text = GetLocalizedString(0x325f);
                int tx = (MeasureTextWidthSmallFontScaled(text,-1,0.75f) >> 1) - 25;
                draw_large_text_edge_faded((float)(y - tx),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            } else if (gVendorMenuState.rows[index].kind == 1) {
                char *text = GetLocalizedString(0x2dc9);
                int tx = (MeasureTextWidthSmallFontScaled(text,-1,0.75f) >> 1) - 25;
                draw_large_text_edge_faded((float)(y - tx),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            }
        }
        i++;
        y += 56;
    } while (i < 7);
}
