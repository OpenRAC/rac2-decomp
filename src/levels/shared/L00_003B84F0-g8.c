/* Draws a beam from the position in D_L00_001AFD78's state object, four quads per segment, and
 * tracks its length: it grows towards the target moby while the hero holds one of its buttonMask
 * buttons and shrinks otherwise.
 *
 * A unit of its own for its flags: the `a.bits = 0` clear needs -frac2-zero-ti-por, the branch
 * onto a divide needs -frac2-hazard-labels, and the small data needs -G8.
 */
#include "include_asm.h"
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

extern int D_L00_001AFCE0 __attribute__((sda));
extern float D_L00_001AFCF4 __attribute__((sda));
extern float D_L00_001AFCF8 __attribute__((sda));
extern int D_L00_001AFCFC __attribute__((sda));
extern int D_L00_001AFD00 __attribute__((sda));
extern int D_L00_001AFD04 __attribute__((sda));
extern int D_L00_001AFD08 __attribute__((sda));
extern int D_L00_001AFD0C __attribute__((sda));
extern int D_L00_001AFD10 __attribute__((sda));
extern int D_L00_001AFD14 __attribute__((sda));
extern float D_L00_001AFD18 __attribute__((sda));
extern float D_L00_001AFD1C __attribute__((sda));
extern float D_L00_001AFD20 __attribute__((sda));
extern float D_L00_001AFD24 __attribute__((sda));
extern float D_L00_001AFD28 __attribute__((sda));
extern float D_L00_001AFD2C __attribute__((sda));
extern float D_L00_001AFD30 __attribute__((sda));
extern float D_L00_001AFD34 __attribute__((sda));
extern float D_L00_001AFD38 __attribute__((sda));
extern float D_L00_001AFD3C __attribute__((sda));
extern float D_L00_001AFD40 __attribute__((sda));
extern float D_L00_001AFD44 __attribute__((sda));
extern float D_L00_001AFD48 __attribute__((sda));
extern float D_L00_001AFD4C __attribute__((sda));
extern float D_L00_001AFD50 __attribute__((sda));
extern float D_L00_001AFD54 __attribute__((sda));
extern float D_L00_001AFD58 __attribute__((sda));
extern float D_L00_001AFD5C __attribute__((sda));
extern float D_L00_001AFD60 __attribute__((sda));
extern float D_L00_001AFD64 __attribute__((sda));
extern float D_L00_001AFD68 __attribute__((sda));
extern float D_L00_001AFD6C __attribute__((sda));
extern float D_L00_001AFD70 __attribute__((sda));
extern float D_L00_001AFD74 __attribute__((sda));
extern Ctl_L00_003B84F0 *D_L00_001AFD78 __attribute__((sda));
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

