#include "include_asm.h"
#include "common.h"

/* A body whose retail bytes address its global through $gp in ordinary flow: the assembler
   only selects that form when the back end emits the .extern size directive, which the
   pinned profile does at -G8 (see docs/build/compiler-notes.md). */
extern unsigned char *CreateMoby(int size);

extern unsigned char *D_L00_001B0A20 __attribute__((sda));

/* Creates the health drain slots object and remembers it in a level global. */
unsigned char *health_drain_slots_create(int unused)
{
    unsigned char *moby = CreateMoby(0xD04 /* moby class 3332 */);

    if (moby != 0) {
        unsigned int initValue = 0xFF;

        D_L00_001B0A20 = moby;
        *(unsigned short *)(moby + 0x32) = initValue;
        moby[0x20] = 1;
        moby[0x30] = initValue;
    }
    return moby;
}

/* Per-frame update of the player's gadget table: it walks the records of one table
   entry, scales each record's pair of floats and asks the slot manager to refresh
   them, then folds the two level globals into the table's offset. */

extern float D_L00_001B096C __attribute__((sda));

extern float D_L00_001B0970 __attribute__((sda));

extern char *level_get_slot_body(int a0, int a1);

extern float FastAddRotations(float a0, float a1);

extern void vaporizer_set_chain_joint_offset(char *rec, int index);

extern int FastDecTimer(char *a0);

/* Updates the Vaporizer joint chain each frame: it fires each joint, eases a shared offset back toward zero, and returns 1 when the chain timer has run out. */
int vaporizer_update_joint_chain(char *moby)
{
    char *state;
    char *table;
    char *base;
    char *rec;
    int index;
    int count;
    int i = 0;
    float value;

    state = *(char **)(moby + 0x68);
    table = level_get_slot_body(0xC04 /* Vaporizer */, *(short *)(state + 0x1A));
    index = *(short *)(state + 0x18);
    base = *(char **)(table + index * 4);
    count = *(short *)(state + 0x20);
    if (count > 0) {
        rec = base;
        do {
            *(float *)(rec + 0x20) = FastAddRotations(*(float *)(rec + 0x20), *(float *)(rec + 0x28));
            vaporizer_set_chain_joint_offset(base, i);
            rec += 0x30;
            i++;
        } while (i < count);
    }
    value = D_L00_001B096C;
    if (value > 7.0f) {
        D_L00_001B096C = 0.0f;
    } else if (value < -7.0f) {
        D_L00_001B096C = 0.0f;
    }
    D_L00_001B096C = D_L00_001B096C - D_L00_001B0970;
    if (D_L00_001B096C <= -4.0f) {
        D_L00_001B096C = D_L00_001B096C + 4.0f;
    }
    return FastDecTimer(state + 0x22) == 0;
}

/* func_L00_003EFA98 and func_L00_003EFD00: two 64-face quad renderers. Each builds a textured
   packet from the level's $gp tuning words, scales a diagonal matrix by the object's size, and
   per face takes four corners and UVs from the face table, transforms them through the matrix,
   the object's basis (0xC0) and position (0x10) plus an offset, and draws the quad. */

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern int D_L00_001B0870 __attribute__((sda));
extern int D_L00_001B0874 __attribute__((sda));
extern int D_L00_001B0878 __attribute__((sda));
extern int D_L00_001B087C __attribute__((sda));
extern int D_L00_001B0880 __attribute__((sda));
extern int D_L00_001B0884 __attribute__((sda));
extern int D_L00_001B0888 __attribute__((sda));
extern float D_L00_001B088C __attribute__((sda));
extern Vector D_L00_0029AF40[];
extern short D_L00_0029B440[][4][2];
extern float D_L00_0029B840[][2];
extern long long GetEffectTextureDescriptor(int id);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void cam_compute_view_direction(char *, char *, int);
extern void draw_world_quad(void *packet, void *frame, int mode);

