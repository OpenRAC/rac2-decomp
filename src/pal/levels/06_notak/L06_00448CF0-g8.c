#include "include_asm.h"

#include "common.h"
extern u8 *g_group_l06_id_lists[];
extern unsigned char *D_L06_001B281C_base[3] __asm__("D_L06_001B281C") __attribute__((sda));
extern int g_moby_l06_group_count;
extern int g_game_l06_frame_counter;
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;
typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;
typedef struct {
    int a;
    int b;
} L06ColorPair;
extern void marker_draw_group(L06Obj *);
extern L06ColorPair g_marker_color_pairs[];
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void moby_transform_joint_point(void *moby, int joint, void *out);
extern void gfx_add_draw_callback_first(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
void marker_update_pulse_pal(L06Obj *self)
{
    L06Cfg *state = self->cfg;
    L06ColorPair colors = g_marker_color_pairs[0];
    unsigned short *id_ptr;
    L06Obj *entity;
    L06Cfg *entity_cfg;
    float angle;
    float blend;

    angle = FastAddRotations(state->angle, 0.25132746f);
    state->angle = angle;
    blend = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = FastTweenColor(colors.a, colors.b, blend);
    if (state->stamp != g_game_l06_frame_counter) {
        for (id_ptr = (unsigned short *)g_group_l06_id_lists[self->group];
             self->group != 0xFF && self->group <= g_moby_l06_group_count && id_ptr != 0 &&
             ((id_ptr != 0 && (short)id_ptr[-1] >= 0) || id_ptr == (unsigned short *)g_group_l06_id_lists[self->group]);
             id_ptr++) {
            entity = (L06Obj *)(D_L06_001B281C_base[0] + ((*id_ptr & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->live != 0) {
                if (entity->cls == 0xDB0) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (entity->kind != 0xFE) {
                        if (entity->kind != 0xFD) {
                            entity_cfg = entity->cfg;
                            moby_transform_joint_point(entity, 0, &entity_cfg->vec);
                            entity_cfg->stamp = g_game_l06_frame_counter;
                        }
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)marker_draw_group, self);
    }
}
