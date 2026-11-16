#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern int func_2DB350(TI128 *dst, float f);

extern void func_L00_0041AEF8_1(void *dst);

extern long long GetEffectTextureDescriptor(int id);

extern float mat_fast_helper_a(float x, float y);

extern float vec_length_xy(void *vec);

extern float vec_distance_xy(void *a, void *b);

extern void FastVecSub(void *dst, void *a, void *b);

extern void vec_scale_to_length(void *dst, void *src, float scale);

extern void euler_to_matrix(void *dst, void *src);

extern void FastVecScale(void *dst, void *src, float scale);

extern void draw_world_quad(void *dst, void *src, int flag);

extern float math_random_angle(void);

/* The parts of a moby that func_L00_004208C8 reads. */
typedef struct {
    char pad0[0x18];
    float height;                 /* 0x18 */
    char pad1C[0xAA - 0x1C];
    short type;                   /* 0xAA */
} GroundMoby;

/* The hero fields func_L00_004208C8 reads; ground is the moby the hero stands on. */
typedef struct {
    char pad0[0x33C];
    GroundMoby *ground;           /* 0x33C */
    char pad340[8];
    short flag348;                /* 0x348 */
    char pad34A[0x2294 - 0x34A];
    int state;                    /* 0x2294 */
} HeroMove;

/* The level object at D_L00_001B8E20, as func_L00_004208C8 reads it. */
typedef struct {
    char pad0[0x30];
    TI128 axis;                   /* 0x30 */
    char pad40[0x40];
    TI128 v80;                    /* 0x80 */
    char pad90[0x14];
    float fA4;                    /* 0xA4 */
} CamMove;

/* The view part of an object's state (state + 0x60). */
typedef struct {
    TI128 v00;                    /* 0x00 */
    TI128 v10;                    /* 0x10 */
    char pad20[0x10];
    TI128 v30;                    /* 0x30 */
    char pad40[0x20];
    TI128 v60;                    /* 0x60 */
    char pad70[0x20];
    TI128 v90;                    /* 0x90 */
    char padA0[0x58];
    GroundMoby *ground;           /* 0xF8 */
    float groundHeight;           /* 0xFC */
} MoveView;

/* The object's state (object + 0x70). */
typedef struct {
    TI128 v00;                    /* 0x00 */
    short h10;                    /* 0x10 */
    char pad12[0x60 - 0x12];
    MoveView view;                /* 0x60 */
    char pad160[0x1E0 - 0x160];
    float f1E0;                   /* 0x1E0 */
} MoveState;

/* The object whose position and state func_L00_004208C8 moves. */
typedef struct {
    char pad0[0x30];
    TI128 position;               /* 0x30 */
    char pad40[0x30];
    MoveState *state;             /* 0x70 */
} MoveObject;

extern HeroMove g_hero_state;

extern int g_hero_locked_flag[] __attribute__((sda));

extern CamMove g_camera_move_state;

extern int g_coll_grid_limit;

extern void FastVecAdd(void *dst, void *a, void *b);

extern float FastVecDot(void *a, void *b);

#ifndef RAC2_T_CAMERAPOSITION
#define RAC2_T_CAMERAPOSITION
/* The level's camera at D_L00_001B8C80 (its address differs per level); only its
   position at +0x140 is read here. */
typedef struct {
    char pad[0x140];
    float f140;
    float f144;
    float f148;
} CameraPosition;
#endif

extern CameraPosition g_scalar_transition_state;

#ifndef RAC2_T_BLOCK_F043C77A5
#define RAC2_T_BLOCK_F043C77A5
typedef struct { int q[4]; } BLOCK_F043c77a5;
#endif

