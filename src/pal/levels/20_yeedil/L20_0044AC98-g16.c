#include "names.h"
/* func_PAL_L20_0044AC98, the PAL copy of func_L20_004451C0: the same C with the rates at 50 Hz
   and the spawn timer scaled by 5/6.
   func_L20_004451C0: the launch platform's update (the Yeedil twin of func_L18_0042FBC8).
   Own unit, flags -O2 -G16 -ffunction-sections -Wa,-G16 (the -g16 precedent rows in
   config/cflags.txt): the two 16-byte vectors D_L20_001B2290/D_L20_001B22A0 are reached
   through $gp (addiu $aN,$gp,..), which -G8 does not give a 16-byte object.
   D_L20_001A8F20 is MACRO_ADDR, so its address is one `la` macro that the assembler
   expands to an adjacent lui/addiu, after the other argument moves as in retail (with a
   split address the lui is scheduled first). */
#include "common.h"

extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength(void *, void *);
extern void gfx_start_color_fade(void *, void *);
extern void gfx_update_color_fade(void *, void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern int IsPointInCuboid(void *, int);
extern void snd_stop_voice(int);
extern int flag_set_first_pending(void *);
extern float math_random_float_range(float, float);
extern int PlayMobySound(int, int, void *);
extern float FastAddRotations(float, float);
extern u8 *protopet_count_group(int, int *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern void protopet_launch_shot(void *, void *, void *);
extern int math_random_int_range(int, int);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void SetDeathBits(void *, int, int);
extern void moby_mark_spawned(void *);

extern float g_launch_platform_lift_max __attribute__((sda));
extern float g_launch_platform_spin_x_max __attribute__((sda));
extern float g_launch_platform_spin_y_max __attribute__((sda));
extern float g_launch_platform_jitter __attribute__((sda));
extern float g_launch_platform_speed __attribute__((sda));
extern float g_launch_platform_gravity __attribute__((sda));
extern int g_launch_platform_spawn_min __attribute__((sda));
extern int g_launch_platform_spawn_max __attribute__((sda));
extern float g_launch_platform_spawn_offset[4] __attribute__((sda));
extern float g_launch_platform_direction[4] __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_effect_color_table[] MACRO_ADDR;

typedef struct {
    u8 pad00[0x20];
    float timer;
    s16 initialized;
    u8 pad26[0x30 - 0x26];
    float scale;
    u8 pad34[0x50 - 0x34];
    u8 effect[0x10];
    float spin_x;
    float spin_y;
    u8 pad68[0x70 - 0x68];
    int start_id;
    int stop_id;
    int group;
    float rest_height;
    float vertical_speed;
    int spawn_timer;
    int sound;
} PlatformState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x68 - 0x21];
    PlatformState *vars;
    u8 pad6C[0x96 - 0x6C];
    u16 frames;
    u8 pad98[0xA8 - 0x98];
    u8 flag_a8;
    u8 padA9[0xC0 - 0xA9];
    float matrix[3][4];
    float rotation[4];
} PlatformObject;

/* The sound slots: 0x70 bytes apart, the owner at +0x88 and the active byte at +0x74. */
extern u8 g_sound_state[];

