#include "common.h"

/* The resident block, as far as func_L00_002B9F00 reads it. */
typedef struct {
    u8 pad000[0xF0];
    float velocity[4];
    u8 pad100[0x214 - 0x100];
    short h214;
    u8 pad216[0x34E - 0x216];
    short h34E;
    u8 pad350[0x1497 - 0x350];
    u8 b1497;
    u8 pad1498[0x2290 - 0x1498];
    int i2290;
    int i2294;
    u8 pad2298[4];
    int i229C;
    u8 pad22a0[0x22B4 - 0x22A0];
    u8 b22B4;
    u8 pad22b5[0x24B8 - 0x22B5];
    float f24B8;
} ResidentState_9F00;

extern char D_00189F10[];
extern ResidentState_9F00 D_00189E20_2;
extern char g_hero_position[];
extern struct { char pad[0x1C]; int count; char pad20[0x20]; float v[4]; } g_collision_result;

extern float func_L00_002D3A58_1(void *);
extern void func_L00_002D3BD8_2(void *, void *, float);
extern void func_L00_002D3B58_1(void *, void *, float);
extern void func_00282CC0_3(void *, void *, void *);
extern int func_002761F8_1(void *, void *, int, int, int);
extern void func_00282D30_9f(void *, void *, float);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern void cam_offset_point_in_view_space(void *, void *, float);
extern float cam_get_view_space_angle(void *);
extern void hero_scale_saved_vectors(float);

/* Scale the hero's velocity into a push (at least minimum long), probe for a surface along it, and trigger the response unless the surface is too steep. */
void hero_try_surface_push_response(float amount, float minimum)
{
    /* The resident block is viewed from three symbols (velocity, block, hero). */
    char *vel = D_00189F10;
    ResidentState_9F00 *state;
    ResidentState_9F00 *base;
    ResidentState_9F00 *hero;
    float push[4], probe[4];
    char *origin;
    float enabled;

    if (func_L00_002D3A58_1(vel) == 0.0f)
        return;
    state = (ResidentState_9F00 *)((unsigned)vel - 0xF0);
    if (0.5f < state->f24B8 && state->i229C != 6 && state->h214 == 0 && state->b1497 == 0)
        return;
    base = &D_00189E20_2;
    if (base->h34E != 0)
        return;
    if (base->i2294 == 31)
        amount = 2.0f;

    func_00282D30_9f(push, base->velocity, amount);
    if (minimum > 0.0f && func_L00_002D3A58_1(push) < minimum) {
        func_L00_002D3BD8_2(push, push, 0.0f);
        cam_offset_point_by_side_direction(push, push, minimum);
    }
    func_L00_002D3B58_1(push, push, 0.0f);

    origin = g_hero_position;
    func_00282CC0_3(push, push, origin);
    qcopy(probe, push);
    cam_offset_point_in_view_space(push, push, 0.3f);
    hero = (ResidentState_9F00 *)(origin - 0x80);
    cam_offset_point_in_view_space(probe, probe, hero->b22B4 == 2 ? -0.7f : -0.35f);

    enabled = 1.0f;
    if (func_002761F8_1(push, probe, 4, hero->i2290, 0)) {
        if (g_collision_result.count > 0 &&
            cam_get_view_space_angle(g_collision_result.v) <= 0.8726646900177002f)
            enabled = 0.0f;
    }
    if (enabled != 0.0f)
        hero_scale_saved_vectors(0.0f);
}
