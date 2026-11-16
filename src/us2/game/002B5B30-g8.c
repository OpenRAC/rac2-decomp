#include "include_asm.h"
#include "names.h"
extern void *D_0026CBB0[];
extern void *D_0026CBE0[];
extern int g_current_game_mode;
extern int g_previous_game_mode;
extern int g_requested_game_mode;
extern int g_request_enabled_flag __attribute__((nosda));
extern int g_requested_setting_b __attribute__((sda));
extern int g_pending_mode_arg_a __attribute__((sda));
extern int g_pending_mode_arg_b __attribute__((sda));
extern char *g_pending_mode_done_flag __attribute__((sda));
extern float g_mode_fade_scale;
extern float g_screen_fade;
extern int g_mode_change_flag;
extern float g_fov_tangent __attribute__((nosda));
extern int g_moby_hide_mode_a;
extern void RestoreMenuDisplayState(void);
extern void menu_end(void);
extern void mpeg_resume_after_movie(void);
extern void cutscene_end(void);
extern void cam_set_value_target(int, int, float, float, float, float);
extern void UpdateViewContext(void);
extern void scene_end_playback(void);
extern void shop_reset_menu_camera(void);
extern void moby_show_all(void);
extern void game_noop(void);
extern void gfx_lighting_wrapper(void);
extern void math_trap_always(void);
extern void request_set_setting_a(int);
extern int menu_get_mode(void);
extern void menu_init_pause_state(int);
extern void menu_set_mode(int, int);
extern void mpeg_start_movie_from_toc(int);
extern float ApproachValue(float *, float, float);
extern void cutscene_start(int);
extern void data_set_small_value_and_refresh(int, int);
extern void scene_init_playback_state(void);
extern void scene_init_list(int);
extern void scene_reset_state_on_start(void);
extern void OpenVendorMenu(int);
extern void moby_hide_all(int, int);
extern void BeginPreviewTransition(void);
extern void gfx_lighting_init_wrapper(void);

/* Applies a requested change of mode: D_001A8BB8 holds the requested mode (-2 when none) and
   D_001A8BB0 the current one. The first dispatch runs the handler of the mode being left and the
   second the handler of the mode being entered; unless that one holds the change (hold), the
   request becomes the current mode and is cleared. Both dispatches read the tables retail has in
   its data (ten code addresses each, one per mode, D_0026CBB0 and D_0026CBE0); `leaving` and
   `entering` only keep the labels alive. A handler reached through a table starts with no known
   values, so D_001A8BB8 is read again where retail reads it (the compare in the first handler of
   mode 3) without any qualifier on the global. */
void mode_apply_pending_change_us2(void)
{
    static void *leaving[12] = {&&L1_3, &&L1_4, &&L1_1, &&L1_2, &&L1_6, &&L1_5, &&L1_7, &&L1_8, &&L1_9, &&L1_0, &&L1_def, &&shared};
    static void *entering[11] = {&&L2_3, &&L2_0, &&L2_4, &&L2_1, &&L2_2, &&L2_6, &&L2_5, &&L2_7, &&L2_8, &&L2_9, &&L2_def};
    int mode = g_current_game_mode;
    int sel;
    int hold;
    g_previous_game_mode = mode;
    if (g_requested_game_mode == -2)
        return;
    if (g_requested_setting_b > 0) {
        g_requested_setting_b--;
        return;
    }
    if (g_request_enabled_flag == 0)
        return;
    if ((unsigned)mode >= 10)
        goto L1_def;
    goto *D_0026CBB0[mode];
L1_3:
    if (g_requested_game_mode != 4 || g_pending_mode_arg_a == 8)
        RestoreMenuDisplayState();
    goto E1;
L1_4:
    menu_end();
    goto E1;
L1_1:
    mpeg_resume_after_movie();
    goto shared;
L1_2:
    cutscene_end();
shared:
    g_fov_tangent = 0.62f;
    cam_set_value_target(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    UpdateViewContext();
    goto E1;
L1_6:
    if (g_pending_mode_arg_a != 4)
        scene_end_playback();
    goto E1;
L1_5:
    shop_reset_menu_camera();
    goto E1;
L1_7:
    moby_show_all();
    goto E1;
L1_8:
    game_noop();
    goto E1;
L1_9:
    gfx_lighting_wrapper();
    goto E1;
L1_def:
    math_trap_always();
L1_0:
E1:
    request_set_setting_a(10);
    hold = 0;
    sel = g_requested_game_mode;
    if ((unsigned)sel >= 10)
        goto L2_def;
    goto *D_0026CBE0[sel];
L2_3:
    if (g_previous_game_mode != 4 || menu_get_mode() == 8)
        menu_init_pause_state(g_pending_mode_arg_a);
L2_0:
    hold = 0;
    goto E2;
L2_4:
    menu_set_mode(g_pending_mode_arg_a, g_pending_mode_arg_b);
    goto E2;
L2_1:
    mpeg_start_movie_from_toc(g_pending_mode_arg_b);
    hold = 0;
    goto E2;
L2_2:
    if ((unsigned)(g_current_game_mode - 1) >= 2) {
        float f;
        ApproachValue(&g_mode_fade_scale, 1.2f, 0.10000001f);
        f = g_mode_fade_scale;
        g_screen_fade = f;
        if (1.0f < f)
            g_screen_fade = 1.0f;
        if (1.2f <= f) {
            hold = 0;
            g_mode_fade_scale = 1.0f;
            cutscene_start(g_pending_mode_arg_a);
        } else {
            hold = 1;
        }
    } else {
        cutscene_start(g_pending_mode_arg_a);
    }
    goto E2;
L2_6:
    if (g_pending_mode_arg_a == 5) {
        data_set_small_value_and_refresh(g_pending_mode_arg_b, 1);
    } else if (g_pending_mode_arg_a == 6) {
        scene_init_playback_state();
    } else {
        if (g_previous_game_mode == 3)
            scene_init_list(g_pending_mode_arg_b);
        else
            scene_reset_state_on_start();
        g_mode_change_flag = 1;
    }
    goto E2;
L2_5:
    OpenVendorMenu(g_pending_mode_arg_a);
    goto E2;
L2_7:
    {
        int fallback = g_moby_hide_mode_a;
        moby_hide_all(g_pending_mode_arg_a ? g_pending_mode_arg_a : fallback, g_pending_mode_arg_b);
    }
    goto E2;
L2_8:
    BeginPreviewTransition();
    goto E2;
L2_9:
    gfx_lighting_init_wrapper();
    goto E2;
L2_def:
    math_trap_always();
E2:
    if (hold == 0) {
        int state;
        if (g_pending_mode_done_flag != 0)
            *g_pending_mode_done_flag = 1;
        state = g_requested_game_mode;
        g_requested_game_mode = -2;
        g_current_game_mode = state;
        g_pending_mode_done_flag = 0;
    }
}
