#include "names.h"
/* Initialize the camera tracking parameters and resolve its initial target. */
#include "common.h"
extern int moby_get_joint_matrix(void *, void *, int, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern void moby_get_joint_midpoint(void *, int, void *);
/* Sets up a new camera object's tracking values and finds its first target position. */
void cam_moby_init_tracking(char *obj, int mode, int index, void *target, void *aim, unsigned char tag, float angle) {
    char *vars;
    float targetPos[4];
    *(int *)(obj+0x98) = 0;
    *(unsigned short *)(obj+0x34)|=0x100;
    vars = *(char **)(obj+0x68);
    qcopy(vars, target);
    qcopy(vars+0x10, aim);
    *(float *)(vars+0x38) = 0.45f;
    *(float *)(vars+0x3c) = 0.033333335f;
    *(float *)(vars+0x40) = 0.5f;
    *(float *)(vars+0x44) = 0.013089971616864204f;
    *(float *)(vars+0x48) = angle*0.00027777778f;
    *(float *)(vars+0x4c) = 0.0017453294713050127f;
    *(short *)(vars+0x34) = 180;
    vars[0x5e] = tag;
    vars[0x5d] = mode;
    vars[0x58] = 0;
    vars[0x5c] = 0;
    *(int *)(vars+0x30) = 0;
    switch (mode) {
        case 2:
        *(short *)(vars+0x36) = index;
        *(short *)(obj+0x7c) = (1<<index)|0x8000;
        vars[0x58] = moby_get_joint_matrix(obj, vars+0x20, *(int *)(vars+0x30), index);
        FastVecSub(vars+0x20, vars+0x20, obj+0x10);
        vec_transform_by_object_or_given(obj, vars+0x20, vars+0x20, 0);
        break;
        case 0: case 3:
        FastVecScale(vars+0x20, obj, 0.0009765625f);
        *(float *)(vars+0x2c) = *(float *)(obj+0xc)*0.0009765625f;
        FastVecSub(vars+0x20, vars+0x20, obj+0x10);
        vec_transform_by_object_or_given(obj, vars+0x20, vars+0x20, 0);
        break;
        case 1:
        *(short *)(vars+0x36) = index;
        *(short *)(obj+0x7c) = (mode<<index)|0x8000;
        moby_get_joint_midpoint(obj, index, targetPos);
        FastVecSub(vars+0x20, targetPos, obj+0x10);
        vec_transform_by_object_or_given(obj, vars+0x20, vars+0x20, 0);
        break;
    }
}
