/* func_L08_004207D0: the radar HUD (levels 08 and 19): three labels, an anchor sprite and one
 * sprite per nearby entity of the anchor's list. Own unit for -g and -frac2-zero-ti-por.
 * label_y/hud_coord are the dead-test HUD helpers (allowed by owner rulings of 7 and 8 November 2026). */
#include "common.h"
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 *D_L08_001A904C MACRO_ADDR, *D_L08_001B29DC MACRO_ADDR;
extern f32 D_L08_001B3244 MACRO_ADDR;
extern f32 D_L08_001B1B84 __attribute__((sda)), D_L08_001B1B88 __attribute__((sda));
extern f32 D_L08_001B1B8C __attribute__((sda)), D_L08_001B1B90 __attribute__((sda));
extern s32 D_L08_001B1B94 __attribute__((sda)), D_L08_001B1B98 __attribute__((sda));
extern f32 D_L08_001B1B9C __attribute__((sda));
extern s32 D_L08_001B1BA0 __attribute__((sda));
extern f32 D_L08_001B1BA4 __attribute__((sda));
extern u32 D_L08_001B1BA8 __attribute__((sda));
extern u16 *D_L08_001FB660[];
extern u8 D_L08_001B9D30[];
extern s32 func_L08_00300090(void), func_L08_003000C0(void);
extern void func_L08_00300100(void);
extern char *func_00336D50(void *, s32);
extern void func_00300A00(char *, u32, f32, f32, f32, f32, f32);
extern u64 func_0027C878(s32);
extern void func_L05_003008C0(f32, f32, f32, f32, s32, s32, s32, s32, u64, u64);
extern f32 func_00282E48(void *, void *);
extern void func_002833F0(void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32), func_002836E8(void *, void *);
extern void func_00283098(void *, void *, void *);
extern s32 func_00283CF0(f32);

extern int D_L08_001B3240;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L08_004207D0(u8 *object)
{
    Vector difference, euler;
    f32 rotation[12], inverse[12];
    u8 *state, *entry, *anchor;
    char *first, *second, *third;
    u16 *cursor, *p;
    f32 y, distance, size, x;
    s32 alpha;
    s64 color;
    u64 texture;
    f32 half;
    func_L08_00300090();
    func_L08_00300100();
    state = *(u8 **)(object + 0x68);
    first = func_00336D50(D_L08_001A904C + 0x8710, 0xBA);
    second = func_00336D50(D_L08_001A904C + 0x8710, 0xBB);
    third = func_00336D50(D_L08_001A904C + 0x8710, 0xBC);
    func_00300A00(first, 0x60442D00, D_L08_001B1B84 + 4.0f, (f32)label_y(first, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    half = 0.5f;
    func_00300A00(second, 0x60241700, D_L08_001B1B84 + 4.0f, (f32)label_y(first, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    func_00300A00(third, 0x55F0C070, D_L08_001B1B84 + 4.0f, (f32)label_y(third, D_L08_001B1B88 + 4.0f, D_L08_001B3244, half, 1), 0.8f, -0.8f, 0.0f);
    y = (f32)label_y(object, D_L08_001B1B88, D_L08_001B3244, 0.5f, 1);
    texture = func_0027C878(D_L08_001B1BA0);
    func_L05_003008C0(D_L08_001B1B84, y, D_L08_001B1B8C, D_L08_001B1B90,
                     0, 0, D_L08_001B1B94, D_L08_001B1B98, 0x80808080UL, texture);
    func_L08_003000C0();
    anchor = *(u8 **)(state + 0x1B0);
    if (!anchor) return;
    cursor = D_L08_001FB660[anchor[0x21]];
    if (!cursor) return;
    p = cursor;
    do {
        entry = D_L08_001B29DC + ((*p & 0x7FFF) << 8);
        if (!entry || entry[0x20] == 0xFE || entry[0x20] == 0xFD || *(s16 *)(entry + 0xAA) == 0x96A) continue;
        distance = func_00282E48(object + 0x10, entry + 0x10);
        if (distance <= D_L08_001B1BA4) {
            y = distance / D_L08_001B1BA4;
            y *= D_L08_001B1B9C;
            euler.q = 0;
            euler.f[2] = 1.5707964f;
            func_002833F0(rotation, &euler);
            func_00282CF0(&difference, entry + 0x10, object + 0x10);
            func_00282F20(&difference, &difference, y);
            func_002836E8(inverse, D_L08_001B9D30);
            func_00283098(&difference, &difference, inverse);
            func_00283098(&difference, &difference, rotation);
            alpha = func_00283CF0((1.0f - distance / D_L08_001B1BA4) * 128.0f);
            size = difference.f[2] * 0.125f + D_L08_001B1B8C * 0.5f;
            if (size > D_L08_001B1B8C + D_L08_001B1B8C) size = D_L08_001B1B8C + D_L08_001B1B8C;
            else if (size < 0.0f) size = 0.0f;
            x = difference.f[0] + D_L08_001B1B84;
            y = (f32)hud_coord(D_L08_001B1B88 - difference.f[1], D_L08_001B3244, 0.5f);
            color = (s32)(D_L08_001B1BA8 | ((u32)alpha << 24));
            texture = func_0027C878(D_L08_001B1BA0);
            func_L05_003008C0(x, y, size, size, 0, 0, D_L08_001B1B94, D_L08_001B1B98, color, texture);
        }
    } while ((s16)*p++ >= 0);
}
