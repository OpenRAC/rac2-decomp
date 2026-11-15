#include "common.h"

typedef unsigned int GroupEffectQuad __attribute__((mode(TI)));
extern void func_0029FCC0(char *,int,float *);
extern void func_0029FC20(char *,int,float *);
extern void func_002830C0(float *,float *,float *);
/* Integer and FP arguments retain their order in the separate EE banks. */
extern void func_00325638(int, char *, float, int, int, int);
extern short *D_001EE5A0[];
extern char *D_001B1B5C;
extern int D_001B1B78 __attribute__((sda));

/* Draws glowing effects at three joints of the object and of the other members of its group. */
void func_00325EC0(unsigned char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float other[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    short *list;
    unsigned char *object;
    if ((unsigned char)self[0x21] == 255) {
        if ((unsigned char)self[0x31]) {
            *(GroupEffectQuad *)offset = 0;
            offset[0] = 0.25f; offset[3] = 1.0f;
            TransformMobyJointToWorld(self,4,pos);
            TransformMobyJointToWorld(self,5,other);
            TransformMobyJointPoint(self,6,matrix);
            transform_vector(offset,offset,matrix);
            DrawCameraFacingFlashB((int)self,(char *)pos,0.125f,0x36F6,0x20000000,0x20000000);
            DrawCameraFacingFlashB((int)self,(char *)other,0.15f,0xFF3E00,0x30000000,0x20000000);
            DrawCameraFacingFlashB((int)self,(char *)offset,0.15f,0xFF3E00,0x10000000,0x30000000);
        }
    } else {
        list = D_001EE5A0[(unsigned char)self[0x21]];
        while ((unsigned char)self[0x21] != 255 && (unsigned char)self[0x21] <= D_001B1B78 && list && ((list && list[-1] >= 0) || list == D_001EE5A0[(unsigned char)self[0x21]])) {
            object = D_001B1B5C + ((unsigned short)*list & 0x7FFF) * 256;
            if (!object) break;
            if (object[0x20] == 254) goto next;
            if (object[0x20] == 253) goto next;
            if ((unsigned char)object[0x31] && *(short *)(object+0xAA) == *(short *)(self+0xAA)) {
                *(GroupEffectQuad *)offset = 0;
                offset[0] = 0.25f; offset[3] = 1.0f;
                TransformMobyJointToWorld(object,4,pos);
                TransformMobyJointToWorld(object,5,other);
                TransformMobyJointPoint(object,6,matrix);
                transform_vector(offset,offset,matrix);
                DrawCameraFacingFlashB((int)object,(char *)pos,0.125f,0x36F6,0x20000000,0x20000000);
                DrawCameraFacingFlashB((int)object,(char *)other,0.15f,0xFF3E00,0x30000000,0x20000000);
                DrawCameraFacingFlashB((int)object,(char *)offset,0.15f,0xFF3E00,0x10000000,0x30000000);
            }
next:
            list++;
        }
    }
}
