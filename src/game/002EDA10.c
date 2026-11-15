#include "common.h"
typedef int QuadEDA __attribute__((mode(TI)));
typedef union VecEDA { QuadEDA q; float f[4]; } VecEDA;
extern unsigned char *D_001B5390;
extern int func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern void func_002ED6B0(unsigned char *);
extern void func_002EE6E0(unsigned char *);
extern void func_002EE238(unsigned char *);
extern void func_002EE610(unsigned char *);
extern void func_002EE000(unsigned char *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern void func_002EE920(unsigned char *,void *);
extern int func_002EEB00(unsigned char *);
extern int func_002ED948(unsigned char *);
extern void func_002EE678(unsigned char *,int);
extern int func_001163B0(void);
extern float func_002A7878(float,float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283B98(float,float);
extern int func_00283DB8(void *,float);
extern int func_002A7820(int,int);
extern void func_002ED9C0(unsigned char *);
extern void func_002EE7B8(unsigned char *);
extern void func_002EE8B0(unsigned char *);
#define IEDA(p,o) (*(int *)((p)+(o)))
#define FEDA(p,o) (*(float *)((p)+(o)))
#define PEDA(p,o) (*(unsigned char **)((p)+(o)))
void func_002EDA10(unsigned char *owner)
{
    VecEDA v, extra, frame[3], zero, up, basis[3], test, rotated;
    unsigned char *d = (unsigned char *)func_002ED688(owner);
    unsigned char *cam;
    unsigned char *target;
    float sign;
    if (!d) return;
    zero.q = 0;
    up.q = 0;
    zero.f[2] = 1.0f;
    up.f[0] = 1.0f;
    qcopy(d+0xB0,owner+0x10);
    if (func_002EE6A8(owner) != 8)
        FastVecAdd(owner+0x10,d+0x90,owner+0x10);
    func_002ED6B0(owner);
    func_002EE6E0(owner);
    func_002EE238(owner);
    func_002EE610(owner);
    UpdateBankedOrientation(owner);
    cam = D_001B5390;
    switch(func_002EE6A8(owner)) {
    case 7:
        vec_scale_to_length(&v,PEDA(d,0x120)+0xC0,-50.0f);
        FastVecAdd(&v,PEDA(d,0x120)+0x10,&v);
        func_002EE920(owner,&v);
        if(func_002EEB00(owner)) {
            func_002EE678(owner,8);
            IEDA(d,0x130)=900;
            sign = (func_001163B0()&1) ? -1.0f : 1.0f;
            FEDA(d,0x140)=sign;
            FEDA(d,0x134)=sign < 0.0f ? 1.5707964f : -1.5707964f;
            FEDA(d,0x144)=func_002A7878(5.0f,15.0f);
        }
        break;
    case 8:
        v.f[2]=0.0f;
        v.f[0]=func_00283198(FEDA(d,0x134))*FEDA(d,0x144);
        v.f[1]=-func_00283180(FEDA(d,0x134))*FEDA(d,0x144);
        v.f[3]=0.0f;
        FEDA(d,0x134)=FastAddRotations(FEDA(d,0x134),FEDA(d,0x140)*0.013089972f);
        qcopy(&basis[2],cam+0x20);
        FastVecCross(&basis[1],&up,&basis[2]);
        vec_scale_to_length(&basis[1],&basis[1],1.0f);
        FastVecCross(&basis[0],&basis[2],&basis[1]);
        matrix_mul_vec3(&v,&v,&basis[0]);
        FastVecAdd(owner+0x10,PEDA(d,0x120)+0x10,&v);
        func_002EE920(owner,&v);
        if(func_002ED948(owner)) func_002EE678(owner,9);
        if(!func_002EEB00(owner)) break;
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(func_00283DB8(&test,256.0f)==-1) {
            func_002ED9C0(owner);
            func_002EE678(owner,1);
        }
        break;
    case 9:
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(func_00283DB8(&test,256.0f)==-1) {
            func_002ED9C0(owner);
            func_002EE678(owner,1);
        }
        break;
    case 4:
        if (!PEDA(d,0x120)) { func_002ED9C0(owner); func_002EE678(owner,1); break; }
        vec_scale_to_length(&v,PEDA(d,0x120)+0xC0,25.0f);
        if (IEDA(d,0xFC)) {
            matrix_mul_vec3(&rotated,d+0x70,PEDA(d,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,PEDA(d,0x120)+0x10,&v);
        func_002EE920(owner,&v);
        if (func_002EEB00(owner)) {
            func_002EE678(owner,5);
            IEDA(d,0x130)=func_002A7820(300,600);
        }
        break;
    case 5:
        if (!PEDA(d,0x120)) { func_002ED9C0(owner); func_002EE678(owner,1); break; }
        vec_scale_to_length(&v,PEDA(d,0x120)+0xC0,5.0f);
        if (IEDA(d,0xFC)) {
            matrix_mul_vec3(&rotated,d+0x70,PEDA(d,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,PEDA(d,0x120)+0x10,&v);
        func_002EE920(owner,&v);
        if(func_002EEB00(owner)) { func_002ED9C0(owner); func_002EE678(owner,1); }
        break;
    case 6:
        if (!PEDA(d,0x120)) { func_002ED9C0(owner); func_002EE678(owner,1); break; }
        vec_scale_to_length(&v,PEDA(d,0x120)+0xC0,10.0f);
        vec_scale_to_length(&extra,PEDA(d,0x120)+0xE0,0.05f);
        if (IEDA(d,0xFC)) {
            matrix_mul_vec3(&rotated,d+0x70,PEDA(d,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,&extra,&v);
        FastVecAdd(&v,PEDA(d,0x120)+0x10,&v);
        func_002EE920(owner,&v);
        if(func_002EEB00(owner)) { func_002ED9C0(owner); func_002EE678(owner,1); }
        break;
    case 3:
        target=PEDA(d,0x10);
        qcopy(&frame[0],target+0xC0);
        FastVecCross(&frame[1],&frame[0],&zero);
        vec_scale_to_length(&frame[1],&frame[1],1.0f);
        FastVecCross(&frame[2],&frame[1],&frame[0]);
        matrix_mul_vec3(&v,d,&frame[0]);
        FastVecAdd(&v,target+0x10,&v);
        func_002EE920(owner,&v);
        break;
    case 1:
        if(func_002EEB00(owner)) func_002EE7B8(owner);
        break;
    case 13:
        if(func_002EEB00(owner)) func_002EE8B0(owner);
        break;
    }
}
