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
extern void func_PAL_002CB5D0(void);
extern void menu_end(void);
extern void mpeg_resume_after_movie(void);
extern void cutscene_end_pal(void);
extern void cam_set_value_target(int, int, float, float, float, float);
extern void UpdateViewContext(void);
extern void scene_end_playback_pal(void);
extern void func_PAL_002F96D8(void);
extern void moby_show_all(void);
extern void func_PAL_00300300(void);
extern void func_PAL_00291A40(void);
extern void math_trap_always(void);
extern void func_PAL_002B5540(int);
extern int menu_get_mode(void);
extern void func_PAL_002CAAF0(int);
extern void menu_set_mode(int, int);
extern void mpeg_start_movie_from_toc(int);
extern float ApproachValue(float *, float, float);
extern void cutscene_start_pal(int);
extern void data_set_small_value_and_refresh(int, int);
extern void scene_init_playback_state(void);
extern void scene_init_list(int);
extern void scene_reset_state_on_start_pal(void);
extern void OpenVendorMenu_pal(int);
extern void moby_hide_all(int, int);
extern void func_PAL_00300130(void);
extern void func_PAL_00291A20(void);

/* Applies a requested change of mode: D_001A8BB8 holds the requested mode (-2 when none) and
   D_001A8BB0 the current one. The first dispatch runs the handler of the mode being left and the
   second the handler of the mode being entered; unless that one holds the change (hold), the
   request becomes the current mode and is cleared. Both dispatches read the tables retail has in
   its data (ten code addresses each, one per mode, D_0026CBB0 and D_0026CBE0); `leaving` and
   `entering` only keep the labels alive. A handler reached through a table starts with no known
   values, so D_001A8BB8 is read again where retail reads it (the compare in the first handler of
   mode 3) without any qualifier on the global. */
void func_PAL_002B57D0(void)
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
        func_PAL_002CB5D0();
    goto E1;
L1_4:
    menu_end();
    goto E1;
L1_1:
    mpeg_resume_after_movie();
    goto shared;
L1_2:
    cutscene_end_pal();
shared:
    g_fov_tangent = 0.62f;
    cam_set_value_target(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    UpdateViewContext();
    goto E1;
L1_6:
    if (g_pending_mode_arg_a != 4)
        scene_end_playback_pal();
    goto E1;
L1_5:
    func_PAL_002F96D8();
    goto E1;
L1_7:
    moby_show_all();
    goto E1;
L1_8:
    func_PAL_00300300();
    goto E1;
L1_9:
    func_PAL_00291A40();
    goto E1;
L1_def:
    math_trap_always();
L1_0:
E1:
    func_PAL_002B5540(10);
    hold = 0;
    sel = g_requested_game_mode;
    if ((unsigned)sel >= 10)
        goto L2_def;
    goto *D_0026CBE0[sel];
L2_3:
    if (g_previous_game_mode != 4 || menu_get_mode() == 8)
        func_PAL_002CAAF0(g_pending_mode_arg_a);
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
        ApproachValue(&g_mode_fade_scale, 1.4f, 0.120000005f);
        f = g_mode_fade_scale;
        g_screen_fade = f;
        if (1.0f < f)
            g_screen_fade = 1.0f;
        if (1.4f <= f) {
            hold = 0;
            g_mode_fade_scale = 1.0f;
            cutscene_start_pal(g_pending_mode_arg_a);
        } else {
            hold = 1;
        }
    } else {
        cutscene_start_pal(g_pending_mode_arg_a);
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
            scene_reset_state_on_start_pal();
        g_mode_change_flag = 1;
    }
    goto E2;
L2_5:
    OpenVendorMenu_pal(g_pending_mode_arg_a);
    goto E2;
L2_7:
    {
        int fallback = g_moby_hide_mode_a;
        moby_hide_all(g_pending_mode_arg_a ? g_pending_mode_arg_a : fallback, g_pending_mode_arg_b);
    }
    goto E2;
L2_8:
    func_PAL_00300130();
    goto E2;
L2_9:
    func_PAL_00291A20();
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

