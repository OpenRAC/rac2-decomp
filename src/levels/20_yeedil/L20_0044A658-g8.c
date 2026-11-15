/* Updates contact state, retaining the separate attached-owner pointer lifetime.
 * Position and fallback vectors are complete sixteen-byte transfers. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2418 __attribute__((sda));

extern u32 D_00189E20[] __attribute__((nosda));

extern void func_002A7750(char *, int, int);

extern void *func_002A9640(char *, int, int);

extern float func_002A96A0(char *, char *);

extern int func_002B3BA8(char *, int, void *, int, float, float);
extern float func_002AA2E8(float *, float, float);

extern void func_L20_0044AB68(char *);

void func_L20_0044A658(char *arg0) {
    char *state;
    char *p;
    u32 *q;
    short t;
    float f;

    state = *(char **)(arg0 + 0x68);
    if (*(u8 *)(arg0 + 0x20) == 0) {
        func_002A7750(arg0, 1, -1);
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        *(int *)(arg0 + 0x98) = 0;
        qcopy((state + 0x180), (arg0 + 0x10));
        *(float *)(arg0 + 0x2C) =
            *(float *)(*(u32 *)(arg0 + 0x24) + 0x24) * D_L20_001B2418;
        *(int *)(state + 0x1B8) = -1;
    }
    if (*(u8 *)(arg0 + 0x20) == 1) {
        return;
    }
    p = func_002A9640(arg0, 0x10000, 0);
    if (p != 0) {
        q = *(u32 **)(p + 0x20);
        if (q != 0) {
            t = *(short *)((char *)q + 0xAA);
            if (t == 0x12F2 || t == 0x12EF) {
                p = 0;
            }
        }
    }
    f = func_002A96A0(arg0, p);
    ApproachValue((float *)(state + 0x20), 0.0f, f);
    *(u8 *)(arg0 + 0xA8) = 0xFF;
    if (*(float *)(state + 0x20) == 0.0f) {
        func_L20_0044AB68(arg0);
        *(u8 *)(arg0 + 0xA8) = 0xFF;
        func_002A7750(arg0, 1, -1);
        *(int *)(arg0 + 0x98) = 0;
        *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    }
    if (*(u8 *)(arg0 + 0x20) == 5) {
        return;
    }
    {
    char *owner = *(char **)(state + 0x1B0);
    if (owner != 0) {
        *(u32 *)(state + 0x150) = (u32)owner;
        qcopy((state + 0x140), (owner + 0x10));
        *(float *)(state + 0x148) = *(float *)(state + 0x148) + 0.5f;
        return;
    }
    }
    func_002B3BA8(arg0, *(int *)(state + 0x160), 0, 0, 1024.0f, 37.0f);
    if (*(u32 *)(state + 0x150) != 0) {
        return;
    }
    {
        u32 *base = (u32 *)D_00189E20;
        *(u32 *)(state + 0x150) = base[0x8A4];
        qcopy((state + 0x140), ((char *)base + 0xD0));
    }
}
