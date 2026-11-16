#include "include_asm.h"


#include "common.h"
extern s32 func_313EA0(s32);
extern u8 *g_beam_definition_table[] __attribute__((sda));
extern u8 g_snivelak_boss_state;
extern void RequestVoiceLine(u8 *, s32);
extern s32 math_fast_float_d(void *);
extern u8 *g_path_l16_table[];
extern s32 FloatToInt(float);
extern s32 moby_apply_damage_to_object(void *, void *, s32);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern u8 *g_moby_instance_table[] __attribute__((sda));
extern s32 g_group_id_limit[] __attribute__((sda));
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;
extern L16VoiceState g_music_state;
extern int g_snivelak_anim_params[];
extern void STUB_printf(void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 coll_test_point(void *, s32, void *, float);

/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
void RequestVoiceLine_pal(u8 *moby, s32 idx)
{
    L16VoiceState *voice = &g_music_state;
    u8 *state;

    state = *(u8 **)(moby + 0x68);
    if (voice->active == 0) {
        if (voice->key == -1 && idx != *(s32 *)(state + 0x354)) {
            if (idx < 20) {
                s32 entry = *(s32 *)(state + (idx << 2) + 0x280);
                voice->selection = 0;
                voice->key = (entry & 0x3FFF) + 0x7D0;
            } else {
                s32 entry = *(s32 *)(state + ((idx - 20) << 2) + 0x2D0);
                voice->selection = 0;
                voice->key = (entry & 0x3FFF) + 0x7D0;
            }
            STUB_printf(g_snivelak_anim_params);
            *(u8 *)(state + idx + 0x310) = 1;
            *(s32 *)(state + 0x350) = 0x2EE;
            *(s32 *)(state + 0x354) = idx;
        }
    }
}


extern s32 math_random_int_below(s32);
extern void snd_play_unplayed_voice_line(u8 *, s32, s32);
extern void RequestVoiceLine_pal(u8 *, s32);

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void snd_play_unplayed_voice_line_pal(u8 *moby, s32 start, s32 end)
{
    u8 *state;
    s32 count;
    s32 i;
    s32 index;

    state = *(u8 **)(moby + 0x68);
    if (end < start)
        return;
    count = end - start + 1;
    index = math_random_int_below(count);
    for (i = 0; i < count; i++) {
        u8 *played_flags = state + 0x310;

        if (played_flags[start + index] == 0) {
            RequestVoiceLine_pal(moby, start + index);
            return;
        }
        index = (index + 1) % count;
    }
    for (i = 0; i < count; i++)
        state[0x310 + start + i] = 0;
    RequestVoiceLine_pal(moby, start + index);
}


extern void moby_set_state(void *, s32, s32);
extern void part_start_record_effect_by_index_pal(s32, s32);
extern void script_queue_keyed_request(s32, s32);
extern void moby_set_flag_bit(void *, s32);
extern void level_capture_checkpoint_state(void *, void *);
extern int MemcardSave(s32, s32);
extern void snd_play_unplayed_voice_line_pal(u8 *, s32, s32);
extern void snivelak_clean_up_arena_mobys(u8 *);
extern void SetMobyAndGroupsEnabled(u8 *, s32);

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
void snivelak_finish_boss_intro_state_pal(u8 *moby)
{
    u8 *state;
    s32 offset;
    u8 *beam_table;

    state = *(u8 **)(moby + 0x68);
    if (*(s32 *)(state + 0x1BC) != 0) {
        s32 effect_id = *(s32 *)(state + 0x1B0);
        s32 effect_arg = *(s32 *)(state + 0x1B4);

        *(s32 *)(state + 0x1BC) = 0;
        part_start_record_effect_by_index_pal(effect_id, effect_arg);
        offset = *(s32 *)(state + 0x1B8) << 7;
        beam_table = g_beam_definition_table[0];
        qcopy(moby + 0x10, beam_table + 0x30 + offset);
        qcopy(moby + 0xF0, beam_table + 0x70 + offset);
        script_queue_keyed_request(*(s32 *)(state + 0x1A4), -1);
    } else {
        script_queue_keyed_request(*(s32 *)(state + 0x1A4), *(s32 *)(state + 0x1AC));
    }
    g_snivelak_boss_state = 1;
    snivelak_clean_up_arena_mobys(moby);
    SetMobyAndGroupsEnabled(moby, 1);
    moby_set_flag_bit(g_moby_instance_table[0] + (*(s32 *)(state + 0x190) << 8), 1);
    level_capture_checkpoint_state(g_beam_definition_table[0] + (*(s32 *)(state + 0x198) << 7) + 0x30,
                  g_beam_definition_table[0] + (*(s32 *)(state + 0x198) << 7) + 0x70);
    snd_play_unplayed_voice_line_pal(moby, 0, 2);
    MemcardSave(0, -1);
    moby_set_state(moby, 2, 1);
}


extern void moby_mark_spawned(void *);
extern void moby_spin_group_entities(void *, float);
extern void moby_mark_flag_and_append_to_list(s32);
extern char g_hero_position[];

/* Cleans up the boss and its parts when the fight ends, then frees the object. */
void snivelak_clean_up_boss_and_free_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);

    g_snivelak_boss_state = 2;
    moby_spin_group_entities(g_moby_instance_table[0] + (*(s32 *)(state + 0x190) << 8), 0.0f);
    part_start_record_effect_by_index_pal(*(s32 *)(state + 0x188), *(s32 *)(state + 0x18C));
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    moby_mark_flag_and_append_to_list(0x11);
    if (*(s32 *)(state + 0x1F0) != 0)
        moby_mark_spawned((void *)*(s32 *)(state + 0x1F0));
    if (*(s32 *)(state + 0x238) != 0)
        moby_mark_spawned((void *)*(s32 *)(state + 0x238));
    if (*(s32 *)(state + 0x23C) != 0)
        moby_mark_spawned((void *)*(s32 *)(state + 0x23C));
    script_queue_keyed_request(*(s32 *)(state + 0x1A0), -1);
    MemcardSave(0, -1);
    moby_mark_spawned(moby);
}




extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float g_scene_origin_transform[];
extern u16 *g_group_l16_id_lists[];
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern char *part_spawn_blast_effect_moby_pal(void *, void *, void *, float);
extern int coll_sweep_from_object(void *, void *, s32, s32, s32, s32, float, float, float);
extern void mat_get_euler_angles(void *, void *);
extern void vec_random_direction(void *, float, float);
extern float math_random_float_range(float, float);
extern char *cam_moby_create_pal(void *, s32, s32, s32, void *, void *, void *, s32, float, float);

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
void debris_l16_piece_update_pal(u8 *moby)
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

    state = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        if (math_fast_float_d(state + 0x30) && !moby[0x31])
            moby_mark_spawned(moby);
        break;
    case 2:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        basis = moby + 0xC0;
        *(float *)(state + 8) -= *(float *)(state + 0x34);
        quaternion_to_rotation_basis(state + 0x20, rotation);
        multiply_matrix3x3(basis, rotation, basis);
        hit = 0;
        if (part_find_owned_effect_slot(moby, 0x10000, 0))
            hit = 1;
        age = *(u16 *)(moby + 0x96);
        old = age++;
        *(u16 *)(moby + 0x96) = age;
        if (old > 75 && coll_test_point(moby + 0x10, 0, moby, 1.0f))
            hit = 1;
        if (hit) {
            FastVecSub(toward, g_scene_origin_transform, moby + 0x10);
            angles = moby + 0xF0;
            vec_scale_to_length(toward, toward, 1.0f);
            part_spawn_blast_effect_moby_pal(moby, moby + 0x10, toward, 0.0f);
            coll_sweep_from_object(moby, moby + 0x10, 0x10001, 0, 1, 0, 4.0f, 20.0f, 2.0f);
            mat_get_euler_angles(basis, angles);
            for (i = 0; i < 6; i++) {
                vec_random_direction(velocity, 0.0f, 0.40000004f);
                FastVecAdd(velocity, velocity, state);
                kind = *(s16 *)(moby + 0xAA);
                speed = math_random_float_range(180.0f, 720.0f);
                life = math_random_float_range(5.0f, 15.0f);
                cam_moby_create_pal(moby, 2, kind, i, moby + 0x10, moby + 0xF0, velocity, 255, speed, life);
            }
            moby_mark_spawned(moby);
        }
        break;
    }
}

