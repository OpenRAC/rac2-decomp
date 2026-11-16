#include "names.h"
/* func_L11_00461308: a Joba moby's state machine with a companion moby (class 0xCF6).
   State 0 spawns the companion; 1 sets or clears flag bits 0x41 on both from a level flag
   and waits on its linked moby's state and func_002ACBC8; 2 makes three
   func_L11_003DD068 calls with randomised directions; 3 waits for func_002ACBC8 to clear.
   In states 1-3 it oscillates its height, places the companion at its offset and emits
   three particles.
   Built -O2 -G0 in its own unit. The random bounds are a two-float block: the lower is
   read through $gp, the upper as the block's second word, a two-instruction absolute
   load that stays out of the call's delay slot as in retail.
*/
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern u8 *hoverbike_bomb_spawn(u8 *, u8 *, u8 *, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_002A05A8(char *);
extern void func_002A0F48(char *);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, int);
extern int g_l11_companion_record_index[] NOT_SDA __attribute__((sda));
typedef struct { int unused; int flags; char pad[56]; } Entry61308;
extern Entry61308 g_carrier_entry_table[];
extern char *g_moby_l11_table[] NOT_SDA __attribute__((sda));
extern char *g_arena_camera_table[] NOT_SDA __attribute__((sda));
extern char g_hero_position[];
/* The random bounds at 001B2388: lower, upper. Retail reads the lower through $gp and the
   upper as the block's second word, absolutely. */
extern float g_carrier_float_params SDATA(D_L11_001B2388);
extern float D_L11_001B2388_block[] __asm__("D_L11_001B2388") __attribute__((sda));
extern char g_carrier_particle_c[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_b[] NOT_SDA __attribute__((sda));
extern char g_carrier_particle_a[] SDATA(D_L11_001B2358);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
/* Updates a floating enemy (moby class 3718) that carries a companion moby: it spawns the companion, bobs up and down, fires three shots at a time, and drops sparks. */
void companion_carrier_update(char *moby)
{
    float vec[4], pos[4], dir[4], tmp[4];
    char *vars = P(moby,0x68);
    int active=0, i, ready;
    float spread, sine, cosine;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        P(vars,0x10)=CreateMoby(0xCF6 /* moby class 3318 */);
        F(vars,0x14)=0; F(vars,0x18)=0;
        if(P(vars,0x10)) {
            moby_init_child_from_parent(P(vars,0x10),0);
            H(P(vars,0x10),0x34)|=6;
            anim_start_blended(P(vars,0x10),0x10,0,0);
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
        if(I(vars,0xC)!=-1) { char *linked=g_moby_l11_table[0]+(I(vars,0xC)<<8); ready=0; if((unsigned char)linked[0x20]!=3) ready=active; }
        if (ready && IsPointInCuboid(g_hero_position,I(vars,0)))
            moby_set_state(moby,2,-1);
        break;
    case 2:
        active=1;
        spread=math_random_float_range(0.0f,0.333f);
        for(i=0;i<3;i++) {
            moby_transform_joint_to_world(moby,i==0?3:i==1?2:4,vec);
            *(TI128 *)tmp = 0;
            tmp[0]=math_random_float_range(-1.0f,1.0f);
            tmp[3]=1.0f;
            tmp[1]=spread+spread-1.0f;
            spread+=0.333f;
            *(TI128 *)dir=*(TI128 *)tmp;
            transform_vector(dir,dir,g_arena_camera_table[0]+(I(vars,4)<<7));
            {
                float high = D_L11_001B2388_block[1];
                float low = g_carrier_float_params;
                hoverbike_bomb_spawn(moby,vec,dir,math_random_float_range(low,high)*0.00027777778f);
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
        F(vars,0x14)=FastAddRotations(F(vars,0x14),0.034906592f);
        sine=math_fast_sin_or_cos_a(F(vars,0x14));
        cosine=math_fast_sin_or_cos_b(F(vars,0x14));
        F(moby,0x18)-=F(vars,0x18);
        F(vars,0x18)=cosine*0.1f;
        F(moby,0x18)+=F(vars,0x18);
        F(moby,0xF4)+=cosine*0.0015f;
        F(moby,0xF0)+=sine*0.0015f;
        *(TI128 *)(P(vars,0x10)+0xF0)=*(TI128 *)(moby+0xF0);
        FastVecScale(vec,moby+0xE0,1.46f);
        FastVecAdd(P(vars,0x10)+0x10,moby+0x10,vec);
        func_002A05A8(P(vars,0x10));
        func_002A0F48(P(vars,0x10));
        FastVecScale(vec,moby+0xE0,0.59f);
        FastVecAdd(pos,moby+0x10,vec);
        vec[0]=vec[1]=0.0f;
        vec[2]=-(math_random_float_range(2.25f,3.5f)*(1.0f/60.0f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_c,1);
        vec[2]=-(math_random_float_range(3.0f,5.0f)*(1.0f/60.0f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_b,1);
        vec[2]=-(math_random_float_range(4.0f,8.0f)*(1.0f/60.0f));
        part_spawn_object_relative_particle(moby,pos,vec,g_carrier_particle_a,1);
    }
}
