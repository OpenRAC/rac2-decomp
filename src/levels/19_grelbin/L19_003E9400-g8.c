#include "include_asm.h"
#include "common.h"

extern float g_attachment_timer_param __attribute__((sda));

extern void func_2EB590();

extern void func_3238E0(void *, void *, int, int, float);

/* Ticks two timers in the object's data, counts up its age, and refreshes its attached effect. */
void moby_update_timers_attachment(char *moby)
{
    char *moby_ptr = moby;
    int vars_addr = *(int *)(moby_ptr + 0x68);

    func_2EB590(vars_addr + 0x230);
    func_2EB590(vars_addr + 0x234);
    if (*(unsigned short *)(moby_ptr + 0x96) < 0xFFFF) {
        *(unsigned short *)(moby_ptr + 0x96) += 1;
    }
    func_3238E0(moby_ptr, vars_addr + 0x2A0, 1, 1, g_attachment_timer_param);
}

extern int g_hero_l19_mode __attribute__((sda));
extern u8 g_warp_trigger_flags[] __attribute__((sda));
extern int g_glow_state_flags[4] __attribute__((sda));
extern char *g_linked_object_table[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern char g_hero_position[];
extern char g_request_l19_queue[];

extern void func_4239B8(char *a0);
extern void func_30DFE8(char *a0);
extern void func_318240(char *a0, s32 a1, s32 a2);
extern void func_31A620(char *a0);
extern s32 func_31E128(char *a0, s32 a1);
extern s32 func_2F1940(char *a0, s32 a1);
extern void func_32C2E8(char *a0);
extern void func_2F1A88(char *a0);
extern s32 func_36E868(void);
extern void func_31F110(s32 a0);
extern void func_321BB0(s32 a0);
extern void func_2BBFD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_30FC48(s32 a0);
extern void func_356928(char *a0, char *a1);
extern void func_309FB8(s32 a0, s32 a1);

/* Per-frame update for a warp trigger (class 4711). When triggered it fades the screen and moves the hero to a linked spot. */
void warp_trigger_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    u8 id;

    func_4239B8(moby);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        if (g_warp_trigger_flags[0] != 0) {
            func_30DFE8(moby);
        } else {
            func_318240(moby, 1, -1);
            func_31A620(moby);
        }
        break;
    case 1:
        if (func_31E128(g_hero_position, *(s32 *)(vars + 0x120)) != 0) {
            if (func_2F1940(g_request_l19_queue, 0x96) != 0) {
                func_2F1940(g_request_l19_queue, 0x14);
                func_2F1940(g_request_l19_queue, 0x97);
                func_32C2E8(moby);
                func_2F1A88(g_request_l19_queue);
                func_318240(moby, 2, -1);
            }
        }
        break;
    case 2:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode == 2) {
            *(u8 *)(moby + 0x31) = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (func_36E868() == 0) {
            g_glow_state_flags[1] = 0;
            func_31F110(0x14);
            func_321BB0(0x14);
            func_2BBFD8(g_linked_object_table[0] + (*(s32 *)(vars + 0x120) << 7) + 0x30,
                        g_linked_object_table[0] + (*(s32 *)(vars + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            *(u8 *)(moby + 0x31) = 1;
            if (*(u8 *)(moby + 0xB0) != 0xFF) {
                id = *(u8 *)(moby + 0xB0);
                if ((g_moby_group_flags[id + (g_current_map_index[0] << 4)] & 0x80) == 0)
                    func_30FC48(id);
                func_356928(g_hero_position, g_hero_position + 0x10);
                func_309FB8(0, -1);
            } else {
                func_309FB8(0, -1);
            }
            func_30DFE8(moby);
        }
        break;
    }
}

extern float g_warp_trigger_radius __attribute__((sda)), g_warp_trigger_speed_in __attribute__((sda));
extern float g_warp_trigger_speed_out __attribute__((sda)), g_warp_trigger_blend_rate __attribute__((sda));
extern float g_warp_trigger_height_range __attribute__((sda)), g_warp_trigger_reset_value __attribute__((sda));
extern float g_warp_trigger_lift_rate __attribute__((sda));
/* The hero: its state word and another mode word. */
typedef struct {
    char pad0[0x2294];
    int state;
    int pad2298;
    int mode;
} HeroModes;
extern HeroModes g_hero_state;
extern u8 g_moby_nibble_table[];
/* Player stats: the pending bolt credit at +0x1C. */
typedef struct { u8 pad0[0x1C]; int pendingBolts; } PlayerStats;
extern PlayerStats g_player_stats MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_warp_triggered_flags[] MACRO_ADDR;
extern void anim_start_blended(void *, int, int, int);
extern void EmitGrelbinGlowSprites(void *);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern float vec_length_xy(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int text_sum_subtitle_lengths(void);
extern void value_set_entry_by_index(int, int);

/* A pickup that floats until the hero is close, then flies to the hero, shrinks, and adds a bolt when it arrives. */
void UpdateHomingCollectible(u8 *object)
{
    float direction[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    float distance, movement, threshold;
    switch (object[0x20]) {
    case 0:
        object[0x23] = 0x80;
        *(u32 *)(object + 0x78) = 0xFFAAAAAA;
        *(u16 *)(object + 0x34) |= 0x800;
        object[0x20] = 1;
        if (object[0x43]) anim_start_blended(object, 0, 0, 0);
        break;
    case 1:
        if (vec_distance_xy(object + 0x10, g_hero_position) < g_warp_trigger_radius &&
            math_fabs(*(float *)(object + 0x18) - *(float *)(g_hero_position + 8)) < g_warp_trigger_height_range) {
            *(float *)vars = g_warp_trigger_reset_value;
            if (object[0x43] != 1) anim_start_blended(object, 1, 0, 20);
            *(float *)(object + 0x48) = *(float *)vars + *(float *)vars;
            object[0x20] = 2;
        }
        if (object[0x31]) EmitGrelbinGlowSprites(object);
        break;
    case 2:
        if (object[0x43] != 1) anim_start_blended(object, 1, 0, 20);
        *(float *)vars += (1.0f - *(float *)vars) * g_warp_trigger_blend_rate;
        *(float *)(object + 0x48) = *(float *)vars + *(float *)vars;
        FastVecSub(direction, g_hero_position, object + 0x10);
        direction[2] += 0.6f;
        distance = vec_length_xy(direction);
        threshold = 0.12f;
        if (*(int *)(g_hero_position + 0x2214) != 0x31)
            movement = g_warp_trigger_speed_in * (*(float *)vars * 0.016666668f);
        else {
            movement = g_warp_trigger_speed_out * (*(float *)vars * 0.016666668f);
            threshold = 0.8f;
        }
        vec_fast_divide_helper(direction, direction, movement);
        FastVecAdd(object + 0x10, object + 0x10, direction);
        if (*(float *)(object + 0x2C) > 0.1f || distance < threshold || distance < movement)
            *(float *)(object + 0x2C) -= g_warp_trigger_lift_rate * *(float *)(*(u8 **)(object + 0x24) + 0x24);
        if ((distance < movement &&
             *(float *)(object + 0x2C) < *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.01f) ||
            g_hero_state.mode == 0x14 || g_hero_state.mode == 0x19 ||
            g_hero_state.state == 0x39 || g_hero_state.state == 0x6F) {
            if (*(u8 **)(vars + 4)) {
                u8 *linked = *(u8 **)(vars + 4);
                int flag_index = *(unsigned short *)(linked + 0xB2);
                if (flag_index & 1) {
                    unsigned char *flag_byte = &g_moby_nibble_table[((short)flag_index >> 1) + (g_current_map_index[0] << 10)];
                    if (((*flag_byte >> 4) & 7) != 7) {
                        *flag_byte += 0x10;
                    }
                } else {
                    unsigned char *flag_byte = &g_moby_nibble_table[((short)flag_index >> 1) + (g_current_map_index[0] << 10)];
                    if ((*flag_byte & 7) != 7) {
                        *flag_byte += 1;
                    }
                }
                moby_mark_spawned(*(u8 **)(vars + 4));
            }
            g_player_stats.pendingBolts++;
            snd_play_from_class_bank(3, 0, object, 0x11C7);
            moby_mark_spawned(object);
            if (!text_sum_subtitle_lengths() && !g_item_enabled_flags[6]) {
                g_item_enabled_flags[6] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index(0x1233, -1);
                g_warp_triggered_flags[0] = 1;
            }
            moby_mark_spawned(object);
        } else EmitGrelbinGlowSprites(object);
        break;
    }
}
