#include "include_asm.h"

#include "common.h"
extern void func_002A7750(char *, s32, s32);
extern void func_0029F338(char *);
extern s32 func_002E5CF8(s32, s32, char *);
extern void func_00282CF0(char *, char *, char *);
extern f32 func_00282DF0(char *);
extern void func_002AAC80(f32 *, f32, f32, f32, f32);
extern void func_0029FCC0(char *, s32, void *);
extern void func_00282CC0(char *, char *, char *);
extern s32 func_002C9218(s32, char *, char *, f32);
extern void func_00282C88(char *);
extern s32 func_00282978(void *);
extern s32 func_00277258(char *, s32, char *, f32);
extern f32 D_L03_001B2A78[];
extern f32 D_L03_001BFDE8[];
extern s32 D_00138324[];
extern f32 D_L03_001B01A0 __attribute__((sda));
extern f32 D_L03_001B01C0 __attribute__((sda));
extern f32 D_L03_001B01C8[3] __attribute__((sda));
extern f32 D_L03_001B01D0;
extern char *D_L03_001BFDD8[];
extern s32 func_002761F8(char *, char *, s32, char *, s32);
extern void func_0029F978(char *, s32, char *);
extern void func_L03_003C8660(char *, char *);
extern void func_L03_0041F048(char *, char *);
extern void func_002AA548(f32 *, f32 *, f32, f32, f32, f32);
extern void func_PAL_L03_003CBB00(char *);
extern void func_L00_003294F0(char *, s32);
extern f32 func_00282E80(char *, char *);
extern void func_002AC9F8(char *, f32);
extern f32 func_00282E48(char *, char *);
extern void func_L03_003C85F8(char *, s32);
extern void func_L03_0041F008(char *, char *);
extern void func_002A0F48(char *);

