#include "common.h"
/* Preserve the observed integer/FP argument banks and the dispatcher's 64-bit flags. */
extern void small_enemy_part_update(u8 *), turret_l16_aim_at_hero(u8 *), EmitSnivelakBoneParticles(u8 *);
extern int math_random_int_below(int), math_random_int_range(int, int), FastDecTimer(short *);
extern void moby_set_state(void *, u8, int), anim_start_blended(void *, int, int, int);
typedef struct {
    u8 reserved_00[0x18];
    u8 enabled, count, kind;
    u8 reserved_1b[0x65];
    u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
extern DispatchFlags moby_dispatch_action_by_kind(
    void *, DispatchContext *);
extern void vec_random_direction(void *, float, float), FastVecAdd(void *, void *, void *);
extern float math_fabs(float), math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern u8 *cam_moby_create(void *, int, int, int, void *, void *, void *, int, float, float);
extern u8 *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *), hero_copy_field_to_moby(void *), moby_fade_out_update(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern char *part_l13_spawn_flash(void *, int, int, int, int, int, int, int, float, int, int);
extern void SetDeathBits(void *, int, int), moby_mark_spawned(void *);
extern int math_is_value_within_step(void *, float);
extern void FastVecSub(void *, void *, void *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern u8 *snivelak_spawn_spark_projectile(void *, void *, void *, int, float);
extern int path_check_entry_for_moby(char *, int);
extern float g_particle_template[] __attribute__((sda));
/* Partial view of the shared effect controls: retail forms this base once. */
extern struct {
    u8 pad000[0x160];
    float strength;
    u8 pad164[4];
    int duration, timer;
    u8 pad170[0x10];
    float damping;
    u8 pad184[4];
    int lifetime;
} D_L16_001B99C0;

/* Updates the object's activation states, death debris and timed aiming sequence. */
void UpdateSnivelakActivationAndDebris(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float velocity[4] __attribute__((aligned(16)));
    float aim[4] __attribute__((aligned(16)));
    DispatchFlags flags;
    u8 *child;
    int i;
    small_enemy_part_update(moby);
    switch (moby[0x95]) {
    case 0:
        *(short *)(state + 0x23e) = math_random_int_below(30);
        if (*(int *)(state + 0x240) == 1 && FastDecTimer((short *)(state + 0x23e))) {
            if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 10);
            moby_set_state(moby, 3, 2);
            break;
        }
        if (*(int *)(state + 0x244)) {
            moby_set_state(moby, 2, 1);
            *(int *)(state + 0x244) = 0;
            if (*(int *)(state + 0x238) < 300)
                *(int *)(state + 0x238) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (*(int *)(state + 0x354) != 1 && *(int *)(state + 0x240) != 1)
            break;
        moby_set_state(moby, 3, 2);
        break;
    case 2:
        if (*(int *)(state + 0x240) == 1) break;
        if (*(int *)(state + 0x354) == 1) break;
        moby_set_state(moby, 2, 1);
        *(int *)(state + 0x238) = math_random_int_range(580, 600);
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(moby, (DispatchContext *)(state + 0x140));
        if ((flags & 1UL) == 1UL) {
            for (i = 0; i < 4; i++) {
                vec_random_direction(velocity, 0.13333334f, 0.20000002f);
                velocity[2] = math_fabs(velocity[2]);
                velocity[2] *= 1.5f;
                FastVecAdd(velocity, velocity, g_particle_template);
                child = cam_moby_create(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, velocity, 255, 30.0f, 15.0f);
                *(void (**)(void *))(child + 0x64) = moby_fade_out_update;
            }
            child = CreateMoby(0x10ce);
            moby_init_child_from_parent(child, moby);
            *(float *)(child + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
            hero_copy_field_to_moby(child);
            part_l13_spawn_flash(moby + 0x10, 0, 45, 40, 40, 40, 45, 1, 1.0f, 1, 1);
            g_snivelak_hero_state.lifetime = 90;
            g_snivelak_hero_state.strength = 0.2f;
            g_snivelak_hero_state.duration = 60;
            g_snivelak_hero_state.damping = 0.1f;
            g_snivelak_hero_state.timer = 0;
            velocity[0] = math_random_signed_float_range(0.5f, 4.0f) * 0.016666668f;
            velocity[1] = math_random_signed_float_range(0.0f, 4.0f) * 0.016666668f;
            velocity[2] = math_random_float_range(7.0f, 9.0f) * 0.016666668f;
            velocity[2] = math_fabs(velocity[2]);
            velocity[2] *= 3.0f;
            FastVecAdd(velocity, velocity, g_particle_template);
            child = cam_moby_create(moby, 3, 0xecb, 0, moby + 0x10,
                moby + 0xf0, velocity, 255, 180.0f, 25.0f);
            hero_copy_field_to_moby(child);
            SetDeathBits(moby, 0, 3);
            moby_mark_spawned(moby);
            return;
        }
        if ((flags & 2UL) == 2UL) {
            if (*(int *)(state + 0x240) == 1 || *(int *)(state + 0x354) == 1) {
                if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 10);
                moby_set_state(moby, 3, 2);
            } else {
                moby_set_state(moby, 2, 1);
                *(int *)(state + 0x238) = math_random_int_range(580, 600);
            }
        }
        break;
    }
    switch (moby[0x20]) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (math_is_value_within_step(moby, 1.0f)) {
            moby_transform_joint_to_world((char *)moby, 2, (char *)velocity);
            FastVecSub(aim, state + 0x1f0, velocity);
            vec_scale_to_length(aim, aim, 0.416666687f);
            snivelak_spawn_spark_projectile(moby, aim, velocity, 0, 2.0f);
        }
        if (*(int *)(state + 0x24c) != -1)
            path_check_entry_for_moby((char *)moby, *(int *)(state + 0x24c));
        if (*(unsigned short *)(moby + 0x96) > 180) {
            if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(state + 0x24c) != -1)
            path_check_entry_for_moby((char *)moby, *(int *)(state + 0x24c));
        if (*(unsigned short *)(moby + 0x96) > 180) {
            if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 10);
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    turret_l16_aim_at_hero(moby);
    EmitSnivelakBoneParticles(moby);
}
