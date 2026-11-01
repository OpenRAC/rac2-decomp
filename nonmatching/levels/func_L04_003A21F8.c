/* Tier: sol-high (task v1231), USA v1.01 game profile -O2 -G8 -ffunction-sections.
 * Retained check.py result: 1708 bytes versus 1700; 0 of 5 places match.
 * A scalar/untyped variant reached 1700 bytes but had worse packet allocation.
 * Compared with the earlier 1772-byte draft, this retains measured 0x1190-byte
 * grid records and two contiguous five-word GS alpha-state views. Explicit
 * small-data views preserve their full 20-byte extents. Splitting the two
 * packed-alpha accumulators restores the retail v0/v1/a0/a1 packet sequence.
 * Calling FloatToInt inside the branches restores the retail shared-call tail.
 * Still different: 1024.0f is hoisted before the blend call; early UV products,
 * the s5/s6 corner-loop allocation and its delay slot differ. The alpha add
 * sinks into a branch slot, leaving a two-instruction cursor store where
 * retail has a GP store, and the tile loop gains one alignment nop.
 * Countdown/index/pointer corner loops tie; separate alpha-result locals and
 * cursor byte/word increments tie. -fno-strict-aliasing did not fix the packet.
 * Next useful experiment: establish the original packet-cursor/GS field views
 * and UV update grouping. No linked build was run; placement symbols remain
 * unvalidated. All required declarations are below.
 *
 * closer D, 1 November 2026: all 240 orders of the uv statements stay at 74-78. 1024.0f (insn 1227) is ready at
 * t=1 of the block and, at priority 2, passes the blend call in sched1; retail issues it first after
 * func_00283D38. A do/while(0) barrier is worse (114), so this is not a block or loop-note boundary.
 */
