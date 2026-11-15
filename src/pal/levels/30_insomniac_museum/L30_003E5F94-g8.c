#include "include_asm.h"

#include "common.h"
extern char D_L30_001B3AE0[] __attribute__((sda)), D_L30_001B3AF0[] __attribute__((sda)), g_hero_position[];
extern float D_L30_001B3B20[] __attribute__((sda));
extern float D_L30_001B0B78 __attribute__((sda));
extern float D_L30_001B0B7C __attribute__((sda));
extern float D_L30_001B0B80 __attribute__((sda));
extern float D_L30_001B0BB0 __attribute__((sda));
extern float D_L30_001B0BBC __attribute__((sda));
extern float D_L30_001B0BC0 __attribute__((sda));
extern float D_L30_001B0BC4 __attribute__((sda));
extern int D_L30_001B0BB4 __attribute__((sda));
extern int D_L30_001B0BB8 __attribute__((sda));
extern char D_L30_001B0B90[16] __attribute__((sda)), D_L30_001B0BA0[16] __attribute__((sda));
extern void moby_set_state(void *,int,int);
extern int func_PAL_00273A10(void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void vec_clear_128(void *),vec_copy_helper_a(void *),FastVecSub(void *,void *,void *),FastVecCross(void *,void *,void *),matrix_mul_vec3(void *,void *,void *),FastVecAdd(void *,void *,void *),euler_rotation_basis(void *,void *);
extern void vec_fast_normalize_helper(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void func_PAL_L00_00328480(void *,void *,float,int,int,void *,unsigned,int,float,float,float);
extern void func_PAL_00273818(void *,int,int,void *,void *,int,float);

void func_PAL_L30_003E5F94(unsigned char *obj) {
    struct { float v[4], axis[4], up[4], pos[4]; } f;
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; moby_set_state(obj,1,-1);
        *(unsigned short *)(obj+0x34)|=0x100;
        qcopy(D_L30_001B3AE0,obj+0x10); qcopy(D_L30_001B3AF0,obj+0xF0);
        vec_clear_128(D_L30_001B3B20); D_L30_001B3B20[2]=0.4f;
        break;
    case 1:
        if(part_find_owned_effect_slot(obj,0x10000,0)) {
            float frameTime=0.020000001f;
            float angleScale;
            FastVecSub(f.v,obj+0x10,g_hero_position);
            angleScale=0.0003490659f;
            vec_fast_normalize_helper(f.v,f.v,D_L30_001B0B78*frameTime);
            f.v[2]=D_L30_001B0B7C*frameTime;
            vec_copy_helper_a(f.up);
            FastVecCross(f.axis,f.v,f.up);
            vec_scale_to_length(f.axis,f.axis,math_fast_sin_or_cos_b(-D_L30_001B0B80*angleScale));
            f.axis[3]=math_fast_sin_or_cos_a(D_L30_001B0B80*angleScale);
            matrix_mul_vec3(f.pos,D_L30_001B0B90,obj+0xC0);
            FastVecAdd(f.pos,f.pos,obj+0x10);
            func_PAL_L00_00328480(obj,f.pos,D_L30_001B0BB0,D_L30_001B0BB4,D_L30_001B0BB8,D_L30_001B0BA0,0x50404040,0,D_L30_001B0BBC,D_L30_001B0BC0,D_L30_001B0BC4);
            func_PAL_00273818(obj,0,-1,f.v,f.axis,255,15.0f);
            *(int *)(obj+0x98)=0; moby_set_state(obj,2,-1);
        }
        break;
    case 2: if(func_PAL_00273A10(obj)) moby_set_state(obj,3,-1); break;
    case 3:
        if(obj[0x23]<2) {
            qcopy(obj+0x10,D_L30_001B3AE0); euler_rotation_basis(obj+0xC0,D_L30_001B3AF0);
            obj[0x23]=128; *(int *)(obj+0x98)=*(int *)(*(char **)(obj+0x24)+0x10); moby_set_state(obj,1,-1);
        } else obj[0x23]-=2;
        break;
    }
    obj[0xA8]=255;
}
