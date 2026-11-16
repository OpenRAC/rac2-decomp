#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x2290]; void *object;
} UpdateHeroBase;
extern UpdateHeroBase g_hero_state;
extern void companion_update_carry_anim(void);
extern void hero_update_effect_slot_pal(void);
extern void vec_add_transformed_point(void *, void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void AdvanceHeroAnimation_pal(void);
extern void UpdateHeroInputAndHistory_pal(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab_pal(void *, void *, void *);
extern void UpdateHeroMotionResponseParameters_pal(void);
extern void snd_update_slot_object(int, void *, int);
extern void snd_stop_voice(int);
extern int coll_sweep_from_object(void *, void *, float, float, int, int, float, int, int);
extern float hero_get_direction_angle_delta(void *, int);
extern float fast_subtract_rotations(float, float);
extern void hero_update_actions_pal(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds_pal(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void UpdateHeroGlowAndExtraManipulators_pal(void);
extern void UpdateHeroJointEffect_pal(void);
extern void hero_update_held_object_pal(void);
extern int PlayMobySound(void *, int, void *);
extern void coll_clear_map_bits_around_pos(void *);
extern void hero_queue_glow_draw_routine(void);
extern void UpdateHeroMobyProbedHeightBounds(void);
extern void func_002A677C(void *);
extern char g_sound_state[];
typedef struct {
    char pad0[0x11DC]; float rate;
    char pad11e0[0x12F8 - 0x11E0]; float negative_angle;
    char pad12fc[0x1334 - 0x12FC]; float field1334, field1338;
    char pad133c[0x13EC - 0x133C]; float field13ec;
    char pad13f0[0x1458 - 0x13F0]; float angle;
    char pad145c[0x1494 - 0x145C]; float field1494, field1498;
} UpdateCamera;
extern UpdateCamera g_hero_tuning_block;
extern int g_hero_flag_a;
extern volatile unsigned char g_state_flag_b[] MACRO_ADDR;
extern float g_hero_update_rate __attribute__((sda));

/* Runs the hero's per-frame update for the current vehicle or mode, calling the movement, camera and effect updates in order (PAL). */
void hero_update_pal(void) {
    float joint_pos[4] __attribute__((aligned(16)));
    AdvanceHeroAnimation_pal();
    UpdateHeroInputAndHistory_pal();
    hero_process_action_command();
    {
        char *hero = (char *)&g_hero_state;
        if (*(u8 *)(hero + 0x22B4) == 1) {
            hero_find_ledge_grab_pal(hero + 0x80, hero + 0x90, hero + 0x550);
            UpdateHeroMotionResponseParameters_pal();
        }
        if (*(u8 *)(hero + 0x22B4) == 2) {
            if (*(int *)(hero + 0x2294) == 0x5B) {
                snd_update_slot_object(8, *(void **)(hero + 0x2290), 10);
            } else {
                int voice_index = *(int *)(hero + 0x242C);
                if (voice_index != -1) {
                    char *voice = g_sound_state + voice_index * 0x70;
                    if (*(void **)(voice + 0x88) == *(void **)(hero + 0x2290) && *(u8 *)(voice + 0x74))
                        snd_stop_voice(voice_index);
                }
                {
                    char *hero = (char *)&g_hero_state;
                    *(int *)(hero + 0x242C) = -1;
                }
            }
            {
                char *hero = (char *)&g_hero_state;
                if (*(int *)(hero + 0x33C)) {
                    vec_add_transformed_point(*(void **)(hero + 0x2290), joint_pos, 0, 0, 2.5f);
                    FastVecAdd(joint_pos, joint_pos, hero + 0x80);
                    coll_sweep_from_object(*(void **)(hero + 0x2290), joint_pos, 4, 100, 0x80000, 0, 1, 1, 0);
                }
                if (*(short *)(hero + 0x1454) && *(float *)(hero + 0x24B8) > 0.15f && !*(u8 *)(hero + 0x1456)) {
                    float angle;
                    {
                        UpdateCamera *camera = &g_hero_tuning_block;
                        camera->field1498 = 0.38880002f;
                        camera->field1494 = 0.053280003f;
                        camera->field1334 = 0.036000002f;
                        camera->field1338 = 0.38880002f;
                    }
                    if (g_hero_flag_a) angle = hero_get_direction_angle_delta(hero + 0x1440, 0);
                    else angle = fast_subtract_rotations(*(float *)(hero + 0x1458), *(float *)(hero + 0x98));
                    {
                        UpdateCamera *camera = &g_hero_tuning_block;
                        camera->angle = angle;
                        camera->negative_angle = -angle;
                    }
                }
            }
        }
    }
    hero_update_actions_pal();
    RebuildRegionObjectMembership();
    {
        char *hero = (char *)&g_hero_state;
        if (!*(u8 *)(hero + 0x22B4)) return;
        UpdateDelayedSounds_pal();
        attachment_update_all();
        if (!*(u8 *)(hero + 0x22B4)) return;
        hero_update_moby_from_hero();
        gfx_fade_screen_effect();
        ApplyHeroAxisScales();
        if (*(u8 *)(hero + 0x22B4) == 1) {
            g_hero_tuning_block.rate = g_hero_update_rate;
            UpdateHeroGlowAndExtraManipulators_pal();
            UpdateHeroJointEffect_pal();
            hero_update_held_object_pal();
            if (*(char **)(hero + 0x24E4)) {
                PlayMobySound(*(char **)(hero + 0x24E4) + 0x10, 0, *(void **)(hero + 0x2290));
                *(u16 *)(hero + 0x2520) = 0x2F;
                *(u16 *)(hero + 0x2522) = *(u16 *)(hero + 0x24E4);
            }
            *(int *)(hero + 0x24E4) = 0;
        }
    }
    {
        char *pos = (char *)&g_hero_state + 0x80;
        char *hero = pos - 0x80;
        coll_clear_map_bits_around_pos(pos);
        if (*(u8 *)(hero + 0x22B4) == 2) {
            if (*g_state_flag_b) g_hero_tuning_block.field13ec = g_hero_update_rate * 1.4f;
            if (*(short *)(hero + 0x1E2) < 10000) ++*(u16 *)(hero + 0x1E2);
            UpdateHeroGlowAndExtraManipulators_pal();
            companion_update_carry_anim();
            hero_update_effect_slot_pal();
            if ((*(u16 *)(*(char **)(hero + 0x2290) + 0x34) ^ 1) & 1) {
                moby_transform_joint_to_world(*(void **)(hero + 0x2290), 6, joint_pos);
                qcopy(pos + 0x1F90, joint_pos);
                hero_queue_glow_draw_routine();
            }
        }
        UpdateHeroMobyProbedHeightBounds();
    }
    func_002A677C(g_hero_state.object);
}
