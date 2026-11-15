#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void vec_add_transformed_or_copy(char *,char *,char *);
extern float mat_fast_helper_a(float,float);
extern void func_002A0F48(char *);
extern unsigned short D_L18_001B18FC __attribute__((sda));
extern float D_L18_001B191C __attribute__((sda));

/* Creates a bouncing fireball (moby class 3998) at a position with a given direction, owner and strength, and returns it. */
char *fireball_spawn(int owner, char *position, char *velocity, int value, float scale, float extra)
{
    char *object = CreateMoby(0xf9e /* moby class 3998 */);
    char *state;
    float angle;
    float sizeFactor;
    unsigned short timer;
    if (object != 0) {
        state = *(char **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x31] = 1;
        object[0x20] = 0;
        *(int *)(state + 0x24) = owner;
        *(TI128 *)(object + 0x10) = *(TI128 *)position;
        *(TI128 *)(state + 0x10) = *(TI128 *)velocity;
        timer = D_L18_001B18FC;
        *(float *)(state + 0x1c) = scale;
        *(int *)(state + 0x20) = value;
        *(short *)(state + 0x28) = timer;
        *(short *)(state + 0x2a) = 0;
        *(int *)(object + 0xf0) = 0;
        *(int *)(object + 0xf4) = 0;
        angle = mat_fast_helper_a(*(float *)velocity, *(float *)(velocity+4));
        *(float *)(object + 0xf8) = angle;
        *(float *)(state + 0x30) = extra;
        sizeFactor = D_L18_001B191C;
        *(float *)(object + 0x2c) = *(float *)(object + 0x2c) * sizeFactor;
        func_002A0F48(object);
    }
    return object;
}

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
extern FlagTable D_L18_0021E7B0;
typedef struct { u8 prefix[0x30]; float position[4]; u8 middle[0x30]; float rotation[4]; } Transform;
extern Transform *g_waypoint_table MACRO_ADDR;
extern u8 *g_moby_l18_table;
extern int D_L18_001B9A80 NOT_SDA;
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
/* Updates a mover (moby class 4333): it waits for a trigger or a hit, then glides smoothly to its target spot and turn, and flags a linked object when done. */
void triggered_l18_mover_update(u8 *obj)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    float ease;
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
        if (D_L18_0021E7B0.flags[I(state,0x8C)] ||
            (B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+g_current_map_index*16]&128)) ||
            (I(state,0x98)!=-1 && coll_point_inside_region(g_hero_position,I(state,0x98)))) {
            qcopy_nc(obj+0x10,g_waypoint_table[I(state,0x80)].position);
            qcopy_nc(obj+0xF0,g_waypoint_table[I(state,0x80)].rotation);
            H(obj,0x34)|=2;
            if (!B(state,0x91)) { moby_mark_spawned(obj); return; }
            moby_set_state(obj,3,-1);
        } else moby_set_state(obj,1,-1);
        break;
    case 1:
        if (!B(obj,0xBC) && !flag_is_third_pending_set(obj) && I(state,0x8C)!=-1 &&
            B(g_moby_l18_table+I(state,0x8C)*256,0x20)!=254 &&
            B(g_moby_l18_table+I(state,0x8C)*256,0x20)!=253 &&
            !(B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+g_current_map_index*16]&128)) &&
            (I(state,0x98)==-1 || !coll_point_inside_region(g_hero_position,I(state,0x98)))) goto effects;
        if (I(state,0x94)!=-1) B(g_moby_l18_table+I(state,0x94)*256,0xBC)=1;
        if (B(state,0x93)) moby_mark_table_entry_flagged(B(obj,0xB0));
        moby_set_state(obj,2,-1);
    effects:
        if (!B(state,0x91) && part_find_owned_effect_slot(obj,0x40000,0)) {
            if (I(state,0x94)!=-1) B(g_moby_l18_table+I(state,0x94)*256,0xBC)=1;
            FastVecAdd(delta,obj+0xD0,obj+0xE0);
            vec_scale_to_length(delta,delta,1.0f/12.0f);
            FastVecAdd(offset,obj+0x10,obj+0xE0);
            SpawnExplosionEffects(obj,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            part_spawn_masked_debris(obj,31,3,6,3,6,delta,255);
            H(obj,0x34)|=1;
            B(obj,0x31)=0;
            I(obj,0x98)=0;
            if (*(s16 *)(obj+0xAA)==0x10ED /* moby class 4333 */) PlayMobySound(0,0,obj);
            if (B(state,0x93)) moby_mark_table_entry_flagged(B(obj,0xB0));
            moby_set_state(obj,2,-1);
        }
        B(obj,0xA8)=255;
        break;
    case 2:
        if (flag_set_first_pending(obj) && (*(s16 *)(obj+0xAA)==0xEDB /* moby class 3803 */ || *(s16 *)(obj+0xAA)==0x1146 /* moby class 4422 */)) PlayMobySound(0,0,obj);
        F(state,0x88)+=1.0f/F(state,0x84);
        if (F(state,0x88)>1) F(state,0x88)=1;
        ease=1.0f-math_fast_sin_or_cos_a(F(state,0x88)*3.1415927f);
        ease*=0.5f;
        FastVecSub(delta,g_waypoint_table[I(state,0x80)].position,state+0x60);
        FastVecScale(delta,delta,ease);
        FastVecAdd(obj+0x10,state+0x60,delta);
        R(obj,0xF8)=math_move_angle_toward_target(F(state,0x78),g_waypoint_table[I(state,0x80)].rotation[2],ease);
        R(obj,0xF4)=math_move_angle_toward_target(F(state,0x74),g_waypoint_table[I(state,0x80)].rotation[1],ease);
        R(obj,0xF0)=math_move_angle_toward_target(F(state,0x70),g_waypoint_table[I(state,0x80)].rotation[0],ease);
        if (F(state,0x88)>=1) moby_set_state(obj,3,-1);
        break;
    case 3:
        if (I(state,0x94)!=-1 && B(g_moby_l18_table+I(state,0x94)*256,0xBC)) break;
        if (B(state,0x90)) { D_L18_001B9A80=0; hero_detach_from_object(0); }
        H(obj,0x34)|=2;
        break;
    }
    if (B(obj,0x20)<3) {
        FastVecSub(delta,obj+0x10,oldpos);
        mat_combine_and_store(state+0x20,delta,oldrot,obj+0xF0);
    }
}
