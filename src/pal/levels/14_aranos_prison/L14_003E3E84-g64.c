#include "common.h"

/* func_PAL_L14_003E3E84, the PAL copy of func_L00_003D1D28: the same C, with its frame counts at 50 Hz. */

typedef int TI128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Mat3[12] __attribute__((aligned(16)));
typedef float Mat4[16] __attribute__((aligned(16)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    float timer;          /* 0x00 */
    s16 t4;               /* 0x04 */
    s16 t6;               /* 0x06 */
    s16 t8;               /* 0x08 */
    s16 tA;               /* 0x0A */
    float fC;             /* 0x0C */
    Vec4 v10; /* 0x10 */
    float f20;            /* 0x20 */
    float f24;            /* 0x24 */
    int t28;              /* 0x28 */
    float f2C;            /* 0x2C */
    Vec4 q30; /* 0x30 */
    int t40;              /* 0x40 */
    int t44;              /* 0x44 */
    float f48;            /* 0x48 */
    int t4C;              /* 0x4C */
    int handle;           /* 0x50 */
} TurretState;

typedef struct {
    Vec4 pos;             /* 0x00: copied by the request consumer as one quadword */
    u8 *source;           /* 0x10 */
    int flags;            /* 0x14 */
    u8 b18;               /* 0x18 */
    u8 b19;               /* 0x19 */
    u16 oclass;           /* 0x1A */
    float damage;         /* 0x1C */
    int count;            /* 0x20 */
    float extra;          /* 0x24: consumed by func_002A8E20 */
} Hit;

typedef struct { u8 pad0[0x28]; int id; u8 pad2C[0x28]; float rate; u8 pad58[0x18]; float damage; u8 pad74[0x6C]; } WeaponEntry;

extern u8 g_hero_state[];
extern u8 g_pad_state[];
extern u8 g_item_slot_to_record[];
extern u8 g_hero_weapon_id_index NOT_SDA;
extern float g_strip_axis[4] NOT_SDA;
extern WeaponEntry g_weapon_l00_table[];
extern u8 g_effect_handle_records[];
extern u8 g_default_vector[] MACRO_ADDR;
typedef struct { u8 pad[0x160]; float f160; int pad164; int i168; int i16C; float f170; int pad174; int i178; } Shake;
extern Shake g_scalar_transition_state;
extern u8 *g_area_hit_targets[];
extern float g_euler_rotation_params[16] __attribute__((sda));
extern int g_effect_state_param_a __attribute__((sda));
extern int g_effect_state_param_b __attribute__((sda));
extern int g_effect_timer_limit_a __attribute__((sda));
extern int g_effect_state_param_c __attribute__((sda));
extern int g_effect_timer_limit_b __attribute__((sda));
extern float g_effect_local_pos_x __attribute__((sda));
extern float g_local_pos_y_offset __attribute__((sda));
extern float g_local_pos_z_offset __attribute__((sda));
extern int g_effect_state_param __attribute__((sda));

extern s32 FastDecTimer(s16 *);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_b(void *);
extern s32 hero_l00_set_action_pal(int, int);
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern void cancel_hero_item_animation_pal(void);
extern void start_equipped_item_animation_pal(void);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int slot_copy_records_to_free(void *);
extern void slot_reset_active(int);
extern float math_random_angle(void);
extern float IntToFloat(int);
extern int PlayMobySound(int, int, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void RenderRadialRingAndQuad_pal(u8 *);
extern void lightning_update_arcs_pal(u8 *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern u8 *part_spawn_pulled_particle(void *, int, float, float, u32, int, int, void *, int, int, int, int);
extern void InitEffectStrips_pal(u8 *, void *, int);
extern s32 coll_process_hit(f32, void *, s32, void *, s32);
extern void QueueMobyImpact(u8 *, Hit *);
extern int StartAttachedEffect_pal(u8 *, int, u8 *);
extern void euler_to_matrix(void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void moby_transform_joint_to_world(u8 *, int, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern float FastAddRotations(float, float);
extern int weapon_fire_damage_ray_pal(u8 *, void *, void *, Hit *);


static inline void SetShake(float amount)
{
    g_scalar_transition_state.f160 = amount;
    g_scalar_transition_state.i168 = (30 * 5 + 2) / 6;
    g_scalar_transition_state.f170 = amount;
    g_scalar_transition_state.i178 = (30 * 5 + 2) / 6;
    g_scalar_transition_state.i16C = 0;
}

/* Per-frame update of the spread-shot weapon (PAL copy of UpdateSpreadWeapon, 50 Hz timings): charges, fires a shot and the damage rays. */
void spread_weapon_update_pal(u8 *self)
{
    Vec4 a;
    Vec4 b;
    TurretState *st = *(TurretState **)(self + 0x68);
    int ready;
    u8 *p;

    if (self[0x20] == 0) {
        self[0x20] = 1;
        st->handle = -1;
        st->t8 = 0;
        st->tA = 0;
        st->t28 = 0;
        st->t44 = 0;
        st->t4C = 0;
    }
    if (self[0x20] == 6) {
        if (FastDecTimer(&st->t4))
            self[0x20] = 1;
    }
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
        hero_l00_set_action_pal(0x1D, 1);
    vec_fast_helper_b(st);
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D) {
        u32 color;
        if (st->timer > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(self, 1.3f, color, 0, 0x21, 0.0f, -1, 90.0f, 4);
    }
    if (st->t4C != 0 && math_fast_float_d(&st->t4C))
        cancel_hero_item_animation_pal();
    if (self[0x42] == self[0x43] && (self[0x60] & 2))
        anim_start_blended_with_flags(self, 1, 0, 2, 0);
    /* moby/state and turret/shot are copies, and large and small are named constants, that gcse's cprop folds back:
     * they keep the insn count and the PRE expression numbers that give retail's spill slots at 0x23C-0x270. */
    {
        u8 *moby = self;
        TurretState *state = st;
        int large = (7 * 5 + 2) / 6;
        int small = (4 * 5 + 2) / 6;
        int delay;
        ready = 1;
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D) {
            if (math_fast_float_d(&((Hero *)g_hero_state)->i[0x2534 / 4]) == 0)
                ready = 0;
        } else {
            ((Hero *)g_hero_state)->i[0x2534 / 4] = (0x28 * 5 + 2) / 6;
        }
        if (self[0x20] == 1 && ((Hero *)g_hero_state)->b[0x22BC] == 0 && st->timer == 0.0f && ((Hero *)g_hero_state)->i[0x1240 / 4] >= (0x17 * 5 + 2) / 6 && ready) {
            if ((((Hero *)g_pad_state)->i[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) && weapon_spend_ammo(-1, 1)) {
                if (((Hero *)g_hero_state)->ptr[0x2290 / 4][0x43] == ((WeaponEntry *)((u8 *)g_weapon_l00_table + g_hero_weapon_id_index * 0xE0))->id || ((Hero *)g_hero_state)->i[0x229C / 4] != 0 || ((Hero *)g_hero_state)->h[0x24EC / 2] != 0) {
                    delay = ((s32)(g_effect_state_param_a) * 5 + 2) / 6;
                    st->t40 = 1;
                    st->t6 = delay;
                } else {
                    st->t40 = 0;
                    st->t6 = 2;
                }
                start_equipped_item_animation_pal();
                st->handle = slot_copy_records_to_free(g_effect_handle_records);
                anim_start_blended_with_flags(self, 2, 0, 2, 0);
                st->t4C = ((s32)(g_effect_state_param) * 5 + 2) / 6;
                self[0x20] = 2;
                st->fC = math_random_angle();
                st->t8 = ((s32)(g_effect_state_param_b) * 5 + 2) / 6;
                st->f20 = 1.0f / IntToFloat(st->t8);
                st->t8 += 2;
                st->tA = ((s32)(g_effect_state_param_c) * 5 + 2) / 6;
                st->f24 = 1.0f / IntToFloat(st->tA);
                st->t28 = ((s32)(g_effect_timer_limit_a) * 5 + 2) / 6;
                st->f2C = 1.0f / IntToFloat(st->t28);
                st->t44 = ((s32)(g_effect_timer_limit_b) * 5 + 2) / 6;
                st->f48 = 1.0f / IntToFloat(st->t44);
                st->t44 += 2;
            } else if (((Hero *)g_pad_state)->i[0x1A4 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) {
                PlayMobySound(5, 0, self);
            }
            if (!(((Hero *)g_pad_state)->i[0x1A0 / 4] & ((Hero *)g_hero_state)->i[0x1230 / 4]) || !get_ammo(-1) || ((Hero *)g_hero_state)->b[0x22B8] == 0) {
                if (st->handle >= 0) {
                    slot_reset_active(st->handle);
                    st->handle = -1;
                }
            }
        }
        if (st->t6 == 0) {
            FastDecTimer(&st->tA);
            FastDecTimer(&st->t8);
            math_fast_float_d(&st->t28);
            math_fast_float_d(&st->t44);
            if (st->t8 != 0 || st->tA != 0 || st->t28 != 0 || st->t44 != 0)
                gfx_add_draw_callback_third(RenderRadialRingAndQuad_pal, self);
            lightning_update_arcs_pal(self);
        }
        if (self[0x20] == 2 || self[0x20] == 3) {
            u8 *turret = moby;
            TurretState *shot = state;
            if (FastDecTimer(&shot->t6)) {
                if (turret[0x20] == 2) {
                    turret[0x20] = 3;
                    qcopy(shot->q30, g_strip_axis);
                    a[0] = g_effect_local_pos_x;
                    a[1] = g_local_pos_y_offset - 0.25f;
                    a[2] = g_local_pos_z_offset;
                    a[3] = 1.0f;
                    matrix_mul_vec3(b, a, turret + 0xC0);
                    FastVecAdd(b, b, turret + 0x10);
                    {
                        u8 *q = part_spawn_pulled_particle(b, large, 0.4f, 8.0f, 0x80FFFFFF, 2, 0, g_default_vector, 0, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    {
                        u8 *q = part_spawn_pulled_particle(b, small, 0.5f, 12.0f, 0x3CFF1010, 2, 0, g_default_vector, 3, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    {
                        u8 *q = part_spawn_pulled_particle(b, small, 0.5f, 4.0f, 0x80FFFFFF, 2, 0, g_default_vector, 3, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    a[2] = -a[2];
                    matrix_mul_vec3(b, a, turret + 0xC0);
                    FastVecAdd(b, b, turret + 0x10);
                    {
                        u8 *q = part_spawn_pulled_particle(b, large, 0.4f, 8.0f, 0x80FFFFFF, 2, 0, g_default_vector, 0, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    {
                        u8 *q = part_spawn_pulled_particle(b, small, 0.5f, 12.0f, 0x3CFF1010, 2, 0, g_default_vector, 3, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    {
                        u8 *q = part_spawn_pulled_particle(b, small, 0.5f, 4.0f, 0x80FFFFFF, 2, 0, g_default_vector, 3, 0, 6, 0);
                        if (q)
                            *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                    }
                    a[2] = 0.0f;
                    a[1] = g_local_pos_y_offset;
                    matrix_mul_vec3(b, a, turret + 0xC0);
                    FastVecAdd(shot->v10, b, turret + 0x10);
                    InitEffectStrips_pal(turret, shot->v10, 0);
                    gfx_add_draw_callback_third(RenderRadialRingAndQuad_pal, turret);
                    PlayMobySound(0, 0, turret);
                    if (shot->t40)
                        SetShake(0.12f);
                    else
                        SetShake(0.06f);
                } else {
                    Hit hit;
                    Vec4 up;
                    Vec4 side;
                    Vec4 fwd;
                    Mat3 basis;
                    Mat3 inv;
                    Mat4 mtx;
                    Vec4 origin;
                    Vec4 offs;
                    u8 *list[20];
                    int saved[20];
                    Vec4 rot;
                    Vec4 dir;
                    Vec4 from;
                    Vec4 to;
                    int count, i, n, h, k, r;
                    float angle, spread;

                    turret[0x20] = 6;
                    shot->t4 = (0x1C * 5 + 2) / 6;
                    hit.flags = 0x10000;
                    hit.count = 1;
                    hit.b18 = 3;
                    hit.b19 = 2;
                    hit.oclass = *(u16 *)(turret + 0xAA);
                    hit.damage = ((WeaponEntry *)((u8 *)g_weapon_l00_table + g_item_slot_to_record[0x1A] * 0xE0))->damage;
                    hit.source = turret;
                    FastVecScale(a, turret + 0xD0, -1.35f);
                    FastVecAdd(a, a, turret + 0x10);
                    FastVecScale(b, turret + 0xC0, 0.275f);
                    FastVecAdd(a, a, b);
                    n = coll_process_hit(1.5f, a, 1, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0);
                    for (h = 0; h < n; h++) {
                        if (g_area_hit_targets[h] != ((Hero *)g_hero_state)->ptr[0x2290 / 4]) {
                            FastVecScale(hit.pos, turret + 0xD0, -1.5f);
                            hit.pos[3] = 5627.925f;
                            QueueMobyImpact(g_area_hit_targets[h], &hit);
                            StartAttachedEffect_pal(g_area_hit_targets[h], 0x44, turret);
                        }
                    }
                    euler_to_matrix(mtx, g_euler_rotation_params);
                    copy_matrix3x4(inv, mtx);
                    moby_transform_joint_to_world(turret, 0, origin);
                    if (((Hero *)g_hero_state)->h[0x24EC / 2] == 1) {
                        FastVecScale(up, turret + 0xD0, -1.0f);
                        FastVecScale(side, turret + 0xC0, -1.0f);
                        FastVecScale(fwd, turret + 0xE0, 0.1f);
                        multiply_matrix3x3(basis, turret + 0xC0, inv);
                    } else {
                        qcopy(up, ((Hero *)g_hero_state)->b + 0x730);
                        qcopy(side, ((Hero *)g_hero_state)->b + 0x740);
                        FastVecScale(fwd, ((Hero *)g_hero_state)->b + 0x750, -0.1f);
                        multiply_matrix3x3(basis, ((Hero *)g_hero_state)->b + 0x730, inv);
                    }
                    qcopy(shot->q30, up);
                    spread = 1.0471977f;
                    count = 0;
                    angle = 0.0f;
                    for (k = 0; k < 20; k++) {
                        list[k] = 0;
                        saved[k] = 0;
                    }
                    for (i = 0; i < 20; i++) {
                        math_build_axis_angle_quat(rot, side, math_random_float_range(0.01f, 0.52359885f));
                        vec_rotate_by_quaternion(dir, up, rot);
                        vec_rotate_by_quaternion(offs, fwd, rot);
                        angle = FastAddRotations(math_random_float_range(spread * 0.5f, spread * 1.5f), angle);
                        math_build_axis_angle_quat(rot, up, angle);
                        vec_rotate_by_quaternion(dir, dir, rot);
                        vec_rotate_by_quaternion(offs, offs, rot);
                        FastVecScale(dir, dir, 38.0f);
                        FastVecAdd(from, origin, offs);
                        FastVecAdd(to, from, dir);
                        p = ((u8 *)weapon_fire_damage_ray_pal(turret, from, to, &hit));
                        if (p) {
                            saved[count] = *(int *)(p + 0x98);
                            list[count] = p;
                            *(int *)(p + 0x98) = 0;
                            count++;
                        }
                    }
                    for (r = 0; r < count; r++)
                        *(int *)(list[r] + 0x98) = saved[r];
                    {
                        WeaponEntry *w = (WeaponEntry *)((u8 *)g_weapon_l00_table + g_item_slot_to_record[0x1A] * 0xE0);
                        shot->timer = 1.0f / w->rate;
                    }
                }
            }
        }
    }
}
