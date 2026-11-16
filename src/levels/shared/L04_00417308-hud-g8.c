#include "names.h"
/* func_L04_00417308 (5,968 bytes; Barlow and Damosel): the race HUD (ruler, rank rows, markers).
 * A FAKEMATCH unit (owner ruling, 13 November 2026; config/fakematch.tsv): each site is marked
 * below. It builds with the switches of tools/compiler/transformers/l04_17308_rules.py and
 * earlier ones (config/cflags.txt; docs/build/compiler-notes.md). */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
typedef struct { s32 v[4]; } T4;
typedef struct { s32 v[5]; } T5;
typedef struct { s32 id; float y; } Slot;
typedef struct { s32 a; s32 flags; char pad[56]; } Rec;

extern T4 g_race_ruler_quad_a;
extern T4 g_race_ruler_quad_b;
extern T5 g_race_ruler_quad_c;
extern char g_str_lap_counter_format[];
extern u8 *g_race_controller __attribute__((sda));
extern s32 g_race_banner_timer __attribute__((sda));
extern s32 g_current_race_index __attribute__((sda));
extern s32 g_race_ruler_last_value __attribute__((sda));
extern s32 g_race_ruler_flash_timer __attribute__((sda));
extern u8 *g_moby_l04_pool __attribute__((sda));
extern s32 g_race_time_ticks;
extern s32 g_current_lap;
extern s32 g_screen_width;
extern s32 g_current_map_index;
extern s32 g_popup_resource_table;
extern float g_race_hud_layout_scale;
extern char g_route_frame_origin[] MACRO_ADDR;
extern float g_route_frame_delta;
extern float g_route_frame_extra;
extern float D_L04_001B31A0_view[] __asm__("D_L04_001B31A0") MACRO_ADDR;
extern float g_race_ruler_scroll_offset;
extern char g_water_camera[];
typedef struct { char pad[0x24]; int kind; u8 *owner; char tail[0x3C]; int active; char pad2[6]; u16 state; } OwnerContext;
extern OwnerContext g_music_state;
extern Slot g_race_ruler_slots[];
extern Rec g_race_challenge_table[];
extern s32 g_race_rank_string_ids[];

