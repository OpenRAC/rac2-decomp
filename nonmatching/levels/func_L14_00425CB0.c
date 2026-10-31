/* Near miss for func_L14_00425CB0 (src/levels/14_aranos_prison/L14_003F4F98.c), checked in a
   unit of its own with -O2 -G8 -ffunction-sections -funroll-loops -malign-loops=2 (2320 bytes
   without the extra flags; it would need an L14_00425CB0-g8.c unit with that cflags row).
   2312/2312 bytes, one region differs: retail reads the price selector byte D_L14_001A7C8F
   (0x1A7C8F, after the "crap\n" format string) with a fresh lui/lbu macro expansion at every
   use. Declared NOT_SDA, as here, cc1 splits the address and keeps %hi(D_L14_001A7C8F) in a
   saved register at the state 2/3/4 price reads, where retail saves %hi(D_L14_00291850).
   A MACRO_ADDR scalar, a plain extern, an sda scalar or an sda/MACRO_ADDR incomplete array
   read as [0] lets reorg pull the load into a delay slot as a $gp load (2304 or 2284 bytes).
   Only an offset sdata reference (an unrelated symbol plus 7) reproduced retail, which is
   not an honest declaration. Not linked, not counted. */
#include "common.h"

/* The shared byte flags table; [7], [0x31] and [0x69] are read here. */
extern u8 D_001A7AF8[] MACRO_ADDR;
extern u8 D_001A7A40;
extern u8 D_L14_001A7C8F NOT_SDA;
extern s32 D_00139768[];
extern u32 D_00138324 NOT_SDA;
extern int D_001A79F8[] MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; float position[4]; float rotation[4];
    u8 padA0[0x40]; float aim[4]; u8 padF0[0x20]; float velocity[4];
} JobaPlayerView;
extern JobaPlayerView D_00189E20;
extern u8 D_00189F00[];
extern u8 D_L14_001BF700[];
typedef struct { u8 pad[0x28]; int price[2]; } PrisonOffer;
extern PrisonOffer D_L14_00291850;
#define OFFER_PRICE (D_L14_001A7C8F ? D_L14_00291850.price[1] : D_L14_00291850.price[0])
/* The dialogue gate is written before each poll and cleared on completion. */
extern volatile int D_L14_001B22E8[] MACRO_ADDR;
extern int D_L14_001A8F00[] MACRO_ADDR;
extern void func_L01_003209F8(u8 *, int, int, float);
extern void func_002A7750(u8 *, int, int);
extern void func_L01_003128C0(char *);
extern s8 *func_L14_00425C08(s8 *);
extern int func_00288AA0(u8 *, int);
extern int func_00288BE8(u8 *);
extern int func_002F5D10(void);
extern int func_L01_003245E0(u8 *, int, float);
extern void func_L00_0030C710(int);
extern void func_L01_00324550(int, int, int);
extern void func_L01_003246D0(int);
extern void func_002A8598(int, int);
extern int func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A7470(u8 *, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00283BE0(float, float);
extern float func_00282E20(void *);
extern void func_002AF1D0(char *, char *, int, int);
extern void func_002AEC48(char *, u8 *, char *, float, float);

void func_L14_00425CB0(u8 *object) {
    float destination[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    int index;
    float rate;
    float yaw, pitch, distance, a, b, heading;
    func_L01_003209F8(object, 0, 0x11D3, 2.5f);
    switch (object[0x20]) {
    case 0:
        *(u8 **)(vars + 0x120) = 0;
        if (D_001A7AF8[7] || D_001A7AF8[0x31] || D_00139768[0x1F] < 0) { func_0029F338(object); return; }
        func_L01_003128C0((char *)object);
        if (D_00139768[0x1F] & 0x40000000) {
            if (func_L14_00425C08((s8 *)object)) func_002A7750(object, 2, -1);
        } else func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_L01_003245E0(object, 10, 2.5f)) {
            func_L01_003246D0((int)object);
            if (func_00288AA0(D_L14_001BF700, 0x7E)) {
                func_00288BE8(D_L14_001BF700);
                func_002A7750(object, 2, -1);
            }
        }
        break;
    case 2:
        D_L14_001B22E8[0] = 1;
        if (D_L14_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 3.14159274f);
            D_L14_001B22E8[0] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (func_L14_00425C08((s8 *)object)) {
                if (object[0x43] != 1) func_002A7470(object, 1, 0, 10);
                if (D_001A79F8[0] < OFFER_PRICE)
                    func_002A7750(object, 3, -1);
                else func_002A7750(object, 4, -1);
            }
        }
        break;
    case 3:
        if (D_001A79F8[0] >= OFFER_PRICE) func_002A7750(object, 4, -1);
        else if (func_L01_003245E0(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x27D5, OFFER_PRICE, -1);
            func_L01_003246D0((int)object);
        }
        break;
    case 4:
        if (D_001A79F8[0] < OFFER_PRICE) {
            func_L00_0030C710(180);
            func_002A7750(object, 3, -1);
        } else if (func_L01_003245E0(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x27D6, OFFER_PRICE, -1);
            func_L01_003246D0((int)object);
            if (D_00138324 & 0x10) {
                D_001A79F8[0] = D_001A79F8[0] - OFFER_PRICE;
                if (func_00288AA0(D_L14_001BF700, 0x7F)) {
                    func_00288BE8(D_L14_001BF700);
                    func_002A7750(object, 5, -1);
                }
            }
        }
        break;
    case 5:
        D_L14_001B22E8[0] = 1;
        if (D_L14_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (*(u8 **)(vars + 0x120) && D_L14_001A8F00[0] == 2) {
            *(u16 *)(*(u8 **)(vars + 0x120) + 0x34) |= 1;
            (*(u8 **)(vars + 0x120))[0x31] = 0;
        }
        if (!func_002F5D10()) {
            D_L14_001B22E8[0] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (object[0x21] != 0xFF) func_002A8598(object[0x21], 1);
            if (*(u8 **)(vars + 0x120)) {
                func_0029F338(*(u8 **)(vars + 0x120));
                *(u8 **)(vars + 0x120) = 0;
            }
            if (!D_001A7AF8[0x31]) {
                D_001A7AF8[0x31] = 1;
                D_001A7AF8[0x69] = 1;
            }
            func_0029B3E0(0, -1);
            *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 3.14159274f);
            if (object[0x43] != 0) func_002A7470(object, 0, 0, 10);
            func_002A7750(object, 6, -1);
        }
        break;
    }
    if (object[0x20] == 1 || object[0x20] == 2 || object[0x20] == 6) {
        if (object[0x43] == 0 && func_00282948(vars + 0x11C)) {
            *(int *)(vars + 0x11C) = func_00283CF0(func_002A7878(1200.0f, 2400.0f));
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            func_002A7470(object, 0, 0, 10);
        }
    }
    rate = 0.02f;
    distance = func_00282E80(object + 0x10, D_00189E20.position);
    if (distance < 8.0f && func_00283C80(*(float *)(object + 0xF8), func_00283248(D_00189E20.aim[0] - *(float *)(object + 0x10), D_00189E20.aim[1] - *(float *)(object + 0x14))) < 1.5707965f) {
        if (func_00282DF0(D_00189E20.velocity) > 0.01f) *(int *)(vars + 0x114) = 120;
        else func_00282948(vars + 0x114);
    } else if (*(int *)(vars + 0x114)) {
        *(int *)(vars + 0x114) = 0;
        qcopy(vars + 0x100, D_00189F00);
    }
    if (func_00282948(vars + 0x118)) {
        *(int *)(vars + 0x118) = func_00283CF0(func_002A7878(180.0f, 300.0f));
        a = func_002A7878(-90.0f, 90.0f);
        heading = func_00283B98(*(float *)(object + 0xF8), a * 0.017453294f);
        b = func_002A7878(0, 30.0f);
        func_002AF000((float *)(vars + 0x100), 6.0f, heading, b * 0.017453294f);
        func_00282CC0((float *)(vars + 0x100), (float *)(vars + 0x100), (float *)(object + 0x10));
    }
    if (*(int *)(vars + 0x114)) {
        qcopy(destination, D_00189F00);
        rate = 0.04f;
    } else qcopy(destination, vars + 0x100);
    qcopy(origin, object + 0x10);
    origin[2] += 2.0f;
    func_00282CF0(difference, destination, origin);
    yaw = func_00283BE0(func_00283248(difference[0], difference[1]), *(float *)(object + 0xF8));
    pitch = -func_00283248(func_00282E20(difference), difference[2]);
    if (yaw > 0.8726647f) yaw = 0.8726647f;
    else if (yaw < -0.8726647f) yaw = -0.8726647f;
    if (pitch > 0.52359885f) pitch = 0.52359885f;
    else if (pitch < -0.017453294f) pitch = -0.017453294f;
    *(float *)(vars + 0x64) = pitch;
    *(float *)(vars + 0x68) = yaw * 0.5f;
    *(float *)(vars + 0xE8) = yaw * 0.3f;
    if (*(u8 **)(vars + 0x120)) func_002AF1D0((char *)object, *(char **)(vars + 0x120), 2, 0);
    if (D_001A7A40) *(float *)(vars + 0x70) = 2.75f;
    for (index = 0; index < 2; index++)
        func_002AEC48((char *)object, vars + index * 0x80, (char *)index, rate, 0.3f);
}
