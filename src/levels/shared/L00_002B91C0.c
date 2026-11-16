#include "common.h"

#ifndef RAC2_T_TI_F41EB487E
#define RAC2_T_TI_F41EB487E
typedef int TI_F41eb487e __attribute__((mode(TI)));
#endif

extern void func_002830C0_2(void *a, void *b, void *c);

extern void func_00282D30_4(void *a, void *b, float value);

extern void hero_apply_reference_tilt_rotation(void *a, void *b, int c, float p, float q, float r);

extern void func_00282CF0_3(void *a, void *b, void *c);

extern void func_00282CC0_3(void *a, void *b, void *c);

#ifndef RAC2_T_VEC4_F41EB487E
#define RAC2_T_VEC4_F41EB487E
typedef struct {
    int a;
    int b;
    float c;
    float d;
} Vec4_F41eb487e;
#endif

#ifndef RAC2_T_RESIDENTSTATE_F41EB487E
#define RAC2_T_RESIDENTSTATE_F41EB487E
typedef struct {
    u8 pad000[0x80];
    u8 area080[0x218 - 0x80];
    short h218;
    u8 pad21a[0x2a0 - 0x21a];
    TI_F41eb487e q2A0;
    u8 pad2b0[0x2c0 - 0x2b0];
    u8 area2C0[0x31c - 0x2c0];
    float f31C;
    u8 pad320[0x34e - 0x320];
    short h34E;
    u8 pad350[0x22c3 - 0x350];
    u8 b22C3;
} ResidentState_F41eb487e;
#endif

extern ResidentState_F41eb487e D_00189E20_5;

extern char g_hero_shrink_vector[];

extern float func_L00_002D3A58_1(void *p);

extern void func_L00_002D3B58_1(void *a, void *b, float f);

extern void func_L00_002D3BD8_2(void *a, void *b, float f);

extern void func_00282CC0_28(void *a, void *b, void *c);

extern void func_00282C88_5(void *a);

extern void  func_002AF000_1(char *p, float a, float b, float c);

extern void  func_00282CC0_18(char *p, char *q, char *r);

extern int   func_002761F8_1(void *a, void *b, int c, int d, int e);

extern void  func_L00_002D36E0_1(void *p, int n, float a, float b, float c);

extern void  func_00282CF0_8(void *dst, void *src, void *arg);

extern float func_00283248_5(float a, float b);

extern float func_00282E20_3(void *p);

extern char  D_L00_001B8C80_2[];

extern char  g_hero_l00_position[];

extern char  D_00189E20_21[];

