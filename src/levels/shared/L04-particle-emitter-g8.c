#include "common.h"

/* Initializes an emitter and its two slot ranges, then spawns nearby particles
 * and registers its render callback on subsequent updates. */
typedef unsigned int EQ __attribute__((mode(TI)));
typedef union { EQ q; float f[4]; } EVec;
#define EB(p,o) (*(u8 *)((char *)(p)+(o)))
#define EH(p,o) (*(s16 *)((char *)(p)+(o)))
#define EI(p,o) (*(s32 *)((char *)(p)+(o)))
#define EF(p,o) (*(float *)((char *)(p)+(o)))
extern char *D_L04_001B25CC;
extern EVec D_L04_0023BDD0[];
extern u8 D_L04_0023D090[];
extern s16 D_L04_0023D860[];
extern float D_L04_001AF3E0 __attribute__((sda));
extern int D_L04_001AF3BC __attribute__((sda));
extern int D_L04_001AF3C0 __attribute__((sda));
extern int D_L04_001AF3C4 __attribute__((sda));
extern int D_L04_001AF3C8 __attribute__((sda));
extern float D_L04_001AF3B4 __attribute__((sda));
extern float D_L04_001AF3B8 __attribute__((sda));
extern char D_L04_001B9680[];
extern float FastVecLength(void *);
extern int math_fast_helper_a(void *,float);
extern float vec_distance_xy(void *,void *);
extern void moby_mark_spawned(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern void transform_vector(void *,void *,void *);
extern char *SpawnSpinningSparkParticle(float,void *,int,float,void *,float,int,float,int);
extern void ref_L04_003C3BA0_00(void *,void *);
extern void DrawEmitterParticles(void *);
extern void part_init_from_ranges(void *,int);
extern void part_init_simple(void *,int);
extern u32 math_add_to_running_total(u32);
typedef struct { short first,count; int matrix; char pad08[0x40]; float radius; } EmitterView;
/* Updates a particle emitter (moby class 760): sets up its particles, then spawns new ones and draws them. */
void particle_l04_emitter_update(char *self) {
    EVec bound, velocity, position;
    char *state = *(char **)(self+0x68), *matrix;
    int i,end,color,kind;
    float size,r;
    char *particle,*data;
    switch (EB(self,0x20)) {
    case 0:
        EB(self,0x20)=1; EB(self,0x30)=255;
        if (((EmitterView *)state)->matrix==-1) { moby_mark_spawned(self); return; }
        ((EmitterView *)state)->radius=FastVecLength(D_L04_001B25CC+((EmitterView *)state)->matrix*128+0x10);
        r=FastVecLength(D_L04_001B25CC+((EmitterView *)state)->matrix*128);
        if (((EmitterView *)state)->radius<r) ((EmitterView *)state)->radius=r;
        EF(state,0x44)=EH(state,0x40) ? ((EmitterView *)state)->radius : 3.0f;
        EF(state,0x50)=FastVecLength(D_L04_001B25CC+((EmitterView *)state)->matrix*128+0x20)*0.5f;
        EH(state,0)=math_add_to_running_total(EH(state,2)+EH(state,0x40));
        end=EH(state,0)+EH(state,2);
        for(i=EH(state,0);i<end;i++) {
            D_L04_0023D090[i]=math_random_int_below(2);
            D_L04_0023BDD0[i].f[3]=1.0f;
            part_init_from_ranges(self,i);
            D_L04_0023D860[i]=0;
        }
        { int start=end; end+=EH(state,0x40);
        for(i=start;i<end;i++) {
            D_L04_0023D090[i]=math_random_int_below(2);
            D_L04_0023BDD0[i].f[3]=1.0f;
            part_init_simple(self,i);
        }
        }
        EF(D_L04_001B25CC+((EmitterView *)state)->matrix*128,0x3C)=1.0f;
        EI(state,0x38)=(EB(state,0x3E)<<16)|(EB(state,0x3D)<<8)|EB(state,0x3C);
        break;
    case 1: {
        int j;
        matrix=D_L04_001B25CC+((EmitterView *)state)->matrix*128;
        qcopy(&bound,matrix+0x30);
        bound.f[2]+=9.0f; bound.f[3]=10.0f;
        if (math_fast_helper_a(&bound,D_L04_001AF3E0)<0) return;
        if (EH(state,0x42) && vec_distance_xy(D_L04_001B9680,self+0x10)<128.0f) {
            for(j=0;j<D_L04_001AF3BC;j++) {
                velocity.f[0]=math_random_signed_float_range(0.0f,1.0f);
                velocity.f[1]=math_random_signed_float_range(0.0f,1.0f);
                velocity.f[2]=1.0f; velocity.f[3]=1.0f;
                transform_vector(&position,&velocity,matrix);
                position.f[2]+=0.5f;
                velocity.f[0]=math_random_signed_float_range(0.0f,0.004166667f);
                velocity.f[1]=math_random_signed_float_range(0.0f,0.004166667f);
                velocity.f[2]=EF(state,0x20)*0.016666668f;
                size=math_random_float_range(EF(state,0x24),EF(state,0x28));
                color=(math_random_int_range(EH(state,0x2C),EH(state,0x2E))<<24)|D_L04_001AF3C8;
                kind=math_random_int_range(D_L04_001AF3C0,D_L04_001AF3C4);
                particle=SpawnSpinningSparkParticle(D_L04_001AF3B4,&position,kind,1.0f,&velocity,D_L04_001AF3B8,color,size,0);
                if (particle) {
                    data=particle+0x20;
                    EH(particle,0xA)=math_random_int_range(EI(state,0x30),EI(state,0x34));
                    EI(data,4)=3; EB(data,0xA)=color>>24; EB(data,0xB)=EB(particle,0xA);
                    if(math_random_int_below(2)) EB(particle,3)=0x44;
                }
            }
        }
        ref_L04_003C3BA0_00(DrawEmitterParticles,self);
        break;
    }
    }
}
