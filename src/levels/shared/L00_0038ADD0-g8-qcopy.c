/* Twin beam strips: two 144-byte strip records (four points, colours, UVs and GS words)
   set up around a basis built from the start, end and a fixed up vector. Store order
   follows retail; the record is a struct view. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283C80(float,float);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(float *,float,float,float);
extern char *func_002C2210(void *,int,unsigned int,int,int,void *,int,float,float,float);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *,void *);
extern void func_002A7398(signed char *,int,int);
extern void func_002AEC18(void *,int);
extern void func_002833F0(void *,void *);
extern void func_002FE8D8(void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00283198(float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern void func_00282C88(void *);
extern int func_002FEC78(unsigned char *,unsigned int);
extern int func_002FED90(void *,void *,float,float,float);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern void func_00283098(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern int func_002A7820(int,int);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern void func_L00_003883B8(char *);
extern void func_L00_0038AA40(char *);
extern void func_L00_00388490(void *,Vector4 *);
extern void func_L00_0038AAD0(void *,Vector4 *);
extern void func_0029FCC0(char *,int,char *);
extern int func_001163B0(void);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282E48(void *,void *);
extern Vector4 D_001B8DC0;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;
void func_L00_0038ADD0(char *object)
{
    Beam first,second;
    Vector4 basis[4],start,end,origin,nearSize,farSize;
    char *work=FIELD(char *,object,0x68);
    float width;
    func_0029FCC0(object,1,(char *)&origin);
    start.bits=origin.bits;
    vec_scale_to_length(&end,work+0x30,func_002A7878(2,4));
    matrix_mul_vec3(&end,&end,object+0xC0);
    FastVecAdd(&end,&end,&origin);
    func_L00_0038AAD0(object,&start);
    first.tex=GetEffectTextureDescriptor(23);
    first.tag=0;
    first.alpha=0xFF9000000260UL;
    first.color[0]=first.color[1]=0x7F103080;
    first.test=0x8000000048UL;
    first.color[2]=first.color[3]=0x103080;
    second.tex=GetEffectTextureDescriptor(23);
    nearSize.bits=0;
    farSize.bits=0;
    second.test=0x8000000048UL;
    second.tag=0;
    second.color[2]=second.color[3]=0x103080;
    second.color[0]=second.color[1]=0x3F103080;
    nearSize.f[3]=1;
    farSize.f[3]=1;
    second.alpha=0xFF9000000260UL;
    width=func_002A7878(0.1f,0.3f);nearSize.f[2]=width;farSize.f[2]=width+width;
    func_L00_0038AA40((char *)&first);func_L00_0038AA40((char *)&second);
    if(!(func_001163B0()&1)) {
        first.uv[0]=0;first.uv[1]=0;first.uv[2]=0;first.uv[3]=1;
        first.uv[4]=1;first.uv[5]=0;first.uv[6]=1;first.uv[7]=1;
        second.uv[0]=0;second.uv[1]=0;second.uv[2]=0;second.uv[3]=1;
        second.uv[4]=1;second.uv[5]=0;second.uv[6]=1;second.uv[7]=1;
    } else {
        first.uv[0]=0;first.uv[1]=1;first.uv[2]=0;first.uv[3]=0;
        first.uv[4]=1;first.uv[5]=1;first.uv[6]=1;first.uv[7]=0;
        second.uv[0]=0;second.uv[1]=1;second.uv[2]=0;second.uv[3]=0;
        second.uv[4]=1;second.uv[5]=1;second.uv[6]=1;second.uv[7]=0;
    }
    FastVecSub(&basis[0],&end,&start);vec_scale_to_length(&basis[0],&basis[0],1);
    FastVecSub(&basis[1],&D_001B8DC0,&start);FastVecCross(&basis[2],&basis[1],&basis[0]);
    vec_scale_to_length(&basis[2],&basis[2],1);FastVecCross(&basis[1],&basis[0],&basis[2]);
    basis[3].bits=start.bits;
    first.point[0].bits=nearSize.bits;second.point[0].bits=farSize.bits;
    FastVecScale(&first.point[1],&first,-1);FastVecScale(&second.point[1],&second,-1);
    transform_vector(&first,&first,basis);transform_vector(&first.point[1],&first.point[1],basis);
    transform_vector(&second,&second,basis);transform_vector(&second.point[1],&second.point[1],basis);
    basis[3].bits=end.bits; nearSize.f[2]*=0.15f;farSize.f[2]=nearSize.f[2]+nearSize.f[2];
    first.point[2].bits=nearSize.bits;second.point[2].bits=farSize.bits;
    FastVecScale(&first.point[3],&first.point[2],-1);FastVecScale(&second.point[3],&second.point[2],-1);
    transform_vector(&first.point[2],&first.point[2],basis);transform_vector(&first.point[3],&first.point[3],basis);
    transform_vector(&second.point[2],&second.point[2],basis);transform_vector(&second.point[3],&second.point[3],basis);
    draw_world_quad(&first,0,0);draw_world_quad(&second,0,0);
}
