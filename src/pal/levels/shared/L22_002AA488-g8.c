#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x2290]; void *object;
} UpdateHeroBase;
extern UpdateHeroBase g_hero_state;
extern void companion_update_carry_anim(void);
extern void func_PAL_L22_002AA488(void);
extern void vec_add_transformed_point(void *, void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L00_002B3608(void);
extern void hero_process_action_command(void);
extern void func_PAL_L00_002ACE70(void *, void *, void *);
extern void func_PAL_L00_002B88A0(void);
extern void snd_update_slot_object(int, void *, int);
extern void snd_stop_voice(int);
extern void coll_sweep_from_object(void *, void *, float, float, int, int, float, int, int);
extern float hero_get_direction_angle_delta(void *, int);
extern float fast_subtract_rotations(float, float);
extern void func_PAL_L22_002D1020(void);
extern void RebuildRegionObjectMembership(void);
extern void func_PAL_L00_002B9C20(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002A5B40(void);
extern void func_PAL_L00_002A5E98(void);
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
extern volatile unsigned char D_001A7A43[] MACRO_ADDR;
extern float D_L22_001A7CF8 __attribute__((sda));

void func_PAL_L22_002AA840(void) {
    float v[4] __attribute__((aligned(16)));
    func_PAL_L00_002D29E8();
    func_PAL_L00_002B3608();
    hero_process_action_command();
    {
        char *g = (char *)&g_hero_state;
        if (*(u8 *)(g + 0x22B4) == 1) {
            func_PAL_L00_002ACE70(g + 0x80, g + 0x90, g + 0x550);
            func_PAL_L00_002B88A0();
        }
        if (*(u8 *)(g + 0x22B4) == 2) {
            if (*(int *)(g + 0x2294) == 0x5B) {
                snd_update_slot_object(8, *(void **)(g + 0x2290), 10);
            } else {
                int n = *(int *)(g + 0x242C);
                if (n != -1) {
                    char *entry = g_sound_state + n * 0x70;
                    if (*(void **)(entry + 0x88) == *(void **)(g + 0x2290) && *(u8 *)(entry + 0x74))
                        snd_stop_voice(n);
                }
                {
                    char *g = (char *)&g_hero_state;
                    *(int *)(g + 0x242C) = -1;
                }
            }
            {
                char *g = (char *)&g_hero_state;
                if (*(int *)(g + 0x33C)) {
                    vec_add_transformed_point(*(void **)(g + 0x2290), v, 0, 0, 2.5f);
                    FastVecAdd(v, v, g + 0x80);
                    coll_sweep_from_object(*(void **)(g + 0x2290), v, 4, 100, 0x80000, 0, 1, 1, 0);
                }
                if (*(short *)(g + 0x1454) && *(float *)(g + 0x24B8) > 0.15f && !*(u8 *)(g + 0x1456)) {
                    float angle;
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->field1498 = 0.38880002f;
                        camera->field1494 = 0.053280003f;
                        camera->field1334 = 0.036000002f;
                        camera->field1338 = 0.38880002f;
                    }
                    if (D_L22_001A8FF0) angle = hero_get_direction_angle_delta(g + 0x1440, 0);
                    else angle = fast_subtract_rotations(*(float *)(g + 0x1458), *(float *)(g + 0x98));
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->angle = angle;
                        camera->negative_angle = -angle;
                    }
                }
            }
        }
    }
    func_PAL_L22_002D1020();
    RebuildRegionObjectMembership();
    {
        char *g = (char *)&g_hero_state;
        if (!*(u8 *)(g + 0x22B4)) return;
        func_PAL_L00_002B9C20();
        attachment_update_all();
        if (!*(u8 *)(g + 0x22B4)) return;
        hero_update_moby_from_hero();
        gfx_fade_screen_effect();
        ApplyHeroAxisScales();
        if (*(u8 *)(g + 0x22B4) == 1) {
            D_L22_0025DE90.rate = D_L22_001A7CF8;
            func_PAL_L00_002A56D0();
            func_PAL_L00_002A5B40();
            func_PAL_L00_002A5E98();
            if (*(char **)(g + 0x24E4)) {
                PlayMobySound(*(char **)(g + 0x24E4) + 0x10, 0, *(void **)(g + 0x2290));
                *(u16 *)(g + 0x2520) = 0x2F;
                *(u16 *)(g + 0x2522) = *(u16 *)(g + 0x24E4);
            }
            *(int *)(g + 0x24E4) = 0;
        }
    }
    {
        char *pos = (char *)&g_hero_state + 0x80;
        char *g = pos - 0x80;
        coll_clear_map_bits_around_pos(pos);
        if (*(u8 *)(g + 0x22B4) == 2) {
            if (*D_001A7A43) D_L22_0025DE90.field13ec = D_L22_001A7CF8 * 1.4f;
            if (*(short *)(g + 0x1E2) < 10000) ++*(u16 *)(g + 0x1E2);
            func_PAL_L00_002A56D0();
            companion_update_carry_anim();
            func_PAL_L22_002AA488();
            if ((*(u16 *)(*(char **)(g + 0x2290) + 0x34) ^ 1) & 1) {
                moby_transform_joint_to_world(*(void **)(g + 0x2290), 6, v);
                qcopy(pos + 0x1F90, v);
                hero_queue_glow_draw_routine();
            }
        }
        UpdateHeroMobyProbedHeightBounds();
    }
    func_002A677C(g_hero_state.object);
}
