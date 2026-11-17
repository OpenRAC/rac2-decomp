#include "common.h"

typedef int Quad __attribute__((mode(TI)));

/* One of the three 0xA0-byte effect slots of D_0022AA10, filled by func_PAL_00317928. */
typedef struct {
    char pad0[0x8C];
    void *owner;                /* 0x8C: 0 for a free slot */
    char pad90[0x10];
} PoolEffect_00315E20;

typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;

/* The launch record func_002A8E20 takes. */
typedef struct {
    float dir[4];
    void *owner;
    int flags;
    u8 kind;
    u8 mode;
    u16 klass;
    float range;
    int count;
} Launch_00315E20;

/* The launcher's state. */
typedef struct { char pad0[0x18]; char *target; } State_00315E20;

extern PoolEffect_00315E20 g_pool_effect_slots[3];
extern char g_hero_state[];
extern Statistics g_statistics_table[];
extern char g_dynamo_joint_position[] __attribute__((sda));
extern char g_emitter_origin[] __attribute__((sda));
extern char g_camera_eye_state[];
extern int g_dynamo_launch_mode __attribute__((sda));
extern int g_pad_held_flags __attribute__((nosda));
extern u32 g_frame_counter;
extern u32 g_current_map_index;
extern u8 g_dynamo_weapon_index __attribute__((nosda));
/* One 0xE0-byte entry per weapon level. */
typedef struct { char pad0[0x70]; float range; char pad74[0x6C]; } Level_00315E20;

extern Level_00315E20 g_weapon_table[];

extern void moby_transform_joint_to_world(void *, int, void *);
extern unsigned int stub_empty_8(int, int);
extern char *FindNearestEligibleTarget(void *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern void hud_add_moby_marker(float, float, float, void *, u32, void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void stub_empty_10(void);
extern int math_fast_float_d(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void alloc_effect_slot_pal(void *, char *, int);
extern void UpdateEffectSlots(void *);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void lock_on_draw_sprites(void *);

/* Update of the lock-on launcher: 0 clears the effect slots, 1 aims at the nearest target and
   waits for the fire button, 2 launches at it and starts three effects, 3 and 4 time the
   cool-down. */
void dynamo_update_pal(u8 *moby)
{
    float dir[4];
    float aim[4];
    float pos[4];
    Launch_00315E20 launch;
    State_00315E20 *state = *(State_00315E20 **)(moby + 0x68);
    char *hero;
    char *hero_state;
    float distance;
    int i;

    *(Quad *)dir = 0;
    if (moby[0x20] == 0) {
        for (i = 2; i >= 0; i--)
            g_pool_effect_slots[i].owner = 0;
        moby[0x20] = 1;
    }
    moby_transform_joint_to_world(moby, 1, g_dynamo_joint_position);
    moby_transform_joint_to_world(moby, 0, g_emitter_origin);
    hero_state = g_hero_state;
    if (*(int *)(hero_state + 0x2294) == 1)
        stub_empty_8(0x1D, 1);
    moby_transform_joint_to_world(moby, 0, aim);

    switch (moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        state->target = 0;
    case 1:
        hero = g_hero_state;
        if (*(u8 *)(hero + 0x22BC) != 0)
            break;
        state->target = FindNearestEligibleTarget(moby);
        if (state->target != 0) {
            distance = fast_vec_dist(g_camera_eye_state, state->target + 0x10) * 0.02f;
            qcopy(pos, state->target + 0x10);
            hud_add_moby_marker(math_fabs(0.9f - distance * 0.65f), 0.0f, 90.0f, moby, 0xFF0FFF0F, pos, 0x26,
                          -1, 4);
            FastVecSub(dir, state->target + 0x10, aim);
        }
        if (!(g_pad_held_flags & *(int *)(hero + 0x1230)))
            break;
        if (state->target == 0)
            break;
        if (*(int *)(hero + 0x340) != 0)
            g_dynamo_launch_mode = 10;
        else
            g_dynamo_launch_mode = 3;
        moby[0x20] = 2;
        stub_empty_10();
        break;
    case 2: {
        char *player;
        Level_00315E20 *level;

        if (!math_fast_float_d(&g_dynamo_launch_mode))
            break;
        player = g_hero_state;
        *(int *)(player + 0xC20) = 0;
        if (g_statistics_table[36].count < 0xFFFF)
            g_statistics_table[36].count++;
        if ((((s32)(g_frame_counter) * 5 + 2) / 6) > g_statistics_table[36].maximum)
            g_statistics_table[36].maximum = (((s32)(g_frame_counter) * 5 + 2) / 6);
        level = &g_weapon_table[g_dynamo_weapon_index];
        launch.flags = 0x10000;
        g_statistics_table[36].levels = g_statistics_table[36].levels | (1 << g_current_map_index) | 0x80000000;
        launch.range = level->range;
        launch.count = 1;
        launch.owner = moby;
        qcopy(&launch, dir);
        vec_fast_normalize_helper(&launch, &launch, 1.0f);
        launch.mode = 2;
        launch.dir[2] = 1.0f;
        launch.dir[3] = 5627.925f;
        launch.klass = *(u16 *)(moby + 0xAA);
        launch.kind = 3;
        QueueMobyImpact(state->target, &launch);
        moby[0x20] = 3;
        if (*(int *)(player + 0x340)) {
            g_dynamo_launch_mode = 12;
            alloc_effect_slot_pal(moby, state->target, 6);
            alloc_effect_slot_pal(moby, state->target, 6);
            alloc_effect_slot_pal(moby, state->target, 6);
        } else {
            g_dynamo_launch_mode = 2;
            alloc_effect_slot_pal(moby, state->target, 2);
            alloc_effect_slot_pal(moby, state->target, 2);
            alloc_effect_slot_pal(moby, state->target, 2);
        }
        state->target = 0;
        break;
    }
    case 3: {
        char *player;

        if (!math_fast_float_d(&g_dynamo_launch_mode))
            break;
        player = g_hero_state;
        *(float *)(player + 0xC20) = 1.0f;
        g_dynamo_launch_mode = 6;
        moby[0x20] = 4;
        break;
    }
    case 4:
        if (math_fast_float_d(&g_dynamo_launch_mode))
            moby[0x20] = 1;
        break;
    }
    UpdateEffectSlots(moby);
    gfx_register_overlay_draw_callback(lock_on_draw_sprites, moby);
}