/* Draws a ball made of 64 textured quads around the object, a larger and flatter version than the next function. */
void gfx_draw_quad_sphere_large(char *object)
{
    RenderPacket packet;
    Vector matrix[3];
    Vector offset;
    char *state = *(char **)(object + 0x68);
    Vector *origin;
    float *u_base, *v_base;
    int face, corner;
    unsigned int color;
    long flags;
    float quarter;

    packet.f78 = GetEffectTextureDescriptor(D_L00_001B0884);
    flags = (long)D_L00_001B0870;
    flags |= (long)D_L00_001B0874 << 2;
    flags |= (long)D_L00_001B0878 << 4;
    flags |= (long)D_L00_001B087C << 6;
    flags |= (long)D_L00_001B0880 << 32;
    packet.f80 = 0xFF9000000260L;
    packet.flags = flags;
    packet.f70 = 0;
    quarter = 0.25f;
    vec_clear_128(&matrix[0]);
    vec_clear_128(&matrix[1]);
    vec_clear_128(&matrix[2]);
    matrix[0].v[0] = *(float *)(state + 0x10) + *(float *)(state + 0x10);
    matrix[1].v[1] = *(float *)(state + 0x10) + *(float *)(state + 0x10);
    matrix[2].v[2] = *(float *)(state + 0x10) * quarter;
    color = D_L00_001B0888 + (*(unsigned int *)(state + 0x24) << 24);
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    cam_compute_view_direction(object + 0x10, (char *)&offset, 1);
    FastVecScale(&offset, &offset, quarter);
    u_base = &packet.uv[0][0];
    v_base = &packet.uv[0][1];
    for (face = 0; face < 64; face++) {
        origin = (Vector *)(object + 0x10);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029AF40[D_L00_0029B440[face][corner][0]];
            int uv = D_L00_0029B440[face][corner][1];

            FastVecScale(&packet.vertex[corner], position, D_L00_001B088C);
            u_base[corner * 2] = D_L00_0029B840[uv][0];
            v_base[corner * 2] = D_L00_0029B840[uv][1];
            matrix_mul_vec3(&packet.vertex[corner], &packet.vertex[corner], matrix);
            matrix_mul_vec3(&packet.vertex[corner], &packet.vertex[corner], object + 0xC0);
            FastVecAdd(&packet.vertex[corner], &packet.vertex[corner], origin);
            FastVecAdd(&packet.vertex[corner], &packet.vertex[corner], &offset);
        }
        draw_world_quad(&packet, 0, 0);
    }
}

/* Draws a ball made of 64 textured quads around the object, a smaller version of the previous function. */
void gfx_draw_quad_sphere_small(char *object)
{
    RenderPacket packet;
    Vector matrix[3];
    Vector offset;
    char *state = *(char **)(object + 0x68);
    Vector *origin;
    float *u_base, *v_base;
    int face, corner;
    unsigned int color;
    long flags;

    packet.f78 = GetEffectTextureDescriptor(D_L00_001B0884);
    flags = (long)D_L00_001B0870;
    flags |= (long)D_L00_001B0874 << 2;
    flags |= (long)D_L00_001B0878 << 4;
    flags |= (long)D_L00_001B087C << 6;
    flags |= (long)D_L00_001B0880 << 32;
    packet.f80 = 0xFF9000000260L;
    packet.flags = flags;
    packet.f70 = 0;
    vec_clear_128(&matrix[0]);
    vec_clear_128(&matrix[1]);
    vec_clear_128(&matrix[2]);
    matrix[0].v[0] = *(float *)(state + 0x10);
    matrix[1].v[1] = *(float *)(state + 0x10);
    matrix[2].v[2] = *(float *)(state + 0x10) * 0.125f;
    color = D_L00_001B0888 + (*(unsigned int *)(state + 0x24) << 24);
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    cam_compute_view_direction(object + 0x10, (char *)&offset, 1);
    FastVecScale(&offset, &offset, 0.25f);
    u_base = &packet.uv[0][0];
    v_base = &packet.uv[0][1];
    for (face = 0; face < 64; face++) {
        origin = (Vector *)(object + 0x10);
        for (corner = 0; corner < 4; corner++) {
            Vector *position = &D_L00_0029AF40[D_L00_0029B440[face][corner][0]];
            int uv = D_L00_0029B440[face][corner][1];

            FastVecScale(&packet.vertex[corner], position, D_L00_001B088C);
            u_base[corner * 2] = D_L00_0029B840[uv][0];
            v_base[corner * 2] = D_L00_0029B840[uv][1];
            matrix_mul_vec3(&packet.vertex[corner], &packet.vertex[corner], matrix);
            matrix_mul_vec3(&packet.vertex[corner], &packet.vertex[corner], object + 0xC0);
            FastVecAdd(&packet.vertex[corner], &packet.vertex[corner], origin);
            FastVecAdd(&packet.vertex[corner], &packet.vertex[corner], &offset);
        }
        draw_world_quad(&packet, 0, 0);
    }
}

extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern float D_L00_001B0940 __attribute__((sda));
extern float D_L00_001B0944 __attribute__((sda));
extern float D_L00_001B0948 __attribute__((sda));
extern float D_L00_001B094C __attribute__((sda));
extern float D_L00_001B0950 __attribute__((sda));
extern float D_L00_001B0954 __attribute__((sda));

