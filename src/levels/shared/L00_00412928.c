#include "common.h"
#include "include_asm.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector g_hero_state_block;
extern Vector g_billboard_corner_table[4];
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_world_to_screen_unit(int, float *, float *);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);


extern void draw_world_quad(char *, int, int);

typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_l00_spawn_explosion_burst_2(char *, char *);
extern void SpawnBurstParticles(char *, char *);
extern void part_spawn_explosion_burst_with_drift(char *, char *, char *);
extern int moby_transform_point_by_attachment(char *, char *, char *, char *);
extern char ref_L00_004195C8_00[];
extern char g_scalar_transition_state[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
/* SpawnState with an attachment parent, as func_L00_00414020 fills it. */
typedef struct ParentedSpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra, extra2;
    char *parent;
} ParentedSpawnState;
/* The record func_L00_00416F68 fills; func_L00_00417D70 reads kind as a mode and parent. */
typedef struct AttachedSpawnState {
    int life;
    int kind;
    char *parent;
} AttachedSpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;



extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

extern int func_00282978_5(char *handle);

extern void func_0029F338_2(char *object);

extern int func_002EDD78(char *handle);

extern void func_002E6EF8(char *callback, char *object);

extern void func_00310440(char *object);

extern void func_00320DE0(char *object, int a, char *b, char *c, char *d, char *e);

extern char ref_L00_00415A38_00[];

extern char ref_L00_00414350_00[];

extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *part_l00_spawn_spinning(void *, void *, int);
extern char g_default_vector[] __attribute__((sda));
typedef struct { char pad[0x140]; float x, y; } CameraHead;
extern float IntToFloat(int);
extern int math_fast_float_d(void *);
extern void lerp_vector(void *, void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);

/* One of the twenty-four 0xB0-byte records at D_L00_0025A920 (claimed by func_L00_00417A40,
   updated by func_L00_00417D70). Measured layout; field roles are inferred from those two. */
typedef struct {
    Vector out0;            /* 0x00: ang0 through the two angle helpers, times amp0 */
    Vector out1;            /* 0x10: the same for ang1 */
    Vector start;           /* 0x20: follows the owner's position */
    Vector point;           /* 0x30: blended between start and end */
    Vector end;             /* 0x40: keeps its offset from start */
    float ang0[3];          /* 0x50 */
    float rate0[3];         /* 0x5C */
    float amp0[3];          /* 0x68 */
    float ang1[3];          /* 0x74 */
    float rate1[3];         /* 0x80 */
    float amp1[3];          /* 0x8C */
    int release;            /* 0x98: timer, frees the record when it expires */
    char *owner;            /* 0x9C */
    int time;               /* 0xA0: timer */
    int duration;           /* 0xA4 */
    int started;            /* 0xA8 */
    int pad;                /* 0xAC */
} EffectRecord;

extern EffectRecord g_spark_l00_records[24];

extern char g_hero_state[];
extern char g_sound_state[];
typedef union { unsigned char b[0x2600]; int i[0x980]; float f[0x980]; char *ptr[0x980]; } EffectHero;
typedef struct { char bytes[0x70]; } EffectReleaseSlot;
extern int FastDecTimer(void *);
extern void moby_mark_spawned(char *);
extern float *moby_get_private_value_0(char *);
extern void UpdateWaveLineEffect(char *);
/* Preserve the object argument passed to the empty callback in retail. */
extern void func_L00_00414018_1(char *);
extern void snd_stop_voice(int);
extern Vector128 g_hero_l00_position;
extern void part_emit_spark_burst_at_moby(char *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern void spark_record_claim(char *, void *, int);
extern void part_spawn_drifting_particles(char *);
extern void beam_glow_sprites_update_owned(char *);
extern void spark_records_update(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);


/* Updates the wave line effect (moby class 4501). It follows the hero and its target, and lets go of its sound when it stops. */
void wave_line_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    char local[32];
    char *child;
    int code, index;
    float *child_data;
    if (FastDecTimer(state + 0x1E) != 0) {
        moby_mark_spawned(object);
        return;
    }
    FastVecScale(local, ((EffectHero *)g_hero_state)->ptr[2212] + 0xE0, 0.75f);
    FastVecAdd(object + 0x10, &((EffectHero *)g_hero_state)->f[32], local);
    if (*(char **)(state + 0x20) != 0) {
        code = *(unsigned char *)(*(char **)(state + 0x20) + 0x20);
        if (code == 254)
            *(char **)(state + 0x20) = 0;
        else if (code == 253)
            *(char **)(state + 0x20) = 0;
        child = *(char **)(state + 0x20);
        if (child != 0) {
            qcopy(state + 0x30, child + 0x10);
            child_data = moby_get_private_value_0(child);
            if (child_data != 0) {
                FastVecScale(local + 16, *(char **)(state + 0x20) + 0xE0, child_data[4]);
                FastVecAdd(state + 0x30, state + 0x30, local + 16);
            }
        }
    }
    if (*(unsigned char *)(object + 0x20) == 1) {
        func_L00_00414018_1(object);
        UpdateWaveLineEffect(object);
    } else {
        index = *(int *)(state + 0x18);
        if (index >= 0) {
            if (index != -1) {
                EffectReleaseSlot *entry = &((EffectReleaseSlot *)g_sound_state)[index];
                if (*(char **)((char *)entry + 0x88) == object &&
                    *(unsigned char *)((char *)entry + 0x74) != 0)
                    snd_stop_voice(index);
            }
            *(int *)(state + 0x18) = -1;
        }
    }
}

