/* func_PAL_L00_004298B0, the PAL copy of func_L00_004243C0: the same C, where rename func_L00_004240D8 becomes func_PAL_L00_004295B8. */
#include "common.h"

/* func_PAL_L00_004298B0: -G8 for the $gp tuning value, -g for the line labels around the
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
extern int func_PAL_L00_004295B8(void *),func_L00_00423BB0(void *),func_L00_004239A8(void *);
extern int func_00282978(short *);
extern float func_00283CE0(int),func_002A7C00(float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002761F8(void *,void *,void *,void *,int),func_L00_004204A0(void *);
extern void func_L00_002D9D98(void);
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
typedef struct { char pad[16]; float pos[4]; char pad20[4]; struct { char pad[16]; int value; } *info; char pad28[112]; int visible; char pad9C[14]; short type; } Moby243;
typedef struct { char pad[44]; float distance; } Move243;
typedef struct { char pad[48]; float offset; short timer; char gap[4]; short flag; char gap2[16]; short counter, locked; } State243;
void func_PAL_L00_004298B0(char *obj)
{
    char *base=P(obj,112);
    char *pos=base+96;
    Move243 *move=(Move243 *)(base+352);
    State243 *state=(State243 *)(base+496);
    char *camera=D_L00_001B8E20;
    char a[16],b[16],c[16],d[16],e[16];
    Moby243 *m;
    char *axis;
    int count,n,blocked=0,numhidden=0,type,camera_type,i;
    float distance=move->distance-state->offset+1.5f;
    float dot,t;
    unsigned short timer;
    Moby243 *entry;
    char *goal;
    func_00282D08(a,base+176,camera-96,0.5f);
    count=func_00277F48(a,1,D_L00_00189E20.owner,0,distance*0.5f);
    if(count>0) {
        char **scan,**hidden;
        scan=D_L00_001C3280;
        hidden=D_L00_0025B9A0;
        for(i=0;i<count;i++) {
            goal=base+176;
            m=(Moby243 *)*scan;
            if(m->visible && (!func_L00_0031BE88(m)||m->type==2923)) {
                type=m->type;
                if(type!=2234 && type!=3335 && type!=4304 && type!=1143 && type!=11) {
                    *hidden++=(char *)m;
                    numhidden++;
                    m->visible=0;
                } else {
                    func_00282CF0(b,m->pos,goal);
                    axis=camera+48;
                    dot=func_00282DB0(axis,b);
                    func_00282D30(c,axis,dot);
                    func_00282CF0(d,b,c);
                    func_00282F20(d,d,1.0f);
                    dot=func_00282DB0(d,move);
                    {
                    float span=move->distance-state->offset;
                    span=dot/span;
                    t=func_002831B0(span);
                    }
                    t=func_00282C48(1.5707963705062866f-t);
                    if(t<0.4363323450088501f) {
                        func_00282DD8(e,move,axis);
                        func_00282F20(e,e,1.0f);
                        if(func_00282DB0(e,b)>0.0f)func_002ACEC0(move,move,camera+32,-0.01745329424738884f);
                        else func_002ACEC0(move,move,camera+32,0.01745329424738884f);
                    }
                }
            }
            scan++;
        }
    }
    if(!state->locked) {
        if(func_PAL_L00_004295B8(obj)) blocked=1;
        if(func_L00_00423BB0(obj)) blocked=1;
    }
    if(func_L00_004239A8(obj))blocked=1;
    {
    float current_distance=move->distance;
    float minimum=D_L00_001B14CC;
    if(current_distance-state->offset<minimum) {
        state->timer=1667;
        state->offset=current_distance-minimum;
    }
    }
    {
    char *active_camera=D_L00_001B8C80.active;
    if(active_camera && ((camera_type=S(active_camera,134))==4 || camera_type==81) && D_L00_001B8C80.counter<8) state->timer=1417;
    }
    if(!state->flag) {
        timer=(unsigned short)state->timer;
        if(blocked || !(((unsigned)(timer-1)<1666) ||
            (D_00138180.x<0.3f && D_00138180.y<0.3f))) goto hold;
    }
    if(func_00282978(&state->timer))state->flag=0;
    if(state->flag) {
        if(func_00282978(&state->timer))state->flag=0;
    }
    t=func_00283CE0(state->timer);
    t=t/func_00283CE0(1667);
    state->offset=func_002A7C00(0.0f,state->offset,t);
    goto scaled;
hold:
    if((short)timer>1667)func_00282978(&state->timer);
    else state->timer=1667;
scaled:
    func_00282F20(move,move,move->distance-state->offset);
    func_00282CC0(b,move,pos+80);
    if(D_L00_00189E20.mode!=49 && !state->locked &&
       func_002761F8(pos+80,b,D_L00_001B184C,D_L00_00189E20.owner,0) &&
       !func_L00_004204A0(D_L00_001BF220)) {
        state->counter++;
        if(state->counter>=25)func_L00_002D9D98();
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
