#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; char *p[0x980]; } Hero;
extern char g_hero_state[];
typedef struct {
    char pad0[4];
    u8 alt;
    char pad5[0x4B];
    float speed;
    char pad54[224 - 0x54];
} Kind;
typedef struct { char pad0[0x18]; char *who; } Hit;
typedef struct {
    float vel[4];
    s16 life;
    s16 kind;
    char *target;
    s16 h18, h1A;
    float scale;
    float v20, v24, v28;
    s16 h2C, h2E;
    int slot;
    s16 h34, h36;
    int i38;
    int id;
    float aim[4];
    int owner;
    int i54;
    float yaw;
    float f5C, f60, f64;
    int flag;
    int handle;
    float start[4];
} Rocket;
extern int CollLine(void *, void *, int, char *, int);
extern int coll_process_hit(void *, int, char *, int, float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern float FastAddRotations(float, float);
extern char *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern char *moby_get_private_value_0(void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern int moby_is_in_special_class_range(void *);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *SelectBestTargetInCone(void *, void *, float, float, int *, int, int, int, float, float, float, int, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void moby_init_child_from_parent(void *, void *, int);
extern int part_alloc_effect_slot(void *, float, float, float, void *);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern void level_init_pending_slot(void *, void *);
extern void level_append_record_to_table(void *, int, int, float);
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
typedef struct { char pad[0x16]; u8 x16; char pad2[0x100]; } Gs;
extern Gs g_item_slot_to_record;
extern int g_hero_locked_flag MACRO_ADDR;
extern int g_active_tether_object MACRO_ADDR;
extern unsigned int g_guided_rocket_slot MACRO_ADDR;
extern char g_scalar_transition_state[];
extern char g_cam_follow_matrix[];
extern Hit g_collision_result;
extern Kind g_weapon_l00_table[];
#define HERO ((Hero *)D_00189E20)
typedef struct { char pad[0x150]; float v[4]; } View;
#define VIEW (((View *)D_L00_001B8C80)->v)
char *func_PAL_L00_00421578(char *owner, void *pos, int mode, int id, char *hint, int flag)
{
    float a[4], b[4], c[4], d[4], e[4], f[4];
    float unused60[8]; /* retail's frame keeps these 0x20 bytes; nothing in the body reaches them */
    float n[4], t[4], u[4];
    int outv;
    char *m, *r;
    Rocket *s;
    float speed, fr;
    char *base;
    int *tab, *pp;
    m = CreateMoby(0x87A);
    if (m) {
    s = *(Rocket **)(m + 0x68);
    s->life = 0xFA;
    s->kind = 0xA;
    s->h2E = 2;
    s->i38 = -1;
    s->id = id;
    s->h18 = 0;
    s->v20 = 0;
    s->v24 = 0;
    s->v28 = 0;
    s->h1A = 0;
    s->h2C = 0;
    s->h34 = 0;
    s->owner = *(s16 *)(owner + 0xAA);
    s->yaw = -1.2217306f;
    s->f5C = 0;
    s->f60 = 0;
    s->f64 = 0;
    s->flag = flag;
    moby_init_child_from_parent(m, owner, -1);
    ((u8 *)m)[0x30] = 0xFF;
    if ((g_weapon_l00_table + g_item_slot_to_record.x16)->alt)
        *(int *)(m + 0x78) = 0xFFFF0A0A;
    else
        *(int *)(m + 0x78) = 0xFF0A0AFF;
    if (flag) {
        FastVecScale(a, HERO->p[0x2290 / 4] + 0xE0, 0.3f);
        FastVecAdd(m + 0x10, m + 0x10, a);
        FastVecScale(b, HERO->p[0x2290 / 4] + 0xD0, 0.3f);
        FastVecAdd(m + 0x10, m + 0x10, b);
        FastVecScale(c, HERO->p[0x2290 / 4] + 0xC0, 0.5f);
        FastVecAdd(m + 0x10, m + 0x10, c);
        FastVecAdd(d, g_hero_state + 0x80, a);
        if (CollLine(d, m + 0x10, 0x10, HERO->p[0x2290 / 4], 0)) {
            FastVecSub(e, d, m + 0x10);
            FastVecScale(e, e, 0.75f);
            FastVecAdd(m + 0x10, m + 0x10, e);
        }
    } else
        qcopy(m + 0x10, pos);
    vec_clear_128(s);
    speed = (g_weapon_l00_table + g_item_slot_to_record.x16)->speed * 0.020000001f;
    if (mode) {
        HERO->f[0xC04 / 4] = VIEW[2];
        HERO->f[0xC08 / 4] = FastAddRotations(-VIEW[1], 0.12217305600643158f);
        vec_build_spherical_offset(s, speed, HERO->f[0xC04 / 4], HERO->f[0xC08 / 4]);
    } else
        cam_offset_point_by_side_direction(s, s, speed);
    vec_clear_128(a);
    euler_rotation_basis(b, a);
    if (mode) {
        a[0] = VIEW[0];
        a[1] = VIEW[1];
        a[2] = VIEW[2];
        euler_rotation_basis(f, a);
        multiply_matrix3x3(b, f, b);
    } else
        multiply_matrix3x3(b, HERO->p[0x2290 / 4] + 0xC0, b);
    copy_matrix_rotation(e, b);
    mat_get_euler_angles(e, m + 0xF0);
    copy_matrix3x4(m + 0xC0, e);
    *(float *)(m + 0xCC) = *(float *)(m + 0xDC) = *(float *)(m + 0xEC) = 0.0f;
    *(u16 *)(m + 0x34) |= 0x100;
    s->scale = 1.0f;
    if (coll_process_hit(m + 0x10, 1, HERO->p[0x2290 / 4], 0, 1.0f) != 0
        && ((g_collision_result.who != 0 && *(char **)(g_collision_result.who + 0x24) != 0
             && *(s16 *)(*(char **)(g_collision_result.who + 0x24) + 0x46) == 5)
            || moby_is_in_special_class_range(g_collision_result.who) != 0)) {
        s->target = g_collision_result.who;
        r = moby_get_private_value_0(s->target);
        if (r) {
            cam_compute_view_direction(m + 0x10, n, 1);
            FastVecScale(t, n, *(float *)(r + 0x10));
            FastVecAdd(m + 0x10, s->target + 0x10, t);
        }
    } else if (flag == 0) {
        char *lock = HERO->p[0x1450 / 4];
        if (lock != 0 && ((u8 *)lock)[0x20] != 0xFE && ((u8 *)lock)[0x20] != 0xFD)
            s->target = lock;
        else
            s->target = SelectBestTargetInCone(m + 0x10, e, 0.174532949924469f, 0.349065899848938f, &outv, 0, 0, 0, 30.0f, 0.0f, 0.0f, 0, 0);
    } else
        s->target = hint;
    if (s->target) {
        cam_compute_view_direction(m + 0x10, n, 1);
        fr = fast_vec_dist(m + 0x10, s->target + 0x10) * 0.033333335f;
        if (fr > 1.0f)
            fr = 1.0f;
        math_apply_axis_rotation_to_quat(s, s, n, -(fr * 0.43633235f));
        s->h36 = 0;
    } else {
        if (mode) {
            FastVecScale(s->aim, g_cam_follow_matrix, 64.0f);
            FastVecAdd(s->aim, s->aim, g_cam_follow_matrix - 0x230);
        } else {
            FastVecScale(n, HERO->p[0x2290 / 4] + 0xC0, 64.0f);
            FastVecAdd(s->aim, m + 0x10, n);
        }
        if (g_hero_locked_flag != 0)
            s->h36 = 0;
        else {
            if ((HERO->i[0x1500 / 4] == 0 && HERO->i[0x2294 / 4] != 0x1D && HERO->i[0x2294 / 4] != 1)
                || ((*(u16 *)(HERO->p[0x2290 / 4] + 0x34) ^ 1) & 1)) {
                cam_compute_view_direction(m + 0x10, n, 1);
                math_apply_axis_rotation_to_quat(s, s, n, -0.43633235f);
            }
            s->h36 = 1;
        }
    }
    if (g_guided_rocket_slot >= 0x19)
        g_guided_rocket_slot = 0;
    s->slot = g_guided_rocket_slot;
    base = level_get_slot_body(s->owner, s->id);
    if (base == 0) {
        moby_mark_spawned(m);
        return 0;
    }
    tab = level_get_slot_header(s->owner, s->id);
    pp = (int *)(base + tab[1]);
    if (pp[s->slot])
        s->slot = -1;
    else {
        g_guided_rocket_slot = (int)(g_guided_rocket_slot + 1) % 25;
        pp[s->slot] = 1;
        s->i54 = 0;
        base += tab[0];
        level_init_pending_slot(m, base + s->slot * 0x150);
        if (g_active_tether_object != 0)
            level_append_record_to_table(s->slot * 0x150 + base, 0x30, 1, 0.0f);
        else {
            level_append_record_to_table(s->slot * 0x150 + base, 0x30, 2, 0.0f);
            level_append_record_to_table(s->slot * 0x150 + base, 0x17, 3, 0.0f);
        }
    }
    math_build_axis_angle_quat(n, m + 0xC0, s->yaw);
    vec_rotate_by_quaternion(m + 0xD0, m + 0xD0, n);
    vec_rotate_by_quaternion(m + 0xE0, m + 0xE0, n);
    s->handle = part_alloc_effect_slot(m, 1.0f, 1.0f, 1.0f, 0);
    qcopy(s->start, m + 0x10);
    if (g_hero_locked_flag != 0) {
        cam_compute_view_direction(m + 0x10, t, 1);
        fr = FastVecDot(t, s);
        FastVecScale(u, t, fr);
        FastVecSub(s, s, u);
    }
    }
    return m;
}
