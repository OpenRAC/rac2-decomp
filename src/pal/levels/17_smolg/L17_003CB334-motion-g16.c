#include "include_asm.h"

#include "common.h"
typedef unsigned int UpdateQuad __attribute__((mode(TI)));
typedef union { UpdateQuad q; float f[4]; } UpdateVec;
extern int D_L17_001B2748 MACRO_ADDR;
extern int D_L17_001C0018 NOT_SDA;
extern float D_L17_001B0390 __attribute__((sda));
extern UpdateVec D_L17_001B0380 __attribute__((sda));
extern char D_00189EA0[];
extern void *D_0018C0B0 NOT_SDA;
extern char D_L17_001A8F20[] __attribute__((sda));
extern float func_002A89A8(void *, int, float);
extern int func_L17_003C70E0(void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_L03_003268C0(void *, int, int, int, int, int, int, void *);
extern void func_002E5CF8(int, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

void func_PAL_L17_003CB334(char *self) {
    UpdateVec oldpos, delta;
    char collision[0x30];
    char *position;
    char *data = *(char **)(self + 0x68);
    float ground;
    if (*(int *)(data + 0xAC) == 1) return;
    position = self + 0x10;
    oldpos.q = *(UpdateQuad *)(self + 0x10);
    if (*(unsigned char *)(self + 0x20) == 0) {
        if (*(int *)(data + 0x90) != -1) {
            ground = func_002A89A8(position, 0, 0.5f);
            *(int *)(data + 0x9C) = D_L17_001C0018;
            if (ground < *(float *)(self + 0x18)) {
                *(float *)(data + 0x98) += D_L17_001B0390 * 0.00040000002f;
                *(float *)(self + 0x18) -= *(float *)(data + 0x98);
            } else {
                *(int *)(data + 0x98) = 0;
                *(float *)(self + 0x18) = ground;
            }
            if (func_L17_003C70E0(self)) {
                func_00283098(&delta, &D_L17_001B0380, self + 0xC0);
                func_002A8C00(collision, self, 0x10001, &delta, 2.0f);
                func_002A8E20(D_0018C0B0, collision);
            }
        }
    }
    if (D_L17_001B2748 >= 31) {
        if (*(int *)(data + 0xA4) == 0 && *(int *)(data + 0xA8) >= 43 &&
            func_00282E48(position, D_00189EA0) < 15.0f && *(unsigned char *)(self + 0x20) == 0) {
            func_L03_003268C0(self, 0x931, 0, 0x931, 4, 6, 0, D_L17_001A8F20);
            func_002E5CF8(0, 0, self);
            *(unsigned char *)(self + 0x20) = 1;
            *(int *)(self + 0x98) = 0;
            *(unsigned short *)(self + 0x34) |= 0x41;
            return;
        } else if (*(int *)(data + 0xA4)) {
            *(int *)(data + 0xA4) = 0;
            *(int *)(data + 0xA8) = 0;
        } else {
            *(int *)(data + 0xA8) += 1;
        }
    }
    func_00282CF0(&delta, position, &oldpos);
    func_002AD6F0(data + 0x50, &delta, self + 0xF0, self + 0xF0);
}
