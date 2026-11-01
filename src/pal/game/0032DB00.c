#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0032DB00);

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
extern void func_PAL_0032E268(char *, void *, void *, float);
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
char *func_PAL_0032DF28(EffectVector *position, int flash, int n0, int n1,
                  int n2, int n3, int n4, int orient, float size, float distance,
                  int mode, int extra, int flags, char *owner)
{
    EffectVector delta, radial, attachment, sphere, direction;
    char *object;
    EffectState *state;
    float angle;
    EffectCamera *camera;
    object=func_0029EFD0(0x13A0);
    if (object) {
        *(unsigned char *)(object+0x30)=255;
        object[0x20]=0;
        SHORT_AT(object,0x32)=255;
        state=*(EffectState **)(object+0x68);
        qcopy(object+0x10,position);
        FLOAT_AT(object,0x1C)=1.0f;
        func_00282CF0(&delta,&D_001B5200.position,object+0x10);
        func_00282F20(&delta,&delta,1.0f);
        func_002AFFD8(object+0x10,(char *)&radial,1);
        qcopy(object+0xC0,&delta);
        func_00282DD8(object+0xD0,object+0xC0,&radial);
        func_00282F20(object+0xD0,object+0xD0,1.0f);
        func_00282DD8(object+0xE0,object+0xD0,object+0xC0);
        FLOAT_AT(object,0xCC)=FLOAT_AT(object,0xDC)=FLOAT_AT(object,0xEC)=0.0f;
        state->values[0]=n0;
        state->values[1]=n1;
        state->values[2]=n2;
        state->values[3]=n3;
        state->values[4]=n4;
        state->mode=mode;
        state->size=size;
        state->duration=state->time=50;
        state->inner=size+size;
        state->outer=size*4.0f;
        state->extra=extra;
        state->flags=flags;
        state->orient=orient;
        state->owner=owner;
        qzero_nc(&attachment);
        if (owner) func_002AD330(object,owner,object+0x10,(char *)&attachment);
        qcopy(&sphere,object+0x10);
        sphere.w=size*3.0f;
        if (func_00283DB8(&sphere,128.0f)==1) {
            state->visible=8;
            state->fade=0.125f;
            if (func_00282E48(position,&D_001B5200.position)<48.0f && flash) {
                camera=&D_001B5200;
                camera->shake_flag=0;
                camera->shake_duration=33;
                camera->shake_amplitude=0.075f;
            }
            if (state->orient) {
                func_00282CF0(&direction,object+0x10,&D_001B5200.position);
                func_00282F20(&direction,&direction,1.0f);
                angle=1.5707963705062866f-func_002831B0(func_00282DB0(&direction,&D_001B5200.forward));
                if (angle<0.45378565788269043f) state->orient=1;
                else state->orient=0;
            }
        } else {
            state->visible=0;
            state->orient=0;
        }
        func_PAL_0032E268(object,&radial,&attachment,distance);
    }
    return object;
}


INCLUDE_ASM("asm/pal/game", func_PAL_0032E268);
