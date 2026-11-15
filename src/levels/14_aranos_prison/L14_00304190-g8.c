#include "common.h"
#include "include_asm.h"

extern int g_current_map_index;

extern int D_001A72E0;

extern int D_L14_001B23D0 __attribute__((sda));

extern char *g_moby_l14_pool __attribute__((sda));

extern char D_L14_00284690[];

extern void func_367708();

extern void func_3674A0();

extern void func_367778();

extern void func_385CB8(unsigned int reg, unsigned long value);

extern void level_init_record_table();

extern void func_2F5CC0(void *dst, void *src, float s);

extern void func_2F5C38(void *dst, void *src, void *src2);

extern void func_420B10();

extern void func_321F58();

extern void func_3DFA10();

extern int flag_is_third_pending_set();

extern int func_3322A0();

extern void func_369AD0();

extern void func_2F5C10();

extern void func_2F5C38(void *dst, void *src, void *src2);

extern void func_2F5D68(void *dst, void *src, void *mtx);

extern void func_2F5F18(void *dst, void *src, float s);

extern float func_2F6C80(float a, float b);

extern float func_2F5B78(float a);

extern void func_317D90();

extern void func_2EE5F0();

extern void gfx_draw_flipbook_billboard();

extern int D_L14_001B092C __attribute__((sda));

extern float math_random_signed_float_range(float a0, float a1);

extern int FloatToInt(float f);

extern long long GetEffectTextureDescriptor(int a);

extern void euler_to_matrix(void *dst, void *src);

extern void FastVecScale(void *dst, void *src, float s);

extern void draw_world_quad(void *dst, void *src, int c);

extern void coll_reset_box_record(char *a);

extern float D_L14_001B0388 __attribute__((sda));

extern float D_L14_001B038C __attribute__((sda));

extern float D_L14_001B0390 __attribute__((sda));

/* This unit is built with -G8: these two bodies reach a global through $gp. */

/* Sets up the level's scene at load time and starts the sound and graphics registers. */
void level_init_scene(void) {
    func_367708();
    D_L14_001B23D0 = (int)D_L14_00284690;
    if (g_current_map_index == 0xE) {
        level_init_record_table();
    } else {
        func_3674A0();
    }
    func_367778();
    func_385CB8(0x47, 0x5360B);
    func_385CB8(0x4E, 0x1000000 | (D_001A72E0 >> 13));
}

