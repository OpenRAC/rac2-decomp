#include "common.h"
extern int D_L11_001A8FF4 __attribute__((sda));
extern char D_L11_001BA8C0[];
extern int func_00283CF0(float);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void func_L11_00436A78(char *);
extern char *func_002A9640(char *,int,int);
extern char *func_L11_004417E8(int);
extern void func_00282CF0(float *,const float *,const float *);
extern void func_00282F20(char *,char *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern int func_002B0ED8(char *,char *,int);
extern void func_L11_00436850(char *);
extern void func_00283698(void *,void *);
extern void func_002AFFD8(void *,void *,int);
extern int func_L11_004461C0(int,void *);
extern void func_002A7750(void *,int,int);
extern float func_L00_002EE290(void *);
extern void func_00282CC0(char *,char *,char *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(char *);
#define F(p,t,o) (*(t *)((char *)(p)+(o)))
/* Initializes the object, adjusts hit velocity, and keeps active movement near its target. */
void func_L11_00436350(char *p) {
    char *s=F(p,char *,0x68), *hit;
    float v[4], angle, z;
    if (F(p,unsigned char,0x20)==0) {
        F(s,unsigned char,0x48)=FloatToInt(15.0f);
        F(s,unsigned char,0x4A)=FloatToInt(4.0f);
        F(s,unsigned char,0x29)=1;
        F(s,char *,0x18)=s+0x100;
        angle=func_002A7878(15.0f,40.0f)*0.017453294f;
        if(func_002A77E0(2)) angle=-angle;
        F(s,float,0x274)=angle;
        if(func_002A77E0(2)==1) F(p,unsigned short,0x34)|=0x8000;
        F(s,short,0x282)=0;
        F(s,unsigned char,0x60)=10;
        F(s,int,0x98)=4;
        F(s,float,0x84)=0.65f;
        F(s,float,0x80)=0.6f;
        F(s,float,0x100)=0.6f;
        F(s,float,0x104)=0.05f;
        F(s,float,0x8C)=0.4f;
        F(s,float,0x108)=0.4f;
        F(s,float,0x10C)=0.4f;
        F(s,float,0x134)=0.01f;
        F(s,float,0x110)=1.5707964897155762f;
        F(s,float,0x130)=0.523598849773407f;
        F(s,float,0x12C)=0.0027777778450399637f;
        F(s,unsigned char,0x28)=3;
        func_L11_00436A78(p);
    }
    if(F(p,unsigned char,0x95)>=2) {
        hit=func_002A9640(p,0x10000,1);
        if(hit) {
            char *other=F(hit,char *,0x20);
            if(other && !F(p,unsigned char,0x31) &&
            (F(other,short,0xAA)==0xA03 || F(other,short,0xAA)==0xB89)) F(hit,int,0x2C)=0;
            if(F(s,short,0x286)) {
                char *velocity=hit+0x10;
                FastVecSub(v,(float *)func_L11_004417E8(F(p,int,0xB8)),(float *)(p+0x10));
                v[2]=0;
                vec_scale_to_length((char *)v,(char *)v,1.0f);
                vec_scale_to_length((char *)v,(char *)v,FastVecDot(velocity,v));
                angle=FastVecLength(velocity);
                FastVecSub((float *)velocity,(float *)velocity,v);
                vec_scale_to_length(velocity,velocity,angle);
            }
        }
        if(func_002B0ED8(p,s+0x50,0)==5) {
            F(s,int,0xE0)=0;
            F(s,float,0xE4)=0.8377581834793091f;
        }
        func_L11_00436850(p);
        if(F(s,short,0x286)) {
            matrix_from_basis_rows(s+0x210,p+0xC0);
            func_002AFFD8(p+0x10,s+0x240,0);
            if(!func_L11_004461C0(F(p,int,0xB8),p+0x10)) {
                F(s,int,0x20)=0;
                func_002A7750(p,11,4);
            }
            if(F(p,unsigned char,0x20)!=11) {
                z=F(p,float,0x18);
                FastVecSub(v,(float *)(p+0x10),(float *)func_L11_004417E8(F(p,int,0xB8)));
                v[2]=0;
                if(func_L00_002EE290(v)>225.0f) {
                    vec_scale_to_length((char *)v,(char *)v,15.0f);
                    FastVecAdd(p+0x10,(char *)v,func_L11_004417E8(F(p,int,0xB8)));
                    F(p,float,0x18)=z;
                }
            }
        }
    }
    if(!F(s,short,0x286) && F(p,unsigned char,0x20)!=11 && !D_L11_001A8FF4) {
        F(p,unsigned short,0x34)|=0x400;
        if(F(p,unsigned char,0x31) && fast_vec_dist(p+0x10,D_L11_001BA8C0)<24.0f) {
            func_002A93B0(p);
            F(p,unsigned char,0x6F)=22;
        }
    } else F(p,unsigned short,0x34)&=0xFBFF;
    if(F(p,unsigned char,0x20)>=2 && F(s,unsigned char,0x2E)==2) func_L11_00436A78(p);
}
