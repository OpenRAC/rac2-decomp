#include "include_asm.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern char D_00139568[];
extern char D_L00_00262570[];
extern char D_L00_001C3280[];
extern float func_00283CE0(int);
extern float func_002AA140(float,float,float);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_002A9850(void *,void *,void *,int,int,int,int,int,float,float,float);
extern void func_0029F338(void *);

void func_PAL_L00_003920F8(unsigned char *object)
{
    Quad local;
    unsigned char *globals=(unsigned char *)D_00139568;
    unsigned char *table=(unsigned char *)D_L00_00262570;
    float limit, amount;
    int effect;
    *(unsigned short *)(object+0x34)|=0x41;
    limit=(func_00283CE0(table[globals[12]*0xE0+4]!=0)+1.0f)*3.0f-0.5f;
    amount=func_00283CE0(object[0xBC]);
    amount=func_002AA140(0.5f,limit,amount*0.083333336f);
    effect=func_00277F48(amount, object+0x10, 0x10, object, 0);
    local=*(Quad *)(object+0x10);
    func_002A9850(object,&local,D_L00_001C3280,effect,0,0x830000,2,1,*(float *)(table+globals[12]*0xE0+0x70),1.0f,1.0f);
    object[0xBC]++;
    if(object[0xBC]>12) func_0029F338(object);
}