extern char g_hero_position[];
extern unsigned char g_sound_state[];
extern void moby_set_state(void *, int, int);
extern void FastVecSub(void *dst, void *a, void *b);
extern float FastVecLength(void *);
extern void FastVecCross(void *dst, void *a, void *b);
extern int moby_count_used_child_slots(char *);
extern int flag_set_first_pending(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_wake_children(char *);
extern int math_fast_float_d(int *);
extern int hero_is_current_selected_id(void *);
extern float fast_vec_dist(void *, void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void moby_place_from_group_matrices(char *, float);
extern void moby_clear_dead_linked(char *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Updates moby class 2788 (no label yet): a door-like part that swings between two positions. */
/* A two-position mover. State 0 stores its two end points (which one is the current
   position depends on word 0x70) and each linked entity's distance to them; state 1 waits on
   func_002ACBC8; states 3 and 4 re-arm the timer at 0x8C and, once func_L00_00324120 says so
   or the player has moved to the other side of the object, start the turn (states 5 and 6),
   which steps func_L14_003DE360 until the angle at 0x80 reaches 0 or pi/2 and then stops the
   object's sound. */
void swinging_mover_update(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    char **ent;
    float *dist;
    int i;
    float distance;
    int side;
    unsigned char *sound;

    qcopy(pos, self + 0x10);
    qcopy(rot, self + 0xF0);

    switch ((unsigned char)self[0x20]) {
    case 0:
        *(unsigned short *)(self + 0x34) |= 0x100;
        *(float *)(vars + 0x7C) = 0.0087266471f;
        *(int *)(vars + 0x78) = -1;
        *(int *)(vars + 0x5C) |= 1;
        if (*(int *)(vars + 0x70) != 0) {
            qcopy(vars + 0x90, self + 0x10);
            qcopy(vars + 0xA0, vars + 0x60);
            *(float *)(vars + 0x80) = 1.5707964f;
            moby_set_state(self, 4, -1);
        } else {
            qcopy(vars + 0xA0, self + 0x10);
            qcopy(vars + 0x90, vars + 0x60);
            *(float *)(vars + 0x80) = 0.0f;
            moby_set_state(self, 3, -1);
        }
        qcopy(vars + 0xB0, vars + 0xA0);
        *(float *)(vars + 0xB8) = *(float *)(vars + 0x98);
        FastVecSub(d1, vars + 0xA0, vars + 0xB0);
        *(float *)(vars + 0x84) = FastVecLength(d1);
        FastVecSub(d2, vars + 0x90, vars + 0xB0);
        *(float *)(vars + 0x88) = FastVecLength(d2);
        FastVecCross(vars + 0xC0, d2, d1);
        ent = (char **)(vars + 0xE0);
        dist = (float *)(vars + 0xF0);
        /* The four linked-entity ids are the words at st+0xD0, just before the distances at
           st+0xF0, so each one is read eight words back from its distance. */
        for (i = 3; i >= 0; i--) {
            if (*(int *)(dist - 8) > 0) {
                *ent = g_moby_l14_pool + (*(int *)(dist - 8) << 8);
                FastVecSub(d1, *ent + 0x10, vars + 0xB0);
                distance = FastVecLength(d1);
                if ((unsigned char)self[0x20] == 4) {
                    dist[0] = distance;
                    dist[4] = *(float *)(vars + 0x84) - *(float *)(vars + 0x88) + distance;
                } else {
                    dist[4] = distance;
                    dist[0] = *(float *)(vars + 0x88) - *(float *)(vars + 0x84) + distance;
                }
            } else {
                *ent = 0;
            }
            ent++;
            dist++;
        }
        if (moby_count_used_child_slots(self) != 0 && *(int *)(vars + 0x74) >= 0) {
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        flag_set_first_pending(self);
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0x74)) != 0) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        moby_set_state(self, 3, -1);
    case 3:
    case 4:
        if (flag_set_first_pending(self) != 0) {
            moby_wake_children(self);
            *(int *)(vars + 0x8C) = 100;
        }
        math_fast_float_d((int *)(vars + 0x8C));
        if (hero_is_current_selected_id(self) == 0) {
            if (!(fast_vec_dist(g_hero_position, self + 0x10) < 30.0f)) {
                break;
            }
            /* Which end the player is nearer; the object's own nearer end must differ. */
            side = fast_vec_dist(g_hero_position, vars + 0x90) > fast_vec_dist(g_hero_position, vars + 0xA0);
            if ((side ^ (fast_vec_dist(self + 0x10, vars + 0x90) > fast_vec_dist(self + 0x10, vars + 0xA0))) == 0) {
                break;
            }
        }
        if (moby_count_used_child_slots(self) == 0 && *(int *)(vars + 0x8C) <= 0) {
            if ((unsigned char)self[0x20] == 4) {
                moby_set_state(self, 5, -1);
            } else {
                moby_set_state(self, 6, -1);
            }
        }
        break;
    case 5:
        if (flag_set_first_pending(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) > 0.0f) {
            moby_place_from_group_matrices(self, -*(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = g_sound_state + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        snd_stop_voice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (hero_is_current_selected_id(self) == 0) {
                moby_set_state(self, 3, -1);
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) < 1.5707964f) {
            moby_place_from_group_matrices(self, *(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = g_sound_state + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        snd_stop_voice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (hero_is_current_selected_id(self) == 0) {
                moby_set_state(self, 4, -1);
            }
        }
        break;
    }
    moby_clear_dead_linked(self);
    FastVecSub(delta, self + 0x10, pos);
    mat_combine_and_store(vars + 0x20, delta, rot, self + 0xF0);
}

/* func_L14_003E5030 is matched in its own unit, src/levels/shared/L14_003E5030-g8.c (-O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */

/* Draws two lines on either side of the object, along its facing direction. */
void gfx_draw_moby_edge_lines(char *moby, int isFirst) {
    float offsetA[4];
    float offsetB[4];
    char *vars;
    char *pos;

    vars = *(char **)(moby + 0x68);
    func_2F5CC0(offsetA, moby + 0xC0, 2.0f);
    func_2F5CC0(offsetB, moby + 0xC0, -2.0f);
    if (*(int *)(vars + 0x7C) != 0) {
        func_2F5CC0(offsetA, offsetA, -1.0f);
        func_2F5CC0(offsetB, offsetB, -1.0f);
    }
    pos = moby + 0x10;
    func_2F5C38(offsetA, offsetA, pos);
    func_2F5C38(offsetB, offsetB, pos);
    func_420B10(*(int *)(vars + 0x64), offsetA, pos, isFirst == 0);
    func_420B10(*(int *)(vars + 0x64), offsetB, pos, 0);
}

/* The id-list walks of func_L14_003DF440 and func_L14_003DF540 read D_L14_001B259C as a bare
   symbol (the second name: `sda` on an array over 8 bytes), while D_L14_001B25B8 is a plain int:
   its `.extern` comes last in the file, so the load in a branch delay slot is a $gp access and
   no other load is. */
extern unsigned short *g_group_entity_lists[];
extern int D_L14_001B25B8;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
extern void *moby_get_vars_word_18(char *a0);

/* 0 when an entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, has a linked object whose word at +0x88 is not the owner; else 1. */
int group_is_linked_to_owner(char *self) {
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    char *t;

    for (p = g_group_entity_lists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[*(int *)(state + 0x68)]);
         p++) {
        e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one range test */
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                t = moby_get_vars_word_18(e);
                if (t != 0 && *(char **)(t + 0x88) != self)
                    return 0;
            }
        }
    }
    return 1;
}

extern float math_fabs(float x);

/* 1 when an entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, is more than 1.5 away from it along the float at +0x18; else 0. */
int group_is_misaligned(char *self) {
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;

    for (p = g_group_entity_lists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[*(int *)(state + 0x68)]);
         p++) {
        e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (math_fabs(*(float *)(e + 0x18) - *(float *)(self + 0x18)) > 1.5f)
                    return 1;
            }
        }
    }
    return 0;
}