/* Runs the launch platform (moby class 4588). It shakes and bounces while the hero is on it, then fires out its cargo and blows up. (PAL: 50 Hz timings) */
void launch_platform_update_pal(PlatformObject *self) {
    PlatformState *vars = self->vars;
    float dt;
    float zero;
    int count;
    u8 *protopet;
    float velocity[4];
    float position[4];
    float offset[4];
    float tip[4];

    dt = moby_update_aim_target_strength(self, part_find_owned_effect_slot(self, 0x10000, 0));
    vars->timer -= dt;
    if (dt > 0.0f) {
        gfx_start_color_fade(self, vars->effect);
        if (vars->timer <= 0.0f) {
            moby_set_state(self, 3, -1);
        }
    }
    self->flag_a8 = 0xFF;
    gfx_update_color_fade(self, vars->effect);

    switch (self->state) {
    case 0:
        vars->rest_height = self->position[2];
        if (vars->initialized == 0) {
            vars->initialized = 1;
            vars->timer = 1.0f;
        }
        vars->spawn_timer = -1;
        vars->scale = 1.0f;
        moby_set_state(self, 1, -1);
        vars->sound = -1;
        break;
    case 1:
        if (math_random_int_below(2) == 0 && vars->start_id != -1) {
            if (IsPointInCuboid(g_hero_position, vars->stop_id)) {
                moby_set_state(self, 3, -1);
            } else if (IsPointInCuboid(g_hero_position, vars->start_id)) {
                moby_set_state(self, 2, -1);
            }
        }
        break;
    case 2:
        if (math_random_int_below(2) == 0 && IsPointInCuboid(g_hero_position, vars->stop_id)) {
            moby_set_state(self, 3, -1);
            if (vars->sound != -1) {
                u8 *slot = g_sound_state + vars->sound * 0x70;

                if (*(PlatformObject **)(slot + 0x88) == self && slot[0x74] != 0) {
                    snd_stop_voice(vars->sound);
                }
            }
            vars->sound = -1;
        }
        if (flag_set_first_pending(self)) {
            self->rotation[0] = 0;
            self->rotation[1] = 0;
            zero = self->rotation[0];
            self->position[2] = vars->rest_height;
            vars->vertical_speed += math_random_float_range(zero, g_launch_platform_lift_max * 0.020000001f);
            vars->spin_x = math_random_float_range(zero, g_launch_platform_spin_x_max * 0.0003490659f);
            vars->spin_y = math_random_float_range(zero, g_launch_platform_spin_y_max * 0.0003490659f);
            self->position[2] = vars->rest_height;
        }
        {
            u8 *slot = g_sound_state + vars->sound * 0x70;

            if (*(PlatformObject **)(slot + 0x88) != self || slot[0x74] == 0) {
                vars->sound = PlayMobySound(0, 4, self);
            }
        }
        if (self->position[2] >= vars->rest_height) {
            self->position[2] += vars->vertical_speed;
            vars->vertical_speed -= g_launch_platform_gravity * 0.00040000002f;
            if (vars->vertical_speed > 0.0f) {
                self->rotation[0] = FastAddRotations(vars->spin_x, self->rotation[0]);
                self->rotation[1] = FastAddRotations(vars->spin_y, self->rotation[1]);
            } else {
                self->rotation[0] = FastAddRotations(-vars->spin_x, self->rotation[0]);
                self->rotation[1] = FastAddRotations(-vars->spin_y, self->rotation[1]);
            }
        } else {
            moby_set_state(self, 2, -1);
        }
        break;
    case 3:
        count = 0;
        for (protopet = protopet_count_group(vars->group, &count); protopet != 0; protopet = protopet_count_group(vars->group, &count)) {
            vec_scale_to_length(velocity, g_launch_platform_direction, g_launch_platform_speed * 0.020000001f);
            matrix_mul_vec3(velocity, velocity, self->matrix);
            vec_add_random_offset(velocity, g_launch_platform_jitter * 0.020000001f);
            matrix_mul_vec3(position, g_launch_platform_spawn_offset, self->matrix);
            FastVecAdd(position, position, self->position);
            vec_scale_to_length(offset, velocity, 0.3f);
            add_vectors(tip, position, offset);
            protopet_launch_shot(protopet, position, velocity);
            *(PlatformObject **)(protopet + 0xB8) = self;
            vars->spawn_timer = ((s32)math_random_int_range(g_launch_platform_spawn_min, g_launch_platform_spawn_max) * 5 + 2) / 6;
        }
        SpawnExplosion(self->position, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        part_spawn_masked_debris(self, 0x1FF, g_effect_color_table, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(1, 0, self);
        SetDeathBits(self, 0, 3);
        moby_mark_spawned(self);
        return;
    }
    if (self->frames <= 0xFFFE) {
        self->frames++;
    }
}
