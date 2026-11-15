#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

extern u8 *D_L11_001B359C;
extern u8 D_00188660[];
extern Vector128 D_L11_001A8F20 __attribute__((sda));
extern s32 D_L11_001B0D88 __attribute__((sda));
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002E59F8(s32);

/* Waits for its trigger object to become active, then bobs the object out and back in a smooth wave with a sound, and repeats. */
void func_L11_00416658(u8 *mobyArg) {
    f32 offset[4] __attribute__((aligned(16)));
    u8 *mobyTable = gMobyTable_L11;
    u8 *entity = mobyArg;
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *target = mobyTable + *(s32 *)(state + 0x68) * 256;
    switch (*(u8 *)(entity + 0x20)) {
    case 0:
        *(u32 *)(state + 0x5C) |= 4;
        *(u8 *)(entity + 0x20) = 1;
        *(f32 *)(state + 0x6C) = 3.1415927410125732f;
        *(s32 *)(state + 0x70) = 0;
        D_L11_001B0D88 = 0;
        qcopy(state + 0x80, entity + 0x10);
        /* fall through */
    case 1: {
        u8 *soundSlot;
        if (*(s32 *)(state + 0x60) && *(u8 *)(target + 0x20) == 2) {
            soundSlot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)gSoundState);
            if (*(u8 **)(soundSlot + 0x88) == entity) {
                if (!*(u8 *)(soundSlot + 0x74))
                    *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 2;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
        }
        break;
    }
    case 2: {
        u8 *soundSlot;
        *(f32 *)(state + 0x70) += 0.05235988646745682f;
        *(f32 *)(state + 0x6C) = FastAddRotations(*(f32 *)(state + 0x6C), 0.05235988646745682f);
        if (*(f32 *)(state + 0x70) >= 3.1415927410125732f) {
            if (*(s32 *)(state + 0x74) != -1) {
                soundSlot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)gSoundState);
                if (*(u8 **)(soundSlot + 0x88) == entity && *(u8 *)(soundSlot + 0x74))
                    StopSoundVoice(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 3;
        } else {
            vec_scale_to_length(offset, entity + 0xD0, -(FastSinOrCosA(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            FastVecAdd(entity + 0x10, offset, state + 0x80);
        }
        break;
    }
    case 3: {
        u8 *soundSlot;
        if (*(u8 *)(target + 0x20) != 2) {
            soundSlot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)gSoundState);
            if (*(u8 **)(soundSlot + 0x88) == entity) {
                if (!*(u8 *)(soundSlot + 0x74))
                    *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = PlayMobySound(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 4;
        }
        break;
    }
    case 4: {
        u8 *soundSlot;
        *(f32 *)(state + 0x70) += 0.05235988646745682f;
        *(f32 *)(state + 0x6C) = FastAddRotations(*(f32 *)(state + 0x6C), 0.05235988646745682f);
        if (*(f32 *)(state + 0x70) >= 6.2831854820251465f) {
            if (*(s32 *)(state + 0x74) != -1) {
                soundSlot = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)gSoundState);
                if (*(u8 **)(soundSlot + 0x88) == entity && *(u8 *)(soundSlot + 0x74))
                    StopSoundVoice(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 1;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
            qcopy(entity + 0x10, state + 0x80);
        } else {
            vec_scale_to_length(offset, entity + 0xD0, -(FastSinOrCosA(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            FastVecAdd(entity + 0x10, offset, state + 0x80);
        }
        break;
    }
    }
    CombineTransformsAndStore(state + 0x20, &D_L11_001A8F20, entity + 0xF0, entity + 0xF0);
}