#ifndef RAC2_T_LOC_F043C77A5
#define RAC2_T_LOC_F043C77A5
typedef struct {
    BLOCK_F043c77a5 b0;
    BLOCK_F043c77a5 b1;
    BLOCK_F043c77a5 b2;
    BLOCK_F043c77a5 b3;
    int   k0, k1, k2, k3;
    int   z80, z84, z88;
    float f92, f96;
    int   z100;
    float f104, f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_F043c77a5;
#endif

extern int moby_is_in_special_class_range(char *object);

extern float *moby_get_private_value_0(char *object);

extern float func_002702C8_1(int *dst, float a, float b, float c, float d, float e);



/* shared native body of family 5a97ab89858c */
/* Fills a sprite packet with default corner positions, colors and draw settings. */
void gfx_init_sprite_packet_small(char *packet)
{
    *(long long *)(packet + 112) = 0;
    *(float *)(packet + 8) = -1.0f;
    *(float *)(packet + 24) = 1.0f;
    *(float *)(packet + 40) = -1.0f;
    *(float *)(packet + 56) = 1.0f;
    *(float *)(packet + 4) = -1.0f;
    *(float *)(packet + 36) = 1.0f;
    *(float *)(packet + 52) = 1.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -1.0f;
    *(float *)(packet + 60) = 1.0f;
}

/* shared native body of family 9a8a2404 */
/* Fills a sprite packet like the one before, but with a wider (double size) shape. */
void gfx_init_sprite_packet_large(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 8) = 0;
    *(float *)(packet + 24) = 2.0f;
    *(int *)(packet + 40) = 0;
    *(float *)(packet + 4) = -1.0f;
    *(float *)(packet + 36) = 1.0f;
    *(float *)(packet + 52) = 1.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 56) = 2.0f;
    *(float *)(packet + 20) = -1.0f;
    *(float *)(packet + 60) = 1.0f;
}


/* The Lava Gun's muzzle glow (class 1481, drawn twice by func_L00_0041AE28).
   Draws a camera-facing sprite (texture 44) at A: fills a local record with the level's
   fixed fields, turns it to face the camera position at D_L00_001B8C80 + 0x140, moves it
   a quarter of the way from A toward the camera, and hands the quad to func_00280B90
   to draw. */
void lava_gun_draw_glow_sprite(void *unused, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float v[3];
    float x;

    func_L00_0041AEF8_1(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = GetEffectTextureDescriptor(44);
    local.v128 = 0x0000FF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = mat_fast_helper_a(g_scalar_transition_state.f140 - a[0], g_scalar_transition_state.f144 - a[1]);
    x = vec_distance_xy(a, &g_scalar_transition_state.f140);
    local.f212 = -mat_fast_helper_a(x, g_scalar_transition_state.f148 - a[2]);
    local.v208 = math_random_angle();
    euler_to_matrix(&local.m00, &local.v208);
    FastVecSub(v, &g_scalar_transition_state.f140, a);
    vec_scale_to_length(v, v, 0.25f);
    local.v192 = a[0] + v[0];
    local.v196 = a[1] + v[1];
    local.v200 = a[2] + v[2];
    local.v204 = 1.0f;
    FastVecScale(&local.b0, &local.b0, f);
    FastVecScale(&local.b1, &local.b1, f);
    FastVecScale(&local.b2, &local.b2, f);
    FastVecScale(&local.b3, &local.b3, f);
    draw_world_quad(&local, &local.m00, 0);
}

/* func_L00_0041B1B8 is in L00_0041ABB8-trail-g8.c. */

/* func_L00_0041B840 is in L00_0041ABB8-ring-g8.c. */

/* func_L00_0041BCC8 is in L00_0041ABB8-beam-g8.c. */

/* Builds a 224-byte local record, writes a looked-up handle and fixed fields, calls bound float helpers, invokes one bound helper on each of four blocks, and passes the record to a final bound helper. */
void gfx_draw_directional_glow_sprite(void *unused, float *b, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float x;

    func_L00_0041AEF8_1(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = GetEffectTextureDescriptor(11);
    local.v128 = 0xFF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = mat_fast_helper_a(a[0], a[1]);
    x = mat_fast_helper_a(vec_length_xy(a), a[2]);
    local.f212 = -x;
    local.v208 = 0.0f;
    euler_to_matrix(&local.m00, &local.v208);
    local.v192 = b[0];
    local.v196 = b[1];
    local.v200 = b[2];
    local.v204 = 1.0f;
    FastVecScale(&local.b0, &local.b0, f);
    FastVecScale(&local.b1, &local.b1, f);
    FastVecScale(&local.b2, &local.b2, f);
    FastVecScale(&local.b3, &local.b3, f);
    draw_world_quad(&local, &local.m00, 0);
}




extern unsigned char *level_get_slot_body(int id, int index);

extern void table_clear_entry_flag(int index);

extern void moby_mark_spawned(void *object);

extern int *level_get_slot_header(int id, int index);

extern float math_random_float_range(float a, float b);

extern int FloatToInt(float value);

extern void DrawTwoLayerPolylineRibbon(int a0, int a1, int a2, int a3, int a4, int a5,
                              float f12, float f13, float f14);

extern void rocket_draw_ribbon_strip(void *self, int flags, int mode);

extern unsigned char g_item_slot_to_record[];

extern unsigned char g_weapon_l00_table[];

#ifndef RAC2_T_ENTRY_262570
#define RAC2_T_ENTRY_262570
/* one 224-byte record of the level's table: the flag byte sits at +4 */
typedef struct {
    unsigned char pad000[4];
    unsigned char flag;
} Entry262570;
#endif

/* Looks the object's record up in the level's table (the resident byte at D_00139568 + 0x16
   is the record's number), asks the level's builder for a matrix with the flags the object's
   own word selects, then reads the record's two colour bytes and hands the level's renderer
   the object's record. */
void rocket_draw_trail(void *moby)
{
    unsigned char *self = moby;
    unsigned char *rec;
    int handle;
    int flags;
    int mode;
    int base;
    float scale;
    unsigned int c1;
    unsigned int c2;

    rec = *(unsigned char **)(self + 0x68);
    handle = level_get_slot_body(*(int *)(rec + 0x50), *(int *)(rec + 0x3C));
    if (handle == 0) {
        table_clear_entry_flag(*(int *)(rec + 0x6C));
        moby_mark_spawned(self);
    } else {
        if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x16] * 224))->flag != 0) {
            flags = 0x802080;
            if (*(int *)(rec + 0x68) != 0)
                flags = 0x802020;
            mode = 0x7F;
        } else {
            flags = 0x202080;
            mode = 0x50;
        }
        rocket_draw_ribbon_strip(self, flags, mode);
        if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x16] * 224))->flag == 0)
            return;
        base = handle + level_get_slot_header(*(int *)(rec + 0x50), *(int *)(rec + 0x3C))[2];
        scale = math_random_float_range(0.5f, 1.0f);
        c1 = (unsigned int)FloatToInt(scale * 127.0f) << 24;
        c2 = (unsigned int)FloatToInt(scale * 48.0f) << 24;
        DrawTwoLayerPolylineRibbon(*(int *)((char *)base + *(int *)(rec + 0x30) * 4),
                          0x17, 0xE, 0x7,
                          0xFF5050 | c1, 0xFF1010 | c2,
                          0.0f, 3.0f, 0.0f);
    }
}


