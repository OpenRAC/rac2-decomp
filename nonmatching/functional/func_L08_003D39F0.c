/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high tier, v0919; complete C reconstruction, not linked.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * USA v1.01: 900/912 bytes, 0/3 placements (08, 19, 30).
 * The earlier helper draft revalidated at 920 bytes with a 0x40 frame.
 * This draft recovers the retail 0x30 frame, saved s0/s1, entry parameter
 * load, and all three 48-byte transfers through the record's quadword view.
 * Scalar aliases describe the same measured 48-byte records; they preserve
 * absolute macro accesses while the quadword view retains record addresses.
 * Remaining: candidate base setup is too early; loads move ahead of stores
 * in each transfer; resident base selection, call slots and allocation differ.
 * Whole-record assignment emits ld/sd even with aligned(16). Disabling the
 * first scheduler gives 904 bytes and interleaved copies but worsens the rest.
 * Default split addresses gives 888 bytes. A named resident pointer does not
 * fix allocation. Reopen with an independently evidenced transfer/lifetime
 * model, retaining all 48 bytes and the real record extents.
 * Only USA v1.01 checked this pass; no linked build or match claimed.
 */

#include "common.h"
typedef int TrackQuad __attribute__((mode(TI)));
typedef union { struct { TrackQuad position; u8 *owner; float distance; int ticks; int duration; int initialized; int tail[3]; } v; TrackQuad quad[3]; } TrackRecord;
typedef struct { float f0,f4,f8,f12,f16,f20; u8 f24,f25; short f26; u8 f28,f29,f30,f31; u8 pad32[16]; short f48,f50; int f52,f56,f60; } PoolRecord64;
extern TrackRecord D_L08_001B3490;
extern TrackRecord D_L08_001B3490_scalar __asm__("D_L08_001B3490") MACRO_ADDR;
extern TrackRecord D_L08_001B34C0;
extern TrackRecord D_L08_001B34C0_scalar __asm__("D_L08_001B34C0") MACRO_ADDR;
extern TrackRecord D_L08_001B34F0;
extern TrackRecord D_L08_001B34F0_scalar __asm__("D_L08_001B34F0") MACRO_ADDR;
extern PoolRecord64 *D_L08_001B0318 __attribute__((sda));
extern int D_L08_001B02FC __attribute__((sda));
extern float D_L08_001B0300 __attribute__((sda));
extern float D_L08_001B0304 __attribute__((sda));
extern float D_L08_001B0308 __attribute__((sda));
extern float D_L08_001B0310 __attribute__((sda));
extern float D_L08_001B0314 __attribute__((sda));
typedef struct { u8 pad[0x1830]; u8 *vehicle; u8 pad1834[0xA60]; int mode; } Resident39;
extern Resident39 D_00189E20;
extern TrackQuad D_L08_001B9B00;
extern int D_L08_001B258C NOT_SDA;
extern void *func_00115484(void *dst, int value, unsigned int size);
extern int func_002ACBC8(void *point, int index);
extern void func_002AF000(float *p, float a, float b, float c);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_00282CF0(void *out, void *a, void *b);
extern PoolRecord64 *func_L00_002D70A0(int kind);
extern void func_L00_002D7140(u8 *object);