/* One 0x30-byte joint of the chain func_L00_003F5870 lays out. */
typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Places one joint of a table entry's chain at `position`: its angle, length and two
   rates come from level tuning values, then func_L00_003F5870 lays out its offset and
   the entry's joint count advances. The record offset is computed once and added to the
   reloaded chain pointer at every store, as retail's addu order shows. */
/* Adds one new joint to the Vaporizer chain at the given position with random-looking angle and speed values. */
void vaporizer_add_chain_joint(char *object, char *position)
{
    char *state = *(char **)(object + 0x68);
    char **table = (char **)level_get_slot_body(0xc04, *(short *)(state + 0x1a));
    short index = *(short *)(state + 0x20);
    char **entry;
    int offset = index * 0x30;
    entry = (char **)((*(short *)(state + 0x18) << 2) + (int)table);
    qcopy(((L00Joint *)(offset + (int)*entry))->position, position);
    ((L00Joint *)(offset + (int)*entry))->angle = math_wrap_angle_to_pi(IntToFloat(index) * 0.017453294f * D_L00_001B0948);
    ((L00Joint *)(offset + (int)*entry))->f28 = math_random_float_range(D_L00_001B0940, D_L00_001B0944) * 0.017453294f;
    ((L00Joint *)(offset + (int)*entry))->length = D_L00_001B094C;
    ((L00Joint *)(offset + (int)*entry))->f2c = math_random_signed_float_range(D_L00_001B0950, D_L00_001B0954) * 0.016666668f;
    vaporizer_set_chain_joint_offset(*entry, index);
    (*(unsigned short *)(state + 0x20))++;
}

/* BEGIN v2340 func_L00_003F0CC8 */

typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Vector impulse;
    int owner, flags;
    unsigned char enabled, kind;
    unsigned short object_class;
    float damage;
    int active;
} DamageRequest;

