/* func_PAL_L13_004280E8, the PAL copy of func_L13_004230B0: the same C, where rename func_L00_002D70A0 becomes func_PAL_L00_002D7850; expr 0.016666668f becomes 0.02f; scale I(d,0x74); scale I(d,0x78); lit 6 becomes 5. */
/* Update the vertical platform, its motion sound, and its pulsing tint.
 * State 1 checks the automatic height transitions after handling its trigger.
 */
#include "common.h"
#define I(p, o) (*(int *)((u8 *)(p)+(o)))
#define P(p, o) (*(u8 **)((u8 *)(p)+(o)))
#define F(p, o) (*(float *)((u8 *)(p)+(o)))
typedef struct {
    u8 pad0[0x88]; float height;
    u8 pad8c[0x33C-0x8C]; u8 *platform;
    u8 pad340[0x2294-0x340]; int mode;
} PlatformHero;
extern PlatformHero D_00189E20;
extern u8 D_00188660[] NOT_SDA;
extern u8 *D_L13_001BFD18;
extern int D_L13_001B2448 MACRO_ADDR;
extern void func_002E59F8(int);
extern int func_L00_00324120(void *);
extern u8 *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(void *);
extern void func_002A7750(void *,int,int);
extern int func_00277258(void *,int,void *,float);
extern int func_002E5CF8(int,int,void *);
extern void func_002AA548(float *,float *,float,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
void func_PAL_L13_004280E8(u8 *m) {
    u8 *d=P(m,0x68);
    u8 oldpos[16] __attribute__((aligned(16)));
    u8 oldrot[16] __attribute__((aligned(16)));
    u8 delta[16] __attribute__((aligned(16)));
    int n;
    unsigned int c, color;
    int tickPhase;
    float f;
    if(D_00189E20.mode==0x82) return;
    qcopy_nc(oldpos,m+0x10);
    qcopy_nc(oldrot,m+0xF0);
    switch(m[0x20]) {
    case 0:
        m[0x30]=255;
        I(d,0x7C)=I(d,0x78);
        I(d,0x5C)|=1;
        qcopy_nc(d+0x90,m+0x10);
        qcopy_nc(d+0x80,d+0x90);
        F(d,0x88)=F(d,0x98)-F(d,0x68);
        I(d,0x60)=(((int)(I(d,0x74)) * 5 + 2) / 6);
        m[0x20]=1;
        I(d,0xB0)=-1;
        I(d,0x64)=0;
        break;
    case 1:
        n=I(d,0xB0);
        if(n!=-1) {
            u8 *sound=D_00188660+n*0x70; if(P(sound,0x88)==m && sound[0x74]) func_002E59F8(n);
        }
        I(d,0xB0)=-1;
        if(func_L00_00324120(m)) {
            if(F(m,0x18)==F(d,0x98)) {
                if(I(d,0xB4)) {
                    P(d,0xB8)=func_PAL_L00_002D7850(5);
                    F(P(d,0xB8),0)=1.0f;
                    F(P(d,0xB8),4)=4.5f;
                    I(d,0xBC)=1;
                }
                func_002A7750(m,2,-1);
            } else {
                if(I(d,0xB4)) {
                    P(d,0xB8)=func_PAL_L00_002D7850(5);
                    F(P(d,0xB8),0)=1.0f;
                    F(P(d,0xB8),4)=4.5f;
                    I(d,0xBC)=1;
                }
                func_002A7750(m,3,-1);
            }
        }
        {
            if(F(m,0x18)-D_00189E20.height>F(d,0x68)*0.5f && F(m,0x18)==F(d,0x98)) func_002A7750(m,2,-1);
            else if(F(m,0x18)-D_00189E20.height<-F(d,0x68)*0.5f && F(m,0x18)==F(d,0x88) && D_00189E20.mode!=0x82) func_002A7750(m,3,-1);
        }
        break;
    case 2:
        if(F(m,0x18)<=F(d,0x88)) {
            if(I(d,0xBC)) { func_L00_002D7140(P(d,0xB8)); I(d,0xBC)=0; }
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=D_00188660+n*0x70; if(P(sound,0x88)==m && sound[0x74]) func_002E59F8(n); }
            I(d,0xB0)=-1;
            if(!func_L00_00324120(m)) m[0x20]=1;
        } else if(!func_00277258(m+0x10,1,m,2.8f) ||
            (F(m,0x18)<=D_00189E20.height || (D_00189E20.platform!=0 && D_00189E20.platform==m) || (D_L13_001BFD18 && *(short *)(D_L13_001BFD18+0xAA)==0xEA3))) {
            { u8 *sound=D_00188660+I(d,0xB0)*0x70; if(P(sound,0x88)!=m || !sound[0x74]) I(d,0xB0)=func_002E5CF8(0,4,m); }
            func_002AA548((float *)(m+0x18),(float *)(d+0x64),F(d,0x88),0.0028000001f,0.0024f,0.120000005f);
        } else {
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=D_00188660+n*0x70; if(P(sound,0x88)==m && sound[0x74]) func_002E59F8(n); }
            I(d,0xB0)=-1;
        }
        break;
    case 3:
        func_002AA548((float *)(m+0x18),(float *)(d+0x64),F(d,0x98),0.0028000001f,0.0024f,0.120000005f);
        if(F(m,0x18)>=F(d,0x98)) {
            if(I(d,0xBC)) { func_L00_002D7140(P(d,0xB8)); I(d,0xBC)=0; }
            n=I(d,0xB0);
            if(n!=-1) { u8 *sound=D_00188660+n*0x70; if(P(sound,0x88)==m && sound[0x74]) func_002E59F8(n); }
            I(d,0xB0)=-1;
            if(!func_L00_00324120(m)) { I(d,0x60)=(((int)(I(d,0x74)) * 5 + 2) / 6); --I(d,0x78); m[0x20]=1; }
        } else {
            { u8 *sound=D_00188660+I(d,0xB0)*0x70; if(P(sound,0x88)!=m || !sound[0x74]) I(d,0xB0)=func_002E5CF8(0,4,m); }
        }
        break;
    case 4:
        n=I(d,0xB0);
        if(n!=-1) { u8 *sound=D_00188660+n*0x70; if(P(sound,0x88)==m && sound[0x74]) func_002E59F8(n); }
        I(d,0xB0)=-1; break;
    }
    f=(float)D_L13_001B2448*(0.02f);
    tickPhase=(int)f;
    f-=(float)tickPhase;
    if(!(tickPhase&1)) f=1.0f-f;
    c=(int)(f*255.0f);
    color=(c<<8)|0x7F000000;
    I(m,0x78)=(c<<16)|color|c;
    func_00282CF0(delta,m+0x10,oldpos);
    func_002AD6F0(d+0x20,delta,oldrot,m+0xF0);
}
