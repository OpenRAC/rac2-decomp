/* func_PAL_L01_003B5970, the PAL copy of func_L01_003B1F08: the same C, where rename func_L01_003208D0 becomes func_PAL_L01_00322798; scale state- becomes returnWait; scale state- becomes returnWait; wrap state- becomes nextWait (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 mode;
    u8 index;
    u8 pad22[2];
    u8 *info;
    u8 pad28[0xC];
    u16 flags;
    u8 pad36[0x32];
    struct MoverState *state;
    u8 pad6C[0x2C];
    int timer;
    u8 pad9C[0x20];
    u8 triggered;
    u8 padBD[0x33];
    float rot[4];
} MoverObject;

typedef struct MoverState {
    u8 pad00[0x20];
    float motion[0x10];
    float homePos[4];
    float homeRot[4];
    int target;
    int waitDuration;
    float moveTime;
    int nextWait;
    u8 pad90[4];
    int returnWait;
    int cycles;
    float t;
    int wait;
    int cycleWait;
    int sound;
    u8 tailAC[1];
} MoverState;

typedef struct {
    u8 pad00[0x30];
    float pos[4];
    u8 pad40[0x30];
    float rot[4];
} MoverTarget;

extern int math_fast_float_d(void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecAdd(void *, void *, void *);
extern u8 g_sound_state[];
extern MoverTarget *g_swamp_patrol_positions __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern void snd_stop_voice(int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void moby_set_byte_on_group(int, int);
extern float math_move_angle_toward_target(float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void glow_flicker_update_pal(void *, void *, int);

#define CLEAR_SOUND() { \
    int id = state->sound; \
    if (id != -1) { \
        u8 *slot = D_00188660 + id * 0x70; \
        if (*(MoverObject **)(slot + 0x88) == moby && slot[0x74]) \
            func_002E59F8(id); \
    } \
    state->sound = -1; \
}

#define KEEP_SOUND() { \
    u8 *slot = D_00188660 + state->sound * 0x70; \
    if (*(MoverObject **)(slot + 0x88) != moby || !slot[0x74]) \
        state->sound = func_002E5DA0(0, 4, moby, 0x9EA); \
}

#define INTERPOLATE() { \
    weight = 1.0f - func_00283180(state->t * 3.1415927f); \
    weight *= 0.5f; \
    func_00282CF0(delta, D_L01_001B264C[state->target].pos, state->homePos); \
    func_00282D30(delta, delta, weight); \
    func_00282CC0(moby->pos, state->homePos, delta); \
    moby->rot[2] = func_002AA150(state->homeRot[2], D_L01_001B264C[state->target].rot[2], weight); \
    moby->rot[1] = func_002AA150(state->homeRot[1], D_L01_001B264C[state->target].rot[1], weight); \
    moby->rot[0] = func_002AA150(state->homeRot[0], D_L01_001B264C[state->target].rot[0], weight); \
}

/* Moves a platform between its home spot and a target spot. It waits, glides there, waits again and glides back, with a sound while it moves (PAL: 50 Hz timings). */
void eased_mover_moby_update_pal(MoverObject *moby)
{
    float old_pos[4] __attribute__((aligned(16)));
    float old_rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    MoverState *state = moby->state;
    float weight;

    qcopy(old_pos, moby->pos);
    qcopy(old_rot, moby->rot);
    switch (moby->mode) {
    case 0:
        moby->flags |= 0x2000;
        state->sound = -1;
        qcopy(state->homePos, moby->pos);
        qcopy(state->homeRot, moby->rot);
        moby_set_state(moby, 1, -1);
        moby->timer = 0;
        break;
    case 1:
        CLEAR_SOUND()
        if (moby->triggered) {
            state->cycleWait = state->cycles;
            state->wait = state->waitDuration;
            moby_set_state(moby, 2, -1);
            moby->timer = *(int *)(moby->info + 0x10);
        }
        break;
    case 2:
        if (math_fast_float_d(&state->wait)) {
            state->t = 0.0f;
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        state->t += 1.0f / state->moveTime;
        if (state->t > 1.0f)
            state->t = 1.0f;
        INTERPOLATE()
        if (state->t >= 1.0f) {
            if (state->nextWait == -1) {
                moby_set_state(moby, 5, -1);
            } else {
                state->wait = (((int)(state->nextWait) * 5 + 2) / 6);
                moby_set_state(moby, 4, -1);
            }
        }
        KEEP_SOUND()
        break;
    case 4:
        CLEAR_SOUND()
        if (math_fast_float_d(&state->wait)) {
            state->t = 1.0f;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 5:
        CLEAR_SOUND()
        if (moby->triggered) {
            state->wait = state->waitDuration;
            moby->triggered = 0;
            moby_set_state(moby, 4, -1);
        }
        break;
    case 6:
        state->t -= 1.0f / state->moveTime;
        if (state->t < 0.0f)
            state->t = 0.0f;
        INTERPOLATE()
        if (state->t <= 0.0f) {
            if (state->cycles == -1) {
                state->wait = (((int)(state->returnWait) * 5 + 2) / 6);
                moby_set_state(moby, 7, -1);
            } else if (math_fast_float_d(&state->cycleWait)) {
                moby_set_byte_on_group(moby->index, 0);
                moby_set_state(moby, 1, -1);
                moby->timer = 0;
            } else {
                state->wait = (((int)(state->returnWait) * 5 + 2) / 6);
                moby_set_state(moby, 7, -1);
            }
        }
        KEEP_SOUND()
        break;
    case 7:
        CLEAR_SOUND()
        if (math_fast_float_d(&state->wait)) {
            state->t = 0.0f;
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    moby->triggered = 0;
    if (moby->mode < 8) {
        FastVecSub(delta, moby->pos, old_pos);
        mat_combine_and_store(state->motion, delta, old_rot, moby->rot);
    }
    glow_flicker_update_pal(moby, state->tailAC, moby->mode >= 2);
}
