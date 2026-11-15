#include "common.h"

extern void func_002A7750(unsigned char *, int, int);
extern float func_00283B98(float, float);
extern float func_00282DF0(void *);
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_0036AE00(int, int);

extern int D_L07_001C9780 __attribute__((nosda));
extern unsigned short **D_L07_001A9014;
extern unsigned char *D_L07_001B295C;
extern float D_L07_001AEBF8[] SDATA(D_L07_001AEBF8);

typedef struct {
    int groups[3];
    float angles[3];
} RotState;

/* Slowly spins the linked groups of level pieces around their own centers. */
void func_L07_00378898(unsigned char *moby)
{
    RotState *groupState = *(RotState **)(moby + 0x68);
    int i;
    unsigned short *matrixIndexPtr;
    unsigned char *matrixEntry;
    float rotation[4];
    float loc[3];
    float *savedPos;
    int axisIndex;
    int axisIndex2;
    float scale;
    float newAngle;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (D_L07_001C9780 != 0)
            return;
        for (i = 0; i < 3; i++) {
            if (groupState->groups[i] == -1) {
                continue;
            }
            /* The transfer helper also preserves the original address recomputation. */
            qzero_nc(rotation);
            newAngle = FastAddRotations(groupState->angles[i], D_L07_001AEBF8[i] * 0.00029088824f);
            groupState->angles[i] = newAngle;
            rotation[2] = newAngle;
            for (matrixIndexPtr = D_L07_001A9014[groupState->groups[i]];
                 matrixIndexPtr != 0 && ((short)matrixIndexPtr[-1] >= 0 || matrixIndexPtr == D_L07_001A9014[groupState->groups[i]]);
                 matrixIndexPtr++) {
                matrixEntry = D_L07_001B295C + ((*matrixIndexPtr & 0x7FFF) << 6);
                if (matrixEntry == 0)
                    break;
                savedPos = loc;
                for (axisIndex = 0; axisIndex < 3; axisIndex++)
                    savedPos[axisIndex] = *(float *)(matrixEntry + 0xC + axisIndex * 16);
                scale = FastVecLength(matrixEntry);
                euler_rotation_basis(matrixEntry, rotation);
                vec_scale_to_length(matrixEntry, matrixEntry, scale);
                vec_scale_to_length(matrixEntry + 0x10, matrixEntry + 0x10, scale);
                for (axisIndex2 = 0; axisIndex2 < 3; axisIndex2++)
                    *(float *)(matrixEntry + 0xC + axisIndex2 * 16) = savedPos[axisIndex2];
                SetupScaleRecord(*matrixIndexPtr & 0x7FFF, 1);
            }
        }
        break;
    }
}
