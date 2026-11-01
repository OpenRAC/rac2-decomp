#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern void func_002A7750();
extern void func_002A0488(void *, void *, void *, void *);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern u8 D_0019B2E8[];
extern u16 D_0018CFDC;
extern u8 D_0019B4A8[];

/* brings the actor into its armed state */
void func_PAL_L02_00410480(u8 *a0, int a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    int one = 1;
    u32 v;

    *(float *)(s0 + 0x20) = (float)*(s16 *)(s0 + 0x24);
    *(u16 *)(s0 + 0x2E2) = one;
    func_002B60B0(a0, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    func_002A7750(a0, 3, 1);
    if (*(u8 *)(a0 + 0x43) != 2)
        func_PAL_002A7E68(a0, 2, 0, 0);
    *(u32 *)(a0 + 0x98) = *(u32 *)(*(u32 *)(a0 + 0x24) + 0x10);
    *(u8 *)(s0 + 0x6A) = 0;
    *(u8 *)(s0 + 0x2E) = one;
    *(u8 *)(a0 + 0x31) = one;
    v = *(u16 *)(a0 + 0x34);
    *(u8 *)(a0 + 0x7F) = 0;
    *(u16 *)(a0 + 0x34) = (v | 0x1000) & 0xFFB8;
    *(u16 *)(s0 + 0x2E8) = a1;
    *(u16 *)(s0 + 0x88) = 0;
    if (*(s16 *)(s0 + 0x50) != 0) {
        *(u16 *)(s0 + 0x50) = 0;
        func_002A0488(a0, *(u8 *)(s0 + 0x54), *(u8 *)(s0 + 0x55), *(u8 *)(s0 + 0x56));
        *(u16 *)(s0 + 0x52) = one;
    }
}


extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float,
                          int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A0F68(void *);
extern void func_L02_0040B980(u8 *);

/* arms the actor: its two effect tracks, then the shared state resets */
void func_PAL_L02_00410598(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    float buf[3];

    *(u16 *)(s1 + 0x2E2) = 0;
    *(u32 *)(s1 + 0x2D4) = 0;
    if (a0[0x31]) {
        func_PAL_L00_003FB330(a0 + 0x10, 0, 5, 5, 0x19, 0x14, 0xA, 1, 0.5f, 0.0f,
                      1, 0, 0, 0);
        func_002E5DA0(0, 0, a0, 0xC3E);
        func_002A7A00(buf, 0.10000001f, 0.14000002f);
        func_00282CC0(buf, buf, s1 + 0xD0);
        func_PAL_002B15D8(a0, 0xFF, buf, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    func_PAL_002A7E68(a0, 0, 0, 3);
    func_PAL_002A0F68(a0);
    func_002A7750(a0, 1, 0);
    *(u8 *)(a0 + 0x31) = 0;
    *(u32 *)(a0 + 0x98) = 0;
    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xEFFF) | 0x47;
}

