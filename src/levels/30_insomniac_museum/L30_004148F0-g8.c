#include "include_asm.h"
#include "names.h"
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern long g_pad_pressed_flags __attribute__((nosda));
extern char g_hero_position[];
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, char *, int, int, int);
extern unsigned int g_beam_l30_quad_color;
extern float g_beam_l30_spin_degrees;
extern int math_is_value_within_step(void *, float);
extern void moby_transform_joint_point(void *, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern char *museum_projectile_spawn(void *, void *, void *, int, float);
extern void moby_mark_spawned(void *);
extern char g_str_museum_tweak_label_a[];
extern char g_str_museum_tweak_label_b[];
extern char g_str_museum_tweak_label_c[];
extern char g_str_museum_tweak_label_d[];
extern char g_str_museum_tweak_label_e[];
extern char g_str_museum_tweak_label_f[];
extern char g_str_museum_tweak_label_g[];
extern char g_str_museum_tweak_label_h[];
extern char g_str_museum_tweak_label_i[];
extern char g_str_museum_tweak_label_j[];
extern char g_str_museum_tweak_label_k[];
extern char g_str_museum_tweak_label_l[];
extern char g_str_museum_tweak_label_m[];
extern char g_str_museum_tweak_label_n[];
extern char g_str_museum_tweak_label_o[];
extern char g_str_museum_tweak_label_p[];
extern char g_str_museum_tweak_label_q[];
extern char g_str_museum_tweak_label_r[];
extern char g_str_museum_tweak_label_s[];
extern char g_str_museum_tweak_label_t[];
extern char g_str_museum_tweak_label_u[];
extern char g_str_museum_tweak_label_v[];
extern char g_str_museum_tweak_label_w[];
extern char g_str_museum_tweak_label_x[];
extern char g_str_museum_tweak_label_y[];
extern char g_str_museum_tweak_label_z[];
extern char g_str_museum_tweak_label_aa[];
extern char g_str_museum_tweak_label_ab[];
extern char g_str_museum_tweak_label_ac[];
extern char g_str_museum_tweak_label_ad[];
extern char g_str_beam_color_red[];
extern char g_str_beam_color_green[];
extern char g_str_beam_color_blue[];
extern int g_beam_width_a[] __attribute__((sda));
extern int g_beam_width_b[] __attribute__((sda));
extern int g_beam_width_c[] __attribute__((sda));
extern int g_beam_width_d[] __attribute__((sda));
extern int g_beam_l30_quad_texture[] __attribute__((sda));
extern int g_beam_l30_glow_size[] __attribute__((sda));
extern int g_beam_alpha_a[] __attribute__((sda));
extern int g_beam_alpha_b[] __attribute__((sda));
extern int g_beam_alpha_c[] __attribute__((sda));
extern int g_beam_spin_speed[] __attribute__((sda));
extern int g_beam_back_offset_a[] __attribute__((sda));
extern int g_beam_back_offset_b[] __attribute__((sda));
extern int g_beam_packet_texture_a[] __attribute__((sda));
extern int g_beam_packet_texture_b[] __attribute__((sda));
extern int g_beam_start_color_red[] __attribute__((sda));
extern int g_beam_start_color_green[] __attribute__((sda));
extern int g_beam_start_color_blue[] __attribute__((sda));
extern int g_beam_end_color_red[] __attribute__((sda));
extern int g_beam_end_color_green[] __attribute__((sda));
extern int g_beam_end_color_blue[] __attribute__((sda));
extern int g_beam_alt_start_color_red[] __attribute__((sda));
extern int g_beam_alt_start_color_green[] __attribute__((sda));
extern int g_beam_alt_start_color_blue[] __attribute__((sda));
extern int g_beam_alt_end_color_red[] __attribute__((sda));
extern int g_beam_alt_end_color_green[] __attribute__((sda));
extern int g_beam_alt_end_color_blue[] __attribute__((sda));
extern int g_beam_color_red[] __attribute__((sda));
extern int g_beam_color_green[] __attribute__((sda));
extern int g_beam_color_blue[] __attribute__((sda));

/* Updates the projectile tester: opens one of two tuning menus on a button press, then fires a test projectile when the camera check passes. */
void museum_projectile_tester_update(char *moby) {
    float matrix[16];
    float velocity[4];
    char *vars = *(char **)(moby+0x68);
    unsigned int color;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        color = g_beam_l30_quad_color;
        *(int *)(vars+0x10) = color & 0xff;
        *(int *)(vars+0x14) = (int)(color & 0xff00) >> 8;
        *(int *)(vars+0x18) = (color >> 16) & 0xff;
        *(int *)(vars+0x1c) = (unsigned int)color >> 24;
        g_beam_l30_spin_degrees = 5.0f;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if (*(int *)(vars+4) != -1 && IsPointInCuboid(g_hero_position,*(int *)(vars+4))) {
            ForceClaimNotice(1,0x27e6,1);
            { long buttons = g_pad_pressed_flags;
              if ((buttons & 3) == 3) moby_set_state(moby,2,-1); }
        }
        if (*(int *)(vars+8) != -1 && IsPointInCuboid(g_hero_position,*(int *)(vars+8))) {
            ForceClaimNotice(1,0x27f1,1);
            { long buttons = g_pad_pressed_flags;
              if ((buttons & 3) == 3) moby_set_state(moby,3,-1); }
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars+0xc) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_width_a, g_str_museum_tweak_label_a, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_width_b, g_str_museum_tweak_label_b, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_width_c, g_str_museum_tweak_label_c, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_width_d, g_str_museum_tweak_label_d, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_l30_glow_size, g_str_museum_tweak_label_e, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_spin_speed, g_str_museum_tweak_label_f, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_back_offset_a, g_str_museum_tweak_label_g, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_back_offset_b, g_str_museum_tweak_label_h, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_l30_quad_texture, g_str_museum_tweak_label_i, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_packet_texture_a, g_str_museum_tweak_label_j, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_packet_texture_b, g_str_museum_tweak_label_k, 0, 0, 60);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(vars+0xc) || *(short *)(*(char **)(vars+0xc)+0xaa) != 0x118a /* moby class 4490 */  || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfd)
            moby_set_state(moby,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars+0xc) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x10, g_str_museum_tweak_label_l, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x14, g_str_museum_tweak_label_m, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x18, g_str_museum_tweak_label_n, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x1c, g_str_museum_tweak_label_o, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alpha_b, g_str_museum_tweak_label_p, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alpha_a, g_str_museum_tweak_label_q, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alpha_c, g_str_museum_tweak_label_r, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_start_color_red, g_str_museum_tweak_label_s, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_end_color_red, g_str_museum_tweak_label_t, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_start_color_green, g_str_museum_tweak_label_u, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_end_color_green, g_str_museum_tweak_label_v, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_start_color_blue, g_str_museum_tweak_label_w, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_end_color_blue, g_str_museum_tweak_label_x, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_start_color_red, g_str_museum_tweak_label_y, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_end_color_red, g_str_museum_tweak_label_z, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_start_color_green, g_str_museum_tweak_label_aa, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_end_color_green, g_str_museum_tweak_label_ab, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_start_color_blue, g_str_museum_tweak_label_ac, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_alt_end_color_blue, g_str_museum_tweak_label_ad, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_color_red, g_str_beam_color_red, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_color_green, g_str_beam_color_green, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), g_beam_color_blue, g_str_beam_color_blue, 0, 0, 255);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(vars+0xc) || *(short *)(*(char **)(vars+0xc)+0xaa) != 0x118a /* moby class 4490 */  || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfd)
            moby_set_state(moby,1,-1);
        break;
    }
    {
        unsigned int packed;
        packed = *(int *)(vars+0x1c) << 24;
        packed |= *(int *)(vars+0x18) << 16;
        packed |= *(int *)(vars+0x14) << 8;
        packed |= *(int *)(vars+0x1c);
        g_beam_l30_quad_color = packed;
    }
    if (math_is_value_within_step(moby,1.0f)) {
        moby_transform_joint_point(moby,0,matrix);
        velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby+0xf8));
        velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby+0xf8));
        velocity[2] = 0;
        vec_scale_to_length(velocity,velocity,0.583333373f);
        if (*(int *)vars) {
            museum_projectile_spawn(moby,velocity,matrix+12,1,0.0f);
            moby_mark_spawned(moby);
        } else museum_projectile_spawn(moby,velocity,matrix+12,0,0.0f);
    }
}