/* Updates the held object, vertical spring motion and three track scales. */
void func_PAL_L03_003CB2E8(char *a0)
{
    char buf[0x30] __attribute__((aligned(16)));
    char *vars = *(char **)(a0 + 0x68);

    s32 i, landed;
    f32 height, distance, length;

    if (*(char **)(vars + 0xF0)) {
        *(s32 *)(*(char **)(vars + 0xF0) + 0x98) = 0;
    }
    func_00282978(vars + 0x104);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        D_L03_001B2A78[0] = -1.0f;
        *(s32 *)(a0 + 0x9C) = 1;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 4) & ~0x400;
        *(s32 *)(vars + 0x10C) = 0;
        *(s32 *)(vars + 0x108) = -1;
        func_00282C88(vars + 0xE0);
        *(f32 *)(vars + 0xF8) = *(f32 *)(a0 + 0x18);
        qcopy(buf, a0 + 0x10);
        *(f32 *)(buf + 8) += 20.0f;
        qcopy(buf + 0x10, a0 + 0x10);
        *(f32 *)(buf + 0x18) += 1.0f;
        if (!func_002761F8(buf + 0x10, buf, 0, a0, 0)) {
            func_0029F338(a0);
            return;
        }
        *(f32 *)(vars + 0xF4) = D_L03_001BFDE8[0];
        for (i = 0; i < 3; i++) {
            func_0029F978(a0, i, vars + 0x20 + i * 0x40);
        }
        func_002A7750(a0, 1, -1);
        break;
    case 1:
    case 2: {
        if (*(u8 *)(a0 + 0x20) == 2) {
            if (D_00138324[0] & 0xE0) {
                if (*(char **)(vars + 0xF0)) {
                    switch (*(s16 *)((*(char **)(vars + 0xF0)) + 0xAA)) {
                    case 0xB85:
                    case 0xCFC:
                        func_L03_003C8660(*(char **)(vars + 0xF0), vars + 0xE0);
                        break;
                    case 0xFFD:
                        func_L03_0041F048(*(char **)(vars + 0xF0), vars + 0xE0);
                        break;
                    }
                    *(s32 *)(*(char **)(vars + 0xF0) + 0x98) =
                        *(s32 *)(*(char **)(*(char **)(vars + 0xF0) + 0x24) + 0x10);
                    *(s16 *)(vars + 0x104) = 25;
                    *(s32 *)(vars + 0xF0) = 0;
                    *(s32 *)(vars + 0xE8) = 0;
                } else if (!*(s16 *)(vars + 0x104) && *(f32 *)(vars + 0xFC) >= -1.5f) {
                    func_002A7750(a0, 3, -1);
                    break;
                }
            } else if (*(s16 *)(vars + 0x106)) {
                *(s16 *)(vars + 0x106) = 0;
                *(u16 *)(a0 + 0x34) &= ~0x400;
                func_002A7750(a0, 1, -1);
            }
        }
        func_002AAC80((f32 *)(vars + 0xE8),
            *(f32 *)(vars + 0xF4) + D_L03_001B01A0 - *(f32 *)(a0 + 0x18),
            0.004f, 0.004f, 0.20000002f);
        func_002AA548((f32 *)(vars + 0xFC), (f32 *)(vars + 0x100),
            0.0f, 0.004f, 0.004f, 0.40000004f);
        func_PAL_L03_003CBB00(a0);
        break;
    }
    case 3: {
        char *contact;

        *(f32 *)(vars + 0x100) -= D_L03_001B01C0 * 0.00040000002f;
        *(f32 *)(vars + 0xFC) += *(f32 *)(vars + 0x100);
        if (!*(s32 *)(vars + 0x10C)) {
            func_002E5CF8(1, 0, a0);
            *(s32 *)(vars + 0x10C) = 1;
        }
        func_PAL_L03_003CBB00(a0);
        func_0029FCC0(a0, 2, buf);
        if (func_00277258(buf, 0, a0, 1.0f) || *(f32 *)(vars + 0xFC) < D_L03_001B01D0) {
            contact = D_L03_001BFDD8[0];
            landed = 1;
            if (contact) {
                switch (*(s16 *)(contact + 0xAA)) {
                case 0xB85:
                    height = *(f32 *)(contact + 0x18) + 2.7f;
                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        *(char **)(vars + 0xF0) = contact;
                    }
                    break;
                case 0xCFC: {
                    f32 height = *(f32 *)(contact + 0x18) + 2.7f;

                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        if (*(u8 *)(contact + 0x20) < 2) {
                            *(char **)(vars + 0xF0) = contact;
                        }
                    }
                    break;
                }
                case 0xFFD:
                    height = *(f32 *)(contact + 0x18) + 2.0f;
                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        func_L00_003294F0(contact, 1);
                        *(char **)(vars + 0xF0) = contact;
                    }
                    break;
                }
            }
            if (landed) {
                if (*(char **)(vars + 0xF0)) {
                    func_002A7750(a0, 4, -1);
                } else {
                    func_002A7750(a0, 2, -1);
                }
                *(s32 *)(vars + 0x100) = 0;
                *(s32 *)(vars + 0x10C) = 0;
            }
        }
        break;
    }
    case 4: {
        f32 height, y;
        char *held = *(char **)(vars + 0xF0);

        qcopy(buf, held + 0x10);
        switch (*(s16 *)(held + 0xAA)) {
        case 0xB85:
            *(f32 *)(buf + 8) += 2.2f;
            break;
        case 0xCFC:
            height = 2.2f;
            y = *(f32 *)(buf + 8);
            goto add_height;
        case 0xFFD:
        default:
            y = *(f32 *)(buf + 8);
            height = 2.0f;
        add_height:
            *(f32 *)(buf + 8) = y + height;
            break;
        }
        func_0029FCC0(a0, 2, buf + 0x10);
        *(f32 *)(buf + 0x20) = func_00282DF0(vars + 0xE0);
        distance = func_00282E80(buf + 0x10, buf);
        func_002AAC80((f32 *)(vars + 0x100), *(f32 *)(buf + 8) - *(f32 *)(buf + 0x18),
            0.008f, 0.008f, 0.20000002f);
        *(f32 *)(vars + 0xFC) += *(f32 *)(vars + 0x100);
        func_002AAC80((f32 *)(buf + 0x20), distance, 0.008f, 0.008f, 0.20000002f);
        func_00282CF0(vars + 0xE0, buf, buf + 0x10);
        *(s32 *)(vars + 0xE8) = 0;
        func_002AC9F8(vars + 0xE0, *(f32 *)(buf + 0x20));
        func_00282CC0(a0 + 0x10, a0 + 0x10, vars + 0xE0);
        func_002C9218(*(s32 *)vars, a0 + 0x10, a0 + 0x10, 1.25f);
        if (func_00282E48(buf + 0x10, buf) < 0.01f) {
            func_002A7750(a0, 2, -1);
            *(s32 *)(vars + 0xE8) = 0;
            *(s32 *)(vars + 0x100) = 0;
            switch (*(s16 *)(*(char **)(vars + 0xF0) + 0xAA)) {
            case 0xB85:
            case 0xCFC:
                func_002E5CF8(2, 0, a0);
                func_L03_003C85F8(*(char **)(vars + 0xF0), (s32)a0);
                break;
            case 0xFFD:
                func_002E5CF8(2, 0, a0);
                func_L03_0041F008(*(char **)(vars + 0xF0), a0);
                break;
            }
        }
        break;
    }
    }
    if (*(char **)(vars + 0xF0)) {
        *(s32 *)(*(char **)(vars + 0xF0) + 0x98) = *(s32 *)(*(char **)(*(char **)(vars + 0xF0) + 0x24) + 0x10);
    }
    {
        s32 j;

        for (j = 0; j < 3; j++) {
            length = *(f32 *)(vars + 0xFC);
            if (length < D_L03_001B01C8[j]) {
                length = D_L03_001B01C8[j];
            }
            *(f32 *)(vars + 0x58 + j * 0x40) = length * 1024.0f / *(f32 *)(a0 + 0x2C);
        }
    }
    func_002A0F48(a0);
    *(f32 *)(a0 + 0xC) *= 4.0f;
}
