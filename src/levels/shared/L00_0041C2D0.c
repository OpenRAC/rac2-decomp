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
extern int D_L00_001A8FF0 MACRO_ADDR;
extern int D_L00_001ADB2C MACRO_ADDR;
extern unsigned int D_L00_001B2D5C MACRO_ADDR;
extern char D_L00_001B8C80[];
extern char D_L00_001B8FF0[];
extern Hit g_collision_result;
extern Kind g_weapon_l00_table[];
#define HERO ((Hero *)D_00189E20)
typedef struct { char pad[0x150]; float v[4]; } View;
#define VIEW (((View *)D_L00_001B8C80)->v)
/* Creates a guided rocket (class 2170) for the owner, places it at the muzzle, aims it and picks a target if there is one. Returns the new rocket, or 0 if it could not be set up. */
char *guided_rocket_create(char *owner, void *pos, int mode, int id, char *hint, int flag)
{
    float a[4], b[4], c[4], d[4], e[4], f[4];
    float unused60[8]; /* retail'vars frame keeps these 0x20 bytes; nothing in the body reaches them */
    float n[4], t[4], u[4];
    int outv;
    char *rocket, *info;
    Rocket *vars;
    float speed, fr;
    char *base;
    int *table, *used;
    rocket = CreateMoby(0x87A /* moby class 2170 */);
    if (rocket) {
    vars = *(Rocket **)(rocket + 0x68);
    vars->life = 0x12C;
    vars->kind = 0xA;
    vars->h2E = 2;
    vars->i38 = -1;
    vars->id = id;
    vars->h18 = 0;
    vars->v20 = 0;
    vars->v24 = 0;
    vars->v28 = 0;
    vars->h1A = 0;
    vars->h2C = 0;
    vars->h34 = 0;
    vars->owner = *(s16 *)(owner + 0xAA);
    vars->yaw = -1.2217306f;
    vars->f5C = 0;
    vars->f60 = 0;
    vars->f64 = 0;
    vars->flag = flag;
    moby_init_child_from_parent(rocket, owner, -1);
    ((u8 *)rocket)[0x30] = 0xFF;
    if ((g_weapon_l00_table + g_item_slot_to_record.x16)->alt)
        *(int *)(rocket + 0x78) = 0xFFFF0A0A;
    else
        *(int *)(rocket + 0x78) = 0xFF0A0AFF;
    if (flag) {
        FastVecScale(a, HERO->p[0x2290 / 4] + 0xE0, 0.3f);
        FastVecAdd(rocket + 0x10, rocket + 0x10, a);
        FastVecScale(b, HERO->p[0x2290 / 4] + 0xD0, 0.3f);
        FastVecAdd(rocket + 0x10, rocket + 0x10, b);
        FastVecScale(c, HERO->p[0x2290 / 4] + 0xC0, 0.5f);
        FastVecAdd(rocket + 0x10, rocket + 0x10, c);
        FastVecAdd(d, g_hero_state + 0x80, a);
        if (CollLine(d, rocket + 0x10, 0x10, HERO->p[0x2290 / 4], 0)) {
            FastVecSub(e, d, rocket + 0x10);
            FastVecScale(e, e, 0.75f);
            FastVecAdd(rocket + 0x10, rocket + 0x10, e);
        }
    } else
        qcopy(rocket + 0x10, pos);
    vec_clear_128(vars);
    speed = (g_weapon_l00_table + g_item_slot_to_record.x16)->speed * 0.016666668f;
    if (mode) {
        HERO->f[0xC04 / 4] = VIEW[2];
        HERO->f[0xC08 / 4] = FastAddRotations(-VIEW[1], 0.12217305600643158f);
        vec_build_spherical_offset(vars, speed, HERO->f[0xC04 / 4], HERO->f[0xC08 / 4]);
    } else
        cam_offset_point_by_side_direction(vars, vars, speed);
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
    mat_get_euler_angles(e, rocket + 0xF0);
    copy_matrix3x4(rocket + 0xC0, e);
    *(float *)(rocket + 0xCC) = *(float *)(rocket + 0xDC) = *(float *)(rocket + 0xEC) = 0.0f;
    *(u16 *)(rocket + 0x34) |= 0x100;
    vars->scale = 1.0f;
    if (coll_process_hit(rocket + 0x10, 1, HERO->p[0x2290 / 4], 0, 1.0f) != 0
        && ((g_collision_result.who != 0 && *(char **)(g_collision_result.who + 0x24) != 0
             && *(s16 *)(*(char **)(g_collision_result.who + 0x24) + 0x46) == 5)
            || moby_is_in_special_class_range(g_collision_result.who) != 0)) {
        vars->target = g_collision_result.who;
        info = moby_get_private_value_0(vars->target);
        if (info) {
            cam_compute_view_direction(rocket + 0x10, n, 1);
            FastVecScale(t, n, *(float *)(info + 0x10));
            FastVecAdd(rocket + 0x10, vars->target + 0x10, t);
        }
    } else if (flag == 0) {
        char *lock = HERO->p[0x1450 / 4];
        if (lock != 0 && ((u8 *)lock)[0x20] != 0xFE && ((u8 *)lock)[0x20] != 0xFD)
            vars->target = lock;
        else
            vars->target = SelectBestTargetInCone(rocket + 0x10, e, 0.174532949924469f, 0.349065899848938f, &outv, 0, 0, 0, 30.0f, 0.0f, 0.0f, 0, 0);
    } else
        vars->target = hint;
    if (vars->target) {
        cam_compute_view_direction(rocket + 0x10, n, 1);
        fr = fast_vec_dist(rocket + 0x10, vars->target + 0x10) * 0.033333335f;
        if (fr > 1.0f)
            fr = 1.0f;
        math_apply_axis_rotation_to_quat(vars, vars, n, -(fr * 0.43633235f));
        vars->h36 = 0;
    } else {
        if (mode) {
            FastVecScale(vars->aim, D_L00_001B8FF0, 64.0f);
            FastVecAdd(vars->aim, vars->aim, D_L00_001B8FF0 - 0x230);
        } else {
            FastVecScale(n, HERO->p[0x2290 / 4] + 0xC0, 64.0f);
            FastVecAdd(vars->aim, rocket + 0x10, n);
        }
        if (D_L00_001A8FF0 != 0)
            vars->h36 = 0;
        else {
            if ((HERO->i[0x1500 / 4] == 0 && HERO->i[0x2294 / 4] != 0x1D && HERO->i[0x2294 / 4] != 1)
                || ((*(u16 *)(HERO->p[0x2290 / 4] + 0x34) ^ 1) & 1)) {
                cam_compute_view_direction(rocket + 0x10, n, 1);
                math_apply_axis_rotation_to_quat(vars, vars, n, -0.43633235f);
            }
            vars->h36 = 1;
        }
    }
    if (D_L00_001B2D5C >= 0x19)
        D_L00_001B2D5C = 0;
    vars->slot = D_L00_001B2D5C;
    base = level_get_slot_body(vars->owner, vars->id);
    if (base == 0) {
        moby_mark_spawned(rocket);
        return 0;
    }
    table = level_get_slot_header(vars->owner, vars->id);
    used = (int *)(base + table[1]);
    if (used[vars->slot])
        vars->slot = -1;
    else {
        D_L00_001B2D5C = (int)(D_L00_001B2D5C + 1) % 25;
        used[vars->slot] = 1;
        vars->i54 = 0;
        base += table[0];
        level_init_pending_slot(rocket, base + vars->slot * 0x150);
        if (D_L00_001ADB2C != 0)
            level_append_record_to_table(vars->slot * 0x150 + base, 0x30, 1, 0.0f);
        else {
            level_append_record_to_table(vars->slot * 0x150 + base, 0x30, 2, 0.0f);
            level_append_record_to_table(vars->slot * 0x150 + base, 0x17, 3, 0.0f);
        }
    }
    math_build_axis_angle_quat(n, rocket + 0xC0, vars->yaw);
    vec_rotate_by_quaternion(rocket + 0xD0, rocket + 0xD0, n);
    vec_rotate_by_quaternion(rocket + 0xE0, rocket + 0xE0, n);
    vars->handle = part_alloc_effect_slot(rocket, 1.0f, 1.0f, 1.0f, 0);
    qcopy(vars->start, rocket + 0x10);
    if (D_L00_001A8FF0 != 0) {
        cam_compute_view_direction(rocket + 0x10, t, 1);
        fr = FastVecDot(t, vars);
        FastVecScale(u, t, fr);
        FastVecSub(vars, vars, u);
    }
    }
    return rocket;
}
