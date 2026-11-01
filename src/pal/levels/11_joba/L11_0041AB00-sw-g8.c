#include "include_asm.h"

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

void func_PAL_L11_0041B2E8(u8 *arg0) {
    f32 tmp[4] __attribute__((aligned(16)));
    u8 *base = D_L11_001B359C;
    u8 *entity = arg0;
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *target = base + *(s32 *)(state + 0x68) * 256;
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
        u8 *entry;
        if (*(s32 *)(state + 0x60) && *(u8 *)(target + 0x20) == 2) {
            entry = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)D_00188660);
            if (*(u8 **)(entry + 0x88) == entity) {
                if (!*(u8 *)(entry + 0x74))
                    *(s32 *)(state + 0x74) = func_002E5CF8(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = func_002E5CF8(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 2;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
        }
        break;
    }
    case 2: {
        u8 *entry;
        *(f32 *)(state + 0x70) += 0.062831864f;
        *(f32 *)(state + 0x6C) = func_00283B98(*(f32 *)(state + 0x6C), 0.062831864f);
        if (*(f32 *)(state + 0x70) >= 3.1415927410125732f) {
            if (*(s32 *)(state + 0x74) != -1) {
                entry = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)D_00188660);
                if (*(u8 **)(entry + 0x88) == entity && *(u8 *)(entry + 0x74))
                    func_002E59F8(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 3;
        } else {
            func_00282F20(tmp, entity + 0xD0, -(func_00283180(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            func_00282CC0(entity + 0x10, tmp, state + 0x80);
        }
        break;
    }
    case 3: {
        u8 *entry;
        if (*(u8 *)(target + 0x20) != 2) {
            entry = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)D_00188660);
            if (*(u8 **)(entry + 0x88) == entity) {
                if (!*(u8 *)(entry + 0x74))
                    *(s32 *)(state + 0x74) = func_002E5CF8(0, 4, entity);
            } else {
                *(s32 *)(state + 0x74) = func_002E5CF8(0, 4, entity);
            }
            *(u8 *)(entity + 0x20) = 4;
        }
        break;
    }
    case 4: {
        u8 *entry;
        *(f32 *)(state + 0x70) += 0.062831864f;
        *(f32 *)(state + 0x6C) = func_00283B98(*(f32 *)(state + 0x6C), 0.062831864f);
        if (*(f32 *)(state + 0x70) >= 6.2831854820251465f) {
            if (*(s32 *)(state + 0x74) != -1) {
                entry = (u8 *)(*(s32 *)(state + 0x74) * 0x70 + (s32)D_00188660);
                if (*(u8 **)(entry + 0x88) == entity && *(u8 *)(entry + 0x74))
                    func_002E59F8(*(s32 *)(state + 0x74));
            }
            *(s32 *)(state + 0x74) = -1;
            *(u8 *)(entity + 0x20) = 1;
            *(f32 *)(state + 0x6C) = 3.1415927410125732f;
            *(s32 *)(state + 0x70) = 0;
            qcopy(entity + 0x10, state + 0x80);
        } else {
            func_00282F20(tmp, entity + 0xD0, -(func_00283180(*(f32 *)(state + 0x6C)) + 1.0f) * 4.0f);
            func_00282CC0(entity + 0x10, tmp, state + 0x80);
        }
        break;
    }
    }
    func_002AD6F0(state + 0x20, &D_L11_001A8F20, entity + 0xF0, entity + 0xF0);
}
