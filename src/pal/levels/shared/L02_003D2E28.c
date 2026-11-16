#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_b(float);
extern char *g_moby_l02_pool __attribute__((sda));
extern char *g_entity_group_lists[];
extern float FastAddRotations(float, float);
extern int g_group_max_index __attribute__((sda));
typedef int L02Word;
extern L02Word g_group_max_index __attribute__((sda));
extern int g_group_max_index __attribute__((sda));
extern void chickenbot_emit_sparks(char *);
extern int g_frame_l02_counter __attribute__((sda));
struct L02PairWord {
    int a;
    int b;
};
extern struct L02PairWord g_chickenbot_color_pair;
extern float FastAddRotations(float, float);
extern int FastTweenColor(int, int, float);
extern void moby_transform_joint_point(char *, int, void *);
extern void gfx_add_draw_callback_first(void *, void *);
struct L02Kind330 {
    char pad[0x328];
    float f328;
    float f32C;
    int f330;
};
struct L02Kind330Entity {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x10];
    unsigned char f31;
    char pad2[0x36];
    struct L02Kind330 *obj;
    char pad3[0x3E];
    short type;
};
struct L02Kind330Object {
    char pad0[0x21];
    unsigned char group;
    char pad1[0x46];
    struct L02Kind330 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L02_001B30C8 differs from the object's word at +0x330, walks the object's group
   and refreshes every live entity of kind 0xA4E, then registers func_L02_003CEFD8. */
void chickenbot_update_group_pulse_color_pal(struct L02Kind330Object *moby) {
    struct L02Kind330 *pulse = moby->obj;
    struct L02PairWord colors = g_chickenbot_color_pair;
    float value;
    unsigned short *member;
    struct L02Kind330Entity *entity;
    struct L02Kind330 *entity_data;

    value = FastAddRotations(pulse->f328, 0.25132746f);
    pulse->f328 = value;
    value = math_fast_sin_or_cos_b(value);
    pulse->f32C = value * 0.5f + 0.5f;
    moby->f78 = FastTweenColor(colors.a, colors.b, pulse->f32C);
    if (pulse->f330 != g_frame_l02_counter) {
        for (member = (unsigned short *)g_entity_group_lists[moby->group];
             moby->group != 0xFF && moby->group <= g_group_max_index && member != 0 &&
             ((member != 0 && (short)member[-1] >= 0) || member == (unsigned short *)g_entity_group_lists[moby->group]);
             member++) {
            entity = (struct L02Kind330Entity *)(g_moby_l02_pool + ((*member & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->f31 != 0 && entity->type == MOBY_CLASS_MEGACORP_CHICKENBOT && entity->state != 0xFE && entity->state != 0xFD) {
                entity_data = entity->obj;
                moby_transform_joint_point((char *)entity, 0, (char *)entity_data + 0x220);
                entity_data->f330 = g_frame_l02_counter;
            }
        }
        gfx_add_draw_callback_first((void *)chickenbot_emit_sparks, moby);
    }
}