typedef struct {
    char pad0[0x10];
    float pos[4];                        
    char pad1[0xF8 - 0x20];
    float heading;                       
} Self_002B52A0;
typedef struct {
    char pad0[0x14];
    float f14, f18, f1C, f20, f24, f28, f2C, f30, f34;       
    unsigned flags38;                    
    char pad1[0x50 - 0x3C];
    float v50[4];                        
    float f60, f64;                      
    char pad3[0x80 - 0x68];
    int w80;                             
    char pad4[0x90 - 0x84];
    volatile float f90;  
    unsigned flags94;                    
    char pad5[0x9C - 0x98];
    int flags9C;                         
    float vel[4];                        
    float speed;                         
    float fB4;                           
    char pad7[0xC0 - 0xB8];
    short hC0, hC2;                      
    char pad8[0xCC - 0xC4];
    float fCC;                           
} Ctl_002B52A0;
extern float g_controller_velocity_limit __attribute__((sda));
extern float math_approach_target_with_direction_mode(void *, float, void *, int, float, float, float);
extern float FastDiffRots(float, float);
extern void vec_clear_128(void *);
extern float vec_distance_xy(void *, void *);
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float vec_length_xy(void *);
extern void math_approach_target_with_braking(void *, float, float, float, float);

void moby_update_controller_velocity_pal(Self_002B52A0 *self, Ctl_002B52A0 *ctl, void *target, float x)
{
    float local[4] __attribute__((aligned(16)));
    float local2[4] __attribute__((aligned(16)));
    float h, scale, dist, dot, len, len2, diff, g90;

    if (!(ctl->flags38 & 0x10))
        math_approach_target_with_direction_mode(&self->heading, x, &ctl->fB4, 0, ctl->f14, ctl->f18, ctl->f1C);
    h = FastDiffRots(self->heading, x);
    if (!(ctl->flags38 & 0x10) && ctl->f30 < h) {
        vec_clear_128(local);
        if (h - ctl->f30 > ctl->fB4 * 25.0f)
            ctl->flags9C |= 2;
    } else {
        ctl->flags9C &= ~2;
        dist = vec_distance_xy(self->pos, target);
        ctl->fCC = dist;
        if (dist <= ctl->f34) {
            vec_clear_128(local);
        } else {
            scale = square_root(2.0f * (dist - ctl->f34) * ctl->f24);
            if (ctl->f28 < scale)
                scale = ctl->f28;
            h = x;
            if (ctl->w80 != 0) {
                x = FastAddRotations(mat_fast_helper_a(ctl->f60 - self->pos[0], ctl->f64 - self->pos[1]), 3.14159f);
                h = fast_subtract_rotations(h, x);
                if (g_controller_velocity_limit < h)
                    h = g_controller_velocity_limit;
                else if (h < -g_controller_velocity_limit)
                    h = -g_controller_velocity_limit;
                h = FastAddRotations(h, x);
            }
            local[0] = math_fast_sin_or_cos_a(h) * scale;
            local[1] = math_fast_sin_or_cos_b(h) * scale;
            local[2] = 0;
        }
    }
    FastVecSub(local2, local, ctl->vel);
    local2[2] = 0;
    dot = FastVecDot(local, ctl->vel);
    if (0.0f < dot)
        vec_clamp_length(local2, ctl->f20);
    else
        vec_clamp_length(local2, ctl->f24);
    FastVecAdd(ctl->vel, ctl->vel, local2);
    len = vec_length_xy(ctl->vel);
    ctl->speed = len;
    if (ctl->flags38 & 4)
        return;
    g90 = ctl->f90;
    if (g90 < self->pos[2]) {
        if (ctl->hC2 < 2) {
            if (self->pos[2] - g90 < 0.15f) {
                len2 = vec_length_xy(ctl->v50);
                if (0.087266475f < mat_fast_helper_a(ctl->v50[2], len2)) {
                    if (-FastVecDot(ctl->vel, ctl->v50) < ctl->vel[2])
                        ctl->vel[2] = -FastVecDot(ctl->vel, ctl->v50);
                }
            }
        }
        ctl->vel[2] = ctl->vel[2] - ctl->f2C;
        if (ctl->hC0 == 0)
            ctl->flags94 |= 0x20;
    } else {
        diff = g90 - self->pos[2];
        if (diff < ctl->vel[2])
            ctl->vel[2] = diff;
        else if (ctl->vel[2] < 0.0f)
            ctl->vel[2] = 0.0f;
        math_approach_target_with_braking(&ctl->vel[2], ctl->f90 - self->pos[2], 0.016f, 0.016f, 1.0f);
    }
}
