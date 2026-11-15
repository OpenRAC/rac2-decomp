#include "common.h"
typedef struct {
    char pad0[0x2290]; void *object;
} UpdateHeroBase;
extern UpdateHeroBase g_hero_state;
extern void companion_update_carry_anim(void);
extern void hero_update_effect_slot(void);
extern void vec_add_transformed_point(void *, void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);

extern void AdvanceHeroAnimation(void);
extern void UpdateHeroInputAndHistory(void);
extern void hero_process_action_command(void);
extern void hero_find_ledge_grab(void *, void *, void *);
extern void UpdateHeroMotionResponseParameters(void);
extern void snd_update_slot_object(int, void *, int);
extern void snd_stop_voice(int);
extern void coll_sweep_from_object(void *, void *, float, float, int, int, float, int, int);
extern float hero_get_direction_angle_delta(void *, int);
extern float fast_subtract_rotations(float, float);
extern void hero_update_actions(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void UpdateHeroGlowAndExtraManipulators(void);
extern void UpdateHeroJointEffect(void);
extern void hero_update_held_object(void);
extern void PlayMobySound(void *, int, void *);
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
extern UpdateCamera D_L22_0025DE90;
extern int D_L22_001A8FF0;
/* Retail reads this byte only inside the mode-2 path (002AAD00..002AAD08).
 * Preserve that conditional access rather than speculating it before the guard.
 * Its owning allocation's extent is unknown, so retain an incomplete declaration. */
extern volatile unsigned char D_001A7A43[] MACRO_ADDR;
extern float D_L22_001A7CF8 __attribute__((sda));

/* Runs the hero's per-frame update for the current vehicle or mode, calling the movement, camera and effect updates in order. */
void hero_update(void) {
    float vec[4] __attribute__((aligned(16)));
    AdvanceHeroAnimation();
    UpdateHeroInputAndHistory();
    hero_process_action_command();
    {
        char *hero = (char *)&g_hero_state;
        if (*(u8 *)(hero + 0x22B4) == 1) {
            hero_find_ledge_grab(hero + 0x80, hero + 0x90, hero + 0x550);
            UpdateHeroMotionResponseParameters();
        }
        if (*(u8 *)(hero + 0x22B4) == 2) {
            if (*(int *)(hero + 0x2294) == 0x5B) {
                snd_update_slot_object(8, *(void **)(hero + 0x2290), 10);
            } else {
                int effectSlot = *(int *)(hero + 0x242C);
                if (effectSlot != -1) {
                    char *entry = g_sound_state + effectSlot * 0x70;
                    if (*(void **)(entry + 0x88) == *(void **)(hero + 0x2290) && *(u8 *)(entry + 0x74))
                        snd_stop_voice(effectSlot);
                }
                {
                    char *hero = (char *)&g_hero_state;
                    *(int *)(hero + 0x242C) = -1;
                }
            }
            {
                char *hero = (char *)&g_hero_state;
                if (*(int *)(hero + 0x33C)) {
                    vec_add_transformed_point(*(void **)(hero + 0x2290), vec, 0, 0, 2.5f);
                    FastVecAdd(vec, vec, hero + 0x80);
                    coll_sweep_from_object(*(void **)(hero + 0x2290), vec, 4, 100, 0x80000, 0, 1, 1, 0);
                }
                if (*(short *)(hero + 0x1454) && *(float *)(hero + 0x24B8) > 0.15f && !*(u8 *)(hero + 0x1456)) {
                    float angle;
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->field1498 = 0.27f;
                        camera->field1494 = 0.037f;
                        camera->field1334 = 0.025f;
                        camera->field1338 = 0.27f;
                    }
                    if (D_L22_001A8FF0) angle = hero_get_direction_angle_delta(hero + 0x1440, 0);
                    else angle = fast_subtract_rotations(*(float *)(hero + 0x1458), *(float *)(hero + 0x98));
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->angle = angle;
                        camera->negative_angle = -angle;
                    }
                }
            }
        }
    }
    hero_update_actions();
    RebuildRegionObjectMembership();
    {
        char *hero = (char *)&g_hero_state;
        if (!*(u8 *)(hero + 0x22B4)) return;
        UpdateDelayedSounds();
        attachment_update_all();
        if (!*(u8 *)(hero + 0x22B4)) return;
        hero_update_moby_from_hero();
        gfx_fade_screen_effect();
        ApplyHeroAxisScales();
        if (*(u8 *)(hero + 0x22B4) == 1) {
            D_L22_0025DE90.rate = D_L22_001A7CF8;
            UpdateHeroGlowAndExtraManipulators();
            UpdateHeroJointEffect();
            hero_update_held_object();
            if (*(char **)(hero + 0x24E4)) {
                PlayMobySound(*(char **)(hero + 0x24E4) + 0x10, 0, *(void **)(hero + 0x2290));
                *(u16 *)(hero + 0x2520) = 0x39;
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
            if (*D_001A7A43) D_L22_0025DE90.field13ec = D_L22_001A7CF8 * 1.4f;
            if (*(short *)(hero + 0x1E2) < 10000) ++*(u16 *)(hero + 0x1E2);
            UpdateHeroGlowAndExtraManipulators();
            companion_update_carry_anim();
            hero_update_effect_slot();
            if ((*(u16 *)(*(char **)(hero + 0x2290) + 0x34) ^ 1) & 1) {
                moby_transform_joint_to_world(*(void **)(hero + 0x2290), 6, vec);
                qcopy(pos + 0x1F90, vec);
                hero_queue_glow_draw_routine();
            }
        }
        UpdateHeroMobyProbedHeightBounds();
    }
    func_002A677C(g_hero_state.object);
}
