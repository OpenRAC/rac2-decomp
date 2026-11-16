#include "include_asm.h"

#include "common.h"
extern f32 g_driver_spark_offset_b[4] __attribute__((sda));
extern f32 g_driver_spark_offset_a[4] __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FloatToInt(f32);
extern s32 math_random_int_below(s32);
extern u8 *part_spawn_spinning_spark_pal(void *, f32, f32, f32, f32, s32, void *, u32, s32);

/* Spawns three sparks (two coloured, one white) from each of the driver's two spark points,
   thrown out behind it. */
void part_spawn_driver_spark_bursts_pal(u8 *self)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    s32 i;
    u8 *particle;
    u8 *origin=self+0x10;
    for(i=0;i<2;i++) {
        if(i==0) matrix_mul_vec3(offset,g_driver_spark_offset_a,self+0xC0);
        else matrix_mul_vec3(offset,g_driver_spark_offset_b,self+0xC0);
        qcopy(pos,origin);
        FastVecAdd(pos,pos,offset);
        velocity[0]=math_fast_sin_or_cos_a(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.060000002f;
        velocity[1]=math_fast_sin_or_cos_b(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.060000002f;
        velocity[2]=0.040000003f;
        particle=part_spawn_spinning_spark_pal(pos,0.1f,1.0f,0.9f,210000.0f,math_random_int_below(16),velocity,0xDF202020,0);
        if(particle) {
            u8 *data=particle+0x20;
            *(u16 *)(particle+10)=8;
            particle[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(data+4)=2;
            data[10]=0xDF;
            data[11]=particle[10];
            particle[3]=0x44;
        }
        velocity[0]=math_fast_sin_or_cos_a(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.060000002f;
        velocity[1]=math_fast_sin_or_cos_b(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.060000002f;
        velocity[2]=0.040000003f;
        particle=part_spawn_spinning_spark_pal(pos,0.1f,1.0f,0.9f,210000.0f,math_random_int_below(16),velocity,0xDF208080,0);
        if(particle) {
            u8 *data=particle+0x20;
            *(u16 *)(particle+10)=8;
            particle[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(data+4)=2;
            data[10]=0xDF;
            data[11]=particle[10];
            particle[3]=0x48;
        }
        velocity[0]=math_fast_sin_or_cos_a(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.020000001f;
        velocity[1]=math_fast_sin_or_cos_b(FastAddRotations(*(f32 *)(self+0xF8),3.141593f))*0.020000001f;
        velocity[2]=0.040000003f;
        particle=part_spawn_spinning_spark_pal(pos,0.1f,1.0f,0.9f,210000.0f,math_random_int_below(16),velocity,0xDF808080,0);
        if(particle) {
            u8 *data=particle+0x20;
            *(u16 *)(particle+10)=8;
            particle[9]=FloatToInt(4.0f)+0x70;
            *(s32 *)(data+4)=2;
            data[10]=0xDF;
            data[11]=particle[10];
            particle[3]=0x44;
        }
    }
}
