#include "include_asm.h"

#include "common.h"
typedef struct BarlowUtilityQueueView BarlowUtilityQueueView;
extern u8 D_001A7B00, D_001A7A40;
extern u32 D_001397D0 NOT_SDA;
extern u32 D_00138324 NOT_SDA;
extern u8 D_00139568[];
extern int D_001A79F8 MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; float position[4]; float rotation[4];
    u8 padA0[0x40]; float aim[4]; u8 padF0[0x20]; float velocity[4];
} JobaPlayerView;
extern JobaPlayerView D_00189E20;
extern u8 D_00189F00[];
extern u8 D_L11_001C0AC0[];
typedef struct {
    u8 pad[0x30];
    float position[4];
    u8 pad40[0x30];
    float rotation[4];
} VendorRecord;
extern VendorRecord *D_L11_001B368C[] MACRO_ADDR;
typedef struct {
    u8 pad[0x80];
    int price;
    u8 tail[0x5C];
} VendorOffer;
extern VendorOffer D_L11_00279BA0[];
extern volatile int D_L11_001B32E8[] MACRO_ADDR;
extern int D_L11_001A8F00[] MACRO_ADDR;
extern void func_L04_00434AD0(u8 *);
extern void func_002A7750(u8 *, int, int);
extern void func_L01_003128C0(char *);
extern int func_002ACBC8(char *, int);
extern int func_00288AA0(u8 *, int);
extern int func_00288BE8(BarlowUtilityQueueView *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(float *, float *, int, int);
extern int func_L01_003245E0(u8 *, int, float);
extern void func_L00_0030C710(int);
extern void func_L01_00324550(int, int, int);
extern void func_L01_003246D0(int);
extern void func_002A8598(int, int);
extern void func_00288308(int);
extern void func_US2_002B1880(int, int);
extern int func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern int func_00282978(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A7470(u8 *, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00283BE0(float, float);
extern float func_00282E20(void *);
extern void func_002AEC48(char *, u8 *, char *, float, float);

void func_US2_L11_00463368(u8 *object) {
    float destination[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    int index, tracking;
    float rate;
    float yaw, pitch, distance, a, b, heading;
    func_L04_00434AD0(object);
    switch (object[0x20]) {
    case 0:
        if (D_001A7B00) { func_0029F338(object); return; }
        if (D_001397D0 & 0x800) func_002A7750(object, 2, -1);
        else func_002A7750(object, 1, -1);
        func_L01_003128C0((char *)object);
        break;
    case 1:
        if (func_002ACBC8((char *)D_00189E20.position, *(int *)(vars + 0x120)) && func_00288AA0(D_L11_001C0AC0, 0x6B)) {
            func_L01_003246D0((int)object);
            func_00288BE8((BarlowUtilityQueueView *)D_L11_001C0AC0);
            func_002A7750(object, 2, -1);
        }
        break;
    case 2:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            VendorRecord *record;
            D_L11_001B32E8[0] = 0;
            record = (VendorRecord *)((u32)D_L11_001B368C[0] + *(int *)(vars + 0x120) * sizeof(VendorRecord));
            func_L00_002B9D60(record->position, record->rotation, 0, 1);
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (D_001A79F8 < ((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price) func_002A7750(object, 3, -1);
            else func_002A7750(object, 4, -1);
        }
        break;
    case 3:
        if (((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price < D_001A79F8) {
            func_002A7750(object, 4, -1);
        } else if (func_L01_003245E0(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x130E, ((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price, -1);
            func_L01_003246D0((int)object);
        }
        break;
    case 4:
        if (D_001A79F8 < ((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price) {
            func_L00_0030C710(180);
            func_002A7750(object, 3, -1);
        } else if (func_L01_003245E0(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x130D, ((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price, -1);
            func_L01_003246D0((int)object);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L11_001C0AC0, 0x6C)) {
                func_00288BE8((BarlowUtilityQueueView *)D_L11_001C0AC0);
                func_002A7750(object, 5, -1);
            }
        }
        break;
    case 5:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            D_L11_001B32E8[0] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (object[0x21] != 0xFF) func_002A8598(object[0x21], 1);
            if (!D_001A7B00) {
                D_001A79F8 = D_001A79F8 - ((VendorOffer *)((u32)D_L11_00279BA0 + D_00139568[8] * sizeof(VendorOffer)))->price;
                func_L00_0030C710(180);
                func_00288308(8);
            }
            index = *(int *)(vars + 0x124);
            if (index != -1) {
                VendorRecord *record = (VendorRecord *)((u32)D_L11_001B368C[0] + index * sizeof(VendorRecord));
                func_L00_002B9D60(record->position, record->rotation, 0, 1);
            }
            func_US2_002B1880(0x1230, -1);
            func_0029B3E0(0, -1);
            func_0029F338(object);
            return;
        }
        break;
    }
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && func_00282978(vars + 0x11E)) {
            *(short *)(vars + 0x11E) = func_00283CF0(func_002A7878(1200.0f, 2400.0f));
            if (object[0x43] != 1) func_002A7470(object, 1, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            func_002A7470(object, 0, 0, 10);
        }
    }
    tracking = 0;
    rate = 0.02f;
    if (object[0x43] == 0) {
        tracking = 1;
        distance = func_00282E80(object + 0x10, D_00189E20.position);
        if (distance < 8.0f && func_00283C80(*(float *)(object + 0xF8), func_00283248(D_00189E20.aim[0] - *(float *)(object + 0x10), D_00189E20.aim[1] - *(float *)(object + 0x14))) < 1.5707965f) {
            if (func_00282DF0(D_00189E20.velocity) > 0.01f) *(int *)(vars + 0x114) = 120;
            else func_00282948(vars + 0x114);
        } else if (*(int *)(vars + 0x114)) {
            *(int *)(vars + 0x114) = 0;
            qcopy(vars + 0x100, D_00189F00);
        }
        if (func_00282948(vars + 0x118)) {
            *(int *)(vars + 0x118) = func_00283CF0(func_002A7878(180.0f, 300.0f));
            a = func_002A7878(-90.0f, 90.0f);
            heading = func_00283B98(*(float *)(object + 0xF8), a * 0.017453294f);
            b = func_002A7878(0, 30.0f);
            func_002AF000((float *)(vars + 0x100), 6.0f, heading, b * 0.017453294f);
            func_00282CC0((float *)(vars + 0x100), (float *)(vars + 0x100), (float *)(object + 0x10));
        }
        if (*(int *)(vars + 0x114)) {
            qcopy(destination, D_00189F00);
            rate = 0.04f;
        } else qcopy(destination, vars + 0x100);
    }
    if (tracking) {
        qcopy(origin, object + 0x10);
        origin[2] += 2.0f;
        func_00282CF0(difference, destination, origin);
        yaw = func_00283BE0(func_00283248(difference[0], difference[1]), *(float *)(object + 0xF8));
        pitch = -func_00283248(func_00282E20(difference), difference[2]);
        if (yaw > 1.5707965f) yaw = 1.5707965f;
        else if (yaw < -1.5707965f) yaw = -1.5707965f;
        if (pitch > 0.52359885f) pitch = 0.52359885f;
        else if (pitch < -0.52359885f) pitch = -0.52359885f;
        *(float *)(vars + 0x64) = pitch;
        *(float *)(vars + 0x68) = yaw * 0.6f;
        *(float *)(vars + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40) *(float *)(vars + 0x70) = 2.75f;
    for (index = 0; index < 2; index++)
        func_002AEC48((char *)object, vars + index * 0x80, (char *)index, rate, 0.3f);
    return;
}
