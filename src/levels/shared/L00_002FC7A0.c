#include "common.h"

typedef u32 u128_04340 __attribute__((mode(TI), aligned(16)));
typedef struct ResidentRenderTextureDefinition_04340 {
    s32 unk0; /* unused here; a word, so the record is 4-byte aligned */
    s16 width;
    s16 height;
    s16 draw_control_count;
    s16 clut_block_offset; /* 0x0A: TEX0.CBP (bit 37) after adding the base */
    s16 mip_block_offset_0;
    s16 mip_block_offset_1;
} ResidentRenderTextureDefinition_04340;
typedef union MaterialMap_04340 {
    u128_04340 q;
    u8 b[16];
} MaterialMap_04340;
typedef struct {
    s16 width;
    s16 height;
    s16 draw_control_count;
    s16 texture_block_offset;
    s16 palette_block_offset;
    s16 mip_block_offset_0;
    s16 mip_block_offset_1;
    s16 mip_block_offset_2;
} ShrubMipTextureDefinition_04340;
typedef struct {
    s32 draw_high;
    s32 draw_shift;
    u8 pad8[8];
    s32 material_base;
    s32 material_shift;
    u8 pad18[8];
    s32 material_index;
    u8 pad24[0x1C];
} ShrubRenderPacket_04340;
typedef struct {
    u8 pad0[0x10];
    union {
        u64 d;
        s32 w[2];
    } tex1;
    u64 payload18;
    union {
        u64 d;
        s32 w[2];
    } tex0;
    u64 payload28;
    u64 miptbp1;
    u64 payload38;
} ShrubMipPacket_04340;
typedef struct {
    s32 count;
    s32 prefix_record_count;
} ShrubRenderGroupHeader_04340;
typedef struct {
    u8 pad0[0x10];
    ShrubRenderGroupHeader_04340 group_header;
} ShrubRenderGroup_04340;
typedef struct {
    ShrubRenderGroup_04340 *group;
    s32 pad4;
} ShrubRenderGroupReference_04340;
typedef struct {
    u8 pad0[0x10];
    f32 scale;
    u8 pad14[2];
    u16 instance_count;
    void *first_instance;
    ShrubMipPacket_04340 *mip_packet;
    u8 pad20[6];
    u16 class_slot;
    s16 group_count;
    u8 pad2A[2];
    s32 packed_geometry;
    u8 pad30[0x10];
    ShrubRenderGroupReference_04340 groups[1];
} ShrubRenderClass_04340;
extern ShrubRenderClass_04340 *D_L00_0021EA20[64];
extern s16 D_L00_0021EB20[64];
extern u8 D_L00_0021EBA0[0x400];
extern s32 D_L00_002203A0[64];
extern MaterialMap_04340 D_L00_002209A0[64];
extern s32 D_L00_001B23F0 __attribute__((sda));
/* Keep the absolute allocation-base loads in their measured form in this G0 unit. */
extern s32 D_001A72F4 __attribute__((sda));
extern u64 D_L00_001C91C0[0x30];
extern s32 func_00283CF0(f32);
extern s32 func_00282A18(s32);
extern char D_L00_001A95A0[];
extern double func_001234F0(float);
extern void func_0026FEB8(const char *, ...);

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef unsigned int Rac2Native_3e18d05650488ad4_FallbackU32;

typedef struct Slot0820eb11 {
    short          f00;    /* +0x00 */
    short          f02;    /* +0x02 */
    unsigned char  f04;    /* +0x04 */
    char           pad05[7];
    unsigned char *f0C;    /* +0x0C */
    int            f10;    /* +0x10 */
    int            f14;    /* +0x14 */
    int            f18;    /* +0x18 */
    int            f1C;    /* +0x1C */
    char           pad20[32];
} Slot0820eb11;

typedef struct Mid {
    char           pad00[0x1C];
    char          *f1C;    /* +0x1C */
} Mid;

typedef struct Ctx {
    char           pad00[0x24];
    Mid           *f24;    /* +0x24 */
    char           pad28[0x28];
    int            f50;    /* +0x50 */
} Ctx;

