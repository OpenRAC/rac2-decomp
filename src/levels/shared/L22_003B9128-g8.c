#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The resident word the hero's key is read from. */
extern u32 g_hero_moby[];

/* the two resident slots func_L22_003B8FE8 fills */
extern int ref_L22_003B8FE8_00 __attribute__((sda));

extern int ref_L22_003B8FE8_01 __attribute__((sda));

/* a plain small extern: $gp in a delay slot, absolute where it stays */
extern s32 D_L22_001A8FF0;

extern u8 *keyed_object_create(u8 *arg0, TI128 *arg1);

typedef union { u8 b[0x100]; TI128 q[0x10]; } Hero;

extern u8 g_hero_state[];

/* the two handles the new object's sound slots get, one per key */
extern s32 D_L22_001AFA00 __attribute__((sda));

extern s32 D_L22_001AFA04 __attribute__((sda));

/* the object the alternate key aims at */
extern u8 *ref_L22_003B9128_00;

/* the facing and range limits of the alternate key's aim */
extern float D_L22_001AF9E4 __attribute__((sda));

extern float D_L22_001AF9E8 __attribute__((sda));

extern s32 snd_start_in_slot(s32, s32, s32);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float FastVecDot(void *, void *);

extern float fast_vec_dist(void *, void *);

extern void arena_push_point_out(void *, float);

/* makes sure the word chosen by the key holds an object (creating and aiming it when it does
   not), then moves it to the given position */
void keyed_object_place(u8 *owner, TI128 *position, s32 is_alternate) {
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

    if (is_alternate != 0) {
        slot = &ref_L22_003B8FE8_01;
    }
    local = *position;
    if (*slot == 0) {
        keyed_object_create(owner, &local);
        if (is_alternate != 0) {
            D_L22_001AFA00 = snd_start_in_slot(0x14, 0, 0);
        } else {
            D_L22_001AFA04 = snd_start_in_slot(0x14, 0, 0);
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
            } else if ((hero = (u8 *)g_hero_moby[0]) == 0) {
                *(s32 *)(payload + 0x48) = 0;
            } else {
                if (is_alternate != 0) {
                    *(u8 **)(payload + 0x44) = target;
                } else {
                    *(u8 **)(payload + 0x44) = hero;
                }
                if (is_alternate != 0) {
                    FastVecScale(&dir, *(u8 **)(payload + 0x44) + 0xE0, 4.0f);
                    FastVecAdd(&dir, &dir, *(u8 **)(payload + 0x44) + 0x10);
                } else {
                    qcopy(&dir, *(u8 **)(payload + 0x44) + 0x10);
                    arena_push_point_out(&dir, 2.2f);
                }
                FastVecSub(payload + 0x50, &dir, owner + 0x10);
                vec_scale_to_length(payload + 0x50, payload + 0x50, 1.0f);
                qcopy(&facing, owner + 0xC0);
                vec_scale_to_length(&facing, &facing, 1.0f);
                dot = FastVecDot(payload + 0x50, &facing);
                if (is_alternate != 0) {
                    dist = fast_vec_dist(target + 0x10, &((Hero *)g_hero_state)->q[8]);
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
        *(s16 *)(payload + 0x40) = is_alternate;
    }
    obj = (u8 *)*slot;
    *(TI128 *)(obj + 0x10) = *pos;
    payload = *(u8 **)(obj + 0x68);
    *(s16 *)(payload + 0x2E) = 1;
}
