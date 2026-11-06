/* func_PAL_L11_003FDC7C, the PAL copy of func_L02_00401ED8: the same C, with its timers scaled to 50 Hz
   (the initial timer read as an int) and func_L02_00402300 becoming func_PAL_L02_00406D40. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int D_L02_001B17C0 __attribute__((sda)), D_L02_001B17C4 __attribute__((sda)), D_L02_001B17C8 __attribute__((sda)), D_L02_001B17CC __attribute__((sda)), D_L02_001B17D0 __attribute__((sda));
extern float D_L02_001B17D4 __attribute__((sda)), D_L02_001B17D8 __attribute__((sda)), D_L02_001B17DC __attribute__((sda));
extern char D_00189EA0[], D_00188660[];
extern void func_002833F0(void *,void *), func_002A7750(void *,int,int), func_00282978(void *), func_L00_002E6EF8(void *,void *), func_L02_00402440(void *), func_PAL_L02_00406D40(void *), func_00282CF0(void *,void *,void *), func_L00_0031BDC0(void *,void *,void *,void *), func_002A8C28(void *,void *,int,int,int,int,float,float,float),func_002E59F8(int);
extern int func_00283DB8(void *,float),func_002E59B0(void *,int),func_L00_0035F5A0(int,int,void *);
extern float func_L02_002F21C0(void *,void *),func_00282DF0(void *);
struct State401ED8 { char pad[0x30]; short timer30, timer32, timer34, sound; };
void func_PAL_L11_003FDC7C(char *o) {
    char *p; Vec point,a,b,c,d,e; float t; int initialTimer;
    func_002833F0(o+0xC0,o+0xF0);
    p=*(char **)(o+0x68);
    switch (*(unsigned char *)(o+0x20)) {
    case 0:
        p[9]=0; p[8]=3; *(int *)(p+0x10)=0; o[0x31]=0; initialTimer=D_L02_001B17C0;
        *(unsigned short *)(o+0x34)=(*(unsigned short *)(o+0x34)&0xEFFF)|1;
        ((struct State401ED8 *)p)->timer30=0; ((struct State401ED8 *)p)->timer32=((s32)(initialTimer) * 5 + 2) / 6; ((struct State401ED8 *)p)->sound=-1;
        func_002A7750(o,1,-1); break;
    case 1:
        if (((struct State401ED8 *)p)->timer32==0) {
            if (((struct State401ED8 *)p)->timer30!=0) {
                ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C4+D_L02_001B17C8) * 5 + 2) / 6;
                ((struct State401ED8 *)p)->timer34=D_L02_001B17CC;
                func_002A7750(o,2,-1);
            }
        } else if (((struct State401ED8 *)p)->timer30!=0) func_00282978(p+0x32);
        break;
    case 2:
        if (((struct State401ED8 *)p)->timer34==0) {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17D0) * 5 + 2) / 6;
            func_002A7750(o,3,-1);
        } else if (((struct State401ED8 *)p)->timer32>D_L02_001B17C8) func_L00_002E6EF8(func_L02_00402440,o);
        else if (((struct State401ED8 *)p)->timer32==0) {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C4+D_L02_001B17C8) * 5 + 2) / 6;
            func_00282978(p+0x34);
        }
        func_00282978(p+0x32); break;
    case 3:
        if (((struct State401ED8 *)p)->timer32!=0) {
            a.q=0;
            a.f[0]=*(float *)(o+0x10); a.f[1]=*(float *)(o+0x14); a.f[2]=*(float *)(o+0x18); a.f[3]=1;
            point.q=a.q;
            if(func_00283DB8(&point,128.0f)>0) {
                if(func_L02_002F21C0(o+0x10,D_00189EA0)<4.0f) {
                    qcopy(&a,o+0x10); qcopy(&b,o+0x10); b.f[2]+=D_L02_001B17D4;
                    func_L00_0031BDC0(&c,&a,&b,D_00189EA0);
                    func_00282CF0(&d,&a,&c); func_00282CF0(&e,&a,&b);
                    t=func_00282DF0(&d); t/=func_00282DF0(&e);
                    if(t<0)t=0; if(t>1)t=1;
                    func_002A8C28(o,&c,0x10001,0,1,0,D_L02_001B17D8+(D_L02_001B17DC-D_L02_001B17D8)*t,(unsigned char)p[0x14],1);
                } else func_002A8C28(o,o+0x10,0x10001,0,1,0,D_L02_001B17D8,(unsigned char)p[0x14],1);
                func_PAL_L02_00406D40(o); func_L00_002E6EF8(func_L02_00402440,o);
            }
            func_00282978(p+0x32);
            if(!func_002E59B0(o,((struct State401ED8 *)p)->sound)) ((struct State401ED8 *)p)->sound=func_L00_0035F5A0(17,4,o);
        } else {
            ((struct State401ED8 *)p)->timer32=((s32)(D_L02_001B17C0) * 5 + 2) / 6;
            if(((struct State401ED8 *)p)->sound!=-1) {
                unsigned char *s=(unsigned char *)D_00188660+((struct State401ED8 *)p)->sound*0x70;
                if(*(char **)(s+0x88)==o && (unsigned char)s[0x74])func_002E59F8(((struct State401ED8 *)p)->sound);
            }
            ((struct State401ED8 *)p)->sound=-1;func_002A7750(o,1,-1);
        } break;
    }
}
