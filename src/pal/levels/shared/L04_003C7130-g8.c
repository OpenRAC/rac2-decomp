/* func_PAL_L04_003C7130, the PAL copy of func_L04_003C3BA0: the same C, where 0.00416667f becomes
 * 0.005f, 0.0166667f becomes 0.02f, and the random value stored at particle+0xA is scaled to 50 Hz. */
#include "common.h"

/* Initializes an emitter and its two slot ranges, then spawns nearby particles
 * and registers its render callback on subsequent updates. */
typedef unsigned int EQ __attribute__((mode(TI)));
typedef union { EQ q; float f[4]; } EVec;
#define EB(p,o) (*(u8 *)((char *)(p)+(o)))
#define EH(p,o) (*(s16 *)((char *)(p)+(o)))
#define EI(p,o) (*(s32 *)((char *)(p)+(o)))
#define EF(p,o) (*(float *)((char *)(p)+(o)))
extern char *D_L04_001B25CC;
extern EVec D_L04_0023BDD0[];
extern u8 D_L04_0023D090[];
extern s16 D_L04_0023D860[];
extern float D_L04_001AF3E0 __attribute__((sda));
extern int D_L04_001AF3BC __attribute__((sda));
extern int D_L04_001AF3C0 __attribute__((sda));
extern int D_L04_001AF3C4 __attribute__((sda));
extern int D_L04_001AF3C8 __attribute__((sda));
extern float D_L04_001AF3B4 __attribute__((sda));
extern float D_L04_001AF3B8 __attribute__((sda));
extern char D_L04_001B9680[];
extern float func_00282DF0(void *);
extern int func_00283DB8(void *,float);
extern float func_00282E80(void *,void *);
extern void func_0029F338(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void func_002830C0(void *,void *,void *);
extern char *func_PAL_002BE9A8(float,void *,int,float,void *,float,int,float,int);
extern void ref_PAL_L04_003C7130_00(void *,void *);
extern void func_PAL_L04_003C7600(void *);
extern void func_L04_003C4858(void *,int);
extern void func_L04_003C49C0(void *,int);
extern u32 func_L04_003C70C8(u32);
typedef struct { short first,count; int matrix; char pad08[0x40]; float radius; } EmitterView;
void func_PAL_L04_003C7130(char *self) {
    EVec bound, velocity, position;
    char *state = *(char **)(self+0x68), *matrix;
    int i,end,color,kind;
    float size,r;
    char *particle,*data;
    switch (EB(self,0x20)) {
    case 0:
        EB(self,0x20)=1; EB(self,0x30)=255;
        if (((EmitterView *)state)->matrix==-1) { func_0029F338(self); return; }
        ((EmitterView *)state)->radius=func_00282DF0(D_L04_001B25CC+((EmitterView *)state)->matrix*128+0x10);
        r=func_00282DF0(D_L04_001B25CC+((EmitterView *)state)->matrix*128);
        if (((EmitterView *)state)->radius<r) ((EmitterView *)state)->radius=r;
        EF(state,0x44)=EH(state,0x40) ? ((EmitterView *)state)->radius : 3.0f;
        EF(state,0x50)=func_00282DF0(D_L04_001B25CC+((EmitterView *)state)->matrix*128+0x20)*0.5f;
        EH(state,0)=func_L04_003C70C8(EH(state,2)+EH(state,0x40));
        end=EH(state,0)+EH(state,2);
        for(i=EH(state,0);i<end;i++) {
            D_L04_0023D090[i]=func_002A77E0(2);
            D_L04_0023BDD0[i].f[3]=1.0f;
            func_L04_003C4858(self,i);
            D_L04_0023D860[i]=0;
        }
        { int start=end; end+=EH(state,0x40);
        for(i=start;i<end;i++) {
            D_L04_0023D090[i]=func_002A77E0(2);
            D_L04_0023BDD0[i].f[3]=1.0f;
            func_L04_003C49C0(self,i);
        }
        }
        EF(D_L04_001B25CC+((EmitterView *)state)->matrix*128,0x3C)=1.0f;
        EI(state,0x38)=(EB(state,0x3E)<<16)|(EB(state,0x3D)<<8)|EB(state,0x3C);
        break;
    case 1: {
        int j;
        matrix=D_L04_001B25CC+((EmitterView *)state)->matrix*128;
        qcopy(&bound,matrix+0x30);
        bound.f[2]+=9.0f; bound.f[3]=10.0f;
        if (func_00283DB8(&bound,D_L04_001AF3E0)<0) return;
        if (EH(state,0x42) && func_00282E80(D_L04_001B9680,self+0x10)<128.0f) {
            for(j=0;j<D_L04_001AF3BC;j++) {
                velocity.f[0]=func_002A78D8(0.0f,1.0f);
                velocity.f[1]=func_002A78D8(0.0f,1.0f);
                velocity.f[2]=1.0f; velocity.f[3]=1.0f;
                func_002830C0(&position,&velocity,matrix);
                position.f[2]+=0.5f;
                velocity.f[0]=func_002A78D8(0.0f,0.0050000004f);
                velocity.f[1]=func_002A78D8(0.0f,0.0050000004f);
                velocity.f[2]=EF(state,0x20)*0.020000001f;
                size=func_002A7878(EF(state,0x24),EF(state,0x28));
                color=(func_002A7820(EH(state,0x2C),EH(state,0x2E))<<24)|D_L04_001AF3C8;
                kind=func_002A7820(D_L04_001AF3C0,D_L04_001AF3C4);
                particle=func_PAL_002BE9A8(D_L04_001AF3B4,&position,kind,1.0f,&velocity,D_L04_001AF3B8,color,size,0);
                if (particle) {
                    data=particle+0x20;
                    EH(particle,0xA)=((s32)func_002A7820(EI(state,0x30),EI(state,0x34)) * 5 + 2) / 6;
                    EI(data,4)=3; EB(data,0xA)=color>>24; EB(data,0xB)=EB(particle,0xA);
                    if(func_002A77E0(2)) EB(particle,3)=0x44;
                }
            }
        }
        ref_PAL_L04_003C7130_00(func_PAL_L04_003C7600,self);
        break;
    }
    }
}
