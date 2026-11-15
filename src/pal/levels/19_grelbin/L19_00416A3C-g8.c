/* func_PAL_L19_00416A3C, the PAL copy of func_L19_00411890: the same C, where 1.0f/12.0f becomes
 * 0.10000001f, the duration F(state,0x84) is scaled to 50 Hz, and three callees take their
 * func_PAL_ names. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define B(p,o) (*((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
/* A rotation component written through its int/float union: such a store may alias any later load. */
typedef union { int i; float f; } Word;
#define R(p,o) (((Word *)((u8 *)(p)+(o)))->f)
extern int g_current_map_index;
extern u8 D_0019B2E8[], g_hero_position[];
typedef struct { u8 prefix[0x464]; u8 flags[0]; } FlagTable;
extern FlagTable D_L19_0021EA30;
typedef struct { u8 prefix[0x30]; float position[4]; u8 middle[0x30]; float rotation[4]; } Transform;
extern Transform *D_L19_001B2B0C MACRO_ADDR;
extern u8 *g_moby_l19_array;
extern int D_L19_001B9D00 NOT_SDA;
extern void moby_set_state(void *,int,int);
extern int coll_point_inside_region(void *,int);
extern void moby_mark_spawned(void *);
extern int flag_is_third_pending_set(void *),flag_set_first_pending(void *);
extern void moby_mark_table_entry_flagged(int);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float);
extern void func_PAL_002AC718(void *,void *,void *,float,float,float,float,float,int,int,int,int,int,int,int,int,int,float,float);
extern void func_PAL_002B15D8(void *,int,float,float,float,float,void *,int);
extern int PlayMobySound(int,int,void *);
extern float math_fast_sin_or_cos_a(float),math_move_angle_toward_target(float,float,float);
extern void func_PAL_L18_002CFE30(int),mat_combine_and_store(void *,void *,void *,void *);
void func_PAL_L19_00416A3C(u8 *obj)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    float t;
    *(TI128 *)oldpos = *(TI128 *)(obj+0x10);
    *(TI128 *)oldrot = *(TI128 *)(obj+0xF0);
    switch (B(obj,0x20)) {
    case 0:
        if (I(state,0x80)==-1) {
            H(obj,0x34)|=2;
            moby_set_state(obj,4,-1);
            return;
        }
        I(state,0x88)=0;
        I(state,0x5C)|=1;
        *(TI128 *)(state+0x60) = *(TI128 *)(obj+0x10);
        *(TI128 *)(state+0x70) = *(TI128 *)(obj+0xF0);
        if (D_L19_0021EA30.flags[I(state,0x8C)] ||
            (B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+g_current_map_index*16]&128)) ||
            (I(state,0x98)!=-1 && coll_point_inside_region(g_hero_position,I(state,0x98)))) {
            qcopy_nc(obj+0x10,D_L19_001B2B0C[I(state,0x80)].position);
            qcopy_nc(obj+0xF0,D_L19_001B2B0C[I(state,0x80)].rotation);
            H(obj,0x34)|=2;
            if (!B(state,0x91)) { moby_mark_spawned(obj); return; }
            moby_set_state(obj,3,-1);
        } else moby_set_state(obj,1,-1);
        break;
    case 1:
        if (!B(obj,0xBC) && !flag_is_third_pending_set(obj) && I(state,0x8C)!=-1 &&
            B(g_moby_l19_array+I(state,0x8C)*256,0x20)!=254 &&
            B(g_moby_l19_array+I(state,0x8C)*256,0x20)!=253 &&
            !(B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+g_current_map_index*16]&128)) &&
            (I(state,0x98)==-1 || !coll_point_inside_region(g_hero_position,I(state,0x98)))) goto effects;
        if (I(state,0x94)!=-1) B(g_moby_l19_array+I(state,0x94)*256,0xBC)=1;
        if (B(state,0x93)) moby_mark_table_entry_flagged(B(obj,0xB0));
        moby_set_state(obj,2,-1);
    effects:
        if (!B(state,0x91) && part_find_owned_effect_slot(obj,0x40000,0)) {
            if (I(state,0x94)!=-1) B(g_moby_l19_array+I(state,0x94)*256,0xBC)=1;
            FastVecAdd(delta,obj+0xD0,obj+0xE0);
            vec_scale_to_length(delta,delta,0.10000001f);
            FastVecAdd(offset,obj+0x10,obj+0xE0);
            func_PAL_002AC718(obj,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            func_PAL_002B15D8(obj,31,3,6,3,6,delta,255);
            H(obj,0x34)|=1;
            B(obj,0x31)=0;
            I(obj,0x98)=0;
            if (*(s16 *)(obj+0xAA)==0x10ED) PlayMobySound(0,0,obj);
            if (B(state,0x93)) moby_mark_table_entry_flagged(B(obj,0xB0));
            moby_set_state(obj,2,-1);
        }
        B(obj,0xA8)=255;
        break;
    case 2:
        if (flag_set_first_pending(obj) && (*(s16 *)(obj+0xAA)==0xEDB || *(s16 *)(obj+0xAA)==0x1146)) PlayMobySound(0,0,obj);
        F(state,0x88)+=1.0f/((F(state,0x84)*5.0f+2.0f)*0.16666667f);
        if (F(state,0x88)>1) F(state,0x88)=1;
        t=1.0f-math_fast_sin_or_cos_a(F(state,0x88)*3.1415927f);
        t*=0.5f;
        FastVecSub(delta,D_L19_001B2B0C[I(state,0x80)].position,state+0x60);
        FastVecScale(delta,delta,t);
        FastVecAdd(obj+0x10,state+0x60,delta);
        R(obj,0xF8)=math_move_angle_toward_target(F(state,0x78),D_L19_001B2B0C[I(state,0x80)].rotation[2],t);
        R(obj,0xF4)=math_move_angle_toward_target(F(state,0x74),D_L19_001B2B0C[I(state,0x80)].rotation[1],t);
        R(obj,0xF0)=math_move_angle_toward_target(F(state,0x70),D_L19_001B2B0C[I(state,0x80)].rotation[0],t);
        if (F(state,0x88)>=1) moby_set_state(obj,3,-1);
        break;
    case 3:
        if (I(state,0x94)!=-1 && B(g_moby_l19_array+I(state,0x94)*256,0xBC)) break;
        if (B(state,0x90)) { D_L19_001B9D00=0; func_PAL_L18_002CFE30(0); }
        H(obj,0x34)|=2;
        break;
    }
    if (B(obj,0x20)<3) {
        FastVecSub(delta,obj+0x10,oldpos);
        mat_combine_and_store(state+0x20,delta,oldrot,obj+0xF0);
    }
}
