/* functional: high. The near-miss draft (1176/1176 bytes; only two spill slots swapped) with func_0027C878 returning a 64-bit word (unsigned long: retail stores it with sd), func_00280B90 declared as the port's host routine defines it (host/render.c: gaddr, int, int; packet and matrix passed as 32-bit game addresses), and the pass-through first argument named. Level 00's callees mapped through functions.tsv (0x2E67A0 func_0027C878, 0x2EAC30 func_00280B90, 0x2EE138 func_00282CF0, 0x2EE178 func_00282D30, 0x2EE220 func_00282DD8, 0x2EE3D0 func_00282F20, 0x2EF250 func_00283CF0, 0x3251D0 func_002AFFD8); data 0x1B1450 ($gp) and 0x1B8DC0. */
/* func_L00_0041BCC8 (DrawEffectSlots, shared, 27 places): draws the ten 0x530-byte beam effect slots at
 * *0x1B1450. For each slot in use (+0x514 == 1): alpha 64, or round(scale*128) while fading (+0x518 == 1);
 * two glow passes (func_L00_0041C160 colour 0x103080 width 0.35, white 0.075); then each of the two beam
 * packets gets its GS header, colours (alpha on corners 0/2), UVs scrolled by +0x500[part] (flipped by
 * +0x4E0[part]), a camera-facing matrix at point[part] (eye from 0x1B8DC0), corners scaled from the source
 * packet (0.5 while fading, else +0x510), and is drawn through func_00280B90.
 * From the near-miss draft nonmatching/levels/func_L00_0041BCC8.c; its matching notes dropped. */
#include "common.h"

typedef int Quad128 __attribute__((mode(TI)));

/* A 0x90-byte packet: four corners, then their colours, UVs and the GS header. */
typedef struct {
    Quad128 vertex[4];            /* 0x00 */
    unsigned int color[4];        /* 0x40 */
    float uv[4][2];               /* 0x50 */
    long header[4];               /* 0x70 */
} BeamPacket;

/* One 0x530-byte effect slot (see func_L00_0041B840). */
typedef struct {
    Quad128 first, second;        /* 0x00 */
    Quad128 point[2];             /* 0x20 */
    char pad40[0x20];
    BeamPacket source[2];         /* 0x60 */
    char pad180[0x120];
    BeamPacket packet[2];         /* 0x2A0 */
    char pad3C0[0x120];
    int phase[2];                 /* 0x4E0 */
    char pad4E8[0x18];
    float scroll[2];              /* 0x500 */
    char pad508[8];
    float scale;                  /* 0x510 */
    int inUse;                    /* 0x514 */
    int fading;                   /* 0x518 */
    char pad51C[0x14];
} EffectSlot;

extern char *D_L00_001B1450 __attribute__((sda));
extern char D_L00_001B8DC0[];
extern int func_00283CF0(float);
extern void func_L00_0041C160(void *, Quad128 *, EffectSlot *, int, float);
extern unsigned long func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it */

void func_L00_0041BCC8(void *arg)
{
    Quad128 matrix[4], eye, normal;
    EffectSlot *slot;
    int index, part, alpha;

    for (index = 0; index < 10; index++) {
        slot = (EffectSlot *)(D_L00_001B1450 + index * 0x530);
        if (slot->inUse != 1)
            continue;
        if (slot->fading == 1) {
            float scale = slot->scale * 64.0f;
            alpha = func_00283CF0(scale + scale);
        } else {
            alpha = 64;
        }
        func_L00_0041C160(arg, slot->point, slot, (alpha << 24) | 0x103080, 0.35f);
        func_L00_0041C160(arg, slot->point, slot, (alpha << 24) | 0xFFFFFF, 0.075f);
        for (part = 0; part < 2; part++) {
            slot->packet[part].header[1] = func_0027C878(23);
            slot->packet[part].header[2] = 0xFF9000000260LL;
            slot->packet[part].header[0] = 0;
            slot->packet[part].color[2] = (alpha << 24) + 0x103080;
            slot->packet[part].color[0] = (alpha << 24) + 0x103080;
            slot->packet[part].color[3] = 0x103080;
            slot->packet[part].color[1] = 0x103080;
            slot->packet[part].header[3] = ((long)(part % 2 + 1) << 2) | 0x8000000040UL;
            if (slot->phase[part] != 0) {
                slot->packet[part].uv[0][0] = slot->scroll[part];
                slot->packet[part].uv[0][1] = 0.0f;
                slot->packet[part].uv[1][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[1][1] = 0.0f;
                slot->packet[part].uv[2][0] = slot->scroll[part];
                slot->packet[part].uv[2][1] = 1.0f;
                slot->packet[part].uv[3][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[3][1] = 1.0f;
            } else {
                slot->packet[part].uv[0][0] = slot->scroll[part];
                slot->packet[part].uv[0][1] = 1.0f;
                slot->packet[part].uv[1][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[1][1] = 1.0f;
                slot->packet[part].uv[2][0] = slot->scroll[part];
                slot->packet[part].uv[2][1] = 0.0f;
                slot->packet[part].uv[3][0] = slot->scroll[part] + 1.0f;
                slot->packet[part].uv[3][1] = 0.0f;
            }
            func_00282CF0(&eye, D_L00_001B8DC0, &slot->point[part]);
            func_002AFFD8(&slot->point[part], &normal, 1);
            func_00282F20(&matrix[0], &eye, 1.0f);
            func_00282DD8(&matrix[1], &matrix[0], &normal);
            func_00282F20(&matrix[1], &matrix[1], 1.0f);
            func_00282DD8(&matrix[2], &matrix[1], &matrix[0]);
            ((float *)&matrix[3])[0] = ((float *)&slot->point[part])[0];
            ((float *)&matrix[3])[1] = ((float *)&slot->point[part])[1];
            ((float *)&matrix[3])[2] = ((float *)&slot->point[part])[2];
            ((float *)&matrix[3])[3] = 1.0f;
            if (slot->fading == 1) {
                func_00282D30(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], 0.5f);
                func_00282D30(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], 0.5f);
                func_00282D30(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], 0.5f);
                func_00282D30(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], 0.5f);
            } else {
                func_00282D30(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], slot->scale);
                func_00282D30(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], slot->scale);
                func_00282D30(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], slot->scale);
                func_00282D30(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], slot->scale);
            }
            func_00280B90((unsigned int)&slot->packet[part], (int)matrix, 0);
        }
    }
}
