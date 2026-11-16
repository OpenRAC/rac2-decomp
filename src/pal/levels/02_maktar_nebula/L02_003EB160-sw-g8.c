#include "include_asm.h"

#include "common.h"
extern float g_slot_effect_rate_range[] __attribute__((sda));
typedef union { u8 b[0x200]; u32 w[0x80]; } GameFlags;
extern u8 g_game_flag_table[];
#define FLAG (((GameFlags *)D_001395B8)->b[0x8F])
extern int g_slot_machine_prize_weights[] __attribute__((sda));
extern char g_str_slot_debug_a[], g_str_slot_debug_b[];
extern char g_sound_state[];
typedef union { u8 b[0x2600]; f32 f[0x980]; } Hero;
extern u8 g_hero_state[];
extern char g_zero_l02_vector[] __attribute__((sda));
extern int g_hovering_object_count, g_player_bolts;
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void DrawScrollingTileBands(char *);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int), flag_set_first_pending(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void func_L00_0030C710(int);
extern void STUB_printf(char *, ...);
extern int math_is_value_within_step_pal(char *, float);
extern int PlayMobySound(int, int, void *);
extern void slot_machine_update_reels_pal(void *), slot_machine_award_prize_pal(void *), snd_stop_voice(int);
extern void anim_start_immediate(void *, int, int);
extern void part_spawn_slot_machine_debris_pal(void *);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void part_init_effect_record(void *, void *, int, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern char *moby_find_group_in_state_13(int);
extern void moby_teleport_to_new_pose(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern void moby_mark_spawned(void *);
extern char *part_find_owned_effect_slot(void *, int, int);
extern void slot_machine_roll_result(void *);
typedef struct { char pad[0x18]; u8 kind; u8 flags; short source_class; char tail[0x14]; } Hit003E6D70;
typedef struct { char pad[0xAA]; short class_id; } SlotActor003E6D70;
typedef struct {
    char pad0[0x20]; float health; short count; char pad26[10];
    float multiplier; char pad34[0x2C]; float reel[3];
    char pad6c[0x38]; int destroyed;
} SlotState003E6D70;

/* Updates the slot-machine actor. State 0 sets it up and rolls the three reel rates; 2 counts the
   spin (past the 36th, moving 40 of weight 1's share to weight 5) and waits for its animation; 3
   and 4 hand over to their own updates; 5 destroys it, with a blast and two prizes when the word at
   +0xA4 is set. Every state but 5 then takes a hit: a hard one from a class other than 0 and 0x47
   destroys it, and in state 1 one from class 0x47 spends ten bolts and starts a spin. */
void UpdateSlotMachine_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float point[4];
    Hit003E6D70 hit;
    float prize_point[4];
    char *contact, *other;
    int i, voice_index;
    float *rate;
    float zero;
    SlotState003E6D70 *init_state = (SlotState003E6D70 *)state;
    if (*(unsigned char *)(moby + 0x31)) gfx_add_draw_callback_first(DrawScrollingTileBands, moby);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
    moby_set_state(moby, 1, -1);
    init_state->health = 3.0f;
    init_state->count = 3;
    init_state->multiplier = 1.0f;
    zero = 0.0f;
    init_state->destroyed = 0;
    init_state->reel[2] = zero;
    init_state->reel[1] = zero;
    init_state->reel[0] = zero;
    rate = (float *)(state + 0x84);
    for (i = 2; i >= 0; i--) *rate++ = math_random_float_range(g_slot_effect_rate_range[0], g_slot_effect_rate_range[1]) * 0.020000001f;
    if (math_random_int_below(2)) *(unsigned short *)(moby + 0x34) |= 0x8000;
    else *(unsigned short *)(moby + 0x34) &= 0x7FFF;
    *(unsigned short *)(moby + 0x34) |= 0x4000;
        break;
    case 2:
    if (flag_set_first_pending(moby)) {
        if (*(unsigned char *)(moby + 0x43) != 1) anim_start_blended_pal(moby, 1, 0, 1);
        func_L00_0030C710(0xC8);
        if (FLAG < 0x7F) FLAG++;
        if (FLAG > 0x24 && g_slot_machine_prize_weights[5] < 30) {
            g_slot_machine_prize_weights[5] += 40;
            g_slot_machine_prize_weights[1] -= 40;
            STUB_printf(g_str_slot_debug_a);
        }
        STUB_printf(g_str_slot_debug_b, FLAG);
    }
    if (*(unsigned char *)(moby + 0x43) == 1) {
        if (*(unsigned char *)(moby + 0x60) & 2) {
            *(unsigned short *)(moby + 0x96) = 0;
            anim_start_blended_pal(moby, 0, 0, 1);
            moby_set_state(moby, 3, -1);
        } else if (math_is_value_within_step_pal(moby, 10.0f)) {
            char *slot = g_sound_state + *(int *)(state + 0x54) * 0x70;
            if (*(char **)(slot + 0x88) != moby || *(unsigned char *)(slot + 0x74) == 0)
                *(int *)(state + 0x54) = PlayMobySound(1, 4, moby);
        }
    }
        break;
    case 3:
    slot_machine_update_reels_pal(moby);
        break;
    case 4:
    if (flag_set_first_pending(moby)) {
        char *slot;
        voice_index = *(int *)(state + 0x54);
        *(int *)(state + 0x50) = 50;
        if (voice_index != -1) {
            slot = g_sound_state + voice_index * 0x70;
            if (*(char **)(slot + 0x88) == moby && *(unsigned char *)(slot + 0x74)) snd_stop_voice(voice_index);
        }
        *(int *)(state + 0x54) = -1;
    }
    slot_machine_award_prize_pal(moby);
        break;
    case 5:
    {
        char *slot;
        voice_index = *(int *)(state + 0x54);
        if (voice_index != -1) {
            slot = g_sound_state + voice_index * 0x70;
            if (*(char **)(slot + 0x88) == moby && *(unsigned char *)(slot + 0x74)) snd_stop_voice(voice_index);
        }
    }
    *(int *)(state + 0x54) = -1;
    anim_start_immediate(moby, 0, 0);
    PlayMobySound(0, 0, moby);
    part_spawn_slot_machine_debris_pal(moby);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xBFFF) | 2;
    if (*(int *)(state + 0xA4)) {
        moby_compute_local_point(moby, point, 0.0f, 0.0f, 1.5f);
        part_init_effect_record(&hit, moby, 0x810001, 2.0f);
        hit.kind = 2;
        hit.flags = 1;
        hit.source_class = ((SlotActor003E6D70 *)moby)->class_id;
        coll_process_hit(point, 16, moby, &hit, 4.0f);
        SpawnExplosion_pal(moby + 0x10, 1, 25, 20, 20, 20, 45, 0, 1, 1, 0, 0, 1.5f, 20.0f);
        if (*(int *)(state + 0x58)) {
            for (i = 0; i < 2; i++) {
                char *prize = moby_find_group_in_state_13(*(int *)(state + 0x58));
                if (prize) {
                    moby_compute_local_point(moby, prize_point, 0.5f, (float)i * 0.9f - 0.45f, 0.0f);
                    moby_teleport_to_new_pose(prize, prize_point, g_zero_l02_vector);
                    *(float *)(prize + 0xF8) = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(float *)(prize + 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - *(float *)(prize + 0x14));
                }
            }
        }
    }
    moby_mark_spawned(moby);
    return;
    case 1:
        break;
    }
    contact = part_find_owned_effect_slot(moby, 0x10000, 0);
    if (!contact) return;
    other = *(char **)(contact + 0x20);
    if (other && *(short *)(other + 0xAA) != 0 && *(short *)(other + 0xAA) != 0x47 && *(float *)(contact + 0x2C) > 2.0f) {
        g_hovering_object_count--;
        moby_set_state(moby, 5, -1);
    } else if (*(unsigned char *)(moby + 0x20) == 1 && other && *(short *)(other + 0xAA) == 0x47 && g_player_bolts > 9) {
        g_player_bolts -= 10;
        slot_machine_roll_result(moby);
        moby_set_state(moby, 2, -1);
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}
