#include "include_asm.h"

#include "common.h"
extern s32 func_00283CF0(f32 a0);
extern u8 *D_L11_001B359C;
extern u8 D_L11_00188660[];
extern void *D_L11_001FC420[];
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002E59F8(s32);
extern s32 D_L11_001B0808 __attribute__((sda));

/* Once the linked object is in state 2 and the shared step counter is in phase, moves the object
   through one cycle along its vector from its start position, keeping its sound playing; when its
   trigger value is set, flags the objects of the two listed groups (0xCF5, 0xCF6, 0xD07) and sets
   its own state to 4.
   The two sound lookups are separate values, and the early exits return without stepping the
   shared counter, as retail does. */
void func_PAL_L11_003FC090(u8 *arg0) {
    f32 tmp[4];
    u8 *base = D_L11_001B359C;
    u8 *self = arg0;
    u8 *vars = *(u8 **)(self+0x68);
    u8 *target = base + *(s32 *)(vars+8)*256;
    u8 *entry;
    s16 *list;
    s16 *start;
    u8 *obj;
    switch (*(u8 *)(self+0x20)) {
    case 0:
        *(u8 *)(self+0x20) = 1;
        *(f32 *)(vars+0xC) = 3.1415927410125732f;
        *(s32 *)(vars+0x10) = 0;
        D_L11_001B0808 = 0;
        qcopy(vars+0x20,self+0x10);
        *(s32 *)(vars+0x1C) = 0;
        /* fall through */
    case 1:
        if (*(s32 *)vars && *(u8 *)(target+0x20) == 2 &&
            D_L11_001B0808 == func_00283CF0(*(f32 *)(vars+4)*15.0f)) {
            *(u8 *)(self+0x20) = 2;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            *(s32 *)(vars+0x10) = 0;
        }
        break;
    case 2: {
        s32 handle;
        *(f32 *)(vars+0x10) += 0.062831864f;
        *(f32 *)(vars+0xC) = func_00283B98(*(f32 *)(vars+0xC),0.062831864f);
        handle = *(s32 *)(vars+0x30);
        entry = D_L11_00188660 + handle * 0x70;
        if (*(u8 **)(entry+0x88) != self || !*(u8 *)(entry+0x74))
            *(s32 *)(vars+0x30) = func_002E5CF8(0,4,self);
        if (*(f32 *)(vars+0x10) >= 6.2831854820251465f) {
            if (*(u8 *)(target+0x20) != 2) {
                *(u8 *)(self+0x20) = 1;
                if (*(s32 *)(vars+0x30) != -1) {
                    u8 *sound = D_L11_00188660 + *(s32 *)(vars+0x30)*0x70;
                    if (*(u8 **)(sound+0x88) == self && *(u8 *)(sound+0x74))
                        func_002E59F8(*(s32 *)(vars+0x30));
                }
                *(s32 *)(vars+0x30) = -1;
            }
            *(s32 *)(vars+0x10) = 0;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            qcopy(self+0x10,vars+0x20);
        } else {
            func_00282F20(tmp,self+0xD0,-(func_00283180(*(f32 *)(vars+0xC))+1.0f)*2.2f);
            func_00282CC0(self+0x10,tmp,vars+0x20);
        }
        break;
    }
    }
    if (*(f32 *)(vars+4) == 1337.0f) {
        if (*(u8 *)(target+0x20) == 2) {
            if (*(s32 *)(vars+0x1C) == 0) {
                *(s32 *)(vars+0x1C) = 1;
                if (*(s32 *)(vars+0x14) == 255 || (start = D_L11_001FC420[*(s32 *)(vars+0x14)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                list = start;
                do {
                    obj = D_L11_001B359C + ((*list & 0x7FFF) << 8);
                    if (*(s8 *)(obj+0x20) >= 0) {
                        s32 kind = *(s16 *)(obj+0xAA);
                        if (kind == 0xCF5) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF6) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xD07) *(u8 *)(obj+0x95) = 1;
                    }
                } while (*list++ >= 0);
                if (*(s32 *)(vars+0x18) == 255 || (start = D_L11_001FC420[*(s32 *)(vars+0x18)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                list = start;
                do {
                    obj = D_L11_001B359C + ((*list & 0x7FFF) << 8);
                    if (*(s8 *)(obj+0x20) >= 0) {
                        s32 kind = *(s16 *)(obj+0xAA);
                        if (kind == 0xD07) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF6) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF5) *(u8 *)(obj+0x95) = 1;
                    }
                } while (*list++ >= 0);
                *(u8 *)(self+0x20) = 4;
            }
            if (++D_L11_001B0808 > 104) D_L11_001B0808 = 0;
        } else D_L11_001B0808 = 0;
    }
}

extern void func_PAL_L01_002EBFB8(s32, s32, s32, s32, s32);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00282948(void *);
extern s32 func_PAL_00289730(s32, s32);
extern u16 D_0018CD60 NOT_SDA;
extern u16 D_00194158 NOT_SDA;
extern u16 D_0018D048 NOT_SDA;
extern s32 D_L11_001B30C8 __attribute__((sda));
extern u8 D_00189EA0[];
extern u8 D_001A7B00[0x38] __attribute__((sda));
extern s32 D_L11_001A9010[] __attribute__((sda));

/* Queues Joba subtitles when inventory and cuboid gates permit, with retry timers. */
void func_PAL_L11_00417778(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0xFF;
        *(s32 *)(state + 0x8) = 0x15E;
        *(s32 *)(state + 0x10) = 0xFA;
    }
    if (*(u8 *)(object + 0x20) != 1) {
        return;
    }
    if (D_001A7B00[0]) {
        func_PAL_L01_002EBFB8(0x9FF, 0x56, 3, *(s32 *)(state + 0x4), -1);
    }
    if (D_L11_001A9010[0] != 0 && D_L11_001B30C8 >= 3) {
        D_0018CD60 = 0xFFFF;
    }
    if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 0x0)) != 0) {
        if (func_00282948(state + 0x8) != 0) {
            if (D_00194158 == 0) {
                func_PAL_00289730(0xA00, 0x57);
                *(s32 *)(state + 0x8) = 0x15E;
            }
        }
    }
    if (D_001A7B00[0x2E]) {
        func_PAL_L01_002EBFB8(0xA03, 0x5A, 0, *(s32 *)(state + 0xC), -1);
    }
    if (D_001A7B00[0xB]) {
        if (D_0018D048 == 0) {
            if (func_00282948(state + 0x10) != 0) {
                func_PAL_00289730(0xA3D, 0x94);
            }
        }
    }
}
