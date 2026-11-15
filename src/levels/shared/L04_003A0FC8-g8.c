#include "common.h"

/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/water_pool_and_sand_mouse.c:
 * build_water_render_setup_packet. */

typedef float Vec4[4];
struct DmaTag {
    u32 tag, addr, vif0, vif1;
};
union PacketCursor {
    struct DmaTag *tag;
    u8 *bytes;
};
extern union PacketCursor D_L04_001B2C48 MACRO_ADDR;
extern void func_002833B8(void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002FC410(void *, int);
extern void func_00283788(void *, void *, void *);
extern void func_002FC870(void);
extern char D_L04_001B9680[];
extern int D_L04_001B201C MACRO_ADDR;
extern unsigned short D_0010ED20 NOT_SDA;
extern char D_0010ED30[];
extern char D_L04_001BDB80[];
extern char D_L04_002A78A0[];
extern unsigned D_L04_001AD890 __attribute__((sda));
extern unsigned D_L04_001AD884 __attribute__((sda));
extern unsigned D_L04_001AD888 __attribute__((sda));
extern unsigned D_L04_001AD88C __attribute__((sda));

typedef struct WaterCamera {
    u8 pad000[0x190];
    Vec4 v190;                 /* 0x190 */
    Vec4 v1A0;                 /* 0x1A0 */
    u8 pad1B0[0x60];
    f32 f210;                  /* 0x210 */
    u8 pad214[0x14];
    f32 f228;                  /* 0x228 */
    f32 f22C;                  /* 0x22C */
} WaterCamera;

/* Builds the VU1 setup packet used to render the water. */
void func_L04_003A0FC8(void)
{
    f32 scaled_translation_matrix[4][4];
    struct DmaTag *base;
    u8 *packet_write_cursor;
    WaterCamera *camera;

    set_scale_matrix(scaled_translation_matrix, 1024.0f);
    FastVecScale(scaled_translation_matrix[3], D_L04_001B9680, -1024.0f);
    scaled_translation_matrix[3][3] = 1.0f;
    if (D_L04_001B201C != 8) {
        VU1_addDataRef(D_0010ED30, D_0010ED20);
        D_L04_001B201C = 8;
    }
    D_L04_001B2C48.tag->tag = 0x10000000;
    D_L04_001B2C48.tag->addr = 0;
    D_L04_001B2C48.tag->vif0 = 0x11000000;
    D_L04_001B2C48.tag->vif1 = 0x1000404;
    base = D_L04_001B2C48.tag;
    base[1].tag = 0;
    base[1].addr = 0;
    base[1].vif0 = 0;
    base[1].vif1 = 0x6C0C43A4;
    multiply_matrix(base + 2, D_L04_001B9680 - 0x100, scaled_translation_matrix);
    multiply_matrix(base + 6, D_L04_001B9680 - 0x80, scaled_translation_matrix);
    base[10].tag = 0x8000;
    base[10].addr = 0x303EC000;
    base[10].vif0 = 0x412;
    camera = (WaterCamera *)D_L04_001BDB80;
    *(f32 *)&base[10].vif1 = camera->f210;
    packet_write_cursor = (u8 *)(base + 11);
    qcopy(packet_write_cursor, &camera->v190);
    packet_write_cursor = (u8 *)(base + 12);
    qcopy(packet_write_cursor, &camera->v1A0);
    *(f32 *)&base[13].tag = camera->f22C;
    *(f32 *)&base[13].addr = camera->f228;
    base[13].vif0 = 0;
    base[13].vif1 = 0;
    base[14].addr = 0x20001D2;
    base[14].vif0 = 0x15000000;
    base[14].tag = 0x3000000;
    base[14].vif1 = 0;
    packet_write_cursor = (u8 *)(base + 15);
    D_L04_001B2C48.tag->tag |= ((packet_write_cursor - (u8 *)D_L04_001B2C48.tag) >> 4) - 1;
    D_L04_001B2C48.bytes = packet_write_cursor;
    AppendFixedDmaBlockTags();
    D_L04_001B2C48.tag->tag = 0x30000007;
    D_L04_001B2C48.tag->addr = (u32)D_L04_002A78A0;
    D_L04_001B2C48.tag->vif0 = 0;
    D_L04_001B2C48.tag->vif1 = 0x50000007;
    D_L04_001AD884 = 0xFFFFFFFFu;
    D_L04_001AD888 = 0xFFFFFFFFu;
    D_L04_001AD88C = 0xFFFFFFFFu;
    D_L04_001AD890 = 0xFFFFFFFFu;
    D_L04_001B2C48.tag++;
}
