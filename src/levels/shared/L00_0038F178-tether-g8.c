#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char *owner;
    float speed;
    int field08, field0c, lifetime;
    char *attachment;
    int field18, field1c;
    char *attachment20;
    void *matrix24, *matrix28;
    int field2c;
    char pad30[0x14];
    float field44, field48;
    int field4c;
} TetherState;
typedef struct {
    char pad00[0x110]; float velocity[4]; char pad120[0x21C]; u8 *supportObject;
    char pad340[0x420]; float axis[4]; char pad770[0x1A90]; float matrix[2][16];
    char *current; char pad2284[0xC]; char *object;
} TetherHero;
extern TetherHero g_hero_state;
/* The moby fields set at spawn (RAC1 struct Moby: state, update_dist, visible, draw_dist). */
typedef struct { char pad00[0x20]; u8 state; char pad21[0xF]; u8 updateDist; u8 visible; s16 drawDist; } TetherActor;
extern int D_L00_001B1BE8[] __attribute__((sda)), D_L00_001B1A4C[] __attribute__((sda));
extern int D_L00_001A8FF0;
extern float D_L00_001AF0E4 __attribute__((sda));
extern float D_L00_001BF220[4];
extern char *CreateMoby(int);
extern s32 moby_get_private_value_2(u8 *);
extern float FastVecLength(void *);
extern void level_save_and_dim_lighting(void *), func_002A0F48(void *);
extern char *cam_follow_create(void *);
extern int hero_l00_set_action(int a0, int a1);
extern void mem_clear(void *, int, int), AttachManipulator(u8 *, u32, u8 *);
extern char *tether_create_fin_piece(char *);
extern void hero_copy_field_to_moby(u8 *);
extern int PlayMobySound(int, int, char *), CollLine(void *, void *, int, void *, int), ForceClaimNotice(int, int, int);
extern void cam_compute_view_direction(char *, char *, int), FastVecCross(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern int part_alloc_effect_slot(void *, int, float, float, float);
/* Creates the active tether actor and its attachments, inheriting the hero's support frame. */
char *visibomb_create_missile(char *owner, char *position, float yaw, float pitch) {
    char *actor = CreateMoby(0xAC /* Visibomb Missile */);
    TetherState *state;
    float start[4] __attribute__((aligned(16)));
    float side[4];
    if (actor) {
        state = *(TetherState **)(actor + 0x68);
        D_L00_001B1BE8[0] = 1;
        g_hero_state.current = actor;
        ((TetherActor *)actor)->updateDist = 0xFF;
        ((TetherActor *)actor)->visible = 1;
        ((TetherActor *)actor)->state = 1;
        ((TetherActor *)actor)->drawDist = 0xFF;
        if (D_L00_001A8FF0) {
            *(float *)(actor + 0xF8) = 0;
            *(float *)(actor + 0xF4) = 0;
        } else {
            *(float *)(actor + 0xF8) = yaw;
            *(float *)(actor + 0xF4) = pitch;
        }
        *(float *)(actor + 0xF0) = 0;
        *(float *)(actor + 0xFC) = 0;
        state->matrix24 = g_hero_state.matrix[0];
        state->matrix28 = g_hero_state.matrix[1];
        state->owner = owner;
        qcopy(actor + 0x10, position);
        state->field08 = 0;
        state->field0c = 0;
        if (g_hero_state.supportObject && moby_get_private_value_2(g_hero_state.supportObject))
            state->speed = FastVecLength(g_hero_state.velocity);
        else state->speed = 0;
        state->field18 = 0;
        state->field1c = 0;
        state->attachment = 0;
        state->field44 = 0.4f;
        state->lifetime = 3000;
        level_save_and_dim_lighting(actor);
        func_002A0F48(actor);
        {
            char *attachment = cam_follow_create(actor);
            state->attachment = attachment;
            hero_l00_set_action(28, 1);
        }
        mem_clear(state->matrix24, 0, 64);
        mem_clear(state->matrix28, 0, 64);
        AttachManipulator((u8 *)actor, 0, state->matrix24);
        AttachManipulator((u8 *)actor, 1, state->matrix28);
        {
            char *attachment = tether_create_fin_piece(actor);
            float dt = D_L00_001AF0E4;
            state->attachment20 = attachment;
            state->field48 = dt * 0.016666668f;
        }
        hero_copy_field_to_moby((u8 *)actor);
        state->field2c = PlayMobySound(0, 4, actor);
        *(Quad *)(start) = *(Quad *)(owner + 0x10);
        start[2] = ((float *)position)[2];
        if (CollLine(start, position, 0, g_hero_state.object, 0)) {
            *(u8 *)(actor + 0xBC) = 1;
            qcopy(actor + 0x10, D_L00_001BF220);
        }
        D_L00_001B1A4C[0] = 1;
        ForceClaimNotice(6, 0, 1);
        if (D_L00_001A8FF0) {
            *(u16 *)(actor + 0x34) |= 0x100;
            qcopy(actor + 0xC0, g_hero_state.axis);
            cam_compute_view_direction(actor + 0x10, actor + 0xE0, 1);
            FastVecCross(side, actor + 0xC0, actor + 0xE0);
            vec_scale_to_length(actor + 0xD0, side, 1.0f);
            FastVecCross(actor + 0xE0, actor + 0xD0, actor + 0xC0);
            *(float *)(actor + 0xCC) = *(float *)(actor + 0xDC) = *(float *)(actor + 0xEC) = 0.0f;
        }
        state->field4c = part_alloc_effect_slot(actor, 0, 1.0f, 1.0f, 1.0f);
    }
    return actor;
}
