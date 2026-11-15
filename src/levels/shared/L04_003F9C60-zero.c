#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern int math_random_int_below(int);
extern float func_002A7878_range(float,float) __asm__("func_002A7878");
extern void vec_scale_to_length(char *,char *,float);
extern void part_kill(void *);
extern int math_random_int_range(int,int);
extern u8 *part_spawn_velocity_particle(void *,void *,int,int,float);
extern unsigned char *SpawnSpinningSparkParticle(void *,float,float,float,float,int,void *,int,int);
/* Frees the 17 effects attached to the moby and, if asked, bursts sparks and puffs of smoke around it. */
void moby_destroy_effects_with_burst(unsigned char *moby,int sparks) {
    unsigned char *vars;
    unsigned char **effect_slot;
    int i=16, j, color, sign;
    int baseColor, negativeSign;
    union { Q16_B0e5d8f83 q; float f[4]; } scratch;
    unsigned char *puff,*puff_data;
    vars=*(unsigned char **)(moby+0x68);
    effect_slot=(unsigned char **)(vars+0x1C);
    for(;i>=0;i--,effect_slot++) {
        if(*effect_slot)part_kill(*effect_slot);
        *effect_slot=0;
    }
    if(sparks) {
        union { Q16_B0e5d8f83 q; float f[4]; } random_dir;
        float *velocity=random_dir.f;
        for(i=4;i>=0;i--) {
            random_dir.q=0;
            random_dir.f[0]=func_002A7878_range(-1,1);
            random_dir.f[1]=func_002A7878_range(-1,1);
            random_dir.f[2]=func_002A7878_range(-1,1);
            scratch.q=random_dir.q;
            vec_scale_to_length((char *)velocity,(char *)&scratch,func_002A7878_range(0.05000000447034836f,0.10000000894069672f));
            part_spawn_velocity_particle(moby+0x10,velocity,0x7F2F4F6F,math_random_int_range(10,15),35000.0f);
        }
    }
    baseColor=0x606060; negativeSign=-1;
    for(j=2;j>=0;j--) {
        color=(math_random_int_range(32,128)<<24)|baseColor;
        sign=math_random_int_below(2)?negativeSign:1;
        scratch.q=0; scratch.f[2]=1; scratch.f[3]=1;
        scratch.f[2]=func_002A7878_range(0.01f,0.025f);
        puff=SpawnSpinningSparkParticle(moby+0x10,0.2f,1,1.02f,140000.0f,sign,&scratch,color,0);
        if(puff) {
            puff_data=puff+0x20;
            *(short *)(puff+0xA)=math_random_int_range(50,80);
            puff_data[0xA]=color>>24;
            *(int *)(puff_data+4)=2;
            puff_data[0xB]=puff[0xA];
            if(math_random_int_below(2))puff[3]=0x44;
        }
    }
}
