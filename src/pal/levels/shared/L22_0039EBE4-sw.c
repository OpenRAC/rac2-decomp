#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x14];
    u8 *target;
    f32 f18;
    f32 f1C;
    f32 f20;
} FollowVars;
extern char D_00189E20[];
extern u32 D_00138320;
extern unsigned int func_L22_002A8CE0(int);
extern unsigned int func_PAL_L22_002C99C8(int, int);
extern void func_PAL_L00_002D2668(int, int, float);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_002E6CF0(void (*)(char *), char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern s32 func_PAL_00311D98(s32 arg0, f32 fparg0);
extern void func_L01_0038EF40(char *);

void func_PAL_L22_0039EBE4(u8 *self)
{
    FollowVars *data;
    u8 *vars;
    f32 dist;
    f32 v1[4];
    f32 v2[4];

    if (((Hero *)D_00189E20)->i[0x2294 / 4] == 1)
        func_PAL_L22_002C99C8(0x1D, 1);
    data = *(FollowVars **)(self + 0x68);
    if (data == 0)
        return;
    vars = 0;
    if (data->target == 0) {
        data->target = (u8 *)func_PAL_00311D98((s32)self, 0.96000004f);
        if (data->target == 0)
            goto have;
    }
    vars = *(u8 **)(data->target + 0x68);
have:
    if ((((Hero *)D_00189E20)->i[0x2294 / 4] == 1 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x1D) && ((Hero *)D_00189E20)->i[0x1B8 / 4] >= 2) {
        func_00273318(self, 1.0f, 0xFF0000FF, 0, 0x24, 0.0f, -1, 90.0f, 4);
        if (((Hero *)D_00189E20)->i[0xAA8 / 4] != 0 && ((Hero *)D_00189E20)->ptr[0xAA4 / 4] != 0)
            func_00273318(self, 1.4f, 0xFFFF0000, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
        else if (((Hero *)D_00189E20)->ptr[0xAD0 / 4] != 0)
            func_00273318(self, 1.4f, 0xFFFF0000, ((Hero *)D_00189E20)->ptr[0xAD0 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
    }

    switch (self[0x20]) {
    case 0:
    case 1:
        if (self[0x60] & 2) {
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, 8);
            self[0x20] = 1;
        }
        if (data->target != 0) {
            u8 *t;
            func_0029FCC0(self, 0, data->target + 0x10);
            t = data->target;
            *(TI128 *)(t + 0xC0) = *(TI128 *)(self + 0xC0);
            *(TI128 *)(t + 0xD0) = *(TI128 *)(self + 0xD0);
            *(TI128 *)(t + 0xE0) = *(TI128 *)(self + 0xE0);
        }
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x23 || (((Hero *)D_00189E20)->i[0x229C / 4] == 0xF && ((Hero *)D_00189E20)->i[0x684 / 4] != 0)) {
            if (vars != 0) {
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.96000004f;
                if (self[0x43] != 3)
                    func_PAL_002A7E68(self, 3, 0, 8);
                func_002E5CF8(0, 0, (char *)self);
                self[0x20] = 2;
            }
        } else if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x8A) {
            if (vars != 0) {
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.96000004f;
                if (self[0x43] != 3)
                    func_PAL_002A7E68(self, 3, 0, 8);
                func_002E5CF8(0, 0, (char *)self);
                self[0x20] = 0xF;
            }
        } else if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x2B) {
            if (vars != 0) {
                f32 d = func_00282E48(((Hero *)D_00189E20)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10);
                int n = 6;
                if (((Hero *)D_00189E20)->i[0x1240 / 4] <= 0x18)
                    n = 4;
                *(f32 *)(vars + 4) = d / (f32)n;
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                if (self[0x43] != 3)
                    func_PAL_002A7E68(self, 3, 0, 8);
                func_002E5CF8(0, 0, (char *)self);
                self[0x20] = 9;
            }
        }
        break;
    case 2:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_00282CF0(v1, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10, data->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += func_00282DF0(&((Hero *)D_00189E20)->b[0x150]);
        if (((Hero *)D_00189E20)->i[0x229C / 4] == 0xF) {
            dist += ((Hero *)D_00189E20)->f[0x644 / 4];
        } else if ((((Hero *)D_00189E20)->i[0x22A4 / 4] == 4 || ((Hero *)D_00189E20)->i[0x22A4 / 4] == 2) && ((Hero *)D_00189E20)->f[0x31C / 4] > 2.0f) {
            dist = 0.96000004f;
        }
        qcopy(v2, &((Hero *)D_00189E20)->q[0x80 / 16]);
        v2[2] += 0.5f;
        if (func_002761F8(v2, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)D_00189E20)->f[0x31C / 4] > 0.5f) {
                func_PAL_L22_002C99C8(6, 1);
            } else {
                func_PAL_L22_002C99C8(0, 0);
                func_PAL_L00_002D2668(func_L22_002A8CE0(0), 0, 12.0f);
            }
            self[0x20] = 6;
        } else if (dist < func_00282E48(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10)) {
            func_00282F20(v1, v1, dist);
            func_00282CC0(data->target + 0x10, data->target + 0x10, v1);
        } else {
            qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10);
            self[0x20] = 3;
        }
        break;
    case 3:
        func_002E5CF8(1, 0, (char *)self);
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10);
        self[0x20] = 4;
        break;
    case 4:
        func_0029FCC0(self, 0, v1);
        qcopy(v1, &((Hero *)D_00189E20)->q[0x80 / 16]);
        v1[2] += 0.5f;
        if (func_002761F8(v1, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)D_00189E20)->h[0x34E / 2] != 0) {
                func_PAL_L22_002C99C8(6, 1);
            } else {
                func_PAL_L22_002C99C8(0, 1);
            }
            self[0x20] = 6;
        } else {
            if ((self[0x60] & 2) && self[0x43] != 4)
                func_PAL_002A7E68(self, 4, 0, 8);
            func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
            data->f20 = data->f20 * 0.88f;
            data->f18 = data->f18 + 0.6981318f;
            if (data->f20 < 0.16800001f) {
                ((Hero *)D_00189E20)->i[0x684 / 4] = 0;
                if (data->target != 0 && func_00282E48(data->target + 0x10, &((Hero *)D_00189E20)->q[0x80 / 16]) > 3.5f) {
                    if ((D_00138320 & ((Hero *)D_00189E20)->u[0x1230 / 4]) == 0) {
                        ((Hero *)D_00189E20)->i[0xAC8 / 4] = 1;
                        func_PAL_L22_002C99C8(0, 0);
                        func_PAL_L00_002D2668(func_L22_002A8CE0(0), 0, 12.0f);
                        self[0x20] = 6;
                    } else {
                        func_002E5CF8(2, 0, (char *)self);
                        if (((Hero *)D_00189E20)->i[0xAB8 / 4] != 0) {
                            func_PAL_L22_002C99C8(0x25, 1);
                        } else {
                            func_PAL_L22_002C99C8(0x24, 1);
                        }
                        self[0x20] = 5;
                    }
                } else {
                    func_PAL_L22_002C99C8(0, 1);
                    self[0x20] = 6;
                }
            }
        }
        break;
    case 5:
        qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAA4 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        data->f20 = data->f20 * 0.88f;
        data->f18 = data->f18 + 0.6981318f;
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if (((Hero *)D_00189E20)->i[0x2294 / 4] != 0x24 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x25)
            self[0x20] = 6;
        break;
    case 6:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        *(f32 *)(vars + 4) = 1.6000001f;
        self[0x20] = 7;
        break;
    case 7:
        func_0029FCC0(self, 0, v2);
        func_00282CF0(v1, v2, data->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += func_00282DF0(&((Hero *)D_00189E20)->b[0x150]);
        if (dist < func_00282E48(data->target + 0x10, v2)) {
            func_00282F20(v1, v1, dist);
            func_00282CC0(data->target + 0x10, data->target + 0x10, v1);
            func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        } else {
            qcopy(data->target + 0x10, v2);
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, 8);
            self[0x20] = 1;
        }
        break;
    case 9:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_00282CF0(v1, ((Hero *)D_00189E20)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10);
        if (*(f32 *)(vars + 4) < func_00282DF0(v1)) {
            func_00282F20(v1, v1, *(f32 *)(vars + 4));
            func_00282CC0(data->target + 0x10, data->target + 0x10, v1);
        } else {
            qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAD4 / 4] + 0x10);
            self[0x20] = 0xB;
            func_002E5CF8(1, 0, (char *)self);
        }
        break;
    case 10:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        self[0x20] = 0xB;
        break;
    case 11:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        if (data->f20 < 0.16800001f) {
            ((Hero *)D_00189E20)->h[0xADC / 2] = 1;
            self[0x20] = 0xC;
        }
        break;
    case 12:
        if (((Hero *)D_00189E20)->ptr[0xAD4 / 4] != 0)
            qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xAD4 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if (((Hero *)D_00189E20)->i[0x2294 / 4] != 0x2B)
            self[0x20] = 0xD;
        break;
    case 13:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        *(f32 *)(vars + 4) = 1.6000001f;
        self[0x20] = 0xE;
        break;
    case 14:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_0029FCC0(self, 0, v2);
        func_00282CF0(v1, v2, data->target + 0x10);
        if (*(f32 *)(vars + 4) < func_00282E48(data->target + 0x10, v2)) {
            func_00282F20(v1, v1, *(f32 *)(vars + 4));
            func_00282CC0(data->target + 0x10, data->target + 0x10, v1);
            func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        } else {
            qcopy(data->target + 0x10, v2);
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, 8);
            self[0x20] = 1;
        }
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x2B && vars != 0) {
            *(f32 *)(vars + 4) = func_00282E48(((Hero *)D_00189E20)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10) * 0.1f;
            data->f1C = 1.0f;
            data->f20 = 0.0f;
            data->f18 = 0.0f;
            if (self[0x43] != 3)
                func_PAL_002A7E68(self, 3, 0, 8);
            self[0x20] = 9;
        }
        break;
    case 15:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        qcopy(v1, &((Hero *)D_00189E20)->q[0x80 / 16]);
        v1[2] += 0.5f;
        if (func_002761F8(v1, ((Hero *)D_00189E20)->ptr[0xB10 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)D_00189E20)->f[0x31C / 4] > 0.5f) {
                func_PAL_L22_002C99C8(6, 1);
            } else {
                func_PAL_L22_002C99C8(0, 0);
                func_PAL_L00_002D2668(func_L22_002A8CE0(0), 0, 12.0f);
            }
            self[0x20] = 0x13;
        } else {
            func_00282CF0(v2, ((Hero *)D_00189E20)->ptr[0xB10 / 4] + 0x10, data->target + 0x10);
            if (*(f32 *)(vars + 4) < func_00282DF0(v2)) {
                func_00282F20(v2, v2, *(f32 *)(vars + 4));
                func_00282CC0(data->target + 0x10, data->target + 0x10, v2);
            } else {
                qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xB10 / 4] + 0x10);
                self[0x20] = 0x11;
                func_002E5CF8(1, 0, (char *)self);
            }
        }
        break;
    case 16:
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        self[0x20] = 0x11;
        break;
    case 17:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        if (data->f20 < 0.16800001f) {
            ((Hero *)D_00189E20)->i[0xB1C / 4] = 1;
            self[0x20] = 0x12;
        }
        break;
    case 18:
        if (((Hero *)D_00189E20)->ptr[0xB10 / 4] != 0)
            qcopy(data->target + 0x10, ((Hero *)D_00189E20)->ptr[0xB10 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        if (((Hero *)D_00189E20)->i[0x229C / 4] != 0x21)
            self[0x20] = 0x13;
        break;
    case 19:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        *(f32 *)(vars + 4) = 1.6000001f;
        self[0x20] = 0x14;
        break;
    case 20:
        if ((self[0x60] & 2) && self[0x43] != 4)
            func_PAL_002A7E68(self, 4, 0, 8);
        func_0029FCC0(self, 0, v2);
        func_00282CF0(v1, v2, data->target + 0x10);
        if (*(f32 *)(vars + 4) < func_00282E48(data->target + 0x10, v2)) {
            func_00282F20(v1, v1, *(f32 *)(vars + 4));
            func_00282CC0(data->target + 0x10, data->target + 0x10, v1);
            func_L00_002E6CF0(func_L01_0038EF40, (char *)self);
        } else {
            qcopy(data->target + 0x10, v2);
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, 8);
            self[0x20] = 1;
        }
        if (((Hero *)D_00189E20)->i[0x229C / 4] == 0x21 && vars != 0) {
            *(f32 *)(vars + 4) = func_00282E48(((Hero *)D_00189E20)->ptr[0xB10 / 4] + 0x10, data->target + 0x10) * 0.1f;
            data->f1C = 1.0f;
            data->f20 = 0.0f;
            data->f18 = 0.0f;
            if (self[0x43] != 3)
                func_PAL_002A7E68(self, 3, 0, 8);
            self[0x20] = 0xF;
        }
        break;
    case 21:
    default:
        break;
    }
}
