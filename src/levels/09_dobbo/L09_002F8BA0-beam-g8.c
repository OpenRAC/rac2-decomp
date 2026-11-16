#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float IntToFloat(int);
extern void func_002A7750_3(unsigned char *, int, int);
extern void anim_start_blended(unsigned char *, int, int, int);
extern int math_fast_float_d(char *);
extern void vec_add_random_offset(void *, float);
extern int math_random_int_below(int);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(void *, void *, float);
extern float g_beam_angle_min __attribute__((sda)), g_beam_angle_max __attribute__((sda));
extern float g_beam_blend_rate __attribute__((sda)), g_beam_l09_scale_factor __attribute__((sda));
extern float g_beam_scale_multiplier __attribute__((sda));
extern int g_beam_alpha_min __attribute__((sda)), g_beam_alpha_max __attribute__((sda));
extern unsigned char g_beam_alpha_step __attribute__((sda));
extern char g_hero_position[];
extern char g_beam_basis_vector[] MACRO_ADDR;
extern void *g_collision_hit_object NOT_SDA;
extern char *g_hero_moby NOT_SDA;
extern float math_square(float);
extern void moby_mark_spawned(void *);
extern int ReleaseRecordSlot(void *);
extern int UpdateBeamLinkRecord(void *, void *);
extern void moby_blend_pos_toward_target(unsigned char *, float);
extern void moby_rescale_vector(unsigned char *);
extern float vec_distance_xy(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern int coll_cast_object_line(void *, void *, void *, int, int, int, int, float, float);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);

/* Region limits of the level: while `mode` is set, a beam link on the wrong side of `low` (or,
   in mode 2, of `high`) is destroyed. */
typedef struct {
    int side;
    char pad04[8];
    int mode;
    char pad10[0x18];
    float low;
    char pad2C[0xC];
    float high;
} DobboLimits;

typedef struct DobboMoby DobboMoby;

/* State block of a beam link (class 0xD09), at its +0x68. */
typedef struct {
    float direction[4];
    float velocity[4];
    DobboMoby *owner;
    DobboMoby *partner;
    float radius;
    float f2c;
    int timer;
    float max_distance;
    float duration_f;
    int hit_timer;
} DobboLinkState;

typedef struct {
    char pad00[0x24];
    float scale;
} DobboMobyClass;

/* Fields shared by the beam link and its owner. */
struct DobboMoby {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[2];
    unsigned char alpha;
    DobboMobyClass *cls;
    char pad28[4];
    float scale;
    unsigned char f30;
    unsigned char f31;
    unsigned short f32;
    unsigned short flags;
    char pad36[0x43 - 0x36];
    unsigned char f43;
    char pad44[4];
    float f48;
    char pad4C[0x60 - 0x4C];
    unsigned char f60;
    char pad61[0x68 - 0x61];
    DobboLinkState *data;
    char pad6C[0xAA - 0x6C];
    short type;
    char padAC[0xBC - 0xAC];
    unsigned char f_bc;
    char padBD[0xF0 - 0xBD];
    float rotation[3];
};

extern DobboLimits g_dobbo_limits;

/* Steps a beam link (class 0xD09) once per frame: spins it, runs its state (ramp up, hold, fade
   out and destroy once its owner is gone, too far or past the level limits), damages what the
   beam touches near the player and passes the link's basis to func_L09_003FB908. */
