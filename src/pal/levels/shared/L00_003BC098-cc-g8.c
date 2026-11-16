/* func_PAL_L00_003BC098, the PAL copy of func_L00_003B84F0: the same C. */
/* Draws a beam from the position in D_L00_001AFD78's state object, four quads per segment, and
 * tracks its length: it grows towards the target moby while the hero holds one of its buttonMask
 * buttons and shrinks otherwise.
 *
 * A unit of its own for its flags: the `a.bits = 0` clear needs -frac2-zero-ti-por, the branch
 * onto a divide needs -frac2-hazard-labels, and the small data needs -G8.
 */
#include "common.h"

typedef int Quad_L00_003B84F0 __attribute__((mode(TI)));
typedef union {
    Quad_L00_003B84F0 bits;
    float f[4];
} Vec4_L00_003B84F0;

typedef struct {
    unsigned char pad0[0x10];
    Vec4_L00_003B84F0 pos;
    unsigned char pad20[0x11];
    unsigned char f31;
} Moby_L00_003B84F0;

typedef struct {
    Moby_L00_003B84F0 *moby;
    unsigned char pad4[0x1C];
    Vec4_L00_003B84F0 pos;
    Vec4_L00_003B84F0 dir;
    float f40;
    float f44;
} Ctl_L00_003B84F0;

typedef struct {
    Vec4_L00_003B84F0 m[4];
    int col[4];
    float uv[8];
    long long q70;
    long long q78;
    long long q80;
    long long q88;
} Packet_L00_003B84F0;

typedef struct {
    unsigned char pad0[0x80];
    Vec4_L00_003B84F0 v80;
    Vec4_L00_003B84F0 v90;
    unsigned char padA0[0x1E0 - 0xA0];
    short f1E0;
    unsigned char pad1E2[0x340 - 0x1E2];
    int f340;
    unsigned char pad344[0x34E - 0x344];
    short f34E;
    unsigned char pad350[0x1230 - 0x350];
    int f1230;
    unsigned char pad1234[0x2294 - 0x1234];
    int f2294;
    unsigned char pad2298[0x22B4 - 0x2298];
    unsigned char f22B4;
} Hero_L00_003B84F0;

extern Hero_L00_003B84F0 g_hero_state;
extern int g_pad_state[];

extern int g_target_lock_disabled __attribute__((sda));
extern float g_tether_beam_length __attribute__((sda));
extern float g_tether_segment_length __attribute__((sda));
extern int g_tether_prim_field_a __attribute__((sda));
extern int g_tether_prim_field_b __attribute__((sda));
extern int g_tether_prim_field_c __attribute__((sda));
extern int g_tether_prim_field_d __attribute__((sda));
extern int g_tether_prim_field_e __attribute__((sda));
extern int g_tether_vertex_color __attribute__((sda));
extern int g_tether_texture __attribute__((sda));
extern float g_tether_scroll_speed __attribute__((sda));
extern float g_tether_grow_speed __attribute__((sda));
extern float g_tether_shrink_speed __attribute__((sda));
extern float g_tether_alpha_a __attribute__((sda));
extern float g_tether_alpha_b __attribute__((sda));
extern float g_tether_pulse_alpha_a __attribute__((sda));
extern float g_tether_pulse_alpha_b __attribute__((sda));
extern float g_tether_uv_offset __attribute__((sda));
extern float g_tether_color_rate_r __attribute__((sda));
extern float g_tether_color_rate_g __attribute__((sda));
extern float g_tether_color_rate_b __attribute__((sda));
extern float g_tether_color_phase_r __attribute__((sda));
extern float g_tether_beam_green_freq __attribute__((sda));
extern float g_tether_beam_blue_freq_b __attribute__((sda));
extern float g_tether_beam_red_freq_b __attribute__((sda));
extern float g_tether_beam_green_freq_b __attribute__((sda));
extern float g_tether_beam_blue_freq_c __attribute__((sda));
extern float g_tether_beam_red_amp __attribute__((sda));
extern float g_tether_beam_green_amp __attribute__((sda));
extern float g_tether_beam_blue_amp __attribute__((sda));
extern float g_tether_beam_phase_scale __attribute__((sda));
extern float g_tether_beam_pulse_speed __attribute__((sda));
extern float g_tether_beam_max_width __attribute__((sda));
extern float g_tether_beam_min_width __attribute__((sda));
extern Ctl_L00_003B84F0 *g_target_lock_aim_state __attribute__((sda));
extern int g_frame_l00_counter MACRO_ADDR;

