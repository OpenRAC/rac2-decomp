#include "common.h"
#include "include_asm.h"

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
extern int func_PAL_002AF6C0(void *, float);
extern void moby_transform_joint_point(void *, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern char *museum_projectile_spawn_pal(void *, void *, void *, int, float);
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

void func_PAL_L30_00419C60(char *obj) {
    float matrix[16];
    float velocity[4];
    char *st = *(char **)(obj+0x68);
    unsigned int color;
    switch ((unsigned char)obj[0x20]) {
    case 0:
        color = g_beam_l30_quad_color;
        *(int *)(st+0x10) = color & 0xff;
        *(int *)(st+0x14) = (int)(color & 0xff00) >> 8;
        *(int *)(st+0x18) = (color >> 16) & 0xff;
        *(int *)(st+0x1c) = (unsigned int)color >> 24;
        g_beam_l30_spin_degrees = 5.0f;
        moby_set_state(obj,1,-1);
        break;
    case 1:
        if (*(int *)(st+4) != -1 && IsPointInCuboid(g_hero_position,*(int *)(st+4))) {
            ForceClaimNotice(1,0x1338,1);
            { long buttons = g_pad_pressed_flags;
              if ((buttons & 3) == 3) moby_set_state(obj,2,-1); }
        }
        if (*(int *)(st+8) != -1 && IsPointInCuboid(g_hero_position,*(int *)(st+8))) {
            ForceClaimNotice(1,0x1343,1);
            { long buttons = g_pad_pressed_flags;
              if ((buttons & 3) == 3) moby_set_state(obj,3,-1); }
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(st+0xc) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_width_a, g_str_museum_tweak_label_a, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_width_b, g_str_museum_tweak_label_b, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_width_c, g_str_museum_tweak_label_c, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_width_d, g_str_museum_tweak_label_d, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_l30_glow_size, g_str_museum_tweak_label_e, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_spin_speed, g_str_museum_tweak_label_f, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_back_offset_a, g_str_museum_tweak_label_g, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_back_offset_b, g_str_museum_tweak_label_h, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_l30_quad_texture, g_str_museum_tweak_label_i, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_packet_texture_a, g_str_museum_tweak_label_j, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_packet_texture_b, g_str_museum_tweak_label_k, 0, 0, 60);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(st+0xc) || *(short *)(*(char **)(st+0xc)+0xaa) != 0x118a || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfd)
            moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            *(char **)(st+0xc) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), st+0x10, g_str_museum_tweak_label_l, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), st+0x14, g_str_museum_tweak_label_m, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), st+0x18, g_str_museum_tweak_label_n, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), st+0x1c, g_str_museum_tweak_label_o, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alpha_b, g_str_museum_tweak_label_p, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alpha_a, g_str_museum_tweak_label_q, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alpha_c, g_str_museum_tweak_label_r, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_start_color_red, g_str_museum_tweak_label_s, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_end_color_red, g_str_museum_tweak_label_t, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_start_color_green, g_str_museum_tweak_label_u, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_end_color_green, g_str_museum_tweak_label_v, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_start_color_blue, g_str_museum_tweak_label_w, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_end_color_blue, g_str_museum_tweak_label_x, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_start_color_red, g_str_museum_tweak_label_y, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_end_color_red, g_str_museum_tweak_label_z, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_start_color_green, g_str_museum_tweak_label_aa, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_end_color_green, g_str_museum_tweak_label_ab, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_start_color_blue, g_str_museum_tweak_label_ac, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_alt_end_color_blue, g_str_museum_tweak_label_ad, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_color_red, g_str_beam_color_red, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_color_green, g_str_beam_color_green, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st+0xc), g_beam_color_blue, g_str_beam_color_blue, 0, 0, 255);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(st+0xc) || *(short *)(*(char **)(st+0xc)+0xaa) != 0x118a || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfd)
            moby_set_state(obj,1,-1);
        break;
    }
    {
        unsigned int packed;
        packed = *(int *)(st+0x1c) << 24;
        packed |= *(int *)(st+0x18) << 16;
        packed |= *(int *)(st+0x14) << 8;
        packed |= *(int *)(st+0x1c);
        g_beam_l30_quad_color = packed;
    }
    if (func_PAL_002AF6C0(obj,1.0f)) {
        moby_transform_joint_point(obj,0,matrix);
        velocity[0] = math_fast_sin_or_cos_a(*(float *)(obj+0xf8));
        velocity[1] = math_fast_sin_or_cos_b(*(float *)(obj+0xf8));
        velocity[2] = 0;
        vec_scale_to_length(velocity,velocity,0.70000005f);
        if (*(int *)st) {
            museum_projectile_spawn_pal(obj,velocity,matrix+12,1,0.0f);
            moby_mark_spawned(obj);
        } else museum_projectile_spawn_pal(obj,velocity,matrix+12,0,0.0f);
    }
}

