#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L03_001A8F00;
extern char D_L03_001A8F20[] __attribute__((sda)), D_L03_001BFDE0[], g_sound_state[];
extern float D_L03_001B0590 __attribute__((sda)), D_L03_001B0594 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern int moby_transform_point_and_rotation_by_parent(void *,void *,void *,void *,void *,void *);
extern void FastVecSub(void *,void *,void *),vec_transform_by_object_or_given(void *,void *,void *,int);
extern void lerp_vector(void *,void *,void *,float),FastVecAdd(void *,void *,void *);
extern float ApproachValue(void *,float,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void moby_set_state(void *,int,int),make_hit_descriptor(void *,void *,int,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern float math_random_angle(void),math_random_float_range(float,float),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void part_spawn_emitter_pair(void *,void *,void *),vec_random_direction(void *,float,float);
extern int math_random_int_below(int),PlayMobySound(int,int,void *),math_fast_float_d(void *);
extern void snd_stop_voice(int),gfx_add_draw_callback_first(void *,void *),gfx_l03_draw_glowing_beam(void *);

/* Interpolates the emitter position, keeps it relative to its attachment,
 * emits particles while active, and releases its sound and object after fading. */
void UpdateInterpolatedParticleEmitter(char *moby) {
    float offsetStep[4], rayStart[4], rayEnd[4], hit[12], spawnVec[4], spawnVel[4];
    char *vars = P(moby, 0x68), *position, *soundSlot;
    float angle, speed;

    if (D_L03_001A8F00 == 2) {
        moby_mark_spawned(moby);
        return;
    }
    position = moby + 0x10;
    if (P(vars, 0x40)) {
        moby_transform_point_and_rotation_by_parent(moby, P(vars, 0x40), position, moby + 0xF0, position, moby + 0xF0);
        FastVecSub(position, position, P(vars, 0x40) + 0x10);
        vec_transform_by_object_or_given(P(vars, 0x40), position, position, 0);
    }
    lerp_vector(offsetStep, vars, vars + 0x10, F(vars, 0x20));
    FastVecAdd(position, position, offsetStep);
    ApproachValue(vars + 0x20, 1.0f, F(vars, 0x24));
    if (P(vars, 0x40)) {
        matrix_mul_vec3(position, position, P(vars, 0x40) + 0xC0);
        FastVecAdd(position, position, P(vars, 0x40) + 0x10);
    }
    switch ((unsigned char)moby[0x20]) {
    case 0:
        I(vars, 0x3C) = -1;
        if (F(vars, 0x20) > 0.5f)
            moby_set_state(moby, 1, -1);
        break;
    case 1:
        qcopy(rayStart, position);
        qcopy(rayEnd, position);
        rayEnd[2] -= F(vars, 0x20) * 5.0f;
        make_hit_descriptor(hit, moby, 0x10001, D_L03_001A8F20, (float)I(vars, 0x38));
        if (CollLine(rayStart, rayEnd, 0, moby, hit) && !P(vars, 0x40)) {
            angle = math_random_angle();
            speed = math_random_float_range(0, 0.5f) * (1.0f / 60.0f);
            spawnVec[0] = math_fast_sin_or_cos_a(angle) * speed;
            spawnVec[1] = math_fast_sin_or_cos_b(angle) * speed;
            spawnVec[2] = 0;
            spawnVec[2] = math_random_float_range(1, 2) * (1.0f / 60.0f);
            part_spawn_emitter_pair(moby, D_L03_001BFDE0, spawnVec);
        }
        if (!P(vars, 0x40) && !math_random_int_below(2)) {
            qcopy(spawnVec, position);
            spawnVec[2] -= math_random_float_range(0, 5);
            vec_random_direction(spawnVel, 0, 1.0f / 30.0f);
            part_spawn_emitter_pair(moby, spawnVec, spawnVel);
        }
        soundSlot = (char *)(I(vars, 0x3C) * 0x70);
        soundSlot = (char *)((int)soundSlot + (int)g_sound_state);
        if (P(soundSlot, 0x88) != moby || !((unsigned char *)soundSlot)[0x74])
            I(vars, 0x3C) = PlayMobySound(0, 4, moby);
        if (F(vars, 0x34) < 1)
            ApproachValue(vars + 0x34, 1, 1.0f / 15.0f);
        if (math_fast_float_d(vars + 0x28))
            moby_set_state(moby, 2, -1);
        break;
    case 2:
        ApproachValue(vars + 0x34, 0, 1.0f / 30.0f);
        if (F(vars, 0x34) <= 0) {
            int handle = I(vars, 0x3C);
            if (handle != -1) {
                int offset = handle * 0x70;
                char *slot = g_sound_state + offset;
                if (P(slot, 0x88) == moby && ((unsigned char *)slot)[0x74])
                    snd_stop_voice(handle);
            }
            I(vars, 0x3C) = -1;
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    F(vars, 0x2C) += D_L03_001B0590 * (1.0f / 60.0f);
    if (F(vars, 0x2C) > 1)
        F(vars, 0x2C) -= 1;
    else if (F(vars, 0x2C) < 1)
        F(vars, 0x2C) += 1;
    F(vars, 0x30) += D_L03_001B0594 * (1.0f / 60.0f);
    if (F(vars, 0x30) > 1)
        F(vars, 0x30) -= 1;
    gfx_add_draw_callback_first(gfx_l03_draw_glowing_beam, moby);
}
