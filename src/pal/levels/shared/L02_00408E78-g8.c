#include "include_asm.h"

#include "common.h"
extern unsigned char D_001395B8[0x100];
extern void FastVecSub(void *, void *, void *);
extern char *g_moby_l02_pool __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_001395B8[];
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
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned int D_00138324 __attribute__((nosda));
extern unsigned char D_L02_001C0700[];
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void moby_set_flag_bit(void *, int);
extern void state_set_flag_one(void);
extern void func_PAL_L02_003294D8(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void func_PAL_002AFC10(int);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern int TryClaimNotice(int, int, int);
extern void data_set_small_value_and_refresh(int, int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern void moby_call_helper_two_one(void);
extern void game_set_stored_value_pair(void (*)(void), void *);
extern void moby_mark_flag_and_append_to_list(int);

void func_PAL_L02_00408E78(char *obj) {
    char *d = *(char **)(obj + 0x68);
    float v[4];
    int dest;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int zone;
        if (*(unsigned char *)(obj + 0x43) != 2) func_PAL_002A7E68(obj, 2, 0, 1);
        moby_set_state(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (g_current_map_index[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(d + 0x20, obj + 0x10);
        qcopy(d + 0x30, obj + 0xf0);
        zone = g_current_map_index[0] << 4;
        *(short *)(d + 0x1e) = D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] >> 7;
        if (D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] & 0x80) {
            if (*(int *)(d + 4)) moby_set_flag_bit(g_moby_l02_pool + (*(int *)(d + 4) << 8), 1);
        }
        if (g_current_map_index[0] == 2 && D_001395B8[0x71] == 26) {
            state_set_flag_one();
            D_001395B8[0x71] = 1;
            func_PAL_L02_003294D8(*(int *)(d + 0x14), *(int *)(d + 0x10));
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            if (D_001A7BC8[4] && !D_001395B8[0xa5]) {
                D_001395B8[0xa5] = 1;
                func_PAL_002AFC10(4);
            }
        }
    }
    case 1:
        if (g_hero_state.portal == obj && g_hero_state.active) {
            FastVecSub(v, g_hero_state.pos, obj + 0x10);
            vec_transform_by_object_or_given(obj, v, v, 0);
            if (v[2] < -0.6f) {
                int currentLevel;
                currentLevel = g_current_map_index[0];
                g_hero_state.state = 2;
                dest = 2;
                if (currentLevel == 26) {
                    TryClaimNotice(8, 0x1303, 1);
                } else {
                    TryClaimNotice(8, D_0019B2E8[*(unsigned char *)(obj + 0xb0) + (currentLevel << 4)] & 0x80 ? 0x131F : 0x1302, 1);
                    dest = 26;
                }
                if (D_00138324 & 0x10) {
                    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                    data_set_small_value_and_refresh(dest, 1);
                    if (dest == 26) D_001395B8[1] = 1;
                }
            }
        }
        if (g_current_map_index[0] == 26 && (D_0019B2E8[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (D_001A7BC8[4]) return;
            if (req_push_queue(D_L02_001C0700, 0xa7)) {
                req_push_queue(D_L02_001C0700, 4);
                req_push_queue(D_L02_001C0700, 0xa8);
                req_launch_queued(D_L02_001C0700);
                game_set_stored_value_pair(moby_call_helper_two_one, obj);
                g_hero_state.flag = 0;
                moby_mark_flag_and_append_to_list(4);
                moby_set_state(obj, 3, -1);
            }
        }
        break;
    }
}
