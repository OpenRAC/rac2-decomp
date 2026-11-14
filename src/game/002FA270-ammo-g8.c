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
extern int func_00288FB8(int);
extern int func_0027F288(char *,int,float);
static __inline__ int screen_y(int y) { int result = (int)((float)y * D_001B2280[0] + 0.5f); if (D_001A7B90) result += 4; return result; }
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
    func_0028EA58(tex, x, screen_y(y), size, (int)((float)size * D_001B2280[0] + 0.5f), colors);
}

void func_002FA270(void)
{
    int pulse, x;
    int left, b;
    int i, index, y, icon, overlay, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    char *text;
    double distance;
    func_002FC620(D_001AD390,D_001AD394,(int)((float)D_001AD398 * D_001B2280[0]+0.5f),screen_y(D_001AD39C));
    if (D_0021F240.scroll < 0) D_0021F240.scroll += 4;
    else if (D_0021F240.scroll > 0) D_0021F240.scroll -= 4;
    i = -5;
    left = 233;
    b = 4;
    pulse = ((func_00282C30(((D_0021F240.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    func_00285548(left-(D_001AD3A0+b),screen_y(325-D_001AD3A4),D_001AD3A8+285,screen_y(D_001AD3AC+381),D_001A7340,D_001A7344,
        pulse);
    b = 2;
    func_00285548(left-(D_001AD3A0+b),screen_y(327-D_001AD3A4),D_001AD3A8+283,screen_y(D_001AD3AC+379),D_001A7340,D_001A7344,0x80442d00);
    y = D_0021F240.scroll - 47;
    do {
        index = i + D_0021F240.selected;
        if (index >= 0 && index < *(int *)((char *)&D_0021F240+0x740)) {
            icon = func_0028E588(((IconInfo *)((char *)D_00239BA0 + D_00139568[D_0021F240.rows.ammo[index].id] * 224))->icon,0);
            overlay = func_0028E588(0xeaa3,D_0021F240.rows.ammo[index].frame);
            special = 0;
            kind = D_00239BA0[D_00139568[D_0021F240.rows.ammo[index].id]].color;
            switch (D_0021F240.rows.ammo[index].id) {
            case 12: case 14: case 17: case 18: case 53: special = 1; break;
            }
            color = func_00336EF8(special && kind == 1 ? 2 : kind) & 0xffffff;
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
            x = y+(D_001AD3B4+b);
            draw_icon(icon,x+D_001AD3C8,D_001AD3B0+D_001AD3CC,D_001AD3C0,colors);
            draw_icon(overlay,y+(D_001AD3B4+b),D_001AD3B0-D_001AD3B8,D_001AD3B8,colors);
            icon = func_0028E588(0xeaa3,3);
            draw_icon(icon,y+(D_001AD3B4+b),(D_001AD3B0-D_001AD3B8)+D_001AD3BC,D_001AD3B8,colors);
        }
        i++;
        y += 56;
    } while (i < 7);
}
