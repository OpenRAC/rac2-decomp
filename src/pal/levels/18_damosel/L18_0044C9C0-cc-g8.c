/* func_PAL_L18_0044C9C0, the PAL copy of func_L18_00447128: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_0032D758 becomes func_PAL_0032F0B8; rename func_L18_002E0070 becomes func_PAL_L18_002E01E0; rename func_L00_0041A5C0 becomes func_PAL_L00_0041F868; rename func_L00_0041BAE8 becomes func_PAL_L00_00420D90; lit 10.0f becomes 12.0f. */
#include "common.h"

typedef struct DamoselHeroView {
    u8 pad0[0xBF8];
    void *saved;
    u8 padBFC[0x1230 - 0xBFC];
    int mask;
    u8 pad1234[0x1244 - 0x1234];
    int mode;
    u8 pad1248[0x1450 - 0x1248];
    void *vehicle;
    u8 pad1454[0x2290 - 0x1454];
    u8 *moby;
    int action;
    u8 pad2298[0x22BC - 0x2298];
    u8 blocked;
    u8 pad22BD[0x2534 - 0x22BD];
    int timer;
} DamoselHeroView;
extern DamoselHeroView D_00189E20;
extern u8 D_00188660[], D_00139568[];
typedef struct DamoselInputView {
    u8 pad[0x1A0];
    int held, pressed;
} DamoselInputView;
extern DamoselInputView D_00138180;
typedef struct DamoselWeaponView {
    u8 pad[0x70];
    float damage;
    u8 tail[0x6C];
} DamoselWeaponView;
extern u8 D_L18_0026BCF0[];
typedef struct DamoselHitRecord {
    float direction[4];
    u8 pad10[8];
    u8 type, active;
    u16 classId;
    int pad1C, flag;
    u8 pad24[12];
} __attribute__((aligned(16))) DamoselHitRecord;

