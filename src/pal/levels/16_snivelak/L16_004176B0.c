#include "include_asm.h"


#include "common.h"
extern s32 func_313EA0(s32);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;
extern void RequestVoiceLine(u8 *, s32);
extern s32 math_fast_float_d(void *);
extern u8 *D_L16_001FE7C0[];
extern s32 FloatToInt(float);
extern s32 moby_apply_damage_to_object(void *, void *, s32);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;
extern L16VoiceState g_music_state;
extern int D_L16_001B1888[];
extern void STUB_printf(void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 coll_test_point(void *, s32, void *, float);

/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
void func_PAL_L16_00417D10(u8 *arg, s32 idx)
{
    L16VoiceState *voice = &g_music_state;
    u8 *s;

    s = *(u8 **)(arg + 0x68);
    if (voice->active == 0) {
        if (voice->key == -1 && idx != *(s32 *)(s + 0x354)) {
            if (idx < 20) {
                s32 v = *(s32 *)(s + (idx << 2) + 0x280);
                voice->selection = 0;
                voice->key = (v & 0x3FFF) + 0x7D0;
            } else {
                s32 v = *(s32 *)(s + ((idx - 20) << 2) + 0x2D0);
                voice->selection = 0;
                voice->key = (v & 0x3FFF) + 0x7D0;
            }
            STUB_printf(D_L16_001B1888);
            *(u8 *)(s + idx + 0x310) = 1;
            *(s32 *)(s + 0x350) = 0x2EE;
            *(s32 *)(s + 0x354) = idx;
        }
    }
}


extern s32 math_random_int_below(s32);
extern void snd_play_unplayed_voice_line(u8 *, s32, s32);
extern void func_PAL_L16_00417D10(u8 *, s32);

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void func_PAL_L16_00417DC0(u8 *arg, s32 start, s32 end)
{
    u8 *s3;
    s32 n;
    s32 i;
    s32 k;

    s3 = *(u8 **)(arg + 0x68);
    if (end < start)
        return;
    n = end - start + 1;
    k = math_random_int_below(n);
    for (i = 0; i < n; i++) {
        u8 *tbl = s3 + 0x310;

        if (tbl[start + k] == 0) {
            func_PAL_L16_00417D10(arg, start + k);
            return;
        }
        k = (k + 1) % n;
    }
    for (i = 0; i < n; i++)
        s3[0x310 + start + i] = 0;
    func_PAL_L16_00417D10(arg, start + k);
}


extern void moby_set_state(void *, s32, s32);
extern void func_PAL_L02_003294D8(s32, s32);
extern void script_queue_keyed_request(s32, s32);
extern void moby_set_flag_bit(void *, s32);
extern void level_capture_checkpoint_state(void *, void *);
extern int MemcardSave(s32, s32);
extern void func_PAL_L16_00417DC0(u8 *, s32, s32);
extern void snivelak_clean_up_arena_mobys(u8 *);
extern void SetMobyAndGroupsEnabled(u8 *, s32);

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
void func_PAL_L16_00417EB0(u8 *arg)
{
    u8 *s0;
    s32 a0;
    u8 *tbl;

    s0 = *(u8 **)(arg + 0x68);
    if (*(s32 *)(s0 + 0x1BC) != 0) {
        s32 h = *(s32 *)(s0 + 0x1B0);
        s32 m = *(s32 *)(s0 + 0x1B4);

        *(s32 *)(s0 + 0x1BC) = 0;
        func_PAL_L02_003294D8(h, m);
        a0 = *(s32 *)(s0 + 0x1B8) << 7;
        tbl = D_L16_001B2C0C[0];
        qcopy(arg + 0x10, tbl + 0x30 + a0);
        qcopy(arg + 0xF0, tbl + 0x70 + a0);
        script_queue_keyed_request(*(s32 *)(s0 + 0x1A4), -1);
    } else {
        script_queue_keyed_request(*(s32 *)(s0 + 0x1A4), *(s32 *)(s0 + 0x1AC));
    }
    D_0013963B = 1;
    snivelak_clean_up_arena_mobys(arg);
    SetMobyAndGroupsEnabled(arg, 1);
    moby_set_flag_bit(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 1);
    level_capture_checkpoint_state(D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x30,
                  D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x70);
    func_PAL_L16_00417DC0(arg, 0, 2);
    MemcardSave(0, -1);
    moby_set_state(arg, 2, 1);
}


extern void moby_mark_spawned(void *);
extern void moby_spin_group_entities(void *, float);
extern void moby_mark_flag_and_append_to_list(s32);
extern char g_hero_position[];

void func_PAL_L16_00417FD8(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    D_0013963B = 2;
    moby_spin_group_entities(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 0.0f);
    func_PAL_L02_003294D8(*(s32 *)(s0 + 0x188), *(s32 *)(s0 + 0x18C));
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    moby_mark_flag_and_append_to_list(0x11);
    if (*(s32 *)(s0 + 0x1F0) != 0)
        moby_mark_spawned((void *)*(s32 *)(s0 + 0x1F0));
    if (*(s32 *)(s0 + 0x238) != 0)
        moby_mark_spawned((void *)*(s32 *)(s0 + 0x238));
    if (*(s32 *)(s0 + 0x23C) != 0)
        moby_mark_spawned((void *)*(s32 *)(s0 + 0x23C));
    script_queue_keyed_request(*(s32 *)(s0 + 0x1A0), -1);
    MemcardSave(0, -1);
    moby_mark_spawned(arg0);
}




extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float D_L16_001B9B00[];
extern u16 *D_L16_001FB660[];
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern char *func_PAL_0032F3B8(void *, void *, void *, float);
extern int coll_sweep_from_object(void *, void *, s32, s32, s32, s32, float, float, float);
extern void mat_get_euler_angles(void *, void *);
extern void vec_random_direction(void *, float, float);
extern float math_random_float_range(float, float);
extern char *func_PAL_002735D0(void *, s32, s32, s32, void *, void *, void *, s32, float, float);

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
void func_PAL_L16_00418580(u8 *arg)
{
    float rotation[12];
    float toward[4];
    float velocity[4];
    u8 *state;
    u8 *basis;
    u8 *angles;
    s32 hit;
    u32 old;
    u32 age;
    s32 i;
    s32 kind;
    float speed;
    float life;

    state = *(u8 **)(arg + 0x68);
    switch (arg[0x20]) {
    case 0:
        FastVecAdd(arg + 0x10, arg + 0x10, state);
        if (math_fast_float_d(state + 0x30) && !arg[0x31])
            moby_mark_spawned(arg);
        break;
    case 2:
        FastVecAdd(arg + 0x10, arg + 0x10, state);
        basis = arg + 0xC0;
        *(float *)(state + 8) -= *(float *)(state + 0x34);
        quaternion_to_rotation_basis(state + 0x20, rotation);
        multiply_matrix3x3(basis, rotation, basis);
        hit = 0;
        if (part_find_owned_effect_slot(arg, 0x10000, 0))
            hit = 1;
        age = *(u16 *)(arg + 0x96);
        old = age++;
        *(u16 *)(arg + 0x96) = age;
        if (old > 75 && coll_test_point(arg + 0x10, 0, arg, 1.0f))
            hit = 1;
        if (hit) {
            FastVecSub(toward, D_L16_001B9B00, arg + 0x10);
            angles = arg + 0xF0;
            vec_scale_to_length(toward, toward, 1.0f);
            func_PAL_0032F3B8(arg, arg + 0x10, toward, 0.0f);
            coll_sweep_from_object(arg, arg + 0x10, 0x10001, 0, 1, 0, 4.0f, 20.0f, 2.0f);
            mat_get_euler_angles(basis, angles);
            for (i = 0; i < 6; i++) {
                vec_random_direction(velocity, 0.0f, 0.40000004f);
                FastVecAdd(velocity, velocity, state);
                kind = *(s16 *)(arg + 0xAA);
                speed = math_random_float_range(180.0f, 720.0f);
                life = math_random_float_range(5.0f, 15.0f);
                func_PAL_002735D0(arg, 2, kind, i, arg + 0x10, arg + 0xF0, velocity, 255, speed, life);
            }
            moby_mark_spawned(arg);
        }
        break;
    }
}

