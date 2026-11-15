#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int g_hovering_object_count MACRO_ADDR;
extern float ref_L02_0043F4C8_1[] __attribute__((sda));
extern float ref_L02_0043F4C8_2[] __attribute__((sda));
extern float ref_L02_0043F4C8_3 __attribute__((sda));
extern float ref_L02_0043F4C8_4 __attribute__((sda));
extern float ref_L02_0043F4C8_5 __attribute__((sda));
extern u8 g_hero_state[];
extern u8 D_L02_001A8F20[] MACRO_ADDR;
extern float math_random_angle(void);
extern float math_random_signed_float_range(float,float);
extern int math_random_int_below(int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void moby_set_state(void *,int,int);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_b(float);
extern void euler_rotation_basis(void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_point_inside_record_volume(void *,int);
extern u8 *part_find_owned_effect_slot(void *,u32,int);
extern int math_random_int_range(int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern float math_fast_float_e(float,float,float);
extern int CollLine(void *,void *,int,void *,int);
extern int flag_set_first_pending(void *);
extern int PlayMobySound(int,int,char *);
extern void func_PAL_L01_002E2968(void *,void *,int,int,int,float,float,float);
extern int FastDecTimer(short *);
extern void vec_clear_128(void *);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_PAL_002B15D8(char *,int,float *,u8,float,float,float,float);
extern void func_PAL_L00_003281C0(void *,int,float);
extern void moby_mark_spawned(void *);
extern void func_PAL_L02_00445550(void *);

/* Advance the hovering object's idle, launch and impact states. */
void func_PAL_L02_00444F60(u8 *object)
{
    Vector delta;
    /* The tilt input dies after 833F0. The later inverse has four rows. */
    union {
        struct { Vector angles; Vector rotation[3]; } tilt;
        Vector inverse[4];
    } workspace;
    Vector destination;
    u8 *effect=*(u8 **)(object+0x68);
    u8 *hit;
    int mode;
    switch(object[0x20]) {
    case 0:
        if(*(int *)(effect+0x40)) g_hovering_object_count=g_hovering_object_count-1;
        qcopy(effect,object+0x10);
        *(float *)(effect+0x10)=math_random_angle();
        *(float *)(effect+0x14)=math_random_angle();
        *(float *)(effect+0x18)=math_random_signed_float_range(ref_L02_0043F4C8_1[0],ref_L02_0043F4C8_1[1])*0.0003490659f;
        *(float *)(effect+0x1C)=math_random_signed_float_range(ref_L02_0043F4C8_2[0],ref_L02_0043F4C8_2[1])*0.0003490659f;
        *(int *)(effect+0x40)=0;
        *(float *)(effect+0x4C)=0.12566373f;
        object[0x40]=math_random_int_below((*(u8 **)(*(u8 **)(object+0x24)+0x48))[0x10]);
        *(short *)(effect+0x48)=180;
        mode=math_random_int_below(2)+1;
        if(object[0x43]!=mode) func_PAL_002A7E68(object,mode,0,5);
        moby_set_state(object,1,-1);
        break;
    case 1: {
        if(object[0x31]) {
            u8 *position=object+0x10;
            *(float *)(effect+0x10)=FastAddRotations(*(float *)(effect+0x10),*(float *)(effect+0x18));
            *(float *)(effect+0x14)=FastAddRotations(*(float *)(effect+0x14),*(float *)(effect+0x1C));
            *(float *)(object+0xF0)=ref_L02_0043F4C8_3*math_fast_sin_or_cos_b(*(float *)(effect+0x10));
            *(float *)(object+0xF4)=ref_L02_0043F4C8_4*math_fast_sin_or_cos_b(*(float *)(effect+0x14));
            workspace.tilt.angles.q=0;
            workspace.tilt.angles.f[0]=*(float *)(effect+0x10);
            workspace.tilt.angles.f[2]=*(float *)(effect+0x14);
            delta.q=workspace.tilt.angles.q;
            euler_rotation_basis(workspace.tilt.rotation,&delta);
            FastVecScale(position,&workspace.tilt.rotation[1],ref_L02_0043F4C8_5);
            FastVecAdd(position,position,effect);
        }
        if(*(short *)(effect+0x3E)) {
            u8 *player=g_hero_state; if(*(u8 **)(player+0x33C)==object && *(int *)(player+0x340)) *(short *)(effect+0x3E)=2;
            if(*(short *)(effect+0x3E)==2) {
                *(float *)(effect+8)-=0.080000006f;
                if(*(int *)(effect+0x50) && coll_point_inside_record_volume(object+0x10,*(int *)(effect+0x50))) moby_set_state(object,3,-1);
            }
        }
        if(*(int *)(effect+0x40)) break;
        hit=part_find_owned_effect_slot(object,0x4210000,0);
        if(!hit) break;
        {
        g_hovering_object_count--;
        *(short *)(effect+0x4A)=((s32)(math_random_int_range(30,60)) * 5 + 2) / 6;
        qcopy(effect+0x20,hit+0x10);
        vec_scale_to_length(effect+0x20,effect+0x20,0.3f);
        FastVecSub(&delta,hit,object+0x10);
        matrix_from_basis_rows(workspace.inverse,object+0xC0);
        transform_vector(&delta,&delta,workspace.inverse);
        *(float *)(effect+0x30)=-(math_fast_float_e(delta.f[2],-1.0f,1.0f)*0.08377582f);
        *(float *)(effect+0x34)=math_fast_float_e(delta.f[1],-1.0f,1.0f)*0.062831864f;
        FastVecScale(&destination,effect+0x20,(float)*(short *)(effect+0x4A));
        FastVecAdd(&destination,object+0x10,&destination);
        if(CollLine(object+0x10,&destination,2,0,0)) *(short *)(effect+0x3C)=1;
        if(*(short *)(effect+0x3C)) moby_set_state(object,3,-1);
        else moby_set_state(object,2,-1);
        }
        break;
    }
    case 2:
        if(flag_set_first_pending(object)) PlayMobySound(0,0,object);
        delta.q=0; workspace.tilt.angles.q=0;
        delta.f[2]=0.080000006f;
        workspace.tilt.angles.f[2]=-0.5f;
        FastVecAdd(&workspace.tilt.angles,&workspace.tilt.angles,object+0x10);
        if(!math_random_int_below(2)) func_PAL_L01_002E2968(&workspace.tilt.angles,&delta,1,0x40F0F0F0,1,0.008f,0.9f,1.04f);
        *(float *)(object+0xF4)=FastAddRotations(*(float *)(object+0xF4),*(float *)(effect+0x30));
        *(float *)(object+0xF8)=FastAddRotations(*(float *)(object+0xF8),*(float *)(effect+0x34));
        FastVecAdd(object+0x10,object+0x10,effect+0x20);
        if(FastDecTimer((short *)(effect+0x4A))) moby_set_state(object,3,-1);
        break;
    case 3:
        if(*(short *)(effect+0x3C)) vec_clear_128(effect+0x20);
        func_PAL_002AC718(object,D_L02_001A8F20,object+0x10,0.0f,0.0f,10,5,15,0.0f,0.0f,9.0f,*(float *)(object+0x2C)*10.0f,-1,0.0f,0,0,-1,0,0x810001);
        func_PAL_002B15D8((char *)object,0x3FFF,(float *)(effect+0x20),255,3.0f,6.0f,3.0f,6.0f);
        func_PAL_L00_003281C0(object,3,0.0f);
        PlayMobySound(1,0,object);
        moby_mark_spawned(object);
        return;
    }
    if(object[0x20]) func_PAL_L02_00445550(object);
}
