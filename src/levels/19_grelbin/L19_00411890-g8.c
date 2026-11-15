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
extern int moby_set_state(void *,int,int);
extern int coll_point_inside_region(void *,int);
extern void moby_mark_spawned(void *);
extern int flag_is_third_pending_set(void *),flag_set_first_pending(void *);
extern void moby_mark_table_entry_flagged(int);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,float,float,float,int,int,int,int,int,int,int,int,int,float,float);
extern void part_spawn_masked_debris(void *,int,float,float,float,float,void *,int);
extern int PlayMobySound(int,int,void *);
extern float math_fast_sin_or_cos_a(float),math_move_angle_toward_target(float,float,float);
extern void hero_detach_from_object(int),mat_combine_and_store(void *,void *,void *,void *);
/* Waits for a trigger or a hit, then smoothly moves and turns the object to a target spot, and removes it or leaves it there. */
void triggered_move_to_target_update(u8 *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby+0x68);
    float ease;
    *(TI128 *)oldpos = *(TI128 *)(moby+0x10);
    *(TI128 *)oldrot = *(TI128 *)(moby+0xF0);
    switch (B(moby,0x20)) {
    case 0:
        if (I(vars,0x80)==-1) {
            H(moby,0x34)|=2;
            moby_set_state(moby,4,-1);
            return;
        }
        I(vars,0x88)=0;
        I(vars,0x5C)|=1;
        *(TI128 *)(vars+0x60) = *(TI128 *)(moby+0x10);
        *(TI128 *)(vars+0x70) = *(TI128 *)(moby+0xF0);
        if (D_L19_0021EA30.flags[I(vars,0x8C)] ||
            (B(moby,0xB0)!=255 && B(vars,0x92) && (D_0019B2E8[B(moby,0xB0)+g_current_map_index*16]&128)) ||
            (I(vars,0x98)!=-1 && coll_point_inside_region(g_hero_position,I(vars,0x98)))) {
            qcopy_nc(moby+0x10,D_L19_001B2B0C[I(vars,0x80)].position);
            qcopy_nc(moby+0xF0,D_L19_001B2B0C[I(vars,0x80)].rotation);
            H(moby,0x34)|=2;
            if (!B(vars,0x91)) { moby_mark_spawned(moby); return; }
            moby_set_state(moby,3,-1);
        } else moby_set_state(moby,1,-1);
        break;
    case 1:
        if (!B(moby,0xBC) && !flag_is_third_pending_set(moby) && I(vars,0x8C)!=-1 &&
            B(g_moby_l19_array+I(vars,0x8C)*256,0x20)!=254 &&
            B(g_moby_l19_array+I(vars,0x8C)*256,0x20)!=253 &&
            !(B(moby,0xB0)!=255 && B(vars,0x92) && (D_0019B2E8[B(moby,0xB0)+g_current_map_index*16]&128)) &&
            (I(vars,0x98)==-1 || !coll_point_inside_region(g_hero_position,I(vars,0x98)))) goto effects;
        if (I(vars,0x94)!=-1) B(g_moby_l19_array+I(vars,0x94)*256,0xBC)=1;
        if (B(vars,0x93)) moby_mark_table_entry_flagged(B(moby,0xB0));
        moby_set_state(moby,2,-1);
    effects:
        if (!B(vars,0x91) && part_find_owned_effect_slot(moby,0x40000,0)) {
            if (I(vars,0x94)!=-1) B(g_moby_l19_array+I(vars,0x94)*256,0xBC)=1;
            FastVecAdd(delta,moby+0xD0,moby+0xE0);
            vec_scale_to_length(delta,delta,1.0f/12.0f);
            FastVecAdd(offset,moby+0x10,moby+0xE0);
            SpawnExplosionEffects(moby,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            part_spawn_masked_debris(moby,31,3,6,3,6,delta,255);
            H(moby,0x34)|=1;
            B(moby,0x31)=0;
            I(moby,0x98)=0;
            if (*(s16 *)(moby+0xAA)==0x10ED /* moby class 4333 */) PlayMobySound(0,0,moby);
            if (B(vars,0x93)) moby_mark_table_entry_flagged(B(moby,0xB0));
            moby_set_state(moby,2,-1);
        }
        B(moby,0xA8)=255;
        break;
    case 2:
        if (flag_set_first_pending(moby) && (*(s16 *)(moby+0xAA)==0xEDB /* moby class 3803 */ || *(s16 *)(moby+0xAA)==0x1146 /* moby class 4422 */)) PlayMobySound(0,0,moby);
        F(vars,0x88)+=1.0f/F(vars,0x84);
        if (F(vars,0x88)>1) F(vars,0x88)=1;
        ease=1.0f-math_fast_sin_or_cos_a(F(vars,0x88)*3.1415927f);
        ease*=0.5f;
        FastVecSub(delta,D_L19_001B2B0C[I(vars,0x80)].position,vars+0x60);
        FastVecScale(delta,delta,ease);
        FastVecAdd(moby+0x10,vars+0x60,delta);
        R(moby,0xF8)=math_move_angle_toward_target(F(vars,0x78),D_L19_001B2B0C[I(vars,0x80)].rotation[2],ease);
        R(moby,0xF4)=math_move_angle_toward_target(F(vars,0x74),D_L19_001B2B0C[I(vars,0x80)].rotation[1],ease);
        R(moby,0xF0)=math_move_angle_toward_target(F(vars,0x70),D_L19_001B2B0C[I(vars,0x80)].rotation[0],ease);
        if (F(vars,0x88)>=1) moby_set_state(moby,3,-1);
        break;
    case 3:
        if (I(vars,0x94)!=-1 && B(g_moby_l19_array+I(vars,0x94)*256,0xBC)) break;
        if (B(vars,0x90)) { D_L19_001B9D00=0; hero_detach_from_object(0); }
        H(moby,0x34)|=2;
        break;
    }
    if (B(moby,0x20)<3) {
        FastVecSub(delta,moby+0x10,oldpos);
        mat_combine_and_store(vars+0x20,delta,oldrot,moby+0xF0);
    }
}
