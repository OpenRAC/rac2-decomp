#include "include_asm.h"
#include "common.h"

typedef struct { float x,y,z,w; } EffectVector __attribute__((aligned(16)));
extern char *func_0029EFD0(int);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282DD8(void *, const void *, const void *);
extern void func_002AFFD8(char *, char *, int);
extern int func_002AD330(char *, char *, char *, char *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_0032CA40(char *, void *, void *, float);
/* The camera: its position at 0x140 and the shake fields func_0032DD40 also sets. */
typedef struct {
    char prefix[0x140];
    EffectVector position;
    char gap150[0x10];
    float shake_amplitude;
    int unknown164;
    int shake_duration;
    int shake_flag;
    char gap170[0x200];
    EffectVector forward;
} EffectCamera;
extern EffectCamera D_001B5200;

#define FLOAT_AT(p,o) (*(float *)((char *)(p)+(o)))
#define SHORT_AT(p,o) (*(short *)((char *)(p)+(o)))

typedef struct {
    short time, duration, visible, pad6;
    float inner, outer, fade, size;
    int orient, extra;
    int values[5];
    int mode, flags;
    char *owner;
} EffectState;

/* Spawns an explosion object (CreateMoby) and starts its effect (EmitExplosionParticles). */
char *func_0032C700(EffectVector *position, int flash, int n0, int n1,
                  int n2, int n3, int n4, int orient, float size, float distance,
                  int mode, int extra, int flags, char *owner)
{
    EffectVector delta, radial, attachment, sphere, direction;
    char *object;
    EffectState *state;
    float angle;
    EffectCamera *camera;
    object=CreateMoby(0x13A0 /* moby class 5024 */);
    if (object) {
        *(unsigned char *)(object+0x30)=255;
        object[0x20]=0;
        SHORT_AT(object,0x32)=255;
        state=*(EffectState **)(object+0x68);
        qcopy(object+0x10,position);
        FLOAT_AT(object,0x1C)=1.0f;
        FastVecSub(&delta,&gActiveCamera.position,object+0x10);
        vec_scale_to_length(&delta,&delta,1.0f);
        ComputeViewDirection(object+0x10,(char *)&radial,1);
        qcopy(object+0xC0,&delta);
        FastVecCross(object+0xD0,object+0xC0,&radial);
        vec_scale_to_length(object+0xD0,object+0xD0,1.0f);
        FastVecCross(object+0xE0,object+0xD0,object+0xC0);
        FLOAT_AT(object,0xCC)=FLOAT_AT(object,0xDC)=FLOAT_AT(object,0xEC)=0.0f;
        state->values[0]=n0;
        state->values[1]=n1;
        state->values[2]=n2;
        state->values[3]=n3;
        state->values[4]=n4;
        state->mode=mode;
        state->size=size;
        state->duration=state->time=60;
        state->inner=size+size;
        state->outer=size*4.0f;
        state->extra=extra;
        state->flags=flags;
        state->orient=orient;
        state->owner=owner;
        qzero_nc(&attachment);
        if (owner) TransformPointByMobyAttachment(object,owner,object+0x10,(char *)&attachment);
        qcopy(&sphere,object+0x10);
        sphere.w=size*3.0f;
        if (FastMathHelperA(&sphere,128.0f)==1) {
            state->visible=10;
            state->fade=0.1f;
            if (fast_vec_dist(position,&gActiveCamera.position)<48.0f && flash) {
                camera=&gActiveCamera;
                camera->shake_flag=0;
                camera->shake_duration=40;
                camera->shake_amplitude=0.075f;
            }
            if (state->orient) {
                FastVecSub(&direction,object+0x10,&gActiveCamera.position);
                vec_scale_to_length(&direction,&direction,1.0f);
                angle=1.5707963705062866f-FastAngleHelper(FastVecDot(&direction,&gActiveCamera.forward));
                if (angle<0.45378565788269043f) state->orient=1;
                else state->orient=0;
            }
        } else {
            state->visible=0;
            state->orient=0;
        }
        EmitExplosionParticles(object,&radial,&attachment,distance);
    }
    return object;
}
