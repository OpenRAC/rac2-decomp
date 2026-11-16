#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void moby_transform_joint_point(char *, int, void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void group_draw_entity_glows(u8 *);
extern unsigned short *g_moby_l12_group_lists[];
extern int g_moby_l12_group_count __attribute__((sda));
extern u8 *g_moby_list_start[3] __attribute__((sda));
extern int g_frame_l12_counter[3] __attribute__((sda));
extern int D_L12_001B29C8_s __asm__("D_L12_001B29C8") __attribute__((sda));
struct L12PairWord {
    int a;
    int b;
};
extern struct L12PairWord g_pulsing_group_color_pair __attribute__((nosda));
struct L12Kind348 {
    char pad[0x348];
    float f348;
    float f34C;
    int f350;
};
struct L12Kind348Entity {
    char pad0[0x20];
    u8 state;
    char pad1[0x10];
    u8 f31;
    char pad2[0x36];
    struct L12Kind348 *obj;
    char pad3[0x3E];
    short type;
};
struct L12Kind348Object {
    char pad0[0x21];
    u8 group;
    char pad1[0x46];
    struct L12Kind348 *obj;
    char pad2[0x0C];
    int f78;
};
extern struct L12PairWord g_pulsing_group_tween_colors;

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L12_001B29C8 differs from the object's word at +0x350, walks the object's group
   and refreshes every live entity of kind 0x11EB, then registers func_L12_004281D8. */
void pulsing_group_update_pal(struct L12Kind348Object *a0) {
    struct L12Kind348 *o = a0->obj;
    struct L12PairWord v = g_pulsing_group_color_pair;
    float f;
    unsigned short *q;
    struct L12Kind348Entity *e;
    struct L12Kind348 *s0;

    f = FastAddRotations(o->f348, 0.25132746f);
    o->f348 = f;
    f = math_fast_sin_or_cos_b(f);
    o->f34C = f * 0.5f + 0.5f;
    a0->f78 = FastTweenColor(v.a, v.b, o->f34C);
    if (o->f350 != D_L12_001B29C8_s) {
        for (q = g_moby_l12_group_lists[a0->group];
             a0->group != 0xFF && a0->group <= g_moby_l12_group_count && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == g_moby_l12_group_lists[a0->group]);
             q++) {
            e = (struct L12Kind348Entity *)(g_moby_list_start[0] + ((*q & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->f31 != 0 && e->type == 0x11EB && e->state != 0xFE && e->state != 0xFD) {
                s0 = e->obj;
                moby_transform_joint_point((char *)e, 0, (char *)s0 + 0x240);
                s0->f350 = g_frame_l12_counter[0];
            }
        }
        gfx_add_draw_callback_first((void *)group_draw_entity_glows, a0);
    }
}
