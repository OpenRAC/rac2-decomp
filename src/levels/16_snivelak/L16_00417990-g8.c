#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern void FastVecScale(void *,void *,float);
extern char *part_spawn_object_following_effect(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void *part_find_owned_effect_slot(void *,unsigned int,int);
extern void moby_set_state(unsigned char *,int,int);
extern void part_explode_object_into_pieces(void *,void *,void *,void *,int,int,int,int,int,int,int);
/* Mixed arguments preserve the EE ABI order within each register bank. */
extern void part_l00_spawn_spark_burst(void *,void *,float,void *,float,int,int,float,float,float);
extern void vec_local_offset_to_world(char *,char *,float,float,float);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,int,float,float,float,float,int,int,int,int,int);
extern void part_kill(void *);
extern char *moby_l00_spawn_child(char *,int,int);
extern int math_fast_float_d(int *);
extern int math_random_int_range(int,int);
extern char g_destructible_smoke_params_c[] SDATA(D_L16_001B1BF0);
extern char g_destructible_smoke_params_b[] SDATA(D_L16_001B1BE8);
extern char g_destructible_smoke_params_a[] SDATA(D_L16_001B1BE0);
extern int g_destructible_smoke_group_bit __attribute__((sda));
/* Runs a destructible object: it smokes, then bursts into sparks and fire when destroyed, then keeps puffing for a while. */
void destructible_smoke_burst_update(char *object)
{
    Vector128 position[1],velocity[1],zero[1];
    int *state=*(int **)(object+0x68);
    *(Vector128 *)position=0;
    *(Vector128 *)velocity=0;
    ((float *)position)[0]=13.0f;
    ((float *)position)[2]=15.0f;
    ((float *)velocity)[0]=0.1666666716f;
    ((float *)velocity)[2]=0.1166666746f;
    switch(*(unsigned char *)(object+0x20)) {
    case 0:
        moby_set_state((unsigned char *)object,1,-1);
        break;
    case 1:
        FastVecScale(position,position,*(float *)(object+0x2c));
        state[1]=(int)part_spawn_object_following_effect(position,object,0x28202080u,-1,1,2,0,0x60,*(float *)(object+0x2c)*3780000.0f,0.75f);
        if(part_find_owned_effect_slot(object,0x4010000u,0)!=0 && state[0]==0) moby_set_state((unsigned char *)object,2,-1);
        *(unsigned char *)(object+0xa8)=0xff;
        break;
    case 2:
        part_explode_object_into_pieces(object,g_destructible_smoke_params_c,g_destructible_smoke_params_b,g_destructible_smoke_params_a,0xffff,0,g_destructible_smoke_group_bit,0,0xffff,0xff,0);
        part_l00_spawn_spark_burst(object,position,0.2f,velocity,0.1166666746f,40,1,1.0f,5.0f,1.0f);
        *(Vector128 *)zero=0;
        vec_local_offset_to_world(object,(char *)position,13.0f,0.0f,14.0f);
        SpawnExplosionEffects(object,zero,position,0.0f,0.0f,10,3,5,0.0f,-1,1.0f,9.0f,0.75f,0.0f,0,0,-1,0,0x810001);
        if(state[1]!=0) part_kill((void *)state[1]);
        moby_l00_spawn_child(object,0x10f2,0);
        *(int *)(object+0x98)=0;
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
        state[2]=100;
        moby_set_state((unsigned char *)object,3,-1);
        break;
    case 3:
        if(state[2]>80) {
            FastVecScale(velocity,velocity,0.5f);
            part_l00_spawn_spark_burst(object,position,0.0f,velocity,0.05000000447f,4,1,1.0f,5.0f,1.0f);
        }
        if(math_fast_float_d(state+2)!=0) {
            FastVecScale(velocity,velocity,0.3333333433f);
            ((float *)velocity)[2]*=0.3333333433f;
            part_l00_spawn_spark_burst(object,position,0.0f,velocity,0.05000000447f,math_random_int_range(3,6),1,0.5f,15.0f,1.0f);
            part_l00_spawn_spark_burst(object,position,0.0f,velocity,0.05000000447f,math_random_int_range(3,6),0,0.5f,15.0f,1.0f);
            state[2]=math_random_int_range(30,80);
        }
        break;
    }
}