/* Clear both entry tables and reset the record state. */
/* Clears the two point lists of the wave line effect and resets its counters. */
void wave_line_reset_effect(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        *(int *)(*(char **)(state + 0) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 0) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 0) + i * 16 + 12) = 1.0f;
    }

    for (i = 0; i < 20; i++) {
        *(int *)(*(char **)(state + 4) + i * 16 + 0) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 4) = 0;
        *(int *)(*(char **)(state + 4) + i * 16 + 8) = 0;
        *(float *)(*(char **)(state + 4) + i * 16 + 12) = 1.0f;
    }

    *(int *)(state + 0xC) = 0;
    *(short *)(state + 0x1C) = 6;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x8) = 0;
}

/* Empty callback that does nothing. */
void moby_noop_callback(void)
{
}

/* Creates an explosion effect (moby class 5020) that can be attached to a parent. It sets up the sizes and timers and shakes the camera when close. */
char *parented_explosion_spawn(float size, char *position, int trigger, int kind, int red, int green,
                        int blue, int enabled, int flags, int extra, int control, int extra2,
                        char *parent)
{
    Vector128 direction[1], up[1], attachment[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139c /* moby class 5020 */);
    ParentedSpawnState *state;
    SpawnObject *self;
    if (object != 0) {
        self = (SpawnObject *)object;
        *(unsigned char *)(object + 0x30) = 0xff;
        object[0x20] = 0;
        *(short *)(object + 0x32) = 0xff;
        state = (ParentedSpawnState *)self->state;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        FastVecSub(direction, g_scalar_transition_state + 0x140, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        state->size = size;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->extra2 = extra2;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->control = control;
        state->flags = flags;
        state->parent = parent;
        qzero_nc(attachment);
        if (parent)
            moby_transform_point_by_attachment(object, parent, object + 0x10, (char *)attachment);
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, g_scalar_transition_state + 0x140) < 48.0f && trigger != 0) {
                char *manager = g_scalar_transition_state;
                *(int *)(manager + 0x16c) = 0;
                *(int *)(manager + 0x168) = 20;
                *(float *)(manager + 0x160) = 0.075f;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, g_scalar_transition_state + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                if (1.5707964f - math_fast_angle_helper(FastVecDot(difference, g_scalar_transition_state + 0x370)) < 0.45378566f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        part_spawn_explosion_burst_with_drift(object, (char *)up, (char *)attachment);
    }
    return object;
}

/* Forwards the cached sub-object into the pair update when it is present, then releases the handle pair or re-arms the module callback. */
void parented_explosion_update(char *object)
{
    char *handle = *(char **)(object + 0x68);

    if (*(int *)(handle + 0x3C) != 0)
        func_00320DE0(object, *(int *)(handle + 0x3C), object + 0x10, object + 0xF0,
                      object + 0x10, object + 0xF0);

    if (func_002EDD78(handle) == 0) {
        func_002EDD78(handle + 4);
        func_002E6EF8(ref_L00_00414350_00, object);
    } else {
        func_00310440(object);
    }
}



/* Draws a flat square sprite that faces the camera, with an optional roll and a random wobble in its texture. */
void gfx_l00_draw_jittered_billboard_quad(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    gfx_init_quad_packet_state(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)(g_scalar_transition_state + 0x140), (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&g_hero_state_block);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = g_billboard_corner_table;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            gfx_world_to_screen_unit((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            gfx_world_to_screen_unit((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    gfx_init_quad_packet_state(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}


/* Creates an explosion effect (moby class 5021). It sets up the sizes and timers and shakes the camera when close. */
char *explosion_spawn(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139d /* moby class 5021 */);
    SpawnState *state;
    SpawnObject *self;
    char *camera;
    float angle;
    if (object != 0) {
        self = (SpawnObject *)object;
        state = self->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = g_scalar_transition_state + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, g_scalar_transition_state + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(difference, (char *)&g_scalar_transition_state + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        part_l00_spawn_explosion_burst_2(object, (char *)up);
    }
    return object;
}


/* Releases the object's cached handle pair when free and otherwise re-arms the module's tick callback. */
void explosion_update(char *object)
{
    char *handle = *(char **)(object + 0x68);

    if (func_002EDD78(handle) == 0) {
        func_002EDD78(handle + 4);
        func_002E6EF8(ref_L00_00415A38_00, object);
    } else {
        func_00310440(object);
    }
}



/* Draws a flat square sprite that faces the camera, with an optional roll and a random wobble in its texture. */
void gfx_draw_jittered_billboard_quad_copy(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    gfx_init_quad_packet_state(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)(g_scalar_transition_state + 0x140), (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&g_hero_state_block);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = g_billboard_corner_table;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            gfx_world_to_screen_unit((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            gfx_world_to_screen_unit((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    gfx_init_quad_packet_state(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}


/* Creates a spark effect object (moby class 5022) that can be attached to a parent. */
char *spark_effect_spawn(Vector128 *position, int kind, char *parent)
{
    Vector128 direction[1], up[1];
    char *object = CreateMoby(0x139E /* moby class 5022 */);
    if (object != 0) {
        SpawnObject *self = (SpawnObject *)object;
        AttachedSpawnState *state = (AttachedSpawnState *)self->state;
        char *first = object + 0x10;
        char *second;
        char *third;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(first, position);
        *(float *)(object + 0x1c) = 1.0f;
        second = object + 0xc0;
        FastVecSub(direction, g_scalar_transition_state + 0x140, first);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(first, (char *)up, 1);
        qcopy(second, direction);
        third = object + 0xd0;
        FastVecCross(third, second, up);
        vec_scale_to_length(third, third, 1.0f);
        FastVecCross(object + 0xe0, third, second);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        state->life = 60;
        state->kind = kind;
        state->parent = parent;
    }
    return object;
}


/* Spawns 25 particles around the object, each drifting away from the camera at a random angle. */
void part_spawn_drifting_particles(char *object)
{
    float spawn[8];
    float heading, angle, speed;
    float spread = 0.0f;
    int i;

    for (i = 24; i >= 0; i--) {
        heading = mat_fast_helper_a(((CameraHead *)g_scalar_transition_state)->x - *(float *)(object + 0x10),
                                ((CameraHead *)g_scalar_transition_state)->y - *(float *)(object + 0x14));
        speed = math_random_signed_float_range(1.0f, 2.0f);
        FloatToInt(speed);
        spawn[0] = *(float *)(object + 0x10) + math_random_signed_float_range(-0.25f, 0.25f);
        spawn[1] = *(float *)(object + 0x14) + math_random_signed_float_range(-0.25f, 0.25f);
        spawn[2] = *(float *)(object + 0x18) + math_random_signed_float_range(-0.25f, 0.25f);
        spread = 0.0f;
        angle = FastAddRotations(heading, math_random_signed_float_range(spread, -1.5707965f));
        speed = 4.0f;
        spawn[4] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        spawn[5] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        spawn[6] = 0.075f;
        part_l00_spawn_spinning(spawn, g_default_vector, 300);
    }
}




/* Steps every record the object owns: jitters its start, moves start (and end with it) to the
   object's position or to an offset from its parent, advances the two angle triples (faster
   while the timer runs), blends point between start and end, and releases the record when
   its release timer expires after the main timer. */
void spark_records_update(char *object)
{
    Vector delta, transformed, offset;
    char *state = *(char **)(object + 0x68);
    int i;

    for (i = 0; i < 24; ++i) {
        EffectRecord *record;
        float ratio, blend;

        if (g_spark_l00_records[i].owner != object)
            continue;
        record = &g_spark_l00_records[i];
        record->start.v[0] += math_random_float_range(-0.1f, 0.1f);
        record->start.v[1] += math_random_float_range(-0.1f, 0.1f);
        record->start.v[2] += math_random_float_range(-0.1f, 0.1f);
        FastVecSub(&delta, &record->end, &record->start);
        if (*(int *)(state + 4) == 0) {
            qcopy(&record->start, object + 0x10);
        } else {
            offset.word = 0;
            offset.v[0] = -0.15f;
            offset.v[1] = -0.8f;
            offset.v[3] = 1.0f;
            matrix_mul_vec3(&transformed, &offset, *(char **)(state + 8) + 0xC0);
            FastVecAdd(&transformed, &transformed, *(char **)(state + 8) + 0x10);
            qcopy(&record->start, &transformed);
        }
        FastVecAdd(&record->end, &record->start, &delta);
        if (record->time != 0) {
            record->ang0[0] = FastAddRotations(record->ang0[0], record->rate0[0] * 100.0f);
            record->ang0[1] = FastAddRotations(record->ang0[1], record->rate0[1] * 100.0f);
            record->ang0[2] = FastAddRotations(record->ang0[2], record->rate0[2] * 100.0f);
            record->ang1[0] = FastAddRotations(record->ang1[0], record->rate1[0] * 100.0f);
            record->ang1[1] = FastAddRotations(record->ang1[1], record->rate1[1] * 100.0f);
            record->ang1[2] = FastAddRotations(record->ang1[2], record->rate1[2] * 100.0f);
        } else {
            record->ang0[0] = FastAddRotations(record->ang0[0], record->rate0[0] * 50.0f);
            record->ang0[1] = FastAddRotations(record->ang0[1], record->rate0[1] * 50.0f);
            record->ang0[2] = FastAddRotations(record->ang0[2], record->rate0[2] * 50.0f);
            record->ang1[0] = FastAddRotations(record->ang1[0], record->rate1[0] * 50.0f);
            record->ang1[1] = FastAddRotations(record->ang1[1], record->rate1[1] * 50.0f);
            record->ang1[2] = FastAddRotations(record->ang1[2], record->rate1[2] * 50.0f);
        }
        record->out0.v[0] = math_fast_sin_or_cos_a(record->ang0[0]) * record->amp0[0];
        record->out0.v[1] = math_fast_sin_or_cos_b(record->ang0[1]) * record->amp0[1];
        record->out0.v[2] = -math_fast_sin_or_cos_b(record->ang0[2]) * record->amp0[2];
        record->out1.v[0] = math_fast_sin_or_cos_a(record->ang1[0]) * record->amp1[0];
        record->out1.v[1] = math_fast_sin_or_cos_b(record->ang1[1]) * record->amp1[1];
        record->out1.v[2] = -math_fast_sin_or_cos_b(record->ang1[2]) * record->amp1[2];
        ratio = IntToFloat(record->time);
        ratio /= IntToFloat(record->duration);
        blend = 1.0f - ratio;
        if (*(int *)(state + 4) == 0)
            lerp_vector(&record->point, &record->start, &record->end, blend);
        else
            lerp_vector(&record->point, &record->start, &record->end, 0.75f);
        if (math_fast_float_d(&record->time)) {
            if (record->started == 0)
                record->started = 1;
            if (math_fast_float_d(&record->release))
                record->owner = 0;
        }
    }
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void curve_compute_next_neighbour_point(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void effect_init_transform_record(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}


/* Creates a blue explosion effect (moby class 5023). It sets up the sizes and timers and shakes the camera when close. */
char *blue_explosion_spawn(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0x139f /* moby class 5023 */);
    SpawnState *state;
    SpawnObject *self;
    char *camera;
    float angle;
    if (object != 0) {
        self = (SpawnObject *)object;
        state = self->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = g_scalar_transition_state + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        self->forward[3] = self->right[3] = self->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, g_scalar_transition_state + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(difference, (char *)&g_scalar_transition_state + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        SpawnBurstParticles(object, (char *)up);
    }
    return object;
}


/* Tests the handle cached in the object and, while the handle reports itself already released, drops the next sub-handle, otherwise runs the object's destroy helper. */
void explosion_release_handle(char *object)
{
    char *handle = *(char **)(object + 104);

    if (func_00282978_5(handle) == 0)
        func_00282978_5(handle + 4);
    else
        func_0029F338_2(object);
}

/* func_L00_00418A80 is defined in L00_00418A80-g8.c. */

/* Runs the destroy helper once the child's status goes negative; otherwise re-arms the module callback
   when the timer at 0x3C is zero or the sphere test accepts the record at 0x30. */
void effect_with_child_update(char *object)
{
    char *handle = *(char **)(object + 0x68);
    char *child = *(char **)(handle + 0x44);

    if (child != 0 && *(signed char *)(child + 0x20) < 0) {
        func_00310440(object);
    } else if (*(float *)(handle + 0x3C) == 0.0f ||
               math_fast_helper_a(handle + 0x30, (float)*(short *)(object + 0x32)) != 0) {
        func_002E6EF8(ref_L00_004195C8_00, object);
    }
}

/* func_L00_00419668 is in L00_00419668-dbg.c. */


/* Marks the object as started and raises the high bit of its flag word, once. */
void effect_moby_start(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x20) = 1;
        *(unsigned short *)(object + 0x34) |= 0x800;
    }
}

/* func_L00_00419C98 is defined in L00_00419C98-g8.c. */

/* func_L00_0041A490 is defined in L00_0041A490-dbg.c. */

