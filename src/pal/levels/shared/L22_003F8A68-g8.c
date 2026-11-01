#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define B(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int ref_L22_003F45D8_00;
extern u16 **ref_L22_003F45D8_01;
extern int ref_L22_003F45D8_02;
extern u16 **ref_L22_003F45D8_03;
extern u8 *ref_L22_003F45D8_04;
extern u8 *ref_L22_003F45D8_05;
extern u8 *ref_L22_003F45D8_06;
extern s16 ref_L22_003F45D8_07[];
extern u8 *ref_L22_003F45D8_08 MACRO_ADDR;
extern int ref_L22_003F45D8_09 __attribute__((sda));
extern int ref_L22_003F45D8_10[];
extern u8 ref_L22_003F45D8_11[] __attribute__((sda));
extern u8 *ref_L22_003F45D8_12;
extern int D_001A79F0;
extern float func_00282E80(void *,void *), func_00282E48(void *,void *);
extern int func_00283CF0(float), func_00282948(void *);
extern u8 *func_0029EFD0(int), *func_002A9640(void *,int,int);
extern void func_0029F338(void *),func_002833F0(void *,void *);
extern void func_002AFD88(void *,void *,float,float,float);
extern void func_00282D30(void *,void *,float),func_002A0F48(void *);
extern void func_L00_00323448(void *,void *,int,int,int,int,int,int);
extern void func_002B37E8(void *,void *);
extern float func_002AA2E8(float *,float,float);
extern void func_PAL_L22_003F9948(void *),func_PAL_L22_003F9A10(void *),func_L22_003F58F8(void *);
extern void func_00283738(void *,void *,void *),func_L00_00323958(void *,void *);
extern void func_L00_0035F5A0(int,int,int),func_L22_003F52D8(void *),func_PAL_L22_003F9B18(void *,int);
extern void func_L22_003A3B50(void *,int),ref_L22_003F45D8_13(void *,int);
typedef unsigned int Qword __attribute__((mode(TI)));
typedef struct {
    Qword basis;
    int group;
    s16 count, second_group;
    u8 *children[14];
    u8 *converted[14];
} ControllerPrefix;

