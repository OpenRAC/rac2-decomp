/* func_PAL_L04_003C7130, the PAL copy of func_L04_003C3BA0: the same C, where 0.00416667f becomes
 * 0.005f, 0.0166667f becomes 0.02f, and the random value stored at particle+0xA is scaled to 50 Hz. */
#include "common.h"

/* Initializes an emitter and its two slot ranges, then spawns nearby particles
 * and registers its render callback on subsequent updates. */
typedef unsigned int EQ __attribute__((mode(TI)));
typedef union { EQ q; float f[4]; } EVec;
#define EB(p,o) (*(u8 *)((char *)(p)+(o)))
#define EH(p,o) (*(s16 *)((char *)(p)+(o)))
#define EI(p,o) (*(s32 *)((char *)(p)+(o)))
#define EF(p,o) (*(float *)((char *)(p)+(o)))
extern char *g_linked_record_table;
extern EVec g_particle_positions[];
extern u8 g_particle_mirror_flags[];
extern s16 g_particle_fade_in_timers[];
extern float g_spark_bound_radius __attribute__((sda));
extern int g_spark_particle_count __attribute__((sda));
extern int g_spark_kind_min __attribute__((sda));
extern int g_spark_kind_max __attribute__((sda));
extern int g_spark_color_rgb __attribute__((sda));
extern float g_spark_particle_param_a __attribute__((sda));
extern float g_spark_particle_param_b __attribute__((sda));
extern char g_tether_zero_vec[];
extern float FastVecLength(void *);
extern int math_fast_helper_a(void *,float);
extern float vec_distance_xy(void *,void *);
extern void moby_mark_spawned(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern void transform_vector(void *,void *,void *);
extern char *func_PAL_002BE9A8(float,void *,int,float,void *,float,int,float,int);
extern void ref_PAL_L04_003C7130_00(void *,void *);
extern void func_PAL_L04_003C7600(void *);
extern void part_init_from_ranges(void *,int);
extern void part_init_simple(void *,int);
extern u32 math_add_to_running_total(u32);
typedef struct { short first,count; int matrix; char pad08[0x40]; float radius; } EmitterView;
void func_PAL_L04_003C7130(char *self) {
    EVec bound, velocity, position;
    char *state = *(char **)(self+0x68), *matrix;
    int i,end,color,kind;
    float size,r;
    char *particle,*data;
    switch (EB(self,0x20)) {
    case 0:
        EB(self,0x20)=1; EB(self,0x30)=255;
        if (((EmitterView *)state)->matrix==-1) { moby_mark_spawned(self); return; }
        ((EmitterView *)state)->radius=FastVecLength(g_linked_record_table+((EmitterView *)state)->matrix*128+0x10);
        r=FastVecLength(g_linked_record_table+((EmitterView *)state)->matrix*128);
        if (((EmitterView *)state)->radius<r) ((EmitterView *)state)->radius=r;
        EF(state,0x44)=EH(state,0x40) ? ((EmitterView *)state)->radius : 3.0f;
        EF(state,0x50)=FastVecLength(g_linked_record_table+((EmitterView *)state)->matrix*128+0x20)*0.5f;
        EH(state,0)=math_add_to_running_total(EH(state,2)+EH(state,0x40));
        end=EH(state,0)+EH(state,2);
        for(i=EH(state,0);i<end;i++) {
            g_particle_mirror_flags[i]=math_random_int_below(2);
            g_particle_positions[i].f[3]=1.0f;
            part_init_from_ranges(self,i);
            g_particle_fade_in_timers[i]=0;
        }
        { int start=end; end+=EH(state,0x40);
        for(i=start;i<end;i++) {
            g_particle_mirror_flags[i]=math_random_int_below(2);
            g_particle_positions[i].f[3]=1.0f;
            part_init_simple(self,i);
        }
        }
        EF(g_linked_record_table+((EmitterView *)state)->matrix*128,0x3C)=1.0f;
        EI(state,0x38)=(EB(state,0x3E)<<16)|(EB(state,0x3D)<<8)|EB(state,0x3C);
        break;
    case 1: {
        int j;
        matrix=g_linked_record_table+((EmitterView *)state)->matrix*128;
        qcopy(&bound,matrix+0x30);
        bound.f[2]+=9.0f; bound.f[3]=10.0f;
        if (math_fast_helper_a(&bound,g_spark_bound_radius)<0) return;
        if (EH(state,0x42) && vec_distance_xy(g_tether_zero_vec,self+0x10)<128.0f) {
            for(j=0;j<g_spark_particle_count;j++) {
                velocity.f[0]=math_random_signed_float_range(0.0f,1.0f);
                velocity.f[1]=math_random_signed_float_range(0.0f,1.0f);
                velocity.f[2]=1.0f; velocity.f[3]=1.0f;
                transform_vector(&position,&velocity,matrix);
                position.f[2]+=0.5f;
                velocity.f[0]=math_random_signed_float_range(0.0f,0.0050000004f);
                velocity.f[1]=math_random_signed_float_range(0.0f,0.0050000004f);
                velocity.f[2]=EF(state,0x20)*0.020000001f;
                size=math_random_float_range(EF(state,0x24),EF(state,0x28));
                color=(math_random_int_range(EH(state,0x2C),EH(state,0x2E))<<24)|g_spark_color_rgb;
                kind=math_random_int_range(g_spark_kind_min,g_spark_kind_max);
                particle=func_PAL_002BE9A8(g_spark_particle_param_a,&position,kind,1.0f,&velocity,g_spark_particle_param_b,color,size,0);
                if (particle) {
                    data=particle+0x20;
                    EH(particle,0xA)=((s32)math_random_int_range(EI(state,0x30),EI(state,0x34)) * 5 + 2) / 6;
                    EI(data,4)=3; EB(data,0xA)=color>>24; EB(data,0xB)=EB(particle,0xA);
                    if(math_random_int_below(2)) EB(particle,3)=0x44;
                }
            }
        }
        ref_PAL_L04_003C7130_00(func_PAL_L04_003C7600,self);
        break;
    }
    }
}
