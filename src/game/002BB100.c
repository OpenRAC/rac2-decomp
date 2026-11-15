#include "common.h"
extern float Fe617c30b_FUN_00283CE0(int);
extern int FloatToInt(float);
extern void part_kill(char *);
extern void FastVecAdd(char *, char *, char *);
typedef int Quad_BB100 __attribute__((mode(TI)));
typedef struct ParticleConfig_BB100 {
    float force[4];
    float minimum[4];
    float maximum[4];
    float sizeStep, spinStep, alphaStep, bounce, damping;
    float alphaMin, alphaMax;
    float colorStep[3], colorMin[3], colorMax[3];
    int flags;
    float sizeMin, sizeMax;
    char *owner;
} ParticleConfig_BB100;
typedef struct ParticleMotion_BB100 {
    float velocity[3];
    ParticleConfig_BB100 *config;
    float alpha, spin;
    u8 fractional[3], direction;
} ParticleMotion_BB100;
typedef struct Particle_BB100 {
    u8 type[4];
    int color;
    u8 spin, mode;
    short life;
    float size;
    float position[4];
    ParticleMotion_BB100 motion;
} Particle_BB100;
extern int FastDecTimer(void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_add_along_axis(void *, void *, void *, float);
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern float D_001BAFC0[];
#define PF(p,o) (*(float *)((char *)(p)+(o)))
#define PI(p,o) (*(int *)((char *)(p)+(o)))
#define PB(p,o) (*(u8 *)((char *)(p)+(o)))
static __inline__ int frac_byte(float value, float scale)
{
    float scaled = value * scale;
    int result = FloatToInt(scaled);

    if (result != 0)
        scaled = scale;
    return result;
}
/* Moves an effect particle each frame. It bounces off walls, changes colour, fade, size and spin, and is removed when it is out of range or invisible. */
void UpdateCollidingEffectParticle(Particle_BB100 *particle)
{
    float next[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    ParticleMotion_BB100 *motion = &particle->motion;
    ParticleConfig_BB100 *config;
    float r,g,b;
    int ri,gi,bi,ai,packed;
    float x,y,z;
    x = particle->position[0]+motion->velocity[0];
    y = particle->position[1]+motion->velocity[1];
    z = particle->position[2]+motion->velocity[2];
    next[0]=x; next[1]=y; next[2]=z;
    config = motion->config;
    if ((config->flags&1) && CollLine(particle->position,next,4,particle,0)) {
        velocity[0]=motion->velocity[0]; velocity[1]=motion->velocity[1]; velocity[2]=motion->velocity[2];
        vec_add_along_axis(temp,velocity,D_001BAFC0,config->bounce);
        motion->velocity[0]=temp[0]; motion->velocity[1]=temp[1]; motion->velocity[2]=temp[2];
        vec_scale_to_length(offset,D_001BAFC0,0.055f);
        FastVecAdd((char *)particle->position,(char *)(D_001BAFC0-8),(char *)offset);
    } else *(Quad_BB100 *)particle->position=*(Quad_BB100 *)next;
    if (config->flags&2) {
        r=Fe617c30b_FUN_00283CE0((PB(particle,4)<<8)|motion->fractional[0])* (1.0f/65535.0f);
        g=FloatToInt((float)((particle->color&0xff00)|motion->fractional[1]))*(1.0f/65535.0f);
        b=FloatToInt((float)(int)(((u32)particle->color>>8 &0xff00)|motion->fractional[2]))*(1.0f/65535.0f);
        if(motion->direction&16) r-=config->colorStep[0]; else r+=config->colorStep[0];
        if(motion->direction&32) g-=config->colorStep[1]; else g+=config->colorStep[1];
        if(motion->direction&64) b-=config->colorStep[2]; else b+=config->colorStep[2];
        if(r>config->colorMax[0]) {r=config->colorMax[0];if(config->flags&0x100)motion->direction^=16;}
        if(r<config->colorMin[0]) {r=config->colorMin[0];if(config->flags&0x10)motion->direction^=16;}
        if(g>config->colorMax[1]) {g=config->colorMax[1];if(config->flags&0x200)motion->direction^=32;}
        if(g<config->colorMin[1]) {g=config->colorMin[1];if(config->flags&0x20)motion->direction^=32;}
        if(b>config->colorMax[2]) {b=config->colorMax[2];if(config->flags&0x400)motion->direction^=64;}
        if(b<config->colorMin[2]) {b=config->colorMin[2];if(config->flags&0x40)motion->direction^=64;}
        motion->fractional[0]=frac_byte(r,65535.0f);
        motion->fractional[1]=FloatToInt(g*65535.0f);
        motion->fractional[2]=FloatToInt(b*65535.0f);
        ri=FloatToInt(r*255.0f);
        gi=FloatToInt(g*255.0f);
        bi=FloatToInt(b*255.0f);
        ai=FloatToInt(motion->alpha*255.0f);
        packed=ri&255;
        packed|=(gi&255)<<8;
        packed|=(bi&255)<<16;
        packed|=ai<<24;
        particle->color=packed;
    } else if(config->flags&4) particle->color=(particle->color&0xffffff)|(FloatToInt(motion->alpha*255.0f)<<24);
    if(config->flags&4) {
        if(motion->direction&128) motion->alpha-=config->alphaStep; else motion->alpha+=config->alphaStep;
        if(motion->alpha>config->alphaMax) {motion->alpha=config->alphaMax;if(config->flags&0x800)motion->direction^=128;}
        if(motion->alpha<config->alphaMin) {motion->alpha=config->alphaMin;if(config->flags&0x80)motion->direction^=128;}
    }
    particle->spin=FloatToInt(motion->spin*255.0f);
    if(config->flags&8) {
        next[0]=motion->velocity[0];next[1]=motion->velocity[1];next[2]=motion->velocity[2];
        if(config->flags&0x8000) {
            euler_to_matrix(matrix,config->owner+0xf0);
            transform_vector(temp,config,matrix);
        } else *(Quad_BB100 *)temp=*(Quad_BB100 *)config;
        FastVecAdd((char *)next,(char *)next,(char *)temp);
        vec_fast_divide_helper(next,next,config->damping);
        motion->velocity[0]=next[0];motion->velocity[1]=next[1];motion->velocity[2]=next[2];
    }
    particle->size+=config->sizeStep;
    if(particle->size<config->sizeMin)particle->size=config->sizeMin;
    if(particle->size>config->sizeMax)particle->size=config->sizeMax;
    motion->spin+=config->spinStep;
    if(motion->alpha<=0.0f || FastDecTimer(&particle->life) || particle->position[0]<config->minimum[0] || particle->position[1]<config->minimum[1] || particle->position[2]<config->minimum[2] || particle->position[0]>config->maximum[0] || particle->position[1]>config->maximum[1] || particle->position[2]>config->maximum[2]) part_kill((char *)particle);
}
#undef PF
#undef PI
#undef PB
