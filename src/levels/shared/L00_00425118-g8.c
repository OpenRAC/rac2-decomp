#include "include_asm.h"
#include "names.h"
extern char D_L00_001B8E20[];
extern float D_L00_001B14AC __attribute__((sda)), D_L00_001B14B0 __attribute__((sda));
extern float D_L00_001B14B8 __attribute__((sda)), D_L00_001B14BC __attribute__((sda));
extern float D_L00_001B14C0 __attribute__((sda)), D_L00_001B14C4 __attribute__((sda));
extern float func_002702C8(void *,float,float,float,float,float);
extern float func_00282C48(float);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00283248(float,float);
extern float func_00283B98(float,float);
extern float func_00283BE0(float,float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Updates the camera turn for a vehicle from forward and turn input. It smooths the speed and bends the camera's direction toward the turn. */
void func_L00_00425118(char *obj,float forward,float turn)
{
    float axis[4];
    char *base=P(obj,112);
    char *state=base+448;
    char *movement=base+352;
    char *camera=D_L00_001B8E20;
    float factor, angle, length, dot, amount;
    F(state,0)=StepSpringDamperClamped(state+4,F(state,0),forward,D_L00_001B14AC,D_L00_001B14B0,0.0f);
    F(movement,52)=F(state,20)*F(state,0);
    if(turn<-0.3f) turn=(turn+0.3f)*1.4285714626312256f;
    else if(turn>0.3f) turn=(turn-0.3f)*1.4285714626312256f;
    else turn=0;
    if(turn==0) factor=D_L00_001B14BC;
    else if(FloatAbs(turn)<FloatAbs(F(state,8))) {
        factor = ((turn>0 && F(state,8)>0) || (turn<0 && F(state,8)<0))
            ? D_L00_001B14BC : D_L00_001B14B8;
    } else factor=D_L00_001B14B8;
    {
        float value=StepSpringDamperClamped(state+12,F(state,8),turn,D_L00_001B14AC,D_L00_001B14B0,factor);
        amount=D_L00_001B14C4*value;
        F(state,8)=value;
    }
    if(forward==0) ApplyAxisRotationToQuaternion(movement,movement,camera+32,F(state,32));
    else ApplyAxisRotationToQuaternion(movement,movement,camera+32,F(movement,52));
    dot=FastVecDot(movement,camera+32);
    length=FastVecLength(movement);
    FastVecCross(axis,camera+32,movement);
    vec_scale_to_length(axis,axis,1.0f);
    angle=FastMatrixHelperA(length,dot);
    if(FloatAbs(angle)<FloatAbs(amount) && factor==D_L00_001B14BC)
        F(state,8)=angle/D_L00_001B14C4;
    if(angle<amount) {
        if(amount<FastAddRotations(angle,D_L00_001B14C0))
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=D_L00_001B14C0;
    } else if(amount<angle && S(P(obj,112),552)>=0) {
        if(FastAddRotations(angle,-D_L00_001B14C0)<amount)
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=-D_L00_001B14C0;
    } else F(movement,56)=0;
    if(amount<0) S(P(obj,112),34)=1;
    ApplyAxisRotationToQuaternion(movement,movement,axis,F(movement,56));
}
