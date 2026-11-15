#include "common.h"

extern u8 D_001A7BD0[] __attribute__((sda));
extern char g_hero_position[];
extern s32 D_L07_001B1048 __attribute__((sda));
extern s32 D_L07_001B104C __attribute__((sda));
extern f32 D_L07_001B1050 __attribute__((sda));
extern s32 D_L07_001FE3B8[] NOT_SDA;

extern void moby_set_state(void *, s32, s32);
extern void moby_mark_spawned(void *);
extern void moby_init_child_from_parent(void *, void *);
extern u8 *CreateMoby(s32);
extern s32 FloatToInt(f32);
extern f32 math_interpolate_between_limits(s32, s32, f32, f32);
extern void boss_reset_with_children(void *);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern f32 moby_update_aim_target_strength(void *, void *);
extern void gfx_start_color_fade(void *, void *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern s32 weapon_select_aim_target(void *, s32, void *, s32, f32, f32);

#define F(p, o) (*(f32 *)((p) + (o)))
#define I(p, o) (*(s32 *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define U(p, o) (*(u16 *)((p) + (o)))

/* Updates a Siberius enemy that has several health stages. It spawns two attached parts when it starts, takes damage, and switches animation each time a stage is lost. */
void UpdatePhasedDamageState(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *part;
    f32 damage, scale;

    if (moby[0x20] == 0) {
        if (D_001A7BD0[0]) {
            moby_set_state(moby, 1, 2);
            moby_mark_spawned(moby);
            return;
        }
        vars[0x48] = FloatToInt(30.0f);
        vars[0x4A] = FloatToInt(11.2f);
        vars[0x2E] = 1;
        moby[0x30] = 255;
        part = CreateMoby(0xD41 /* moby class 3393 */);
        if (part) {
            moby_init_child_from_parent(part, moby);
            U(part, 0x34) |= 0x400;
            *(u8 **)(vars + 0x410) = part;
        }
        part = CreateMoby(0xD45 /* moby class 3397 */);
        if (part) {
            moby_init_child_from_parent(part, moby);
            *(u8 **)(vars + 0x414) = part;
            U(part, 0x34) |= 0x100;
        }
        if (H(vars, 0x24) == 0) {
            H(vars, 0x24) = 100;
            F(vars, 0x20) = 100.0f;
        } else {
            scale = 1.0f - math_interpolate_between_limits(5, 20, 0.0f, 0.5f);
            H(vars, 0x24) = FloatToInt(scale * (f32)H(vars, 0x24));
            F(vars, 0x20) *= scale;
        }
        {
            s32 active = D_L07_001B104C;

            H(*(u8 **)(moby + 0x24), 0x46) = 5;
            U(moby, 0x34) |= 0x5000;
            if (active)
                D_L07_001B1048++;
        }
        D_L07_001B104C = 0;
        moby_set_state(moby, 1, 2);
        boss_reset_with_children(moby);
    }
    F(vars, 0x30) = D_L07_001B1050;
    damage = moby_update_aim_target_strength(moby, part_find_owned_effect_slot(moby, 0x10000, 0));
    if ((I(vars, 0x420) >= 3 || (u32)(moby[0x20] - 10) >= 5) &&
        (damage != 0.0f || vars[0x2E] == 2)) {
        s32 amount = (s32)(damage * 32.0f);

        D_L07_001FE3B8[vars[0x37]] += amount;
        vars[0x167] = 150;
        gfx_start_color_fade(moby, vars + 0x160, amount);
        if (I(vars, 0x420) < 2)
            ApproachValue((f32 *)(vars + 0x20), F(vars, 0x430), damage);
        else
            ApproachValue((f32 *)(vars + 0x20), 0.0f, damage);
        if (vars[0x2E] == 2) {
            if ((f32)I(vars, 0x420) <= 1.0f)
                F(vars, 0x20) = F(vars, 0x430);
            else
                F(vars, 0x20) = 0.0f;
        }
        if (F(vars, 0x20) <= F(vars, 0x430)) {
            F(vars, 0x430) = (f32)H(vars, 0x24) - (f32)H(vars, 0x24) *
                ((f32)(I(vars, 0x420) + 2) * 0.16694492f);
            I(vars, 0x420)++;
            I(vars, 0x458) = FloatToInt(math_interpolate_between_limits(3, 7, 1.0f, 4.0f));
            if (F(vars, 0x20) - 1.0f < F(vars, 0x430))
                F(vars, 0x430) = F(vars, 0x20) - 1.0f;
            if (F(vars, 0x430) < 0.0f)
                F(vars, 0x430) = 0.0f;
            if (moby[0x95] == 0)
                moby_set_state(moby, 10, -1);
            else
                moby_set_state(moby, 12, -1);
        }
    }
    moby[0xA8] = 255;
    vars[0x2E] = 1;
    if (moby[0x95] == 0)
        weapon_select_aim_target(moby, -1, g_hero_position, 0, 16.0f, 4.0f);
    else
        weapon_select_aim_target(moby, I(vars, 0x188), 0, 0, 0.0f, 0.0f);
}
