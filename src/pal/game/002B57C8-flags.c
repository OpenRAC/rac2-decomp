#include "include_asm.h"

extern int D_001B1688 __attribute__((sda));
extern char *func_002B5D28(void *);
extern void func_002B5CD8(void *, void *);
extern void func_002B5BC0(void *, void *, float);
extern void func_00282C88(void *);
extern void func_PAL_002B5E58(void *, void *, void *, void *, void *, float);
extern void func_002B5678(void *, void *, void *, void *);
extern void func_PAL_002B63E0(void *, void *, void *, void *);
extern void func_002B5EF8(void *, void *, float);
extern void func_002B62A0(void);
typedef int PoseVector128 __attribute__((mode(TI)));

int func_PAL_002B5C98(void *self, void *target, float amount)
{
    char *data = func_002B5D28(self);
    PoseVector128 work[3];

    if (data == 0)
        return 8;
    if (D_001B1688 == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    if (!(*(int *)(data + 0x38) & 0x100))
        func_002B5CD8(self, data);
    {
        PoseVector128 *src = (PoseVector128 *)((char *)self + 0x10);
        work[0] = *src;
    }
    if (D_001B1688 - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
        func_002B5BC0(self, data, 0.0f);
        *(unsigned char *)(data + 0xEA) = 0xFF;
        *(int *)(data + 0x9C) &= ~2;
        *(float *)(data + 0xB4) = 0.0f;
        *(int *)(data + 0x80) = 0;
        func_00282C88(data + 0xA0);
    }
    *(int *)(data + 0xBC) = D_001B1688;
    func_PAL_002B5E58(self, data, target, &work[1], &work[2], amount);
    func_002B5678(self, data, &work[0], &work[2]);
    func_PAL_002B63E0(self, data, target, &work[0]);
    func_002B5EF8(self, data, amount);
    func_002B62A0();
    return *(int *)(data + 0x94);
}