void func_L08_003D39F0(u8 *object)
{
    float offset[4] __attribute__((aligned(16)));
    u8 *vehicle;
    int *data = *(int **)(object + 0x68);
    int limit;
    TrackRecord *candidate;
    switch (object[0x20]) {
    case 0:
        func_00115484(&D_L08_001B3490_scalar, 0, 48);
        func_00115484(&D_L08_001B34C0_scalar, 0, 48);
        func_00115484(&D_L08_001B34F0_scalar, 0, 48);
        D_L08_001B34F0_scalar.v.ticks = 65535;
        D_L08_001B34F0_scalar.v.distance = 100000.0f;
        D_L08_001B3490_scalar.v.distance = 100000.0f;
        D_L08_001B3490_scalar.v.ticks = 65535;
        D_L08_001B34C0_scalar.v.distance = 100000.0f;
        D_L08_001B34C0_scalar.v.ticks = 65535;
        D_L08_001B0318 = 0;
        object[0x20] = 1;
        return;
    case 1: break;
    default: return;
    }
    if (*data != -1 && func_002ACBC8(&D_L08_001B9B00, *data))
        D_L08_001B258C = 2;
    candidate = &D_L08_001B34C0;
    if (D_00189E20.mode == 0x31 && (vehicle = D_00189E20.vehicle) != 0) {
        func_002AF000(offset, D_L08_001B0300, *(float *)(vehicle + 0xf8), -*(float *)(vehicle + 0xf4) * 0.5f);
        func_00282CC0(&D_L08_001B3490_scalar.v.position, offset, D_00189E20.vehicle + 0x10);
        if (D_L08_001B0318 == 0) {
            D_L08_001B0318 = func_L00_002D70A0(5);
            if (D_L08_001B0318 == 0)
                goto finish;
        }
        vehicle = D_00189E20.vehicle;
        if (*(short *)(vehicle + 0xaa) == 0x905) {
            D_L08_001B0318->f0 = D_L08_001B0304;
            D_L08_001B0318->f12 = -1.0f;
            D_L08_001B0318->f8 = -1.0f;
        } else {
            D_L08_001B0318->f0 = D_L08_001B0308;
            D_L08_001B0318->f12 = D_L08_001B0310;
            D_L08_001B0318->f8 = D_L08_001B0314;
        }
        D_L08_001B0318->f31 = 1;
        func_00282CF0(D_L08_001B0318->pad32, &D_L08_001B3490_scalar.v.position, &D_L08_001B9B00);
        goto finish;
    }
    if (D_L08_001B34F0_scalar.v.owner == D_L08_001B34C0_scalar.v.owner)
        D_L08_001B34C0_scalar.v.duration = D_L08_001B34F0_scalar.v.duration + 1;
    if (D_L08_001B34C0_scalar.v.owner != D_L08_001B3490_scalar.v.owner && D_L08_001B34C0_scalar.v.owner != 0) {
        limit = D_L08_001B34C0_scalar.v.duration;
        if (limit < D_L08_001B02FC)
            limit = D_L08_001B02FC;
        D_L08_001B3490_scalar.v.ticks++;
        if (D_L08_001B3490_scalar.v.ticks >= limit) {
            ((TrackQuad *)&D_L08_001B3490)[0] = candidate->quad[0];
            ((TrackQuad *)&D_L08_001B3490)[1] = candidate->quad[1];
            ((TrackQuad *)&D_L08_001B3490)[2] = candidate->quad[2];
            D_L08_001B3490_scalar.v.initialized = 1;
        }
    } else if (D_L08_001B3490_scalar.v.initialized == 0) {
        ((TrackQuad *)&D_L08_001B3490)[0] = candidate->quad[0];
        ((TrackQuad *)&D_L08_001B3490)[1] = candidate->quad[1];
        ((TrackQuad *)&D_L08_001B3490)[2] = candidate->quad[2];
        D_L08_001B3490_scalar.v.initialized = 1;
    }
    if (D_L08_001B3490_scalar.v.owner != 0) {
        if (D_L08_001B0318 == 0) {
            D_L08_001B0318 = func_L00_002D70A0(5);
            if (D_L08_001B0318 == 0)
                goto finish;
        }
        D_L08_001B0318->f31 = 1;
        D_L08_001B0318->f0 = 7.0f;
        func_00282CF0(D_L08_001B0318->pad32, &D_L08_001B3490_scalar.v.position, &D_L08_001B9B00);
    } else if (D_L08_001B0318 != 0) {
        func_L00_002D7140((u8 *)D_L08_001B0318);
        D_L08_001B0318 = 0;
    }
finish:
    ((TrackQuad *)&D_L08_001B34F0)[0] = candidate->quad[0];
    ((TrackQuad *)&D_L08_001B34F0)[1] = candidate->quad[1];
    ((TrackQuad *)&D_L08_001B34F0)[2] = candidate->quad[2];
    func_00115484(candidate, 0, 48);
    D_L08_001B34C0_scalar.v.ticks = 65535;
    D_L08_001B34C0_scalar.v.distance = 100000.0f;
    D_L08_001B3490_scalar.v.initialized = 0;
}
