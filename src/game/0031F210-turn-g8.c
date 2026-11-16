#include "common.h"

/* Moby fields used by the update. */
typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0x47];
    char *data;
    char pad6c[0x29];
    unsigned char f95;
    unsigned short timer;
} TurnObject;

/* Per-object data: turn angle state, and two joint chains at +0x530 and +0x5B0. */
typedef struct {
    char pad00[0x26];
    char f26[2];
    char pad28[0x28];
    char f50[0x220];
    char f270[2];
    char f272[0x2E];
    char f2A0[0xC];
    float turnAngle;
    char pad2b0[0x14];
    int f2C4;
    char pad2c8[0x20];
    float turnRate;
    char pad2ec[0x10];
    char f2FC[0x234];
    char f530[0x80];
    char f5B0[1];
} TurnData;

extern void gfx_update_color_fade(void *, void *);
extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void value_set_and_smooth(void *, void *, int, int, float);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts(void *, float, void *, int, void *);
/* The incomplete sda array retains the retail absolute address macro. */
extern char g_default_effect_vector[] __attribute__((sda));
extern void gfx_draw_beam_quad_between_points_2(void);
extern void gfx_register_overlay_draw_callback(void (*)(void), void *);
extern void group_sync_counter(void *, void *);

/* Steer the object toward its turn target and update its joint chains. */
void group_enemy_update_turn_joints(TurnObject *object)
{
    TurnData *data = (TurnData *)object->data;

    if (object->f95 != 0 && object->state != 3 && object->f95 != 5 && data->f2C4 == 0) {
        data->turnAngle = FastAddRotations(data->turnAngle, data->turnRate * 0.017453294f);
        enemy_attach_turn_child_parts(object, data->turnAngle, data->f2A0, 1, g_default_effect_vector);
    } else {
        enemy_attach_turn_child_parts(object, data->turnAngle, data->f2A0, 0, g_default_effect_vector);
    }
    gfx_update_color_fade(object, data->f50);
    FastDecTimer(data->f270);
    FastDecTimer(data->f272);
    FastDecTimer(data->f26);
    moby_update_eased_node(object, data->f530, 7, 0.03f, 0.3f);
    moby_update_eased_node(object, data->f5B0, 8, 0.03f, 0.3f);
    if (object->timer < 65535)
        object->timer++;
    if (object->state == 4 || object->state == 5 || object->f95 == 2 || object->state == 10)
        gfx_register_overlay_draw_callback(gfx_draw_beam_quad_between_points_2, object);
    group_sync_counter(object, data->f2FC);
    value_set_and_smooth(object, data->f530, 7, 1, 2.5f);
}