/* Moves and spins an object that flies off and is removed once it has gone far enough. */
void flying_away_update(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        func_321F58(moby, 1, -1);
        if (*(int *)(vars + 0x0) != -1) {
            func_3DFA10(moby, 0);
        }
        break;
    case 1:
        if (flag_is_third_pending_set(moby) != 0) {
            if (*(int *)(vars + 0x0) != -1) {
                func_3DFA10(moby, 1);
            }
            func_321F58(moby, 2, -1);
            {
                float s = D_L14_001B0388 * 0.016666668f;

                *(float *)(vars + 0xC) = s;
                if (*(int *)(vars + 0x8) != 0) {
                    *(float *)(vars + 0xC) = -s;
                }
            }
            *(int *)(vars + 0x10) = 0;
        }
        break;
    case 2:
        {
            float a[4];
            float b[4];

            if (func_3322A0(moby) != 0) {
                func_369AD0(0, 0, moby);
            }
            func_2F5C10(b);
            func_2F5D68(a, moby + 0xC0, b);
            func_2F5F18(a, a, *(float *)(vars + 0xC));
            func_2F5C38(moby + 0x10, moby + 0x10, a);
            {
                float old = *(float *)(vars + 0xC);
                float m;

                *(float *)(vars + 0x10) = *(float *)(vars + 0x10) + old;
                if (*(int *)(vars + 0x8) != 0) {
                    m = old - D_L14_001B038C * 0.00027777778f;
                } else {
                    m = old + D_L14_001B038C * 0.00027777778f;
                }
                {
                    float x = m * D_L14_001B0390;

                    *(float *)(vars + 0xC) = m;
                    *(float *)(moby + 0xF0) = func_2F6C80(*(float *)(moby + 0xF0), x);
                }
            }
            if (func_2F5B78(*(float *)(vars + 0x10)) > 4.0f) {
                func_317D90(moby);
                return;
            }
        }
        break;
    }
    if (*(unsigned char *)(moby + 0x31) != 0 && *(int *)(vars + 0x4) != -1) {
        func_2EE5F0(gfx_draw_flipbook_billboard, moby);
    }
}

