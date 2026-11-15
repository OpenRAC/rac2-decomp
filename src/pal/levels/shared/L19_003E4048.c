/* func_PAL_L19_003E4048, the PAL copy of func_L19_003DFD68: the same C, where the per-frame speeds
   and steps take their 50 Hz values, and the hit timer and the first timer limit scale by 5/6.
   The second limit, D_L19_001B0BE0, scales only as a divisor: its end-of-state tests stay as in USA. */
/* Per-frame update of the grelbin-style effect moby (L19 + L20): a seven-state switch that
   blends the instance's colors and vectors from the state timer, steps the timer, and
   handles the hero hit loop and the sound slots. Needs -g and -ffast-math (min/max). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* the frame counter of the effect moby, a u16 at +0x96 */
static inline u16 moby_timer(char *m)
{
    return *(u16 *)(m + 0x96);
}

/* the moby's per-instance variables (m + 0x68) */
typedef struct {
    u8 pad0[8];
    s32 i8;
    u8 padC[0x14];
    f32 v20[4][4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    f32 v90[4];
    f32 vA0[4];
    s32 iB0;
    s32 iB4;
    s32 iB8;
    s32 iBC;
    f32 fC0;
    s32 iC4;
    s32 iC8;
    s32 iCC;
    f32 fD0;
    s32 iD4;
    f32 fD8;
    f32 fDC;
    s32 iE0;
    s32 iE4;
} PvVars;

/* one 0x100-byte record of the level's moby-class table at D_L19_001B2A1C */
typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    u8 pad20[3];
    u8 b23;
    u8 pad24[0x10];
    u16 h34;
    u8 pad36[0x62];
    s32 i98;
    u8 pad9C[0x24];
    f32 mat[4][4];
} ClassRec;

