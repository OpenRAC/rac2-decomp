#include "common.h"
extern float Fe617c30b_FUN_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);
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
extern int func_00282978(void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_002AB168(void *, void *, void *, float);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern float D_001BAFC0[];
#define PF(p,o) (*(float *)((char *)(p)+(o)))
#define PI(p,o) (*(int *)((char *)(p)+(o)))
#define PB(p,o) (*(u8 *)((char *)(p)+(o)))
static __inline__ int frac_byte(float value, float scale)
{
    float scaled = value * scale;
    int result = func_00283CF0(scaled);

    if (result != 0)
        scaled = scale;
    return result;
}
void func_002BB100(Particle_BB100 *p)
{
    float next[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    ParticleMotion_BB100 *q = &p->motion;
    ParticleConfig_BB100 *cfg;
    float r,g,b;
    int ri,gi,bi,ai,packed;
    float x,y,z;
    x = p->position[0]+q->velocity[0];
    y = p->position[1]+q->velocity[1];
    z = p->position[2]+q->velocity[2];
    next[0]=x; next[1]=y; next[2]=z;
    cfg = q->config;
    if ((cfg->flags&1) && func_002761F8(p->position,next,4,p,0)) {
        velocity[0]=q->velocity[0]; velocity[1]=q->velocity[1]; velocity[2]=q->velocity[2];
        func_002AB168(temp,velocity,D_001BAFC0,cfg->bounce);
        q->velocity[0]=temp[0]; q->velocity[1]=temp[1]; q->velocity[2]=temp[2];
        func_00282F20(offset,D_001BAFC0,0.055f);
        func_00282CC0((char *)p->position,(char *)(D_001BAFC0-8),(char *)offset);
    } else *(Quad_BB100 *)p->position=*(Quad_BB100 *)next;
    if (cfg->flags&2) {
        r=Fe617c30b_FUN_00283CE0((PB(p,4)<<8)|q->fractional[0])* (1.0f/65535.0f);
        g=func_00283CF0((float)((p->color&0xff00)|q->fractional[1]))*(1.0f/65535.0f);
        b=func_00283CF0((float)(int)(((u32)p->color>>8 &0xff00)|q->fractional[2]))*(1.0f/65535.0f);
        if(q->direction&16) r-=cfg->colorStep[0]; else r+=cfg->colorStep[0];
        if(q->direction&32) g-=cfg->colorStep[1]; else g+=cfg->colorStep[1];
        if(q->direction&64) b-=cfg->colorStep[2]; else b+=cfg->colorStep[2];
        if(r>cfg->colorMax[0]) {r=cfg->colorMax[0];if(cfg->flags&0x100)q->direction^=16;}
        if(r<cfg->colorMin[0]) {r=cfg->colorMin[0];if(cfg->flags&0x10)q->direction^=16;}
        if(g>cfg->colorMax[1]) {g=cfg->colorMax[1];if(cfg->flags&0x200)q->direction^=32;}
        if(g<cfg->colorMin[1]) {g=cfg->colorMin[1];if(cfg->flags&0x20)q->direction^=32;}
        if(b>cfg->colorMax[2]) {b=cfg->colorMax[2];if(cfg->flags&0x400)q->direction^=64;}
        if(b<cfg->colorMin[2]) {b=cfg->colorMin[2];if(cfg->flags&0x40)q->direction^=64;}
        q->fractional[0]=frac_byte(r,65535.0f);
        q->fractional[1]=func_00283CF0(g*65535.0f);
        q->fractional[2]=func_00283CF0(b*65535.0f);
        ri=func_00283CF0(r*255.0f);
        gi=func_00283CF0(g*255.0f);
        bi=func_00283CF0(b*255.0f);
        ai=func_00283CF0(q->alpha*255.0f);
        packed=ri&255;
        packed|=(gi&255)<<8;
        packed|=(bi&255)<<16;
        packed|=ai<<24;
        p->color=packed;
    } else if(cfg->flags&4) p->color=(p->color&0xffffff)|(func_00283CF0(q->alpha*255.0f)<<24);
    if(cfg->flags&4) {
        if(q->direction&128) q->alpha-=cfg->alphaStep; else q->alpha+=cfg->alphaStep;
        if(q->alpha>cfg->alphaMax) {q->alpha=cfg->alphaMax;if(cfg->flags&0x800)q->direction^=128;}
        if(q->alpha<cfg->alphaMin) {q->alpha=cfg->alphaMin;if(cfg->flags&0x80)q->direction^=128;}
    }
    p->spin=func_00283CF0(q->spin*255.0f);
    if(cfg->flags&8) {
        next[0]=q->velocity[0];next[1]=q->velocity[1];next[2]=q->velocity[2];
        if(cfg->flags&0x8000) {
            func_00283410(matrix,cfg->owner+0xf0);
            func_002830C0(temp,cfg,matrix);
        } else *(Quad_BB100 *)temp=*(Quad_BB100 *)cfg;
        func_00282CC0((char *)next,(char *)next,(char *)temp);
        func_00282FB8(next,next,cfg->damping);
        q->velocity[0]=next[0];q->velocity[1]=next[1];q->velocity[2]=next[2];
    }
    p->size+=cfg->sizeStep;
    if(p->size<cfg->sizeMin)p->size=cfg->sizeMin;
    if(p->size>cfg->sizeMax)p->size=cfg->sizeMax;
    q->spin+=cfg->spinStep;
    if(q->alpha<=0.0f || func_00282978(&p->life) || p->position[0]<cfg->minimum[0] || p->position[1]<cfg->minimum[1] || p->position[2]<cfg->minimum[2] || p->position[0]>cfg->maximum[0] || p->position[1]>cfg->maximum[1] || p->position[2]>cfg->maximum[2]) func_002B9180((char *)p);
}
#undef PF
#undef PI
#undef PB
