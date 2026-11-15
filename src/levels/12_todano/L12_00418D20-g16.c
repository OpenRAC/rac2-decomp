#include "common.h"
extern f32 D_L12_001B1C60[4] __attribute__((sda));
extern f32 D_L12_001B1C50[4] __attribute__((sda));

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern s32 func_00283CF0(f32);
extern s32 func_002A77E0(s32);
extern u8 *func_002BDCE8(void *, f32, f32, f32, f32, s32, void *, u32, s32);
void func_L12_00418D20(u8 *self)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    s32 i;
    u8 *p;
    u8 *origin=self+0x10;
    for(i=0;i<2;i++) {
        if(i==0) matrix_mul_vec3(offset,D_L12_001B1C50,self+0xC0);
        else matrix_mul_vec3(offset,D_L12_001B1C60,self+0xC0);
        qcopy(pos,origin);
        FastVecAdd(pos,pos,offset);
        velocity[0]=func_00283180(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.050000004f;
        velocity[1]=func_00283198(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.050000004f;
        velocity[2]=0.033333335f;
        p=SpawnSpinningSparkParticle(pos,0.1f,1.0f,0.9f,210000.0f,func_002A77E0(16),velocity,0xDF202020,0);
        if(p) {
            u8 *d=p+0x20;
            *(u16 *)(p+10)=10;
            p[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(d+4)=2;
            d[10]=0xDF;
            d[11]=p[10];
            p[3]=0x44;
        }
        velocity[0]=func_00283180(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.050000004f;
        velocity[1]=func_00283198(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.050000004f;
        velocity[2]=0.033333335f;
        p=SpawnSpinningSparkParticle(pos,0.1f,1.0f,0.9f,210000.0f,func_002A77E0(16),velocity,0xDF208080,0);
        if(p) {
            u8 *d=p+0x20;
            *(u16 *)(p+10)=10;
            p[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(d+4)=2;
            d[10]=0xDF;
            d[11]=p[10];
            p[3]=0x48;
        }
        velocity[0]=func_00283180(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.016666668f;
        velocity[1]=func_00283198(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.016666668f;
        velocity[2]=0.033333335f;
        p=SpawnSpinningSparkParticle(pos,0.1f,1.0f,0.9f,210000.0f,func_002A77E0(16),velocity,0xDF808080,0);
        if(p) {
            u8 *d=p+0x20;
            *(u16 *)(p+10)=10;
            p[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(d+4)=2;
            d[10]=0xDF;
            d[11]=p[10];
            p[3]=0x44;
        }
    }
}
