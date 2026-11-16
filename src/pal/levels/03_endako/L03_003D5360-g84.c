#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x80];
    char position[0x10];
    char pad90[0x33C - 0x90];
    char *object;
    int active;
    char pad344[0x22B4 - 0x344];
    unsigned char mode;
    char pad22B5[0x24FC - 0x22B5];
    unsigned short flag;
} EndakoPlayerState;
typedef struct {
    char pad0[6];
    unsigned char first;
    unsigned char second;
    char pad8[0xA2 - 8];
    unsigned char seen;
} EndakoFlags;
typedef struct {
    char pad0[0x30];
    char position[0x10];
    char pad40[0x30];
    char rotation[0x10];
} EndakoPlacement;
extern EndakoPlayerState g_hero_state;
extern EndakoFlags g_game_flag_table;
extern char g_moby_group_flags[];
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern int g_current_map_index, g_hero_l03_mode;
extern char *g_moby_record_base;
extern EndakoPlacement *g_linked_effect_records;
extern char g_str_clank_scene_key[];
extern char g_clank_scene_spawn_position[] SDATA(D_L03_001B0650);
extern float g_clank_scene_spawn_value_x, g_clank_scene_spawn_value_y;
extern void moby_set_state(), script_queue_keyed_request(), moby_init_child_from_parent(), anim_start_immediate();
extern void func_002A0F48(), state_set_flag_one(), part_start_record_effect_by_index_pal(), moby_set_group_enabled();
extern void hero_reset_position_and_direction_pal(), hero_reset_carried_objects(), moby_mark_spawned(), moby_mark_table_entry_flagged();
extern void game_set_stored_value_pair(), game_set_slowdown_factor_pal();
extern s32 req_launch_queued();
extern void clank_scene_finish_pal(), console_remote_view_cleanup_pal(), object_restore_linked_after_scene_pal();
extern char *CreateMoby();
extern int IsPointInCuboid(), req_push_queue(), flag_is_third_pending_set();
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
#define I(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(unsigned short *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

/* Clank scene switch (PAL): first runs the Clank cutscene when the hero reaches the area, then the
   remote view console; also pulses the console glow colour. */
