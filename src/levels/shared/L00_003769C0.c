#include "common.h"

/* func_L00_003769C0: vendor list rows with a colour search. Own unit, default
 * -O2 -G0 -ffunction-sections. The search's do/while(0) group starts with the
 * real `one` argument of the label call, so `top` sits inside the loop notes
 * while `j = 0` stays outside the group (its refs then tie with `wanted`, and
 * the lower pseudo `wanted` takes $a2 as in retail). Incomplete SDA arrays keep
 * the absolute rematerialisation in this G0 unit.
 */
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern int D_001A7340[] __attribute__((sda));
extern int D_001A7344[] __attribute__((sda));
typedef struct { int words[0x744/4]; } Menu705;
extern Menu705 D_L00_0022F7C0[];
typedef struct { int key; unsigned int color; } MenuColor;
extern MenuColor D_L00_0028E9F0[];
extern void func_002FC620(int, int, int, int);
extern int func_00282C30(int);
extern void func_00285548(int,int,int,int,int,int,unsigned int);
extern char *func_0028E588(int,int);
extern int func_0028EA58(char *,int,int,int,int,unsigned int *);
#define MW(o) (D_L00_0022F7C0[0].words[(o)/4])
#define MY(y) ((int)(D_L00_001B25E0[0]*(y)+0.5f)+(D_001A7B90[0]?4:0))
static __inline__ int fade(int v)
{
    double d=256.0f-(float)v;
    if(d<0.0) d=0.0-d;
    return 128-(int)(d*0.75);
}
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
        row=(char *)D_L00_0022F7C0+0x140+idx*28;
        text=func_0028E588(0xea97,*(int *)row);
        a=fade(y+2);
        b=fade(y+40);
        if(a<0) a=0;
        if(b<0) b=0;
        a<<=24; b<<=24;
        if(*(int *)row==0) {
            char *label;
            int key;
            int off;
            int *wanted;    /* declared before j: equal priorities go to the lower pseudo */
            int j;
            int one;

            j=0;
            do {
            one=1;
        top:
                off=j*8;
                key=*(int *)((char *)D_L00_0028E9F0+off);
                if(key) {
                    j++;
                    wanted=(int *)((char *)D_L00_0022F7C0+0x158+idx*28);
                    if(*wanted!=key) goto top;
                    color=*(unsigned int *)((char *)D_L00_0028E9F0+(off+4));
                }
            } while(0);
            label=func_0028E588(0xea97,one);
            colors[2]=colors[0]=a|color;
            colors[3]=colors[1]=b|color;
            func_0028EA58(label,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
            color=0xf0f0b0;
        }
        colors[3]=colors[1]=b|color;
        colors[2]=colors[0]=a|color;
        func_0028EA58(text,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
    }
    }
}
#undef MW
#undef MY
