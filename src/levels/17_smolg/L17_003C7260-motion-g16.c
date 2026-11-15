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
extern float func_0031CD58(void *, int, float);
extern int func_L17_003C70E0(void *);
extern void func_002EF398(void *, void *, void *);
extern void func_0031D090(void *, void *, int, void *, float);
extern void func_0031D2B0(void *, void *);
extern float func_002EF078(void *, void *);
extern void func_00327FF8(void *, int, int, int, int, int, int, void *);
extern void func_003629B8(int, int, void *);
extern void func_002EEEE8(void *, void *, void *);
extern void func_00323370(void *, void *, void *, void *);
/* Updates the falling object: it drops to the ground, hurts the player if it lands on
   them, and wakes up when the player stays close for a while. */
void func_L17_003C7260(char *self) {
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
            ground = func_0031CD58(position, 0, 0.5f);
            *(int *)(data + 0x9C) = D_L17_001C0018;
            if (ground < *(float *)(self + 0x18)) {
                *(float *)(data + 0x98) += D_L17_001B0390 * 0.00027777778f;
                *(float *)(self + 0x18) -= *(float *)(data + 0x98);
            } else {
                *(int *)(data + 0x98) = 0;
                *(float *)(self + 0x18) = ground;
            }
            if (IsPlayerInsideObjectFootprint(self)) {
                func_002EF398(&delta, &D_L17_001B0380, self + 0xC0);
                func_0031D090(collision, self, 0x10001, &delta, 2.0f);
                func_0031D2B0(gHeroMoby_0018C0B0, collision);
            }
        }
    }
    if (D_L17_001B2748 >= 31) {
        if (*(int *)(data + 0xA4) == 0 && *(int *)(data + 0xA8) >= 51 &&
            func_002EF078(position, gHeroPosition) < 15.0f && *(unsigned char *)(self + 0x20) == 0) {
            func_00327FF8(self, 0x931, 0, 0x931, 4, 6, 0, D_L17_001A8F20);
            func_003629B8(0, 0, self);
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
    func_002EEEE8(&delta, position, &oldpos);
    func_00323370(data + 0x50, &delta, self + 0xF0, self + 0xF0);
}
