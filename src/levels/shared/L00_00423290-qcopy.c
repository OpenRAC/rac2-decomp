#include "common.h"
/* Camera id/state fields are independently observed at the same offsets
 * as the public RAC1 Camera prefix (origin/main 1d8228cc). */
typedef struct {
    unsigned char bytes00[0x70];
    char *state;
    unsigned char bytes74[0x12];
    short id;
} CameraInitPrefix;
extern unsigned char D_00189E20[];


#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif

extern void func_00282CF0_2(void *b, void *c, void *d);

extern void func_00282CC0(void *c, void *c2, void *s);

extern void func_00282D30(void *dst, void *src, float k);

extern float func_00282DB0_1(char *local, char *p);

extern void func_00282C88(void *a);





/* Sets up the follow camera from the hero's position and facing. It starts the camera just behind the hero. */
void func_L00_00423290(CameraInitPrefix *camera)
{
    char *cameraState;
    char *transform;
    char *nearPoint;
    char *farPoint;
    char *movement;
    char *hero;
    char *workPtr;
    char *heroPosition;
    V4_F0fba48d3 *quadDest;
    char backDirection[16];
    char offsetBuf[16];

    if (camera->id != 0)
        return;

    hero = (char *)gHeroState + 0x2C0;
    workPtr = camera->state;
    movement = workPtr + 0x160;
    transform = workPtr + 0x60;
    cameraState = workPtr;
    workPtr = backDirection;

    FastVecScale(workPtr, hero, -1.0f);
    /* The hero's position, 0x240 below the facing direction the call above uses. */
    heroPosition = hero - 0x240;
    *(V4_F0fba48d3 *)transform = *(V4_F0fba48d3 *)heroPosition;
    quadDest = (V4_F0fba48d3 *)(cameraState + 0xC0);
    *quadDest = *(V4_F0fba48d3 *)transform;
    nearPoint = cameraState + 0xB0;
    farPoint = cameraState + 0xF0;
    FastVecScale(cameraState + 0x70, backDirection, func_00282DB0_1(transform, backDirection));
    ClearVector128(cameraState + 0xD0);
    ClearVector128(cameraState + 0xE0);
    ClearVector128(cameraState + 0x100);
    FastVecScale(offsetBuf, backDirection, *(float *)(movement + 0x30));
    FastVecAdd(nearPoint, offsetBuf, transform);
    FastVecScale(offsetBuf, backDirection, *(float *)(transform + 0xB0));
    FastVecAdd(farPoint, offsetBuf, transform);
    quadDest = (V4_F0fba48d3 *)(cameraState + 0xA0);
    *quadDest = *(V4_F0fba48d3 *)farPoint;
    func_00282CF0_2(movement, (char *)camera + 0x30, nearPoint);
    quadDest = (V4_F0fba48d3 *)(cameraState + 0x170);
    *quadDest = *(V4_F0fba48d3 *)movement;
    *(V4_F0fba48d3 *)cameraState = *(V4_F0fba48d3 *)((char *)camera + 0x30);
    FastVecAdd(cameraState + 0x210, nearPoint, movement);
    *(int *)(cameraState + 0x240) = 0;
}
