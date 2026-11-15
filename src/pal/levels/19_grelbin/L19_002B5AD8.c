#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
typedef struct {
    u8 pad0[0x80];
    TI16 f80;
    u8 pad90[0xF0 - 0x90];
    TI16 fF0;
    u8 pad100[0x10];
    TI16 f110;
    u8 pad120[0x1DC - 0x120];
    s16 f1DC;
    u8 pad1DE[0x21C - 0x1DE];
    s16 f21C;
    u8 pad21E[0x68E - 0x21E];
    s16 f68E;
    u8 pad690[0x6C4 - 0x690];
    void *f6C4;
    u8 pad6C8[0x1497 - 0x6C8];
    u8 f1497;
    u8 pad1498[0x1500 - 0x1498];
    s32 f1500;
    u8 pad1504[0x1874 - 0x1504];
    s32 f1874;
    u8 pad1878[0x2290 - 0x1878];
    u8 *f2290;
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 f22B4;
    u8 pad22B5[0x249C - 0x22B5];
    u8 *f249C;
    u8 pad24A0[0x24CC - 0x24A0];
    s32 f24CC;
} Player_002B5BF0;
typedef struct {
    u8 pad0[0x10];
    float f10;
    float f14;
    float f18;
    float f1C;
    u8 *f20;
    s32 f24;
    u8 f28;
    u8 pad29[3];
    float f2C;
    s32 f30;
    u8 pad34[4];
    u8 *f38;
    u8 pad3C[4];
} Entry_002B5BF0;
extern Player_002B5BF0 g_hero_state;
extern Entry_002B5BF0 D_L19_001C4100[];
extern s32 D_L19_001A8F00 __attribute__((sda));
extern s32 D_L19_001B0040 __attribute__((sda));
extern u8 g_bolt_multiplier __attribute__((sda));
extern u8 D_001A7A33 __attribute__((sda));
extern float fade_get_value(void);
extern float func_PAL_L00_00381328(float);
extern s32 FloatToInt(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, s32, float, float, float);
extern void func_PAL_L19_002C45D0(s32, s32);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void func_PAL_L00_002A4D58(s32);
extern void hero_play_sound(s32, s32);
extern void hero_flatten_push_vector(void *, s32, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

s32 func_PAL_L19_002B5AD8(s32 arg0) {
    TI16 vec;
    Entry_002B5BF0 *e;
    u8 *moby;
    u8 *other;
    s32 flag;
    s32 bits;

    if (g_hero_state.f229C == 20 || g_hero_state.f229C == 7) {
        return 0;
    }
    if (g_hero_state.f2294 == 0x31) {
        return 0;
    }
    if (g_hero_state.f1DC != 0) {
        return 0;
    }
    if (D_L19_001A8F00 != 0) {
        return 0;
    }
    g_hero_state.f249C = 0;
    moby = g_hero_state.f2290;
    if (moby[0xA8] == 0xFF) {
        return 0;
    }
    e = &D_L19_001C4100[moby[0xA8]];
    if (e->f38 != moby) {
        return 0;
    }
    if (g_hero_state.f22B4 == 4) {
        if (D_L19_001B0040 != 0 || g_hero_state.f2294 == 0x6F) {
            return 0;
        }
    } else if ((e->f24 & 9) == 0) {
        return 0;
    }
    if (e->f2C != 0.0f) {
        D_001A7A33 = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && g_hero_state.f22B4 == 0) {
        e->f2C = func_PAL_L00_00381328(e->f2C);
        if (e->f2C == 0.0f) {
            return 0;
        }
    }
    g_hero_state.f249C = e->f20;
    if (g_hero_state.f22B4 == 4 && D_L19_001B0040 == 0 && g_hero_state.f2294 != 0x6F) {
        u8 *m = *(u8 **)(g_hero_state.f2290 + 0x68);
        *(s16 *)(m + 0x3BC) -= 0x96;
        if (*(s16 *)(m + 0x3BC) < 0) {
            *(s16 *)(m + 0x3BC) = 0;
        }
    }
    if (arg0 == 0) {
        return 1;
    }
    flag = 0;
    hero_clear_tracked_slots();
    if (e->f30 & 1) {
        qcopy(&vec, &e->f10);
        if (e->f1C == 5627.9248046875f) {
            flag = 1;
        }
    } else if (e->f20 != 0) {
        FastVecSub(&vec, &g_hero_state.f80, e->f20 + 0x10);
    } else {
        hero_build_relative_point(&vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.f22B4) {
    case 0:
        other = g_hero_state.f249C;
        if (other != 0 && (*(s16 *)(other + 0xAA) == 0x4EB || *(s16 *)(other + 0xAA) == 0x558)) {
            func_PAL_L19_002C45D0(0x7D, 1);
            return 1;
        }
        if ((g_hero_state.f2294 == 1 || g_hero_state.f2294 == 0x1D || g_hero_state.f1500 != 0)
            && !(e->f24 & 8)) {
            u8 *r = part_find_owned_effect_slot(g_hero_state.f2290, 1, 0);

            if (r != 0) {
                func_PAL_L00_002A4D58(FloatToInt(*(float *)(r + 0x2C)));
            }
            if (g_hero_state.f24CC == 0) {
                func_PAL_L19_002C45D0(0x16, 1);
            }
            g_hero_state.f1DC = 0x40;
            if (g_hero_state.f21C == 0) {
                g_hero_state.f21C = 0xF;
            }
            hero_play_sound(0x14, 0);
            return 0;
        }
        if (g_hero_state.f229C == 0x12) {
            func_PAL_L19_002C45D0(0x72, 1);
        } else if (g_hero_state.f229C == 0x11) {
            func_PAL_L19_002C45D0(0x73, 1);
        } else if (e->f24 & 8) {
            func_PAL_L19_002C45D0(0x8C, 1);
        } else {
            func_PAL_L19_002C45D0(0x16, 1);
        }
        if (g_hero_state.f2294 == 0x8C) {
            qzero(&vec);
        } else {
            hero_flatten_push_vector(&vec, flag, g_hero_state.f1497 ? 0.0f : 0.06600001f, 0.034f);
            if (flag != 0 && e->f28 == 4) {
                cam_scale_view_space_height(&vec, &vec, 2.0f);
            }
        }
        break;
    case 4:
        func_PAL_L19_002C45D0(0x90, 1);
        hero_flatten_push_vector(&vec, flag, 0.10000001f, 0.060000002f);
        break;
    }
    FastVecAdd(&g_hero_state.fF0, &g_hero_state.fF0, &vec);
    FastVecAdd(&g_hero_state.f110, &g_hero_state.f110, &vec);
    return 1;
}


/* func_PAL_L19_002B6160, the PAL copy of func_L19_002B6278: the same C, where the
   ramp step 0.02f becomes 0.024f and the last call's 0.02f, 0.3f and 0.06666667f become
   0.028800001f, 0.43200004f and 0.080000006f. */
void func_PAL_L19_002B6160(void) {
    int a3;
    int v1;
    float r;

    if (((Hero *)&g_hero_state)->b[0x22B4] == 0 || ((Hero *)&g_hero_state)->b[0x22B4] == 4) {
        ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.8f;
        ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.7f;
        ((Hero *)&g_hero_state)->f[0x260 / 4] = 0.45f;
    }

    a3 = ((Hero *)&g_hero_state)->i[0x229C / 4];
    if (a3 == 4) {
        if (((Hero *)&g_hero_state)->h[0x4AC / 2] < ((Hero *)&g_hero_state)->i[0x1B8 / 4]) {
            if (((Hero *)&g_hero_state)->b[0x49E] == 0) {
                ((Hero *)&g_hero_state)->f[0x25C / 4] = ((Hero *)&g_hero_state)->f[0x4B8 / 4];
            }
        }
    } else {
        v1 = ((Hero *)&g_hero_state)->i[0x2294 / 4];
        if (v1 == 6) {
            ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.5f;
        } else if (v1 == 4) {
            ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(a3 - 0x11) < 2) {
            ((Hero *)&g_hero_state)->i[0x258 / 4] = 0;
            ((Hero *)&g_hero_state)->i[0x25C / 4] = 0;
        } else if (v1 == 0x7C) {
            ((Hero *)&g_hero_state)->f[0x260 / 4] = 0.8f;
        }
    }

    if (((Hero *)&g_hero_state)->b[0x287] == 0)
        goto slow;
    if (((Hero *)&g_hero_state)->i[0x22A4 / 4] == 0x12)
        goto slow;
    if (((Hero *)&g_hero_state)->i[0x22B0 / 4] == 0x12)
        goto slow;
    if (((Hero *)&g_hero_state)->b[0x22B4] == 0) {
        if (((Hero *)&g_hero_state)->f[0x254 / 4] < 0.53f)
            goto slow;
    }
    if (((Hero *)&g_hero_state)->i[0x229C / 4] == 0x11)
        goto slow;
    if (((Hero *)&g_hero_state)->b[0x1494] != 0)
        goto slow;

    r = vec_distance_xy((u8 *)&g_hero_state + 0x240, (u8 *)&g_hero_state + 0x80);
    if (r > ((Hero *)&g_hero_state)->f[0x264 / 4] * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *p = (u8 *)&g_hero_state + 0x250;
        float step = 0.024f;
        ApproachValue((float *)p, ((Hero *)&g_hero_state)->f[0x258 / 4], step);
        ApproachValue((float *)(p + 4), ((Hero *)&g_hero_state)->f[0x25C / 4], step);
        math_spring_float_to_goal(
            (float *)(p + 0x14),
            (float *)(p + 0x18),
            ((Hero *)&g_hero_state)->f[0x260 / 4],
            0.028800001f,
            0.43200004f,
            0.080000006f);
    }
}