/* The record func_L14_003F0E98 resets: four vertices, four words, eight floats,
   then three 64-bit fields. */
typedef struct {
    struct {
        int id;
        float x;
        float y;
        float z;
    } v[4];
    int p[4];
    float f[8];
    long long q;
    long long r;
    long long s;
} L14_003F0F38_rec;

/* The record, a 64-bit word, a matrix, a vector and a direction. */
typedef struct {
    L14_003F0F38_rec rec;
    long long t;
    float mat[12];
    float vec[4];
    float dir[4];
} L14_003F0F38_frame;

/* The caller supplies an unused scale in F12; the body replaces it before use. */
/* Builds two ribbon-like quads at the object with random fading colours and draws them. */
void gfx_draw_fading_quads(char *moby, char *target, float unused_scale, int colorBase, int fadeA, int fadeB) {
    L14_003F0F38_frame fr;
    char *vars;
    long long id;
    long long sv;
    long long tw;
    long long tv;

    vars = *(char **)(moby + 0x68);

    fadeA = fadeA - ((int)FloatToInt(math_random_signed_float_range(0.0f, 5.0f)) << 24);
    coll_reset_box_record(&fr.rec);

    fr.rec.f[0] = *(float *)vars;
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)vars;
    fr.rec.f[3] = 1.0f;
    fr.rec.f[4] = *(float *)vars + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)vars + 1.0f;
    fr.rec.f[7] = 1.0f;

    id = GetEffectTextureDescriptor(D_L14_001B092C);
    fr.rec.r = id;
    fr.rec.s = 280993940374112LL;
    fr.t = 0x8000000048LL;
    fr.rec.p[0] = colorBase + fadeA;
    fr.rec.q = 0LL;

    fadeA = fadeA - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = colorBase + fadeA;
    fadeA = fadeA - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = colorBase + fadeA;
    fadeA = fadeA - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = colorBase + fadeA;

    fr.dir[2] = *(float *)(moby + 0xF8);
    fr.dir[1] = *(float *)(moby + 0xF4);
    fr.dir[0] = 1.5707965f;
    fr.dir[3] = 0.0f;
    euler_to_matrix(fr.mat, fr.dir);

    fr.vec[0] = *(float *)target;
    fr.vec[1] = *(float *)(target + 4);
    fr.vec[2] = *(float *)(target + 8);
    fr.vec[3] = 1.0f;
    FastVecScale(&fr.rec.v[0], &fr.rec.v[0], 1.0f);
    FastVecScale(&fr.rec.v[1], &fr.rec.v[1], 1.0f);
    FastVecScale(&fr.rec.v[2], &fr.rec.v[2], 1.0f);
    FastVecScale(&fr.rec.v[3], &fr.rec.v[3], 1.0f);
    draw_world_quad(&fr.rec, fr.mat, 0);

    tv = 0x8000000044LL;
    fr.rec.f[0] = *(float *)(vars + 8);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(vars + 8);
    fr.rec.f[3] = 1.0f;
    fr.t = tv;
    fadeB = fadeB - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[0] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(math_random_signed_float_range(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = colorBase + fadeB;
    fr.rec.f[4] = *(float *)(vars + 8) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(vars + 8) + 1.0f;
    fr.rec.f[7] = 1.0f;
    draw_world_quad(&fr.rec, fr.mat, 0);
}

extern float D_L14_001B04B0 __attribute__((sda));
extern float D_L14_001B04B4 __attribute__((sda));
extern float D_L14_001B04B8 __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void gfx_world_to_screen_unit(void *, float *, float *);
extern float math_fast_sin_or_cos_b(float);
extern float moby_get_state_progress(char *);
extern float math_wrap_angle_two_pi(float);

/* The caller fills four vertices (indices 0..3), colors at +0x40,
 * and four UV pairs at +0x50 in its quad packet. */
typedef struct {
    float rows[4][4];
    unsigned int colors[4];
    float pairs[4][2];
} L14Swing;

/* Works out one corner of a wobbling quad: its position and clamped texture coordinates. */
void gfx_calc_wobble_quad_corner(char *object, L14Swing *base, int index, float *a, float *b, float *c,
                       int phase0, int phase1)
{
    float v[4];

    FastVecScale(v, b, (float)phase1 * 0.125f);
    FastVecAdd(base->rows[index], a, v);
    FastVecScale(v, c, (float)phase0 * 0.125f);
    FastVecAdd(base->rows[index], base->rows[index], v);
    gfx_world_to_screen_unit(base->rows[index], &base->pairs[index][0], &base->pairs[index][1]);
    base->pairs[index][0] += (1.0f - moby_get_state_progress(object)) * D_L14_001B04B0
        * math_fast_sin_or_cos_b(math_wrap_angle_two_pi((D_L14_001B04B4 + D_L14_001B04B4) * (moby_get_state_progress(object) * 3.1415927f)
                                          + (float)phase0 * 3.1415927f / D_L14_001B04B8));
    base->pairs[index][1] += (1.0f - moby_get_state_progress(object)) * D_L14_001B04B0
        * math_fast_sin_or_cos_b(math_wrap_angle_two_pi((D_L14_001B04B4 + D_L14_001B04B4) * (moby_get_state_progress(object) * 3.1415927f)
                                          + (float)phase1 * 3.1415927f / D_L14_001B04B8));
    if (1.0f < base->pairs[index][0])
        base->pairs[index][0] = 1.0f;
    else if (base->pairs[index][0] < 0.0f)
        base->pairs[index][0] = 0.0f;
    if (1.0f < base->pairs[index][1])
        base->pairs[index][1] = 1.0f;
    else if (base->pairs[index][1] < 0.0f)
        base->pairs[index][1] = 0.0f;
}

extern float D_L14_001B04BC __attribute__((sda));
extern s32 D_L14_001B04D4 __attribute__((sda));
extern float D_L14_001B04D8 __attribute__((sda));
extern float D_L14_001B04DC __attribute__((sda));
extern s32 D_L14_001B04E0 __attribute__((sda));
extern s32 D_L14_001B04E4 __attribute__((sda));
extern s32 D_L14_001B04E8 __attribute__((sda));
extern s32 D_L14_001B04EC __attribute__((sda));
extern s32 D_L14_001B04F0 __attribute__((sda));
extern float D_L14_001B04F4 __attribute__((sda));
extern char D_L14_001A8F20[] MACRO_ADDR;

extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern char *part_spawn_size_changing(char *pos, char *vel, int life, int color, int speed, int alpha, int endAlpha,
                           float size, float endSize, float gravity, int kind);

/* Spawns a flash particle: jitters the position at random within the object's scaled radius, blends a
   random opaque colour toward the record's colour (rec+0x84) by the object's fade factor, and spawns it
   with a random life and speed. */
void part_l14_spawn_flash(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char *rec = *(char **)(obj + 0x68);
    int argb, color, life, red, green, blue;

    qcopy(pos, obj + 0x10);
    pos[0] += math_random_float_range(D_L14_001B04BC * -moby_get_state_progress(obj), D_L14_001B04BC * moby_get_state_progress(obj));
    pos[1] += math_random_float_range(D_L14_001B04BC * -moby_get_state_progress(obj), D_L14_001B04BC * moby_get_state_progress(obj));
    pos[2] += math_random_float_range(D_L14_001B04BC * -moby_get_state_progress(obj), 0.0f);
    qcopy(vel, D_L14_001A8F20);
    red = math_random_int_range(0, D_L14_001B04EC);
    green = math_random_int_range(0, D_L14_001B04E8);
    blue = math_random_int_range(0, D_L14_001B04E4);
    argb = 0xFF000000 | (green << 8);
    color = FastTweenColor((red << 16) | argb | blue, *(int *)(rec + 0x84), moby_get_state_progress(obj));
    life = math_random_int_range(D_L14_001B04D4 / 2, D_L14_001B04D4);
    part_spawn_size_changing((char *)pos, (char *)vel, life, color, math_random_int_range(0, D_L14_001B04E0), 0x80, 0,
                  D_L14_001B04D8, D_L14_001B04DC, D_L14_001B04F4, D_L14_001B04F0);
}
