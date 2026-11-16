#include "include_asm.h"

#include "common.h"
extern unsigned char g_game_flag_table[0x100];
extern void FastVecSub(void *, void *, void *);
extern char *g_moby_l02_pool __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned char g_moby_group_flags[];
extern unsigned char g_game_flag_table[];
struct PortalPlayer {
    char pad0[0x80];
    float pos[4];
    char pad90[0x182];
    short state;
    char pad214[0x128];
    char *portal;
    int active;
    char pad344[0x21ac];
    unsigned char flag;
};
extern struct PortalPlayer g_hero_state;
extern unsigned char g_hero_position[];
extern unsigned char g_map_visited_flags[] __attribute__((sda));
extern unsigned int g_pad_held_flags __attribute__((nosda));
extern unsigned char g_message_queue[];
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void moby_set_flag_bit(void *, int);
extern void state_set_flag_one(void);
extern void part_start_record_effect_by_index_pal(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void snd_play_indexed_pal(int);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern int TryClaimNotice(int, int, int);
extern void data_set_small_value_and_refresh(int, int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern void moby_call_helper_two_one(void);
extern void game_set_stored_value_pair(void (*)(void), void *);
extern void moby_mark_flag_and_append_to_list(int);

/* Updates a portal: opens it, lets the hero enter it and travel to the next place. */
void portal_update_pal(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    float local_pos[4];
    int dest;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int zone;
        if (*(unsigned char *)(obj + 0x43) != 2) anim_start_blended_pal(obj, 2, 0, 1);
        moby_set_state(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (g_current_map_index[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(vars + 0x20, obj + 0x10);
        qcopy(vars + 0x30, obj + 0xf0);
        zone = g_current_map_index[0] << 4;
        *(short *)(vars + 0x1e) = g_moby_group_flags[*(unsigned char *)(obj + 0xb0) + zone] >> 7;
        if (g_moby_group_flags[*(unsigned char *)(obj + 0xb0) + zone] & 0x80) {
            if (*(int *)(vars + 4)) moby_set_flag_bit(g_moby_l02_pool + (*(int *)(vars + 4) << 8), 1);
        }
        if (g_current_map_index[0] == 2 && g_game_flag_table[0x71] == 26) {
            state_set_flag_one();
            g_game_flag_table[0x71] = 1;
            part_start_record_effect_by_index_pal(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            if (g_map_visited_flags[4] && !g_game_flag_table[0xa5]) {
                g_game_flag_table[0xa5] = 1;
                snd_play_indexed_pal(4);
            }
        }
    }
    case 1:
        if (g_hero_state.portal == obj && g_hero_state.active) {
            FastVecSub(local_pos, g_hero_state.pos, obj + 0x10);
            vec_transform_by_object_or_given(obj, local_pos, local_pos, 0);
            if (local_pos[2] < -0.6f) {
                int map_index;
                map_index = g_current_map_index[0];
                g_hero_state.state = 2;
                dest = 2;
                if (map_index == 26) {
                    TryClaimNotice(8, 0x1303, 1);
                } else {
                    TryClaimNotice(8, g_moby_group_flags[*(unsigned char *)(obj + 0xb0) + (map_index << 4)] & 0x80 ? 0x131F : 0x1302, 1);
                    dest = 26;
                }
                if (g_pad_held_flags & 0x10) {
                    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                    data_set_small_value_and_refresh(dest, 1);
                    if (dest == 26) g_game_flag_table[1] = 1;
                }
            }
        }
        if (g_current_map_index[0] == 26 && (g_moby_group_flags[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (g_map_visited_flags[4]) return;
            if (req_push_queue(g_message_queue, 0xa7)) {
                req_push_queue(g_message_queue, 4);
                req_push_queue(g_message_queue, 0xa8);
                req_launch_queued(g_message_queue);
                game_set_stored_value_pair(moby_call_helper_two_one, obj);
                g_hero_state.flag = 0;
                moby_mark_flag_and_append_to_list(4);
                moby_set_state(obj, 3, -1);
            }
        }
        break;
    }
}
