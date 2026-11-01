#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 normal, quaternion, matrix[3]; } GroundRotation;
extern void func_002AFDD8(char *,char *,char *,char *);
extern char D_00189E20[];
extern float func_00283248(float,float);
extern float func_00282C48(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282F20(void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);

void func_PAL_L16_00398E88(char *object)
{
    GroundRotation local;
    char *state=*(char **)(object+0x68);
    func_002AFDD8(object,(char *)&local.normal,D_00189E20,0);
    *(float *)(state+0x38)=-func_00283248(((float *)&local.normal)[0],((float *)&local.normal)[1]);
    if (*(float *)(state+0x38)>0.25132746f) {
        *(float *)(state+0x38)=0.25132746f;
    } else if (*(float *)(state+0x38)<-0.25132746f) *(float *)(state+0x38)=-0.25132746f;
    if (func_00282C48(*(float *)(state+0x38)) <= 0.00174532947f) return;
    func_00282F20(&local.quaternion,object+0xe0,func_00283198(*(float *)(state+0x38)*0.5f));
    ((float *)&local.quaternion)[3]=func_00283180(*(float *)(state+0x38)*0.5f);
    func_00283958(&local.quaternion,local.matrix);
    func_00283738(object+0xc0,local.matrix,object+0xc0);
}