extern int func_001157AC(char *);
extern int sprintf(char *, char *, ...);
extern void UpdateViewContext(void);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);
extern void text_draw_medium(int, int, unsigned long long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long long, char *, int);
extern int text_draw_centered_large(int, int, unsigned long long, char *, int);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void transform_vector(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern void set_identity_matrix(void *);
extern void euler_to_matrix(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern float fast_subtract_rotations(float, float);
extern int FastTweenColor(int, int, float);
extern char *GetLocalizedString(int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, void *);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long long, int);
extern void level_set_rect(int, int, float, float, float, float);
extern float ApproachValue(float *, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern f32 math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern int snd_resume_music_stream(void);
extern int PlayMobySound(int, int, void *);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_draw_scaled_object_two_axes(void *, float, int, float, float, float, float);
extern void DrawNativeQuads(void *, float, float, int, float, void *);
extern void *table_find_by_id(void *, int);
extern void hud_draw_race_banner(u8 *);
extern void menu_draw_box_two_labels();
extern void DrawRaceTimerHud(u8 *);
extern void GetAnimationPathPoint(void *, void *, int, int, void *, void *, void *);

typedef struct { char pad[0x1C4]; s32 m1C4, m1C8, m1CC, m1D0; float m1D4; s32 m1D8, m1DC, m1E0; } Marker;
#define OM(o) ((Marker *)(o))
#define I(b, o) (*(s32 *)((b) + (o)))
#define F(b, o) (*(float *)((b) + (o)))
#define CLAMP01(x) do { if ((x) > 1.0f) (x) = 1.0f; if ((x) < 0.0f) (x) = 0.0f; } while (0)

extern int g_race_hud_mode;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord_a(float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord_ah(float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (scaled == half)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
/* FAKEMATCH: label_y plus a second dead mode test (D_L04_001B2D40 + 1 == active): one more n20 reference, no code */
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    if (g_race_hud_mode + 1 == active)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}
#define HC(k) hud_coord((k), D_L04_001B2D44, 0.5f)
#define HCN(k) hud_coord_a((k), D_L04_001B2D44, 0.5f, n20)
#define LY2(hd, k) label_y2((void *)(hd), (k), D_L04_001B2D44, 0.5f, 1)
#define LY(hd, k) label_y((void *)(hd), (k), D_L04_001B2D44, 0.5f, 1)

/* Draws the race screen: the progress ruler, the rank rows and the markers for each racer. */
s32 hud_draw_race_ruler(void)
{
    T4 A = g_race_ruler_quad_a;
    T4 B = g_race_ruler_quad_b;
    u8 *h = g_race_controller;
    T5 C = g_race_ruler_quad_c;
    u8 *p = *(u8 **)(h + 0x68);
    u8 *obj;
    u8 *o;
    u8 *e;
    char buf[16];
    Vec m[4];
    Vec v90[4];
    Vec vD0, vE0, vF0;
    float tmp;
    s32 sy, sy2, sy3;
    u8 *pa, *pb, *arr;
    Vec *m2; /* FAKEMATCH: named &m[2] declared before hp: its alter_reg slot 0x120 precedes hp's 0x124 */
    u8 *hp;
    float fr, fs, fm, fe, f21, fa, fd;
    int n33, n20, ne, i, col, idx, v, va, v3, vy;
    int j;
    int one2;
    int none;
    int one3;
    int one4;
    float half;
    float rh;
    float fz;
    float k15;
    float tenth;
    int mcol;
    Vec *mv;
    char *s;

    n20 = 1;
    if (h[0xBC] == n20)
        menu_draw_box_two_labels();
    if (g_race_banner_timer > 0) {
        DrawRaceTimerHud(h);
        math_fast_float_d(&g_race_banner_timer);
        if (g_race_banner_timer == 0xAD)
            PlayMobySound(0xD, 0, h);
    } else if (math_fabs(F(p, 0x4A4)) > 1.5707964f) {
        gfx_draw_rounded_box(HC(112.0f), HC(142.0f), 0xAF, g_screen_width - 0xAF, 0x60, 0x60442D00);
        level_set_rect(0x60, 0x55F0C070, (float)HC(112.0f), (float)HC(142.0f) /* FAKEMATCH: was HCN; drops one n20 ref so n20 lands at 23/250 */, 175.0f,
                      (float)(g_screen_width - 0xAF));
        {
            int x, y, len;
            do { s = GetLocalizedString(0x2F95); x = g_screen_width / 2; y = label_y((void *)x, 118.0f, g_race_hud_layout_scale, 0.5f, n20); } while (0); len = func_001157AC(s);
            text_draw_centered_large(x, y, 0x700000E4, s, len);
        }
        if (I(p, 0x76C) == 0) {
            OwnerContext *context = &g_music_state;
            I(p, 0x76C) = n20;
            if ((context->active != 0 || context->kind != -1) && (u16)(context->state - 6) >= 2)
                context->state = 5;
        }
        if (I(p, 0x76C) != 0) {
            OwnerContext *context = &g_music_state;
            if (!context->active && context->kind == -1) {
                context->kind = I(p, 0x760) + 0xBB8;
                context->owner = h;
            }
            snd_resume_music_stream();
        }
    }
    if (math_fabs(F(p, 0x4A4)) < 1.5707964f && I(p, 0x76C) != 0) {
        OwnerContext *context = &g_music_state;
        I(p, 0x76C) = 0;
        if ((u16)(context->state - 6) >= 2)
            context->state = 5;
    }
    if ((u32)(h[0xBC] - 1) < 4 || g_race_time_ticks < 0x3C)
        hud_draw_race_banner(h);
    if (g_popup_resource_table != 0) {
        { float q = math_fast_sin_or_cos_b(0.56217057f) / math_fast_sin_or_cos_a(0.56217057f); u8 *cam = g_water_camera; F(cam, 0xB0) = q; }
        UpdateViewContext();
        { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x2D); gfx_draw_scaled_object_two_axes(spr, 10.0f, 0x60442D00, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x2E); gfx_draw_scaled_object_two_axes(spr, 10.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (I(p, 0x360) != 0) {
            float fr;
            va = A.v[I(p, 0x360) - 1];
            vF0.i[0] = va;
            vF0.i[1] = va;
            vF0.i[2] = va;
            vF0.i[3] = va;
            idx = 0;
            switch (I(p, 0x360)) {
            case 1: idx = 0; break;
            case 2: idx = 1; break;
            case 3: idx = 2; break;
            }
            hud_draw_sprite_gradient(GetIconFrame(0x7568, idx), 0x3E, HC(17.0f), 0x28, HC(35.0f), &vF0);
            fr = (float)I(p, 0x364) / (float)C.v[I(p, 0x360)];
            if (fr > 1.0f) fr = 1.0f;
            if (fr < 0.0f) fr = 0.0f;
            gfx_draw_screen_rectangle(0x6F, HC(28.0f), (int)(fr * 91.0f) + 0x6F, HC(41.0f), 0xFFFFF0, &vF0);
        }
        n33 = I(p, 0x33C);
        if (n33 > 0) {
            if (g_race_ruler_last_value != n33) {
                if (g_race_ruler_last_value < n33)
                    g_race_ruler_flash_timer = 0x2D;
                else
                    g_race_ruler_flash_timer = 0;
                g_race_ruler_last_value = I(p, 0x33C);
            }
            if (g_race_ruler_flash_timer > 0)
                g_race_ruler_flash_timer = g_race_ruler_flash_timer - 1;
            col = FastTweenColor(0x603F00B2, 0x800000FF, (float)g_race_ruler_flash_timer * 0.022222223f);
            { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x35); gfx_draw_scaled_object_two_axes(spr, 11.0f, col, (float)LY(spr, 10.0f), 1.0f, 1.0f, (float)g_race_ruler_last_value); }
        } else {
            g_race_ruler_last_value = 0;
        }
        {
        one4 = 1;
        if (I(p, 0x278) != 0)
            fa = (float)I(p, 0x278) / (float)I(p, 0x650);
        else
            fa = (float)I(p, 0x338) * 0.004166667f;
        if (fa > 1.0f) fa = 1.0f;
        if (fa < 0.0f) fa = 0.0f;
        vF0.i[0] = 0x603F00B2;
        vF0.i[1] = 0x603F00B2;
        vF0.i[2] = 0x603F00B2;
        vF0.i[3] = 0x603F00B2;
        gfx_draw_screen_rectangle(0x1A, label_y((void *)&vF0, (float)(0x62 - (int)(fa * 74.0f)), g_race_hud_layout_scale, 0.5f, one4), 0x26, HC(98.0f), 0xFFFFF0,
                      &vF0);
        }
        { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x3F); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x60442D00, (float)label_y(spr, 10.0f, g_race_hud_layout_scale, 0.5f, one4), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x40); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x55F0C070, (float)label_y(spr, 10.0f, g_race_hud_layout_scale, 0.5f, one4), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x41); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (g_current_map_index == 4)
            { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x42); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        else
            { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x30); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (g_current_map_index == 4 && (g_race_challenge_table[g_current_race_index].flags & 4))
            { void *spr = (void *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x43); gfx_draw_scaled_object_two_axes(spr, 498.0f, 0x60FFDE8D, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        n20 = I(p, 0x320);
        if ((u32)(n20 - 1) >= 0x14)
            n20 = 0x14;
        {
            int y;
            int c;
            int k;
            mcol = n20 >= 0xA ? 0x11D : 0x123;
            k = g_race_rank_string_ids[n20 - 1]; /* FAKEMATCH: index precomputed outside the group */
            /* FAKEMATCH: call inside the rank-row group so the 24.0 li.s precedes the s copy (0xAF8); label_y4 with n20 active keeps n20 (23/250 = 0.368..0.375 window) above s and below the s1 allocno */
            do { s = GetLocalizedString(k); y = label_y4((void *)n20, 24.0f, g_race_hud_layout_scale, 0.5f, n20); } while (0);
            c = B.v[n20 < 4 ? n20 - 1 : 3];
            text_draw_medium(mcol, y, c, s, -1);
        }
        {
            int r = sprintf(buf, g_str_lap_counter_format, g_current_lap + 1, 3);
            int y = label_y3((void *)r, 71.0f, g_race_hud_layout_scale, 0.5f, 1);
            int len = func_001157AC(buf);
            text_draw_centered_medium(0x1D5, y, 0x60F0F0F0, buf, len);
        }
        set_identity_matrix(m);
        matrix_from_basis_rows(m, &g_route_frame_delta);
        AppendScreenRectPacket(0x157, HC(36.0f), 0x1AB, HC(37.0f), 0x25F0C070, 0);
        AppendScreenRectPacket(0x151, HC(28.0f), 0x1AB, HC(29.0f), 0x25F0C070, 0);
        AppendScreenRectPacket(0x160, HC(45.0f), 0x1AB, HC(46.0f), 0x25F0C070, 0);
        one3 = 1; /* FAKEMATCH: before i = 0 so one3 is born before the &vF0 copy dies */
        i = 0;
        FastVecScale(&vD0, h + 0xC0, F(p, 0x30C) + F(p, 0x27C));
        hp = h + 0x10;
        transform_vector(&vE0, &vD0, m);
        arr = p + 0x1E4;
        fd = FastVecDot(&vE0, &g_route_frame_delta);
        pa = p + 0x494;
        pb = p + 0x498;
        FastVecScale(&vD0, &g_route_frame_delta, fd);
        add_vectors(&vF0, &vE0, &vD0);
        ApproachValue(&g_race_ruler_scroll_offset, vE0.f[0] * -1.25f, 0.050000004f);
        m2 = &m[2]; /* FAKEMATCH: set-once &m[2], see decl */
        for (; i < 9; i++) {
            fz = 0.0f; /* FAKEMATCH: set-once zero, hoisted first (retail preheader order) */
            rh = 0.5f; /* FAKEMATCH: per-iteration ruler half, hoisted by loop.c; reload_cse makes it retail's mov.s f23,f20 (gcse would otherwise copy-propagate the 0.5 register into the ruler) */
            sy = (int)(g_race_ruler_slots[i].y + g_race_ruler_scroll_offset);
            if (sy < 0x164 && g_race_ruler_scroll_offset < fz /* FAKEMATCH: fz */) {
                if (i == 0)
                    g_race_ruler_slots[0].y = g_race_ruler_slots[8].y + 8.0f;
                else
                    g_race_ruler_slots[i].y = g_race_ruler_slots[i - 1].y + 8.0f;
            } else if (sy >= 0x1A4 && g_race_ruler_scroll_offset > 0.0f) {
                if (i == 8)
                    g_race_ruler_slots[8].y = g_race_ruler_slots[0].y - 8.0f;
                else
                    g_race_ruler_slots[i].y = g_race_ruler_slots[i + 1].y - 8.0f;
            }
            g_race_ruler_slots[i].y = g_race_ruler_slots[i].y + g_race_ruler_scroll_offset;
            sy = (int)g_race_ruler_slots[i].y;
            if (sy < 0x173)
                fr = ((float)sy - 355.0f) * 0.06666667f;
            else if (sy >= 0x195)
                fr = (420.0f - (float)sy) * 0.06666667f;
            else
                fr = 1.0f;
            if (fr > 1.0f) fr = 1.0f;
            if (fr < 0.0f) fr = 0.0f;
            mcol = FastTweenColor(0x10F0C070, 0x25F0C070, fr);
            AppendScreenRectPacket(sy, hud_coord_a(21.0f, g_race_hud_layout_scale, rh, one3), sy + 1, hud_coord_a(55.0f, g_race_hud_layout_scale, rh, one3), mcol, 0);
        }
        FastVecSub(&vE0, hp, g_route_frame_origin);
        transform_vector(&vD0, &vE0, m);
        fa = vD0.f[1] * 0.2f;
        if (fa > 1.0f)
            fa = 1.0f;
        if (fa < -1.0f)
            fa = -1.0f;
        sy3 = (int)(fa * 13.0f) + 0x24;
        obj = (u8 *)(u32)table_find_by_id((void *)(u32)(g_popup_resource_table + 0x8710), 0x3E);
        f21 = mat_fast_helper_a(g_route_frame_delta, D_L04_001B31A0_view[1]);
        j = 0;
        none = -1; /* FAKEMATCH: set-once -1 after j = 0 puts j's daddu fp before the hoisted -1 (0x1070/0x1090) */
        one2 = 1;
        half = 0.5f;
        tenth = 0.1f;
        do {
            ne = *(s32 *)((int)arr + (j << 2));
            if (ne != none) {
                e = g_moby_l04_pool + (ne << 8);
                o = *(u8 **)(e + 0x68);
                if (e[0x20] == 2 || h[0xBC] == one2 || h[0xBC] == 3) {
                    FastVecSub(&vE0, e + 0x10, g_route_frame_origin);
                    transform_vector(&vD0, &vE0, m);
                    sy = (int)(vD0.f[0] + vD0.f[0]) + 0x183;
                    vy = (int)(vD0.f[1] * 4.0f);
                    sy2 = vy + 0x24;
                    if ((u32)(vy + 0xD) < 0x1B && sy < 0x1A5 && sy >= 0x168) {
                        if (sy < 0x173)
                            fm = ((float)sy - 360.0f) * tenth;
                        else if (sy >= 0x19A)
                            fm = (420.0f - (float)sy) * tenth;
                        else
                            fm = 1.0f;
                        if (fm == 1.0f) {
                            if (sy2 < 0x1D)
                                fm = ((float)sy2 - 23.0f) * 0.2f;
                            else if (sy2 >= 0x2C)
                                fm = (49.0f - (float)sy2) * 0.2f;
                        }
                        mcol = FastTweenColor(0x100040E4, 0x600040E4, fm);
                        tmp = fast_subtract_rotations(f21, F(e, 0xF8));
                        if (OM(o)->m1D4 == -1.0f)
                            OM(o)->m1D4 = tmp;
                        else
                            math_approach_target_with_direction_mode(o + 0x1D4, tmp, 0.002327106f, 0.002327106f, 4.712389f,
                                          o + 0x1E0, 0);
                        v = OM(o)->m1CC;
                        if (v == none) {
                            OM(o)->m1CC = sy;
                        } else {
                            tmp = (float)v;
                            math_step_value_toward_target(&tmp, o + 0x1D8, (float)sy, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            OM(o)->m1CC = (int)tmp;
                        }
                        v = OM(o)->m1D0;
                        if (v == none) {
                            OM(o)->m1D0 = sy2;
                        } else {
                            tmp = (float)v;
                            math_step_value_toward_target(&tmp, o + 0x1DC, (float)sy2, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            OM(o)->m1D0 = (int)tmp;
                        }
                        vD0.f[1] = OM(o)->m1D4;
                        vD0.f[0] = 0.0f;
                        vD0.f[2] = 0.0f;
                        euler_to_matrix(v90, &vD0);
                        FastVecScale(v90, v90, F(obj, 0xC));
                        FastVecScale(&v90[2], &v90[2], F(obj, 0xC));
                        DrawNativeQuads(obj, (float)OM(o)->m1CC, (float)label_y(o, (float)OM(o)->m1D0, g_race_hud_layout_scale, half, one2),
                                      mcol, 0.0f, v90);
                    } else {
                        OM(o)->m1D0 = none;
                        OM(o)->m1D4 = -1.0f;
                        OM(o)->m1CC = none;
                        OM(o)->m1E0 = 0;
                        OM(o)->m1D8 = 0;
                        OM(o)->m1DC = 0;
                    }
                    GetAnimationPathPoint(&sy, &sy2, I(o, 0x120), I(o, 0x124), o + 0x1C4, o + 0x1C8,
                                      p);
                    AppendScreenRectPacket(sy - 2, hud_coord_a((float)(sy2 - 1), g_race_hud_layout_scale, half, one2), sy + 2, hud_coord_a((float)(sy2 + 3), g_race_hud_layout_scale, half, one2),
                                  0x600040E4, 0);
                }
            }
            j++;
        } while (j < 0x15);
        fa = fast_subtract_rotations(f21, F(h, 0xF8));
        if (F(p, 0x4A4) == -1.0f)
            F(p, 0x4A4) = fa;
        else
            math_approach_target_with_direction_mode(p + 0x4A4, fa, 0.002327106f, 0.002327106f, 4.712389f, p + 0x4B0, 0);
        I(p, 0x49C) = 0x183;
        v3 = I(p, 0x4A0);
        if (v3 == -1) {
            I(p, 0x4A0) = sy3;
        } else {
            tmp = (float)v3;
            math_step_value_toward_target(&tmp, p + 0x4AC, (float)sy3, 0.1388889f, 0.1388889f, 5.8333335f);
            I(p, 0x4A0) = (int)tmp;
        }
        vD0.f[1] = F(p, 0x4A4);
        vD0.f[0] = 0.0f;
        vD0.f[2] = 0.0f;
        euler_to_matrix(m, &vD0);
        FastVecScale(m, m, F(obj, 0xC));
        FastVecScale(m2, m2, F(obj, 0xC));
        DrawNativeQuads(obj, (float)I(p, 0x49C), (float)label_y(obj, (float)I(p, 0x4A0), g_race_hud_layout_scale, 0.5f, 1), 0x8000A6E4, 0.0f, m);
        GetAnimationPathPoint(&sy, &sy2, I(p, 0x314), I(p, 0x318), pa, pb, p);
        AppendScreenRectPacket(sy, HC((float)sy2), sy + 4, HC((float)(sy2 + 4)), 0x8000A6E4, 0);
        VU1_addGSregister(0x47, 0x5360B);
        if (h[0x20] != 3) {
            fe = F(p, 0x28C) * 0.008726647f;
            { float q = math_fast_sin_or_cos_b(fe) / math_fast_sin_or_cos_a(fe); u8 *cam = g_water_camera; F(cam, 0xB0) = q; }
            UpdateViewContext();
        }
    }
    return 1;
}
