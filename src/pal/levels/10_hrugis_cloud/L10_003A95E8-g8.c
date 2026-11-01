#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char pad0[0x80]; Vec position; unsigned char pad90[0x294];
    float pitch; unsigned char pad328[0x20]; short allowed;
    unsigned char pad34a[0x1f46]; char *object;
} PlayerView;
extern PlayerView D_00189E20;
extern int D_L04_001A8FF0;
extern int D_L04_001A8FF4 __attribute__((sda));
extern float D_L04_001B0280 __attribute__((sda)),D_L04_001B0284 __attribute__((sda));
extern char *D_L04_001FB5A0[];
extern Vec D_L04_001BFAE0;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; } Collision;
extern Collision D_L04_001BFAC0;
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern char *func_002AB1F0(char *);
extern float func_00283248(float,float),func_00283C80(float,float),func_00282C48(float),func_002831B0(float),func_00283CE0(int);
extern float func_00282E80(void *,void *),func_00282E48(void *,void *),func_00282DB0(void *,void *),func_00282DF0(void *);
extern void func_002AF000(void *,float,float,float);

/* Target selection: the nearest visible candidate in front of the player within the aim cone. */
char *func_PAL_L10_003DD218(char *obj,Vec *origin,float *yaw,float *pitch) {
    struct { Vec origin,offset,player; char *disabled[128]; Vec target,aim,ray,axis; } frame;
    Vec *start=&frame.origin;
    char *ctx=*(char **)(obj+0x68),*selected,*candidate,*definition,*hit;
    Vec *pos; int n,index,accepted,visible,tries,i;
    float best=D_L04_001B0284,heading,elevation,delta,distance,dot,length,angle,radius;
    start->q=origin->q;
    func_00282D30(&frame.offset,D_00189E20.object+0xE0,0.5f);
    selected=0;
    func_00282CC0(&frame.player,D_00189E20.object+0x10,&frame.offset);
    if(func_002761F8(&frame.player,start,6,D_00189E20.object,0)) {
        qcopy(start,&D_L04_001BFAE0);
        return 0;
    }
    n=0; index=0;
    while((candidate=D_L04_001FB5A0[index])!=0) {
        if(*(unsigned char *)(candidate+0x20)==0xFE) goto next;
        if(*(unsigned char *)(candidate+0x20)==0xFD) goto next;
        if(*(short *)(candidate+0xAA)==0xE7D || *(short *)(candidate+0xAA)==0xEB0) goto next;
        { Vec *t=&frame.target; qcopy(t,candidate+0x10); }
        definition=func_002AB1F0(candidate);
        if(!definition || *(unsigned char *)(definition+0xE)==3) goto next;
        func_00282D30(&frame.aim,candidate+0xE0,*(float *)(definition+0x10));
        func_00282CC0(&frame.target,&frame.target,&frame.aim);
        if(!candidate || !*(char **)(candidate+0x24) || *(short *)(*(char **)(candidate+0x24)+0x46)!=5) goto next;
        accepted=0;
        heading=func_00283248(frame.target.f[0]-start->f[0],frame.target.f[1]-start->f[1]);
        elevation=func_00283248(func_00282E80(start,&frame.target),frame.target.f[2]-start->f[2]);
        delta=func_00283C80(*yaw,heading);
        distance=func_00282E48(start,&frame.target);
        if(D_L04_001A8FF0 || D_00189E20.allowed || D_L04_001A8FF4) {
            if(distance<2.5f) {
            func_00282CF0(&frame.ray,candidate+0x10,D_00189E20.object+0x10);
            dot=func_00282DB0(&frame.ray,D_00189E20.object+0xE0);
            if(func_00282C48(dot)<2.0f) {
                func_00282D30(&frame.axis,D_00189E20.object+0xE0,dot);
                func_00282CF0(&frame.ray,&frame.ray,&frame.axis);
                dot=func_00282DB0(&frame.ray,D_00189E20.object+0xC0);
                { float len=func_00282DF0(&frame.ray);
                if(len!=0.0f && 1.5707964f-func_002831B0(dot/len)<1.0471977f) accepted=1; }
            }
            }
        } else {
            if(distance<2.5f) {
                char *pobj=D_00189E20.object;
                angle=func_00283248(*(float *)(candidate+0x10)-D_00189E20.position.f[0],*(float *)(candidate+0x14)-D_00189E20.position.f[1]);
                if(func_00283C80(*(float *)(pobj+0xF8),angle)<1.0471977f && func_00282C48(start->f[2]-frame.target.f[2])<2.0f) accepted=1;
            }
        }
        if(accepted && !func_002761F8(start,&frame.target,6,D_00189E20.object,0)) { selected=candidate; *pitch=-elevation; *yaw=heading; break; }
        if((distance>best && candidate!=*(char **)(ctx+0x10)) || distance>D_L04_001B0284) goto next;
        func_002AF000(&frame.aim,distance,*yaw,*pitch+D_00189E20.pitch*0.5f);
        func_00282CC0(&frame.aim,&frame.aim,start);
        angle=func_00282E48(&frame.aim,&frame.target);
        angle=func_002831B0(angle/(distance+distance)); angle+=angle;
        if(D_L04_001B0280*0.017453294f<angle && (definition=func_002AB1F0(candidate))!=0) {
            radius=func_00283CE0((unsigned char)definition[10])*0.125f;
            length=func_002831B0(radius/distance);
            if(radius<distance) { angle-=length; if(angle<0.0f) angle=0.0f; }
        }
        if(angle<D_L04_001B0280*0.017453294f) {
            visible=1;
            qcopy(&frame.ray,start); tries=0;
            while(func_002761F8(&frame.ray,&frame.target,6,obj,0)) {
                Collision *col;
                if(++tries>6) break;
                col=&D_L04_001BFAC0;
                hit=col->hit;
                if(hit) {
                    if(*(short *)(hit+0xAA)==0xE7D || *(short *)(hit+0xAA)==0xEB0) {
                        frame.disabled[n++]=hit; *(int *)(hit+0x98)=0;
                        if(n>127) break;
                        qcopy(&frame.ray,&col->point);
                        continue;
                    }
                    if(hit==candidate) break;
                }
                visible=0; break;
            }
            if(visible) { *pitch=-elevation; best=distance; if(delta<0.17453295f) *yaw=heading; selected=candidate; if(candidate==*(char **)(ctx+0x10)) return selected; }
        }
next:
        ++index;
    }
    for(i=0;i<n;++i) { char *m=frame.disabled[i]; *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10); }
    return selected;
}
