#include "common.h"

/* func_US2_002F8FF8, the USA v2.00 copy of func_002F8178: the same C with its callees renamed.
   func_0026F720's slot moved: it is 0x0026F728 in the boot, but in a level func_0026F728 is the
   next function and func_0026F720 is this one, so neither name holds in every program and the
   call takes a ref_ name. */

/* Opens the vendor menu (RAC1 open_vendor_menu). It calls the boot-only
   func_US2_002FA608, so it has a unit of its own and the call stays extern. */

typedef struct { int id, kind; char pad[0x10]; } ShopSlot_002F8178;
typedef struct {
    int state, unused4, field8, fieldC;
    int base10, base14, unused18, base1C;
    char pad20[8];
    char *moby;
    char pad2C[0xC];
    int field38;
    char pad3C[8];
    int field44;
    int unused48, field4C, mode;
    char pad54[0xC];
    int restore, field64, field68, field6C;
    char pad70[8];
    int field78, field7C, index, field84, field88, field8C;
    char pad90[0x10];
    int fieldA0, fieldA4;
    char padA8[0xC];
    int fieldB4, fieldB8;
    float fieldBC;
    char padC0[0x10];
    float position[4], rotation[4];
    char padF0[0x50];
    ShopSlot_002F8178 slots[64];
    int count, field744;
    char pad748[0x18];
} Shop_002F8178;
extern Shop_002F8178 D_0021F240;
typedef struct { char pad[0xC]; int baseC, base10; } Resources_002F8178;
extern Resources_002F8178 D_001BAEC0;
typedef struct { char pad[0x20]; short level; } Settings_002F8178;
extern Settings_002F8178 D_001A79F8 MACRO_ADDR;
typedef struct {
    char pad[0x1248];
    int mode;
    char pad124C[0x1069];
    char flag22B5;
    char pad22B6[6];
    char flag22BC;
} Hero_002F8178;
extern Hero_002F8178 D_00189E20;
extern char D_001B5340[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern unsigned char D_001A7BB1;
extern int D_001A7B90;
extern int D_001A7AF0 MACRO_ADDR;
extern int D_001AD1C0;
extern int D_001AD1C4 __attribute__((sda)), D_001AD230 __attribute__((sda));
extern char D_001AD1E0[] SDATA(D_001AD1E0), D_001AD1F0[] SDATA(D_001AD1F0);
extern char D_001AD210[] SDATA(D_001AD210), D_001AD220[] SDATA(D_001AD220);
extern float D_001AD234 SDATA(D_001AD234), D_001AD238 SDATA(D_001AD238);
extern float D_001B2280, D_001B15A0;
extern int D_001B15A4;
extern int D_001B2238, D_001B2244, D_001B2248;
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001A8BB0;
extern struct { int w, h; } D_001A7340;
extern char D_00152CE4[], D_001C2AC0[];
extern void func_00282A60(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_002A0F48(void *);
extern void func_US2_002FA608(void);
extern void func_002F6608(int);
extern void func_002F71B8(void);
extern void func_002F73A8(void);
extern void func_002F7738(void);
extern void func_00132AF8(int);
extern void func_002B72E8(int);
extern void func_00132028(void);
extern void func_0028E408(void);
extern void func_0029B698(int);
extern void func_0029B6D0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00288EA0(void);
extern unsigned int func_US2_0026F750(int, int);
extern void ref_US2_002F8FF8_00(void);
extern void func_00283098(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_00335438(void *, void *, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_US2_00272378(void);

void func_US2_002F8FF8(char *moby)
{
    int mode, v, visible, count;
    float vec[4];

    func_00282A60(&D_0021F240, 0, 0x760);
    if (D_001A7B90) D_001B2280 = 1.076923f;
    else D_001B2280 = 1.0f;
    D_0021F240.restore = 0;
    D_001AD1C0 = D_001A79F8.level;
    mode = (int)moby;
    if ((unsigned)moby < 4) {
        D_0021F240.restore = 1;
        moby = func_0029EFD0(11);
        *(short *)(moby + 0x32) = 64;
        if (D_001A7BB1) qcopy(vec, D_001AD1F0);
        else qcopy(vec, D_001AD1E0);
        vec[2] = -vec[2];
        func_00282CC0(moby + 0x10, D_001B5340, vec);
        func_00282C88(moby + 0xF0);
        *(float *)(moby + 0xF8) = 3.1415927f;
        func_002A0F48(moby);
        D_0021F240.restore = 1;
        D_0021F240.field744 = 0;
        moby[0x20] = 3;
        if (mode == 0) {
            D_0021F240.field744 = 0;
            D_0021F240.mode = 0;
        } else if (mode == 1) {
            D_0021F240.mode = 1;
        } else if (mode == 2) {
            D_0021F240.mode = 2;
            D_0021F240.fieldBC = -1.5707964f;
            D_0021F240.fieldB4 = 0;
            D_0021F240.fieldB8 = 0;
            D_0021F240.fieldA4 = 0;
        } else {
            D_0021F240.mode = 3;
        }
    } else if (*(short *)(moby + 0xAA) == 11) {
        D_0021F240.field744 = 0;
        v = *(int *)(*(char **)(moby + 0x68) + 0x94);
        if (v == 0) {
            D_0021F240.mode = 0;
        } else if (v == 1) {
            D_0021F240.mode = 1;
            func_US2_002FA608();
        } else if (v == 4) {
            D_0021F240.mode = 2;
        } else if (v == 2) {
            D_0021F240.mode = 3;
        } else if (v == 3) {
            D_0021F240.field744 = 1;
            D_0021F240.mode = 0;
        }
    } else if (*(short *)(moby + 0xAA) == 0x1309) {
        D_0021F240.moby = moby;
        D_0021F240.mode = 2;
    } else if (*(short *)(moby + 0xAA) == 0xDDC) {
        D_0021F240.moby = moby;
        D_0021F240.mode = 1;
        func_US2_002FA608();
    }
    if (D_001AD1C4 != -1) D_0021F240.mode = D_001AD1C4;
    D_0021F240.field88 = 0;
    D_0021F240.field8C = 0;
    D_0021F240.field38 = 0;
    D_0021F240.field44 = D_001A7BB4[0] - 1;
    if (D_0021F240.field44 < 0) D_0021F240.field44 = 0;
    D_0021F240.field78 = -1;
    D_0021F240.field7C = -1;
    D_0021F240.field64 = 0;
    D_0021F240.index = 0;
    D_001B2244 = 0;
    D_0021F240.field84 = 0;
    D_0021F240.field68 = -1;
    D_001AD234 = 0.8f;
    D_001AD238 = 1.0f;
    D_001B2290 = 96;
    D_001B2248 = 0;
    D_001B2238 = 0;
    D_001B2294 = 96;
    D_001AD230 = 0;
    D_001B2284 = 0;
    D_001B2288 = 0;
    D_001B2298 = 85;
    D_001B228C = 0;
    func_00132AF8(93);
    func_002B72E8(0);
    func_00132028();
    if (D_0021F240.mode == 0) func_002F6608(0);
    else if (D_0021F240.mode == 3) func_002F71B8();
    else if (D_0021F240.mode == 1) func_002F73A8();
    else if (D_0021F240.mode == 2) func_002F7738();
    count = D_0021F240.count;
    visible = count / 2;
    if (count < 3) visible = 1;
    D_0021F240.index = count / 2;
    D_0021F240.field6C = (visible - count / 2) * 40;
    func_0028E408();
    if (D_0021F240.mode != 2) func_0029B698(0x112A880);
    if (D_0021F240.mode == 0 && D_0021F240.slots[D_0021F240.index].kind == 1 && D_00189E20.mode != 10)
        func_0029B6D0(D_0021F240.slots[D_0021F240.index].id, 0x112A880);
    D_0021F240.state = 0;
    D_0021F240.base10 = D_001BAEC0.base10 + 0x60000;
    D_0021F240.base1C = D_0021F240.base10 + D_001A7340.w * D_001A7340.h * 4;
    D_0021F240.field8 = 0;
    D_0021F240.fieldC = 1;
    D_0021F240.moby = moby;
    D_0021F240.base14 = D_001BAEC0.baseC + 0x60000;
    func_002E5CF8(3, 17, moby);
    D_0021F240.field4C = D_001A7AF0;
    D_0021F240.fieldA0 = *(short *)D_00152CE4;
    func_00288EA0();
    D_001A8BB0 = 5;
    D_001B15A0 = 0.0f;
    D_001B15A4 = 0;
    func_US2_0026F750(97, 1);
    D_00189E20.flag22BC = 1;
    D_00189E20.flag22B5 = 1;
    ref_US2_002F8FF8_00();
    if (!D_0021F240.restore) {
        if (D_001A7BB1) func_00283098(D_0021F240.position, D_001AD1F0, D_0021F240.moby + 0xC0);
        else func_00283098(D_0021F240.position, D_001AD1E0, D_0021F240.moby + 0xC0);
        func_00282CC0(D_0021F240.position, D_0021F240.position, D_0021F240.moby + 0x10);
        D_0021F240.rotation[2] = func_00283B98(*(float *)(D_0021F240.moby + 0xF8), 3.1415927f);
        func_00335438(D_0021F240.position, D_0021F240.rotation, 1, 0, 0);
        qcopy(vec, D_0021F240.position);
        if (D_0021F240.mode == 2) vec[1] += 5.0f;
        func_00335370(vec);
        func_003353C8(D_0021F240.rotation);
        func_US2_00272378();
    }
    func_00283098(D_001C2AC0 + 0x10, D_001AD210, D_0021F240.moby + 0xC0);
    qcopy(D_001C2AC0, D_001AD220);
    qzero_nc(D_001C2AC0 + 0x30);
    qzero_nc(D_001C2AC0 + 0x20);
}