typedef struct LvlSlotNode {
    char                 pad00[0x1C];
    struct LvlSlotNode  *next;   /* +0x1C */
} LvlSlotNode;

typedef struct LvlSlotCtx {
    char          pad00[0x50];
    LvlSlotNode  *head;          /* +0x50 */
} LvlSlotCtx;

extern void func_002B7B18(int value, char *target);

extern void func_002B7CE0(int value);

extern int D_L00_001BCAC0[];

extern int D_0014B540[];

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424;

extern int D_001A7420_1;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_1;

extern int D_001A7420_2;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_2;

extern int D_001A7420_3;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_3;

extern int D_001A7420_4;

extern int D_L00_001A904C_1 __attribute__((sda));

extern void func_0034CE28(int value, int argument);

extern void func_L00_004427C8(int value, int argument);

extern void func_L00_004427D0(int value, int argument);

extern int D_L00_001A904C_2 __attribute__((sda));

extern void func_L00_00443DF8(int);

extern void func_L00_00443E18(int);

extern void func_0034E478(int);

extern void func_0034E4F8(int);

extern int func_003418C0(int a, int b);

extern void func_0034CE98(int value, int argument);

extern int D_L00_001A904C_7 __attribute__((sda));

extern int func_003387A0_1(int a, int b, int c);

extern int func_00338040_1(int a, int b, int c);

extern void func_L00_0042D9D0(int);

extern unsigned char *D_L05_001B2520 __attribute__((sda));

extern unsigned char *D_L05_001B2524 __attribute__((sda));

extern unsigned int D_L05_001B2048 __attribute__((sda));

extern unsigned int D_L05_001B2440 __attribute__((sda));

extern Slot0820eb11 D_L03_001D23C0[6];

extern unsigned char D_L03_001CA5C0[];

extern void func_00283658_1(char *a, char *b);

extern void func_002A3F10_3(char *a, int b, int c, char *d);

extern void func_00283788_5(char *a, char *b, char *c);

extern void func_00282D30_21(char *a, char *b, float c);

extern void func_00282CC0_24(char *a, char *b, char *c);

extern void func_00291788(unsigned long long);

extern void func_00291640(unsigned long long);

extern void func_002F0D00(void *, void *, int);

extern unsigned char D_L00_001C7040[] __attribute__((nosda));

extern int r1_D_0015EE84_m __asm__("r1_D_0015EE84") MACRO_ADDR;

extern int r1_D_L00_001C47B8[];

extern int r1_D_L00_001792B8[];

extern void func_00348EC0(int);

extern void func_003478F0(int);

extern void func_003465D0(int);

extern void func_00339590(int);

extern void func_0033A3E0(int);

extern void func_0033B910(int);

extern void func_0033F030(int);

extern void func_00345358(int);

extern void func_00341C20(int);

extern void func_003438E8(int);

extern void func_L00_00433F50(int);

extern void func_0033D970(int);

extern void func_0033C738(int);

extern void func_0033CC20(int);

extern void func_0033D638(int);

extern void func_0033C028(int);

extern void func_0033C378(int);

extern int func_0033C590(int, int);

extern int func_L00_00432448(int, int);

extern int func_L00_00432ED0(int, int);

extern int func_0033BE98(int, int);

extern int func_0033C2D8(int, int);

extern int func_0033E3A0(int, int);

extern int func_0033D028(int, int);

extern int func_L00_00433560(int, int);

extern int func_003424C0(int, int);

extern int func_00341EE8(int, int);

extern int func_0033FB98(int, int);

extern int func_003398A8(int, int);

extern int func_00339F28(int, int);

extern int func_0033B540(int, int);

extern int func_0033EA60(int, int);

extern int func_00344478(int, int);

extern int func_00343798(int, int);

extern int func_0033E5C0(int, int);

extern int func_L00_00433198(int, int);

extern void func_00282A60(char *, int, int);

/* Measured partial layouts; original type and game roles are unknown. */

/* RAC2 family 0820eb1123250c0b - 192 bytes, 2 placements.
 * Slot0820eb11 allocator: find the first free of six 64-byte slots, fill it in and
 * link it at the head of the context's list.
 */

                    /* 64 bytes */

