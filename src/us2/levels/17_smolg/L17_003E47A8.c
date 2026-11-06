/*
 * func_US2_L17_003E47A8, the USA v2.00 copy of func_L17_003E31E8: the same C, where each
 * func_002A6C58(object,0,3) now tests the short at 0xB4 and passes 0x1000 when it is zero.
 * The two qzero stores become qzero_nc: with qzero the second arm merges whole into the first.
 */

#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int D_L17_001CA140[];
extern int D_L17_001A8F00 MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern char *D_L17_001B2C1C[] __attribute__((sda));
extern float D_L17_001B0CAC SDATA(D_L17_001B0CAC);
extern float D_L17_001B0CB0 SDATA(D_L17_001B0CB0);
extern float D_L17_001B0CB4 SDATA(D_L17_001B0CB4);
typedef struct { char pad[0x80]; float x,y; } L17HeroRecord;
extern L17HeroRecord D_00189E20;
extern void func_L17_003E41A8(char *);
extern void func_L17_003C7250(char *,char *);
extern int func_L17_003C5B68(char *);
extern void func_L17_003C5AF8(char *);
extern void func_L17_003E3148(char *);
extern void func_L17_003E4560(char *);
extern void func_L17_003E47E8(char *);
extern int func_L17_003E48E0(char *);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern void func_002A7750(char *,int,int);
extern void func_002A7470(char *,int,int,int);
extern void func_002A7398(char *,int,int);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern int func_002B3890(char *);
extern int func_002B1C20(char *,void *);
extern void func_002A6C58(char *,int,int);
extern void func_L01_003E9CF8(char *,int,int);
extern void func_0029F338(char *);
extern void func_002AA2E8(float *,float,float);
extern void func_002AE8C0(char *,void *,float,float);
extern float func_00283248(float,float);
extern void func_002AA800(float *,int,float,float);
extern int func_002B3868(char *);
extern float func_00282E80(void *,void *);
extern int func_002AEB60(char *,float);
extern void func_002E5CF8(int,int,char *);
extern int func_002A8C28(char *,float,void *,int,float,float,int,int,int);
extern void func_002B60B0(char *,float,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_00331440(char *,void *,int,float,float,float);
extern float func_00283180(float),func_00283198(float);
extern void func_00282CD8(void *,void *,void *);
extern float func_00283B98(float,float);
extern void func_002A7CA0(char *,float,float *,float,float,float);

void func_US2_L17_003E47A8(char *object)
{
    float movement[4], position[4];
    char *vars, *other;
    int flags;
    float angle;
    if (D_L17_001CA140[0]) return;
    vars=P(object,0x68);
    if (D_L17_001A8F00==2) {
        if (!B(object,0x31)) return;
        I(vars,0x454)=1;
        I(object,0x98)=0;
        U(object,0x34)=(U(object,0x34)|0x41)&0xEFFF;
        return;
    }
    if (I(vars,0x454)) {
        U(object,0x34)=(U(object,0x34)&0xFFBE)|0x1000;
        I(object,0x98)=I(P(object,0x24),0x10);
        I(vars,0x454)=0;
    }
    func_L17_003E41A8(object);
    func_00282948((int *)(vars+0x440));
    if (I(vars,0x450)!=-1) {
        other=(char *)((I(vars,0x450)<<8)+(u32)D_L17_001B2C1C[0]);
        if (H(other,0xAA)==0x929) func_L17_003C7250(other,object);
    }
    switch(B(object,0x95)) {
    case 0:
        if (I(vars,0x428)==-1 || I(vars,0x42C)==-1 ||
            D_L17_001B2C1C[0]+(I(vars,0x42C)<<8)==object ||
            !(D_L17_001B2C1C[0]+(I(vars,0x42C)<<8)) ||
            B(D_L17_001B2C1C[0]+(I(vars,0x42C)<<8),0x20)==0xFE ||
            B(D_L17_001B2C1C[0]+(I(vars,0x42C)<<8),0x20)==0xFD ||
            !func_L17_003C5B68(D_L17_001B2C1C[0]+(I(vars,0x428)<<8))) {
            func_00282948((int *)(vars+0x41C));
            if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                func_L17_003E3148(object);
                if(I(vars,0x428)!=-1) {
                    if(!func_L17_003C5B68(D_L17_001B2C1C[0]+(I(vars,0x428)<<8))) break;
                    func_L17_003C5AF8(D_L17_001B2C1C[0]+(I(vars,0x428)<<8));
                    { char *entityBase = D_L17_001B2C1C[0];
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                    if(H((I(vars,0x428)<<8)+(u32)entityBase,0xAA)==0x929) {
                        func_002A7750(object,8,3);
                        func_002A7398(object,9,0);
                        F(object,0xF8)=F((char *)((I(vars,0x428)<<8)+(u32)D_L17_001B2C1C[0]),0xF8);
                        I(vars,0x428)=-1;
                    } else {
                        I(vars,0x428)=-1;
                        func_002A7750(object,10,2);
                        if(B(object,0x43)!=2) func_002A7470(object,2,0,14);
                        goto restoreCollision;
                    }
                    }
                } else {
                    func_002A7750(object,10,2);
                    if(B(object,0x43)!=2) func_002A7470(object,2,0,14);
restoreCollision:
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                }
            } else if(H(vars,0x406)) {
                func_002A7750(object,2,1);
                H(vars,0x406)=0;
                I(vars,0x3FC)=func_00283CF0(func_002A7878(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                H(vars,0x400)=0;
            }
        }
        break;
    case 1:
        if(H(vars,0x404)==1 && I(vars,0x440)==0) {
            func_L17_003E3148(object);
            func_002A7750(object,10,2);
            if(B(object,0x43)!=2) func_002A7470(object,2,0,14);
        } else if(I(vars,0x3FC)==0) {
            func_002A7750(object,1,0);
            if(B(object,0x43)!=0) func_002A7470(object,0,0,12);
        }
        break;
    case 2:
        if(H(vars,0x404)!=1 && func_002A77E0(19)==0) {
            func_002A7750(object,2,1);
            I(vars,0x3FC)=func_00283CF0(func_002A7878(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
            H(vars,0x400)=0;
        }
        break;
    case 3:
        if(func_002B3890(object) && F(object,0x48)<0.0f) F(object,0x48)=1.0f;
        if(B(object,0x20)!=8) {
            flags=func_002B1C20(object,vars+0x60);
            if(flags&1) {
                H(vars,0x98)=0;
                if(H(object,0xB4)) func_002A6C58(object,0,3);
        else func_002A6C58(object,0x1000,3);
                func_L01_003E9CF8(object,0,0);
                return;
            }
            if(flags&2) {
                if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                    func_L17_003E3148(object);
                    func_002A7750(object,4,2);
                    if(B(object,0x43)!=9) func_002A7470(object,9,0,14);
                } else {
                    func_002A7750(object,2,1);
                    I(vars,0x3FC)=func_00283CF0(func_002A7878(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                    H(vars,0x400)=func_002A7820(120,700);
                }
            }
        }
        break;
    }
    if(F(object,0x18)-F(vars,0x3D8)>10.0f || F(object,0x18)<10.0f) {
        H(vars,0x98)=0;
        qzero_nc(object+0xF0);
        if(H(object,0xB4)) func_002A6C58(object,0,3);
        else func_002A6C58(object,0x1000,3);
        func_0029F338(object);
        return;
    }
    if(F(object,0x18)<75.0f && D_001A79F0==11) {
        H(vars,0x98)=0;
        qzero_nc(object+0xF0);
        if(H(object,0xB4)) func_002A6C58(object,0,3);
        else func_002A6C58(object,0x1000,3);
        func_0029F338(object);
        return;
    }
    switch(B(object,0x20)) {
    case 1:
        func_00282978((short *)(vars+0x400));
        if(B(object,0x43)==0 && H(vars,0x400)!=0) {
            if(B(object,0x43)!=9) func_002A7470(object,9,0,14);
        }
        if(H(vars,0x400)>20) func_002AA2E8((float *)(vars+0x124),D_L17_001B0CB0*(1.0f/60.0f),0.0019444445f);
        else func_002AA2E8((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            F(object,0x48)=0.8f;
            if(H(vars,0x400)==0) {
                if(B(object,0x43)!=func_002A77E0(2)) func_002A7470(object,func_002A77E0(2),0,12);
            }
            func_002AE8C0(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==0 || B(object,0x43)==1) && (B(object,0x60)&2)) {
            H(vars,0x400)=func_002A7820(120,500);
            if(B(object,0x43)!=9) func_002A7470(object,9,0,12);
        }
        break;
    case 2:
        func_00282978((short *)(vars+0x400));
        if(B(object,0x43)!=9 && B(object,0x43)!=5 && B(object,0x43)!=4) {
            if(B(object,0x43)!=9) func_002A7470(object,9,0,14);
        }
        if(H(vars,0x400)>20) func_002AA2E8((float *)(vars+0x124),D_L17_001B0CB4*(1.0f/60.0f),0.0019444445f);
        else func_002AA2E8((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            if(H(vars,0x400)==0) {
                func_002A7470(object,5,0,12);
                if(func_002A77E0(2)==1 && B(object,0x43)!=4) func_002A7470(object,4,0,12);
            }
            func_002AE8C0(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==4 || B(object,0x43)==5) && (B(object,0x60)&2)) {
            H(vars,0x400)=func_002A7820(120,200);
            if(B(object,0x43)!=9) func_002A7470(object,9,0,12);
        }
        goto restoreAnimationSpeed;
    case 10:
        if(B(object,0x60)&2) {
            func_002A7750(object,4,-1);
            if(B(object,0x43)!=9) func_002A7470(object,9,0,14);
        }
        func_002AA800((float *)(object+0xF8),0,func_00283248(D_00189E20.x-F(object,0x10),D_00189E20.y-F(object,0x14)),0.10471977f);
        break;
    case 4:
        if(func_002B3868(object)) I(vars,0x418)=func_002A7820(80,100);
        F(object,0x48)=1.0f;
        if(func_00282E80(object+0x10,P(vars,0x408)+0x10)<=D_L17_001B0CAC) {
            func_002A7750(object,5,2);
            if(B(object,0x43)!=6) func_002A7470(object,6,2,6);
            F(vars,0x414)=0;
        } else if(func_00282948((int *)(vars+0x418))) {
            /* The separate magnitude lets angle avoid crossing the side call, so its store
               schedules after the arguments of the timer call below. */
            {
                float magnitude=func_002A7878(0.26179942f,0.52359884f);
                int side=func_002A77E0(2);
                angle=magnitude;
                if(side==0) angle=-angle;
                F(vars,0x414)=angle;
            }
            I(vars,0x418)=func_002A7820(150,200);
            func_002A7750(object,5,2);
            if(B(object,0x43)!=6) func_002A7470(object,6,2,6);
        }
        break;
    case 5:
        if(B(object,0x42)==6) {
            if(func_002AEB60(object,8.0f)) func_002E5CF8(3,0,object);
            if(B(object,0x42)==6) {
                if(func_002AEB60(object,10.0f)) {
                    if(func_002A8C28(object,1.0f,object+0x10,0x4000001,F(vars,0x430),1.0f,0,1,0)>0) I(vars,0x448)=1;
                    else I(vars,0x448)=0;
                } else if(B(object,0x42)==6 && ((B(object,0x60)&2) || func_002AEB60(object,11.0f))) {
                    if(func_00282E80(object+0x10,P(vars,0x408)+0x10)>D_L17_001B0CAC) {
                        if((func_00282E80(object+0x10,P(vars,0x408)+0x10)==0.0f ? 1.0f : 0.0f)>D_L17_001B0CAC) {
                            if(func_002A7820(0,7)>0) {
                                func_002A7750(object,11,2);
                                if(B(object,0x43)!=7) func_002A7470(object,7,0,14);
                            }
                        } else {
                            func_002A7750(object,6,2);
                            if(B(object,0x43)!=9) func_002A7470(object,9,0,14);
                        }
                    }
                }
            }
        }
        break;
    case 11:
        if(B(object,0x60)&2) {
            func_002A7750(object,4,2);
            if(B(object,0x43)!=9) func_002A7470(object,9,0,0);
        }
        break;
    case 6:
        func_002B60B0(object,0.005f,0.10000001f,0.017453294f,1.0471977f);
        if(func_002B3868(object)) {
            func_00282CF0(vars+0x3E0,object+0x10,P(vars,0x408)+0x10);
            F(vars,0x3E8)=0;
            func_00282F20(vars+0x3E0,vars+0x3E0,10.0f);
            func_00282CC0(vars+0x3E0,vars+0x3E0,object+0x10);
            F(object,0x48)=-1.0f;
        }
        func_L02_00331440(object,vars+0x3E0,16,func_00283248(F(vars,0x3E0)-F(object,0x10),F(vars,0x3E4)-F(object,0x14)),-1.0f,-1.0f);
        if(B(object,0x42)==2 && (B(object,0x60)&2)) {
            if(B(object,0x43)!=9) func_002A7470(object,9,0,10);
            F(object,0x48)=1.0f;
        }
        if(B(object,0x42)==9 && (B(object,0x60)&2)) {
            if(I(vars,0x448)==0) {
                func_002A7750(object,4,2);
                if(B(object,0x43)!=9) func_002A7470(object,9,0,6);
            } else {
                func_002A7750(object,11,2);
                if(B(object,0x43)!=7) func_002A7470(object,7,0,14);
                I(vars,0x448)=0;
            }
restoreAnimationSpeed:
            F(object,0x48)=1.0f;
        }
        break;
    case 8:
        movement[0]=func_00283180(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[1]=func_00283198(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[2]=0;
        func_00282CD8(position,object+0x10,movement);
        if(func_00282E80(object+0x10,vars+0x3D0)>6.0f) func_002A7750(object,4,2);
        break;
    case 3:
        angle=func_00283B98(func_00283248(F(P(vars,0x408),0x10)-F(object,0x10),F(P(vars,0x408),0x14)-F(object,0x14)),F(vars,0x414));
        func_002A7CA0(object,angle,(float *)(vars+0x410),0.05f,0.3f,0.10471977f);
        if(B(object,0x60)&2) {
            func_002A7750(object,4,-1);
            if(B(object,0x43)!=9) func_002A7470(object,9,0,15);
        }
        break;
    case 9:
        if(func_L17_003E48E0(object)) {
            if(H(object,0xB4)) func_002A6C58(object,0,3);
        else func_002A6C58(object,0x1000,3);
            func_0029F338(object);
            return;
        }
        break;
    }
    if(B(object,0x20)!=8 && B(object,0x20)!=9 && B(object,0x20)!=6) func_L17_003E4560(object);
    func_L17_003E47E8(object);
}
