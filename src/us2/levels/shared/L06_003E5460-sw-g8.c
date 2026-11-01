#include "include_asm.h"

#include "common.h"
extern int D_001A79F0;
extern u8 D_001A7B00;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
typedef struct {
    char pad0[0x212];
    u16 action, mode;
    char pad216[0x126];
    char *attached;
    char pad340[0xE];
    s16 animation;
} RouteHero;
extern RouteHero D_00189E20;
extern char D_00189EA0[];
extern int D_00138324 NOT_SDA;
extern int currentLevelGp SDATA(D_001A79F0);
extern int D_L06_001A8FB4 __attribute__((sda));
extern int D_L06_001AF524 __attribute__((sda));
extern float D_L06_001AF528 __attribute__((sda));
extern float D_L06_001AF530 __attribute__((sda));
extern float D_L06_001AF53C __attribute__((sda));
extern char *D_L06_001FE500[];
typedef struct { char pad0[0x464]; u8 collected[1]; } RouteLevelState;
extern RouteLevelState D_L06_0021E830;
extern void func_0029F338(void *);
extern int func_L06_003E3CC8(void *);
extern void func_L06_0036F728(void *, int);
extern void func_L03_00339128(void *, void *, int, int, int, int, int, float);
extern float func_00283248(float, float);
extern int func_L02_002EF388(void *, void *, void *, int, int);
extern int func_002ACBC8(void *, int);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_002A7CA0(void *, void *, float, float, float, float);
extern int func_L06_003E4BE0(void *, int, void *);
extern float func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_US2_L06_003E5228(void *, int);
extern int func_L06_003E3ED0(void *);
extern void func_L06_003E4FA0(void *);
extern void func_L06_003E4F08(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define B(p,o) (*(u8 *)((p)+(o)))
typedef struct {
    char pad[0x60];
    float timer;
    int moving;
    int unknown68;
    float pitchRate;
    float rollRate;
    int forcedRoute;
    int pointIndex;
    int enabled;
    int trigger[5], approach[5], depart[5], back[5];
    char padD0[0x2C];
    float yawRate;
    int persistent;
    int returnTimer;
    float baseHeight;
} Routes;
typedef struct {
    char pad0[0x20];
    u8 state;
    char pad21[0x11];
    u16 flags32;
    char pad34[0x88];
    u8 route;
} RouteMoby;
#define M ((RouteMoby *)moby)

void func_US2_L06_003E5460(char *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    Routes *st = *(Routes **)(moby+0x68);
    char *node;
    if (D_001A79F0 == 11) {
      if (!st->persistent && D_001A7B00) {
        func_0029F338(moby);
        return;
      }
    }
    func_L06_0036F728(moby,func_L06_003E3CC8(moby));
    if (D_L06_001AF524) {
        int i;
        for(i=0;i<I(D_L06_001FE500[st->approach[0]],0);i++)
            func_L03_00339128(D_L06_001FE500[st->approach[0]]+16+i*16,moby,4,0x800000FF,127,2,255,0.333f);
        for(i=0;i<I(D_L06_001FE500[st->depart[0]],0);i++)
            func_L03_00339128(D_L06_001FE500[st->depart[0]]+16+i*16,moby,4,0x8000FF00,127,2,255,0.333f);
        for(i=0;i<I(D_L06_001FE500[st->back[0]],0);i++)
            func_L03_00339128(D_L06_001FE500[st->back[0]]+16+i*16,moby,4,0x80FF0000,127,2,255,0.333f);
    }
    qcopy(oldpos,moby+0x10);
    qcopy(oldrot,moby+0xF0);
    switch(M->state) {
    case 0:
        st->baseHeight=F(moby,0x18);
        if(st->approach[0]!=-1) {
            rot[2]=func_00283248(F(D_L06_001FE500[st->approach[0]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->approach[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=D_L06_001FE500[st->approach[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                st->baseHeight=F(node,0x18);
            } else {
                func_L02_002EF388(moby,D_L06_001FE500[st->approach[0]]+16,rot,0,0);
                st->baseHeight=F(D_L06_001FE500[st->approach[0]],0x18);
            }
        } else if(st->depart[0]!=-1) {
            rot[2]=func_00283248(F(D_L06_001FE500[st->depart[0]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[0]],0x24)-F(moby,0x14));
            if ((H(moby,0x34)^1)&1) {
                node=D_L06_001FE500[st->depart[0]];
                qcopy(moby+0x10,node+0x10);
                qcopy(moby+0xF0,rot);
                st->baseHeight=F(node,0x18);
            } else {
                func_L02_002EF388(moby,D_L06_001FE500[st->depart[0]]+16,rot,0,0);
                st->baseHeight=F(D_L06_001FE500[st->depart[0]],0x18);
            }
        }
        M->flags32=0x80; B(moby,0x30)=255; st->forcedRoute=-1;
        M->state=1; I(moby,0x98)=0;
        {
            u16 id=H(moby,0xB2);
            if (!D_L06_0021E830.collected[(s16)id]) {
                int bits=D_0019B4A8[((s16)id>>1)+(currentLevelGp<<10)];
                if (!((id & 1) ? ((bits >> 4) & 7) != 0 : (bits & 7) != 0)) break;
            }
            func_0029F338(moby); return;
        }
    case 1: {
        int i;
        if (!st->enabled) break;
        if (!(D_0019B2E8[B(moby,0xB0)+(currentLevelGp<<4)]&0x80)) break;
        for(i=0;i<5;i++) {
            if(st->trigger[i]==-1 && st->forcedRoute!=i) continue;
            if(!func_002ACBC8(D_00189EA0,st->trigger[i]) && st->forcedRoute!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(st->approach[i]!=-1) {
                rot[2]=func_00283248(F(D_L06_001FE500[st->approach[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->approach[i]],0x24)-F(moby,0x14));
                func_L02_002EF388(moby,D_L06_001FE500[st->approach[i]]+16,rot,0,0);
                st->baseHeight=F(D_L06_001FE500[st->approach[i]],0x18);
            } else if (st->depart[i]!=-1) {
                if(func_00282E48(moby+0x10,D_L06_001FE500[st->depart[i]]+16)>4) {
                    rot[2]=func_00283248(F(D_L06_001FE500[st->depart[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[i]],0x24)-F(moby,0x14));
                    func_L02_002EF388(moby,D_L06_001FE500[st->depart[i]]+16,rot,0,0);
                    st->baseHeight=F(D_L06_001FE500[st->depart[i]],0x18);
                }
                func_002A7CA0(moby,&st->yawRate,func_00283248(F(D_L06_001FE500[st->depart[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            st->timer=D_L06_001AF528*(1.0f/60); st->moving=1; st->forcedRoute=-1;
            break;
        }
        break;
    }
    case 2:
        if(st->approach[M->route]==-1 || func_L06_003E4BE0(moby,st->approach[M->route],&st->pointIndex)) {
            M->state=3; I((char *)st,0xE4)=-1;
        }
        break;
    case 3: {
        int i;
        func_002A7CA0(moby,&st->yawRate,func_00283248(F(D_L06_001FE500[st->depart[M->route]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[M->route]],0x24)-F(moby,0x14)),0.000581776490435f,0.000581776490435f,0.0203621778637f);
        func_002AAA00(moby+0xF4,0,&st->pitchRate,D_L06_001AF530*0.000004848137291264255f,D_L06_001AF530*0.000004848137291264255f,0.20943954586982727f,0);
        func_002AAA00(moby+0xF0,0,&st->rollRate,D_L06_001AF53C*0.000004848137291264255f,D_L06_001AF53C*0.000004848137291264255f,0.20943954586982727f,0);
        if(D_00189E20.attached==moby && !D_00189E20.animation) {
            func_US2_L06_003E5228(moby,M->route);
            if((D_00138324&16) && D_L06_001A8FB4==8) {
                st->timer=0; M->state=5; st->moving=1;
            }
        }
        for(i=0;i<5;i++) {
            if(st->trigger[i]==-1 && st->forcedRoute!=i) continue;
            if(i==M->route) continue;
            if(!func_002ACBC8(D_00189EA0,st->trigger[i]) && st->forcedRoute!=i) continue;
            I(moby,0x98)=I(*(char **)(moby+0x24),0x10);
            if(st->approach[i]!=-1) {
                rot[2]=func_00283248(F(D_L06_001FE500[st->approach[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->approach[i]],0x24)-F(moby,0x14));
                func_L02_002EF388(moby,D_L06_001FE500[st->approach[i]]+16,rot,0,0);
                st->baseHeight=F(D_L06_001FE500[st->approach[i]],0x18);
            } else if (st->depart[i]!=-1) {
                if(func_00282E48(moby+0x10,D_L06_001FE500[st->depart[i]]+16)>4) {
                    rot[2]=func_00283248(F(D_L06_001FE500[st->depart[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[i]],0x24)-F(moby,0x14));
                    func_L02_002EF388(moby,D_L06_001FE500[st->depart[i]]+16,rot,0,0);
                    st->baseHeight=F(D_L06_001FE500[st->depart[i]],0x18);
                }
                func_002A7CA0(moby,&st->yawRate,func_00283248(F(D_L06_001FE500[st->depart[i]],0x20)-F(moby,0x10),F(D_L06_001FE500[st->depart[i]],0x24)-F(moby,0x14)),0.00116355298087f,0.00116355298087f,0.104719772935f);
            }
            M->route=i; M->state=2; M->flags32=0x80;
            st->timer=D_L06_001AF528*(1.0f/60); st->moving=1; st->forcedRoute=-1;
            break;
        }
        break;
    }
    case 4: M->state=5; break;
    case 5:
        if(func_L06_003E3ED0(moby)) {
            D_00189E20.action=4; D_00189E20.mode=8;
            func_L06_003E4FA0(moby);
        }
        if(func_L06_003E4BE0(moby,st->depart[M->route],&st->pointIndex)) {
            M->state=6; st->returnTimer=120;
        }
        break;
    case 6:
        func_002AAA00(moby+0xF4,0,&st->pitchRate,D_L06_001AF530*0.000004848137291264255f,D_L06_001AF530*0.000004848137291264255f,0.20943954586982727f,0);
        func_002AAA00(moby+0xF0,0,&st->rollRate,D_L06_001AF53C*0.000004848137291264255f,D_L06_001AF53C*0.000004848137291264255f,0.20943954586982727f,0);
        if(st->back[M->route]!=-1 && func_00282E48(moby+0x10,D_00189EA0)>15) {
            M->state=7; st->moving=1;
        } else if(st->back[M->route]==-1 && func_00282E80(moby+0x10,D_00189EA0)>5) M->state=1;
        break;
    case 7:
        if(func_L06_003E4BE0(moby,st->back[M->route],&st->pointIndex)) {
            M->flags32=0; M->state=1; I(moby,0x98)=0;
        }
        break;
    }
    func_L06_003E4F08(moby);
    func_00282CF0(delta,moby+0x10,oldpos);
    func_002AD6F0((char *)st+0x20,delta,oldrot,moby+0xF0);
}