void func_L00_002FC7A0(void)
{
}


/* func_L00_002FC980 is defined in its own unit. */


void func_L00_002FD308(unsigned long long argument)
{
    func_00291788(argument);
    func_00291640(argument);
}

/* walks the eight thirty-two-byte entries: for the ones with both flags set it
   hands the two halfword offsets of the entry to the shared routine and clears
   them */
void func_L00_002FD400(void)
{
    unsigned char *entry = D_L00_001C7040;
    int i;
    int base;
    short first;

    for (i = 0; i < 8; i++) {
        if (*(int *)(entry + 0x10) != 0 && *(int *)(entry + 0xC) != 0) {
            base = *(int *)(entry + 0xC);
            first = *(short *)(entry + 0x8);
            func_002F0D00((void *)(base + (first << 1)),
                          (void *)(base + (first << 1) + (*(short *)(entry + 0xA) << 1)), i);
            *(short *)(entry + 0x8) = 0;
            *(short *)(entry + 0xA) = 0;
        }
        entry += 0x30;
    }
}

/* func_L00_002FD480 is matched in its own unit, src/levels/shared/L00_002FD480-g8-qcopy.c (-O2 -G8 -ffunction-sections -frac2-qcopy). */


INCLUDE_ASM("asm/levels", func_L00_002FE268);


INCLUDE_ASM("asm/levels", func_L00_002FF6A8);

/* Registers the class, relocates its streams, and builds its GS texture packets.
 * Adapted from RAC1 src/game/loaders.c, register_shrub_render_class, which
 * credits Lombyte's GPL-3.0 src/rendering/register_shrub_render_class.c
 * (RAC1 US 0x203B08).
 */
