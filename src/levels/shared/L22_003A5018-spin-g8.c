#include "common.h"
extern u8 D_00189E20[];
extern f32 func_00282E48(void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern int func_002B3868(void *);
extern void func_L00_0035F5A0(int, int, int);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_L00_00325600(void *, void *, int);
extern void func_00282D30(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283360(void *);
extern void func_002B9180(void *);
extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, f32);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L22_003A2988(void *, f32);
extern int func_002A77E0(int);
extern f32 ref_L22_003FC870_00 __attribute__((sda));
extern f32 ref_L22_003FC870_01 __attribute__((sda));
extern int ref_L22_003FC870_02 __attribute__((sda));
extern f32 ref_L22_003FC870_03 __attribute__((sda));
extern u8 * ref_L22_003FC870_04 __attribute__((sda));
extern f32 ref_L22_003FC870_05 __attribute__((sda));
extern f32 ref_L22_003FC870_06;
extern const f32 ref_L22_003FC870_07;
extern u8 ref_L22_003FC870_08[];
extern u8 * ref_L22_003FC870_09;
extern void func_L22_003FCF08(void *, void *, int, int);

void func_L22_003FC870(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    f32 f;
    int i;
    u8 *basis;
    f32 side;
    f32 rot[4] __attribute__((aligned(16)));
    union {
        struct {
            f32 mat[12];
            f32 start[4];
            f32 end[4];
            f32 scale[12];
        } transform;
        struct {
            f32 mat[4];
            f32 move[4];
            f32 start[4];
            f32 end[4];
        } collision;
    } scratch __attribute__((aligned(16)));
    if (func_002B3868(obj) && obj[0x20] == 0x10) func_L00_0035F5A0(0x12, 0, 0);
    if (obj[0x31]) {
        f = func_00282E48(D_00189E20 + 0x80, obj + 0x10);
        *(f32 *)(ctl + 0x44) = f;
    if (ref_L22_003FC870_07 <= f) obj[0x23] = 127;
    } else *(f32 *)(ctl + 0x44) = 2000.0f;
    if (obj[0x20] == 0) {
        qzero_nc(rot);
        rot[2] = 0.018907737f;
        func_002833F0(scratch.transform.mat, rot);
        func_00283738(obj + 0xC0, obj + 0xC0, scratch.transform.mat);
        func_002AFFD8(obj + 0x10, ctl + 0x10, 0);
        func_L00_00325600(obj + 0xC0, ctl + 0x10, 0);
    } else {
        qzero_nc(rot);
        rot[2] = ((45.0f - (f32)*(u16 *)(obj + 0x96)) * 22.0f + 155.0f) * 0.00029088825f;
        func_002833F0(scratch.transform.mat, rot);
        if (func_002B3868(obj)) { obj[0x23] = 127; *(f32 *)(obj + 0x2C) *= 1.2f; }
        if (obj[0x23] >= 3) obj[0x23]--;
        if (obj[0x23] >= 11 && obj[0x20] == 0x10) {
            switch (*(u16 *)(obj + 0x96) & 3) {
            case 0:
                func_00282D30(scratch.transform.start, obj + 0xC0, -ref_L22_003FC870_00);
                func_00282CC0(scratch.transform.start, scratch.transform.start, obj + 0x10);
                func_00282D30(scratch.transform.end, obj + 0xD0, -ref_L22_003FC870_01);
                break;
            case 1:
                func_00282D30(scratch.transform.start, obj + 0xC0, ref_L22_003FC870_00);
                func_00282CC0(scratch.transform.start, scratch.transform.start, obj + 0x10);
                func_00282D30(scratch.transform.end, obj + 0xD0, ref_L22_003FC870_01);
                break;
            case 2:
                func_00282D30(scratch.transform.start, obj + 0xD0, ref_L22_003FC870_00);
                func_00282CC0(scratch.transform.start, scratch.transform.start, obj + 0x10);
                func_00282D30(scratch.transform.end, obj + 0xC0, ref_L22_003FC870_01);
                break;
            case 3:
                func_00282D30(scratch.transform.start, obj + 0xD0, -ref_L22_003FC870_00);
                func_00282CC0(scratch.transform.start, scratch.transform.start, obj + 0x10);
                func_00282D30(scratch.transform.end, obj + 0xC0, -ref_L22_003FC870_01);
                break;
            }
            func_L22_003FCF08(scratch.transform.start, scratch.transform.end, ref_L22_003FC870_02, 0);
        }
        func_00283360(scratch.transform.scale);
        scratch.transform.scale[0] = scratch.transform.scale[5] = scratch.transform.scale[10] = (45.0f - (f32)*(u16 *)(obj + 0x96) * 0.022222223f) * (ref_L22_003FC870_03 * 0.022222223f);
        func_00283738(scratch.transform.mat, scratch.transform.scale, scratch.transform.mat);
        func_00283738(obj + 0xC0, obj + 0xC0, scratch.transform.mat);
        
        if (*(u16 *)(obj + 0x96) >= 46) {
            func_0029F338(obj);
            return;
        }
        if (obj[0x20] == 0x10) {
            qcopy(obj + 0x10, D_00189E20 + 0x80);
            func_002AFFD8(obj + 0x10, ctl + 0x10, 0);
            func_L00_00325600(obj + 0xC0, ctl + 0x10, 0);
            func_00282F20(scratch.transform.start, ctl + 0x10, -((f32)*(u16 *)(obj + 0x96) * 0.022222223f) * 7.5f);
            func_00282CC0(obj + 0x10, obj + 0x10, scratch.transform.start);
        } else {
            qcopy(obj + 0x10, ref_L22_003FC870_04 + 0x10);
            func_002AFFD8(obj + 0x10, ctl + 0x10, 0);
            func_L00_00325600(obj + 0xC0, ctl + 0x10, 0);
            func_00282F20(scratch.transform.start, ctl + 0x10, -((f32)*(u16 *)(obj + 0x96) * 0.022222223f) * 7.5f);
            func_00282CC0(obj + 0x10, obj + 0x10, scratch.transform.start);
        }
    }
    if (*(u16 *)(obj + 0x96) < 65535) (*(u16 *)(obj + 0x96))++;
    else *(u16 *)(obj + 0x96) = 0;
    if (*(s16 *)(ctl + 0x2A) != 0 && (*(u16 *)(obj + 0x96) & 31) == 0) {
        func_00282D30(rot, ctl + 0x10, 6.0f);
        func_00282D30(scratch.collision.mat, ctl + 0x10, -3.0f);
        func_00282CC0(rot, rot, obj + 0x10);
        func_00282CC0(scratch.collision.mat, scratch.collision.mat, obj + 0x10);
        if (func_002761F8(scratch.collision.mat, rot, 0x12, 0, 0) == 0) {
            func_L22_003A2988(obj + 0x10, 0.0f);
            func_00282D30(scratch.collision.move,
                obj + 0xC0 + func_002A77E0(2) * 16,
                func_002A77E0(2) ? ref_L22_003FC870_05 : -ref_L22_003FC870_06);
            func_00282CC0(obj + 0x10, obj + 0x10, scratch.collision.move);
            func_L22_003A2988(obj + 0x10, 0.0f);
            func_00282D30(scratch.collision.start, ctl + 0x10, 3.0f);
            func_00282D30(scratch.collision.end, ctl + 0x10, -3.0f);
            func_00282CC0(scratch.collision.start, scratch.collision.start, obj + 0x10);
            func_00282CC0(scratch.collision.end, scratch.collision.end, obj + 0x10);
            if (func_002761F8(scratch.collision.end, scratch.collision.start, 0x12, 0, 0)) qcopy(obj + 0x10, ref_L22_003FC870_08);
            *(s16 *)(ctl + 0x2A) = 0;
        }
    }
}