extern long long GetEffectTextureDescriptor(int);
extern float vec_distance_xy(void *, void *);
extern void moby_set_flag_bit(void *, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_ease_out_quad(float);
extern float math_complement_power(float, int);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

void target_tether_draw_beam_pal(Moby_L00_003B84F0 *moby)
{
    Packet_L00_003B84F0 packet;
    Vec4_L00_003B84F0 b;
    Vec4_L00_003B84F0 a;
    Vec4_L00_003B84F0 c;
    Vec4_L00_003B84F0 vx;
    Vec4_L00_003B84F0 vy;
    Vec4_L00_003B84F0 vz;
    Vec4_L00_003B84F0 p;
    Ctl_L00_003B84F0 *control;
    long long alpha0;
    long long alpha1;
    int on;
    int flag;
    int col;
    int alpha;
    int red;
    int green;
    int blue;
    float dist;
    float x;
    float t;
    float w;
    float u;
    float s;
    float phase;
    float range;
    float inv;

    control = g_target_lock_aim_state;
    if (control == 0) {
        return;
    }
    packet.q78 = GetEffectTextureDescriptor(g_tether_texture);
    {
        /* Two ALPHA register values: alpha1 swaps the A and B fields of alpha0. The order of
           these steps, and building each value in a local of its own, decides sched1's order
           and so local-alloc's priorities for the whole block. */
        long long aShifted = (long long)g_tether_prim_field_a << 2;
        long long bShifted = (long long)g_tether_prim_field_b << 2;
        long long plain, swapped, swappedFull, plainFull;

        inv = 1.0f - g_tether_uv_offset;
        swapped = (long long)g_tether_prim_field_b | aShifted;
        plain = (long long)g_tether_prim_field_a | bShifted;
        plainFull = plain | (long long)g_tether_prim_field_c << 4;
        swappedFull = swapped | (long long)g_tether_prim_field_c << 4;
        plainFull |= (long long)g_tether_prim_field_d << 6;
        swappedFull |= (long long)g_tether_prim_field_d << 6;
        plainFull |= (long long)g_tether_prim_field_e << 32;
        alpha0 = plainFull;
        swappedFull |= (long long)g_tether_prim_field_e << 32;
        alpha1 = swappedFull;
    }
    packet.col[3] = g_tether_vertex_color;
    packet.col[2] = g_tether_vertex_color;
    packet.col[1] = g_tether_vertex_color;
    on = (g_pad_state[0x1A0 / 4] & g_hero_state.f1230) != 0;
    packet.col[0] = g_tether_vertex_color;
    packet.q88 = alpha0;
    packet.uv[0] = g_tether_uv_offset;
    packet.uv[4] = g_tether_uv_offset;
    packet.q80 = 0xFF9000000260LL;
    packet.uv[2] = inv;
    packet.uv[6] = inv;
    packet.uv[1] = g_tether_uv_offset;
    packet.q70 = 4;
    packet.uv[3] = g_tether_uv_offset;
    packet.uv[5] = inv;
    packet.uv[7] = inv;

    dist = g_tether_beam_length;
    if (g_hero_state.f340 == 0 || g_hero_state.f34E != 0 || g_target_lock_disabled != 0 || g_hero_state.f1E0 != 0) {
        on = 0;
    }
    if (control->moby != 0 && control->moby->f31 != 0) {
        dist = vec_distance_xy(&moby->pos, &control->moby->pos);
    }
    if (control->f44 < dist - g_tether_grow_speed * 0.020000001f && on != 0) {
        control->f44 = control->f44 + g_tether_grow_speed * 0.020000001f;
    } else if (control->f44 > dist + g_tether_shrink_speed * 0.020000001f || on == 0) {
        control->f44 = control->f44 - g_tether_shrink_speed * 0.020000001f;
        if (control->f44 < 0.0f) {
            control->f44 = 0.0f;
        }
    } else {
        control->f44 = dist;
    }
    if (on != 0 && g_target_lock_disabled == 0 && g_hero_state.f1E0 == 0 && control->f44 > dist - 0.5f && control->moby != 0) {
        control->f44 = 0.0f;
        control->f40 = 0.0f;
        g_hero_state.f1E0 = 25;
        moby_set_flag_bit(control->moby, 1);
        if (g_hero_state.f22B4 == 0) {
            level_capture_checkpoint_state(&g_hero_state.v80, &g_hero_state.v90);
        }
    }
    if (control->f44 > dist) {
        control->f44 = dist;
    }
    control->f40 = control->f40 + g_tether_scroll_speed * 0.020000001f;
    if (control->f40 > g_tether_segment_length + g_tether_segment_length) {
        control->f40 = control->f40 - (g_tether_segment_length + g_tether_segment_length);
    }
    a.bits = 0;
    a.f[0] = 1.0f;
    vec_scale_to_length(&b, &control->dir, -1.0f);
    b.f[2] = -b.f[2];
    flag = 0;
    FastVecCross(&c, &b, &a);
    vec_scale_to_length(&c, &c, 1.0f);
    FastVecCross(&a, &b, &c);
    vec_scale_to_length(&a, &a, 1.0f);
    range = g_tether_beam_max_width - g_tether_beam_min_width;
    for (x = control->f40; x < control->f44; x += g_tether_segment_length) {
        if (x <= control->f44) {
            t = 0.5f;
            if (g_tether_beam_length < control->f44) {
                if (x < g_tether_beam_length * 0.5f) {
                    t = x / g_tether_beam_length;
                } else if (control->f44 - g_tether_beam_length * 0.5f < x) {
                    t = (x - (control->f44 - g_tether_beam_length)) / g_tether_beam_length;
                }
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                phase = x * g_tether_beam_phase_scale;
                u = (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(phase + IntToFloat(g_frame_l00_counter) * g_tether_beam_pulse_speed)) + 1.0f) * 0.5f;
                if (u > 0.99999f) {
                    u = 0.99999f;
                } else if (u < 0.01f) {
                    u = 0.01f;
                }
                w = g_tether_beam_min_width + range * math_ease_out_quad(u);
            } else {
                t = x / control->f44;
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                w = g_tether_beam_max_width * math_fast_sin_or_cos_b(t * 3.1415927f);
                if (t > g_tether_beam_max_width) {
                    t = g_tether_beam_max_width;
                } else if (t < 0.01f) {
                    t = 0.01f;
                }
            }
            s = math_complement_power(math_fast_sin_or_cos_b(t * 3.1415927f), 2);
            alpha = FloatToInt((flag ? g_tether_alpha_b : g_tether_alpha_a) * s);
            red = FloatToInt(g_tether_beam_red_amp * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(g_tether_color_rate_r * IntToFloat(g_frame_l00_counter) + x * g_tether_color_phase_r), g_tether_beam_red_freq_b * 0.017453294f)) + 1.0f));
            green = FloatToInt(g_tether_beam_green_amp * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(g_tether_color_rate_g * IntToFloat(g_frame_l00_counter) + x * g_tether_beam_green_freq), g_tether_beam_green_freq_b * 0.017453294f)) + 1.0f));
            blue = FloatToInt(g_tether_beam_blue_amp * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(g_tether_color_rate_b * IntToFloat(g_frame_l00_counter) + x * g_tether_beam_blue_freq_b), g_tether_beam_blue_freq_c * 0.017453294f)) + 1.0f));
            if ((g_pad_state[0x1A0 / 4] & 8) || g_hero_state.f2294 == 0x1D) {
                alpha = FloatToInt((flag ? g_tether_pulse_alpha_b : g_tether_pulse_alpha_a) * math_complement_power(math_fast_sin_or_cos_b(t * 3.1415927f), 2));
                if (x < control->f44 * 0.5f) {
                    alpha = FloatToInt(flag ? g_tether_pulse_alpha_b : g_tether_pulse_alpha_a);
                }
                col = red | (green << 8);
                col = col | (blue << 16);
                col = col | (alpha << 24);
                packet.col[3] = col;
                packet.col[2] = col;
                packet.col[1] = col;
                packet.col[0] = col;
            } else {
                col = red | (green << 8);
                col = col | (blue << 16);
                col = col | (alpha << 24);
                packet.col[3] = col;
                packet.col[2] = col;
                packet.col[1] = col;
                packet.col[0] = col;
            }
            flag ^= 1;

            vec_scale_to_length(&vx, &b, x);
            vec_scale_to_length(&vy, &a, w);
            vec_scale_to_length(&vz, &c, w);
            FastVecSub(&p, &control->pos, &vx);
            packet.m[3].bits = p.bits;
            FastVecAdd(&p, &packet.m[3], &vz);
            packet.m[1].bits = p.bits;
            FastVecSub(&p, &packet.m[1], &vy);
            packet.m[0].bits = p.bits;
            FastVecSub(&p, &packet.m[3], &vy);
            packet.m[2].bits = p.bits;
            draw_world_quad(&packet, 0, 1);
            FastVecAdd(&p, &packet.m[1], &vy);
            packet.m[0].bits = p.bits;
            FastVecAdd(&p, &packet.m[3], &vy);
            packet.m[2].bits = p.bits;
            draw_world_quad(&packet, 0, 1);
            FastVecSub(&p, &packet.m[3], &vz);
            packet.m[1].bits = p.bits;
            FastVecSub(&p, &packet.m[2], &vz);
            packet.m[0].bits = p.bits;
            draw_world_quad(&packet, 0, 1);
            FastVecSub(&p, &packet.m[1], &vy);
            packet.m[0].bits = p.bits;
            FastVecSub(&p, &packet.m[3], &vy);
            packet.m[2].bits = p.bits;
            draw_world_quad(&packet, 0, 1);
            if (flag) {
                packet.q88 = alpha1;
            } else {
                packet.q88 = alpha0;
            }
        }
    }
}
