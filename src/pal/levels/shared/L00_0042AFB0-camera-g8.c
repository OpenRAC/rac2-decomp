#include "include_asm.h"

extern char D_L00_001B8E20[];
typedef struct { char pad[0x2290]; char *owner; int mode; char pad2[0x1c]; unsigned char flag; } CameraPlayer;
extern CameraPlayer D_L00_00189E20;
extern float D_L00_001B14E0 __attribute__((sda)), D_L00_001B14E4 __attribute__((sda));
extern float D_L00_001B1508 __attribute__((sda)), D_L00_001B150C __attribute__((sda));
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern void func_L00_00424A08(int, float, float);
#define F(p,n) (*(float *)((p)+(n)))
#define S(p,n) (*(short *)((p)+(n)))
#define P(p,n) (*(char **)((p)+(n)))

void func_PAL_L00_0042AFB0(char *obj, float *out1, float *out2)
{
    char *base = P(obj,112);
    char *state = base+576;
    char *movement = base+352;
    char *camera = D_L00_001B8E20;
    float t, target, value;
    if (!S(state,6) && ((S(state,4) && F(camera,164)==0.0f &&
         func_00282DB0(D_L00_00189E20.owner+192,obj)<=-0.3f) ||
        (func_00282C48(F(camera,164))>0.0001f &&
         func_00282DB0(camera+128,obj)<=-0.3f))) {
        S(state,4)=100;
        t=F(camera,164)*14.285699844360352f;
        if (t>1.0f) t=1.0f;
        target = D_L00_00189E20.flag==1 ? 4.0f : F(state,12);
        value=F(movement,88)+(target-F(movement,88))*t;
        if (value>F(state,8)) F(state,8)=value;
        func_L00_00424A08(0,F(state,8),0.003000000026077032f);
        *out1=D_L00_001B14E0+(D_L00_001B1508-D_L00_001B14E0)*t;
        *out2=D_L00_001B14E4+(D_L00_001B150C-D_L00_001B14E4)*t;
    } else {
        if (S(state,4)) {
            S(state,4)=0;
            F(state,8)=F(movement,88);
        }
        if (D_L00_00189E20.mode==132) {
            *out1=0.04f;
            *out2=0.2f;
        } else {
            *out1=D_L00_001B14E0;
            *out2=D_L00_001B14E4;
        }
    }
}