void func_L00_002FFAB8(ShrubRenderClass_04340 *render_class, ResidentRenderTextureDefinition_04340 *textures,
                   u128_04340 *material_map, ShrubMipTextureDefinition_04340 *mip_texture, s32 class_id) {
    s32 group_index;
    s32 index;
    s32 fixed_threshold;
    MaterialMap_04340 *slot_materials;
    ShrubMipPacket_04340 *packed_mip_packet;
    ShrubMipPacket_04340 *mip_packet;
    ShrubRenderGroupHeader_04340 *group_header;
    ShrubRenderPacket_04340 *packet;

    D_L00_0021EBA0[class_id] = D_L00_001B23F0;
    D_L00_0021EB20[D_L00_001B23F0] = class_id;
    D_L00_0021EA20[D_L00_001B23F0] = render_class;
    render_class->class_slot = D_L00_001B23F0;
    fixed_threshold = func_00283CF0(render_class->scale * 1024.0f);
    D_L00_002203A0[D_L00_001B23F0] = fixed_threshold;
    D_L00_001B23F0++;
    render_class->first_instance = 0;
    render_class->instance_count = 0;
    if (render_class->packed_geometry != 0) {
        render_class->packed_geometry += (s32)render_class;
    }
    for (group_index = 0; group_index < render_class->group_count; group_index++) {
        render_class->groups[group_index].group =
            (ShrubRenderGroup_04340 *)(((s32)render_class->groups[group_index].group) + ((s32)render_class));
    }

    packed_mip_packet = render_class->mip_packet;
    if (packed_mip_packet != 0) {
        s32 material_base;
        s32 material_shift;

        mip_packet = (ShrubMipPacket_04340 *)((s32)packed_mip_packet + (s32)render_class);
        render_class->mip_packet = mip_packet;
        material_base = mip_packet->tex1.w[0];
        material_shift = mip_packet->tex1.w[1];
        if (mip_texture != 0) {
            s32 mip_width_units[4];
            s32 width_log2;
            s32 height_log2;
            s32 gs_block_base;
            u64 draw_word;
            s32 width;
            s32 level;
            s32 draw_control_count;
            s32 palette_block;
            s32 texture_block;
            s32 mip_block_0;
            s32 mip_block_1;
            s32 mip_block_2;

            width = mip_texture->width;
            for (level = 0; level < 4; level++) {
                mip_width_units[level] = width >> (level + 6);
                if (mip_width_units[level] <= 0) {
                    mip_width_units[level] = 1;
                }
            }

            width_log2 = func_00282A18(mip_texture->width);
            height_log2 = func_00282A18(mip_texture->height);
            draw_control_count = mip_texture->draw_control_count;
            texture_block = mip_texture->texture_block_offset;
            gs_block_base = D_001A72F4 >> 8;
            palette_block = mip_texture->palette_block_offset + gs_block_base;
            mip_block_0 = mip_texture->mip_block_offset_0 + gs_block_base;
            mip_block_1 = mip_texture->mip_block_offset_1 + gs_block_base;
            mip_block_2 = mip_texture->mip_block_offset_2 + gs_block_base;
            mip_packet->tex1.d = (s64)(((u64)(draw_control_count - 1) << 2) | ((u64)1 << 5) | ((u64)material_shift << 6)) | ((s64)material_base << 32);
            mip_packet->tex0.d = (s64)((u64)((s64)palette_block | ((s64)mip_width_units[0] << 14) | ((s64)0x13 << 20) | ((s64)width_log2 << 26)) | ((u64)height_log2 << 30) | ((u64)1 << 34) | ((u64)(texture_block + gs_block_base) << 37)) | ((s64)4 << 61);
            draw_word = (u64)mip_block_0 | ((u64)mip_width_units[1] << 14);
            draw_word |= (u64)mip_block_1 << 20;
            draw_word |= (u64)mip_width_units[2] << 34;
            draw_word |= (u64)mip_block_2 << 40;
            draw_word |= (u64)mip_width_units[3] << 54;
            mip_packet->miptbp1 = draw_word;
        } else {
            s32 template_index;
            s32 template_slot;
            u64 template_tex0;
            u64 template_tex1;
            u64 template_mip;
            u64 draw_bits;
            u64 template_draw_word;

            for (template_index = 0; D_L00_001C91C0[(template_index + 1) * 3] != 0; template_index++) {
            }
            template_tex0 = D_L00_001C91C0[template_index * 3];
            template_slot = template_index * 3;
            template_tex1 = D_L00_001C91C0[template_slot + 1];
            template_mip = D_L00_001C91C0[template_slot + 2];
            draw_bits = ((u64)material_shift << 6) | 0x20;
            template_draw_word = (template_tex1 & 0x1C) | draw_bits | ((u64)material_base << 32);
            mip_packet->tex0.d = template_tex0;
            mip_packet->miptbp1 = template_mip;
            mip_packet->tex1.d = template_draw_word;
        }
    }
    slot_materials = &D_L00_002209A0[D_L00_0021EBA0[class_id]];
    qcopy(slot_materials, material_map);
    for (group_index = 0; group_index < render_class->group_count; group_index++) {
        group_header = &render_class->groups[group_index].group->group_header;
        packet = (ShrubRenderPacket_04340 *)((((u8 *)group_header) + (group_header->prefix_record_count * 16)) + 0x10);
        for (index = 0; index < group_header->count; index++) {
            s32 material_index;
            s32 material_base;
            s32 draw_shift;
            s32 draw_high;
            s32 material_shift;

            material_index = slot_materials->b[packet->material_index];
            draw_high = packet->draw_high;
            draw_shift = packet->draw_shift;
            material_base = packet->material_base;
            material_shift = packet->material_shift;
            if (textures != 0) {
                ResidentRenderTextureDefinition_04340 *texture;
                s32 width_bits;
                s32 width_units_64;
                s32 width_units_128;
                s32 width_log2;
                s32 height_log2;
                s32 gs_block_base;
                s32 mip_block_1;
                s32 mip_block_0;
                s32 draw_control_count;
                u64 tex0_word;
                u64 tex1_word;
                u64 mip_word;
                u64 clamp_word;

                texture = &textures[material_index];
                width_bits = (u16)texture->width << 16;
                width_units_64 = width_bits >> 22;
                width_units_128 = width_bits >> 23;
                if (width_units_64 <= 0) {
                    width_units_64 = 1;
                }
                if (width_units_128 <= 0) {
                    width_units_128 = 1;
                }
                width_log2 = func_00282A18(width_bits >> 16);
                height_log2 = func_00282A18(texture->height);
                gs_block_base = D_001A72F4 >> 8;
                draw_control_count = texture->draw_control_count;
                width_bits = texture->clut_block_offset + gs_block_base;
                mip_block_0 = texture->mip_block_offset_0 + gs_block_base;
                mip_block_1 = texture->mip_block_offset_1 + gs_block_base;
                tex1_word = (s64)(((u64)(draw_control_count - 1) << 2) | ((u64)1 << 5) | ((u64)draw_shift << 6)) | ((s64)draw_high << 32);
                clamp_word = (u64)material_base | ((u64)material_shift << 2) | ((u64)material_index << 24);
                mip_word = (s64)(((u64)width_units_128 << 14) | ((u64)mip_block_0 << 20) | ((u64)1 << 34) | ((u64)mip_block_1 << 40)) | ((s64)1 << 54);
                tex0_word = (s64)((u64)(((s64)width_units_64 << 14) | ((s64)0x13 << 20) | ((s64)width_log2 << 26)) | ((u64)height_log2 << 30) | ((u64)1 << 34) | ((u64)width_bits << 37)) | ((s64)4 << 61);
                *(u64 *)&packet->draw_high = tex1_word;
                *(u64 *)&packet->material_base = clamp_word;
                *(u64 *)&packet->material_index = mip_word;
                *(u64 *)((u8 *)packet + 0x30) = tex0_word;
            } else {
                s32 template_index;
                u64 template_tex0;
                u64 template_tex1;
                u64 template_mip;
                u64 draw_bits;
                u64 template_draw_word;
                u64 template_clamp_word;

                template_tex0 = D_L00_001C91C0[material_index * 3];
                template_index = material_index * 3;
                template_tex1 = D_L00_001C91C0[template_index + 1];
                template_mip = D_L00_001C91C0[template_index + 2];
                draw_bits = ((u64)draw_shift << 6) | 0x20;
                template_draw_word = (template_tex1 & 0x1C) | draw_bits | ((u64)draw_high << 32);
                template_clamp_word = (u64)material_base | ((u64)material_shift << 2) | ((u64)material_index << 24);
                *(u64 *)&packet->draw_high = template_draw_word;
                *(u64 *)&packet->material_base = template_clamp_word;
                *(u64 *)&packet->material_index = template_mip;
                *(u64 *)((u8 *)packet + 0x30) = template_tex0;
            }
            packet++;
        }
    }
}


