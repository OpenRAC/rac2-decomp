#include "common.h"

/* The one body of L08_003D3928.c whose retail bytes reach 8_tabora's data through $gp:
   a store in ordinary flow, which only the small-data profile (-G8, from this file's
   name) reaches, as a one-instruction form.  The `sda` declaration is what makes cc1
   emit the bare symbol operand and the `.extern` the assembler needs. */

extern s32 D_L08_001B1FA8 __attribute__((sda));

extern s32 func_L08_003289D0(s32);

/* Totals three table lookups into one $-gp word and returns it. */
s32 func_L08_00435938(void)
{
    s32 first = func_L08_003289D0(0x96A);
    s32 second = func_L08_003289D0(0x1002);
    s32 sum = first + second + func_L08_003289D0(0x8C4);

    D_L08_001B1FA8 = sum;
    return sum;
}

typedef int TI128 __attribute__((mode(TI)));

/* The three 0x30-byte target records of L08_003D3928.c: [0] the tracked owner, [1] the
   nearest one seen this frame, [2] last frame's [1]. MACRO_ADDR keeps every field access
   one assembler macro and every address taken one unsplit `la`. */
typedef struct {
    TI128 pos;      /* 0x00 */
    void *owner;    /* 0x10 */
    float dist;     /* 0x14 */
    s32 unk18;      /* 0x18 */
    s32 unk1C;      /* 0x1C */
    s32 valid;      /* 0x20 */
    s32 pad[3];
} L08Target;

extern L08Target D_L08_001B3490[3] MACRO_ADDR;

/* A 0x40-byte pool entry from func_L00_002D70A0; its position vector is at 0x20. */
typedef struct {
    float x0;
    float x4;
    float x8;
    float xC;
    u8 pad10[0x1F - 0x10];
    u8 x1F;
    float pos[4];
    u8 pad30[0x10];
} L08Marker;

/* The resident player state: the vehicle at 0x1830, the movement mode at 0x2294. */
typedef struct {
    u8 pad0[0x1830];
    u8 *vehicle;
    u8 pad1834[0x2294 - 0x1834];
    s32 mode;
} L08Player;

extern L08Player D_00189E20;
extern L08Marker *D_L08_001B0318 __attribute__((sda));
extern s32 D_L08_001B02FC __attribute__((sda));
extern float D_L08_001B0300 __attribute__((sda));
extern float D_L08_001B0304 __attribute__((sda));
extern float D_L08_001B0308 __attribute__((sda));
extern float D_L08_001B0310 __attribute__((sda));
extern float D_L08_001B0314 __attribute__((sda));
extern TI128 D_L08_001B9B00;
extern s32 D_L08_001B258C MACRO_ADDR;

extern void *func_00115484(void *, int, unsigned int);
extern int func_002ACBC8(void *, int);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern L08Marker *func_L00_002D70A0(int);
extern void func_L00_002D7140(void *);

static __inline__ void CopyTarget(L08Target *dst, L08Target *src)
{
    TI128 *d = (TI128 *)dst;
    TI128 *s = (TI128 *)src;

    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
}

/* Per-frame target tracker: a vehicle mode places a marker ahead of the vehicle; on foot
   record [1] replaces record [0] once it has been nearest for long enough, a marker
   follows record [0]'s owner, and [1] is shifted into [2] and cleared for the next frame. */
void func_L08_003D39F0(u8 *object)
{
    float offset[4] __attribute__((aligned(16)));
    u8 *vehicle;
    int *data = *(int **)(object + 0x68);
    int limit;

    switch (object[0x20]) {
    case 0:
        func_00115484(&D_L08_001B3490[0], 0, 48);
        func_00115484(&D_L08_001B3490[1], 0, 48);
        func_00115484(&D_L08_001B3490[2], 0, 48);
        D_L08_001B3490[0].dist = 100000.0f;
        D_L08_001B3490[0].unk18 = 65535;
        D_L08_001B3490[1].dist = 100000.0f;
        D_L08_001B3490[1].unk18 = 65535;
        D_L08_001B3490[2].dist = 100000.0f;
        D_L08_001B3490[2].unk18 = 65535;
        D_L08_001B0318 = 0;
        object[0x20] = 1;
        return;
    case 1:
        break;
    default:
        return;
    }
    if (*data != -1 && func_002ACBC8(&D_L08_001B9B00, *data))
        D_L08_001B258C = 2;
    if (D_00189E20.mode == 0x31 && (vehicle = D_00189E20.vehicle) != 0) {
        func_002AF000(offset, D_L08_001B0300, *(float *)(vehicle + 0xF8), -*(float *)(vehicle + 0xF4) * 0.5f);
        func_00282CC0(&D_L08_001B3490[0].pos, offset, D_00189E20.vehicle + 0x10);
        if (D_L08_001B0318 == 0) {
            D_L08_001B0318 = func_L00_002D70A0(5);
            if (D_L08_001B0318 == 0)
                goto shift;
        }
        if (*(s16 *)(D_00189E20.vehicle + 0xAA) == 0x905) {
            D_L08_001B0318->x0 = D_L08_001B0304;
            D_L08_001B0318->xC = -1.0f;
            D_L08_001B0318->x8 = -1.0f;
        } else {
            D_L08_001B0318->x0 = D_L08_001B0308;
            D_L08_001B0318->xC = D_L08_001B0310;
            D_L08_001B0318->x8 = D_L08_001B0314;
        }
        D_L08_001B0318->x1F = 1;
        func_00282CF0(D_L08_001B0318->pos, &D_L08_001B3490[0].pos, &D_L08_001B9B00);
        goto shift;
    }
    if (D_L08_001B3490[2].owner == D_L08_001B3490[1].owner)
        D_L08_001B3490[1].unk1C = D_L08_001B3490[2].unk1C + 1;
    if (D_L08_001B3490[1].owner != D_L08_001B3490[0].owner && D_L08_001B3490[1].owner != 0) {
        limit = D_L08_001B3490[1].unk1C;
        if (limit < D_L08_001B02FC)
            limit = D_L08_001B02FC;
        D_L08_001B3490[0].unk18++;
        if (D_L08_001B3490[0].unk18 >= limit) {
            CopyTarget(&D_L08_001B3490[0], &D_L08_001B3490[1]);
            D_L08_001B3490[0].valid = 1;
        }
    } else if (D_L08_001B3490[0].valid == 0) {
        CopyTarget(&D_L08_001B3490[0], &D_L08_001B3490[1]);
        D_L08_001B3490[0].valid = 1;
    }
    if (D_L08_001B3490[0].owner != 0) {
        if (D_L08_001B0318 == 0) {
            D_L08_001B0318 = func_L00_002D70A0(5);
            if (D_L08_001B0318 == 0)
                goto shift;
        }
        D_L08_001B0318->x0 = 7.0f;
        D_L08_001B0318->x1F = 1;
        func_00282CF0(D_L08_001B0318->pos, &D_L08_001B3490[0].pos, &D_L08_001B9B00);
    } else if (D_L08_001B0318 != 0) {
        func_L00_002D7140(D_L08_001B0318);
        D_L08_001B0318 = 0;
    }
shift:
    CopyTarget(&D_L08_001B3490[2], &D_L08_001B3490[1]);
    func_00115484(&D_L08_001B3490[1], 0, 48);
    D_L08_001B3490[1].unk18 = 65535;
    D_L08_001B3490[1].dist = 100000.0f;
    D_L08_001B3490[0].valid = 0;
}
