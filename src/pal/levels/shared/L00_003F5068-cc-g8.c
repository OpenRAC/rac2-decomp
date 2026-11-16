#include "names.h"
/* func_PAL_L00_003F5068, the PAL copy of func_L00_003F0CC8: the same C, where rename func_0032B598 becomes func_PAL_0032CDB0; rename func_0032ABC0 becomes func_PAL_0032C3B0; rename func_0032AA30 becomes func_PAL_0032C220. */
#include "common.h"

/* A body whose retail bytes address its global through $gp in ordinary flow: the assembler
   only selects that form when the back end emits the .extern size directive, which the
   pinned profile does at -G8 (see docs/build/compiler-notes.md). */
/* Per-frame update of the player's gadget table: it walks the records of one table
   entry, scales each record's pair of floats and asks the slot manager to refresh
   them, then folds the two level globals into the table's offset. */

extern float FastAddRotations(float a0, float a1);

/* func_L00_003EFA98 and func_L00_003EFD00: two 64-face quad renderers. Each builds a textured
   packet from the level's $gp tuning words, scales a diagonal matrix by the object's size, and
   per face takes four corners and UVs from the face table, transforms them through the matrix,
   the object's basis (0xC0) and position (0x10) plus an offset, and draws the quad. */

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
extern Vector g_quad_sphere_vertices[];
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
/* One 0x30-byte joint of the chain func_L00_003F5870 lays out. */
/* Places one joint of a table entry's chain at `position`: its angle, length and two
   rates come from level tuning values, then func_L00_003F5870 lays out its offset and
   the entry's joint count advances. The record offset is computed once and added to the
   reloaded chain pointer at every store, as retail's addu order shows. */
/* BEGIN v2340 func_PAL_L00_003F5068 */

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
extern Vector g_camera_l00_position, g_hero_l00_position;
extern float g_lightning_burst_angles[137][2];
extern char *g_area_hit_targets[];
extern Light g_light_table[];
extern int g_lightning_burst_object __attribute__((sda));
extern float math_random_angle(void);
extern float IntToFloat(int);
extern float math_square(float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecSub(Vector *, const Vector *, const Vector *);
extern void vec_scale_to_length(Vector *, const Vector *, float);
extern int CollLine(Vector *, Vector *, int, char *, int);
extern void part_claim_ring_piece_pal(char *, Vector *, int);
extern void part_claim_debris_piece_pal(char *);
extern int math_fast_float_d(int *);
extern int coll_process_hit(Vector *, int, char *, DamageRequest *, float);
extern void make_hit_descriptor(char *, int, int, float, Quad16 *);
extern void QueueMobyImpact(char *, DamageRequest *);
/* Retail passes the object in $a0 although the matched definition in src/game/00327038.c
   takes no parameters, so this caller declares it without a prototype. */
extern void math_init_random_direction_table();
extern void part_init_trail_sparkle_pairs_pal(void *);
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

/* Updates the hero lightning burst: sparks and rings grow around the hero, then everything nearby takes damage, and the effect fades out (PAL: 50 Hz). */
void hero_lightning_burst_update_pal(char *object)
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
        state->timer = 50;
        state->radius = 0.0f;
        for (i = 0; i < 137; i++) {
            g_lightning_burst_angles[i][0] = math_random_angle();
            g_lightning_burst_angles[i][1] = math_random_angle();
        }
    case 1:
        *(unsigned char *)(object + 0x20) = 2;
    case 2:
        progress = IntToFloat(state->timer);
        progress /= IntToFloat(50);
        state->radius = math_square(1.0f - progress) * 15.0f;
        if (state->timer % 3 == 0) {
            first_angle = math_random_angle();
            second_angle = math_random_angle();
            vec_build_spherical_offset(point.v, state->radius, first_angle, second_angle);
            FastVecAdd(&point, &point, (Vector *)&((Hero *)g_hero_state)->b[0xE0]);
            if (CollLine((Vector *)&((Hero *)g_hero_state)->b[0xE0], &point, 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0) != 0)
                qcopy(&point, &g_hero_l00_position);
            part_claim_ring_piece_pal(object, &point, 8);
        }
        if (state->timer < 8 && (state->timer & 7) == 0)
            part_claim_debris_piece_pal(object);
        if (math_fast_float_d(&state->timer) != 0) {
            state->timer = 100;
            *(unsigned char *)(object + 0x20) = 3;
            count = coll_process_hit((Vector *)&((Hero *)g_hero_state)->b[0xE0], 0, object, 0, 15.0f);
            if (count > 0) {
                hit = g_area_hit_targets;
                remaining = count;
                do {
                    req = &request;
                    if ((*(unsigned long long *)(*hit + 0x30) & 0x500000000000ULL) != 0 &&
                        *hit != ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(short *)(*hit + 0xaa) != 0xce7 &&
                        *(short *)(*hit + 0xaa) != 0xbb8) {
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
        if ((state->timer & 7) == 0) part_claim_debris_piece_pal(object);
        math_fast_float_d(&state->timer);
        part_init_trail_sparkle_pairs_pal(object);
        if (state->timer == 33) *(unsigned char *)(object + 0x20) = 4;
        break;
    case 4:
        if (math_fast_float_d(&state->timer) != 0 && state->pending == 0) {
            if (state->first != 0) moby_mark_spawned(state->first);
            if (state->second != 0) moby_mark_spawned(state->second);
            if (state->light != -1) gfx_free_point_light(state->light);
            g_lightning_burst_object = 0;
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    progress = IntToFloat(state->timer) / IntToFloat(100);
    progress = 1.0f - progress;
    progress *= 6.2831855f;
    progress -= 3.1415927f;
    progress = math_fast_sin_or_cos_a(progress);
    progress = (progress + 1.0f) * 0.5f;
    if (state->first != 0) {
        **(int **)(state->first + 0x68) = FloatToInt(progress * 32.0f);
        *(float *)(state->first + 0xf8) = FastAddRotations(*(float *)(state->first + 0xf8), 0.062831864f);
        satellite = state->first;
        euler_rotation_basis((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->first + 0xc0) *= 0.5f;
        *(float *)(state->first + 0xd4) *= 0.5f;
        *(float *)(state->first + 0xe8) = progress * 1.5f;
        qcopy(state->first + 0x10, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->second != 0) {
        **(int **)(state->second + 0x68) = FloatToInt(progress * 32.0f);
        *(float *)(state->second + 0xf8) = fast_subtract_rotations(*(float *)(state->second + 0xf8), 0.062831864f);
        satellite = state->second;
        euler_rotation_basis((Vector *)(satellite + 0xc0), (Vector *)(satellite + 0xf0));
        *(float *)(state->second + 0xe8) = progress;
        qcopy(state->second + 0x10, ((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
    }
    if (state->light != -1) {
        light = &g_light_table[state->light];
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