/* func_L00_00300090 is defined in L00_002FC7A0-00300090-g8.c (-G8 small data). */

INCLUDE_ASM("asm/levels", func_L00_00300378);

/* Debug listing of moby class sizes: takes the 32-byte class records with a nonzero
   data offset as (class id, offset) pairs, turns each offset into the kilobytes up to
   the next one (the last up to end), sorts them largest first and prints each with
   "moby %d:      %.1fK\n". */
void func_L00_00300438(int *records, int count, int end)
{
    struct { float id, weight; } values[512];
    int n = 0;
    int sorted;
    int i;

    for (i = 0; i < count; i++) {
        if (records[i * 8] != 0) {
            values[n].id = records[i * 8 + 1];
            values[n].weight = records[i * 8];
            n++;
        }
    }
    {
        int k;
        for (k = 0; k < n - 1; k++)
            values[k].weight = (values[k + 1].weight - values[k].weight) / 1024.0f;
    }
    values[n - 1].weight = ((float)end - values[n - 1].weight) / 1024.0f;
    do {
        int k;
        sorted = 1;
        for (k = 0; k < n - 1; k++) {
            if (values[k].weight < values[k + 1].weight) {
                float id = values[k].id, weight = values[k].weight;
                values[k].id = values[k + 1].id;
                values[k].weight = values[k + 1].weight;
                values[k + 1].id = id;
                values[k + 1].weight = weight;
                sorted = 0;
            }
        }
    } while (!sorted);
    {
        int j;
        for (j = 0; j < n; j++)
            func_0026FEB8(D_L00_001A95A0, func_00283CF0(values[j].id), func_001234F0(values[j].weight));
    }
}

