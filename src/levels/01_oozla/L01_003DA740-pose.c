#include "common.h"

/* func_L01_00405300, in a unit of its own: retail reaches its globals with
   assembler macro loads (-mno-split-addresses), which keep its branches from
   taking the loads into their delay slots. The pose types are those of
   func_L01_003EC0C0 (L01_003DA740.c); struct (not cast) accesses matter there
   too, for the order of the table and index loads. */

typedef struct {
    unsigned char pad00[0x30];
    float position[4];              /* 0x30 */
    unsigned char pad40[0x30];
    float rotation[4];              /* 0x70 */
} PoseRecord;
typedef struct {
    unsigned char pad00[0x20];
    float track[4];                 /* 0x20 */
    unsigned char pad30[0x2C];
    int flags;                      /* 0x5C */
    float start_position[4];        /* 0x60 */
    float start_rotation[4];        /* 0x70 */
    int index;                      /* 0x80 */
    float duration;                 /* 0x84 */
    float t;                        /* 0x88 */
    int link;                       /* 0x8C */
    int sound;                      /* 0x90 */
} PoseMotion;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];              /* 0x10 */
    unsigned char state;            /* 0x20 */
    unsigned char pad21[0x13];
    unsigned short flags;           /* 0x34 */
    unsigned char pad36[0x32];
    PoseMotion *vars;               /* 0x68 */
    unsigned char pad6C[0x3C];
    unsigned char hit_slot;         /* 0xA8 */
    unsigned char padA9[0x13];
    unsigned char command;          /* 0xBC */
    unsigned char padBD[0x33];
    float rotation[4];              /* 0xF0 */
} PoseMoby;
typedef struct { unsigned char data[256]; } AttachObject;

extern AttachObject *g_moby_l01_table __attribute__((sda));
extern PoseRecord *g_swamp_patrol_positions MACRO_ADDR;
extern unsigned char g_hero_input_enabled[];
extern unsigned char g_hero_override_flag[];
extern float math_fast_sin_or_cos_a(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_move_angle_toward_target(float, float, float);
extern void moby_set_state(void *, int, int);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Eases into its table pose once its command byte is set, its linked moby is
   missing or dying (state 0xFE/0xFD), D_001A7B0B is clear or D_001A7B2A set;
   then sets bit 2 of its flags. */
/* Moves the object smoothly to a set position and angle when triggered, then keeps it there. */
void move_to_pose_update(PoseMoby *moby)
{
    float position[4], rotation[4], delta[4];
    PoseMotion *p = moby->vars;
    float blend;

    qcopy(position, moby->position);
    qcopy(rotation, moby->rotation);
    switch (moby->state) {
    case 0:
        p->t = 0.0f;
        p->flags |= 1;
        qcopy(p->start_position, moby->position);
        qcopy(p->start_rotation, moby->rotation);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (moby->command || p->link == -1 ||
            g_moby_l01_table[p->link].data[0x20] == 0xfe ||
            g_moby_l01_table[p->link].data[0x20] == 0xfd ||
            !g_hero_input_enabled[0] || g_hero_override_flag[0])
            moby_set_state(moby, 2, -1);
        moby->hit_slot = 255;
        break;
    case 2:
        p->t += 1.0f / p->duration;
        if (p->t > 1.0f) p->t = 1.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(p->t * 3.1415927f)) * 0.5f;
        FastVecSub(delta, g_swamp_patrol_positions[p->index].position, p->start_position);
        FastVecScale(delta, delta, blend);
        FastVecAdd(moby->position, p->start_position, delta);
        moby->rotation[2] = math_move_angle_toward_target(p->start_rotation[2], g_swamp_patrol_positions[p->index].rotation[2], blend);
        moby->rotation[1] = math_move_angle_toward_target(p->start_rotation[1], g_swamp_patrol_positions[p->index].rotation[1], blend);
        moby->rotation[0] = math_move_angle_toward_target(p->start_rotation[0], g_swamp_patrol_positions[p->index].rotation[0], blend);
        if (p->t >= 1.0f) moby_set_state(moby, 3, -1);
        break;
    case 3:
        moby->flags |= 2;
        break;
    }
    if (moby->state < 3) {
        FastVecSub(delta, moby->position, position);
        mat_combine_and_store(p->track, delta, rotation, moby->rotation);
    }
}
