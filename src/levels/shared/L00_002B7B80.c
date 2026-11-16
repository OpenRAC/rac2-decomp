#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { f32 f[0x300]; } Pose;

extern char g_hero_state[];
extern char g_hero_item_attach_records[];

extern void cam_set_limits_first(float, float);
extern void cam_set_limits_second(float, float);
extern void cam_set_limits_third(float, float);
extern void cam_set_limits_fourth(float, float);
extern float hero_get_direction_angle_delta(void *, int);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float ApproachValue(float *, float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);

typedef struct { float f[4]; } __attribute__((aligned(16))) V_c;
typedef struct { V_c r[4]; } M_c;
typedef struct { TI128 q[4]; } QM_c;
extern float FastVecDot(void *, void *);
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern void FastVecCross(void *, void *, void *);
extern void mat_fast_helper_b(void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern float math_approach_with_velocity(float *, float, float *, float, float, float, int);

/* Hero pose tweaks by movement mode: per-mode joint offsets written to the level pose table, clamped (modes 2, 8, 0x82, and the 2/4 substates). */
void hero_apply_mode_pose_offsets(void)
{
    float x, nx, s, a, ang, mag, yaw, x8, x82, xs;
    int mode;
    int left, right;

    if (((Hero *)g_hero_state)->h[0x1454 / 2] != 0 && ((Hero *)g_hero_state)->f[0x24B8 / 4] > 0.15f && ((Hero *)g_hero_state)->i[0x2294 / 4] != 11
        && ((Hero *)g_hero_state)->b[0x1456] == 0) {
        ((Pose *)g_hero_item_attach_records)->f[0xA8 / 4] = 0.27f;
        ((Pose *)g_hero_item_attach_records)->f[0xA4 / 4] = 0.037f;
        ((Pose *)g_hero_item_attach_records)->f[0x154 / 4] = 0.025f;
        ((Pose *)g_hero_item_attach_records)->f[0x158 / 4] = 0.27f;
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            yaw = hero_get_direction_angle_delta(((Hero *)g_hero_state)->b + 0x1440, 0);
        } else {
            yaw = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1458 / 4], ((Hero *)g_hero_state)->f[0x98 / 4]);
        }
        ((Pose *)g_hero_item_attach_records)->f[0x68 / 4] = yaw;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = -yaw;
        return;
    }
    mode = ((Hero *)g_hero_state)->i[0x2294 / 4];
    if (mode == 2) {
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        if (((Hero *)g_hero_state)->i[0x2298 / 4] == 1) {
            x = ((Hero *)g_hero_state)->f[0x1A4 / 4] * 17.0f;
            if (x > 1.4f) x = 1.4f;
            else if (x < -1.4f) x = -1.4f;
            if (math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f < x) x = math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f;
            else if (x < -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f) x = -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) * 3.0f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) {
                if (x > 1.1f) x = 1.1f;
                else if (x < -1.1f) x = -1.1f;
                cam_set_limits_second(0.055f, 0.3f);
                cam_set_limits_fourth(0.07f, 0.3f);
                if (math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]) < x) x = math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]);
                else if (x < -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4])) x = -math_fabs(((Hero *)g_hero_state)->f[0x1A8 / 4]);
            }
            nx = -x;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = nx * 0.11f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] * 0.25f;
            s = ((Hero *)g_hero_state)->f[0x174 / 4] * 10.526316f;
            if (s > 1.0f) s = 1.0f;
            if (s < 0.0f) s = 0.0f;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] * s;
            ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x * 0.31f;
            if (((Hero *)g_hero_state)->b[0x40F] != 0) ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = 0.0f;
            ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x * -0.15f;
            ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x * 0.7f;
            ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = math_fabs(x) * -0.15f;
            ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x) * 0.16f;
            ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = nx * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = nx * 0.3f;
            ((Pose *)g_hero_item_attach_records)->f[0x954 / 4] = math_fabs(x) * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xA04 / 4] = math_fabs(x) * 0.2f;
        } else {
            float v = ((Hero *)g_hero_state)->f[0x1A8 / 4];
            float y, ny, d, e;
            if (((Hero *)g_hero_state)->f[0x24B8 / 4] < 0.8f && ((Hero *)g_hero_state)->i[0x1B8 / 4] < 40) {
                ApproachValue(&v, 0.0f, (float)(40 - ((Hero *)g_hero_state)->i[0x1B8 / 4]) * 0.087266475f);
            }
            y = v * 0.5f;
            if (y > 0.8f) y = 0.8f;
            else if (y < -0.8f) y = -0.8f;
            y = y * math_fabs(y) * 1.25f;
            ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = y;
            ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = y;
            d = math_fabs(y);
            ny = -y;
            ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = d * 0.25f;
            ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = ny * 0.35f;
            ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = ny * 0.3f;
        }
    } else if (mode == 8) {
        cam_set_limits_first(0.008f, 0.08f);
        cam_set_limits_second(0.015f, 0.08f);
        cam_set_limits_third(0.015f, 0.08f);
        cam_set_limits_fourth(0.008f, 0.1f);
        x8 = ((Hero *)g_hero_state)->f[0x1A8 / 4] * 1.6f;
        if (x8 > 1.25f) x8 = 1.25f;
        else if (x8 < -1.25f) x8 = -1.25f;
        ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -x8 * 0.52f;
        if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.28f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.28f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x8 * 1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x8 * 0.58f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x8 * -0.28f;
        if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] > 0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = 0.6f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] < -0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = -0.6f;
        ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = math_fabs(x8) * 0.2f;
        if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] > 0.2f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = 0.2f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] < -0.2f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -0.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x8) * 0.16f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -x8 * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -x8 * 0.3f;
    } else if (mode == 0x82) {
        cam_set_limits_first(0.017f, 0.33f);
        cam_set_limits_second(0.015f, 0.25f);
        cam_set_limits_third(0.015f, 0.25f);
        cam_set_limits_fourth(0.008f, 0.25f);
        x82 = ((Hero *)g_hero_state)->f[0x1A8 / 4] * 0.7f;
        if (x82 > 1.2f) x82 = 1.2f;
        else if (x82 < -1.2f) x82 = -1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -x82 * 0.52f;
        if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.28f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.28f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.28f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = x82 * 1.2f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = x82 * 0.58f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = x82 * -0.28f;
        if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] > 0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = 0.6f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x278 / 4] < -0.6f) ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = -0.6f;
        ((Pose *)g_hero_item_attach_records)->f[0x270 / 4] = math_fabs(x82) * 0.16f;
        ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = FastAddRotations(((Pose *)g_hero_item_attach_records)->f[0x64 / 4], -0.122173056f);
        if (((Hero *)g_hero_state)->f[0x24B8 / 4] > 0.1f) {
            ang = fast_subtract_rotations(((Hero *)g_hero_state)->f[0x1A0 / 4], ((Hero *)g_hero_state)->f[0x98 / 4]);
            mag = ((Hero *)g_hero_state)->f[0x24B8 / 4] * 0.6108653f;
            ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -math_fast_sin_or_cos_b(ang) * mag;
            ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = FastAddRotations(((Pose *)g_hero_item_attach_records)->f[0x64 / 4], math_fast_sin_or_cos_a(ang) * mag);
            if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] > 0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = 0.47123894f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x60 / 4] < -0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x60 / 4] = -0.47123894f;
            if (((Pose *)g_hero_item_attach_records)->f[0x64 / 4] > 0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = 0.47123894f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x64 / 4] < -0.47123894f) ((Pose *)g_hero_item_attach_records)->f[0x64 / 4] = -0.47123894f;
        }
        ((Pose *)g_hero_item_attach_records)->f[0x6D4 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x624 / 4] = 0.025f;
        ((Pose *)g_hero_item_attach_records)->f[0x6D8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0x628 / 4] = 0.37f;
        left = 1;
        right = 1;
        if (((Hero *)g_hero_state)->b[0x22BB] == 1) {
            right = 0;
        } else if (((Hero *)g_hero_state)->b[0x22BB] == 2) {
            left = 0;
            right = 0;
        }
        a = FastAddRotations(((Hero *)g_hero_state)->f[0x118 / 4] * 5.0f, 0.296706f);
        if (left) {
            ((Pose *)g_hero_item_attach_records)->f[0x5E8 / 4] = -0.3490659f;
            ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = -a;
            if (((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] > 0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = 0.6108653f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] < -0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x5E0 / 4] = -0.6108653f;
        }
        if (right) {
            ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = a;
            ((Pose *)g_hero_item_attach_records)->f[0x698 / 4] = 0.3490659f;
            if (((Pose *)g_hero_item_attach_records)->f[0x690 / 4] > 0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = 0.6108653f;
            else if (((Pose *)g_hero_item_attach_records)->f[0x690 / 4] < -0.6108653f) ((Pose *)g_hero_item_attach_records)->f[0x690 / 4] = -0.6108653f;
        }
        ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -((Hero *)g_hero_state)->f[0x118 / 4] * 7.7f;
        if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] > 0.64577186f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = 0.64577186f;
        else if (((Pose *)g_hero_item_attach_records)->f[0x274 / 4] < -0.64577186f) ((Pose *)g_hero_item_attach_records)->f[0x274 / 4] = -0.64577186f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -x82 * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -x82 * 0.3f;
    } else if (((Hero *)g_hero_state)->i[0x229C / 4] == 2 || ((Hero *)g_hero_state)->i[0x229C / 4] == 4) {
        cam_set_limits_first(0.04f, 0.2f);
        cam_set_limits_second(0.04f, 0.2f);
        cam_set_limits_third(0.04f, 0.2f);
        cam_set_limits_fourth(0.02f, 0.2f);
        xs = ((Hero *)g_hero_state)->f[0x1A8 / 4];
        if (xs > 1.4f) xs = 1.4f;
        else if (xs < -1.4f) xs = -1.4f;
        ((Pose *)g_hero_item_attach_records)->f[0x118 / 4] = xs * 0.29f;
        ((Pose *)g_hero_item_attach_records)->f[0x1C0 / 4] = xs * -0.27f;
        ((Pose *)g_hero_item_attach_records)->f[0x278 / 4] = xs * 0.87f;
        ((Pose *)g_hero_item_attach_records)->f[0x958 / 4] = -xs * 0.35f;
        ((Pose *)g_hero_item_attach_records)->f[0xB68 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xAB8 / 4] = ((Pose *)g_hero_item_attach_records)->f[0xA08 / 4] = -xs * 0.3f;
    }
}

