#include "common.h"

typedef struct DamoselHeroView {
    u8 pad0[0xBF8];
    void *saved;
    u8 padBFC[0x1230 - 0xBFC];
    int mask;
    u8 pad1234[0x1244 - 0x1234];
    int mode;
    u8 pad1248[0x1450 - 0x1248];
    void *vehicle;
    u8 pad1454[0x2290 - 0x1454];
    u8 *moby;
    int action;
    u8 pad2298[0x22BC - 0x2298];
    u8 blocked;
    u8 pad22BD[0x2534 - 0x22BD];
    int timer;
} DamoselHeroView;
extern DamoselHeroView g_hero_state;
extern u8 g_sound_state[], g_item_slot_to_record[];
typedef struct DamoselInputView {
    u8 pad[0x1A0];
    int held, pressed;
} DamoselInputView;
extern DamoselInputView g_pad_state;
typedef struct DamoselWeaponView {
    u8 pad[0x70];
    float damage;
    u8 tail[0x6C];
} DamoselWeaponView;
extern u8 D_L18_0026BCF0[];
typedef struct DamoselHitRecord {
    float direction[4];
    u8 pad10[8];
    u8 type, active;
    u16 classId;
    int pad1C, flag;
    u8 pad24[12];
} __attribute__((aligned(16))) DamoselHitRecord;

