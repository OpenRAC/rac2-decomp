#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x1E0];
    short state;
    char pad2[0x14E];
    int a, b;
} HandlerState;
extern void moby_set_state(void *, int, int);
extern int hero_is_current_selected_id(void *);
extern int TryClaimNotice(int, int, int);
extern int g_pad_held_flags[];
extern int g_warp_state __attribute__((sda));
extern HandlerState g_hero_state;
extern char *g_hero_ptr_table[];
extern float g_warp_pad_glow_amount;
extern char *g_linked_object_table;
extern float ApproachValue(float *, float, float);
extern void load_scene_chunk(int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void snd_stop_voice(int);

/* Per-frame update for a warp pad (class 3804). It shows a prompt near the hero, and when the button is pressed it fades out, moves the hero to the target spot, and fades back in (USA v2.00 copy). */
void warp_pad_update_us2(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *target;
    unsigned timer;
    int waiting;
    if (*(u8 *)(obj + 0x20) == 0) {
        *(u8 *)(obj + 0x30) = 255;
        moby_set_state(obj, 1, -1);
        *(int *)(vars + 0x18) = -1;
    }
    if (*(u8 *)(obj + 0x20) == 1) {
        if (hero_is_current_selected_id(obj)) {
            if (*(int *)(vars + 8) == 0) TryClaimNotice(8, 0x134C, 1);
            else if (*(int *)(vars + 8) == 1) TryClaimNotice(8, 0x134E, 1);
            else TryClaimNotice(8, 0x134B, 1);
            if ((g_pad_held_flags[0] & 0x10) && g_warp_state == 8 && g_hero_state.state == 0 && *(short *)(g_hero_ptr_table[0]+0x86) != 5) {
                *(u16 *)(obj + 0x96) = 0;
                g_hero_state.state = 2;
                moby_set_state(obj, 2, -1);
            }
        }
    }
    if (*(u8 *)(obj + 0x20) == 2) {
        ApproachValue(&g_warp_pad_glow_amount, 1.0f, 0.033333335f);
        timer = *(u16 *)(obj + 0x96);
        waiting = timer++ < 0x20;
        *(u16 *)(obj + 0x96) = timer;
        if (!waiting) {
            target = g_linked_object_table + (*(int *)(vars + 4)<<7);
            g_hero_state.a = 0;
            g_hero_state.b = 0;
            load_scene_chunk(*(int *)vars, *(int *)(vars + 0x10));
            hero_reset_position_and_direction(target + 0x30, target + 0x70, 0, 1);
            g_warp_pad_glow_amount = 1.0f;
            moby_set_state(obj, 3, -1);
        } else g_hero_state.state = 2;
    }
    if (*(u8 *)(obj + 0x20) == 3) {
        ApproachValue(&g_warp_pad_glow_amount, 0.0f, 0.033333335f);
        if (g_warp_pad_glow_amount <= 0.0f) {
            g_warp_pad_glow_amount = 0.0f;
            moby_set_state(obj, 1, -1);
            if (*(int *)(vars + 0x18) != -1) {
                snd_stop_voice(*(int *)(vars + 0x18));
                *(int *)(vars + 0x18) = -1;
            }
        }
    }
}
