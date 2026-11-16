#include "include_asm.h"
#include "names.h"

extern int FastTweenColor(int a, int b, float c);
extern float FastAddRotations(float a, float b);
extern float math_fast_sin_or_cos_b(float a);
extern int FastTweenColor(int a, int b, float c);
extern unsigned short *g_group_entity_lists[];
extern int g_group_link_limit;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L14Cfg;
typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L14Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L14Obj;
typedef struct {
    int a;
    int b;
} L14ColorPair;
extern void group_marker_draw(L14Obj *);
extern L14ColorPair g_group_marker_colors[];
extern int g_frame_tick_counter;
extern void moby_transform_joint_point(void *moby, int joint, void *out);
extern void gfx_add_draw_callback_first(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   first colour pair and, when its stamp is not the current one, refreshes every live class-0x112B
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L14_00428BA0 for the owner. */
void group_marker_update_pulse_pal(L14Obj *self)
{
    L14Cfg *state = self->cfg;
    L14ColorPair colors = g_group_marker_colors[0];
    unsigned short *p;
    L14Obj *e;
    L14Cfg *s0;
    float angle;
    float blend;

    angle = FastAddRotations(state->angle, 0.25132746f);
    state->angle = angle;
    blend = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = FastTweenColor(colors.a, colors.b, blend);
    if (state->stamp != g_frame_tick_counter) {
        for (p = g_group_entity_lists[self->group];
             self->group != 0xFF && self->group <= g_group_link_limit && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[self->group]);
             p++) {
            e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0x112B) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            moby_transform_joint_point(e, 0, &s0->vec);
                            s0->stamp = g_frame_tick_counter;
                        }
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)group_marker_draw, self);
    }
}