/* func_PAL_L30_004188D8, the PAL copy of func_L30_004135A0: the same C, where the title string
   becomes the localized text 0xB60. */
extern void func_37BB30(int, unsigned long long);
extern void func_302298(int, int, int, int, int, int);
extern void func_2F0670(int, int, unsigned long long, char *, int);
extern int sprintf(char *, char *, ...);
extern int g_museum_menu_box_left __attribute__((sda));
extern int g_museum_menu_line_height __attribute__((sda));
extern int g_museum_menu_label_x __attribute__((sda));
extern int g_museum_menu_text_y __attribute__((sda));
extern int g_museum_menu_value_x __attribute__((sda));
extern int g_museum_menu_box_color __attribute__((sda));
extern int g_museum_menu_box_top, g_museum_menu_box_right;
extern int g_museum_menu_title_color;
extern char *GetLocalizedString(int);
extern char g_str_museum_menu_label_format[];
extern char g_str_museum_menu_blank[];
extern char g_str_museum_menu_int_format[];
extern char g_str_museum_menu_float_format[];
extern void *g_tweak_item_ptrs[];
extern char *g_tweak_item_labels[];
extern unsigned char g_tweak_item_types[] __attribute__((sda)) NOT_SDA;
void func_PAL_L30_004188D8(char *obj) {
    char text[256];
    int i = 0, count = 0;
    int *st = *(int **)(obj + 0x68);
    func_37BB30(0x42, 0x8000000044ULL);
    func_302298(g_museum_menu_box_left, g_museum_menu_box_top, g_museum_menu_box_right, g_museum_menu_box_top + g_museum_menu_line_height * (st[1] < 17 ? st[1] : 16), g_museum_menu_box_color, 0);
    func_2F0670(2, 8, g_museum_menu_title_color, GetLocalizedString(0xB60), -1);
    for (; i < 32 - st[2] && count < st[1] && count < 16; i++) {
        if (!g_tweak_item_ptrs[i + st[2]]) continue;
        count++;
        if (g_tweak_item_labels[i]) {
            sprintf(text, g_str_museum_menu_label_format, g_tweak_item_labels[i + st[2]]);
            func_2F0670(g_museum_menu_label_x, g_museum_menu_text_y + i * g_museum_menu_line_height, g_museum_menu_title_color, text, -1);
        }
        if (st[0] == i + st[2]) {
            sprintf(text, g_str_museum_menu_blank);
            func_2F0670(g_museum_menu_label_x - 16, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008000ULL, text, -1);
        }
        switch (g_tweak_item_types[i + st[2]]) {
        case 0:
            sprintf(text, g_str_museum_menu_int_format, *(int *)g_tweak_item_ptrs[i + st[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 1:
            sprintf(text, g_str_museum_menu_float_format, (double)*(float *)g_tweak_item_ptrs[i + st[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 2:
            sprintf(text, g_str_museum_menu_int_format, *(unsigned char *)g_tweak_item_ptrs[i + st[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 3:
            sprintf(text, g_str_museum_menu_int_format, *(short *)g_tweak_item_ptrs[i + st[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        }
    }
}
