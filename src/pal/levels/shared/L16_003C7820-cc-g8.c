/* func_PAL_L16_003C7820, the PAL copy of func_L16_003C3A10: the same C, where scale func_002A7820(D_L16_001B0410,D_L16_001B0414). */
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
char *func_PAL_L16_003C7820(char *parent,char *position,char *rotation)
{
    char *object=func_0029EFD0(0xa80);
    char *state;
    float factor;
    if (object != 0) {
        state=*(char **)(object+0x68);
        func_002B37E8(object,parent);
        factor=func_002A7878(D_L16_001B0418,D_L16_001B041C);
        *(float *)(object+0x2c)=*(float *)(*(char **)(object+0x24)+0x24)*factor;
        *(Vector128 *)(object+0x10)=*(Vector128 *)position;
        *(Vector128 *)(object+0xf0)=*(Vector128 *)rotation;
        func_002A7A00((float *)state,0.060000002f,0.14000002f);
        func_002A7A00((float *)(state+0x10),D_L16_001B0408*0.0003490659f,D_L16_001B040C*0.0003490659f);
        *(float *)(state+0x20)=func_002A7878(D_L16_001B0400,D_L16_001B0404)*0.00040000002f;
        *(int *)(state+0x24)=(((int)(func_002A7820(D_L16_001B0410,D_L16_001B0414)) * 5 + 2) / 6);
    }
    return object;
}
