#include "common.h"

/* EE integer and FP banks retain the helper's two pointers and scale. */
extern void func_00282F20(float, void *, void *);
extern float D_L09_001B11C0 __attribute__((sda));
extern float D_L09_001B11D0 __attribute__((sda));
extern s32 D_L09_001B1280 __attribute__((sda));
extern s32 D_L09_001B11B8 __attribute__((sda));
extern u8 D_L09_001B11C8 __attribute__((sda));
extern s32 D_L09_001B11C4 __attribute__((sda));
extern u16 D_L09_001B11CC __attribute__((sda));
extern float func_00282E80(char *a0, char *a1);
extern void func_0029FC20(char *a0, s32 a1, void *a2);
extern void func_00282CF0(float *a0, char *a1, float *a2);
extern char *func_L09_003AE8C8(float *a0, char *a1, float *a2, s32 a3, s32 t0, float f12, float f13, float f14, float f15);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern s32 func_002829A8(char *a0);

void func_L09_003FEAE8(char *a0) {
    char *s2 = *(char **)(a0 + 0x68);
    float matrix[16];
    float va[4];

    {
        if (*(u8 *)(s2 + 0x42B) != 0 && func_00282E80(s2 + 0x390, *(char **)(s2 + 0x150) + 0x10) < 3.0f) {
            *(s16 *)(s2 + 0x412) = 600;
            if (*(s16 *)(s2 + 0x426) == 0 && *(u8 *)(s2 + 0x428) == 0) {
                func_0029FC20(a0, *(u8 *)(s2 + 0x429) + 4, matrix);
                if (*(u8 *)(s2 + 0x441) && func_00282E80(s2 + 0x140, s2 + 0x390) < 3.0f) {
                    func_00282CF0(va, s2 + 0x140, matrix + 12);
                } else {
                    func_00282CF0(va, s2 + 0x390, matrix + 12);
                }
                func_00282F20(D_L09_001B11C0 * 0.016666668f, va, va);
                func_L09_003AE8C8(matrix + 12, a0, va, 1, 1, (float)*(u8 *)(s2 + 0x34), D_L09_001B11D0, 1.0f, 0.5f);
                if (*(u8 *)(s2 + 0x42A) % D_L09_001B1280 == 0)
                    func_002E5CF8(D_L09_001B11B8, 0, a0);
                *(u8 *)(s2 + 0x429) ^= 1;
                *(u8 *)(s2 + 0x42A) += 1;
                *(u8 *)(s2 + 0x428) = D_L09_001B11C8;
                if (D_L09_001B11C4 < *(u8 *)(s2 + 0x42A)) {
                    *(u8 *)(s2 + 0x42A) = 0;
                    *(u16 *)(s2 + 0x426) = D_L09_001B11CC;
                }
            }
        } else if (*(u8 *)(s2 + 0x428) == 0) {
            if (func_002829A8(s2 + 0x42A) == 0)
                *(u8 *)(s2 + 0x428) = D_L09_001B11C8;
        }
    }
}
