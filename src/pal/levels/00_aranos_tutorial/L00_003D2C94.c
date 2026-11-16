#include "include_asm.h"



#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct {
    char pad00[0x24];
    float f24;
} AranosModel;
typedef struct AranosMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[2];
    unsigned char f23;
    AranosModel *model;
    char pad28[4];
    float f2C;
    char pad30;
    unsigned char f31;
    char pad32[2];
    unsigned short flags;
    char pad36[0x2E];
    void (*hook)(void *);
    void *ctx;
    char pad6C[0x10];
    unsigned short f7C;
    char pad7E[0x1A];
    int f98;
    char pad9C[0xC];
    unsigned char fA8;
    char padA9;
    short classId;
    char padAC[0x14];
    char matrix[0x30];
    Vec rotation;
} AranosMoby;
extern AranosMoby *cam_moby_create(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern char g_hero_position[];
extern int IsPointInCuboid(char *, unsigned int);
extern void moby_mark_spawned(void *);
extern int PlayMobySound(int, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern AranosMoby *g_launch_moby_list[];
extern void moby_mark_spawned(void *);
typedef struct {
    unsigned int flag;
    int frames;
} AranosDriftCtx;

/* Once its flag is set, drifts the object along its heading for 100 frames, then removes it. */
void func_PAL_L00_003D3478(AranosMoby *obj) {
    AranosDriftCtx *ctx;
    int result;
    float angle;
    float point[3];

    ctx = obj->ctx;
    if (obj->state == 0) {
        result = IsPointInCuboid(g_hero_position, ctx->flag);
        if (result != 0) {
            obj->state = 1;
            ctx->frames = 0;
            PlayMobySound(0, 0, obj);
        }
    }
    if (obj->state != 1)
        return;
    angle = obj->rotation.f[2];
    point[0] = math_fast_sin_or_cos_a(angle) * 0.50000006f;
    angle = obj->rotation.f[2];
    point[1] = math_fast_sin_or_cos_b(angle) * 0.50000006f;
    point[2] = 0.0f;
    FastVecAdd(&obj->position, &obj->position, point);
    ctx->frames += 1;
    if (ctx->frames < 0x65)
        return;
    moby_mark_spawned(obj);
}



extern void euler_rotation_basis(void *, void *);
extern int math_random_int_range(int, int);
extern int math_fast_float_d(void *);
extern float math_random_signed_float_range(float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

void func_PAL_L00_003D38F8(char *obj) {
    char *ctx;
    float limit;
    ctx = *(char **)(obj + 0x68);
    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(ctx + 8) = math_random_signed_float_range(5.0f, 15.0f);
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(ctx + 0x0C) = math_random_int_range(0x3C, 0x78);
        limit = *(float *)(ctx + 8) * 0.017453294f;
        if (*(float *)(obj + 0xF0) < limit) {
            PlayMobySound(0, 0, obj);
        } else {
            PlayMobySound(1, 0, obj);
        }
    }
    if (*(unsigned char *)(obj + 0x20) != 1) return;
    limit = *(float *)(ctx + 8) * 0.017453294f;
    math_spring_float_to_goal((float *)(obj + 0xF0), (float *)ctx, limit,
        0.0010471977f, 0.0010471977f, 0.0052359886f);
    euler_rotation_basis(obj + 0xC0, obj + 0xF0);
    if (math_fast_float_d(ctx + 0x0C) != 0) {
        *(unsigned char *)(obj + 0x20) = 0;
    } else if (*(float *)(obj + 0xF0) == *(float *)(ctx + 8) * 0.017453294f) {
        *(unsigned char *)(obj + 0x20) = 0;
    }
}


typedef struct {
    char pad00[4];
    float f04;
    char pad08[0x48];
    int f50;
} AranosChildCtx;
extern float g_effect_fade_value_a __attribute__((sda));
extern float g_effect_fade_value_b __attribute__((sda));
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern int flag_set_first_pending(void *);
extern void moby_set_state(void *, int, int);
extern void vec_random_direction(void *, float, float);
extern int coll_scatter_points_in_shapes(void *, int, void *, int, float);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *moby_l00_spawn_child(void *, int, int);
extern AranosMoby *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void glow_fade_update_pal(void *);
extern void set_moby_color(void *, unsigned char, unsigned char, unsigned char);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
typedef struct {
    AranosMoby *sparks[16];
    float decay[16];
    int hold;
    int timer;
} AranosSparkerCtx;

/* Spawns a burst of sparks around the object, then fades them until the timer runs out. */
void func_PAL_L00_003D3A48(AranosMoby *obj) {
    struct {
        Vec velocity, offset, position;
    } frame;
    AranosSparkerCtx *ctx = obj->ctx;
    AranosMoby *child;
    AranosChildCtx *childctx;
    int type, i;
    float life;

    switch (obj->state) {
    case 0:
        for (i = 15; i >= 0; i--)
            ctx->sparks[i] = 0;
        if (obj->classId == 0xAC9) {
            obj->rotation.f[1] += 0.78539824f;
            euler_rotation_basis(obj->matrix, &obj->rotation);
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x10000, 0) && ctx->hold == 0)
            moby_set_state(obj, 2, -1);
        obj->fA8 = 0xFF;
        return;
    case 2: {
        unsigned char alpha;
        int count = 5, n;

        if (g_effect_fade_value_a < 0.85f && g_effect_fade_value_b < 0.85f)
            count = 14;
        for (n = 0; n < count; n++) {
            vec_random_direction(&frame.offset, 0.85f, 1.95f);
            coll_scatter_points_in_shapes(obj, 1, &frame.position, 0xFFFF, 1000.0f);
            FastVecAdd(&frame.offset, &frame.offset, &frame.position);
            frame.velocity.f[2] = math_random_float_range(0.0f, 5.0f) * 0.020000001f;
            frame.velocity.f[1] = math_random_float_range(-6.0f, 6.0f) * 0.020000001f;
            if (math_random_int_below(4)) {
                type = 1;
                ctx->decay[n] = math_random_float_range(20.0f, 40.0f) * 0.00040000002f;
                frame.velocity.f[0] = math_random_float_range(-8.0f, -4.0f) * 0.020000001f;
                life = math_random_float_range(5.0f, 10.0f);
            } else {
                type = 2;
                ctx->decay[n] = 0.0f;
                frame.velocity.f[0] = math_random_float_range(2.0f, 4.0f) * 0.020000001f;
                life = math_random_float_range(15.0f, 20.0f);
            }
            child = cam_moby_create_pal(obj, type, 0x43E, math_random_int_below(4), &frame.offset, &obj->rotation, &frame.velocity,
                                  0xFF, 180.0f, life);
            ctx->sparks[n] = child;
            if (child) {
                child->hook = glow_fade_update_pal;
                life = math_random_float_range(0.75f, 5.0f);
                ctx->sparks[n]->f2C = ctx->sparks[n]->model->f24 * life;
                childctx = ctx->sparks[n]->ctx;
                alpha = 0x80;
                set_moby_color(ctx->sparks[n], 0x20, 0x60, alpha);
                ctx->sparks[n]->f23 = alpha;
                childctx->f50 = 0x1806020;
            }
        }
        snd_play_from_class_bank(math_random_int_range(0, 1), 0, obj, 0xC0A);
        switch (obj->classId) {
        case 0xC0A:
            moby_l00_spawn_child(obj, 0xC10, 0);
            break;
        case 0xC0B:
            moby_l00_spawn_child(obj, 0xC11, 0);
            break;
        case 0xC0C:
            moby_l00_spawn_child(obj, 0xC12, 0);
            break;
        case 0xC0D:
            moby_l00_spawn_child(obj, 0xC13, 0);
            break;
        case 0xE01:
            obj->f7C = 0x8001;
            break;
        case 0xE02:
            obj->f7C = 0x8001;
            break;
        case 0xAC9:
            obj->f7C = 0x8001;
            break;
        }
        moby_set_state(obj, 3, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(obj)) {
            if (!(obj->f7C & 0x8000)) {
                obj->f31 = 0;
                obj->flags |= 1;
            }
            obj->f98 = 0;
            ctx->timer = 250;
        }
        if (!math_fast_float_d(&ctx->timer)) {
            for (i = 0; i < 16; i++) {
                if (ctx->sparks[i])
                    ((AranosChildCtx *)ctx->sparks[i]->ctx)->f04 -= ctx->decay[i];
            }
        } else if (!(obj->f7C & 0x8000)) {
            moby_mark_spawned(obj);
        }
        return;
    default:
        return;
    }
}



