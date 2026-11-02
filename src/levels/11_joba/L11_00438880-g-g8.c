/* func_L11_00438880: skips set entries in the 13-byte flag table at state+0x380,
 * then for each pair of points state+0x100+prev*16 / state+0x100+next*16
 * fills a four-corner quad record twice (func_00281DE8 setup, func_00280B90
 * submit) with different widths, colours and UVs, and
 * finally advances the scrolling UV offset at state+0x35C, wrapping to [-1,1].
 * Built -G8 -g -mno-split-addresses in its own unit (SDATA UV base, absolute
 * NOT_SDA load of 001B12B4).
 * The flag scans index through a block-local `j = next-1`: as a separate
 * variable, the C front end cannot fold flags+(next-1) into (flags+next)-1,
 * so loop.c sees a giv (next-1) feeding the address giv; the summed benefit
 * makes it strength-reduce the address into a pointer register. That gives
 * retail's pointer cursor, the pre-loop test through the computed address and
 * the separate copy into the cursor in the second scan.
 * Explicit UV pointer locals give the spills at 0x100/0x104, following at
 * 0x108 and flags at 0x10C. Casting the shifted alpha byte to int avoids an
 * unsigned-to-float fallback absent in retail. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, int, int);
extern float func_002A7878(float, float);
extern char D_L11_001BA8C0[];
extern float D_L11_001B12B0 __attribute__((sda));
extern float D_L11_001B12B8 __attribute__((sda));
extern float D_L11_001B12BC __attribute__((sda));
extern float D_L11_001B12C0 __attribute__((sda));
extern float D_L11_001B12A8 __attribute__((sda));
extern unsigned int D_L11_001B12A0 __attribute__((sda));
extern unsigned int D_L11_001B12A4 __attribute__((sda));
extern float D_L11_001B1280[] SDATA(D_L11_001B1280);
extern float D_L11_001B1284[];
extern float D_L11_001B12B4[] NOT_SDA;
/* The alpha range endpoint at 001B12B4 is read as float by retail. */
void func_L11_00438880(char *obj) {
    float end[4], start[4], span[4], a[4], b[4], inset[4];
    struct { Quadword pos[4]; unsigned int color[4]; float uv[4][2]; unsigned long words[4]; } quad;
    Quadword corner;
    float *uv0, *uv1;
    char *st=*(char **)(obj+0x68);
    int next, prev, following, i;
    unsigned char *flags;
    unsigned int color;
    if (*(unsigned char *)(obj+0x20)<2) return;
    next=1; prev=0; flags=(unsigned char *)(st+0x380);
    while(next<13) { int j=next-1; if(!flags[j]) break; next++; }
    while (next<12) {
        qcopy(end,st+0x100+next*16);
        qcopy(start,st+0x100+prev*16);
        following=next+1;
        func_00282CF0(inset,start,end);
        func_00282F20(inset,inset,D_L11_001B12C0);
        func_00282CC0(end,end,inset);
        func_00282CF0(span,end,start);
        func_00282CF0(a,end,D_L11_001BA8C0);
        func_00282CF0(b,start,D_L11_001BA8C0);
        func_00282DD8(a,a,span);
        func_00282DD8(b,b,span);
        func_00282F20(a,a,D_L11_001B12B8);
        func_00282F20(b,b,D_L11_001B12B8);
        func_00281DE8(&quad,23,1,128);
        color=(D_L11_001B12A0 & 0xFFFFFF) | ((int)(func_002A7878(D_L11_001B12B0,D_L11_001B12B4[0])*(int)(D_L11_001B12A0>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        uv0=&quad.uv[0][0]; uv1=&quad.uv[0][1];
        for(i=0;i<4;i++) { uv0[i*2]=D_L11_001B1280[i*2]+*(float *)(st+0x35C); uv1[i*2]=D_L11_001B1284[i*2]; }
        func_00282CF0(&corner,end,a); quad.pos[0]=corner;
        func_00282CC0(&corner,end,a); quad.pos[1]=corner;
        func_00282CF0(&corner,start,b); quad.pos[2]=corner;
        func_00282CC0(&corner,start,b); quad.pos[3]=corner;
        func_00280B90(&quad,0,0);
        func_00282F20(a,a,D_L11_001B12BC);
        func_00282F20(b,b,D_L11_001B12BC);
        func_00282CF0(&corner,end,a); quad.pos[0]=corner;
        func_00282CC0(&corner,end,a); quad.pos[1]=corner;
        func_00282CF0(&corner,start,b); quad.pos[2]=corner;
        func_00282CC0(&corner,start,b); quad.pos[3]=corner;
        func_00281DE8(&quad,43,1,128);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=D_L11_001B12A4;
        func_00280B90(&quad,0,0);
        prev=next; next=following;
        while(next<13) { int j=next-1; if(!flags[j]) break; next++; }
    }
    *(float *)(st+0x35C)+=D_L11_001B12A8;
    if (*(float *)(st+0x35C)>1) *(float *)(st+0x35C)-=2;
    if (*(float *)(st+0x35C)<-1) *(float *)(st+0x35C)+=2;
}
