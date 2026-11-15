#include "include_asm.h"
#include "names.h"
typedef unsigned int Quad __attribute__((mode(TI)));

extern char D_00139568[];
extern char D_L00_00262570[];
extern char D_L00_001C3280[];
extern float func_00283CE0(int);
extern float func_002AA140(float,float,float);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_002A9850(void *,void *,void *,int,int,int,int,int,float,float,float);
extern void func_0029F338(void *);


/* Each frame, tests a growing area in front of the weapon for a hit and applies damage, then removes the object after 15 frames. */
void func_L00_0038F020(unsigned char *object)
{
    Quad local;
    unsigned char *globals=(unsigned char *)gItemSlotToRecord;
    unsigned char *table=(unsigned char *)gWeaponTable_L00;
    float limit, amount;
    int effect;
    *(unsigned short *)(object+0x34)|=0x41;
    limit=(IntToFloat(table[globals[12]*0xE0+4]!=0)+1.0f)*3.0f-0.5f;
    amount=IntToFloat(object[0xBC]);
    amount=LerpFloat_002AA140(0.5f,limit,amount*0.06666667014360428f);
    effect=ProcessCollisionHit(amount, object+0x10, 0x10, object, 0);
    local=*(Quad *)(object+0x10);
    QueueKnockbackForNodes(object,&local,gAreaHitTargets,effect,0,0x830000,2,1,*(float *)(table+globals[12]*0xE0+0x70),1.0f,1.0f);
    object[0xBC]++;
    if(object[0xBC]>15) MarkMobySpawned(object);
}
