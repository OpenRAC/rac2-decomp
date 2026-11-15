#include "common.h"
typedef int Qword_34A88 __attribute__((mode(TI)));
typedef union { Qword_34A88 q; float f[4]; } V651;
typedef struct { char p0[0x31C]; float distance; char p320[0x28]; short h348,h34A,h34C,h34E; char p350[0x14E]; unsigned char b49E; char p49F[15]; short h4AE; char p4B0[0x1DE4]; int i2294; } Hero651;
extern Hero651 D_00189E20;
extern char D_001B53A0[];
extern int D_001A8CA0;
extern float D_001B120C __attribute__((sda));
extern short D_001B11D8 __attribute__((sda)), D_001B11F0 __attribute__((sda)), D_001B11F4 __attribute__((sda)), D_001B1208 __attribute__((sda)), D_001B1220 __attribute__((sda));
extern float D_001B11C0 __attribute__((sda)), D_001B11C4 __attribute__((sda)), D_001B1234 __attribute__((sda));
extern float func_00282DB0(void *, void *), func_00282DF0(void *), func_00283CE0(int), func_003348A8(void *,float);
extern int func_00283CF0(float), func_00277258(void *,int,int,float),func_00282978(void *),func_00334730(void *,int);
extern void func_00282D30(void *,void *,float),func_00282CF0(void *,void *,void *),func_00282D08(void *,void *,void *,float);
extern void func_00334710(int, Qword_34A88 *);
extern void func_003349E8(void *,int,float);
#define H651(p,o) (*(short *)((p)+(o)))
#define F651(p,o) (*(float *)((p)+(o)))
#define I651(p,o) (*(int *)((p)+(o)))
#define B651(p,o) (*(unsigned char *)((p)+(o)))
void func_00334A88(char *obj, void *out)
{
    V651 base, temp;

    char *cam = D_001B53A0;
    char *state = *(char **)(obj+0x70)+0x60;
    char *axis;
    int mode, blocked;
    float f;
    if (D_00189E20.h348 || D_001A8CA0 || (H651(state,0xEE) && D_00189E20.h34E)) {
        H651(state,0xEC)=15;
        B651(state,0xD6)=1;
        H651(state,0xEE)=1;
        FastVecScale(state+0x10,cam+0x30,FastVecDot(state,cam+0x30));
        qcopy(state+0x20,state+0x10);
        mode=B651(state,0xC4);
        axis=cam+0x30;
        if ((unsigned)(mode-5)<3 || mode==3)
            func_003349E8(state+0x30,1,D_001B120C*0.5f);
    } else {
        if (H651(state,0xEE)==1) {
            FastVecScale(state+0x10,cam+0x30,FastVecDot(state,cam+0x30));
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=cam+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                func_003349E8(state+0x30,1,D_001B120C*0.5f);
            f=IntToFloat(H651(state,0xD8))/IntToFloat(15);
            H651(state,0xD8)=FloatToInt(IntToFloat(H651(state,0xEC))*f);
            H651(state,0xEE)=2;
        } else {
            axis=cam+0x30;
            if (H651(state,0xEE)>=2) {
            f=FastVecDot(state,axis);
            FastVecScale(state+0x10,axis,f);
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=cam+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                func_003349E8(state+0x30,1,D_001B120C*0.5f);
            if (++H651(state,0xEE)>=16) H651(state,0xEE)=0;
            }
        }
    }
    func_00334710((int)obj,&base.q);
    if (D_00189E20.i2294==0x74) {
        FastVecScale(out,axis,FastVecDot(state,axis));
        FastVecSub(state,state,out);
        FastVecScale(out,axis,FastVecDot(axis,state+0x60));
        qcopy(state+0x10,out);
        if (B651(state,0xC4)!=11) {
            char *p;
            B651(state,0xC4)=11;
            qcopy(obj+0x40,obj);
            p=*(char **)(obj+0x70)+0x20;
            H651(p,0)=D_001B11D8;
            F651(p,0x24)=1.0f/IntToFloat(H651(p,0));
        }
        return;
    }
    switch (B651(state,0xC4)) {
    case 2: {
        float angle;
        if (D_00189E20.i2294==17 || (D_00189E20.b49E && D_00189E20.distance>0.2f && ((angle=func_003348A8(obj,F651(state,0xB0)))<D_001B11C4 || angle>D_001B11C0))) {
            B651(state,0xC4)=1;
            H651(state,0xC6)=D_001B11F0;
            F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
        }
        blocked=0;
        if (D_00189E20.h34C && (!D_00189E20.b49E || D_00189E20.h4AE>=16)) blocked=1;
        else if (func_00334730(&temp,1)!=1) blocked=1;
        else {
            f=FastVecDot(&temp,axis);
            if (f<FastVecLength(state+0x10)) blocked=1;
        }
        if (blocked) {
            qcopy(out,state+0x10);
            f=FastVecDot(&base,axis);
            FastVecScale(&temp,axis,f);
            FastVecSub(state,&base,&temp);
        } else {
            func_00334730(&temp,1);
            FastVecScale(out,axis,FastVecDot(&temp,axis));
            FastVecSub(state,&temp,out);
        }
        break;
    }
    case 3: case 5: case 6: case 7:
        lerp_vector(state+0x10,state+0x30,state+0x20,(float)H651(state,0xD4)*F651(state,0xCC));
        if (!B651(state,0xD7) && func_00277258(obj+0x30,18,0,0.2f)) {
            qcopy(state+0x30,state+0x10); B651(state,0xD7)=1;
        }
        qcopy(out,state+0x10);
        f=FastVecDot(&base,axis);
        FastVecScale(&temp,axis,f);
        FastVecSub(state,&base,&temp);
        if (FastDecTimer(state+0xD4)) {
            if (B651(state,0xC4)==9) {
                B651(state,0xC4)=10; H651(state,0xD4)=D_001B1220;
                qcopy(state+0x20,state+0x10);
                FastVecScale(&temp,axis,F651(state,0xD0));
                FastVecSub(state+0x30,state+0x20,&temp);
            } else if (B651(state,0xC4)==6) {
                B651(state,0xC4)=7; H651(state,0xD4)=D_001B11F4;
                qcopy(state+0x30,state+0x20); qcopy(state+0x20,state+0x10);
            } else {
                B651(state,0xC4)=4; H651(state,0xC6)=D_001B1208;
                F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
            }
        }
        break;
    case 8:
        qcopy(out,state+0x10);
        f=FastVecDot(&base,axis);
        FastVecScale(&temp,axis,f);
        FastVecSub(state,&base,&temp);
        break;
    case 9: case 10:
        FastVecScale(out,axis,FastVecDot(&base,axis));
        FastVecSub(state,&base,out);
        lerp_vector(out,out,state+0x20,D_001B1234);
        break;
    default:
        FastVecScale(out,axis,FastVecDot(&base,axis));
        FastVecSub(state,&base,out);
        break;
    }
}
