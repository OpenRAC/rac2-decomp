#include "common.h"

/* func_L00_004243C0: -G8 for the $gp tuning value, -g for the line labels around the
 * division and the hold test, and -fstrict-aliasing as in its neighbour L00_004240D8:
 * type-based alias analysis gives the camera-type test and the registers after it their
 * retail form. The owner block (+0x70) is read through its position (+0x60),
 * aim (+0xB0), movement (+0x160) and state (+0x1F0) parts; `goal` is assigned inside the
 * loop (loop.c hoists it) so its spill slot precedes the scan and hidden pointers. */

extern char D_L00_001B8E20[],D_L00_001BF220[];
typedef struct { char pad[404]; char *active; char gap[620]; int counter; } GlobalCamera243;
typedef struct { char pad[256]; float x, y; } Controls243;
extern GlobalCamera243 D_L00_001B8C80;
extern Controls243 D_00138180;
extern char *D_L00_001C3280[], *D_L00_0025B9A0[];
extern char *D_L00_001B184C;
extern float D_L00_001B14CC __attribute__((sda));
typedef struct { char pad[0x2290]; char *owner; int mode; } Player243;
extern Player243 D_L00_00189E20;
extern void func_00282D08(void *,void *,void *,float);
extern int func_00277F48(void *,int,void *,int,float),func_L00_0031BE88(void *);
extern void func_00282CF0(void *,void *,void *),func_00282D30(void *,void *,float),func_00282F20(void *,void *,float);
extern float func_00282DB0(void *,void *),func_002831B0(float),func_00282C48(float);
extern void func_00282DD8(void *,void *,void *),func_002ACEC0(void *,void *,void *,float);
extern int func_L00_004240D8(void *),func_L00_00423BB0(void *),func_L00_004239A8(void *);
extern int func_00282978(short *);
extern float func_00283CE0(int),func_002A7C00(float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002761F8(void *,void *,void *,void *,int),func_L00_004204A0(void *);
extern void func_L00_002D9D98(void);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define U(p,n) (*(unsigned short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
#define I(p,n) (*(int *)((char *)(p)+(n)))
typedef struct { char pad[16]; float pos[4]; char pad20[4]; struct { char pad[16]; int value; } *info; char pad28[112]; int visible; char pad9C[14]; short type; } Moby243;
typedef struct { char pad[44]; float distance; } Move243;
typedef struct { char pad[48]; float offset; short timer; char gap[4]; short flag; char gap2[16]; short counter, locked; } State243;
/* Runs the follow camera each frame. It hides objects that block the view, pushes the camera away from walls, and slowly pulls it back out. */
void func_L00_004243C0(char *obj)
{
    char *base=P(obj,112);
    char *pos=base+96;
    Move243 *move=(Move243 *)(base+352);
    State243 *state=(State243 *)(base+496);
    char *camera=D_L00_001B8E20;
    char probe[16],toMoby[16],alongAxis[16],perpendicular[16],side[16];
    Moby243 *moby;
    char *axis;
    int count,n,blocked=0,numhidden=0,type,cameraType,i;
    float distance=move->distance-state->offset+1.5f;
    float dot,angle;
    unsigned short timer;
    Moby243 *entry;
    char *goal;
    lerp_vector(probe,base+176,camera-96,0.5f);
    count=ProcessCollisionHit(probe,1,D_L00_00189E20.owner,0,distance*0.5f);
    if(count>0) {
        char **scan,**hidden;
        scan=gAreaHitTargets;
        hidden=D_L00_0025B9A0;
        for(i=0;i<count;i++) {
            goal=base+176;
            moby=(Moby243 *)*scan;
            if(moby->visible && (!HasPendingInnerFlag(moby)||moby->type==2923 /* moby class 2923 */)) {
                type=moby->type;
                if(type!=2234 /* moby class 2234 */ && type!=3335 /* Jobian Saur-Beast */ && type!=4304 /* Y.E.T.I. */ && type!=1143 /* Megacorp Vendor Logo */ && type!=11 /* Megacorp Vendor */) {
                    *hidden++=(char *)moby;
                    numhidden++;
                    moby->visible=0;
                } else {
                    FastVecSub(toMoby,moby->pos,goal);
                    axis=camera+48;
                    dot=FastVecDot(axis,toMoby);
                    FastVecScale(alongAxis,axis,dot);
                    FastVecSub(perpendicular,toMoby,alongAxis);
                    vec_scale_to_length(perpendicular,perpendicular,1.0f);
                    dot=FastVecDot(perpendicular,move);
                    {
                    float span=move->distance-state->offset;
                    span=dot/span;
                    angle=FastAngleHelper(span);
                    }
                    angle=FloatAbs(1.5707963705062866f-angle);
                    if(angle<0.4363323450088501f) {
                        FastVecCross(side,move,axis);
                        vec_scale_to_length(side,side,1.0f);
                        if(FastVecDot(side,toMoby)>0.0f)ApplyAxisRotationToQuaternion(move,move,camera+32,-0.01745329424738884f);
                        else ApplyAxisRotationToQuaternion(move,move,camera+32,0.01745329424738884f);
                    }
                }
            }
            scan++;
        }
    }
    if(!state->locked) {
        if(SweepFollowCameraProbe(obj)) blocked=1;
        if(CheckCameraNoop(obj)) blocked=1;
    }
    if(ProbeFollowCameraCollision(obj))blocked=1;
    {
    float currentDistance=move->distance;
    float minimum=D_L00_001B14CC;
    if(currentDistance-state->offset<minimum) {
        state->timer=2000;
        state->offset=currentDistance-minimum;
    }
    }
    {
    char *activeCamera=D_L00_001B8C80.active;
    if(activeCamera && ((cameraType=S(activeCamera,134))==4 || cameraType==81) && D_L00_001B8C80.counter<10) state->timer=1700;
    }
    if(!state->flag) {
        timer=(unsigned short)state->timer;
        if(blocked || !(((unsigned)(timer-1)<1999) ||
            (gPadState.x<0.3f && gPadState.y<0.3f))) goto hold;
    }
    if(FastDecTimer(&state->timer))state->flag=0;
    if(state->flag) {
        if(FastDecTimer(&state->timer))state->flag=0;
    }
    angle=IntToFloat(state->timer);
    angle=angle/IntToFloat(2000);
    state->offset=CosineBlend(0.0f,state->offset,angle);
    goto scaled;
hold:
    if((short)timer>2000)FastDecTimer(&state->timer);
    else state->timer=2000;
scaled:
    vec_scale_to_length(move,move,move->distance-state->offset);
    FastVecAdd(toMoby,move,pos+80);
    if(D_L00_00189E20.mode!=49 && !state->locked &&
       CollLine(pos+80,toMoby,D_L00_001B184C,D_L00_00189E20.owner,0) &&
       !IsPointInCollisionGrid(D_L00_001BF220)) {
        state->counter++;
        if(state->counter>=30)ResetDefaultCamera();
    } else state->counter=0;
    if(numhidden>0) {
        char **restore=D_L00_0025B9A0;
        int remaining=numhidden;
        do {
            entry=(Moby243 *)*restore++;
            entry->visible=entry->info->value;
        } while(--remaining);
    }
}