/* func_L00_002B8930 is implemented in L00_002B8930-motion.c. */

/* func_L00_002B8CB8 is implemented in L00_002B8CB8-g8.c. */

/* func_L00_002B8E48 is matched in its own unit, src/levels/shared/L00_002B8E48-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */


/* Hero reference tilt rotation; adapted from RAC1 hero_steering_and_tilt.c (GPL-3.0). */
void hero_apply_reference_tilt_rotation(V_c *v, M_c *m, void *p, float a, float b, float c) {
    M_c m0;
    M_c m1;
    V_c r;
    V_c x;
    float t;
    float d, pitch, yaw, roll;
    t = 0.0f;
    {
        QM_c *d = (QM_c *)m, *s = (QM_c *)(g_hero_state);
        d->q[0] = s->q[0];
        d->q[1] = s->q[1];
        d->q[2] = s->q[2];
        d->q[3] = s->q[3];
    }
    d = FastVecDot(v, &m->r[2]);
    pitch = mat_fast_helper_a(d, square_root(1.0f - d * d));
    FastVecCross(&x, v, &m->r[2]);
    if (x.f[2] < 0.99f) {
        roll = mat_fast_helper_a(x.f[0], x.f[1]);
        r.f[0] = 0.0f;
        r.f[1] = 0.0f;
        r.f[2] = -roll;
        mat_fast_helper_b(&m1, &r);
        multiply_matrix(m, &m1, m);
        transform_vector(&x, &x, &m1);
        yaw = mat_fast_helper_a(x.f[2], x.f[0]);
        r.f[0] = 0.0f;
        r.f[2] = 0.0f;
        r.f[1] = -yaw;
        mat_fast_helper_b(&m0, &r);
        multiply_matrix(m, &m0, m);
        transform_vector(&x, &x, &m0);
    } else {
        roll = 0.0f;
        yaw = roll;
    }
    if (p) {
        r.f[2] = pitch;
        r.f[0] = 0.0f;
    } else {
        math_approach_with_velocity(&t, pitch, (float *)(g_hero_state + 0xA4), a, b, c, 0);
        r.f[0] = 0.0f;
        r.f[2] = t;
    }
    r.f[1] = 0.0f;
    mat_fast_helper_b(&m1, &r);
    multiply_matrix(m, &m1, m);
    r.f[1] = yaw;
    r.f[2] = 0.0f;
    mat_fast_helper_b(&m0, &r);
    multiply_matrix(m, &m0, m);
    r.f[2] = roll;
    r.f[1] = 0.0f;
    mat_fast_helper_b(&m1, &r);
    multiply_matrix(m, &m1, m);
    if (p) mat_get_euler_angles(m, p);
    else mat_get_euler_angles(m, g_hero_state + 0x90);
}