typedef int DamoselQuad __attribute__((mode(TI)));
extern u8 *D_L18_001B1DCC __attribute__((sda));
extern u8 *D_L18_001B1DD0 __attribute__((sda));
extern u8 *D_L18_001B1DC8 __attribute__((sda));
extern u8 *g_nearby_hit_targets[];
extern int D_L18_001A8FF0, D_L18_001A8F00;
extern void table_clear_entry_flag(int);
extern int AcquireEntitySlot(void *, int, void *);
extern u8 *level_get_slot_body(int, int);
extern unsigned char *mem_align_up_sixteen_alt(void *);
extern void snd_stop_voice(int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int math_fast_float_d(void *);
extern int get_ammo(int);
extern float math_spring_float_to_goal(void *, void *, float, float, float, float);
extern int weapon_spend_ammo(int, int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern void anim_start_blended(void *, int, int, int);
extern int coll_process_hit(float, void *, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern void QueueMobyImpact(void *, void *);
extern int StartAttachedEffect(void *, int, void *);
extern s32 hero_l18_set_action(int, int);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_compute_object_to_target(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void AppendVectorRingEntry(void *, void *, void *, int);
extern void lava_gun_update_blobs(void *);
extern void lava_gun_update_ring_entries(void *);
extern void part_l00_update_effect_slots_2(void *);
extern void gfx_add_draw_callback_third(void (*)(char *), void *);
extern void lava_gun_draw_shot(char *);

/* Updates the Lava Gun (moby class 1481): while the fire button is held it sprays lava, hurting targets in front and playing a sound, and updates the stream effects. */
void lava_l18_gun_update(u8 *obj)
{
    float velocity[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    DamoselHitRecord hit;
    int scratch;
    u8 *state = *(u8 **)(obj + 0x68);
    int i = 0, active, count;
    u8 *entry;
    u8 **targets;
    if (g_hero_state.mode == 3 && D_L18_001B1DCC) {
        for (i = 0; i < 35; i++) {
            u8 *entry = D_L18_001B1DCC + i * 64;
            if (*(int *)(entry + 0x38) >= 0) {
                table_clear_entry_flag(*(int *)(entry + 0x38));
                *(int *)(entry + 0x38) = -1;
            }
        }
    }
    if (!obj[0x20]) {
        *(int *)(state + 0x34) = AcquireEntitySlot(obj, 0, &scratch);
        D_L18_001B1DD0 = level_get_slot_body(*(short *)(obj + 0xAA), *(int *)(state + 0x34));
        D_L18_001B1DC8 = mem_align_up_sixteen_alt(D_L18_001B1DD0 + 0x33E0);
        D_L18_001B1DCC = mem_align_up_sixteen_alt(D_L18_001B1DC8 + 0x1F40);
        {
            int *word = (int *)(D_L18_001B1DC8 + 0x1F30);
            for (i = 124; i >= 0; i--, word -= 16) *word = 1;
        }
        entry = D_L18_001B1DD0 + 0x33C4;
        for (i = 9; i >= 0; i--, entry -= 0x530) *(int *)entry = 0;
        {
            int invalid = -1;
            entry = D_L18_001B1DCC + 0x8B8;
            for (i = 34; i >= 0; i--, entry -= 64) *(int *)entry = invalid;
        }
        *(int *)(state + 0x3C) = 0; *(int *)(state + 0x48) = 0;
        *(int *)(state + 0x40) = 0; *(int *)(state + 0x44) = 0;
        *(int *)(state + 0x54) = 0; *(int *)(state + 0x50) = 0;
        *(int *)(state + 0x58) = 0; *(int *)(state + 0x5C) = 0;
        *(int *)(state + 0x60) = 0; *(int *)(state + 0x64) = 0;
        obj[0x20] = 1; *(int *)(state + 0x38) = -1;
    }
    if (g_hero_state.mode == 3) {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = g_sound_state + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) snd_stop_voice(handle);
        }
        *(int *)(state + 0x38) = -1;
        return;
    }
    moby_transform_joint_to_world(obj, 0, state);
    if (obj[0x42] == obj[0x43] && (obj[0x60] & 2)) anim_start_blended_with_flags(obj, 1, 0, 2, 0);
    active = 1;
    if (g_hero_state.action == 29) {
        if (!math_fast_float_d(&g_hero_state.timer)) active = 0;
    } else g_hero_state.timer = 40;
    if ((g_pad_state.held & g_hero_state.mask) && active && get_ammo(-1) && !g_hero_state.blocked) {
        math_spring_float_to_goal(state + 0x50, state + 0x54, 10.0f, 0.0075f, 0.002f, 10.0f);
        if (*(int *)(state + 0x60) % 10 == 0) weapon_spend_ammo(-1, 1);
        ++*(int *)(state + 0x60);
        if (!snd_is_voice_playing_for_owner(obj, *(int *)(state + 0x38))) *(int *)(state + 0x38) = PlayMobySound(0, 4, obj);
        if (obj[0x43] != 2) anim_start_blended(obj, 2, 0, 0);
        count = coll_process_hit(0.5f, state, 16, obj, 0);
        if (count > 0) {
            targets = g_nearby_hit_targets;
            {
                int remaining = count;
                do {
                    if (*targets != g_hero_state.moby) {
                        FastVecSub(direction, *targets + 0x10, obj + 0x10);
                        vec_scale_to_length(direction, direction, 1.0f);
                        vec_scale_to_length(&hit, &hit, 1.0f);
                        make_hit_descriptor(&hit, obj, 0x910000,
                            ((DamoselWeaponView *)(D_L18_0026BCF0 + g_item_slot_to_record[0x1D] * 0xE0))->damage,
                            direction);
                        hit.flag = 1;
                        *(DamoselQuad *)&hit = *(DamoselQuad *)direction;
                        hit.direction[3] = 5627.925f;
                        hit.type = 9; hit.active = 1;
                        hit.classId = *(short *)(*targets + 0xAA);
                        QueueMobyImpact(*targets, &hit);
                        StartAttachedEffect(*targets, 29, obj);
                        PlayMobySound(1, 0, obj);
                    }
                    ++targets;
                } while (--remaining);
            }
        }
    } else {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = g_sound_state + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) snd_stop_voice(handle);
        }
        *(int *)(state + 0x38) = -1;
        if ((g_pad_state.pressed & g_hero_state.mask) && !get_ammo(-1) && !g_hero_state.blocked) PlayMobySound(2, 0, obj);
        math_spring_float_to_goal(state + 0x50, state + 0x54, 0.0f, 0.06f, 0.01f, 0.125f);
        *(int *)(state + 0x60) = 0;
    }
    if (g_hero_state.action == 1) hero_l18_set_action(29, 1);
    moby_transform_joint_to_world(obj, 0, state);
    vec_clear_128(velocity);
    velocity[1] = -1.0f;
    matrix_mul_vec3(velocity, velocity, obj + 0xC0);
    velocity[2] += 0.02f;
    vec_scale_to_length(velocity, velocity, *(float *)(state + 0x50) * 0.05f);
    if (g_hero_state.vehicle) {
        g_hero_state.saved = g_hero_state.vehicle;
        vec_compute_object_to_target(g_hero_state.vehicle, state, velocity, *(float *)(state + 0x50) * 0.05f);
        if (D_L18_001A8FF0) {
            FastVecScale(direction, obj + 0xE0, 0.02f);
            FastVecAdd(velocity, velocity, direction);
        } else {
            velocity[2] += 0.02f;
        }
    }
    qcopy(state + 0x10, state);
    if (g_hero_state.action) math_apply_axis_rotation_to_quat(velocity, velocity, g_hero_state.moby + 0xD0, -0.09817477f);
    if (*(float *)(state + 0x50) != 0.0f) AppendVectorRingEntry(obj, state, velocity, 40);
    *(float *)(state + 0x58) -= 0.1f;
    if (*(float *)(state + 0x58) <= -8.0f) *(float *)(state + 0x58) += 8.0f;
    *(float *)(state + 0x5C) -= 0.025f;
    if (*(float *)(state + 0x5C) <= -8.0f) *(float *)(state + 0x5C) += 8.0f;
    if (*(float *)(state + 0x50) != 0.0f) {
        lava_gun_update_blobs(obj); lava_gun_update_ring_entries(obj);
    } else {
        *(int *)(state + 0x44) = 0; *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x48) = 0; *(int *)(state + 0x40) = 0;
    }
    part_l00_update_effect_slots_2(obj);
    if (D_L18_001A8F00 != 2 && obj[0x31]) gfx_add_draw_callback_third(lava_gun_draw_shot, obj);
}
