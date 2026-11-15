#include "common.h"

extern s32 D_L09_001B2878 __attribute__((sda));
extern u8 *D_L09_001B285C MACRO_ADDR;
extern u16 *D_L09_001FB560[];


extern f32 D_L09_001B13B8 __attribute__((sda));
extern f32 D_L09_001B13BC __attribute__((sda));
extern f32 D_L09_001B13C4 __attribute__((sda));
extern f32 D_L09_001B13C8 __attribute__((sda));
extern f32 D_L09_001B13CC __attribute__((sda));
extern f32 D_L09_001B13D0 __attribute__((sda));
extern u8 *D_0018C0B0 NOT_SDA;

extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_002A7790(f32);
extern void func_002AEE70(u8 *, void *, void *, f32, f32, f32);
extern void func_002AEF28(u8 *, void *, void *, f32, f32, f32);

/* Keeps the object at a smooth height above the ground and pushes it away from others in its group. */
void func_L09_00403398(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    f32 origin[4] __attribute__((aligned(16)));
    f32 pushSum[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    u8 *ground;
    u16 *groupList;
    u8 *neighbor;
    f32 limit, current, len, weight;
    f32 height;

    *(f32 *)(state + 0x288) = *(f32 *)(obj + 0x18);
    if (obj[0x20] != 9 && obj[0x20] != 4) {
        height = *(f32 *)(state + 0x294) - 0.033333335f;
        *(f32 *)(state + 0x294) = height;
        qcopy(origin, obj + 0x10);
        origin[2] = height + (D_L09_001B13C4 - D_L09_001B13BC);
        ground = *(u8 **)(state + 0x188);
        if (ground == 0 || (ground != gHeroMoby_0018C0B0 && *(s16 *)(ground + 0xAA) != 0xD57 /* moby class 3415 */ &&
                       *(s16 *)(*(u8 **)(ground + 0x24) + 0x46) >= 11)) {
            limit = *(f32 *)(state + 0x288) + D_L09_001B13BC;
            current = *(f32 *)(state + 0x294);
            if (current < limit)
                *(f32 *)(state + 0x294) = current + (limit - current) * D_L09_001B13C8;
        }
        limit = *(f32 *)(state + 0x264) + D_L09_001B13BC;
        current = *(f32 *)(state + 0x294);
        if (current < limit)
            *(f32 *)(state + 0x294) = current + (limit - current) * D_L09_001B13C8;
        if (obj[0x20] >= 6 && obj[0x20] <= 8) {
            limit = *(f32 *)(*(u8 **)(state + 0x230) + 0x18) + D_L09_001B13B8;
            current = *(f32 *)(state + 0x294);
            if (current < limit)
                *(f32 *)(state + 0x294) = current + (limit - current) * D_L09_001B13CC;
        }
        *(f32 *)(obj + 0x18) = *(f32 *)(state + 0x294);
        qzero_nc(pushSum);
        groupList = D_L09_001FB560[obj[0x21]];
        for (;
             obj[0x21] != 0xFF && obj[0x21] <= D_L09_001B2878 && groupList != 0 &&
             ((groupList != 0 && (s16)groupList[-1] >= 0) || groupList == D_L09_001FB560[obj[0x21]]);
             groupList++) {
            neighbor = D_L09_001B285C + ((*groupList & 0x7FFF) << 8);
            if (neighbor == 0)
                break;
            FastVecSub(offset, obj + 0x10, neighbor + 0x10);
            len = FastVecLength(offset);
            if (len > D_L09_001B13D0)
                len = D_L09_001B13D0;
            else if (len < 0.0f)
                len = 0.0f;
            weight = 1.0f - len / D_L09_001B13D0;
            Square(weight);
            vec_scale_to_length(offset, offset, len * weight);
            FastVecAdd(pushSum, pushSum, offset);
        }
        FastVecAdd(obj + 0x10, obj + 0x10, pushSum);
        UpdateWrappedAngleOffset(obj, state + 0x278, state + 0x27C, 0.1f, 0.087266475f, *(f32 *)(obj + 0x18));
        ScaleOwnerWordsByAngles(obj, state + 0x280, state + 0x284, 0.13962635f, 0.026179943f, 0.026179943f);
    } else {
        *(f32 *)(state + 0x294) = *(f32 *)(obj + 0x18);
    }
}