void func_PAL_L22_003F8A68(u8 *obj) {
    u8 *ctl=P(obj,0x68);
    float matrix[12] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    switch(B(obj,0x20)) {
        case 0:
        {
            int i,known,layer,nearest,kind;
            u16 *list;
            float best,max,d,scale,offset;
            u8 *created;
            nearest=-1;
            best=9999.0f;
            max=0.0f;
            kind=-1;
            for(i=0;i<ref_L22_003F45D8_00;i++) {
                for(list=ref_L22_003F45D8_01[i]; list && ((s16)list[-1]>=0 || list==ref_L22_003F45D8_01[i]); list++) {
                    int index,type;
                    u8 *entity,*inst;
                    index=*list&0x7fff;
                    entity=ref_L22_003F45D8_04+index*64;
                    if(!entity) break;
                    inst=ref_L22_003F45D8_08+index*32;
                    type=ref_L22_003F45D8_07[B(inst,0x1d)];
                    d=func_00282E80(entity+0x30,obj+0x10);
                    if(d<best) {
                        kind=type;
                        best=d;
                        nearest=i;
                    }
                }
            }
            if(nearest==-1 || best>2.0f) {
                func_0029F338(obj);
                return;
            }
            I(ctl,0x10)=nearest;
            I(ctl,0xa4)=kind;
            func_002833F0(obj+0xc0,obj+0xf0);
            {
                u16 group=U(ctl,0x10);
                int count=ref_L22_003F45D8_02;
                H(ctl,0x16)=group;
                if((s16)group>=count) H(ctl,0x16)=-1;
            }
            for(known=0;known<ref_L22_003F45D8_09;known++) if(ref_L22_003F45D8_10[known]==kind) break;
            if(known==ref_L22_003F45D8_09) {
                ref_L22_003F45D8_09=known+1;
                ref_L22_003F45D8_10[known]=kind;
            }
            for(list=ref_L22_003F45D8_01[I(ctl,0x10)];list && ((s16)list[-1]>=0 || list==ref_L22_003F45D8_01[I(ctl,0x10)]);list++) {
                int index,type;
                u8 *entity,*inst;
                index=*list&0x7fff;
                entity=ref_L22_003F45D8_04+index*64;
                if(!entity) break;
                inst=ref_L22_003F45D8_08+index*32;
                type=ref_L22_003F45D8_07[B(inst,0x1d)];
                if(type!=0xca4 && type!=0xca5 && type!=0xca7) {
                    d=func_00282E48(entity+0x30,ref_L22_003F45D8_11);
                    if(max<d) max=d;
                }
            }
            H(ctl,0x14)=func_00283CF0((max-func_00282E48(obj+0x10,ref_L22_003F45D8_11)+4.5f)*0.25f);
            F(ctl,0xa0)=H(ctl,0x14)*4.0f;
            qcopy_nc(ctl,obj+0xe0);
            scale=1.0f;
            offset=0.0f;
            for(layer=0;layer<H(ctl,0x14);layer++) {
                if(kind==0xc4c) created=func_0029EFD0(0xdcb);
                else created=func_0029EFD0(0xdcc);
                if(created) {
                    qcopy(created+0x10,obj+0x10);
                    qcopy(created+0xf0,obj+0xf0);
                    *(Qword *)(created+0xc0)=*(Qword *)(obj+0xc0);
                    *(Qword *)(created+0xd0)=*(Qword *)(obj+0xd0);
                    *(Qword *)(created+0xe0)=*(Qword *)(obj+0xe0);
                    func_002AFD88(obj,created+0x10,0.0f,0.0f,offset);
                    offset+=4.0f;
                    func_00282D30(created+0xc0,created+0xc0,scale);
                    func_00282D30(created+0xd0,created+0xd0,scale);
                    U(created,0x34)|=0x4100;
                    func_002A0F48(created);
                    P(ctl,0x18+layer*4)=created;
                }
                scale*=1.08f;
            }
            func_L00_00323448(obj,ctl+0xd0,90,-1,I(ctl,0x10),H(ctl,0x16),7,0);
            B(ctl,0x11d)=1;
            F(ctl,0xac)=50.0f;
            B(obj,0x30)=255;
            B(obj,0x20)=1;
            break;
        }
        case 1:
        {
            int j,i,index,type,second,first,active;
            u16 *list;
            u8 *entity,*inst,*created,*hit,*scan,*rec,*found,*end;
            hit=0;
            for(i=0;i<H(ctl,0x14);i++) {
                if(!((ControllerPrefix *)ctl)->children[i]) continue;
                found=func_002A9640(((ControllerPrefix *)ctl)->children[i],0x80000,0);
                if(!found) continue;
                hit=found;
                if(I(ctl,0xa8) || !(F(hit,0x2c)<F(ctl,0xac))) continue;
                for(list=ref_L22_003F45D8_01[I(ctl,0x10)];list && ((s16)list[-1]>=0 || list==ref_L22_003F45D8_01[I(ctl,0x10)]);list++) {
                    index=*list&0x7fff;
                    entity=ref_L22_003F45D8_04+index*64;
                    if(!entity) break;
                    inst=ref_L22_003F45D8_08+index*32;
                    type=ref_L22_003F45D8_07[B(inst,0x1d)];
                    if(type!=0xc4a && type!=0xc4c && type!=0xc4f && type!=0xc50 && type!=0xf5f && type!=0xc55) continue;
                    if(func_00282E48(entity+0x30,((ControllerPrefix *)ctl)->children[i]+0x10)>2.0f) continue;
                    first=0xdc2;
                    second=0xdc3;
                    switch(type) {
                        case 0xc4c:
                        first=0xdc4;
                        second=0xdc5;
                        break;
                        case 0xc4f:
                        first=0xdc6;
                        second=0xdc7;
                        break;
                        case 0xc50:
                        second=first=0xdc8;
                        break;
                        case 0xc51:
                        second=first=0xdc9;
                        break;
                        case 0xc55:
                        second=first=0xdca;
                        break;
                        case 0xf5f:
                        second=first=0x1217;
                        break;
                        case 0xf61:
                        second=first=0x1218;
                        break;
                        case 0xf83:
                        second=first=0x1219;
                        break;
                        case 0xf84:
                        second=first=0x121a;
                        break;
                        case 0xf8a:
                        second=first=0x121b;
                        break;
                        case 0xf8b:
                        second=first=0x121c;
                        break;
                        case 0xf9a:
                        second=first=0x121d;
                        break;
                        case 0xf9b:
                        second=first=0x121e;
                        break;
                        case 0xfff:
                        second=first=0x121f;
                        break;
                        case 0x1000:
                        second=first=0x1220;
                        break;
                        case 0xffd:
                        second=first=0x1221;
                        break;
                        case 0xffe:
                        second=first=0x1222;
                        break;
                        case 0xf8d:
                        second=first=0x1223;
                        break;
                    }
                    created=0;
                    if(((ControllerPrefix *)ctl)->converted[i]) {
                        if(H(((ControllerPrefix *)ctl)->converted[i],0xaa)!=second) {
                            created=func_0029EFD0(second);
                            if(!created) break;
                            func_0029F338(((ControllerPrefix *)ctl)->converted[i]);
                            rec=ctl;
                            do {
                                if(!B(rec,0x11c) && ((ControllerPrefix *)ctl)->converted[i]==ref_L22_003F45D8_12+H(rec,0x118)*256) H(rec,0x118)=(created-ref_L22_003F45D8_12)>>8;
                                rec+=0x50;
                            } while((int)rec<(int)(ctl+0x1c20));
                            ((ControllerPrefix *)ctl)->converted[i]=created;
                        }
                    } else created=func_0029EFD0(first);
                    if(created) {
                        end=ctl+0x1c20;
                        active=1;
                        for(scan=ctl;(int)scan<(int)end;scan+=0x50) {
                            if(B(scan,0x11c)==active && H(scan,0x118)==index) {
                                B(scan,0x11c)=0;
                                H(scan,0x118)=(created-ref_L22_003F45D8_12)>>8;
                                break;
                            }
                        }
                        func_002B37E8(created,((ControllerPrefix *)ctl)->children[i]);
                        ((ControllerPrefix *)ctl)->converted[i]=created;
                        *(Qword *)(created+0xc0)=*(Qword *)(entity);
                        *(Qword *)(created+0xd0)=*(Qword *)(entity+0x10);
                        *(Qword *)(created+0xe0)=*(Qword *)(entity+0x20);
                        U(created,0x34)|=0x100;
                        B(inst,0x1e)|=4;
                    }
                    break;
                }
            }
            if(func_00282948(ctl+0xa8) && hit) {
                func_002AA2E8((float *)(ctl+0xac),0.0f,F(hit,0x2c));
                if(F(ctl,0xac)==0.0f) {
                    B(obj,0x20)=2;
                    break;
                }
                func_PAL_L22_003F9948(obj);
                I(ctl,0xa8)=33;
            }
            for(j=0;j<H(ctl,0x14);j++) B(((ControllerPrefix *)ctl)->children[j],0xa8)=255;
            func_PAL_L22_003F9A10(obj);
            if(I(ctl,0xc8)) {
                qzero_nc(rotation);
                rotation[2]=0.010471977f;
                func_002833F0(matrix,rotation);
                func_00283738(obj+0xc0,obj+0xc0,matrix);
            }
            func_L22_003F58F8(obj);
            if(F(ctl,0xbc)!=0.0f || I(ctl,0xc8)) func_L00_00323958(obj,ctl+0xd0);
            break;
        }
        case 2:
        {
            int i,j;
            u16 *list;
            u8 *inst;
            func_L00_0035F5A0(16,0,0);
            func_L22_003F52D8(obj);
            func_PAL_L22_003F9B18(obj,1);
            if(D_001A79F0==22) func_L22_003A3B50(obj+0x10,0);
            else if(D_001A79F0==23) ref_L22_003F45D8_13(obj+0x10,0);
            for(i=0;i<H(ctl,0x14);i++) if(((ControllerPrefix *)ctl)->children[i]) func_0029F338(((ControllerPrefix *)ctl)->children[i]);
            for(j=0;j<H(ctl,0x14);j++) if(((ControllerPrefix *)ctl)->converted[j]) func_0029F338(((ControllerPrefix *)ctl)->converted[j]);
            if(I(ctl,0x10)>=0) {
                for(list=ref_L22_003F45D8_01[I(ctl,0x10)];list && ((s16)list[-1]>=0 || list==ref_L22_003F45D8_01[I(ctl,0x10)]);list++) {
                    inst=ref_L22_003F45D8_05+(*list&0x7fff)*32;
                    if(!inst)break;
                    B(inst,0x1e)|=4;
                }
            }
            if(H(ctl,0x16)>=0) {
                for(list=ref_L22_003F45D8_03[H(ctl,0x16)];list && ((s16)list[-1]>=0 || list==ref_L22_003F45D8_03[H(ctl,0x16)]);list++) {
                    inst=ref_L22_003F45D8_06+(*list&0x7fff)*32;
                    if(!inst)break;
                    B(inst,0x16)|=1;
                }
            }
            B(obj,0x20)=3;
            break;
        }
    }
}