void func_L00_00300610(void)
{
}

INCLUDE_ASM("asm/levels", func_L00_00300618);

/* func_L00_003032F0 is matched in L00_003032F0.c (built with -fno-gcse). */

extern unsigned char D_L00_001C9340[];

extern int func_00283D80(void *, void *, void *);

/* Walks the level's sixteen-byte table entries downwards and returns the one-based
   index of the first entry the shared test accepts, zero when none does. */
int func_L00_00303388(unsigned char *object)
{
    unsigned char *data = D_L00_001C9340;
    int i = *(int *)(data + 0xC) - 1;

    if (i >= 0) {
        unsigned char *table = data + 0x20;
        unsigned char *p = table + (i << 4);
        unsigned char *q = table + ((i << 4) + 0x20);

        do {
            if (func_00283D80(object, p, q) != 0)
                return i + 1;
            q -= 0x10;
            p -= 0x10;
            i--;
        } while (i >= 0);
    }
    return 0;
}

/* func_L00_00303418 lives in L00_00303418-sdata.c. */

/* func_L00_00303530 is defined in its own unit. */

INCLUDE_ASM("asm/levels", func_L00_00303990);

/* Reads a record count from a per-level data root, indexes a fixed 332-byte-stride table with it, and when the int after position index is greater than the one at position index calls two helpers with the entry value added to a per-level base; returns 1. */
int func_L00_003046D0(int index)
{
    int j = index + 1;
    int *d = D_L00_001BCAC0;
    int *b = D_0014B540;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        func_002B7B18(hold, (char *)(cur + b[6341]));
        func_002B7CE0(0);
    }
    return 1;
}

/* func_L00_00304AE8 is defined in L00_002FC7A0-g8.c (-G8 small data). */


INCLUDE_ASM("asm/levels", func_L00_003080D0);


extern int r1_func_L00_0024A798(int);
extern struct { int a, b, c; char *p; } r1_D_L07_001842F0;


/* rac1-decomp src/overlays/l07_umbris/menu_cache_entry.c: func_L00_00308408 */
/* Clears each set bit in a rectangle of a per-row bit grid, notifying for each. */
void func_L00_00308408(int x, int y0, int w, int h) {
    int y = y0;
    for (; y < y0 + h; y++) {
        int rowbase = (y >> 5) << 4;
        int i;
        for (i = x; i < x + w; i++) {
            unsigned char *p = (unsigned char *)r1_D_L07_001842F0.p + (y << 6) + i / 8;
            if (*p != 0) {
                int bit = 1 << (i & 7);
                if (*p & bit) {
                    r1_func_L00_0024A798((i >> 5) + rowbase);
                    *p = *p & ~bit;
                }
            }
        }
    }
}

/* func_L00_00308538 is defined in its own unit. */

INCLUDE_ASM("asm/levels", func_L00_00308700);

/* rac1-decomp src/overlays/shared/menu_00249720.c: func_L00_0024B1B0 */
/* stores a value into a table slot chosen by the current index */
void func_L00_00309140(int a, int b) {
    int i = r1_D_0015EE84_m;
    if (i < 19) {
        b += r1_D_L00_001C47B8[i];
        r1_D_L00_001792B8[b] = a;
    }
}

void func_L00_00309368(void)
{
}

INCLUDE_ASM("asm/levels", func_L00_00309DB0);

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void func_L00_0030C710(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_0034CE28(value + 0x376C8, argument);
}

