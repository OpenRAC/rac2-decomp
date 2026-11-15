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
/* Tilts the object to follow the slope of the ground under it, within a small angle limit. */
void func_L16_00395C00(char *object)
{
    GroundRotation local;
    char *state=*(char **)(object+0x68);
    TransformVectorByObjectOrGiven(object,(char *)&local.normal,gHeroState,0);
    *(float *)(state+0x38)=-FastMatrixHelperA(((float *)&local.normal)[0],((float *)&local.normal)[1]);
    if (*(float *)(state+0x38)>0.2094395459f) {
        *(float *)(state+0x38)=0.2094395459f;
    } else if (*(float *)(state+0x38)<-0.2094395459f) *(float *)(state+0x38)=-0.2094395459f;
    if (FloatAbs(*(float *)(state+0x38)) <= 0.00174532947f) return;
    vec_scale_to_length(&local.quaternion,object+0xe0,FastSinOrCosB(*(float *)(state+0x38)*0.5f));
    ((float *)&local.quaternion)[3]=FastSinOrCosA(*(float *)(state+0x38)*0.5f);
    quaternion_to_rotation_basis(&local.quaternion,local.matrix);
    multiply_matrix3x3(object+0xc0,local.matrix,object+0xc0);
}