extern char g_hero_state[];
extern u8 g_sound_state[];
extern int D_001A7A00[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char D_L19_001B9A40[];
extern char *D_L19_001FE700[];
extern ClassRec *g_moby_l19_array[] __attribute__((sda));
extern char *D_L19_001C3F00[];
extern f32 D_L19_001B0C1C[] __attribute__((sda));
extern f32 D_L19_001B0C20[] __attribute__((sda));
extern f32 D_L19_001B0B50 __attribute__((sda));
extern f32 D_L19_001B0B54 __attribute__((sda));
extern f32 D_L19_001B0B60[4] __attribute__((sda));
extern f32 D_L19_001B0B70 __attribute__((sda));
extern f32 D_L19_001B0B74 __attribute__((sda));
extern f32 D_L19_001B0B78 __attribute__((sda));
extern int D_L19_001B0B7C __attribute__((sda));
extern f32 D_L19_001B0B90[4] __attribute__((sda));
extern int D_L19_001B0BA0 __attribute__((sda));
extern f32 D_L19_001B0BA4 __attribute__((sda));
extern f32 D_L19_001B0BA8 __attribute__((sda));
extern f32 D_L19_001B0BAC __attribute__((sda));
extern f32 D_L19_001B0BB0 __attribute__((sda));
extern f32 D_L19_001B0BB4 __attribute__((sda));
extern f32 D_L19_001B0BB8 __attribute__((sda));
extern f32 D_L19_001B0BC0[2] __attribute__((sda));
extern f32 D_L19_001B0BC8[2] __attribute__((sda));
extern f32 D_L19_001B0BD0 __attribute__((sda));
extern f32 D_L19_001B0BD8[2] __attribute__((sda));
extern f32 D_L19_001B0BE0 __attribute__((sda));
extern f32 D_L19_001B0BF0[4] __attribute__((sda));
extern f32 D_L19_001B0C00[4] __attribute__((sda));
extern f32 D_L19_001B0C18 __attribute__((sda));
extern int D_L19_001B0C28[] __attribute__((sda));
extern int g_frame_l19_counter __attribute__((sda));
extern char D_L19_003E1C98[];
extern char D_L19_003E10A0[];
extern char D_L19_003E1D98[];

extern int coll_process_hit(float, void *, int, void *, void *);
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void mat_fast_helper_c(float *, float *);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void part_queue_impact_effect(void *, void *, int, void *, void *, float);
extern int IsPointInCuboid(void *, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int flag_set_first_pending(char *);
extern void func_PAL_002BEF58(void *, void *, int, float);
extern void path_sample_position(char *, int, void *, void *, int, float);
extern void snd_stop_voice(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_L00_002B3000(void);
extern void gfx_add_draw_callback_first(void *, void *);
extern int coll_point_inside_region(void *, int);
extern void gfx_queue_draw_callback(void *, void *);
extern void protopet_start_enter_anim(char *, int);
extern void func_PAL_L18_00400ED0(char *);
extern void func_PAL_L18_00400FF8(char *);
extern void func_PAL_L19_002C45D0(int, int);

void func_PAL_L19_003E4048(char *m)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 vm[3][4] __attribute__((aligned(16)));
    PvVars *pv;
    char *path;
    char *rec;
    ClassRec *tbl;
    ClassRec *tbl2;
    char *src;
    char *snd;
    char *t;
    int n;
    int i;
    int k;
    int cls;
    int st;
    int j;
    float f;
    float g;
    float r;

    pv = *(PvVars **)(m + 0x68);
    qcopy(pos, m + 0x10);
    qcopy(rot, m + 0xF0);
    if (pv->iD4 != -1 && coll_point_inside_region(D_L19_001B9A40, pv->iD4) != 0) {
        protopet_start_enter_anim(m, 0);
    }
    if (pv->iE0 > 0) {
        math_fast_float_d(&pv->iE0);
        if (pv->iE0 < 2) {
            func_PAL_L00_002B3000();
        }
    }
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        qcopy(pv->v60, m + 0x10);
        qcopy(pv->v70, m + 0xF0);
        if (pv->iB0 != -1) {
            pv->fD8 = 0.0f;
            path = D_L19_001FE700[pv->iB0];
            r = 1.0f / fast_vec_dist(path + 0x10, path + 0x20);
            pv->fDC = r * (0.020000001f * pv->fD0);
            qcopy(m + 0x10, path + 0x10);
            pv->iE0 = -1;
        }
        if (*(s16 *)(m + 0xAA) != 0xD9B && *(s16 *)(m + 0xAA) != 0x11CF) {
            pv->i8 = 0;
        }
        if (pv->iC8 != -1) {
            FastVecSub(pv->vA0, m + 0x10, g_moby_l19_array[0][pv->iC8].pos);
            mat_fast_helper_c(vm[0], (float *)g_moby_l19_array[0][pv->iC8].mat);
            matrix_mul_vec3(pv->vA0, pv->vA0, vm[0]);
        }
        if (pv->iB4 != -1) {
            *(u16 *)(m + 0x34) |= 1;
            moby_set_state(m, 4, -1);
        } else {
            moby_set_state(m, 1, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(m) != 0) {
            *(u16 *)(m + 0x34) |= 1;
        }
        if (IsPointInCuboid(g_hero_state + 0x80, pv->iB4) != 0) {
            if (pv->iC8 == -1) {
                *(u16 *)(m + 0x34) |= 0x100;
                vec_scale_to_length(m + 0xC0, m + 0xC0, 0.03234f);
                moby_set_state(m, 7, -1);
            } else {
                moby_set_state(m, 1, -1);
            }
        }
        break;
    case 1:
        if (flag_set_first_pending(m) != 0) {
            vec_scale_to_length(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
        }
        if (pv->iB0 != -1) {
            path_sample_position(D_L19_001FE700[pv->iB0], 0, m + 0x10, m + 0xF0, 0, pv->fD8);
            pv->fD8 = pv->fD8 + pv->fDC;
        } else {
            if (pv->iC8 != -1) {
                tbl = g_moby_l19_array[0];
                *(u16 *)(m + 0x34) = tbl[pv->iC8].h34;
                *(u8 *)(m + 0x23) = tbl[pv->iC8].b23;
                tbl2 = g_moby_l19_array[0];
                *(u16 *)(m + 0x34) = tbl2[pv->iC8].h34;
                *(int *)(m + 0x98) = tbl2[pv->iC8].i98;
                cls = pv->iC8;
                for (k = 0; k < 4; k++) {
                    qcopy(m + 0xC0 + k * 16, tbl2[cls].mat[k]);
                }
                matrix_mul_vec3(vm[0], pv->vA0, m + 0xC0);
                FastVecAdd(m + 0x10, vm[0], g_moby_l19_array[0][pv->iC8].pos);
            } else {
                FastVecAdd(m + 0x10, m + 0x10, pv->v80);
            }
            if (pv->iE4 == -1
                || *(char **)((snd = (char *)g_sound_state + pv->iE4 * 0x70) + 0x88) != m
                || *(u8 *)(snd + 0x74) == 0) {
                pv->iE4 = snd_play_from_class_bank(0, 4, m, 0xD5C);
            }
            if (pv->iB8 != -1 && pv->iC8 == -1 && IsPointInCuboid(m + 0x10, pv->iB8) != 0) {
                if (pv->iE4 != -1) {
                    snd = (char *)g_sound_state + pv->iE4 * 0x70;
                    if (*(char **)(snd + 0x88) == m && *(u8 *)(snd + 0x74) != 0) {
                        snd_stop_voice(pv->iE4);
                    }
                }
                pv->iE4 = -1;
                if (*(s16 *)(m + 0xAA) == 0xD9B || *(s16 *)(m + 0xAA) == 0x11CF) {
                    moby_set_state(m, 5, -1);
                } else {
                    moby_set_state(m, 6, -1);
                }
            }
        }
        if (*(s16 *)(m + 0xAA) == 0xD9B) {
            matrix_mul_vec3(vm[0], D_L19_001B0B60, m + 0xC0);
            FastVecAdd(vm[0], vm[0], m + 0x10);
            n = coll_process_hit(D_L19_001B0B70, vm[0], 0, m, 0);
            if (n != 0) {
                for (j = 0; j < n; j++) {
                    t = D_L19_001C3F00[j];
                    if (t == ((Hero *)g_hero_state)->ptr[0x2290 / 4]) {
                        FastVecScale(vm[1], m + 0xC0, -D_L19_001B0B78);
                        vm[1][2] = D_L19_001B0B78 * 4.0f;
                        vm[1][3] = 5627.9248f;
                        func_PAL_L19_002C45D0(0, 1);
                        g = (f32)D_001A7A00[0] * 30.0f;
                        part_queue_impact_effect(t, m, 0x10001, g_hero_state + 0x80, vm[1], g > 100.0f ? g : 100.0f);
                        pv->iE0 = (D_L19_001B0B7C * 5 + 2) / 6;
                        func_PAL_L00_003FB330(g_hero_state + 0x80, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                    } else {
                        FastVecScale(vm[1], m + 0xC0, D_L19_001B0B74);
                        vm[1][3] = 5627.9248f;
                        vm[1][2] = D_L19_001B0B74 * 4.0f;
                        part_queue_impact_effect(t, m, 0x10001, t + 0x10, vm[1], 50.0f);
                    }
                }
            }
            func_PAL_L18_00400ED0(m);
            if (*(u8 *)(m + 0x31) != 0 && (g_frame_l19_counter & 0xF) == (((int)m >> 8) & 0xF)) {
                for (i = 0; i < D_L19_001B0BA0; i++) {
                    matrix_mul_vec3(vm[1], D_L19_001B0B90, m + 0xC0);
                    FastVecAdd(vm[1], vm[1], m + 0x10);
                    f = math_random_float_range(D_L19_001B0BAC, D_L19_001B0BB0) * 0.020000001f;
                    vec_scale_to_length(vm[2], m + 0xD0, math_random_int_below(2) != 0 ? -f : f);
                    vm[2][2] = math_random_float_range(-0.10000001f, 0.020000001f);
                    vm[2][3] = -0.012f;
                    func_PAL_002BEF58(vm[1], vm[2], 0, math_random_float_range(D_L19_001B0BA4, D_L19_001B0BA8));
                }
            }
        }
        break;
    case 5:
        flag_set_first_pending(m);
        r = D_L19_001B0B54 * 0.0003490659f;
        pv->v80[2] = pv->v80[2] - D_L19_001B0B50 * 0.00040000002f;
        *(f32 *)(m + 0xF4) = FastAddRotations(*(f32 *)(m + 0xF4), r);
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 6:
        if (flag_set_first_pending(m) != 0) {
            *(u8 *)(m + 0xBC) = 0;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) |= 0x100;
            pv->fC0 = D_L19_001B0C18;
            matrix_mul_vec3(pv->v90, D_L19_001B0BF0, m + 0xC0);
            FastVecAdd(pv->v90, m + 0x10, pv->v90);
            vec_scale_to_length(pv->v80, m + 0xC0, D_L19_001B0BB4 * 0.020000001f);
            *(u16 *)(m + 0x34) |= 8;
            snd_play_from_class_bank(1, 0, m, 0xD5C);
            if (*(u8 *)(m + 0x31) != 0) {
                func_PAL_L18_00400FF8(m);
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            FastVecScale(m + 0xC0, m + 0xC0, D_L19_001B0BC8[g_is_pal_video[0] != 0] * 0.020000001f + 1.0f);
            pv->fC0 = D_L19_001B0C18 + (D_L19_001B0C1C[0] - D_L19_001B0C18) * (IntToFloat(moby_timer(m)) / ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f), D_L19_001B0C28[0], D_L19_001B0C28[1]);
            if ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f < (f32)moby_timer(m)) {
                *(u8 *)(m + 0xBC) = 1;
                vec_scale_to_length(pv->v80, m + 0xC0, D_L19_001B0BB8 * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 1) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f - D_L19_001B0BD8[g_is_pal_video[0] != 0] * 0.020000001f);
            pv->fC0 = D_L19_001B0C1C[0] + (D_L19_001B0C20[0] - D_L19_001B0C1C[0]) * (IntToFloat(moby_timer(m)) / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f), D_L19_001B0C28[1], D_L19_001B0C28[2]);
            *(u8 *)(m + 0x23) = FloatToInt((1.0f - IntToFloat(moby_timer(m)) / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f)) * 128.0f);
            if (D_L19_001B0BE0 < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                if (pv->iBC != 0) {
                    pv->fD8 = 0.0f;
                    qcopy(m + 0x10, pv->v60);
                    qcopy(m + 0xF0, pv->v70);
                    moby_set_state(m, 7, -1);
                } else {
                    *(u16 *)(m + 0x34) &= ~0x100;
                    protopet_start_enter_anim(m, 1);
                }
            }
        }
        if (*(u8 *)(m + 0x31) != 0) {
            gfx_queue_draw_callback(D_L19_003E1C98, m);
            gfx_queue_draw_callback(D_L19_003E10A0, m);
            gfx_add_draw_callback_first(D_L19_003E1D98, m);
        }
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 7:
        if (flag_set_first_pending(m) != 0) {
            *(u8 *)(m + 0xBC) = 1;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & ~1) | 0x100;
            pv->fC0 = D_L19_001B0C18;
            *(u8 *)(m + 0x23) = 0;
            for (i = 0; i < 3; i++) {
                vec_scale_to_length(vm[i], m + 0xC0 + i * 0x10, 1.0f);
            }
            matrix_mul_vec3(pv->v90, D_L19_001B0C00, vm[0]);
            FastVecScale(pv->v90, pv->v90, IntToFloat(pv->iCC) + 1.0f);
            FastVecAdd(pv->v90, m + 0x10, pv->v90);
            vec_scale_to_length(pv->v80, m + 0xC0, (IntToFloat(pv->iCC) + 1.0f) * (0.020000001f * D_L19_001B0BC0[g_is_pal_video[0] != 0]));
            *(u16 *)(m + 0x34) |= 8;
            if (*(u8 *)(m + 0x31) != 0) {
                func_PAL_L18_00400FF8(m);
            }
            snd_play_from_class_bank(1, 0, m, 0xD5C);
        } else if (*(u8 *)(m + 0xBC) == 1) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f / (1.0f - D_L19_001B0BD8[g_is_pal_video[0] != 0] * 0.020000001f));
            pv->fC0 = D_L19_001B0C20[0] + (D_L19_001B0C1C[0] - D_L19_001B0C20[0]) * (IntToFloat(moby_timer(m)) / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f), D_L19_001B0C28[2], D_L19_001B0C28[1]);
            *(u8 *)(m + 0x23) = FloatToInt(IntToFloat(moby_timer(m)) * 128.0f / ((D_L19_001B0BE0 * 5.0f + 2.0f) / 6.0f));
            if (D_L19_001B0BE0 < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                *(u8 *)(m + 0x23) = 0x80;
                *(u8 *)(m + 0xBC) = 0;
                *(u16 *)(m + 0x34) &= ~8;
                vec_scale_to_length(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f / (D_L19_001B0BC8[g_is_pal_video[0] != 0] * 0.020000001f + 1.0f));
            pv->fC0 = D_L19_001B0C1C[0] + (D_L19_001B0C18 - D_L19_001B0C1C[0]) * (IntToFloat(moby_timer(m)) / ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f), D_L19_001B0C28[1], D_L19_001B0C28[0]);
            if ((D_L19_001B0BD0 * 5.0f + 2.0f) / 6.0f < (f32)moby_timer(m)) {
                *(u16 *)(m + 0x34) &= ~0x100;
                moby_set_state(m, 1, -1);
            }
        }
        if (pv->iE4 == -1
            || *(char **)((snd = (char *)g_sound_state + pv->iE4 * 0x70) + 0x88) != m
            || *(u8 *)(snd + 0x74) == 0) {
            pv->iE4 = snd_play_from_class_bank(0, 4, m, 0xD5C);
        }
        if (*(u8 *)(m + 0x31) != 0) {
            gfx_queue_draw_callback(D_L19_003E1C98, m);
            gfx_queue_draw_callback(D_L19_003E10A0, m);
            gfx_add_draw_callback_first(D_L19_003E1D98, m);
        }
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 2:
        if (pv->iD4 != -1 && coll_point_inside_region(D_L19_001B9A40, pv->iD4) == 0) {
            rec = *(char **)(m + 0x24);
            st = *(u8 *)(m + 0x94);
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(u8 *)(m + 0x20) = st;
        }
        break;
    }
    FastVecSub(vm[0], m + 0x10, pos);
    mat_combine_and_store(pv->v20, vm[0], rot, m + 0xF0);
    if (*(f32 *)(m + 0x18) < 85.0f && *(u8 *)(m + 0x20) == 5) {
        func_PAL_L00_003FB330(m + 0x10, 0, 5, 0, 5, 0x14, 0, 0, 4.0f, 0.0f, 1, 0, 0, 0);
        protopet_start_enter_anim(m, 1);
    }
    if (moby_timer(m) < 0xFFFF) {
        *(u16 *)(m + 0x96) = moby_timer(m) + 1;
    }
    
}
