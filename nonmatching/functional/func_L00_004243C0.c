/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: sol-high (v1110), USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections -g, separate -g8.c unit.
 * Best rechecked result: 1404/1404 bytes, 0/27 places, first mismatch +0x8.
 * Separate restoration pointer, entry and counter locals recover camera in fp,
 * loop temporaries in s5/s6/s7, and the final six-instruction restoration loop.
 * The hold-label control flow plus a real unsigned timer snapshot recovers the
 * timer region's ordering and signed conversion at the hold path. Separate
 * division source lines and -g restore both measured pairs of pre-divide nops.
 * Typed global views and a scoped distance/minimum snapshot recover the camera
 * object's base addressing and avoid the distance reload after timer storage.
 * Remaining: initial target pointer spills at entry rather than at loop entry,
 * shifting the pointer/flag/count stack slots; prologue and call scheduling,
 * early-skip loop branch, and retained timer-pointer allocation differ.
 * Adding a timer pointer recovers part of that region but swaps movement/state
 * registers and grows to 1412 bytes. A loop-local target alias and aggregate
 * vector scratch each tie their plain forms. No linked build run.
 * Required declarations are included below. Next: recover the initial target's
 * lifetime/spill transition and timer-pointer lifetime without fake dependencies.
 */
#include "include_asm.h"
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
typedef struct { char pad[44]; float distance; } Move243;
typedef struct { char pad[48]; float offset; short timer; char gap[4]; short flag; char gap2[16]; short counter, locked; } State243;
void func_L00_004243C0(char *obj)
{
    char *base=P(obj,112),*target=base+176,*pos=base+96;
    Move243 *move=(Move243 *)(base+352);
    State243 *state=(State243 *)(base+496);
    char *camera=D_L00_001B8E20;
    char a[16],b[16],c[16],d[16],e[16];
    char **scan,**hidden;
    char *m,*axis;
    int count,n,blocked=0,numhidden=0,type,i;
    float distance=move->distance-state->offset+1.5f;
    float dot,t;
    unsigned short timer;
    func_00282D08(a,target,camera-96,0.5f);
    count=func_00277F48(a,1,D_L00_00189E20.owner,0,distance*0.5f);
    if(count>0) {
        scan=D_L00_001C3280;
        hidden=D_L00_0025B9A0;
        n=count;
        do {
            m=*scan;
            if(I(m,152) && (!func_L00_0031BE88(m)||S(m,170)==2923)) {
                type=S(m,170);
                if(type!=2234 && type!=3335 && type!=4304 && type!=1143 && type!=11) {
                    *hidden=m;
                    numhidden++;
                    I(m,152)=0;
                    hidden++;
                } else {
                    func_00282CF0(b,m+16,target);
                    axis=camera+48;
                    dot=func_00282DB0(axis,b);
                    func_00282D30(c,axis,dot);
                    func_00282CF0(d,b,c);
                    func_00282F20(d,d,1.0f);
                    dot=func_00282DB0(d,move);
                    t=move->distance-state->offset;
                    t=dot/t;
                    t=func_002831B0(t);
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
        } while(--n);
    }
    if(!state->locked) {
        if(func_L00_004240D8(obj)) blocked=1;
        if(func_L00_00423BB0(obj)) blocked=1;
    }
    if(func_L00_004239A8(obj))blocked=1;
    {
    float current_distance=move->distance;
    float minimum=D_L00_001B14CC;
    if(current_distance-state->offset<minimum) {
        state->timer=2000;
        state->offset=current_distance-minimum;
    }
    }
    {
    char *active_camera=D_L00_001B8C80.active;
    if(active_camera && (S(active_camera,134)==4 || S(active_camera,134)==81) && D_L00_001B8C80.counter<10) state->timer=1700;
    }
    if(!state->flag) {
        timer=(unsigned short)state->timer;
        if(blocked || !(((unsigned)(timer-1)<1999) ||
            (D_00138180.x<0.3f && D_00138180.y<0.3f))) goto hold;
        if(func_00282978(&state->timer))state->flag=0;
    }
    if(state->flag) {
        if(func_00282978(&state->timer))state->flag=0;
    }
    t=func_00283CE0(state->timer);
    t=t/func_00283CE0(2000);
    state->offset=func_002A7C00(0.0f,state->offset,t);
    goto scaled;
hold:
    if((short)timer>2000)func_00282978(&state->timer);
    else state->timer=2000;
scaled:
    func_00282F20(move,move,move->distance-state->offset);
    func_00282CC0(b,move,pos+80);
    if(D_L00_00189E20.mode!=49 && !state->locked &&
       func_002761F8(pos+80,b,D_L00_001B184C,D_L00_00189E20.owner,0) &&
       !func_L00_004204A0(D_L00_001BF220)) {
        state->counter++;
        if(state->counter>=30)func_L00_002D9D98();
    } else state->counter=0;
    if(numhidden>0) {
        char **restore=D_L00_0025B9A0;
        int remaining=numhidden;
        char *entry;
        do {
            entry=*restore++;
            I(entry,152)=I(P(entry,36),16);
        } while(--remaining);
    }
}
