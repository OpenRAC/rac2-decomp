#include "common.h"

extern float func_00282DB0(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern int D_L07_001A8FF0 MACRO_ADDR;
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern int func_00278E78(void);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282D30(void *, void *, float);
typedef int GroundQuad __attribute__((mode(TI)));
typedef struct { char prefix[0x18]; unsigned char *object; int count; float position[4]; char gap[16]; float normal[4]; } GroundCollision;
extern int D_001A79F0 __attribute__((sda));
extern int D_L07_001A8FF4 __attribute__((sda));
extern GroundCollision D_L07_001BF640;
extern int func_L00_002ADF80(void);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_L00_002E2048(void);
extern float func_002A90F8(float *, void *);
extern int func_002ABB78(char *);
extern int func_002AB1F0(unsigned char *);
extern int func_002AD0B0(unsigned char *);
extern float func_002B0360(char *);
extern float func_00282E48(void *, void *);
extern void func_001290E0(void *, void *);
extern float func_L00_002D3EA8(void *);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFF60(char *, char *, int);
extern void func_L00_002B8E48(void *, float *);
extern void func_L00_002D3638(float *, float, float, int, float);
extern float func_00282C48(float);
/* This entry is +0x24 inside the catalogued ASM extent, not a new function identity. */

typedef struct GroundView {
    unsigned char pad0[128];
    struct {
        unsigned char pad80[8];
        float field_88;
        unsigned char tail[4];
    } vector_80;
    unsigned char pad90[32];
    struct {
        unsigned char padb0[12];
        float field_bc;
    } vector_b0;
    unsigned char padc0[420];
    float field_264;
    unsigned char pad268[56];
    struct {
        int field_2a0;
        int field_2a4;
        float field_2a8;
        unsigned char tail[4];
    } vector_2a0;
    struct {
        unsigned char tail[16];
    } vector_2b0;
    struct {
        unsigned char pad2c0[8];
        float field_2c8;
        unsigned char tail[4];
    } vector_2c0;
    struct {
        unsigned char tail[16];
    } vector_2d0;
    struct {
        unsigned char tail[16];
    } vector_2e0;
    struct {
        unsigned char pad2f0[12];
        float field_2fc;
    } vector_2f0;
    float footHeight[2];
    float footYaw[2];
    float footPitch[2];
    float field_318;
    float field_31c;
    float field_320;
    float field_324;
    float field_328;
    float field_32c;
    float field_330;
    float field_334;
    int field_338;
    int field_33c;
    int field_340;
    unsigned char pad344[6];
    short field_34a;
    short field_34c;
    short field_34e;
    unsigned char pad350[332];
    unsigned char field_49c;
    unsigned char pad49d[1907];
    int field_c10;
    unsigned char padc14[2172];
    short field_1490;
    unsigned char pad1492[11];
    unsigned char field_149d;
    unsigned char pad149e[1058];
    int field_18c0;
    unsigned char pad18c4[2508];
    char * field_2290;
    int field_2294;
    unsigned char pad2298[4];
    int field_229c;
    unsigned char pad22a0[35];
    unsigned char field_22c3;
} GroundView;
extern GroundView D_00189E20;

void func_L07_002B3580(void)
{
    float end[4];
    float start[4];
    float difference[4];
    float left[4];
    float right[4];
    float angles[2];
    float normal[4];
    float reach, scale;
    int side;
    ++D_00189E20.field_34e;
    D_00189E20.vector_2a0.field_2a8 = 1.0f;
    ++D_00189E20.field_34c;
    D_00189E20.vector_2a0.field_2a0 = 0;
    D_00189E20.vector_2a0.field_2a4 = 0;
    D_00189E20.field_320 = 0.0f;
    D_00189E20.field_318 = 0.0f;
    func_00282C88((GroundQuad *)(&D_00189E20.vector_2d0));
    D_00189E20.field_34a = 0;
    D_00189E20.field_31c = 32.0f;
    D_00189E20.field_33c = 0;
    scale = 2.2f;
    if (D_00189E20.field_338)
        ++D_00189E20.field_338;
    reach = D_00189E20.field_264 * scale;
    if (D_00189E20.field_229c == 2)
        reach = D_00189E20.field_264 * 2.9f;
    if (func_L00_002ADF80())
        reach = 0.0f;
    func_L00_002B47A8(start, end, 1, reach, -48.0f);
    if (func_002761F8(start, end, 2, D_00189E20.field_2290, 0)) {
        D_00189E20.field_149d = func_L00_002E2048();
        if (D_L07_001BF640.object)
            D_00189E20.field_149d = 0;
        if (D_001A79F0 == 7 && D_L07_001BF640.object)
            D_00189E20.field_149d = 1;
        D_00189E20.field_1490 = func_00278E78();
        if (!D_00189E20.field_1490) {
            D_00189E20.field_330 = func_002A90F8(D_L07_001BF640.position, &D_00189E20.vector_2b0);
            if (D_00189E20.vector_80.field_88 < D_00189E20.field_330 && D_00189E20.field_338 < 1)
                D_00189E20.field_338 = 1;
            if (!func_002761F8(start, end, 0x24, D_00189E20.field_2290, 0))
                goto contacts_done;
            D_00189E20.field_149d = func_L00_002E2048();
        }
        if (D_00189E20.field_1490 == 13) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            D_00189E20.field_330 = D_L07_001BF640.position[2];
            if (!func_002761F8(start, end, 4, D_00189E20.field_2290, 0))
                goto contacts_done;
        }
        if (D_00189E20.field_1490 == 3) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            D_00189E20.field_334 = D_L07_001BF640.position[2];
            if (!func_002761F8(start, end, 4, D_00189E20.field_2290, 0))
                goto contacts_done;
        }
        if (D_00189E20.field_1490 == 11) {
            D_00189E20.field_334 = D_L07_001BF640.position[2];
        } else {
            if (D_L07_001BF640.object) {
                unsigned char *record;
                if (func_002ABB78((char *)D_L07_001BF640.object))
                    D_00189E20.field_34a = 1;
                record = (unsigned char *)func_002AB1F0(D_L07_001BF640.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    D_00189E20.field_34a = 1;
                record = (unsigned char *)func_002AD0B0(D_L07_001BF640.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    D_00189E20.field_34a = 1;
            }
            if (D_L07_001BF640.count > 0) {
                qcopy(&D_00189E20.vector_2d0, D_L07_001BF640.position);
                D_00189E20.field_318 = D_L07_001BF640.position[2];
                if (D_L07_001A8FF0)
                    D_00189E20.field_318 = func_002B0360((char *)D_L07_001BF640.position);
                D_00189E20.field_31c = func_00282E48(&D_00189E20.vector_80, &D_00189E20.vector_2d0);
                D_00189E20.field_33c = (int)D_L07_001BF640.object;
                func_001290E0(&D_00189E20.vector_2a0, D_L07_001BF640.normal);
                D_00189E20.field_320 = func_L00_002D3EA8(D_L07_001BF640.normal);
                D_00189E20.field_32c = func_00283248(D_L07_001BF640.normal[0], D_L07_001BF640.normal[1]);
                func_00282CF0(difference, &D_00189E20.vector_2d0, &D_00189E20.vector_80);
                if (func_00282DB0(difference, &D_00189E20.vector_2a0) > 0.0f)
                    D_00189E20.field_31c = -D_00189E20.field_31c;
                if (D_00189E20.field_31c < 0.02f) {
                    D_00189E20.field_34c = 0;
                    if (D_00189E20.field_320 <= 0.8726646900177002f || D_00189E20.field_22c3) {
                        D_00189E20.field_34e = 0;
                        D_00189E20.field_c10 = (int)D_L07_001BF640.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (D_00189E20.vector_80.field_88 > D_00189E20.field_330)
        D_00189E20.field_338 = 0;
    if (D_00189E20.field_34e) {
        D_00189E20.field_340 = 0;
    } else {
        ++D_00189E20.field_340;
        qcopy(&D_00189E20.vector_2e0, &D_00189E20.vector_2d0);
        if (D_00189E20.field_2294 != 56)
            D_00189E20.field_18c0 = 0;
    }
    func_00282C88((GroundQuad *)(&D_00189E20.vector_2c0));
    switch (D_00189E20.field_22c3) {
    case 0:
        D_00189E20.vector_2c0.field_2c8 = -1.0f;
        break;
    case 1:
        if (D_L07_001A8FF4) {
            func_002AFF60((char *)&D_00189E20.vector_80, (char *)&D_00189E20.vector_2c0, 0);
        } else {
            if (D_00189E20.vector_2f0.field_2fc != 0.0f) {
                func_002AA2E8(&D_00189E20.vector_2f0.field_2fc, 0.0f, 1.0f);
                qcopy(&D_00189E20.vector_2c0, &D_00189E20.vector_2f0);
            } else {
                qcopy(&D_00189E20.vector_2c0, &D_00189E20.vector_2a0);
                func_00282D30(&D_00189E20.vector_2c0, &D_00189E20.vector_2c0, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (D_00189E20.vector_b0.field_bc > 0.0f)
                sign = 1.0f;
            func_00282CF0(&D_00189E20.vector_2c0, &D_00189E20.vector_b0, &D_00189E20.vector_80);
            func_00282F20(&D_00189E20.vector_2c0, &D_00189E20.vector_2c0, sign);
        }
        break;
    }
    D_00189E20.field_324 = 0.0f;
    D_00189E20.field_328 = 0.0f;
    D_00189E20.footPitch[0] = 0;
    D_00189E20.footPitch[1] = 0;
    D_00189E20.footYaw[0] = 0;
    D_00189E20.footYaw[1] = 0;
    D_00189E20.footHeight[0] = 0;
    D_00189E20.footHeight[1] = 0;
    if (D_00189E20.field_31c < 0.25f &&
        (D_00189E20.field_229c == 0 || D_00189E20.field_229c == 12 || D_00189E20.field_229c == 9 || D_00189E20.field_229c == 7 ||
         (D_00189E20.field_229c == 4 && D_00189E20.field_49c) || D_00189E20.field_229c == 1)) {
        func_L00_002B8E48(&D_00189E20.vector_2a0, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            D_00189E20.field_324 = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            D_00189E20.field_328 = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            func_L00_002D3638(left, 0.2f, angle, 1, 0.44999998807907104f);
            func_L00_002D3638(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (func_002761F8(left, right, 0x22, D_00189E20.field_2290, 0)) {
                if (D_L07_001A8FF0) {
                    float firstHeight = func_002B0360((char *)D_L07_001BF640.position);
                    D_00189E20.footHeight[side] = firstHeight - func_002B0360((char *)&D_00189E20.vector_2d0);
                } else {
                    D_00189E20.footHeight[side] = D_L07_001BF640.position[2] - D_00189E20.field_318;
                }
                if (func_00282C48(D_00189E20.footHeight[side]) > 0.4f)
                    D_00189E20.footHeight[side] = 0.0f;
                func_001290E0(normal, D_L07_001BF640.normal);
                func_L00_002B8E48(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    D_00189E20.footYaw[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    D_00189E20.footPitch[side] = angles[0];
            } else {
                D_00189E20.footHeight[side] = 0.0f;
                D_00189E20.footYaw[side] = D_00189E20.field_324;
                D_00189E20.footPitch[side] = D_00189E20.field_328;
            }
        }
    }
}
