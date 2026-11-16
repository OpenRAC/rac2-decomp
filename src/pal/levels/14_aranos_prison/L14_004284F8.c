#include "include_asm.h"
#include "names.h"

extern void func_423000();
extern void func_423240();
extern void func_423358();
extern void func_423B30();
extern void func_423BD8();

/* Updates the tourist actor: sets it up on its first update, then runs its per-frame handlers. (PAL) */
void space_l14_tourist_update_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        func_423000(moby);
    } else {
        func_423240(moby);
        func_423358(moby);
        func_423B30(moby);
        func_423BD8(moby);
    }
}


extern int moby_step_at_own_position_factor(char *object, float factor);
extern int moby_step_at_own_position(char *object);
extern int moby_step_controller(char *object, char *bone, float factor);
extern int moby_turn_toward_target_and_step(char *object, char *bone, float factor);
extern void *jtbl_002AA360[];

/* Dispatches on the owner's animation step and plays the matching bone animation. */
void actor_play_bone_anim_pal(char *moby)
{
    static void * volatile tab[] = { &&cA, &&cC };
    char *vars;
    unsigned int anim_step;

    anim_step = *(unsigned char *)(moby + 0x42) - 1;
    vars = *(char **)(moby + 0x68);
    if (anim_step < 19) {
        goto *jtbl_002AA360[anim_step];
    }
    goto end;
cA:
    if (*(short *)(vars + 0x776) != 0) {
        moby_step_at_own_position_factor(moby, *(float *)(vars + 0x744));
    } else {
        moby_step_at_own_position(moby);
    }
    goto out;
cC:
    if (*(short *)(vars + 0x77A) != 0) {
        moby_step_controller(moby, vars + 0x700, *(float *)(vars + 0x768));
    } else {
        moby_turn_toward_target_and_step(moby, vars + 0x700, *(float *)(vars + 0x740));
    }
out:
end:
    return;
}

#include "common.h"
extern char g_tether_l14_origin_vec[];
extern char g_tether_l14_origin_vec[];
extern void gfx_update_color_fade_pal(char *a0, void *a1);
extern void moby_update_eased_node(char *a0, void *a1, int a2, float a3, float a4);
extern float fast_vec_dist(char *a0, void *a1);
extern void moby_update_ground_check(char *a0);

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
void actor_restart_anim_pal(char *moby)
{
    char *vars;
    float ease_limit;
    float ease_rate;

    vars = *(char **)(moby + 0x68);
    ease_rate = 0.0432f;
    ease_limit = 0.43200004f;
    gfx_update_color_fade_pal(moby, vars + 0x50);
    moby_update_eased_node(moby, vars + 0x680, 1, ease_rate, ease_limit);
    moby_update_eased_node(moby, vars + 0x600, 0, ease_rate, ease_limit);
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = *(unsigned short *)(moby + 0x96) + 1;
    *(unsigned short *)(vars + 0x776) = 0;
    *(unsigned short *)(vars + 0x778) = 0;
    *(unsigned short *)(vars + 0x77A) = 0;
    if (*(unsigned char *)(moby + 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, g_tether_l14_origin_vec) < 24.0f) {
            moby_update_ground_check(moby);
            *(unsigned char *)(moby + 0x6F) = 0x16;
        }
    }
}

