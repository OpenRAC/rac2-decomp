#include "include_asm.h"

#include "common.h"
extern float D_L17_001B0328 __attribute__((sda));
extern int D_L17_001C0018 NOT_SDA;
extern unsigned char D_L17_001DBF81[];
extern char *D_L17_001DAD00[];
extern float func_002A89A8(void *, int, float);
extern void func_002A7398(void *, int, int);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
typedef unsigned int StateQuad __attribute__((mode(TI)));

void func_PAL_L17_003C9D00(char *self) {
    union { StateQuad q; float f[4]; } oldpos, delta;
    char *data = *(char **)(self + 0x68);
    float ground;
    unsigned char index;
    oldpos.q = *(StateQuad *)(self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (*(int *)(data + 0x90) != -1) {
            ground = func_002A89A8(self + 0x10, 0, 0.5f);
            *(int *)(data + 0x9C) = D_L17_001C0018;
            if (ground < *(float *)(self + 0x18)) {
                *(float *)(data + 0x98) += D_L17_001B0328 * 0.00040000002f;
                *(float *)(self + 0x18) -= *(float *)(data + 0x98);
            } else {
                *(int *)(data + 0x98) = 0;
                *(float *)(self + 0x18) = ground;
            }
        }
        break;
    case 1:
        if (*(unsigned char *)(self + 0x42) == 1 && (*(unsigned char *)(self + 0x60) & 2)) {
            *(short *)(self + 0xAA) = 0x921;
            index = D_L17_001DBF81[0];
            *(unsigned char *)(self + 0x22) = index;
            *(char **)(self + 0x24) = D_L17_001DAD00[*(unsigned char *)(self + 0x22)];
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            func_002A7398(self, 0, 0);
            *(unsigned char *)(self + 0x20) = 2;
            if (*(int *)(data + 0x90) != -1) *(int *)(data + 0x94) = 500;
        }
        break;
    case 2:
        if (*(int *)(data + 0x90) != -1 && func_00282948(data + 0x94)) {
            func_0029F338(self);
            return;
        }
        break;
    }
    func_00282CF0(&delta, self + 0x10, &oldpos);
    func_002AD6F0(data + 0x50, &delta, self + 0xF0, self + 0xF0);
}
