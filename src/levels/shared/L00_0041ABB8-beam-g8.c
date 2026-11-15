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

extern char *g_lava_gun_beam_slots __attribute__((sda));
extern char g_camera_l00_position[];
extern int FloatToInt(float);
extern void gfx_draw_directional_glow_sprite(void *, Quad128 *, EffectSlot *, int, float);
extern long long GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

/* The slot's alpha: 64, or an integer from func_00283CF0 of 128 times its scale while fading. */
static inline int BeamAlpha(EffectSlot *slot)
{
    int alpha;

    if (slot->fading == 1) {
        float scale = slot->scale * 64.0f;
        alpha = FloatToInt(scale + scale);
    } else {
        alpha = 64;
    }
    return alpha;
}

/* For each of the 10 slots in use: two func_L00_0041C160 calls with colours built from its alpha,
 * then for both parts fills the packet's header, colours and UVs, builds a basis matrix from the
 * point and passes the scaled packet and the matrix to func_00280B90. */
void DrawEffectSlots(void *unused)
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
        slot = (EffectSlot *)(index * 0x530 + (int)g_lava_gun_beam_slots);
        if (slot->inUse != 1)
            continue;
        alpha = BeamAlpha(slot);
        gfx_draw_directional_glow_sprite(unused, slot->point, slot, (alpha << 24) | 0x103080, 0.35f);
        gfx_draw_directional_glow_sprite(unused, slot->point, slot, (alpha << 24) | 0xFFFFFF, 0.075f);
        for (part = 0; part < 2; part++) {
            slot->packet[part].header[1] = GetEffectTextureDescriptor(23);
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
            FastVecSub(&eye, g_camera_l00_position, point);
            cam_compute_view_direction(point, &normal, 1);
            vec_scale_to_length(&matrix[0], &eye, 1.0f);
            FastVecCross(&matrix[1], &matrix[0], &normal);
            vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
            FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
            ((float *)&matrix[3])[0] = ((float *)point)[0];
            ((float *)&matrix[3])[1] = ((float *)point)[1];
            ((float *)&matrix[3])[2] = ((float *)point)[2];
            ((float *)&matrix[3])[3] = 1.0f;
            if (slot->fading == 1) {
                FastVecScale(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], 0.5f);
                FastVecScale(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], 0.5f);
                FastVecScale(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], 0.5f);
                FastVecScale(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], 0.5f);
            } else {
                FastVecScale(&slot->packet[part].vertex[0], &slot->source[part].vertex[0], slot->scale);
                FastVecScale(&slot->packet[part].vertex[1], &slot->source[part].vertex[1], slot->scale);
                FastVecScale(&slot->packet[part].vertex[2], &slot->source[part].vertex[2], slot->scale);
                FastVecScale(&slot->packet[part].vertex[3], &slot->source[part].vertex[3], slot->scale);
            }
            draw_world_quad(&slot->packet[part], matrix, 0);
        }
    }
}
