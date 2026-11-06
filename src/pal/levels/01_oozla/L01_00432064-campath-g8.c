/* func_PAL_L01_00432064, the PAL copy of func_L01_0042C540: the same C, where the duration is
 * scaled to 50 Hz in both places and pos, angles and scale take their stack slots in another order. */
#include "common.h"

typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; f32 f[4]; } PathVec;
typedef struct { f32 stiffness, damping; u8 pad[8]; PathVec value; } PathSpring;
typedef struct { s32 a, b; f32 distance, angleDistance; s32 c; s16 d, duration; } PathMotion;
typedef struct { s16 indices[8]; f32 lengths[8]; f32 factor; } PathMarks;
typedef struct { PathSpring position, rotation; PathMotion motion; PathMarks marks; } PathState;
typedef struct { s32 count; u8 pad[12]; PathVec points[1]; } PathRecord;
typedef struct { u8 pad[0xB0]; f32 value; } PathGlobals;
typedef struct { u8 pad[0x194]; u8 *transform; } PathTransformGlobal;
typedef struct {
    u8 pad[0x20]; s32 positionPath, rotationPath; u8 pad28[0x10];
    u8 state, pad39; s16 duration; f32 speed; u8 pad40[0x14]; s32 camera;
} PathSettings;
typedef struct { PathVec transform[4]; u8 pad40[0x30]; PathState *state; u8 pad74[0x10]; s16 config; } PathObject;
typedef struct { u8 pad[0x1C]; PathSettings *settings; } PathConfig;
extern PathConfig *D_L01_001B1F04;
extern PathGlobals D_L01_001BD9C0;
extern PathTransformGlobal D_L01_001B9380;
extern PathRecord *D_L01_001FE180[];
extern u8 *D_L01_001B264C __attribute__((sda));
extern f32 func_00283248(f32,f32);
extern f32 func_00282E48(void *,void *);
extern f32 func_00283CE0(s32);
extern void func_00282C88(void *);
extern void func_PAL_L01_002BEC60(s32,s32);
extern void func_PAL_L00_002B9CD8(void *,void *,s32,s32);
/* Starts a camera path: resets its motion and mark records, measures both
 * paths' segment lengths, primes both springs and copies the template transform. */
void func_PAL_L01_00432064(void *arg) {
    PathVec orientation;
    PathObject *obj=arg;
    PathSettings *settings=D_L01_001B1F04[obj->config].settings;
    PathMarks *marks;
    PathSpring *spring;
    PathMotion *motion;
    s32 i;
    f32 distance, factor;
    PathVec *scale,*pos,*angles;
    settings->state=3;
    motion=&obj->state->motion;
    motion->a=0;
    motion->b=0;
    motion->distance=0;
    motion->angleDistance=0;
    motion->c=0;
    motion->d=0;
    motion->duration=((s32)settings->duration * 5 + 2) / 6;
    marks=&obj->state->marks;
    for(i=0;i<8;i++) {
        marks->lengths[i]=0;
        marks->indices[i]=-1;
    }
    factor=D_L01_001BD9C0.value;
    scale=&obj->transform[3]; pos=&obj->transform[1]; angles=&obj->transform[2];
    marks->factor=func_00283248(1.0f,factor)*2.0f;
    if(settings->positionPath>=0) {
        s32 i, marked=0; PathRecord *path;
        path=D_L01_001FE180[settings->positionPath];
        for(i=0;i<path->count;i++) {
            if(path->points[i].f[3]>0) {
                marks->lengths[marked]=path->points[i].f[3];
                marks->indices[marked]=i;
                marked++;
            }
            distance=func_00282E48(&path->points[i],&path->points[(i+1)%path->count]);
            path->points[i].f[3]=distance;
            if(i<path->count-1) motion->distance+=distance;
        }
    }
    if(settings->duration>0)
        settings->speed=(motion->distance/func_00283CE0(((s32)settings->duration * 5 + 2) / 6))*60.0f;
    if(settings->rotationPath>=0) {
        s32 i; PathRecord *path;
        path=D_L01_001FE180[settings->rotationPath];
        for(i=0;i<path->count;i++) {
            distance=func_00282E48(&path->points[i],&path->points[(i+1)%path->count]);
            path->points[i].f[3]=distance;
            if(i<path->count-1) motion->angleDistance+=distance;
        }
    }
    spring=&obj->state->position;
    spring->stiffness=0.03f; spring->damping=0.2f;
    func_00282C88(&spring->value);
    spring=&obj->state->rotation;
    spring->stiffness=0.03f; spring->damping=0.2f;
    func_00282C88(&spring->value);
    { u8 *template=D_L01_001B9380.transform;
    qcopy(scale,template+0x30);
    qcopy(obj,template);
    qcopy(pos,template+0x10);
    qcopy(angles,template+0x20); }
    { s32 cameraIndex=settings->camera;
    if(cameraIndex<0) func_PAL_L01_002BEC60(111,1);
    else {
        u8 (*cameras)[128]=(void *)D_L01_001B264C;
        orientation.q=0; orientation.f[3]=1;
        func_PAL_L00_002B9CD8(cameras[cameraIndex]+0x30,&orientation,111,0);
    } }
}