void func_L00_0030C748(int a0, int a1)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_0034CAE8(value + 0x376C8, a0, a1);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void func_L00_0030C788(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_L00_004427C8(value + 0x376C8, argument);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void func_L00_0030C7C0(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_L00_004427D0(value + 0x376C8, argument);
}

void func_L00_0030C7F8(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_0034B000(value + 0x37EB0, argument);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030C930(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_L00_00443DF8(value + 0x36F28);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030CF60(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_L00_00443E18(value + 0x36F28);
}

void func_L00_0030D1A8(void)
{
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030D1B0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0034E478(value + 0x36F28);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030D1E0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0034E4F8(value + 0x36F28);
}

/* The wrappers below dispatch to a handler the object table names: the object's base word lives
 * in a shared global, the handler for it at a fixed byte offset from that base. Same family as
 * the one in src/game/0029BCC8.c, which reads D_001A8CFC instead. */

/* The value-returning half of the same family: the handler is called with the object base,
 * the fixed byte offset added and the caller's argument, and its result is returned. */

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D210(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00348EC0(value + 0x39140);
}

int func_L00_0030D240(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_003489E8(value + 0x39140, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D280(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_003478F0(value + 0x39590);
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D2B0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_003465D0(value + 0x39A98);
}

int func_L00_0030D2E0(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_00346C60(value + 0x39590, argument);
    return 0;
}

int func_L00_0030D368(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_00339320(value + 0x3B1F0, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D3A8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00339590(value + 0x3B1F0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D3D8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_00339F28(v + 0x3ADE8, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D418(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033A3E0(value + 0x3ADE8);
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D448(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033B910(value + 0x3B490);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D478(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_0033B540(v + 0x3B490, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D4B8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033F030(value + 0x3B7C0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D4E8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_0033EA60(v + 0x3B7C0, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D528(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00345358(value + 0x39F38);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D558(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_00344478(v + 0x39F38, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D598(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00341C20(value + 0x3BE08);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D5C8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_003418C0(v + 0x3BE08, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D608(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00341C20(value + 0x3BE08);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D638(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_003418C0(v + 0x3BE08, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D678(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_003438E8(value + 0x3C108);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D6A8(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_00343798(v + 0x3C108, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D6E8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_L00_00433F50(value + 0x3C440);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D718(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_0033E5C0(v + 0x3C440, a0);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D758(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D970(value + 0x3CDB0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int func_L00_0030D788(int a0)
{
    int v = D_L00_001A904C_1;

    if (v != 0) {
        return func_L00_00433198(v + 0x3CDB0, a0);
    }
    return 0;
}

/* Reads a bound global word; when it is non-zero it calls the object's handler with that value
 * plus a fixed base offset as the first argument and the function's own argument as the second,
 * returning the handler's result, otherwise returns 0. */
int func_L00_0030D7C8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033C590(value + 0x3D060, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D808(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C738(value + 0x3D060);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030D838(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_L00_00432448(value + 0x3D310, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D878(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033CC20(value + 0x3D310);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030D8A8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_L00_00432ED0(value + 0x3D900, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D8E8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D638(value + 0x3D900);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030D918(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033BE98(value + 0x3DBB0, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D958(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C028(value + 0x3DBB0);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030D988(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033C2D8(value + 0x3DE60, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_L00_0030D9C8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033C378(value + 0x3DE60);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030D9F8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033E3A0(value + 0x3EDB8, argument);
    return 0;
}

void func_L00_0030DA38(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033E428(value + 0x3EDB8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030DA68(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033D028(value + 0x3D5C0, argument);
    return 0;
}

void func_L00_0030DAA8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033D2C0(value + 0x3D5C0);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030DAD8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_L00_00433560(value + 0x3E5A8, argument);
    return 0;
}

void func_L00_0030DB18(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033DCC8(value + 0x3E5A8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030DB48(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_003424C0(value + 0x3E1D8, argument);
    return 0;
}

void func_L00_0030DB88(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00342758(value + 0x3E1D8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030DBB8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_00341EE8(value + 0x3E430, argument);
    return 0;
}

void func_L00_0030DBF8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00341F38(value + 0x3E430);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void func_L00_0030DC80(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        func_0034CE98(value + 0x376C8, argument);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030DCB8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033FB98(value + 0x3A388, argument);
    return 0;
}

void func_L00_0030DCF8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00340250(value + 0x3A388);
}

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int func_L00_0030DD70(int a0, int a1)
{
    int v = D_L00_001A904C_7;

    if (v == 0) return a0;
    return func_003387A0_1(v + 0x36F28, a0, a1);
}

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int func_L00_0030DDB0(int a0, int a1)
{
    int v = D_L00_001A904C_7;

    if (v == 0) return a0;
    return func_00338040_1(v + 0x36F28, a0, a1);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030DDF0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_L00_0042D9D0(value + 0x36F28);
}

void func_L00_0030DE20(void)
{
}


void func_L00_0030DFE0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_003399B0(value + 0x3CAA8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int func_L00_0030E010(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_003398A8(value + 0x3CAA8, argument);
    return 0;
}

/* shared native body of family e7046bc951256c7e */
void func_L00_00310048(void)
{
    unsigned char *p;
    int seen = 0;

    D_L05_001B2440 = 0;
    for (p = D_L05_001B2520; p < D_L05_001B2524; p += 256) {
        if ((p[32] >= 254 && *(unsigned int *)(p + 160) <= D_L05_001B2048) || seen) {
            D_L05_001B2440++;
            if (p[32] == 0xff)
                seen = 1;
        }
    }
}


/* rac1-decomp src/overlays/shared/mobyfunc_0024FD50.c: func_L00_0024FFE8 */
void func_L00_00310838(unsigned char *a, int dx, int dy) {
    int i;
    int n = a[4] + a[5];
    int *t = *(int **)a;
    for (i = 0; i < n; i++, t += 4) {
        unsigned short *e = *(unsigned short **)t;
        int c = ((unsigned char *)e)[2]; int cnt; e += 2; if (c != 0) { cnt = c; do { e[0] = e[0] + dx; e[1] = e[1] + dy; e += 2; cnt--; } while (cnt != 0); }
    }
}

/* shared native body of family 0820eb1123250c0b */
Slot0820eb11 *func_L00_00310BC8(Ctx *ctx, int index)
{
    int i;
    Slot0820eb11 *slot;
    unsigned char *p;

    for (i = 0; i < 6; i++) {
        if (D_L03_001D23C0[i].f04 == 0) {
            break;
        }
    }
    slot = &D_L03_001D23C0[i];
    slot->f04 = 1;
    slot->f00 = index;
    slot->f10 = (int)(D_L03_001CA5C0 + i * 5376);
    slot->f14 = (int)ctx->f24;
    p = (unsigned char *)*(unsigned int *)(ctx->f24->f1C + (short)index * 4 + 4);
    slot->f02 = p[2];
    slot->f0C = p + (p[0] + 4);
    slot->f1C = ctx->f50;
    ctx->f50 = (int)slot;
    return slot;
}

/* The free half of the allocator above: unlinks the slot the caller's handle points at from
 * the context's slot list, wipes the sixty-four bytes and nulls the handle. The handle is
 * re-read at every mention (no local copy) - that is what keeps the retail allocation. */
void func_L00_00310C88(LvlSlotCtx *ctx, LvlSlotNode **handle)
{
    LvlSlotNode *cur;

    if (*handle == 0)
        return;

    if (ctx->head == *handle) {
        ctx->head = (*handle)->next;
    } else {
        cur = ctx->head;
        while (cur->next != 0 && cur->next != *handle)
            cur = cur->next;
        if (cur->next == *handle)
            cur->next = (*handle)->next;
    }
    func_00282A60((char *)*handle, 0, 0x40);
    *handle = 0;
}

/* func_L00_00310D30 is defined in its own unit. */

INCLUDE_ASM("asm/levels", func_L00_003110E8);

/* scales a float field by 1/1024, fills a 64-byte stack buffer from the object, then applies three per-element helper calls over n 64-byte records. */
void func_L00_003116A8(char *a0, int n, int a2, char *a3)
{
    char buf[64];
    float f20;
    int i;

    f20 = *(float *)(a0 + 44) * 0.0009765625f;
    func_00283658_1(buf, a0 + 192);
    func_002A3F10_3(a0, n, a2, a3);
    for (i = 0; i < n; i++) {
        func_00283788_5(a3 + i * 64, buf, a3 + i * 64);
        func_00282D30_21(a3 + i * 64 + 48, a3 + i * 64 + 48, f20);
        func_00282CC0_24(a3 + i * 64 + 48, a3 + i * 64 + 48, a0 + 16);
    }
}


ASM_FUNC("asm/levels", func_L00_00314D40);
