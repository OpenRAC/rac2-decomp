#include "include_asm.h"

/* func_US2_002FAB0C, the v2.00 boot copy of func_002F9C80: the same C, where the bottom y 382
 * becomes 388, the two text ids become 0x30f5 and 0x2c5f, and the text sits one unit further left. */
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
extern int func_L00_002E9210(char *,int,float);
extern void func_US2_002FA630(float,float,unsigned long,float,char *,int);

#define screen_y(y) ((int)(D_001B2280[0] * (y) + 0.5f) + (D_001A7B90 ? 4 : 0))

void func_US2_002FAB0C(void)
{
    int pulse;
    int i, index, y, icon, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    double distance;
    func_002FC620(58,456,(int)(D_001B2280[0]*320.0f+0.5f),screen_y(388));
    if (D_0021F240.scroll < 0) D_0021F240.scroll += 4;
    else if (D_0021F240.scroll > 0) D_0021F240.scroll -= 4;
    i = -5;
    pulse = ((func_00282C30(((D_0021F240.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    func_00285548(229,screen_y(325),285,screen_y(381),D_001A7340,D_001A7344,
        pulse);
    func_00285548(231,screen_y(327),283,screen_y(379),D_001A7340,D_001A7344,0x80442d00);
    y = D_0021F240.scroll - 47;
    do {
        index = i + D_0021F240.selected;
        if (index >= 0 && index < D_0021F240.count) {
            icon = func_0028E588((D_00239BA0 + D_00139568[D_0021F240.rows[index].id])->icon,0);
            if (D_0021F240.rows[index].owned) kind = 2;
            else {
                special = 0;
                kind = D_00239BA0[D_00139568[D_0021F240.rows[index].id]].color;
                switch (D_0021F240.rows[index].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1; break;
                }
                kind = special && kind == 1 ? 2 : kind;
            }
            color = func_00336EF8(kind) & 0xffffff;
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
            func_0028EA58(icon,y+4,screen_y(329),40,(int)(D_001B2280[0]*40.0f+0.5f),colors);
            if (D_0021F240.rows[index].owned) {
                char *text = func_00288FB8(0x30f5);
                int tx = (func_L00_002E9210(text,-1,0.75f) >> 1) - 25;
                func_US2_002FA630((float)(y - tx - 1),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            } else if (D_0021F240.rows[index].kind == 1) {
                char *text = func_00288FB8(0x2c5f);
                int tx = (func_L00_002E9210(text,-1,0.75f) >> 1) - 25;
                func_US2_002FA630((float)(y - tx - 1),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            }
        }
        i++;
        y += 56;
    } while (i < 7);
}
