#include "include_asm.h"

#include "common.h"
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8, field7AC, field7B0, field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290, field2294, field2298, field229C;
} RippleHero;
#define RIPPLE_HERO (*(RippleHero *)&D_00189E20)
extern void STUB_printf(void *, int, int, int, int);
extern void water_select_table_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void func_002FD1B8_ripple(void *, int, int, float, float, float, float) __asm__("func_002FD1B8");
extern int point_in_path_xy(void *, void *, int);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern char D_L04_001ADA00[];
extern char *g_route_path_table[];
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
#define WINT(p,o) (*(int *)((char *)(p)+(o)))
#define WFLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define WPTR(p,o) (*(char **)((char *)(p)+(o)))
extern u32 FastDecTimer(u8 *);
extern int FloatToInt(float);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 g_hero_state;
extern s32 FloatToInt(f32 value);
extern s32 math_random_int_below(s32 limit);
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;
extern s32 GetFirstMobyInGroup(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u32 *out, u32 value, s32 arg2, s32 arg3);
extern f32 FastVecDot(void *a, void *b);
extern f32 square_root(f32 x);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern s32 func_001163B0(void);
extern u8 *ref_L04_00358868_00[];
extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);
extern u32 FastDecTimer(u8 *ptr);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#define MACRO_ADDR __attribute__((section(".sdata")))
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern u32 D_L04_001B2E84 __attribute__((sda));

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */
void func_PAL_L04_003A49E0(char *self) {
    char *state = WPTR(WPTR(self, 0x28), 0x68);
    float x, y, half, r;

    if (WBYTE(WPTR(self, 0x28), 0xBC) >= WBYTE(state, 0x15)) {
        STUB_printf(D_L04_001ADA00, WSHORT(WPTR(self, 0x28), 0xB2),
                      WSHORT(WPTR(self, 0x28), 0xAA), WBYTE(WPTR(self, 0x28), 0xBC),
                      WBYTE(state, 0x15));
        WBYTE(WPTR(self, 0x28), 0x20) = 2;
        WBYTE(WPTR(self, 0x28), 0xBC) = 0;
        WSHORT(state, 0x16) = 50;
        WBYTE(state, 0x14) ^= 1;
        water_select_table_slot(WPTR(self, 0x28), WINT(self, 0x1C), WINT(self, 0x18));
        if (WINT(state, 0x10) >= 0 && !WBYTE(state, 0x14)) {
            int i;
            for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
                r = math_random_float_range(-4.0f, 4.0f);
                x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
                x += r;
                y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
                func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                     x, y, 1.0f, -0.05f);
            }
        }
    }
    if (WBYTE(state, 0x14)) return;
    if (WINT(state, 0x20) != -1) {
        char *p = g_route_path_table[WINT(state, 0x20)];
        if (point_in_path_xy((char *)&g_hero_state + 0x80, p + 0x10, WINT(p, 0)))
            WFLOAT(&g_hero_state, 0x330) = WFLOAT(WPTR(self, 0x28), 0x18);
    }
    half = (WFLOAT(state, 0) - WFLOAT(state, 4)) * 0.5f;
    WFLOAT(WPTR(self, 0x28), 0x18) =
        WFLOAT(state, 4) + (math_fast_sin_or_cos_a(WFLOAT(state, 8)) * half + half);
    if (RIPPLE_HERO.field229C != 20 && RIPPLE_HERO.field229C != 25 &&
        RIPPLE_HERO.field2294 != 0x39 && RIPPLE_HERO.field2294 != 0x78 &&
        RIPPLE_HERO.field2294 != 0x79)
        WFLOAT(state, 8) = FastAddRotations(WFLOAT(state, 8), WFLOAT(state, 0xC));
    if (WINT(state, 0x10) >= 0 && !math_random_int_below(200)) {
        int i;
        for (i = WINT(state, 0x10); i < WINT(self, 4); i++) {
            r = math_random_float_range(-4.0f, 4.0f);
            x = WFLOAT(WPTR(self, 8) + i * 0x1190, 0);
            x += r;
            y = WFLOAT(WPTR(self, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
            func_002FD1B8_ripple(WPTR(self, 8) + i * 0x1190, 1, 1,
                                 x, y, 1.0f, -0.05f);
        }
    }
}
