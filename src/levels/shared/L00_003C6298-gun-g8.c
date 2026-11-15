#include "common.h"

#define FIELD(p, type, offset) (*(type *)((char *)(p) + (offset)))
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    Vec position;
    char *target;
    float health, remaining;
    short timer, active;
    char pad20[0x24];
    int cooldown;
    float yaw, pitch;
    char beam[0x10];
} BeamContext;
typedef struct { unsigned short count, pad; unsigned int maximum, levels; } Statistics;
typedef struct { char pad[0x10]; Vec position; } Light;
typedef struct { char pad[0xE0]; } Weapon;
typedef struct {
    char pad000[0x730]; Vec matrix[3];
    char pad760[0xAD0]; int input;
    char pad1234[0x10]; int weapon;
    char pad1248[0x1048]; char *object;
    int state, field2298, mode;
    char pad22A0[0x18]; unsigned char flag;
    char pad22B9[0x233]; short aiming;
    char pad24EE[0x46]; int timer;
} Hero;
extern Hero g_hero_state;
extern Statistics D_0018C360[];
extern unsigned int D_001A7390 MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern unsigned int D_00138320 NOT_SDA;
extern unsigned char D_00139578 NOT_SDA;
extern Weapon g_weapon_l00_table[];
extern int D_L00_001B2A0C MACRO_ADDR;
extern int D_L00_001B2A04 MACRO_ADDR;
extern int D_L00_001B2A08 MACRO_ADDR;
extern int D_L00_001B2A00 __attribute__((sda));
extern int D_L00_001B2A08_sda __attribute__((sda));
extern int D_L00_001B2A0C_sda __attribute__((sda));
extern int D_L00_001AFFAC __attribute__((sda));
extern float D_L00_001AFFA8 __attribute__((sda));
extern float D_L00_001AFFC8 __attribute__((sda));
extern float D_L00_001AFFB8[2];
extern int D_L00_001AFFB0[2];
extern int D_L00_001AFFB0_sda __attribute__((sda));
extern int D_L00_001B0E30[] __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern int D_L00_001A903C[] MACRO_ADDR;
extern Light D_L00_001C6F40[];
typedef struct { char prefix[0x74]; unsigned char active; char pad75[0x13]; char *owner; } SoundView;
extern char g_sound_state[];
extern Vec D_L00_001B8C80[];
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern void anim_start_blended(void *, int, int, int);
extern void start_equipped_item_animation(void);
extern void cancel_hero_item_animation(void);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void hero_l00_set_action(int, int);
extern void copy_matrix3x4(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float vec_length_xy(void *);
extern char *ref_L00_003C6298_00(void *, void *, void *, void *);
extern char *moby_get_private_value_0(void *);
extern float IntToFloat(int);
extern float math_lerp_float(float, float, float);
extern int math_update_angle_and_blend(void *, int, int, float);
extern void gauge_popup_show(int, int, int, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index(int, int);
extern int PlayMobySound(int, int, void *);
extern void *sheep_spawn_from_object(void *);
extern void lightning_l00_beam_update(void *);
extern int gfx_add_point_light(float, void *, int, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void gfx_free_point_light(int);
extern void snd_stop_voice(int);
extern void anim_start_blended_with_flags(void *, int, int, int, int);

/* Per-frame update of the Sheepinator weapon. While fire is held it aims the beam, picks a target, drains its health, turns it into a sheep when done, and plays the light and sound. When fire is released it fades the light and stops the sound. */
void sheepinator_update(char *owner)
{
    Vec direction;
    union {
        struct { Vec matrix[3], inverse[4]; } aim;
        struct { Vec offset, point; } light;
    } work;
    BeamContext *context = FIELD(owner, BeamContext *, 0x68);
    int special;
    int allowed;
    char *target, *definition;
    char *weapon;
    int upgraded;
    float rate, scale;

    special = 0;
    if (g_hero_state.weapon == 3) special = 1;
    if (!FIELD(owner, unsigned char, 0x20)) {
        FIELD(owner, unsigned char, 0x20) = 1;
        D_L00_001B2A04 = -1;
        D_L00_001B2A0C = -1;
        D_L00_001B2A08 = 0;
    }
    FastDecTimer(&context->timer);
    allowed = 1;
    if (g_hero_state.state == 29) {
        if (!math_fast_float_d(&g_hero_state.timer)) allowed = 0;
    } else g_hero_state.timer = 40;

    if ((unsigned int)g_hero_state.mode < 2 &&
        (D_00138320 & g_hero_state.input) && allowed) {
        if (FIELD(owner, unsigned char, 0x43) != 2)
            anim_start_blended(owner, 2, 0, 0);
        if (!g_hero_state.flag) start_equipped_item_animation();
        if (!context->active) {
            context->active = 1;
            if (D_0018C360[16].count < 65535) D_0018C360[16].count++;
            if (D_001A7390 > D_0018C360[16].maximum) D_0018C360[16].maximum = D_001A7390;
            D_0018C360[16].levels = (D_0018C360[16].levels | (1u << g_current_map_index)) | 0x80000000u;
        }
        if (!context->timer) context->timer = 15;
        moby_transform_joint_to_world(owner, 0, context);
        if (g_hero_state.state == 1) hero_l00_set_action(29, 1);
        direction.q = 0;
        if (g_hero_state.state == 29 &&
            (FIELD(g_hero_state.object, unsigned short, 0x34) & 1)) {
            copy_matrix3x4(work.aim.matrix, D_L00_001B8C80);
            matrix_from_basis_rows(work.aim.inverse, work.aim.matrix);
            direction.f[2] = 1.0f;
            transform_vector(&direction, &direction, work.aim.inverse);
        } else if (g_hero_state.aiming == 1) {
            FastVecScale(&direction, owner + 0xD0, -1.0f);
        } else {
            direction.f[0] = 1.0f;
            matrix_mul_vec3(&direction, &direction, g_hero_state.matrix);
        }
        context->yaw = mat_fast_helper_a(direction.f[0], direction.f[1]);
        context->pitch = mat_fast_helper_a(vec_length_xy(&direction), direction.f[2]);
        work.aim.matrix[0].q = context->position.q;
        target = ref_L00_003C6298_00(owner, work.aim.matrix, &context->yaw, &context->pitch);
        math_fast_float_d(&context->cooldown);
        if (context->target) {
            unsigned char state = FIELD(context->target, unsigned char, 0x20);
            if (state == 254) goto clear_target;
            if (state == 253) {
clear_target:
                context->target = 0;
                context->cooldown = 0;
            }
        }
        if (!target) {
            if (!context->cooldown) goto no_target;
        } else {
            definition = moby_get_private_value_0(target);
            if (target != context->target && !context->cooldown) {
                context->target = target;
                context->health = IntToFloat(FIELD(definition, short, 4));
                context->remaining = FIELD(definition, float, 0);
                context->cooldown = 30;
                if (context->health <= 1.0f) context->remaining = 0.0f;
            }
        }
        {
            float ticks = 1.0f;
            weapon = (char *)&g_weapon_l00_table[D_00139578];
            upgraded = 0;
            if (FIELD(weapon, int, 0)) upgraded = FIELD(weapon, unsigned char, 4) == 2;
            if (upgraded) D_L00_001AFFA8 = 35.0f;
            else D_L00_001AFFA8 = 10.0f;
            scale = ticks * 0.0166666675f;
            context->remaining -= D_L00_001AFFA8 * scale;
            if (context->remaining < 0.0f) context->remaining = 0.0f;
            D_L00_001AFFC8 = context->remaining / context->health;
            goto have_target;
        }
no_target:
        D_L00_001AFFC8 = 1.0f;
have_target:
        rate = math_lerp_float(D_L00_001AFFB8[0], D_L00_001AFFB8[1], D_L00_001AFFC8);
        gauge_popup_show(1, math_update_angle_and_blend(context->beam, D_L00_001AFFB0_sda, D_L00_001AFFB0[1], rate * 0.0002908882452175021f), 0, D_L00_001AFFC8);
        if (context->target && context->remaining <= 0.0f) {
            int target_class = FIELD(context->target, short, 0xAA);
            if (g_current_map_index == 12 && target_class == 0xFB4 /* Mutant Test-Squirrel */) {
                D_L00_001B0E30[0] = D_L00_001B0E30[0] + 1;
                if (D_L00_001B0E30[0] >= 16 && !D_001A7A60[22]) {
                    D_001A7A60[22] = 1;
                    snd_play_from_global_bank(1, 0, 0);
                    value_set_entry_by_index(0x1233, -1);
                    D_L00_001A903C[0] = 1;
                }
            }
            PlayMobySound(3, 0, owner);
            sheep_spawn_from_object(context->target);
            D_L00_001AFFAC++;
            context->target = 0;
        }
        lightning_l00_beam_update(owner);
        if (D_L00_001B2A04 == -1)
            D_L00_001B2A04 = gfx_add_point_light(7.5f, owner + 0x10, 0x207F7F, 0.0f);
        if (D_L00_001B2A04 >= 0) {
            float light_x, light_y, light_z;
            Light *light;
            D_L00_001B2A08 = 20;
            vec_scale_to_length(&work.light.offset, owner + 0xD0, -0.5f);
            FastVecAdd(&work.light.point, context, &work.light.offset);
            light_x = work.light.point.f[0];
            light_y = work.light.point.f[1];
            light_z = work.light.point.f[2];
            light = &D_L00_001C6F40[D_L00_001B2A04];
            light->position.f[3] = 7.5f;
            light->position.f[1] = light_y;
            light->position.f[2] = light_z;
            light->position.f[0] = light_x;
        }
        if (!snd_is_voice_playing_for_owner(owner, D_L00_001B2A0C))
            D_L00_001B2A0C_sda = PlayMobySound(1, 4, owner);
    } else {
        context->target = 0;
        context->active = 0;
        context->cooldown = 0;
        D_L00_001B2A00 = 1;
        if (D_L00_001B2A04 >= 0) {
            float light_x2, light_y2, light_z2;
            Light *light;
            vec_scale_to_length(&direction, owner + 0xD0, -0.5f);
            FastVecAdd(&work.light.offset, context, &direction);
            light_x2 = work.light.offset.f[0];
            light_y2 = work.light.offset.f[1];
            light_z2 = work.light.offset.f[2];
            light = &D_L00_001C6F40[D_L00_001B2A04];
            light->position.f[2] = light_z2;
            light->position.f[3] = 7.5f;
            light->position.f[0] = light_x2;
            light->position.f[1] = light_y2;
            rate = IntToFloat(D_L00_001B2A08) * 0.05f;
            {
                Light *color = &D_L00_001C6F40[D_L00_001B2A04];
                FIELD(color, float, 0) = rate;
                FIELD(color, float, 4) = rate;
                FIELD(color, float, 8) = rate * 0.25f;
            }
            if (math_fast_float_d(&D_L00_001B2A08)) {
                gfx_free_point_light(D_L00_001B2A04);
                D_L00_001B2A04 = -1;
            }
        }
        if (D_L00_001B2A04 >= 0) {
            if (D_L00_001B2A08_sda) goto sound_cleanup;
            gfx_free_point_light(D_L00_001B2A04);
            D_L00_001B2A04 = -1;
        }
sound_cleanup:
        if (D_L00_001B2A0C >= 0) {
            int sound = D_L00_001B2A0C;
            if (sound != -1) {
                SoundView *entry = (SoundView *)(g_sound_state + sound * 0x70);
                if (entry->owner == owner && entry->active) snd_stop_voice(sound);
            }
            D_L00_001B2A0C = -1;
        }
        if (FIELD(owner, unsigned char, 0x60) & 2) anim_start_blended_with_flags(owner, 1, 0, 1, 0);
        cancel_hero_item_animation();
    }
    if (special && D_L00_001B2A04 >= 0) {
        gfx_free_point_light(D_L00_001B2A04);
        D_L00_001B2A04 = -1;
    }
}
