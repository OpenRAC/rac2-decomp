#include "include_asm.h"

#include "common.h"
extern float func_002A89A8(void *, int, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float D_L09_001B13BC __attribute__((sda));
extern char *D_L09_001FE6C0[];
typedef struct {
    char pad_0[0x28];
    signed char field_28;
    char pad_29[0x7];
    int field_30;
    char pad_34[0x14];
    signed char field_48;
    char pad_49[0x1];
    signed char field_4A;
    char pad_4B[0x15];
    signed char field_60;
    signed char field_61;
    signed char field_62;
    char pad_63[0x3];
    signed char field_66;
    signed char field_67;
    char pad_68[0x4];
    float field_6C;
    float field_70;
    float field_74;
    float field_78;
    float field_7C;
    float field_80;
    float field_84;
    char pad_88[0x4];
    float field_8C;
    char pad_90[0x8];
    int field_98;
    char pad_9C[0x20];
    signed char field_BC;
    signed char field_BD;
    signed char field_BE;
    signed char field_BF;
    char pad_C0[0x2];
    signed char field_C2;
    signed char field_C3;
    char pad_C4[0x2];
    signed char field_C6;
    char pad_C7[0x39];
    float field_100;
    float field_104;
    float field_108;
    float field_10C;
    float field_110;
    char pad_114[0x18];
    float field_12C;
    float field_130;
    char pad_134[0x4];
    int field_138;
    int field_13C;
    char pad_140[0x9C];
    float field_1DC;
    char pad_1E0[0x2];
    short field_1E2;
    short field_1E4;
    char pad_1E6[0x1A];
    float field_200;
    char pad_204[0x8];
    float field_20C;
    float field_210;
    char pad_214[0x2C];
    int field_240;
    char pad_244[0xC];
    int field_250;
    int field_254;
    int field_258;
    char pad_25C[0x4];
    float field_260;
    float field_264;
    char pad_268[0xC];
    short field_274;
    char pad_276[0x12];
    float field_288;
    int field_28C;
    char pad_290[0x4];
    float field_294;
} DobboInitData;

/* Runs on the object's first update: fills in its record's defaults, resolves the angles from
   degrees and, when the record names a path node, moves the object to it. */
void func_PAL_L09_00407C08(char *obj) {
    DobboInitData *data = *(DobboInitData **)(obj + 0x68);
    float value;
    int one;
    data->field_288 = func_002A89A8(obj + 0x10, 0, 0.5f);
    value = data->field_288 + D_L09_001B13BC;
    data->field_294 = value;
    if (value < data->field_264) data->field_294 = data->field_264;
    data->field_274 = -1;
    if (data->field_260 == -1.0f) data->field_260 = 0.0174532942f * func_002A78D8(25.0f, 100.0f);
    else data->field_260 *= 0.0174532942f;
    data->field_48 = func_00283CF0(15.0f);
    data->field_4A = func_00283CF0(2.4f);
    data->field_60 = 9;
    data->field_61 = 0;
    data->field_62 = 0;
    data->field_66 = 0;
    data->field_67 = 0;
    one = 1;
    data->field_6C = 0.120000005f;
    data->field_70 = 0.080000006f;
    data->field_98 = one;
    data->field_78 = 0.012f;
    data->field_7C = data->field_74 = 0.006f;
    data->field_80 = 0.5f;
    data->field_84 = D_L09_001B13BC;
    data->field_8C = 0.4f;
    data->field_C3 = data->field_C2 = data->field_BF = data->field_BE = data->field_BD = data->field_BC = -1;
    data->field_C6 = one;
    data->field_100 = 1.0f;
    data->field_104 = 1.1f;
    data->field_10C = data->field_108 = 2.8f;
    data->field_110 = 3.14159274f;
    data->field_130 = 25.1327438f;
    data->field_12C = 0.00112f;
    if (data->field_258 != -1) data->field_13C = data->field_258;
    else data->field_13C = data->field_254;
    data->field_1E4 = 200;
    data->field_138 |= 0x10;
    data->field_1DC = data->field_260 * 0.017453294f;
    data->field_1E2 = 100;
    func_002B60B0(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
    qcopy((char *)data+0x1F0, obj+0x10);
    data->field_200 = 1.0f;
    data->field_20C = 5.0f;
    data->field_210 = 10.0f;
    data->field_28 = 3;
    data->field_28C = data->field_240;
    data->field_30 = 0;
    if (data->field_250 != -1) {
        qcopy(obj+0x10, D_L09_001FE6C0[data->field_250] + 0x10);
        func_002A7750(obj, 1, 0);
    } else func_002A7750(obj, 2, 2);
    if (*(unsigned char *)(obj+0x43)) func_PAL_002A7E68(obj, 0, 0, 1);
}

/*
 * func_PAL_L09_00403698, the PAL copy of func_L09_003FEAE8: the same C, where 600 becomes 500,
 * 0.016666668f becomes 0.020000001f, and D_L09_001B11C8 and D_L09_001B11CC are read as words and
 * scaled to 50 Hz.
 */
extern void func_00282F20(float, void *, void *);
extern float D_L09_001B11C0 __attribute__((sda));
extern float D_L09_001B11D0 __attribute__((sda));
extern s32 D_L09_001B1280 __attribute__((sda));
extern s32 D_L09_001B11B8 __attribute__((sda));
extern s32 D_L09_001B11C8 __attribute__((sda));
extern s32 D_L09_001B11C4 __attribute__((sda));
extern s32 D_L09_001B11CC __attribute__((sda));
extern float func_00282E80(char *a0, char *a1);
extern void func_0029FC20(char *a0, s32 a1, void *a2);
extern void func_00282CF0(float *a0, char *a1, float *a2);
extern char *func_L09_003AE8C8(float *a0, char *a1, float *a2, s32 a3, s32 t0, float f12, float f13, float f14, float f15);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern s32 func_002829A8(char *a0);

void func_PAL_L09_00403698(char *a0) {
    char *s2 = *(char **)(a0 + 0x68);
    float matrix[16];
    float va[4];

    {
        if (*(u8 *)(s2 + 0x42B) != 0 && func_00282E80(s2 + 0x390, *(char **)(s2 + 0x150) + 0x10) < 3.0f) {
            *(s16 *)(s2 + 0x412) = 500;
            if (*(s16 *)(s2 + 0x426) == 0 && *(u8 *)(s2 + 0x428) == 0) {
                func_0029FC20(a0, *(u8 *)(s2 + 0x429) + 4, matrix);
                if (*(u8 *)(s2 + 0x441) && func_00282E80(s2 + 0x140, s2 + 0x390) < 3.0f) {
                    func_00282CF0(va, s2 + 0x140, matrix + 12);
                } else {
                    func_00282CF0(va, s2 + 0x390, matrix + 12);
                }
                func_00282F20(D_L09_001B11C0 * 0.020000001f, va, va);
                func_L09_003AE8C8(matrix + 12, a0, va, 1, 1, (float)*(u8 *)(s2 + 0x34), D_L09_001B11D0, 1.0f, 0.5f);
                if (*(u8 *)(s2 + 0x42A) % D_L09_001B1280 == 0)
                    func_002E5CF8(D_L09_001B11B8, 0, a0);
                *(u8 *)(s2 + 0x429) ^= 1;
                *(u8 *)(s2 + 0x42A) += 1;
                *(u8 *)(s2 + 0x428) = (D_L09_001B11C8 * 5 + 2) / 6;
                if (D_L09_001B11C4 < *(u8 *)(s2 + 0x42A)) {
                    *(u8 *)(s2 + 0x42A) = 0;
                    *(u16 *)(s2 + 0x426) = (D_L09_001B11CC * 5 + 2) / 6;
                }
            }
        } else if (*(u8 *)(s2 + 0x428) == 0) {
            if (func_002829A8(s2 + 0x42A) == 0)
                *(u8 *)(s2 + 0x428) = (D_L09_001B11C8 * 5 + 2) / 6;
        }
    }
}