void target_tether_draw_beam(Moby_L00_003B84F0 *obj)
{
    Packet_L00_003B84F0 pkt;
    Vec4_L00_003B84F0 b;
    Vec4_L00_003B84F0 a;
    Vec4_L00_003B84F0 c;
    Vec4_L00_003B84F0 vx;
    Vec4_L00_003B84F0 vy;
    Vec4_L00_003B84F0 vz;
    Vec4_L00_003B84F0 p;
    Ctl_L00_003B84F0 *ctl;
    long long alpha0;
    long long alpha1;
    int on;
    int flag;
    int col;
    int alpha;
    int r;
    int g;
    int bl;
    float dist;
    float x;
    float t;
    float w;
    float u;
    float s;
    float phase;
    float range;
    float inv;

    ctl = D_L00_001AFD78;
    if (ctl == 0) {
        return;
    }
    pkt.q78 = GetEffectTextureDescriptor(D_L00_001AFD14);
    {
        /* Two ALPHA register values: alpha1 swaps the A and B fields of alpha0. The order of
           these steps, and building each value in a local of its own, decides sched1's order
           and so local-alloc's priorities for the whole block. */
        long long aShifted = (long long)D_L00_001AFCFC << 2;
        long long bShifted = (long long)D_L00_001AFD00 << 2;
        long long plain, swapped, swappedFull, plainFull;

        inv = 1.0f - D_L00_001AFD34;
        swapped = (long long)D_L00_001AFD00 | aShifted;
        plain = (long long)D_L00_001AFCFC | bShifted;
        plainFull = plain | (long long)D_L00_001AFD04 << 4;
        swappedFull = swapped | (long long)D_L00_001AFD04 << 4;
        plainFull |= (long long)D_L00_001AFD08 << 6;
        swappedFull |= (long long)D_L00_001AFD08 << 6;
        plainFull |= (long long)D_L00_001AFD0C << 32;
        alpha0 = plainFull;
        swappedFull |= (long long)D_L00_001AFD0C << 32;
        alpha1 = swappedFull;
    }
    pkt.col[3] = D_L00_001AFD10;
    pkt.col[2] = D_L00_001AFD10;
    pkt.col[1] = D_L00_001AFD10;
    on = (g_pad_state[0x1A0 / 4] & g_hero_state.f1230) != 0;
    pkt.col[0] = D_L00_001AFD10;
    pkt.q88 = alpha0;
    pkt.uv[0] = D_L00_001AFD34;
    pkt.uv[4] = D_L00_001AFD34;
    pkt.q80 = 0xFF9000000260LL;
    pkt.uv[2] = inv;
    pkt.uv[6] = inv;
    pkt.uv[1] = D_L00_001AFD34;
    pkt.q70 = 4;
    pkt.uv[3] = D_L00_001AFD34;
    pkt.uv[5] = inv;
    pkt.uv[7] = inv;

    dist = D_L00_001AFCF4;
    if (g_hero_state.f340 == 0 || g_hero_state.f34E != 0 || D_L00_001AFCE0 != 0 || g_hero_state.f1E0 != 0) {
        on = 0;
    }
    if (ctl->moby != 0 && ctl->moby->f31 != 0) {
        dist = vec_distance_xy(&obj->pos, &ctl->moby->pos);
    }
    if (ctl->f44 < dist - D_L00_001AFD1C * 0.016666668f && on != 0) {
        ctl->f44 = ctl->f44 + D_L00_001AFD1C * 0.016666668f;
    } else if (ctl->f44 > dist + D_L00_001AFD20 * 0.016666668f || on == 0) {
        ctl->f44 = ctl->f44 - D_L00_001AFD20 * 0.016666668f;
        if (ctl->f44 < 0.0f) {
            ctl->f44 = 0.0f;
        }
    } else {
        ctl->f44 = dist;
    }
    if (on != 0 && D_L00_001AFCE0 == 0 && g_hero_state.f1E0 == 0 && ctl->f44 > dist - 0.5f && ctl->moby != 0) {
        ctl->f44 = 0.0f;
        ctl->f40 = 0.0f;
        g_hero_state.f1E0 = 30;
        moby_set_flag_bit(ctl->moby, 1);
        if (g_hero_state.f22B4 == 0) {
            level_capture_checkpoint_state(&g_hero_state.v80, &g_hero_state.v90);
        }
    }
    if (ctl->f44 > dist) {
        ctl->f44 = dist;
    }
    ctl->f40 = ctl->f40 + D_L00_001AFD18 * 0.016666668f;
    if (ctl->f40 > D_L00_001AFCF8 + D_L00_001AFCF8) {
        ctl->f40 = ctl->f40 - (D_L00_001AFCF8 + D_L00_001AFCF8);
    }
    a.bits = 0;
    a.f[0] = 1.0f;
    vec_scale_to_length(&b, &ctl->dir, -1.0f);
    b.f[2] = -b.f[2];
    flag = 0;
    FastVecCross(&c, &b, &a);
    vec_scale_to_length(&c, &c, 1.0f);
    FastVecCross(&a, &b, &c);
    vec_scale_to_length(&a, &a, 1.0f);
    range = D_L00_001AFD70 - D_L00_001AFD74;
    for (x = ctl->f40; x < ctl->f44; x += D_L00_001AFCF8) {
        if (x <= ctl->f44) {
            t = 0.5f;
            if (D_L00_001AFCF4 < ctl->f44) {
                if (x < D_L00_001AFCF4 * 0.5f) {
                    t = x / D_L00_001AFCF4;
                } else if (ctl->f44 - D_L00_001AFCF4 * 0.5f < x) {
                    t = (x - (ctl->f44 - D_L00_001AFCF4)) / D_L00_001AFCF4;
                }
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                phase = x * D_L00_001AFD68;
                u = (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(phase + IntToFloat(g_frame_l00_counter) * D_L00_001AFD6C)) + 1.0f) * 0.5f;
                if (u > 0.99999f) {
                    u = 0.99999f;
                } else if (u < 0.01f) {
                    u = 0.01f;
                }
                w = D_L00_001AFD74 + range * math_ease_out_quad(u);
            } else {
                t = x / ctl->f44;
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                w = D_L00_001AFD70 * math_fast_sin_or_cos_b(t * 3.1415927f);
                if (t > D_L00_001AFD70) {
                    t = D_L00_001AFD70;
                } else if (t < 0.01f) {
                    t = 0.01f;
                }
            }
            s = math_complement_power(math_fast_sin_or_cos_b(t * 3.1415927f), 2);
            alpha = FloatToInt((flag ? D_L00_001AFD28 : D_L00_001AFD24) * s);
            r = FloatToInt(D_L00_001AFD5C * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(D_L00_001AFD38 * IntToFloat(g_frame_l00_counter) + x * D_L00_001AFD44), D_L00_001AFD50 * 0.017453294f)) + 1.0f));
            g = FloatToInt(D_L00_001AFD60 * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(D_L00_001AFD3C * IntToFloat(g_frame_l00_counter) + x * D_L00_001AFD48), D_L00_001AFD54 * 0.017453294f)) + 1.0f));
            bl = FloatToInt(D_L00_001AFD64 * (math_fast_sin_or_cos_b(FastAddRotations(math_wrap_angle_to_pi(D_L00_001AFD40 * IntToFloat(g_frame_l00_counter) + x * D_L00_001AFD4C), D_L00_001AFD58 * 0.017453294f)) + 1.0f));
            if ((g_pad_state[0x1A0 / 4] & 8) || g_hero_state.f2294 == 0x1D) {
                alpha = FloatToInt((flag ? D_L00_001AFD30 : D_L00_001AFD2C) * math_complement_power(math_fast_sin_or_cos_b(t * 3.1415927f), 2));
                if (x < ctl->f44 * 0.5f) {
                    alpha = FloatToInt(flag ? D_L00_001AFD30 : D_L00_001AFD2C);
                }
                col = r | (g << 8);
                col = col | (bl << 16);
                col = col | (alpha << 24);
                pkt.col[3] = col;
                pkt.col[2] = col;
                pkt.col[1] = col;
                pkt.col[0] = col;
            } else {
                col = r | (g << 8);
                col = col | (bl << 16);
                col = col | (alpha << 24);
                pkt.col[3] = col;
                pkt.col[2] = col;
                pkt.col[1] = col;
                pkt.col[0] = col;
            }
            flag ^= 1;

            vec_scale_to_length(&vx, &b, x);
            vec_scale_to_length(&vy, &a, w);
            vec_scale_to_length(&vz, &c, w);
            FastVecSub(&p, &ctl->pos, &vx);
            pkt.m[3].bits = p.bits;
            FastVecAdd(&p, &pkt.m[3], &vz);
            pkt.m[1].bits = p.bits;
            FastVecSub(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            FastVecSub(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            draw_world_quad(&pkt, 0, 1);
            FastVecAdd(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            FastVecAdd(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            draw_world_quad(&pkt, 0, 1);
            FastVecSub(&p, &pkt.m[3], &vz);
            pkt.m[1].bits = p.bits;
            FastVecSub(&p, &pkt.m[2], &vz);
            pkt.m[0].bits = p.bits;
            draw_world_quad(&pkt, 0, 1);
            FastVecSub(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            FastVecSub(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            draw_world_quad(&pkt, 0, 1);
            if (flag) {
                pkt.q88 = alpha1;
            } else {
                pkt.q88 = alpha0;
            }
        }
    }
}
