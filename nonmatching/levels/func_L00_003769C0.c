/* Closer C, 1 November 2026: -O2 -G0 -ffunction-sections -fmove-all-movables, 1212/1216, 43 rows. Retail's search keeps
 * its integer index, so it is a goto loop: loop.c reduces every do/while or for form. Left: retail recomputes the
 * entry address for the colour (addu v0,a1,a0; lw 4(v0)), idx/colour take s2/s3 the other way, i+1/y+56 swapped.
 * Closer C4: cse reuses the key address whichever way the sum is written; table base a1 and j a3 follow from that row.
 */
#include "common.h"
/* sol-high; USA v1.01, -O2 -G0 -ffunction-sections.
 * Best check: 1212/1216 bytes, 0 of 27 places match; no linked match.
 * Postincrement search removes the duplicated first table test, but strength
 * reduction turns it into a pointer walk. The compiler shares idx*28 across
 * row accesses (mult/addu instead of retail's two madd formations), swaps the
 * next-index/next-row saved and stack values, and schedules color stores
 * differently. A useful next experiment must retain the integer table index
 * and independent row-address formation without adding memory effects.
 * Required declarations are included below. Incomplete SDA arrays preserve
 * the measured absolute rematerialization in this G0 unit.
 */
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern int D_001A7340[] __attribute__((sda));
extern int D_001A7344[] __attribute__((sda));
typedef struct { int words[0x744/4]; } Menu705;
extern Menu705 D_L00_0022F7C0[];
typedef struct { int key; unsigned int color; } MenuColor;
extern MenuColor D_L00_0028E9F0[] __attribute__((sda));
typedef struct { int words[7]; } MenuRow;
extern MenuRow D_L00_0022F900[] __attribute__((sda));
extern void func_002FC620(int, int, int, int);
extern int func_00282C30(int);
extern void func_00285548(int,int,int,int,int,int,unsigned int);
extern char *func_0028E588(int,int);
extern void func_0028EA58(char *,int,int,int,int,unsigned int *);
#define MW(o) (D_L00_0022F7C0[0].words[(o)/4])
#define MY(y) ((int)(D_L00_001B25E0[0]*(y)+0.5f)+(D_001A7B90[0]?4:0))
void func_L00_003769C0(void)
{
    int y;
    int bottom, top;
    unsigned int pulse;
    unsigned int color;
    unsigned int colors[4];


    bottom=MY(382.0f);
    top=(int)(D_L00_001B25E0[0]*320.0f+0.5f);
    func_002FC620(58,456,top,bottom);
    if (MW(0x6c)<0) MW(0x6c)+=4;
    else if(MW(0x6c)>0) MW(0x6c)-=4;
    color=0xf0f0b0;
    pulse=(func_00282C30(((MW(4)<<2)&63)-32)+64)*0x10202;
    func_00285548(229,MY(325.0f),285,MY(381.0f),D_001A7340[0],D_001A7344[0],0x80000000|pulse);
    func_00285548(231,MY(327.0f),283,MY(379.0f),D_001A7340[0],D_001A7344[0],0x80442d00);
    y=MW(0x6c)-47;
    { int i;
    for(i=-5;i<7;i++,y+=56) {
        int idx, a,b;
        double d;
        char *text, *row;
        idx=i+MW(0x80);
        if(idx<0 || idx>=MW(0x740)) continue;
        row=(char *)&D_L00_0022F900[idx];
        text=func_0028E588(0xea97,*(int *)row);
        d=256.0f-(float)(y+2);
        if(d<0.0) d=0.0-d;
        a=128-(int)(d*0.75);
        d=256.0f-(float)(y+40);
        if(d<0.0) d=0.0-d;
        b=128-(int)(d*0.75);
        if(a<0) a=0;
        if(b<0) b=0;
        a<<=24; b<<=24;
        if(*(int *)row==0) {
            int j=0;
            char *label;
            int key;
            int off;
        top:
            off=j*8;
            key=((MenuColor *)((char *)D_L00_0028E9F0+off))->key;
            if(key) {
                j++;
                if(*(int *)((char *)D_L00_0022F7C0+0x158+idx*28)!=key) goto top;
                color=((MenuColor *)((char *)D_L00_0028E9F0+off))->color;
            }
            label=func_0028E588(0xea97,1);
            colors[2]=colors[0]=a|color;
            colors[3]=colors[1]=b|color;
            func_0028EA58(label,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
            color=0xf0f0b0;
        }
        colors[2]=colors[0]=a|color;
        colors[3]=colors[1]=b|color;
        func_0028EA58(text,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
    }
    }
}
#undef MW
#undef MY
