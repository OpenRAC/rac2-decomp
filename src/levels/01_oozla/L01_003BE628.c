#include "common.h"

#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))
#define S16(p, o) (*(short *)((p) + (o)))

extern int weapon_select_aim_target(void *, int, void *, int, float, float);
extern void moby_update_floor_and_ceiling_heights(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void moby_release_attack_slot(void *), moby_trigger_linked_groups(void *), moby_free_glow_light(void *);
extern int math_fast_helper_a(void *, float);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern u8 g_dynamic_light_table[];
/* Integer and FP arguments retain their independent EE register order. */
extern u8 *CreateAttachedType57Effect(float, void *, unsigned int, int);
extern int math_fast_float_d(int *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);

/* Per-frame upkeep for the Mutant Firefly: handles hits, its glow light, glow effect and the timers that change its speed. */
void firefly_update_collision_and_light(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68), *effect, *entry;
    float sphere[4] __attribute__((aligned(16)));
    float effect_position[4] __attribute__((aligned(16)));
    float *object_position;
    int contact, active;
    weapon_select_aim_target(moby, I32(vars, 0x29c), 0, 0, F32(vars, 0x22c), 0.0f);
    moby_update_floor_and_ceiling_heights(moby);
    F32(moby, 0x2c) = F32(*(u8 **)(moby + 0x24), 0x24) * 1.25f;
    contact = moby_apply_damage_to_object(moby, vars + 0x50, 0);
    if (contact) {
        if (F32(vars, 0x20) <= 0.0f) I32(vars, 0xcc) = -1;
        moby_release_attack_slot(moby);
        moby_trigger_linked_groups(moby);
        effect = *(u8 **)(vars + 0x290);
        if (effect && effect + 0x20 && effect[0] == 0x57) {
            I32(effect, 0x20) = 0;
            *(u8 **)(vars + 0x290) = 0;
        }
    }
    object_position = (float *)(moby + 0x10);
    qcopy(sphere, object_position);
    active = moby[0x31];
    sphere[3] = 4.0f;
    if ((active || math_fast_helper_a(sphere, (float)S16(moby, 0x32)) != -1)
        && (unsigned int)(moby[0x20] - 2) < 7) {
        if (S16(vars, 0x202) == -1) {
            qcopy(effect_position, object_position);
            effect_position[2] += 1.0f;
            F32(vars, 0x204) = 0.01f;
            S16(vars, 0x202) = part_l00_alloc_effect_slot_2(effect_position, 4.0f, 0.0f, 0.01f, 0.008999999612569809f, 0.003000000026077032f);
        } else {
            F32(vars, 0x204) += 0.01f;
            if (F32(vars, 0x204) > 1.0f) F32(vars, 0x204) = 1.0f;
            entry = g_dynamic_light_table + S16(vars, 0x202) * 32;
            F32(entry, 0) = F32(vars, 0x204);
            F32(entry, 4) = F32(vars, 0x204) * 0.9f;
            F32(entry, 8) = F32(vars, 0x204) * 0.3f;
            F32(entry, 0x10) = F32(moby, 0x10);
            F32(entry, 0x14) = F32(moby, 0x14);
            F32(entry, 0x18) = F32(moby, 0x18) + 1.0f;
        }
        if (*(u8 **)(vars + 0x290) == 0)
            *(u8 **)(vars + 0x290) = CreateAttachedType57Effect(210000.0f, moby, 0x40105070, -1);
    } else {
        effect = *(u8 **)(vars + 0x290);
        if (effect && effect[0] == 0x57 && effect + 0x20) {
            I32(effect, 0x20) = 0;
            *(u8 **)(vars + 0x290) = 0;
        }
        if (S16(vars, 0x202) != -1) moby_free_glow_light(moby);
    }
    if (moby[0x20] >= 6 && math_fast_float_d((int *)(vars + 0x258))) {
        if (F32(vars, 0x24c) > 0.5f) F32(vars, 0x24c) = math_random_float_range(0.0f, 0.4f);
        else F32(vars, 0x24c) = math_random_float_range(0.6f, 1.0f);
        I32(vars, 0x258) = math_random_int_range(45, 150);
    }
    if (moby[0x20] == 8) F32(vars, 0x28c) = 1.0f;
    else if (moby[0x20] >= 6 && math_fast_float_d((int *)(vars + 0x25c))) {
        if (F32(vars, 0x28c) > -1.75f) F32(vars, 0x28c) = math_random_float_range(0.5f, 1.1f);
        else F32(vars, 0x28c) = math_random_float_range(1.6500000953674316f, 5.0f);
        I32(vars, 0x25c) = math_random_int_range(110, 60);
    }
}
