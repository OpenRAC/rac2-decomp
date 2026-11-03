/* sol-high, task v1165: retained C attempt, USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections (002F9BC0-ammo-g8.c).
 * Best: 1536 bytes versus 1552 retail, 0 of 28 places match.
 * Recompiled the orch/main draft on the pinned worker compiler; its former
 * -frac2-no-reduce-tree-depth option is unavailable and was not used.
 * Operand order (float)coordinate * scale reproduces the opening FP sequence.
 * Passing the special/color conditional directly to func_00336EF8 reproduces
 * retail's beql selection, whereas assigning kind first produces movz.
 * Remaining: 233-(padding+4/2) folds into 229/231-padding; x+(padding+2)
 * associates with x+2, keeping it live across the fade and drawing calls.
 * Retail instead keeps 233 in s0, x in s6, icon in s7 and overlay in fp;
 * this draft keeps x in s7, icon in fp and spills overlay to sp+0x14.
 * Scheduling, later FP allocation, clamp order and corner stores also differ.
 * Inline, statement-expression and conditional scaling forms did not close
 * the gap; unsigned grouping gave identical output to the signed form.
 * -fno-expensive-optimizations: 1516 bytes, 0/28; -fno-gcse: 1536, 0/28.
 * Eleven checker calls and one regalloc diagnostic; no linked build run.
 * Next: independently evidenced UI expression/type structure that preserves
 * the coordinate grouping without barriers or invented memory accesses.
 * All required declarations follow; switch IDs are from retail's jump table.
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
extern int func_0028EA58(int,int,int,int,int,unsigned int *);
extern char *func_00288FB8(int);
extern int func_0027F288(char *,int,float);
extern void func_002F97A0(float,float,unsigned long,float,char *,int);
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
extern int D_001AD3C0 __attribute__((sda));
extern int D_001AD3C4 __attribute__((sda));
extern int D_001AD3C8 __attribute__((sda));
extern int D_001AD3D0 __attribute__((sda));
extern int D_001AD3D8 __attribute__((sda));
extern int D_001AD3BC __attribute__((sda));
void func_002FA270(void)
{
    int pulse;
    int i, index, y, icon, overlay, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    char *text;
    double distance;
    func_002FC620(D_001AD390,D_001AD394,(int)((float)D_001AD398 * D_001B2280[0]+0.5f),screen_y(D_001AD39C));
    if (D_0021F240.scroll < 0) D_0021F240.scroll += 4;
    else if (D_0021F240.scroll > 0) D_0021F240.scroll -= 4;
    i = -5;
    pulse = ((func_00282C30(((D_0021F240.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    func_00285548(233-(D_001AD3A0+4),screen_y(325-D_001AD3A4),D_001AD3A8+285,screen_y(D_001AD3AC+381),D_001A7340,D_001A7344,
        pulse);
    func_00285548(233-(D_001AD3A0+2),screen_y(327-D_001AD3A4),D_001AD3A8+283,screen_y(D_001AD3AC+379),D_001A7340,D_001A7344,0x80442d00);
    y = D_0021F240.scroll - 47;
    do {
        index = i + D_0021F240.selected;
        if (index >= 0 && index < *(int *)((char *)&D_0021F240+0x740)) {
            icon = func_0028E588(D_00239BA0[D_00139568[D_0021F240.rows.ammo[index].id]].icon,0);
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
            if (alpha1 < 0) alpha1 = 0;
            if (alpha0 < 0) alpha0 = 0;
            colors[3] = colors[1] = (alpha1<<24)|color;
            colors[2] = colors[0] = (alpha0<<24)|color;
            func_0028EA58(icon,y+(D_001AD3C4+2)+D_001AD3D8,screen_y(D_001AD3C0+D_001AD3CC),D_001AD3D0,(int)((float)D_001AD3C0 * D_001B2280[0]+0.5f),colors);
            func_0028EA58(overlay,y+(D_001AD3C4+2),screen_y(D_001AD3C0-D_001AD3C8),D_001AD3C8,(int)((float)D_001AD3C8 * D_001B2280[0]+0.5f),colors);
            icon = func_0028E588(0xeaa3,3);
            func_0028EA58(icon,y+(D_001AD3C4+2),screen_y((D_001AD3C0-D_001AD3C8)+D_001AD3BC),D_001AD3C8,(int)((float)D_001AD3C8 * D_001B2280[0]+0.5f),colors);
        }
        i++;
        y += 56;
    } while (i < 7);
}
