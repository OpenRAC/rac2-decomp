#include "names.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;
extern float g_pair_game_collision_radius __attribute__((sda));
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *),FastVecDot(void *,void *);
extern void FastVecScale(void *,void *,float),vec_fast_normalize(void *,void *,void *);
extern void pair_game_wrap_coordinates(float *,float *);
extern void *part_find_owned_effect_slot(void *,unsigned int,int);
extern void part_l00_spawn_explosion_particles(void *,void *);
typedef struct {
    unsigned char *actors[2];
    unsigned char reserved08[8];
    Vector positions[2];
    Vector velocities[2];
    unsigned char reserved50[8];
    int scores[2];
    int phase;
} PairContext;
/* Handles the two ships bumping each other, flying out of the area or being hit. It updates the scores and starts the explosion. */
void pair_game_resolve_collisions(unsigned char *object)
{
    Vector difference, opposite;
    PairContext *context=*(PairContext **)(object+0x68);
    int i;
    if(context->phase==0) {
        FastVecSub(&difference,&context->positions[0],&context->positions[1]);
        if(FastVecLength(&difference)<g_pair_game_collision_radius+g_pair_game_collision_radius) {
            FastVecScale(&opposite,&difference,-1.0f);
            if(FastVecDot(&difference,&context->velocities[1])>0.0f)
                vec_fast_normalize(&context->velocities[1],&context->velocities[1],&opposite);
            if(FastVecDot(&difference,&context->velocities[0])<0.0f)
                vec_fast_normalize(&context->velocities[0],&context->velocities[0],&difference);
        }
    }
    for(i=0;i<2;++i) {
        pair_game_wrap_coordinates(&context->positions[i].v[1],&context->positions[i].v[2]);
        if(*(unsigned short *)(context->actors[i]+0x34)&1) continue;
        if(context->positions[i].v[1]*context->positions[i].v[1]+
            context->positions[i].v[2]*context->positions[i].v[2]<g_pair_game_collision_radius ||
            part_find_owned_effect_slot(context->actors[i],0x10000,0)) {
            context->phase=i+1;
            *(unsigned short *)(context->actors[i]+0x34)|=1;
            context->actors[i][0x31]=0;
            if(*(unsigned short *)(context->actors[(i+1)&1]+0x34)&1) --context->scores[i];
            else ++context->scores[(i+1)&1];
            part_l00_spawn_explosion_particles(context->actors[i],context->actors[i]+0x10);
        }
    }
}
