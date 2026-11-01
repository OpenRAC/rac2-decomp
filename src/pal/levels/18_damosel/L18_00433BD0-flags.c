#include "include_asm.h"

#include "common.h"
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern void func_002AA2E8(void *, float, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_002AAA00(void *, void *, float, float, float, float, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_PAL_L18_004347D0(void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L18_0042FAA8(void *);
extern u8 *D_L18_001B281C;
extern float D_L18_001B1430 __attribute__((sda));
extern float D_L18_001B1434 __attribute__((sda));
extern float D_L18_001B1438 __attribute__((sda));
extern float D_L18_001B143C __attribute__((sda));
extern float D_L18_001B1440 __attribute__((sda));
extern float D_L18_001B1444 __attribute__((sda));
extern float D_L18_001B1448 __attribute__((sda));
extern float D_L18_001B144C __attribute__((sda));
extern float D_L18_001B1450 __attribute__((sda));
extern float D_L18_001B1454 __attribute__((sda));
extern float D_L18_001B1458 __attribute__((sda));
extern float D_L18_001B145C __attribute__((sda));
extern float D_L18_001B1460 __attribute__((sda));
extern float D_L18_001B1468[6] __attribute__((sda));
extern u8 D_L18_001B1480[16] __attribute__((sda));
extern u8 D_L18_001B1490[] __attribute__((sda));
extern u8 D_L18_002A9BE0[];
#define F(p, o) (*(float *)((p) + (o)))

void func_PAL_L18_00434320(u8 *a, int turn, int tilt)
{
    u8 *s = *(u8 **)(a + 0x68);
    int i;

    if (turn) {
        if (a[0x20] == 2)
            func_002AEE70(a, s + 0xC8, s + 0xCC, D_L18_001B1444,
                          D_L18_001B1434 * 0.0003490659f, -1.0f);
        else
            func_002AEE70(a, s + 0xC8, s + 0xCC, D_L18_001B1430,
                          D_L18_001B1434 * 0.0003490659f, -1.0f);
    }
    if (tilt) {
        if (a[0x20] == 2)
            func_002AEF28(a, s + 0xD0, s + 0xD4, D_L18_001B1448,
                          D_L18_001B143C * 0.0003490659f,
                          D_L18_001B1440 * 0.0003490659f);
        else
            func_002AEF28(a, s + 0xD0, s + 0xD4, D_L18_001B1438,
                          D_L18_001B143C * 0.0003490659f,
                          D_L18_001B1440 * 0.0003490659f);
    } else {
        func_002AA2E8(a + 0xF0, 0.0f, 0.062831864f);
        func_002AA2E8(a + 0xF4, 0.0f, 0.062831864f);
    }
    func_002AA548(a + 0x10, s + 0x80, F(s, 0x70),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    func_002AA548(a + 0x14, s + 0x84, F(s, 0x74),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    func_002AA548(a + 0x18, s + 0x88, F(s, 0x78),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    if (func_00282E80(a + 0x10, s + 0x70) > 1.0f) {
        u8 *heading = a + 0xF8;
        float angle = func_00283248(F(s, 0x70) - F(a, 0x10),
                                    F(s, 0x74) - F(a, 0x14));
        func_002AAA00(heading, s + 0xD8, angle,
                      D_L18_001B144C * 6.981318e-06f,
                      D_L18_001B1450 * 6.981318e-06f,
                      D_L18_001B1454 * 0.0003490659f, 0);
    }
    {
        int *ids = (int *)(s + 0x90);
        u8 *offset = D_L18_002A9BE0;

        for (i = 0; i < 6; i++, offset += 16, ids++) {
            if (*ids != -1) {
                u8 *e = D_L18_001B281C + (*ids << 8);
                func_00283098(e + 0x10, offset, a + 0xC0);
                func_00282CC0(e + 0x10, e + 0x10, a + 0x10);
                if (i < 3) {
                    F(e, 0xF0) = F(a, 0xF4);
                    F(e, 0xF4) = -F(a, 0xF0);
                    F(e, 0xF8) = func_00283B98(F(a, 0xF8), D_L18_001B1468[i]);
                } else {
                    F(e, 0xF0) = -F(a, 0xF4);
                    F(e, 0xF4) = F(a, 0xF0);
                    F(e, 0xF8) = func_00283B98(F(a, 0xF8), D_L18_001B1468[i]);
                }
            }
        }
    }
    func_PAL_L18_004347D0(a, D_L18_001B1480);
    func_PAL_L18_004347D0(a, D_L18_001B1490);
    func_L00_002E6EF8(func_L18_0042FAA8, a);
}
