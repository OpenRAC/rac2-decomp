#include "names.h"
/* The -G8 sibling of L04_002CC748.c for the water grid renderer: its globals are read through $gp
   and the packet cursor through a macro address. */
#include "common.h"
/* Adapted from RAC1 render_water_grids, GPL-3.0, with RAC2 blend/GS setup. */
extern void BuildWaterRenderSetupPacket(void);
extern void VU1_addGSregister(u32,u64);
extern float math_ease_out_quad(float);
extern int FastTweenColor(int,int,float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void transform_vector(void *,void *,void *);
extern int is_vector_outside_clip(void *);
extern void ripple_heights_to_scratchpad(void *,void *);
extern void water_submit_patch_at_pos(void *);
extern void water_fill_grid_points(void *);
extern void water_scroll_texture_coords(void *);
extern u64 GetEffectTextureDescriptor(int);
extern void water_cull_and_submit_tile(void *,int,int);
extern char D_L04_001B9680[];
extern union { u32 *words; char *bytes; } D_L04_001B2C48 MACRO_ADDR;
extern int D_L04_001ADA30 __attribute__((sda));
extern int D_L04_001ADA34 __attribute__((sda));
extern int D_L04_001AD820 __attribute__((sda));
extern int D_L04_001AD82C __attribute__((sda));
extern int D_L04_001AD884 __attribute__((sda));
extern int D_L04_001AD888 __attribute__((sda));
extern int D_L04_001AD88C __attribute__((sda));
extern int D_L04_001AD890 __attribute__((sda));
extern float D_L04_001AD848, D_L04_001AD84C;
typedef struct {
    f32 position[3];
    u8 pad0C[8];
    s32 texture0, texture1;
    u8 alpha2, alpha1;
    u16 active;
    u8 pad20[8];
    f32 uv0, uv1, scroll0, scroll1, uv2, uv3;
    s32 field40, edges, reverse;
    f32 blend;
    u8 heights[0x1140];
} WaterGrid;
typedef struct { s32 a,b,c,d,alpha; } WaterAlphaState;
extern WaterAlphaState ref_L04_003A21F8_00 SDATA(ref_L04_003A21F8_00);
extern WaterAlphaState ref_L04_003A21F8_01 SDATA(ref_L04_003A21F8_01);
/* Both arms end in the same call, so jump2 merges them, and the test on the value already in a
   register leaves no instruction. Until then it ends a block right after the call. */
static inline float water_ease(float t, s32 reverse, float scale) {
    if (reverse) return scale * math_ease_out_quad(t);
    return math_ease_out_quad(t);
}
/* Draws every active water patch: fades it in or out, skips ones off screen, and sends their wave tiles to the screen. */
void render_water_grids(WaterGrid *water_grid, s32 count) {
    f32 corners[4][4];
    f32 near_clip[4];
    f32 far_clip[4];
    f32 x_offset, y_offset, x_end, y_end, z;
    float blend, twice, alpha, v, upper, lower, interpolated_alpha;
    float fade, scroll0, scroll1, uv, uv2, uv3;
    u64 state0, state1;
    u32 near_bits, far_bits;
    s32 mask;
    s32 i, j, mode, reverse;
    s32 n, index, alpha_index;
    f32 *height;
    u64 *data;

    BuildWaterRenderSetupPacket();
    VU1_addGSregister(0x47,0x53001);
    VU1_addGSregister(0x48,0x53001);
    i = 0;
    if (count > 0) do {
        u16 active = water_grid->active;
        if (active == 0) goto next_entity;
        reverse = water_grid->reverse;
        if (reverse) blend=water_grid->blend;
        else blend=1.0f-water_grid->blend;
        blend=water_ease(blend,reverse,1.0f);
        fade = 1.0f-blend;
        scroll0 = water_grid->scroll0 * fade;
        scroll1 = water_grid->scroll1 * fade;
        uv = fade * -0.0016f;
        uv2 = fade * 0.02f;
        uv3 = fade * -0.031f;
        water_grid->uv0 = uv;
        water_grid->uv1 = uv;
        water_grid->scroll0 = scroll0;
        water_grid->scroll1 = scroll1;
        water_grid->uv2 = uv2;
        water_grid->uv3 = uv3;
        D_L04_001AD820=FastTweenColor(D_L04_001ADA30,D_L04_001ADA34,blend);
        x_offset = water_grid->position[0] + D_L04_001AD848;
        x_end = water_grid->position[0] - D_L04_001AD848;
        corners[0][0] = x_offset;
        y_offset = water_grid->position[1] + D_L04_001AD84C;
        y_end = water_grid->position[1] - D_L04_001AD84C;
        corners[0][1] = y_offset;
        z = water_grid->position[2];
        corners[0][2] = z;
        corners[0][3] = 1.0f;
        corners[1][0] = x_end;
        corners[1][1] = y_offset;
        corners[1][2] = z;
        corners[1][3] = 1.0f;
        corners[2][0] = x_offset;
        corners[2][1] = y_end;
        corners[2][2] = z;
        corners[2][3] = 1.0f;
        corners[3][0] = x_end;
        corners[3][1] = y_end;
        corners[3][2] = z;
        corners[3][3] = 1.0f;
        near_bits = 0;
        far_bits = 0;
        for (j = 0; j < 4; j++) {
            FastVecSub(near_clip, corners[j], D_L04_001B9680);
            FastVecScale(far_clip, near_clip, 1024.0f);
            FastVecScale(near_clip, near_clip, 1024.0f);
            transform_vector(far_clip, far_clip, D_L04_001B9680 - 0x80);
            transform_vector(near_clip, near_clip, D_L04_001B9680 - 0x40);
            far_bits = (far_bits << 8) | is_vector_outside_clip(far_clip);
            near_bits = (near_bits << 8) | is_vector_outside_clip(near_clip);
        }
        if ((near_bits & 0x01010101) == 0x01010101) goto next_entity;
        if ((near_bits & 0x02020202) == 0x02020202) goto next_entity;
        if ((near_bits & 0x04040404) == 0x04040404) goto next_entity;
        if ((near_bits & 0x08080808) == 0x08080808) goto next_entity;
        if ((near_bits & 0x20202020) == 0x20202020) goto next_entity;

        twice=blend+blend;
        ripple_heights_to_scratchpad((void *)0x70000000, (u8 *)water_grid + ((*(s32 *)&D_L04_001AD82C) * 0x5c0 + 0x50));
        water_submit_patch_at_pos(water_grid);
        water_fill_grid_points(water_grid);
        water_scroll_texture_coords(water_grid);
        if (water_grid->edges & 1) {
            height = (f32 *)0x70002008;
            for (n = 0x10; n >= 0; n--, height += 3) *height = water_grid->position[2];
        }
        if (water_grid->edges & 2) {
            height = (f32 *)0x700020c8;
            for (n = 0x10; n >= 0; n--, height += 0x33) *height = water_grid->position[2];
        }
        if (water_grid->edges & 4) {
            height = (f32 *)0x70002cc8;
            for (n = 0x10; n >= 0; n--, height += 3) *height = water_grid->position[2];
        }
        if (water_grid->edges & 8) {
            height = (f32 *)0x70002008;
            for (n = 0x10; n >= 0; n--, height += 0x33) *height = water_grid->position[2];
        }
        mode = (far_bits & 0x2f2f2f2f) != 0;
        if (!mode) {
            mode = 2;
            if (!(near_bits & 0x2f2f2f2f)) mode = 0;
        }
        mask = water_grid->active;
        alpha=IntToFloat(water_grid->alpha1);
        v=IntToFloat(ref_L04_003A21F8_00.alpha);
        interpolated_alpha = alpha + (v-alpha)*blend;
        lower = 1.0f-twice;
        upper = twice-1.0f;
        D_L04_001B2C48.words[0] = 0x10000005;
        D_L04_001B2C48.words[1] = 0;
        D_L04_001B2C48.words[2] = 0x11000000;
        D_L04_001B2C48.words[3] = 0x50000005;
        reverse = water_grid->reverse;
        D_L04_001B2C48.bytes += 16;
        if (reverse) {
            if (twice<=1.0f) { ref_L04_003A21F8_01.b=1; ref_L04_003A21F8_01.alpha=FloatToInt(lower*70.0f); }
            else { ref_L04_003A21F8_01.b=2; ref_L04_003A21F8_01.alpha=FloatToInt(upper*170.5f); }
        } else if (twice>=1.0f) { n=2; ref_L04_003A21F8_01.b=n; ref_L04_003A21F8_01.alpha=FloatToInt(upper*170.0f); }
        else { ref_L04_003A21F8_01.b=1; ref_L04_003A21F8_01.alpha=FloatToInt(lower*70.0f); }
        alpha_index=FloatToInt(interpolated_alpha);
        data = (u64 *)D_L04_001B2C48.words;
        data[0] = 0x4000000000008001ULL;
        data[1] = 0xeeee;
        state0 = (u64)ref_L04_003A21F8_00.a;
        state0 |= (u64)ref_L04_003A21F8_00.b<<2;
        state0 |= (u64)ref_L04_003A21F8_00.c<<4;
        state0 |= (u64)ref_L04_003A21F8_00.d<<6;
        state0 |= (u64)alpha_index<<32;
        data[2] = state0;
        data[3] = 0x42;
        state1 = (u64)ref_L04_003A21F8_01.a;
        state1 |= (u64)ref_L04_003A21F8_01.b<<2;
        state1 |= (u64)ref_L04_003A21F8_01.c<<4;
        state1 |= (u64)ref_L04_003A21F8_01.d<<6;
        state1 |= (u64)ref_L04_003A21F8_01.alpha<<32;
        data[4] = state1;
        data[5] = 0x43;
        data[6] = GetEffectTextureDescriptor(water_grid->texture1);
        data[7] = 6;
        data[8] = GetEffectTextureDescriptor(water_grid->texture0);
        data[9] = 7;
        {
            u32 texture_id = water_grid->texture0;
            u32 second_texture_id = water_grid->texture1;
            D_L04_001B2C48.words = (u32 *)(data + 10);
            (*(u32 *)&D_L04_001AD884) = texture_id;
            (*(u32 *)&D_L04_001AD888) = second_texture_id;
        }
        (*(u32 *)&D_L04_001AD88C) = water_grid->alpha2;
        (*(u32 *)&D_L04_001AD890) = alpha_index;
        for (index = 0; index < 16; index++, mask = (s32)mask >> 1) {
            if (mask & 1) water_cull_and_submit_tile(water_grid, index, mode);
        }
next_entity:
        i++;
        water_grid++;
    } while (i < count);
    D_L04_001B2C48.words[0] = 0x10000000;
    D_L04_001B2C48.words[1] = 0;
    D_L04_001B2C48.words[2] = 0x13000000;
    D_L04_001B2C48.words[3] = 0;
    D_L04_001B2C48.bytes += 16;
    VU1_addGSregister(0x47,0x5360B);
    VU1_addGSregister(0x48,0x5360B);
}
