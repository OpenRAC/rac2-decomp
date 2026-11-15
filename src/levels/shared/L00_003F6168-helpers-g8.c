#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *func_L00_0032A088(int,int);
extern char *func_L00_0032A0B8(int,int);
extern int func_00282978(char *);
extern void func_00282F20(char *,char *,float);
extern void func_00282CC0(char *,char *,char *);
extern float D_L00_001B0988 __attribute__((sda));
extern float D_L00_001B09C0 __attribute__((sda));
extern float D_L00_001B099C __attribute__((sda));
#define RECORD (base + *(short *)(state + 0x18) * 0x60)
int func_L00_003F6168(char *object)
{
    TI128 step;
    int index;
    char *state = *(char **)(object + 0x68);
    char *base = func_L00_0032A088(0xc04,*(short *)(state + 0x1a));
    base += *(int *)func_L00_0032A0B8(0xc04,*(short *)(state + 0x1a));
    if (*(short *)(RECORD + 0x50) == 0) return 0;
    if (FastDecTimer(RECORD + 0x52) != 0) {
        *(short *)(RECORD + 0x50) = 0;
        return 0;
    }
    index = *(short *)(state + 0x18);
    qcopy(base + index*0x60 + 0x20,object + 0x10);
    *(float *)(base + index*0x60 + 0x54) += D_L00_001B0988;
    if (*(float *)(RECORD + 0x54) >= 4.0f) *(float *)(RECORD + 0x54) -= 4.0f;
    *(float *)(RECORD + 0x58) += D_L00_001B09C0;
    if (*(float *)(RECORD + 0x58) >= 4.0f) *(float *)(RECORD + 0x58) -= 4.0f;
    vec_scale_to_length((char *)&step,state,D_L00_001B099C * 0.016666668f);
    FastVecAdd(RECORD,RECORD,(char *)&step);
    FastVecAdd(RECORD+0x10,RECORD+0x10,(char *)&step);
    return 1;
}
#undef RECORD
