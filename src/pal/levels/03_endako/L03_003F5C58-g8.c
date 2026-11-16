#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 pad00[0x20];
    float health;
    s16 max_health;
    u8 pad26[2];
    u8 mode28;
    u8 pad29[0x2E - 0x29];
    u8 hit_mode;
    u8 pad2F[0x48 - 0x2F];
    u8 timer48;
    u8 pad49;
    u8 timer4A;
    u8 pad4B[0x70 - 0x4B];
    u8 hit70[7];
    u8 timer77;
    u8 pad78[0x88 - 0x78];
    int path;
    u8 pad8C[0xA4 - 0x8C];
    int spawn_record;
    int start_record;
    u8 padAC[0x290 - 0xAC];
    Quad home;
    u8 pad2A0[0x2B0 - 0x2A0];
    Quad start;
    u8 pad2C0[0x2CC - 0x2C0];
    int *route;
    u8 pad2D0[0x2DC - 0x2D0];
    int route_index;
    u8 pad2E0[0x308 - 0x2E0];
    u8 stage;
    u8 pad309[2];
    u8 flag30B;
    u8 pad30C[0x314 - 0x30C];
    int entries[7];
    int active;
    float threshold;
    u8 pad338[0x3C2 - 0x338];
    s16 difficulty;
    u8 pad3C4[0x3CC - 0x3C4];
    int target;
} DamageState;
typedef struct { int count; u8 pad[0xC]; float point[1][4]; } EntityPath;
extern int FloatToInt(float);
extern void moby_set_flag_bit(void *, int);
extern void moby_mark_spawned(void *);
extern int level_get_difficulty_scaled(int);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void endako_boss_process_group(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern int PlayMobySound(int, int, void *);
extern void gfx_start_color_fade_pal(void *, void *);
extern f32 ApproachValue(void *, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern u8 *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern void moby_fade_out_update_pal(void);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void endako_boss_play_voice_lines_pal(void *);
extern u8 *g_moby_record_base[] __attribute__((sda));
extern u8 g_moby_group_flags[] NOT_SDA;
extern int g_current_map_index[] __attribute__((sda));
extern u8 *g_path_l03_entry_table[] NOT_SDA;
extern float g_endako_boss_damage_scale __attribute__((sda));

/* Endako boss damage update: sets the boss up on its first frame (health by difficulty, path
   points), then takes hits, sheds armour pieces as health drops and dies at zero. */
void endako_boss_update_damage_pal(u8 *entity) {
    DamageState *state = *(DamageState **)(entity + 0x68);
    u8 *hit, *effect;
    EntityPath *path;
    int index, count, part, i, bit;
    float amount;
    union { Quad q; float f[4]; } local;

    if (entity[0x20] == 0) {
        state->timer48 = FloatToInt(30);
        state->timer4A = FloatToInt(32);
        state->hit_mode = 1;
        moby_set_flag_bit(g_moby_record_base[0] + (state->start_record << 8), 1);
        if (g_moby_group_flags[(entity[0xB0] & 0x7F) + (g_current_map_index[0] << 4)] & 0x80) {
            moby_mark_spawned(entity);
            return;
        }
        state->difficulty = level_get_difficulty_scaled(entity[0xB0]);
        switch (state->difficulty) {
        case 2:
            state->max_health = FloatToInt(state->max_health * 0.9f);
            break;
        case 1:
            state->max_health = FloatToInt(state->max_health * 0.7f);
            break;
        }
        state->target = -1;
        state->health = state->max_health;
        *(u16 *)(entity + 0x7C) = 0x3F;
        entity[0x30] = 255;
        *(u16 *)(entity + 0x32) += 0x40;
        state->mode28 = 3;
        state->threshold = state->health * 0.75f;
        qcopy(&state->home, entity + 0x10);
        qcopy(&state->start, entity + 0x10);
        *(int *)(entity + 0x98) = 0;
        *(u16 *)(entity + 0x34) = (*(u16 *)(entity + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(entity, 1, 0);
        if (entity[0x43]) {
            anim_start_blended_pal(entity, 0, 0, 0);
        }
        state->flag30B = 1;
        state->active = 1;
        path = (EntityPath *)g_path_l03_entry_table[state->path];
        for (index = 0, count = 0; index < path->count; index++) {
            if (path->point[index][3] >= 0) {
                state->entries[count] = index;
                count++;
                if (count >= 7) {
                    break;
                }
            }
        }
        moby_set_flag_bit(g_moby_record_base[0] + (state->spawn_record << 8), 1);
        endako_boss_process_group(entity);
    }
    *(float *)(entity + 0x2C) = *(float *)(*(u8 **)(entity + 0x24) + 0x24) * g_endako_boss_damage_scale;

    hit = part_find_owned_effect_slot(entity, 0x10000, 0);
    if (hit && *(u8 **)(hit + 0x20) && *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0x9DF) {
        hit = 0;
    }
    amount = moby_update_aim_target_strength_pal(entity, hit);
    if (amount != 0 || state->hit_mode == 2) {
        state->timer77 = 150;
        PlayMobySound(1, 0, entity);
        gfx_start_color_fade_pal(entity, state->hit70);
        if (entity[0x95]) {
            if (state->hit_mode == 2) {
                state->health = 0;
            } else {
                ApproachValue(&state->health, 0, amount);
            }
            if (state->health == 0 && entity[0x20] != 14 && entity[0x20] != 15) {
                moby_set_state(entity, 14, 1);
            } else if (state->threshold > 0 && state->health < state->threshold) {
                for (part = 0; part < 2; part++) {
                    i = state->stage * 2 + part;
                    bit = 1 << i;
                    local.q = 0;
                    local.f[1] = 0.14000002f;
                    local.f[2] = 0.10000001f;
                    if (part) {
                        local.f[1] = -0.14000002f;
                    }
                    matrix_mul_vec3(&local, &local, entity + 0xC0);
                    effect = cam_moby_create_pal(entity, 1, *(s16 *)(entity + 0xAA), i, entity + 0x10,
                                           entity + 0xF0, &local, 255, 30, 15);
                    *(void **)(effect + 0x64) = moby_fade_out_update_pal;
                    *(u16 *)(entity + 0x7C) &= ~bit;
                }
                state->stage++;
                moby_set_state(entity, 13, 6);
                state->threshold = (FloatToInt(state->health * 4 / state->max_health) * state->max_health) * 0.25f;
            }
        } else if (entity[0x20] == 2) {
            moby_set_state(entity, 3, -1);
            state->route_index = *state->route - 1;
        }
    }
    if ((unsigned)(entity[0x20] - 6) < 8) {
        weapon_select_aim_target(entity, -1, 0, 0, 16, 8);
    }
    state->hit_mode = 1;
    endako_boss_play_voice_lines_pal(entity);
    entity[0xA8] = 255;
}
