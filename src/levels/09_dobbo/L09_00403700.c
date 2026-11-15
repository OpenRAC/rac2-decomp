/* func_L09_00403700 (152 bytes): while the object is in state 7, sparks four of its bones
   through func_002A8D70 with the controller's byte as the second coordinate. */
#include "common.h"

extern int func_002A8D70(float x, float y, float z, void *object, int bone, int mode, int first, int second, int third);

/* Makes sparks come off four of the object while it is in state 7. */
void func_L09_00403700(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    s32 i;

    if (*(u8 *)(obj + 0x20) == 7) {
        for (i = 0; i < 4; i++)
            TestHitAtBone(0.17f, *(u8 *)(vars + 0x34), 1.0f, obj, i, 0x4000001, 0, 1, 0);
    }
}
