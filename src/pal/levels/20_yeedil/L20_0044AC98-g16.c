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
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void SetDeathBits(void *, int, int);
extern void moby_mark_spawned(void *);

extern float D_L20_001B2260 __attribute__((sda));
extern float D_L20_001B2264 __attribute__((sda));
extern float D_L20_001B2268 __attribute__((sda));
extern float D_L20_001B226C __attribute__((sda));
extern float D_L20_001B2270 __attribute__((sda));
extern float D_L20_001B227C __attribute__((sda));
extern int D_L20_001B2280 __attribute__((sda));
extern int D_L20_001B2284 __attribute__((sda));
extern float D_L20_001B2290[4] __attribute__((sda));
extern float D_L20_001B22A0[4] __attribute__((sda));
extern u8 g_hero_position[];
extern u8 D_L20_001A8F20[] MACRO_ADDR;

typedef struct {
    u8 pad00[0x20];
    float timer;
    s16 initialized;
    u8 pad26[0x30 - 0x26];
    float scale;
    u8 pad34[0x50 - 0x34];
    u8 effect[0x10];
    float spinX;
    float spinY;
    u8 pad68[0x70 - 0x68];
    int startId;
    int stopId;
    int group;
    float restHeight;
    float verticalSpeed;
    int spawnTimer;
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
    u8 flagA8;
    u8 padA9[0xC0 - 0xA9];
    float matrix[3][4];
    float rotation[4];
} PlatformObject;

/* The sound slots: 0x70 bytes apart, the owner at +0x88 and the active byte at +0x74. */
extern u8 g_sound_state[];

void func_PAL_L20_0044AC98(PlatformObject *self) {
    PlatformState *s = self->vars;
    float dt;
    float zero;
    int count;
    u8 *p;
    float velocity[4];
    float position[4];
    float offset[4];
    float tip[4];

    dt = moby_update_aim_target_strength(self, part_find_owned_effect_slot(self, 0x10000, 0));
    s->timer -= dt;
    if (dt > 0.0f) {
        gfx_start_color_fade(self, s->effect);
        if (s->timer <= 0.0f) {
            moby_set_state(self, 3, -1);
        }
    }
    self->flagA8 = 0xFF;
    gfx_update_color_fade(self, s->effect);

    switch (self->state) {
    case 0:
        s->restHeight = self->position[2];
        if (s->initialized == 0) {
            s->initialized = 1;
            s->timer = 1.0f;
        }
        s->spawnTimer = -1;
        s->scale = 1.0f;
        moby_set_state(self, 1, -1);
        s->sound = -1;
        break;
    case 1:
        if (math_random_int_below(2) == 0 && s->startId != -1) {
            if (IsPointInCuboid(g_hero_position, s->stopId)) {
                moby_set_state(self, 3, -1);
            } else if (IsPointInCuboid(g_hero_position, s->startId)) {
                moby_set_state(self, 2, -1);
            }
        }
        break;
    case 2:
        if (math_random_int_below(2) == 0 && IsPointInCuboid(g_hero_position, s->stopId)) {
            moby_set_state(self, 3, -1);
            if (s->sound != -1) {
                u8 *slot = g_sound_state + s->sound * 0x70;

                if (*(PlatformObject **)(slot + 0x88) == self && slot[0x74] != 0) {
                    snd_stop_voice(s->sound);
                }
            }
            s->sound = -1;
        }
        if (flag_set_first_pending(self)) {
            self->rotation[0] = 0;
            self->rotation[1] = 0;
            zero = self->rotation[0];
            self->position[2] = s->restHeight;
            s->verticalSpeed += math_random_float_range(zero, D_L20_001B2260 * 0.020000001f);
            s->spinX = math_random_float_range(zero, D_L20_001B2264 * 0.0003490659f);
            s->spinY = math_random_float_range(zero, D_L20_001B2268 * 0.0003490659f);
            self->position[2] = s->restHeight;
        }
        {
            u8 *slot = g_sound_state + s->sound * 0x70;

            if (*(PlatformObject **)(slot + 0x88) != self || slot[0x74] == 0) {
                s->sound = PlayMobySound(0, 4, self);
            }
        }
        if (self->position[2] >= s->restHeight) {
            self->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L20_001B227C * 0.00040000002f;
            if (s->verticalSpeed > 0.0f) {
                self->rotation[0] = FastAddRotations(s->spinX, self->rotation[0]);
                self->rotation[1] = FastAddRotations(s->spinY, self->rotation[1]);
            } else {
                self->rotation[0] = FastAddRotations(-s->spinX, self->rotation[0]);
                self->rotation[1] = FastAddRotations(-s->spinY, self->rotation[1]);
            }
        } else {
            moby_set_state(self, 2, -1);
        }
        break;
    case 3:
        count = 0;
        for (p = protopet_count_group(s->group, &count); p != 0; p = protopet_count_group(s->group, &count)) {
            vec_scale_to_length(velocity, D_L20_001B22A0, D_L20_001B2270 * 0.020000001f);
            matrix_mul_vec3(velocity, velocity, self->matrix);
            vec_add_random_offset(velocity, D_L20_001B226C * 0.020000001f);
            matrix_mul_vec3(position, D_L20_001B2290, self->matrix);
            FastVecAdd(position, position, self->position);
            vec_scale_to_length(offset, velocity, 0.3f);
            add_vectors(tip, position, offset);
            protopet_launch_shot(p, position, velocity);
            *(PlatformObject **)(p + 0xB8) = self;
            s->spawnTimer = ((s32)math_random_int_range(D_L20_001B2280, D_L20_001B2284) * 5 + 2) / 6;
        }
        SpawnExplosion(self->position, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        part_spawn_masked_debris(self, 0x1FF, D_L20_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(1, 0, self);
        SetDeathBits(self, 0, 3);
        moby_mark_spawned(self);
        return;
    }
    if (self->frames <= 0xFFFE) {
        self->frames++;
    }
}
