/* func_US2_L08_003DB3BC, the USA v2.00 copy of func_L08_003D9F68: the same C, where case 11 passes
   B(state,0x40C)==2?0x1000:0 instead of 0 as the second argument of the call, and that callee is
   this release's own func_US2_002A7AA8 (v1.01 func_002A6C58, 1856 -> 1880 bytes). */
#include "common.h"
#define B(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void func_L08_003D92D8(void *), func_L08_003D8348(void *), func_L08_003D8CA8(void *), func_L08_003D9208(void *), func_L08_003D9798(void *);
extern int func_002A77E0(int),func_002A7820(int,int),func_001163B0(void);
extern int func_L08_003D8918(int),func_L08_003D8990(int),func_L08_003D8948(int),func_L08_003D89D8(int);
extern void func_0026FEB8(void *,int,int),func_002A7470(void *,int,int,int),func_002A7750(void *,int,int);
extern int func_L08_0032F898(void *,void *,float,float,int,int,int,int);
extern int func_00282948(void *);
extern int func_002B5258(void *);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_L01_003BD178(void *,void *,int,float,float,float,float,float,float);
extern int func_L08_003D9038(void *,float,float,float,float,float,float,float);
extern int func_002B6318(void *),func_002B1C20(void *,void *);
extern int func_L01_00321178(void *,void *);
extern void func_002B5278(void *,float);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,int),func_00277258(void *,int,void *,float);
extern void func_00283028(void *,void *,void *),func_00282D30(void *,void *,float);
extern float func_00282E80(void *,void *),func_00283248(float,float),func_00283C80(float,float);
extern void func_L01_00337A60(void *,void *,void *,int);
extern u8 D_L08_002B5270[];
typedef struct { u8 pad[0x18]; u8 *moby; u32 pad1C; float point[4], adjusted[4], normal[4]; } Collision;
extern Collision D_L08_001BFF40;
typedef struct {
    u8 pad00[0x24];
    u8 *anim;
    u8 pad28[9];
    u8 active;
    u16 field32, flags;
    u8 pad36[0x62];
    int animation;
} GroundMoby;
extern u8 *D_L08_001FE7C0[];
extern u8 D_00189EA0[];
extern int D_0018C0B4[];
extern void func_L08_003D7E68(void *),func_L08_003D7FB8(void *,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_US2_002A7AA8(void *,int,int);
extern u8 D_L08_001A8F20[] MACRO_ADDR;
typedef struct { u8 pad[0x464]; u8 flags[0]; } MobyFlags;
extern MobyFlags D_L08_0021DE80, D_L08_0021EAF0;
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern u8 D_0019B2E8[],D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;
void func_US2_L08_003DB3BC(u8 *object)
{
    u8 *state=P(object,0x68);
    float old[4], delta[4];
    int ready, result;
    func_L08_003D92D8(object);
    switch(B(object,0x20)) {
    case 0:
        func_L08_003D8348(object);
        if(!object || B(object,0x20)==0xFE || B(object,0x20)==0xFD) return;
        break;
    case 1: {
        int trigger;
        ready=0;
        switch(B(state,0x40D)) {
        case 0:
            if(!func_002A77E0(7))
                {trigger=func_L08_0032F898(object,state+0x210,(float)S(state,0x408),0,I(state,0x410),I(state,0x418),I(state,0x414),-1)^2; goto trigger_test;}
            break;
        case 1:
            if(I(state,0x400)!=-1) ready=func_L08_003D8918(I(state,0x400))!=0;
            else {func_0026FEB8(D_L08_002B5270,S(object,0xAA),S(object,0xB2)); B(state,0x40D)=0;}
            break;
        case 2: trigger=B(object,0xBC);goto trigger_test;
        case 3: ready=func_L08_003D8990(I(state,0x468))!=0;break;
        case 4: ready=func_L08_003D8948(I(state,0x400))!=0;break;
        case 5: trigger=func_L08_003D89D8(I(state,0x404));
        trigger_test: ready=trigger!=0;break;
        }
        if(B(object,0xBC)&2) ready=1;
        if(ready) {
            I(state,0x15C)=I(state,0x428); I(object,0x98)=I(P(object,0x24),0x10);
            B(object,0x30)=B(state,0x408); qzero_nc(state+0x1C0);
            I(state,0x440)=func_002A7820(0,180); func_002A7750(object,3,-1);
        }
        break;
    }
    case 3:
        if(func_00282948(state+0x440)) {
            if(B(object,0x43)!=4) func_002A7470(object,4,0,10);
            B(object,0x31)=1; H(object,0x34)&=0xFFFE;func_002A7750(object,2,0);
        }
        break;
    case 2:
        if(func_0029F530(object)<12.0f) {
            qcopy_nc(old,object+0x10); old[2]=F(state,0x434);
            func_L01_003BD178(object,old,3,1,1.5f,0.5f,0,0.1f,0.8f);
        }
        if(B(object,0x60)&2) {
            switch(B(object,0x95)) { case 0: {
                H(object,0x34)&=0xFFFE; B(object,0x31)=1; H(object,0x34)|=0x1000;
                I(state,0x440)=func_002A7820(180,360);func_L08_003D8CA8(object);
                if(B(object,0x43)!=9) func_002A7470(object,9,0,10);
                func_002A7750(object,6,1);
            break; } case 1: {
                H(object,0x34)&=0xEFFF;
                if(B(object,0x43)!=11) func_002A7470(object,11,0,10);
                I(state,0x440)=0; B(object,0x31)=0; H(object,0x34)|=1;
                func_002A7750(object,1,-1);
            break; } }
        }
        break;
    case 4: {
        u8 *collisionMoby;
        GroundMoby *ground=(GroundMoby *)object;
        qcopy_nc(old,object+0x10);func_00282CC0(object+0x10,object+0x10,state+0xD0);
        F(state,0xD8)-=0.0027222223579883575f;F(object,0x18)+=1.5f;
        if(func_002761F8(old,object+0x10,0,object,0)) {
            u8 *hitMoby=D_L08_001BFF40.moby;
            if(hitMoby) {
                if(S(hitMoby,0xAA)==0x945 || S(hitMoby,0xAA)==0x9C6) goto no_ray_response;
            }
            func_00282CF0(delta,old,D_L08_001BFF40.point);
            func_00282F20(delta,delta,1.5f);func_00282CC0(object+0x10,object+0x10,delta);
        }
        no_ray_response:
        if(func_00277258(object+0x10,0,object,1.5f)) {
            collisionMoby=D_L08_001BFF40.moby;
            if(collisionMoby) {
                if(S(collisionMoby,0xAA)==0x945 || S(collisionMoby,0xAA)==0x9C6) goto no_overlap_response;
            } else {
                if(F(object,0x18)<=F(state,0x434)+1.5f+0.1f && F(state,0xD8)<0) {
                    ground->flags|=0x1000;
                    ground->animation=I(ground->anim,0x10);ground->active=1;ground->flags&=0xFFFE;
                    I(state,0x440)=func_002A7820(180,360);func_L08_003D8CA8(object);
                    if(B(object,0x43)!=15) func_002A7470(object,15,0,5);
                    func_002A7750(object,5,-1);
                    goto no_overlap_response;
                }
            }
            qcopy_nc(object+0x10,D_L08_001BFF40.adjusted);
            func_00283028(state+0xD0,state+0xD0,D_L08_001BFF40.normal);
            func_00282D30(state+0xD0,state+0xD0,0.8f);
        }
        no_overlap_response:
        F(object,0x18)-=1.5f; F(state,0xD8)-=0.0027222223579883575f;
        if(F(object,0x18)<F(state,0x434)) F(object,0x18)=F(state,0x434);
        break;
    }
    case 5:
        func_002B5258(object);
        if(B(object,0x60)&2) {
            if(B(object,0x43)!=9) func_002A7470(object,9,0,2);
            func_002A7750(object,6,1);
        }
        break;
    case 6:
        switch(B(object,0x95)) {
        case 0:
            func_002B5258(object);
            if(B(object,0x60)&2) {
                if(!I(state,0x440)) {
                    I(state,0x440)=func_002A7820(180,360);func_L08_003D8CA8(object);
                    if(B(object,0x43)!=9) func_002A7470(object,9,0,10);
                    func_002A7750(object,6,1);
                } else if(B(object,0x43)!=(func_001163B0()&1)) func_002A7470(object,func_001163B0()&1,0,10);
            }
            break;
        case 1:
            if((func_L08_003D9038(object,120,360,90,8,0,2,1)&0x80)||!I(state,0x440)) {
                I(state,0x440)=func_002A7820(30,90);
                if(B(object,0x43)!=(func_001163B0()&1)) func_002A7470(object,func_001163B0()&1,0,10);
                func_002A7750(object,6,0);
            }
            break;
        case 2:
            qcopy_nc(state+0x3F0,state+0x3E0);
            if(func_L08_003D9038(object,120,360,90,8,0,2,1)&0x80) {
                if(B(object,0x43)!=5) func_002A7470(object,5,0,10);
                func_002A7750(object,2,1);
            }
            break;
        }
        if(func_002A77E0(7)) break;
        if(I(state,0x448) || func_L08_0032F898(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1)!=2) {
            if(I(state,0x428)!=-1) {u8 *e=D_L08_001FE7C0[I(state,0x428)];func_L01_00337A60(state+0x210,state+0x210,e+0x10,I(e,0));}
            if(B(state,0x40C)==3) {
                I(state,0x48C)=600;I(state,0x15C)=I(state,0x428);B(state,0x40C)=1;
                qcopy_nc(state+0x3F0,state+0x230);
                if(B(object,0x43)!=9)func_002A7470(object,9,0,func_002A7820(3,6));
                func_002A7750(object,8,0);I(state,0x480)=0;
                break;
            }
            if(!func_002A77E0(9)) {
                I(state,0x15C)=I(state,0x428);I(state,0x448)=func_002A7820(300,360)*2;
                if(B(object,0x43)!=((func_001163B0()&1)+2))func_002A7470(object,(func_001163B0()&1)|2,0,10);
                func_002A7750(object,7,0);
            }
        } else if(B(object,0x20)==6 && B(state,0x40C)==0 && B(object,0x95)!=2) {
            if(B(object,0x43)!=9)func_002A7470(object,9,0,10);
            func_002A7750(object,6,2);
        }
        break;
    case 7:
        switch(B(object,0x95)) { case 0: {
            func_002B5258(object);
            if((B(object,0x60)&2) && (unsigned)(B(object,0x42)-2)<2)I(state,0x440)=0;
            if(!I(state,0x440)) {
                I(state,0x440)=func_002A7820(180,360);
                if(B(object,0x43)!=9)func_002A7470(object,9,0,10);
                func_002A7750(object,7,1);
            }
        break; } case 1: {
            int moved;
            if(I(state,0x44C)) moved=func_L08_003D9038(object,720,180,720,12,0.1f,4,1);
            else moved=func_L08_003D9038(object,180,180,180,12,0.1f,4,1);
            if(moved&0x80) I(state,0x440)=0;
            if(!I(state,0x440)) {
                func_L08_003D8CA8(object);I(state,0x440)=func_002A7820(20,60);
                if(B(object,0x43)!=(func_001163B0()&1))func_002A7470(object,func_001163B0()&1,0,10);
                func_002A7750(object,7,0);
            }
        break; } }
        if(func_002A77E0(7))break;
        if(!I(state,0x48C)) {
            result=func_L08_0032F898(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1);
            if(result==2 || D_0018C0B4[0]==49) {
                I(state,0x254)=2;
                if(!func_002A77E0(4)) {
                    if(B(object,0x43)!=6)func_002A7470(object,6,0,func_002A7820(3,6));
                    func_002A7750(object,8,1);
                }
                if(!I(state,0x448)) {
                    if(B(object,0x43)!=(func_001163B0()&1))func_002A7470(object,func_001163B0()&1,0,10);
                    func_002A7750(object,6,0);
                }
                break;
            }
        }
        if(!I(state,0x44C) && (func_00282E80(object+0x10,state+0x230)<12 || I(state,0x48C))) {
            qcopy_nc(state+0x3F0,state+0x230);
            if(B(object,0x43)!=9)func_002A7470(object,9,0,func_002A7820(3,6));
            func_002A7750(object,8,0);I(state,0x480)=0;
        }
        break;
    case 8: {
        int blocked=0;
        qcopy_nc(state+0x3F0,state+0x230);
        switch(B(object,0x95)) {
        case 0:
            if(func_L08_003D9038(object,360,180,180,16,0.2f,4,0.5f))I(state,0x480)++;
            if(I(state,0x480)>60) {
                if(func_00282E80(object+0x10,state+0x230)<6 && func_00283C80(F(object,0xF8),func_00283248(F(state,0x230)-F(object,0x10),F(state,0x234)-F(object,0x14)))<1.5707964897155762f) {
                    if(B(object,0x43)!=6)func_002A7470(object,6,0,func_002A7820(3,6));
                    func_002A7750(object,8,1);
                } else { I(state,0x480)=0; blocked=1; }
            }
            if(func_00282E80(object+0x10,state+0x230)<4.2f) {
                if(func_00283C80(F(object,0xF8),func_00283248(F(state,0x230)-F(object,0x10),F(state,0x234)-F(object,0x14)))<1.5707964897155762f) {
                    if(B(object,0x43)!=6)func_002A7470(object,6,0,func_002A7820(3,6));
                    func_002A7750(object,8,1);
                }
            }
            if(!I(state,0x48C)) {
                if(blocked || func_L08_0032F898(object,state+0x210,(float)S(object,0x32),(float)S(state,0x40E),I(state,0x41C),I(state,0x424),I(state,0x420),-1)==2) {
                    if(!I(state,0x448)) {
                        I(state,0x440)=0;
                        if(B(object,0x43)!=(func_001163B0()&1))func_002A7470(object,func_001163B0()&1,0,10);
                        func_002A7750(object,6,0);
                    } else {
                        func_L08_003D9038(object,360,180,180,16,0.2f,4,0.5f);
                        I(state,0x440)=0;I(state,0x44C)=func_002A7820(90,180);
                        func_L08_003D8CA8(object);func_002A7750(object,7,0);
                    }
                    goto update_timers;
                }
            }
            if(I(state,0x48C)>0) {qcopy_nc(state+0x210,D_00189EA0);qcopy_nc(state+0x230,D_00189EA0);F(state,0x238)+=0.4f;}
            break;
        case 1:
            func_002B5258(object);
            if(B(object,0x42)==6 && (B(object,0x60)&2)) {
                if(B(object,0x43)!=7)func_002A7470(object,7,0,5);
                func_002A7750(object,8,2);
            }
            break;
        case 2:
            {u8 *hit=P(state,0x250);
            if(hit)func_002B5278(object,func_00283248(F(hit,0x10)-F(object,0x10),F(hit,0x14)-F(object,0x14)));
            else func_002B5278(object,func_00283248(F(state,0x210)-F(object,0x10),F(state,0x214)-F(object,0x14)));}
            if(B(object,0x42)==7 && func_0029F530(object)>24) {
                func_L08_003D9798(object);
                if(B(object,0x60)&2) {
                    if(B(object,0x43)!=8)func_002A7470(object,8,0,10);
                    func_002A7750(object,8,3);
                }
            }
            break;
        case 3:
            func_002B5258(object);
            if(B(object,0x60)&2) {
                I(state,0x48C)=0;I(state,0x440)=0;I(state,0x448)=0;I(state,0x480)=0;
                I(state,0x44C)=func_002A7820(90,180);func_002A7750(object,7,0);func_L08_003D8CA8(object);
            }
            break;
        }
        break;
    }
    case 9:
        I(state,0x430)++; result=func_002B1C20(object,state+0x50);
        if(result&1)func_002A7750(object,11,-1);
        else if((result&2) || I(state,0x430)>360) {
            I(state,0x430)=0;B(state,0x6A)=2;qzero_nc(state+0x1C0);I(state,0x440)=0;
            if(F(state,0x20)<=0)func_002A7750(object,11,-1);
            else if(!func_002B6318(object)) {
                if(B(object,0x43)!=9)func_002A7470(object,9,0,10);
                func_002A7750(object,10,-1);
            } else {
                if(B(object,0x43))func_002A7470(object,0,0,10);
                func_002A7750(object,7,0);
            }
        }
        break;
    case 10:
        F(state,0x154)=0.1f;func_L01_00321178(object,state+0x3E0);
        if(!(I(state,0x1B4)&0x100))func_002A7750(object,7,0);
        break;
    case 11: {
        int index;
        u8 idx;
        func_L08_003D7E68(object);func_L08_003D7FB8(object,D_L08_001A8F20);
        func_002ABBB8(object,D_L08_001A8F20,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,1,0x810001);
        func_US2_002A7AA8(object,B(state,0x40C)==2?0x1000:0,3);
        D_L08_0021DE80.flags[S(object,0xB2)]=B(object,0xB0)+2;
        index=B(object,0xB0);
        if(index==0xFF || (idx=index, !(D_L08_001B2840[idx]&0x80) && (D_0019B2E8[idx+(D_001A79F0<<4)]&0x80)))
            D_L08_0021EAF0.flags[S(object,0xB2)]=B(object,0xB0)+2;
        if(H(object,0xB2)&1) {
            u8 *flag=D_0019B4A8+((S(object,0xB2)>>1)+(D_001A79F0<<10));
            if(((*flag>>4)&7)!=7)*flag+=0x10;
        } else {
            u8 *flag=D_0019B4A8+((S(object,0xB2)>>1)+(D_001A79F0<<10));
            if((*flag&7)!=7)++*flag;
        }
        func_0029F338(object);
        return;
    }
    }
    update_timers:
    func_L08_003D9208(object);
    if(F(object,0x10)<30 || F(object,0x10)>993 || F(object,0x14)<30 || F(object,0x14)>993 || F(object,0x18)<30 || F(object,0x18)>993)func_0029F338(object);
}
