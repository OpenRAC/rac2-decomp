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
extern long long func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* The slot's alpha: 64, or an integer from func_00283CF0 of 128 times its scale while fading. */
static inline int BeamAlpha(EffectSlot *slot)
{
    int alpha;

    if (slot->fading == 1) {
        float scale = slot->scale * 64.0f;
        alpha = func_00283CF0(scale + scale);
    } else {
        alpha = 64;
    }
    return alpha;
}

/* For each of the 10 slots in use: two func_L00_0041C160 calls with colours built from its alpha,
 * then for both parts fills the packet's header, colours and UVs, builds a basis matrix from the
 * point and passes the scaled packet and the matrix to func_00280B90. */
void func_L00_0041BCC8(void *unused)
{
    Quad128 matrix[4], eye, normal;
    EffectSlot *slot;
    Quad128 *point;
    float *scroll;
    int part, alpha;
    int rgb;
    long tag;
    int context;
    int index;

    for (index = 0; index < 10; index++) {
        slot = (EffectSlot *)(index * 0x530 + (int)D_L00_001B1450);
        if (slot->inUse != 1)
            continue;
        alpha = BeamAlpha(slot);
        func_L00_0041C160(unused, slot->point, slot, (alpha << 24) | 0x103080, 0.35f);
        func_L00_0041C160(unused, slot->point, slot, (alpha << 24) | 0xFFFFFF, 0.075f);
        for (part = 0; part < 2; part++) {
            slot->packet[part].header[1] = func_0027C878(23);
            tag = 0xFF9000000260LL;
            slot->packet[part].header[2] = tag;
            slot->packet[part].header[0] = 0;
            rgb = 0x103080;
            slot->packet[part].color[2] = (alpha << 24) + rgb;
            slot->packet[part].color[0] = (alpha << 24) + rgb;
            slot->packet[part].color[3] = rgb;
            slot->packet[part].color[1] = rgb;
            context = part % 2 + 1;
            slot->packet[part].header[3] = ((long)context << 2) | 0x8000000040UL;
            scroll = &slot->scroll[part];
            if (slot->phase[part] != 0) {
                slot->packet[part].uv[0][0] = *scroll;
                slot->packet[part].uv[0][1] = 0.0f;
                slot->packet[part].uv[1][0] = *scroll + 1.0f;
                slot->packet[part].uv[1][1] = 0.0f;
                slot->packet[part].uv[2][0] = *scroll;
                slot->packet[part].uv[2][1] = 1.0f;
                slot->packet[part].uv[3][0] = *scroll + 1.0f;
                slot->packet[part].uv[3][1] = 1.0f;
            } else {
                slot->packet[part].uv[0][0] = *scroll;
                slot->packet[part].uv[0][1] = 1.0f;
                slot->packet[part].uv[1][0] = *scroll + 1.0f;
                slot->packet[part].uv[1][1] = 1.0f;
                slot->packet[part].uv[2][0] = *scroll;
                slot->packet[part].uv[2][1] = 0.0f;
                slot->packet[part].uv[3][0] = *scroll + 1.0f;
                slot->packet[part].uv[3][1] = 0.0f;
            }
            point = &slot->point[part];
            func_00282CF0(&eye, D_L00_001B8DC0, point);
            func_002AFFD8(point, &normal, 1);
            func_00282F20(&matrix[0], &eye, 1.0f);
            func_00282DD8(&matrix[1], &matrix[0], &normal);
            func_00282F20(&matrix[1], &matrix[1], 1.0f);
            func_00282DD8(&matrix[2], &matrix[1], &matrix[0]);
            ((float *)&matrix[3])[0] = ((float *)point)[0];
            ((float *)&matrix[3])[1] = ((float *)point)[1];
            ((float *)&matrix[3])[2] = ((float *)point)[2];
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
            func_00280B90(&slot->packet[part], matrix, 0);
        }
    }
}