typedef struct {
    int pending, timer;
    char *first, *second;
    int light;
    float radius;
} EffectState;
typedef struct {
    int reserved[2];
    float intensity;
    int flags;
    Vector position;
} Light;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; QuadWord q[0x260]; } Hero;
extern u8 g_hero_state[];
extern Vector g_camera_l00_position, D_L00_001BF220;
extern float D_L00_00252F60[137][2];
extern char *g_area_hit_targets[];
extern Light D_L00_001C6F40[];
extern int D_L00_001B08D0 __attribute__((sda));
extern float math_random_angle(void);
extern float IntToFloat(int);
extern float math_square(float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecSub(Vector *, const Vector *, const Vector *);
extern void vec_scale_to_length(Vector *, const Vector *, float);
extern int CollLine(Vector *, Vector *, int, char *, int);
extern void part_claim_ring_piece(char *, Vector *, int);
extern void part_claim_debris_piece(char *);
extern int math_fast_float_d(int *);
extern int coll_process_hit(Vector *, int, char *, DamageRequest *, float);
extern void make_hit_descriptor(char *, int, int, float, Quad16 *);
extern void QueueMobyImpact(char *, DamageRequest *);
/* Retail passes the object in $a0 although the matched definition in src/game/00327038.c
   takes no parameters, so this caller declares it without a prototype. */
extern void math_init_random_direction_table();
extern void part_init_trail_sparkle_pairs(void *);
extern void moby_mark_spawned(void *);
extern void gfx_free_point_light(int);
extern float math_fast_sin_or_cos_a(float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void euler_rotation_basis(Vector *, const Vector *);
extern void part_update_debris_pieces(int);
extern void part_update_trail_nodes(s8 *);
extern void part_update_ring_pieces(char *);
/* The binder: func_L00_002E6EF8 in most programs, a per-level variant in levels 08, 09, 19 and 30. */
extern void ref_L00_003F0CC8_00(void (*)(void *), void *);
extern void gfx_update_screen_fade(void *);

/* Updates the lightning burst around the hero: sparks fly out, then nearby enemies are hurt and pushed away, then the glow fades and the object removes itself. */
void hero_lightning_burst_update(char *object)
{
    Vector point;
    DamageRequest request;
    DamageRequest *req;
    EffectState *state = *(EffectState **)(object + 0x68);
    char **hit;
    char *satellite;
    Light *light;
    int count, remaining, i;
    float progress, first_angle, second_angle;

    qcopy(object + 0x10, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        state->timer = 60;
        state->radius = 0.0f;
        for (i = 0; i < 137; i++) {
            D_L00_00252F60[i][0] = math_random_angle();
            D_L00_00252F60[i][1] = math_random_angle();
        }
    case 1:
        *(unsigned char *)(object + 0x20) = 2;
    case 2:
        progress = IntToFloat(state->timer);
        progress /= IntToFloat(60);
        state->radius = math_square(1.0f - progress) * 15.0f;
        if (state->timer % 3 == 0) {
            first_angle = math_random_angle();
            second_angle = math_random_angle();
            vec_build_spherical_offset(point.v, state->radius, first_angle, second_angle);
            FastVecAdd(&point, &point, (Vector *)&((Hero *)g_hero_state)->b[0xE0]);
            if (CollLine((Vector *)&((Hero *)g_hero_state)->b[0xE0], &point, 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0) != 0)
                qcopy(&point, &D_L00_001BF220);
            part_claim_ring_piece(object, &point, 10);
        }
        if (state->timer < 10 && (state->timer & 7) == 0)
            part_claim_debris_piece(object);
        if (math_fast_float_d(&state->timer) != 0) {
            state->timer = 120;
            *(unsigned char *)(object + 0x20) = 3;
            count = coll_process_hit((Vector *)&((Hero *)g_hero_state)->b[0xE0], 0, object, 0, 15.0f);
            if (count > 0) {
                hit = g_area_hit_targets;
                remaining = count;
                do {
                    req = &request;
                    if ((*(unsigned long long *)(*hit + 0x30) & 0x500000000000ULL) != 0 &&
                        *hit != ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(short *)(*hit + 0xaa) != 0xce7 /* moby class 3303 */ &&
                        *(short *)(*hit + 0xaa) != 0xbb8 /* Space Tourist */) {
                        FastVecSub(&point, (Vector *)(*hit + 0x10), (Vector *)&((Hero *)g_hero_state)->b[0xE0]);
                        vec_scale_to_length(&point, &point, 1.0f);
                        /* The incoming request impulse is not initialized in retail. */
                        vec_scale_to_length(&req->impulse, &req->impulse, 1.0f);
                        make_hit_descriptor((char *)req, (int)object, 0x830000, 30.0f, (Quad16 *)&point);
                        request.impulse.word = point.word;
                        request.active = 1;
                        request.impulse.v[3] = 5627.9248f;
                        request.enabled = 5;
                        request.kind = 3;
                        request.object_class = *(unsigned short *)(*hit + 0xaa);
                        QueueMobyImpact(*hit, req);
                    }
                    ++hit;
                } while (--remaining != 0);
            }
            math_init_random_direction_table(object);
        }
        break;
    case 3:
        if ((state->timer & 7) == 0) part_claim_debris_piece(object);
        math_fast_float_d(&state->timer);
        part_init_trail_sparkle_pairs(object);
        if (state->timer == 40) *(unsigned char *)(object + 0x20) = 4;
        break;
    case 4:
        if (math_fast_float_d(&state->timer) != 0 && state->pending == 0) {
            if (state->first != 0) moby_mark_spawned(state->first);
            if (state->second != 0) moby_mark_spawned(state->second);
            if (state->light != -1) gfx_free_point_light(state->light);
            D_L00_001B08D0 = 0;
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    progress = IntToFloat(state->timer) / IntToFloat(120);
    progress = 1.0f - progress;
    progress *= 6.2831855f;
    progress -= 3.1415927f;
    progress = math_fast_sin_or_cos_a(progress);
    progress = (progress + 1.0f) * 0.5f;
    if (state->first != 0) {
        **(int **)(state->first + 0x68) = FloatToInt(progress * 32.0f);
        *(float *)(state->first + 0xf8) = FastAddRotations(*(float *)(state->first + 0xf8), 0.052359887f);
        satellite = state->first;
        euler_rotation_basis((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->first + 0xc0) *= 0.5f;
        *(float *)(state->first + 0xd4) *= 0.5f;
        *(float *)(state->first + 0xe8) = progress * 1.5f;
        qcopy(state->first + 0x10, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->second != 0) {
        **(int **)(state->second + 0x68) = FloatToInt(progress * 32.0f);
        *(float *)(state->second + 0xf8) = fast_subtract_rotations(*(float *)(state->second + 0xf8), 0.052359887f);
        satellite = state->second;
        euler_rotation_basis((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->second + 0xe8) = progress;
        qcopy(state->second + 0x10, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->light != -1) {
        light = &D_L00_001C6F40[state->light];
        vec_scale_to_length(&point, (Vector *)&((Hero *)g_hero_state)->b[0x2A0], 0.5f);
        FastVecAdd(&light->position, (Vector *)(((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10), &point);
        FastVecSub(&point, &g_camera_l00_position, &light->position);
        vec_scale_to_length(&point, &point, 0.15f);
        FastVecAdd(&light->position, &light->position, &point);
        light->intensity = progress;
        light->position.v[3] = 5.0f;
        light->flags = 0;
    }
    part_update_debris_pieces((int)object);
    part_update_trail_nodes((s8 *)object);
    part_update_ring_pieces(object);
    ref_L00_003F0CC8_00(gfx_update_screen_fade, object);
}
