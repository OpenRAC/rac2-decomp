#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x1E0];
    short state;
    char pad2[0x14E];
    int a, b;
} HandlerState;
extern void func_002A7750(void *, int, int);
extern int func_L00_00324120(void *);
extern void func_002B0C28(int, int, int);
extern int D_00138324[];
extern int D_L19_001A8FB4 __attribute__((sda));
extern HandlerState D_00189E20;
extern char *D_L19_001B9A90[];
extern float D_L19_001B2420;
extern char *D_L19_001B2B0C;
extern float func_002AA2E8(float *, float, float);
extern void func_PAL_L00_00305110(int, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_002E59F8(int);

void func_PAL_L19_004170C8(char *obj)
{
    char *data = *(char **)(obj + 0x68);
    char *target;
    unsigned timer;
    int waiting;
    if (*(u8 *)(obj + 0x20) == 0) {
        *(u8 *)(obj + 0x30) = 255;
        func_002A7750(obj, 1, -1);
        *(int *)(data + 0x18) = -1;
    }
    if (*(u8 *)(obj + 0x20) == 1) {
        if (func_L00_00324120(obj)) {
            if (*(int *)(data + 8) == 0) func_002B0C28(8, 0x134C, 1);
            else if (*(int *)(data + 8) == 1) func_002B0C28(8, 0x134E, 1);
            else func_002B0C28(8, 0x134B, 1);
            if ((D_00138324[0] & 0x10) && D_L19_001A8FB4 == 8 && D_00189E20.state == 0 && *(short *)(D_L19_001B9A90[0]+0x86) != 5) {
                *(u16 *)(obj + 0x96) = 0;
                D_00189E20.state = 2;
                func_002A7750(obj, 2, -1);
            }
        }
    }
    if (*(u8 *)(obj + 0x20) == 2) {
        func_002AA2E8(&D_L19_001B2420, 1.0f, 0.040000003f);
        timer = *(u16 *)(obj + 0x96);
        waiting = timer++ < 0x1B;
        *(u16 *)(obj + 0x96) = timer;
        if (!waiting) {
            target = D_L19_001B2B0C + (*(int *)(data + 4)<<7);
            D_00189E20.a = 0;
            D_00189E20.b = 0;
            func_PAL_L00_00305110(*(int *)data, *(int *)(data + 0x10));
            func_PAL_L00_002B9CD8(target + 0x30, target + 0x70, 0, 1);
            D_L19_001B2420 = 1.0f;
            func_002A7750(obj, 3, -1);
        } else D_00189E20.state = 2;
    }
    if (*(u8 *)(obj + 0x20) == 3) {
        func_002AA2E8(&D_L19_001B2420, 0.0f, 0.040000003f);
        if (D_L19_001B2420 <= 0.0f) {
            D_L19_001B2420 = 0.0f;
            func_002A7750(obj, 1, -1);
            if (*(int *)(data + 0x18) != -1) {
                func_002E59F8(*(int *)(data + 0x18));
                *(int *)(data + 0x18) = -1;
            }
        }
    }
}
