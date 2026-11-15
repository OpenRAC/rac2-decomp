#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *,void *);
extern float func_002A7878(float,float);
extern void func_002A7A00(float *,float,float);
extern int func_002A7820(int,int);
extern float D_L16_001B0418 __attribute__((sda));
extern float D_L16_001B041C __attribute__((nosda));
extern float D_L16_001B0408 __attribute__((sda));
extern float D_L16_001B040C __attribute__((nosda));
extern float D_L16_001B0400 __attribute__((sda));
extern float D_L16_001B0404 __attribute__((nosda));
extern int D_L16_001B0410 __attribute__((sda));
extern int D_L16_001B0414 __attribute__((nosda));
/* Creates a new object (moby class 2688) at the given spot with a random size, spin and lifetime. */
char *func_L16_003C3A10(char *parent,char *position,char *rotation)
{
    char *object=CreateMoby(0xa80);
    char *state;
    float factor;
    if (object != 0) {
        state=*(char **)(object+0x68);
        InitChildObjectFromParent(object,parent);
        factor=RandomFloatRange(D_L16_001B0418,D_L16_001B041C);
        *(float *)(object+0x2c)=*(float *)(*(char **)(object+0x24)+0x24)*factor;
        *(Vector128 *)(object+0x10)=*(Vector128 *)position;
        *(Vector128 *)(object+0xf0)=*(Vector128 *)rotation;
        RandomDirectionVector((float *)state,0.05000000447f,0.1166666746f);
        RandomDirectionVector((float *)(state+0x10),D_L16_001B0408*0.0002908882452f,D_L16_001B040C*0.0002908882452f);
        *(float *)(state+0x20)=RandomFloatRange(D_L16_001B0400,D_L16_001B0404)*0.0002777777845f;
        *(int *)(state+0x24)=RandomIntRange(D_L16_001B0410,D_L16_001B0414);
    }
    return object;
}