void clank_scene_switch_update_pal(char *obj)
{
    char *vars = P(obj, 0x68);
    int state = B(obj, 0x20);

    switch (state) {
    case 0: {
        char *clank;

        B(obj, 0x30) = 255;
        if (!(B(g_moby_group_flags, B(obj, 0xB0) + (g_current_map_index << 4)) & 128)) {
            if (g_hero_state.mode == 1) {
                moby_set_state(obj, 2, -1);
                script_queue_keyed_request(I(vars, 0x20), -1);
            } else {
                moby_set_state(obj, 1, -1);
                {
                    char *existing = g_moby_record_base + (I(vars, 0) << 8);
                    I(existing, 0x98) = 0;
                    H(existing, 0x34) = (H(existing, 0x34) | 0x41) & ~0x1000;
                }
                clank = CreateMoby(0x57);
                moby_init_child_from_parent(clank, obj);
                qcopy_nc(clank + 0x10, g_linked_effect_records[I(vars, 4)].position);
                qcopy_nc(clank + 0xF0, g_linked_effect_records[I(vars, 4)].rotation);
                H(clank, 0x32) = 0x30;
                H(clank, 0x34) |= 2;
                anim_start_immediate(clank, 0x13, 0);
                I(clank, 0x98) = 0;
                qcopy_nc(clank + 0x10, g_clank_scene_spawn_position);
                F(clank, 0xF4) = g_clank_scene_spawn_value_x;
                F(clank, 0xF8) = g_clank_scene_spawn_value_y;
                func_002A0F48(clank);
                P(vars, 0x2C) = clank;
                if (g_game_flag_table.first) {
                    state_set_flag_one();
                    part_start_record_effect_by_index_pal(I(vars, 0x18), I(vars, 0x1C));
                }
            }
            moby_set_group_enabled(I(vars, 0xC), 1);
            g_hero_state.flag = 1;
        } else {
            if (!g_game_flag_table.seen) {
                state_set_flag_one();
                hero_reset_position_and_direction_pal(obj + 0x10, obj + 0xF0, 0, 1);
            }
            if (g_hero_state.mode == 1) {
                script_queue_keyed_request(I(vars, 0x24), -1);
                hero_reset_carried_objects(0);
                moby_mark_spawned(g_moby_record_base + (I(vars, 0) << 8));
                moby_mark_table_entry_flagged(B(obj, 0xB0));
                hero_reset_position_and_direction_pal(obj + 0x10, obj + 0xF0, 0, 1);
            }
            /* Resident flag bytes, 8 bytes further on in USA v2.00. A symbol-plus-offset
               .sdata address is neither split nor a one-insn operand, so each store stays
               retail's lui $at/sb macro (see L00_002CAB08.c). */
            g_item_owned_flags[2] = 1;
            g_item_owned_flags[0x3A] = 1;
            g_item_owned_flags[3] = 1;
            g_item_owned_flags[0x3B] = 1;
            g_item_owned_flags[4] = 1;
            g_item_owned_flags[0x3C] = 1;
            g_hero_state.flag = 0;
            moby_set_group_enabled(I(vars, 8), 1);
            moby_set_group_enabled(I(vars, 0xC), 0);
            moby_mark_spawned(obj);
        }
        return;
    }
    case 1:
        if (!g_game_flag_table.first
            && IsPointInCuboid(g_hero_state.position, I(vars, 4))
            && req_push_queue(g_str_clank_scene_key, 0x31)) {
            req_launch_queued(g_str_clank_scene_key);
            game_set_stored_value_pair(object_restore_linked_after_scene_pal, obj);
            g_game_flag_table.first = state;
        }
        if (g_hero_l03_mode != 2) {
            {
                u32 timer = H(P(vars, 0x2C), 0x96);
                u32 old = timer++;
                H(P(vars, 0x2C), 0x96) = timer;
                if (old >= 4) {
                    H(P(vars, 0x2C), 0x34) &= ~0x41;
                    H(P(vars, 0x2C), 0x34) |= 0x1000;
                    I(P(vars, 0x2C), 0x98) = I(P(P(vars, 0x2C), 0x24), 0x10);
                }
            }
        } else {
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
        }
        if (flag_is_third_pending_set(obj)) {
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
            if (g_game_flag_table.second)
                clank_scene_finish_pal(obj);
            else if (req_push_queue(g_str_clank_scene_key, 0x32)) {
                req_launch_queued(g_str_clank_scene_key);
                game_set_stored_value_pair(clank_scene_finish_pal, obj);
            }
            game_set_slowdown_factor_pal();
            moby_set_state(obj, 2, -1);
            return;
        } else if (g_hero_state.mode == 1) {
            char *linked;

            script_queue_keyed_request(I(vars, 0x20), -1);
            linked = g_moby_record_base + (I(vars, 0) << 8);
            H(linked, 0x34) = (H(linked, 0x34) & ~0x41) | 0x1000;
            I(linked, 0x98) = I(P(linked, 0x24), 0x10);
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
            moby_set_state(obj, 2, -1);
            return;
        }
        return;
    case 2:
        if (g_hero_state.object == obj && g_hero_state.active) {
            moby_set_group_enabled(I(vars, 8), 1);
            moby_set_group_enabled(I(vars, 0xC), 0);
            if (req_push_queue(g_str_clank_scene_key, 0x33)) {
                req_launch_queued(g_str_clank_scene_key);
                game_set_stored_value_pair(console_remote_view_cleanup_pal, obj);
                moby_set_state(obj, 3, -1);
            }
            return;
        }
        break;
    default:
        return;
    }
    {
        F(vars, 0x30) = FastAddRotations(F(vars, 0x30), 0.12915438f);
        state = FastTweenColor(0x808C8C8C, 0x80282828,
            math_fast_sin_or_cos_b(F(vars, 0x30)) * 0.5f + 0.5f);
        I(obj, 0x78) = FastTweenColor(I(obj, 0x78), state, 0.18f);
    }
}
