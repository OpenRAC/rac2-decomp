#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_00422624);

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_00422F18);

typedef unsigned char u8;
typedef unsigned int u32;
extern void func_00282C98(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_002AA2E8(void *, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_PAL_L01_00323068(void *, void *);
extern u8 D_L03_00188660[];
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern u8 *D_L03_001FB5A0[];
typedef struct {
    u32 field00;
    u8 pad04[0x0C];
    u8 field10[1];
} Entry41D1D8;
extern Entry41D1D8 *D_L03_001FE700[];
extern u8 D_001A7B08[0x40] __attribute__((sda));

/* Projects the state position onto its path, clamps lateral displacement,
 * advances the path blend nearby, and maintains its movement sound. */
void func_PAL_L03_00423128(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *entry = (u8 *)D_L03_001FE700[*(int *)(state + 0x210)];
    float delta[4], along[4], across[4], axis[4], point[4], scaled[4];
    float distance;
    float side;
    func_00282C98(axis);
    func_00282CF0(along, entry + 0x20, entry + 0x10);
    along[2] = 0;
    func_00282DD8(across, along, axis);
    func_00282F20(across, across, 1.0f);
    func_00282F20(along, along, 1.0f);
    func_00282CF0(delta, state + 0x1F0, entry + 0x10);
    delta[2] = 0;
    distance = func_00282DB0(delta, across);
    if (distance > *(float *)(state + 0x218)) distance = *(float *)(state + 0x218);
    else if (distance < -*(float *)(state + 0x218)) distance = -*(float *)(state + 0x218);
    func_00282D08(point, entry + 0x10, entry + 0x20, *(float *)(state + 0x340));
    func_00282F20(scaled, across, distance);
    func_00282CC0(point, point, scaled);
    func_00282CF0(delta, state + 0x1F0, point);
    delta[2] = 0;
    side = func_00282DB0(delta, along);
    if (func_00282E80(state + 0x1F0, point) < 6.0f) {
        float target = (side < 0.0f);
        func_002AA2E8(state + 0x340, target, 0.020000001f);
    }
    if (func_00282E48(entity + 0x10, point) >= 0.5f) {
        u8 *sound = D_L03_00188660 + *(int *)(state + 0x350) * 0x70;
        if (*(u8 **)(sound + 0x88) != entity || !sound[0x74])
            *(int *)(state + 0x350) = func_002E5CF8(0, 4, entity);
    } else {
        int slot = *(int *)(state + 0x350);
        if (slot != -1) {
            u8 *sound = D_L03_00188660 + slot * 0x70;
            if (*(u8 **)(sound + 0x88) == entity && sound[0x74]) func_002E59F8(slot);
        }
        *(int *)(state + 0x350) = -1;
    }
    func_PAL_L01_00323068(entity, point);
    *(int *)(state + 0x1A8) = 0;
}





INCLUDE_ASM("asm/pal/levels", func_PAL_L03_00423F28);