typedef int DamoselQuad __attribute__((mode(TI)));
extern u8 *D_L18_001B1DCC __attribute__((sda));
extern u8 *D_L18_001B1DD0 __attribute__((sda));
extern u8 *D_L18_001B1DC8 __attribute__((sda));
extern u8 *D_L18_001C3C80[];
extern int D_L18_001A8FF0, D_L18_001A8F00;
extern void func_002FEE50(int);
extern int func_L00_00329E90(void *, int, void *);
extern u8 *func_L00_0032A088(int, int);
extern u8 *func_L00_0041A490(void *);
extern void func_002E59F8(int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_00282948(void *);
extern int func_L00_002D4040(int);
extern void func_002AA3A8(void *, void *, float, float, float, float);
extern void func_L00_002D3F30(int, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0032F0B8(void *, int, void *);
extern void func_PAL_L18_002E01E0(int, int);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032A1A8(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_0041ABB8(void *, void *, void *, int);
extern void func_PAL_L00_0041F868(void *);
extern void func_L00_0041A500(void *);
extern void func_PAL_L00_00420D90(void *);
extern void func_L00_002E6EF8(void (*)(char *), void *);
extern void func_L00_0041AE28(char *);

void func_PAL_L18_0044C9C0(u8 *obj)
{
    float velocity[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    DamoselHitRecord hit;
    int scratch;
    u8 *state = *(u8 **)(obj + 0x68);
    int i = 0, active, count;
    u8 *entry;
    u8 **targets;
    if (D_00189E20.mode == 3 && D_L18_001B1DCC) {
        for (i = 0; i < 35; i++) {
            u8 *entry = D_L18_001B1DCC + i * 64;
            if (*(int *)(entry + 0x38) >= 0) {
                func_002FEE50(*(int *)(entry + 0x38));
                *(int *)(entry + 0x38) = -1;
            }
        }
    }
    if (!obj[0x20]) {
        *(int *)(state + 0x34) = func_L00_00329E90(obj, 0, &scratch);
        D_L18_001B1DD0 = func_L00_0032A088(*(short *)(obj + 0xAA), *(int *)(state + 0x34));
        D_L18_001B1DC8 = func_L00_0041A490(D_L18_001B1DD0 + 0x33E0);
        D_L18_001B1DCC = func_L00_0041A490(D_L18_001B1DC8 + 0x1F40);
        {
            int *word = (int *)(D_L18_001B1DC8 + 0x1F30);
            for (i = 124; i >= 0; i--, word -= 16) *word = 1;
        }
        entry = D_L18_001B1DD0 + 0x33C4;
        for (i = 9; i >= 0; i--, entry -= 0x530) *(int *)entry = 0;
        {
            int invalid = -1;
            entry = D_L18_001B1DCC + 0x8B8;
            for (i = 34; i >= 0; i--, entry -= 64) *(int *)entry = invalid;
        }
        *(int *)(state + 0x3C) = 0; *(int *)(state + 0x48) = 0;
        *(int *)(state + 0x40) = 0; *(int *)(state + 0x44) = 0;
        *(int *)(state + 0x54) = 0; *(int *)(state + 0x50) = 0;
        *(int *)(state + 0x58) = 0; *(int *)(state + 0x5C) = 0;
        *(int *)(state + 0x60) = 0; *(int *)(state + 0x64) = 0;
        obj[0x20] = 1; *(int *)(state + 0x38) = -1;
    }
    if (D_00189E20.mode == 3) {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = D_00188660 + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) func_002E59F8(handle);
        }
        *(int *)(state + 0x38) = -1;
        return;
    }
    func_0029FCC0(obj, 0, state);
    if (obj[0x42] == obj[0x43] && (obj[0x60] & 2)) func_002A75E0(obj, 1, 0, 2, 0);
    active = 1;
    if (D_00189E20.action == 29) {
        if (!func_00282948(&D_00189E20.timer)) active = 0;
    } else D_00189E20.timer = 33;
    if ((D_00138180.held & D_00189E20.mask) && active && func_L00_002D4040(-1) && !D_00189E20.blocked) {
        func_002AA3A8(state + 0x50, state + 0x54, 10.0f, 0.009000001f, 0.0024f, 12.0f);
        if (*(int *)(state + 0x60) % 10 == 0) func_L00_002D3F30(-1, 1);
        ++*(int *)(state + 0x60);
        if (!func_002E59B0(obj, *(int *)(state + 0x38))) *(int *)(state + 0x38) = func_002E5CF8(0, 4, obj);
        if (obj[0x43] != 2) func_PAL_002A7E68(obj, 2, 0, 0);
        count = func_00277F48(0.5f, state, 16, obj, 0);
        if (count > 0) {
            targets = D_L18_001C3C80;
            {
                int remaining = count;
                do {
                    if (*targets != D_00189E20.moby) {
                        func_00282CF0(direction, *targets + 0x10, obj + 0x10);
                        func_00282F20(direction, direction, 1.0f);
                        func_00282F20(&hit, &hit, 1.0f);
                        func_002A8C00(&hit, obj, 0x910000,
                            ((DamoselWeaponView *)(D_L18_0026BCF0 + D_00139568[0x1D] * 0xE0))->damage,
                            direction);
                        hit.flag = 1;
                        *(DamoselQuad *)&hit = *(DamoselQuad *)direction;
                        hit.direction[3] = 5627.925f;
                        hit.type = 9; hit.active = 1;
                        hit.classId = *(short *)(*targets + 0xAA);
                        func_002A8E20(*targets, &hit);
                        func_PAL_0032F0B8(*targets, 29, obj);
                        func_002E5CF8(1, 0, obj);
                    }
                    ++targets;
                } while (--remaining);
            }
        }
    } else {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = D_00188660 + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) func_002E59F8(handle);
        }
        *(int *)(state + 0x38) = -1;
        if ((D_00138180.pressed & D_00189E20.mask) && !func_L00_002D4040(-1) && !D_00189E20.blocked) func_002E5CF8(2, 0, obj);
        func_002AA3A8(state + 0x50, state + 0x54, 0.0f, 0.072000004f, 0.012f, 0.15f);
        *(int *)(state + 0x60) = 0;
    }
    if (D_00189E20.action == 1) func_PAL_L18_002E01E0(29, 1);
    func_0029FCC0(obj, 0, state);
    func_00282C88(velocity);
    velocity[1] = -1.0f;
    func_00283098(velocity, velocity, obj + 0xC0);
    velocity[2] += 0.02f;
    func_00282F20(velocity, velocity, *(float *)(state + 0x50) * 0.05f);
    if (D_00189E20.vehicle) {
        D_00189E20.saved = D_00189E20.vehicle;
        func_L00_0032A1A8(D_00189E20.vehicle, state, velocity, *(float *)(state + 0x50) * 0.05f);
        if (D_L18_001A8FF0) {
            func_00282D30(direction, obj + 0xE0, 0.02f);
            func_00282CC0(velocity, velocity, direction);
        } else {
            velocity[2] += 0.02f;
        }
    }
    qcopy(state + 0x10, state);
    if (D_00189E20.action) func_002ACEC0(velocity, velocity, D_00189E20.moby + 0xD0, -0.09817477f);
    if (*(float *)(state + 0x50) != 0.0f) func_L00_0041ABB8(obj, state, velocity, 33);
    *(float *)(state + 0x58) -= 0.1f;
    if (*(float *)(state + 0x58) <= -8.0f) *(float *)(state + 0x58) += 8.0f;
    *(float *)(state + 0x5C) -= 0.025f;
    if (*(float *)(state + 0x5C) <= -8.0f) *(float *)(state + 0x5C) += 8.0f;
    if (*(float *)(state + 0x50) != 0.0f) {
        func_PAL_L00_0041F868(obj); func_L00_0041A500(obj);
    } else {
        *(int *)(state + 0x44) = 0; *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x48) = 0; *(int *)(state + 0x40) = 0;
    }
    func_PAL_L00_00420D90(obj);
    if (D_L18_001A8F00 != 2 && obj[0x31]) func_L00_002E6EF8(func_L00_0041AE28, obj);
}