void UpdateBeamLink(DobboMoby *moby)
{
    DobboLinkState *state;
    DobboMoby *owner;
    Vec ray_start, ray_end, basis[4];
    float distance;
    int hit;

    if (g_dobbo_limits.mode) {
        if (moby->position[2] < g_dobbo_limits.low && g_dobbo_limits.side == 1)
            goto destroy;
        if (g_dobbo_limits.low < moby->position[2] && !g_dobbo_limits.side)
            goto destroy;
        if (g_dobbo_limits.mode == 2) {
            if (g_dobbo_limits.high < moby->position[2] && g_dobbo_limits.side == 1)
                goto destroy;
            if (moby->position[2] < g_dobbo_limits.high && g_dobbo_limits.side == 2)
                goto destroy;
        }
    }
    state = moby->data;
    /* each axis draws its own random turn */
    moby->rotation[0] = FastAddRotations(moby->rotation[0],
        math_random_float_range(g_beam_angle_min * 0.017453294f, g_beam_angle_max * 0.017453294f));
    moby->rotation[1] = FastAddRotations(moby->rotation[1],
        math_random_float_range(g_beam_angle_min * 0.017453294f, g_beam_angle_max * 0.017453294f));
    moby->rotation[2] = FastAddRotations(moby->rotation[2],
        math_random_float_range(g_beam_angle_min * 0.017453294f, g_beam_angle_max * 0.017453294f));
    switch (moby->state) {
    case 0:
        func_002A7750_3((unsigned char *)moby, 1, -1);
        break;
    case 1:
        if (moby->f60 & 2) {
            if (moby->f43 != 1)
                anim_start_blended((unsigned char *)moby, 1, 0, 10);
            moby->f48 = 2;
        }
        moby_blend_pos_toward_target((unsigned char *)moby,
            g_beam_l09_scale_factor * math_square(1.0f - IntToFloat(state->timer) / state->duration_f));
        if (math_fast_float_d((char *)&state->timer))
            func_002A7750_3((unsigned char *)moby, 2, -1);
        if (!state->owner || state->owner->state == 254 || state->owner->state == 253)
            func_002A7750_3((unsigned char *)moby, 3, -1);
        break;
    case 2:
    case 3:
        if (moby->f60 & 2) {
            if (moby->f43 != 1)
                anim_start_blended((unsigned char *)moby, 1, 0, 10);
            moby->f48 = 2;
        }
        moby_blend_pos_toward_target((unsigned char *)moby, g_beam_blend_rate);
        moby_rescale_vector((unsigned char *)moby);
        owner = state->owner;
        if (state->max_distance < vec_distance_xy(moby->position, owner->position) || !state->owner ||
            state->owner->state == 254 || state->owner->state == 253)
            func_002A7750_3((unsigned char *)moby, 3, -1);
        if (moby->state == 3) {
            if (moby->alpha < g_beam_alpha_min) {
            destroy:
                ReleaseRecordSlot(moby);
                moby_mark_spawned(moby);
                return;
            }
            moby->scale *= g_beam_scale_multiplier;
            moby->alpha -= g_beam_alpha_min;
        }
        break;
    }
    distance = vec_distance_xy(moby->position, g_hero_position);
    if (distance < state->radius * 2 + 1) {
        owner = state->owner;
        if (owner && owner->type == 0xCEA && owner->state != 254 && owner->state != 253) {
            DobboMoby *partner = state->partner;
            if (partner && partner->type == 0xD09 && partner->state != 254 && partner->state != 253) {
                hit = 0;
                if (moby->f_bc == 1 && owner->data) {
                    qcopy(&ray_start, moby->position);
                    qcopy(&ray_end, partner->position);
                    vec_add_random_offset(&ray_start, 0.1f);
                    vec_add_random_offset(&ray_end, 0.1f);
                    if (coll_cast_object_line(state->owner, &ray_start, &ray_end, 0x210001, 0, 1, 0,
                                          state->f2c, 1)) {
                        if (g_collision_hit_object == *(void **)(g_hero_position + 0x2210))
                            hit = 1;
                    }
                }
                if (!math_random_int_below(4) && distance < 2 &&
                    coll_sweep_from_object(state->owner, moby->position, 0x210001, 0, 1, 0,
                                  moby->scale * 0.4f / moby->cls->scale, state->f2c, 1)) {
                    if (g_collision_hit_object == g_hero_moby)
                        hit = 1;
                }
                if (math_fast_float_d((char *)&state->hit_timer) && hit)
                    state->hit_timer = 60;
            }
        }
    }
    if (moby->state != 3) {
        moby->alpha += g_beam_alpha_step;
        if (moby->alpha > g_beam_alpha_max)
            moby->alpha = g_beam_alpha_max;
    }
    if (moby->f_bc == 1) {
        DobboMoby *partner = state->partner;
        if (partner && partner->state != 254 && partner->state != 253) {
            FastVecSub(basis[0].f, partner->position, moby->position);
            vec_scale_to_length(basis, basis, 1);
            qcopy(&basis[2], g_beam_basis_vector);
            FastVecCross(&basis[2], basis, &basis[1]);
            qcopy(&basis[3], moby->position);
            UpdateBeamLinkRecord(moby, basis);
        }
    }
}