#include "common.h"
/* Adapted from RAC1 render_water_grids, GPL-3.0, with RAC2 blend/GS setup. */
extern void func_L04_003A0FC8(void);
extern void func_002FC560(u32,u64);
extern float func_002A7798(float);
extern int func_00283D38(int,int,float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002830C0(void *,void *,void *);
extern int func_00282BE0(void *);
extern void func_L04_0032F1D8(void *,void *);
extern void func_L04_0032F3C0(void *);
extern void func_L04_003A0C40(void *);
extern void func_L04_003A00E8(void *);
extern u64 func_0027C878(int);
extern void func_L04_003A0CE8(void *,int,int);
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
void func_L04_003A21F8(WaterGrid *pos, s32 count) {
    f32 corners[4][4];
    f32 near_clip[4];
    f32 far_clip[4];
    f32 x_offset, y_offset, x_end, y_end, z;
    float blend, twice, alpha, v, upper, lower, interpolated_alpha;
    float fade, scroll0, scroll1, uv;
    f32 (*corner)[4];
    u64 state0, state1;
    u32 near_bits, far_bits;
    s32 mask;
    s32 i, j, mode;
    s32 height_index, index, alpha_index;
    f32 *height;
    u64 *data;

    func_L04_003A0FC8();
    func_002FC560(0x47,0x53001);
    func_002FC560(0x48,0x53001);
    i = 0;
    if (count > 0) do {
        u16 active = pos->active;
        if (active == 0) goto next_entity;
        if (pos->reverse) blend=pos->blend;
        else blend=1.0f-pos->blend;
        blend=func_002A7798(blend);
        fade = 1.0f-blend;
        scroll0 = pos->scroll0 * fade;
        scroll1 = pos->scroll1 * fade;
        uv = fade * -0.0016f;
        pos->scroll0 = scroll0;
        pos->scroll1 = scroll1;
        pos->uv0 = uv;
        pos->uv3 = fade * -0.031f;
        pos->uv2 = fade * 0.02f;
        pos->uv1 = uv;
        D_L04_001AD820=func_00283D38(D_L04_001ADA30,D_L04_001ADA34,blend);
        x_offset = pos->position[0] + D_L04_001AD848;
        x_end = pos->position[0] - D_L04_001AD848;
        corners[0][0] = x_offset;
        y_offset = pos->position[1] + D_L04_001AD84C;
        y_end = pos->position[1] - D_L04_001AD84C;
        corners[0][1] = y_offset;
        z = pos->position[2];
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
        for (j = 0, corner = corners; j < 4; j++, corner++) {
            func_00282CF0(near_clip, *corner, D_L04_001B9680);
            func_00282D30(far_clip, near_clip, 1024.0f);
            func_00282D30(near_clip, near_clip, 1024.0f);
            func_002830C0(far_clip, far_clip, D_L04_001B9680 - 0x80);
            func_002830C0(near_clip, near_clip, D_L04_001B9680 - 0x40);
            far_bits = (far_bits << 8) | func_00282BE0(far_clip);
            near_bits = (near_bits << 8) | func_00282BE0(near_clip);
        }
        if ((near_bits & 0x01010101) == 0x01010101) goto next_entity;
        if ((near_bits & 0x02020202) == 0x02020202) goto next_entity;
        if ((near_bits & 0x04040404) == 0x04040404) goto next_entity;
        if ((near_bits & 0x08080808) == 0x08080808) goto next_entity;
        if ((near_bits & 0x20202020) == 0x20202020) goto next_entity;

        twice=blend+blend;
        func_L04_0032F1D8((void *)0x70000000, (u8 *)pos + ((*(s32 *)&D_L04_001AD82C) * 0x5c0 + 0x50));
        func_L04_0032F3C0(pos);
        func_L04_003A0C40(pos);
        func_L04_003A00E8(pos);
        if (pos->edges & 1) {
            height = (f32 *)0x70002008;
            for (height_index = 0x10; height_index >= 0; height_index--, height += 3) *height = pos->position[2];
        }
        if (pos->edges & 2) {
            height = (f32 *)0x700020c8;
            for (height_index = 0x10; height_index >= 0; height_index--, height += 0x33) *height = pos->position[2];
        }
        if (pos->edges & 4) {
            height = (f32 *)0x70002cc8;
            for (height_index = 0x10; height_index >= 0; height_index--, height += 3) *height = pos->position[2];
        }
        if (pos->edges & 8) {
            height = (f32 *)0x70002008;
            for (height_index = 0x10; height_index >= 0; height_index--, height += 0x33) *height = pos->position[2];
        }
        mode = (far_bits & 0x2f2f2f2f) != 0;
        if (!mode) {
            mode = 2;
            if (!(near_bits & 0x2f2f2f2f)) mode = 0;
        }
        mask = pos->active;
        alpha=func_00283CE0(pos->alpha1);
        v=func_00283CE0(ref_L04_003A21F8_00.alpha);
        interpolated_alpha = alpha + (v-alpha)*blend;
        lower = 1.0f-twice;
        upper = twice-1.0f;
        D_L04_001B2C48.words[0] = 0x10000005;
        D_L04_001B2C48.words[1] = 0;
        D_L04_001B2C48.words[2] = 0x11000000;
        D_L04_001B2C48.words[3] = 0x50000005;
        D_L04_001B2C48.bytes += 16;
        if (pos->reverse) {
            if (twice<=1.0f) { ref_L04_003A21F8_01.b=1; ref_L04_003A21F8_01.alpha=func_00283CF0(lower*70.0f); }
            else { ref_L04_003A21F8_01.b=2; ref_L04_003A21F8_01.alpha=func_00283CF0(upper*170.5f); }
        } else if (twice>=1.0f) { ref_L04_003A21F8_01.b=2; ref_L04_003A21F8_01.alpha=func_00283CF0(upper*170.0f); }
        else { ref_L04_003A21F8_01.b=1; ref_L04_003A21F8_01.alpha=func_00283CF0(lower*70.0f); }
        alpha_index=func_00283CF0(interpolated_alpha);
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
        data[6] = func_0027C878(pos->texture1);
        data[7] = 6;
        data[8] = func_0027C878(pos->texture0);
        data[9] = 7;
        D_L04_001B2C48.words = (u32 *)(data + 10);
        {
            u32 texture_id = pos->texture0;
            u32 second_texture_id = pos->texture1;
            (*(u32 *)&D_L04_001AD884) = texture_id;
            (*(u32 *)&D_L04_001AD888) = second_texture_id;
        }
        (*(u32 *)&D_L04_001AD88C) = pos->alpha2;
        (*(u32 *)&D_L04_001AD890) = alpha_index;
        for (index = 0; index < 16; index++, mask = (s32)mask >> 1) {
            if (mask & 1) func_L04_003A0CE8(pos, index, mode);
        }
next_entity:
        i++;
        pos++;
    } while (i < count);
    D_L04_001B2C48.words[0] = 0x10000000;
    D_L04_001B2C48.words[1] = 0;
    D_L04_001B2C48.words[2] = 0x13000000;
    D_L04_001B2C48.words[3] = 0;
    D_L04_001B2C48.bytes += 16;
    func_002FC560(0x47,0x5360B);
    func_002FC560(0x48,0x5360B);
}
