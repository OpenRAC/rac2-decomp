#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[4960];
    void *p1360;
    void *p1364;
    void *p1368;
    unsigned char pad1[4512];
    float f250C;
    float f2510;
    float f2514;
} Persistent_F882f1178;
typedef struct {
    unsigned char pad[120];
    int field120;
} Node_F882f1178;
extern Persistent_F882f1178 D_00189E20_11;
extern int D_L00_001A8F00 __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_L00_00326048(int, float *, int, int, float);
extern int ref_L00_002D4A38_00 __attribute__((sda));

void func_PAL_L00_002D4F60(void)
{
    Node_F882f1178 *node;

    node = (Node_F882f1178 *)D_00189E20_11.p1360;
    if (node != 0) {
        if (ref_L00_002D4A38_00 == 2)
            D_00189E20_11.f250C = func_00283B98(D_00189E20_11.f250C, 0.024434613f);
        else
            D_00189E20_11.f250C = func_00283B98(D_00189E20_11.f250C, 0.04188791f);
        node->field120 = func_00283D38(0xd2d2d2, 0x285050,
                                 func_00283198(D_00189E20_11.f250C) * 0.5f + 0.5f);
    }
    node = (Node_F882f1178 *)D_00189E20_11.p1364;
    if (node != 0) {
        if (D_L00_001A8F00 != 2) {
            float limit;
            int which;

            limit = func_00283B98(D_00189E20_11.f2510, 0.059341207f);
            D_00189E20_11.f2510 = limit;
            which = 0x1ee628;
            if (limit > 0.0f && limit < 1.9198623895645142f) {
                which = 0x1e1ed2;
            }
            node->field120 = func_00283D38(node->field120, which, 0.070000000298023224f);
        } else {
            D_00189E20_11.f2510 = func_00283B98(D_00189E20_11.f2510, 0.031415932f);
            node->field120 = func_00283D38(0x1e1ed2, 0x1e1e50,
                                     func_00283198(D_00189E20_11.f2510) * 0.5f + 0.5f);
        }
    }
    if (D_00189E20_11.p1368 != 0) {
        if (D_L00_001A8F00 == 2)
            func_L00_00326048((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.031415932f);
        else
            func_L00_00326048((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.048869226f);
    }
}