typedef struct {
    u8 pad0[0x88];
    float f88;
    u8 pad8c[0xc];
    float f98;
    u8 pad9c[0x54];
    float vf0[4];
    u8 pad100[0x40];
    float v140[4];
    u8 pad150[0x20];
    float f170;
    u8 pad174[0x2c];
    float f1a0;
    u8 pad1a4[0xc];
    float f1b0;
    u8 pad1b4[0x4];
    int f1b8;
    u8 pad1bc[0xe4];
    float v2a0[4];
    u8 pad2b0[0x68];
    float f318;
    u8 pad31c[0x4];
    float f320;
    float f324;
    u8 pad328[0xd8];
    float f400;
    float f404;
    u8 pad408[0x658];
    float va60[4];
    float fa70;
    u8 pada74[0x1820];
    int f2294;
    u8 pad2298[0x220];
    float f24b8;
} State9598;
extern State9598 D_00189E20_9598;
extern void hero_resolve_stick_direction(int, float);
extern void hero_steer_heading(int, float, float, float);
extern void hero_build_move_impulse(float, float);
extern void ref_L00_002B9598_0(int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fabs(float);
extern int g_hero_state_flags;

/* initialises three 16-byte records, folds a resident 32-byte quad into the first of them, then for the stored mode 2 runs a four-argument fallback and for mode 1 with a short or low field re-copies the resident quad; finally scales and copies the two remaining records through three more calls */
void hero_update_lean_reference(void)
{
    u8 scratch[64];
    Vec4_F41eb487e A, B, C;
    float hi = 0.035f;
    float lo = 0.3f;

    *(TI_F41eb487e *)&A = 0;
    *(TI_F41eb487e *)&B = 0;
    *(TI_F41eb487e *)&C = 0;

    A.c = 1.0f;
    B.c = 0.8f;
    C.c = 0.8f;

    func_002830C0_2(&B, &B, &D_00189E20_5);

    *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&D_00189E20_5.q2A0;
    if (D_00189E20_5.b22C3 == 2) {
        func_00282D30_4(&A, &D_00189E20_5.area2C0, -1.0f);
    }

    if (D_00189E20_5.b22C3 == 1 && (D_00189E20_5.h34E < 10 || D_00189E20_5.f31C < 1.0f))
        *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&D_00189E20_5.q2A0;

    if (D_00189E20_5.h34E != 0 && D_00189E20_5.h218 != 0) {
        lo = 0.001f;
        hi = lo;
    }

    hero_apply_reference_tilt_rotation(&A, scratch, 0, hi, lo, 0.0f);

    if (D_00189E20_5.b22C3 == 1 && D_00189E20_5.h34E != 0) {
        func_002830C0_2(&C, &C, scratch);
        func_00282CF0_3(&D_00189E20_5.area080, &D_00189E20_5.area080, &C);
        func_00282CC0_3(&D_00189E20_5.area080, &D_00189E20_5.area080, &B);
    }
}


/* reads a scalar through DATA0 and, when it exceeds 0.001f, re-normalises the vector at DATA0 (and DATA0-112) from the elapsed float, clamping the amount at zero; otherwise it runs the plain refresh entry point. */
void hero_shrink_vector_by_amount(float a0)
{
    char *p = g_hero_shrink_vector;
    float x = a0;
    float r = func_L00_002D3A58_1(p);
    float d;

    if (0.001f < r) {
        func_L00_002D3B58_1(p, p, 0.0f);
        d = r - x;
        if (d < 0.0f)
            d = 0.0f;
        func_L00_002D3BD8_2(p, p, d);
        func_00282CC0_28(p - 112, p - 112, p);
    } else {
        func_00282C88_5(p);
    }
}

/* Moves the hero's reference point toward where the stick points, correcting it so it stays on the ground and not in walls. */
void hero_steer_reference_point(void)
{
    float desired[4] __attribute__((aligned(16)));
    float original[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float correction[4] __attribute__((aligned(16)));
    float x, limit, t, angle, scale, step, length, adjustment;
    hero_resolve_stick_direction(0, 1.0f);
    hero_steer_heading(0, 0.02f, 0.2f, 0.061086535f);
    if (D_00189E20_9598.f2294 == 19) {
        if (D_00189E20_9598.f24b8 < 0.2f) D_00189E20_9598.f1a0 = D_00189E20_9598.f98;
        D_00189E20_9598.f1b0 = 0.4f;
    } else if (D_00189E20_9598.f2294 == 21) D_00189E20_9598.f1b0 = 0.0f;
    desired[0] = math_fast_sin_or_cos_a(D_00189E20_9598.f1a0) * D_00189E20_9598.f1b0 * 0.09833333641290665f;
    desired[1] = math_fast_sin_or_cos_b(D_00189E20_9598.f1a0) * D_00189E20_9598.f1b0 * 0.09833333641290665f;
    desired[2] = 0.0f;
    qcopy_nc(original, desired);
    if (D_00189E20_9598.fa70 > 0.0f) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy_nc(previous, D_00189E20_9598.va60);
        func_00282CC0_3(desired, desired, D_00189E20_9598.va60);
        func_00282C88_5(D_00189E20_9598.va60);
    }
    x = -(D_00189E20_9598.vf0[0] * desired[0] + D_00189E20_9598.vf0[1] * desired[1]);
    if (x > 0.0f) {
        x /= func_00282E20_3(desired);
        x /= func_00282E20_3(D_00189E20_9598.vf0);
    }
    if (x > 1.0f) x = 1.0f;
    if (x < 0.0f) x = 0.0f;
    limit = D_00189E20_9598.f1b0 * 0.00068055559f;
    limit += x * 0.00055555557f;
    if (g_hero_state_flags) limit = 0.00030555556f;
    if (D_00189E20_9598.f2294 == 19 && D_00189E20_9598.f1b8 < 15 && D_00189E20_9598.f170 < 0.050000004f)
        limit = 0.0030555557f;
    if (D_00189E20_9598.f170 > 0.09833333641290665f) limit = 0.0036111111f;
    if (D_00189E20_9598.fa70 > 0.0f) {
        x = -FastVecDot(original, previous);
        length = FastVecLength(original);
        if (length > 0.0f) x /= length;
        length = func_00282E20_3(previous);
        adjustment = (length - x) / length * 0.00083333335f;
        if (D_00189E20_9598.f24b8 < 0.3f && adjustment < 0.00083333335f) adjustment = 0.00083333335f;
        if (limit < adjustment) limit = adjustment;
    }
    func_00282CF0_3(delta, desired, D_00189E20_9598.v140);
    delta[2] = 0.0f;
    if (FastVecLength(delta) > limit) vec_scale_to_length(delta, delta, limit);
    func_00282CC0_3(D_00189E20_9598.vf0, D_00189E20_9598.v140, delta);
    if (D_00189E20_9598.f320 > 0.087266475f) {
        angle = func_00283248_5(D_00189E20_9598.v2a0[0], D_00189E20_9598.v2a0[1]);
        scale = D_00189E20_9598.f320 * 0.16976526f;
        step = D_00189E20_9598.f320 * 0.0030062596779316664f;
        delta[0] = math_fast_sin_or_cos_a(angle) * scale;
        delta[1] = math_fast_sin_or_cos_b(angle) * scale;
        delta[2] = 0.0f;
        func_00282CF0_3(correction, delta, D_00189E20_9598.vf0);
        correction[2] = 0.0f;
        if (FastVecLength(correction) > step) vec_scale_to_length(correction, correction, step);
        func_00282CC0_3(D_00189E20_9598.vf0, D_00189E20_9598.vf0, correction);
    }
    qcopy_nc(delta, D_00189E20_9598.vf0);
    delta[2] = 0.0f;
    D_00189E20_9598.f400 = FastVecDot(delta, desired);
    t = FastVecLength(desired);
    if (t > 0.0f) D_00189E20_9598.f400 /= t * 0.09833333641290665f;
    ref_L00_002B9598_0(0);
    if (D_00189E20_9598.f404 < 0.017453294f && D_00189E20_9598.f324 > 0.087266475f)
        func_00282D30_4(D_00189E20_9598.vf0, D_00189E20_9598.vf0, math_fast_sin_or_cos_a(D_00189E20_9598.f324));
    D_00189E20_9598.f404 = D_00189E20_9598.f324;
    if (math_fabs(D_00189E20_9598.f88 - D_00189E20_9598.f318) < 0.15f) D_00189E20_9598.f88 = D_00189E20_9598.f318;
}


/* The resident block the slot table lives in, and the two vector helpers. */
extern char D_00189E20_2[];

extern char g_hero_direction_matrix[];

extern void transform_vector(void *a0, void *a1, void *a2);

extern float mat_fast_helper_a(float a, float b);

extern float math_shortest_angle_delta(float from, int selector, float to);

/* Transform the direction into resident space and return its selected angle delta. */
float hero_get_direction_angle_delta(void *a0, int selector)
{
    float v[4];

    transform_vector(v, a0, g_hero_direction_matrix);
    return math_shortest_angle_delta(mat_fast_helper_a(v[0], v[1]), selector, 0.0f);
}

/* The resident id this forwards, and the helper it calls. */
extern int g_hero_moby;

extern int PlayMobySound(int index, int flags, char *object);

/* Forward the sound index, flags and resident object pointer; return the result. */
int hero_play_sound(int index, int flags)
{
    return PlayMobySound(index, flags, (char *)g_hero_moby);
}


/* Claims the first free slot of the eight 8-byte entries at resident +0x23EC: a slot whose
   leading short is clear takes the three arguments, a pending marker and its two extra
   fields, and the search stops at the first one taken. */
void hero_queue_delayed_event(int a0, int a1, int a2)
{
    char *base = D_00189E20_2;
    short *slot = (short *)(base + 0x23EC);
    int i;

    for (i = 0; i < 8; i++, slot += 4) {
        if (slot[0] != 0)
            continue;
        slot[0] = 1;
        slot[3] = a2;
        slot[2] = a1;
        slot[1] = a0;
        return;
    }
}

/* The eight 8-byte entries func_L00_002B9C58 claims at resident +0x23EC. */
typedef struct {
    short pending;
    short id;
    short timer;
    short arg;
} DelayedSlot_9CA8;

extern struct {
    u8 pad0[0x149D];
    u8 b149D;
    u8 pad149e[0x23EC - 0x149E];
    DelayedSlot_9CA8 slots[8];
} D_00189E20_9CA8;

extern int FastDecTimer(void *);
extern void hero_play_footstep_sound_dust(int, int, int, int);

/* Ticks the timer of each of the eight entries; one whose timer reports 2 is cleared and
   fires: id 0x16 calls func_L00_002A61C8 with the resident byte at +0x149D, any other id
   goes to func_L00_002B9B88 with the entry's argument. */
void UpdateDelayedSounds(void)
{
    int i;
    short id;

    for (i = 0; i < 8; i++) {
        if (FastDecTimer(&D_00189E20_9CA8.slots[i].timer) == 2) {
            id = D_00189E20_9CA8.slots[i].id;
            D_00189E20_9CA8.slots[i].pending = 0;
            if (id == 0x16)
                hero_play_footstep_sound_dust(D_00189E20_9CA8.b149D, 1, 1, 0x32);
            else
                hero_play_sound(id, D_00189E20_9CA8.slots[i].arg);
        }
    }
}

extern char g_hero_position[];

extern int g_hero_ledge_move_flag;

extern void func_00283410_1(void *a, void *b);

extern void func_002833F0_1(void *a, void *b);

extern void hero_reset_speeds_and_vectors(void);

extern void level_release_slot_list(void *p);

extern void cancel_hero_item_animation(void);

extern void attachment_reset_all(void);

extern s32 hero_l00_set_action(int a0, int a1);

extern void anim_start_object_at_frame(int a0, int a1);

extern void hero_l00_update_ground_contact(void);

extern float func_00282E48_1(void *a, void *b);

extern void tracked_moby_set_state(int a0, int a1);

extern void global_object_start(void *a, int b);

extern void cam_reset_default(void);

extern void level_apply_nearest_env_preset(void *p);

/* The resident block, as far as func_L00_002B9D60 touches it. */
typedef struct {
    u8 pad000[0x34E];
    short h34E;
    u8 pad350[0x3A0 - 0x350];
    int i3A0;
    int flags3A4;
    u8 pad3a8[0x2290 - 0x3A8];
    char *object;
    u8 pad2294[0x229C - 0x2294];
    int i229C;
    u8 pad22a0[0x24EF - 0x22A0];
    u8 b24EF;
} ResidentState_9D60;

/* Reset the hero position and direction, the resident movement state and the related level objects. */
void hero_reset_position_and_direction(void *position, void *direction, int sound, int refresh)
{
    ResidentState_9D60 *res;
    char *hero = g_hero_position;

    qcopy(hero, position);
    res = (ResidentState_9D60 *)(hero - 0x80);
    qcopy(res->object + 0x10, position);
    qcopy(hero + 0x10, direction);

    func_00283410_1(res, hero + 0x10);
    func_002833F0_1(res->object + 0xC0, hero + 0x10);
    hero_reset_speeds_and_vectors();
    level_release_slot_list(hero + 0x1860);
    level_release_slot_list(hero + 0x19B0);

    res->flags3A4 &= ~1;
    res->flags3A4 &= ~2;
    res->h34E = 1;
    res->i3A0 = 0;
    res->b24EF = 0;

    cancel_hero_item_animation();
    attachment_reset_all();

    if (sound != -1)
        hero_l00_set_action(sound, 2);

    anim_start_object_at_frame(*(u8 *)(res->object + 0x43), *(u8 *)(res->object + 0x41));

    if (res->i229C == 0x11)
        g_hero_ledge_move_flag = 1;
    else
        g_hero_ledge_move_flag = 0;

    hero_l00_update_ground_contact();

    if (func_00282E48_1(g_hero_position, g_hero_position + 0x250) < 1.0f)
        qcopy(g_hero_position, g_hero_position + 0x250);

    tracked_moby_set_state(0, 0);
    global_object_start(0, 0);

    if (refresh != 0)
        cam_reset_default();

    level_apply_nearest_env_preset(*(void **)(g_hero_position + 0x2210));
}

/* queries a resident table with a stack request and blends a vector back into the resident record */
/* Probes the ground in front of the hero and stores the slope angle of what it finds. */
int hero_probe_ground_slope_ahead(void)
{
    char buf[48];
    char *base = D_L00_001B8C80_2;
    char *res;
    float v;

    func_002AF000_1(buf, 10.0f, *(float *)(base + 344), -*(float *)(base + 340));
    func_00282CC0_18(buf, buf, base + 320);
    res = D_00189E20_21;
    if (func_002761F8_1(base + 320, buf, 4, *(int *)(res + 8848), 0)) {
        func_L00_002D36E0_1(buf + 16, 1, 0.5f, 0.0f, 0.5f);
        func_00282CF0_8(buf + 32, g_hero_l00_position, buf + 16);
        v = func_00283248_5(*(float *)(buf + 32), *(float *)(buf + 36));
        *(float *)(res + 3076) = v;
        v = func_00282E20_3(buf + 32);
        *(float *)(res + 3080) = func_00283248_5(v, *(float *)(buf + 40));
        return 1;
    }
    return 0;
}

/* The resident fields func_L00_002BA508 reads and writes. */
typedef struct {
    u8 pad0[0x184];
    float f184;
    u8 pad188[0x1B8 - 0x188];
    int i1B8;
    u8 pad1bc[0x278 - 0x1BC];
    float f278;
    u8 pad27c[0x280 - 0x27C];
    float f280;
    u8 b284;
    u8 pad285[0xC04 - 0x285];
    float fC04;
    float fC08;
    u8 padc0c[0x1220 - 0xC0C];
    char *p1220;
    u8 pad1224[0x123A - 0x1224];
    u8 b123A;
    u8 pad123b[0x1500 - 0x123B];
    int i1500;
    u8 pad1504[0x1A30 - 0x1504];
    u8 area1A30[0x2290 - 0x1A30];
    char *p2290;
    int i2294;
} ResidentState_A508;

extern ResidentState_A508 D_00189E20_A508;

/* The level vector at +0x150 of the block func_L00_002BA410 queries. */
extern struct {
    u8 pad0[0x150];
    float x, y, z;
} D_L00_001B8C80_A508;

extern float FastAddRotations(float a, float b);
extern int moby_is_class_71(void *obj);
extern void vec_clear_128(void *m);
extern void cam_offset_point_by_side_direction(void *dst, void *src, float f);
extern void vec_build_spherical_offset(void *m, float a, float b, float c);
extern void euler_rotation_basis(void *dst, void *v);
extern void multiply_matrix3x3(void *dst, void *a, void *b);
extern void copy_matrix_rotation(void *dst, void *src);
extern void mat_get_euler_angles(void *src, void *dst);
extern void level_init_pending_slot(void *obj, void *area);
extern void level_append_record_to_table(void *area, int a, int b, float f);
extern void anim_start_blended(void *obj, int a, int b, int c);

/* Once per hero state, set up the object at resident +0x1220 (the special case uses a stored angle
   and the level vector at +0x150 of the block func_L00_002BA410 queries, otherwise the unit scale
   and the parent transform) and pass the composed transform to the object at +0xF0.
   Does nothing once the byte at +0x123A is set. */
void hero_setup_attached_object_transform(void)
{
    float scratch[4];
    u8 transform[48], level_transform[48], composed[64];
    char *object, *record, *matrix;
    int special;

    if (D_00189E20_A508.b123A)
        return;

    special = 0;
    if (D_00189E20_A508.i1500)
        special = 1;
    if (D_00189E20_A508.i2294 == 1 || D_00189E20_A508.i2294 == 29) {
        special = 0;
        if (D_00189E20_A508.i1B8 > 20)
            special = 1;
    }

    if (special && !hero_probe_ground_slope_ahead()) {
        D_00189E20_A508.fC04 = D_L00_001B8C80_A508.z;
        D_00189E20_A508.fC08 = FastAddRotations(-D_L00_001B8C80_A508.y, 0.12217305600643158f);
    }

    object = D_00189E20_A508.p1220;
    if (!moby_is_class_71(object))
        return;
    D_00189E20_A508.b123A = 1;
    if (special)
        hero_play_sound(17, 0);

    *(u8 *)(object + 0x20) = 10;
    record = *(char **)(object + 0x68);
    if (D_00189E20_A508.f278 < 1.2f && D_00189E20_A508.f280 > 0.6632251739501953f
        && !D_00189E20_A508.b284)
        *(short *)(record + 0x76) = 1;

    matrix = record + 0x40;
    vec_clear_128(matrix);
    if (!special)
        cam_offset_point_by_side_direction(matrix, matrix, 1.0f);
    else
        vec_build_spherical_offset(matrix, 1.0f, D_00189E20_A508.fC04, D_00189E20_A508.fC08);

    vec_clear_128(scratch);
    euler_rotation_basis(transform, scratch);
    if (special) {
        scratch[0] = D_L00_001B8C80_A508.x;
        scratch[1] = D_L00_001B8C80_A508.y;
        scratch[2] = D_L00_001B8C80_A508.z;
        euler_rotation_basis(level_transform, scratch);
        multiply_matrix3x3(transform, level_transform, transform);
    } else {
        multiply_matrix3x3(transform, D_00189E20_A508.p2290 + 0xC0, transform);
    }
    copy_matrix_rotation(composed, transform);
    mat_get_euler_angles(composed, object + 0xF0);

    *(int *)(record + 0x64) = 0;
    *(float *)(record + 0x60) = 0.38333335518836975f;
    if (D_00189E20_A508.f184 < 0.3333333432674408f) {
        level_init_pending_slot(object, D_00189E20_A508.area1A30);
        level_append_record_to_table(D_00189E20_A508.area1A30, 48, 3, 0.0f);
        level_append_record_to_table(D_00189E20_A508.area1A30, 23, 5, 0.0f);
    }
    anim_start_blended(object, 6, 0, 5);
}
