#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The resident word the hero's key is read from. */
extern u32 D_0018C0B0[];

/* the two resident slots func_L22_003B8FE8 fills */
extern int ref_L22_003B8FE8_00 __attribute__((sda));

extern int ref_L22_003B8FE8_01 __attribute__((sda));

/* a plain small extern: $gp in a delay slot, absolute where it stays */
extern s32 D_L22_001A8FF0;

extern u8 *func_L22_003B8FE8(u8 *arg0, TI128 *arg1);

typedef union { u8 b[0x100]; TI128 q[0x10]; } Hero;

extern u8 D_00189E20[];

/* the two handles the new object's sound slots get, one per key */
extern s32 D_L22_001AFA00 __attribute__((sda));

extern s32 D_L22_001AFA04 __attribute__((sda));

/* the object the alternate key aims at */
extern u8 *ref_L22_003B9128_00;

/* the facing and range limits of the alternate key's aim */
extern float D_L22_001AF9E4 __attribute__((sda));

extern float D_L22_001AF9E8 __attribute__((sda));

extern s32 func_L00_0035F5A0(s32, s32, s32);

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282DB0(void *, void *);

extern float func_00282E48(void *, void *);

extern void func_L22_003A2988(void *, float);

/* makes sure the word chosen by the key holds an object (creating and aiming it when it does
   not), then moves it to the given position */
void func_L22_003B9128(u8 *owner, TI128 *position, s32 isAlternate) {
    s32 *slot = &ref_L22_003B8FE8_00;
    TI128 local;
    TI128 *pos = &local;
    TI128 dir;
    TI128 facing;
    u8 *obj;
    u8 *payload;
    u8 *found;
    u8 *target;
    u8 *hero;
    float dot;
    float dist;

    if (isAlternate != 0) {
        slot = &ref_L22_003B8FE8_01;
    }
    local = *position;
    if (*slot == 0) {
        CreateKeyedObject(owner, &local);
        if (isAlternate != 0) {
            D_L22_001AFA00 = StartEffectInSlot(0x14, 0, 0);
        } else {
            D_L22_001AFA04 = StartEffectInSlot(0x14, 0, 0);
        }
        found = (u8 *)*slot;
        if (found == 0) {
            return;
        }
        obj = found;
        payload = *(u8 **)(obj + 0x68);
        if (*(s16 *)(obj + 0xAA) != 0x5F3 /* moby class 1523 */) {
            return;
        }
        if (D_L22_001A8FF0 != 0) {
            target = ref_L22_003B9128_00;
            if (target == 0) {
                *(s32 *)(payload + 0x48) = 0;
            } else if ((hero = (u8 *)gHeroMoby_0018C0B0[0]) == 0) {
                *(s32 *)(payload + 0x48) = 0;
            } else {
                if (isAlternate != 0) {
                    *(u8 **)(payload + 0x44) = target;
                } else {
                    *(u8 **)(payload + 0x44) = hero;
                }
                if (isAlternate != 0) {
                    FastVecScale(&dir, *(u8 **)(payload + 0x44) + 0xE0, 4.0f);
                    FastVecAdd(&dir, &dir, *(u8 **)(payload + 0x44) + 0x10);
                } else {
                    qcopy(&dir, *(u8 **)(payload + 0x44) + 0x10);
                    PushPointOutOfArena(&dir, 2.2f);
                }
                FastVecSub(payload + 0x50, &dir, owner + 0x10);
                vec_scale_to_length(payload + 0x50, payload + 0x50, 1.0f);
                qcopy(&facing, owner + 0xC0);
                vec_scale_to_length(&facing, &facing, 1.0f);
                dot = FastVecDot(payload + 0x50, &facing);
                if (isAlternate != 0) {
                    dist = fast_vec_dist(target + 0x10, &((Hero *)gHeroState)->q[8]);
                    if (dot < D_L22_001AF9E4) {
                        *(s32 *)(payload + 0x44) = 0;
                    } else if (D_L22_001AF9E8 < dist) {
                        *(s32 *)(payload + 0x44) = 0;
                    } else {
                        *(s16 *)(payload + 0x42) = 1;
                    }
                } else {
                    *(s32 *)(payload + 0x44) = 0;
                }
                *(s32 *)(payload + 0x48) = 0;
            }
        }
        *(s16 *)(payload + 0x40) = isAlternate;
    }
    obj = (u8 *)*slot;
    *(TI128 *)(obj + 0x10) = *pos;
    payload = *(u8 **)(obj + 0x68);
    *(s16 *)(payload + 0x2E) = 1;
}
