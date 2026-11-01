/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
#include "common.h"
/* sol-high, 29 October 2026. Retained matching attempt.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * Current USA check: 1332/1336 bytes, 0/27 placements, first mismatch +0x8.
 * The earlier standalone draft was 1336/1336, also 0/27, with rematerialized
 * axis addresses. This draft retains the axis, uses partial typed state views,
 * separates the first length temporary and preserves the smoothing result.
 * GPR allocation remains different: retail retains settings in fp and spills
 * position at sp+0x50; this draft spills settings. Store/call scheduling differs.
 * -g recovers the measured division hazard nops; the complete body is still short.
 * RAC1 reference: src/overlays/shared/follow_camera.c, follow_camera_build_view
 * (func_L00_002EA4C0), with RAC2-specific rotation and banking logic retained.
 * Reopen with stronger evidence for the original camera pointer lifetimes.
 * Required declarations and partial structure views are included below.
 */
#include "include_asm.h"
extern char D_L00_001B8E20[] NOT_SDA;
extern char D_00189F00[];
extern int D_0018A160;
extern float D_L00_001B14C4 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D08(void *,void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_00282978(void *);
extern float func_00282DB0(void *,void *),func_00282DF0(void *);
extern float func_002702C8(void *,float,float,float,float,float);
extern float func_002703B0(void *,float,float,float,float,float);
extern float func_002831B0(float),func_00283248(float,float);
extern float func_00283BE0(float,float),func_00283CE0(int);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define H(p,n) (*(short *)((char *)(p)+(n)))
typedef struct {
    short h0, h2;
    float f4, f8;
    int iC, i10; float f14, f18;
    float f1C, f20, f24;
    float f28; int i2C, i30;
    float f34, f38;
    char pad3C[4];
} OrientationState;
typedef struct {
    float pos[4]; char pad10[0x40]; float direction[4]; char pad60[0x50];
    float fB0; int iB4; float fB8; int iBC, iC0;
    unsigned char bC4, bC5; short hC6;
    char padC8[0xE]; unsigned char bD6, bD7; short hD8, hDA;
    float fDC, fE0, fE4, fE8; short hEC, hEE;
    int iF0, iF4, iF8, iFC;
} CameraSettings;
typedef struct {
    float pos[4], previous[4]; int i20, i24, i28; float f2C, f30;
    int i34, i38; short h3C, h3E; char pad40[4]; int i44;
    float f48; char pad4C[4]; int i50; float f54, f58; char pad5C[4];
} MovementState;

void func_L00_00425560(char *obj)
{
    struct { float t[4],a[4],b[4],c[4],d[4]; } scratch;
    char *camera=D_L00_001B8E20, *axis;
    char *base=*(char **)(obj+112);
    CameraSettings *settings=(CameraSettings *)(base+96);
    OrientationState *state=(OrientationState *)(base+32);
    MovementState *move;
    char *pos,*right,*up;
    float len,delta,angle,dot,roll,x,vectorLength;
    if (settings->bC4==11) {
        func_00282CF0(obj,D_00189F00,obj+48);
        axis=camera+32;
        func_00282F20(obj,obj,1.0f);
        right=obj+16; up=obj+32;
        func_00282978(state);
    } else {
        char *v=base+160;
        char *moveBase;
        axis=camera+32;
        len=func_00282DB0(v,axis);
        pos=obj+48;
        func_00282D30(scratch.t,axis,len);
        func_00282CF0(scratch.a,v,scratch.t);
        moveBase=*(char **)(obj+112);
        move=(MovementState *)(moveBase+352);
        func_00282D30(scratch.t,axis,func_00282DB0(pos,axis));
        func_00282CF0(scratch.b,pos,scratch.t);
        func_00282CF0(scratch.c,scratch.a,scratch.b);
        if (state->f28!=0.0f) func_002ACEC0(scratch.c,scratch.c,axis,state->f28);
        vectorLength=func_00282DF0(scratch.c);
        if (vectorLength>=0.05f) func_00282D30(obj,scratch.c,1.0f/vectorLength);
        else {
            func_00282D30(scratch.d,axis,func_00282DB0(obj,axis));
            func_00282CF0(obj,obj,scratch.d);
        }
        right=obj+16;
        func_00282DD8(right,obj,axis);
        func_00282F20(right,right,1.0f);
        up=obj+32;
        roll=0.0f;
        state->f8=func_002702C8(&state->i10,state->f8,move->f30,0.004f,0.2f,0.0f);
        x=func_002702C8(&state->iC,state->f4,settings->fB0,0.004f,0.2f,0.0f);
        angle=state->f8-x;
        state->f4=x;
        func_00282D30(scratch.t,axis,-func_00282DB0(move->previous,axis));
        func_00282CF0(scratch.t,scratch.t,scratch.c);
        func_00282CF0(scratch.d,pos,scratch.t);
        func_00282D30(scratch.t,axis,-angle);
        func_00282CF0(scratch.d,scratch.d,scratch.t);
        func_00282CF0(scratch.c,scratch.d,pos);
        angle=func_00282DF0(scratch.c);
        if (angle!=0.0f) {
            angle=1.5707963705062866f-func_002831B0(func_00282DB0(obj,scratch.c)/angle);
            func_00282DD8(up,right,obj);
            if (func_00282DB0(up,scratch.c)<0.0f) angle=-angle;
            dot=func_00282DB0(move,axis);
            len=func_00282DF0(move);
            if (D_0018A160) {
                x=func_00283248(len,dot)/D_L00_001B14C4;
                if (x < -0.1f) {
                    x=-x;
                    if(x>0.5f) x=1.0f-x;
                    x=x+x;
                    roll=x*0.2617994248867035f;
                }
            }
            state->f14=func_002703B0(&state->f18,state->f14,roll,state->f1C,state->f20,0.0f);
            angle=func_00283BE0(angle,state->f14);
            if(angle>1.2217305898666382f) angle=1.2217305898666382f;
            else if(angle < -1.2217305898666382f) angle=-1.2217305898666382f;
            func_002ACEC0(obj,obj,right,angle);
            func_00282F20(obj,obj,1.0f);
        }
    }
    if(state->h0) {
        func_00282978(state);
        x=func_00283CE0(state->h0);
        func_00282D08(obj,obj,obj+64,x*state->f24);
        func_00282F20(obj,obj,1.0f);
    }
    func_00282DD8(right,obj,axis);
    func_00282F20(right,right,1.0f);
    func_00282DD8(up,right,obj);
}
