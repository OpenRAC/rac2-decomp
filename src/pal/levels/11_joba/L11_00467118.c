#include "names.h"
/* func_PAL_L11_00467118, the PAL copy of func_L11_00461308: the same C, where func_002A7470
   becomes func_PAL_002A7E68; func_L11_003DD068 becomes func_PAL_L11_003E0F10; 0.00027777778f
   becomes 0.00040000002f; 0.034906592f becomes 0.04188791f; func_002A05A8 becomes
   func_PAL_002A0F68; 1.0f / 60.0f becomes 0.020000001f. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern void anim_start_blended_pal(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern u8 *hoverbike_bomb_spawn_pal(u8 *, u8 *, u8 *, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_002A0F68(char *);
extern void func_002A0F48(char *);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, int);
extern int g_l11_companion_record_index[] NOT_SDA __attribute__((sda));
typedef struct { int unused; int flags; char pad[56]; } Entry61308;
extern Entry61308 g_carrier_entry_table[];
extern char *g_moby_l11_table[] NOT_SDA __attribute__((sda));
extern char *g_arena_camera_table[] NOT_SDA __attribute__((sda));
extern char g_hero_position[];
extern float g_carrier_float_params SDATA(D_L11_001B2388);
extern float D_L11_001B2388_block[] __asm__("D_L11_001B2388") __attribute__((sda));
extern char g_carrier_particle_c[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_b[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_a[] SDATA(D_L11_001B2358);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
/* Per-frame update of the level-11 companion carrier: it spawns its companion, bobs while the player is inside its area, and fires three shots (PAL: 50 Hz timings). */
void companion_carrier_update_pal(char *moby)
{
    float vec[4], pos[4], world_dir[4], local_dir[4];
    char *vars = P(moby,0x68);
    int active=0, i, ready;
    float t, sin_value, cos_value;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        P(vars,0x10)=CreateMoby(0xCF6);
        F(vars,0x14)=0; F(vars,0x18)=0;
        if(P(vars,0x10)) {
            moby_init_child_from_parent(P(vars,0x10),0);
            H(P(vars,0x10),0x34)|=6;
            anim_start_blended_pal(P(vars,0x10),0x10,0,0);
        }
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if ((g_carrier_entry_table[g_l11_companion_record_index[0]].flags&0x10) && !I(vars,8)) {
            H(moby,0x34)|=0x41;
            H(P(vars,0x10),0x34)|=0x41;
            I(moby,0x98)=0;
            return;
        }
        active=1;
        H(moby,0x34)&=0xFFBE;
        H(P(vars,0x10),0x34)&=0xFFBE;
        I(moby,0x98)=I(P(moby,0x24),0x10);
        ready=1;
        if(I(vars,0xC)!=-1) { char *target=g_moby_l11_table[0]+(I(vars,0xC)<<8); ready=0; if((unsigned char)target[0x20]!=3) ready=active; }
        if (ready && IsPointInCuboid(g_hero_position,I(vars,0)))
            moby_set_state(moby,2,-1);
        break;
    case 2:
        active=1;
        t=math_random_float_range(0.0f,0.333f);
        for(i=0;i<3;i++) {
            moby_transform_joint_to_world(moby,i==0?3:i==1?2:4,vec);
            *(TI128 *)local_dir = 0;
            local_dir[0]=math_random_float_range(-1.0f,1.0f);
            local_dir[3]=1.0f;
            local_dir[1]=t+t-1.0f;
            t+=0.333f;
            *(TI128 *)world_dir=*(TI128 *)local_dir;
            transform_vector(world_dir,world_dir,g_arena_camera_table[0]+(I(vars,4)<<7));
            {
                float high = D_L11_001B2388_block[1];
                float low = g_carrier_float_params;
                hoverbike_bomb_spawn_pal(moby,vec,world_dir,math_random_float_range(low,high)*0.00040000002f);
            }
        }
        moby_set_state(moby,3,-1);
        break;
    case 3:
        active=1;
        if(!IsPointInCuboid(g_hero_position,I(vars,0))) moby_set_state(moby,1,-1);
        break;
    }
    if(active) {
        F(vars,0x14)=FastAddRotations(F(vars,0x14),0.04188791f);
        sin_value=math_fast_sin_or_cos_a(F(vars,0x14));
        cos_value=math_fast_sin_or_cos_b(F(vars,0x14));
        F(moby,0x18)-=F(vars,0x18);
        F(vars,0x18)=cos_value*0.1f;
        F(moby,0x18)+=F(vars,0x18);
        F(moby,0xF4)+=cos_value*0.0015f;
        F(moby,0xF0)+=sin_value*0.0015f;
        *(TI128 *)(P(vars,0x10)+0xF0)=*(TI128 *)(moby+0xF0);
        FastVecScale(vec,moby+0xE0,1.46f);
        FastVecAdd(P(vars,0x10)+0x10,moby+0x10,vec);
        func_PAL_002A0F68(P(vars,0x10));
        func_002A0F48(P(vars,0x10));
        FastVecScale(vec,moby+0xE0,0.59f);
        FastVecAdd(pos,moby+0x10,vec);
        vec[0]=vec[1]=0.0f;
        vec[2]=-(math_random_float_range(2.25f,3.5f)*(0.020000001f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_c,1);
        vec[2]=-(math_random_float_range(3.0f,5.0f)*(0.020000001f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_b,1);
        vec[2]=-(math_random_float_range(4.0f,8.0f)*(0.020000001f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_a,1);
    }
}