/* func_L00_0041EB38 is in L00_0041ABB8-shot-g8.c. */

/* func_L00_0041EE58 is in L00_0041ABB8-homing.c. */



/* func_L00_0041FC20 is defined in L00_0041FC20.c. */

extern float g_camera_l00_position[];

extern float math_random_float_range(float a, float b);

extern float math_random_signed_float_range(float a, float b);

extern int FloatToInt(float a);

extern float FastAddRotations(float a, float b);

extern void vec_build_spherical_offset(float *p, float a, float b, float c);

extern void *part_spawn_burst(float *out, float *in, int a2, int a3, unsigned int a4, int a5,
                           float f1, float f2, float f3, float f4, float f5);

/* Points the level's fixed vector at the given position, then spawns twenty
   particles around it, each one a random offset along the fixed vector.
   `size` is written but never read: that second reference to 210000.0f is what
   makes the compiler hold the constant in a saved float register ($f29) instead
   of rematerialising it at the call, which is what the retail does. */
void rocket_spawn_smoke_burst(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float f20;
    float f21;
    float f28;
    float size;
    float r;
    int n;
    int id;

    FastVecSub(v, g_camera_l00_position, pos);
    f28 = mat_fast_helper_a(v[0], v[1]);
    n = 19;
    do {
        n--;
        f21 = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        size = math_random_float_range(0.05f, 0.2f) * 210000.0f;
        f20 = math_random_float_range(0.0f, 1.3962636f);
        r = FastAddRotations(f28, math_random_signed_float_range(0.0f, 1.3962636f));
        vec_build_spherical_offset(dir, f21 * (1.0f / 60.0f), r, f20);
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[0] = pos[0] + r;
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[1] = pos[1] + r;
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[2] = pos[2] + r;
        part_spawn_burst(out, dir, 30, 127, 0x7F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    } while (n >= 0);
}

/* calls two guards and returns 1 only when both succeed and the object's float field is not positive */
int moby_is_target_dead(char *object)
{
    float *p;

    if (moby_is_in_special_class_range(object) != 0)
        return 0;
    p = moby_get_private_value_0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}


/* Tells whether a point touches the level collision grid. */
int coll_is_point_in_grid(TI128 *src)
{
    TI128 local;

    local = *src;
    return func_2DB350(&local, 0.0f) != 0;
}

/* Moves the object, its state's vectors and the view by the input step. While the hero
   stands on the same moby (hero +0x33C), a rise of that moby's height (+0x18) since the
   last frame raises the step's height. Then the step's component along the axis at
   D_L00_001B8E20 + 0x30 goes to the view's vector at +0x10, and in hero states 11 and 12
   the off-axis part is cancelled again with the vector at +0x80 scaled by +0xA4. */
void TranslateObjectAndView(MoveObject *object, TI128 *input)
{
    TI128 delta, projected, correction, remainder;
    TI128 *step = &delta;
    CamMove *cam = &g_camera_move_state;
    MoveState *state = object->state;
    MoveView *view = &state->view;
    GroundMoby *ground;
    float height, along;

    delta = *input;
    ground = g_hero_state.ground;
    if (ground != 0) {
        if (g_hero_locked_flag[0] == 0) {
            if (g_hero_state.flag348 == 0) {
                if (ground == view->ground) {
                    height = ground->height - view->groundHeight;
                    if (height > 0.0f && ((float *)step)[2] < height)
                        ((float *)step)[2] = height;
                    view->groundHeight = g_hero_state.ground->height;
                } else {
                    view->ground = ground;
                    view->groundHeight = g_hero_state.ground->height;
                }
            } else
                view->ground = 0;
        } else
            view->ground = 0;
    } else
        view->ground = 0;

    FastVecAdd(&object->position, step, &object->position);
    FastVecAdd(&view->v60, step, &view->v60);
    FastVecAdd(&view->v00, step, &view->v00);
    FastVecAdd(&view->v90, step, &view->v90);
    FastVecAdd(&view->v30, step, &view->v30);
    FastVecAdd(&state->v00, step, &state->v00);
    along = FastVecDot(step, &cam->axis);
    FastVecScale(&projected, &cam->axis, along);
    FastVecAdd(&view->v10, &view->v10, &projected);
    if (g_hero_state.flag348 == 0 &&
        !(g_hero_state.ground != 0 && g_hero_state.ground->type == 0x22D &&
          g_coll_grid_limit < 31))
        object->state->f1E0 = ((float *)step)[3];
    if ((unsigned int)(g_hero_state.state - 11) < 2) {
        MoveState *next = object->state;

        next->h10 = 0;
        FastVecScale(&correction, &cam->v80, cam->fA4);
        along = FastVecDot(&cam->axis, step);
        FastVecScale(&remainder, &cam->axis, along);
        FastVecSub(&remainder, step, &remainder);
        FastVecSub(&correction, &correction, &remainder);
        FastVecAdd(&object->position, &correction, &object->position);
        FastVecAdd(&view->v60, &correction, &view->v60);
        FastVecAdd(&view->v00, &correction, &view->v00);
        FastVecAdd(&view->v90, &correction, &view->v90);
        FastVecAdd(&next->v00, &correction, &next->v00);
    }
}

/* func_L00_00420C38 is built from L00_0041ABB8-anim-g8.c. */

/* reads a base pointer from a0+112 and pushes three consecutive tweak slots through the same five-float interpolation helper, writing each result back over the first float vector while forwarding three trailing floats unchanged. */
void cam_ease_vector_toward(char *a0, float *a1, float *a2,
                                        float f12, float f13, float f14)
{
    int *p = *(int **)(a0 + 112);

    a1[0] = func_002702C8_1(p + 64, a1[0], a2[0], f12, f13, f14);
    a1[1] = func_002702C8_1(p + 65, a1[1], a2[1], f12, f13, f14);
    a1[2] = func_002702C8_1(p + 66, a1[2], a2[2], f12, f13, f14);
}



/* func_L00_00422268 is in L00_0041ABB8-g8.c. */
